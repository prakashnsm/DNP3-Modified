/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class PointRecord {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected PointRecord(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PointRecord obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_PointRecord(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public PointRecord(String arName) {
    this(javadnp3JNI.new_PointRecord__SWIG_0(arName), true);
  }

  public PointRecord() {
    this(javadnp3JNI.new_PointRecord__SWIG_1(), true);
  }

  public void setName(String value) {
    javadnp3JNI.PointRecord_Name_set(swigCPtr, this, value);
  }

  public String getName() {
    return javadnp3JNI.PointRecord_Name_get(swigCPtr, this);
  }

}