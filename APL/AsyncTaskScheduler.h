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
#ifndef __ASYNC_TASK_SCHEDULER_H_
#define __ASYNC_TASK_SCHEDULER_H_


#include <set>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "TimeSource.h"
#include "Lock.h"

namespace apl
{

class AsyncTaskBase;
class AsyncTaskGroup;
class ITimerSource;


/** Thread-safe object that coordinates multiple task groups and manages their lifecycle
*/
class AsyncTaskScheduler
{
	friend class AsyncTaskGroup;

public:

	AsyncTaskScheduler(ITimerSource* apTimerSrc, ITimeSource* apTimeSrc = TimeSource::Inst());
	~AsyncTaskScheduler();

	AsyncTaskGroup* CreateNewGroup();
	void ReleaseGroup(AsyncTaskGroup*);

private:
	SigLock mLock;

	ITimerSource* mpTimerSrc;
	ITimeSource* mpTimeSrc;
	typedef std::set<AsyncTaskGroup*> GroupSet;
	GroupSet mGroupSet;
};

}

#endif
