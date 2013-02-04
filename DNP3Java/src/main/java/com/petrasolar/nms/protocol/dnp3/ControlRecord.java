/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class ControlRecord extends PointRecord {
  private long swigCPtr;

  protected ControlRecord(long cPtr, boolean cMemoryOwn) {
    super(javadnp3JNI.ControlRecord_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ControlRecord obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_ControlRecord(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ControlRecord(String arName, CommandModes aMode, long aSelectTimeoutMS) {
    this(javadnp3JNI.new_ControlRecord__SWIG_0(arName, aMode.swigValue(), aSelectTimeoutMS), true);
  }

  public ControlRecord(String arName, CommandModes aMode) {
    this(javadnp3JNI.new_ControlRecord__SWIG_1(arName, aMode.swigValue()), true);
  }

  public ControlRecord(String arName) {
    this(javadnp3JNI.new_ControlRecord__SWIG_2(arName), true);
  }

  public ControlRecord() {
    this(javadnp3JNI.new_ControlRecord__SWIG_3(), true);
  }

  public void setCommandMode(CommandModes value) {
    javadnp3JNI.ControlRecord_CommandMode_set(swigCPtr, this, value.swigValue());
  }

  public CommandModes getCommandMode() {
    return CommandModes.swigToEnum(javadnp3JNI.ControlRecord_CommandMode_get(swigCPtr, this));
  }

  public void setSelectTimeoutMS(long value) {
    javadnp3JNI.ControlRecord_SelectTimeoutMS_set(swigCPtr, this, value);
  }

  public long getSelectTimeoutMS() {
    return javadnp3JNI.ControlRecord_SelectTimeoutMS_get(swigCPtr, this);
  }

}
