/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.petrasolar.nms.protocol.dnp3;

public final class VtoQuality {
  public final static VtoQuality VQ_ONLINE = new VtoQuality("VQ_ONLINE", javadnp3JNI.VQ_ONLINE_get());
  public final static VtoQuality VQ_RESTART = new VtoQuality("VQ_RESTART", javadnp3JNI.VQ_RESTART_get());
  public final static VtoQuality VQ_COMM_LOST = new VtoQuality("VQ_COMM_LOST", javadnp3JNI.VQ_COMM_LOST_get());
  public final static VtoQuality VQ_REMOTE_FORCED_DATA = new VtoQuality("VQ_REMOTE_FORCED_DATA", javadnp3JNI.VQ_REMOTE_FORCED_DATA_get());
  public final static VtoQuality VQ_RESERVED_1 = new VtoQuality("VQ_RESERVED_1", javadnp3JNI.VQ_RESERVED_1_get());
  public final static VtoQuality VQ_RESERVED_2 = new VtoQuality("VQ_RESERVED_2", javadnp3JNI.VQ_RESERVED_2_get());
  public final static VtoQuality VQ_RESERVED_3 = new VtoQuality("VQ_RESERVED_3", javadnp3JNI.VQ_RESERVED_3_get());
  public final static VtoQuality VQ_RESERVED_4 = new VtoQuality("VQ_RESERVED_4", javadnp3JNI.VQ_RESERVED_4_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static VtoQuality swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + VtoQuality.class + " with value " + swigValue);
  }

  private VtoQuality(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private VtoQuality(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private VtoQuality(String swigName, VtoQuality swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static VtoQuality[] swigValues = { VQ_ONLINE, VQ_RESTART, VQ_COMM_LOST, VQ_REMOTE_FORCED_DATA, VQ_RESERVED_1, VQ_RESERVED_2, VQ_RESERVED_3, VQ_RESERVED_4 };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
