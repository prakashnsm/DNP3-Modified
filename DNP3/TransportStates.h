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
#ifndef __TRANSPORT_STATES_H_
#define __TRANSPORT_STATES_H_


#include "TLS_Base.h"
#include <APL/Singleton.h>

namespace apl
{
namespace dnp
{

/** Represents the closed state, only come online
*/
class TLS_Closed : public TLS_Base
{
	MACRO_STATE_SINGLETON_INSTANCE(TLS_Closed);

	void LowerLayerUp(TransportLayer*);
};

/** Represents the ready state
*/
class TLS_Ready : public TLS_Base
{
	MACRO_STATE_SINGLETON_INSTANCE(TLS_Ready);

	void Send(const boost::uint8_t*, size_t, TransportLayer*);
	void HandleReceive(const boost::uint8_t*, size_t, TransportLayer*);
	void LowerLayerDown(TransportLayer*);
};

/** Represents the sending state
*/
class TLS_Sending : public TLS_Base
{
	MACRO_STATE_SINGLETON_INSTANCE(TLS_Sending);

	void HandleReceive(const boost::uint8_t*, size_t, TransportLayer*);
	void HandleSendSuccess(TransportLayer*);
	void HandleSendFailure(TransportLayer*);
	void LowerLayerDown(TransportLayer*);
};

}
} //end namepsace


#endif
