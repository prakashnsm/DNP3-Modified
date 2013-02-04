package com.petrasolar.nms.protocol.dnp3.demo.slave;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.petrasolar.nms.protocol.dnp3.*;
import com.petrasolar.nms.protocol.dnp3.demo.*;

public class DNP3SlaveDemo extends ResponseAcceptor implements Runnable{
  
  private int localAddr = 1;
  
  public DNP3SlaveDemo() { 
  }
  
  public DNP3SlaveDemo(int localAddr) {
	  this.localAddr=localAddr;
  }
  
  public static void main(String[] args) {

    ExecutorService executor = Executors.newFixedThreadPool(10);
    executor.execute(new DNP3SlaveDemo(2));
    
  }

  public void run() {

    StackManager sm = new StackManager();
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

    DeviceTemplate device = new DeviceTemplate(5, 5, 5, 5, 5, 5, 5);
    
    SlaveStackConfig ssc = new SlaveStackConfig();
    ssc.setApp(new AppConfig(100000, 10, (5*1024)));
    ssc.setLink(new LinkConfig(false, false, 0, localAddr, 100, 1000));
    ssc.setDevice(device);
    
    IStackObserver stackObs = new StackObserver("Slave");
    ssc.getSlave().setMpObserver(stackObs);

    ILogBase logger = DNP3Logger.getInstance();//new DNP3Logger();
    IPhysicalLayerObserver aplObs = new APLObserver();

    sm.AddLogHook(logger);
    sm.AddTCPServer("tcpserver", new PhysLayerSettings(FilterLevel.LEV_DEBUG, 5000, aplObs), "172.27.138.91", 20000);

    new CommandAcceptor(sm , ssc, this);

    while(true);
  }

}
