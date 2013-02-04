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

#ifndef __ENHANCED_VTO_H_
#define __ENHANCED_VTO_H_

#include <APL/Types.h>

namespace apl
{
namespace dnp
{

class VtoData;

class EnhancedVto
{
public:

	const static size_t MAGIC_BYTES_SIZE = 3;
	const static char MAGIC_BYTES[MAGIC_BYTES_SIZE];

	static VtoData CreateVtoData(bool aLocalVtoConnectionOpened, boost::uint8_t aChannelId);

	/** Throws an exception if the frame is not an enhanced vto control frame */
	static void ReadVtoData(const VtoData& arData, bool& arLocalVtoConnectionOpened, boost::uint8_t& arChannelId);

};

}
}

/* vim: set ts=4 sw=4: */

#endif

