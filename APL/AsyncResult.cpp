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

#include "AsyncResult.h"

namespace apl
{

AsyncResult::AsyncResult() : mIsComplete(false)
{
			
}

void AsyncResult::Complete()
{
	if(mIsComplete) throw InvalidStateException(LOCATION, "Async result is already complete");
	mIsComplete = true;
}

void AsyncResult::Success()
{
	CriticalSection cs(&mLock);	
	this->Complete();
	cs.Broadcast();
}

void AsyncResult::Failure(const FunctionVoidZero& arFun)
{
	CriticalSection cs(&mLock);
	this->Complete();
	mRethrow = arFun;
	cs.Broadcast();
}

void AsyncResult::Wait()
{
	CriticalSection cs(&mLock);
	while(!mIsComplete) cs.Wait();
	if(mRethrow) mRethrow();
}

}
