/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public final class CommandStatus {
  public final static CommandStatus CS_SUCCESS = new CommandStatus("CS_SUCCESS", javadnp3JNI.CS_SUCCESS_get());
  public final static CommandStatus CS_TIMEOUT = new CommandStatus("CS_TIMEOUT", javadnp3JNI.CS_TIMEOUT_get());
  public final static CommandStatus CS_NO_SELECT = new CommandStatus("CS_NO_SELECT", javadnp3JNI.CS_NO_SELECT_get());
  public final static CommandStatus CS_FORMAT_ERROR = new CommandStatus("CS_FORMAT_ERROR", javadnp3JNI.CS_FORMAT_ERROR_get());
  public final static CommandStatus CS_NOT_SUPPORTED = new CommandStatus("CS_NOT_SUPPORTED", javadnp3JNI.CS_NOT_SUPPORTED_get());
  public final static CommandStatus CS_ALREADY_ACTIVE = new CommandStatus("CS_ALREADY_ACTIVE", javadnp3JNI.CS_ALREADY_ACTIVE_get());
  public final static CommandStatus CS_HARDWARE_ERROR = new CommandStatus("CS_HARDWARE_ERROR", javadnp3JNI.CS_HARDWARE_ERROR_get());
  public final static CommandStatus CS_LOCAL = new CommandStatus("CS_LOCAL", javadnp3JNI.CS_LOCAL_get());
  public final static CommandStatus CS_TOO_MANY_OPS = new CommandStatus("CS_TOO_MANY_OPS", javadnp3JNI.CS_TOO_MANY_OPS_get());
  public final static CommandStatus CS_NOT_AUTHORIZED = new CommandStatus("CS_NOT_AUTHORIZED", javadnp3JNI.CS_NOT_AUTHORIZED_get());
  public final static CommandStatus CS_UNDEFINED = new CommandStatus("CS_UNDEFINED", javadnp3JNI.CS_UNDEFINED_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static CommandStatus swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + CommandStatus.class + " with value " + swigValue);
  }

  private CommandStatus(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private CommandStatus(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private CommandStatus(String swigName, CommandStatus swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static CommandStatus[] swigValues = { CS_SUCCESS, CS_TIMEOUT, CS_NO_SELECT, CS_FORMAT_ERROR, CS_NOT_SUPPORTED, CS_ALREADY_ACTIVE, CS_HARDWARE_ERROR, CS_LOCAL, CS_TOO_MANY_OPS, CS_NOT_AUTHORIZED, CS_UNDEFINED };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
