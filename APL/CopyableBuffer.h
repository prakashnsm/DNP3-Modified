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
#ifndef __COPYABLE_BUFFER_H_
#define __COPYABLE_BUFFER_H_

#include "Types.h"
#include <stddef.h>
#include <memory>
#include <sstream>

namespace apl
{

/** Implements a dynamic buffer with a safe
	copy constructor. This makes it easier to compose with
	classes without requiring an explicit copy constructor
*/
class CopyableBuffer
{

	friend std::ostream& operator<<(std::ostream& output, const CopyableBuffer& arBuff);

public:
	// Construct null buffer
	CopyableBuffer();
	// Construct based on starting size of buffer
	CopyableBuffer(size_t aSize);
	CopyableBuffer(const boost::uint8_t*, size_t aSize);
	CopyableBuffer(const CopyableBuffer&);
	CopyableBuffer& operator=(const CopyableBuffer&);
	~CopyableBuffer();

	bool operator==( const CopyableBuffer& other) const;
	bool operator!=( const CopyableBuffer& other) const {
		return ! (*this == other);
	}

	const boost::uint8_t* Buffer() const {
		return mpBuff;
	}
	const boost::uint8_t* WriteBuffer() const {
		return mpBuff;
	}
	operator const boost::uint8_t* () const {
		return mpBuff;
	}
	operator boost::uint8_t* () {
		return mpBuff;
	}

	size_t Size() const {
		return mSize;
	}
	void Zero();

protected:
	boost::uint8_t* mpBuff;

private:
	size_t mSize;
};


}

#endif


