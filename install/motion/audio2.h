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

						An abstraction layer over audio2 layer

*******************************************************************************
*******************************************************************************/

#ifndef __audio2__
#define __audio2__

class dsp;

typedef void (* shutdown_callback)(const char* message, void* arg);

class audio2 {
    
public:
			 audio2() {}
    virtual ~audio2() {}
    
    virtual bool init(const char* name, dsp*)               = 0;
    virtual bool start()                                    = 0;
    virtual void stop()                                     = 0;
    virtual void render()                                   = 0;
    virtual void shutdown(shutdown_callback cb, void* arg)  {}
    
    virtual int getBufferSize() = 0;
    virtual int getSampleRate() = 0;
    
    virtual int getNumInputs() { return -1; }
    virtual int getNumOutputs() { return -1; }
    
    virtual float getCPULoad() { return 0.f; }
    
    virtual void setInputValue(int ch,float val)           = 0;
    virtual float getOutputValue(int ch) { return 0.f; }
    
};
					
#endif
