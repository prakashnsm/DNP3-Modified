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
#include "PhysicalLayerMonitor.h"

#include "IPhysicalLayerAsync.h"
#include "PhysicalLayerMonitorStates.h"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <assert.h>
#include "Logger.h"

namespace apl
{

PhysicalLayerMonitor::PhysicalLayerMonitor(Logger* apLogger, IPhysicalLayerAsync* apPhys, ITimerSource* apTimerSrc, millis_t aOpenRetry) :
	Loggable(apLogger),
	IHandlerAsync(apLogger),
	mpPhys(apPhys),
	mpTimerSrc(apTimerSrc),
	mpOpenTimer(NULL),
	mpState(MonitorStateInit::Inst()),
	mFinalShutdown(false),
	M_OPEN_RETRY(aOpenRetry)
{
	assert(apPhys != NULL);
	assert(apTimerSrc != NULL);
	mpPhys->SetHandler(this);
}

PhysicalLayerMonitor::~PhysicalLayerMonitor()
{}

PhysicalLayerState PhysicalLayerMonitor::GetState()
{
	return mpState->GetState();
}

/* ------ Public functions ----- */

void PhysicalLayerMonitor::AddObserver(IPhysicalLayerObserver* apObserver)
{
	assert(apObserver != NULL);
	CriticalSection cs(&mLock);
	mObservers.insert(apObserver);
}

bool PhysicalLayerMonitor::WaitForShutdown(millis_t aTimeoutMs)
{
	CriticalSection cs(&mLock);

	while(!mFinalShutdown) {
		if(aTimeoutMs < 0) cs.Wait();
		else {
			cs.TimedWait(aTimeoutMs);
			break;
		}
	}

	return mFinalShutdown;
}

void PhysicalLayerMonitor::ChangeState(IMonitorState* apState)
{
	LOG_BLOCK(LEV_INFO, mpState->ConvertToString() << " -> " << apState->ConvertToString() << " : " << mpPhys->ConvertStateToString());
	IMonitorState* pLast = mpState;

	CriticalSection cs(&mLock);
	mpState = apState;
	if(pLast->GetState() != apState->GetState()) {
		for(ObserverSet::iterator i = mObservers.begin(); i != mObservers.end(); ++i) (*i)->OnStateChange(apState->GetState());

		// signaling this way makes sure we're free and clear of the event that causes this
		// before someone else and deletes
		if(mpState->GetState() == PLS_SHUTDOWN) mpTimerSrc->Post(boost::bind(&PhysicalLayerMonitor::DoFinalShutdown, this));
	}
}

void PhysicalLayerMonitor::DoFinalShutdown()
{
	CriticalSection cs(&mLock);
	mFinalShutdown = true;
	cs.Broadcast();
}

/* ------- User facing events that occurs ------- */

void PhysicalLayerMonitor::Start()
{
	LOG_BLOCK(LEV_INFO, "Start()");
	mpState->OnStartRequest(this);
}

void PhysicalLayerMonitor::StartOne()
{
	LOG_BLOCK(LEV_INFO, "StartOne()");
	mpState->OnStartOneRequest(this);
}

void PhysicalLayerMonitor::Close()
{
	LOG_BLOCK(LEV_INFO, "Close()");
	mpState->OnCloseRequest(this);
}

void PhysicalLayerMonitor::Suspend()
{
	LOG_BLOCK(LEV_INFO, "Suspend()");
	mpState->OnSuspendRequest(this);
}

void PhysicalLayerMonitor::Shutdown()
{
	LOG_BLOCK(LEV_INFO, "Shutdown()");
	mpState->OnShutdownRequest(this);
}

/* ------- External events that occurs ------- */

void PhysicalLayerMonitor::OnOpenTimerExpiration()
{
	LOG_BLOCK(LEV_INFO, "OnOpenTimerExpiration()");
	assert(mpOpenTimer != NULL);
	mpOpenTimer = NULL;
	mpState->OnOpenTimeout(this);
}

void PhysicalLayerMonitor::_OnOpenFailure()
{
	LOG_BLOCK(LEV_INFO, "_OnOpenFailure()");
	mpState->OnOpenFailure(this);
	this->OnPhysicalLayerOpenFailureCallback();
}

void PhysicalLayerMonitor::_OnLowerLayerUp()
{
	LOG_BLOCK(LEV_INFO, "_OnLowerLayerUp");
	mpState->OnLayerOpen(this);
	this->OnPhysicalLayerOpenSuccessCallback();
}

void PhysicalLayerMonitor::_OnLowerLayerDown()
{
	LOG_BLOCK(LEV_INFO, "_OnLowerLayerDown");
	mpState->OnLayerClose(this);
	this->OnPhysicalLayerCloseCallback();
}

/* ------- Actions for the states ------- */

void PhysicalLayerMonitor::StartOpenTimer()
{
	assert(mpOpenTimer == NULL);
	mpOpenTimer = mpTimerSrc->Start(M_OPEN_RETRY, boost::bind(&PhysicalLayerMonitor::OnOpenTimerExpiration, this));
}

void PhysicalLayerMonitor::CancelOpenTimer()
{
	assert(mpOpenTimer != NULL);
	mpOpenTimer->Cancel();
	mpOpenTimer = NULL;
}

/* ------- Internal helper functions ------- */



}
