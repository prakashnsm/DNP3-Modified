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
#include "ThreadBoost.h"
#include "TimingTools.h"

namespace apl
{

ThreadBoost::ThreadBoost(Threadable* apRunnable) :
	ThreadBase(apRunnable),
	mEntryPoint(boost::bind(&Threadable::Start, apRunnable)),
	mpThread(NULL)
{

}

ThreadBoost::~ThreadBoost()
{
	RequestStop();
	WaitForStop();
}

void ThreadBoost::Start()
{
	assert(mpThread == NULL);
	mpThread = new boost::thread(mEntryPoint);
}

void ThreadBoost::WaitForStop()
{
	if(mpThread != NULL) mpThread->join();
	delete mpThread;
	mpThread = NULL;
}

void ThreadBoost::SleepFor(millis_t millis, bool ensureSleepForCorrectTime)
{

	if(ensureSleepForCorrectTime) {
		StopWatch sw;
		millis_t remain = millis;
		do {
			boost::this_thread::sleep(boost::posix_time::milliseconds(remain));
			millis_t remain = millis - sw.Elapsed(false);
			if(remain <= 0) break;
			boost::this_thread::yield();
		}
		while(true);
	}
	else {
		boost::this_thread::sleep(boost::posix_time::milliseconds(millis));
	}

}

};
