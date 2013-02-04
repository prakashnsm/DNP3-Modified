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
#ifndef __HEADER_READ_ITERATOR_H_
#define __HEADER_READ_ITERATOR_H_

#include <APL/Types.h>
#include <vector>
#include <assert.h>

#include "APDUConstants.h"
#include "ObjectHeader.h"
#include "ObjectInterfaces.h"
#include "DNPConstants.h"
#include <APL/Exception.h>

class IObjectHeader;

namespace apl
{
namespace dnp
{

class ObjectReadIterator;

/**
 * A class that represents a DNP3 Object Header in an APDU object.
 */
class HeaderInfo
{
public:

	HeaderInfo(const ObjectHeaderField& arData, size_t aCount, size_t aPrefixSize, IObjectHeader* apHeader, ObjectBase* apObject, size_t aPos) :
		mPos(aPos),
		mHeaderData(arData),
		mCount(aCount),
		mPrefixSize(aPrefixSize),
		mpHeader(apHeader),
		mpObjectBase(apObject)
	{}

	HeaderInfo() {}

	// accessor helpers to simplify reading code
	ObjectHeaderTypes GetHeaderType() const {
		return mpHeader->GetType();
	}
	ObjectTypes GetObjectType() const {
		return mpObjectBase->GetType();
	}
	int GetGroup() const {
		return mHeaderData.Group;
	}
	int GetVariation() const {
		return mHeaderData.Variation;
	}
	QualifierCode GetQualifier() const {
		return mHeaderData.Qualifier;
	}
	size_t GetPrefixSize() const {
		return mPrefixSize;
	}
	size_t GetCount() const {
		return mCount;
	}
	size_t GetHeaderSize() const {
		return mpHeader->GetSize();
	}
	const ObjectBase* GetBaseObject() const {
		return mpObjectBase;
	}
	const IObjectHeader* GetHeader() const {
		return mpHeader;
	}
	size_t GetPosition() const {
		return mPos;
	}

private:

	size_t mPos;
	ObjectHeaderField mHeaderData;
	size_t mCount;
	size_t mPrefixSize;
	IObjectHeader* mpHeader;
	ObjectBase* mpObjectBase;
};

/**
 * An interator that clients can use to loop over the object headers in an
 * APDU object.
 */
class HeaderReadIterator
{
	friend class APDU;

public:

	const HeaderInfo* operator->() const;
	const boost::uint8_t* operator*() const;
	const HeaderReadIterator& operator++();
	const HeaderReadIterator operator++(int);
	const HeaderInfo& info() const;

	ObjectReadIterator BeginRead();
	size_t Count() {
		return mpHeaders->size();
	}
	bool IsEnd() {
		return mIndex >= mpHeaders->size();
	}

private:

	HeaderReadIterator(const std::vector<HeaderInfo>* apHeaders, const boost::uint8_t* apBuffer, bool aHasData);

	const std::vector<HeaderInfo>* mpHeaders;
	const boost::uint8_t* mpBuffer;
	bool mHasData;
	size_t mIndex;

};

inline const HeaderInfo& HeaderReadIterator::info() const
{
	if(mIndex >= mpHeaders->size()) {
		throw apl::Exception(LOCATION, "Iter out of bounds", ALERR_ITERATOR_OUT_OF_BOUNDS);
	}
	return (*mpHeaders)[mIndex];
}

inline const boost::uint8_t* HeaderReadIterator::operator*() const
{
	if(mIndex >= mpHeaders->size()) {
		throw apl::Exception(LOCATION, "Iter out of bounds", ALERR_ITERATOR_OUT_OF_BOUNDS);
	}
	return mpBuffer + (*mpHeaders)[mIndex].GetPosition();
}

inline const HeaderInfo* HeaderReadIterator::operator->() const
{
	if(mIndex >= mpHeaders->size()) {
		throw apl::Exception(LOCATION, "", ALERR_ITERATOR_OUT_OF_BOUNDS);
	}
	return &(*mpHeaders)[mIndex];
}

inline const HeaderReadIterator& HeaderReadIterator::operator++()
{
	if(mIndex >= mpHeaders->size()) {
		throw apl::Exception(LOCATION, "", ALERR_ITERATOR_OUT_OF_BOUNDS);
	}
	++mIndex;
	return (*this);
}

inline const HeaderReadIterator HeaderReadIterator::operator++(int)
{
	if(mIndex >= mpHeaders->size()) {
		throw apl::Exception(LOCATION, "", ALERR_ITERATOR_OUT_OF_BOUNDS);
	}
	HeaderReadIterator tmp(*this);
	++mIndex;
	return tmp;
}

}
}

/* vim: set ts=4 sw=4: */

#endif
