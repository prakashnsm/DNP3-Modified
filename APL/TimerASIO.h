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
#ifndef __TIMER_ASIO_H_
#define __TIMER_ASIO_H_


#include <boost/asio.hpp>
#include "ITimerSource.h"

namespace apl
{

/**
 * This is a wrapper for ASIO timers that are used to post events
 * on a queue. Events can be posted for immediate consumption or
 * some time in the future. Events can be consumbed by the posting
 * thread or another thread.
 *
 * @section Class Goals
 *
 * Decouple APL code form ASIO so ASIO could be replace if need be.
 *
 * There is a problem with ASIO. When cancel is called, an event is
 * posted. We wanted a cancel that does not generate any events.
 *
 */
class TimerASIO : public ITimer
{
	friend class TimerSourceASIO;

public:
	TimerASIO(boost::asio::io_service&);

	// Implement ITimer
	void Cancel();

	/**
	 * Return the timer's expiry time as an absolute time.
	 */
	boost::posix_time::ptime ExpiresAt();

private:

	bool mCanceled;

	boost::asio::deadline_timer mTimer;
};

}

#endif
