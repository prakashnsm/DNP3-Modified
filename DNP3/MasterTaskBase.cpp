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

#include "MasterTaskBase.h"
#include "APDU.h"
#include <APL/Logger.h>
#include <APL/AsyncTaskInterfaces.h>

namespace apl
{
namespace dnp
{

MasterTaskBase::MasterTaskBase(Logger* apLogger) :
	Loggable(apLogger)
{}

TaskResult MasterTaskBase::OnPartialResponse(const APDU& arAPDU)
{
	if(this->ValidateIIN(arAPDU.GetIIN())) return this->_OnPartialResponse(arAPDU);
	else return TR_FAIL;
}

TaskResult MasterTaskBase::OnFinalResponse(const APDU& arAPDU)
{
	if(this->ValidateIIN(arAPDU.GetIIN())) return this->_OnFinalResponse(arAPDU);
	else return TR_FAIL;
}

bool MasterTaskBase::ValidateIIN(const IINField& GetIIN) const
{
	return true;
}

SingleRspBase::SingleRspBase(Logger* apLogger) : MasterTaskBase(apLogger)
{}

TaskResult SingleRspBase::_OnPartialResponse(const APDU&)
{
	LOG_BLOCK(LEV_WARNING, "Ignoring non-FIN response to task: " << this->Name());
	return TR_FAIL;
}

SimpleRspBase::SimpleRspBase(Logger* apLogger) : SingleRspBase(apLogger)
{}

TaskResult SimpleRspBase::_OnFinalResponse(const APDU& arAPDU)
{
	if(arAPDU.BeginRead().Count() > 0) {
		LOG_BLOCK(LEV_WARNING, "Unexpected object headers in response: " << this->Name());
	}

	return TR_SUCCESS;
}

}
} //ens ns
