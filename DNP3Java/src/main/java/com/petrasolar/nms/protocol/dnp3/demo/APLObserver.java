package com.petrasolar.nms.protocol.dnp3.demo;

import org.apache.log4j.Logger;

import com.petrasolar.nms.protocol.dnp3.*;

//import org.totalgrid.reef.protocol.dnp3.IPhysicalLayerObserver;
//import org.totalgrid.reef.protocol.dnp3.PhysicalLayerState;

public class APLObserver  extends IPhysicalLayerObserver{
	Logger log = Logger.getLogger(APLObserver.class);
  @Override
  public void OnStateChange(PhysicalLayerState aplState) {
    log.debug(" PhysicalLayerState : "+aplState);
  }
}
