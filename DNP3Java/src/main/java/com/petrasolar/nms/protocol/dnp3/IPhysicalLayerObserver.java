/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class IPhysicalLayerObserver {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected IPhysicalLayerObserver(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IPhysicalLayerObserver obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_IPhysicalLayerObserver(swigCPtr);
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
    javadnp3JNI.IPhysicalLayerObserver_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.IPhysicalLayerObserver_change_ownership(this, swigCPtr, true);
  }

  public void OnStateChange(PhysicalLayerState arg0) {
    javadnp3JNI.IPhysicalLayerObserver_OnStateChange(swigCPtr, this, arg0.swigValue());
  }

  public IPhysicalLayerObserver() {
    this(javadnp3JNI.new_IPhysicalLayerObserver(), true);
    javadnp3JNI.IPhysicalLayerObserver_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
