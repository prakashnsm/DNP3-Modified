package com.petrasolar.nms.protocol.dnp3.lib;

import org.apache.log4j.Logger;

import org.totalgrid.reef.protocol.dnp3.ILogBase;
import org.totalgrid.reef.protocol.dnp3.LogEntry;

public class DNP3Logger extends ILogBase {
	public static final String STR_SPLITTER = " - ";
	Logger log = Logger.getLogger(DNP3Logger.class);
	private static DNP3Logger logger;

	private DNP3Logger() {
	}

	public static DNP3Logger getInstance() {
		if (logger == null) {
			logger = new DNP3Logger();
		}
		return logger;
	}

	@Override
	public void Log(LogEntry arEntry) {
		log.debug(arEntry.GetDeviceName() + STR_SPLITTER + arEntry.GetMessage());
	}

	@Override
	public void SetVar(String aSource, String aVarName, int aValue) {
		log.debug("SetVar : source: " + aSource + "  varName: " + aVarName
				+ "  value: " + aValue);
	}

	@Override
	protected void finalize() {
		log.debug("Finalize called");
	}

}
