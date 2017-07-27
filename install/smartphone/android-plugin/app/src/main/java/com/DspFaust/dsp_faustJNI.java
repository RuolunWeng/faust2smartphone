/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.DspFaust;

public class dsp_faustJNI {

  static {
    try {
        java.lang.System.loadLibrary("dsp_faust");
    } catch (UnsatisfiedLinkError e) {
        java.lang.System.err.println("native code library failed to load.\n" + e);
        java.lang.System.exit(1);
    }
  }

  public final static native long new_DspFaust(int jarg1, int jarg2);
  public final static native void delete_DspFaust(long jarg1);
  public final static native boolean DspFaust_start(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_stop(long jarg1, DspFaust jarg1_);
  public final static native boolean DspFaust_isRunning(long jarg1, DspFaust jarg1_);
  public final static native long DspFaust_keyOn(long jarg1, DspFaust jarg1_, int jarg2, int jarg3);
  public final static native int DspFaust_keyOff(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native long DspFaust_newVoice(long jarg1, DspFaust jarg1_);
  public final static native int DspFaust_deleteVoice(long jarg1, DspFaust jarg1_, long jarg2);
  public final static native void DspFaust_propagateMidi(long jarg1, DspFaust jarg1_, int jarg2, double jarg3, int jarg4, int jarg5, int jarg6, int jarg7);
  public final static native String DspFaust_getJSONUI(long jarg1, DspFaust jarg1_);
  public final static native String DspFaust_getJSONMeta(long jarg1, DspFaust jarg1_);
  public final static native int DspFaust_getParamsCount(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_setParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, float jarg3);
  public final static native void DspFaust_setParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, float jarg3);
  public final static native float DspFaust_getParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2);
  public final static native float DspFaust_getParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native void DspFaust_setVoiceParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, long jarg3, float jarg4);
  public final static native void DspFaust_setVoiceParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, long jarg3, float jarg4);
  public final static native float DspFaust_getVoiceParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, long jarg3);
  public final static native float DspFaust_getVoiceParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, long jarg3);
  public final static native String DspFaust_getParamAddress(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native String DspFaust_getVoiceParamAddress(long jarg1, DspFaust jarg1_, int jarg2, long jarg3);
  public final static native void DspFaust_propagateAcc(long jarg1, DspFaust jarg1_, int jarg2, float jarg3);
  public final static native void DspFaust_setAccConverter(long jarg1, DspFaust jarg1_, int jarg2, int jarg3, int jarg4, float jarg5, float jarg6, float jarg7);
  public final static native void DspFaust_propagateGyr(long jarg1, DspFaust jarg1_, int jarg2, float jarg3);
  public final static native void DspFaust_setGyrConverter(long jarg1, DspFaust jarg1_, int jarg2, int jarg3, int jarg4, float jarg5, float jarg6, float jarg7);
  public final static native float DspFaust_getCPULoad(long jarg1, DspFaust jarg1_);
  public final static native int DspFaust_getScreenColor(long jarg1, DspFaust jarg1_);
}
