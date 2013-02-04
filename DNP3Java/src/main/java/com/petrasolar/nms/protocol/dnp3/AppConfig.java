/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class AppConfig {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected AppConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AppConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_AppConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AppConfig() {
    this(javadnp3JNI.new_AppConfig__SWIG_0(), true);
  }

  public AppConfig(long aRspTimeout, long aNumRetry, long aFragSize) {
    this(javadnp3JNI.new_AppConfig__SWIG_1(aRspTimeout, aNumRetry, aFragSize), true);
  }

  public AppConfig(long aRspTimeout, long aNumRetry) {
    this(javadnp3JNI.new_AppConfig__SWIG_2(aRspTimeout, aNumRetry), true);
  }

  public AppConfig(long aRspTimeout) {
    this(javadnp3JNI.new_AppConfig__SWIG_3(aRspTimeout), true);
  }

  public void setRspTimeout(long value) {
    javadnp3JNI.AppConfig_RspTimeout_set(swigCPtr, this, value);
  }

  public long getRspTimeout() {
    return javadnp3JNI.AppConfig_RspTimeout_get(swigCPtr, this);
  }

  public void setNumRetry(long value) {
    javadnp3JNI.AppConfig_NumRetry_set(swigCPtr, this, value);
  }

  public long getNumRetry() {
    return javadnp3JNI.AppConfig_NumRetry_get(swigCPtr, this);
  }

  public void setFragSize(long value) {
    javadnp3JNI.AppConfig_FragSize_set(swigCPtr, this, value);
  }

  public long getFragSize() {
    return javadnp3JNI.AppConfig_FragSize_get(swigCPtr, this);
  }

}
