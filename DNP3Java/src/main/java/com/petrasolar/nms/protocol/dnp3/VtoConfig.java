/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class VtoConfig {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected VtoConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(VtoConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_VtoConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public VtoConfig() {
    this(javadnp3JNI.new_VtoConfig(), true);
  }

  public void AddVtoRouterConfig(VtoRouterConfig arSetting) {
    javadnp3JNI.VtoConfig_AddVtoRouterConfig(swigCPtr, this, VtoRouterConfig.getCPtr(arSetting), arSetting);
  }

  public void setMRouterConfigs(VectorOfVtoRouterConfig value) {
    javadnp3JNI.VtoConfig_mRouterConfigs_set(swigCPtr, this, VectorOfVtoRouterConfig.getCPtr(value), value);
  }

  public VectorOfVtoRouterConfig getMRouterConfigs() {
    long cPtr = javadnp3JNI.VtoConfig_mRouterConfigs_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VectorOfVtoRouterConfig(cPtr, false);
  }

}
