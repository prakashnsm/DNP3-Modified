package com.petrasolar.nms.protocol.dnp3.demo;

import com.petrasolar.nms.protocol.dnp3.*;

import org.apache.log4j.Logger;
//import org.totalgrid.reef.protocol.dnp3.BinaryOutput;
//import org.totalgrid.reef.protocol.dnp3.CommandResponse;
//import org.totalgrid.reef.protocol.dnp3.CommandStatus;
//import org.totalgrid.reef.protocol.dnp3.DeviceTemplate;
//import org.totalgrid.reef.protocol.dnp3.FilterLevel;
//import org.totalgrid.reef.protocol.dnp3.ICommandAcceptor;
//import org.totalgrid.reef.protocol.dnp3.IDataObserver;
//import org.totalgrid.reef.protocol.dnp3.IResponseAcceptor;
//import org.totalgrid.reef.protocol.dnp3.SlaveStackConfig;
//import org.totalgrid.reef.protocol.dnp3.StackManager;

public class CommandAcceptor extends ICommandAcceptor {

	Logger log = Logger.getLogger(CommandAcceptor.class);

	public static int INSTANCE = 1;
	private int counter = 0;
	private IDataObserver dataObserver;
	private SlaveStackConfig ssc;

	@Override
	public void AcceptCommand(BinaryOutput binaryOutput, long arg1, int aSequence,
			IResponseAcceptor apRspAcceptor) {
		log.debug("BinaryOutput : "+binaryOutput+" Binary["+arg1+"] aSequence : "+aSequence +" apRspAcceptor : "+apRspAcceptor);
		apRspAcceptor.AcceptResponse(new CommandResponse(CommandStatus.CS_SUCCESS), aSequence);
		ssc.setDevice(new DeviceTemplate(5,5,5,5,5,5,5));
	}

	
	public CommandAcceptor() {
	}

	public CommandAcceptor(StackManager sm, SlaveStackConfig ssc,
			IResponseAcceptor responseAcceptor) {
		this.ssc = ssc;
		dataObserver = sm.AddSlave("tcpserver", "dnpSlave("+(INSTANCE++)+")", FilterLevel.LEV_DEBUG, this, ssc);
		dataObserver.swigTakeOwnership();
	}

}
