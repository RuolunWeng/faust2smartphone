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

//**************************************************************
// Soundfile handling
//**************************************************************

// Must be done before <<includeclass>> otherwise the 'Soundfile' type is not known

#if SOUNDFILE
#include "faust/gui/SoundUI.h"
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

#include "faust/dsp/faust-poly-engine.h"

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

#include "DspFaust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

DspFaust::DspFaust(int sample_rate, int buffer_size)
{
#if IOS_DRIVER
    audio* driver = new iosaudio(sample_rate, buffer_size);
#elif ANDROID_DRIVER
    audio* driver = new androidaudio(sample_rate, buffer_size);
#endif

    init(driver);
}

void DspFaust::init(audio* driver){
	fPolyEngine = new FaustPolyEngine(NULL,driver);

#if IOS_MIDI_SUPPORT
    fMidiUI = new MidiUI(new rt_midi());
	fPolyEngine->buildUserInterface(fMidiUI);
#endif

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
    argv[10] = "1";
    fOSCUI = new OSCUI("Faust", 11, (char**)argv);
    driver->setComputeCb(osc_compute_callback, fOSCUI);
    fPolyEngine->buildUserInterface(fOSCUI);
#endif

#if SOUNDFILE
    // Use bundle path
    fSoundInterface = new SoundUI(SoundUI::getBinaryPath());
    // SoundUI has to be dispatched on all internal voices
    fPolyEngine->setGroup(false);
    fPolyEngine->buildUserInterface(fSoundInterface);
    fPolyEngine->setGroup(true);
#endif

}


DspFaust::~DspFaust(){
	delete fPolyEngine;
#if IOS_MIDI_SUPPORT
    delete fMidiUI;
#endif

#if OSCCTRL
    delete fOSCUI;
#endif

#if SOUNDFILE
    delete fSoundInterface;
#endif


}

bool DspFaust::start(){
#if IOS_MIDI_SUPPORT
    fMidiUI->run();
#endif

#if OSCCTRL
    fOSCUI->run();
#endif

	return fPolyEngine->start();
}

void DspFaust::stop(){
#if IOS_MIDI_SUPPORT
    fMidiUI->stop();
#endif

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

int DspFaust::getParamsCount(){
	return fPolyEngine->getParamsCount();
}

void DspFaust::setParamValue(const char* address, float value){
	fPolyEngine->setParamValue(address, value);
}

void DspFaust::setParamValue(int id, float value){
	fPolyEngine->setParamValue(id, value);
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

const char* DspFaust::getMetadata(const char* address, const char* key)
{
    return fPolyEngine->getMetadata(address, key);
}

const char* DspFaust::getMetadata(int id, const char* key)
{
    return fPolyEngine->getMetadata(id, key);
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
