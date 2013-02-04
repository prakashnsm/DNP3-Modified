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

#include "PhysLoopback.h"

#include "IPhysicalLayerAsync.h"
#include "Logger.h"

namespace apl
{

PhysLoopback::PhysLoopback(Logger* apLogger, IPhysicalLayerAsync* apPhys, ITimerSource* apTimerSrc) :
	Loggable(apLogger),
	PhysicalLayerMonitor(apLogger, apPhys, apTimerSrc, 5000),
	mBytesRead(0),
	mBytesWritten(0),
	mBuffer(1024)
{

}

void PhysLoopback::StartRead()
{
	mpPhys->AsyncRead(mBuffer, mBuffer.Size());
}

void PhysLoopback::_OnReceive(const boost::uint8_t* apData, size_t aNumBytes)
{
	mBytesRead += aNumBytes;
	mBytesWritten += aNumBytes;
	mpPhys->AsyncWrite(mBuffer, aNumBytes);
}

void PhysLoopback::_OnSendSuccess(void)
{
	this->StartRead();
}

void PhysLoopback::_OnSendFailure(void)
{

}

void PhysLoopback::OnPhysicalLayerOpenSuccessCallback(void)
{
	this->StartRead();
}

}

