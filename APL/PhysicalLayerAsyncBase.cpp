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
#include "PhysicalLayerAsyncBase.h"

#include "IHandlerAsync.h"
#include "Logger.h"
#include "Exception.h"

#include <sstream>


using namespace std;

namespace apl
{

///////////////////////////////////
// State object
///////////////////////////////////

PhysicalLayerAsyncBase::State::State() :
	mOpen(false),
	mOpening(false),
	mReading(false),
	mWriting(false),
	mClosing(false)
{}

bool PhysicalLayerAsyncBase::State::IsOpen() const
{
	return mOpen;
}

bool PhysicalLayerAsyncBase::State::IsOpening() const
{
	return mOpening;
}

bool PhysicalLayerAsyncBase::State::IsReading() const
{
	return mReading;
}

bool PhysicalLayerAsyncBase::State::IsWriting() const
{
	return mWriting;
}

bool PhysicalLayerAsyncBase::State::IsClosing() const
{
	return mClosing;
}

bool PhysicalLayerAsyncBase::State::IsClosed() const
{
	return !(mOpening || mOpen || mClosing || mReading || mWriting);
}

bool PhysicalLayerAsyncBase::State::CanOpen() const
{
	return this->IsClosed();
}

bool PhysicalLayerAsyncBase::State::CanClose() const
{
	return (mOpen || mOpening) && !mClosing;
}

bool PhysicalLayerAsyncBase::State::CanRead() const
{
	return mOpen && !mClosing && !mReading;
}

bool PhysicalLayerAsyncBase::State::CanWrite() const
{
	return mOpen && !mClosing && !mWriting;
}

bool PhysicalLayerAsyncBase::State::CallbacksPending() const
{
	return mOpening || mReading || mWriting;
}

bool PhysicalLayerAsyncBase::State::CheckForClose()
{
	if(mClosing && !this->CallbacksPending()) {
		mClosing = mOpen = false;
		return true;
	}
	else return false;
}

std::string PhysicalLayerAsyncBase::State::ConvertStateToString() const
{
	std::ostringstream oss;
	oss << "Open: " << mOpen << " Opening: " << mOpening
	    << " Reading: " << mReading << " Writing: " << mWriting
	    << " Closing: " << mClosing;

	return oss.str();
}

///////////////////////////////////
// PhysicalLayerAsyncBase
///////////////////////////////////

PhysicalLayerAsyncBase::PhysicalLayerAsyncBase(Logger* apLogger) :
	Loggable(apLogger),
	mpHandler(NULL)
{

}

////////////////////////////////////
// External Events
////////////////////////////////////

void PhysicalLayerAsyncBase::AsyncOpen()
{
	if(mState.CanOpen()) {
		mState.mOpening = true;
		this->DoOpen();
	}
	else throw InvalidStateException(LOCATION, "AsyncOpen: " + this->ConvertStateToString());
}

/** Marshalls the DoThisLayerDown call
so that all upward OnLowerLayerDown calls are made directly
from the io_service.
*/
void PhysicalLayerAsyncBase::AsyncClose()
{
	this->StartClose();
	if(mState.CheckForClose()) this->DoThisLayerDown();
}

void PhysicalLayerAsyncBase::StartClose()
{
	if(mState.CanClose()) {
		mState.mClosing = true;

		if(mState.mOpening) this->DoOpeningClose();
		else this->DoClose();
	}
	else throw InvalidStateException(LOCATION, "StartClose: " + this->ConvertStateToString());
}

void PhysicalLayerAsyncBase::AsyncWrite(const boost::uint8_t* apBuff, size_t aNumBytes)
{
	if(aNumBytes < 1) throw ArgumentException(LOCATION, "aNumBytes must be > 0");

	if(mState.CanWrite()) {
		mState.mWriting = true;
		this->DoAsyncWrite(apBuff, aNumBytes);
	}
	else throw InvalidStateException(LOCATION, "AsyncWrite: " + this->ConvertStateToString());
}

void PhysicalLayerAsyncBase::AsyncRead(boost::uint8_t* apBuff, size_t aMaxBytes)
{
	if(aMaxBytes < 1) throw ArgumentException(LOCATION, "aMaxBytes must be > 0");

	if(mState.CanRead()) {
		mState.mReading = true;
		this->DoAsyncRead(apBuff, aMaxBytes);
	}
	else throw InvalidStateException(LOCATION, "AsyncRead: " + this->ConvertStateToString());
}

///////////////////////////////////////
// Internal events
///////////////////////////////////////

void PhysicalLayerAsyncBase::OnOpenCallback(const boost::system::error_code& arErr)
{
	if(mState.mOpening) {
		mState.mOpening = false;

		this->DoOpenCallback();

		if(arErr) {
			LOG_BLOCK(LEV_WARNING, arErr.message());
			mState.CheckForClose();
			this->DoOpenFailure();
			if(mpHandler) mpHandler->OnOpenFailure();
		}
		else { // successful connection
			if(this->IsClosing()) { // but the connection was closed
				mState.CheckForClose();
				this->DoClose();
				if(mpHandler) mpHandler->OnOpenFailure();
			}
			else {
				mState.mOpen = true;
				this->DoOpenSuccess();
				if(mpHandler) mpHandler->OnLowerLayerUp();
			}
		}
	}
	else throw InvalidStateException(LOCATION, "OnOpenCallback: " + this->ConvertStateToString());
}

void PhysicalLayerAsyncBase::OnReadCallback(const boost::system::error_code& arErr, boost::uint8_t* apBuff, size_t aSize)
{
	if(mState.mReading) {
		mState.mReading = false;

		if(arErr) {
			LOG_BLOCK(LEV_WARNING, arErr.message());
			if(mState.CanClose()) this->StartClose();
		}
		else {
			if(mState.mClosing) {
				LOG_BLOCK(LEV_INFO, "Ignoring received bytes since layer is closing: " << aSize);
			}
			else {
				this->DoReadCallback(apBuff, aSize);
			}
		}

		if(mState.CheckForClose()) this->DoThisLayerDown();
	}
	else throw InvalidStateException(LOCATION, "OnReadCallback: " + this->ConvertStateToString());
}

void PhysicalLayerAsyncBase::OnWriteCallback(const boost::system::error_code& arErr, size_t aNumBytes)
{
	if(mState.mWriting) {
		mState.mWriting = false;

		if(arErr) {
			LOG_BLOCK(LEV_WARNING, arErr.message());
			if(mState.CanClose()) this->StartClose();
		}
		else {
			if(mState.mClosing) {
				LOG_BLOCK(LEV_INFO, "Ignoring written bytes since layer is closing: " << aNumBytes);
			}
			else {
				this->DoWriteSuccess();
			}
		}

		if(mState.CheckForClose()) this->DoThisLayerDown();
	}
	else throw InvalidStateException(LOCATION, "OnWriteCallback: " + this->ConvertStateToString());
}

////////////////////////////////////
// Actions
////////////////////////////////////

void PhysicalLayerAsyncBase::DoWriteSuccess()
{
	if(mpHandler) mpHandler->OnSendSuccess();
}

void PhysicalLayerAsyncBase::DoThisLayerDown()
{
	if(mpHandler) mpHandler->OnLowerLayerDown();
}

void PhysicalLayerAsyncBase::DoReadCallback(boost::uint8_t* apBuff, size_t aNumBytes)
{
	if(mpHandler) mpHandler->OnReceive(apBuff, aNumBytes);
}

} //end namespace

