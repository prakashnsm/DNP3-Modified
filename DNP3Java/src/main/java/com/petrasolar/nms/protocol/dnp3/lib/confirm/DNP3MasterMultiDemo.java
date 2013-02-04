package com.petrasolar.nms.protocol.dnp3.lib.confirm;

import org.totalgrid.reef.protocol.dnp3.*;
import com.petrasolar.nms.protocol.dnp3.lib.*;

public class DNP3MasterMultiDemo extends ResponseAcceptor implements Runnable {

	private static final int INTEGRITY_RATE = 60000;

	private int noOfSlaves = 2;

	public DNP3MasterMultiDemo() {
	}


	/**
	 * @param args
	 */
	public static void main(String[] args) {

		new Thread(new DNP3MasterMultiDemo()).start();
	}

	public void run() {

		
		
		StackManager sm = new StackManager();
		
		for (int i = 0; i < noOfSlaves; i++) {
			new Thread(new TestThread(sm, i)).start();
		}

		
	}
	
	class TestThread implements Runnable
	{
		StackManager sm ;
		int remotAddr;
		public TestThread(StackManager sm , int remotAddr) {
				this.sm = sm;
				this.remotAddr = remotAddr;
		}
		@Override
		public void run() {
			
			System.out.println("Thread Name : "+Thread.currentThread().getName());
			
			ILogBase logger = DNP3Logger.getInstance();//new DNP3Logger();
			sm.AddLogHook(logger);
			
			IStackObserver stackObs = new StackObserver("Master");

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

			msc.setApp(new AppConfig(100000, 10, (5 * 1024)));
			msc.setLink(new LinkConfig(true, false, 3, 100+remotAddr, (remotAddr+1), 1000));

			msc.setMaster(mc);

			sm.AddTCPClient("tcpclient"+remotAddr, new PhysLayerSettings(
					FilterLevel.LEV_DEBUG, 5000, aplObs), "192.168.56.1", 20000+remotAddr);

			new DataObserver(sm, msc,null,remotAddr);
			
			while (true)
				;
		}
	}

}
