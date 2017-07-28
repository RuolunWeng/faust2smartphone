/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
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

#if OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#include <math.h>
#include <cmath>

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Audio engine
//**************************************************************

#include "faust/dsp/faust-poly-engine_a.h"

//**************************************************************
// Android Audio
//**************************************************************

#include "faust/audio/android-dsp.h"

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "DspFaustMotion.h"
#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(DspFaustMotion *dspFaustMotion, int sample_rate, int buffer_size){
    fPolyEngine = new FaustPolyEngine(new androidaudio(sample_rate, buffer_size));
    
    fDSPFAUSTMOTION = dspFaustMotion;
    
    //**************************************************************
    // OSC TEST ALLEN
    //**************************************************************
    
    // OSC
#if OSCCTRL
    const char* argv[9];
    argv[0] = "0x00";
    argv[1] = "-xmit";
    argv[2] = "1";
    argv[3] = "-desthost";
    argv[4] = "192.168.1.5";
    argv[5] = "-port";
    argv[6] = "5510";
    argv[7] = "-outport";
    argv[8] = "5511";
    fOSCUI = new OSCUI("0x00", 9, (char**)argv);
    fPolyEngine->buildUserInterface(fOSCUI);
    
#endif
    
    
}

DspFaust::~DspFaust(){
    delete fPolyEngine;
    
#if OSCCTRL
    delete fOSCUI;
#endif
    
}

bool DspFaust::start(){
    
#if OSCCTRL
    fOSCUI->run();
#endif
    
    return fPolyEngine->start();
}

void DspFaust::stop(){
    
#if OSCCTRL
    fOSCUI->stop();
#endif
    
    fPolyEngine->stop();
}

bool DspFaust::isRunning(){
    return fPolyEngine->isRunning();
}

unsigned long DspFaust::keyOn(int pitch, int velocity){
    return (long) fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch){
    return fPolyEngine->keyOff(pitch);
}

unsigned long DspFaust::newVoice(){
    return (long) fPolyEngine->newVoice();
}

int DspFaust::deleteVoice(unsigned long voice){
    return fPolyEngine->deleteVoice(voice);
}

void DspFaust::allNotesOff(){
    fPolyEngine->allNotesOff();
}

void DspFaust::propagateMidi(int count, double time, int type, int channel, int data1, int data2){
    fPolyEngine->propagateMidi(count, time, type, channel, data1, data2);
}

const char* DspFaust::getJSONUI(){
    return fPolyEngine->getJSONUI();
}

const char* DspFaust::getJSONMeta(){
    return fPolyEngine->getJSONMeta();
}

const char* DspFaust::getMeta(const char* name){
    return fPolyEngine->getMeta(name);
}

int DspFaust::getParamsCount(){
    return fPolyEngine->getParamsCount();
}

void DspFaust::setParamValue(const char* address, float value){
    fPolyEngine->setParamValue(address, value);
}

void DspFaust::setParamValue(int id, float value){
    fPolyEngine->setParamValue(id, value);
}


bool DspFaust::setOSCValue(const char* address, int inPort, int outPort){
    
#if OSCCTRL
    
    if (isRunning()) {
        return false;
    } else {
        fOSCUI->setUDPPort(inPort);
        fOSCUI->setUDPOut(outPort);
        fOSCUI->setDestAddress(address);
        return true;
    }
    
#else
    return false;
#endif
    
}

float DspFaust::getParamValue(const char* address){
    return fPolyEngine->getParamValue(address);
}

float DspFaust::getParamValue(int id){
    return fPolyEngine->getParamValue(id);
}

void DspFaust::setVoiceParamValue(const char* address, unsigned long voice, float value){
    fPolyEngine->setVoiceParamValue(address, voice, value);
}

void DspFaust::setVoiceParamValue(int id, unsigned long voice, float value){
    fPolyEngine->setVoiceParamValue(id, voice, value);
}

float DspFaust::getVoiceParamValue(const char* address, unsigned long voice){
    return fPolyEngine->getVoiceParamValue(address, voice);
}

float DspFaust::getVoiceParamValue(int id, unsigned long voice){
    return fPolyEngine->getVoiceParamValue(id, voice);
}

const char* DspFaust::getParamAddress(int id){
    return fPolyEngine->getParamAddress(id);
}

const char* DspFaust::getVoiceParamAddress(int id, unsigned long voice){
    return fPolyEngine->getVoiceParamAddress(id, voice);
}

float DspFaust::getParamMin(const char* address){
    return fPolyEngine->getParamMin(address);
}

float DspFaust::getParamMin(int id){
    return fPolyEngine->getParamMin(id);
}

float DspFaust::getParamMax(const char* address){
    return fPolyEngine->getParamMax(address);
}

float DspFaust::getParamMax(int id){
    return fPolyEngine->getParamMax(id);
}

float DspFaust::getParamInit(const char* address){
    return fPolyEngine->getParamInit(address);
}

float DspFaust::getParamInit(int id){
    return fPolyEngine->getParamInit(id);
}

const char* DspFaust::getParamTooltip(const char* address){
    return fPolyEngine->getParamTooltip(address);
}

const char* DspFaust::getParamTooltip(int id){
    return fPolyEngine->getParamTooltip(id);
}

void DspFaust::propagateAcc(int acc, float v){
    fPolyEngine->propagateAcc(acc, v);
}

void DspFaust::setAccConverter(int p, int acc, int curve, float amin, float amid, float amax){
    fPolyEngine->setAccConverter(p, acc, curve, amin, amid, amax);
}

void DspFaust::propagateGyr(int acc, float v){
    fPolyEngine->propagateGyr(acc, v);
}

void DspFaust::setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax){
    fPolyEngine->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

float DspFaust::getCPULoad(){
    return fPolyEngine->getCPULoad();
}

int DspFaust::getScreenColor(){
    return fPolyEngine->getScreenColor();
}

bool DspFaust::getOSCIsOn() {
#if OSCCTRL
    return true;
#else
    return false;
#endif
}

void DspFaust::initFrame(){
    
    // inverse matrix the matrix reference
    float a11 = matrixA[0][0];
    float a12 = matrixA[0][1];
    float a13 = matrixA[0][2];
    float a21 = matrixA[1][0];
    float a22 = matrixA[1][1];
    float a23 = matrixA[1][2];
    float a31 = matrixA[2][0];
    float a32 = matrixA[2][1];
    float a33 = matrixA[2][2];
    
    float detA=a11*a22*a33+a21*a32*a13+a31*a12*a23-a11*a32*a23-a31*a22*a13-a21*a12*a33;
    
    matrixB[0][0] =(1/detA)*(a22*a33-a23*a32);
    matrixB[0][1] =(1/detA)*(a13*a32-a12*a33);
    matrixB[0][2] =(1/detA)*(a12*a23-a13*a22);
    
    matrixB[1][0] =(1/detA)*(a23*a31-a21*a33);
    matrixB[1][1] =(1/detA)*(a11*a33-a13*a31);
    matrixB[1][2] =(1/detA)*(a13*a21-a11*a23);
    
    matrixB[2][0] =(1/detA)*(a21*a32-a22*a31);
    matrixB[2][1] =(1/detA)*(a12*a31-a11*a32);
    matrixB[2][2] =(1/detA)*(a11*a22-a12*a21);
    
}


void DspFaust::checkAdress() {
    
    paramsMotionNum = fDSPFAUSTMOTION->getOutputChannelNum();
    
    for(int i=0; i<fDSPFAUSTMOTION->getParamsCount(); i++){
        const char* data = fDSPFAUSTMOTION->getParamAddress(i);
        if (endsWith(data,"On")) {
            paramsMotionGates.push_back(data);
            paramsMotionNames.push_back(fDSPFAUSTMOTION->getParamTooltip(i));
            paramsKeys.push_back("/" + paramsMotionNames[i]);
            paramsOn.push_back(false);
            paramsAddress.push_back("");
        }
    }
    
    for(int i=0; i<getParamsCount(); i++){
        const char* data = getParamAddress(i);
        for (int p=0; p< paramsMotionNum; p++) {
            if (endsWith(data,paramsKeys[p])) {
                paramsOn[p] = true;
                paramsAddress[p]= data;
                fDSPFAUSTMOTION->setParamValue(paramsMotionGates[p].c_str(), 1);
            }
        }
        
    }
}


void  DspFaust::sendMotion()  {
    
    for (int i=0; i< paramsMotionNum; i++) {
        if (paramsOn[i]) {
            setParamValue(paramsAddress[i].c_str(), fDSPFAUSTMOTION->getOutput(i));
        }
    }
    
}


void DspFaust::motionRender(float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,float m9){
    
    matrixA[0][0] = m1;
    matrixA[0][1] = m2;
    matrixA[0][2] = m3;
    matrixA[1][0] = m4;
    matrixA[1][1] = m5;
    matrixA[1][2] = m6;
    matrixA[2][0] = m7;
    matrixA[2][1] = m8;
    matrixA[2][2] = m9;
    
    // Initializing elements of matrix mult to 0.
    // Multiplication de matrix
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrixC[i][j] = 0;
        }
    }
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++){
                matrixC[i][j] += matrixA[i][k]* matrixB[k][j];
            }
        }
    }
    
    // brasG
    fDSPFAUSTMOTION->sendInput(0, matrixC[0][0]);
    fDSPFAUSTMOTION->sendInput(1, matrixC[0][1]);
    fDSPFAUSTMOTION->sendInput(2, matrixC[0][2]);
    // pieds
    fDSPFAUSTMOTION->sendInput(3, (-1)*matrixC[1][0]);
    fDSPFAUSTMOTION->sendInput(4, (-1)*matrixC[1][1]);
    fDSPFAUSTMOTION->sendInput(5, (-1)*matrixC[1][2]);
    // dos
    fDSPFAUSTMOTION->sendInput(6, (-1)*matrixC[2][0]);
    fDSPFAUSTMOTION->sendInput(7, (-1)*matrixC[2][1]);
    fDSPFAUSTMOTION->sendInput(8, (-1)*matrixC[2][2]);
    // brasD
    fDSPFAUSTMOTION->sendInput(9, (-1)*matrixC[0][0]);
    fDSPFAUSTMOTION->sendInput(10, (-1)*matrixC[0][1]);
    fDSPFAUSTMOTION->sendInput(11, (-1)*matrixC[0][2]);
    // tête
    fDSPFAUSTMOTION->sendInput(12, matrixC[1][0]);
    fDSPFAUSTMOTION->sendInput(13, matrixC[1][1]);
    fDSPFAUSTMOTION->sendInput(14, matrixC[1][2]);
    // ventre
    fDSPFAUSTMOTION->sendInput(15, matrixC[2][0]);
    fDSPFAUSTMOTION->sendInput(16, matrixC[2][1]);
    fDSPFAUSTMOTION->sendInput(17, matrixC[2][2]);
    
    fDSPFAUSTMOTION->render();
    
    sendMotion();
    
}
