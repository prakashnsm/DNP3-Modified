/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public class LogTypes {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected LogTypes(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(LogTypes obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        javadnp3JNI.delete_LogTypes(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static FilterAssoc getFilters() {
    long cPtr = javadnp3JNI.LogTypes_filters_get();
    return (cPtr == 0) ? null : new FilterAssoc(cPtr, false);
  }

  public static int FilterLevelToMask(FilterLevel arg0) {
    return javadnp3JNI.LogTypes_FilterLevelToMask(arg0.swigValue());
  }

  public static int GetFilterMask(char c) {
    return javadnp3JNI.LogTypes_GetFilterMask__SWIG_0(c);
  }

  public static int GetFilterMask(String arg) {
    return javadnp3JNI.LogTypes_GetFilterMask__SWIG_1(arg);
  }

  public static String GetLevelString(FilterLevel aLevel) {
    return javadnp3JNI.LogTypes_GetLevelString(aLevel.swigValue());
  }

  public static String GetFilterString(int aLevel) {
    return javadnp3JNI.LogTypes_GetFilterString(aLevel);
  }

  public LogTypes() {
    this(javadnp3JNI.new_LogTypes(), true);
  }

  public final static long NUM_FILTER = javadnp3JNI.LogTypes_NUM_FILTER_get();
  public final static int MASK_ALL_LEVELS = javadnp3JNI.LogTypes_MASK_ALL_LEVELS_get();
}