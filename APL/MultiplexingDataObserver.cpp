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

#include "MultiplexingDataObserver.h"

namespace apl
{

MultiplexingDataObserver :: MultiplexingDataObserver()
{}

MultiplexingDataObserver :: MultiplexingDataObserver(IDataObserver* apObserver1)
{
	AddObserver(apObserver1);
}

MultiplexingDataObserver :: MultiplexingDataObserver(IDataObserver* apObserver1, IDataObserver* apObserver2)
{
	AddObserver(apObserver1);
	AddObserver(apObserver2);
}

void MultiplexingDataObserver :: AddObserver(IDataObserver* apObserver)
{
	mObservers.push_back(apObserver);
}

void MultiplexingDataObserver :: _Start()
{
	mLock.Lock();
	StartOrEnd(true);
}

void MultiplexingDataObserver :: _End()
{
	StartOrEnd(false);
	mLock.Unlock();
}

void MultiplexingDataObserver :: StartOrEnd(bool aStart)
{
	std::vector<IDataObserver*>::iterator iter = mObservers.begin();

	while(iter != mObservers.end()) {
		if(aStart) (*iter)->Start();
		else (*iter)->End();
		++iter;
	}
}

void MultiplexingDataObserver :: _Update(const Binary& arPoint, size_t aIndex)
{
	PassThrough<Binary>(arPoint, aIndex);
}
void MultiplexingDataObserver :: _Update(const Analog& arPoint, size_t aIndex)
{
	PassThrough<Analog>(arPoint, aIndex);
}
void MultiplexingDataObserver :: _Update(const Counter& arPoint, size_t aIndex)
{
	PassThrough<Counter>(arPoint, aIndex);
}
void MultiplexingDataObserver :: _Update(const ControlStatus& arPoint, size_t aIndex)
{
	PassThrough<ControlStatus>(arPoint, aIndex);
}
void MultiplexingDataObserver :: _Update(const SetpointStatus& arPoint, size_t aIndex)
{
	PassThrough<SetpointStatus>(arPoint, aIndex);
}

template <typename T>
void MultiplexingDataObserver :: PassThrough(const T& arPoint, size_t aIndex)
{
	std::vector<IDataObserver*>::iterator iter = mObservers.begin();

	while(iter != mObservers.end()) {
		(*iter)->Update(arPoint, aIndex);
		++iter;
	}
}

}
