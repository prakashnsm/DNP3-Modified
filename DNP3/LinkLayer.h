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
#ifndef __LINK_LAYER_H_
#define __LINK_LAYER_H_


#include <queue>
#include <APL/AsyncLayerInterfaces.h>
#include <APL/ITimerSource.h>

#include "ILinkContext.h"
#include "LinkFrame.h"
#include "LinkConfig.h"

namespace apl
{
namespace dnp
{

class ILinkRouter;
class PriStateBase;
class SecStateBase;

//	@section desc Implements the contextual state of DNP3 Data Link Layer
class LinkLayer : public ILowerLayer, public ILinkContext
{
public:

	LinkLayer(apl::Logger*, ITimerSource*, const LinkConfig& arConfig);

	void SetRouter(ILinkRouter*);

	// ILinkContext interface
	void OnLowerLayerUp();
	void OnLowerLayerDown();

	// IFrameSink interface
	void Ack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void Nack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void LinkStatus(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void NotSupported (bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc);
	void TestLinkStatus(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc);
	void ResetLinkStates(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc);
	void RequestLinkStatus(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc);
	void ConfirmedUserData(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength);
	void UnconfirmedUserData(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength);

	// Functions called by the primary and secondary station states
	void ChangeState(PriStateBase*);
	void ChangeState(SecStateBase*);

	Logger* GetLogger() {
		return mpLogger;
	}

	void DoDataUp(const boost::uint8_t* apData, size_t aLength) {
		if(mpUpperLayer) mpUpperLayer->OnReceive(apData, aLength);
	}

	void DoSendSuccess() {
		if(mpUpperLayer) mpUpperLayer->OnSendSuccess();
	}

	void DoSendFailure() {
		if(mpUpperLayer) mpUpperLayer->OnSendFailure();
	}

	void ResetReadFCB() {
		mNextReadFCB = true;
	}
	void ToggleReadFCB() {
		mNextReadFCB = !mNextReadFCB;
	}
	bool NextReadFCB() {
		return mNextReadFCB;
	}

	void ResetWriteFCB() {
		mNextWriteFCB = true;
	}
	void ToggleWriteFCB() {
		mNextWriteFCB = !mNextWriteFCB;
	}
	bool NextWriteFCB() {
		return mNextWriteFCB;
	}

	// Helpers for sending frames
	void SendAck();
	void SendLinkStatus();
	void SendResetLinks();
	void SendUnconfirmedUserData(const boost::uint8_t* apData, size_t aLength);
	void SendDelayedUserData(bool aFCB);

	void StartTimer();
	void CancelTimer();

	const LinkConfig mCONFIG;

	//Retry Count
	void ResetRetry();
	bool Retry();
	size_t RetryRemaining() {
		return mRetryRemaining;
	}

	LinkFrame mPriFrame;
	LinkFrame mSecFrame;
	LinkFrame mDelayedPriFrame;

private:

	void Transmit(const LinkFrame&);

	size_t mRetryRemaining;

	ITimerSource* mpTimerSrc;
	ITimer* mpTimer;

	// callback from the active timer
	void OnTimeout();

	bool mNextReadFCB;
	bool mNextWriteFCB;
	bool mIsOnline;

	bool Validate(bool aIsMaster, boost::uint16_t aSrc, boost::uint16_t aDest);

	/* Events - NVII delegates from ILayerDown and Events produced internally */
	void _Send(const boost::uint8_t*, size_t);

	std::string SendString() {
		return "~>";
	}

	ILinkRouter* mpRouter;
	PriStateBase* mpPriState;
	SecStateBase* mpSecState;
};

}
}

#endif
