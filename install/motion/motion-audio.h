/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
			
#include "faust/dsp/dsp.h"
#include "faust/audio/audio2.h"


class dummy_audio : public audio2 {

    private:

        dsp* fDSP2;

        long fSampleRate2;
        long fBufferSize2; 

        FAUSTFLOAT** fInChannel2;
        FAUSTFLOAT** fOutChannel2;  

        int fCount;

    public:

        dummy_audio(int count = 10)
            :fSampleRate2(48000), fBufferSize2(512), fCount(count) {}
        dummy_audio(int srate, int bsize, int count = 10)
            :fSampleRate2(srate), fBufferSize2(bsize), fCount(count) {}
    
        virtual ~dummy_audio() 
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
            fDSP2->init(fSampleRate2);
            
            fInChannel2 = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fOutChannel2 = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
            
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
            printf("Render Motion\n");
            //printf("...\n");
            
            render();
    
            return true;
        }
        virtual void stop()
        {
            
            delete fDSP2;
            printf("stop buffer\n");
        }

        virtual void render()
        {
            fDSP2->compute(fBufferSize2, fInChannel2, fOutChannel2);
            //printf("...\n");
        }

        virtual int get_buffer_size() { return 0; }
        virtual int get_sample_rate() { return 0; }
    
};
					
#endif
