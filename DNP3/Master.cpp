//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Green Enery Corp licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//

#include "Master.h"

#include "MasterStates.h"
#include "ObjectReadIterator.h"
#include "ResponseLoader.h"
#include "VtoEventBufferAdapter.h"

#include <APL/DataInterfaces.h>
#include <APL/AsyncTaskInterfaces.h>
#include <APL/AsyncTaskGroup.h>
#include <APL/AsyncTaskBase.h>
#include <APL/AsyncTaskPeriodic.h>
#include <APL/AsyncTaskNonPeriodic.h>
#include <APL/Logger.h>
#include <APL/ITimerSource.h>
#include <APL/AsyncTaskContinuous.h>
#include <APL/CopyableBuffer.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

using namespace boost;

namespace apl
{
namespace dnp
{

Master::Master(Logger* apLogger, MasterConfig aCfg, IAppLayer* apAppLayer, IDataObserver* apPublisher, AsyncTaskGroup* apTaskGroup, ITimerSource* apTimerSrc, ITimeSource* apTimeSrc) :
	Loggable(apLogger),
	mVtoReader(apLogger),
	mVtoWriter(apLogger->GetSubLogger("VtoWriter"), aCfg.VtoWriterQueueSize),
	mRequest(aCfg.FragSize),
	mpAppLayer(apAppLayer),
	mpPublisher(apPublisher),
	mpTaskGroup(apTaskGroup),
	mpTimerSrc(apTimerSrc),
	mpTimeSrc(apTimeSrc),
	mpState(AMS_Closed::Inst()),
	mpTask(NULL),
	mpScheduledTask(NULL),
	mpObserver(aCfg.mpObserver),
	mState(SS_UNKNOWN),
	mSchedule(apTaskGroup, this, aCfg),
	mClassPoll(apLogger, apPublisher, &mVtoReader),
	mClearRestart(apLogger),
	mConfigureUnsol(apLogger),
	mTimeSync(apLogger, apTimeSrc),
	mExecuteBO(apLogger),
	mExecuteSP(apLogger),
	mVtoTransmitTask(apLogger, aCfg.FragSize, aCfg.UseNonStandardVtoFunction)
{
	/*
	 * Establish a link between the mCommandQueue and the
	 * mSchedule.mpCommandTask.  When new data is written to mCommandQueue,
	 * wake up mpCommandTask to process the data.
	 */
	mCommandQueue.SetNotifier(
	    mNotifierSource.Get(
	        boost::bind(
	            &AsyncTaskBase::Enable,
	            mSchedule.mpCommandTask
	        ),
	        mpTimerSrc
	    )
	);

	/*
	 * Establish a link between the mVtoWriter and the
	 * mSchedule.mpVtoTransmitTask.  When new data is written to
	 * mVtoWriter, wake up the mSchedule.mpVtoTransmitTask.
	 */
	mVtoWriter.AddObserver(
	    mNotifierSource.Get(
	        boost::bind(
	            &AsyncTaskBase::Enable,
	            mSchedule.mpVtoTransmitTask
	        ),
	        mpTimerSrc
	    )
	);

	/*
	 * Set the initial state of the communication link.
	 */
	this->UpdateState(SS_COMMS_DOWN);
}

void Master::UpdateState(StackStates aState)
{
	if(mState != aState) {
		LOG_BLOCK(LEV_INFO, "StackState: " << ConvertStackStateToString(aState));
		mState = aState;
		if(mpObserver != NULL) mpObserver->OnStateChange(aState);
		if(mState == SS_COMMS_UP) {
			mSchedule.mpVtoTransmitTask->Enable();
		}
	}
}

void Master::ProcessIIN(const IINField& arIIN)
{
	this->UpdateState(SS_COMMS_UP);

	bool check_state = false;

	//The clear IIN task only happens in response to detecting an IIN bit.
	if(arIIN.GetNeedTime()) {
		LOG_BLOCK(LEV_INFO, "Need time detected");
		mSchedule.mpTimeTask->SilentEnable();
		check_state = true;
	}

	if(mLastIIN.GetDeviceTrouble()) LOG_BLOCK(LEV_WARNING, "IIN Device trouble detected");

	if(mLastIIN.GetEventBufferOverflow()) LOG_BLOCK(LEV_WARNING, "Event buffer overflow detected");

	// If this is detected, we need to reset the startup tasks
	if(mLastIIN.GetDeviceRestart()) {
		LOG_BLOCK(LEV_WARNING, "Device restart detected");
		mSchedule.ResetStartupTasks();
		mSchedule.mpClearRestartTask->SilentEnable();
		check_state = true;
	}

	if(check_state) mpTaskGroup->CheckState();
}

void Master::ProcessCommand(ITask* apTask)
{
	CommandData info;

	if(mpState == AMS_Closed::Inst()) { //we're closed
		if(!mCommandQueue.RespondToCommand(CS_HARDWARE_ERROR)) apTask->Disable();
	}
	else {

		switch(mCommandQueue.Next()) {
		case(apl::CT_BINARY_OUTPUT): {
				apl::BinaryOutput cmd;
				mCommandQueue.Read(cmd, info);
				mExecuteBO.Set(cmd, info, true);
				mpState->StartTask(this, apTask, &mExecuteBO);
			}
			break;
		case(apl::CT_SETPOINT): {
				apl::Setpoint cmd;
				mCommandQueue.Read(cmd, info);
				mExecuteSP.Set(cmd, info, true);
				mpState->StartTask(this, apTask, &mExecuteSP);
			}
			break;
		default:
			apTask->Disable(); //no commands to be read
			break;
		}
	}
}

void Master::StartTask(MasterTaskBase* apMasterTask, bool aInit)
{
	if(aInit) apMasterTask->Init();
	apMasterTask->ConfigureRequest(mRequest);
	mpAppLayer->SendRequest(mRequest);
}

/* Tasks */

void Master::SyncTime(ITask* apTask)
{
	if(mLastIIN.GetNeedTime()) {
		mpState->StartTask(this, apTask, &mTimeSync);
	}
	else apTask->Disable();
}

void Master::WriteIIN(ITask* apTask)
{
	if(mLastIIN.GetDeviceRestart()) {
		mpState->StartTask(this, apTask, &mClearRestart);
	}
	else apTask->Disable();
}

void Master::IntegrityPoll(ITask* apTask)
{
	mClassPoll.Set(PC_CLASS_0);
	mpState->StartTask(this, apTask, &mClassPoll);
}

void Master::EventPoll(ITask* apTask, int aClassMask)
{
	mClassPoll.Set(aClassMask);
	mpState->StartTask(this, apTask, &mClassPoll);
}

void Master::ChangeUnsol(ITask* apTask, bool aEnable, int aClassMask)
{
	mConfigureUnsol.Set(aEnable, aClassMask);
	mpState->StartTask(this, apTask, &mConfigureUnsol);
}

void Master::TransmitVtoData(ITask* apTask)
{
	if(mpState == AMS_Closed::Inst()) apTask->Disable();
	else {
		size_t max = mVtoTransmitTask.mBuffer.NumAvailable();
		VtoEventBufferAdapter adapter(&mVtoTransmitTask.mBuffer);
		mVtoWriter.Flush(&adapter, max);

		LOG_BLOCK(LEV_DEBUG, "TransmitVtoData: " << std::boolalpha << mVtoTransmitTask.mBuffer.IsFull() << " size: " << mVtoTransmitTask.mBuffer.Size());

		/* Any data to transmit? */
		if (mVtoTransmitTask.mBuffer.Size() > 0) {
			/* Start the mVtoTransmitTask */
			mpState->StartTask(this, apTask, &mVtoTransmitTask);
		}
		else {
			/* Stop the mVtoTransmitTask */
			apTask->Disable();
		}
	}
}

/* Implement IAppUser */

void Master::OnLowerLayerUp()
{
	mpState->OnLowerLayerUp(this);
	mSchedule.EnableOnlineTasks();
}

void Master::OnLowerLayerDown()
{
	mpState->OnLowerLayerDown(this);
	mSchedule.DisableOnlineTasks();
	this->UpdateState(SS_COMMS_DOWN);
}

void Master::OnSolSendSuccess()
{
	mpState->OnSendSuccess(this);
}

void Master::OnSolFailure()
{
	this->UpdateState(SS_COMMS_DOWN);
	mpState->OnFailure(this);
}

void Master::OnUnsolSendSuccess()
{
	throw InvalidStateException(LOCATION, "Master can't send unsol");
}

void Master::OnUnsolFailure()
{
	throw InvalidStateException(LOCATION, "Master can't send unsol");
}

void Master::OnPartialResponse(const APDU& arAPDU)
{
	mLastIIN = arAPDU.GetIIN();
	this->ProcessIIN(mLastIIN);
	mpState->OnPartialResponse(this, arAPDU);
}

void Master::OnFinalResponse(const APDU& arAPDU)
{
	mLastIIN = arAPDU.GetIIN();
	this->ProcessIIN(arAPDU.GetIIN());
	mpState->OnFinalResponse(this, arAPDU);
}

void Master::OnUnsolResponse(const APDU& arAPDU)
{
	mLastIIN = arAPDU.GetIIN();
	this->ProcessIIN(mLastIIN);
	mpState->OnUnsolResponse(this, arAPDU);
}

/* Private functions */

void Master::ProcessDataResponse(const APDU& arResponse)
{
	try {
		ResponseLoader loader(this->mpLogger, this->mpPublisher, this->GetVtoReader());

		for(HeaderReadIterator hdr = arResponse.BeginRead(); !hdr.IsEnd(); ++hdr)
			loader.Process(hdr);
	}
	catch(Exception ex) {
		EXCEPTION_BLOCK(LEV_WARNING, ex)
	}
}

}
} //end ns

/* vim: set ts=4 sw=4: */
