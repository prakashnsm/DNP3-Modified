/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class ILogBase {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ILogBase(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ILogBase obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_ILogBase(swigCPtr);
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
    javadnp3JNI.ILogBase_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.ILogBase_change_ownership(this, swigCPtr, true);
  }

  public void Log(LogEntry arEntry) {
    javadnp3JNI.ILogBase_Log(swigCPtr, this, LogEntry.getCPtr(arEntry), arEntry);
  }

  public void SetVar(String aSource, String aVarName, int aValue) {
    javadnp3JNI.ILogBase_SetVar(swigCPtr, this, aSource, aVarName, aValue);
  }

  public ILogBase() {
    this(javadnp3JNI.new_ILogBase(), true);
    javadnp3JNI.ILogBase_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
