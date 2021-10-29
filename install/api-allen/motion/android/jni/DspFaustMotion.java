/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.DspFaust;

public class DspFaustMotion {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected DspFaustMotion(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(DspFaustMotion obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dsp_faustJNI.delete_DspFaustMotion(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public DspFaustMotion(int arg0, int arg1) {
    this(dsp_faustJNI.new_DspFaustMotion(arg0, arg1), true);
  }

  public boolean start() {
    return dsp_faustJNI.DspFaustMotion_start(swigCPtr, this);
  }

  public void stop() {
    dsp_faustJNI.DspFaustMotion_stop(swigCPtr, this);
  }

  public void render() {
    dsp_faustJNI.DspFaustMotion_render(swigCPtr, this);
  }

  public void setInput(int arg0, float arg1) {
    dsp_faustJNI.DspFaustMotion_setInput(swigCPtr, this, arg0, arg1);
  }

  public float getOutput(int arg0) {
    return dsp_faustJNI.DspFaustMotion_getOutput(swigCPtr, this, arg0);
  }

  public int getOutputChannelNum() {
    return dsp_faustJNI.DspFaustMotion_getOutputChannelNum(swigCPtr, this);
  }

  public int getInputChannelNum() {
    return dsp_faustJNI.DspFaustMotion_getInputChannelNum(swigCPtr, this);
  }

  public boolean isRunning() {
    return dsp_faustJNI.DspFaustMotion_isRunning(swigCPtr, this);
  }

  public void setOSCValue(String arg0, String arg1, String arg2) {
    dsp_faustJNI.DspFaustMotion_setOSCValue__SWIG_0(swigCPtr, this, arg0, arg1, arg2);
  }

  public boolean setOSCValue(String arg0, int arg1, int arg2) {
    return dsp_faustJNI.DspFaustMotion_setOSCValue__SWIG_1(swigCPtr, this, arg0, arg1, arg2);
  }

  public String getJSONUI() {
    return dsp_faustJNI.DspFaustMotion_getJSONUI(swigCPtr, this);
  }

  public String getJSONMeta() {
    return dsp_faustJNI.DspFaustMotion_getJSONMeta(swigCPtr, this);
  }

  public int getParamsCount() {
    return dsp_faustJNI.DspFaustMotion_getParamsCount(swigCPtr, this);
  }

  public void setParamValue(String arg0, float arg1) {
    dsp_faustJNI.DspFaustMotion_setParamValue__SWIG_0(swigCPtr, this, arg0, arg1);
  }

  public void setParamValue(int arg0, float arg1) {
    dsp_faustJNI.DspFaustMotion_setParamValue__SWIG_1(swigCPtr, this, arg0, arg1);
  }

  public float getParamValue(String arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamValue__SWIG_0(swigCPtr, this, arg0);
  }

  public float getParamValue(int arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamValue__SWIG_1(swigCPtr, this, arg0);
  }

  public String getParamAddress(int arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamAddress(swigCPtr, this, arg0);
  }

  public float getParamMin(String arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamMin__SWIG_0(swigCPtr, this, arg0);
  }

  public float getParamMin(int arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamMin__SWIG_1(swigCPtr, this, arg0);
  }

  public float getParamMax(String arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamMax__SWIG_0(swigCPtr, this, arg0);
  }

  public float getParamMax(int arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamMax__SWIG_1(swigCPtr, this, arg0);
  }

  public float getParamInit(String arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamInit__SWIG_0(swigCPtr, this, arg0);
  }

  public float getParamInit(int arg0) {
    return dsp_faustJNI.DspFaustMotion_getParamInit__SWIG_1(swigCPtr, this, arg0);
  }

  public String getMetadata(String arg0, String arg1) {
    return dsp_faustJNI.DspFaustMotion_getMetadata__SWIG_0(swigCPtr, this, arg0, arg1);
  }

  public String getMetadata(int arg0, String arg1) {
    return dsp_faustJNI.DspFaustMotion_getMetadata__SWIG_1(swigCPtr, this, arg0, arg1);
  }

  public void propagateAcc(int arg0, float arg1) {
    dsp_faustJNI.DspFaustMotion_propagateAcc(swigCPtr, this, arg0, arg1);
  }

  public void setAccConverter(int arg0, int arg1, int arg2, float arg3, float arg4, float arg5) {
    dsp_faustJNI.DspFaustMotion_setAccConverter(swigCPtr, this, arg0, arg1, arg2, arg3, arg4, arg5);
  }

  public void propagateGyr(int arg0, float arg1) {
    dsp_faustJNI.DspFaustMotion_propagateGyr(swigCPtr, this, arg0, arg1);
  }

  public void setGyrConverter(int arg0, int arg1, int arg2, float arg3, float arg4, float arg5) {
    dsp_faustJNI.DspFaustMotion_setGyrConverter(swigCPtr, this, arg0, arg1, arg2, arg3, arg4, arg5);
  }

  public float getCPULoad() {
    return dsp_faustJNI.DspFaustMotion_getCPULoad(swigCPtr, this);
  }

  public int getScreenColor() {
    return dsp_faustJNI.DspFaustMotion_getScreenColor(swigCPtr, this);
  }

}
