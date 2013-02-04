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

#include "PhysicalLayerMonitorStates.h"

#include "Logger.h"
#include "Exception.h"
#include "IPhysicalLayerAsync.h"

#include <sstream>

namespace apl
{

/* --- MonitorStateActions --- */

void MonitorStateActions::ChangeState(PhysicalLayerMonitor* apContext, IMonitorState* apState)
{
	apContext->ChangeState(apState);
}

void MonitorStateActions::StartOpenTimer(PhysicalLayerMonitor* apContext)
{
	apContext->StartOpenTimer();
}

void MonitorStateActions::CancelOpenTimer(PhysicalLayerMonitor* apContext)
{
	apContext->CancelOpenTimer();
}

void MonitorStateActions::AsyncClose(PhysicalLayerMonitor* apContext)
{
	apContext->mpPhys->AsyncClose();
}

void MonitorStateActions::AsyncOpen(PhysicalLayerMonitor* apContext)
{
	apContext->mpPhys->AsyncOpen();
}

/* --- IMonitorState --- */

std::string IMonitorState::ConvertToString()
{
	std::ostringstream oss;
	oss << this->Name() << "(" << ConvertPhysicalLayerStateToString(this->GetState()) << ")";
	return oss.str();
}

/* --- ExceptsOnLayerOpen --- */

void ExceptsOnLayerOpen::OnLayerOpen(PhysicalLayerMonitor* apContext)
{
	throw InvalidStateException(LOCATION, "Not opening: " + this->Name());
}

/* --- NotOpening --- */

void NotOpening::OnOpenFailure(PhysicalLayerMonitor* apContext)
{
	throw InvalidStateException(LOCATION, "Not opening: " + this->Name());
}

/* --- NotOpen --- */

void NotOpen::OnLayerClose(PhysicalLayerMonitor* apContext)
{
	throw InvalidStateException(LOCATION, "Not open: " + this->Name());
}

/* --- NotWaitingForTimer --- */

void NotWaitingForTimer::OnOpenTimeout(PhysicalLayerMonitor* apContext)
{
	throw InvalidStateException(LOCATION, "Not waiting for timer: " + this->Name());
}

/* --- IgnoresClose --- */

void IgnoresClose::OnCloseRequest(PhysicalLayerMonitor* apContext)
{
	LOGGER_BLOCK(apContext->GetLogger(), LEV_DEBUG, "Ignoring Close(): " << this->Name());
}

/* --- IgnoresSuspend --- */

void IgnoresSuspend::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	LOGGER_BLOCK(apContext->GetLogger(), LEV_DEBUG, "Ignoring Suspend(): " << this->Name());
}

/* --- StartsOnClose --- */

void StartsOnClose::OnLayerClose(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspended::Inst());
	apContext->Start();
}

/* --- IgnoresShutdown --- */

void IgnoresShutdown::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	LOGGER_BLOCK(apContext->GetLogger(), LEV_DEBUG, "Ignoring Stop(): " << this->Name());
}

/* --- IgnoresStart --- */

void IgnoresStart::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	LOGGER_BLOCK(apContext->GetLogger(), LEV_DEBUG, "Ignoring Start(): " << this->Name());
}

/* --- IgnoresStartOne --- */

void IgnoresStartOne::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	LOGGER_BLOCK(apContext->GetLogger(), LEV_DEBUG, "Ignoring StartOne(): " << this->Name());
}

/* --- OpenFailureCausesWait --- */

void OpenFailureCausesWait::OnOpenFailure(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateWaiting::Inst());
	MonitorStateActions::StartOpenTimer(apContext);
}

/* --- WaitingBase --- */

void MonitorStateWaitingBase::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::CancelOpenTimer(apContext);
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspended::Inst());
}

void MonitorStateWaitingBase::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::CancelOpenTimer(apContext);
	MonitorStateActions::ChangeState(apContext, MonitorStateShutdown::Inst());
}

/* ----------------- Concrete ----------------- */


/* --- Shutdown --- */

MonitorStateShutdown MonitorStateShutdown::mInstance;

/* --- Suspended --- */

MonitorStateSuspended MonitorStateSuspended::mInstance;

/* --- Init --- */

MonitorStateInit MonitorStateInit::mInstance;

/* ---- SuspendedBase --- */
void MonitorStateSuspendedBase::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpening::Inst());
	MonitorStateActions::AsyncOpen(apContext);
}

void MonitorStateSuspendedBase::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningOne::Inst());
	MonitorStateActions::AsyncOpen(apContext);
}

void MonitorStateSuspendedBase::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateShutdown::Inst());
}

/* --- OpeningBase --- */

void MonitorStateOpeningBase::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningStopping::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpeningBase::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningSuspending::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

/* --- Opening --- */

MonitorStateOpening MonitorStateOpening::mInstance;

void MonitorStateOpening::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningOne::Inst());
}

void MonitorStateOpening::OnCloseRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningClosing::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpening::OnLayerOpen(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpen::Inst());
}

/* --- OpeningOne --- */

MonitorStateOpeningOne MonitorStateOpeningOne::mInstance;

void MonitorStateOpeningOne::OnOpenFailure(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspended::Inst());
}

void MonitorStateOpeningOne::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpening::Inst());
}

void MonitorStateOpeningOne::OnCloseRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningSuspending::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpeningOne::OnLayerOpen(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpenOne::Inst());
}

/* --- OpeningClosing --- */

MonitorStateOpeningClosing MonitorStateOpeningClosing::mInstance;

void MonitorStateOpeningClosing::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningSuspending::Inst());
}

void MonitorStateOpeningClosing::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningStopping::Inst());
}

void MonitorStateOpeningClosing::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningSuspending::Inst());
}

/* --- OpeningStopping --- */

MonitorStateOpeningStopping MonitorStateOpeningStopping::mInstance;

/* --- OpeningSuspending --- */

MonitorStateOpeningSuspending MonitorStateOpeningSuspending::mInstance;

void MonitorStateOpeningSuspending::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningClosing::Inst());
}

void MonitorStateOpeningSuspending::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningStopping::Inst());
}

/* --- Open --- */

MonitorStateOpen MonitorStateOpen::mInstance;

void MonitorStateOpen::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpenOne::Inst());
}

void MonitorStateOpen::OnCloseRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateClosing::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpen::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspending::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpen::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateShutingDown::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

/* --- OpenOne --- */

MonitorStateOpenOne MonitorStateOpenOne::mInstance;

void MonitorStateOpenOne::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateOpen::Inst());
}

void MonitorStateOpenOne::OnCloseRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspending::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpenOne::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspending::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpenOne::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateShutingDown::Inst());
	MonitorStateActions::AsyncClose(apContext);
}

void MonitorStateOpenOne::OnLayerClose(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspended::Inst());
}

/* --- Waiting --- */

MonitorStateWaiting MonitorStateWaiting::mInstance;

void MonitorStateWaiting::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateWaitingOne::Inst());
}

void MonitorStateWaiting::OnOpenTimeout(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::AsyncOpen(apContext);
	MonitorStateActions::ChangeState(apContext, MonitorStateOpening::Inst());
}

/* --- WaitingOne --- */

MonitorStateWaitingOne MonitorStateWaitingOne::mInstance;

void MonitorStateWaitingOne::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateWaiting::Inst());
}

void MonitorStateWaitingOne::OnOpenTimeout(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::AsyncOpen(apContext);
	MonitorStateActions::ChangeState(apContext, MonitorStateOpeningOne::Inst());
}

/* --- Closing --- */

MonitorStateClosing MonitorStateClosing::mInstance;

void MonitorStateClosing::OnStartOneRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspending::Inst());
}

void MonitorStateClosing::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateShutingDown::Inst());
}

void MonitorStateClosing::OnSuspendRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspending::Inst());
}

/* --- Suspending --- */

MonitorStateSuspending MonitorStateSuspending::mInstance;

void MonitorStateSuspending::OnLayerClose(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateSuspended::Inst());
}

void MonitorStateSuspending::OnStartRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateClosing::Inst());
}

void MonitorStateSuspending::OnShutdownRequest(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateShutingDown::Inst());
}

/* --- Stopping --- */

MonitorStateShutingDown MonitorStateShutingDown::mInstance;

void MonitorStateShutingDown::OnLayerClose(PhysicalLayerMonitor* apContext)
{
	MonitorStateActions::ChangeState(apContext, MonitorStateShutdown::Inst());
}

}
