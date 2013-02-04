package com.petrasolar.nms.protocol.dnp3.demo;

import org.apache.log4j.Logger;
//import org.totalgrid.reef.protocol.dnp3.*;

import com.petrasolar.nms.protocol.dnp3.*;


public class ResponseAcceptor extends IResponseAcceptor{


Logger log = Logger.getLogger(ResponseAcceptor.class);
  ICommandAcceptor commandAcceptor; 
  
  String slaveDnp3Address;
  
  
  public void setCommandAcceptor(ICommandAcceptor commandAcceptor) {
	this.commandAcceptor = commandAcceptor;
}

public void setSlaveDnp3Address(String slaveDnp3Address) {
	this.slaveDnp3Address = slaveDnp3Address;
}

public ResponseAcceptor() {
}

public ResponseAcceptor(String slaveDnp3Address) {
		this.slaveDnp3Address = slaveDnp3Address;
}

@Override
public void AcceptResponse(CommandResponse commandResponse, int aSequence) {
	
	CommandStatus cs = commandResponse.getMResult(); 
  log.debug("CommandResponse : "+commandResponse + "-  aSequence :"+aSequence);
  log.debug("In AcceptResponse, slaveDnp3Address=" +slaveDnp3Address + ", swigValue=" + cs.swigValue()); 
  }

public void processCommand() {

    try {
                                  Thread.sleep(1000);
             BinaryOutput bo;
                                         // set up on/off switch
             	int count = 0 ;
             	
					if ((count %2) == 0)
                            bo = new BinaryOutput(ControlCode.CC_LATCH_ON);
                    else
                            bo = new BinaryOutput(ControlCode.CC_LATCH_OFF);

                Setpoint setpoint;
                setpoint = new Setpoint(count);

                commandAcceptor.AcceptCommand(bo, 1, 1, this);
                commandAcceptor.AcceptCommand(setpoint, 1, 1, this);
                
                count++;


    } catch (InterruptedException ie) {
                    log.error("processCommand Interrupted exception,slaveDnp3Address = " + slaveDnp3Address + " ie = " + ie.getMessage());
    } catch (Exception e) {
                    log.error("processCommand exception, slaveDnp3Address = " +slaveDnp3Address + " e = " + e.getMessage());
    }
}

} 
