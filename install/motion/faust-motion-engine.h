/************************************************************************
 ************************************************************************
 FAUST Polyphonic Architecture File
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

#ifndef __faust_motion_engine__
#define __faust_motion_engine__

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "faust/misc.h"
#include "faust/dsp/dsp.h"
#include "faust/audio/audio2.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/APIUI.h"
#include "faust/dsp/faust-engine.h"

//**************************************************************
// Motion "audio" DSP engine
//**************************************************************

using namespace std;


class FaustMotionEngine {
    
protected:
    
    dsp* fFinalDSP;           // the "final" dsp object submitted to the audio driver
    
    APIUI fAPIUI;             // the UI description
    
    string fJSONUI;
    string fJSONMeta;
    bool fRunning;
    audio2* fDriver;
    
    
    
public:
    
    FaustMotionEngine(audio2* driver = NULL)
    {
        
        fDriver = driver;
        fRunning = false;
        mydsp* motion_dsp = new mydsp();
        
        fFinalDSP = motion_dsp;
        
        // Update JSONs version
        JSONUI jsonui2(motion_dsp->getNumInputs(), motion_dsp->getNumOutputs());
        fFinalDSP->buildUserInterface(&jsonui2);
        fJSONUI = jsonui2.JSON();
        JSONUI jsonui2M(motion_dsp->getNumInputs(), motion_dsp->getNumOutputs());
        fFinalDSP->metadata(&jsonui2M);
        fJSONMeta = jsonui2M.JSON();
        
        fFinalDSP->buildUserInterface(&fAPIUI);
        
        fDriver->init("Motion", fFinalDSP);
    }
    
    virtual ~FaustMotionEngine()
    {
        delete fDriver;
        delete fFinalDSP;
    }
    
    /*
     * start()
     * Begins the processing and return true if the connection
     * with the audio device was successful and false if not.
     */
    bool start()
    {
        if (!fRunning) {
            fRunning = fDriver->start();
        }
        return fRunning;
    }
    
    /*
     * isRunning()
     * Returns true if the DSP frames are being computed and
     * false if not.
     */
    bool isRunning()
    {
        return fRunning;
    }
    
    /*
     * stop()
     * Stops the processing, closes the audio engine.
     */
    void stop()
    {
        if (fRunning) {
            fRunning = false;
            fDriver->stop();
        }
    }
    
    /*
     * render()
     * Render motion dsp buffer
     */
    
    void render()
    {
        
        fDriver->render();
    }
    
    /*
     * setInput(int,float)
     * connect motion input
     */
    void setInput(int channel,float value)
    {
        fDriver->setInputValue(channel, value);
    }
    
    /*
     * getOutput(int)
     * get motion output
     */
    float getOutput(int channel)
    {
        return fDriver->getOutputValue(channel);
    }
    
    /*
     * getOutputChannelNum()
     * get motion output num
     */
    float getOutputChannelNum()
    {
        return fDriver->getNumOutputs();
    }
    
    /*
     * getInputChannelNum()
     * get motion output
     */
    float getInputChannelNum()
    {
        return fDriver->getNumInputs();
    }

        /*
         * getJSONUI()
         * Returns a string containing a JSON description of the
         * UI of the Faust object.
         */
        const char* getJSONUI()
        {
            return fJSONUI.c_str();
        }

        /*
         * getJSONMeta()
         * Returns a string containing a JSON description of the
         * metadata of the Faust object.
         */
        const char* getJSONMeta()
        {
            return fJSONMeta.c_str();
        }

        /*
         * buildUserInterface(ui)
         * Calls the polyphonic of monophonic buildUserInterface with the ui parameter.
         */
        void buildUserInterface(UI* ui_interface)
        {
            fFinalDSP->buildUserInterface(ui_interface);
        }

        /*
         * getParamsCount()
         * Returns the number of control parameters of the Faust object.
         */
        int getParamsCount()
        {
            return fAPIUI.getParamsCount();
        }

        /*
         * setParamValue(address, value)
         * Sets the value of the parameter associated with address.
         */
        void setParamValue(const char* address, float value)
        {
            int id = fAPIUI.getParamIndex(address);
            if (id >= 0) {
                fAPIUI.setParamValue(id, value);
                // In POLY mode, update all voices
                GUI::updateAllGuis();
            }
        }

        /*
         * getParamValue(address)
         * Takes the address of a parameter and returns its current
         * value.
         */
        float getParamValue(const char* address)
        {
            int id = fAPIUI.getParamIndex(address);
            return (id >= 0) ? fAPIUI.getParamValue(id) : 0.f;
        }

        /*
         * setParamValue(id, value)
         * Sets the value of the parameter associated with id.
         */
        void setParamValue(int id, float value)
        {
            fAPIUI.setParamValue(id, value);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }

        /*
         * getParamValue(id)
         * Takes the id of a parameter and returns its current
         * value.
         */
        float getParamValue(int id)
        {
            return fAPIUI.getParamValue(id);
        }
       /*
       * getParamAddress(id)
       * Returns the address of a parameter in function of its "id".
       */
        const char* getParamAddress(int id)
        {
        return fAPIUI.getParamAddress(id);
        }


        /*
         * getParamMin(address)
         * Returns the minimum value of a parameter.
         */
        float getParamMin(const char* address)
        {
            int id = fAPIUI.getParamIndex(address);
            return (id >= 0) ? fAPIUI.getParamMin(id) : 0.f;
        }

        /*
         * getParamMin(id)
         * Returns the minimum value of a parameter.
         */
        float getParamMin(int id)
        {
            return fAPIUI.getParamMin(id);
        }

        /*
         * getParamMax(address)
         * Returns the maximum value of a parameter.
         */
        float getParamMax(const char* address)
        {
            int id = fAPIUI.getParamIndex(address);
            return (id >= 0) ? fAPIUI.getParamMax(id) : 0.f;
        }

        /*
         * getParamMax(id)
         * Returns the maximum value of a parameter.
         */
        float getParamMax(int id)
        {
            return fAPIUI.getParamMax(id);
        }

        /*
         * getParamInit(address)
         * Returns the default value of a parameter.
         */
        float getParamInit(const char* address)
        {
            int id = fAPIUI.getParamIndex(address);
            return (id >= 0) ? fAPIUI.getParamInit(id) : 0.f;
        }

        /*
         * getParamInit(id)
         * Returns the default value of a parameter.
         */
        float getParamInit(int id)
        {
            return fAPIUI.getParamInit(id);
        }

        /*
         * getMetadata(address, key)
         * Returns the metadata of a parameter.
         */
        const char* getMetadata(const char* address, const char* key)
        {
            int id = fAPIUI.getParamIndex(address);
            return (id >= 0) ? fAPIUI.getMetadata(id, key) : "";
        }
    
        /*
         * getMetadata(id, key)
         * Returns the metadata of a parameter.
         */
        const char* getMetadata(int id, const char* key)
        {
            return fAPIUI.getMetadata(id, key);
        }

        /*
         * propagateAcc(int acc, float v)
         * Propage accelerometer value to the curve conversion layer.
         */
        void propagateAcc(int acc, float v)
        {
            fAPIUI.propagateAcc(acc, v);
            GUI::updateAllGuis();
        }

        /*
         * setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change accelerometer curve mapping.
         */
        void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
        {
           fAPIUI.setAccConverter(p, acc, curve, amin, amid, amax);
        }

        /*
         * propagateGyr(int gyr, float v)
         * Propage gyroscope value to the curve conversion layer.
         */
        void propagateGyr(int gyr, float v)
        {
            fAPIUI.propagateGyr(gyr, v);
            GUI::updateAllGuis();
        }

        /*
         * setGyrConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change gyroscope curve mapping.
         */
        void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
        {
            fAPIUI.setGyrConverter(p, gyr, curve, amin, amid, amax);
        }

        /*
         * getCPULoad()
         * Return DSP CPU load.
         */
        float getCPULoad() { return fDriver->getCPULoad(); }

        /*
         * getScreenColor() -> c:int
         * Get the requested screen color c :
         * c <  0 : no screen color requested (keep regular UI)
         * c >= 0 : requested color (no UI but a colored screen)
         */
        int getScreenColor()
        {
            return fAPIUI.getScreenColor();
        }

};

#endif // __faust_motion_engine__
