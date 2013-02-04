/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class ICommandAcceptor {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ICommandAcceptor(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ICommandAcceptor obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_ICommandAcceptor(swigCPtr);
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
    javadnp3JNI.ICommandAcceptor_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.ICommandAcceptor_change_ownership(this, swigCPtr, true);
  }

  public void AcceptCommand(BinaryOutput arCommand, long aIndex, int aSequence, IResponseAcceptor apRspAcceptor) {
    javadnp3JNI.ICommandAcceptor_AcceptCommand__SWIG_0(swigCPtr, this, BinaryOutput.getCPtr(arCommand), arCommand, aIndex, aSequence, IResponseAcceptor.getCPtr(apRspAcceptor), apRspAcceptor);
  }

  public void AcceptCommand(Setpoint arCommand, long aIndex, int aSequence, IResponseAcceptor apRspAcceptor) {
    javadnp3JNI.ICommandAcceptor_AcceptCommand__SWIG_1(swigCPtr, this, Setpoint.getCPtr(arCommand), arCommand, aIndex, aSequence, IResponseAcceptor.getCPtr(apRspAcceptor), apRspAcceptor);
  }

  public ICommandAcceptor() {
    this(javadnp3JNI.new_ICommandAcceptor(), true);
    javadnp3JNI.ICommandAcceptor_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
