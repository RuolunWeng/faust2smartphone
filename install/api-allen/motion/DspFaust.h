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

#ifndef __api_motion__
#define __api_motion__


//===============API Reference==============
//==========================================

class FaustPolyEngine;
class OSCUI;
class DspFaustMotion;
class audio;

class DspFaust
{
public:
    //--------------`DspFaust(int SR, int BS)`----------------
    // Constructor.
    //
    // #### Arguments
    //
    // * `SR`: sampling rate
    // * `BS`: block size
    //--------------------------------------------------------
    DspFaust(DspFaustMotion*,int,int);
    ~DspFaust();
    
    //---------------------`bool start()`---------------------
    // Start the audio processing.
    //
    // Returns `true` if successful and `false` if not.
    //--------------------------------------------------------
    bool start();
    
    //-----------------`void stop()`--------------------------
    // Stop the audio processing.
    //--------------------------------------------------------
    void stop();
    
    //---------------------`bool isRunning()`-----------------
    // Returns `true` if audio is running.
    //--------------------------------------------------------
    bool isRunning();
    
    //--------`long keyOn(int pitch, int velocity)`-----------
    // Instantiate a new polyphonic voice. This method can
    // only be used if the `[style:poly]` metadata is used in
    // the Faust code or if the `-polyvoices` flag has been
    // provided before compilation.
    //
    // `keyOn` will return 0 if the Faust object is not
    // polyphonic or the address to the allocated voice as
    // a `long` otherwise. This value can be used later with
    // [`setVoiceParamValue`](#setvoiceparamvalue) or
    // [`getVoiceParamValue`](#getvoiceparamvalue) to access
    // the parameters of a specific voice.
    //
    // #### Arguments
    //
    // * `pitch`: MIDI note number (0-127)
    // * `velocity`: MIDI velocity (0-127)
    //--------------------------------------------------------
    long keyOn(int, int);
    
    //----------------`int keyOff(int pitch)`-----------------
    // De-instantiate a polyphonic voice. This method can
    // only be used if the `[style:poly]` metadata is used in
    // the Faust code or if the `-polyvoices` flag has been
    // provided before compilation.
    //
    // `keyOff` will return 0 if the object is not polyphonic
    // and 1 otherwise.
    //
    // #### Arguments
    //
    // * `pitch`: MIDI note number (0-127), should be the same
    // as the one used for `keyOn`
    //--------------------------------------------------------
    int keyOff(int);
    
    //-------------------`long newVoice()`--------------------
    // Instantiate a new polyphonic voice. This method can
    // only be used if the `[style:poly]` metadata is used in
    // the Faust code or if `-polyvoices` flag has been
    // provided before compilation.
    //
    // `keyOn` will return 0 if the Faust object is not
    // polyphonic or the address to the allocated voice as
    // a `long` otherwise. This value can be used later with
    // `setVoiceParamValue`, `getVoiceParamValue` or
    // `deleteVoice` to access the parameters of a specific
    // voice.
    //--------------------------------------------------------
    long newVoice();
    
    //---------`int deleteVoice(long voice)`------------------
    // De-instantiate a polyphonic voice. This method can
    // only be used if the `[style:poly]` metadata is used in
    // the Faust code or if `-polyvoices` flag has been
    // provided before compilation.
    //
    // `deleteVoice` will return 0 if the object is not polyphonic
    // and 1 otherwise.
    //
    // #### Arguments
    //
    // * `voice`: the address of the voice given by `newVoice`
    //--------------------------------------------------------
    int deleteVoice(long);
    
    //-----------------`void allNotesOff()`----------------
    // Gently terminates all the active voices.
    //--------------------------------------------------------
    void allNotesOff();
    
    //-----------------`const char* getJSONUI()`----------------
    // Returns the JSON description of the UI of the Faust object.
    //--------------------------------------------------------
    const char* getJSONUI();
    
    //-----------------`const char* getJSONMeta()`----------------
    // Returns the JSON description of the metadata of the Faust object.
    //--------------------------------------------------------
    const char* getJSONMeta();
    
    //-----------------`const char* getMeta(const char*)`----------------
    // Returns the JSON description of the metadata of the Faust object.
    //--------------------------------------------------------
    const char* getMeta(const char*);
    
    
    //-----------------`int getParamsCount()`-----------------
    // Returns the number of parameters of the Faust object.
    //--------------------------------------------------------
    int getParamsCount();
    
    //----`void setParamValue(const char* address, float value)`------
    // Set the value of one of the parameters of the Faust
    // object in function of its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    // * `value`: value of the parameter
    //--------------------------------------------------------
    void setParamValue(const char*, float);
    
    //----`void setOSCValue(const char* address, const char* address, const char* address)`------
    // Set the value of OSC of the Faust
    //
    //
    // #### Arguments
    //
    // * `address`: address of ip
    // * `address`: address of inport
    // * `address`: address of outport
    //--------------------------------------------------------
    void setOSCValue(const char*, const char*, const char*);
    
    // Android version
    bool setOSCValue(const char*, int, int);
    
    //----`void setParamValue(int id, float value)`---
    // Set the value of one of the parameters of the Faust
    // object in function of its id.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    // * `value`: value of the parameter
    //--------------------------------------------------------
    void setParamValue(int, float);
    
    //----`float getParamValue(const char* address)`----------
    // Returns the value of a parameter in function of its
    // address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamValue(const char*);
    
    //---------`float getParamValue(int id)`----------
    // Returns the value of a parameter in function of its
    // id.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamValue(int);
    
    //----`void setVoiceParamValue(const char* address, long voice, float value)`-----
    // Set the value of one of the parameters of the Faust
    // object in function of its address (path) for a
    // specific voice.
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    // * `voice`: address of the polyphonic voice (retrieved
    // from `keyOn`
    // * `value`: value of the parameter
    //--------------------------------------------------------
    void setVoiceParamValue(const char*, long, float);
    
    //----`void setVoiceValue(int id, long voice, float value)`-----
    // Set the value of one of the parameters of the Faust
    // object in function of its id for a
    // specific voice.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    // * `voice`: address of the polyphonic voice (retrieved
    // from `keyOn`
    // * `value`: value of the parameter
    //--------------------------------------------------------
    void setVoiceParamValue(int, long, float);
    
    //----`float getVoiceParamValue(const char* address, long voice)`----
    // Returns the value of a parameter in function of its
    // address (path) for a specific voice.
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    // * `voice`: address of the polyphonic voice (retrieved
    // from `keyOn`)
    //--------------------------------------------------------
    float getVoiceParamValue(const char*, long);
    
    //----`float getVoiceParamValue(int id, long voice)`----
    // Returns the value of a parameter in function of its
    // id for a specific voice.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    // * `voice`: address of the polyphonic voice (retrieved
    // from `keyOn`)
    //--------------------------------------------------------
    float getVoiceParamValue(int, long);
    
    //----`const char* getParamAddress(int id)`---------------
    // Returns the address (path) of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    const char* getParamAddress(int);
    
    //----`const char* getVoiceParamAddress(int id, long voice)`-----
    // Returns the address (path) of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    // * `voice`: address of the polyphonic voice (retrieved
    // from `keyOn`)
    //--------------------------------------------------------
    const char* getVoiceParamAddress(int, long);
    
    //-------`float getParamMin(const char* address)`---------
    // Returns the minimum value of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamMin(const char*);
    
    //--------------`float getParamMin(int id)`---------------
    // Returns the minimum value of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamMin(int);
    
    //-------`float getParamMax(const char* address)`---------
    // Returns the maximum value of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamMax(const char*);
    
    //--------------`float getParamMax(int id)`---------------
    // Returns the maximum value of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamMax(int);
    
    //-------`float getParamInit(const char* address)`---------
    // Returns the default value of a parameter in function of
    // its address (path).
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    float getParamInit(const char*);
    
    //--------------`float getParamInit(int id)`---------------
    // Returns the default value of a parameter in function
    // of its ID.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    float getParamInit(int);
    
    //-----`const char* getMetadata(const char* address, const char* key)`-----
    // Returns the metadataof a parameter in function of
    // its address (path) and the metadata key.
    //
    // #### Arguments
    //
    // * `address`: address (path) of the parameter
    //--------------------------------------------------------
    const char* getMetadata(const char*, const char*);
    
    //----`const char* getMetadata(int id, const char* key)`---------------
    // Returns the metadataof a parameter in function of
    // its iD and the metadata key.
    //
    // #### Arguments
    //
    // * `id`: id of the parameter
    //--------------------------------------------------------
    const char* getMetadata(int, const char*);
    
    
    //----`void propagateAcc(int acc, float v)`---------------
    // Propagate the RAW value of a specific accelerometer
    // axis to the Faust object.
    //
    // #### Arguments
    //
    // * `acc`: the accelerometer axis (**0**: x, **1**: y, **2**: z)
    // * `v`: the RAW acceleromter value in m/s
    //--------------------------------------------------------
    void propagateAcc(int, float);
    
    //----`void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)`-----
    // Set the conversion curve for the accelerometer.
    //
    // #### Arguments
    //
    // * `p`: the UI parameter id
    // * `acc`: the accelerometer axis (**0**: x, **1**: y, **2**: z)
    // * `curve`: the curve (**0**: up, **1**: down, **2**: up and down)
    // * `amin`: mapping min point
    // * `amid`: mapping middle point
    // * `amax`: mapping max point
    //--------------------------------------------------------
    // TODO: eventually should add a link to tutorials on this in the doc
    void setAccConverter(int, int, int, float, float, float);
    
    //----`void propagateGyr(int gyr, float v)`---------------
    // Propagate the RAW value of a specific gyroscope
    // axis to the Faust object.
    //
    // #### Arguments
    //
    // * `gyr`: the gyroscope axis (**0**: x, **1**: y, **2**: z)
    // * `v`: the RAW acceleromter value in m/s
    //--------------------------------------------------------
    void propagateGyr(int, float);
    
    //----`void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)`-----
    // Set the conversion curve for the gyroscope.
    //
    // #### Arguments
    //
    // * `p`: the UI parameter id
    // * `acc`: the accelerometer axis (**0**: x, **1**: y, **2**: z)
    // * `curve`: the curve (**0**: up, **1**: down, **2**: up and down)
    // * `amin`: mapping min point
    // * `amid`: mapping middle point
    // * `amax`: mapping max point
    //--------------------------------------------------------
    // TODO: eventually should add a link to tutorials on this in the doc
    void setGyrConverter(int, int, int, float, float, float);
    
    //------------------`float getCPULoad()`------------------
    // Returns the CPU load.
    //--------------------------------------------------------
    float getCPULoad();
    
    int getScreenColor();
    
    //------------------`bool getOSCIsOn()`------------------
    // Returns OSC is ON or OFF.
    //--------------------------------------------------------
    bool getOSCIsOn();
    
    //----`void motionRender(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)`-----
    // Calul the Rotaiton matrix value
    //
    // #### Arguments
    //
    // * `float m..`: element of rotation matrix
    //--------------------------------------------------------
    void motionRender(float,float,float,float,float,float,float,float,float);
    
    //------------------`void initFrame()`------------------
    // Set Reference Frame for Rotation matrix
    //--------------------------------------------------------
    void initFrame();
    
    //------------------`void sendMotion()`------------------
    // Set motion value to controllers correspontants
    //--------------------------------------------------------
    void sendMotion();
    
    //------------------`void checkAdress()`------------------
    // Active the process correspontant in motion engine
    //--------------------------------------------------------
    void checkAdress();
    
private:
    FaustPolyEngine *fPolyEngine;
    OSCUI *fOSCUI;
    DspFaustMotion *fDSPFAUSTMOTION;
    
    void init(audio* driver);
    
    float matrixA[3][3];
    float matrixB[3][3];
    float matrixC[3][3];
    
    int paramsMotionNum;
    std::vector<std::string>paramsAddress;
    std::vector<bool>paramsOn;
    std::vector<std::string>paramsKeys;
    std::vector<std::string>paramsMotionGates;
    std::vector<std::string>paramsMotionNames;
    
    /* LIST OF MOTION LIB IN ORDER 
    std::string paramsMotion[74] = {"sxp","syp","szp","sxn","syn","szn","ixp","iyp"
        ,"izp","ixn","iyn","izn","pixp","piyp","pizp","pixn","piyn","pizn","axpn"
        ,"aypn","azpn","axp","ayp","azp","axn","ayn","azn","totalaccel"
        ,"gxpn","gypn","gzpn","gxp","gyp","gzp","gxn","gyn","gzn","totalgyro"
        ,"brasG_cour","brasG_rear","brasG_jardin","brasG_front","brasG_down","brasG_up"
        ,"pieds_cour","pieds_rear","pieds_jardin","pieds_front","pieds_down","pieds_up"
        ,"dos_cour","dos_rear","dos_jardin","dos_front","dos_down","dos_up"
        ,"brasD_cour","brasD_rear","brasD_jardin","brasD_front","brasD_down","brasD_up"
        ,"tete_cour","tete_rear","tete_jardin","tete_front","tete_down","tete_up"
        ,"ventre_cour","ventre_rear","ventre_jardin","ventre_front","ventre_down","ventre_up"};
     */
    
};

#endif
