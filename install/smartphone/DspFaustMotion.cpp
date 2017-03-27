/************************************************************************
 ************************************************************************
 FAUST API Architecture File
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2016 GRAME, Centre National de Creation Musicale
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

#if OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#include <math.h>
#include <cmath>

//**************************************************************
// Intrinsic
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Polyphony
//**************************************************************

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
	fMotionEngine = new FaustMotionEngine(new dummy_audio(sample_rate, buffer_size, 10));


//**************************************************************
// OSC TEST ALLEN
//**************************************************************

// OSC
#if OSCCTRL
    const char* argv[9];
    argv[0] = "0x00";//(char*)_name;
    argv[1] = "-xmit";
    argv[2] = "1";//transmit_value(transmit);
    argv[3] = "-desthost";
    argv[4] = "192.168.1.20";//[outputIPText cStringUsingEncoding:[NSString defaultCStringEncoding]];
    argv[5] = "-port";
    argv[6] = "5512";//[inputPortText cStringUsingEncoding:[NSString defaultCStringEncoding]];
    argv[7] = "-outport";
    argv[8] = "5513";//[outputPortText cStringUsingEncoding:[NSString defaultCStringEncoding]];
    fOSCUI = new OSCUI("0x00", 9, (char**)argv);
    fMotionEngine->buildUserInterface(fOSCUI);

#endif


}



DspFaustMotion::~DspFaustMotion(){
	delete fMotionEngine;

#if OSCCTRL
    delete fOSCUI;
#endif


}

bool DspFaustMotion::start(){

#if OSCCTRL
    fOSCUI->run();
#endif

	return fMotionEngine->start();
}

void DspFaustMotion::stop(){

#if OSCCTRL
    fOSCUI->stop();
#endif

	fMotionEngine->stop();
}


void DspFaustMotion::render(){

    
    fMotionEngine->render();
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

const char* DspFaustMotion::getParamTooltip(const char* address){
    return fMotionEngine->getParamTooltip(address);
}

const char* DspFaustMotion::getParamTooltip(int id){
    return fMotionEngine->getParamTooltip(id);
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
