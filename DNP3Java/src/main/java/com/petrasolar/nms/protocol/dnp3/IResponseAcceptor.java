/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class IResponseAcceptor {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected IResponseAcceptor(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IResponseAcceptor obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_IResponseAcceptor(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    javadnp3JNI.IResponseAcceptor_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.IResponseAcceptor_change_ownership(this, swigCPtr, true);
  }

  public void AcceptResponse(CommandResponse arResponse, int aSequence) {
    javadnp3JNI.IResponseAcceptor_AcceptResponse(swigCPtr, this, CommandResponse.getCPtr(arResponse), arResponse, aSequence);
  }

  public IResponseAcceptor() {
    this(javadnp3JNI.new_IResponseAcceptor(), true);
    javadnp3JNI.IResponseAcceptor_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
