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
#include "UnsolicitedChannel.h"

#include <APL/Logger.h>
#include "AppLayer.h"

namespace apl
{
namespace dnp
{


UnsolicitedChannel::UnsolicitedChannel(Logger* apLogger, AppLayer* apApp, ITimerSource* apTimerSrc, millis_t aTimeout) :
	AppLayerChannel("Unsolicited", apLogger, apApp, apTimerSrc, aTimeout)
{}

void UnsolicitedChannel::OnUnsol(APDU& arAPDU)
{
	AppControlField acf = arAPDU.GetControl();

	if(acf.SEQ == mSequence) {
		LOG_BLOCK(LEV_INFO, "Ignoring repeat unsol seq: " << acf.SEQ)
	}
	else { // only process the data if the sequence number is new
		mSequence = acf.SEQ;
		mpAppLayer->mpUser->OnUnsolResponse(arAPDU);
	}
}

void UnsolicitedChannel::DoSendSuccess()
{
	mpAppLayer->mpUser->OnUnsolSendSuccess();
}

void UnsolicitedChannel::DoFailure()
{
	mpAppLayer->mpUser->OnUnsolFailure();
}

}
}


