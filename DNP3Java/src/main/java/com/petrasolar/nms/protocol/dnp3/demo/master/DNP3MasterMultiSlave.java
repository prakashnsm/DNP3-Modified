package com.petrasolar.nms.protocol.dnp3.demo.master;

import org.apache.log4j.Logger;

import com.petrasolar.nms.protocol.dnp3.*;
import com.petrasolar.nms.protocol.dnp3.demo.*;

public class DNP3MasterMultiSlave extends ResponseAcceptor implements Runnable {

	private static Logger log = Logger.getLogger(DNP3MasterMultiSlave.class);
	
	private static final int INTEGRITY_RATE = 60000;
	private int noOfSlave = 1;
	private long aRspTimeout = 60000;
	private long aNumRetry = 5;
	private long aFragSize = (2 * 1024);
	
	private long aTimeout = 1000;
	
	private String remoteAddr = "192.168.56.1";
	private int remotePort = 20000;
	private int localDNP3Addr = 100;


	public String getRemoteAddr() {
		return remoteAddr;
	}

	public void setRemoteAddr(String remoteAddr) {
		this.remoteAddr = remoteAddr;
	}

	public int getRemotePort() {
		return remotePort;
	}

	public void setRemotePort(int remotePort) {
		this.remotePort = remotePort;
	}

	public int getLocalDNP3Addr() {
		return localDNP3Addr;
	}

	public void setLocalDNP3Addr(int localDNP3Addr) {
		this.localDNP3Addr = localDNP3Addr;
	}

	public DNP3MasterMultiSlave() {
		this.noOfSlave = 1;
	}

	public DNP3MasterMultiSlave(int noOfSlave) {
		this.noOfSlave = noOfSlave;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		DNP3MasterMultiSlave dmdn = new DNP3MasterMultiSlave(2);
		
		if (args.length>2) {
			dmdn.setRemoteAddr(args[0]);
			try{
			dmdn.setRemotePort(Integer.parseInt(args[1]));
			dmdn.setLocalDNP3Addr(Integer.parseInt(args[2]));
			}catch(NumberFormatException nfe){
				log.error(nfe.getMessage(),nfe);
				log.error("Usage: com.petrasolar.nms.protocol.dnp3.demo.master.DNP3MasterDemoNew <Remote IP address> <Remote Port> <local DNP3 Master address>");
			}
		}
		
		dmdn.run();
	}


	public void run() {
		StackManager sm = new StackManager();
		
		IPhysicalLayerObserver aplObs = new APLObserver();

		sm.AddTCPClient("tcpclient"+noOfSlave, new PhysLayerSettings(
				FilterLevel.LEV_DEBUG, 5000, aplObs), getRemoteAddr(), getRemotePort());
		attachSlave(sm);
	};

	private void attachSlave(StackManager sm) {
		for (int i = 1; i <= noOfSlave; i++) {
			
			ILogBase logger = DNP3Logger.getInstance();//new DNP3Logger();
			sm.AddLogHook(logger);
			
			MasterStackConfig msc = getMasterConfig();
			msc.setApp(new AppConfig(aRspTimeout, aNumRetry, aFragSize));
			msc.setLink(new LinkConfig(true, false, aNumRetry, getLocalDNP3Addr() , i, aTimeout));
			new DataObserver(sm, msc, this,noOfSlave);
		}
		while (true);
	}

	private MasterStackConfig getMasterConfig() {
		IStackObserver stackObs = new StackObserver("Master");

		MasterStackConfig msc = new MasterStackConfig();
		MasterConfig mc = new MasterConfig();

		ExceptionScan es1 = new ExceptionScan();
		es1.setClassMask(1);
		es1.setScanRate(1000);

		ExceptionScan es2 = new ExceptionScan();
		es2.setClassMask(2);
		es2.setScanRate(1000);

//		ExceptionScan es3 = new ExceptionScan();
//		es3.setClassMask(3);
//		es3.setScanRate(1000);
//
//		ExceptionScan es4 = new ExceptionScan();
//		es4.setClassMask(0);
//		es4.setScanRate(1000);

		VectorOfExceptionScan eScanVector = new VectorOfExceptionScan();
		eScanVector.add(es1);
		eScanVector.add(es2);
//		eScanVector.add(es3);
//		eScanVector.add(es4);

		mc.setIntegrityRate(INTEGRITY_RATE);
		mc.setMScans(eScanVector);
		mc.setMpObserver(stackObs);

		msc.setMaster(mc);

		return msc;
	}
}
