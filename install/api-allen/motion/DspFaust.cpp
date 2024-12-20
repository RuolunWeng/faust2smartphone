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

#include <cmath>
#include <cstring>

#include "faust/misc.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/JSONUIDecoder.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/meta.h"

#include "faust/gui/JSONUI.h"
#include "faust/gui/GUI.h"


// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)


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
#include "faust/dsp/faust-poly-engine_m.h"

//**************************************************************
// IOS Coreaudio / Android audio
//**************************************************************

#if IOS_DRIVER
#include "faust/audio/coreaudio-ios-dsp.h"
#elif ANDROID_DRIVER
#include <android/log.h>
#include "faust/audio/android-dsp.h"
#endif

//**************************************************************
// Interface
//**************************************************************

#if IOS_MIDI_SUPPORT
#include "faust/midi/rt-midi.h"
#include "faust/midi/RtMidi.cpp"
#endif

#include "DspFaustMotion.h"
#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static bool hasCompileOption(char* options, const char* option)
{
    char* token;
    const char* sep = " ";
    for (token = strtok(options, sep); token; token = strtok(nullptr, sep)) {
        if (strcmp(token, option) == 0) return true;
    }
    return false;
}

DspFaust::DspFaust(DspFaustMotion *dspFaustMotion, int sample_rate, int buffer_size)
{
#if IOS_DRIVER
    audio* driver = new iosaudio(sample_rate, buffer_size);
#elif ANDROID_DRIVER
    audio* driver = new androidaudio(sample_rate, buffer_size);
#endif

    fDSPFAUSTMOTION = dspFaustMotion;
    
    init(new mydsp(),driver);

    

}

void DspFaust::init(dsp* mono_dsp,audio* driver){
    fPolyEngine = new MyFaustPolyEngine(mono_dsp,driver);

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
    argv[10] = "1";
    fOSCUI = new OSCUI("Faust", 11, (char**)argv);
    //driver->addControlCallback(osc_compute_callback, fOSCUI);
    fPolyEngine->buildUserInterface(fOSCUI);
#endif

#if SOUNDFILE
    // Use bundle path
    // Retrieving DSP object 'compile_options'
    struct MyMeta : public Meta
    {
        string fCompileOptions;
        void declare(const char* key, const char* value)
        {
            if (strcmp(key, "compile_options") == 0) fCompileOptions = value;
        }
        MyMeta(){}
    };
    
    MyMeta meta;
    mono_dsp->metadata(&meta);
    bool is_double = hasCompileOption((char*)meta.fCompileOptions.c_str(), "-double");
    //bool is_double = hasCompileOption((char*)getMeta("compile_options"), "-double");
    fSoundInterface = new SoundUI(SoundUI::getBinaryPath(), -1, nullptr, is_double);
    fPolyEngine->buildUserInterface(fSoundInterface);
#endif

#if IOS_MIDI_SUPPORT
    fMidiUI = new MidiUI(new rt_midi());
	fPolyEngine->buildUserInterface(fMidiUI);
#endif

}



DspFaust::~DspFaust(){
    delete fPolyEngine;

#if OSCCTRL
    delete fOSCUI;
#endif

#if SOUNDFILE
    delete fSoundInterface;
#endif

#if IOS_MIDI_SUPPORT
    delete fMidiUI;
#endif

}

bool DspFaust::start(){

#if OSCCTRL
    fOSCUI->run();
#endif

#if IOS_MIDI_SUPPORT
    fMidiUI->run();
#endif

    return fPolyEngine->start();
}

void DspFaust::stop(){

#if OSCCTRL
    fOSCUI->stop();
#endif

#if IOS_MIDI_SUPPORT
    fMidiUI->stop();
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
    if (isRunning()) {
    } else {
#if OSCALL
        oscfaust::OSCControler::gXmit = 1;
#endif
#if OSCALIAS
        oscfaust::OSCControler::gXmit = 2;
#endif
        fOSCUI->setUDPPort(atoi(inPort));
        fOSCUI->setUDPOut(atoi(outPort));
        fOSCUI->setDestAddress(address);
    }
#endif
    
    fDSPFAUSTMOTION->setOSCValue(address, inPort, outPort);


}

bool DspFaust::setOSCValue(const char* address, int inPort, int outPort){

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
        fOSCUI->setUDPPort(inPort);
        fOSCUI->setUDPOut(outPort);
        fOSCUI->setDestAddress(address);
        return true;
    }

#else
    return false;
#endif
    
    fDSPFAUSTMOTION->setOSCValue(address, inPort, outPort);

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

float DspFaust::getParamStep(int p){
    return fPolyEngine->getParamStep(p);
}

const char* DspFaust::getMetadata(const char* address, const char* key)
{
    return fPolyEngine->getMetadata(address, key);
}

const char* DspFaust::getMetadata(int id, const char* key)
{
    return fPolyEngine->getMetadata(id, key);
}

const char* DspFaust::getParamShortName(int p){
    return fPolyEngine->getParamShortname(p);
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

bool DspFaust::getMIDIIsOn() {
#if IOS_MIDI_SUPPORT
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
    
 // basic setRef used with SHC & GuitareMotion
    matrixD[0][0] =a11;
    matrixD[0][1] =a12;
    matrixD[0][2] =a13;

    matrixD[1][0] =a21;
    matrixD[1][1] =a22;
    matrixD[1][2] =a23;

    matrixD[2][0] =a31;
    matrixD[2][1] =a32;
    matrixD[2][2] =a33;

}


    void DspFaust::checkAdress() {

        paramsMotionNum = fDSPFAUSTMOTION->getOutputChannelNum();


        for(int i=0; i<fDSPFAUSTMOTION->getParamsCount(); i++){
            const char* data = fDSPFAUSTMOTION->getMetadata(i, "motionName");
            if (data != nullptr) {
                if (strcmp(data, "") != 0) {
                    paramsMotionGates.push_back(fDSPFAUSTMOTION->getParamAddress(i));
                    paramsKeys.push_back(data);
                    paramsOn.push_back(false);
                    paramsAddressList.push_back(AddressInit);
                }
            }

        }

        for(int i=0; i<getParamsCount(); i++){
            const char* data = getMetadata(i, "motion");
            if (data != nullptr) {
                for (int p=0; p< paramsMotionNum; p++) {
                    if (MapUI::endsWith(data,paramsKeys[p])) {
                        paramsOn[p] = true;
                        paramsAddressList[p].push_back(getParamAddress(i));
                        fDSPFAUSTMOTION->setParamValue(paramsMotionGates[p].c_str(), 1);
                    }
                }
            }

        }
    }


    void  DspFaust::sendMotion()  {

        //        for (int i=0; i< paramsMotionNum; i++) {
        //            if (paramsOn[i]) {
        //                for (int j=0; j< paramsAddressList[i].size(); j++) {
        //                    setParamValue(paramsAddressList[i][j].c_str(), fDSPFAUSTMOTION->getOutput(i));
        //                }
        //
        //            }
        //        }
                for (int i = 0; i < paramsMotionNum; i++) {
                    if (paramsOn[i]) {
                        for (int j = 0; j < paramsAddressList[i].size(); j++) {
                            // Get the parameter address
                            const char* paramAddress = paramsAddressList[i][j].c_str();

                            // Get the min and max values for this parameter
                            float paramMin = getParamMin(paramAddress);
                            float paramMax = getParamMax(paramAddress);

                            // Get the output value and scale it
                            float outputValue = fDSPFAUSTMOTION->getOutput(i);
                            float normalizedValue;

                            // Check if outputValue is in the range [-1, 1] or [0, 1]
                            if (MapUI::endsWith(paramsKeys[i],"raw")) {
                                // Scale [-1, 1] range to [paramMin, paramMax]
                                // Normalize outputValue from [-1, 1] to [0, 1]
                                normalizedValue = (outputValue + 1.0f) / 2.0f;
                            } else {
                                // Already in the range [0, 1], use directly
                                normalizedValue = outputValue;
                            }

                            // Scale the normalized value to the [paramMin, paramMax] range
                            float scaledValue = paramMin + (normalizedValue * (paramMax - paramMin));
                            // Set the scaled value to the parameter
                            setParamValue(paramAddress, scaledValue);

                        }
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

    // orientation axe des X
    //r00_out = r00*r00_Ref + r10*r10_Ref + r20*r20_Ref;
    //r01_out = r01*r00_Ref + r11*r10_Ref + r21*r20_Ref;
    //r02_out = r02*r00_Ref + r12*r10_Ref + r22*r20_Ref;
    float r00_out = m1 * matrixD[0][0] + m4 * matrixD[1][0] + m7 * matrixD[2][0];
    float r01_out = m2 * matrixD[0][0] + m5 * matrixD[1][0] + m8 * matrixD[2][0];
    float r02_out = m3 * matrixD[0][0] + m6 * matrixD[1][0] + m9 * matrixD[2][0];

    // orientation axe des Y
    // r10_out = (r00*r01_Ref + r10*r11_Ref + r20*r21_Ref)*(-1);
    // r11_out = r01*r01_Ref + r11*r11_Ref + r21*r21_Ref;
    // r12_out = (r02*r01_Ref + r12*r11_Ref + r22*r21_Ref)*(-1);
    float r10_out = m1 * matrixD[0][1] + m4 * matrixD[1][1] + m7 * matrixD[2][1];
    float r11_out = m2 * matrixD[0][1] + m5 * matrixD[1][1] + m8 * matrixD[2][1];
    float r12_out = m3 * matrixD[0][1] + m6 * matrixD[1][1] + m9 * matrixD[2][1];

    // orientation axe des Z
    //r20_out = r00*r02_Ref + r10*r12_Ref + r20*r22_Ref;
    //r21_out = r01*r02_Ref + r11*r12_Ref + r21*r22_Ref;
    //r22_out = r02*r02_Ref + r12*r12_Ref + r22*r22_Ref;
    float r20_out = m1 * matrixD[0][2] + m4 * matrixD[1][2] + m7 * matrixD[2][2];
    float r21_out = m2 * matrixD[0][2] + m5 * matrixD[1][2] + m8 * matrixD[2][2];
    float r22_out = m3 * matrixD[0][2] + m6 * matrixD[1][2] + m9 * matrixD[2][2];

    // brasG
    fDSPFAUSTMOTION->setInput(0, matrixC[0][0]);
    fDSPFAUSTMOTION->setInput(1, matrixC[0][1]);
    fDSPFAUSTMOTION->setInput(2, matrixC[0][2]);

    // pieds
    fDSPFAUSTMOTION->setInput(3, (-1)*matrixC[1][0]);
    fDSPFAUSTMOTION->setInput(4, (-1)*matrixC[1][1]);
    fDSPFAUSTMOTION->setInput(5, (-1)*matrixC[1][2]);

    // dos
    fDSPFAUSTMOTION->setInput(6, (-1)*matrixC[2][0]);
    fDSPFAUSTMOTION->setInput(7, (-1)*matrixC[2][1]);
    fDSPFAUSTMOTION->setInput(8, (-1)*matrixC[2][2]);


    // brasD
    fDSPFAUSTMOTION->setInput(9, (-1)*matrixC[0][0]);
    fDSPFAUSTMOTION->setInput(10, (-1)*matrixC[0][1]);
    fDSPFAUSTMOTION->setInput(11, (-1)*matrixC[0][2]);
    // tête
    fDSPFAUSTMOTION->setInput(12, matrixC[1][0]);
    fDSPFAUSTMOTION->setInput(13, matrixC[1][1]);
    fDSPFAUSTMOTION->setInput(14, matrixC[1][2]);
    // ventre
    fDSPFAUSTMOTION->setInput(15, matrixC[2][0]);
    fDSPFAUSTMOTION->setInput(16, matrixC[2][1]);
    fDSPFAUSTMOTION->setInput(17, matrixC[2][2]);

    // matrix data out usefull SHC or GuitareMotion
    fDSPFAUSTMOTION->setInput(18, r00_out); // MXx
    fDSPFAUSTMOTION->setInput(19, r01_out); // MXy
    fDSPFAUSTMOTION->setInput(20, r02_out); // MXz
    fDSPFAUSTMOTION->setInput(21, r10_out); // MYx
    fDSPFAUSTMOTION->setInput(22, r11_out); // MYy
    fDSPFAUSTMOTION->setInput(23, r12_out); // MYz
    fDSPFAUSTMOTION->setInput(24, r20_out); // MZx
    fDSPFAUSTMOTION->setInput(25, r21_out); // MZy
    fDSPFAUSTMOTION->setInput(26, r22_out); // MZz

    fDSPFAUSTMOTION->render();

    sendMotion();
        
#if OSCCTRL
    fOSCUI->endBundle();
#endif
    
    GUI::updateAllGuis();

}

float DspFaust::getRotationMatrix(int a,int b){

  return matrixC[a][b];

}
