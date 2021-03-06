/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class DataPoint {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected DataPoint(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(DataPoint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_DataPoint(swigCPtr);
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
    javadnp3JNI.DataPoint_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.DataPoint_change_ownership(this, swigCPtr, true);
  }

  public DataTypes GetType() {
    return DataTypes.swigToEnum(javadnp3JNI.DataPoint_GetType(swigCPtr, this));
  }

  public long GetTime() {
    return javadnp3JNI.DataPoint_GetTime(swigCPtr, this);
  }

  public short GetQuality() {
    return (getClass() == DataPoint.class) ? javadnp3JNI.DataPoint_GetQuality(swigCPtr, this) : javadnp3JNI.DataPoint_GetQualitySwigExplicitDataPoint(swigCPtr, this);
  }

  public boolean CheckQualityBit(short aQualMask) {
    return javadnp3JNI.DataPoint_CheckQualityBit(swigCPtr, this, aQualMask);
  }

  public void SetQuality(short aQuality) {
    if (getClass() == DataPoint.class) javadnp3JNI.DataPoint_SetQuality(swigCPtr, this, aQuality); else javadnp3JNI.DataPoint_SetQualitySwigExplicitDataPoint(swigCPtr, this, aQuality);
  }

  public void SetTime(long arTime) {
    javadnp3JNI.DataPoint_SetTime(swigCPtr, this, arTime);
  }

  public void SetToNow() {
    javadnp3JNI.DataPoint_SetToNow(swigCPtr, this);
  }

  public String ToString() {
    return javadnp3JNI.DataPoint_ToString(swigCPtr, this);
  }

  public String GetClassMask() {
    return javadnp3JNI.DataPoint_GetClassMask(swigCPtr, this);
  }

  public void SetClassMask(String aClassMask) {
    javadnp3JNI.DataPoint_SetClassMask(swigCPtr, this, aClassMask);
  }

  public int GetGroup() {
    return javadnp3JNI.DataPoint_GetGroup(swigCPtr, this);
  }

  public void SetGroup(int aGroup) {
    javadnp3JNI.DataPoint_SetGroup(swigCPtr, this, aGroup);
  }

  public int GetVariation() {
    return javadnp3JNI.DataPoint_GetVariation(swigCPtr, this);
  }

  public void SetVariation(int aVariation) {
    javadnp3JNI.DataPoint_SetVariation(swigCPtr, this, aVariation);
  }

  protected DataPoint(short aQuality, DataTypes aType) {
    this(javadnp3JNI.new_DataPoint(aQuality, aType.swigValue()), true);
    javadnp3JNI.DataPoint_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
