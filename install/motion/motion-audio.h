/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2017 GRAME, Allen Weng, SHCM
 Copyright (C) 2014-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.


 ************************************************************************
 ************************************************************************/

/******************************************************************************
 *******************************************************************************

 A Motion "audio" driver

 *******************************************************************************
 *******************************************************************************/

#ifndef __motion_audio__
#define __motion_audio__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "faust/dsp/dsp.h"
#include "faust/audio/audio_m.h"


class motion_audio : public myaudio {

private:

    dsp* fDSP2;

    long fSampleRate2;
    long fBufferSize2;

    int fNumInputs2;
    int fNumOutputs2;

    FAUSTFLOAT** fInChannel2;
    FAUSTFLOAT** fOutChannel2;

    int fRender;
    int fCount;
    bool fIsSample;
    bool fManager;

public:

    motion_audio(int sr, int bs, int count = 10, bool sample = false, bool manager = false)
    :fSampleRate2(sr), fBufferSize2(bs), fRender(0), fCount(count), fIsSample(sample), fManager(manager) {}

    motion_audio(int count = 10)
    :fSampleRate2(48000), fBufferSize2(512), fRender(0), fCount(count), fIsSample(false), fManager(false) {}

    virtual ~motion_audio()
    {
        for (int i = 0; i < fDSP2->getNumInputs(); i++) {
            delete[] fInChannel2[i];
        }
        for (int i = 0; i < fDSP2->getNumOutputs(); i++) {
            delete[] fOutChannel2[i];
        }

        delete [] fInChannel2;
        delete [] fOutChannel2;
    }

    virtual bool init(const char* name, dsp* dsp)
    {
        fDSP2 = dsp;
        fNumInputs2 = fDSP2->getNumInputs();
        fNumOutputs2 = fDSP2->getNumOutputs();

        if (fManager) {
            // classInit is called elsewhere with a custom memory manager
            fDSP2->instanceInit(fSampleRate2);
        } else {
            fDSP2->init(fSampleRate2);
        }

        fInChannel2 = new FAUSTFLOAT*[fNumInputs2];
        fOutChannel2 = new FAUSTFLOAT*[fNumOutputs2];

        for (int i = 0; i < fDSP2->getNumInputs(); i++) {
            fInChannel2[i] = new FAUSTFLOAT[fBufferSize2];
            memset(fInChannel2[i], 0, sizeof(FAUSTFLOAT) * fBufferSize2);
        }
        for (int i = 0; i < fDSP2->getNumOutputs(); i++) {
            fOutChannel2[i] = new FAUSTFLOAT[fBufferSize2];
            memset(fOutChannel2[i], 0, sizeof(FAUSTFLOAT) * fBufferSize2);
        }
        return true;
    }
    virtual bool start()
    {
        fRender = fCount;
        while (--fRender > 0) {
            printf("Render motion buffer\n");
            render();
        }
        return true;
    }
    virtual void stop()
    {
        printf("stop buffer\n");
    }

    virtual void setInputValue(int channel,float value)
    {
        if (fNumInputs2 > channel) {
            for (int frame = 0; frame < fBufferSize2; frame++) {
                fInChannel2[channel][frame] = value;
            }
        }
    }

    virtual void render()
    {
        fDSP2->compute(fBufferSize2, fInChannel2, fOutChannel2);

        if (fNumInputs2 > 0) {
            if (fIsSample) {
                for (int frame = 0; frame < fBufferSize2; frame++) {
                    std::cout << std::setprecision(6) << "sample in " << fInChannel2[0][frame] << std::endl;
                }
            }
        }
        if (fNumOutputs2 > 0) {
            if (fIsSample) {
                for (int frame = 0; frame < fBufferSize2; frame++) {
                    std::cout << std::fixed << std::setprecision(6) << "sample out " << fOutChannel2[0][frame] << std::endl;
                }
            }
        }

    }

    virtual float getOutputValue(int channel)
    {
        if (fNumOutputs2 > channel) {
            for (int frame = 0; frame < fBufferSize2; frame++) {
                return fOutChannel2[channel][frame];
            }
        }

    }

    virtual int getBufferSize() { return fBufferSize2; }
    virtual int getSampleRate() { return fSampleRate2; }

    virtual int getNumInputs() { return fNumInputs2; }
    virtual int getNumOutputs() { return fNumOutputs2; }

};

#endif
