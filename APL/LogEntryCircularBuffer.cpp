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
#include "LogEntryCircularBuffer.h"
#include <iostream>

namespace apl
{

LogEntryCircularBuffer :: LogEntryCircularBuffer(size_t aMaxEntries) :
	mMaxEntries(aMaxEntries)
{

}

size_t LogEntryCircularBuffer :: Count()
{
	CriticalSection cs(&mLock);
	return mItemQueue.size();
}

bool LogEntryCircularBuffer :: ReadLog(LogEntry& mEntry, int aTimeout)
{
	CriticalSection cs(&mLock);

	if(CheckRead(mEntry)) return true;
	else {
		if(aTimeout < 0) cs.Wait();
		else if(aTimeout > 0) cs.TimedWait(aTimeout);
		if(CheckRead(mEntry)) return true;
	}

	return false;
}

void LogEntryCircularBuffer :: BlockUntilEntry()
{
	CriticalSection cs(&mLock);
	if(mItemQueue.size() == 0) cs.Wait();
}

bool LogEntryCircularBuffer :: CheckRead(LogEntry& aEntry)
{
	if(mItemQueue.size() > 0) {
		aEntry = mItemQueue.front(); //make a copy of the front of the queue
		mItemQueue.pop_front();
		return true;
	}
	else return false;
}

void LogEntryCircularBuffer :: AddIgnoreCode(int aCode)
{
	mIgnoreCodes.insert(aCode);
}

void LogEntryCircularBuffer :: Log( const apl::LogEntry& arEntry )
{
	if(mIgnoreCodes.find(arEntry.GetErrorCode()) == mIgnoreCodes.end()) { //only log messages that aren't ignored

		size_t num = 0;
		{
			CriticalSection cs(&mLock);
			num = mItemQueue.size();
			mItemQueue.push_back(arEntry);
			if(mItemQueue.size() > mMaxEntries) {
				mItemQueue.pop_front();
			}
			cs.Signal();
		}

		// only notify if the queue was empty
		if(num == 0) this->NotifyAll();
	}
}

void LogEntryCircularBuffer :: SetMaxEntries(size_t aMax)
{
	CriticalSection cs(&mLock);
	mMaxEntries = aMax;
	while(mItemQueue.size() > aMax) mItemQueue.pop_front();
}
}
