package com.petrasolar.nms.protocol.dnp3.lib;

import org.apache.log4j.Logger;
import org.totalgrid.reef.protocol.dnp3.Analog;
import org.totalgrid.reef.protocol.dnp3.Binary;
import org.totalgrid.reef.protocol.dnp3.ControlStatus;
import org.totalgrid.reef.protocol.dnp3.Counter;
import org.totalgrid.reef.protocol.dnp3.FilterLevel;
import org.totalgrid.reef.protocol.dnp3.ICommandAcceptor;
import org.totalgrid.reef.protocol.dnp3.IDataObserver;
import org.totalgrid.reef.protocol.dnp3.IResponseAcceptor;
import org.totalgrid.reef.protocol.dnp3.MasterStackConfig;
import org.totalgrid.reef.protocol.dnp3.SetpointStatus;
import org.totalgrid.reef.protocol.dnp3.StackManager;

public class DataObserver extends IDataObserver {

	Logger log = Logger.getLogger(DataObserver.class);

	public static int INSTANCE = 0;
	private int counter = 0;
	private ICommandAcceptor commandAcceptor;
	private IResponseAcceptor responseAcceptor;
	
	private String  slaveAddr;
	
	

	public ICommandAcceptor getCommandAcceptor() {
		return commandAcceptor;
	}

	public void setcommandAcceptor(ICommandAcceptor commandAcceptor) {
		this.commandAcceptor = commandAcceptor;
	}

	public IResponseAcceptor getResponseAcceptor() {
		return responseAcceptor;
	}

	public void setResponseAcceptor(IResponseAcceptor responseAcceptor) {
		this.responseAcceptor = responseAcceptor;
	}

	@Override
	protected void _Start() {
		log.debug("DataObserver ("+this.slaveAddr+") Start with counter : " + counter);
	}

	@Override
	protected void _End() {
		log.debug("DataObserver ("+this.slaveAddr+") End with counter : " + counter);
	}

	@Override
	protected void _Update(Binary arPoint, long arg1) {
		log.debug("_Update Slave: "+this.slaveAddr+" binary; arPoint: " + arPoint.ToString() + "  Binary["
				+ arg1 + "] counter: " + (++this.counter));
//		 Setpoint sp = new Setpoint(this.counter);
//		 commandAcceptor.AcceptCommand(sp, arg1, arPoint.GetQuality()
//		 ,responseAcceptor);
	}

	@Override
	protected void _Update(ControlStatus arPoint, long arg1) {
//		 Setpoint sp = new Setpoint(++this.counter);
//		 commandAcceptor.AcceptCommand(sp, arg1, arPoint.GetQuality()
//		 ,responseAcceptor);
		log.debug("_Update Slave: "+this.slaveAddr+" control status : "+ arPoint);
	}

	@Override
	protected void _Update(Analog arPoint, long arg1) {
		log.debug("_Update Slave: "+this.slaveAddr+" analog; arPoint: " + arPoint.ToString() + "  Analog["
				+ arg1 + "] counter: " + (++this.counter) + " swigValue : "+arPoint.GetType().swigValue() + " GetType : "+arPoint.GetType());
//		arPoint.g
//		 Setpoint sp = new Setpoint(++this.counter);
//		 commandAcceptor.AcceptCommand(sp, arg1, arPoint.GetQuality()
//		 ,responseAcceptor);
	}

	@Override
	protected void _Update(Counter arPoint, long arg1) {
		log.debug("_Update Slave: "+this.slaveAddr+" counter");
	}

	@Override
	protected void _Update(SetpointStatus arPoint, long arg1) {
		log.debug("_Update Slave: "+this.slaveAddr+" setPointStatus");
	}

	public DataObserver() {
		
	}
	public DataObserver(String slaveAddr) {
		this.slaveAddr = slaveAddr;
		}
	

	public DataObserver(StackManager sm, MasterStackConfig msc,
			IResponseAcceptor responseAcceptor,int remoteAddress) {
		INSTANCE++;
		this.slaveAddr = ""+INSTANCE;
		//commandAcceptor = 
		sm.AddMaster("tcpclient"+remoteAddress, "dnpMaster("+this.slaveAddr+")", FilterLevel.LEV_DEBUG, this, msc);
//		commandAcceptor.swigTakeOwnership();

				
		try{
			Thread.sleep(5000);
		}catch(Exception ex)
		{
			ex.printStackTrace();
		}
		
		this.responseAcceptor = responseAcceptor;
//		this.responseAcceptor.swigReleaseOwnership();
	}

}
