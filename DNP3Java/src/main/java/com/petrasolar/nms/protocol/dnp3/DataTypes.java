/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public final class DataTypes {
  public final static DataTypes DT_BINARY = new DataTypes("DT_BINARY");
  public final static DataTypes DT_ANALOG = new DataTypes("DT_ANALOG");
  public final static DataTypes DT_COUNTER = new DataTypes("DT_COUNTER");
  public final static DataTypes DT_CONTROL_STATUS = new DataTypes("DT_CONTROL_STATUS");
  public final static DataTypes DT_SETPOINT_STATUS = new DataTypes("DT_SETPOINT_STATUS");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static DataTypes swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + DataTypes.class + " with value " + swigValue);
  }

  private DataTypes(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private DataTypes(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private DataTypes(String swigName, DataTypes swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static DataTypes[] swigValues = { DT_BINARY, DT_ANALOG, DT_COUNTER, DT_CONTROL_STATUS, DT_SETPOINT_STATUS };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

