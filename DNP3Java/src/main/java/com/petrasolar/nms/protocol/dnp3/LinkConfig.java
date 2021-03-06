/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class LinkConfig {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected LinkConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(LinkConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_LinkConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public LinkConfig(boolean aIsMaster, boolean aUseConfirms, long aNumRetry, int aLocalAddr, int aRemoteAddr, long aTimeout) {
    this(javadnp3JNI.new_LinkConfig__SWIG_0(aIsMaster, aUseConfirms, aNumRetry, aLocalAddr, aRemoteAddr, aTimeout), true);
  }

  public LinkConfig(boolean aIsMaster, boolean aUseConfirms) {
    this(javadnp3JNI.new_LinkConfig__SWIG_1(aIsMaster, aUseConfirms), true);
  }

  public void setIsMaster(boolean value) {
    javadnp3JNI.LinkConfig_IsMaster_set(swigCPtr, this, value);
  }

  public boolean getIsMaster() {
    return javadnp3JNI.LinkConfig_IsMaster_get(swigCPtr, this);
  }

  public void setUseConfirms(boolean value) {
    javadnp3JNI.LinkConfig_UseConfirms_set(swigCPtr, this, value);
  }

  public boolean getUseConfirms() {
    return javadnp3JNI.LinkConfig_UseConfirms_get(swigCPtr, this);
  }

  public void setNumRetry(long value) {
    javadnp3JNI.LinkConfig_NumRetry_set(swigCPtr, this, value);
  }

  public long getNumRetry() {
    return javadnp3JNI.LinkConfig_NumRetry_get(swigCPtr, this);
  }

  public void setLocalAddr(int value) {
    javadnp3JNI.LinkConfig_LocalAddr_set(swigCPtr, this, value);
  }

  public int getLocalAddr() {
    return javadnp3JNI.LinkConfig_LocalAddr_get(swigCPtr, this);
  }

  public void setRemoteAddr(int value) {
    javadnp3JNI.LinkConfig_RemoteAddr_set(swigCPtr, this, value);
  }

  public int getRemoteAddr() {
    return javadnp3JNI.LinkConfig_RemoteAddr_get(swigCPtr, this);
  }

  public void setTimeout(long value) {
    javadnp3JNI.LinkConfig_Timeout_set(swigCPtr, this, value);
  }

  public long getTimeout() {
    return javadnp3JNI.LinkConfig_Timeout_get(swigCPtr, this);
  }

}
