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
#ifndef __PACKING_UNPACKING_H_
#define __PACKING_UNPACKING_H_


#include "Types.h"
#include <stddef.h>
#include <limits>
#include <iostream>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace apl
{
class UInt8
{
public:
	static boost::uint8_t Read(const boost::uint8_t* apStart) {
		return (*apStart);
	}
	static void Write(boost::uint8_t* apStart, boost::uint8_t aValue) {
		*(apStart) = aValue;
	}

	const static size_t Size = 1;
	const static boost::uint8_t Max;
	const static boost::uint8_t Min;

	typedef boost::uint8_t Type;
};

template <class T>
class BytesBE
{
public:
	static T Read( const boost::uint8_t* apStart ) {
		T ret = 0;
		for ( size_t i = 0; i < Size; i++ ) {
			ret |= static_cast<T>(apStart[i]) << (8 * (Size - 1 - i));
		}
		return ret;
	}
	static void Write( boost::uint8_t* apStart, T aValue ) {
		for ( size_t i = 0; i < Size; i++ ) {
			apStart[i] = static_cast<boost::uint8_t>((aValue >> 8 * (Size - 1 - i)) & 0xFF);
		}
	}

	typedef T Type;
	const static size_t Size = sizeof(T);
	const static T Max;
	const static T Min;
};

template <class T>
const T BytesBE<T>::Max = std::numeric_limits<T>::max();

template <class T>
const T BytesBE<T>::Min = std::numeric_limits<T>::min();

template <class T>
class Bit16LE
{
public:
	static T Read(const boost::uint8_t* apStart) {
		T ret = *(apStart);
		ret |= *(++apStart) << 8;
		return ret;
	}

	static void Write(boost::uint8_t* apStart, T aValue) {
		*(apStart) = static_cast<boost::uint8_t>(aValue & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 8) & 0xFF);
	}

	typedef T Type;

	const static size_t Size = 2;
	const static T Max;
	const static T Min;
};

template <class T>
const T Bit16LE<T>::Max = std::numeric_limits<T>::max();

template <class T>
const T Bit16LE<T>::Min = std::numeric_limits<T>::min();

template <class T>
class Bit32LE
{
public:
	static T Read(const boost::uint8_t* apStart) {
		T  ret = *(apStart);
		ret |= *(++apStart) << 8;
		ret |= *(++apStart) << 16;
		ret |= *(++apStart) << 24;
		return ret;
	}
	static void Write(boost::uint8_t* apStart, T aValue) {
		*(apStart) = static_cast<boost::uint8_t>(aValue & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 8) & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 16) & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 24) & 0xFF);
	}

	typedef T Type;

	const static size_t Size = 4;
	const static T Max;
	const static T Min;
};

template <class T>
const T Bit32LE<T>::Max = std::numeric_limits<T>::max();

template <class T>
const T Bit32LE<T>::Min = std::numeric_limits<T>::min();



typedef Bit16LE<boost::int16_t> Int16LE;
typedef Bit16LE<boost::uint16_t> UInt16LE;
typedef Bit32LE<boost::int32_t> Int32LE;
typedef Bit32LE<boost::uint32_t> UInt32LE;

typedef BytesBE<boost::uint16_t> UInt16BE;
typedef BytesBE<boost::int16_t> Int16BE;
typedef BytesBE<boost::uint32_t> UInt32BE;
typedef BytesBE<boost::int32_t> Int32BE;

typedef BytesBE<boost::uint64_t> UInt64BE;
typedef BytesBE<boost::int64_t> Int64BE;

class UInt48LE
{
public:
	static boost::int64_t Read(const boost::uint8_t* apStart) {

		boost::int64_t  ret = *(apStart);
		ret |= static_cast<boost::int64_t>(*(++apStart)) << 8;
		ret |= static_cast<boost::int64_t>(*(++apStart)) << 16;
		ret |= static_cast<boost::int64_t>(*(++apStart)) << 24;
		ret |= static_cast<boost::int64_t>(*(++apStart)) << 32;
		ret |= static_cast<boost::int64_t>(*(++apStart)) << 40;

		return ret;
	}

	static void Write(boost::uint8_t* apStart, boost::int64_t aValue) {
		if(aValue > MAX) aValue = MAX;

		*(apStart) = static_cast<boost::uint8_t>(aValue & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 8) & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 16) & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 24) & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 32) & 0xFF);
		*(++apStart) = static_cast<boost::uint8_t>((aValue >> 40) & 0xFF);
	}

	const static boost::int64_t MAX = 281474976710655ULL; // 2^48 -1

	const static size_t Size = 6;

	typedef boost::int64_t Type;
};

template <class T>
class Float
{
public:
	typedef T Type;

	const static size_t Size = sizeof(T);
	const static T Max;
	const static T Min;

protected:

	static T NaiveRead(const boost::uint8_t* apStart) {
		return *reinterpret_cast<const T*>(apStart);
	}


	static void NaiveWrite(boost::uint8_t* apStart, T aValue) {
		*reinterpret_cast<T*>(apStart) = aValue;
	}
};

template <class T>
const T Float<T>::Max = std::numeric_limits<T>::max();

template <class T>
const T Float<T>::Min = -std::numeric_limits<T>::max();

class SingleFloat : public Float<float>
{
public:
	static float Read(const boost::uint8_t* apStart);

	static void Write(boost::uint8_t* apStart, float aValue);
};

class DoubleFloat : public Float<double>
{
public:
	static double Read(const boost::uint8_t* apStart);
	static void Write(boost::uint8_t* apStart, double aValue);

private:

#if defined(ARM) || defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB)
	static double FlipWord32(double aValue);
#endif
};
}

#endif
