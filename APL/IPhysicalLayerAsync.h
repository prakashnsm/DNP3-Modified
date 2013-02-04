//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one or more
// contributor license agreements. See the NOTICE file distributed with this
// work for additional information regarding copyright ownership.  Green Enery
// Corp licenses this file to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance with the
// License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
//

#ifndef _I_PHYSICAL_LAYER_ASYNC_H_
#define _I_PHYSICAL_LAYER_ASYNC_H_

#include "AsyncLayerInterfaces.h"

namespace apl
{

class IHandlerAsync;

class IPhysicalLayerState
{

public:

	virtual bool CanOpen() const = 0;

	virtual bool CanClose() const = 0;

	virtual bool CanRead() const = 0;

	virtual bool CanWrite() const = 0;

	/** @return True if the layer is performing an async read */
	virtual bool IsReading() const = 0;

	/** @return True if the layer is performing an async write */
	virtual bool IsWriting() const = 0;

	/** @return True if the layer is performing an asynchronously closing */
	virtual bool IsClosing() const = 0;

	/** @return True if the layer is in the closed with no other activity */
	virtual bool IsClosed() const = 0;

	/** @return True if the layer is performing an asynchronously opening */
	virtual bool IsOpening() const = 0;

	/** @return True if the layer is open for read/write */
	virtual bool IsOpen() const = 0;

	/** @return A string representing the state of the physical layer */
	virtual std::string ConvertStateToString() const = 0;
};


/**
 * Defines an asynchronous interface for serial/tcp/?
 */
class IPhysicalLayerAsync : public IPhysicalLayerState
{
public:

	virtual ~IPhysicalLayerAsync() {}

	/**
	 * Starts an open operation.
	 *
	 * Callback is either IHandlerAsync::OnLowerLayerUp or
	 * IHandlerAsync::OnOpenFailure.
	 */
	virtual void AsyncOpen() = 0;

	/**
	 * Starts a close operation.
	 *
	 * Callback is IHandlerAsync::OnLowerLayerDown.  Callback occurs
	 * after all Asynchronous operations have occured.  If the user
	 * code has an outstanding read or write, those handlers will not
	 * be called.
	 */
	virtual void AsyncClose() = 0;

	/**
	 * Starts a send operation.
	 *
	 * Callback is IHandlerAsync::OnSendSuccess or a failure will
	 * result in the layer closing.
	 *
	 * @param apBuffer		The buffer from which the write operation
	 * 						will write data. This buffer must remain
	 * 						available until the write callback or close
	 * 						occurs.
	 * @param aLength		Number of bytes to write. Callback occurs
	 * 						after ALL bytes have been written.
	 */
	virtual void AsyncWrite(const boost::uint8_t* apBuffer, size_t aLength) = 0;

	/**
	 * Starts a read operation.
	 *
	 * Use SetHandler to provide a callback that is called by
	 * OnReceive(const boost::uint8_t*, size_t) or a failure will
	 * result in the layer closing.
	 *
	 * @param apBuffer		The buffer the read operation will fill.
	 * 						This buffer must remain available until the
	 * 						read callback or close occurs.
	 * @param aMaxLength	Maximum number of bytes to read. Callback
	 * 						occurs after any bytes are available.
	 */
	virtual void AsyncRead(boost::uint8_t* apBuffer, size_t aMaxLength) = 0;

	/**
	 * Set the handler interface for callbacks. A read interface has
	 * been added so the max size is no longer required.
	 *
	 * @param apHandler		Class that will process asynchronous
	 * 						callbacks
	 */
	virtual void SetHandler(IHandlerAsync* apHandler) = 0;
};

};

/* vim: set ts=4 sw=4: */

#endif
