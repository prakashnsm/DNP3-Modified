/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class SerialSettings {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected SerialSettings(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SerialSettings obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_SerialSettings(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setMDevice(String value) {
    javadnp3JNI.SerialSettings_mDevice_set(swigCPtr, this, value);
  }

  public String getMDevice() {
    return javadnp3JNI.SerialSettings_mDevice_get(swigCPtr, this);
  }

  public void setMBaud(int value) {
    javadnp3JNI.SerialSettings_mBaud_set(swigCPtr, this, value);
  }

  public int getMBaud() {
    return javadnp3JNI.SerialSettings_mBaud_get(swigCPtr, this);
  }

  public void setMDataBits(int value) {
    javadnp3JNI.SerialSettings_mDataBits_set(swigCPtr, this, value);
  }

  public int getMDataBits() {
    return javadnp3JNI.SerialSettings_mDataBits_get(swigCPtr, this);
  }

  public void setMStopBits(int value) {
    javadnp3JNI.SerialSettings_mStopBits_set(swigCPtr, this, value);
  }

  public int getMStopBits() {
    return javadnp3JNI.SerialSettings_mStopBits_get(swigCPtr, this);
  }

  public void setMParity(ParityType value) {
    javadnp3JNI.SerialSettings_mParity_set(swigCPtr, this, value.swigValue());
  }

  public ParityType getMParity() {
    return ParityType.swigToEnum(javadnp3JNI.SerialSettings_mParity_get(swigCPtr, this));
  }

  public void setMFlowType(FlowType value) {
    javadnp3JNI.SerialSettings_mFlowType_set(swigCPtr, this, value.swigValue());
  }

  public FlowType getMFlowType() {
    return FlowType.swigToEnum(javadnp3JNI.SerialSettings_mFlowType_get(swigCPtr, this));
  }

  public SerialSettings() {
    this(javadnp3JNI.new_SerialSettings(), true);
  }

}
