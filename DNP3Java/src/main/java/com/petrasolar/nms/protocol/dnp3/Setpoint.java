/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class Setpoint extends CommandRequest {
  private long swigCPtr;

  protected Setpoint(long cPtr, boolean cMemoryOwn) {
    super(javadnp3JNI.Setpoint_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Setpoint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_Setpoint(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Setpoint(short aValue) {
    this(javadnp3JNI.new_Setpoint__SWIG_0(aValue), true);
  }

  public Setpoint(int aValue) {
    this(javadnp3JNI.new_Setpoint__SWIG_1(aValue), true);
  }

  public Setpoint(double aValue) {
    this(javadnp3JNI.new_Setpoint__SWIG_2(aValue), true);
  }

  public Setpoint() {
    this(javadnp3JNI.new_Setpoint__SWIG_3(), true);
  }

  public String ToString() {
    return javadnp3JNI.Setpoint_ToString(swigCPtr, this);
  }

  public boolean stEqual(Setpoint arRHS) {
    return javadnp3JNI.Setpoint_stEqual(swigCPtr, this, Setpoint.getCPtr(arRHS), arRHS);
  }

  public int GetIntValue() {
    return javadnp3JNI.Setpoint_GetIntValue(swigCPtr, this);
  }

  public double GetValue() {
    return javadnp3JNI.Setpoint_GetValue(swigCPtr, this);
  }

  public void SetValue(double aValue) {
    javadnp3JNI.Setpoint_SetValue__SWIG_0(swigCPtr, this, aValue);
  }

  public void SetValue(int aValue) {
    javadnp3JNI.Setpoint_SetValue__SWIG_1(swigCPtr, this, aValue);
  }

  public SetpointEncodingType GetOptimalEncodingType() {
    return SetpointEncodingType.swigToEnum(javadnp3JNI.Setpoint_GetOptimalEncodingType(swigCPtr, this));
  }

  public SetpointEncodingType GetEncodingType() {
    return SetpointEncodingType.swigToEnum(javadnp3JNI.Setpoint_GetEncodingType(swigCPtr, this));
  }

  public void SetEncodingType(SetpointEncodingType aEncodingType) {
    javadnp3JNI.Setpoint_SetEncodingType(swigCPtr, this, aEncodingType.swigValue());
  }

  public final static CommandTypes EnumType = CommandTypes.swigToEnum(javadnp3JNI.Setpoint_EnumType_get());
}