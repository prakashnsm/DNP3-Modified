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

#include "LinkRoute.h"

#include <sstream>

namespace apl
{
namespace dnp
{

LinkRoute::LinkRoute(const boost::uint16_t aRemoteAddr, const boost::uint16_t aLocalAddr) :
	remote(aRemoteAddr),
	local(aLocalAddr)
{}

LinkRoute::LinkRoute() :
	remote(0),
	local(0)
{}

bool LinkRoute::LessThan::operator ()(const LinkRoute& a, const LinkRoute& b) const
{
	if(a.remote < b.remote) return true;
	else if(b.remote < a.remote) return false;
	else return a.local < b.local;
}

std::string LinkRoute::ToString() const
{
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}

std::ostream& operator<<(std::ostream& oss, const LinkRoute& arRoute)
{
	return oss << " Local: " << arRoute.local << " Remote: " << arRoute.remote;
}

}
}

