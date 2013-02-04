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
#ifndef __OBJECT_READ_ITERATOR_H_
#define __OBJECT_READ_ITERATOR_H_

#include <assert.h>

#include <APL/Types.h>

#include "HeaderReadIterator.h"
#include "ObjectHeader.h"
#include "ObjectInterfaces.h"

class IObjectHeader;

namespace apl
{
namespace dnp
{

class ObjectInfo
{
	friend class ObjectReadIterator;

public:

	size_t Index() const {
		return mIndex;
	}
	size_t Start() const {
		return mStart;
	}

private:

	size_t mIndex;		// the objects device-based index
	size_t mStart;		// used in conjunction with bitfield objects only,
	// returns the device-based index of the first
	// object in the collection
};

/**
 * An iterator that clients can use to loop over the object data in an
 * APDU object.  This class is usually used in conjunction with the
 * HeaderReadIterator class.
*/
class ObjectReadIterator
{
	friend class HeaderReadIterator;

public:

	bool HasData() {
		return mHasData;
	}
	const ObjectInfo* operator->() const;
	const boost::uint8_t* operator*() const;

	const ObjectReadIterator& operator++();   //prefix version
	const ObjectReadIterator operator++(int); //postfix version
	const HeaderInfo& Header() {
		return mHeaderInfo;
	}

	size_t Count() const {
		return mHeaderInfo.GetCount();
	}
	bool IsEnd() const {
		return mCurrentObjectNum >= Count();
	}

private:

	ObjectReadIterator(const HeaderInfo& arInfo, const boost::uint8_t* apBuffer, bool aHasData);
	HeaderInfo mHeaderInfo;
	size_t mCurrentObjectNum;
	ObjectInfo mInfo;
	const boost::uint8_t* mpPrefixPos;
	const boost::uint8_t* mpPosition;
	const boost::uint8_t* mpBuffer;
	bool mHasData;

	void SetObjectInfo();

	//private helpers
	size_t CalcIndex();
	size_t CalcCountIndex(QualifierCode aCode, const boost::uint8_t* apPrefixPos);
	size_t CalcObjSize(const boost::uint8_t* apPrefixPos);
};

inline const ObjectInfo* ObjectReadIterator::operator->() const
{
	if(this->IsEnd()) throw apl::Exception(LOCATION, "", ALERR_ITERATOR_OUT_OF_BOUNDS);
	return &mInfo;
}

inline const boost::uint8_t* ObjectReadIterator::operator*() const
{
	if(this->IsEnd()) throw apl::Exception(LOCATION, "", ALERR_ITERATOR_OUT_OF_BOUNDS);
	if(!mHasData) throw apl::Exception(LOCATION, "", ALERR_ITERATOR_NO_DATA);
	return mpPosition;
}

inline const ObjectReadIterator& ObjectReadIterator::operator++()
{
	if(this->IsEnd()) throw apl::Exception(LOCATION, "", ALERR_ITERATOR_OUT_OF_BOUNDS);

	++mCurrentObjectNum;

	if(!this->IsEnd()) {
		//Don't advance the prefix position if the object is a bitfield
		if(mHeaderInfo.GetObjectType() != OT_BITFIELD) {
			mpPrefixPos += mHeaderInfo.GetPrefixSize() + this->CalcObjSize(mpPrefixPos);
		}

		this->SetObjectInfo();
	}

	return (*this);
}

inline const ObjectReadIterator ObjectReadIterator::operator++(int)
{
	ObjectReadIterator tmp(*this);
	++(*this);
	return tmp;
}

}
}

/* vim: set ts=4 sw=4: */

#endif
