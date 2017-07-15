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

#include "faust/dsp/faust-poly-engine_a.h"

//**************************************************************
// IOS Coreaudio
//**************************************************************

#include "faust/audio/coreaudio-ios-dsp.h"


//**************************************************************
// Interface
//**************************************************************

#include "DspFaustMotion.h"
#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(DspFaustMotion *dspFaustMotion, int sample_rate, int buffer_size){
    fPolyEngine = new FaustPolyEngine(new iosaudio(sample_rate, buffer_size));
    
    fDSPFAUSTMOTION = dspFaustMotion;
    
#if OSCCTRL
    const char* argv[9];
    argv[0] = "FAUST";
    argv[1] = "-xmit";
    argv[2] = "1";
    argv[3] = "-desthost";
    argv[4] = "192.168.1.5";
    argv[5] = "-port";
    argv[6] = "5510";
    argv[7] = "-outport";
    argv[8] = "5511";
    fOSCUI = new OSCUI("FAUST", 9, (char**)argv);
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

long DspFaust::keyOn(int pitch, int velocity){
    return (long) fPolyEngine->keyOn(pitch, velocity);
}

int DspFaust::keyOff(int pitch){
    return fPolyEngine->keyOff(pitch);
}

long DspFaust::newVoice(){
    return (long) fPolyEngine->newVoice();
}

int DspFaust::deleteVoice(long voice){
    return fPolyEngine->deleteVoice(voice);
}

void DspFaust::allNotesOff(){
    fPolyEngine->allNotesOff();
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

void DspFaust::setOSCValue(const char* address, const char* inPort, const char* outPort){
    
#if OSCCTRL
    delete fOSCUI;
    const char* argv[9];
    argv[0] = "FAUST";
    argv[1] = "-xmit";
    argv[2] = "1";
    argv[3] = "-desthost";
    argv[4] = address;
    argv[5] = "-port";
    argv[6] = inPort;
    argv[7] = "-outport";
    argv[8] = outPort;
    fOSCUI = new OSCUI("FAUST", 9, (char**)argv);
    fPolyEngine->buildUserInterface(fOSCUI);
    fOSCUI->run();
#endif
    
    
}


float DspFaust::getParamValue(const char* address){
    return fPolyEngine->getParamValue(address);
}

float DspFaust::getParamValue(int id){
    return fPolyEngine->getParamValue(id);
}

void DspFaust::setVoiceParamValue(const char* address, long voice, float value){
    fPolyEngine->setVoiceParamValue(address, voice, value);
}

void DspFaust::setVoiceParamValue(int id, long voice, float value){
    fPolyEngine->setVoiceParamValue(id, voice, value);
}

float DspFaust::getVoiceParamValue(const char* address, long voice){
    return fPolyEngine->getVoiceParamValue(address, voice);
}

float DspFaust::getVoiceParamValue(int id, long voice){
    return fPolyEngine->getVoiceParamValue(id, voice);
}

const char* DspFaust::getParamAddress(int id){
    return fPolyEngine->getParamAddress(id);
}

const char* DspFaust::getVoiceParamAddress(int id, long voice){
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
    
    for(int i=0; i<getParamsCount(); i++){
        const char* data = getParamAddress(i);
        if (endsWith(data,"/totalaccel")) {
            totalAccelIsOn = true;
            totalAccelAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/totalaccelOn", 1);
        } else if (endsWith(data,"/totalgyro")) {
            totalGyroIsOn = true;
            totalGyroAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/totalgyroOn", 1);
        } else if (endsWith(data,"/sxp")) {
            sxpIsOn = true;
            sxpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/sxpOn", 1);
        } else if (endsWith(data,"/syp")) {
            sypIsOn = true;
            sypAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/sypOn", 1);
        } else if (endsWith(data,"/szp")) {
            szpIsOn = true;
            szpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/szpOn", 1);
        } else if (endsWith(data,"/sxn")) {
            sxnIsOn = true;
            sxnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/sxnOn", 1);
        } else if (endsWith(data,"/syn")) {
            synIsOn = true;
            synAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/synOn", 1);
        } else if (endsWith(data,"/szn")) {
            sznIsOn = true;
            sznAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/sznOn", 1);
        } else if (endsWith(data,"/ixp")) {
            ixpIsOn = true;
            ixpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ixpOn", 1);
        } else if (endsWith(data,"/iyp")) {
            iypIsOn = true;
            iypAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/iypOn", 1);
        } else if (endsWith(data,"/izp")) {
            izpIsOn = true;
            izpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/izpOn", 1);
        } else if (endsWith(data,"/ixn")) {
            ixnIsOn = true;
            ixnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ixnOn", 1);
        } else if (endsWith(data,"/iyn")) {
            iynIsOn = true;
            iynAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/iynOn", 1);
        } else if (endsWith(data,"/izn")) {
            iznIsOn = true;
            iznAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/iznOn", 1);
        } else if (endsWith(data,"/pixp")) {
            pixpIsOn = true;
            pixpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pixpOn", 1);
        } else if (endsWith(data,"/piyp")) {
            piypIsOn = true;
            piypAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/piypOn", 1);
        } else if (endsWith(data,"/pizp")) {
            pizpIsOn = true;
            pizpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pizpOn", 1);
        } else if (endsWith(data,"/pixn")) {
            pixnIsOn = true;
            pixnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pixnOn", 1);
        } else if (endsWith(data,"/piyn")) {
            piynIsOn = true;
            piynAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/piynOn", 1);
        } else if (endsWith(data,"/pizn")) {
            piznIsOn = true;
            piznAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/piznOn", 1);
        } else if (endsWith(data,"/axpn")) {
            axpnIsOn = true;
            axpnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/axpnOn", 1);
        } else if (endsWith(data,"/aypn")) {
            aypnIsOn = true;
            aypnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/aypnOn", 1);
        } else if (endsWith(data,"/azpn")) {
            azpnIsOn = true;
            azpnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/azpnOn", 1);
        } else if (endsWith(data,"/axp")) {
            axpIsOn = true;
            axpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/axpOn", 1);
        } else if (endsWith(data,"/ayp")) {
            aypIsOn = true;
            aypAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/aypOn", 1);
        } else if (endsWith(data,"/azp")) {
            azpIsOn = true;
            azpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/azpOn", 1);
        } else if (endsWith(data,"/axn")) {
            axnIsOn = true;
            axnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/axnOn", 1);
        } else if (endsWith(data,"/ayn")) {
            aynIsOn = true;
            aynAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/aynOn", 1);
        } else if (endsWith(data,"/azn")) {
            aznIsOn = true;
            aznAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/aznOn", 1);
        } else if (endsWith(data,"/gxpn")) {
            gxpnIsOn = true;
            gxpnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gxpnOn", 1);
        } else if (endsWith(data,"/gypn")) {
            gypnIsOn = true;
            gypnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gypnOn", 1);
        } else if (endsWith(data,"/gzpn")) {
            gzpnIsOn = true;
            gzpnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gzpnOn", 1);
        } else if (endsWith(data,"/gxp")) {
            gxpIsOn = true;
            gxpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gxpOn", 1);
        } else if (endsWith(data,"/gyp")) {
            gypIsOn = true;
            gypAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gypOn", 1);
        } else if (endsWith(data,"/gzp")) {
            gzpIsOn = true;
            gzpAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gzpOn", 1);
        } else if (endsWith(data,"/gxn")) {
            gxnIsOn = true;
            gxnAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gxnOn", 1);
        } else if (endsWith(data,"/gyn")) {
            gynIsOn = true;
            gynAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gynOn", 1);
        } else if (endsWith(data,"/gzn")) {
            gznIsOn = true;
            gznAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/gznOn", 1);
        } else if (endsWith(data,"/brasG_cour")) {
            brasGcourIsOn = true;
            brasGcourAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasG_courOn", 1);
        } else if (endsWith(data,"/brasG_rear")) {
            brasGrearIsOn = true;
            brasGrearAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasG_rearOn", 1);
        } else if (endsWith(data,"/brasG_jardin")) {
            brasGjardinIsOn = true;
            brasGjardinAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasG_jardinOn", 1);
        } else if (endsWith(data,"/brasG_front")) {
            brasGfrontIsOn = true;
            brasGfrontAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasG_frontOn", 1);
        } else if (endsWith(data,"/brasG_down")) {
            brasGdownIsOn = true;
            brasGdownAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasG_downOn", 1);
        } else if (endsWith(data,"/brasG_up")) {
            brasGupIsOn = true;
            brasGupAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasG_upOn", 1);
        } else if (endsWith(data,"/pieds_cour")) {
            piedscourIsOn = true;
            piedscourAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pieds_courOn", 1);
        } else if (endsWith(data,"/pieds_rear")) {
            piedsrearIsOn = true;
            piedsrearAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pieds_rearOn", 1);
        } else if (endsWith(data,"/pieds_jardin")) {
            piedsjardinIsOn = true;
            piedsjardinAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pieds_jardinOn", 1);
        } else if (endsWith(data,"/pieds_front")) {
            piedsfrontIsOn = true;
            piedsfrontAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pieds_frontOn", 1);
        } else if (endsWith(data,"/pieds_down")) {
            piedsdownIsOn = true;
            piedsdownAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pieds_downOn", 1);
        } else if (endsWith(data,"/pieds_up")) {
            piedsupIsOn = true;
            piedsupAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/pieds_upOn", 1);
        } else if (endsWith(data,"/dos_cour")) {
            doscourIsOn = true;
            doscourAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/dos_courOn", 1);
        } else if (endsWith(data,"/dos_rear")) {
            dosrearIsOn = true;
            dosrearAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/dos_rearOn", 1);
        } else if (endsWith(data,"/dos_jardin")) {
            dosjardinIsOn = true;
            dosjardinAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/dos_jardinOn", 1);
        } else if (endsWith(data,"/dos_front")) {
            dosfrontIsOn = true;
            dosfrontAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/dos_frontOn", 1);
        } else if (endsWith(data,"/dos_down")) {
            dosdownIsOn = true;
            dosdownAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/dos_downOn", 1);
        } else if (endsWith(data,"/dos_up")) {
            dosupIsOn = true;
            dosupAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/dos_upOn", 1);
        } else if (endsWith(data,"/brasD_cour")) {
            brasDcourIsOn = true;
            brasDcourAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasD_courOn", 1);
        } else if (endsWith(data,"/brasD_rear")) {
            brasDrearIsOn = true;
            brasDrearAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasD_rearOn", 1);
        } else if (endsWith(data,"/brasD_jardin")) {
            brasDjardinIsOn = true;
            brasDjardinAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasD_jardinOn", 1);
        } else if (endsWith(data,"/brasD_front")) {
            brasDfrontIsOn = true;
            brasDfrontAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasD_frontOn", 1);
        } else if (endsWith(data,"/brasD_down")) {
            brasDdownIsOn = true;
            brasDdownAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasD_downOn", 1);
        } else if (endsWith(data,"/brasD_up")) {
            brasDupIsOn = true;
            brasDupAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/brasD_upOn", 1);
        } else if (endsWith(data,"/tete_cour")) {
            tetecourIsOn = true;
            tetecourAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/tete_courOn", 1);
        } else if (endsWith(data,"/tete_rear")) {
            teterearIsOn = true;
            teterearAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/tete_rearOn", 1);
        } else if (endsWith(data,"/tete_jardin")) {
            tetejardinIsOn = true;
            tetejardinAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/tete_jardinOn", 1);
        } else if (endsWith(data,"/tete_front")) {
            tetefrontIsOn = true;
            tetefrontAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/tete_frontOn", 1);
        } else if (endsWith(data,"/tete_down")) {
            tetedownIsOn = true;
            tetedownAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/tete_downOn", 1);
        } else if (endsWith(data,"/tete_up")) {
            teteupIsOn = true;
            teteupAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/tete_upOn", 1);
        }else if (endsWith(data,"/ventre_cour")) {
            ventrecourIsOn = true;
            ventrecourAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ventre_courOn", 1);
        } else if (endsWith(data,"/ventre_rear")) {
            ventrerearIsOn = true;
            ventrerearAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ventre_rearOn", 1);
        } else if (endsWith(data,"/ventre_jardin")) {
            ventrejardinIsOn = true;
            ventrejardinAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ventre_jardinOn", 1);
        } else if (endsWith(data,"/ventre_front")) {
            ventrefrontIsOn = true;
            ventrefrontAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ventre_frontOn", 1);
        } else if (endsWith(data,"/ventre_down")) {
            ventredownIsOn = true;
            ventredownAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ventre_downOn", 1);
        } else if (endsWith(data,"/ventre_up")) {
            ventreupIsOn = true;
            ventreupAddress = getParamAddress(i);
            fDSPFAUSTMOTION->setParamValue("/Motion/ventre_upOn", 1);
        }
        
        
    }
}


void  DspFaust::sendMotion()  {
    
    if (totalAccelIsOn) {
        setParamValue(totalAccelAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mtotalaccel"));
    }
    if (totalGyroIsOn) {
        setParamValue(totalGyroAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mtotalgyro"));
    }
    if (sxpIsOn) {
        setParamValue(sxpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Msxp"));
    }
    if (sypIsOn) {
        setParamValue(sypAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Msyp"));
    }
    if (szpIsOn) {
        setParamValue(szpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mszp"));
    }
    if (sxnIsOn) {
        setParamValue(sxnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Msxn"));
    }
    if (synIsOn) {
        setParamValue(synAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Msyn"));
    }
    if (sznIsOn) {
        setParamValue(sznAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mszn"));
    }
    if (ixpIsOn) {
        setParamValue(ixpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mixp"));
    }
    if (iypIsOn) {
        setParamValue(iypAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Miyp"));
    }
    if (izpIsOn) {
        setParamValue(izpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mizp"));
    }
    if (ixnIsOn) {
        setParamValue(ixnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mixn"));
    }
    if (iynIsOn) {
        setParamValue(iynAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Miyn"));
    }
    if (iznIsOn) {
        setParamValue(iznAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mizn"));
    }
    if (pixpIsOn) {
        setParamValue(pixpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mpixp"));
    }
    if (piypIsOn) {
        setParamValue(piypAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mpiyp"));
    }
    if (pizpIsOn) {
        setParamValue(pizpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mpizp"));
    }
    if (pixnIsOn) {
        setParamValue(pixnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mpixn"));
    }
    if (piynIsOn) {
        setParamValue(piynAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mpiyn"));
    }
    if (piznIsOn) {
        setParamValue(piznAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mpizn"));
    }
    if (axpnIsOn) {
        setParamValue(axpnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Maxpn"));
    }
    if (aypnIsOn) {
        setParamValue(aypnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Maypn"));
    }
    if (azpnIsOn) {
        setParamValue(azpnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mazpn"));
    }
    if (axpIsOn) {
        setParamValue(axpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Maxp"));
    }
    if (aypIsOn) {
        setParamValue(aypAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mayp"));
    }
    if (azpIsOn) {
        setParamValue(azpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mazp"));
    }
    if (axnIsOn) {
        setParamValue(axnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Maxn"));
    }
    if (aynIsOn) {
        setParamValue(aynAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mayn"));
    }
    if (aznIsOn) {
        setParamValue(aznAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mazn"));
    }
    if (gxpnIsOn) {
        setParamValue(gxpnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgxpn"));
    }
    if (gypnIsOn) {
        setParamValue(gypnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgypn"));
    }
    if (gzpnIsOn) {
        setParamValue(gzpnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgzpn"));
    }
    if (gxpIsOn) {
        setParamValue(gxpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgxp"));
    }
    if (gypIsOn) {
        setParamValue(gypAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgyp"));
    }
    if (gzpIsOn) {
        setParamValue(gzpAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgzp"));
    }
    if (gypIsOn) {
        setParamValue(gypAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgyp"));
    }
    if (gxnIsOn) {
        setParamValue(gxnAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgxn"));
    }
    if (gynIsOn) {
        setParamValue(gynAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgyn"));
    }
    if (gznIsOn) {
        setParamValue(gznAddress, fDSPFAUSTMOTION->getParamValue("/Motion/Mgzn"));
    }
    if (brasGcourIsOn) {
        setParamValue(brasGcourAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasG_cour"));
    }
    if (brasGrearIsOn) {
        setParamValue(brasGrearAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasG_rear"));
    }
    if (brasGjardinIsOn) {
        setParamValue(brasGjardinAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasG_jardin"));
    }
    if (brasGfrontIsOn) {
        setParamValue(brasGfrontAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasG_front"));
    }
    if (brasGdownIsOn) {
        setParamValue(brasGdownAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasG_down"));
    }
    if (brasGupIsOn) {
        setParamValue(brasGupAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasG_up"));
    }
    if (piedscourIsOn) {
        setParamValue(piedscourAddress, fDSPFAUSTMOTION->getParamValue("/Motion/pieds_cour"));
    }
    if (piedsrearIsOn) {
        setParamValue(piedsrearAddress, fDSPFAUSTMOTION->getParamValue("/Motion/pieds_rear"));
    }
    if (piedsjardinIsOn) {
        setParamValue(piedsjardinAddress, fDSPFAUSTMOTION->getParamValue("/Motion/pieds_jardin"));
    }
    if (piedsfrontIsOn) {
        setParamValue(piedsfrontAddress, fDSPFAUSTMOTION->getParamValue("/Motion/pieds_front"));
    }
    if (piedsdownIsOn) {
        setParamValue(piedsdownAddress, fDSPFAUSTMOTION->getParamValue("/Motion/pieds_down"));
    }
    if (piedsupIsOn) {
        setParamValue(piedsupAddress, fDSPFAUSTMOTION->getParamValue("/Motion/pieds_up"));
    }
    if (doscourIsOn) {
        setParamValue(doscourAddress, fDSPFAUSTMOTION->getParamValue("/Motion/dos_cour"));
    }
    if (dosrearIsOn) {
        setParamValue(dosrearAddress, fDSPFAUSTMOTION->getParamValue("/Motion/dos_rear"));
    }
    if (dosjardinIsOn) {
        setParamValue(dosjardinAddress, fDSPFAUSTMOTION->getParamValue("/Motion/dos_jardin"));
    }
    if (dosfrontIsOn) {
        setParamValue(dosfrontAddress, fDSPFAUSTMOTION->getParamValue("/Motion/dos_front"));
    }
    if (dosdownIsOn) {
        setParamValue(dosdownAddress, fDSPFAUSTMOTION->getParamValue("/Motion/dos_down"));
    }
    if (dosupIsOn) {
        setParamValue(dosupAddress, fDSPFAUSTMOTION->getParamValue("/Motion/dos_up"));
    }
    if (brasDcourIsOn) {
        setParamValue(brasDcourAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasD_cour"));
    }
    if (brasDrearIsOn) {
        setParamValue(brasDrearAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasD_rear"));
    }
    if (brasDjardinIsOn) {
        setParamValue(brasDjardinAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasD_jardin"));
    }
    if (brasDfrontIsOn) {
        setParamValue(brasDfrontAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasD_front"));
    }
    if (brasDdownIsOn) {
        setParamValue(brasDdownAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasD_down"));
    }
    if (brasDupIsOn) {
        setParamValue(brasDupAddress, fDSPFAUSTMOTION->getParamValue("/Motion/brasD_up"));
    }
    if (tetecourIsOn) {
        setParamValue(tetecourAddress, fDSPFAUSTMOTION->getParamValue("/Motion/tete_cour"));
    }
    if (teterearIsOn) {
        setParamValue(teterearAddress, fDSPFAUSTMOTION->getParamValue("/Motion/tete_rear"));
    }
    if (tetejardinIsOn) {
        setParamValue(tetejardinAddress, fDSPFAUSTMOTION->getParamValue("/Motion/tete_jardin"));
    }
    if (tetefrontIsOn) {
        setParamValue(tetefrontAddress, fDSPFAUSTMOTION->getParamValue("/Motion/tete_front"));
    }
    if (tetedownIsOn) {
        setParamValue(tetedownAddress, fDSPFAUSTMOTION->getParamValue("/Motion/tete_down"));
    }
    if (teteupIsOn) {
        setParamValue(teteupAddress, fDSPFAUSTMOTION->getParamValue("/Motion/tete_up"));
    }
    if (ventrecourIsOn) {
        setParamValue(ventrecourAddress, fDSPFAUSTMOTION->getParamValue("/Motion/ventre_cour"));
    }
    if (ventrerearIsOn) {
        setParamValue(ventrerearAddress, fDSPFAUSTMOTION->getParamValue("/Motion/ventre_rear"));
    }
    if (ventrejardinIsOn) {
        setParamValue(ventrejardinAddress, fDSPFAUSTMOTION->getParamValue("/Motion/ventre_jardin"));
    }
    if (ventrefrontIsOn) {
        setParamValue(ventrefrontAddress, fDSPFAUSTMOTION->getParamValue("/Motion/ventre_front"));
    }
    if (ventredownIsOn) {
        setParamValue(ventredownAddress, fDSPFAUSTMOTION->getParamValue("/Motion/ventre_down"));
    }
    if (ventreupIsOn) {
        setParamValue(ventreupAddress, fDSPFAUSTMOTION->getParamValue("/Motion/ventre_up"));
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
    
    fDSPFAUSTMOTION->setParamValue("/Motion/brasD_x", (-1)*matrixC[0][0]);
    fDSPFAUSTMOTION->setParamValue("/Motion/brasD_y", (-1)*matrixC[0][1]);
    fDSPFAUSTMOTION->setParamValue("/Motion/brasD_z", (-1)*matrixC[0][2]);
    
    fDSPFAUSTMOTION->setParamValue("/Motion/pieds_x", (-1)*matrixC[1][0]);
    fDSPFAUSTMOTION->setParamValue("/Motion/pieds_y", (-1)*matrixC[1][1]);
    fDSPFAUSTMOTION->setParamValue("/Motion/pieds_z", (-1)*matrixC[1][2]);
    
    fDSPFAUSTMOTION->setParamValue("/Motion/dos_x", (-1)*matrixC[2][0]);
    fDSPFAUSTMOTION->setParamValue("/Motion/dos_y", (-1)*matrixC[2][1]);
    fDSPFAUSTMOTION->setParamValue("/Motion/dos_z", (-1)*matrixC[2][2]);
    
    fDSPFAUSTMOTION->setParamValue("/Motion/brasG_x", matrixC[0][0]);
    fDSPFAUSTMOTION->setParamValue("/Motion/brasG_y", matrixC[0][1]);
    fDSPFAUSTMOTION->setParamValue("/Motion/brasG_z", matrixC[0][2]);
    
    fDSPFAUSTMOTION->setParamValue("/Motion/tete_x", matrixC[1][0]);
    fDSPFAUSTMOTION->setParamValue("/Motion/tete_y", matrixC[1][1]);
    fDSPFAUSTMOTION->setParamValue("/Motion/tete_z", matrixC[1][2]);
    
    fDSPFAUSTMOTION->setParamValue("/Motion/ventre_x", matrixC[2][0]);
    fDSPFAUSTMOTION->setParamValue("/Motion/ventre_y", matrixC[2][1]);
    fDSPFAUSTMOTION->setParamValue("/Motion/ventre_z", matrixC[2][2]);
    
    fDSPFAUSTMOTION->render();
    
    sendMotion();
    
    
}

