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
#ifndef __PHYSICAL_LAYER_MAP_H_
#define __PHYSICAL_LAYER_MAP_H_

#include "IPhysicalLayerSource.h"
#include "PhysicalLayerInstance.h"
#include "PhysLayerSettings.h"
#include "Lock.h"
#include "Loggable.h"

#include <map>

namespace apl
{
/** Threadsafe object
*/
class PhysicalLayerMap : public IPhysicalLayerSource, private Loggable
{
public:
	PhysicalLayerMap(Logger* apBaseLogger, boost::asio::io_service*);
	virtual ~PhysicalLayerMap();

	IPhysicalLayerAsync* AcquireLayer(const std::string& arName);
	void ReleaseLayer(const std::string& arName);
	PhysLayerSettings GetSettings(const std::string& arName);

protected:

	SigLock mLock;

	Logger* MakeLogger(const std::string& arName, FilterLevel);

	// unsynchronized versions
	PhysLayerSettings _GetSettings(const std::string& arName);
	PhysLayerInstance* _GetInstance(const std::string& arName);

	void AddLayer(const std::string& arName, PhysLayerSettings aSettings, PhysLayerInstance aInstance);

	typedef std::map<std::string, PhysLayerSettings> NameToSettingsMap;
	typedef std::map<std::string, PhysLayerInstance> NameToInstanceMap;
	typedef std::map<std::string, bool> AcquiredMap;
	
	NameToSettingsMap mNameToSettingsMap;
	NameToInstanceMap mNameToInstanceMap;
	AcquiredMap mAcquiredMap;
	
	boost::asio::io_service* mpService;
	Logger* mpBaseLogger;
};


}

#endif

