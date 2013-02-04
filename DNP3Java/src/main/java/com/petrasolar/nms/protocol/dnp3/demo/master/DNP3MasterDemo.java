package com.petrasolar.nms.protocol.dnp3.demo.master;

import com.petrasolar.nms.protocol.dnp3.*;
import com.petrasolar.nms.protocol.dnp3.demo.*;

public class DNP3MasterDemo extends ResponseAcceptor implements Runnable{
  
  private static final int INTEGRITY_RATE = 60000;
  private int remortAddr = 1;
  
  public DNP3MasterDemo() { 
  }
  
  public DNP3MasterDemo(int remortAddr) {
	  this.remortAddr=remortAddr;
  }
  
  /**
 * @param args
 */
public static void main(String[] args) {

//    ExecutorService executor = Executors.newFixedThreadPool(10);
//    executor.execute(new DNP3MasterDemo(1));

//    ExecutorService executor1 = Executors.newFixedThreadPool(10);
//    executor1.execute(new DNP3MasterDemo(2));
    
    new Thread(new DNP3MasterDemo(1)).start();
//    new Thread(new DNP3MasterDemo(1)).start();
//    executor.execute(new DNP3MasterDemo(3));
//    executor.execute(new DNP3MasterDemo());
//    executor.execute(new DNP3MasterDemo());
//    executor.execute(new DNP3MasterDemo());
  }

  public void run() {

    StackManager sm = new StackManager();
    IStackObserver stackObs = new StackObserver("Master");

    ILogBase logger = DNP3Logger.getInstance();//new DNP3Logger();
    sm.AddLogHook(logger);
    
    IPhysicalLayerObserver aplObs = new APLObserver();

    ExceptionScan es1 = new ExceptionScan();
    es1.setClassMask(1);
    es1.setScanRate(1000);
    
    ExceptionScan es2 = new ExceptionScan();
    es2.setClassMask(2);
    es2.setScanRate(1000);
    
    ExceptionScan es3 = new ExceptionScan();
    es3.setClassMask(3);
    es3.setScanRate(1000);

    VectorOfExceptionScan eScanVector = new VectorOfExceptionScan();
    eScanVector.add(es1);
    eScanVector.add(es2);
    eScanVector.add(es3);

    MasterConfig mc = new MasterConfig();

    mc.setIntegrityRate(INTEGRITY_RATE);
    mc.setMScans(eScanVector);

    mc.setMpObserver(stackObs);
    
    MasterStackConfig msc = new MasterStackConfig();
    
    msc.setApp(new AppConfig(100000, 10, (5*1024)));
    msc.setLink(new LinkConfig(true, false, 3, 101, remortAddr, 1000));

    msc.setMaster(mc);
    
    sm.AddTCPClient("tcpclient"+remortAddr, new PhysLayerSettings(FilterLevel.LEV_DEBUG, 5000, aplObs), "192.168.56.1", 20000);
//    sm.AddTCPClient("tcpclient", new PhysLayerSettings(FilterLevel.LEV_DEBUG, 5000, aplObs), "172.27.138.91", 20000);
    
    new DataObserver(sm, msc, this,remortAddr);
//
    while(true);
  }

}
