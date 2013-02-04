/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class VtoRouterConfig {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected VtoRouterConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(VtoRouterConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_VtoRouterConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public VtoRouterConfig() {
    this(javadnp3JNI.new_VtoRouterConfig(), true);
  }

  public void setMPhysicalLayerName(String value) {
    javadnp3JNI.VtoRouterConfig_mPhysicalLayerName_set(swigCPtr, this, value);
  }

  public String getMPhysicalLayerName() {
    return javadnp3JNI.VtoRouterConfig_mPhysicalLayerName_get(swigCPtr, this);
  }

  public void setMSettings(VtoRouterSettings value) {
    javadnp3JNI.VtoRouterConfig_mSettings_set(swigCPtr, this, VtoRouterSettings.getCPtr(value), value);
  }

  public VtoRouterSettings getMSettings() {
    long cPtr = javadnp3JNI.VtoRouterConfig_mSettings_get(swigCPtr, this);
    return (cPtr == 0) ? null : new VtoRouterSettings(cPtr, false);
  }

}
