package com.petrasolar.nms.protocol.dnp3.demo;

import org.apache.log4j.Logger;
import org.totalgrid.reef.protocol.dnp3.INotifier;

public class Notifier extends INotifier{
	Logger log = Logger.getLogger(Notifier.class);
	
@Override
public void Notify() {
	log.debug("Notify is called.");
}

}
