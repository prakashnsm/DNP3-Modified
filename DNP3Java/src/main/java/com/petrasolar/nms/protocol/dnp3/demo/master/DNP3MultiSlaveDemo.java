package com.petrasolar.nms.protocol.dnp3.demo.master;

import org.apache.log4j.Logger;

import com.petrasolar.nms.protocol.dnp3.*;
import com.petrasolar.nms.protocol.dnp3.demo.*;

public class DNP3MultiSlaveDemo {

	private static final FilterLevel LOG_LEVEL = FilterLevel.LEV_DEBUG;
	private static Logger log = Logger.getLogger(DNP3MultiSlaveDemo.class);

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		int numberOfSlave = 1;
		String argName = "tcpClient";
		int portNumber = 20000;
		String addrName = "192.168.56.1";
		StackManager stackManager = new StackManager();
		ILogBase logger = DNP3Logger.getInstance();//new DNP3Logger();
		stackManager.AddLogHook(logger);

		ResponseAcceptor[] commandAdapterArray = new ResponseAcceptor[numberOfSlave];
		DataObserver[] myDataObserverTArray = new DataObserver[numberOfSlave];
		MasterStackConfig[] stackConfigArray = new MasterStackConfig[numberOfSlave];


		for (int i = 0; i < numberOfSlave; i++) {
			log.debug("add client name:" + argName + Integer.toString(i+1)
					+ "addrName:" + addrName + " portNumber:" + portNumber);
			IPhysicalLayerObserver aplObs = new APLObserver();
			stackManager.AddTCPClient(argName + Integer.toString(i+1),
					new PhysLayerSettings(LOG_LEVEL, 5000, aplObs), addrName,
					portNumber);
			portNumber++;

			// declare array of DataObserver and CommandAdapeter
		
			// for (int i = 0; i < numberOfSlave; i++) {
			stackConfigArray[i] = new MasterStackConfig();
			stackConfigArray[i].setApp(new AppConfig(100000, 10, (5 * 1024)));
			stackConfigArray[i].getLink().setLocalAddr(100);
			IStackObserver stackObs = new StackObserver("Master");
			MasterConfig mc = new MasterConfig();
			mc.setIntegrityRate(60000);
			mc.setMpObserver(stackObs);

			stackConfigArray[i].setMaster(mc);
			stackConfigArray[i].getLink().setRemoteAddr(i + 1);
			myDataObserverTArray[i] = new DataObserver(Integer.toString(i + 1));
			commandAdapterArray[i] = new ResponseAcceptor(
					Integer.toString(i + 1));

			// try{
			// Thread.sleep(10000);
			// }catch(Exception ex)
			// {
			// ex.printStackTrace();
			// }

			commandAdapterArray[i].setCommandAcceptor(stackManager.AddMaster(
					argName + Integer.toString(i + 1), "master", LOG_LEVEL,
					myDataObserverTArray[i], stackConfigArray[i]));
			System.out.println("AddMaster argName:" + argName
					+ Integer.toString(i + 1));
		}

		// run forever
		for (;;) {
			for (int i = 0; i < numberOfSlave; i++) {
				commandAdapterArray[i].processCommand();
			}
		}
	}
}
