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
#ifndef __BASE_DATA_TYPES_H_
#define __BASE_DATA_TYPES_H_


#include "Types.h"
#include "QualityMasks.h"
#include "QualityConverter.h"

#include <sstream>
#include <ostream>
#include <limits>
#include <math.h>
#include <string.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace apl
{
template <class T>
struct MaxMinWrapper {
	static T Max() {
		return std::numeric_limits<T>::max();
	}
	static T Min() {
		return std::numeric_limits<T>::min();
	}
};

template <>
struct MaxMinWrapper<double> { //partial specialization for double
	static double Max() {
		return std::numeric_limits<double>::max();
	}
	static double Min() {
		return -std::numeric_limits<double>::max();
	}
};

// useful template for pairing a value with an index
template <class T>
struct Change {
	Change() {}
	Change(const T& arVal, size_t aIndex) :
		mValue(arVal),
		mIndex(aIndex)
	{}

	T mValue;
	size_t mIndex;
};

enum DataTypes {
	DT_BINARY,
	DT_ANALOG,
	DT_COUNTER,
	DT_CONTROL_STATUS,
	DT_SETPOINT_STATUS
};

std::string GetDataTypeName(DataTypes aType);

/**
  Base class shared by all of the DataPoint types. There are 5 major data types and they all have
  a value, timestamp and a quality field. The timestamp should reflect when the value was measured
  or calculated. The quality field should be set approriately depending on the data type. Each datatype
  has a its own defintion of the quality field that indicate specific conditions but all of the
  datatypes define an XX_ONLINE bit, that is the default "nominal" value. This quality field is not
  for applying alarming information, that needs to be done with Binaries or in other channels.
*/
class DataPoint
{
public:
	virtual ~DataPoint() {}

	DataTypes GetType() const;
	TimeStamp_t GetTime() const;

	virtual boost::uint8_t GetQuality() const;
	bool CheckQualityBit(boost::uint8_t aQualMask) const;

	virtual void SetQuality(boost::uint8_t aQuality);
	void SetTime(const TimeStamp_t arTime);
	void SetToNow();

	virtual std::string ToString() const = 0;

	std::string GetClassMask() const {
		return mClassMask;
	}
	void SetClassMask(std::string aClassMask) {
		mClassMask = aClassMask+" - MappingValue_new. DataTypes :  "+ aClassMask;
	}
	
	int GetGroup() const {
		return mGroup;
	}
	void SetGroup(int aGroup) {
		mGroup = aGroup;
	}

	int GetVariation() const {
		return mVariation;
	}
	void SetVariation(int aVariation) {
		mVariation = aVariation;
	}
protected:

	//These constructors can only be invoked by super classes
	DataPoint(boost::uint8_t aQuality, DataTypes aType);

	boost::uint8_t mQuality;	//	bitfield that stores type specific quality information
	TimeStamp_t mTime;		//	the time that the measurement was made

	std::string mClassMask;

	int mGroup;
	int mVariation;


private:
	DataPoint();
	DataTypes mType;
};

// Inlined definitions from DataPoint
inline DataTypes DataPoint::GetType() const
{
	return mType;
}
inline TimeStamp_t DataPoint::GetTime() const
{
	return mTime;
}
inline boost::uint8_t  DataPoint::GetQuality() const
{
	return mQuality;
}
inline bool DataPoint::CheckQualityBit(boost::uint8_t aQualMask) const
{
	return (aQualMask & mQuality) != 0;
}
inline void DataPoint::SetTime(const TimeStamp_t arTime)
{
	mTime = arTime;
}
inline void DataPoint::SetQuality(boost::uint8_t aQuality)
{
	mQuality = aQuality;
}

/**
   Base class for Binary and ControlStatus data types, shouldn't be used directly.
*/
class BoolDataPoint : public DataPoint
{
public:

	bool GetValue() const;
	void SetValue(bool aValue);

	boost::uint8_t GetQuality() const;
	void SetQuality(boost::uint8_t aQuality);

	void SetQualityValue(boost::uint8_t aFlag);

	bool ShouldGenerateEvent(const BoolDataPoint& arRHS, double aDeadband, boost::uint32_t aLastReportedVal) const;

	std::string ToString() const;

	bool operator==(const BoolDataPoint& rhs) {
		return GetValue() == rhs.GetValue() && GetQuality() == rhs.GetQuality();
	}

protected:
	//BoolDataPoint(const BoolDataPoint& arRHS);
	BoolDataPoint(boost::uint8_t aQuality, DataTypes aType, boost::uint8_t aValueMask);

private:
	BoolDataPoint();
	// bool data points store their value as a bit in the quality field
	boost::uint8_t mValueMask;
};

inline void BoolDataPoint::SetValue(bool aValue)
{
	mQuality = (aValue) ? (mQuality | mValueMask) : (mQuality & (~mValueMask));
}
inline bool BoolDataPoint::GetValue() const
{
	return (mQuality & mValueMask) != 0;
}

inline boost::uint8_t BoolDataPoint::GetQuality() const
{
	return mQuality;
}

inline void BoolDataPoint::SetQualityValue(boost::uint8_t aFlag)
{
	mQuality = aFlag;
}

inline void BoolDataPoint::SetQuality(boost::uint8_t aQuality)
{
	mQuality = (mQuality & (mValueMask));
	mQuality |= aQuality;
}

inline bool BoolDataPoint::ShouldGenerateEvent(const BoolDataPoint& arRHS, double /*aDeadband*/, boost::uint32_t /*aLastReportedVal*/) const
{
	return mQuality != arRHS.mQuality;
}

template <class T>
bool ExceedsDeadband(const T& val1, const T& val2, double aDeadband)
{
	//T can be unsigned data type so std::abs won't work since it only directly supports signed data types
	//If one uses std::abs and T is unsigned one will get an ambiguous override error.
	boost::uint32_t diff;

	if (val1 < val2) {
		diff = val2 - val1;
	}
	else {
		diff = val1 - val2;
	}

	return (diff > aDeadband);
}

template <>
bool ExceedsDeadband<double>(const double& val1, const double& val2, double aDeadband);

//Common subclass to analogs and counters
template <class T>
class TypedDataPoint : public DataPoint
{
public:

	T GetValue() const {
		return mValue;
	}
	void SetValue(T aValue) {
		mValue = aValue;
	}

	bool ShouldGenerateEvent(const TypedDataPoint<T>& arRHS, double aDeadband, T aLastReportedVal) const;

	typedef T Type;

	static const T MAX_VALUE;
	static const T MIN_VALUE;

	std::string ToString() const;

	bool operator==(const TypedDataPoint<T>& rhs) {
		return GetValue() == rhs.GetValue() && GetQuality() == rhs.GetQuality();
	}

protected:
	// IntDataPoints have seperate fields for quality and value
	TypedDataPoint(boost::uint8_t aQuality, DataTypes aType);
	T mValue;

private:
	TypedDataPoint();
};

template <class T>
const T TypedDataPoint<T>::MAX_VALUE = MaxMinWrapper<T>::Max();

template <class T>
const T TypedDataPoint<T>::MIN_VALUE = MaxMinWrapper<T>::Min();

template <class T>
TypedDataPoint<T>::TypedDataPoint(boost::uint8_t aQuality, DataTypes aType) :
	DataPoint(aQuality, aType),
	mValue(0)
{

}

template <class T>
bool TypedDataPoint<T>::ShouldGenerateEvent(const TypedDataPoint<T>& arRHS, double aDeadband, T aLastReportedVal) const
{
	if (mQuality != arRHS.mQuality)	return true;

	return ExceedsDeadband<T>(arRHS.GetValue(), aLastReportedVal, aDeadband);
}

template <class T>
std::string TypedDataPoint<T>::ToString() const
{
	std::ostringstream oss;
	oss << "Value: " << GetValue() << " Quality: " << static_cast<int>(GetQuality());
	return oss.str();
}

}

#endif
