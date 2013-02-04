package com.petrasolar.nms.protocol.dnp3.demo;

import com.petrasolar.nms.protocol.dnp3.demo.master.DNP3MasterDemo;
import com.petrasolar.nms.protocol.dnp3.demo.slave.DNP3SlaveDemo;

public class DemoDNP3APP {
	
	public static void main(String[] args) {
		if(args.length>0)
		{
			if(args[0].equalsIgnoreCase("master"))
			{
				DNP3MasterDemo.main(args);
			}
			else if(args[0].equalsIgnoreCase("slave"))
			{
				DNP3SlaveDemo.main(args);
			}
			else{
				System.out.println("help message: DemoDNP3APP [options] \n options: master or slave");
			}
		}else{
			System.out.println("help message: DemoDNP3APP [options] \n options: master or slave");
		}
	}
}
