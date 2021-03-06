/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class BoolDataPoint extends DataPoint {
  private long swigCPtr;

  protected BoolDataPoint(long cPtr, boolean cMemoryOwn) {
    super(javadnp3JNI.BoolDataPoint_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(BoolDataPoint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_BoolDataPoint(swigCPtr);
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
    javadnp3JNI.BoolDataPoint_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    javadnp3JNI.BoolDataPoint_change_ownership(this, swigCPtr, true);
  }

  public boolean GetValue() {
    return javadnp3JNI.BoolDataPoint_GetValue(swigCPtr, this);
  }

  public void SetValue(boolean aValue) {
    javadnp3JNI.BoolDataPoint_SetValue(swigCPtr, this, aValue);
  }

  public short GetQuality() {
    return (getClass() == BoolDataPoint.class) ? javadnp3JNI.BoolDataPoint_GetQuality(swigCPtr, this) : javadnp3JNI.BoolDataPoint_GetQualitySwigExplicitBoolDataPoint(swigCPtr, this);
  }

  public void SetQuality(short aQuality) {
    if (getClass() == BoolDataPoint.class) javadnp3JNI.BoolDataPoint_SetQuality(swigCPtr, this, aQuality); else javadnp3JNI.BoolDataPoint_SetQualitySwigExplicitBoolDataPoint(swigCPtr, this, aQuality);
  }

  public void SetQualityValue(short aFlag) {
    javadnp3JNI.BoolDataPoint_SetQualityValue(swigCPtr, this, aFlag);
  }

  public boolean ShouldGenerateEvent(BoolDataPoint arRHS, double aDeadband, long aLastReportedVal) {
    return javadnp3JNI.BoolDataPoint_ShouldGenerateEvent(swigCPtr, this, BoolDataPoint.getCPtr(arRHS), arRHS, aDeadband, aLastReportedVal);
  }

  public String ToString() {
    return (getClass() == BoolDataPoint.class) ? javadnp3JNI.BoolDataPoint_ToString(swigCPtr, this) : javadnp3JNI.BoolDataPoint_ToStringSwigExplicitBoolDataPoint(swigCPtr, this);
  }

  public boolean bdpEqual(BoolDataPoint rhs) {
    return javadnp3JNI.BoolDataPoint_bdpEqual(swigCPtr, this, BoolDataPoint.getCPtr(rhs), rhs);
  }

  protected BoolDataPoint(short aQuality, DataTypes aType, short aValueMask) {
    this(javadnp3JNI.new_BoolDataPoint(aQuality, aType.swigValue(), aValueMask), true);
    javadnp3JNI.BoolDataPoint_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
