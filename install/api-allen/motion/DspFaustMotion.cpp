/************************************************************************
 ************************************************************************
 FAUST API Architecture File
 Copyright (C) 2017 GRAME, Allen Weng, SHCM
 Copyright (C) 2014-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/GUI.h"
#include "faust/gui/JSONUIDecoder.h"
#include "faust/dsp/dsp-adapter.h"


#include <math.h>
#include <cmath>


#if OSCCTRL
#define OSC_IP_ADDRESS  "192.168.0.101"
#define OSC_IN_PORT     "5510"
#define OSC_OUT_PORT    "5511"

#include "faust/gui/OSCUI.h"

static void osc_compute_callback(void* arg)
{
    static_cast<OSCUI*>(arg)->endBundle();
}

#endif

//**************************************************************
// Intrinsic
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/faust-poly-engine.h"
#include "faust/dsp/faust-motion-engine.h"

//**************************************************************
// IOS Coreaudio
//**************************************************************

#include "faust/audio/motion-audio.h"


//**************************************************************
// Interface
//**************************************************************


#include "DspFaustMotion.h"


DspFaustMotion::DspFaustMotion(int sample_rate, int buffer_size){
    
    myaudio* driver2= new motion_audio(sample_rate, buffer_size, 0, false, false);
    fMotionEngine = new FaustMotionEngine(NULL,driver2);
    
    // OSC
    #if OSCCTRL
        const char* argv[11];
        argv[0] = "Faust";
        argv[1] = "-xmit";
        #if OSCALL
            argv[2] = "1";
        #endif
        #if OSCALIAS
            argv[2] = "2";
        #endif
        argv[3] = "-desthost";
        argv[4] = OSC_IP_ADDRESS;
        argv[5] = "-port";
        argv[6] = OSC_IN_PORT;
        argv[7] = "-outport";
        argv[8] = OSC_OUT_PORT;
        argv[9] = "-bundle";
        argv[10] = "0";
        fMotionOSCUI = new OSCUI("Faust", 11, (char**)argv);
        driver2->addControlCallback(osc_compute_callback, fMotionOSCUI);
        fMotionEngine->buildUserInterface(fMotionOSCUI);
    #endif

}



DspFaustMotion::~DspFaustMotion(){
    delete fMotionEngine;
    
    #if OSCCTRL
        delete fMotionOSCUI;
    #endif

}

bool DspFaustMotion::start(){
    #if OSCCTRL
        fMotionOSCUI->run();
    #endif

    return fMotionEngine->start();
    
    
}

void DspFaustMotion::stop(){
    #if OSCCTRL
        fMotionOSCUI->stop();
    #endif

    fMotionEngine->stop();
    
    
}
    
void DspFaustMotion::setOSCValue(const char* address, const char* inPort, const char* outPort){

#if OSCCTRL
    if (isRunning()) {
    } else {
#if OSCALL
        oscfaust::OSCControler::gXmit = 1;
#endif
#if OSCALIAS
        oscfaust::OSCControler::gXmit = 2;
#endif
        fMotionOSCUI->setUDPPort(atoi(inPort));
        fMotionOSCUI->setUDPOut(atoi(outPort));
        fMotionOSCUI->setDestAddress(address);
    }
#endif


}

bool DspFaustMotion::setOSCValue(const char* address, int inPort, int outPort){

#if OSCCTRL

    if (isRunning()) {
        return false;
    } else {
#if OSCALL
        oscfaust::OSCControler::gXmit = 1;
#endif
#if OSCALIAS
        oscfaust::OSCControler::gXmit = 2;
#endif
        fMotionOSCUI->setUDPPort(inPort);
        fMotionOSCUI->setUDPOut(outPort);
        fMotionOSCUI->setDestAddress(address);
        return true;
    }

#else
    return false;
#endif

}


void DspFaustMotion::render(){

    fMotionEngine->render();
}

void DspFaustMotion::setInput(int channel, float value) {

    fMotionEngine->setInput(channel, value);
}

float DspFaustMotion::getOutput(int channel) {

    return fMotionEngine->getOutput(channel);

}

int DspFaustMotion::getOutputChannelNum() {

    return fMotionEngine->getOutputChannelNum();
}

int DspFaustMotion::getInputChannelNum() {

    return fMotionEngine->getInputChannelNum();

}

bool DspFaustMotion::isRunning(){
    return fMotionEngine->isRunning();
}


const char* DspFaustMotion::getJSONUI(){
    return fMotionEngine->getJSONUI();
}

const char* DspFaustMotion::getJSONMeta(){
    return fMotionEngine->getJSONMeta();
}

int DspFaustMotion::getParamsCount(){
    return fMotionEngine->getParamsCount();
}

void DspFaustMotion::setParamValue(const char* address, float value){
    fMotionEngine->setParamValue(address, value);
}

const char* DspFaustMotion::getParamAddress(int id){
    return fMotionEngine->getParamAddress(id);
}

void DspFaustMotion::setParamValue(int id, float value){
    fMotionEngine->setParamValue(id, value);
}

float DspFaustMotion::getParamValue(const char* address){
    return fMotionEngine->getParamValue(address);
}

float DspFaustMotion::getParamValue(int id){
    return fMotionEngine->getParamValue(id);
}

float DspFaustMotion::getParamMin(const char* address){
    return fMotionEngine->getParamMin(address);
}

float DspFaustMotion::getParamMin(int id){
    return fMotionEngine->getParamMin(id);
}

float DspFaustMotion::getParamMax(const char* address){
    return fMotionEngine->getParamMax(address);
}

float DspFaustMotion::getParamMax(int id){
    return fMotionEngine->getParamMax(id);
}

float DspFaustMotion::getParamInit(const char* address){
    return fMotionEngine->getParamInit(address);
}

float DspFaustMotion::getParamInit(int id){
    return fMotionEngine->getParamInit(id);
}

const char* DspFaustMotion::getMetadata(const char* address, const char* key)
{
    return fMotionEngine->getMetadata(address, key);
}

const char* DspFaustMotion::getMetadata(int id, const char* key)
{
    return fMotionEngine->getMetadata(id, key);
}

void DspFaustMotion::propagateAcc(int acc, float v){
    fMotionEngine->propagateAcc(acc, v);
}

void DspFaustMotion::setAccConverter(int p, int acc, int curve, float amin, float amid, float amax){
    fMotionEngine->setAccConverter(p, acc, curve, amin, amid, amax);
}

void DspFaustMotion::propagateGyr(int acc, float v){
    fMotionEngine->propagateGyr(acc, v);
}

void DspFaustMotion::setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax){
    fMotionEngine->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

float DspFaustMotion::getCPULoad(){
    return fMotionEngine->getCPULoad();
}

int DspFaustMotion::getScreenColor(){
    return fMotionEngine->getScreenColor();
}
