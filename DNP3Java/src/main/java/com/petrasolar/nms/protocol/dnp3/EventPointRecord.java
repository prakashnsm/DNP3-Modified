/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class EventPointRecord extends PointRecord {
  private long swigCPtr;

  protected EventPointRecord(long cPtr, boolean cMemoryOwn) {
    super(javadnp3JNI.EventPointRecord_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(EventPointRecord obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_EventPointRecord(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public EventPointRecord(String arName, PointClass aPointClass) {
    this(javadnp3JNI.new_EventPointRecord__SWIG_0(arName, aPointClass.swigValue()), true);
  }

  public EventPointRecord() {
    this(javadnp3JNI.new_EventPointRecord__SWIG_1(), true);
  }

  public void setEventClass(PointClass value) {
    javadnp3JNI.EventPointRecord_EventClass_set(swigCPtr, this, value.swigValue());
  }

  public PointClass getEventClass() {
    return PointClass.swigToEnum(javadnp3JNI.EventPointRecord_EventClass_get(swigCPtr, this));
  }

}
