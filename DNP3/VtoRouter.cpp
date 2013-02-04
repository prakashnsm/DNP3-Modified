/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.  Green Enery
 * Corp licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include "VtoRouter.h"

#include <boost/bind.hpp>

#include <APL/Exception.h>
#include <APL/IPhysicalLayerAsync.h>
#include <APL/Logger.h>
#include <APL/Util.h>

#include "VtoReader.h"
#include "VtoRouterSettings.h"

namespace apl
{
namespace dnp
{

VtoRouter::VtoRouter(const VtoRouterSettings& arSettings, Logger* apLogger, IVtoWriter* apWriter, IPhysicalLayerAsync* apPhysLayer, ITimerSource* apTimerSrc) :
	Loggable(apLogger),
	PhysicalLayerMonitor(apLogger, apPhysLayer, apTimerSrc, arSettings.OPEN_RETRY_MS),
	IVtoCallbacks(arSettings.CHANNEL_ID),
	mpVtoWriter(apWriter),
	mReadBuffer(1024),
	mWriteData(0)
{
	assert(apLogger != NULL);
	assert(apWriter != NULL);
	assert(apPhysLayer != NULL);
	assert(apTimerSrc != NULL);
}

void VtoRouter::OnVtoDataReceived(const VtoData& arData)
{
	LOG_BLOCK(LEV_DEBUG, "GotRemoteData: " << arData.GetSize() << " Type: " << ToString(arData.GetType()));

	if(this->CheckIncomingVtoData(arData)) {
		/*
		 * Each physical layer action is processed serially, so we can take
		 * advantage of the FIFO structure to keep things simple.
		 */
		this->mPhysLayerTxBuffer.push(arData);
		this->CheckForPhysWrite();
	}
}

void VtoRouter::_OnReceive(const boost::uint8_t* apData, size_t aLength)
{
	LOG_BLOCK(LEV_COMM, "GotLocalData: " << aLength);

	// turn the incoming data into a VtoMessage object and enque it
	VtoMessage msg(VTODT_DATA, apData, aLength);
	this->mVtoTxBuffer.push_back(msg);

	this->CheckForVtoWrite();
	this->CheckForPhysRead();
}

void VtoRouter::CheckForVtoWrite()
{
	if(!mVtoTxBuffer.empty()) {
		VtoMessage msg = mVtoTxBuffer.front();
		mVtoTxBuffer.pop_front();

		// type DATA means this is a buffer and we need to pull the data out and send it to the vto writer
		if(msg.type == VTODT_DATA) {
			size_t numWritten = mpVtoWriter->Write(msg.data.Buffer(), msg.data.Size(), this->GetChannelId());
			LOG_BLOCK(LEV_INTERPRET, "VtoWriter: " << numWritten << " of " << msg.data.Size());
			if(numWritten < msg.data.Size()) {
				size_t remainder = msg.data.Size() - numWritten;
				VtoMessage partial(VTODT_DATA, msg.data.Buffer() + numWritten, remainder);
				mVtoTxBuffer.push_front(partial);
			}
			else this->CheckForVtoWrite();
		}
		else {
			// if we have generated REMOTE_OPENED or REMOTE_CLOSED message we need to send the SetLocalVtoState
			// update to the vtowriter so it can be serialized in the correct order.
			mpVtoWriter->SetLocalVtoState(msg.type == VTODT_REMOTE_OPENED, this->GetChannelId());
			this->CheckForVtoWrite();
		}
	}

	this->CheckForPhysRead();
}

void VtoRouter::_OnSendSuccess()
{
	// look for more data to write
	this->CheckForPhysWrite();
}

void VtoRouter::_OnSendFailure()
{
	/* Do nothing here because they layer will be closing anyway */
}

void VtoRouter::CheckForPhysRead()
{
	if(mpPhys->CanRead() && mVtoTxBuffer.size() < 10) {	//TODO - Make this configurable or track the size in bytes
		mpPhys->AsyncRead(mReadBuffer, mReadBuffer.Size());
	}
}

void VtoRouter::CheckForPhysWrite()
{
	if(!mPhysLayerTxBuffer.empty()) {
		VtoDataType type = mPhysLayerTxBuffer.front().GetType();
		if(type == VTODT_DATA) {
			// only write to the physical layer if we have a valid local connection
			if(mpPhys->CanWrite()) {
				mWriteData = mPhysLayerTxBuffer.front();
				mPhysLayerTxBuffer.pop();
				mpPhys->AsyncWrite(mWriteData.mpData, mWriteData.GetSize());
				LOG_BLOCK(LEV_COMM, "Wrote: " << mWriteData.GetSize());
			}
		}
		else {
			this->mPhysLayerTxBuffer.pop();
			this->DoVtoRemoteConnectedChanged(type == VTODT_REMOTE_OPENED);
		}
	}
}

void VtoRouter::NotifyRemoteSideOfState(bool aConnected)
{
	mVtoTxBuffer.push_back(VtoMessage(aConnected ? VTODT_REMOTE_OPENED : VTODT_REMOTE_CLOSED));
	this->CheckForVtoWrite();
}

void VtoRouter::FlushBuffers()
{
	// clear out all of the data when we close the local connection

	while(mPhysLayerTxBuffer.size() > 0) {
		LOG_BLOCK(LEV_WARNING, "Tossing data: " << this->mPhysLayerTxBuffer.front().GetType() << " size: " << this->mPhysLayerTxBuffer.front().GetSize());
		this->mPhysLayerTxBuffer.pop();
	}

}

void VtoRouter::OnBufferAvailable()
{
	this->CheckForVtoWrite();
}

void VtoRouter::OnPhysicalLayerOpenSuccessCallback()
{
	this->SetLocalConnected(true);

	this->CheckForPhysRead();
	this->CheckForPhysWrite();
	this->CheckForVtoWrite();
}

void VtoRouter::OnPhysicalLayerOpenFailureCallback()
{
	this->SetLocalConnected(false);
	this->CheckForPhysWrite();
	this->CheckForVtoWrite();
}

void VtoRouter::OnPhysicalLayerCloseCallback()
{
	this->SetLocalConnected(false);
	this->CheckForPhysWrite();
	this->CheckForVtoWrite();
}

}
}

/* vim: set ts=4 sw=4: */

