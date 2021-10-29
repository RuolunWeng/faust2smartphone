/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
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

  public final static native long new_DspFaust(long jarg1, DspFaustMotion jarg1_, int jarg2, int jarg3);
  public final static native void delete_DspFaust(long jarg1);
  public final static native boolean DspFaust_start(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_stop(long jarg1, DspFaust jarg1_);
  public final static native boolean DspFaust_isRunning(long jarg1, DspFaust jarg1_);
  public final static native int DspFaust_keyOn(long jarg1, DspFaust jarg1_, int jarg2, int jarg3);
  public final static native int DspFaust_keyOff(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native int DspFaust_newVoice(long jarg1, DspFaust jarg1_);
  public final static native int DspFaust_deleteVoice(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native void DspFaust_allNotesOff(long jarg1, DspFaust jarg1_);
  public final static native String DspFaust_getJSONUI(long jarg1, DspFaust jarg1_);
  public final static native String DspFaust_getJSONMeta(long jarg1, DspFaust jarg1_);
  public final static native String DspFaust_getMeta(long jarg1, DspFaust jarg1_, String jarg2);
  public final static native int DspFaust_getParamsCount(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_setParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, float jarg3);
  public final static native void DspFaust_setOSCValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, String jarg3, String jarg4);
  public final static native boolean DspFaust_setOSCValue__SWIG_1(long jarg1, DspFaust jarg1_, String jarg2, int jarg3, int jarg4);
  public final static native void DspFaust_setParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, float jarg3);
  public final static native float DspFaust_getParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2);
  public final static native float DspFaust_getParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native void DspFaust_setVoiceParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, int jarg3, float jarg4);
  public final static native void DspFaust_setVoiceParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, int jarg3, float jarg4);
  public final static native float DspFaust_getVoiceParamValue__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, int jarg3);
  public final static native float DspFaust_getVoiceParamValue__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, int jarg3);
  public final static native String DspFaust_getParamAddress(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native String DspFaust_getVoiceParamAddress(long jarg1, DspFaust jarg1_, int jarg2, int jarg3);
  public final static native float DspFaust_getParamMin__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2);
  public final static native float DspFaust_getParamMin__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native float DspFaust_getParamMax__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2);
  public final static native float DspFaust_getParamMax__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native float DspFaust_getParamInit__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2);
  public final static native float DspFaust_getParamInit__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2);
  public final static native String DspFaust_getMetadata__SWIG_0(long jarg1, DspFaust jarg1_, String jarg2, String jarg3);
  public final static native String DspFaust_getMetadata__SWIG_1(long jarg1, DspFaust jarg1_, int jarg2, String jarg3);
  public final static native void DspFaust_propagateAcc(long jarg1, DspFaust jarg1_, int jarg2, float jarg3);
  public final static native void DspFaust_setAccConverter(long jarg1, DspFaust jarg1_, int jarg2, int jarg3, int jarg4, float jarg5, float jarg6, float jarg7);
  public final static native void DspFaust_propagateGyr(long jarg1, DspFaust jarg1_, int jarg2, float jarg3);
  public final static native void DspFaust_setGyrConverter(long jarg1, DspFaust jarg1_, int jarg2, int jarg3, int jarg4, float jarg5, float jarg6, float jarg7);
  public final static native float DspFaust_getCPULoad(long jarg1, DspFaust jarg1_);
  public final static native int DspFaust_getScreenColor(long jarg1, DspFaust jarg1_);
  public final static native boolean DspFaust_getOSCIsOn(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_motionRender(long jarg1, DspFaust jarg1_, float jarg2, float jarg3, float jarg4, float jarg5, float jarg6, float jarg7, float jarg8, float jarg9, float jarg10);
  public final static native void DspFaust_initFrame(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_sendMotion(long jarg1, DspFaust jarg1_);
  public final static native void DspFaust_checkAdress(long jarg1, DspFaust jarg1_);
  public final static native float DspFaust_getRotationMatrix(long jarg1, DspFaust jarg1_, int jarg2, int jarg3);
  public final static native long new_DspFaustMotion(int jarg1, int jarg2);
  public final static native void delete_DspFaustMotion(long jarg1);
  public final static native boolean DspFaustMotion_start(long jarg1, DspFaustMotion jarg1_);
  public final static native void DspFaustMotion_stop(long jarg1, DspFaustMotion jarg1_);
  public final static native void DspFaustMotion_render(long jarg1, DspFaustMotion jarg1_);
  public final static native void DspFaustMotion_setInput(long jarg1, DspFaustMotion jarg1_, int jarg2, float jarg3);
  public final static native float DspFaustMotion_getOutput(long jarg1, DspFaustMotion jarg1_, int jarg2);
  public final static native int DspFaustMotion_getOutputChannelNum(long jarg1, DspFaustMotion jarg1_);
  public final static native int DspFaustMotion_getInputChannelNum(long jarg1, DspFaustMotion jarg1_);
  public final static native boolean DspFaustMotion_isRunning(long jarg1, DspFaustMotion jarg1_);
  public final static native void DspFaustMotion_setOSCValue__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2, String jarg3, String jarg4);
  public final static native boolean DspFaustMotion_setOSCValue__SWIG_1(long jarg1, DspFaustMotion jarg1_, String jarg2, int jarg3, int jarg4);
  public final static native String DspFaustMotion_getJSONUI(long jarg1, DspFaustMotion jarg1_);
  public final static native String DspFaustMotion_getJSONMeta(long jarg1, DspFaustMotion jarg1_);
  public final static native int DspFaustMotion_getParamsCount(long jarg1, DspFaustMotion jarg1_);
  public final static native void DspFaustMotion_setParamValue__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2, float jarg3);
  public final static native void DspFaustMotion_setParamValue__SWIG_1(long jarg1, DspFaustMotion jarg1_, int jarg2, float jarg3);
  public final static native float DspFaustMotion_getParamValue__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2);
  public final static native float DspFaustMotion_getParamValue__SWIG_1(long jarg1, DspFaustMotion jarg1_, int jarg2);
  public final static native String DspFaustMotion_getParamAddress(long jarg1, DspFaustMotion jarg1_, int jarg2);
  public final static native float DspFaustMotion_getParamMin__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2);
  public final static native float DspFaustMotion_getParamMin__SWIG_1(long jarg1, DspFaustMotion jarg1_, int jarg2);
  public final static native float DspFaustMotion_getParamMax__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2);
  public final static native float DspFaustMotion_getParamMax__SWIG_1(long jarg1, DspFaustMotion jarg1_, int jarg2);
  public final static native float DspFaustMotion_getParamInit__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2);
  public final static native float DspFaustMotion_getParamInit__SWIG_1(long jarg1, DspFaustMotion jarg1_, int jarg2);
  public final static native String DspFaustMotion_getMetadata__SWIG_0(long jarg1, DspFaustMotion jarg1_, String jarg2, String jarg3);
  public final static native String DspFaustMotion_getMetadata__SWIG_1(long jarg1, DspFaustMotion jarg1_, int jarg2, String jarg3);
  public final static native void DspFaustMotion_propagateAcc(long jarg1, DspFaustMotion jarg1_, int jarg2, float jarg3);
  public final static native void DspFaustMotion_setAccConverter(long jarg1, DspFaustMotion jarg1_, int jarg2, int jarg3, int jarg4, float jarg5, float jarg6, float jarg7);
  public final static native void DspFaustMotion_propagateGyr(long jarg1, DspFaustMotion jarg1_, int jarg2, float jarg3);
  public final static native void DspFaustMotion_setGyrConverter(long jarg1, DspFaustMotion jarg1_, int jarg2, int jarg3, int jarg4, float jarg5, float jarg6, float jarg7);
  public final static native float DspFaustMotion_getCPULoad(long jarg1, DspFaustMotion jarg1_);
  public final static native int DspFaustMotion_getScreenColor(long jarg1, DspFaustMotion jarg1_);
}
