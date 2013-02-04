package com.petrasolar.nms.protocol.dnp3.lib;


import org.apache.log4j.Logger;

import org.totalgrid.reef.protocol.dnp3.IStackObserver;
import org.totalgrid.reef.protocol.dnp3.StackStates;

public class StackObserver extends IStackObserver {
  Logger log = Logger.getLogger(StackObserver.class);
  
  private String configType;
  public StackObserver() {
  }
  public StackObserver(String configType) {
	  this.configType=configType;
  }
  
  @Override
  public void OnStateChange(StackStates aState) {
    log.debug(this.configType + "StackConfig onStateChange : "+aState);
  }
}
