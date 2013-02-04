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
#include "SlaveResponseTypes.h"

#include "SlaveConfig.h"
#include "Objects.h"

#include <APL/Exception.h>

namespace apl
{
namespace dnp
{

SlaveResponseTypes::SlaveResponseTypes(const SlaveConfig& arCfg)
{
	mpStaticBinary = GetStaticBinary(arCfg.mStaticBinary);
	mpStaticAnalog = GetStaticAnalog(arCfg.mStaticAnalog);
	mpStaticCounter = GetStaticCounter(arCfg.mStaticCounter);
	mpStaticControlStatus = Group10Var2::Inst();
	mpStaticSetpointStatus = GetStaticSetpointStatus(arCfg.mStaticSetpointStatus);

	mpEventBinary = GetEventBinary(arCfg.mEventBinary);
	mpEventAnalog = GetEventAnalog(arCfg.mEventAnalog);
	mpEventCounter = GetEventCounter(arCfg.mEventCounter);

	/* This is the only valid Slave VTO response, therefore it doesn't need to be configurable */
	mpEventVto = Group113Var0::Inst();
}

StreamObject<Binary>* SlaveResponseTypes::GetStaticBinary(GrpVar gv)
{
	switch(gv.Grp) {
	case(1):
		switch(gv.Var) {
			//case(1): return Group1Var1::Inst();
		case(2): return Group1Var2::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid static binary");
}

StreamObject<Analog>* SlaveResponseTypes::GetStaticAnalog(GrpVar gv)
{
	switch(gv.Grp) {
	case(30):
		switch(gv.Var) {
		case(1): return Group30Var1::Inst();
		case(2): return Group30Var2::Inst();
		case(3): return Group30Var3::Inst();
		case(4): return Group30Var4::Inst();
		case(5): return Group30Var5::Inst();
		case(6): return Group30Var6::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid static analog");
}

StreamObject<Counter>* SlaveResponseTypes::GetStaticCounter(GrpVar gv)
{
	switch(gv.Grp) {
	case(20):
		switch(gv.Var) { //delta counters are obsolete and have been omitted
			//as valid slave responses
		case(1): return Group20Var1::Inst();
		case(2): return Group20Var2::Inst();
		case(5): return Group20Var5::Inst();
		case(6): return Group20Var6::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid static counter");
}

StreamObject<SetpointStatus>* SlaveResponseTypes::GetStaticSetpointStatus(GrpVar gv)
{
	switch(gv.Grp) {
	case(40):
		switch(gv.Var) {
		case(1): return Group40Var1::Inst();
		case(2): return Group40Var2::Inst();
		case(3): return Group40Var3::Inst();
		case(4): return Group40Var4::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid setpoint status");
}

StreamObject<Binary>* SlaveResponseTypes::GetEventBinary(GrpVar gv)
{
	switch(gv.Grp) {
	case(2):
		switch(gv.Var) {
		case(1): return Group2Var1::Inst();
		case(2): return Group2Var2::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid event binary");
}

StreamObject<Analog>* SlaveResponseTypes::GetEventAnalog(GrpVar gv)
{
	switch(gv.Grp) {
	case(32):
		switch(gv.Var) {
		case(1): return Group32Var1::Inst();
		case(2): return Group32Var2::Inst();
		case(3): return Group32Var3::Inst();
		case(4): return Group32Var4::Inst();
		case(5): return Group32Var5::Inst();
		case(6): return Group32Var6::Inst();
		case(7): return Group32Var7::Inst();
		case(8): return Group32Var8::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid event analog");
}

StreamObject<Counter>* SlaveResponseTypes::GetEventCounter(GrpVar gv)
{
	switch(gv.Grp) {
	case(22):
		switch(gv.Var) { //delta counters are obsolete and have been omitted
			//as valid slave responses
		case(1): return Group22Var1::Inst();
		case(2): return Group22Var2::Inst();
		case(5): return Group22Var5::Inst();
		case(6): return Group22Var6::Inst();
		}
		break;
	}

	throw ArgumentException(LOCATION, "Invalid event counter");
}


}
}

