package com.petrasolar.nms.protocol.dnp3.demo.master;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.totalgrid.reef.protocol.dnp3.Binary;
import org.totalgrid.reef.protocol.dnp3.BinaryOutput;
import org.totalgrid.reef.protocol.dnp3.FilterLevel;
import org.totalgrid.reef.protocol.dnp3.ICommandAcceptor;
import org.totalgrid.reef.protocol.dnp3.IDataObserver;
import org.totalgrid.reef.protocol.dnp3.IStackObserver;
import org.totalgrid.reef.protocol.dnp3.MasterStackConfig;
import org.totalgrid.reef.protocol.dnp3.PhysLayerSettings;
import org.totalgrid.reef.protocol.dnp3.Setpoint;
import org.totalgrid.reef.protocol.dnp3.StackManager;
import org.totalgrid.reef.protocol.dnp3.StackStates;

//import com.petrasolar.nms.protocol.dnp3.demo.MyDataObserver;

//import org.totalgrid.reef.protocol.dnp3.FilterLevel;
//import org.totalgrid.reef.protocol.dnp3.MasterStackConfig;
//import org.totalgrid.reef.protocol.dnp3.PhysLayerSettings;
//import org.totalgrid.reef.protocol.dnp3.StackManager;
//import org.totalgrid.reef.protocol.dnp3.DeviceTemplate;
//import org.totalgrid.reef.protocol.dnp3.ICommandAcceptor;
//import org.totalgrid.reef.protocol.dnp3.SlaveStackConfig;

//import com.petrasolar.nms.protocol.dnp3.FilterLevel;
//import com.petrasolar.nms.protocol.dnp3.IStackObserver;
//import com.petrasolar.nms.protocol.dnp3.MasterStackConfig;
//import com.petrasolar.nms.protocol.dnp3.PhysLayerSettings;
//import com.petrasolar.nms.protocol.dnp3.StackManager;


public class DNP3MasterDemo1 {
  /*
   static{
     if(System.getProperty("org.totalgrid.reef.protocol.dnp3.nostaticload") == null)
     {
       System.out.println("Lib Path : "+System.getProperty("java.library.path"));
       System.out.println("org.totalgrid.reef.protocol.dnp3.nostaticload lib is null");
       System.loadLibrary("dnp3java");
       System.out.println("org.totalgrid.reef.protocol.dnp3.nostaticload lib is "+System.getProperty("org.totalgrid.reef.protocol.dnp3.nostaticload"));
     }
     
    for (Entry<Object, Object> entry : System.getProperties().entrySet()) {
      System.out.println("Prop Key : "+entry.getKey()+" \nValue :" +entry.getValue() );
    }
   }
   */
   public static void main(String[] args) {
     int localDNP3 = 100;
     int remoteDNP3 = 1;
     String remortIp = "172.27.138.91";
     int remotePort = 20000;
     
     FilterLevel LOG_LEVEL = FilterLevel.LEV_INFO;

     StackManager stk = new StackManager(){
       
     };
     IStackObserver stackObs =  new IStackObserver(){
       @Override
      public void OnStateChange(StackStates aState) {
//        super.OnStateChange(aState);
      }
     };
     
//     StackStates stckState = new StackStates();
     
//     stackObs.OnStateChange(StackStates.SS_COMMS_UP);
//     ILogBase ilog = new ILogBase();
    
//     ilog.Log(new LogEntry());
//     stk.AddLogHook(ilog);
//     IDataObserver dataObs = new IDataObserver();
     
     IDataObserver dataObs = new IDataObserver();//MyDataObserver();
     
     /*ICommandAcceptor commandAcc= new ICommandAcceptor(){
       @Override
      public void AcceptCommand(Setpoint arCommand, long aIndex, int aSequence, IResponseAcceptor apRspAcceptor) {
        // TODO Auto-generated method stub
        super.AcceptCommand(arCommand, aIndex, aSequence, apRspAcceptor);
      }
     };*/
      
//     IPhysicalLayerObserver iplo = new IPhysicalLayerObserver();
//     PostingNotifier
//     INotifier  inotify = new INotifier();
     
     ExecutorService executor = Executors.newFixedThreadPool(10);
     
//     mast
     
     stk.AddTCPClient("tcpclient", new PhysLayerSettings(LOG_LEVEL, 3000), remortIp, remotePort);
    
     MasterStackConfig masterConfig = new MasterStackConfig();
     masterConfig.getLink().setLocalAddr(localDNP3);
     masterConfig.getLink().setRemoteAddr(remoteDNP3);
     masterConfig.getMaster().setIntegrityRate(60000);
     masterConfig.getMaster().setMpObserver(stackObs);
     
     ICommandAcceptor commandAcceptor =  stk.AddMaster(
         "tcpclient",           // port name
         "master",              // stack name
         LOG_LEVEL ,            // log filter level
         dataObs,               // callback for data processing
         masterConfig           // stack configuration
       );
     
     
     BinaryOutput bo = new BinaryOutput();
     Setpoint sp = new Setpoint();
Binary binary = new Binary(); 

dataObs.swigTakeOwnership();
dataObs.Start();
dataObs.Update(binary, 0);
dataObs.End();

//     SlaveStackConfig slaveConfig = new SlaveStackConfig();
//     slaveConfig.setDevice(new DeviceTemplate(100, 100, 100));
//     stk.AddSlave("tcpserver", "slave", FilterLevel.LEV_INFO, commandAcc, slaveConfig);
//     mstConfig


for(;;);

   }
   

}
