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
#include "LinkLayerRouter.h"


#include <APL/Exception.h>
#include <APL/IPhysicalLayerAsync.h>
#include <APL/Logger.h>
#include <sstream>
#include <boost/foreach.hpp>

#include "ILinkContext.h"
#include "LinkFrame.h"

using namespace std;

namespace apl
{
namespace dnp
{

LinkLayerRouter::LinkLayerRouter(apl::Logger* apLogger, IPhysicalLayerAsync* apPhys, ITimerSource* apTimerSrc, millis_t aOpenRetry) :
	Loggable(apLogger),
	PhysicalLayerMonitor(apLogger, apPhys, apTimerSrc, aOpenRetry),
	mReceiver(apLogger, this),
	mTransmitting(false)
{}

void LinkLayerRouter::AddContext(ILinkContext* apContext, const LinkRoute& arRoute)
{
	assert(apContext != NULL);

	if(mAddressMap.find(arRoute) != mAddressMap.end()) {
		ostringstream oss;
		oss << "Route already in use: " << arRoute;
		throw ArgumentException(LOCATION, oss.str());
	}

	BOOST_FOREACH(AddressMap::value_type v, mAddressMap) {
		if(apContext == v.second) {
			ostringstream oss;
			oss << "Context already is bound to route:  " << v.first;
			throw ArgumentException(LOCATION, oss.str());
		}
	}

	mAddressMap[arRoute] = apContext;
	if(this->GetState() == PLS_OPEN) apContext->OnLowerLayerUp();

	this->Start();
}

void LinkLayerRouter::RemoveContext(const LinkRoute& arRoute)
{
	AddressMap::iterator i = mAddressMap.find(arRoute);
	if(i == mAddressMap.end()) throw ArgumentException(LOCATION, "LinkRoute not bound: " + arRoute.ToString());
	else {

		ILinkContext* pContext = i->second;
		mAddressMap.erase(i);

		if(this->GetState() == PLS_OPEN) pContext->OnLowerLayerDown();

		// if no stacks are bound, suspend the router
		if(mAddressMap.size() == 0) {
			this->Suspend();
		}
	}


}

ILinkContext* LinkLayerRouter::GetContext(const LinkRoute& arRoute)
{
	AddressMap::iterator i = mAddressMap.find(arRoute);
	return (i == mAddressMap.end()) ? NULL : i->second;
}


ILinkContext* LinkLayerRouter::GetDestination(boost::uint16_t aDest, boost::uint16_t aSrc)
{
	LinkRoute route(aSrc, aDest);

	ILinkContext* pDest = GetContext(route);

	if(pDest == NULL && mpLogger->IsEnabled(LEV_WARNING)) {
		std::ostringstream oss;
		oss << "Frame w/ unknown route: " << route;
		LogEntry le(LEV_WARNING, mpLogger->GetName(), LOCATION, oss.str(), DLERR_UNKNOWN_ROUTE);
		le.AddValue("SOURCE", aSrc);
		le.AddValue("DESTINATION", aDest);
		mpLogger->Log(le);
	}

	return pDest;
}

//////////////////////////////////////////////////////
// IFrameSink Implementation
//////////////////////////////////////////////////////

void LinkLayerRouter::Ack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->Ack(aIsMaster, aIsRcvBuffFull, aDest, aSrc);
}
void LinkLayerRouter::Nack(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->Nack(aIsMaster, aIsRcvBuffFull, aDest, aSrc);
}
void LinkLayerRouter::LinkStatus(bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->LinkStatus(aIsMaster, aIsRcvBuffFull, aDest, aSrc);
}
void LinkLayerRouter::NotSupported (bool aIsMaster, bool aIsRcvBuffFull, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->NotSupported(aIsMaster, aIsRcvBuffFull, aDest, aSrc);
}
void LinkLayerRouter::TestLinkStatus(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->TestLinkStatus(aIsMaster, aFcb, aDest, aSrc);
}
void LinkLayerRouter::ResetLinkStates(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->ResetLinkStates(aIsMaster, aDest, aSrc);
}
void LinkLayerRouter::RequestLinkStatus(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->RequestLinkStatus(aIsMaster, aDest, aSrc);
}
void LinkLayerRouter::ConfirmedUserData(bool aIsMaster, bool aFcb, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->ConfirmedUserData(aIsMaster, aFcb, aDest, aSrc, apData, aDataLength);
}
void LinkLayerRouter::UnconfirmedUserData(bool aIsMaster, boost::uint16_t aDest, boost::uint16_t aSrc, const boost::uint8_t* apData, size_t aDataLength)
{
	ILinkContext* pDest = GetDestination(aDest, aSrc);
	if(pDest) pDest->UnconfirmedUserData(aIsMaster, aDest, aSrc, apData, aDataLength);
}

void LinkLayerRouter::_OnReceive(const boost::uint8_t*, size_t aNumBytes)
{
	// The order is important here. You must let the receiver process the byte or another read could write
	// over the buffer before it is processed
	mReceiver.OnRead(aNumBytes); //this may trigger callbacks to the local ILinkContext interface
	if(mpPhys->CanRead()) { // this is required because the call above could trigger the layer to be closed
		mpPhys->AsyncRead(mReceiver.WriteBuff(), mReceiver.NumWriteBytes()); //start another read
	}
}

void LinkLayerRouter::Transmit(const LinkFrame& arFrame)
{
	LinkRoute lr(arFrame.GetDest(), arFrame.GetSrc());

	if (this->GetContext(lr)) {
		if (!this->IsLowerLayerUp()) {
			throw InvalidStateException(LOCATION, "LowerLayerDown");
		}
		this->mTransmitQueue.push_back(arFrame);
		this->CheckForSend();
	}
	else {
		ostringstream oss;
		oss << "Unassociated context w/ route: " << lr;
		throw ArgumentException(LOCATION, oss.str());
	}
}

void LinkLayerRouter::_OnSendSuccess()
{
	assert(mTransmitQueue.size() > 0);
	assert(mTransmitting);
	const LinkFrame& f = mTransmitQueue.front();
	LinkRoute lr(f.GetDest(), f.GetSrc());
	ILinkContext* pContext = this->GetContext(lr);
	assert(pContext != NULL);
	mTransmitting = false;
	mTransmitQueue.pop_front();
	this->CheckForSend();
}

void LinkLayerRouter::_OnSendFailure()
{
	LOG_BLOCK(LEV_ERROR, "Unexpected _OnSendFailure");
	mTransmitting = false;
	this->CheckForSend();
}

void LinkLayerRouter::CheckForSend()
{
	if(mTransmitQueue.size() > 0 && !mTransmitting) {
		mTransmitting = true;
		const LinkFrame& f = mTransmitQueue.front();
		LOG_BLOCK(LEV_INTERPRET, "~> " << f.ToString());
		mpPhys->AsyncWrite(f.GetBuffer(), f.GetSize());
	}
}

void LinkLayerRouter::OnPhysicalLayerOpenSuccessCallback()
{
	if(mpPhys->CanRead())
		mpPhys->AsyncRead(mReceiver.WriteBuff(), mReceiver.NumWriteBytes());

	BOOST_FOREACH(AddressMap::value_type p, mAddressMap) {
		p.second->OnLowerLayerUp();
	}
}

void LinkLayerRouter::OnPhysicalLayerCloseCallback()
{
	mTransmitting = false;
	mTransmitQueue.erase(mTransmitQueue.begin(), mTransmitQueue.end());
	for(AddressMap::iterator i = mAddressMap.begin(); i != mAddressMap.end(); ++i) {
		i->second->OnLowerLayerDown();
	}
}

}
}

/* vim: set ts=4 sw=4: */
