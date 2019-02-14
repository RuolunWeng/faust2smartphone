//----------------------------------------------------------
// name: "Faust Motion Library [Motion+RotationMatrix]"
// version: "0.7"
//
// Code generated with Faust 2.15.4 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
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

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <cstdlib>
#include <string.h>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

static int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

static int int2pow2(int x) { int r = 0; while ((1<<r) < x) r++; return r; }

static long lopt(char* argv[], const char* name, long def)
{
	int	i;
    for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return std::atoi(argv[i+1]);
	return def;
}

static bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

static const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param samplingRate - the sampling rate in Hertz
         */
        virtual void init(int samplingRate) = 0;

        /**
         * Init instance state
         *
         * @param samplingRate - the sampling rate in Hertz
         */
        virtual void instanceInit(int samplingRate) = 0;

        /**
         * Init instance constant state
         *
         * @param samplingRate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __dsp_adapter__
#define __dsp_adapter__

#include <string.h>
#include <iostream>

// Adapts a DSP for a different number of inputs/outputs

class dsp_adapter : public decorator_dsp {
    
    private:
        
        FAUSTFLOAT** fAdaptedInputs;
        FAUSTFLOAT** fAdaptedOutputs;
        int fHardwareInputs;
        int fHardwareOutputs;
        
        void adaptBuffers(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fHardwareInputs; i++) {
                fAdaptedInputs[i] = inputs[i];
            }
            for (int i = 0; i < fHardwareOutputs; i++) {
                fAdaptedOutputs[i] = outputs[i];
            }
        }
        
    public:
        
        dsp_adapter(dsp* dsp, int hardware_inputs, int hardware_outputs, int buffer_size):decorator_dsp(dsp)
        {
            fHardwareInputs = hardware_inputs;
            fHardwareOutputs = hardware_outputs;
             
            fAdaptedInputs = new FAUSTFLOAT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs() - fHardwareInputs; i++) {
                fAdaptedInputs[i + fHardwareInputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedInputs[i + fHardwareInputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            
            fAdaptedOutputs = new FAUSTFLOAT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs() - fHardwareOutputs; i++) {
                fAdaptedOutputs[i + fHardwareOutputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedOutputs[i + fHardwareOutputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
        
        virtual ~dsp_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs() - fHardwareInputs; i++) {
                delete [] fAdaptedInputs[i + fHardwareInputs];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs() - fHardwareOutputs; i++) {
                delete [] fAdaptedOutputs[i + fHardwareOutputs];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual int getNumInputs() { return fHardwareInputs; }
        virtual int getNumOutputs() { return fHardwareOutputs; }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(date_usec, count, fAdaptedInputs, fAdaptedOutputs);
        }
        
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(count, fAdaptedInputs, fAdaptedOutputs);
        }
};

// Adapts a DSP for a different sample size

template <typename TYPE_INT, typename TYPE_EXT>
class dsp_sample_adapter : public decorator_dsp {
    
    protected:
    
        TYPE_INT** fAdaptedInputs;
        TYPE_INT** fAdaptedOutputs;
    
        void adaptInputBuffers(int count, FAUSTFLOAT** inputs)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    fAdaptedInputs[chan][frame] = TYPE_INT(reinterpret_cast<TYPE_EXT**>(inputs)[chan][frame]);
                }
            }
        }
    
        void adaptOutputsBuffers(int count, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    reinterpret_cast<TYPE_EXT**>(outputs)[chan][frame] = TYPE_EXT(fAdaptedOutputs[chan][frame]);
                }
            }
        }
    
    public:
    
        dsp_sample_adapter(dsp* dsp):decorator_dsp(dsp)
        {
            fAdaptedInputs = new TYPE_INT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs(); i++) {
                fAdaptedInputs[i] = new TYPE_INT[4096];
            }
            
            fAdaptedOutputs = new TYPE_INT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs(); i++) {
                fAdaptedOutputs[i] = new TYPE_INT[4096];
            }
        }
    
        virtual ~dsp_sample_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fAdaptedInputs[i];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fAdaptedOutputs[i];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses SAMPLE_TYPE
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses SAMPLE_TYPE
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
       }
};

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/
 
#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <iostream>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
# pragma warning (disable: 4334)
#else
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

static ringbuffer_t *ringbuffer_create(size_t sz);
static void ringbuffer_free(ringbuffer_t *rb);
static void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
static void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
static size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
static size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
static void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_read_space(const ringbuffer_t *rb);
static int ringbuffer_mlock(ringbuffer_t *rb);
static void ringbuffer_reset(ringbuffer_t *rb);
static void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
static size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
static void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two. */

static ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

static void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

static int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading. This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

static size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing. This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

static size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader. Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance. Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

static size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer. Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

static void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

static void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader. `vec' is an array of two places. Set
   the values at `vec' to hold the current readable data at `rb'. If
   the readable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer. `vec' is an array of two places. Set
   the values at `vec' to hold the current writeable data at `rb'. If
   the writeable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone) {}
    
    virtual ~uiItemBase()
    {}
    
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    virtual double cache() = 0;
    virtual void reflectZone() = 0;
};


static void deleteClist(clist* cl);

struct clist : public std::list<uiItemBase*>
{
    
    virtual ~clist()
    {
        deleteClist(this);
    }
        
};

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data);

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*> fGuiList;
        zmap fZoneMap;
        bool fStopped;
        
     public:
            
        GUI():fStopped(false)
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all items
            zmap::iterator it;
            for (it = fZoneMap.begin(); it != fZoneMap.end(); it++) {
                delete (*it).second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItemBase* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        }
 
        void updateAllZones()
        {
            for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++) {
                FAUSTFLOAT* z = m->first;
                clist*	l = m->second;
                if (z) {
                    FAUSTFLOAT v = *z;
                    for (clist::iterator c = l->begin(); c != l->end(); c++) {
                        if ((*c)->cache() != v) (*c)->reflectZone();
                    }
                }
            }
        }
        
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* l = fZoneMap[z];
            for (clist::iterator c = l->begin(); c != l->end(); c++) {
                if ((*c)->cache() != v) (*c)->reflectZone();
            }
        }
    
        static void updateAllGuis()
        {
            std::list<GUI*>::iterator g;
            for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
                (*g)->updateAllZones();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        virtual void show() {};	
        virtual bool run() { return false; };

        static void runAllGuis() {
            std::list<GUI*>::iterator g;
            for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
                (*g)->run();
            }
        }
    
        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {};
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition
 */

template <typename REAL>
class uiTypedItem : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItem(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItem()
        {}
    
        void modifyZone(REAL v)
        {
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
    
        double cache() { return fCache; }
    
};

class uiItem : public uiTypedItem<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItem<FAUSTFLOAT>(ui, zone)
        {}

    public:

        virtual ~uiItem() 
        {}

		void modifyZone(FAUSTFLOAT v)
		{
			fCache = v;
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

};

/**
 * User Interface item owned (and so deleted) by external code
 */

class uiOwnedItem : public uiItem {
    
    protected:
    
        uiOwnedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
    
     public:
    
        virtual ~uiOwnedItem()
        {}
    
        virtual void reflectZone() {}
};

/**
 * Callback Item
 */

class uiCallbackItem : public uiItem {
    
    protected:
    
        uiCallback fCallback;
        void* fData;
    
    public:
    
        uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
        : uiItem(ui, zone), fCallback(foo), fData(data) {}
        
        virtual void reflectZone() 
        {		
            FAUSTFLOAT v = *fZone;
            fCache = v; 
            fCallback(v, fData);	
        }
};

/**
 *  For timestamped control
 */

struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items
 */

class uiTimedItem : public uiItem
{
    
    protected:
        
        bool fDelete;
        
    public:
    
        using uiItem::modifyZone;
        
        uiTimedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiTimedItem()
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }
        
        virtual void modifyZone(double date, FAUSTFLOAT v)
        {
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                std::cerr << "ringbuffer_write error DatedControl" << std::endl;
            }
        }
    
};

/**
 * Allows to group a set of zones
 */

class uiGroupItem : public uiItem
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            std::vector<FAUSTFLOAT*>::iterator it;
            for (it = fZoneMap.begin(); it != fZoneMap.end(); it++) {
                (*(*it)) = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Can not be defined as method in the classes

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    std::list<uiItemBase*>::iterator it;
    for (it = cl->begin(); it != cl->end(); it++) {
        uiOwnedItem* owned = static_cast<uiOwnedItem*>(*it);
        // owned items are deleted by external code
        if (!owned) {
            delete (*it);
        }
    }
}

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    std::string index;
    std::string init;
    std::string min;
    std::string max;
    std::string step;
    std::vector<std::pair<std::string, std::string> > meta;
};

/*
// Menu {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values);
static bool parseMenuItem(const char*& p, std::string& name, double& value);

// Menu {'foo.wav'; 'bar.wav'}
static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug = false);
static bool parseMenuItem2(const char*& p, std::string& name);

static void skipBlank(const char*& p);
static bool parseChar(const char*& p, char x);
static bool parseWord(const char*& p, const char* w);
static bool parseString(const char*& p, char quote, std::string& s);
static bool parseSQString(const char*& p, std::string& s);
static bool parseDQString(const char*& p, std::string& s);
static bool parseDouble(const char*& p, double& x);
static bool parseList(const char*& p, std::vector<std::string>& items);
*/

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    std::cerr << "Parse error : " << errmsg << " here : " << p << std::endl;
    return true;
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
static bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    double sign = +1.0;    // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part
    
    bool valid = false;    // true if the number contains at least one digit
    skipBlank(p);
    const char* saved = p; // to restore position if we fail
    
    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    if (valid)  {
        x = sign*(ipart + dpart/dcoef);
    } else {
        p = saved;
    }
    return valid;
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseString(const char*& p, char quote, std::string& s)
{
    std::string str;
    skipBlank(p);
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseSQString(const char*& p, std::string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseDQString(const char*& p, std::string& s)
{
    return parseString(p, '"', s);
}

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
static bool parseMenuItem(const char*& p, std::string& name, double& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

static bool parseMenuItem2(const char*& p, std::string& name)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values)
{
    std::vector<std::string> tmpnames;
    std::vector<double> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            std::string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug)
{
    std::vector<std::string> tmpnames;
    const char* saved = p;  // to restore position if we fail
    
    if (parseChar(p, '{')) {
        do {
            std::string n;
            if (parseMenuItem2(p, n)) {
                tmpnames.push_back(n);
            } else {
                goto error;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            return true;
        }
    }
    
error:
    if (debug) { std::cerr << "parseMenuList2 : (" << saved << ") is not a valid list !\n"; }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of strings
/// ---------------------------------------------------------------------
static bool parseList(const char*& p, std::vector<std::string>& items)
{
    const char* saved = p;  // to restore position if we fail
    if (parseChar(p, '[')) {
        do {
            std::string item;
            if (!parseDQString(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items));
        }
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo*>& uiItems, int& numItems)
{
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo* item = new itemInfo;
                        item->type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->index = value;
                    }
                }
                
                else if (label == "meta") {
                    itemInfo* item = uiItems[numItems];
                    if (!parseItemMetaData(p, item->meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->init = value;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->min = value;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->max = value;
                    }
                }
                
                else if (label == "step"){
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->step = value;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do { 
                            if (!parseUI(p, uiItems, numItems)) {
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo* item = new itemInfo;
                            item->type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                return false;
            }
            
        } while (tryChar(p, ','));
        
        return parseChar(p, '}');
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p, std::map<std::string, std::string>& metadatas1, std::map<std::string, std::vector<std::string> >& metadatas2, std::vector<itemInfo*>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, metadatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metadatas2[key] = items;
                    items.clear();
                } else {
                    metadatas1[key] = value;
                }
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

static FAUSTFLOAT STR2REAL(const std::string& s) { return FAUSTFLOAT(std::strtod(s.c_str(), NULL)); }

//-------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface'
//-------------------------------------------------------------------

struct Soundfile;

typedef std::map<std::string, std::pair <int, FAUSTFLOAT*> > controlMap;

struct JSONUIDecoder {

    std::string fName;
    std::string fFileName;
    
    std::map<std::string, std::string> fMetadatas;
    std::vector<itemInfo*> fUiItems;     
    
    FAUSTFLOAT* fInControl;
    FAUSTFLOAT* fOutControl;
    Soundfile** fSoundfiles;
    
    std::string fJSON;
    
    int fNumInputs, fNumOutputs; 
    int fInputItems, fOutputItems, fSoundfileItems;
    
    std::string fVersion;
    std::string fCompileOptions;
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    int fDSPSize;
    
    controlMap fPathInputTable;     // [path, <index, zone>]
    controlMap fPathOutputTable;    // [path, <index, zone>]

    bool isInput(const std::string& type) { return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox"); }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }

    JSONUIDecoder(const std::string& json) 
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::vector<std::string> > meta_datas;
        parseJson(p, fMetadatas, meta_datas, fUiItems);
        
        // fMetadatas will contain the "meta" section as well as <name : val>, <inputs : val>, <ouputs : val> pairs
        if (fMetadatas.find("name") != fMetadatas.end()) {
            fName = fMetadatas["name"];
            fMetadatas.erase("name");
        } else {
            fName = "";
        }
        
        if (fMetadatas.find("filename") != fMetadatas.end()) {
            fFileName = fMetadatas["filename"];
            fMetadatas.erase("filename");
        } else {
            fName = "";
        }
     
        if (fMetadatas.find("version") != fMetadatas.end()) {
            fVersion = fMetadatas["version"];
            fMetadatas.erase("version");
        } else {
            fVersion = "";
        }
        
        if (fMetadatas.find("compile_options") != fMetadatas.end()) {
            fCompileOptions = fMetadatas["compile_options"];
            fMetadatas.erase("compile_options");
        } else {
            fCompileOptions = "";
        }
        
        if (meta_datas.find("library_list") != meta_datas.end()) {
            fLibraryList = meta_datas["library_list"];
            meta_datas.erase("library_list");
        }
        
        if (meta_datas.find("include_pathnames") != meta_datas.end()) {
            fIncludePathnames = meta_datas["include_pathnames"];
            meta_datas.erase("include_pathnames");
        }
  
        if (fMetadatas.find("size") != fMetadatas.end()) {
            fDSPSize = std::atoi(fMetadatas["size"].c_str());
            fMetadatas.erase("size");
        } else {
            fDSPSize = -1;
        }
         
        if (fMetadatas.find("inputs") != fMetadatas.end()) {
            fNumInputs = std::atoi(fMetadatas["inputs"].c_str());
            fMetadatas.erase("inputs");
        } else {
            fNumInputs = -1;
        }
        
        if (fMetadatas.find("outputs") != fMetadatas.end()) {
            fNumOutputs = std::atoi(fMetadatas["outputs"].c_str());
            fMetadatas.erase("outputs");
        } else {
            fNumOutputs = -1;
        }
       
        fInputItems = 0;
        fOutputItems = 0;
        fSoundfileItems = 0;
        
        std::vector<itemInfo*>::iterator it;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            std::string type = (*it)->type;
            if (isInput(type)) {
                fInputItems++;
            } else if (isOutput(type)) {
                fOutputItems++;          
            } else if (isSoundfile(type)) {
                fSoundfileItems++;
            }
        }
        
        fInControl = new FAUSTFLOAT[fInputItems];
        fOutControl = new FAUSTFLOAT[fOutputItems];
        fSoundfiles = new Soundfile*[fSoundfileItems];
        
        int counterIn = 0;
        int counterOut = 0;
        
        // Prepare the fPathTable and init zone
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            std::string type = (*it)->type;
            // Meta data declaration for input items
            if (isInput(type)) {
                if ((*it)->address != "") {
                    fPathInputTable[(*it)->address] = std::make_pair(std::atoi((*it)->index.c_str()), &fInControl[counterIn]);
                }
                fInControl[counterIn] = STR2REAL((*it)->init);
                counterIn++;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                if ((*it)->address != "") {
                    fPathOutputTable[(*it)->address] = std::make_pair(std::atoi((*it)->index.c_str()), &fOutControl[counterOut]);
                }
                fOutControl[counterOut] = FAUSTFLOAT(0);
                counterOut++;
            }
        }
    }
    
    virtual ~JSONUIDecoder() 
    {
        std::vector<itemInfo*>::iterator it;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            delete(*it);
        }
        delete [] fInControl;
        delete [] fOutControl;
        delete [] fSoundfiles;
    }
    
    void metadata(Meta* m)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = fMetadatas.begin(); it != fMetadatas.end(); it++) {
            m->declare((*it).first.c_str(), (*it).second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        std::vector<itemInfo*>::iterator it;
        int item = 0;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            if (isInput((*it)->type)) {
                fInControl[item++] = STR2REAL((*it)->init);
            }
        }
    }
   
    void buildUserInterface(UI* ui)
    {
        // To be sure the floats are correctly encoded
        char* tmp_local = setlocale(LC_ALL, NULL);
        setlocale(LC_ALL, "C");

        int counterIn = 0;
        int counterOut = 0;
        int counterSound = 0;
        std::vector<itemInfo*>::iterator it;
        
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            
            std::string type = (*it)->type;
            
            FAUSTFLOAT init = STR2REAL((*it)->init);
            FAUSTFLOAT min = STR2REAL((*it)->min);
            FAUSTFLOAT max = STR2REAL((*it)->max);
            FAUSTFLOAT step = STR2REAL((*it)->step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                fInControl[counterIn] = init;
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    ui->declare(&fInControl[counterIn], (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                fOutControl[counterOut] = init;
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    ui->declare(&fOutControl[counterOut], (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    ui->declare(0, (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui->openHorizontalBox((*it)->label.c_str());
            } else if (type == "vgroup") { 
                ui->openVerticalBox((*it)->label.c_str());
            } else if (type == "tgroup") {
                ui->openTabBox((*it)->label.c_str());
            } else if (type == "vslider") {
                ui->addVerticalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
            } else if (type == "hslider") {
                ui->addHorizontalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);            
            } else if (type == "checkbox") {
                ui->addCheckButton((*it)->label.c_str(), &fInControl[counterIn]);
            } else if (type == "soundfile") {
                ui->addSoundfile((*it)->label.c_str(), (*it)->url.c_str(), &fSoundfiles[counterSound]);
            } else if (type == "hbargraph") {
                ui->addHorizontalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
            } else if (type == "vbargraph") {
                ui->addVerticalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
            } else if (type == "nentry") {
                ui->addNumEntry((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
            } else if (type == "button") {
                ui->addButton((*it)->label.c_str(), &fInControl[counterIn]);
            } else if (type == "close") {
                ui->closeBox();
            }
            
            if (isInput(type)) {
                counterIn++;
            } else if (isOutput(type)) {
                counterOut++;
            } else if (isSoundfile(type)) {
                counterSound++;
            }
        }
        
        setlocale(LC_ALL, tmp_local);
    }
    
    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) return true;
        }
        return false;
    }
    
};

#endif


#include <math.h>
#include <cmath>

//**************************************************************
// Intrinsic
//**************************************************************


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp2
#endif

class mydsp2 : public dsp {
  private:
	FAUSTFLOAT 	fcheckbox0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fVec0[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider2;
	int 	iTempPerm0;
	int 	iVec1[2];
	int 	iTempPerm1;
	int 	iRec2[2];
	int 	iTempPerm2;
	float 	fConst2;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider3;
	int 	iTempPerm3;
	int 	iRec0[2];
	float 	fTempPerm4;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider4;
	float 	fVec2[2];
	float 	fRec8[2];
	int 	iTempPerm5;
	int 	iVec3[2];
	int 	iTempPerm6;
	int 	iRec7[2];
	int 	iTempPerm7;
	float 	fRec9[2];
	int 	iTempPerm8;
	int 	iRec5[2];
	float 	fTempPerm9;
	FAUSTFLOAT 	fcheckbox2;
	FAUSTFLOAT 	fslider5;
	float 	fVec4[2];
	float 	fRec13[2];
	int 	iTempPerm10;
	int 	iVec5[2];
	int 	iTempPerm11;
	int 	iRec12[2];
	int 	iTempPerm12;
	float 	fRec14[2];
	int 	iTempPerm13;
	int 	iRec10[2];
	float 	fTempPerm14;
	FAUSTFLOAT 	fcheckbox3;
	FAUSTFLOAT 	fslider6;
	float 	fVec6[2];
	float 	fRec18[2];
	int 	iTempPerm15;
	int 	iVec7[2];
	int 	iTempPerm16;
	int 	iRec17[2];
	int 	iTempPerm17;
	float 	fRec19[2];
	int 	iTempPerm18;
	int 	iRec15[2];
	float 	fTempPerm19;
	FAUSTFLOAT 	fcheckbox4;
	FAUSTFLOAT 	fslider7;
	float 	fVec8[2];
	float 	fRec23[2];
	int 	iTempPerm20;
	int 	iVec9[2];
	int 	iTempPerm21;
	int 	iRec22[2];
	int 	iTempPerm22;
	float 	fRec24[2];
	int 	iTempPerm23;
	int 	iRec20[2];
	float 	fTempPerm24;
	FAUSTFLOAT 	fcheckbox5;
	FAUSTFLOAT 	fslider8;
	float 	fVec10[2];
	float 	fRec28[2];
	int 	iTempPerm25;
	int 	iVec11[2];
	int 	iTempPerm26;
	int 	iRec27[2];
	int 	iTempPerm27;
	float 	fRec29[2];
	int 	iTempPerm28;
	int 	iRec25[2];
	float 	fTempPerm29;
	FAUSTFLOAT 	fcheckbox6;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fcheckbox7;
	FAUSTFLOAT 	fcheckbox8;
	float 	fVec12[2];
	float 	fRec30[2];
	float 	fTempPerm30;
	float 	fTempPerm31;
	FAUSTFLOAT 	fcheckbox9;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fcheckbox10;
	FAUSTFLOAT 	fcheckbox11;
	float 	fVec13[2];
	float 	fRec31[2];
	float 	fTempPerm32;
	float 	fTempPerm33;
	FAUSTFLOAT 	fcheckbox12;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fcheckbox13;
	FAUSTFLOAT 	fcheckbox14;
	float 	fVec14[2];
	float 	fRec32[2];
	float 	fTempPerm34;
	float 	fTempPerm35;
	FAUSTFLOAT 	fcheckbox15;
	FAUSTFLOAT 	fslider13;
	float 	fVec15[2];
	float 	fRec33[2];
	float 	fTempPerm36;
	float 	fTempPerm37;
	FAUSTFLOAT 	fcheckbox16;
	FAUSTFLOAT 	fslider14;
	float 	fVec16[2];
	float 	fRec34[2];
	float 	fTempPerm38;
	float 	fTempPerm39;
	FAUSTFLOAT 	fcheckbox17;
	FAUSTFLOAT 	fslider15;
	float 	fVec17[2];
	float 	fRec35[2];
	float 	fTempPerm40;
	float 	fTempPerm41;
	FAUSTFLOAT 	fcheckbox18;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	float 	fVec18[2];
	float 	fRec36[2];
	float 	fTempPerm42;
	FAUSTFLOAT 	fcheckbox19;
	FAUSTFLOAT 	fslider18;
	float 	fVec19[2];
	float 	fRec37[2];
	float 	fTempPerm43;
	FAUSTFLOAT 	fcheckbox20;
	FAUSTFLOAT 	fslider19;
	float 	fVec20[2];
	float 	fRec38[2];
	float 	fTempPerm44;
	FAUSTFLOAT 	fcheckbox21;
	FAUSTFLOAT 	fslider20;
	float 	fVec21[2];
	float 	fRec39[2];
	float 	fTempPerm45;
	FAUSTFLOAT 	fcheckbox22;
	FAUSTFLOAT 	fslider21;
	float 	fVec22[2];
	float 	fRec40[2];
	float 	fTempPerm46;
	FAUSTFLOAT 	fcheckbox23;
	FAUSTFLOAT 	fslider22;
	float 	fVec23[2];
	float 	fRec41[2];
	float 	fTempPerm47;
	FAUSTFLOAT 	fcheckbox24;
	FAUSTFLOAT 	fslider23;
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fcheckbox25;
	FAUSTFLOAT 	fcheckbox26;
	FAUSTFLOAT 	fcheckbox27;
	float 	fVec24[2];
	float 	fConst5;
	float 	fRec44[2];
	FAUSTFLOAT 	fslider25;
	float 	fTempPerm48;
	float 	fConst6;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	float 	fTempPerm49;
	float 	fRec43[2];
	float 	fRec42[2];
	float 	fTempPerm50;
	FAUSTFLOAT 	fcheckbox28;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fcheckbox29;
	FAUSTFLOAT 	fcheckbox30;
	float 	fVec25[2];
	float 	fRec47[2];
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fRec46[2];
	float 	fRec45[2];
	float 	fTempPerm53;
	FAUSTFLOAT 	fcheckbox31;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fcheckbox32;
	FAUSTFLOAT 	fcheckbox33;
	float 	fVec26[2];
	float 	fRec50[2];
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fRec49[2];
	float 	fRec48[2];
	float 	fTempPerm56;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fRec52[2];
	float 	fRec51[2];
	float 	fTempPerm59;
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fRec54[2];
	float 	fRec53[2];
	float 	fTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fRec56[2];
	float 	fRec55[2];
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fRec58[2];
	float 	fRec57[2];
	float 	fTempPerm68;
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fRec60[2];
	float 	fRec59[2];
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fTempPerm73;
	float 	fRec62[2];
	float 	fRec61[2];
	float 	fTempPerm74;
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fRec64[2];
	float 	fRec63[2];
	float 	fTempPerm77;
	FAUSTFLOAT 	fcheckbox34;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fcheckbox35;
	FAUSTFLOAT 	fcheckbox36;
	FAUSTFLOAT 	fcheckbox37;
	float 	fRec67[2];
	FAUSTFLOAT 	fslider32;
	float 	fTempPerm78;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	float 	fTempPerm79;
	float 	fRec66[2];
	float 	fRec65[2];
	float 	fTempPerm80;
	FAUSTFLOAT 	fcheckbox38;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fcheckbox39;
	FAUSTFLOAT 	fcheckbox40;
	float 	fRec70[2];
	float 	fTempPerm81;
	float 	fTempPerm82;
	float 	fRec69[2];
	float 	fRec68[2];
	float 	fTempPerm83;
	FAUSTFLOAT 	fcheckbox41;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fcheckbox42;
	FAUSTFLOAT 	fcheckbox43;
	float 	fRec73[2];
	float 	fTempPerm84;
	float 	fTempPerm85;
	float 	fRec72[2];
	float 	fRec71[2];
	float 	fTempPerm86;
	float 	fTempPerm87;
	float 	fTempPerm88;
	float 	fRec75[2];
	float 	fRec74[2];
	float 	fTempPerm89;
	float 	fTempPerm90;
	float 	fTempPerm91;
	float 	fRec77[2];
	float 	fRec76[2];
	float 	fTempPerm92;
	float 	fTempPerm93;
	float 	fTempPerm94;
	float 	fRec79[2];
	float 	fRec78[2];
	float 	fTempPerm95;
	float 	fTempPerm96;
	float 	fTempPerm97;
	float 	fRec81[2];
	float 	fRec80[2];
	float 	fTempPerm98;
	float 	fTempPerm99;
	float 	fTempPerm100;
	float 	fRec83[2];
	float 	fRec82[2];
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fRec85[2];
	float 	fRec84[2];
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fRec87[2];
	float 	fRec86[2];
	float 	fTempPerm107;
	FAUSTFLOAT 	fcheckbox44;
	float 	fConst7;
	float 	fConst8;
	FAUSTFLOAT 	fslider37;
	float 	fTempPerm108;
	FAUSTFLOAT 	fcheckbox45;
	FAUSTFLOAT 	fcheckbox46;
	FAUSTFLOAT 	fcheckbox47;
	FAUSTFLOAT 	fcheckbox48;
	FAUSTFLOAT 	fcheckbox49;
	FAUSTFLOAT 	fcheckbox50;
	float 	fTempPerm109;
	FAUSTFLOAT 	fcheckbox51;
	float 	fTempPerm110;
	float 	fTempPerm111;
	FAUSTFLOAT 	fcheckbox52;
	float 	fTempPerm112;
	float 	fRec88[2];
	float 	fTempPerm113;
	FAUSTFLOAT 	fslider38;
	float 	fTempPerm114;
	float 	fTempPerm115;
	float 	fRec89[2];
	float 	fTempPerm116;
	FAUSTFLOAT 	fslider39;
	float 	fRec90[2];
	float 	fTempPerm117;
	FAUSTFLOAT 	fslider40;
	float 	fRec91[2];
	float 	fTempPerm118;
	FAUSTFLOAT 	fslider41;
	float 	fTempPerm119;
	float 	fRec92[2];
	float 	fTempPerm120;
	FAUSTFLOAT 	fslider42;
	float 	fRec93[2];
	float 	fTempPerm121;
	FAUSTFLOAT 	fcheckbox53;
	float 	fTempPerm122;
	FAUSTFLOAT 	fcheckbox54;
	FAUSTFLOAT 	fcheckbox55;
	FAUSTFLOAT 	fcheckbox56;
	FAUSTFLOAT 	fcheckbox57;
	FAUSTFLOAT 	fcheckbox58;
	float 	fTempPerm123;
	float 	fTempPerm124;
	float 	fTempPerm125;
	float 	fTempPerm126;
	float 	fRec94[2];
	float 	fTempPerm127;
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fRec95[2];
	float 	fTempPerm130;
	float 	fRec96[2];
	float 	fTempPerm131;
	float 	fRec97[2];
	float 	fTempPerm132;
	float 	fTempPerm133;
	float 	fRec98[2];
	float 	fTempPerm134;
	float 	fRec99[2];
	float 	fTempPerm135;
	FAUSTFLOAT 	fcheckbox59;
	float 	fTempPerm136;
	FAUSTFLOAT 	fcheckbox60;
	FAUSTFLOAT 	fcheckbox61;
	FAUSTFLOAT 	fcheckbox62;
	FAUSTFLOAT 	fcheckbox63;
	FAUSTFLOAT 	fcheckbox64;
	FAUSTFLOAT 	fcheckbox65;
	FAUSTFLOAT 	fcheckbox66;
	float 	fTempPerm137;
	FAUSTFLOAT 	fcheckbox67;
	FAUSTFLOAT 	fcheckbox68;
	float 	fTempPerm138;
	float 	fTempPerm139;
	FAUSTFLOAT 	fcheckbox69;
	float 	fTempPerm140;
	float 	fRec100[2];
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fTempPerm143;
	float 	fRec101[2];
	float 	fTempPerm144;
	float 	fRec102[2];
	float 	fTempPerm145;
	float 	fRec103[2];
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fRec104[2];
	float 	fTempPerm148;
	float 	fRec105[2];
	float 	fTempPerm149;
	FAUSTFLOAT 	fcheckbox70;
	float 	fTempPerm150;
	FAUSTFLOAT 	fcheckbox71;
	FAUSTFLOAT 	fcheckbox72;
	FAUSTFLOAT 	fcheckbox73;
	FAUSTFLOAT 	fcheckbox74;
	FAUSTFLOAT 	fcheckbox75;
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fRec106[2];
	float 	fTempPerm155;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fRec107[2];
	float 	fTempPerm158;
	float 	fRec108[2];
	float 	fTempPerm159;
	float 	fRec109[2];
	float 	fTempPerm160;
	float 	fTempPerm161;
	float 	fRec110[2];
	float 	fTempPerm162;
	float 	fRec111[2];
	float 	fTempPerm163;
	FAUSTFLOAT 	fcheckbox76;
	float 	fTempPerm164;
	FAUSTFLOAT 	fcheckbox77;
	FAUSTFLOAT 	fcheckbox78;
	FAUSTFLOAT 	fcheckbox79;
	FAUSTFLOAT 	fcheckbox80;
	FAUSTFLOAT 	fcheckbox81;
	FAUSTFLOAT 	fcheckbox82;
	float 	fTempPerm165;
	FAUSTFLOAT 	fcheckbox83;
	float 	fTempPerm166;
	float 	fTempPerm167;
	FAUSTFLOAT 	fcheckbox84;
	float 	fTempPerm168;
	float 	fRec112[2];
	float 	fTempPerm169;
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fRec113[2];
	float 	fTempPerm172;
	float 	fRec114[2];
	float 	fTempPerm173;
	float 	fRec115[2];
	float 	fTempPerm174;
	float 	fTempPerm175;
	float 	fRec116[2];
	float 	fTempPerm176;
	float 	fRec117[2];
	float 	fTempPerm177;
	FAUSTFLOAT 	fcheckbox85;
	float 	fTempPerm178;
	FAUSTFLOAT 	fcheckbox86;
	FAUSTFLOAT 	fcheckbox87;
	FAUSTFLOAT 	fcheckbox88;
	FAUSTFLOAT 	fcheckbox89;
	FAUSTFLOAT 	fcheckbox90;
	float 	fTempPerm179;
	float 	fTempPerm180;
	float 	fTempPerm181;
	float 	fTempPerm182;
	float 	fRec118[2];
	float 	fTempPerm183;
	float 	fTempPerm184;
	float 	fTempPerm185;
	float 	fRec119[2];
	float 	fTempPerm186;
	float 	fRec120[2];
	float 	fTempPerm187;
	float 	fRec121[2];
	float 	fTempPerm188;
	float 	fTempPerm189;
	float 	fRec122[2];
	float 	fTempPerm190;
	float 	fRec123[2];
	float 	fTempPerm191;
	float 	fTempPerm192;
	float 	fTempPerm193;
	float 	fTempPerm194;
	float 	fTempPerm195;
	float 	fTempPerm196;
	float 	fTempPerm197;
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fTempPerm200;
	float 	fTempPerm201;
	float 	fTempPerm202;
	float 	fTempPerm203;
	float 	fTempPerm204;
	float 	fTempPerm205;
	float 	fTempPerm206;
	float 	fTempPerm207;
	float 	fTempPerm208;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "motion_v7b.lib");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Faust Motion Library [Motion+RotationMatrix]");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.7");
	}

	virtual int getNumInputs() { return 18; }
	virtual int getNumOutputs() { return 91; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		iTempPerm0 = 0;
		iTempPerm1 = 0;
		iTempPerm2 = 0;
		fConst2 = (1.0f / fConst0);
		iTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
		iTempPerm6 = 0;
		iTempPerm7 = 0;
		iTempPerm8 = 0;
		fTempPerm9 = 0;
		iTempPerm10 = 0;
		iTempPerm11 = 0;
		iTempPerm12 = 0;
		iTempPerm13 = 0;
		fTempPerm14 = 0;
		iTempPerm15 = 0;
		iTempPerm16 = 0;
		iTempPerm17 = 0;
		iTempPerm18 = 0;
		fTempPerm19 = 0;
		iTempPerm20 = 0;
		iTempPerm21 = 0;
		iTempPerm22 = 0;
		iTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		iTempPerm26 = 0;
		iTempPerm27 = 0;
		iTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fConst3 = (37.699111843077517f / fConst0);
		fConst4 = (1.0f / (fConst3 + 1.0f));
		fConst5 = (1.0f - fConst3);
		fTempPerm48 = 0;
		fConst6 = (1000.0f / fConst0);
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		fTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		fTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		fTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		fTempPerm106 = 0;
		fTempPerm107 = 0;
		fConst7 = expf((0 - (100.0f / fConst0)));
		fConst8 = (1.0f - fConst7);
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		fTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
		fTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		fTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
		fTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		fTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		fTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		fTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		fTempPerm167 = 0;
		fTempPerm168 = 0;
		fTempPerm169 = 0;
		fTempPerm170 = 0;
		fTempPerm171 = 0;
		fTempPerm172 = 0;
		fTempPerm173 = 0;
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		fTempPerm178 = 0;
		fTempPerm179 = 0;
		fTempPerm180 = 0;
		fTempPerm181 = 0;
		fTempPerm182 = 0;
		fTempPerm183 = 0;
		fTempPerm184 = 0;
		fTempPerm185 = 0;
		fTempPerm186 = 0;
		fTempPerm187 = 0;
		fTempPerm188 = 0;
		fTempPerm189 = 0;
		fTempPerm190 = 0;
		fTempPerm191 = 0;
		fTempPerm192 = 0;
		fTempPerm193 = 0;
		fTempPerm194 = 0;
		fTempPerm195 = 0;
		fTempPerm196 = 0;
		fTempPerm197 = 0;
		fTempPerm198 = 0;
		fTempPerm199 = 0;
		fTempPerm200 = 0;
		fTempPerm201 = 0;
		fTempPerm202 = 0;
		fTempPerm203 = 0;
		fTempPerm204 = 0;
		fTempPerm205 = 0;
		fTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
	}
	virtual void instanceResetUserInterface() {
		fcheckbox0 = 0.0;
		fslider0 = 50.0f;
		fslider1 = 0.0f;
		fslider2 = 0.75f;
		fslider3 = 75.0f;
		fcheckbox1 = 0.0;
		fslider4 = 0.0f;
		fcheckbox2 = 0.0;
		fslider5 = 0.0f;
		fcheckbox3 = 0.0;
		fslider6 = 0.0f;
		fcheckbox4 = 0.0;
		fslider7 = 0.0f;
		fcheckbox5 = 0.0;
		fslider8 = 0.0f;
		fcheckbox6 = 0.0;
		fslider9 = 1.5f;
		fslider10 = 0.0f;
		fcheckbox7 = 0.0;
		fcheckbox8 = 0.0;
		fcheckbox9 = 0.0;
		fslider11 = 0.0f;
		fcheckbox10 = 0.0;
		fcheckbox11 = 0.0;
		fcheckbox12 = 0.0;
		fslider12 = 0.0f;
		fcheckbox13 = 0.0;
		fcheckbox14 = 0.0;
		fcheckbox15 = 0.0;
		fslider13 = 0.0f;
		fcheckbox16 = 0.0;
		fslider14 = 0.0f;
		fcheckbox17 = 0.0;
		fslider15 = 0.0f;
		fcheckbox18 = 0.0;
		fslider16 = 0.080000000000000002f;
		fslider17 = 0.0f;
		fcheckbox19 = 0.0;
		fslider18 = 0.0f;
		fcheckbox20 = 0.0;
		fslider19 = 0.0f;
		fcheckbox21 = 0.0;
		fslider20 = 0.0f;
		fcheckbox22 = 0.0;
		fslider21 = 0.0f;
		fcheckbox23 = 0.0;
		fslider22 = 0.0f;
		fcheckbox24 = 0.0;
		fslider23 = 1.3500000000000001f;
		fslider24 = 0.0f;
		fcheckbox25 = 0.0;
		fcheckbox26 = 0.0;
		fcheckbox27 = 0.0;
		fslider25 = 0.10000000000000001f;
		fslider26 = 10.0f;
		fslider27 = 10.0f;
		fcheckbox28 = 0.0;
		fslider28 = 0.0f;
		fcheckbox29 = 0.0;
		fcheckbox30 = 0.0;
		fcheckbox31 = 0.0;
		fslider29 = 0.0f;
		fcheckbox32 = 0.0;
		fcheckbox33 = 0.0;
		fcheckbox34 = 0.0;
		fslider30 = 0.79000000000000004f;
		fslider31 = 0.0f;
		fcheckbox35 = 0.0;
		fcheckbox36 = 0.0;
		fcheckbox37 = 0.0;
		fslider32 = 0.01f;
		fslider33 = 250.0f;
		fslider34 = 0.0f;
		fcheckbox38 = 0.0;
		fslider35 = 0.0f;
		fcheckbox39 = 0.0;
		fcheckbox40 = 0.0;
		fcheckbox41 = 0.0;
		fslider36 = 0.0f;
		fcheckbox42 = 0.0;
		fcheckbox43 = 0.0;
		fcheckbox44 = 0.0;
		fslider37 = 1.0f;
		fcheckbox45 = 0.0;
		fcheckbox46 = 0.0;
		fcheckbox47 = 0.0;
		fcheckbox48 = 0.0;
		fcheckbox49 = 0.0;
		fcheckbox50 = 0.0;
		fcheckbox51 = 0.0;
		fcheckbox52 = 0.0;
		fslider38 = 1.0f;
		fslider39 = 1.0f;
		fslider40 = 1.0f;
		fslider41 = 1.0f;
		fslider42 = 1.0f;
		fcheckbox53 = 0.0;
		fcheckbox54 = 0.0;
		fcheckbox55 = 0.0;
		fcheckbox56 = 0.0;
		fcheckbox57 = 0.0;
		fcheckbox58 = 0.0;
		fcheckbox59 = 0.0;
		fcheckbox60 = 0.0;
		fcheckbox61 = 0.0;
		fcheckbox62 = 0.0;
		fcheckbox63 = 0.0;
		fcheckbox64 = 0.0;
		fcheckbox65 = 0.0;
		fcheckbox66 = 0.0;
		fcheckbox67 = 0.0;
		fcheckbox68 = 0.0;
		fcheckbox69 = 0.0;
		fcheckbox70 = 0.0;
		fcheckbox71 = 0.0;
		fcheckbox72 = 0.0;
		fcheckbox73 = 0.0;
		fcheckbox74 = 0.0;
		fcheckbox75 = 0.0;
		fcheckbox76 = 0.0;
		fcheckbox77 = 0.0;
		fcheckbox78 = 0.0;
		fcheckbox79 = 0.0;
		fcheckbox80 = 0.0;
		fcheckbox81 = 0.0;
		fcheckbox82 = 0.0;
		fcheckbox83 = 0.0;
		fcheckbox84 = 0.0;
		fcheckbox85 = 0.0;
		fcheckbox86 = 0.0;
		fcheckbox87 = 0.0;
		fcheckbox88 = 0.0;
		fcheckbox89 = 0.0;
		fcheckbox90 = 0.0;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) iVec1[i] = 0;
		for (int i=0; i<2; i++) iRec2[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) iRec0[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) iVec3[i] = 0;
		for (int i=0; i<2; i++) iRec7[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) iRec5[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) iVec5[i] = 0;
		for (int i=0; i<2; i++) iRec12[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) iRec10[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) iVec7[i] = 0;
		for (int i=0; i<2; i++) iRec17[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) iRec15[i] = 0;
		for (int i=0; i<2; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) iVec9[i] = 0;
		for (int i=0; i<2; i++) iRec22[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) iRec20[i] = 0;
		for (int i=0; i<2; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) iVec11[i] = 0;
		for (int i=0; i<2; i++) iRec27[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) iRec25[i] = 0;
		for (int i=0; i<2; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fVec23[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fVec24[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fVec25[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fVec26[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec60[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec68[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec75[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec78[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual mydsp2* clone() {
		return new mydsp2();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Motion");
		ui_interface->declare(&fcheckbox0, "00", "");
		ui_interface->declare(&fcheckbox0, "motionName", "sxp");
		ui_interface->addCheckButton("sxpOn", &fcheckbox0);
		ui_interface->declare(&fcheckbox1, "01", "");
		ui_interface->declare(&fcheckbox1, "motionName", "syp");
		ui_interface->addCheckButton("sypOn", &fcheckbox1);
		ui_interface->declare(&fcheckbox2, "02", "");
		ui_interface->declare(&fcheckbox2, "motionName", "szp");
		ui_interface->addCheckButton("szpOn", &fcheckbox2);
		ui_interface->declare(&fcheckbox3, "03", "");
		ui_interface->declare(&fcheckbox3, "motionName", "sxn");
		ui_interface->addCheckButton("sxnOn", &fcheckbox3);
		ui_interface->declare(&fcheckbox4, "04", "");
		ui_interface->declare(&fcheckbox4, "motionName", "syn");
		ui_interface->addCheckButton("synOn", &fcheckbox4);
		ui_interface->declare(&fcheckbox5, "05", "");
		ui_interface->declare(&fcheckbox5, "motionName", "szn");
		ui_interface->addCheckButton("sznOn", &fcheckbox5);
		ui_interface->declare(&fcheckbox6, "06", "");
		ui_interface->declare(&fcheckbox6, "motionName", "ixp");
		ui_interface->addCheckButton("ixpOn", &fcheckbox6);
		ui_interface->declare(&fcheckbox9, "07", "");
		ui_interface->declare(&fcheckbox9, "motionName", "iyp");
		ui_interface->addCheckButton("iypOn", &fcheckbox9);
		ui_interface->declare(&fcheckbox12, "08", "");
		ui_interface->declare(&fcheckbox12, "motionName", "izp");
		ui_interface->addCheckButton("izpOn", &fcheckbox12);
		ui_interface->declare(&fcheckbox15, "09", "");
		ui_interface->declare(&fcheckbox15, "motionName", "ixn");
		ui_interface->addCheckButton("ixnOn", &fcheckbox15);
		ui_interface->declare(&fslider0, "101", "");
		ui_interface->declare(&fslider0, "showName", "highPass");
		ui_interface->addHorizontalSlider("hp_Param", &fslider0, 50.0f, 1.0f, 50.0f, 0.01f);
		ui_interface->declare(&fslider2, "102", "");
		ui_interface->declare(&fslider2, "showName", "shockThred");
		ui_interface->addHorizontalSlider("shock_thr_Param", &fslider2, 0.75f, 0.10000000000000001f, 3.0f, 0.01f);
		ui_interface->declare(&fslider3, "103", "");
		ui_interface->declare(&fslider3, "showName", "antirebond");
		ui_interface->declare(&fslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("antirebon_Param", &fslider3, 75.0f, 0.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider9, "104", "");
		ui_interface->declare(&fslider9, "showName", "lowPass");
		ui_interface->addHorizontalSlider("lp_Param", &fslider9, 1.5f, 0.10000000000000001f, 20.0f, 0.01f);
		ui_interface->declare(&fslider16, "105", "");
		ui_interface->declare(&fslider16, "showName", "osfproj");
		ui_interface->addHorizontalSlider("osfproj_Param", &fslider16, 0.080000000000000002f, 0.0f, 0.33000000000000002f, 0.01f);
		ui_interface->declare(&fslider25, "106", "");
		ui_interface->declare(&fslider25, "showName", "accThred");
		ui_interface->addHorizontalSlider("tacc_thr_Param", &fslider25, 0.10000000000000001f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider23, "107", "");
		ui_interface->declare(&fslider23, "showName", "accGain");
		ui_interface->addHorizontalSlider("tacc_gain_Param", &fslider23, 1.3500000000000001f, 0.0f, 5.0f, 0.01f);
		ui_interface->declare(&fslider27, "108", "");
		ui_interface->declare(&fslider27, "showName", "accEvUp");
		ui_interface->addHorizontalSlider("tacc_up_Param", &fslider27, 10.0f, 0.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider26, "109", "");
		ui_interface->declare(&fslider26, "showName", "accEvDown");
		ui_interface->addHorizontalSlider("tacc_down_Param", &fslider26, 10.0f, 0.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fcheckbox16, "10", "");
		ui_interface->declare(&fcheckbox16, "motionName", "iyn");
		ui_interface->addCheckButton("iynOn", &fcheckbox16);
		ui_interface->declare(&fslider32, "110", "");
		ui_interface->declare(&fslider32, "showName", "gyoThred");
		ui_interface->addHorizontalSlider("tgyr_thr_Param", &fslider32, 0.01f, 0.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider30, "111", "");
		ui_interface->declare(&fslider30, "showName", "gyoGain");
		ui_interface->addHorizontalSlider("tgyr_gain_Param", &fslider30, 0.79000000000000004f, 0.0f, 5.0f, 0.01f);
		ui_interface->declare(&fslider34, "112", "");
		ui_interface->declare(&fslider34, "showName", "gyoEvUp");
		ui_interface->addHorizontalSlider("tgyr_up_Param", &fslider34, 0.0f, 0.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider33, "113", "");
		ui_interface->declare(&fslider33, "showName", "gyoEvDown");
		ui_interface->addHorizontalSlider("tgyr_down_Param", &fslider33, 250.0f, 0.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider37, "114", "");
		ui_interface->declare(&fslider37, "showName", "shapeCour");
		ui_interface->addHorizontalSlider("shapeCour_Param", &fslider37, 1.0f, 0.0f, 100.0f, 0.01f);
		ui_interface->declare(&fslider38, "115", "");
		ui_interface->declare(&fslider38, "showName", "shapeRear");
		ui_interface->addHorizontalSlider("shapeRear_Param", &fslider38, 1.0f, 0.0f, 100.0f, 0.01f);
		ui_interface->declare(&fslider39, "116", "");
		ui_interface->declare(&fslider39, "showName", "shapeJardin");
		ui_interface->addHorizontalSlider("shapeJardin_Param", &fslider39, 1.0f, 0.0f, 100.0f, 0.01f);
		ui_interface->declare(&fslider40, "117", "");
		ui_interface->declare(&fslider40, "showName", "shapeFront");
		ui_interface->addHorizontalSlider("shapeFront_Param", &fslider40, 1.0f, 0.0f, 100.0f, 0.01f);
		ui_interface->declare(&fslider41, "118", "");
		ui_interface->declare(&fslider41, "showName", "shapeDown");
		ui_interface->addHorizontalSlider("shapeDown_Param", &fslider41, 1.0f, 0.0f, 100.0f, 0.01f);
		ui_interface->declare(&fslider42, "119", "");
		ui_interface->declare(&fslider42, "showName", "shapeUp");
		ui_interface->addHorizontalSlider("shapeUp_Param", &fslider42, 1.0f, 0.0f, 100.0f, 0.01f);
		ui_interface->declare(&fcheckbox17, "11", "");
		ui_interface->declare(&fcheckbox17, "motionName", "izn");
		ui_interface->addCheckButton("iznOn", &fcheckbox17);
		ui_interface->declare(&fcheckbox18, "12", "");
		ui_interface->declare(&fcheckbox18, "motionName", "pixp");
		ui_interface->addCheckButton("pixpOn", &fcheckbox18);
		ui_interface->declare(&fcheckbox19, "13", "");
		ui_interface->declare(&fcheckbox19, "motionName", "piyp");
		ui_interface->addCheckButton("piypOn", &fcheckbox19);
		ui_interface->declare(&fcheckbox20, "14", "");
		ui_interface->declare(&fcheckbox20, "motionName", "pizp");
		ui_interface->addCheckButton("pizpOn", &fcheckbox20);
		ui_interface->declare(&fcheckbox21, "15", "");
		ui_interface->declare(&fcheckbox21, "motionName", "pixn");
		ui_interface->addCheckButton("pixnOn", &fcheckbox21);
		ui_interface->declare(&fcheckbox22, "16", "");
		ui_interface->declare(&fcheckbox22, "motionName", "piyn");
		ui_interface->addCheckButton("piynOn", &fcheckbox22);
		ui_interface->declare(&fcheckbox23, "17", "");
		ui_interface->declare(&fcheckbox23, "motionName", "pizn");
		ui_interface->addCheckButton("piznOn", &fcheckbox23);
		ui_interface->declare(&fcheckbox24, "18", "");
		ui_interface->declare(&fcheckbox24, "motionName", "axpn");
		ui_interface->addCheckButton("axpnOn", &fcheckbox24);
		ui_interface->declare(&fcheckbox28, "19", "");
		ui_interface->declare(&fcheckbox28, "motionName", "aypn");
		ui_interface->addCheckButton("aypnOn", &fcheckbox28);
		ui_interface->declare(&fcheckbox31, "20", "");
		ui_interface->declare(&fcheckbox31, "motionName", "azpn");
		ui_interface->addCheckButton("azpnOn", &fcheckbox31);
		ui_interface->declare(&fcheckbox25, "21", "");
		ui_interface->declare(&fcheckbox25, "motionName", "axp");
		ui_interface->addCheckButton("axpOn", &fcheckbox25);
		ui_interface->declare(&fcheckbox29, "22", "");
		ui_interface->declare(&fcheckbox29, "motionName", "ayp");
		ui_interface->addCheckButton("aypOn", &fcheckbox29);
		ui_interface->declare(&fcheckbox32, "23", "");
		ui_interface->declare(&fcheckbox32, "motionName", "azp");
		ui_interface->addCheckButton("azpOn", &fcheckbox32);
		ui_interface->declare(&fcheckbox26, "24", "");
		ui_interface->declare(&fcheckbox26, "motionName", "axn");
		ui_interface->addCheckButton("axnOn", &fcheckbox26);
		ui_interface->declare(&fcheckbox30, "25", "");
		ui_interface->declare(&fcheckbox30, "motionName", "ayn");
		ui_interface->addCheckButton("aynOn", &fcheckbox30);
		ui_interface->declare(&fcheckbox33, "26", "");
		ui_interface->declare(&fcheckbox33, "motionName", "azn");
		ui_interface->addCheckButton("aznOn", &fcheckbox33);
		ui_interface->declare(&fcheckbox27, "27", "");
		ui_interface->declare(&fcheckbox27, "motionName", "totalaccel");
		ui_interface->addCheckButton("totalaccelOn", &fcheckbox27);
		ui_interface->declare(&fcheckbox34, "28", "");
		ui_interface->declare(&fcheckbox34, "motionName", "gxpn");
		ui_interface->addCheckButton("gxpnOn", &fcheckbox34);
		ui_interface->declare(&fcheckbox38, "29", "");
		ui_interface->declare(&fcheckbox38, "motionName", "gypn");
		ui_interface->addCheckButton("gypnOn", &fcheckbox38);
		ui_interface->declare(&fcheckbox41, "30", "");
		ui_interface->declare(&fcheckbox41, "motionName", "gzpn");
		ui_interface->addCheckButton("gzpnOn", &fcheckbox41);
		ui_interface->declare(&fcheckbox35, "31", "");
		ui_interface->declare(&fcheckbox35, "motionName", "gxp");
		ui_interface->addCheckButton("gxpOn", &fcheckbox35);
		ui_interface->declare(&fcheckbox39, "32", "");
		ui_interface->declare(&fcheckbox39, "motionName", "gyp");
		ui_interface->addCheckButton("gypOn", &fcheckbox39);
		ui_interface->declare(&fcheckbox42, "33", "");
		ui_interface->declare(&fcheckbox42, "motionName", "gzp");
		ui_interface->addCheckButton("gzpOn", &fcheckbox42);
		ui_interface->declare(&fcheckbox36, "34", "");
		ui_interface->declare(&fcheckbox36, "motionName", "gxn");
		ui_interface->addCheckButton("gxnOn", &fcheckbox36);
		ui_interface->declare(&fcheckbox40, "35", "");
		ui_interface->declare(&fcheckbox40, "motionName", "gyn");
		ui_interface->addCheckButton("gynOn", &fcheckbox40);
		ui_interface->declare(&fcheckbox43, "36", "");
		ui_interface->declare(&fcheckbox43, "motionName", "gzn");
		ui_interface->addCheckButton("gznOn", &fcheckbox43);
		ui_interface->declare(&fcheckbox37, "37", "");
		ui_interface->declare(&fcheckbox37, "motionName", "totalgyro");
		ui_interface->addCheckButton("totalgyroOn", &fcheckbox37);
		ui_interface->declare(&fcheckbox44, "38", "");
		ui_interface->declare(&fcheckbox44, "motionName", "brasG_cour");
		ui_interface->addCheckButton("brasG_courOn", &fcheckbox44);
		ui_interface->declare(&fcheckbox45, "39", "");
		ui_interface->declare(&fcheckbox45, "motionName", "brasG_rear");
		ui_interface->addCheckButton("brasG_rearOn", &fcheckbox45);
		ui_interface->declare(&fcheckbox46, "40", "");
		ui_interface->declare(&fcheckbox46, "motionName", "brasG_jardin");
		ui_interface->addCheckButton("brasG_jardinOn", &fcheckbox46);
		ui_interface->declare(&fcheckbox47, "41", "");
		ui_interface->declare(&fcheckbox47, "motionName", "brasG_front");
		ui_interface->addCheckButton("brasG_frontOn", &fcheckbox47);
		ui_interface->declare(&fcheckbox48, "42", "");
		ui_interface->declare(&fcheckbox48, "motionName", "brasG_down");
		ui_interface->addCheckButton("brasG_downOn", &fcheckbox48);
		ui_interface->declare(&fcheckbox49, "43", "");
		ui_interface->declare(&fcheckbox49, "motionName", "brasG_up");
		ui_interface->addCheckButton("brasG_upOn", &fcheckbox49);
		ui_interface->declare(&fcheckbox53, "44", "");
		ui_interface->declare(&fcheckbox53, "motionName", "pieds_cour");
		ui_interface->addCheckButton("pieds_courOn", &fcheckbox53);
		ui_interface->declare(&fcheckbox54, "45", "");
		ui_interface->declare(&fcheckbox54, "motionName", "pieds_rear");
		ui_interface->addCheckButton("pieds_rearOn", &fcheckbox54);
		ui_interface->declare(&fcheckbox55, "46", "");
		ui_interface->declare(&fcheckbox55, "motionName", "pieds_jardin");
		ui_interface->addCheckButton("pieds_jardinOn", &fcheckbox55);
		ui_interface->declare(&fcheckbox56, "47", "");
		ui_interface->declare(&fcheckbox56, "motionName", "pieds_front");
		ui_interface->addCheckButton("pieds_frontOn", &fcheckbox56);
		ui_interface->declare(&fcheckbox57, "48", "");
		ui_interface->declare(&fcheckbox57, "motionName", "pieds_down");
		ui_interface->addCheckButton("pieds_downOn", &fcheckbox57);
		ui_interface->declare(&fcheckbox58, "49", "");
		ui_interface->declare(&fcheckbox58, "motionName", "pieds_up");
		ui_interface->addCheckButton("pieds_upOn", &fcheckbox58);
		ui_interface->declare(&fcheckbox59, "50", "");
		ui_interface->declare(&fcheckbox59, "motionName", "dos_cour");
		ui_interface->addCheckButton("dos_courOn", &fcheckbox59);
		ui_interface->declare(&fcheckbox60, "51", "");
		ui_interface->declare(&fcheckbox60, "motionName", "dos_rear");
		ui_interface->addCheckButton("dos_rearOn", &fcheckbox60);
		ui_interface->declare(&fcheckbox61, "52", "");
		ui_interface->declare(&fcheckbox61, "motionName", "dos_jardin");
		ui_interface->addCheckButton("dos_jardinOn", &fcheckbox61);
		ui_interface->declare(&fcheckbox62, "53", "");
		ui_interface->declare(&fcheckbox62, "motionName", "dos_front");
		ui_interface->addCheckButton("dos_frontOn", &fcheckbox62);
		ui_interface->declare(&fcheckbox63, "54", "");
		ui_interface->declare(&fcheckbox63, "motionName", "dos_down");
		ui_interface->addCheckButton("dos_downOn", &fcheckbox63);
		ui_interface->declare(&fcheckbox64, "55", "");
		ui_interface->declare(&fcheckbox64, "motionName", "dos_up");
		ui_interface->addCheckButton("dos_upOn", &fcheckbox64);
		ui_interface->declare(&fcheckbox70, "56", "");
		ui_interface->declare(&fcheckbox70, "motionName", "brasD_cour");
		ui_interface->addCheckButton("brasD_courOn", &fcheckbox70);
		ui_interface->declare(&fcheckbox71, "57", "");
		ui_interface->declare(&fcheckbox71, "motionName", "brasD_rear");
		ui_interface->addCheckButton("brasD_rearOn", &fcheckbox71);
		ui_interface->declare(&fcheckbox72, "58", "");
		ui_interface->declare(&fcheckbox72, "motionName", "brasD_jardin");
		ui_interface->addCheckButton("brasD_jardinOn", &fcheckbox72);
		ui_interface->declare(&fcheckbox73, "59", "");
		ui_interface->declare(&fcheckbox73, "motionName", "brasD_front");
		ui_interface->addCheckButton("brasD_frontOn", &fcheckbox73);
		ui_interface->declare(&fcheckbox74, "60", "");
		ui_interface->declare(&fcheckbox74, "motionName", "brasD_down");
		ui_interface->addCheckButton("brasD_downOn", &fcheckbox74);
		ui_interface->declare(&fcheckbox75, "61", "");
		ui_interface->declare(&fcheckbox75, "motionName", "brasD_up");
		ui_interface->addCheckButton("brasD_upOn", &fcheckbox75);
		ui_interface->declare(&fcheckbox76, "62", "");
		ui_interface->declare(&fcheckbox76, "motionName", "tete_cour");
		ui_interface->addCheckButton("tete_courOn", &fcheckbox76);
		ui_interface->declare(&fcheckbox77, "63", "");
		ui_interface->declare(&fcheckbox77, "motionName", "tete_rear");
		ui_interface->addCheckButton("tete_rearOn", &fcheckbox77);
		ui_interface->declare(&fcheckbox78, "64", "");
		ui_interface->declare(&fcheckbox78, "motionName", "tete_jardin");
		ui_interface->addCheckButton("tete_jardinOn", &fcheckbox78);
		ui_interface->declare(&fcheckbox79, "65", "");
		ui_interface->declare(&fcheckbox79, "motionName", "tete_front");
		ui_interface->addCheckButton("tete_frontOn", &fcheckbox79);
		ui_interface->declare(&fcheckbox80, "66", "");
		ui_interface->declare(&fcheckbox80, "motionName", "tete_down");
		ui_interface->addCheckButton("tete_downOn", &fcheckbox80);
		ui_interface->declare(&fcheckbox81, "67", "");
		ui_interface->declare(&fcheckbox81, "motionName", "tete_up");
		ui_interface->addCheckButton("tete_upOn", &fcheckbox81);
		ui_interface->declare(&fcheckbox85, "68", "");
		ui_interface->declare(&fcheckbox85, "motionName", "ventre_cour");
		ui_interface->addCheckButton("ventre_courOn", &fcheckbox85);
		ui_interface->declare(&fcheckbox86, "69", "");
		ui_interface->declare(&fcheckbox86, "motionName", "ventre_rear");
		ui_interface->addCheckButton("ventre_rearOn", &fcheckbox86);
		ui_interface->declare(&fcheckbox87, "70", "");
		ui_interface->declare(&fcheckbox87, "motionName", "ventre_jardin");
		ui_interface->addCheckButton("ventre_jardinOn", &fcheckbox87);
		ui_interface->declare(&fcheckbox88, "71", "");
		ui_interface->declare(&fcheckbox88, "motionName", "ventre_front");
		ui_interface->addCheckButton("ventre_frontOn", &fcheckbox88);
		ui_interface->declare(&fcheckbox89, "72", "");
		ui_interface->declare(&fcheckbox89, "motionName", "ventre_down");
		ui_interface->addCheckButton("ventre_downOn", &fcheckbox89);
		ui_interface->declare(&fcheckbox90, "73", "");
		ui_interface->declare(&fcheckbox90, "motionName", "ventre_up");
		ui_interface->addCheckButton("ventre_upOn", &fcheckbox90);
		ui_interface->declare(&fcheckbox7, "74", "");
		ui_interface->declare(&fcheckbox7, "motionName", "ixpn");
		ui_interface->addCheckButton("ixpnOn", &fcheckbox7);
		ui_interface->declare(&fcheckbox10, "75", "");
		ui_interface->declare(&fcheckbox10, "motionName", "iypn");
		ui_interface->addCheckButton("iypnOn", &fcheckbox10);
		ui_interface->declare(&fcheckbox13, "76", "");
		ui_interface->declare(&fcheckbox13, "motionName", "izpn");
		ui_interface->addCheckButton("izpnOn", &fcheckbox13);
		ui_interface->declare(&fcheckbox8, "77", "");
		ui_interface->declare(&fcheckbox8, "motionName", "ixpn_sym");
		ui_interface->addCheckButton("ixpn_symOn", &fcheckbox8);
		ui_interface->declare(&fcheckbox11, "78", "");
		ui_interface->declare(&fcheckbox11, "motionName", "iypn_sym");
		ui_interface->addCheckButton("iypn_symOn", &fcheckbox11);
		ui_interface->declare(&fcheckbox14, "79", "");
		ui_interface->declare(&fcheckbox14, "motionName", "izpn_sym");
		ui_interface->addCheckButton("izpn_symOn", &fcheckbox14);
		ui_interface->declare(&fcheckbox65, "80", "");
		ui_interface->declare(&fcheckbox65, "motionName", "dosx");
		ui_interface->addCheckButton("dosxOn", &fcheckbox65);
		ui_interface->declare(&fcheckbox67, "81", "");
		ui_interface->declare(&fcheckbox67, "motionName", "dosy");
		ui_interface->addCheckButton("dosyOn", &fcheckbox67);
		ui_interface->declare(&fcheckbox66, "82", "");
		ui_interface->declare(&fcheckbox66, "motionName", "coox");
		ui_interface->addCheckButton("cooxOn", &fcheckbox66);
		ui_interface->declare(&fcheckbox68, "83", "");
		ui_interface->declare(&fcheckbox68, "motionName", "cooy");
		ui_interface->addCheckButton("cooyOn", &fcheckbox68);
		ui_interface->declare(&fcheckbox69, "84", "");
		ui_interface->declare(&fcheckbox69, "motionName", "cooz");
		ui_interface->addCheckButton("coozOn", &fcheckbox69);
		ui_interface->declare(&fcheckbox82, "85", "");
		ui_interface->declare(&fcheckbox82, "motionName", "cooxT");
		ui_interface->addCheckButton("cooxTOn", &fcheckbox82);
		ui_interface->declare(&fcheckbox83, "86", "");
		ui_interface->declare(&fcheckbox83, "motionName", "cooyT");
		ui_interface->addCheckButton("cooyTOn", &fcheckbox83);
		ui_interface->declare(&fcheckbox84, "87", "");
		ui_interface->declare(&fcheckbox84, "motionName", "coozT");
		ui_interface->addCheckButton("coozTOn", &fcheckbox84);
		ui_interface->declare(&fcheckbox50, "88", "");
		ui_interface->declare(&fcheckbox50, "motionName", "cooxBG");
		ui_interface->addCheckButton("cooxBGOn", &fcheckbox50);
		ui_interface->declare(&fcheckbox51, "89", "");
		ui_interface->declare(&fcheckbox51, "motionName", "cooyBG");
		ui_interface->addCheckButton("cooyBGOn", &fcheckbox51);
		ui_interface->declare(&fcheckbox52, "90", "");
		ui_interface->declare(&fcheckbox52, "motionName", "coozBG");
		ui_interface->addCheckButton("coozBGOn", &fcheckbox52);
		ui_interface->declare(&fslider24, "acc", "0 0 -30 0 30");
		ui_interface->declare(&fslider24, "hidden", "1");
		ui_interface->addHorizontalSlider("acc_x", &fslider24, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider28, "acc", "1 0 -30 0 30");
		ui_interface->declare(&fslider28, "hidden", "1");
		ui_interface->addHorizontalSlider("acc_y", &fslider28, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider29, "acc", "2 0 -30 0 30");
		ui_interface->declare(&fslider29, "hidden", "1");
		ui_interface->addHorizontalSlider("acc_z", &fslider29, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider31, "gyr", "0 0 -35 0 35");
		ui_interface->declare(&fslider31, "hidden", "1");
		ui_interface->addHorizontalSlider("gx", &fslider31, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider35, "gyr", "1 0 -35 0 35");
		ui_interface->declare(&fslider35, "hidden", "1");
		ui_interface->addHorizontalSlider("gy", &fslider35, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider36, "gyr", "2 0 -35 0 35");
		ui_interface->declare(&fslider36, "hidden", "1");
		ui_interface->addHorizontalSlider("gz", &fslider36, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider13, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fslider13, "hidden", "1");
		ui_interface->addHorizontalSlider("ixn", &fslider13, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider10, "acc", "0 0 -10 0 10");
		ui_interface->declare(&fslider10, "hidden", "1");
		ui_interface->addHorizontalSlider("ixp", &fslider10, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider14, "acc", "1 1 -10 0 10");
		ui_interface->declare(&fslider14, "hidden", "1");
		ui_interface->addHorizontalSlider("iyn", &fslider14, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider11, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fslider11, "hidden", "1");
		ui_interface->addHorizontalSlider("iyp", &fslider11, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider15, "acc", "2 1 -10 0 10");
		ui_interface->declare(&fslider15, "hidden", "1");
		ui_interface->addHorizontalSlider("izn", &fslider15, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider12, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fslider12, "hidden", "1");
		ui_interface->addHorizontalSlider("izp", &fslider12, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider20, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fslider20, "hidden", "1");
		ui_interface->addHorizontalSlider("pixn", &fslider20, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider17, "acc", "0 0 -10 0 10");
		ui_interface->declare(&fslider17, "hidden", "1");
		ui_interface->addHorizontalSlider("pixp", &fslider17, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider21, "acc", "1 1 -10 0 10");
		ui_interface->declare(&fslider21, "hidden", "1");
		ui_interface->addHorizontalSlider("piyn", &fslider21, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider18, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fslider18, "hidden", "1");
		ui_interface->addHorizontalSlider("piyp", &fslider18, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider22, "acc", "2 1 -10 0 10");
		ui_interface->declare(&fslider22, "hidden", "1");
		ui_interface->addHorizontalSlider("pizn", &fslider22, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider19, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fslider19, "hidden", "1");
		ui_interface->addHorizontalSlider("pizp", &fslider19, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->declare(&fslider6, "acc", "0 1 -30 0 30");
		ui_interface->declare(&fslider6, "hidden", "1");
		ui_interface->addHorizontalSlider("sxn", &fslider6, 0.0f, -3.0f, 3.0f, 0.0001f);
		ui_interface->declare(&fslider1, "acc", "0 0 -30 0 30");
		ui_interface->declare(&fslider1, "hidden", "1");
		ui_interface->addHorizontalSlider("sxp", &fslider1, 0.0f, -3.0f, 3.0f, 0.0001f);
		ui_interface->declare(&fslider7, "acc", "1 1 -30 0 30");
		ui_interface->declare(&fslider7, "hidden", "1");
		ui_interface->addHorizontalSlider("syn", &fslider7, 0.0f, -3.0f, 3.0f, 0.0001f);
		ui_interface->declare(&fslider4, "acc", "1 0 -30 0 30");
		ui_interface->declare(&fslider4, "hidden", "1");
		ui_interface->addHorizontalSlider("syp", &fslider4, 0.0f, -3.0f, 3.0f, 0.0001f);
		ui_interface->declare(&fslider8, "acc", "2 1 -30 0 30");
		ui_interface->declare(&fslider8, "hidden", "1");
		ui_interface->addHorizontalSlider("szn", &fslider8, 0.0f, -3.0f, 3.0f, 0.0001f);
		ui_interface->declare(&fslider5, "acc", "2 0 -30 0 30");
		ui_interface->declare(&fslider5, "hidden", "1");
		ui_interface->addHorizontalSlider("szp", &fslider5, 0.0f, -3.0f, 3.0f, 0.0001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fcheckbox0);
		int 	iSlow1 = (fSlow0 != 0.0f);
		float 	fSlow2 = tanf((fConst1 * float(fslider0)));
		float 	fSlow3 = (1.0f / fSlow2);
		float 	fSlow4 = (fSlow3 + 1.0f);
		float 	fSlow5 = (0 - (1.0f / (fSlow2 * fSlow4)));
		float 	fSlow6 = max((float)0, float(fslider1));
		float 	fSlow7 = (1.0f / fSlow4);
		float 	fSlow8 = (1.0f - fSlow3);
		float 	fSlow9 = (fSlow6 / fSlow2);
		float 	fSlow10 = float(fslider2);
		float 	fSlow11 = float(fslider3);
		float 	fSlow12 = float(fcheckbox1);
		int 	iSlow13 = (fSlow12 != 0.0f);
		float 	fSlow14 = max((float)0, float(fslider4));
		float 	fSlow15 = (fSlow14 / fSlow2);
		float 	fSlow16 = float(fcheckbox2);
		int 	iSlow17 = (fSlow16 != 0.0f);
		float 	fSlow18 = max((float)0, float(fslider5));
		float 	fSlow19 = (fSlow18 / fSlow2);
		float 	fSlow20 = float(fcheckbox3);
		int 	iSlow21 = (fSlow20 != 0.0f);
		float 	fSlow22 = max((float)0, float(fslider6));
		float 	fSlow23 = (fSlow22 / fSlow2);
		float 	fSlow24 = float(fcheckbox4);
		int 	iSlow25 = (fSlow24 != 0.0f);
		float 	fSlow26 = max((float)0, float(fslider7));
		float 	fSlow27 = (fSlow26 / fSlow2);
		float 	fSlow28 = float(fcheckbox5);
		int 	iSlow29 = (fSlow28 != 0.0f);
		float 	fSlow30 = max((float)0, float(fslider8));
		float 	fSlow31 = (fSlow30 / fSlow2);
		float 	fSlow32 = float(fcheckbox6);
		int 	iSlow33 = (fSlow32 != 0.0f);
		float 	fSlow34 = (1.0f / tanf((fConst1 * float(fslider9))));
		float 	fSlow35 = (1.0f / (fSlow34 + 1.0f));
		float 	fSlow36 = (1.0f - fSlow34);
		float 	fSlow37 = max((float)0, float(fslider10));
		float 	fSlow38 = float(fcheckbox7);
		int 	iSlow39 = (fSlow38 != 0.0f);
		float 	fSlow40 = float(fcheckbox8);
		int 	iSlow41 = (fSlow40 != 0.0f);
		float 	fSlow42 = float(fcheckbox9);
		int 	iSlow43 = (fSlow42 != 0.0f);
		float 	fSlow44 = max((float)0, float(fslider11));
		float 	fSlow45 = float(fcheckbox10);
		int 	iSlow46 = (fSlow45 != 0.0f);
		float 	fSlow47 = float(fcheckbox11);
		int 	iSlow48 = (fSlow47 != 0.0f);
		float 	fSlow49 = float(fcheckbox12);
		int 	iSlow50 = (fSlow49 != 0.0f);
		float 	fSlow51 = max((float)0, float(fslider12));
		float 	fSlow52 = float(fcheckbox13);
		int 	iSlow53 = (fSlow52 != 0.0f);
		float 	fSlow54 = float(fcheckbox14);
		int 	iSlow55 = (fSlow54 != 0.0f);
		float 	fSlow56 = float(fcheckbox15);
		int 	iSlow57 = (fSlow56 != 0.0f);
		float 	fSlow58 = max((float)0, float(fslider13));
		float 	fSlow59 = float(fcheckbox16);
		int 	iSlow60 = (fSlow59 != 0.0f);
		float 	fSlow61 = max((float)0, float(fslider14));
		float 	fSlow62 = float(fcheckbox17);
		int 	iSlow63 = (fSlow62 != 0.0f);
		float 	fSlow64 = max((float)0, float(fslider15));
		float 	fSlow65 = float(fcheckbox18);
		int 	iSlow66 = (fSlow65 != 0.0f);
		float 	fSlow67 = float(fslider16);
		float 	fSlow68 = (fSlow67 + 1.0f);
		float 	fSlow69 = float(fslider17);
		float 	fSlow70 = float(fcheckbox19);
		int 	iSlow71 = (fSlow70 != 0.0f);
		float 	fSlow72 = float(fslider18);
		float 	fSlow73 = float(fcheckbox20);
		int 	iSlow74 = (fSlow73 != 0.0f);
		float 	fSlow75 = float(fslider19);
		float 	fSlow76 = float(fcheckbox21);
		int 	iSlow77 = (fSlow76 != 0.0f);
		float 	fSlow78 = float(fslider20);
		float 	fSlow79 = float(fcheckbox22);
		int 	iSlow80 = (fSlow79 != 0.0f);
		float 	fSlow81 = float(fslider21);
		float 	fSlow82 = float(fcheckbox23);
		int 	iSlow83 = (fSlow82 != 0.0f);
		float 	fSlow84 = float(fslider22);
		float 	fSlow85 = float(fcheckbox24);
		int 	iSlow86 = (fSlow85 != 0.0f);
		float 	fSlow87 = float(fslider23);
		float 	fSlow88 = float(fslider24);
		float 	fSlow89 = float(fcheckbox25);
		int 	iSlow90 = (fSlow89 != 0.0f);
		float 	fSlow91 = float(fcheckbox26);
		int 	iSlow92 = (fSlow91 != 0.0f);
		float 	fSlow93 = float(fcheckbox27);
		int 	iSlow94 = (fSlow93 != 0.0f);
		float 	fSlow95 = float(fslider25);
		float 	fSlow96 = expf((0 - (fConst6 / float(fslider26))));
		float 	fSlow97 = expf((0 - (fConst6 / float(fslider27))));
		float 	fSlow98 = float(fcheckbox28);
		int 	iSlow99 = (fSlow98 != 0.0f);
		float 	fSlow100 = float(fslider28);
		float 	fSlow101 = float(fcheckbox29);
		int 	iSlow102 = (fSlow101 != 0.0f);
		float 	fSlow103 = float(fcheckbox30);
		int 	iSlow104 = (fSlow103 != 0.0f);
		float 	fSlow105 = float(fcheckbox31);
		int 	iSlow106 = (fSlow105 != 0.0f);
		float 	fSlow107 = float(fslider29);
		float 	fSlow108 = float(fcheckbox32);
		int 	iSlow109 = (fSlow108 != 0.0f);
		float 	fSlow110 = float(fcheckbox33);
		int 	iSlow111 = (fSlow110 != 0.0f);
		float 	fSlow112 = float(fcheckbox34);
		int 	iSlow113 = (fSlow112 != 0.0f);
		float 	fSlow114 = float(fslider30);
		float 	fSlow115 = (0.0010000000000000009f * float(fslider31));
		float 	fSlow116 = float(fcheckbox35);
		int 	iSlow117 = (fSlow116 != 0.0f);
		float 	fSlow118 = float(fcheckbox36);
		int 	iSlow119 = (fSlow118 != 0.0f);
		float 	fSlow120 = float(fcheckbox37);
		int 	iSlow121 = (fSlow120 != 0.0f);
		float 	fSlow122 = float(fslider32);
		float 	fSlow123 = expf((0 - (fConst6 / float(fslider33))));
		float 	fSlow124 = expf((0 - (fConst6 / float(fslider34))));
		float 	fSlow125 = float(fcheckbox38);
		int 	iSlow126 = (fSlow125 != 0.0f);
		float 	fSlow127 = (0.0010000000000000009f * float(fslider35));
		float 	fSlow128 = float(fcheckbox39);
		int 	iSlow129 = (fSlow128 != 0.0f);
		float 	fSlow130 = float(fcheckbox40);
		int 	iSlow131 = (fSlow130 != 0.0f);
		float 	fSlow132 = float(fcheckbox41);
		int 	iSlow133 = (fSlow132 != 0.0f);
		float 	fSlow134 = (0.0010000000000000009f * float(fslider36));
		float 	fSlow135 = float(fcheckbox42);
		int 	iSlow136 = (fSlow135 != 0.0f);
		float 	fSlow137 = float(fcheckbox43);
		int 	iSlow138 = (fSlow137 != 0.0f);
		float 	fSlow139 = float(fcheckbox44);
		int 	iSlow140 = (fSlow139 != 0.0f);
		float 	fSlow141 = float(fslider37);
		float 	fSlow142 = float(fcheckbox45);
		int 	iSlow143 = (fSlow142 != 0.0f);
		float 	fSlow144 = float(fcheckbox46);
		int 	iSlow145 = (fSlow144 != 0.0f);
		float 	fSlow146 = float(fcheckbox47);
		int 	iSlow147 = (fSlow146 != 0.0f);
		float 	fSlow148 = float(fcheckbox48);
		int 	iSlow149 = (fSlow148 != 0.0f);
		float 	fSlow150 = float(fcheckbox49);
		int 	iSlow151 = (fSlow150 != 0.0f);
		float 	fSlow152 = float(fcheckbox50);
		int 	iSlow153 = (fSlow152 != 0.0f);
		float 	fSlow154 = float(fcheckbox51);
		int 	iSlow155 = (fSlow154 != 0.0f);
		float 	fSlow156 = float(fcheckbox52);
		int 	iSlow157 = (fSlow156 != 0.0f);
		float 	fSlow158 = float(fslider38);
		float 	fSlow159 = float(fslider39);
		float 	fSlow160 = float(fslider40);
		float 	fSlow161 = float(fslider41);
		float 	fSlow162 = float(fslider42);
		float 	fSlow163 = float(fcheckbox53);
		int 	iSlow164 = (fSlow163 != 0.0f);
		float 	fSlow165 = float(fcheckbox54);
		int 	iSlow166 = (fSlow165 != 0.0f);
		float 	fSlow167 = float(fcheckbox55);
		int 	iSlow168 = (fSlow167 != 0.0f);
		float 	fSlow169 = float(fcheckbox56);
		int 	iSlow170 = (fSlow169 != 0.0f);
		float 	fSlow171 = float(fcheckbox57);
		int 	iSlow172 = (fSlow171 != 0.0f);
		float 	fSlow173 = float(fcheckbox58);
		int 	iSlow174 = (fSlow173 != 0.0f);
		float 	fSlow175 = float(fcheckbox59);
		int 	iSlow176 = (fSlow175 != 0.0f);
		float 	fSlow177 = float(fcheckbox60);
		int 	iSlow178 = (fSlow177 != 0.0f);
		float 	fSlow179 = float(fcheckbox61);
		int 	iSlow180 = (fSlow179 != 0.0f);
		float 	fSlow181 = float(fcheckbox62);
		int 	iSlow182 = (fSlow181 != 0.0f);
		float 	fSlow183 = float(fcheckbox63);
		int 	iSlow184 = (fSlow183 != 0.0f);
		float 	fSlow185 = float(fcheckbox64);
		int 	iSlow186 = (fSlow185 != 0.0f);
		float 	fSlow187 = float(fcheckbox65);
		int 	iSlow188 = (fSlow187 != 0.0f);
		float 	fSlow189 = float(fcheckbox66);
		int 	iSlow190 = (fSlow189 != 0.0f);
		float 	fSlow191 = float(fcheckbox67);
		int 	iSlow192 = (fSlow191 != 0.0f);
		float 	fSlow193 = float(fcheckbox68);
		int 	iSlow194 = (fSlow193 != 0.0f);
		float 	fSlow195 = float(fcheckbox69);
		int 	iSlow196 = (fSlow195 != 0.0f);
		float 	fSlow197 = float(fcheckbox70);
		int 	iSlow198 = (fSlow197 != 0.0f);
		float 	fSlow199 = float(fcheckbox71);
		int 	iSlow200 = (fSlow199 != 0.0f);
		float 	fSlow201 = float(fcheckbox72);
		int 	iSlow202 = (fSlow201 != 0.0f);
		float 	fSlow203 = float(fcheckbox73);
		int 	iSlow204 = (fSlow203 != 0.0f);
		float 	fSlow205 = float(fcheckbox74);
		int 	iSlow206 = (fSlow205 != 0.0f);
		float 	fSlow207 = float(fcheckbox75);
		int 	iSlow208 = (fSlow207 != 0.0f);
		float 	fSlow209 = float(fcheckbox76);
		int 	iSlow210 = (fSlow209 != 0.0f);
		float 	fSlow211 = float(fcheckbox77);
		int 	iSlow212 = (fSlow211 != 0.0f);
		float 	fSlow213 = float(fcheckbox78);
		int 	iSlow214 = (fSlow213 != 0.0f);
		float 	fSlow215 = float(fcheckbox79);
		int 	iSlow216 = (fSlow215 != 0.0f);
		float 	fSlow217 = float(fcheckbox80);
		int 	iSlow218 = (fSlow217 != 0.0f);
		float 	fSlow219 = float(fcheckbox81);
		int 	iSlow220 = (fSlow219 != 0.0f);
		float 	fSlow221 = float(fcheckbox82);
		int 	iSlow222 = (fSlow221 != 0.0f);
		float 	fSlow223 = float(fcheckbox83);
		int 	iSlow224 = (fSlow223 != 0.0f);
		float 	fSlow225 = float(fcheckbox84);
		int 	iSlow226 = (fSlow225 != 0.0f);
		float 	fSlow227 = float(fcheckbox85);
		int 	iSlow228 = (fSlow227 != 0.0f);
		float 	fSlow229 = float(fcheckbox86);
		int 	iSlow230 = (fSlow229 != 0.0f);
		float 	fSlow231 = float(fcheckbox87);
		int 	iSlow232 = (fSlow231 != 0.0f);
		float 	fSlow233 = float(fcheckbox88);
		int 	iSlow234 = (fSlow233 != 0.0f);
		float 	fSlow235 = float(fcheckbox89);
		int 	iSlow236 = (fSlow235 != 0.0f);
		float 	fSlow237 = float(fcheckbox90);
		int 	iSlow238 = (fSlow237 != 0.0f);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* input4 = input[4];
		FAUSTFLOAT* input5 = input[5];
		FAUSTFLOAT* input6 = input[6];
		FAUSTFLOAT* input7 = input[7];
		FAUSTFLOAT* input8 = input[8];
		FAUSTFLOAT* input9 = input[9];
		FAUSTFLOAT* input10 = input[10];
		FAUSTFLOAT* input11 = input[11];
		FAUSTFLOAT* input12 = input[12];
		FAUSTFLOAT* input13 = input[13];
		FAUSTFLOAT* input14 = input[14];
		FAUSTFLOAT* input15 = input[15];
		FAUSTFLOAT* input16 = input[16];
		FAUSTFLOAT* input17 = input[17];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		FAUSTFLOAT* output8 = output[8];
		FAUSTFLOAT* output9 = output[9];
		FAUSTFLOAT* output10 = output[10];
		FAUSTFLOAT* output11 = output[11];
		FAUSTFLOAT* output12 = output[12];
		FAUSTFLOAT* output13 = output[13];
		FAUSTFLOAT* output14 = output[14];
		FAUSTFLOAT* output15 = output[15];
		FAUSTFLOAT* output16 = output[16];
		FAUSTFLOAT* output17 = output[17];
		FAUSTFLOAT* output18 = output[18];
		FAUSTFLOAT* output19 = output[19];
		FAUSTFLOAT* output20 = output[20];
		FAUSTFLOAT* output21 = output[21];
		FAUSTFLOAT* output22 = output[22];
		FAUSTFLOAT* output23 = output[23];
		FAUSTFLOAT* output24 = output[24];
		FAUSTFLOAT* output25 = output[25];
		FAUSTFLOAT* output26 = output[26];
		FAUSTFLOAT* output27 = output[27];
		FAUSTFLOAT* output28 = output[28];
		FAUSTFLOAT* output29 = output[29];
		FAUSTFLOAT* output30 = output[30];
		FAUSTFLOAT* output31 = output[31];
		FAUSTFLOAT* output32 = output[32];
		FAUSTFLOAT* output33 = output[33];
		FAUSTFLOAT* output34 = output[34];
		FAUSTFLOAT* output35 = output[35];
		FAUSTFLOAT* output36 = output[36];
		FAUSTFLOAT* output37 = output[37];
		FAUSTFLOAT* output38 = output[38];
		FAUSTFLOAT* output39 = output[39];
		FAUSTFLOAT* output40 = output[40];
		FAUSTFLOAT* output41 = output[41];
		FAUSTFLOAT* output42 = output[42];
		FAUSTFLOAT* output43 = output[43];
		FAUSTFLOAT* output44 = output[44];
		FAUSTFLOAT* output45 = output[45];
		FAUSTFLOAT* output46 = output[46];
		FAUSTFLOAT* output47 = output[47];
		FAUSTFLOAT* output48 = output[48];
		FAUSTFLOAT* output49 = output[49];
		FAUSTFLOAT* output50 = output[50];
		FAUSTFLOAT* output51 = output[51];
		FAUSTFLOAT* output52 = output[52];
		FAUSTFLOAT* output53 = output[53];
		FAUSTFLOAT* output54 = output[54];
		FAUSTFLOAT* output55 = output[55];
		FAUSTFLOAT* output56 = output[56];
		FAUSTFLOAT* output57 = output[57];
		FAUSTFLOAT* output58 = output[58];
		FAUSTFLOAT* output59 = output[59];
		FAUSTFLOAT* output60 = output[60];
		FAUSTFLOAT* output61 = output[61];
		FAUSTFLOAT* output62 = output[62];
		FAUSTFLOAT* output63 = output[63];
		FAUSTFLOAT* output64 = output[64];
		FAUSTFLOAT* output65 = output[65];
		FAUSTFLOAT* output66 = output[66];
		FAUSTFLOAT* output67 = output[67];
		FAUSTFLOAT* output68 = output[68];
		FAUSTFLOAT* output69 = output[69];
		FAUSTFLOAT* output70 = output[70];
		FAUSTFLOAT* output71 = output[71];
		FAUSTFLOAT* output72 = output[72];
		FAUSTFLOAT* output73 = output[73];
		FAUSTFLOAT* output74 = output[74];
		FAUSTFLOAT* output75 = output[75];
		FAUSTFLOAT* output76 = output[76];
		FAUSTFLOAT* output77 = output[77];
		FAUSTFLOAT* output78 = output[78];
		FAUSTFLOAT* output79 = output[79];
		FAUSTFLOAT* output80 = output[80];
		FAUSTFLOAT* output81 = output[81];
		FAUSTFLOAT* output82 = output[82];
		FAUSTFLOAT* output83 = output[83];
		FAUSTFLOAT* output84 = output[84];
		FAUSTFLOAT* output85 = output[85];
		FAUSTFLOAT* output86 = output[86];
		FAUSTFLOAT* output87 = output[87];
		FAUSTFLOAT* output88 = output[88];
		FAUSTFLOAT* output89 = output[89];
		FAUSTFLOAT* output90 = output[90];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow1) {
				fVec0[0] = fSlow6;
				fRec3[0] = ((fSlow5 * fVec0[1]) - (fSlow7 * ((fSlow8 * fRec3[1]) - fSlow9)));
				iTempPerm0 = (fRec3[0] > fSlow10);
				iVec1[0] = iTempPerm0;
				iTempPerm1 = (iVec1[0] > iVec1[1]);
				iRec2[0] = ((int(iTempPerm1))?(iRec2[1] + 1):iRec2[1]);
				iTempPerm2 = ((int(iRec0[1]))?((int((min(1, iRec2[0]) == 1)))?iTempPerm1:0):1);
				fRec4[0] = ((fConst2 + fRec4[1]) * float(iTempPerm2));
				iTempPerm3 = (iTempPerm2 * ((1000.0f * fRec4[0]) < fSlow11));
				iRec0[0] = (iTempPerm3 == 0);
				int 	iRec1 = iTempPerm3;
				fTempPerm4 = (fSlow0 * float(iRec1));
			}
			output0[i] = (FAUSTFLOAT)fTempPerm4;
			if (iSlow13) {
				fVec2[0] = fSlow14;
				fRec8[0] = ((fSlow5 * fVec2[1]) - (fSlow7 * ((fSlow8 * fRec8[1]) - fSlow15)));
				iTempPerm5 = (fRec8[0] > fSlow10);
				iVec3[0] = iTempPerm5;
				iTempPerm6 = (iVec3[0] > iVec3[1]);
				iRec7[0] = ((int(iTempPerm6))?(iRec7[1] + 1):iRec7[1]);
				iTempPerm7 = ((int(iRec5[1]))?((int((min(1, iRec7[0]) == 1)))?iTempPerm6:0):1);
				fRec9[0] = ((fConst2 + fRec9[1]) * float(iTempPerm7));
				iTempPerm8 = (iTempPerm7 * ((1000.0f * fRec9[0]) < fSlow11));
				iRec5[0] = (iTempPerm8 == 0);
				int 	iRec6 = iTempPerm8;
				fTempPerm9 = (fSlow12 * float(iRec6));
			}
			output1[i] = (FAUSTFLOAT)fTempPerm9;
			if (iSlow17) {
				fVec4[0] = fSlow18;
				fRec13[0] = ((fSlow5 * fVec4[1]) - (fSlow7 * ((fSlow8 * fRec13[1]) - fSlow19)));
				iTempPerm10 = (fRec13[0] > fSlow10);
				iVec5[0] = iTempPerm10;
				iTempPerm11 = (iVec5[0] > iVec5[1]);
				iRec12[0] = ((int(iTempPerm11))?(iRec12[1] + 1):iRec12[1]);
				iTempPerm12 = ((int(iRec10[1]))?((int((min(1, iRec12[0]) == 1)))?iTempPerm11:0):1);
				fRec14[0] = ((fConst2 + fRec14[1]) * float(iTempPerm12));
				iTempPerm13 = (iTempPerm12 * ((1000.0f * fRec14[0]) < fSlow11));
				iRec10[0] = (iTempPerm13 == 0);
				int 	iRec11 = iTempPerm13;
				fTempPerm14 = (fSlow16 * float(iRec11));
			}
			output2[i] = (FAUSTFLOAT)fTempPerm14;
			if (iSlow21) {
				fVec6[0] = fSlow22;
				fRec18[0] = ((fSlow5 * fVec6[1]) - (fSlow7 * ((fSlow8 * fRec18[1]) - fSlow23)));
				iTempPerm15 = (fRec18[0] > fSlow10);
				iVec7[0] = iTempPerm15;
				iTempPerm16 = (iVec7[0] > iVec7[1]);
				iRec17[0] = ((int(iTempPerm16))?(iRec17[1] + 1):iRec17[1]);
				iTempPerm17 = ((int(iRec15[1]))?((int((min(1, iRec17[0]) == 1)))?iTempPerm16:0):1);
				fRec19[0] = ((fConst2 + fRec19[1]) * float(iTempPerm17));
				iTempPerm18 = (iTempPerm17 * ((1000.0f * fRec19[0]) < fSlow11));
				iRec15[0] = (iTempPerm18 == 0);
				int 	iRec16 = iTempPerm18;
				fTempPerm19 = (fSlow20 * float(iRec16));
			}
			output3[i] = (FAUSTFLOAT)fTempPerm19;
			if (iSlow25) {
				fVec8[0] = fSlow26;
				fRec23[0] = ((fSlow5 * fVec8[1]) - (fSlow7 * ((fSlow8 * fRec23[1]) - fSlow27)));
				iTempPerm20 = (fRec23[0] > fSlow10);
				iVec9[0] = iTempPerm20;
				iTempPerm21 = (iVec9[0] > iVec9[1]);
				iRec22[0] = ((int(iTempPerm21))?(iRec22[1] + 1):iRec22[1]);
				iTempPerm22 = ((int(iRec20[1]))?((int((min(1, iRec22[0]) == 1)))?iTempPerm21:0):1);
				fRec24[0] = ((fConst2 + fRec24[1]) * float(iTempPerm22));
				iTempPerm23 = (iTempPerm22 * ((1000.0f * fRec24[0]) < fSlow11));
				iRec20[0] = (iTempPerm23 == 0);
				int 	iRec21 = iTempPerm23;
				fTempPerm24 = (fSlow24 * float(iRec21));
			}
			output4[i] = (FAUSTFLOAT)fTempPerm24;
			if (iSlow29) {
				fVec10[0] = fSlow30;
				fRec28[0] = ((fSlow5 * fVec10[1]) - (fSlow7 * ((fSlow8 * fRec28[1]) - fSlow31)));
				iTempPerm25 = (fRec28[0] > fSlow10);
				iVec11[0] = iTempPerm25;
				iTempPerm26 = (iVec11[0] > iVec11[1]);
				iRec27[0] = ((int(iTempPerm26))?(iRec27[1] + 1):iRec27[1]);
				iTempPerm27 = ((int(iRec25[1]))?((int((min(1, iRec27[0]) == 1)))?iTempPerm26:0):1);
				fRec29[0] = ((fConst2 + fRec29[1]) * float(iTempPerm27));
				iTempPerm28 = (iTempPerm27 * ((1000.0f * fRec29[0]) < fSlow11));
				iRec25[0] = (iTempPerm28 == 0);
				int 	iRec26 = iTempPerm28;
				fTempPerm29 = (fSlow28 * float(iRec26));
			}
			output5[i] = (FAUSTFLOAT)fTempPerm29;
			if (iSlow33 || iSlow39 || iSlow41) {
				fVec12[0] = fSlow37;
				fRec30[0] = (0 - (fSlow35 * ((fSlow36 * fRec30[1]) - (fSlow37 + fVec12[1]))));
				fTempPerm30 = min((float)1, max((float)0, fRec30[0]));
			}
			if (iSlow33) {
				fTempPerm31 = (fSlow32 * fTempPerm30);
			}
			output6[i] = (FAUSTFLOAT)fTempPerm31;
			if (iSlow43 || iSlow46 || iSlow48) {
				fVec13[0] = fSlow44;
				fRec31[0] = (0 - (fSlow35 * ((fSlow36 * fRec31[1]) - (fSlow44 + fVec13[1]))));
				fTempPerm32 = min((float)1, max((float)0, fRec31[0]));
			}
			if (iSlow43) {
				fTempPerm33 = (fSlow42 * fTempPerm32);
			}
			output7[i] = (FAUSTFLOAT)fTempPerm33;
			if (iSlow50 || iSlow53 || iSlow55) {
				fVec14[0] = fSlow51;
				fRec32[0] = (0 - (fSlow35 * ((fSlow36 * fRec32[1]) - (fSlow51 + fVec14[1]))));
				fTempPerm34 = min((float)1, max((float)0, fRec32[0]));
			}
			if (iSlow50) {
				fTempPerm35 = (fSlow49 * fTempPerm34);
			}
			output8[i] = (FAUSTFLOAT)fTempPerm35;
			if (iSlow57 || iSlow39 || iSlow41) {
				fVec15[0] = fSlow58;
				fRec33[0] = (0 - (fSlow35 * ((fSlow36 * fRec33[1]) - (fSlow58 + fVec15[1]))));
				fTempPerm36 = min((float)1, max((float)0, fRec33[0]));
			}
			if (iSlow57) {
				fTempPerm37 = (fSlow56 * fTempPerm36);
			}
			output9[i] = (FAUSTFLOAT)fTempPerm37;
			if (iSlow60 || iSlow46 || iSlow48) {
				fVec16[0] = fSlow61;
				fRec34[0] = (0 - (fSlow35 * ((fSlow36 * fRec34[1]) - (fSlow61 + fVec16[1]))));
				fTempPerm38 = min((float)1, max((float)0, fRec34[0]));
			}
			if (iSlow60) {
				fTempPerm39 = (fSlow59 * fTempPerm38);
			}
			output10[i] = (FAUSTFLOAT)fTempPerm39;
			if (iSlow63 || iSlow53 || iSlow55) {
				fVec17[0] = fSlow64;
				fRec35[0] = (0 - (fSlow35 * ((fSlow36 * fRec35[1]) - (fSlow64 + fVec17[1]))));
				fTempPerm40 = min((float)1, max((float)0, fRec35[0]));
			}
			if (iSlow63) {
				fTempPerm41 = (fSlow62 * fTempPerm40);
			}
			output11[i] = (FAUSTFLOAT)fTempPerm41;
			if (iSlow66) {
				fVec18[0] = fSlow69;
				fRec36[0] = (0 - (fSlow35 * ((fSlow36 * fRec36[1]) - (fSlow69 + fVec18[1]))));
				fTempPerm42 = (fSlow65 * min((float)1, max((float)0, (fSlow68 * max((float)0, ((0.5f * ((0.63661977236758138f * asinf(min((float)1, max((float)-1, fRec36[0])))) + 1.0f)) - fSlow67))))));
			}
			output12[i] = (FAUSTFLOAT)fTempPerm42;
			if (iSlow71) {
				fVec19[0] = fSlow72;
				fRec37[0] = (0 - (fSlow35 * ((fSlow36 * fRec37[1]) - (fSlow72 + fVec19[1]))));
				fTempPerm43 = (fSlow70 * min((float)1, max((float)0, (fSlow68 * max((float)0, ((0.5f * ((0.63661977236758138f * asinf(min((float)1, max((float)-1, fRec37[0])))) + 1.0f)) - fSlow67))))));
			}
			output13[i] = (FAUSTFLOAT)fTempPerm43;
			if (iSlow74) {
				fVec20[0] = fSlow75;
				fRec38[0] = (0 - (fSlow35 * ((fSlow36 * fRec38[1]) - (fSlow75 + fVec20[1]))));
				fTempPerm44 = (fSlow73 * min((float)1, max((float)0, (fSlow68 * max((float)0, ((0.5f * ((0.63661977236758138f * asinf(min((float)1, max((float)-1, fRec38[0])))) + 1.0f)) - fSlow67))))));
			}
			output14[i] = (FAUSTFLOAT)fTempPerm44;
			if (iSlow77) {
				fVec21[0] = fSlow78;
				fRec39[0] = (0 - (fSlow35 * ((fSlow36 * fRec39[1]) - (fSlow78 + fVec21[1]))));
				fTempPerm45 = (fSlow76 * min((float)1, max((float)0, (fSlow68 * max((float)0, ((0.5f * ((0.63661977236758138f * asinf(min((float)1, max((float)-1, fRec39[0])))) + 1.0f)) - fSlow67))))));
			}
			output15[i] = (FAUSTFLOAT)fTempPerm45;
			if (iSlow80) {
				fVec22[0] = fSlow81;
				fRec40[0] = (0 - (fSlow35 * ((fSlow36 * fRec40[1]) - (fSlow81 + fVec22[1]))));
				fTempPerm46 = (fSlow79 * min((float)1, max((float)0, (fSlow68 * max((float)0, ((0.5f * ((0.63661977236758138f * asinf(min((float)1, max((float)-1, fRec40[0])))) + 1.0f)) - fSlow67))))));
			}
			output16[i] = (FAUSTFLOAT)fTempPerm46;
			if (iSlow83) {
				fVec23[0] = fSlow84;
				fRec41[0] = (0 - (fSlow35 * ((fSlow36 * fRec41[1]) - (fSlow84 + fVec23[1]))));
				fTempPerm47 = (fSlow82 * min((float)1, max((float)0, (fSlow68 * max((float)0, ((0.5f * ((0.63661977236758138f * asinf(min((float)1, max((float)-1, fRec41[0])))) + 1.0f)) - fSlow67))))));
			}
			output17[i] = (FAUSTFLOAT)fTempPerm47;
			if (iSlow86 || iSlow90 || iSlow92 || iSlow94) {
				fVec24[0] = fSlow88;
				fRec44[0] = (fConst4 * ((fSlow88 - fVec24[1]) + (fConst5 * fRec44[1])));
			}
			if (iSlow86) {
				fTempPerm48 = fabsf(min((float)1, (fSlow87 * max((float)0, (fabsf(fRec44[0]) - fSlow95)))));
				fTempPerm49 = ((int((fRec42[1] > fTempPerm48)))?fSlow96:fSlow97);
				fRec43[0] = ((fRec43[1] * fTempPerm49) + (fTempPerm48 * (1.0f - fTempPerm49)));
				fRec42[0] = fRec43[0];
				fTempPerm50 = (fSlow85 * fRec42[0]);
			}
			output18[i] = (FAUSTFLOAT)fTempPerm50;
			if (iSlow99 || iSlow102 || iSlow104 || iSlow94) {
				fVec25[0] = fSlow100;
				fRec47[0] = (fConst4 * ((fSlow100 - fVec25[1]) + (fConst5 * fRec47[1])));
			}
			if (iSlow99) {
				fTempPerm51 = fabsf(min((float)1, (fSlow87 * max((float)0, (fabsf(fRec47[0]) - fSlow95)))));
				fTempPerm52 = ((int((fRec45[1] > fTempPerm51)))?fSlow96:fSlow97);
				fRec46[0] = ((fRec46[1] * fTempPerm52) + (fTempPerm51 * (1.0f - fTempPerm52)));
				fRec45[0] = fRec46[0];
				fTempPerm53 = (fSlow98 * fRec45[0]);
			}
			output19[i] = (FAUSTFLOAT)fTempPerm53;
			if (iSlow106 || iSlow109 || iSlow111 || iSlow94) {
				fVec26[0] = fSlow107;
				fRec50[0] = (fConst4 * ((fSlow107 - fVec26[1]) + (fConst5 * fRec50[1])));
			}
			if (iSlow106) {
				fTempPerm54 = fabsf(min((float)1, (fSlow87 * max((float)0, (fabsf(fRec50[0]) - fSlow95)))));
				fTempPerm55 = ((int((fRec48[1] > fTempPerm54)))?fSlow96:fSlow97);
				fRec49[0] = ((fRec49[1] * fTempPerm55) + (fTempPerm54 * (1.0f - fTempPerm55)));
				fRec48[0] = fRec49[0];
				fTempPerm56 = (fSlow105 * fRec48[0]);
			}
			output20[i] = (FAUSTFLOAT)fTempPerm56;
			if (iSlow90) {
				fTempPerm57 = fabsf(min((float)1, (fSlow87 * max((float)0, (fRec44[0] - fSlow95)))));
				fTempPerm58 = ((int((fRec51[1] > fTempPerm57)))?fSlow96:fSlow97);
				fRec52[0] = ((fRec52[1] * fTempPerm58) + (fTempPerm57 * (1.0f - fTempPerm58)));
				fRec51[0] = fRec52[0];
				fTempPerm59 = (fSlow89 * fRec51[0]);
			}
			output21[i] = (FAUSTFLOAT)fTempPerm59;
			if (iSlow102) {
				fTempPerm60 = fabsf(min((float)1, (fSlow87 * max((float)0, (fRec47[0] - fSlow95)))));
				fTempPerm61 = ((int((fRec53[1] > fTempPerm60)))?fSlow96:fSlow97);
				fRec54[0] = ((fRec54[1] * fTempPerm61) + (fTempPerm60 * (1.0f - fTempPerm61)));
				fRec53[0] = fRec54[0];
				fTempPerm62 = (fSlow101 * fRec53[0]);
			}
			output22[i] = (FAUSTFLOAT)fTempPerm62;
			if (iSlow109) {
				fTempPerm63 = fabsf(min((float)1, (fSlow87 * max((float)0, (fRec50[0] - fSlow95)))));
				fTempPerm64 = ((int((fRec55[1] > fTempPerm63)))?fSlow96:fSlow97);
				fRec56[0] = ((fRec56[1] * fTempPerm64) + (fTempPerm63 * (1.0f - fTempPerm64)));
				fRec55[0] = fRec56[0];
				fTempPerm65 = (fSlow108 * fRec55[0]);
			}
			output23[i] = (FAUSTFLOAT)fTempPerm65;
			if (iSlow92) {
				fTempPerm66 = fabsf(min((float)1, (fSlow87 * max((float)0, (0 - (fSlow95 + fRec44[0]))))));
				fTempPerm67 = ((int((fRec57[1] > fTempPerm66)))?fSlow96:fSlow97);
				fRec58[0] = ((fRec58[1] * fTempPerm67) + (fTempPerm66 * (1.0f - fTempPerm67)));
				fRec57[0] = fRec58[0];
				fTempPerm68 = (fSlow91 * fRec57[0]);
			}
			output24[i] = (FAUSTFLOAT)fTempPerm68;
			if (iSlow104) {
				fTempPerm69 = fabsf(min((float)1, (fSlow87 * max((float)0, (0 - (fSlow95 + fRec47[0]))))));
				fTempPerm70 = ((int((fRec59[1] > fTempPerm69)))?fSlow96:fSlow97);
				fRec60[0] = ((fRec60[1] * fTempPerm70) + (fTempPerm69 * (1.0f - fTempPerm70)));
				fRec59[0] = fRec60[0];
				fTempPerm71 = (fSlow103 * fRec59[0]);
			}
			output25[i] = (FAUSTFLOAT)fTempPerm71;
			if (iSlow111) {
				fTempPerm72 = fabsf(min((float)1, (fSlow87 * max((float)0, (0 - (fSlow95 + fRec50[0]))))));
				fTempPerm73 = ((int((fRec61[1] > fTempPerm72)))?fSlow96:fSlow97);
				fRec62[0] = ((fRec62[1] * fTempPerm73) + (fTempPerm72 * (1.0f - fTempPerm73)));
				fRec61[0] = fRec62[0];
				fTempPerm74 = (fSlow110 * fRec61[0]);
			}
			output26[i] = (FAUSTFLOAT)fTempPerm74;
			if (iSlow94) {
				fTempPerm75 = fabsf(min((float)1, (fSlow87 * max((float)0, (sqrtf(((faustpower<2>(fRec44[0]) + faustpower<2>(fRec47[0])) + faustpower<2>(fRec50[0]))) - fSlow95)))));
				fTempPerm76 = ((int((fRec63[1] > fTempPerm75)))?fSlow96:fSlow97);
				fRec64[0] = ((fRec64[1] * fTempPerm76) + (fTempPerm75 * (1.0f - fTempPerm76)));
				fRec63[0] = fRec64[0];
				fTempPerm77 = (fSlow93 * fRec63[0]);
			}
			output27[i] = (FAUSTFLOAT)fTempPerm77;
			if (iSlow113 || iSlow117 || iSlow119 || iSlow121) {
				fRec67[0] = (fSlow115 + (0.999f * fRec67[1]));
			}
			if (iSlow113) {
				fTempPerm78 = fabsf(min((float)1, (fSlow114 * max((float)0, (fabsf(fRec67[0]) - fSlow122)))));
				fTempPerm79 = ((int((fRec65[1] > fTempPerm78)))?fSlow123:fSlow124);
				fRec66[0] = ((fRec66[1] * fTempPerm79) + (fTempPerm78 * (1.0f - fTempPerm79)));
				fRec65[0] = fRec66[0];
				fTempPerm80 = (fSlow112 * fRec65[0]);
			}
			output28[i] = (FAUSTFLOAT)fTempPerm80;
			if (iSlow126 || iSlow129 || iSlow131 || iSlow121) {
				fRec70[0] = (fSlow127 + (0.999f * fRec70[1]));
			}
			if (iSlow126) {
				fTempPerm81 = fabsf(min((float)1, (fSlow114 * max((float)0, (fabsf(fRec70[0]) - fSlow122)))));
				fTempPerm82 = ((int((fRec68[1] > fTempPerm81)))?fSlow123:fSlow124);
				fRec69[0] = ((fRec69[1] * fTempPerm82) + (fTempPerm81 * (1.0f - fTempPerm82)));
				fRec68[0] = fRec69[0];
				fTempPerm83 = (fSlow125 * fRec68[0]);
			}
			output29[i] = (FAUSTFLOAT)fTempPerm83;
			if (iSlow133 || iSlow136 || iSlow138 || iSlow121) {
				fRec73[0] = (fSlow134 + (0.999f * fRec73[1]));
			}
			if (iSlow133) {
				fTempPerm84 = fabsf(min((float)1, (fSlow114 * max((float)0, (fabsf(fRec73[0]) - fSlow122)))));
				fTempPerm85 = ((int((fRec71[1] > fTempPerm84)))?fSlow123:fSlow124);
				fRec72[0] = ((fRec72[1] * fTempPerm85) + (fTempPerm84 * (1.0f - fTempPerm85)));
				fRec71[0] = fRec72[0];
				fTempPerm86 = (fSlow132 * fRec71[0]);
			}
			output30[i] = (FAUSTFLOAT)fTempPerm86;
			if (iSlow117) {
				fTempPerm87 = fabsf(min((float)1, (fSlow114 * max((float)0, (fRec67[0] - fSlow122)))));
				fTempPerm88 = ((int((fRec74[1] > fTempPerm87)))?fSlow123:fSlow124);
				fRec75[0] = ((fRec75[1] * fTempPerm88) + (fTempPerm87 * (1.0f - fTempPerm88)));
				fRec74[0] = fRec75[0];
				fTempPerm89 = (fSlow116 * fRec74[0]);
			}
			output31[i] = (FAUSTFLOAT)fTempPerm89;
			if (iSlow129) {
				fTempPerm90 = fabsf(min((float)1, (fSlow114 * max((float)0, (fRec70[0] - fSlow122)))));
				fTempPerm91 = ((int((fRec76[1] > fTempPerm90)))?fSlow123:fSlow124);
				fRec77[0] = ((fRec77[1] * fTempPerm91) + (fTempPerm90 * (1.0f - fTempPerm91)));
				fRec76[0] = fRec77[0];
				fTempPerm92 = (fSlow128 * fRec76[0]);
			}
			output32[i] = (FAUSTFLOAT)fTempPerm92;
			if (iSlow136) {
				fTempPerm93 = fabsf(min((float)1, (fSlow114 * max((float)0, (fRec73[0] - fSlow122)))));
				fTempPerm94 = ((int((fRec78[1] > fTempPerm93)))?fSlow123:fSlow124);
				fRec79[0] = ((fRec79[1] * fTempPerm94) + (fTempPerm93 * (1.0f - fTempPerm94)));
				fRec78[0] = fRec79[0];
				fTempPerm95 = (fSlow135 * fRec78[0]);
			}
			output33[i] = (FAUSTFLOAT)fTempPerm95;
			if (iSlow119) {
				fTempPerm96 = fabsf(min((float)1, (fSlow114 * max((float)0, (0 - (fSlow122 + fRec67[0]))))));
				fTempPerm97 = ((int((fRec80[1] > fTempPerm96)))?fSlow123:fSlow124);
				fRec81[0] = ((fRec81[1] * fTempPerm97) + (fTempPerm96 * (1.0f - fTempPerm97)));
				fRec80[0] = fRec81[0];
				fTempPerm98 = (fSlow118 * fRec80[0]);
			}
			output34[i] = (FAUSTFLOAT)fTempPerm98;
			if (iSlow131) {
				fTempPerm99 = fabsf(min((float)1, (fSlow114 * max((float)0, (0 - (fSlow122 + fRec70[0]))))));
				fTempPerm100 = ((int((fRec82[1] > fTempPerm99)))?fSlow123:fSlow124);
				fRec83[0] = ((fRec83[1] * fTempPerm100) + (fTempPerm99 * (1.0f - fTempPerm100)));
				fRec82[0] = fRec83[0];
				fTempPerm101 = (fSlow130 * fRec82[0]);
			}
			output35[i] = (FAUSTFLOAT)fTempPerm101;
			if (iSlow138) {
				fTempPerm102 = fabsf(min((float)1, (fSlow114 * max((float)0, (0 - (fSlow122 + fRec73[0]))))));
				fTempPerm103 = ((int((fRec84[1] > fTempPerm102)))?fSlow123:fSlow124);
				fRec85[0] = ((fRec85[1] * fTempPerm103) + (fTempPerm102 * (1.0f - fTempPerm103)));
				fRec84[0] = fRec85[0];
				fTempPerm104 = (fSlow137 * fRec84[0]);
			}
			output36[i] = (FAUSTFLOAT)fTempPerm104;
			if (iSlow121) {
				fTempPerm105 = fabsf(min((float)1, (fSlow114 * max((float)0, (sqrtf(((faustpower<2>(fRec67[0]) + faustpower<2>(fRec70[0])) + faustpower<2>(fRec73[0]))) - fSlow122)))));
				fTempPerm106 = ((int((fRec86[1] > fTempPerm105)))?fSlow123:fSlow124);
				fRec87[0] = ((fRec87[1] * fTempPerm106) + (fTempPerm105 * (1.0f - fTempPerm106)));
				fRec86[0] = fRec87[0];
				fTempPerm107 = (fSlow120 * fRec86[0]);
			}
			output37[i] = (FAUSTFLOAT)fTempPerm107;
			if (iSlow140 || iSlow143 || iSlow145 || iSlow147 || iSlow149 || iSlow151 || iSlow153) {
				fTempPerm108 = (float)input0[i];
			}
			if (iSlow140 || iSlow143 || iSlow145 || iSlow147 || iSlow149 || iSlow151 || iSlow155) {
				fTempPerm109 = (float)input1[i];
			}
			if (iSlow140 || iSlow145 || iSlow149 || iSlow151) {
				fTempPerm110 = faustpower<2>(fTempPerm109);
			}
			if (iSlow140 || iSlow143 || iSlow145 || iSlow147 || iSlow149 || iSlow151 || iSlow157) {
				fTempPerm111 = (float)input2[i];
			}
			if (iSlow140 || iSlow143 || iSlow145 || iSlow147) {
				fTempPerm112 = faustpower<2>(fTempPerm111);
			}
			if (iSlow140) {
				fRec88[0] = ((fConst7 * fRec88[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow141 * sqrtf(((faustpower<2>((fTempPerm108 + 1.0f)) + fTempPerm110) + fTempPerm112)))))));
				fTempPerm113 = (fSlow139 * fRec88[0]);
			}
			output38[i] = (FAUSTFLOAT)fTempPerm113;
			if (iSlow143 || iSlow147 || iSlow149 || iSlow151) {
				fTempPerm114 = faustpower<2>(fTempPerm108);
			}
			if (iSlow143 || iSlow147) {
				fTempPerm115 = (fTempPerm112 + fTempPerm114);
			}
			if (iSlow143) {
				fRec89[0] = ((fConst7 * fRec89[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow158 * sqrtf((faustpower<2>((fTempPerm109 + 1.0f)) + fTempPerm115)))))));
				fTempPerm116 = (fSlow142 * fRec89[0]);
			}
			output39[i] = (FAUSTFLOAT)fTempPerm116;
			if (iSlow145) {
				fRec90[0] = ((fConst7 * fRec90[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow159 * sqrtf((faustpower<2>((fTempPerm108 + -1.0f)) + (fTempPerm110 + fTempPerm112))))))));
				fTempPerm117 = (fSlow144 * fRec90[0]);
			}
			output40[i] = (FAUSTFLOAT)fTempPerm117;
			if (iSlow147) {
				fRec91[0] = ((fConst7 * fRec91[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((fTempPerm115 + faustpower<2>((fTempPerm109 + -1.0f)))))))));
				fTempPerm118 = (fSlow146 * fRec91[0]);
			}
			output41[i] = (FAUSTFLOAT)fTempPerm118;
			if (iSlow149 || iSlow151) {
				fTempPerm119 = (fTempPerm110 + fTempPerm114);
			}
			if (iSlow149) {
				fRec92[0] = ((fConst7 * fRec92[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((fTempPerm119 + faustpower<2>((fTempPerm111 + 1.0f)))))))));
				fTempPerm120 = (fSlow148 * fRec92[0]);
			}
			output42[i] = (FAUSTFLOAT)fTempPerm120;
			if (iSlow151) {
				fRec93[0] = ((fConst7 * fRec93[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm119 + faustpower<2>((fTempPerm111 + -1.0f)))))))));
				fTempPerm121 = (fSlow150 * fRec93[0]);
			}
			output43[i] = (FAUSTFLOAT)fTempPerm121;
			if (iSlow164 || iSlow166 || iSlow168 || iSlow170 || iSlow172 || iSlow174) {
				fTempPerm122 = (float)input3[i];
				fTempPerm123 = (float)input4[i];
			}
			if (iSlow164 || iSlow168 || iSlow172 || iSlow174) {
				fTempPerm124 = faustpower<2>(fTempPerm123);
			}
			if (iSlow164 || iSlow166 || iSlow168 || iSlow170 || iSlow172 || iSlow174) {
				fTempPerm125 = (float)input5[i];
			}
			if (iSlow164 || iSlow166 || iSlow168 || iSlow170) {
				fTempPerm126 = faustpower<2>(fTempPerm125);
			}
			if (iSlow164) {
				fRec94[0] = ((fConst7 * fRec94[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow141 * sqrtf(((faustpower<2>((fTempPerm122 + 1.0f)) + fTempPerm124) + fTempPerm126)))))));
				fTempPerm127 = (fSlow163 * fRec94[0]);
			}
			output44[i] = (FAUSTFLOAT)fTempPerm127;
			if (iSlow166 || iSlow170 || iSlow172 || iSlow174) {
				fTempPerm128 = faustpower<2>(fTempPerm122);
			}
			if (iSlow166 || iSlow170) {
				fTempPerm129 = (fTempPerm126 + fTempPerm128);
			}
			if (iSlow166) {
				fRec95[0] = ((fConst7 * fRec95[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow158 * sqrtf((faustpower<2>((fTempPerm123 + 1.0f)) + fTempPerm129)))))));
				fTempPerm130 = (fSlow165 * fRec95[0]);
			}
			output45[i] = (FAUSTFLOAT)fTempPerm130;
			if (iSlow168) {
				fRec96[0] = ((fConst7 * fRec96[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow159 * sqrtf((faustpower<2>((fTempPerm122 + -1.0f)) + (fTempPerm124 + fTempPerm126))))))));
				fTempPerm131 = (fSlow167 * fRec96[0]);
			}
			output46[i] = (FAUSTFLOAT)fTempPerm131;
			if (iSlow170) {
				fRec97[0] = ((fConst7 * fRec97[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((fTempPerm129 + faustpower<2>((fTempPerm123 + -1.0f)))))))));
				fTempPerm132 = (fSlow169 * fRec97[0]);
			}
			output47[i] = (FAUSTFLOAT)fTempPerm132;
			if (iSlow172 || iSlow174) {
				fTempPerm133 = (fTempPerm124 + fTempPerm128);
			}
			if (iSlow172) {
				fRec98[0] = ((fConst7 * fRec98[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((fTempPerm133 + faustpower<2>((fTempPerm125 + 1.0f)))))))));
				fTempPerm134 = (fSlow171 * fRec98[0]);
			}
			output48[i] = (FAUSTFLOAT)fTempPerm134;
			if (iSlow174) {
				fRec99[0] = ((fConst7 * fRec99[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm133 + faustpower<2>((fTempPerm125 + -1.0f)))))))));
				fTempPerm135 = (fSlow173 * fRec99[0]);
			}
			output49[i] = (FAUSTFLOAT)fTempPerm135;
			if (iSlow176 || iSlow178 || iSlow180 || iSlow182 || iSlow184 || iSlow186 || iSlow188 || iSlow190) {
				fTempPerm136 = (float)input6[i];
			}
			if (iSlow176 || iSlow178 || iSlow180 || iSlow182 || iSlow184 || iSlow186 || iSlow192 || iSlow194) {
				fTempPerm137 = (float)input7[i];
			}
			if (iSlow176 || iSlow180 || iSlow184 || iSlow186) {
				fTempPerm138 = faustpower<2>(fTempPerm137);
			}
			if (iSlow176 || iSlow178 || iSlow180 || iSlow182 || iSlow184 || iSlow186 || iSlow196) {
				fTempPerm139 = (float)input8[i];
			}
			if (iSlow176 || iSlow178 || iSlow180 || iSlow182) {
				fTempPerm140 = faustpower<2>(fTempPerm139);
			}
			if (iSlow176) {
				fRec100[0] = ((fConst7 * fRec100[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow141 * sqrtf(((faustpower<2>((fTempPerm136 + 1.0f)) + fTempPerm138) + fTempPerm140)))))));
				fTempPerm141 = (fSlow175 * fRec100[0]);
			}
			output50[i] = (FAUSTFLOAT)fTempPerm141;
			if (iSlow178 || iSlow182 || iSlow184 || iSlow186) {
				fTempPerm142 = faustpower<2>(fTempPerm136);
			}
			if (iSlow178 || iSlow182) {
				fTempPerm143 = (fTempPerm140 + fTempPerm142);
			}
			if (iSlow178) {
				fRec101[0] = ((fConst7 * fRec101[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow158 * sqrtf((faustpower<2>((fTempPerm137 + 1.0f)) + fTempPerm143)))))));
				fTempPerm144 = (fSlow177 * fRec101[0]);
			}
			output51[i] = (FAUSTFLOAT)fTempPerm144;
			if (iSlow180) {
				fRec102[0] = ((fConst7 * fRec102[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow159 * sqrtf((faustpower<2>((fTempPerm136 + -1.0f)) + (fTempPerm138 + fTempPerm140))))))));
				fTempPerm145 = (fSlow179 * fRec102[0]);
			}
			output52[i] = (FAUSTFLOAT)fTempPerm145;
			if (iSlow182) {
				fRec103[0] = ((fConst7 * fRec103[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((fTempPerm143 + faustpower<2>((fTempPerm137 + -1.0f)))))))));
				fTempPerm146 = (fSlow181 * fRec103[0]);
			}
			output53[i] = (FAUSTFLOAT)fTempPerm146;
			if (iSlow184 || iSlow186) {
				fTempPerm147 = (fTempPerm138 + fTempPerm142);
			}
			if (iSlow184) {
				fRec104[0] = ((fConst7 * fRec104[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((fTempPerm147 + faustpower<2>((fTempPerm139 + 1.0f)))))))));
				fTempPerm148 = (fSlow183 * fRec104[0]);
			}
			output54[i] = (FAUSTFLOAT)fTempPerm148;
			if (iSlow186) {
				fRec105[0] = ((fConst7 * fRec105[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm147 + faustpower<2>((fTempPerm139 + -1.0f)))))))));
				fTempPerm149 = (fSlow185 * fRec105[0]);
			}
			output55[i] = (FAUSTFLOAT)fTempPerm149;
			if (iSlow198 || iSlow200 || iSlow202 || iSlow204 || iSlow206 || iSlow208) {
				fTempPerm150 = (float)input9[i];
				fTempPerm151 = (float)input10[i];
			}
			if (iSlow198 || iSlow202 || iSlow206 || iSlow208) {
				fTempPerm152 = faustpower<2>(fTempPerm151);
			}
			if (iSlow198 || iSlow200 || iSlow202 || iSlow204 || iSlow206 || iSlow208) {
				fTempPerm153 = (float)input11[i];
			}
			if (iSlow198 || iSlow200 || iSlow202 || iSlow204) {
				fTempPerm154 = faustpower<2>(fTempPerm153);
			}
			if (iSlow198) {
				fRec106[0] = ((fConst7 * fRec106[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow141 * sqrtf(((faustpower<2>((fTempPerm150 + 1.0f)) + fTempPerm152) + fTempPerm154)))))));
				fTempPerm155 = (fSlow197 * fRec106[0]);
			}
			output56[i] = (FAUSTFLOAT)fTempPerm155;
			if (iSlow200 || iSlow204 || iSlow206 || iSlow208) {
				fTempPerm156 = faustpower<2>(fTempPerm150);
			}
			if (iSlow200 || iSlow204) {
				fTempPerm157 = (fTempPerm154 + fTempPerm156);
			}
			if (iSlow200) {
				fRec107[0] = ((fConst7 * fRec107[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow158 * sqrtf((faustpower<2>((fTempPerm151 + 1.0f)) + fTempPerm157)))))));
				fTempPerm158 = (fSlow199 * fRec107[0]);
			}
			output57[i] = (FAUSTFLOAT)fTempPerm158;
			if (iSlow202) {
				fRec108[0] = ((fConst7 * fRec108[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow159 * sqrtf((faustpower<2>((fTempPerm150 + -1.0f)) + (fTempPerm152 + fTempPerm154))))))));
				fTempPerm159 = (fSlow201 * fRec108[0]);
			}
			output58[i] = (FAUSTFLOAT)fTempPerm159;
			if (iSlow204) {
				fRec109[0] = ((fConst7 * fRec109[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((fTempPerm157 + faustpower<2>((fTempPerm151 + -1.0f)))))))));
				fTempPerm160 = (fSlow203 * fRec109[0]);
			}
			output59[i] = (FAUSTFLOAT)fTempPerm160;
			if (iSlow206 || iSlow208) {
				fTempPerm161 = (fTempPerm152 + fTempPerm156);
			}
			if (iSlow206) {
				fRec110[0] = ((fConst7 * fRec110[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((fTempPerm161 + faustpower<2>((fTempPerm153 + 1.0f)))))))));
				fTempPerm162 = (fSlow205 * fRec110[0]);
			}
			output60[i] = (FAUSTFLOAT)fTempPerm162;
			if (iSlow208) {
				fRec111[0] = ((fConst7 * fRec111[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm161 + faustpower<2>((fTempPerm153 + -1.0f)))))))));
				fTempPerm163 = (fSlow207 * fRec111[0]);
			}
			output61[i] = (FAUSTFLOAT)fTempPerm163;
			if (iSlow210 || iSlow212 || iSlow214 || iSlow216 || iSlow218 || iSlow220 || iSlow222) {
				fTempPerm164 = (float)input12[i];
			}
			if (iSlow210 || iSlow212 || iSlow214 || iSlow216 || iSlow218 || iSlow220 || iSlow224) {
				fTempPerm165 = (float)input13[i];
			}
			if (iSlow210 || iSlow214 || iSlow218 || iSlow220) {
				fTempPerm166 = faustpower<2>(fTempPerm165);
			}
			if (iSlow210 || iSlow212 || iSlow214 || iSlow216 || iSlow218 || iSlow220 || iSlow226) {
				fTempPerm167 = (float)input14[i];
			}
			if (iSlow210 || iSlow212 || iSlow214 || iSlow216) {
				fTempPerm168 = faustpower<2>(fTempPerm167);
			}
			if (iSlow210) {
				fRec112[0] = ((fConst7 * fRec112[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow141 * sqrtf(((faustpower<2>((fTempPerm164 + 1.0f)) + fTempPerm166) + fTempPerm168)))))));
				fTempPerm169 = (fSlow209 * fRec112[0]);
			}
			output62[i] = (FAUSTFLOAT)fTempPerm169;
			if (iSlow212 || iSlow216 || iSlow218 || iSlow220) {
				fTempPerm170 = faustpower<2>(fTempPerm164);
			}
			if (iSlow212 || iSlow216) {
				fTempPerm171 = (fTempPerm168 + fTempPerm170);
			}
			if (iSlow212) {
				fRec113[0] = ((fConst7 * fRec113[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow158 * sqrtf((faustpower<2>((fTempPerm165 + 1.0f)) + fTempPerm171)))))));
				fTempPerm172 = (fSlow211 * fRec113[0]);
			}
			output63[i] = (FAUSTFLOAT)fTempPerm172;
			if (iSlow214) {
				fRec114[0] = ((fConst7 * fRec114[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow159 * sqrtf((faustpower<2>((fTempPerm164 + -1.0f)) + (fTempPerm166 + fTempPerm168))))))));
				fTempPerm173 = (fSlow213 * fRec114[0]);
			}
			output64[i] = (FAUSTFLOAT)fTempPerm173;
			if (iSlow216) {
				fRec115[0] = ((fConst7 * fRec115[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((fTempPerm171 + faustpower<2>((fTempPerm165 + -1.0f)))))))));
				fTempPerm174 = (fSlow215 * fRec115[0]);
			}
			output65[i] = (FAUSTFLOAT)fTempPerm174;
			if (iSlow218 || iSlow220) {
				fTempPerm175 = (fTempPerm166 + fTempPerm170);
			}
			if (iSlow218) {
				fRec116[0] = ((fConst7 * fRec116[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((fTempPerm175 + faustpower<2>((fTempPerm167 + 1.0f)))))))));
				fTempPerm176 = (fSlow217 * fRec116[0]);
			}
			output66[i] = (FAUSTFLOAT)fTempPerm176;
			if (iSlow220) {
				fRec117[0] = ((fConst7 * fRec117[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm175 + faustpower<2>((fTempPerm167 + -1.0f)))))))));
				fTempPerm177 = (fSlow219 * fRec117[0]);
			}
			output67[i] = (FAUSTFLOAT)fTempPerm177;
			if (iSlow228 || iSlow230 || iSlow232 || iSlow234 || iSlow236 || iSlow238) {
				fTempPerm178 = (float)input15[i];
				fTempPerm179 = (float)input16[i];
			}
			if (iSlow228 || iSlow232 || iSlow236 || iSlow238) {
				fTempPerm180 = faustpower<2>(fTempPerm179);
			}
			if (iSlow228 || iSlow230 || iSlow232 || iSlow234 || iSlow236 || iSlow238) {
				fTempPerm181 = (float)input17[i];
			}
			if (iSlow228 || iSlow230 || iSlow232 || iSlow234) {
				fTempPerm182 = faustpower<2>(fTempPerm181);
			}
			if (iSlow228) {
				fRec118[0] = ((fConst7 * fRec118[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow141 * sqrtf(((faustpower<2>((fTempPerm178 + 1.0f)) + fTempPerm180) + fTempPerm182)))))));
				fTempPerm183 = (fSlow227 * fRec118[0]);
			}
			output68[i] = (FAUSTFLOAT)fTempPerm183;
			if (iSlow230 || iSlow234 || iSlow236 || iSlow238) {
				fTempPerm184 = faustpower<2>(fTempPerm178);
			}
			if (iSlow230 || iSlow234) {
				fTempPerm185 = (fTempPerm182 + fTempPerm184);
			}
			if (iSlow230) {
				fRec119[0] = ((fConst7 * fRec119[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow158 * sqrtf((faustpower<2>((fTempPerm179 + 1.0f)) + fTempPerm185)))))));
				fTempPerm186 = (fSlow229 * fRec119[0]);
			}
			output69[i] = (FAUSTFLOAT)fTempPerm186;
			if (iSlow232) {
				fRec120[0] = ((fConst7 * fRec120[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow159 * sqrtf((faustpower<2>((fTempPerm178 + -1.0f)) + (fTempPerm180 + fTempPerm182))))))));
				fTempPerm187 = (fSlow231 * fRec120[0]);
			}
			output70[i] = (FAUSTFLOAT)fTempPerm187;
			if (iSlow234) {
				fRec121[0] = ((fConst7 * fRec121[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((fTempPerm185 + faustpower<2>((fTempPerm179 + -1.0f)))))))));
				fTempPerm188 = (fSlow233 * fRec121[0]);
			}
			output71[i] = (FAUSTFLOAT)fTempPerm188;
			if (iSlow236 || iSlow238) {
				fTempPerm189 = (fTempPerm180 + fTempPerm184);
			}
			if (iSlow236) {
				fRec122[0] = ((fConst7 * fRec122[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((fTempPerm189 + faustpower<2>((fTempPerm181 + 1.0f)))))))));
				fTempPerm190 = (fSlow235 * fRec122[0]);
			}
			output72[i] = (FAUSTFLOAT)fTempPerm190;
			if (iSlow238) {
				fRec123[0] = ((fConst7 * fRec123[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm189 + faustpower<2>((fTempPerm181 + -1.0f)))))))));
				fTempPerm191 = (fSlow237 * fRec123[0]);
			}
			output73[i] = (FAUSTFLOAT)fTempPerm191;
			if (iSlow39) {
				fTempPerm192 = (fSlow38 * min((float)1, max((float)0, (0 - (0.5f * (fTempPerm36 - (fTempPerm30 + 1.0f)))))));
			}
			output74[i] = (FAUSTFLOAT)fTempPerm192;
			if (iSlow46) {
				fTempPerm193 = (fSlow45 * min((float)1, max((float)0, (0 - (0.5f * (fTempPerm38 - (fTempPerm32 + 1.0f)))))));
			}
			output75[i] = (FAUSTFLOAT)fTempPerm193;
			if (iSlow53) {
				fTempPerm194 = (fSlow52 * min((float)1, max((float)0, (0 - (0.5f * (fTempPerm40 - (fTempPerm34 + 1.0f)))))));
			}
			output76[i] = (FAUSTFLOAT)fTempPerm194;
			if (iSlow41) {
				fTempPerm195 = (fSlow40 * min((float)1, max((float)0, (1.0f - (fTempPerm30 + fTempPerm36)))));
			}
			output77[i] = (FAUSTFLOAT)fTempPerm195;
			if (iSlow48) {
				fTempPerm196 = (fSlow47 * min((float)1, max((float)0, (1.0f - (fTempPerm32 + fTempPerm38)))));
			}
			output78[i] = (FAUSTFLOAT)fTempPerm196;
			if (iSlow55) {
				fTempPerm197 = (fSlow54 * min((float)1, max((float)0, (1.0f - (fTempPerm34 + fTempPerm40)))));
			}
			output79[i] = (FAUSTFLOAT)fTempPerm197;
			if (iSlow188) {
				fTempPerm198 = (fSlow187 * min((float)1, (1.6666666666666665f * max((float)0, ((0.5f * (1.0f - fTempPerm136)) + -0.20000000000000001f)))));
			}
			output80[i] = (FAUSTFLOAT)fTempPerm198;
			if (iSlow192) {
				fTempPerm199 = (fSlow191 * min((float)1, (1.6666666666666665f * max((float)0, ((0.5f * (1.0f - fTempPerm137)) + -0.20000000000000001f)))));
			}
			output81[i] = (FAUSTFLOAT)fTempPerm199;
			if (iSlow190) {
				fTempPerm200 = (fSlow189 * fTempPerm136);
			}
			output82[i] = (FAUSTFLOAT)fTempPerm200;
			if (iSlow194) {
				fTempPerm201 = (fSlow193 * fTempPerm137);
			}
			output83[i] = (FAUSTFLOAT)fTempPerm201;
			if (iSlow196) {
				fTempPerm202 = (fSlow195 * fTempPerm139);
			}
			output84[i] = (FAUSTFLOAT)fTempPerm202;
			if (iSlow222) {
				fTempPerm203 = (fSlow221 * fTempPerm164);
			}
			output85[i] = (FAUSTFLOAT)fTempPerm203;
			if (iSlow224) {
				fTempPerm204 = (fSlow223 * fTempPerm165);
			}
			output86[i] = (FAUSTFLOAT)fTempPerm204;
			if (iSlow226) {
				fTempPerm205 = (fSlow225 * fTempPerm167);
			}
			output87[i] = (FAUSTFLOAT)fTempPerm205;
			if (iSlow153) {
				fTempPerm206 = (fSlow152 * fTempPerm108);
			}
			output88[i] = (FAUSTFLOAT)fTempPerm206;
			if (iSlow155) {
				fTempPerm207 = (fSlow154 * fTempPerm109);
			}
			output89[i] = (FAUSTFLOAT)fTempPerm207;
			if (iSlow157) {
				fTempPerm208 = (fSlow156 * fTempPerm111);
			}
			output90[i] = (FAUSTFLOAT)fTempPerm208;
			// post processing
			if (iSlow238) {
				fRec123[1] = fRec123[0];
			}
			if (iSlow236) {
				fRec122[1] = fRec122[0];
			}
			if (iSlow234) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow232) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow230) {
				fRec119[1] = fRec119[0];
			}
			if (iSlow228) {
				fRec118[1] = fRec118[0];
			}
			if (iSlow220) {
				fRec117[1] = fRec117[0];
			}
			if (iSlow218) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow216) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow214) {
				fRec114[1] = fRec114[0];
			}
			if (iSlow212) {
				fRec113[1] = fRec113[0];
			}
			if (iSlow210) {
				fRec112[1] = fRec112[0];
			}
			if (iSlow208) {
				fRec111[1] = fRec111[0];
			}
			if (iSlow206) {
				fRec110[1] = fRec110[0];
			}
			if (iSlow204) {
				fRec109[1] = fRec109[0];
			}
			if (iSlow202) {
				fRec108[1] = fRec108[0];
			}
			if (iSlow200) {
				fRec107[1] = fRec107[0];
			}
			if (iSlow198) {
				fRec106[1] = fRec106[0];
			}
			if (iSlow186) {
				fRec105[1] = fRec105[0];
			}
			if (iSlow184) {
				fRec104[1] = fRec104[0];
			}
			if (iSlow182) {
				fRec103[1] = fRec103[0];
			}
			if (iSlow180) {
				fRec102[1] = fRec102[0];
			}
			if (iSlow178) {
				fRec101[1] = fRec101[0];
			}
			if (iSlow176) {
				fRec100[1] = fRec100[0];
			}
			if (iSlow174) {
				fRec99[1] = fRec99[0];
			}
			if (iSlow172) {
				fRec98[1] = fRec98[0];
			}
			if (iSlow170) {
				fRec97[1] = fRec97[0];
			}
			if (iSlow168) {
				fRec96[1] = fRec96[0];
			}
			if (iSlow166) {
				fRec95[1] = fRec95[0];
			}
			if (iSlow164) {
				fRec94[1] = fRec94[0];
			}
			if (iSlow151) {
				fRec93[1] = fRec93[0];
			}
			if (iSlow149) {
				fRec92[1] = fRec92[0];
			}
			if (iSlow147) {
				fRec91[1] = fRec91[0];
			}
			if (iSlow145) {
				fRec90[1] = fRec90[0];
			}
			if (iSlow143) {
				fRec89[1] = fRec89[0];
			}
			if (iSlow140) {
				fRec88[1] = fRec88[0];
			}
			if (iSlow121) {
				fRec86[1] = fRec86[0];
				fRec87[1] = fRec87[0];
			}
			if (iSlow138) {
				fRec84[1] = fRec84[0];
				fRec85[1] = fRec85[0];
			}
			if (iSlow131) {
				fRec82[1] = fRec82[0];
				fRec83[1] = fRec83[0];
			}
			if (iSlow119) {
				fRec80[1] = fRec80[0];
				fRec81[1] = fRec81[0];
			}
			if (iSlow136) {
				fRec78[1] = fRec78[0];
				fRec79[1] = fRec79[0];
			}
			if (iSlow129) {
				fRec76[1] = fRec76[0];
				fRec77[1] = fRec77[0];
			}
			if (iSlow117) {
				fRec74[1] = fRec74[0];
				fRec75[1] = fRec75[0];
			}
			if (iSlow133) {
				fRec71[1] = fRec71[0];
				fRec72[1] = fRec72[0];
			}
			if (iSlow133 || iSlow136 || iSlow138 || iSlow121) {
				fRec73[1] = fRec73[0];
			}
			if (iSlow126) {
				fRec68[1] = fRec68[0];
				fRec69[1] = fRec69[0];
			}
			if (iSlow126 || iSlow129 || iSlow131 || iSlow121) {
				fRec70[1] = fRec70[0];
			}
			if (iSlow113) {
				fRec65[1] = fRec65[0];
				fRec66[1] = fRec66[0];
			}
			if (iSlow113 || iSlow117 || iSlow119 || iSlow121) {
				fRec67[1] = fRec67[0];
			}
			if (iSlow94) {
				fRec63[1] = fRec63[0];
				fRec64[1] = fRec64[0];
			}
			if (iSlow111) {
				fRec61[1] = fRec61[0];
				fRec62[1] = fRec62[0];
			}
			if (iSlow104) {
				fRec59[1] = fRec59[0];
				fRec60[1] = fRec60[0];
			}
			if (iSlow92) {
				fRec57[1] = fRec57[0];
				fRec58[1] = fRec58[0];
			}
			if (iSlow109) {
				fRec55[1] = fRec55[0];
				fRec56[1] = fRec56[0];
			}
			if (iSlow102) {
				fRec53[1] = fRec53[0];
				fRec54[1] = fRec54[0];
			}
			if (iSlow90) {
				fRec51[1] = fRec51[0];
				fRec52[1] = fRec52[0];
			}
			if (iSlow106) {
				fRec48[1] = fRec48[0];
				fRec49[1] = fRec49[0];
			}
			if (iSlow106 || iSlow109 || iSlow111 || iSlow94) {
				fRec50[1] = fRec50[0];
				fVec26[1] = fVec26[0];
			}
			if (iSlow99) {
				fRec45[1] = fRec45[0];
				fRec46[1] = fRec46[0];
			}
			if (iSlow99 || iSlow102 || iSlow104 || iSlow94) {
				fRec47[1] = fRec47[0];
				fVec25[1] = fVec25[0];
			}
			if (iSlow86) {
				fRec42[1] = fRec42[0];
				fRec43[1] = fRec43[0];
			}
			if (iSlow86 || iSlow90 || iSlow92 || iSlow94) {
				fRec44[1] = fRec44[0];
				fVec24[1] = fVec24[0];
			}
			if (iSlow83) {
				fRec41[1] = fRec41[0];
				fVec23[1] = fVec23[0];
			}
			if (iSlow80) {
				fRec40[1] = fRec40[0];
				fVec22[1] = fVec22[0];
			}
			if (iSlow77) {
				fRec39[1] = fRec39[0];
				fVec21[1] = fVec21[0];
			}
			if (iSlow74) {
				fRec38[1] = fRec38[0];
				fVec20[1] = fVec20[0];
			}
			if (iSlow71) {
				fRec37[1] = fRec37[0];
				fVec19[1] = fVec19[0];
			}
			if (iSlow66) {
				fRec36[1] = fRec36[0];
				fVec18[1] = fVec18[0];
			}
			if (iSlow63 || iSlow53 || iSlow55) {
				fRec35[1] = fRec35[0];
				fVec17[1] = fVec17[0];
			}
			if (iSlow60 || iSlow46 || iSlow48) {
				fRec34[1] = fRec34[0];
				fVec16[1] = fVec16[0];
			}
			if (iSlow57 || iSlow39 || iSlow41) {
				fRec33[1] = fRec33[0];
				fVec15[1] = fVec15[0];
			}
			if (iSlow50 || iSlow53 || iSlow55) {
				fRec32[1] = fRec32[0];
				fVec14[1] = fVec14[0];
			}
			if (iSlow43 || iSlow46 || iSlow48) {
				fRec31[1] = fRec31[0];
				fVec13[1] = fVec13[0];
			}
			if (iSlow33 || iSlow39 || iSlow41) {
				fRec30[1] = fRec30[0];
				fVec12[1] = fVec12[0];
			}
			if (iSlow29) {
				iRec25[1] = iRec25[0];
				fRec29[1] = fRec29[0];
				iRec27[1] = iRec27[0];
				iVec11[1] = iVec11[0];
				fRec28[1] = fRec28[0];
				fVec10[1] = fVec10[0];
			}
			if (iSlow25) {
				iRec20[1] = iRec20[0];
				fRec24[1] = fRec24[0];
				iRec22[1] = iRec22[0];
				iVec9[1] = iVec9[0];
				fRec23[1] = fRec23[0];
				fVec8[1] = fVec8[0];
			}
			if (iSlow21) {
				iRec15[1] = iRec15[0];
				fRec19[1] = fRec19[0];
				iRec17[1] = iRec17[0];
				iVec7[1] = iVec7[0];
				fRec18[1] = fRec18[0];
				fVec6[1] = fVec6[0];
			}
			if (iSlow17) {
				iRec10[1] = iRec10[0];
				fRec14[1] = fRec14[0];
				iRec12[1] = iRec12[0];
				iVec5[1] = iVec5[0];
				fRec13[1] = fRec13[0];
				fVec4[1] = fVec4[0];
			}
			if (iSlow13) {
				iRec5[1] = iRec5[0];
				fRec9[1] = fRec9[0];
				iRec7[1] = iRec7[0];
				iVec3[1] = iVec3[0];
				fRec8[1] = fRec8[0];
				fVec2[1] = fVec2[0];
			}
			if (iSlow1) {
				iRec0[1] = iRec0[0];
				fRec4[1] = fRec4[0];
				iRec2[1] = iRec2[0];
				iVec1[1] = iVec1[0];
				fRec3[1] = fRec3[0];
				fVec0[1] = fVec0[0];
			}
		}
	}
};



//**************************************************************
// Polyphony
//**************************************************************

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __faust_poly_engine__
#define __faust_poly_engine__

#include <math.h>
#include <stdio.h>
#include <string.h>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __audio__
#define __audio__

#include <set>
#include <utility>

class dsp;

typedef void (* shutdown_callback)(const char* message, void* arg);

typedef void (* compute_callback)(void* arg);

class audio {
    
    protected:
    
        shutdown_callback fShutdown;    // Shutdown callback
        void* fShutdownArg;             // Shutdown callback data
    
        std::set<std::pair<compute_callback, void*> > fComputeCallbackList;
    
    public:
    
        audio():fShutdown(nullptr), fShutdownArg(nullptr) {}
        virtual ~audio() {}

        virtual bool init(const char* name, dsp* dsp) = 0;
    
        virtual bool start() = 0;
        virtual void stop() = 0;
    
        void setShutdownCallback(shutdown_callback cb, void* arg)
        {
            fShutdown = cb;
            fShutdownArg = arg;
        }
    
        void addControlCallback(compute_callback cb, void* arg)
        {
            fComputeCallbackList.insert(std::make_pair(cb, arg));
        }
        bool removeControlCallback(compute_callback cb, void* arg)
        {
            return (fComputeCallbackList.erase(std::make_pair(cb, arg)) == 1);
        }
        void runControlCallbacks()
        {
            for (auto& it : fComputeCallbackList) {
                it.first(it.second);
            }
        }
    
        virtual int getBufferSize() = 0;
        virtual int getSampleRate() = 0;

        virtual int getNumInputs() = 0;
        virtual int getNumOutputs() = 0;

        virtual float getCPULoad() { return 0.f; }
};
					
#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

template <typename REAL>
class JSONUIAux : public PathBuilder, public Meta, public UI
{

    protected:
    
        std::stringstream fJSON;
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fVersion;           // Compiler version
        std::string fCompileOptions;    // Compilation options
        std::vector<std::string> fLibraryList;
        std::vector<std::string> fIncludePathnames;
        std::string fName;
        std::string fFileName;
        std::string fExpandedCode;
        std::string fSHAKey;
        std::string fDSPSize;           // In bytes
        std::map<std::string, int> fPathTable;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::stringstream dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    // add escape for single quote
                    case '\'':
                        dst << "\\'";
                        break;
                    default:
                        dst << src[i];
                        break;
                }
            }
            return dst.str();
        }
    
        std::string getAddressIndex(const std::string& path)
        {
            if (fPathTable.find(path) != fPathTable.end()) {
                std::stringstream num; num << fPathTable[path];
                return num.str();
            } else {
                return "-1";
            }
        }
      
     public:
     
        JSONUIAux(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  const std::string& size,
                  const std::map<std::string, int>& path_table)
        {
            init(name, filename, inputs, outputs, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table);
        }

        JSONUIAux(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), "", std::map<std::string, int>());
        }

        JSONUIAux(int inputs, int outputs)
        {
            init("", "", inputs, outputs, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), "", std::map<std::string, int>());
        }
        
        JSONUIAux()
        {
            init("", "", -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), "", std::map<std::string, int>());
        }
 
        virtual ~JSONUIAux() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  const std::string& size,
                  const std::map<std::string, int>& path_table)
        {
            fTab = 1;
            
            // Start Meta generation
            fMeta.str("");
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            fUI.str("");
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fFileName = filename;
            fInputs = inputs;
            fOutputs = outputs;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            fControlsLevel.push_back(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab + 1);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            fControlsLevel.pop_back();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
  
        virtual void addGenericButton(const char* label, const char* name)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab + 1, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab + 1, fUI); fUI << "\"index\": \"" << getAddressIndex(path) << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab + 1, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab + 1, false);
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, REAL init, REAL min, REAL max, REAL step)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab + 1, fUI); fUI << "\"index\": \"" << getAddressIndex(path) << "\",";
            }
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"init\": \"" << init << "\",";
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\",";
            tab(fTab + 1, fUI); fUI << "\"step\": \"" << step << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, REAL min, REAL max) 
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab + 1, fUI); fUI << "\"index\": \"" << getAddressIndex(path) << "\",";
            }
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addSoundfile(const char* label, const char* url, Soundfile** zone)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab + 1, fUI); fUI << "\"index\": \"" << getAddressIndex(path) << "\"";
            }
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        // -- metadata declarations

        virtual void declare(REAL* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            // fName found in metadata
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            // fFileName found in metadata
            if ((strcmp(key, "filename") == 0) && (fFileName == "")) fFileName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            fJSON << "{";
            fTab += 1;
            tab(fTab, fJSON); fJSON << "\"name\": \"" << fName << "\",";
            tab(fTab, fJSON); fJSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, fJSON); fJSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, fJSON); fJSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, fJSON);
                fJSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    fJSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) fJSON << ",";
                }
                fJSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, fJSON);
                fJSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    fJSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) fJSON << ",";
                }
                fJSON << "],";
            }
            if (fDSPSize != "") { tab(fTab, fJSON); fJSON << "\"size\": \"" << fDSPSize << "\","; }
            if (fSHAKey != "") { tab(fTab, fJSON); fJSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, fJSON); fJSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, fJSON); fJSON << "\"inputs\": \"" << fInputs << "\","; 
            tab(fTab, fJSON); fJSON << "\"outputs\": \"" << fOutputs << "\",";
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                fJSON << fMeta.str() << fUI.str();
            } else {
                fJSON << fUI.str();
            }
            tab(fTab, fJSON); fJSON << "}";
            return (flat) ? flatten(fJSON.str()) : fJSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

class JSONUI : public JSONUIAux<FAUSTFLOAT>
{
    public :
    
        JSONUI(const std::string& name,
               const std::string& filename,
               int inputs,
               int outputs,
               const std::string& sha_key,
               const std::string& dsp_code,
               const std::string& version,
               const std::string& compile_options,
               const std::vector<std::string>& library_list,
               const std::vector<std::string>& include_pathnames,
               const std::string& size,
               const std::map<std::string, int>& path_table):
        JSONUIAux<FAUSTFLOAT>(name, filename,
                              inputs, outputs,
                              sha_key, dsp_code,
                              version, compile_options,
                              library_list, include_pathnames,
                              size, path_table)
        {}
        
        JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
        JSONUIAux<FAUSTFLOAT>(name, filename, inputs, outputs)
        {}
        
        JSONUI(int inputs, int outputs):JSONUIAux<FAUSTFLOAT>(inputs, outputs)
        {}
        
        JSONUI():JSONUIAux<FAUSTFLOAT>()
        {}
    
        virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef API_UI_H
#define API_UI_H

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
							    (GRAME, © 2015)

Set of conversion objects used to map user interface values (for example a gui slider
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter

-- ZoneReader are used to implement screencolor metadata

ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) = 0;
        virtual double faust2ui(double x) = 0;
};

//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{

    private:

        Interpolator fUI2F;
        Interpolator fF2UI;

    public:

        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}

        LinearValueConverter() :
            fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) {	return fUI2F(x); }
        virtual double faust2ui(double x) {	return fF2UI(x); }

};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
        LinearValueConverter(umin, umax, log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) 	{ return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x)	{ return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, exp(fmin), exp(fmax))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::exp(x)); }

};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {

    protected:

        bool fActive;

    public:

        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}

        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;

        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmin,fmid,fmax);
            fF2A = Interpolator3pt(fmin,fmid,fmax,amin,amid,amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmax,fmid,fmin);
            fF2A = Interpolator3pt(fmin,fmid,fmax,amax,amid,amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotone function
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmin,fmax,fmin);
            fF2A = Interpolator(fmin,fmax,amin,amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotone function
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmax,fmin,fmax);
            fF2A = Interpolator(fmin,fmax,amin,amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    private:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* valueConverter) : ZoneControl(zone), fValueConverter(valueConverter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        void update(double v) { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            if (fZone != 0) {
                return (int)fInterpolator(*fZone);
            } else {
                return 127;
            }
        }

};

#endif

class APIUI : public PathBuilder, public Meta, public UI
{
    public:
    
        enum ItemType { kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph };
  
    protected:
    
        enum { kLin = 0, kLog = 1, kExp = 2 };
    
        int fNumParameters;
        std::vector<std::string> fPaths;
        std::vector<std::string> fLabels;
        std::map<std::string, int> fPathMap;
        std::map<std::string, int> fLabelMap;
        std::vector<ValueConverter*> fConversion;
        std::vector<FAUSTFLOAT*> fZone;
        std::vector<FAUSTFLOAT> fInit;
        std::vector<FAUSTFLOAT> fMin;
        std::vector<FAUSTFLOAT> fMax;
        std::vector<FAUSTFLOAT> fStep;
        std::vector<ItemType> fItemType;
        std::vector<std::map<std::string, std::string> > fMetaData;
        std::vector<ZoneControl*> fAcc[3];
        std::vector<ZoneControl*> fGyr[3];

        // Screen color control
        // "...[screencolor:red]..." etc.
        bool fHasScreenControl;      // true if control screen color metadata
        ZoneReader* fRedReader;
        ZoneReader* fGreenReader;
        ZoneReader* fBlueReader;

        // Current values controlled by metadata
        std::string fCurrentUnit;
        int fCurrentScale;
        std::string fCurrentAcc;
        std::string fCurrentGyr;
        std::string fCurrentColor;
        std::string fCurrentTooltip;
        std::map<std::string, std::string> fCurrentMetadata;
    
        // Add a generic parameter
        virtual void addParameter(const char* label,
                                FAUSTFLOAT* zone,
                                FAUSTFLOAT init,
                                FAUSTFLOAT min,
                                FAUSTFLOAT max,
                                FAUSTFLOAT step,
                                ItemType type)
        {
            std::string path = buildPath(label);
            fPathMap[path] = fLabelMap[label] = fNumParameters++;
            fPaths.push_back(path);
            fLabels.push_back(label);
            fZone.push_back(zone);
            fInit.push_back(init);
            fMin.push_back(min);
            fMax.push_back(max);
            fStep.push_back(step);
            fItemType.push_back(type);
            
            // handle scale metadata
            switch (fCurrentScale) {
                case kLin:
                    fConversion.push_back(new LinearValueConverter(0, 1, min, max));
                    break;
                case kLog:
                    fConversion.push_back(new LogValueConverter(0, 1, min, max));
                    break;
                case kExp: fConversion.push_back(new ExpValueConverter(0, 1, min, max));
                    break;
            }
            fCurrentScale = kLin;
            
            if (fCurrentAcc.size() > 0 && fCurrentGyr.size() > 0) {
                std::cerr << "warning : 'acc' and 'gyr' metadata used for the same " << label << " parameter !!\n";
            }

            // handle acc metadata "...[acc : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentAcc.size() > 0) {
                std::istringstream iss(fCurrentAcc);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fAcc[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    std::cerr << "incorrect acc metadata : " << fCurrentAcc << std::endl;
                }
                fCurrentAcc = "";
            }
       
            // handle gyr metadata "...[gyr : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentGyr.size() > 0) {
                std::istringstream iss(fCurrentGyr);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fGyr[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    std::cerr << "incorrect gyr metadata : " << fCurrentGyr << std::endl;
                }
                fCurrentGyr = "";
            }
        
            // handle screencolor metadata "...[screencolor:red|green|blue|white]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == 0)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == 0)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == 0) && (fGreenReader == 0) && (fBlueReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    std::cerr << "incorrect screencolor metadata : " << fCurrentColor << std::endl;
                }
            }
            fCurrentColor = "";
            
            fMetaData.push_back(fCurrentMetadata);
            fCurrentMetadata.clear();
        }

        int getZoneIndex(std::vector<ZoneControl*>* table, int p, int val)
        {
            FAUSTFLOAT* zone = fZone[p];
            for (size_t i = 0; i < table[val].size(); i++) {
                if (zone == table[val][i]->getZone()) return i;
            }
            return -1;
        }
    
        void setConverter(std::vector<ZoneControl*>* table, int p, int val, int curve, double amin, double amid, double amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            // Deactivates everywhere..
            if (id1 != -1) table[0][id1]->setActive(false);
            if (id2 != -1) table[1][id2]->setActive(false);
            if (id3 != -1) table[2][id3]->setActive(false);
            
            if (val == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getZoneIndex(table, p, val);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                    table[val][id4]->setMappingValues(curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]);
                    table[val][id4]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fZone[p];
                    table[val].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]));
                }
            }
        }
    
        void getConverter(std::vector<ZoneControl*>* table, int p, int& val, int& curve, double& amin, double& amid, double& amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            if (id1 != -1) {
                val = 0;
                curve = table[val][id1]->getCurve();
                table[val][id1]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                val = 1;
                curve = table[val][id2]->getCurve();
                table[val][id2]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                val = 2;
                curve = table[val][id3]->getCurve();
                table[val][id3]->getMappingValues(amin, amid, amax);
            } else {
                val = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }

     public:
    
        enum Type { kAcc = 0, kGyr = 1, kNoType };
   
        APIUI() : fNumParameters(0), fHasScreenControl(false), fRedReader(0), fGreenReader(0), fBlueReader(0), fCurrentScale(kLin)
        {}

        virtual ~APIUI()
        {
            std::vector<ValueConverter*>::iterator it1;
            for (it1 = fConversion.begin(); it1 != fConversion.end(); it1++) {
                delete(*it1);
            }

            std::vector<ZoneControl*>::iterator it2;
            for (int i = 0; i < 3; i++) {
                for (it2 = fAcc[i].begin(); it2 != fAcc[i].end(); it2++) {
                    delete(*it2);
                }
                for (it2 = fGyr[i].begin(); it2 != fGyr[i].end(); it2++) {
                    delete(*it2);
                }
            }
            
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }
    
        // -- widget's layouts

        virtual void openTabBox(const char* label)          { fControlsLevel.push_back(label); }
        virtual void openHorizontalBox(const char* label)   { fControlsLevel.push_back(label); }
        virtual void openVerticalBox(const char* label)     { fControlsLevel.push_back(label); }
        virtual void closeBox()                             { fControlsLevel.pop_back(); }

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kButton);
        }

        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kCheckButton);
        }

        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kVSlider);
        }

        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kHSlider);
        }

        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kNumEntry);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0, kHBargraph);
        }

        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0, kVBargraph);
        }
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            // Keep matadata
            fCurrentMetadata[key] = val;
            
            if (strcmp(key, "scale") == 0) {
                if (strcmp(val, "log") == 0) {
                    fCurrentScale = kLog;
                } else if (strcmp(val, "exp") == 0) {
                    fCurrentScale = kExp;
                } else {
                    fCurrentScale = kLin;
                }
            } else if (strcmp(key, "unit") == 0) {
                fCurrentUnit = val;
            } else if (strcmp(key, "acc") == 0) {
                fCurrentAcc = val;
            } else if (strcmp(key, "gyr") == 0) {
                fCurrentGyr = val;
            } else if (strcmp(key, "screencolor") == 0) {
                fCurrentColor = val; // val = "red", "green", "blue" or "white"
            } else if (strcmp(key, "tooltip") == 0) {
                fCurrentTooltip = val;
            }
        }

        virtual void declare(const char* key, const char* val)
        {}

		//-------------------------------------------------------------------------------
		// Simple API part
		//-------------------------------------------------------------------------------
		int getParamsCount() { return fNumParameters; }
        int getParamIndex(const char* path)
        {
            if (fPathMap.find(path) != fPathMap.end()) {
                return fPathMap[path];
            } else if (fLabelMap.find(path) != fLabelMap.end()) {
                return fLabelMap[path];
            } else {
                return -1;
            }
        }
        const char* getParamAddress(int p) { return fPaths[p].c_str(); }
        const char* getParamLabel(int p) { return fLabels[p].c_str(); }
        std::map<const char*, const char*> getMetadata(int p)
        {
            std::map<const char*, const char*> res;
            std::map<std::string, std::string> metadata = fMetaData[p];
            std::map<std::string, std::string>::iterator it;
            for (it = metadata.begin(); it != metadata.end(); ++it) {
                res[(*it).first.c_str()] = (*it).second.c_str();
            }
            return res;
        }

        const char* getMetadata(int p, const char* key)
        {
            return (fMetaData[p].find(key) != fMetaData[p].end()) ? fMetaData[p][key].c_str() : "";
        }
        FAUSTFLOAT getParamMin(int p) { return fMin[p]; }
        FAUSTFLOAT getParamMax(int p) { return fMax[p]; }
        FAUSTFLOAT getParamStep(int p) { return fStep[p]; }
        FAUSTFLOAT getParamInit(int p) { return fInit[p]; }

        FAUSTFLOAT* getParamZone(int p) { return fZone[p]; }
        FAUSTFLOAT getParamValue(int p) { return *fZone[p]; }
        void setParamValue(int p, FAUSTFLOAT v) { *fZone[p] = v; }

        double getParamRatio(int p) { return fConversion[p]->faust2ui(*fZone[p]); }
        void setParamRatio(int p, double r) { *fZone[p] = fConversion[p]->ui2faust(r); }

        double value2ratio(int p, double r)	{ return fConversion[p]->faust2ui(r); }
        double ratio2value(int p, double r)	{ return fConversion[p]->ui2faust(r); }
    
        /**
         * Return the control type (kAcc, kGyr, or -1) for a given parameter
         *
         * @param p - the UI parameter index
         *
         * @return the type
         */
        Type getParamType(int p)
        {
            if (p >= 0) {
                if (getZoneIndex(fAcc, p, 0) != -1
                    || getZoneIndex(fAcc, p, 1) != -1
                    || getZoneIndex(fAcc, p, 2) != -1) {
                    return kAcc;
                } else if (getZoneIndex(fGyr, p, 0) != -1
                           || getZoneIndex(fGyr, p, 1) != -1
                           || getZoneIndex(fGyr, p, 2) != -1) {
                    return kGyr;
                }
            }
            return kNoType;
        }
    
        /**
         * Return the Item type (kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph) for a given parameter
         *
         * @param p - the UI parameter index
         *
         * @return the Item type
         */
        ItemType getParamItemType(int p)
        {
            return fItemType[p];
        }
   
        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant float* zones.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @param value - the new value
         *
         */
        void propagateAcc(int acc, double value)
        {
            for (size_t i = 0; i < fAcc[acc].size(); i++) {
                fAcc[acc][i]->update(value);
            }
        }
    
        /**
         * Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setAccConverter(int p, int acc, int curve, double amin, double amid, double amax)
        {
            setConverter(fAcc, p, acc, curve, amin, amid, amax);
        }
    
        /**
         * Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setGyrConverter(int p, int gyr, int curve, double amin, double amid, double amax)
        {
             setConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
    
        /**
         * Used to edit accelerometer curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - the acc value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getAccConverter(int p, int& acc, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fAcc, p, acc, curve, amin, amid, amax);
        }

        /**
         * Used to edit gyroscope curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param gyr - the gyr value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getGyrConverter(int p, int& gyr, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
    
        /**
         * Set a new value coming from an gyroscope, propagate it to all relevant float* zones.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param value - the new value
         *
         */
        void propagateGyr(int gyr, double value)
        {
            for (size_t i = 0; i < fGyr[gyr].size(); i++) {
                fGyr[gyr][i]->update(value);
            }
        }
   
        // getScreenColor() : -1 means no screen color control (no screencolor metadata found)
        // otherwise return 0x00RRGGBB a ready to use color
        int getScreenColor()
        {
            if (fHasScreenControl) {
                int r = (fRedReader) ? fRedReader->getValue() : 0;
                int g = (fGreenReader) ? fGreenReader->getValue() : 0;
                int b = (fBlueReader) ? fBlueReader->getValue() : 0;
                return (r<<16) | (g<<8) | b;
            } else {
                return -1;
            }
        }

};

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <cmath>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/*******************************************************************************
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 *******************************************************************************/

class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 127)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return 0; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {

            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7

        };

        enum MidiCtrl {

            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120

        };
};

/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 ****************************************************/

class midi_handler : public midi {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
        
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->clock(time);
                }
            } else if (type == MIDI_START) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->startSync(time);
                }
            } else if (type == MIDI_STOP) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->stopSync(time);
                }
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->progChange(time, channel, data1);
                }
            } else if (type == MIDI_AFTERTOUCH) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->chanPress(time, channel, data1);
                }
            }
        }

        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF || ((type == MIDI_NOTE_ON) && (data2 == 0))) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOff(time, channel, data1, data2);
                }
            } else if (type == MIDI_NOTE_ON) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            } else if (type == MIDI_CONTROL_CHANGE) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            } else if (type == MIDI_PITCH_BEND) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
                }
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyPress(time, channel, data1, data2);
                }
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->sysEx(time, message);
                }
            }
        }

};

//-------------------------------
// For timestamped MIDI messages
//-------------------------------

struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

#endif // __midi__

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/*****************************************************************************
* Helper code for MIDI meta and polyphonic 'nvoices' parsing
******************************************************************************/

struct MidiMeta : public Meta, public std::map<std::string, std::string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        if (this->find(key) != this->end()) {
            return (*this)[key];
        } else {
            return def;
        }
    }
    
    static void analyse(dsp* tmp_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        tmp_dsp->buildUserInterface(&jsonui);
        std::string json = jsonui.JSON();
        midi_sync = ((json.find("midi") != std::string::npos) &&
                     ((json.find("start") != std::string::npos) ||
                      (json.find("stop") != std::string::npos) ||
                      (json.find("clock") != std::string::npos) ||
                      (json.find("timestamp") != std::string::npos)));
    
    #if defined(NVOICES) && NVOICES!=NUM_VOICES
        nvoices = NVOICES;
    #else
        MidiMeta meta;
        tmp_dsp->metadata(&meta);
        std::string numVoices = meta.get("nvoices", "0");
        nvoices = std::atoi(numVoices.c_str());
        if (nvoices < 0) nvoices = 0;
    #endif
    }
};

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data is handled.
 ******************************************************************************/

class uiMidi {
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        
    public:
        
        uiMidi(midi* midi_out, bool input):fMidiOut(midi_out), fInputCtrl(input)
        {}
        virtual ~uiMidi()
        {}
    
};

/*****************************************************************************
 * Base class for MIDI aware UI items
 ******************************************************************************/

class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidi(midi_out, input), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/*****************************************************************************
 * Base class for MIDI aware UI items with timestamp support
 ******************************************************************************/

class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidi(midi_out, input), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

//-------------
// MIDI sync
//-------------

class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->startSync(0);
            }
        }
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stopSync(0);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
};

class uiMidiClock : public uiMidiTimedItem
{

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
    
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }

};

//----------------------
// Standard MIDI events
//----------------------

class uiMidiProgChange : public uiMidiTimedItem
{
    
    private:
        
        int fPgm;
  
    public:
    
        uiMidiProgChange(midi* midi_out, int pgm, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fPgm(pgm)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->progChange(0, fPgm);
            }
        }
        
};

class uiMidiChanPress : public uiMidiTimedItem
{
    private:
        
        int fPress;
  
    public:
    
        uiMidiChanPress(midi* midi_out, int press, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fPress(press)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->chanPress(0, fPress);
            }
        }
        
};

class uiMidiCtrlChange : public uiMidiTimedItem
{
    private:
    
        int fCtrl;
        LinearValueConverter fConverter;
 
    public:
    
        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fCtrl(ctrl), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->ctrlChange(0, fCtrl, fConverter.faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
 
};

class uiMidiPitchWheel : public uiMidiTimedItem
{

    private:
    	
		// currently, the range is of pitchwheel if fixed (-2/2 semitones)
        FAUSTFLOAT wheel2bend(float v)
        {
            return std::pow(2.0,(v/16383.0*4-2)/12);
        }

        int bend2wheel(float v)
        {
            return (int)((12*std::log(v)/std::log(2.0)+2)/4*16383);
        }
 
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->pitchWheel(0, bend2wheel(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(wheel2bend(v));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, wheel2bend(v));
            }
        }
 
};

class uiMidiKeyOn : public uiMidiTimedItem
{

    private:
        
        int fKeyOn;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fKeyOn(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOn(0, fKeyOn, fConverter.faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
};

class uiMidiKeyOff : public uiMidiTimedItem
{

    private:
        
        int fKeyOff;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fKeyOff(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOff(0, fKeyOff, fConverter.faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
};

class uiMidiKeyPress : public uiMidiTimedItem
{

    private:
    
        int fKey;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fKey(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyPress(0, fKey, fConverter.faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
};

class MapUI;

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi
{

    protected:
    
        std::map <int, std::vector<uiMidiCtrlChange*> > fCtrlChangeTable;
        std::map <int, std::vector<uiMidiProgChange*> > fProgChangeTable;
        std::map <int, std::vector<uiMidiChanPress*> >  fChanPressTable;
        std::map <int, std::vector<uiMidiKeyOn*> >      fKeyOnTable;
        std::map <int, std::vector<uiMidiKeyOff*> >     fKeyOffTable;
        std::map <int, std::vector<uiMidiKeyOn*> >      fKeyTable;
        std::map <int, std::vector<uiMidiKeyPress*> >   fKeyPressTable;
        std::vector<uiMidiPitchWheel*>                  fPitchWheelTable;
        
        std::vector<uiMidiStart*>   fStartTable;
        std::vector<uiMidiStop*>    fStopTable;
        std::vector<uiMidiClock*>   fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiHandler, num, this, zone, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &num) == 1) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiHandler, num, this, zone, input));
                        } else if (fMetaAux[i].second == "pitchwheel" || fMetaAux[i].second == "pitchbend") {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, input));
                        // MIDI sync
                        } else if (fMetaAux[i].second == "start") {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "stop") {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "clock") {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        // Explicit metadata to activate 'timestamp' mode
                        } else if (fMetaAux[i].second == "timestamp") {
                            fTimeStamp = true;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }

    public:
    
        MidiUI():fMidiHandler(NULL), fDelete(false), fTimeStamp(false)
        {}

        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            fDelete = delete_handler;
        }
 
        virtual ~MidiUI() 
        { 
            fMidiHandler->removeMidiIn(this);
            if (fDelete) delete fMidiHandler;
        }
        
        bool run() { return fMidiHandler->startMidi(); }
        void stop() { fMidiHandler->stopMidi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API 
        
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            if (fKeyOnTable.find(note) != fKeyOnTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fKeyOnTable[note].size(); i++) {
                        fKeyOnTable[note][i]->modifyZone(date, FAUSTFLOAT(velocity));
                    }
                } else {
                    for (unsigned int i = 0; i < fKeyOnTable[note].size(); i++) {
                        fKeyOnTable[note][i]->modifyZone(FAUSTFLOAT(velocity));
                    }
                }
            }
            // If note is in fKeyTable, handle it as a keyOn
            if (fKeyTable.find(note) != fKeyTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fKeyTable[note].size(); i++) {
                        fKeyTable[note][i]->modifyZone(date, FAUSTFLOAT(velocity));
                    }
                } else {
                    for (unsigned int i = 0; i < fKeyTable[note].size(); i++) {
                        fKeyTable[note][i]->modifyZone(FAUSTFLOAT(velocity));
                    }
                }
            }
            return 0;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            if (fKeyOffTable.find(note) != fKeyOffTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fKeyOffTable[note].size(); i++) {
                        fKeyOffTable[note][i]->modifyZone(date, FAUSTFLOAT(velocity));
                    }
                } else {
                    for (unsigned int i = 0; i < fKeyOffTable[note].size(); i++) {
                        fKeyOffTable[note][i]->modifyZone(FAUSTFLOAT(velocity));
                    }
                }
            }
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            if (fKeyTable.find(note) != fKeyTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fKeyTable[note].size(); i++) {
                        fKeyTable[note][i]->modifyZone(date, 0);
                    }
                } else {
                    for (unsigned int i = 0; i < fKeyTable[note].size(); i++) {
                        fKeyTable[note][i]->modifyZone(0);
                    }
                }
            }
        }
           
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            if (fCtrlChangeTable.find(ctrl) != fCtrlChangeTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fCtrlChangeTable[ctrl].size(); i++) {
                        fCtrlChangeTable[ctrl][i]->modifyZone(date, FAUSTFLOAT(value));
                    }
                } else {
                    for (unsigned int i = 0; i < fCtrlChangeTable[ctrl].size(); i++) {
                        fCtrlChangeTable[ctrl][i]->modifyZone(FAUSTFLOAT(value));
                    }
                }
            }
        }
        
        void progChange(double date, int channel, int pgm)
        {
            if (fProgChangeTable.find(pgm) != fProgChangeTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fProgChangeTable[pgm].size(); i++) {
                        fProgChangeTable[pgm][i]->modifyZone(date, FAUSTFLOAT(1));
                    }
                } else {
                    for (unsigned int i = 0; i < fProgChangeTable[pgm].size(); i++) {
                        fProgChangeTable[pgm][i]->modifyZone(FAUSTFLOAT(1));
                    }
                }
            }
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            if (fTimeStamp) {
                for (unsigned int i = 0; i < fPitchWheelTable.size(); i++) {
                    fPitchWheelTable[i]->modifyZone(date, FAUSTFLOAT(wheel));
                }
            } else {
                for (unsigned int i = 0; i < fPitchWheelTable.size(); i++) {
                    fPitchWheelTable[i]->modifyZone(FAUSTFLOAT(wheel));
                }
            }
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            if (fKeyPressTable.find(pitch) != fKeyPressTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fKeyPressTable[pitch].size(); i++) {
                        fKeyPressTable[pitch][i]->modifyZone(date, FAUSTFLOAT(press));
                    }
                } else {
                    for (unsigned int i = 0; i < fKeyPressTable[pitch].size(); i++) {
                        fKeyPressTable[pitch][i]->modifyZone(FAUSTFLOAT(press));
                    }
                }
            }
        }
        
        void chanPress(double date, int channel, int press)
        {
            if (fChanPressTable.find(press) != fChanPressTable.end()) {
                if (fTimeStamp) {
                    for (unsigned int i = 0; i < fChanPressTable[press].size(); i++) {
                        fChanPressTable[press][i]->modifyZone(date, FAUSTFLOAT(1));
                    }
                } else {
                    for (unsigned int i = 0; i < fChanPressTable[press].size(); i++) {
                        fChanPressTable[press][i]->modifyZone(FAUSTFLOAT(1));
                    }
                }
            } 
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (unsigned int i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (unsigned int i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (unsigned int i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <float.h>
#include <assert.h>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <assert.h>


// Base class and common code for binary combiners

class dsp_binary_combiner : public dsp {
    
    protected:
        
        dsp* fDSP1;
        dsp* fDSP2;
        
     public:
        
        dsp_binary_combiner(dsp* dsp1, dsp* dsp2):fDSP1(dsp1), fDSP2(dsp2)
        {}
        
        virtual ~dsp_binary_combiner()
        {
            delete fDSP1;
            delete fDSP2;
        }
    
        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
        
        virtual void init(int samplingRate)
        {
            fDSP1->init(samplingRate);
            fDSP2->init(samplingRate);
        }
        
        virtual void instanceInit(int samplingRate)
        {
            fDSP1->instanceInit(samplingRate);
            fDSP2->instanceInit(samplingRate);
        }
        
        virtual void instanceConstants(int samplingRate)
        {
            fDSP1->instanceConstants(samplingRate);
            fDSP2->instanceConstants(samplingRate);
        }
        
        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }
        
        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }
    
        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }
 
};

// Combine two 'compatible' DSP in sequence

class dsp_sequencer : public dsp_binary_combiner {
    
    private:
    
        FAUSTFLOAT** fSeqBuffer;
         
    public:
        
        dsp_sequencer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            assert(fDSP1->getNumOutputs() == fDSP2->getNumInputs());
            fSeqBuffer = new FAUSTFLOAT*[fDSP1->getNumOutputs()];
            for (int i = 0; i < fDSP1->getNumOutputs(); i++) {
                fSeqBuffer[i] = new FAUSTFLOAT[buffer_size];
            }
        }
        
        virtual ~dsp_sequencer()
        {
            for (int i = 0; i < fDSP1->getNumOutputs(); i++) {
               delete [] fSeqBuffer[i];
            }
            
            delete [] fSeqBuffer;
        }
               
        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openTabBox("Sequencer");
            ui_interface->openVerticalBox("DSP1");
            fDSP1->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->openVerticalBox("DSP2");
            fDSP2->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->closeBox();
        }
    
        virtual dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone());
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fSeqBuffer);
            fDSP2->compute(count, fSeqBuffer, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
    
};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp_binary_combiner {
    
    private:
        
        FAUSTFLOAT** fInputsDSP2;
        FAUSTFLOAT** fOutputsDSP2;
    
    public:
        
        dsp_parallelizer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fInputsDSP2 = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fOutputsDSP2 = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
        }
        
        virtual ~dsp_parallelizer()
        {
            delete [] fInputsDSP2;
            delete [] fOutputsDSP2;
        }
               
        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openTabBox("Parallelizer");
            ui_interface->openVerticalBox("DSP1");
            fDSP1->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->openVerticalBox("DSP2");
            fDSP2->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->closeBox();
        }
    
        virtual dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone());
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);
            
            // Shift inputs/outputs channels for fDSP2
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                fInputsDSP2[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                fOutputsDSP2[chan] = outputs[fDSP1->getNumOutputs() + chan];
            }
            
            fDSP2->compute(count, fInputsDSP2, fOutputsDSP2);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
    
};

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>


/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            do {
                if ((*it).second == zone) return (*it).first;
            }
            while (it++ != fPathZoneMap.end());
            return "";
        }
};

#endif // FAUST_MAPUI_H
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>


//----------------------------------------------------------------
//  Proxy dsp definition created from the DSP JSON description
//  This class allows a 'proxy' dsp to control a real dsp 
//  possibly running somewhere else.
//----------------------------------------------------------------

class proxy_dsp : public dsp {

    private:
    
        int fSamplingFreq;
        JSONUIDecoder* fDecoder;
        
    public:
    
        proxy_dsp(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSamplingFreq = -1;
        }
          
        proxy_dsp(dsp* dsp)
        {
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            fSamplingFreq = dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
       
        virtual int getNumInputs() 	{ return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy dsp 
        virtual void init(int samplingRate)
        {
            instanceInit(samplingRate);
        }
        virtual void instanceInit(int samplingRate)
        {
            instanceConstants(samplingRate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int samplingRate) { fSamplingFreq = samplingRate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSamplingFreq; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif

#define kActiveVoice      0
#define kFreeVoice        -1
#define kReleaseVoice     -2
#define kNoVoice          -3

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

// endsWith(<str>,<end>) : returns true if <str> ends with <end>

static bool endsWith(std::string const& str, std::string const& end)
{
    size_t l1 = str.length();
    size_t l2 = end.length();
    return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
}

static double midiToFreq(double note)
{
    return 440.0 * std::pow(2.0, (note-69.0)/12.0);
}

/**
 * Allows to control zones in a grouped manner.
 */

class GroupUI : public GUI, public PathBuilder
{

    private:

        std::map<std::string, uiGroupItem*> fLabelZoneMap;

        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            if (!endsWith(label, "/gate")
                && !endsWith(label, "/freq")
                && !endsWith(label, "/gain")) {

                // Groups all controller except 'freq', 'gate', and 'gain'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }

        uiCallbackItem* fPanic;

    public:

        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        }
    
        virtual ~GroupUI()
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        }

        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }

        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }

        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }

};

/**
 * One voice of polyphony.
 */

struct dsp_voice : public MapUI, public decorator_dsp {

    int fNote;                          // Playing note actual pitch
    int fDate;                          // KeyOn date
    FAUSTFLOAT fLevel;                  // Last audio block level
    std::vector<std::string> fGatePath; // Paths of 'gate' control
    std::vector<std::string> fGainPath; // Paths of 'gain' control
    std::vector<std::string> fFreqPath; // Paths of 'freq' control
 
    dsp_voice(dsp* dsp):decorator_dsp(dsp)
    {
        dsp->buildUserInterface(this);
        fNote = kFreeVoice;
        fLevel = FAUSTFLOAT(0);
        fDate = 0;
        extractPaths(fGatePath, fFreqPath, fGainPath);
    }
    virtual ~dsp_voice()
    {}

    void extractPaths(std::vector<std::string>& gate, std::vector<std::string>& freq, std::vector<std::string>& gain)
    {
        // Keep gain, freq and gate labels
        std::map<std::string, FAUSTFLOAT*>::iterator it;
        for (it = getMap().begin(); it != getMap().end(); it++) {
            std::string path = (*it).first;
            if (endsWith(path, "/gate")) {
                gate.push_back(path);
            } else if (endsWith(path, "/freq")) {
                freq.push_back(path);
            } else if (endsWith(path, "/gain")) {
                gain.push_back(path);
            }
        }
    }

    // MIDI velocity [0..127]
    void keyOn(int pitch, int velocity, bool trigger)
    {
        keyOn(pitch, float(velocity)/127.f, trigger);
    }

    // Normalized MIDI velocity [0..1]
    void keyOn(int pitch, float velocity, bool trigger)
    {
        for (size_t i = 0; i < fFreqPath.size(); i++) {
            setParamValue(fFreqPath[i], midiToFreq(pitch));
        }
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(1));
        }
        for (size_t i = 0; i < fGainPath.size(); i++) {
            setParamValue(fGainPath[i], velocity);
        }
        
        fNote = pitch;
    }

    void keyOff(bool hard = false)
    {
        // No use of velocity for now...
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        if (hard) {
            // Immediately stop voice
            fNote = kFreeVoice;
        } else {
            // Release voice
            fNote = kReleaseVoice;
        }
    }

};

/**
 * A group of voices.
 */

struct dsp_voice_group {

    GroupUI fGroups;

    std::vector<dsp_voice*> fVoiceTable; // Individual voices
    dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control

    FAUSTFLOAT fPanic;

    bool fVoiceControl;
    bool fGroupControl;

    dsp_voice_group(uiCallback cb, void* arg, bool control, bool group)
        :fGroups(&fPanic, cb, arg),
        fVoiceGroup(0), fPanic(FAUSTFLOAT(0)),
        fVoiceControl(control), fGroupControl(group)
    {}

    virtual ~dsp_voice_group()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            delete fVoiceTable[i];
        }
        delete fVoiceGroup;
    }

    void addVoice(dsp_voice* voice)
    {
        fVoiceTable.push_back(voice);
    }

    void clearVoices()
    {
        fVoiceTable.clear();
    }

    void init()
    {
        // Groups all uiItem for a given path
        fVoiceGroup = new proxy_dsp(fVoiceTable[0]);
        fVoiceGroup->buildUserInterface(&fGroups);
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->buildUserInterface(&fGroups);
        }
    }

    void buildUserInterface(UI* ui_interface)
    {
        if (fVoiceTable.size() > 1) {
            ui_interface->openTabBox("Polyphonic");

            // Grouped voices UI
            ui_interface->openVerticalBox("Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();

            // If not grouped, also add individual voices UI
            if (!fGroupControl) {
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    char buffer[32];
                    snprintf(buffer, 32, ((fVoiceTable.size() < 8) ? "Voice%ld" : "V%ld"), long(i+1));
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }

            ui_interface->closeBox();
        } else {
            fVoiceTable[0]->buildUserInterface(ui_interface);
        }
    }

};

/**
 * Base class for MIDI controllable DSP.
 */

class dsp_poly : public decorator_dsp, public midi {

    public:
    
        dsp_poly(dsp* dsp):decorator_dsp(dsp)
        {}
    
        virtual ~dsp_poly() {}
    
        // Group API
        virtual void setGroup(bool group) = 0;
        virtual bool getGroup() = 0;

};

/**
 * Polyphonic DSP: groups a set of DSP to be played together or triggered by MIDI.
 *
 * All voices are preallocated by cloning the single DSP voice given at creation time.
 * Dynamic voice allocation is done in 'getFreeVoice'
 */

class mydsp2_poly : public dsp_voice_group, public dsp_poly {

    private:

        FAUSTFLOAT** fMixBuffer;
        int fDate;

        FAUSTFLOAT mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer)
        {
            FAUSTFLOAT level = 0;
            for (int i = 0; i < getNumOutputs(); i++) {
                FAUSTFLOAT* mixChannel = mixBuffer[i];
                FAUSTFLOAT* outChannel = outputBuffer[i];
                for (int j = 0; j < count; j++) {
                    level = std::max<FAUSTFLOAT>(level, (FAUSTFLOAT)fabs(outChannel[j]));
                    mixChannel[j] += outChannel[j];
                }
            }
            return level;
        }

        void clearOutput(int count, FAUSTFLOAT** mixBuffer)
        {
            for (int i = 0; i < getNumOutputs(); i++) {
                memset(mixBuffer[i], 0, count * sizeof(FAUSTFLOAT));
            }
        }
    
        int getPlayingVoice(int pitch)
        {
            int voice_playing = kNoVoice;
            int oldest_date_playing = INT_MAX;
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fNote == pitch) {
                    // Keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
            
            return voice_playing;
        }
    
        // Always returns a voice
        int getFreeVoice()
        {
            int voice = kNoVoice;
            
            // Looks for the first available voice
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fNote == kFreeVoice) {
                    voice = int(i);
                    goto result;
                }
            }

            {
                // Otherwise steal one
                int voice_release = kNoVoice;
                int voice_playing = kNoVoice;
                
                int oldest_date_release = INT_MAX;
                int oldest_date_playing = INT_MAX;

                // Scan all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    if (fVoiceTable[i]->fNote == kReleaseVoice) {
                        // Keeps oldest release voice
                        if (fVoiceTable[i]->fDate < oldest_date_release) {
                            oldest_date_release = fVoiceTable[i]->fDate;
                            voice_release = int(i);
                        }
                    } else {
                        // Otherwise keeps oldest playing voice
                        if (fVoiceTable[i]->fDate < oldest_date_playing) {
                            oldest_date_playing = fVoiceTable[i]->fDate;
                            voice_playing = int(i);
                        }
                    }
                }
            
                // Then decide which one to steal
                if (oldest_date_release != INT_MAX) {
                    std::cout << "Steal release voice : voice_date " << fVoiceTable[voice_release]->fDate << " cur_date = " << fDate << " voice = " << voice_release << std::endl;
                    voice = voice_release;
                    goto result;
                } else if (oldest_date_playing != INT_MAX) {
                    std::cout << "Steal playing voice : voice_date " << fVoiceTable[voice_playing]->fDate << " cur_date = " << fDate << " voice = " << voice_playing << std::endl;
                    voice = voice_playing;
                    goto result;
                } else {
                    assert(false);
                    return kNoVoice;
                }
            }
            
        result:
            // So that envelop is always re-initialized
            fVoiceTable[voice]->instanceClear();
            fVoiceTable[voice]->fDate = fDate++;
            fVoiceTable[voice]->fNote = kActiveVoice;
            return voice;
        }

        static void panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<mydsp2_poly*>(arg)->allNotesOff(true);
            }
        }

        bool checkPolyphony()
        {
            if (fVoiceTable.size() > 0) {
                return true;
            } else {
                std::cout << "DSP is not polyphonic...\n";
                return false;
            }
        }

    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be used for one voice. Beware: mydsp2_poly will use and finally delete the pointer.
         * @param nvoices - number of polyphony voices
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
         *                If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *                setGroup/getGroup methods can be used to set/get the group state.
         *
         */
        mydsp2_poly(dsp* dsp,
                   int nvoices,
                   bool control = false,
                   bool group = true)
        : dsp_voice_group(panic, this, control, group), dsp_poly(dsp) // dsp parameter is deallocated by ~dsp_poly
        {
            fDate = 0;

            // Create voices
            assert(nvoices > 0);
            for (int i = 0; i < nvoices; i++) {
                addVoice(new dsp_voice(dsp->clone()));
            }

            // Init audio output buffers
            fMixBuffer = new FAUSTFLOAT*[getNumOutputs()];
            for (int i = 0; i < getNumOutputs(); i++) {
                fMixBuffer[i] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }

            dsp_voice_group::init();
        }

        virtual ~mydsp2_poly()
        {
            for (int i = 0; i < getNumOutputs(); i++) {
                delete[] fMixBuffer[i];
            }
            delete[] fMixBuffer;
        }

        // DSP API
    
        void buildUserInterface(UI* ui_interface)
        {
            dsp_voice_group::buildUserInterface(ui_interface);
        }

        void init(int samplingRate)
        {
            decorator_dsp::init(samplingRate);
            fVoiceGroup->init(samplingRate);
            fPanic = FAUSTFLOAT(0);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->init(samplingRate);
            }
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int samplingRate)
        {
            decorator_dsp::instanceConstants(samplingRate);
            fVoiceGroup->instanceConstants(samplingRate);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceConstants(samplingRate);
            }
        }

        void instanceResetUserInterface()
        {
            decorator_dsp::instanceResetUserInterface();
            fVoiceGroup->instanceResetUserInterface();
            fPanic = FAUSTFLOAT(0);
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceResetUserInterface();
            }
        }

        void instanceClear()
        {
            decorator_dsp::instanceClear();
            fVoiceGroup->instanceClear();
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceClear();
            }
        }

        virtual mydsp2_poly* clone()
        {
            return new mydsp2_poly(fDSP->clone(), int(fVoiceTable.size()), fVoiceControl, fGroupControl);
        }

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= MIX_BUFFER_SIZE);

            // First clear the outputs
            clearOutput(count, outputs);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fNote != kFreeVoice) {
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixVoice(count, fMixBuffer, outputs);
                        // Check the level to possibly set the voice in kFreeVoice again
                        if ((voice->fLevel < VOICE_STOP_LEVEL) && (voice->fNote == kReleaseVoice)) {
                            voice->fNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, outputs);
                }
            }
        }

        void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        // Terminate all active voices, gently or immediately (depending of 'hard' value)
        void allNotesOff(bool hard = false)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->keyOff(hard);
            }
        }

        // Additional polyphonic API
        MapUI* newVoice()
        {
            return fVoiceTable[getFreeVoice()];
        }

        void deleteVoice(MapUI* voice)
        {
            std::vector<dsp_voice*>::iterator it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                (*it)->keyOff();
            } else {
                std::cout << "Voice not found\n";
            }
        }
    
        void setGroup(bool group) { fGroupControl = group; }
        bool getGroup() { return fGroupControl; }

        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getFreeVoice();
                fVoiceTable[voice]->keyOn(pitch, velocity, true);
                return fVoiceTable[voice];
            } else {
                return 0;
            }
        }

        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getPlayingVoice(pitch);
                if (voice != kNoVoice) {
                    fVoiceTable[voice]->keyOff();
                } else {
                    std::cout << "Playing pitch = " << pitch << " not found\n";
                }
            }
        }

        void pitchWheel(int channel, int wheel)
        {}

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

        void progChange(int channel, int pgm)
        {}

        void keyPress(int channel, int pitch, int press)
        {}

        void chanPress(int channel, int press)
        {}

        void ctrlChange14bits(int channel, int ctrl, int value)
        {}

};

static std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    std::string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

/**
 * Polyphonic DSP with an integrated effect. fPolyDSP will respond to MIDI messages.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
        
        dsp_poly* fPolyDSP;
        
    public:
        
        dsp_poly_effect(dsp_poly* dsp1, dsp* dsp2)
        :dsp_poly(dsp2), fPolyDSP(dsp1)
        {}
        
        virtual ~dsp_poly_effect()
        {
            // dsp_poly_effect is also a decorator_dsp, which will free fPolyDSP
        }
        
        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return fPolyDSP->keyOn(channel, pitch, velocity);
        }
        void keyOff(int channel, int pitch, int velocity)
        {
            fPolyDSP->keyOff(channel, pitch, velocity);
        }
        void keyPress(int channel, int pitch, int press)
        {
            fPolyDSP->keyPress(channel, pitch, press);
        }
        void chanPress(int channel, int press)
        {
            fPolyDSP->chanPress(channel, press);
        }
        void ctrlChange(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange(channel, ctrl, value);
        }
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange14bits(channel, ctrl, value);
        }
        void pitchWheel(int channel, int wheel)
        {
            fPolyDSP->pitchWheel(channel, wheel);
        }
        void progChange(int channel, int pgm)
        {
            fPolyDSP->progChange(channel, pgm);
        }
        
        // Group API
        void setGroup(bool group)
        {
            fPolyDSP->setGroup(group);
        }
        bool getGroup()
        {
            return fPolyDSP->getGroup();
        }
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */

struct dsp_poly_factory : public dsp_factory {
    
    dsp_factory* fProcessFactory;
    dsp_factory* fEffectFactory;
    
    std::string getEffectCode(const std::string& dsp_content)
    {
        std::stringstream effect_code;
        effect_code << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        effect_code << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        effect_code << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        return effect_code.str();
    }

    dsp_poly_factory(dsp_factory* process_factory = NULL,
                     dsp_factory* effect_factory = NULL):
    fProcessFactory(process_factory)
    ,fEffectFactory(effect_factory)
    {}
    
    virtual ~dsp_poly_factory()
    {}
    
    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    virtual std::string getCompileOptions() { return fProcessFactory->getCompileOptions(); }
    virtual std::vector<std::string> getLibraryList() { return fProcessFactory->getLibraryList(); }
    virtual std::vector<std::string> getIncludePathnames() { return fProcessFactory->getIncludePathnames(); }
    
    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }
    
    /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete'
     *
     * @param nvoices - number of polyphony voices
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group)
    {
        dsp_poly* dsp_poly = new mydsp2_poly(fProcessFactory->createDSPInstance(), nvoices, control, group);
        if (fEffectFactory) {
            // the 'dsp_poly' object has to be controlled with MIDI, so kept separated from new dsp_sequencer(...) object
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, fEffectFactory->createDSPInstance()));
        } else {
            return new dsp_poly_effect(dsp_poly, dsp_poly);
        }
    }
    
    /* Create a new DSP instance, to be deleted with C++ 'delete' */
    dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }
    
};

#endif // __poly_dsp__
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __faust_engine__
#define __faust_engine__

#ifdef __cplusplus
extern "C" {
#endif

    void* create(int, int); // To be implemented
    void destroy(void*);

    bool start(void*);
    void stop(void*);
    
    bool isRunning(void*);

    unsigned long keyOn(void*, int, int);
    int keyOff(void*, int);
    
    void propagateMidi(void*, int, double, int, int, int, int);

    const char* getJSONUI(void*);
    const char* getJSONMeta(void*);

    int getParamsCount(void*);

    void setParamValue(void*, const char*, float);
    float getParamValue(void*, const char*);
    
    void setParamIdValue(void*, int, float);
    float getParamIdValue(void*, int);

    void setVoiceParamValue(void*, const char*, unsigned long, float);
    float getVoiceParamValue(void*, const char*, unsigned long);

    const char* getParamAddress(void*, int);

    void propagateAcc(void*, int, float);
    void setAccConverter(void*, int, int, int, float, float, float);

    void propagateGyr(void*, int, float);
    void setGyrConverter(void*, int, int, int, float, float, float);

    float getCPULoad(void*);
    int getScreenColor(void*);

#ifdef __cplusplus
}
#endif

#endif // __faust_engine__

//**************************************************************
// Mono or polyphonic audio DSP engine
//**************************************************************

using namespace std;

class FaustPolyEngine {
        
    protected:

        mydsp2_poly* fPolyDSP;     // the polyphonic Faust object
        dsp* fFinalDSP;           // the "final" dsp object submitted to the audio driver
    
        APIUI fAPIUI;             // the UI description

        string fJSONUI;
        string fJSONMeta;
        bool fRunning;
        audio* fDriver;

        #if MIDICTRL    
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
        #endif
    
        void init(dsp* mono_dsp, audio* driver, midi_handler* midi)
        {
            bool midi_sync = false;
            int nvoices = 0;
            fRunning = false;
            
            MidiMeta::analyse(mono_dsp, midi_sync, nvoices);
            
            // Getting the UI JSON
            JSONUI jsonui1(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
            mono_dsp->buildUserInterface(&jsonui1);
            fJSONUI = jsonui1.JSON();
            
            // Getting the metadata JSON
            JSONUI jsonui1M(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
            mono_dsp->metadata(&jsonui1M);
            fJSONMeta = jsonui1M.JSON();
            
            if ((fJSONUI.find("keyboard") != std::string::npos
                || fJSONUI.find("poly") != std::string::npos)
                && (nvoices > 0)) {
                
                fPolyDSP = new mydsp2_poly(mono_dsp, nvoices, true);
            #if MIDICTRL 
                fMidiHandler.addMidiIn(fPolyDSP);
            #endif
                if (midi) midi->addMidiIn(fPolyDSP);
                
            #if POLY2
                fFinalDSP = new dsp_sequencer(fPolyDSP, new effect());
            #else
                fFinalDSP = fPolyDSP;
            #endif
                
                // Update JSONs with Poly version
                JSONUI jsonui2(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
                fFinalDSP->buildUserInterface(&jsonui2);
                fJSONUI = jsonui2.JSON();
                JSONUI jsonui2M(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
                fFinalDSP->metadata(&jsonui2M);
                fJSONMeta = jsonui2M.JSON();
                
            } else {
                fPolyDSP = NULL;
                fFinalDSP = mono_dsp;
            }
            
          #if MIDICTRL 
            fFinalDSP->buildUserInterface(&fMidiUI);
          #endif
            fFinalDSP->buildUserInterface(&fAPIUI);
            
            // Retrieving DSP object name
            struct MyMeta : public Meta
            {
                string fName;
                void declare(const char* key, const char* value)
                {
                    if (strcmp(key, "name") == 0) fName = value;
                }
                MyMeta():fName("Dummy"){}
            };
      
            MyMeta meta;
            fFinalDSP->metadata(&meta);
            if (midi) midi->setName(meta.fName);
            
            if (driver) {
                // If driver cannot be initialized, start will fail later on...
                if (!driver->init(meta.fName.c_str(), fFinalDSP)) {
                    delete driver;
                    fDriver = NULL;
                } else {
                    fDriver = driver;
                }
            } else {
                fDriver = NULL;
            }
        }
    
    public:

#if MIDICTRL     
        FaustPolyEngine(dsp* mono_dsp, audio* driver = NULL, midi_handler* midi = NULL):fMidiUI(&fMidiHandler)
#else
        FaustPolyEngine(dsp* mono_dsp, audio* driver = NULL, midi_handler* midi = NULL)
#endif
        {
            init(((mono_dsp) ? mono_dsp : new mydsp2()), driver, midi);
        }
    
        virtual ~FaustPolyEngine()
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
                fRunning = (fDriver) ? fDriver->start() : false;
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
                if (fDriver) fDriver->stop();
            }
        }
    
        void setGroup(bool group) { if (fPolyDSP) fPolyDSP->setGroup(group); }
        bool getGroup() { return (fPolyDSP) ? fPolyDSP->getGroup() : false; }
    
        /*
         * keyOn(pitch, velocity)
         * Instantiates a new polyphonic voice where velocity
         * and pitch are MIDI numbers (0-127). keyOn can only
         * be used if the [style:poly] metadata is used in the
         * Faust code. keyOn will return 0 if the object is not
         * polyphonic and the allocated voice otherwise.
         */
        MapUI* keyOn(int pitch, int velocity)
        {
            if (fPolyDSP) {
                return fPolyDSP->keyOn(0, pitch, velocity); // MapUI* passed to Java as an integer
            } else {
                return 0;
            }
        }

        /*
         * keyOff(pitch)
         * De-instantiates a polyphonic voice where pitch is the
         * MIDI number of the note (0-127). keyOff can only be
         * used if the [style:poly] metadata is used in the Faust
         * code. keyOn will return 0 if the object is not polyphonic
         * and 1 otherwise.
         */
        int keyOff(int pitch, int velocity = 127)
        {
            if (fPolyDSP) {
                fPolyDSP->keyOff(0, pitch, velocity);
                return 1;
            } else {
                return 0;
            }
        }

        /*
         * newVoice()
         * Instantiate a new voice and returns the corresponding mapUI.
         */
        MapUI* newVoice()
        {
            if (fPolyDSP) {
                return fPolyDSP->newVoice();
            } else {
                return 0;
            }
        }

        /*
         * deleteVoice(MapUI* voice)
         * Delete a voice based on its MapUI*.
         */
        int deleteVoice(MapUI* voice)
        {
            if (fPolyDSP) {
                fPolyDSP->deleteVoice(voice);
                return 1;
            } else {
                return 0;
            }
        }

        /*
         * deleteVoice(unsigned long voice)
         * Delete a voice based on its MapUI* casted as a unsigned long.
         */
        int deleteVoice(unsigned long voice)
        {
            return deleteVoice(reinterpret_cast<MapUI*>(voice));
        }
        
        /*
         * allNotesOff()
         * Gently terminates all the active voices.
         */
        void allNotesOff()
        {
            if (fPolyDSP) {
                fPolyDSP->allNotesOff();
            }
        }
    
        /*
         * Propagate MIDI data to the Faust object.
         */
        void propagateMidi(int count, double time, int type, int channel, int data1, int data2)
        {
#if MIDICTRL
            if (count == 3) fMidiHandler.handleData2(time, type, channel, data1, data2);
            else if (count == 2) fMidiHandler.handleData1(time, type, channel, data1);
            else if (count == 1) fMidiHandler.handleSync(time, type);
            GUI::updateAllGuis();
#endif
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
         * Calls the polyphonic or monophonic buildUserInterface with the ui parameter.
         */
        void buildUserInterface(UI* ui_interface)
        {
            fFinalDSP->buildUserInterface(ui_interface);
        }
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fFinalDSP->compute(count, inputs, outputs);
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
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
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
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
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
         * setVoiceParamValue(address, voice, value)
         * Sets the value of the parameter associated with address for
         * the voice. setVoiceParamValue can only be
         * used if the [style:poly] metadata is used in the Faust code.
         */
        void setVoiceParamValue(const char* address, unsigned long voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }

        /*
         * setVoiceParamValue(id, voice, value)
         * Sets the value of the parameter associated with the id for
         * the voice. setVoiceParamValue can only be
         * used if the [style:poly] metadata is used in the Faust code.
         */
        void setVoiceParamValue(int id, unsigned long voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(reinterpret_cast<MapUI*>(voice)->getParamAddress(id), value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code.
         */
        float getVoiceParamValue(const char* address, unsigned long voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(address);
        }

        /*
         * getVoiceParamValue(id, voice)
         * Gets the parameter value associated with the id for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code.
         */
        float getVoiceParamValue(int id, unsigned long voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(reinterpret_cast<MapUI*>(voice)->getParamAddress(id));
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
         * getVoiceParamAddress(id, voice)
         * Returns the address of a parameter for a specific voice 
         * in function of its "id".
         */
        const char* getVoiceParamAddress(int id, unsigned long voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamAddress(id).c_str();
        }
        
        /*
         * getParamMin(address)
         * Returns the minimum value of a parameter.
         */
        float getParamMin(const char* address)
        {
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
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
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
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
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
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
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
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
        float getCPULoad() { return (fDriver) ? fDriver->getCPULoad() : 0.f; }

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

// Public C API

#ifdef __cplusplus
extern "C" {
#endif
    
    
#ifdef __cplusplus
}
#endif

#endif // __faust_poly_engine__
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

#ifndef __faust_motion_engine_m__
#define __faust_motion_engine_m__


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

						An abstraction layer over myaudio layer

*******************************************************************************
*******************************************************************************/

#ifndef __myaudio__
#define __myaudio__


class myaudio : public audio
{

public:

    
    virtual void render()                                  = 0;

    virtual void setInputValue(int ch,float val)           = 0;
    virtual float getOutputValue(int ch) { return 0.f; }
    

};

#endif


//**************************************************************
// Motion "audio" DSP engine modified from faust_poly_engine
//**************************************************************

using namespace std;


class FaustMotionEngine : public FaustPolyEngine
{

public:

    myaudio* fDriver;

    FaustMotionEngine(dsp* mono_dsp, myaudio* driver = NULL) : FaustPolyEngine(mono_dsp,driver)
    {
        init(((mono_dsp) ? mono_dsp : new mydsp2()), driver, NULL);
        fDriver = driver;
    }

    virtual ~FaustMotionEngine()
    {
        //delete fDriver;
        //delete fFinalDSP;
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

};

#endif // __faust_motion_engine__

//**************************************************************
// IOS Coreaudio
//**************************************************************

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


//**************************************************************
// Interface
//**************************************************************


#include "DspFaustMotion.h"


DspFaustMotion::DspFaustMotion(int sample_rate, int buffer_size){
    fMotionEngine = new FaustMotionEngine(NULL,new motion_audio(sample_rate, buffer_size, 0, false, false));

}



DspFaustMotion::~DspFaustMotion(){
    delete fMotionEngine;

}

bool DspFaustMotion::start(){

    return fMotionEngine->start();
}

void DspFaustMotion::stop(){

    fMotionEngine->stop();
}


void DspFaustMotion::render(){

    fMotionEngine->render();
}

void DspFaustMotion::setInput(int channel, float value) {

    fMotionEngine->setInput(channel, value);
}

float DspFaustMotion::getOutput(int channel) {

    return fMotionEngine->getOutput(channel);

}

int DspFaustMotion::getOutputChannelNum() {

    return fMotionEngine->getOutputChannelNum();
}

int DspFaustMotion::getInputChannelNum() {

    return fMotionEngine->getInputChannelNum();

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

const char* DspFaustMotion::getMetadata(const char* address, const char* key)
{
    return fMotionEngine->getMetadata(address, key);
}

const char* DspFaustMotion::getMetadata(int id, const char* key)
{
    return fMotionEngine->getMetadata(id, key);
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
