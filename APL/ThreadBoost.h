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
#ifndef __THREAD_BOOST_H_
#define __THREAD_BOOST_H_

#include "ThreadBase.h"
#include "Types.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

namespace apl
{

class ThreadBoost : public ThreadBase
{

public:
	ThreadBoost(Threadable* apObj);
	virtual ~ThreadBoost ();

	void Start();
	void WaitForStop();
	static void SleepFor(millis_t millis, bool ensureSleepForCorrectTime = false);

private:

	boost::function0<void> mEntryPoint;
	boost::thread* mpThread;

};

}//end namespace

#endif
