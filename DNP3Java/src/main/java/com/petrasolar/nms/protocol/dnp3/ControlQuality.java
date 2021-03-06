/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public final class ControlQuality {
  public final static ControlQuality TQ_ONLINE = new ControlQuality("TQ_ONLINE", javadnp3JNI.TQ_ONLINE_get());
  public final static ControlQuality TQ_RESTART = new ControlQuality("TQ_RESTART", javadnp3JNI.TQ_RESTART_get());
  public final static ControlQuality TQ_COMM_LOST = new ControlQuality("TQ_COMM_LOST", javadnp3JNI.TQ_COMM_LOST_get());
  public final static ControlQuality TQ_REMOTE_FORCED_DATA = new ControlQuality("TQ_REMOTE_FORCED_DATA", javadnp3JNI.TQ_REMOTE_FORCED_DATA_get());
  public final static ControlQuality TQ_LOCAL_FORCED_DATA = new ControlQuality("TQ_LOCAL_FORCED_DATA", javadnp3JNI.TQ_LOCAL_FORCED_DATA_get());
  public final static ControlQuality TQ_RESERVED_1 = new ControlQuality("TQ_RESERVED_1", javadnp3JNI.TQ_RESERVED_1_get());
  public final static ControlQuality TQ_RESERVED_2 = new ControlQuality("TQ_RESERVED_2", javadnp3JNI.TQ_RESERVED_2_get());
  public final static ControlQuality TQ_STATE = new ControlQuality("TQ_STATE", javadnp3JNI.TQ_STATE_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static ControlQuality swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + ControlQuality.class + " with value " + swigValue);
  }

  private ControlQuality(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private ControlQuality(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private ControlQuality(String swigName, ControlQuality swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static ControlQuality[] swigValues = { TQ_ONLINE, TQ_RESTART, TQ_COMM_LOST, TQ_REMOTE_FORCED_DATA, TQ_LOCAL_FORCED_DATA, TQ_RESERVED_1, TQ_RESERVED_2, TQ_STATE };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

