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
#ifndef __I_FRAME_SINK_H_
#define __I_FRAME_SINK_H_

#include <APL/Types.h>
#include <stddef.h>

namespace apl
{
namespace dnp
{

// @section DESCRIPTION Interface that receives parsed FT3 frame information
class IFrameSink
{
public:

	virtual ~IFrameSink() {}

	//	Sec to Pri

	virtual void Ack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;
	virtual void Nack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;
	virtual void LinkStatus(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;
	virtual void NotSupported (bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;


	//	Pri to Sec

	virtual void TestLinkStatus(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;
	virtual void ResetLinkStates(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;
	virtual void RequestLinkStatus(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc) = 0;
	virtual void ConfirmedUserData(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength) = 0;
	virtual void UnconfirmedUserData(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength) = 0;
};

}
}

#endif

