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
#include "TLS_Base.h"



#include "TransportLayer.h"
#include <APL/Exception.h>

namespace apl
{
namespace dnp
{

void TLS_Base::Send(const boost::uint8_t*, size_t, TransportLayer*)
{
	throw InvalidStateException(LOCATION, this->Name() );
}

void TLS_Base::HandleReceive(const boost::uint8_t*, size_t, TransportLayer*)
{
	throw InvalidStateException(LOCATION, this->Name() );
}

void TLS_Base::HandleSendSuccess(TransportLayer*)
{
	throw InvalidStateException(LOCATION, this->Name() );
}

void TLS_Base::HandleSendFailure(TransportLayer*)
{
	throw InvalidStateException(LOCATION, this->Name() );
}

void TLS_Base::LowerLayerUp(TransportLayer*)
{
	throw InvalidStateException(LOCATION, this->Name() );
}

void TLS_Base::LowerLayerDown(TransportLayer*)
{
	throw InvalidStateException(LOCATION, this->Name() );
}

}
}
