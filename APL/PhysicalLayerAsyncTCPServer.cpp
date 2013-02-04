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

#include "PhysicalLayerAsyncTCPServer.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>

#include "Exception.h"
#include "IHandlerAsync.h"
#include "Logger.h"

using namespace boost;
using namespace boost::system;
using namespace boost::asio;
using namespace std;

namespace apl
{

PhysicalLayerAsyncTCPServer::PhysicalLayerAsyncTCPServer(Logger* apLogger, boost::asio::io_service* apIOService, const std::string& arEndpoint, boost::uint16_t aPort) :
	PhysicalLayerAsyncBaseTCP(apLogger, apIOService),
	mLocalEndpoint(ip::tcp::v4(), aPort),
	mAcceptor(*apIOService)
{
	mLocalEndpoint.address( ResolveAddress(arEndpoint) );
}

/* Implement the actions */
void PhysicalLayerAsyncTCPServer::DoOpen()
{
	if(!mAcceptor.is_open()) {
		boost::system::error_code ec;
		mAcceptor.open(mLocalEndpoint.protocol(), ec);
		if(ec) throw Exception(LOCATION, ec.message());

		mAcceptor.set_option(ip::tcp::acceptor::reuse_address(true));
		mAcceptor.bind(mLocalEndpoint, ec);
		if(ec) throw Exception(LOCATION, ec.message());

		mAcceptor.listen(socket_base::max_connections, ec);
		if(ec) throw Exception(LOCATION, ec.message());
	}

	mAcceptor.async_accept(mSocket,
	                       mRemoteEndpoint,
	                       boost::bind(&PhysicalLayerAsyncTCPServer::OnOpenCallback,
	                                   this,
	                                   boost::asio::placeholders::error));
}

void PhysicalLayerAsyncTCPServer::CloseAcceptor()
{
	boost::system::error_code ec;
	mAcceptor.close(ec);
	if(ec) {
		LOG_BLOCK(LEV_WARNING, "Error while closing tcp acceptor: " << ec);
	}
}

void PhysicalLayerAsyncTCPServer::DoOpenCallback()
{
	this->CloseAcceptor();
}

void PhysicalLayerAsyncTCPServer::DoOpeningClose()
{
	this->CloseAcceptor();
}

void PhysicalLayerAsyncTCPServer::DoOpenSuccess()
{
	LOG_BLOCK(LEV_INFO, "Accepted connection from: " << mRemoteEndpoint);
}

}

/* vim: set ts=4 sw=4: */
