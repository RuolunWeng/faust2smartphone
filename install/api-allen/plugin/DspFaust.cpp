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

#if OSCCTRL
#define OSC_IP_ADDRESS  "192.168.1.108"
#define OSC_IN_PORT     "5510"
#define OSC_OUT_PORT    "5511"

#include "faust/gui/OSCUI.h"

static void osc_compute_callback(void* arg)
{
    static_cast<OSCUI*>(arg)->endBundle();
}

#endif

#include <math.h>
#include <cmath>

//**************************************************************
// Soundfile handling
//**************************************************************

// Must be done before <<includeclass>> otherwise the 'Soundfile' type is not known

#if SOUNDFILE
#include "faust/gui/SoundUI.h"
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


#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(int sample_rate, int buffer_size){
    
    myaudio* driver = new motion_audio(sample_rate, buffer_size, 0, false, false);
    
    fMotionEngine = new FaustMotionEngine(NULL,driver);

    //**************************************************************
    // OSC TEST ALLEN
    //**************************************************************

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
    fOSCUI = new OSCUI("Faust", 11, (char**)argv);
    driver->addControlCallback(osc_compute_callback, fOSCUI);
    fMotionEngine->buildUserInterface(fOSCUI);

#endif

#if SOUNDFILE
    // Use bundle path
    fSoundInterface = new SoundUI(SoundUI::getBinaryPath());
    // SoundUI has to be dispatched on all internal voices
    fMotionEngine->setGroup(false);
    fMotionEngine->buildUserInterface(fSoundInterface);
    fMotionEngine->setGroup(true);
#endif

}


DspFaust::~DspFaust(){
    delete fMotionEngine;

#if OSCCTRL
    delete fOSCUI;
#endif

#if SOUNDFILE
    delete fSoundInterface;
#endif
}

bool DspFaust::start(){

#if OSCCTRL
    fOSCUI->run();
#endif

    return fMotionEngine->start();
}

void DspFaust::stop(){

#if OSCCTRL
    fOSCUI->stop();
#endif

    fMotionEngine->stop();
}


void DspFaust::render(){

    fMotionEngine->render();
}

void DspFaust::setInput(int channel, float value) {

    fMotionEngine->setInput(channel, value);
}

float DspFaust::getOutput(int channel) {

    return fMotionEngine->getOutput(channel);

}

int DspFaust::getOutputChannelNum() {

    return fMotionEngine->getOutputChannelNum();
}

int DspFaust::getInputChannelNum() {

    return fMotionEngine->getInputChannelNum();

}

bool DspFaust::isRunning(){
    return fMotionEngine->isRunning();
}


const char* DspFaust::getJSONUI(){
    return fMotionEngine->getJSONUI();
}

const char* DspFaust::getJSONMeta(){
    return fMotionEngine->getJSONMeta();
}

int DspFaust::getParamsCount(){
    return fMotionEngine->getParamsCount();
}

void DspFaust::setParamValue(const char* address, float value){
    fMotionEngine->setParamValue(address, value);
}

const char* DspFaust::getParamAddress(int id){
    return fMotionEngine->getParamAddress(id);
}

void DspFaust::setParamValue(int id, float value){
    fMotionEngine->setParamValue(id, value);
}

float DspFaust::getParamValue(const char* address){
    return fMotionEngine->getParamValue(address);
}

float DspFaust::getParamValue(int id){
    return fMotionEngine->getParamValue(id);
}

float DspFaust::getParamMin(const char* address){
    return fMotionEngine->getParamMin(address);
}

float DspFaust::getParamMin(int id){
    return fMotionEngine->getParamMin(id);
}

float DspFaust::getParamMax(const char* address){
    return fMotionEngine->getParamMax(address);
}

float DspFaust::getParamMax(int id){
    return fMotionEngine->getParamMax(id);
}

float DspFaust::getParamInit(const char* address){
    return fMotionEngine->getParamInit(address);
}

float DspFaust::getParamInit(int id){
    return fMotionEngine->getParamInit(id);
}

const char* DspFaust::getMetadata(const char* address, const char* key)
{
    return fMotionEngine->getMetadata(address, key);
}

const char* DspFaust::getMetadata(int id, const char* key)
{
    return fMotionEngine->getMetadata(id, key);
}

void DspFaust::propagateAcc(int acc, float v){
    fMotionEngine->propagateAcc(acc, v);
}

void DspFaust::setAccConverter(int p, int acc, int curve, float amin, float amid, float amax){
    fMotionEngine->setAccConverter(p, acc, curve, amin, amid, amax);
}

void DspFaust::propagateGyr(int acc, float v){
    fMotionEngine->propagateGyr(acc, v);
}

void DspFaust::setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax){
    fMotionEngine->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

float DspFaust::getCPULoad(){
    return fMotionEngine->getCPULoad();
}

int DspFaust::getScreenColor(){
    return fMotionEngine->getScreenColor();
}
