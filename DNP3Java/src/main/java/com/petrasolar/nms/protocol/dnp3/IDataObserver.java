/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class IDataObserver extends ITransactable {
  private long swigCPtr;

  protected IDataObserver(long cPtr, boolean cMemoryOwn) {
    super(javadnp3JNI.IDataObserver_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IDataObserver obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_IDataObserver(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    javadnp3JNI.IDataObserver_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.IDataObserver_change_ownership(this, swigCPtr, true);
  }

  public void Update(Binary arg0, long aIndex) {
    javadnp3JNI.IDataObserver_Update__SWIG_0(swigCPtr, this, Binary.getCPtr(arg0), arg0, aIndex);
  }

  public void Update(Analog arg0, long aIndex) {
    javadnp3JNI.IDataObserver_Update__SWIG_1(swigCPtr, this, Analog.getCPtr(arg0), arg0, aIndex);
  }

  public void Update(Counter arg0, long aIndex) {
    javadnp3JNI.IDataObserver_Update__SWIG_2(swigCPtr, this, Counter.getCPtr(arg0), arg0, aIndex);
  }

  public void Update(ControlStatus arg0, long aIndex) {
    javadnp3JNI.IDataObserver_Update__SWIG_3(swigCPtr, this, ControlStatus.getCPtr(arg0), arg0, aIndex);
  }

  public void Update(SetpointStatus arg0, long aIndex) {
    javadnp3JNI.IDataObserver_Update__SWIG_4(swigCPtr, this, SetpointStatus.getCPtr(arg0), arg0, aIndex);
  }

  protected void _Update(Binary arPoint, long arg1) {
    javadnp3JNI.IDataObserver__Update__SWIG_0(swigCPtr, this, Binary.getCPtr(arPoint), arPoint, arg1);
  }

  protected void _Update(Analog arPoint, long arg1) {
    javadnp3JNI.IDataObserver__Update__SWIG_1(swigCPtr, this, Analog.getCPtr(arPoint), arPoint, arg1);
  }

  protected void _Update(Counter arPoint, long arg1) {
    javadnp3JNI.IDataObserver__Update__SWIG_2(swigCPtr, this, Counter.getCPtr(arPoint), arPoint, arg1);
  }

  protected void _Update(ControlStatus arPoint, long arg1) {
    javadnp3JNI.IDataObserver__Update__SWIG_3(swigCPtr, this, ControlStatus.getCPtr(arPoint), arPoint, arg1);
  }

  protected void _Update(SetpointStatus arPoint, long arg1) {
    javadnp3JNI.IDataObserver__Update__SWIG_4(swigCPtr, this, SetpointStatus.getCPtr(arPoint), arPoint, arg1);
  }

  public IDataObserver() {
    this(javadnp3JNI.new_IDataObserver(), true);
    javadnp3JNI.IDataObserver_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
