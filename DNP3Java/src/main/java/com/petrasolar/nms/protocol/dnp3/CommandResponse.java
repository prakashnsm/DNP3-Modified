/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class CommandResponse {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected CommandResponse(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(CommandResponse obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_CommandResponse(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public CommandResponse() {
    this(javadnp3JNI.new_CommandResponse__SWIG_0(), true);
  }

  public CommandResponse(CommandStatus aStatus) {
    this(javadnp3JNI.new_CommandResponse__SWIG_1(aStatus.swigValue()), true);
  }

  public void setMResult(CommandStatus value) {
    javadnp3JNI.CommandResponse_mResult_set(swigCPtr, this, value.swigValue());
  }

  public CommandStatus getMResult() {
    return CommandStatus.swigToEnum(javadnp3JNI.CommandResponse_mResult_get(swigCPtr, this));
  }

}