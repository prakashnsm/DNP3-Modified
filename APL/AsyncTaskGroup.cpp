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
#include "AsyncTaskGroup.h"

#include "AsyncTaskBase.h"
#include "AsyncTaskPeriodic.h"
#include "AsyncTaskNonPeriodic.h"
#include "AsyncTaskContinuous.h"
#include "AsyncTaskScheduler.h"
#include "Exception.h"

#include "ITimerSource.h"

#include <boost/foreach.hpp>
#include <boost/bind.hpp>

using namespace boost::posix_time;

namespace apl
{

AsyncTaskGroup::AsyncTaskGroup(ITimerSource* apTimerSrc, ITimeSource* apTimeSrc) :
	mIsRunning(false),
	mShutdown(false),
	mpTimerSrc(apTimerSrc),
	mpTimeSrc(apTimeSrc),
	mpTimer(NULL)
{

}

AsyncTaskGroup::~AsyncTaskGroup()
{
	this->Shutdown();

	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		delete p;
	}
}

AsyncTaskBase* AsyncTaskGroup::Add(millis_t aPeriod, millis_t aRetryDelay, int aPriority, const TaskHandler& arCallback, const std::string& arName)
{
	AsyncTaskBase* pTask;
	if(aPeriod >= 0)
		pTask = new AsyncTaskPeriodic(aPeriod, aRetryDelay, aPriority, arCallback, this, arName);
	else
		pTask = new AsyncTaskNonPeriodic(aRetryDelay, aPriority, arCallback, this, arName);

	mTaskVec.push_back(pTask);
	return pTask;
}

void AsyncTaskGroup::ResetTasks(int aMask)
{
	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		if(!p->IsRunning() && (p->GetFlags() & aMask)) p->Reset();
	}
}

AsyncTaskContinuous* AsyncTaskGroup::AddContinuous(int aPriority, const TaskHandler& arCallback, const std::string& arName)
{
	AsyncTaskContinuous* pTask = new AsyncTaskContinuous(aPriority, arCallback, this, arName);
	mTaskVec.push_back(pTask);
	return pTask;
}

void AsyncTaskGroup::Remove(AsyncTaskBase* apTask)
{
	for(TaskVec::iterator i = mTaskVec.begin(); i != mTaskVec.end(); ++i) {
		if(*i == apTask) {
			delete *i;
			mTaskVec.erase(i);
			return;
		}
	}
	throw ArgumentException(LOCATION, "Task not found");
}

void AsyncTaskGroup::Shutdown()
{
	if(mpTimer) {
		mpTimer->Cancel();
		mpTimer = NULL;
	}

	mShutdown = true;
}

void AsyncTaskGroup::Enable()
{
	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		p->SilentEnable();
	}
	this->CheckState();
}

void AsyncTaskGroup::Disable()
{
	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		p->SilentDisable();
	}
	this->CheckState();
}

void AsyncTaskGroup::Enable(int aMask)
{
	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		if((p->GetFlags() & aMask) != 0) p->SilentEnable();
	}
	this->CheckState();
}

void AsyncTaskGroup::Disable(int aMask)
{
	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		if((p->GetFlags() & aMask) != 0) p->SilentDisable();
	}
	this->CheckState();
}

AsyncTaskBase* AsyncTaskGroup::GetNext(const boost::posix_time::ptime& arTime)
{
	this->Update(arTime);
	TaskVec::iterator max = max_element(mTaskVec.begin(), mTaskVec.end(), AsyncTaskBase::LessThanGroupLevel);

	AsyncTaskBase* pRet = NULL;
	if(max != mTaskVec.end()) {
		AsyncTaskBase* p = *max;
		if(!p->IsRunning() && p->IsEnabled()) pRet = p;
	}

	return pRet;
}

void AsyncTaskGroup::CheckState()
{
	if(!mShutdown) {
		ptime now = GetUTC();
		AsyncTaskBase* pTask = GetNext(now);

		if(pTask == NULL) return;
		if(pTask->NextRunTime() == max_date_time) return;

		if(pTask->NextRunTime() <= now) {
			mIsRunning = true;
			pTask->Dispatch();
		}
		else {
			this->RestartTimer(pTask->NextRunTime());
		}
	}
}

void AsyncTaskGroup::OnCompletion()
{
	if(!mIsRunning) throw InvalidStateException(LOCATION, "Not running");
	mIsRunning = false;
	this->CheckState();
}

boost::posix_time::ptime AsyncTaskGroup::GetUTC() const
{
	return mpTimeSrc->GetUTC();
}

void AsyncTaskGroup::Update(const boost::posix_time::ptime& arTime)
{
	BOOST_FOREACH(AsyncTaskBase * p, mTaskVec) {
		p->UpdateTime(arTime);
	}
}

void AsyncTaskGroup::RestartTimer(const boost::posix_time::ptime& arTime)
{
	if(mpTimer != NULL) {
		if(mpTimer->ExpiresAt() != arTime) {
			mpTimer->Cancel();
			mpTimer = NULL;
		}
	}

	if(mpTimer == NULL)
		mpTimer = mpTimerSrc->Start(arTime, boost::bind(&AsyncTaskGroup::OnTimerExpiration, this));
}

void AsyncTaskGroup::OnTimerExpiration()
{
	mpTimer = NULL;
	this->CheckState();
}

} // end ns
