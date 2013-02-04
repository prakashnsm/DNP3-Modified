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
#ifndef __LOGGABLE_H_
#define __LOGGABLE_H_

#include "Configure.h"
#include "LogBase.h"


namespace apl
{
class Logger;

class Loggable
{
public:
	Loggable( Logger* apLogger );

protected:
	Logger* mpLogger;
};

//macro to remove boiler-plate code for logging messages
#define LOG_BLOCK(severity, string) ERROR_BLOCK(severity, string, -1)

#define EXCEPTION_BLOCK(severity, ex) ERROR_BLOCK(severity, ex.GetErrorString(), ex.ErrorCode())

//macro to remove boiler-plate code for logging messages with an error code
#define ERROR_BLOCK(severity, string, code) ERROR_LOGGER_BLOCK(this->mpLogger, severity, string, code)

#define LOGGER_BLOCK(logger, severity, string) ERROR_LOGGER_BLOCK(logger, severity, string, -1)

#ifndef APL_LOGALL
#define ERROR_LOGGER_BLOCK(logger, severity, string, code)\
	if(logger->IsEnabled(severity)){\
		std::ostringstream somecrazyname_oss;\
		somecrazyname_oss << string;\
		logger->Log(severity, LOCATION, somecrazyname_oss.str(), code);\
	}
#else
#define ERROR_LOGGER_BLOCK(logger, severity, string, code)\
	{ \
	std::ostringstream somecrazyname_oss;\
	somecrazyname_oss << string;\
	logger->Log(severity, LOCATION, somecrazyname_oss.str(), code); \
	}
#endif

}

#endif

