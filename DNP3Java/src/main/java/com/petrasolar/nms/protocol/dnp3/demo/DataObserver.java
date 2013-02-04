package com.petrasolar.nms.protocol.dnp3.demo;

import com.petrasolar.nms.protocol.dnp3.*;

import org.apache.log4j.Logger;

public class DataObserver extends IDataObserver {

	Logger log = Logger.getLogger(DataObserver.class);

	public static int INSTANCE = 0;
	private int counter = 0;
	private ICommandAcceptor commandAcceptor;
	private IResponseAcceptor responseAcceptor;

	private String slaveAddr;

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
		log.debug("DataObserver (" + this.slaveAddr + ") Start with counter : "
				+ counter);
	}

	@Override
	protected void _End() {
		log.debug("DataObserver (" + this.slaveAddr + ") End with counter : "
				+ counter);
	}

	@Override
	protected void _Update(Binary arPoint, long arg1) {

		log.debug("_Update Slave: " + this.slaveAddr + " binary; arPoint: "
				+ arPoint.ToString() + "  Binary[" + arg1 + "] counter: "
				+ (++this.counter) + "\nGetClassMask Value:"
				+ arPoint.GetClassMask() + "\tGroup : " + arPoint.GetGroup()
				+ "\tVariation : " + arPoint.GetVariation());
		// Setpoint sp = new Setpoint(this.counter);
		// commandAcceptor.AcceptCommand(sp, arg1, arPoint.GetQuality()
		// ,responseAcceptor);
	}

	@Override
	protected void _Update(ControlStatus arPoint, long arg1) {
		// Setpoint sp = new Setpoint(++this.counter);
		// commandAcceptor.AcceptCommand(sp, arg1, arPoint.GetQuality()
		// ,responseAcceptor);
		log.debug("_Update Slave: " + this.slaveAddr + " control status : "
				+ arPoint + "\nGetClassMask Value:" + arPoint.GetClassMask()
				+ "\tGroup : " + arPoint.GetGroup() + "\tVariation : "
				+ arPoint.GetVariation());
	}

	@Override
	protected void _Update(Analog arPoint, long arg1) {

		log.debug("_Update Slave: " + this.slaveAddr + " analog; arPoint: "
				+ arPoint.ToString() + "  Analog[" + arg1 + "] counter: "
				+ (++this.counter) + "\nGetClassMask Value:"
				+ arPoint.GetClassMask() + "\tGroup : " + arPoint.GetGroup()
				+ "\tVariation : " + arPoint.GetVariation());
		// Setpoint sp = new Setpoint(++this.counter);
		// commandAcceptor.AcceptCommand(sp, arg1, arPoint.GetQuality()
		// ,responseAcceptor);
	}

	@Override
	protected void _Update(Counter arPoint, long arg1) {
		log.debug("_Update Slave: " + this.slaveAddr + " counter"
				+ "\nGetClassMask Value:" + arPoint.GetClassMask()
				+ "\tGroup : " + arPoint.GetGroup() + "\tVariation : "
				+ arPoint.GetVariation());
	}

	@Override
	protected void _Update(SetpointStatus arPoint, long arg1) {
		log.debug("_Update Slave: " + this.slaveAddr + " setPointStatus"
				+ "\nGetClassMask Value:" + arPoint.GetClassMask()
				+ "\tGroup : " + arPoint.GetGroup() + "\tVariation : "
				+ arPoint.GetVariation());
	}

	public DataObserver() {

	}

	public DataObserver(String slaveAddr) {
		this.slaveAddr = slaveAddr;
	}

	public DataObserver(StackManager sm, MasterStackConfig msc,
			IResponseAcceptor responseAcceptor, int remoteAddress) {
		INSTANCE++;
		this.slaveAddr = "" + INSTANCE;
		// commandAcceptor =
		sm.AddMaster("tcpclient" + remoteAddress, "dnpMaster(" + this.slaveAddr
				+ ")", FilterLevel.LEV_DEBUG, this, msc);
		// commandAcceptor.swigTakeOwnership();

		try {
			Thread.sleep(5000);
		} catch (Exception ex) {
			ex.printStackTrace();
		}

		this.responseAcceptor = responseAcceptor;
		// this.responseAcceptor.swigReleaseOwnership();
	}

}
