#define TARGET_OS_IPHONE 1
/* ------------------------------------------------------------
name: "Faust Motion Library [Motion+RotationMatrix]"
version: "0.7"
Code generated with Faust 2.39.9 (https://faust.grame.fr)
Compilation options: -a /usr/local/share/faust/api-allen/motion/DspFaustMotion.cpp -lang cpp -i -cn mydsp2 -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp2_H__
#define  __mydsp2_H__

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

/************************** BEGIN misc.h *******************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <string>

/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct Meta
{
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

static int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

static int int2pow2(int x) { int r = 0; while ((1<<r) < x) r++; return r; }

static long lopt(char* argv[], const char* name, long def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return std::atoi(argv[i+1]);
    return def;
}

static long lopt1(int argc, char* argv[], const char* longname, const char* shortname, long def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return atoi(argv[i]);
        }
    }
    return def;
}

static const char* lopts(char* argv[], const char* name, const char* def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
    return def;
}

static const char* lopts1(int argc, char* argv[], const char* longname, const char* shortname, const char* def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return argv[i];
        }
    }
    return def;
}

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

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

#endif

/**************************  END  misc.h **************************/
/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

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

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
    
    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
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

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t count) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param size - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(size_t size, size_t reads, size_t writes) {}
    
    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
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
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
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
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
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

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
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

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class ScopedNoDenormals
{
    private:
    
        intptr_t fpsr;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
           asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            _mm_setcsr(static_cast<uint32_t>(fpsr_aux));
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined ( __SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #else
            #if defined(__SSE__)
            #if defined(__SSE2__)
                intptr_t mask = 0x8040;
            #else
                intptr_t mask = 0x8000;
            #endif
            #else
                intptr_t mask = 0x0000;
            #endif
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals();

#endif

/************************** END dsp.h **************************/
/*

  Copyright (C) 2012 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __jsonfaustui__
#define __jsonfaustui__

#include <string>

namespace httpdfaust
{

template <typename C> class jsonui;
 
class jsonfaustui : public UI, public Meta
{
	jsonui<FAUSTFLOAT>* fJSON;
    
	public:

        jsonfaustui(const char* name, const char* address, int port);
		virtual ~jsonfaustui();

		//--------------------------------------------
		// UI methods
		//--------------------------------------------
		// -- widget's layouts
		virtual void openTabBox(const char* label);
		virtual void openHorizontalBox(const char* label);
		virtual void openVerticalBox(const char* label);
		virtual void closeBox();

		// -- active widgets
		void addButton(const char* label, FAUSTFLOAT* zone);
		void addCheckButton(const char* label, FAUSTFLOAT* zone);
		void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
		void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
		void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

		// -- passive widgets
		void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
		void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, float min, float max);
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

		// -- metadata declarations
		void declare(FAUSTFLOAT*, const char*, const char*);

		//--------------------------------------------
		// additionnal methods (not part of UI)
		//--------------------------------------------
		void numInput(int n);			// should be called with the inputs number
		void numOutput(int n);          // should be called with the outputs number
		void declare(const char* , const char*); // global metadata declaration

		//--------------------------------------------
		// and eventually how to get the json as a string
		//--------------------------------------------
		std::string	json(bool flatten);
};

} //end namespace

#endif
/************************** BEGIN JSONUI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
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
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>

/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
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
    
        std::string replaceCharList(std::string str, const std::vector<char>& ch1, char ch2)
        {
            std::vector<char>::const_iterator beg = ch1.begin();
            std::vector<char>::const_iterator end = ch1.end();
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) {
                    str[i] = ch2;
                }
            }
            return str;
        }
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::vector<char> rep = {' ', '#', '*', ',', '/', '?', '[', ']', '{', '}', '(', ')'};
            replaceCharList(res, rep, '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

typedef std::vector<std::tuple<std::string, int, int, int, int, int>> MemoryLayoutType;
typedef std::map<std::string, int> PathTableType;

template <typename REAL>
class JSONUIReal : public PathBuilder, public Meta, public UIReal<REAL>
{

    protected:
    
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
        int fDSPSize;                   // In bytes
        PathTableType fPathTable;
        MemoryLayoutType fMemoryLayout;
        bool fExtended;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs, fSRIndex;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::string dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    default:
                        dst += src[i];
                        break;
                }
            }
            return dst;
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
    
        int getAddressIndex(const std::string& path)
        {
            return (fPathTable.find(path) != fPathTable.end()) ? fPathTable[path] : -1;
        }
      
     public:
     
        JSONUIReal(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const PathTableType& path_table,
                  MemoryLayoutType memory_layout)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table, memory_layout);
        }

        JSONUIReal(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, PathTableType(), MemoryLayoutType());
        }

        JSONUIReal(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, PathTableType(), MemoryLayoutType());
        }
        
        JSONUIReal()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, PathTableType(), MemoryLayoutType());
        }
 
        virtual ~JSONUIReal() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        void setSRIndex(int sr_index) { fSRIndex = sr_index; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const PathTableType& path_table,
                  MemoryLayoutType memory_layout,
                  bool extended = false)
        {
            fTab = 1;
            fExtended = extended;
            if (fExtended) {
                fUI << std::setprecision(std::numeric_limits<REAL>::max_digits10);
                fMeta << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            
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
            fSRIndex = sr_index;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
            fMemoryLayout = memory_layout;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            pushLabel(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab);
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
            popLabel();
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
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab, false);
            fTab -= 1;
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
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"init\": " << init << ",";
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max << ",";
            tab(fTab, fUI); fUI << "\"step\": " << step;
            fTab -= 1;
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
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max;
            fTab -= 1;
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
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path);
            }
            fTab -= 1;
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
            std::stringstream JSON;
            if (fExtended) {
                JSON << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            JSON << "{";
            fTab += 1;
            tab(fTab, JSON); JSON << "\"name\": \"" << fName << "\",";
            tab(fTab, JSON); JSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, JSON); JSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, JSON); JSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    JSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    JSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fMemoryLayout.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"memory_layout\": [";
                for (size_t i = 0; i < fMemoryLayout.size(); i++) {
                    // DSP or field name, type, size, sizeBytes, reads, writes
                    std::tuple<std::string, int, int, int, int, int> item = fMemoryLayout[i];
                    tab(fTab + 1, JSON);
                    JSON << "{\"size\": " << std::get<3>(item) << ", ";
                    JSON << "\"reads\": " << std::get<4>(item) << ", ";
                    JSON << "\"writes\": " << std::get<5>(item) << "}";
                    if (i < (fMemoryLayout.size() - 1)) JSON << ",";
                }
                tab(fTab, JSON);
                JSON << "],";
            }
            if (fDSPSize != -1) { tab(fTab, JSON); JSON << "\"size\": " << fDSPSize << ","; }
            if (fSHAKey != "") { tab(fTab, JSON); JSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, JSON); JSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, JSON); JSON << "\"inputs\": " << fInputs << ",";
            tab(fTab, JSON); JSON << "\"outputs\": " << fOutputs << ",";
            if (fSRIndex != -1) { tab(fTab, JSON); JSON << "\"sr_index\": " << fSRIndex << ","; }
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                JSON << fMeta.str() << fUI.str();
            } else {
                JSON << fUI.str();
            }
            tab(fTab, JSON); JSON << "}";
            return (flat) ? flatten(JSON.str()) : JSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

struct JSONUI : public JSONUIReal<FAUSTFLOAT>, public UI
{
    
    JSONUI(const std::string& name,
           const std::string& filename,
           int inputs,
           int outputs,
           int sr_index,
           const std::string& sha_key,
           const std::string& dsp_code,
           const std::string& version,
           const std::string& compile_options,
           const std::vector<std::string>& library_list,
           const std::vector<std::string>& include_pathnames,
           int size,
           const PathTableType& path_table,
           MemoryLayoutType memory_layout):
    JSONUIReal<FAUSTFLOAT>(name, filename,
                          inputs, outputs,
                          sr_index,
                          sha_key, dsp_code,
                          version, compile_options,
                          library_list, include_pathnames,
                          size, path_table, memory_layout)
    {}
    
    JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
    JSONUIReal<FAUSTFLOAT>(name, filename, inputs, outputs)
    {}
    
    JSONUI(int inputs, int outputs):JSONUIReal<FAUSTFLOAT>(inputs, outputs)
    {}
    
    JSONUI():JSONUIReal<FAUSTFLOAT>()
    {}

    virtual void openTabBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openTabBox(label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openHorizontalBox(label);
    }
    virtual void openVerticalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openVerticalBox(label);
    }
    virtual void closeBox()
    {
        JSONUIReal<FAUSTFLOAT>::closeBox();
    }
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addButton(label, zone);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addCheckButton(label, zone);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
    }
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
    {
        JSONUIReal<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
    }
    
    // -- metadata declarations
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(zone, key, val);
    }

    virtual void declare(const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(key, val);
    }

    virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/
/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>


/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of complete hierarchical 'paths' and zones for each UI item.
 *
 * Simple 'labels' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
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
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // setParamValue/getParamValue
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", path.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};

#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN GUI.h **********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <assert.h>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/************************** BEGIN ValueConverter.h ********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
 ValueConverter.h
 (GRAME, Copyright 2015-2019)
 
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
 LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
 LogValueConverter(umin, umax, fmin, fmax)
 ExpValueConverter(umin, umax, fmin, fmax)
 
 -- ValueConverters used for accelerometers based on 3 points
 
 AccUpConverter(amin, amid, amax, fmin, fmid, fmax)        -- curve 0
 AccDownConverter(amin, amid, amax, fmin, fmid, fmax)      -- curve 1
 AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)    -- curve 2
 AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)    -- curve 3
 
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
// y = v1 + (x-lo) * coef           with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef              with offset = v1 - lo*coef
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
class ValueConverter // Identity by default
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) { return x; };
        virtual double faust2ui(double x) { return x; };
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
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

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

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
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

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
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
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
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
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
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

        virtual void update(double v) const {}

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

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) const { *fZone = FAUSTFLOAT(fValueConverter->ui2faust(v)); }

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
        void update(double v) const { if (fValueConverters[fCurve]->getActive()) *fZone = FAUSTFLOAT(fValueConverters[fCurve]->ui2faust(v)); }

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
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/
/************************** BEGIN MetaDataUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <string.h>
#include <assert.h>
#include <stdio.h> // We use the lighter fprintf code

/************************** BEGIN SimpleParser.h *********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

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
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdio.h> // We use the lighter fprintf code
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    int index;
    double init;
    double fmin;
    double fmax;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), fmin(0.), fmax(0.), step(0.)
    {}
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    fprintf(stderr, "Parse error : %s here : %s\n", errmsg, p);
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
 * @brief parseDouble : parse number [s]dddd[.dddd] or [s]d[.dddd][E|e][s][dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    double sign = 1.0;     // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part
    double expsign = 1.0;  // sign of the E|e part
    double expcoef = 0.0;  // multiplication factor of E|e part
    
    bool valid = false;    // true if the number contains at least one digit
    
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    
    // Sign
    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    
    // Integral part
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    
    // Possible decimal part
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    
    // Possible E|e part
    if (parseChar(p, 'E') || parseChar(p, 'e')) {
        if (parseChar(p, '+')) {
            expsign = 1.0;
        } else if (parseChar(p, '-')) {
            expsign = -1.0;
        }
        while (isdigit(*p)) {
            expcoef = expcoef*10 + (*p - '0');
            p++;
        }
    }
    
    if (valid)  {
        x = (sign*(ipart + dpart/dcoef)) * std::pow(10.0, expcoef*expsign);
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
    // single quoted
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
    if (debug) { fprintf(stderr, "parseMenuList2 : (%s) is not a valid list !\n", p); }
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
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    const char* saved = p; // to restore position if we fail
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
        }
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
    const char* saved = p; // to restore position if we fail
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        double dbl = 0;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo item;
                        item.type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].index = int(dbl);
                    }
                }
                
                else if (label == "meta") {
                    if (!parseItemMetaData(p, uiItems[numItems].meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].init = dbl;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmin = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmax = dbl;
                    }
                }
                
                else if (label == "step") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do {
                            if (!parseUI(p, uiItems, numItems)) {
                                p = saved;
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo item;
                            item.type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                p = saved;
                return false;
            }
            
        } while (tryChar(p, ','));
    
        return parseChar(p, '}');
    } else {
        return true; // "items": [] is valid
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p,
                      std::map<std::string, std::pair<std::string, double> >& metaDatas0,
                      std::map<std::string, std::string>& metaDatas1,
                      std::map<std::string, std::vector<std::string> >& metaDatas2,
                      std::vector<itemInfo>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        double dbl = 0;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, dbl, metaDatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metaDatas2[key] = items;
                    items.clear();
                } else if (value != "") {
                    metaDatas0[key].first = value;
                } else {
                    metaDatas0[key].second = dbl;
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
/**************************  END  SimpleParser.h **************************/

static bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
        scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
        scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
        scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
        scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
        scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
        scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
    protected:
        
        std::string                         fGroupTooltip;
        std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
        std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
        std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
        std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
        std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
        std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
        std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
        std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
        std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
        std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
        std::set<FAUSTFLOAT*>               fHiddenSet;          // set of hidden widget zone
        
        void clearMetadata()
        {
            fGuiSize.clear();
            fTooltip.clear();
            fUnit.clear();
            fRadioDescription.clear();
            fMenuDescription.clear();
            fKnobSet.clear();
            fLedSet.clear();
            fNumSet.clear();
            fLogSet.clear();
            fExpSet.clear();
            fHiddenSet.clear();
            fGroupTooltip = "";
        }
        
        /**
         * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
         * (but not those in the middle of the string)
         */
        static std::string rmWhiteSpaces(const std::string& s)
        {
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if ((i != std::string::npos) && (j != std::string::npos)) {
                return s.substr(i, 1+j-i);
            } else {
                return "";
            }
        }
        
        /**
         * Format tooltip string by replacing some white spaces by
         * return characters so that line width doesn't exceed n.
         * Limitation : long words exceeding n are not cut.
         */
        std::string formatTooltip(int n, const std::string& tt)
        {
            std::string ss = tt;  // ss string we are going to format
            int lws = 0;          // last white space encountered
            int lri = 0;          // last return inserted
            for (int i = 0; i < (int)tt.size(); i++) {
                if (tt[i] == ' ') lws = i;
                if (((i-lri) >= n) && (lws > lri)) {
                    // insert return here
                    ss[lws] = '\n';
                    lri = lws;
                }
            }
            return ss;
        }
        
    public:
        
        virtual ~MetaDataUI()
        {}
        
        enum Scale {
            kLin,
            kLog,
            kExp
        };
        
        Scale getScale(FAUSTFLOAT* zone)
        {
            if (fLogSet.count(zone) > 0) return kLog;
            if (fExpSet.count(zone) > 0) return kExp;
            return kLin;
        }
        
        bool isKnob(FAUSTFLOAT* zone)
        {
            return fKnobSet.count(zone) > 0;
        }
        
        bool isRadio(FAUSTFLOAT* zone)
        {
            return fRadioDescription.count(zone) > 0;
        }
        
        bool isMenu(FAUSTFLOAT* zone)
        {
            return fMenuDescription.count(zone) > 0;
        }
        
        bool isLed(FAUSTFLOAT* zone)
        {
            return fLedSet.count(zone) > 0;
        }
        
        bool isNumerical(FAUSTFLOAT* zone)
        {
            return fNumSet.count(zone) > 0;
        }
        
        bool isHidden(FAUSTFLOAT* zone)
        {
            return fHiddenSet.count(zone) > 0;
        }
        
        /**
         * Extracts metadata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
         */
        static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
        {
            enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
            int state = kLabel; int deep = 0;
            std::string key, value;
            
            for (unsigned int i = 0; i < fulllabel.size(); i++) {
                char c = fulllabel[i];
                switch (state) {
                    case kLabel :
                        assert(deep == 0);
                        switch (c) {
                            case '\\' : state = kEscape1; break;
                            case '[' : state = kKey; deep++; break;
                            default : label += c;
                        }
                        break;
                        
                    case kEscape1:
                        label += c;
                        state = kLabel;
                        break;
                        
                    case kEscape2:
                        key += c;
                        state = kKey;
                        break;
                        
                    case kEscape3:
                        value += c;
                        state = kValue;
                        break;
                        
                    case kKey:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape2;
                                break;
                                
                            case '[':
                                deep++;
                                key += c;
                                break;
                                
                            case ':':
                                if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    key += c;
                                }
                                break;
                            default : key += c;
                        }
                        break;
                        
                    case kValue:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape3;
                                break;
                                
                            case '[':
                                deep++;
                                value += c;
                                break;
                                
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    value += c;
                                }
                                break;
                            default : value += c;
                        }
                        break;
                        
                    default:
                        fprintf(stderr, "ERROR unrecognized state %d\n", state);
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions.
         */
        void declare(FAUSTFLOAT* zone, const char* key, const char* value)
        {
            if (zone == 0) {
                // special zone 0 means group metadata
                if (strcmp(key, "tooltip") == 0) {
                    // only group tooltip are currently implemented
                    fGroupTooltip = formatTooltip(30, value);
                } else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
            } else {
                if (strcmp(key, "size") == 0) {
                    fGuiSize[zone] = atof(value);
                }
                else if (strcmp(key, "tooltip") == 0) {
                    fTooltip[zone] = formatTooltip(30, value);
                }
                else if (strcmp(key, "unit") == 0) {
                    fUnit[zone] = value;
                }
                else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
                else if (strcmp(key, "scale") == 0) {
                    if (strcmp(value, "log") == 0) {
                        fLogSet.insert(zone);
                    } else if (strcmp(value, "exp") == 0) {
                        fExpSet.insert(zone);
                    }
                }
                else if (strcmp(key, "style") == 0) {
                    if (strcmp(value, "knob") == 0) {
                        fKnobSet.insert(zone);
                    } else if (strcmp(value, "led") == 0) {
                        fLedSet.insert(zone);
                    } else if (strcmp(value, "numerical") == 0) {
                        fNumSet.insert(zone);
                    } else {
                        const char* p = value;
                        if (parseWord(p, "radio")) {
                            fRadioDescription[zone] = std::string(p);
                        } else if (parseWord(p, "menu")) {
                            fMenuDescription[zone] = std::string(p);
                        }
                    }
                }
            }
        }
    
};

#endif
/**************************  END  MetaDataUI.h **************************/
/************************** BEGIN ring-buffer.h **************************/
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
/**************************  END  ring-buffer.h **************************/

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

/**
 * Base class for uiTypedItem: memory zones that can be grouped and synchronized, using an internal cache.
 */
struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone)
    {
        assert(ui);
        assert(zone);
    }
    
    virtual ~uiItemBase()
    {}
    
    /**
     * This method will be called when the value changes externally,
     * and will signal the new value to all linked uItem
     * when the value is different from the cached one.
     *
     * @param v - the new value
     */
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    
    /**
     * This method will be called when the value changes externally,
     * and will signal the new value to all linked uItem
     * when the value is different from the cached one.
     *
     * @param date - the timestamp of the received value in usec
     * @param v - the new value
     */
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    
    /**
     * This method is called by the synchronisation mecanism and is expected
     * to 'reflect' the new value, by changing the Widget layout for instance,
     * or sending a message (OSC, MIDI...)
     */
    virtual void reflectZone() = 0;
    
    /**
     * Return the cached value.
     *
     * @return - the cached value
     */
    virtual double cache() = 0;
    
};

// Declared as 'static' to avoid code duplication at link time
static void deleteClist(clist* cl);

/**
 * A list containing all groupe uiItemBase objects.
 */
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
            for (const auto& it : fZoneMap) {
                delete it.second;
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
    
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* cl = fZoneMap[z];
            for (const auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (const auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (const auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        // Start event or message processing
        virtual bool run() { return false; };
        // Stop event or message processing
        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {}
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
 * User Interface Item: abstract definition.
 */
template <typename REAL>
class uiTypedItemReal : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItemReal(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItemReal()
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

class uiItem : public uiTypedItemReal<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItemReal<FAUSTFLOAT>(ui, zone)
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
 * Base class for items with a value converter.
 */
struct uiConverter {
    
    ValueConverter* fConverter;
    
    uiConverter(MetaDataUI::Scale scale, FAUSTFLOAT umin, FAUSTFLOAT umax, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        // Select appropriate converter according to scale mode
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(umin, umax, fmin, fmax);
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(umin, umax, fmin, fmax);
        } else {
            fConverter = new LinearValueConverter(umin, umax, fmin, fmax);
        }
    }
    
    virtual ~uiConverter()
    {
        delete fConverter;
    }
};

/**
 * User Interface item owned (and so deleted) by external code.
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
 * Callback Item.
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
 *  For timestamped control.
 */
struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items.
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
                fprintf(stderr, "ringbuffer_write error DatedControl\n");
            }
        }
    
};

/**
 * Allows to group a set of zones.
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
            for (const auto& it : fZoneMap) {
                *it = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Cannot be defined as method in the classes.

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    for (const auto& it : *cl) {
        // This specific code is only used in JUCE context. TODO: use proper 'shared_ptr' based memory management.
    #if defined(JUCE_32BIT) || defined(JUCE_64BIT)
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    #else
        delete it;
    #endif
    }
}

#endif
/**************************  END  GUI.h **************************/
/************************** BEGIN JSONUIDecoder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <functional>

/************************** BEGIN CGlue.h *****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*************************************************************************/

#ifndef CGLUE_H
#define CGLUE_H

/************************** BEGIN CInterface.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/


#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
struct Soundfile;

/*******************************************************************************
 * UI, Meta and MemoryManager structures for C code.
 ******************************************************************************/

// -- widget's layouts

typedef void (* openTabBoxFun) (void* ui_interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* ui_interface, const char* label);
typedef void (* openVerticalBoxFun) (void* ui_interface, const char* label);
typedef void (* closeBoxFun) (void* ui_interface);

// -- active widgets

typedef void (* addButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive widgets

typedef void (* addHorizontalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

// -- soundfiles
    
typedef void (* addSoundfileFun) (void* ui_interface, const char* label, const char* url, struct Soundfile** sf_zone);

typedef void (* declareFun) (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    addSoundfileFun addSoundfile;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (void* ui_interface, const char* key, const char* value);

typedef struct {

    void* metaInterface;
    
    metaDeclareFun declare;

} MetaGlue;

/***************************************
 *  Interface for the DSP object
 ***************************************/

typedef char dsp_imp;
    
typedef dsp_imp* (* newDspFun) ();
typedef void (* destroyDspFun) (dsp_imp* dsp);
typedef int (* getNumInputsFun) (dsp_imp* dsp);
typedef int (* getNumOutputsFun) (dsp_imp* dsp);
typedef void (* buildUserInterfaceFun) (dsp_imp* dsp, UIGlue* ui);
typedef int (* getSampleRateFun) (dsp_imp* dsp);
typedef void (* initFun) (dsp_imp* dsp, int sample_rate);
typedef void (* classInitFun) (int sample_rate);
typedef void (* instanceInitFun) (dsp_imp* dsp, int sample_rate);
typedef void (* instanceConstantsFun) (dsp_imp* dsp, int sample_rate);
typedef void (* instanceResetUserInterfaceFun) (dsp_imp* dsp);
typedef void (* instanceClearFun) (dsp_imp* dsp);
typedef void (* computeFun) (dsp_imp* dsp, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
typedef void (* metadataFun) (MetaGlue* meta);
    
/***************************************
 * DSP memory manager functions
 ***************************************/

typedef void* (* allocateFun) (void* manager_interface, size_t size);
typedef void (* destroyFun) (void* manager_interface, void* ptr);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} MemoryManagerGlue;

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CInterface.h **************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * UI glue code
 ******************************************************************************/
 
class UIFloat
{

    public:

        UIFloat() {}

        virtual ~UIFloat() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, float* zone) = 0;
        virtual void addCheckButton(const char* label, float* zone) = 0;
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(float* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueFloat(void* cpp_interface)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueFloat(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueFloat(void* cpp_interface, float* zone, const char* key, const char* value)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

class UIDouble
{

    public:

        UIDouble() {}

        virtual ~UIDouble() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, double* zone) = 0;
        virtual void addCheckButton(const char* label, double* zone) = 0;
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max) = 0;
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(double* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueDouble(void* cpp_interface)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueDouble(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueDouble(void* cpp_interface, double* zone, const char* key, const char* value)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

static void buildUIGlue(UIGlue* glue, UI* ui_interface, bool is_double)
{
    glue->uiInterface = ui_interface;
    
    if (is_double) {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueDouble);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueDouble);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueDouble);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueDouble);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueDouble);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueDouble);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueDouble);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueDouble);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueDouble);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueDouble);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueDouble);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueDouble);
        glue->declare = reinterpret_cast<declareFun>(declareGlueDouble);
    } else {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueFloat);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueFloat);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueFloat);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueFloat);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueFloat);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueFloat);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueFloat);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueFloat);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueFloat);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueFloat);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueFloat);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueFloat);
        glue->declare = reinterpret_cast<declareFun>(declareGlueFloat);
    }
}
    
struct UITemplate
{
    
    void* fCPPInterface;

    UITemplate(void* cpp_interface):fCPPInterface(cpp_interface)
    {}
    
    virtual ~UITemplate() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label)
    {
        openTabBoxGlueFloat(fCPPInterface, label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        openHorizontalBoxGlueFloat(fCPPInterface, label);
    }
    virtual void openVerticalBox(const char* label)
    {
        openVerticalBoxGlueFloat(fCPPInterface, label);
    }
    virtual void closeBox()
    {
        closeBoxGlueFloat(fCPPInterface);
    }
    
    // float version
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        addButtonGlueFloat(fCPPInterface, label, zone);
    }
    virtual void addCheckButton(const char* label, float* zone)
    {
        addCheckButtonGlueFloat(fCPPInterface, label, zone);
    }
    
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addVerticalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addHorizontalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        addNumEntryGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
    {
        addHorizontalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
    }
    
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {
        addVerticalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
    }

    // -- metadata declarations
    
    virtual void declare(float* zone, const char* key, const char* val)
    {
        declareGlueFloat(fCPPInterface, zone, key, val);
    }
    
    // double version
    
    virtual void addButton(const char* label, double* zone)
    {
        addButtonGlueDouble(fCPPInterface, label, zone);
    }
    virtual void addCheckButton(const char* label, double* zone)
    {
        addCheckButtonGlueDouble(fCPPInterface, label, zone);
    }
    
    virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
    {
        addVerticalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
    {
        addHorizontalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
    {
        addNumEntryGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }

    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
    {
        addSoundfileGlueFloat(fCPPInterface, label, url, sf_zone);
    }

    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max)
    {
        addHorizontalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
    }
    
    virtual void addVerticalBargraph(const char* label, double* zone, double min, double max)
    {
        addVerticalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
    }

    // -- metadata declarations
    
    virtual void declare(double* zone, const char* key, const char* val)
    {
        declareGlueDouble(fCPPInterface, zone, key, val);
    }

};

/*******************************************************************************
 * Meta glue code
 ******************************************************************************/

static void declareMetaGlue(void* cpp_interface, const char* key, const char* value)
{
    Meta* meta_interface = static_cast<Meta*>(cpp_interface);
    meta_interface->declare(key, value);
}

static void buildMetaGlue(MetaGlue* glue, Meta* meta)
{
    glue->metaInterface = meta;
    glue->declare = declareMetaGlue;
}
    
/*******************************************************************************
 * Memory manager glue code
 ******************************************************************************/

static void* allocateMemoryManagerGlue(void* cpp_interface, size_t size)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    return manager_interface->allocate(size);
}
    
static void destroyMemoryManagerGlue(void* cpp_interface, void* ptr)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    manager_interface->destroy(ptr);
}

static void buildManagerGlue(MemoryManagerGlue* glue, dsp_memory_manager* manager)
{
    glue->managerInterface = manager;
    glue->allocate = allocateMemoryManagerGlue;
    glue->destroy = destroyMemoryManagerGlue;
}

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CGlue.h **************************/

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//------------------------------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface' and 'metadata' methods
//------------------------------------------------------------------------------------------

#define REAL_UI(ui_interface) reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(index)      reinterpret_cast<REAL*>(&memory_block[index])
#define REAL_EXT_ADR(index)  reinterpret_cast<FAUSTFLOAT*>(&memory_block[index])
#define SOUNDFILE_ADR(index) reinterpret_cast<Soundfile**>(&memory_block[index])

typedef std::function<void(FAUSTFLOAT)> ReflectFunction;
typedef std::function<FAUSTFLOAT()> ModifyFunction;

struct ExtZoneParam {

    virtual void reflectZone() = 0;
    virtual void modifyZone() = 0;
    
    virtual void setReflectZoneFun(ReflectFunction reflect) = 0;
    virtual void setModifyZoneFun(ModifyFunction modify) = 0;
    
    virtual ~ExtZoneParam()
    {}
    
};

// Templated decoder

struct JSONUIDecoderBase
{
    virtual ~JSONUIDecoderBase()
    {}
    
    virtual void metadata(Meta* m) = 0;
    virtual void metadata(MetaGlue* glue) = 0;
    virtual int getDSPSize() = 0;
    virtual std::string getName() = 0;
    virtual std::string getLibVersion() = 0;
    virtual std::string getCompileOptions() = 0;
    virtual std::vector<std::string> getLibraryList() = 0;
    virtual std::vector<std::string> getIncludePathnames() = 0;
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual int getSampleRate(char* memory_block) = 0;
    virtual void setReflectZoneFun(int index, ReflectFunction fun) = 0;
    virtual void setModifyZoneFun(int index, ModifyFunction fun) = 0;
    virtual void setupDSPProxy(UI* ui_interface, char* memory_block) = 0;
    virtual bool hasDSPProxy() = 0;
    virtual std::vector<ExtZoneParam*>& getInputControls() = 0;
    virtual std::vector<ExtZoneParam*>& getOutputControls() = 0;
    virtual void resetUserInterface() = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

template <typename REAL>
struct JSONUIDecoderReal : public JSONUIDecoderBase {
    
    struct ZoneParam : public ExtZoneParam {
        
        FAUSTFLOAT fZone;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(ReflectFunction reflect = [](FAUSTFLOAT value) {}, ModifyFunction modify = []() { return FAUSTFLOAT(-1); })
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { fReflect(fZone); }
        void modifyZone() { fZone = fModify(); }
    #endif
        
        void setReflectZoneFun(ReflectFunction reflect) { fReflect = reflect; }
        void setModifyZoneFun(ModifyFunction modify) { fModify = modify; }
        
    };
    
    typedef std::vector<ExtZoneParam*> controlMap;
  
    std::string fName;
    std::string fFileName;
    std::string fJSON;
    std::string fVersion;
    std::string fCompileOptions;
    
    std::map<std::string, std::string> fMetadata;
    std::vector<itemInfo> fUiItems;
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fDSPSize;
    bool fDSPProxy;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]
    
    bool startWith(const std::string& str, const std::string& prefix)
    {
        return (str.substr(0, prefix.size()) == prefix);
    }

    bool isInput(const std::string& type)
    {
        return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox");
    }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }
    
    std::string getString(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? map[key].first : "";
    }
    
    int getInt(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? int(map[key].second) : -1;
    }
    
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        fPathInputTable[index]->setReflectZoneFun(fun);
    }
    
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        fPathOutputTable[index]->setModifyZoneFun(fun);
    }

    JSONUIDecoderReal(const std::string& json)
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::pair<std::string, double> > meta_data1;
        std::map<std::string, std::vector<std::string> > meta_data2;
        parseJson(p, meta_data1, fMetadata, meta_data2, fUiItems);
        
        // meta_data1 contains <name : val>, <inputs : val>, <ouputs : val> pairs etc...
        fName = getString(meta_data1, "name");
        fFileName = getString(meta_data1, "filename");
        fVersion = getString(meta_data1, "version");
        fCompileOptions = getString(meta_data1, "compile_options");
        
        if (meta_data2.find("library_list") != meta_data2.end()) {
            fLibraryList = meta_data2["library_list"];
        } else {
            // 'library_list' is coded as successive 'library_pathN' metadata
            for (const auto& it : fMetadata) {
                if (startWith(it.first, "library_path")) {
                    fLibraryList.push_back(it.second);
                }
            }
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = getInt(meta_data1, "size");
        fNumInputs = getInt(meta_data1, "inputs");
        fNumOutputs = getInt(meta_data1, "outputs");
        fSRIndex = getInt(meta_data1, "sr_index");
        fDSPProxy = false;
        
        // Prepare the fPathTable and init zone
        for (const auto& it : fUiItems) {
            std::string type = it.type;
            // Meta data declaration for input items
            if (isInput(type)) {
                ZoneParam* param = new ZoneParam();
                fPathInputTable.push_back(param);
                param->fZone = it.init;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                ZoneParam* param = new ZoneParam();
                fPathOutputTable.push_back(param);
                param->fZone = REAL(0);
            }
        }
    }
    
    virtual ~JSONUIDecoderReal()
    {
        for (const auto& it : fPathInputTable) {
            delete it;
        }
        for (const auto& it : fPathOutputTable) {
            delete it;
        }
    }
    
    void metadata(Meta* m)
    {
        for (const auto& it : fMetadata) {
            m->declare(it.first.c_str(), it.second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        for (const auto& it : fMetadata) {
            m->declare(m->metaInterface, it.first.c_str(), it.second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        int item = 0;
        for (const auto& it : fUiItems) {
            if (isInput(it.type)) {
                static_cast<ZoneParam*>(fPathInputTable[item++])->fZone = it.init;
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        for (const auto& it : fUiItems) {
            int index = it.index;
            if (isInput(it.type)) {
                *REAL_ADR(index) = it.init;
            } else if (isSoundfile(it.type)) {
                if (*SOUNDFILE_ADR(index) == nullptr) {
                    *SOUNDFILE_ADR(index) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
    
    void setupDSPProxy(UI* ui_interface, char* memory_block)
    {
        if (!fDSPProxy) {
            fDSPProxy = true;
            int countIn = 0;
            int countOut = 0;
            for (const auto& it : fUiItems) {
                std::string type = it.type;
                int index = it.index;
                if (isInput(type)) {
                    fPathInputTable[countIn++]->setReflectZoneFun([=](FAUSTFLOAT value) { *REAL_ADR(index) = REAL(value); });
                } else if (isOutput(type)) {
                    fPathOutputTable[countOut++]->setModifyZoneFun([=]() { return FAUSTFLOAT(*REAL_ADR(index)); });
                }
            }
        }
        
        // Setup soundfile in any case
        for (const auto& it : fUiItems) {
            if (isSoundfile(it.type)) {
                ui_interface->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(it.index));
            }
        }
    }
    
    bool hasDSPProxy() { return fDSPProxy; }
  
    void buildUserInterface(UI* ui_interface)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        int countIn = 0;
        int countOut = 0;
        int countSound = 0;
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(&static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(&static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "soundfile") {
                // Nothing
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "close") {
                ui_interface->closeBox();
            }
            
            if (isInput(type)) {
                countIn++;
            } else if (isOutput(type)) {
                countOut++;
            } else if (isSoundfile(type)) {
                countSound++;
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            int index = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), REAL_ADR(index));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(index));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), REAL_ADR(index), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), REAL_ADR(index), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), REAL_ADR(index));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            int index = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, 0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index));
            } else if (type == "soundfile") {
                ui_interface->addSoundfile(ui_interface->uiInterface, it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(index));
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index));
            } else if (type == "close") {
                ui_interface->closeBox(ui_interface->uiInterface);
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
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
    
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    
};

// FAUSTFLOAT templated decoder

struct JSONUIDecoder : public JSONUIDecoderReal<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderReal<FAUSTFLOAT>(json)
    {}
};

// Generic factory

static JSONUIDecoderBase* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDecoderReal<double>(json);
    } else {
        return new JSONUIDecoderReal<float>(json);
    }
}

#endif
/**************************  END  JSONUIDecoder.h **************************/
/************************** BEGIN dsp-adapter.h *************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_adapter__
#define __dsp_adapter__

#ifndef _WIN32
#include <alloca.h>
#endif
#include <string.h>
#include <cmath>
#include <assert.h>
#include <stdio.h>


// Adapts a DSP for a different number of inputs/outputs
class dsp_adapter : public decorator_dsp {
    
    private:
    
        FAUSTFLOAT** fAdaptedInputs;
        FAUSTFLOAT** fAdaptedOutputs;
        int fHWInputs;
        int fHWOutputs;
        int fBufferSize;
    
        void adaptBuffers(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fHWInputs; i++) {
                fAdaptedInputs[i] = inputs[i];
            }
            for (int i = 0; i < fHWOutputs; i++) {
                fAdaptedOutputs[i] = outputs[i];
            }
        }
    
    public:
    
        dsp_adapter(dsp* dsp, int hw_inputs, int hw_outputs, int buffer_size):decorator_dsp(dsp)
        {
            fHWInputs = hw_inputs;
            fHWOutputs = hw_outputs;
            fBufferSize = buffer_size;
            
            fAdaptedInputs = new FAUSTFLOAT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs() - fHWInputs; i++) {
                fAdaptedInputs[i + fHWInputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedInputs[i + fHWInputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            
            fAdaptedOutputs = new FAUSTFLOAT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs() - fHWOutputs; i++) {
                fAdaptedOutputs[i + fHWOutputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedOutputs[i + fHWOutputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
    
        virtual ~dsp_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs() - fHWInputs; i++) {
                delete [] fAdaptedInputs[i + fHWInputs];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs() - fHWOutputs; i++) {
                delete [] fAdaptedOutputs[i + fHWOutputs];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual int getNumInputs() { return fHWInputs; }
        virtual int getNumOutputs() { return fHWOutputs; }
    
        virtual dsp_adapter* clone() { return new dsp_adapter(fDSP->clone(), fHWInputs, fHWOutputs, fBufferSize); }
    
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
template <typename REAL_INT, typename REAL_EXT>
class dsp_sample_adapter : public decorator_dsp {
    
    private:
    
        REAL_INT** fAdaptedInputs;
        REAL_INT** fAdaptedOutputs;
    
        void adaptInputBuffers(int count, FAUSTFLOAT** inputs)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    fAdaptedInputs[chan][frame] = REAL_INT(reinterpret_cast<REAL_EXT**>(inputs)[chan][frame]);
                }
            }
        }
    
        void adaptOutputsBuffers(int count, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    reinterpret_cast<REAL_EXT**>(outputs)[chan][frame] = REAL_EXT(fAdaptedOutputs[chan][frame]);
                }
            }
        }
    
    public:
    
        dsp_sample_adapter(dsp* dsp):decorator_dsp(dsp)
        {
            fAdaptedInputs = new REAL_INT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs(); i++) {
                fAdaptedInputs[i] = new REAL_INT[4096];
            }
            
            fAdaptedOutputs = new REAL_INT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs(); i++) {
                fAdaptedOutputs[i] = new REAL_INT[4096];
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
    
        virtual dsp_sample_adapter* clone() { return new dsp_sample_adapter(fDSP->clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
};

// Template used to specialize double parameters expressed as NUM/DENOM
template <int NUM, int DENOM>
struct Double {
    static constexpr double value() { return double(NUM)/double(DENOM); }
};

// Base class for filters
template <class fVslider0, int fVslider1>
struct Filter {
    inline int getFactor() { return fVslider1; }
};

// Identity filter: copy input to output
template <class fVslider0, int fVslider1>
struct Identity : public Filter<fVslider0, fVslider1> {
    inline int getFactor() { return fVslider1; }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        memcpy(output0, input0, count * sizeof(FAUSTFLOAT));
    }
};

// Generated with process = fi.lowpass(3, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3 : public Filter<fVslider0, fVslider1> {
    
    REAL fVec0[2];
    REAL fRec1[2];
    REAL fRec0[3];
    
    inline REAL LowPass3_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3()
    {
        for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
            fVec0[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 1.0000000000000002) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (fSlow1 + 1.0));
        REAL fSlow4 = (1.0 - fSlow1);
        REAL fSlow5 = (((fSlow1 + -1.0000000000000002) / fSlow0) + 1.0);
        REAL fSlow6 = (2.0 * (1.0 - (1.0 / LowPass3_faustpower2_f(fSlow0))));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            REAL fTemp0 = REAL(input0[i]);
            fVec0[0] = fTemp0;
            fRec1[0] = (0.0 - (fSlow3 * ((fSlow4 * fRec1[1]) - (fTemp0 + fVec0[1]))));
            fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow5 * fRec0[2]) + (fSlow6 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fVec0[1] = fVec0[0];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass(4, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass4 : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass4_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass4()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0f;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec0[l1] = 0.0f;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.76536686473017945) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (((fSlow1 + 1.8477590650225735) / fSlow0) + 1.0));
        REAL fSlow4 = (((fSlow1 + -1.8477590650225735) / fSlow0) + 1.0);
        REAL fSlow5 = (2.0 * (1.0 - (1.0 / LowPass4_faustpower2_f(fSlow0))));
        REAL fSlow6 = (((fSlow1 + -0.76536686473017945) / fSlow0) + 1.0);
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow3 * ((fSlow4 * fRec1[2]) + (fSlow5 * fRec1[1]))));
            fRec0[0] = ((fSlow3 * (fRec1[2] + (fRec1[0] + (2.0 * fRec1[1])))) - (fSlow2 * ((fSlow6 * fRec0[2]) + (fSlow5 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass3e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fVec0[2];
    REAL fRec0[2];
    
    inline REAL LowPass3e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fVec0[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (fSlow1 + 0.82244590899881598));
        REAL fSlow3 = (0.82244590899881598 - fSlow1);
        REAL fSlow4 = (1.0 / (((fSlow1 + 0.80263676416103003) / fSlow0) + 1.4122708937742039));
        REAL fSlow5 = LowPass3e_faustpower2_f(fSlow0);
        REAL fSlow6 = (0.019809144837788999 / fSlow5);
        REAL fSlow7 = (fSlow6 + 1.1615164189826961);
        REAL fSlow8 = (((fSlow1 + -0.80263676416103003) / fSlow0) + 1.4122708937742039);
        REAL fSlow9 = (2.0 * (1.4122708937742039 - (1.0 / fSlow5)));
        REAL fSlow10 = (2.0 * (1.1615164189826961 - fSlow6));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow4 * ((fSlow8 * fRec1[2]) + (fSlow9 * fRec1[1]))));
            REAL fTemp0 = (fSlow4 * (((fSlow7 * fRec1[0]) + (fSlow10 * fRec1[1])) + (fSlow7 * fRec1[2])));
            fVec0[0] = fTemp0;
            fRec0[0] = (0.0 - (fSlow2 * ((fSlow3 * fRec0[1]) - (fTemp0 + fVec0[1]))));
            output0[i] = FAUSTFLOAT(fRec0[0]);
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fVec0[1] = fVec0[0];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass6e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass6e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec2[3];
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass6e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass6e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec2[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.16840487111358901) / fSlow0) + 1.0693584077073119));
        REAL fSlow3 = LowPass6e_faustpower2_f(fSlow0);
        REAL fSlow4 = (1.0 / fSlow3);
        REAL fSlow5 = (fSlow4 + 53.536152954556727);
        REAL fSlow6 = (1.0 / (((fSlow1 + 0.51247864188914105) / fSlow0) + 0.68962136448467504));
        REAL fSlow7 = (fSlow4 + 7.6217312988706034);
        REAL fSlow8 = (1.0 / (((fSlow1 + 0.78241304682164503) / fSlow0) + 0.24529150870616001));
        REAL fSlow9 = (9.9999997054999994e-05 / fSlow3);
        REAL fSlow10 = (fSlow9 + 0.00043322720055500002);
        REAL fSlow11 = (((fSlow1 + -0.78241304682164503) / fSlow0) + 0.24529150870616001);
        REAL fSlow12 = (2.0 * (0.24529150870616001 - fSlow4));
        REAL fSlow13 = (2.0 * (0.00043322720055500002 - fSlow9));
        REAL fSlow14 = (((fSlow1 + -0.51247864188914105) / fSlow0) + 0.68962136448467504);
        REAL fSlow15 = (2.0 * (0.68962136448467504 - fSlow4));
        REAL fSlow16 = (2.0 * (7.6217312988706034 - fSlow4));
        REAL fSlow17 = (((fSlow1 + -0.16840487111358901) / fSlow0) + 1.0693584077073119);
        REAL fSlow18 = (2.0 * (1.0693584077073119 - fSlow4));
        REAL fSlow19 = (2.0 * (53.536152954556727 - fSlow4));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec2[0] = (REAL(input0[i]) - (fSlow8 * ((fSlow11 * fRec2[2]) + (fSlow12 * fRec2[1]))));
            fRec1[0] = ((fSlow8 * (((fSlow10 * fRec2[0]) + (fSlow13 * fRec2[1])) + (fSlow10 * fRec2[2]))) - (fSlow6 * ((fSlow14 * fRec1[2]) + (fSlow15 * fRec1[1]))));
            fRec0[0] = ((fSlow6 * (((fSlow7 * fRec1[0]) + (fSlow16 * fRec1[1])) + (fSlow7 * fRec1[2]))) - (fSlow2 * ((fSlow17 * fRec0[2]) + (fSlow18 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (((fSlow5 * fRec0[0]) + (fSlow19 * fRec0[1])) + (fSlow5 * fRec0[2]))));
            fRec2[2] = fRec2[1];
            fRec2[1] = fRec2[0];
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// A "si.bus(N)" like hard-coded class
struct dsp_bus : public dsp {
    
    int fChannels;
    int fSampleRate;
    
    dsp_bus(int channels):fChannels(channels), fSampleRate(-1)
    {}
    
    virtual int getNumInputs() { return fChannels; }
    virtual int getNumOutputs() { return fChannels; }
    
    virtual int getSampleRate() { return fSampleRate; }
    
    virtual void buildUserInterface(UI* ui_interface) {}
    virtual void init(int sample_rate)
    {
        //classInit(sample_rate);
        instanceInit(sample_rate);
    }
    
    virtual void instanceInit(int sample_rate)
    {
        fSampleRate = sample_rate;
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }
    
    virtual void instanceConstants(int sample_rate) {}
    virtual void instanceResetUserInterface() {}
    virtual void instanceClear() {}
    
    virtual dsp* clone() { return new dsp_bus(fChannels); }
    
    virtual void metadata(Meta* m) {}
    
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        for (int chan = 0; chan < fChannels; chan++) {
            memcpy(outputs[chan], inputs[chan], sizeof(FAUSTFLOAT) * count);
        }
    }
    
    virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

// Base class for sample-rate adapter
template <typename FILTER>
class sr_sampler : public decorator_dsp {
    
    protected:
    
        std::vector<FILTER> fInputLowPass;
        std::vector<FILTER> fOutputLowPass;
    
        inline int getFactor() { return this->fOutputLowPass[0].getFactor(); }
    
    public:
    
        sr_sampler(dsp* dsp):decorator_dsp(dsp)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                fInputLowPass.push_back(FILTER());
            }
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                fOutputLowPass.push_back(FILTER());
            }
        }
};

// Down sample-rate adapter
template <typename FILTER>
class dsp_down_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_down_sampler(dsp* dsp):sr_sampler<FILTER>(dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate / this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate / this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate / this->getFactor());
        }
    
        virtual dsp_down_sampler* clone() { return new dsp_down_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count / this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Lowpass filtering in place on 'inputs'
                this->fInputLowPass[chan].compute(count, inputs[chan], inputs[chan]);
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Decimate
                for (int frame = 0; frame < real_count; frame++) {
                    fInputs[chan][frame] = inputs[chan][frame * this->getFactor()];
                }
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at lower rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Puts zeros
                memset(outputs[chan], 0, sizeof(FAUSTFLOAT) * count);
                for (int frame = 0; frame < real_count; frame++) {
                    // Copy one sample every 'DownFactor'
                    // Apply volume
                    //outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame] * this->getFactor();
                    outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame];
                }
                // Lowpass filtering in place on 'outputs'
                this->fOutputLowPass[chan].compute(count, outputs[chan], outputs[chan]);
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Up sample-rate adapter
template <typename FILTER>
class dsp_up_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_up_sampler(dsp* dsp):sr_sampler<FILTER>(dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate * this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate * this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate * this->getFactor());
        }
    
        virtual dsp_up_sampler* clone() { return new dsp_up_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count * this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Puts zeros
                memset(fInputs[chan], 0, sizeof(FAUSTFLOAT) * real_count);
                for (int frame = 0; frame < count; frame++) {
                    // Copy one sample every 'UpFactor'
                    fInputs[chan][frame * this->getFactor()] = inputs[chan][frame];
                }
                // Lowpass filtering in place on 'fInputs'
                this->fInputLowPass[chan].compute(real_count, fInputs[chan], fInputs[chan]);
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at upper rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Lowpass filtering in place on 'fOutputs'
                this->fOutputLowPass[chan].compute(real_count, fOutputs[chan], fOutputs[chan]);
                // Decimate
                for (int frame = 0; frame < count; frame++) {
                    // Apply volume
                    //outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()] * this->getFactor();
                    outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()];
                }
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Create a UP/DS + Filter adapted DSP
template <typename REAL>
dsp* createSRAdapter(dsp* DSP, int ds = 0, int us = 0, int filter = 0)
{
    if (ds > 0) {
        switch (filter) {
            case 0:
                if (ds == 2) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 3>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            default:
                fprintf(stderr, "ERROR : filter type must be in [0..4] range\n");
                assert(false);
                return nullptr;
        }
    } else if (us > 0) {
        
        switch (filter) {
            case 0:
                if (us == 2) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 3>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            default:
                fprintf(stderr, "ERROR : filter type must be in [0..4] range\n");
                assert(false);
                return nullptr;
        }
    } else {
        return DSP;
    }
}
    
#endif
/************************** END dsp-adapter.h **************************/


#include <math.h>
#include <cmath>


#if OSCCTRL
#define OSC_IP_ADDRESS  "192.168.0.101"
#define OSC_IN_PORT     "5510"
#define OSC_OUT_PORT    "5511"

/************************** BEGIN OSCUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *********************************************************************/

#ifndef __OSCUI__
#define __OSCUI__

#include <vector>
#include <string>

/*

  Faust Project

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __OSCControler__
#define __OSCControler__

#include <string>
/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __FaustFactory__
#define __FaustFactory__

#include <stack>
#include <string>
#include <sstream>

/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __FaustNode__
#define __FaustNode__

#include <string>
#include <vector>

/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __MessageDriven__
#define __MessageDriven__

#include <string>
#include <vector>

/*

  Copyright (C) 2010  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __MessageProcessor__
#define __MessageProcessor__

namespace oscfaust
{

class Message;
//--------------------------------------------------------------------------
/*!
	\brief an abstract class for objects able to process OSC messages	
*/
class MessageProcessor
{
	public:
		virtual		~MessageProcessor() {}
		virtual void processMessage( const Message* msg ) = 0;
};

} // end namespoace

#endif
/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __smartpointer__
#define __smartpointer__

#include <cassert>

namespace oscfaust
{

/*!
\brief the base class for smart pointers implementation

	Any object that want to support smart pointers should
	inherit from the smartable class which provides reference counting
	and automatic delete when the reference count drops to zero.
*/
class smartable {
	private:
		unsigned 	refCount;		
	public:
		//! gives the reference count of the object
		unsigned refs() const         { return refCount; }
		//! addReference increments the ref count and checks for refCount overflow
		void addReference()           { refCount++; assert(refCount != 0); }
		//! removeReference delete the object when refCount is zero		
		void removeReference()		  { if (--refCount == 0) delete this; }
		
	protected:
		smartable() : refCount(0) {}
		smartable(const smartable&): refCount(0) {}
		//! destructor checks for non-zero refCount
		virtual ~smartable()    
        { 
            /* 
                See "Static SFaustNode create (const char* name, C* zone, C init, C min, C max, const char* prefix, GUI* ui)" comment.
                assert (refCount == 0); 
            */
        }
		smartable& operator=(const smartable&) { return *this; }
};

/*!
\brief the smart pointer implementation

	A smart pointer is in charge of maintaining the objects reference count 
	by the way of pointers operators overloading. It supports class 
	inheritance and conversion whenever possible.
\n	Instances of the SMARTP class are supposed to use \e smartable types (or at least
	objects that implements the \e addReference and \e removeReference
	methods in a consistent way).
*/
template<class T> class SMARTP {
	private:
		//! the actual pointer to the class
		T* fSmartPtr;

	public:
		//! an empty constructor - points to null
		SMARTP()	: fSmartPtr(0) {}
		//! build a smart pointer from a class pointer
		SMARTP(T* rawptr) : fSmartPtr(rawptr)              { if (fSmartPtr) fSmartPtr->addReference(); }
		//! build a smart pointer from an convertible class reference
		template<class T2> 
		SMARTP(const SMARTP<T2>& ptr) : fSmartPtr((T*)ptr) { if (fSmartPtr) fSmartPtr->addReference(); }
		//! build a smart pointer from another smart pointer reference
		SMARTP(const SMARTP& ptr) : fSmartPtr((T*)ptr)     { if (fSmartPtr) fSmartPtr->addReference(); }

		//! the smart pointer destructor: simply removes one reference count
		~SMARTP()  { if (fSmartPtr) fSmartPtr->removeReference(); }
		
		//! cast operator to retrieve the actual class pointer
		operator T*() const  { return fSmartPtr;	}

		//! '*' operator to access the actual class pointer
		T& operator*() const {
			// checks for null dereference
			assert (fSmartPtr != 0);
			return *fSmartPtr;
		}

		//! operator -> overloading to access the actual class pointer
		T* operator->() const	{ 
			// checks for null dereference
			assert (fSmartPtr != 0);
			return fSmartPtr;
		}

		//! operator = that moves the actual class pointer
		template <class T2>
		SMARTP& operator=(T2 p1_)	{ *this=(T*)p1_; return *this; }

		//! operator = that moves the actual class pointer
		SMARTP& operator=(T* p_)	{
			// check first that pointers differ
			if (fSmartPtr != p_) {
				// increments the ref count of the new pointer if not null
				if (p_ != 0) p_->addReference();
				// decrements the ref count of the old pointer if not null
				if (fSmartPtr != 0) fSmartPtr->removeReference();
				// and finally stores the new actual pointer
				fSmartPtr = p_;
			}
			return *this;
		}
		//! operator < to support SMARTP map with Visual C++
		bool operator<(const SMARTP<T>& p_)	const			  { return fSmartPtr < ((T *) p_); }
		//! operator = to support inherited class reference
		SMARTP& operator=(const SMARTP<T>& p_)                { return operator=((T *) p_); }
		//! dynamic cast support
		template<class T2> SMARTP& cast(T2* p_)               { return operator=(dynamic_cast<T*>(p_)); }
		//! dynamic cast support
		template<class T2> SMARTP& cast(const SMARTP<T2>& p_) { return operator=(dynamic_cast<T*>(p_)); }
};

}

#endif

namespace oscfaust
{

class Message;
class OSCRegexp;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
/*!
	\brief a base class for objects accepting OSC messages
	
	Message driven objects are hierarchically organized in a tree.
	They provides the necessary to dispatch an OSC message to its destination
	node, according to the message OSC address. 
	
	The principle of the dispatch is the following:
	- first the processMessage() method should be called on the top level node
	- next processMessage call propose 
*/
class MessageDriven : public MessageProcessor, public smartable
{
	std::string						fName;			///< the node name
	std::string						fOSCPrefix;		///< the node OSC address prefix (OSCAddress = fOSCPrefix + '/' + fName)
	std::vector<SMessageDriven>		fSubNodes;		///< the subnodes of the current node

	protected:
				 MessageDriven(const char *name, const char *oscprefix) : fName (name), fOSCPrefix(oscprefix) {}
		virtual ~MessageDriven() {}

	public:
		static SMessageDriven create(const char* name, const char *oscprefix)	{ return new MessageDriven(name, oscprefix); }

		/*!
			\brief OSC message processing method.
			\param msg the osc message to be processed
			The method should be called on the top level node.
		*/
		virtual void	processMessage(const Message* msg);

		/*!
			\brief propose an OSc message at a given hierarchy level.
			\param msg the osc message currently processed
			\param regexp a regular expression based on the osc address head
			\param addrTail the osc address tail
			
			The method first tries to match the regular expression with the object name. 
			When it matches:
			- it calls \c accept when \c addrTail is empty 
			- or it \c propose the message to its subnodes when \c addrTail is not empty. 
			  In this case a new \c regexp is computed with the head of \c addrTail and a new \c addrTail as well.
		*/
		virtual void	propose(const Message* msg, const OSCRegexp* regexp, const std::string& addrTail);

		/*!
			\brief accept an OSC message. 
			\param msg the osc message currently processed
			\return true when the message is processed by the node
			
			The method is called only for the destination nodes. The real message acceptance is the node 
			responsability and may depend on the message content.
		*/
		virtual bool	accept(const Message* msg);

		/*!
			\brief handler for the \c 'get' message
			\param ipdest the output message destination IP
			
			The \c 'get' message is supported by every node:
			- it is propagated to the subnodes until it reaches terminal nodes
			- a terminal node send its state on \c 'get' request to the IP address given as parameter.
			The \c get method is basically called by the accept method.
		*/
		virtual void	get(unsigned long ipdest) const;

		/*!
			\brief handler for the \c 'get' 'attribute' message
			\param ipdest the output message destination IP
			\param what the requested attribute
			
			The \c 'get' message is supported by every node:
			- it is propagated to the subnodes until it reaches terminal nodes
			- a terminal node send its state on \c 'get' request to the IP address given as parameter.
			The \c get method is basically called by the accept method.
		*/
		virtual void	get(unsigned long ipdest, const std::string& what) const {}

		void			add(SMessageDriven node)	{ fSubNodes.push_back (node); }
		const char*		getName() const				{ return fName.c_str(); }
		std::string		getOSCAddress() const;
		int				size() const				{ return (int)fSubNodes.size (); }
		
		const std::string&	name() const			{ return fName; }
		SMessageDriven	subnode(int i)              { return fSubNodes[i]; }
};

} // end namespoace

#endif
/*

  Copyright (C) 2011  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __Message__
#define __Message__

#include <string>
#include <vector>

namespace oscfaust
{

class OSCStream;
template <typename T> class MsgParam;
class baseparam;
typedef SMARTP<baseparam>	Sbaseparam;

//--------------------------------------------------------------------------
/*!
	\brief base class of a message parameters
*/
class baseparam : public smartable
{
	public:
		virtual ~baseparam() {}

		/*!
		 \brief utility for parameter type checking
		*/
		template<typename X> bool isType() const { return dynamic_cast<const MsgParam<X>*> (this) != 0; }
		/*!
		 \brief utility for parameter convertion
		 \param errvalue the returned value when no conversion applies
		 \return the parameter value when the type matches
		*/
		template<typename X> X	value(X errvalue) const 
			{ const MsgParam<X>* o = dynamic_cast<const MsgParam<X>*> (this); return o ? o->getValue() : errvalue; }
		/*!
		 \brief utility for parameter comparison
		*/
		template<typename X> bool	equal(const baseparam& p) const 
			{ 
				const MsgParam<X>* a = dynamic_cast<const MsgParam<X>*> (this); 
				const MsgParam<X>* b = dynamic_cast<const MsgParam<X>*> (&p);
				return a && b && (a->getValue() == b->getValue());
			}
		/*!
		 \brief utility for parameter comparison
		*/
		bool operator==(const baseparam& p) const 
			{ 
				return equal<float>(p) || equal<int>(p) || equal<std::string>(p);
			}
		bool operator!=(const baseparam& p) const
			{ 
				return !equal<float>(p) && !equal<int>(p) && !equal<std::string>(p);
			}
			
		virtual SMARTP<baseparam> copy() const = 0;
};

//--------------------------------------------------------------------------
/*!
	\brief template for a message parameter
*/
template <typename T> class MsgParam : public baseparam
{
	T fParam;
	public:
				 MsgParam(T val) : fParam(val)	{}
		virtual ~MsgParam() {}
		
		T getValue() const { return fParam; }
		
		virtual Sbaseparam copy() const { return new MsgParam<T>(fParam); }
};

//--------------------------------------------------------------------------
/*!
	\brief a message description
	
	A message is composed of an address (actually an OSC address),
	a message string that may be viewed as a method name
	and a list of message parameters.
*/
class Message
{
    public:
        typedef SMARTP<baseparam>		argPtr;		///< a message argument ptr type
        typedef std::vector<argPtr>		argslist;	///< args list type

    private:
        unsigned long	fSrcIP;			///< the message source IP number
        std::string	fAddress;			///< the message osc destination address
        std::string	fAlias;             ///< the message alias osc destination address
        argslist	fArguments;			///< the message arguments

    public:
            /*!
                \brief an empty message constructor
            */
             Message() {}
            /*!
                \brief a message constructor
                \param address the message destination address
            */
            Message(const std::string& address) : fAddress(address), fAlias("") {}
             
            Message(const std::string& address, const std::string& alias) : fAddress(address), fAlias(alias) {}
            /*!
                \brief a message constructor
                \param address the message destination address
                \param args the message parameters
            */
            Message(const std::string& address, const argslist& args) 
                : fAddress(address), fArguments(args) {}
            /*!
                \brief a message constructor
                \param msg a message
            */
             Message(const Message& msg);
    virtual ~Message() {} //{ freed++; std::cout << "running messages: " << (allocated - freed) << std::endl; }

    /*!
        \brief adds a parameter to the message
        \param val the parameter
    */
    template <typename T> void add(T val)	{ fArguments.push_back(new MsgParam<T>(val)); }
    /*!
        \brief adds a float parameter to the message
        \param val the parameter value
    */
    void	add(float val)					{ add<float>(val); }
    
    /*!
     \brief adds a double parameter to the message
     \param val the parameter value
     */
    void	add(double val)					{ add<double>(val); }
    
    /*!
        \brief adds an int parameter to the message
        \param val the parameter value
    */
    void	add(int val)					{ add<int>(val); }
    
    /*!
        \brief adds a string parameter to the message
        \param val the parameter value
    */
    void	add(const std::string& val)		{ add<std::string>(val); }

    /*!
        \brief adds a parameter to the message
        \param val the parameter
    */
    void	add(argPtr val)                 { fArguments.push_back( val ); }

    /*!
        \brief sets the message address
        \param addr the address
    */
    void				setSrcIP(unsigned long addr)		{ fSrcIP = addr; }

    /*!
        \brief sets the message address
        \param addr the address
    */
    void				setAddress(const std::string& addr)		{ fAddress = addr; }
    /*!
        \brief print the message
        \param out the output stream
    */
    void				print(std::ostream& out) const;
    /*!
        \brief send the message to OSC
        \param out the OSC output stream
    */
    void				print(OSCStream& out) const;
    /*!
        \brief print message arguments
        \param out the OSC output stream
    */
    void				printArgs(OSCStream& out) const;

    /// \brief gives the message address
    const std::string&	address() const		{ return fAddress; }
    /// \brief gives the message alias
    const std::string&	alias() const		{ return fAlias; }
    /// \brief gives the message parameters list
    const argslist&		params() const		{ return fArguments; }
    /// \brief gives the message parameters list
    argslist&			params()			{ return fArguments; }
    /// \brief gives the message source IP 
    unsigned long		src() const			{ return fSrcIP; }
    /// \brief gives the message parameters count
    int					size() const		{ return (int)fArguments.size(); }

    bool operator == (const Message& other) const;	

    /*!
        \brief gives a message float parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, float& val) const		{ val = params()[i]->value<float>(val); return params()[i]->isType<float>(); }
    
    /*!
     \brief gives a message double parameter
     \param i the parameter index (0 <= i < size())
     \param val on output: the parameter value when the parameter type matches
     \return false when types don't match
     */
    bool	param(int i, double& val) const		{ val = params()[i]->value<double>(val); return params()[i]->isType<double>(); }
    
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, int& val) const		{ val = params()[i]->value<int>(val); return params()[i]->isType<int>(); }
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, unsigned int& val) const		{ val = params()[i]->value<int>(val); return params()[i]->isType<int>(); }
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
        \note a boolean value is handled as integer
    */
    bool	param(int i, bool& val) const		{ int ival = 0; ival = params()[i]->value<int>(ival); val = ival!=0; return params()[i]->isType<int>(); }
    /*!
        \brief gives a message int parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, long int& val) const	{ val = long(params()[i]->value<int>(val)); return params()[i]->isType<int>(); }
    /*!
        \brief gives a message string parameter
        \param i the parameter index (0 <= i < size())
        \param val on output: the parameter value when the parameter type matches
        \return false when types don't match
    */
    bool	param(int i, std::string& val) const { val = params()[i]->value<std::string>(val); return params()[i]->isType<std::string>(); }
};


} // end namespoace

#endif
/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __RootNode__
#define __RootNode__

#include <map>
#include <string>
#include <vector>


namespace oscfaust
{

class OSCIO;
class RootNode;
typedef class SMARTP<RootNode> SRootNode;

/**
 * an alias target includes a map to rescale input values to output values
 * and a target osc address. The input values can be given in reversed order
 * to reverse the control
 */
struct aliastarget
{
	double      fMinIn;
	double      fMaxIn;
	double      fMinOut;
	double      fMaxOut;
	std::string fTarget;	// the real osc address

	aliastarget(const char* address, double imin, double imax, double omin, double omax)
		: fMinIn(imin), fMaxIn(imax), fMinOut(omin), fMaxOut(omax), fTarget(address) {}

	aliastarget(const aliastarget& t)
		: fMinIn(t.fMinIn), fMaxIn(t.fMaxIn), fMinOut(t.fMinOut), fMaxOut(t.fMaxOut), fTarget(t.fTarget) {}

	double scale(double x) const 
    {
        if (fMinIn < fMaxIn) {
            // increasing control
            double z = (x < fMinIn) ? fMinIn : (x > fMaxIn) ? fMaxIn : x;
            return fMinOut + (z-fMinIn)*(fMaxOut-fMinOut)/(fMaxIn-fMinIn);
            
        } else if (fMinIn > fMaxIn) {
            // reversed control
            double z = (x < fMaxIn) ? fMaxIn : (x > fMinIn) ? fMinIn : x;
            return fMinOut + (fMinIn-z)*(fMaxOut-fMinOut)/(fMinIn-fMaxIn);
            
        } else {
            // no control !
            return (fMinOut+fMaxOut)/2.0f;
        }
    }
    
    double invscale(double x) const
    {
        if (fMinOut < fMaxOut) {
            // increasing control
            double z = (x < fMinOut) ? fMinOut : (x > fMaxOut) ? fMaxOut : x;
            return fMinIn + (z-fMinOut)*(fMaxIn-fMinIn)/(fMaxOut-fMinOut);
            
        } else if (fMinOut > fMaxOut) {
            // reversed control
            double z = (x < fMaxOut) ? fMaxOut : (x > fMinOut) ? fMinOut : x;
            return fMinIn + (fMinOut-z)*(fMaxIn-fMinIn)/(fMinOut-fMaxOut);
            
        } else {
            // no control !
            return (fMinIn+fMaxIn)/2.0f;
        }
    }
};

//--------------------------------------------------------------------------
/*!
	\brief a faust root node

	A Faust root node handles the \c 'hello' message and provides support
	for incoming osc signal data. 
*/
class RootNode : public MessageDriven
{

    private:
        int *fUPDIn, *fUDPOut, *fUDPErr;    // the osc port numbers (required by the hello method)
        OSCIO* fIO;                         // an OSC IO controler
        JSONUI* fJSON;

        typedef std::map<std::string, std::vector<aliastarget> > TAliasMap;
        TAliasMap fAliases;

        template <typename T>
        void processAliasAux(const std::string& address, T val);
        void processAlias(const std::string& address, float val);
        void processAlias(const std::string& address, double val);
    
        void eraseAliases(const std::string& target);
        void eraseAlias(const std::string& target, const std::string& alias);
        bool aliasError(const Message* msg);

    protected:
        RootNode(const char *name, JSONUI* json, OSCIO* io = NULL) : MessageDriven(name, ""), fUPDIn(0), fUDPOut(0), fUDPErr(0), fIO(io), fJSON(json) {}
        virtual ~RootNode() {}

    public:
        static SRootNode create(const char* name, JSONUI* json, OSCIO* io = NULL) { return new RootNode(name, json, io); }

        virtual void processMessage(const Message* msg);
        virtual bool accept(const Message* msg);
        virtual void get(unsigned long ipdest) const;
        virtual void get(unsigned long ipdest, const std::string& what) const;

        template <typename T>
        bool aliasMsgAux(const Message* msg, T omin, T omax);
        bool aliasMsg(const Message* msg, double omin, double omax);
        bool aliasMsg(const Message* msg, float omin, float omax);
    
        template <typename T>
        void addAliasAux(const char* alias, const char* address, T imin, T imax, T omin, T omax);
        void addAlias(const char* alias, const char* address, float imin, float imax, float omin, float omax);
        void addAlias(const char* alias, const char* address, double imin, double imax, double omin, double omax);
    
        bool acceptSignal(const Message* msg);      ///< handler for signal data
        void hello(unsigned long ipdest) const;     ///< handler for the 'hello' message
        void setPorts(int* in, int* out, int* err);

        std::vector<std::pair<std::string, double> > getAliases(const std::string& address, double value);
};

} // end namespoace

#endif

namespace oscfaust
{

/**
 * map (rescale) input values to output values
 */
template <typename C> struct mapping
{
	const C fMinOut;
	const C fMaxOut;
	mapping(C omin, C omax) : fMinOut(omin), fMaxOut(omax) {}
	C clip (C x) { return (x < fMinOut) ? fMinOut : (x > fMaxOut) ? fMaxOut : x; }
};

//--------------------------------------------------------------------------
/*!
	\brief a faust node is a terminal node and represents a faust parameter controler
*/
template <typename C> class FaustNode : public MessageDriven, public uiTypedItemReal<C>
{
	mapping<C>	fMapping;
    RootNode*   fRoot;
    bool        fInput;  // true for input nodes (slider, button...)
	
	//---------------------------------------------------------------------
	// Warning !!!
	// The cast (C*)fZone is necessary because the real size allocated is
	// only known at execution time. When the library is compiled, fZone is
	// uniquely defined by FAUSTFLOAT.
	//---------------------------------------------------------------------
	bool store(C val) { *(C*)this->fZone = fMapping.clip(val); return true; }
	void sendOSC() const;

	protected:
		FaustNode(RootNode* root, const char *name, C* zone, C init, C min, C max, const char* prefix, GUI* ui, bool initZone, bool input) 
			: MessageDriven(name, prefix), uiTypedItemReal<C>(ui, zone), fMapping(min, max), fRoot(root), fInput(input)
			{
                if (initZone) {
                    *zone = init; 
                }
            }
			
		virtual ~FaustNode() {}

	public:
		typedef SMARTP<FaustNode<C> > SFaustNode;
		static SFaustNode create(RootNode* root, const char* name, C* zone, C init, C min, C max, const char* prefix, GUI* ui, bool initZone, bool input)	
        { 
            SFaustNode node = new FaustNode(root, name, zone, init, min, max, prefix, ui, initZone, input); 
            /*
                Since FaustNode is a subclass of uiItem, the pointer will also be kept in the GUI class, and it's desallocation will be done there.
                So we don't want to have smartpointer logic desallocate it and we increment the refcount.
            */
            node->addReference();
            return node; 
        }
    
		bool accept(const Message* msg);
		void get(unsigned long ipdest) const;		///< handler for the 'get' message
		virtual void reflectZone() { sendOSC(); this->fCache = *this->fZone; }
};

} // end namespace

#endif

class GUI;
namespace oscfaust
{

class OSCIO;
class RootNode;
typedef class SMARTP<RootNode> SRootNode;
class MessageDriven;
typedef class SMARTP<MessageDriven>	SMessageDriven;

//--------------------------------------------------------------------------
/*!
	\brief a factory to build a OSC UI hierarchy
	
	Actually, makes use of a stack to build the UI hierarchy.
	It includes a pointer to a OSCIO controler, but just to give it to the root node.
*/
class FaustFactory
{
    std::stack<SMessageDriven>  fNodes;		///< maintains the current hierarchy level
    SRootNode  fRoot;   ///< keep track of the root node
    OSCIO*     fIO;     ///< hack to support audio IO via OSC, actually the field is given to the root node
    GUI*       fGUI;    ///< a GUI pointer to support updateAllGuis(), required for bi-directionnal OSC
    JSONUI*    fJSON;
    
    private:
        std::string addressFirst(const std::string& address) const;
        std::string addressTail(const std::string& address) const;
        
    public:
        FaustFactory(GUI* ui, JSONUI* json, OSCIO * io = NULL);
        virtual ~FaustFactory();
        
        template <typename C> void addnode(const char* label, C* zone, C init, C min, C max, bool initZone, bool input);
        template <typename C> void addAlias(const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max, const char* label);
        
        void addAlias(const char* alias, const char* address, float imin, float imax, float omin, float omax);
        void addAlias(const char* alias, const char* address, double imin, double imax, double omin, double omax);
        void opengroup(const char* label);
        void closegroup();
        
        SRootNode root() const; 
};

/**
 * Add a node to the OSC UI tree in the current group at the top of the stack 
 */
template <typename C> void FaustFactory::addnode(const char* label, C* zone, C init, C min, C max, bool initZone, bool input) 
{
	SMessageDriven top;
	if (fNodes.size()) top = fNodes.top();
	if (top) {
		std::string prefix = top->getOSCAddress();
		top->add(FaustNode<C>::create(root(), label, zone, init, min, max, prefix.c_str(), fGUI, initZone, input));
	}
}

/**
 * Add an alias (actually stored and handled at root node level
 */
template <typename C> void FaustFactory::addAlias(const std::string& fullpath, C* zone, C imin, C imax, C init, C min, C max, const char* label)
{
	std::istringstream 	ss(fullpath);
	std::string 		realpath; 
 
	ss >> realpath >> imin >> imax;
	SMessageDriven top = fNodes.top();
	if (top) {
		std::string target = top->getOSCAddress() + "/" + label;
		addAlias(realpath.c_str(), target.c_str(), C(imin), C(imax), C(min), C(max));
	}
}

} // end namespoace

#endif

class GUI;

typedef void (*ErrorCallback)(void*);  

namespace oscfaust
{

class OSCIO;
class OSCSetup;
class OSCRegexp;
    
//--------------------------------------------------------------------------
/*!
	\brief the main Faust OSC Lib API
	
	The OSCControler is essentially a glue between the memory representation (in charge of the FaustFactory),
	and the network services (in charge of OSCSetup).
*/
class OSCControler
{
	int fUDPPort,   fUDPOut, fUPDErr;	// the udp ports numbers
	std::string     fDestAddress;		// the osc messages destination address, used at initialization only
										// to collect the address from the command line
	std::string     fBindAddress;		// when non empty, the address used to bind the socket for listening
	OSCSetup*		fOsc;				// the network manager (handles the udp sockets)
	OSCIO*			fIO;				// hack for OSC IO support (actually only relayed to the factory)
	FaustFactory*	fFactory;			// a factory to build the memory representation

    bool            fInit;
    
	public:
		/*
			base udp port is chosen in an unassigned range from IANA PORT NUMBERS (last updated 2011-01-24)
			see at http://www.iana.org/assignments/port-numbers
			5507-5552  Unassigned
		*/
		enum { kUDPBasePort = 5510 };
            
        OSCControler(int argc, char* argv[], GUI* ui, JSONUI* json, OSCIO* io = NULL, ErrorCallback errCallback = NULL, void* arg = NULL, bool init = true);

        virtual ~OSCControler();
	
		//--------------------------------------------------------------------------
		// addnode, opengroup and closegroup are simply relayed to the factory
		//--------------------------------------------------------------------------
		// Add a node in the current group (top of the group stack)
		template <typename T> void addnode(const char* label, T* zone, T init, T min, T max, bool input = true)
							{ fFactory->addnode(label, zone, init, min, max, fInit, input); }
		
		//--------------------------------------------------------------------------
		// This method is used for alias messages. The arguments imin and imax allow
		// to map incomming values from the alias input range to the actual range 
		template <typename T> void addAlias(const std::string& fullpath, T* zone, T imin, T imax, T init, T min, T max, const char* label)
							{ fFactory->addAlias(fullpath, zone, imin, imax, init, min, max, label); }

		void opengroup(const char* label)		{ fFactory->opengroup(label); }
		void closegroup()						{ fFactory->closegroup(); }
	   
		//--------------------------------------------------------------------------
		void run();				// starts the network services
		void endBundle();		// when bundle mode is on, close and send the current bundle (if any)
		void stop();			// stop the network services
		std::string getInfos() const; // gives information about the current environment (version, port numbers,...)

		int	getUDPPort() const			{ return fUDPPort; }
		int	getUDPOut()	const			{ return fUDPOut; }
		int	getUDPErr()	const			{ return fUPDErr; }
		const char*	getDestAddress() const { return fDestAddress.c_str(); }
		const char*	getRootName() const;	// probably useless, introduced for UI extension experiments
    
        void setUDPPort(int port) { fUDPPort = port; }
        void setUDPOut(int port) { fUDPOut = port; }
        void setUDPErr(int port) { fUPDErr = port; }
        void setDestAddress(const char* address) { fDestAddress = address; }

        // By default, an osc interface emits all parameters. You can filter specific params dynamically.
        static std::vector<OSCRegexp*>     fFilteredPaths; // filtered paths will not be emitted
        static void addFilteredPath(std::string path);
        static bool isPathFiltered(std::string path);
        static void resetFilteredPaths();
    
		static float version();				// the Faust OSC library version number
		static const char* versionstr();	// the Faust OSC library version number as a string
		static int gXmit;                   // a static variable to control the transmission of values
                                            // i.e. the use of the interface as a controler
		static int gBundle;                 // a static variable to control the osc bundle mode
};

#define kNoXmit     0
#define kAll        1
#define kAlias      2

}

#endif

#ifdef _WIN32
#define strcasecmp _stricmp
#endif

/******************************************************************************
 *******************************************************************************
 
 OSC (Open Sound Control) USER INTERFACE
 
 *******************************************************************************
 *******************************************************************************/
/*
 
 Note about the OSC addresses and the Faust UI names:
 ----------------------------------------------------
 There are potential conflicts between the Faust UI objects naming scheme and
 the OSC address space. An OSC symbolic names is an ASCII string consisting of
 printable characters other than the following:
	space
 #	number sign
 *	asterisk
 ,	comma
 /	forward
 ?	question mark
 [	open bracket
 ]	close bracket
 {	open curly brace
 }	close curly brace
 
 a simple solution to address the problem consists in replacing
 space or tabulation with '_' (underscore)
 all the other osc excluded characters with '-' (hyphen)
 
 This solution is implemented in the proposed OSC UI;
 */

class OSCUI : public GUI
{
    
    private:
        
        oscfaust::OSCControler*	fCtrl;
        std::vector<const char*> fAlias;
        JSONUI fJSON;
        
        const char* tr(const char* label) const
        {
            static char buffer[1024];
            char* ptr = buffer; int n = 1;
            while (*label && (n++ < 1024)) {
                switch (*label) {
                    case ' ': case '	':
                        *ptr++ = '_';
                        break;
                    case '#': case '*': case ',': case '/': case '?':
                    case '[': case ']': case '{': case '}': case '(': case ')':
                        *ptr++ = '_';
                        break;
                    default:
                        *ptr++ = *label;
                }
                label++;
            }
            *ptr = 0;
            return buffer;
        }
        
        // add all accumulated alias
        void addalias(FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, const char* label)
        {
            for (unsigned int i = 0; i < fAlias.size(); i++) {
                fCtrl->addAlias(fAlias[i], zone, FAUSTFLOAT(0), FAUSTFLOAT(1), init, min, max, label);
            }
            fAlias.clear();
        }
        
    public:
        
        OSCUI(const char* /*applicationname*/, int argc, char* argv[],
              oscfaust::OSCIO* io = NULL,
              ErrorCallback errCallback = NULL,
              void* arg = NULL,
              bool init = true) : GUI()
        {
            fCtrl = new oscfaust::OSCControler(argc, argv, this, &fJSON, io, errCallback, arg, init);
            // fCtrl->opengroup(applicationname);
        }
        
        virtual ~OSCUI() { delete fCtrl; }
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)          { fCtrl->opengroup(tr(label)); fJSON.openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fCtrl->opengroup(tr(label)); fJSON.openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fCtrl->opengroup(tr(label)); fJSON.openVerticalBox(label); }
        virtual void closeBox()                             { fCtrl->closegroup(); fJSON.closeBox(); }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            const char* l = tr(label);
            addalias(zone, 0, 0, 1, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(1));
            fJSON.addButton(label, zone);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            const char* l = tr(label);
            addalias(zone, 0, 0, 1, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), FAUSTFLOAT(0), FAUSTFLOAT(1));
            fJSON.addCheckButton(label, zone);
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            const char* l = tr(label);
            addalias(zone, init, min, max, l);
            fCtrl->addnode(l, zone, init, min, max);
            fJSON.addVerticalSlider(label, zone, init, min, max, step);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            const char* l = tr(label);
            addalias(zone, init, min, max, l);
            fCtrl->addnode(l, zone, init, min, max);
            fJSON.addHorizontalSlider(label, zone, init, min, max, step);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            const char* l = tr(label);
            addalias(zone, init, min, max, l);
            fCtrl->addnode(l, zone, init, min, max);
            fJSON.addNumEntry(label, zone, init, min, max, step);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            const char* l = tr(label);
            addalias(zone, 0, min, max, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), min, max, false);
            fJSON.addHorizontalBargraph(label, zone, min, max);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            const char* l = tr(label);
            addalias(zone, 0, min, max, l);
            fCtrl->addnode(l, zone, FAUSTFLOAT(0), min, max, false);
            fJSON.addVerticalBargraph(label, zone, min, max);
        }
            
        // -- metadata declarations
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* alias)
        {
            if (strcasecmp(key, "OSC") == 0) fAlias.push_back(alias);
            fJSON.declare(zone, key, alias);
        }
        
        bool run()
        {
            fCtrl->run();
            return true;
        }
        
        void stop()			{ fCtrl->stop(); }
        void endBundle() 	{ fCtrl->endBundle(); }
        
        std::string getInfos()          { return fCtrl->getInfos(); }
        
        const char* getRootName()		{ return fCtrl->getRootName(); }
        int getUDPPort()                { return fCtrl->getUDPPort(); }
        int getUDPOut()                 { return fCtrl->getUDPOut(); }
        int getUDPErr()                 { return fCtrl->getUDPErr(); }
        const char* getDestAddress()    { return fCtrl->getDestAddress(); }
        
        void setUDPPort(int port)       { fCtrl->setUDPPort(port); }
        void setUDPOut(int port)        { fCtrl->setUDPOut(port); }
        void setUDPErr(int port)        { fCtrl->setUDPErr(port); }
        void setDestAddress(const char* address)    { return fCtrl->setDestAddress(address); }
    
};

#endif // __OSCUI__
/**************************  END  OSCUI.h **************************/

static void osc_compute_callback(void* arg)
{
    static_cast<OSCUI*>(arg)->endBundle();
}

#endif

//**************************************************************
// Intrinsic
//**************************************************************


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp2
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float mydsp2_faustpower2_f(float value) {
	return value * value;
}

class mydsp2 : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fVec0[2];
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	int iTempPerm0;
	int iVec1[2];
	int iTempPerm1;
	int iRec2[2];
	int iTempPerm2;
	float fConst2;
	float fRec4[2];
	FAUSTFLOAT fHslider3;
	int iTempPerm3;
	int iRec0[2];
	float fTempPerm4;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider4;
	float fVec2[2];
	float fRec8[2];
	int iTempPerm5;
	int iVec3[2];
	int iTempPerm6;
	int iRec7[2];
	int iTempPerm7;
	float fRec9[2];
	int iTempPerm8;
	int iRec5[2];
	float fTempPerm9;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fHslider5;
	float fVec4[2];
	float fRec13[2];
	int iTempPerm10;
	int iVec5[2];
	int iTempPerm11;
	int iRec12[2];
	int iTempPerm12;
	float fRec14[2];
	int iTempPerm13;
	int iRec10[2];
	float fTempPerm14;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHslider6;
	float fVec6[2];
	float fRec18[2];
	int iTempPerm15;
	int iVec7[2];
	int iTempPerm16;
	int iRec17[2];
	int iTempPerm17;
	float fRec19[2];
	int iTempPerm18;
	int iRec15[2];
	float fTempPerm19;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fHslider7;
	float fVec8[2];
	float fRec23[2];
	int iTempPerm20;
	int iVec9[2];
	int iTempPerm21;
	int iRec22[2];
	int iTempPerm22;
	float fRec24[2];
	int iTempPerm23;
	int iRec20[2];
	float fTempPerm24;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fHslider8;
	float fVec10[2];
	float fRec28[2];
	int iTempPerm25;
	int iVec11[2];
	int iTempPerm26;
	int iRec27[2];
	int iTempPerm27;
	float fRec29[2];
	int iTempPerm28;
	int iRec25[2];
	float fTempPerm29;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fHslider10;
	float fVec12[2];
	float fRec30[2];
	float fTempPerm30;
	float fTempPerm31;
	FAUSTFLOAT fCheckbox9;
	FAUSTFLOAT fCheckbox10;
	FAUSTFLOAT fCheckbox11;
	FAUSTFLOAT fHslider11;
	float fVec13[2];
	float fRec31[2];
	float fTempPerm32;
	float fTempPerm33;
	FAUSTFLOAT fCheckbox12;
	FAUSTFLOAT fCheckbox13;
	FAUSTFLOAT fCheckbox14;
	FAUSTFLOAT fHslider12;
	float fVec14[2];
	float fRec32[2];
	float fTempPerm34;
	float fTempPerm35;
	FAUSTFLOAT fCheckbox15;
	FAUSTFLOAT fHslider13;
	float fVec15[2];
	float fRec33[2];
	float fTempPerm36;
	float fTempPerm37;
	FAUSTFLOAT fCheckbox16;
	FAUSTFLOAT fHslider14;
	float fVec16[2];
	float fRec34[2];
	float fTempPerm38;
	float fTempPerm39;
	FAUSTFLOAT fCheckbox17;
	FAUSTFLOAT fHslider15;
	float fVec17[2];
	float fRec35[2];
	float fTempPerm40;
	float fTempPerm41;
	FAUSTFLOAT fCheckbox18;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	float fVec18[2];
	float fRec36[2];
	float fTempPerm42;
	FAUSTFLOAT fCheckbox19;
	FAUSTFLOAT fHslider18;
	float fVec19[2];
	float fRec37[2];
	float fTempPerm43;
	FAUSTFLOAT fCheckbox20;
	FAUSTFLOAT fHslider19;
	float fVec20[2];
	float fRec38[2];
	float fTempPerm44;
	FAUSTFLOAT fCheckbox21;
	FAUSTFLOAT fHslider20;
	float fVec21[2];
	float fRec39[2];
	float fTempPerm45;
	FAUSTFLOAT fCheckbox22;
	FAUSTFLOAT fHslider21;
	float fVec22[2];
	float fRec40[2];
	float fTempPerm46;
	FAUSTFLOAT fCheckbox23;
	FAUSTFLOAT fHslider22;
	float fVec23[2];
	float fRec41[2];
	float fTempPerm47;
	FAUSTFLOAT fCheckbox24;
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT fCheckbox25;
	FAUSTFLOAT fCheckbox26;
	FAUSTFLOAT fCheckbox27;
	float fConst4;
	FAUSTFLOAT fHslider24;
	float fVec24[2];
	float fConst5;
	float fRec44[2];
	FAUSTFLOAT fHslider25;
	float fTempPerm48;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT fHslider27;
	float fTempPerm49;
	float fRec43[2];
	float fRec42[2];
	float fTempPerm50;
	FAUSTFLOAT fCheckbox28;
	FAUSTFLOAT fCheckbox29;
	FAUSTFLOAT fCheckbox30;
	FAUSTFLOAT fHslider28;
	float fVec25[2];
	float fRec47[2];
	float fTempPerm51;
	float fTempPerm52;
	float fRec46[2];
	float fRec45[2];
	float fTempPerm53;
	FAUSTFLOAT fCheckbox31;
	FAUSTFLOAT fCheckbox32;
	FAUSTFLOAT fCheckbox33;
	FAUSTFLOAT fHslider29;
	float fVec26[2];
	float fRec50[2];
	float fTempPerm54;
	float fTempPerm55;
	float fRec49[2];
	float fRec48[2];
	float fTempPerm56;
	float fTempPerm57;
	float fTempPerm58;
	float fRec52[2];
	float fRec51[2];
	float fTempPerm59;
	float fTempPerm60;
	float fTempPerm61;
	float fRec54[2];
	float fRec53[2];
	float fTempPerm62;
	float fTempPerm63;
	float fTempPerm64;
	float fRec56[2];
	float fRec55[2];
	float fTempPerm65;
	float fTempPerm66;
	float fTempPerm67;
	float fRec58[2];
	float fRec57[2];
	float fTempPerm68;
	float fTempPerm69;
	float fTempPerm70;
	float fRec60[2];
	float fRec59[2];
	float fTempPerm71;
	float fTempPerm72;
	float fTempPerm73;
	float fRec62[2];
	float fRec61[2];
	float fTempPerm74;
	float fTempPerm75;
	float fTempPerm76;
	float fRec64[2];
	float fRec63[2];
	float fTempPerm77;
	FAUSTFLOAT fCheckbox34;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT fCheckbox35;
	FAUSTFLOAT fCheckbox36;
	FAUSTFLOAT fCheckbox37;
	FAUSTFLOAT fCheckbox38;
	float fConst6;
	FAUSTFLOAT fHslider31;
	float fConst7;
	float fRec67[2];
	FAUSTFLOAT fHslider32;
	float fTempPerm78;
	FAUSTFLOAT fHslider33;
	FAUSTFLOAT fHslider34;
	float fTempPerm79;
	float fRec66[2];
	float fRec65[2];
	float fTempPerm80;
	FAUSTFLOAT fCheckbox39;
	FAUSTFLOAT fCheckbox40;
	FAUSTFLOAT fCheckbox41;
	FAUSTFLOAT fHslider35;
	float fRec70[2];
	float fTempPerm81;
	float fTempPerm82;
	float fRec69[2];
	float fRec68[2];
	float fTempPerm83;
	FAUSTFLOAT fCheckbox42;
	FAUSTFLOAT fCheckbox43;
	FAUSTFLOAT fCheckbox44;
	FAUSTFLOAT fHslider36;
	float fRec73[2];
	float fTempPerm84;
	float fTempPerm85;
	float fRec72[2];
	float fRec71[2];
	float fTempPerm86;
	float fTempPerm87;
	float fTempPerm88;
	float fRec75[2];
	float fRec74[2];
	float fTempPerm89;
	float fTempPerm90;
	float fTempPerm91;
	float fRec77[2];
	float fRec76[2];
	float fTempPerm92;
	float fTempPerm93;
	float fTempPerm94;
	float fRec79[2];
	float fRec78[2];
	float fTempPerm95;
	float fTempPerm96;
	float fTempPerm97;
	float fRec81[2];
	float fRec80[2];
	float fTempPerm98;
	float fTempPerm99;
	float fTempPerm100;
	float fRec83[2];
	float fRec82[2];
	float fTempPerm101;
	float fTempPerm102;
	float fTempPerm103;
	float fRec85[2];
	float fRec84[2];
	float fTempPerm104;
	float fTempPerm105;
	float fTempPerm106;
	float fTempPerm107;
	float fRec87[2];
	float fRec86[2];
	float fTempPerm108;
	FAUSTFLOAT fCheckbox45;
	float fConst8;
	float fConst9;
	FAUSTFLOAT fHslider37;
	FAUSTFLOAT fCheckbox46;
	FAUSTFLOAT fCheckbox47;
	FAUSTFLOAT fCheckbox48;
	FAUSTFLOAT fCheckbox49;
	FAUSTFLOAT fCheckbox50;
	FAUSTFLOAT fCheckbox51;
	float fTempPerm109;
	FAUSTFLOAT fCheckbox52;
	float fTempPerm110;
	float fTempPerm111;
	FAUSTFLOAT fCheckbox53;
	float fTempPerm112;
	float fTempPerm113;
	float fRec88[2];
	float fTempPerm114;
	FAUSTFLOAT fHslider38;
	float fTempPerm115;
	float fTempPerm116;
	float fRec89[2];
	float fTempPerm117;
	FAUSTFLOAT fHslider39;
	float fRec90[2];
	float fTempPerm118;
	FAUSTFLOAT fHslider40;
	float fRec91[2];
	float fTempPerm119;
	FAUSTFLOAT fHslider41;
	float fTempPerm120;
	float fRec92[2];
	float fTempPerm121;
	FAUSTFLOAT fHslider42;
	float fRec93[2];
	float fTempPerm122;
	FAUSTFLOAT fCheckbox54;
	FAUSTFLOAT fCheckbox55;
	FAUSTFLOAT fCheckbox56;
	FAUSTFLOAT fCheckbox57;
	FAUSTFLOAT fCheckbox58;
	FAUSTFLOAT fCheckbox59;
	float fTempPerm123;
	float fTempPerm124;
	float fTempPerm125;
	float fTempPerm126;
	float fTempPerm127;
	float fRec94[2];
	float fTempPerm128;
	float fTempPerm129;
	float fTempPerm130;
	float fRec95[2];
	float fTempPerm131;
	float fRec96[2];
	float fTempPerm132;
	float fRec97[2];
	float fTempPerm133;
	float fTempPerm134;
	float fRec98[2];
	float fTempPerm135;
	float fRec99[2];
	float fTempPerm136;
	FAUSTFLOAT fCheckbox60;
	FAUSTFLOAT fCheckbox61;
	FAUSTFLOAT fCheckbox62;
	FAUSTFLOAT fCheckbox63;
	FAUSTFLOAT fCheckbox64;
	FAUSTFLOAT fCheckbox65;
	FAUSTFLOAT fCheckbox66;
	FAUSTFLOAT fCheckbox67;
	float fTempPerm137;
	FAUSTFLOAT fCheckbox68;
	FAUSTFLOAT fCheckbox69;
	float fTempPerm138;
	float fTempPerm139;
	FAUSTFLOAT fCheckbox70;
	float fTempPerm140;
	float fTempPerm141;
	float fRec100[2];
	float fTempPerm142;
	float fTempPerm143;
	float fTempPerm144;
	float fRec101[2];
	float fTempPerm145;
	float fRec102[2];
	float fTempPerm146;
	float fRec103[2];
	float fTempPerm147;
	float fTempPerm148;
	float fRec104[2];
	float fTempPerm149;
	float fRec105[2];
	float fTempPerm150;
	FAUSTFLOAT fCheckbox71;
	FAUSTFLOAT fCheckbox72;
	FAUSTFLOAT fCheckbox73;
	FAUSTFLOAT fCheckbox74;
	FAUSTFLOAT fCheckbox75;
	FAUSTFLOAT fCheckbox76;
	float fTempPerm151;
	float fTempPerm152;
	float fTempPerm153;
	float fTempPerm154;
	float fTempPerm155;
	float fRec106[2];
	float fTempPerm156;
	float fTempPerm157;
	float fTempPerm158;
	float fRec107[2];
	float fTempPerm159;
	float fRec108[2];
	float fTempPerm160;
	float fRec109[2];
	float fTempPerm161;
	float fTempPerm162;
	float fRec110[2];
	float fTempPerm163;
	float fRec111[2];
	float fTempPerm164;
	FAUSTFLOAT fCheckbox77;
	FAUSTFLOAT fCheckbox78;
	FAUSTFLOAT fCheckbox79;
	FAUSTFLOAT fCheckbox80;
	FAUSTFLOAT fCheckbox81;
	FAUSTFLOAT fCheckbox82;
	FAUSTFLOAT fCheckbox83;
	float fTempPerm165;
	FAUSTFLOAT fCheckbox84;
	float fTempPerm166;
	float fTempPerm167;
	FAUSTFLOAT fCheckbox85;
	float fTempPerm168;
	float fTempPerm169;
	float fRec112[2];
	float fTempPerm170;
	float fTempPerm171;
	float fTempPerm172;
	float fRec113[2];
	float fTempPerm173;
	float fRec114[2];
	float fTempPerm174;
	float fRec115[2];
	float fTempPerm175;
	float fTempPerm176;
	float fRec116[2];
	float fTempPerm177;
	float fRec117[2];
	float fTempPerm178;
	FAUSTFLOAT fCheckbox86;
	FAUSTFLOAT fCheckbox87;
	FAUSTFLOAT fCheckbox88;
	FAUSTFLOAT fCheckbox89;
	FAUSTFLOAT fCheckbox90;
	FAUSTFLOAT fCheckbox91;
	float fTempPerm179;
	float fTempPerm180;
	float fTempPerm181;
	float fTempPerm182;
	float fTempPerm183;
	float fRec118[2];
	float fTempPerm184;
	float fTempPerm185;
	float fTempPerm186;
	float fRec119[2];
	float fTempPerm187;
	float fRec120[2];
	float fTempPerm188;
	float fRec121[2];
	float fTempPerm189;
	float fTempPerm190;
	float fRec122[2];
	float fTempPerm191;
	float fRec123[2];
	float fTempPerm192;
	float fTempPerm193;
	float fTempPerm194;
	float fTempPerm195;
	float fTempPerm196;
	float fTempPerm197;
	float fTempPerm198;
	float fTempPerm199;
	float fTempPerm200;
	float fTempPerm201;
	float fTempPerm202;
	float fTempPerm203;
	float fTempPerm204;
	float fTempPerm205;
	float fTempPerm206;
	float fTempPerm207;
	float fTempPerm208;
	float fTempPerm209;
	float fTempPerm210;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.1");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.4");
		m->declare("compile_options", "-a /usr/local/share/faust/api-allen/motion/DspFaustMotion.cpp -lang cpp -i -cn mydsp2 -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "motion_v7c.lib");
		m->declare("filters.lib/dcblockerat:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblockerat:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblockerat:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "Faust Motion Library [Motion+RotationMatrix]");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.1");
		m->declare("version", "0.7");
	}

	virtual int getNumInputs() {
		return 18;
	}
	virtual int getNumOutputs() {
		return 92;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.14159274f / fConst0;
		fConst2 = 1.0f / fConst0;
		float fConst3 = 37.6991119f / fConst0;
		fConst4 = 1.0f / (fConst3 + 1.0f);
		fConst5 = 1.0f - fConst3;
		fConst6 = 44.0999985f / fConst0;
		fConst7 = 1.0f - fConst6;
		fConst8 = std::exp(0.0f - 100.0f / fConst0);
		fConst9 = 1.0f - fConst8;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.75f);
		fHslider3 = FAUSTFLOAT(75.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fCheckbox2 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fCheckbox3 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fCheckbox4 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
		fCheckbox5 = FAUSTFLOAT(0.0f);
		fHslider8 = FAUSTFLOAT(0.0f);
		fCheckbox6 = FAUSTFLOAT(0.0f);
		fCheckbox7 = FAUSTFLOAT(0.0f);
		fCheckbox8 = FAUSTFLOAT(0.0f);
		fHslider9 = FAUSTFLOAT(1.5f);
		fHslider10 = FAUSTFLOAT(0.0f);
		fCheckbox9 = FAUSTFLOAT(0.0f);
		fCheckbox10 = FAUSTFLOAT(0.0f);
		fCheckbox11 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(0.0f);
		fCheckbox12 = FAUSTFLOAT(0.0f);
		fCheckbox13 = FAUSTFLOAT(0.0f);
		fCheckbox14 = FAUSTFLOAT(0.0f);
		fHslider12 = FAUSTFLOAT(0.0f);
		fCheckbox15 = FAUSTFLOAT(0.0f);
		fHslider13 = FAUSTFLOAT(0.0f);
		fCheckbox16 = FAUSTFLOAT(0.0f);
		fHslider14 = FAUSTFLOAT(0.0f);
		fCheckbox17 = FAUSTFLOAT(0.0f);
		fHslider15 = FAUSTFLOAT(0.0f);
		fCheckbox18 = FAUSTFLOAT(0.0f);
		fHslider16 = FAUSTFLOAT(0.080000000000000002f);
		fHslider17 = FAUSTFLOAT(0.0f);
		fCheckbox19 = FAUSTFLOAT(0.0f);
		fHslider18 = FAUSTFLOAT(0.0f);
		fCheckbox20 = FAUSTFLOAT(0.0f);
		fHslider19 = FAUSTFLOAT(0.0f);
		fCheckbox21 = FAUSTFLOAT(0.0f);
		fHslider20 = FAUSTFLOAT(0.0f);
		fCheckbox22 = FAUSTFLOAT(0.0f);
		fHslider21 = FAUSTFLOAT(0.0f);
		fCheckbox23 = FAUSTFLOAT(0.0f);
		fHslider22 = FAUSTFLOAT(0.0f);
		fCheckbox24 = FAUSTFLOAT(0.0f);
		fHslider23 = FAUSTFLOAT(1.3500000000000001f);
		fCheckbox25 = FAUSTFLOAT(0.0f);
		fCheckbox26 = FAUSTFLOAT(0.0f);
		fCheckbox27 = FAUSTFLOAT(0.0f);
		fHslider24 = FAUSTFLOAT(0.0f);
		fHslider25 = FAUSTFLOAT(0.10000000000000001f);
		fHslider26 = FAUSTFLOAT(10.0f);
		fHslider27 = FAUSTFLOAT(10.0f);
		fCheckbox28 = FAUSTFLOAT(0.0f);
		fCheckbox29 = FAUSTFLOAT(0.0f);
		fCheckbox30 = FAUSTFLOAT(0.0f);
		fHslider28 = FAUSTFLOAT(0.0f);
		fCheckbox31 = FAUSTFLOAT(0.0f);
		fCheckbox32 = FAUSTFLOAT(0.0f);
		fCheckbox33 = FAUSTFLOAT(0.0f);
		fHslider29 = FAUSTFLOAT(0.0f);
		fCheckbox34 = FAUSTFLOAT(0.0f);
		fHslider30 = FAUSTFLOAT(0.79000000000000004f);
		fCheckbox35 = FAUSTFLOAT(0.0f);
		fCheckbox36 = FAUSTFLOAT(0.0f);
		fCheckbox37 = FAUSTFLOAT(0.0f);
		fCheckbox38 = FAUSTFLOAT(0.0f);
		fHslider31 = FAUSTFLOAT(0.0f);
		fHslider32 = FAUSTFLOAT(0.01f);
		fHslider33 = FAUSTFLOAT(50.0f);
		fHslider34 = FAUSTFLOAT(50.0f);
		fCheckbox39 = FAUSTFLOAT(0.0f);
		fCheckbox40 = FAUSTFLOAT(0.0f);
		fCheckbox41 = FAUSTFLOAT(0.0f);
		fHslider35 = FAUSTFLOAT(0.0f);
		fCheckbox42 = FAUSTFLOAT(0.0f);
		fCheckbox43 = FAUSTFLOAT(0.0f);
		fCheckbox44 = FAUSTFLOAT(0.0f);
		fHslider36 = FAUSTFLOAT(0.0f);
		fCheckbox45 = FAUSTFLOAT(0.0f);
		fHslider37 = FAUSTFLOAT(1.0f);
		fCheckbox46 = FAUSTFLOAT(0.0f);
		fCheckbox47 = FAUSTFLOAT(0.0f);
		fCheckbox48 = FAUSTFLOAT(0.0f);
		fCheckbox49 = FAUSTFLOAT(0.0f);
		fCheckbox50 = FAUSTFLOAT(0.0f);
		fCheckbox51 = FAUSTFLOAT(0.0f);
		fCheckbox52 = FAUSTFLOAT(0.0f);
		fCheckbox53 = FAUSTFLOAT(0.0f);
		fHslider38 = FAUSTFLOAT(1.0f);
		fHslider39 = FAUSTFLOAT(1.0f);
		fHslider40 = FAUSTFLOAT(1.0f);
		fHslider41 = FAUSTFLOAT(1.0f);
		fHslider42 = FAUSTFLOAT(1.0f);
		fCheckbox54 = FAUSTFLOAT(0.0f);
		fCheckbox55 = FAUSTFLOAT(0.0f);
		fCheckbox56 = FAUSTFLOAT(0.0f);
		fCheckbox57 = FAUSTFLOAT(0.0f);
		fCheckbox58 = FAUSTFLOAT(0.0f);
		fCheckbox59 = FAUSTFLOAT(0.0f);
		fCheckbox60 = FAUSTFLOAT(0.0f);
		fCheckbox61 = FAUSTFLOAT(0.0f);
		fCheckbox62 = FAUSTFLOAT(0.0f);
		fCheckbox63 = FAUSTFLOAT(0.0f);
		fCheckbox64 = FAUSTFLOAT(0.0f);
		fCheckbox65 = FAUSTFLOAT(0.0f);
		fCheckbox66 = FAUSTFLOAT(0.0f);
		fCheckbox67 = FAUSTFLOAT(0.0f);
		fCheckbox68 = FAUSTFLOAT(0.0f);
		fCheckbox69 = FAUSTFLOAT(0.0f);
		fCheckbox70 = FAUSTFLOAT(0.0f);
		fCheckbox71 = FAUSTFLOAT(0.0f);
		fCheckbox72 = FAUSTFLOAT(0.0f);
		fCheckbox73 = FAUSTFLOAT(0.0f);
		fCheckbox74 = FAUSTFLOAT(0.0f);
		fCheckbox75 = FAUSTFLOAT(0.0f);
		fCheckbox76 = FAUSTFLOAT(0.0f);
		fCheckbox77 = FAUSTFLOAT(0.0f);
		fCheckbox78 = FAUSTFLOAT(0.0f);
		fCheckbox79 = FAUSTFLOAT(0.0f);
		fCheckbox80 = FAUSTFLOAT(0.0f);
		fCheckbox81 = FAUSTFLOAT(0.0f);
		fCheckbox82 = FAUSTFLOAT(0.0f);
		fCheckbox83 = FAUSTFLOAT(0.0f);
		fCheckbox84 = FAUSTFLOAT(0.0f);
		fCheckbox85 = FAUSTFLOAT(0.0f);
		fCheckbox86 = FAUSTFLOAT(0.0f);
		fCheckbox87 = FAUSTFLOAT(0.0f);
		fCheckbox88 = FAUSTFLOAT(0.0f);
		fCheckbox89 = FAUSTFLOAT(0.0f);
		fCheckbox90 = FAUSTFLOAT(0.0f);
		fCheckbox91 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		iTempPerm0 = 0;
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iVec1[l2] = 0;
		}
		iTempPerm1 = 0;
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iRec2[l3] = 0;
		}
		iTempPerm2 = 0;
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
		}
		iTempPerm3 = 0;
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec0[l5] = 0;
		}
		fTempPerm4 = 0.0f;
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		iTempPerm5 = 0;
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iVec3[l8] = 0;
		}
		iTempPerm6 = 0;
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			iRec7[l9] = 0;
		}
		iTempPerm7 = 0;
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		iTempPerm8 = 0;
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec5[l11] = 0;
		}
		fTempPerm9 = 0.0f;
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fVec4[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec13[l13] = 0.0f;
		}
		iTempPerm10 = 0;
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			iVec5[l14] = 0;
		}
		iTempPerm11 = 0;
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			iRec12[l15] = 0;
		}
		iTempPerm12 = 0;
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec14[l16] = 0.0f;
		}
		iTempPerm13 = 0;
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			iRec10[l17] = 0;
		}
		fTempPerm14 = 0.0f;
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fVec6[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec18[l19] = 0.0f;
		}
		iTempPerm15 = 0;
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			iVec7[l20] = 0;
		}
		iTempPerm16 = 0;
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			iRec17[l21] = 0;
		}
		iTempPerm17 = 0;
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec19[l22] = 0.0f;
		}
		iTempPerm18 = 0;
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec15[l23] = 0;
		}
		fTempPerm19 = 0.0f;
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fVec8[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec23[l25] = 0.0f;
		}
		iTempPerm20 = 0;
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			iVec9[l26] = 0;
		}
		iTempPerm21 = 0;
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			iRec22[l27] = 0;
		}
		iTempPerm22 = 0;
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec24[l28] = 0.0f;
		}
		iTempPerm23 = 0;
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			iRec20[l29] = 0;
		}
		fTempPerm24 = 0.0f;
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fVec10[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec28[l31] = 0.0f;
		}
		iTempPerm25 = 0;
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			iVec11[l32] = 0;
		}
		iTempPerm26 = 0;
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			iRec27[l33] = 0;
		}
		iTempPerm27 = 0;
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec29[l34] = 0.0f;
		}
		iTempPerm28 = 0;
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			iRec25[l35] = 0;
		}
		fTempPerm29 = 0.0f;
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fVec12[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec30[l37] = 0.0f;
		}
		fTempPerm30 = 0.0f;
		fTempPerm31 = 0.0f;
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fVec13[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec31[l39] = 0.0f;
		}
		fTempPerm32 = 0.0f;
		fTempPerm33 = 0.0f;
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fVec14[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec32[l41] = 0.0f;
		}
		fTempPerm34 = 0.0f;
		fTempPerm35 = 0.0f;
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fVec15[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec33[l43] = 0.0f;
		}
		fTempPerm36 = 0.0f;
		fTempPerm37 = 0.0f;
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fVec16[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec34[l45] = 0.0f;
		}
		fTempPerm38 = 0.0f;
		fTempPerm39 = 0.0f;
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fVec17[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec35[l47] = 0.0f;
		}
		fTempPerm40 = 0.0f;
		fTempPerm41 = 0.0f;
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fVec18[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec36[l49] = 0.0f;
		}
		fTempPerm42 = 0.0f;
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fVec19[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec37[l51] = 0.0f;
		}
		fTempPerm43 = 0.0f;
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fVec20[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec38[l53] = 0.0f;
		}
		fTempPerm44 = 0.0f;
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fVec21[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec39[l55] = 0.0f;
		}
		fTempPerm45 = 0.0f;
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fVec22[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec40[l57] = 0.0f;
		}
		fTempPerm46 = 0.0f;
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fVec23[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec41[l59] = 0.0f;
		}
		fTempPerm47 = 0.0f;
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			fVec24[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec44[l61] = 0.0f;
		}
		fTempPerm48 = 0.0f;
		fTempPerm49 = 0.0f;
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec43[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec42[l63] = 0.0f;
		}
		fTempPerm50 = 0.0f;
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fVec25[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec47[l65] = 0.0f;
		}
		fTempPerm51 = 0.0f;
		fTempPerm52 = 0.0f;
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fRec46[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec45[l67] = 0.0f;
		}
		fTempPerm53 = 0.0f;
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fVec26[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 2; l69 = l69 + 1) {
			fRec50[l69] = 0.0f;
		}
		fTempPerm54 = 0.0f;
		fTempPerm55 = 0.0f;
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec49[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fRec48[l71] = 0.0f;
		}
		fTempPerm56 = 0.0f;
		fTempPerm57 = 0.0f;
		fTempPerm58 = 0.0f;
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			fRec52[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			fRec51[l73] = 0.0f;
		}
		fTempPerm59 = 0.0f;
		fTempPerm60 = 0.0f;
		fTempPerm61 = 0.0f;
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			fRec54[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec53[l75] = 0.0f;
		}
		fTempPerm62 = 0.0f;
		fTempPerm63 = 0.0f;
		fTempPerm64 = 0.0f;
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fRec56[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			fRec55[l77] = 0.0f;
		}
		fTempPerm65 = 0.0f;
		fTempPerm66 = 0.0f;
		fTempPerm67 = 0.0f;
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec58[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec57[l79] = 0.0f;
		}
		fTempPerm68 = 0.0f;
		fTempPerm69 = 0.0f;
		fTempPerm70 = 0.0f;
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fRec60[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 2; l81 = l81 + 1) {
			fRec59[l81] = 0.0f;
		}
		fTempPerm71 = 0.0f;
		fTempPerm72 = 0.0f;
		fTempPerm73 = 0.0f;
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec62[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 2; l83 = l83 + 1) {
			fRec61[l83] = 0.0f;
		}
		fTempPerm74 = 0.0f;
		fTempPerm75 = 0.0f;
		fTempPerm76 = 0.0f;
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			fRec64[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			fRec63[l85] = 0.0f;
		}
		fTempPerm77 = 0.0f;
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec67[l86] = 0.0f;
		}
		fTempPerm78 = 0.0f;
		fTempPerm79 = 0.0f;
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec66[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec65[l88] = 0.0f;
		}
		fTempPerm80 = 0.0f;
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec70[l89] = 0.0f;
		}
		fTempPerm81 = 0.0f;
		fTempPerm82 = 0.0f;
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			fRec69[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fRec68[l91] = 0.0f;
		}
		fTempPerm83 = 0.0f;
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			fRec73[l92] = 0.0f;
		}
		fTempPerm84 = 0.0f;
		fTempPerm85 = 0.0f;
		for (int l93 = 0; l93 < 2; l93 = l93 + 1) {
			fRec72[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec71[l94] = 0.0f;
		}
		fTempPerm86 = 0.0f;
		fTempPerm87 = 0.0f;
		fTempPerm88 = 0.0f;
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec75[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec74[l96] = 0.0f;
		}
		fTempPerm89 = 0.0f;
		fTempPerm90 = 0.0f;
		fTempPerm91 = 0.0f;
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec77[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec76[l98] = 0.0f;
		}
		fTempPerm92 = 0.0f;
		fTempPerm93 = 0.0f;
		fTempPerm94 = 0.0f;
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fRec79[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2; l100 = l100 + 1) {
			fRec78[l100] = 0.0f;
		}
		fTempPerm95 = 0.0f;
		fTempPerm96 = 0.0f;
		fTempPerm97 = 0.0f;
		for (int l101 = 0; l101 < 2; l101 = l101 + 1) {
			fRec81[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec80[l102] = 0.0f;
		}
		fTempPerm98 = 0.0f;
		fTempPerm99 = 0.0f;
		fTempPerm100 = 0.0f;
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec83[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fRec82[l104] = 0.0f;
		}
		fTempPerm101 = 0.0f;
		fTempPerm102 = 0.0f;
		fTempPerm103 = 0.0f;
		for (int l105 = 0; l105 < 2; l105 = l105 + 1) {
			fRec85[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec84[l106] = 0.0f;
		}
		fTempPerm104 = 0.0f;
		fTempPerm105 = 0.0f;
		fTempPerm106 = 0.0f;
		fTempPerm107 = 0.0f;
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec87[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec86[l108] = 0.0f;
		}
		fTempPerm108 = 0.0f;
		fTempPerm109 = 0.0f;
		fTempPerm110 = 0.0f;
		fTempPerm111 = 0.0f;
		fTempPerm112 = 0.0f;
		fTempPerm113 = 0.0f;
		for (int l109 = 0; l109 < 2; l109 = l109 + 1) {
			fRec88[l109] = 0.0f;
		}
		fTempPerm114 = 0.0f;
		fTempPerm115 = 0.0f;
		fTempPerm116 = 0.0f;
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec89[l110] = 0.0f;
		}
		fTempPerm117 = 0.0f;
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fRec90[l111] = 0.0f;
		}
		fTempPerm118 = 0.0f;
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fRec91[l112] = 0.0f;
		}
		fTempPerm119 = 0.0f;
		fTempPerm120 = 0.0f;
		for (int l113 = 0; l113 < 2; l113 = l113 + 1) {
			fRec92[l113] = 0.0f;
		}
		fTempPerm121 = 0.0f;
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fRec93[l114] = 0.0f;
		}
		fTempPerm122 = 0.0f;
		fTempPerm123 = 0.0f;
		fTempPerm124 = 0.0f;
		fTempPerm125 = 0.0f;
		fTempPerm126 = 0.0f;
		fTempPerm127 = 0.0f;
		for (int l115 = 0; l115 < 2; l115 = l115 + 1) {
			fRec94[l115] = 0.0f;
		}
		fTempPerm128 = 0.0f;
		fTempPerm129 = 0.0f;
		fTempPerm130 = 0.0f;
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fRec95[l116] = 0.0f;
		}
		fTempPerm131 = 0.0f;
		for (int l117 = 0; l117 < 2; l117 = l117 + 1) {
			fRec96[l117] = 0.0f;
		}
		fTempPerm132 = 0.0f;
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec97[l118] = 0.0f;
		}
		fTempPerm133 = 0.0f;
		fTempPerm134 = 0.0f;
		for (int l119 = 0; l119 < 2; l119 = l119 + 1) {
			fRec98[l119] = 0.0f;
		}
		fTempPerm135 = 0.0f;
		for (int l120 = 0; l120 < 2; l120 = l120 + 1) {
			fRec99[l120] = 0.0f;
		}
		fTempPerm136 = 0.0f;
		fTempPerm137 = 0.0f;
		fTempPerm138 = 0.0f;
		fTempPerm139 = 0.0f;
		fTempPerm140 = 0.0f;
		fTempPerm141 = 0.0f;
		for (int l121 = 0; l121 < 2; l121 = l121 + 1) {
			fRec100[l121] = 0.0f;
		}
		fTempPerm142 = 0.0f;
		fTempPerm143 = 0.0f;
		fTempPerm144 = 0.0f;
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec101[l122] = 0.0f;
		}
		fTempPerm145 = 0.0f;
		for (int l123 = 0; l123 < 2; l123 = l123 + 1) {
			fRec102[l123] = 0.0f;
		}
		fTempPerm146 = 0.0f;
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fRec103[l124] = 0.0f;
		}
		fTempPerm147 = 0.0f;
		fTempPerm148 = 0.0f;
		for (int l125 = 0; l125 < 2; l125 = l125 + 1) {
			fRec104[l125] = 0.0f;
		}
		fTempPerm149 = 0.0f;
		for (int l126 = 0; l126 < 2; l126 = l126 + 1) {
			fRec105[l126] = 0.0f;
		}
		fTempPerm150 = 0.0f;
		fTempPerm151 = 0.0f;
		fTempPerm152 = 0.0f;
		fTempPerm153 = 0.0f;
		fTempPerm154 = 0.0f;
		fTempPerm155 = 0.0f;
		for (int l127 = 0; l127 < 2; l127 = l127 + 1) {
			fRec106[l127] = 0.0f;
		}
		fTempPerm156 = 0.0f;
		fTempPerm157 = 0.0f;
		fTempPerm158 = 0.0f;
		for (int l128 = 0; l128 < 2; l128 = l128 + 1) {
			fRec107[l128] = 0.0f;
		}
		fTempPerm159 = 0.0f;
		for (int l129 = 0; l129 < 2; l129 = l129 + 1) {
			fRec108[l129] = 0.0f;
		}
		fTempPerm160 = 0.0f;
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fRec109[l130] = 0.0f;
		}
		fTempPerm161 = 0.0f;
		fTempPerm162 = 0.0f;
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fRec110[l131] = 0.0f;
		}
		fTempPerm163 = 0.0f;
		for (int l132 = 0; l132 < 2; l132 = l132 + 1) {
			fRec111[l132] = 0.0f;
		}
		fTempPerm164 = 0.0f;
		fTempPerm165 = 0.0f;
		fTempPerm166 = 0.0f;
		fTempPerm167 = 0.0f;
		fTempPerm168 = 0.0f;
		fTempPerm169 = 0.0f;
		for (int l133 = 0; l133 < 2; l133 = l133 + 1) {
			fRec112[l133] = 0.0f;
		}
		fTempPerm170 = 0.0f;
		fTempPerm171 = 0.0f;
		fTempPerm172 = 0.0f;
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fRec113[l134] = 0.0f;
		}
		fTempPerm173 = 0.0f;
		for (int l135 = 0; l135 < 2; l135 = l135 + 1) {
			fRec114[l135] = 0.0f;
		}
		fTempPerm174 = 0.0f;
		for (int l136 = 0; l136 < 2; l136 = l136 + 1) {
			fRec115[l136] = 0.0f;
		}
		fTempPerm175 = 0.0f;
		fTempPerm176 = 0.0f;
		for (int l137 = 0; l137 < 2; l137 = l137 + 1) {
			fRec116[l137] = 0.0f;
		}
		fTempPerm177 = 0.0f;
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec117[l138] = 0.0f;
		}
		fTempPerm178 = 0.0f;
		fTempPerm179 = 0.0f;
		fTempPerm180 = 0.0f;
		fTempPerm181 = 0.0f;
		fTempPerm182 = 0.0f;
		fTempPerm183 = 0.0f;
		for (int l139 = 0; l139 < 2; l139 = l139 + 1) {
			fRec118[l139] = 0.0f;
		}
		fTempPerm184 = 0.0f;
		fTempPerm185 = 0.0f;
		fTempPerm186 = 0.0f;
		for (int l140 = 0; l140 < 2; l140 = l140 + 1) {
			fRec119[l140] = 0.0f;
		}
		fTempPerm187 = 0.0f;
		for (int l141 = 0; l141 < 2; l141 = l141 + 1) {
			fRec120[l141] = 0.0f;
		}
		fTempPerm188 = 0.0f;
		for (int l142 = 0; l142 < 2; l142 = l142 + 1) {
			fRec121[l142] = 0.0f;
		}
		fTempPerm189 = 0.0f;
		fTempPerm190 = 0.0f;
		for (int l143 = 0; l143 < 2; l143 = l143 + 1) {
			fRec122[l143] = 0.0f;
		}
		fTempPerm191 = 0.0f;
		for (int l144 = 0; l144 < 2; l144 = l144 + 1) {
			fRec123[l144] = 0.0f;
		}
		fTempPerm192 = 0.0f;
		fTempPerm193 = 0.0f;
		fTempPerm194 = 0.0f;
		fTempPerm195 = 0.0f;
		fTempPerm196 = 0.0f;
		fTempPerm197 = 0.0f;
		fTempPerm198 = 0.0f;
		fTempPerm199 = 0.0f;
		fTempPerm200 = 0.0f;
		fTempPerm201 = 0.0f;
		fTempPerm202 = 0.0f;
		fTempPerm203 = 0.0f;
		fTempPerm204 = 0.0f;
		fTempPerm205 = 0.0f;
		fTempPerm206 = 0.0f;
		fTempPerm207 = 0.0f;
		fTempPerm208 = 0.0f;
		fTempPerm209 = 0.0f;
		fTempPerm210 = 0.0f;
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp2* clone() {
		return new mydsp2();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Motion");
		ui_interface->declare(&fCheckbox0, "00", "");
		ui_interface->declare(&fCheckbox0, "motionName", "sxp");
		ui_interface->addCheckButton("sxpOn", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "01", "");
		ui_interface->declare(&fCheckbox1, "motionName", "syp");
		ui_interface->addCheckButton("sypOn", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "02", "");
		ui_interface->declare(&fCheckbox2, "motionName", "szp");
		ui_interface->addCheckButton("szpOn", &fCheckbox2);
		ui_interface->declare(&fCheckbox3, "03", "");
		ui_interface->declare(&fCheckbox3, "motionName", "sxn");
		ui_interface->addCheckButton("sxnOn", &fCheckbox3);
		ui_interface->declare(&fCheckbox4, "04", "");
		ui_interface->declare(&fCheckbox4, "motionName", "syn");
		ui_interface->addCheckButton("synOn", &fCheckbox4);
		ui_interface->declare(&fCheckbox5, "05", "");
		ui_interface->declare(&fCheckbox5, "motionName", "szn");
		ui_interface->addCheckButton("sznOn", &fCheckbox5);
		ui_interface->declare(&fCheckbox6, "06", "");
		ui_interface->declare(&fCheckbox6, "motionName", "ixp");
		ui_interface->addCheckButton("ixpOn", &fCheckbox6);
		ui_interface->declare(&fCheckbox9, "07", "");
		ui_interface->declare(&fCheckbox9, "motionName", "iyp");
		ui_interface->addCheckButton("iypOn", &fCheckbox9);
		ui_interface->declare(&fCheckbox12, "08", "");
		ui_interface->declare(&fCheckbox12, "motionName", "izp");
		ui_interface->addCheckButton("izpOn", &fCheckbox12);
		ui_interface->declare(&fCheckbox15, "09", "");
		ui_interface->declare(&fCheckbox15, "motionName", "ixn");
		ui_interface->addCheckButton("ixnOn", &fCheckbox15);
		ui_interface->declare(&fHslider0, "101", "");
		ui_interface->declare(&fHslider0, "showName", "highPass");
		ui_interface->addHorizontalSlider("hp_Param", &fHslider0, FAUSTFLOAT(50.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(50.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider2, "102", "");
		ui_interface->declare(&fHslider2, "showName", "shockThred");
		ui_interface->addHorizontalSlider("shock_thr_Param", &fHslider2, FAUSTFLOAT(0.75f), FAUSTFLOAT(0.100000001f), FAUSTFLOAT(3.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider3, "103", "");
		ui_interface->declare(&fHslider3, "showName", "antirebond");
		ui_interface->declare(&fHslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("antirebon_Param", &fHslider3, FAUSTFLOAT(75.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider9, "104", "");
		ui_interface->declare(&fHslider9, "showName", "lowPass");
		ui_interface->addHorizontalSlider("lp_Param", &fHslider9, FAUSTFLOAT(1.5f), FAUSTFLOAT(0.100000001f), FAUSTFLOAT(20.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider16, "105", "");
		ui_interface->declare(&fHslider16, "showName", "osfproj");
		ui_interface->addHorizontalSlider("osfproj_Param", &fHslider16, FAUSTFLOAT(0.0799999982f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.330000013f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider25, "106", "");
		ui_interface->declare(&fHslider25, "showName", "accThred");
		ui_interface->addHorizontalSlider("tacc_thr_Param", &fHslider25, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider23, "107", "");
		ui_interface->declare(&fHslider23, "showName", "accGain");
		ui_interface->addHorizontalSlider("tacc_gain_Param", &fHslider23, FAUSTFLOAT(1.35000002f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider26, "108", "");
		ui_interface->declare(&fHslider26, "showName", "accEvUp");
		ui_interface->addHorizontalSlider("tacc_up_Param", &fHslider26, FAUSTFLOAT(10.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider27, "109", "");
		ui_interface->declare(&fHslider27, "showName", "accEvDown");
		ui_interface->addHorizontalSlider("tacc_down_Param", &fHslider27, FAUSTFLOAT(10.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fCheckbox16, "10", "");
		ui_interface->declare(&fCheckbox16, "motionName", "iyn");
		ui_interface->addCheckButton("iynOn", &fCheckbox16);
		ui_interface->declare(&fHslider32, "110", "");
		ui_interface->declare(&fHslider32, "showName", "gyoThred");
		ui_interface->addHorizontalSlider("tgyr_thr_Param", &fHslider32, FAUSTFLOAT(0.00999999978f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider30, "111", "");
		ui_interface->declare(&fHslider30, "showName", "gyoGain");
		ui_interface->addHorizontalSlider("tgyr_gain_Param", &fHslider30, FAUSTFLOAT(0.790000021f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider33, "112", "");
		ui_interface->declare(&fHslider33, "showName", "gyoEvUp");
		ui_interface->addHorizontalSlider("tgyr_up_Param", &fHslider33, FAUSTFLOAT(50.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider34, "113", "");
		ui_interface->declare(&fHslider34, "showName", "gyoEvDown");
		ui_interface->addHorizontalSlider("tgyr_down_Param", &fHslider34, FAUSTFLOAT(50.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider37, "114", "");
		ui_interface->declare(&fHslider37, "showName", "shapeCour");
		ui_interface->addHorizontalSlider("shapeCour_Param", &fHslider37, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider38, "115", "");
		ui_interface->declare(&fHslider38, "showName", "shapeRear");
		ui_interface->addHorizontalSlider("shapeRear_Param", &fHslider38, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider39, "116", "");
		ui_interface->declare(&fHslider39, "showName", "shapeJardin");
		ui_interface->addHorizontalSlider("shapeJardin_Param", &fHslider39, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider40, "117", "");
		ui_interface->declare(&fHslider40, "showName", "shapeFront");
		ui_interface->addHorizontalSlider("shapeFront_Param", &fHslider40, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider41, "118", "");
		ui_interface->declare(&fHslider41, "showName", "shapeDown");
		ui_interface->addHorizontalSlider("shapeDown_Param", &fHslider41, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider42, "119", "");
		ui_interface->declare(&fHslider42, "showName", "shapeUp");
		ui_interface->addHorizontalSlider("shapeUp_Param", &fHslider42, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fCheckbox17, "11", "");
		ui_interface->declare(&fCheckbox17, "motionName", "izn");
		ui_interface->addCheckButton("iznOn", &fCheckbox17);
		ui_interface->declare(&fCheckbox18, "12", "");
		ui_interface->declare(&fCheckbox18, "motionName", "pixp");
		ui_interface->addCheckButton("pixpOn", &fCheckbox18);
		ui_interface->declare(&fCheckbox19, "13", "");
		ui_interface->declare(&fCheckbox19, "motionName", "piyp");
		ui_interface->addCheckButton("piypOn", &fCheckbox19);
		ui_interface->declare(&fCheckbox20, "14", "");
		ui_interface->declare(&fCheckbox20, "motionName", "pizp");
		ui_interface->addCheckButton("pizpOn", &fCheckbox20);
		ui_interface->declare(&fCheckbox21, "15", "");
		ui_interface->declare(&fCheckbox21, "motionName", "pixn");
		ui_interface->addCheckButton("pixnOn", &fCheckbox21);
		ui_interface->declare(&fCheckbox22, "16", "");
		ui_interface->declare(&fCheckbox22, "motionName", "piyn");
		ui_interface->addCheckButton("piynOn", &fCheckbox22);
		ui_interface->declare(&fCheckbox23, "17", "");
		ui_interface->declare(&fCheckbox23, "motionName", "pizn");
		ui_interface->addCheckButton("piznOn", &fCheckbox23);
		ui_interface->declare(&fCheckbox24, "18", "");
		ui_interface->declare(&fCheckbox24, "motionName", "axpn");
		ui_interface->addCheckButton("axpnOn", &fCheckbox24);
		ui_interface->declare(&fCheckbox28, "19", "");
		ui_interface->declare(&fCheckbox28, "motionName", "aypn");
		ui_interface->addCheckButton("aypnOn", &fCheckbox28);
		ui_interface->declare(&fCheckbox31, "20", "");
		ui_interface->declare(&fCheckbox31, "motionName", "azpn");
		ui_interface->addCheckButton("azpnOn", &fCheckbox31);
		ui_interface->declare(&fCheckbox25, "21", "");
		ui_interface->declare(&fCheckbox25, "motionName", "axp");
		ui_interface->addCheckButton("axpOn", &fCheckbox25);
		ui_interface->declare(&fCheckbox29, "22", "");
		ui_interface->declare(&fCheckbox29, "motionName", "ayp");
		ui_interface->addCheckButton("aypOn", &fCheckbox29);
		ui_interface->declare(&fCheckbox32, "23", "");
		ui_interface->declare(&fCheckbox32, "motionName", "azp");
		ui_interface->addCheckButton("azpOn", &fCheckbox32);
		ui_interface->declare(&fCheckbox26, "24", "");
		ui_interface->declare(&fCheckbox26, "motionName", "axn");
		ui_interface->addCheckButton("axnOn", &fCheckbox26);
		ui_interface->declare(&fCheckbox30, "25", "");
		ui_interface->declare(&fCheckbox30, "motionName", "ayn");
		ui_interface->addCheckButton("aynOn", &fCheckbox30);
		ui_interface->declare(&fCheckbox33, "26", "");
		ui_interface->declare(&fCheckbox33, "motionName", "azn");
		ui_interface->addCheckButton("aznOn", &fCheckbox33);
		ui_interface->declare(&fCheckbox27, "27", "");
		ui_interface->declare(&fCheckbox27, "motionName", "totalaccel");
		ui_interface->addCheckButton("totalaccelOn", &fCheckbox27);
		ui_interface->declare(&fCheckbox34, "28", "");
		ui_interface->declare(&fCheckbox34, "motionName", "gxpn");
		ui_interface->addCheckButton("gxpnOn", &fCheckbox34);
		ui_interface->declare(&fCheckbox39, "29", "");
		ui_interface->declare(&fCheckbox39, "motionName", "gypn");
		ui_interface->addCheckButton("gypnOn", &fCheckbox39);
		ui_interface->declare(&fCheckbox42, "30", "");
		ui_interface->declare(&fCheckbox42, "motionName", "gzpn");
		ui_interface->addCheckButton("gzpnOn", &fCheckbox42);
		ui_interface->declare(&fCheckbox35, "31", "");
		ui_interface->declare(&fCheckbox35, "motionName", "gxp");
		ui_interface->addCheckButton("gxpOn", &fCheckbox35);
		ui_interface->declare(&fCheckbox40, "32", "");
		ui_interface->declare(&fCheckbox40, "motionName", "gyp");
		ui_interface->addCheckButton("gypOn", &fCheckbox40);
		ui_interface->declare(&fCheckbox43, "33", "");
		ui_interface->declare(&fCheckbox43, "motionName", "gzp");
		ui_interface->addCheckButton("gzpOn", &fCheckbox43);
		ui_interface->declare(&fCheckbox36, "34", "");
		ui_interface->declare(&fCheckbox36, "motionName", "gxn");
		ui_interface->addCheckButton("gxnOn", &fCheckbox36);
		ui_interface->declare(&fCheckbox41, "35", "");
		ui_interface->declare(&fCheckbox41, "motionName", "gyn");
		ui_interface->addCheckButton("gynOn", &fCheckbox41);
		ui_interface->declare(&fCheckbox44, "36", "");
		ui_interface->declare(&fCheckbox44, "motionName", "gzn");
		ui_interface->addCheckButton("gznOn", &fCheckbox44);
		ui_interface->declare(&fCheckbox37, "37", "");
		ui_interface->declare(&fCheckbox37, "motionName", "totalgyro");
		ui_interface->addCheckButton("totalgyroOn", &fCheckbox37);
		ui_interface->declare(&fCheckbox45, "38", "");
		ui_interface->declare(&fCheckbox45, "motionName", "brasG_cour");
		ui_interface->addCheckButton("brasG_courOn", &fCheckbox45);
		ui_interface->declare(&fCheckbox46, "39", "");
		ui_interface->declare(&fCheckbox46, "motionName", "brasG_rear");
		ui_interface->addCheckButton("brasG_rearOn", &fCheckbox46);
		ui_interface->declare(&fCheckbox47, "40", "");
		ui_interface->declare(&fCheckbox47, "motionName", "brasG_jardin");
		ui_interface->addCheckButton("brasG_jardinOn", &fCheckbox47);
		ui_interface->declare(&fCheckbox48, "41", "");
		ui_interface->declare(&fCheckbox48, "motionName", "brasG_front");
		ui_interface->addCheckButton("brasG_frontOn", &fCheckbox48);
		ui_interface->declare(&fCheckbox49, "42", "");
		ui_interface->declare(&fCheckbox49, "motionName", "brasG_down");
		ui_interface->addCheckButton("brasG_downOn", &fCheckbox49);
		ui_interface->declare(&fCheckbox50, "43", "");
		ui_interface->declare(&fCheckbox50, "motionName", "brasG_up");
		ui_interface->addCheckButton("brasG_upOn", &fCheckbox50);
		ui_interface->declare(&fCheckbox54, "44", "");
		ui_interface->declare(&fCheckbox54, "motionName", "pieds_cour");
		ui_interface->addCheckButton("pieds_courOn", &fCheckbox54);
		ui_interface->declare(&fCheckbox55, "45", "");
		ui_interface->declare(&fCheckbox55, "motionName", "pieds_rear");
		ui_interface->addCheckButton("pieds_rearOn", &fCheckbox55);
		ui_interface->declare(&fCheckbox56, "46", "");
		ui_interface->declare(&fCheckbox56, "motionName", "pieds_jardin");
		ui_interface->addCheckButton("pieds_jardinOn", &fCheckbox56);
		ui_interface->declare(&fCheckbox57, "47", "");
		ui_interface->declare(&fCheckbox57, "motionName", "pieds_front");
		ui_interface->addCheckButton("pieds_frontOn", &fCheckbox57);
		ui_interface->declare(&fCheckbox58, "48", "");
		ui_interface->declare(&fCheckbox58, "motionName", "pieds_down");
		ui_interface->addCheckButton("pieds_downOn", &fCheckbox58);
		ui_interface->declare(&fCheckbox59, "49", "");
		ui_interface->declare(&fCheckbox59, "motionName", "pieds_up");
		ui_interface->addCheckButton("pieds_upOn", &fCheckbox59);
		ui_interface->declare(&fCheckbox60, "50", "");
		ui_interface->declare(&fCheckbox60, "motionName", "dos_cour");
		ui_interface->addCheckButton("dos_courOn", &fCheckbox60);
		ui_interface->declare(&fCheckbox61, "51", "");
		ui_interface->declare(&fCheckbox61, "motionName", "dos_rear");
		ui_interface->addCheckButton("dos_rearOn", &fCheckbox61);
		ui_interface->declare(&fCheckbox62, "52", "");
		ui_interface->declare(&fCheckbox62, "motionName", "dos_jardin");
		ui_interface->addCheckButton("dos_jardinOn", &fCheckbox62);
		ui_interface->declare(&fCheckbox63, "53", "");
		ui_interface->declare(&fCheckbox63, "motionName", "dos_front");
		ui_interface->addCheckButton("dos_frontOn", &fCheckbox63);
		ui_interface->declare(&fCheckbox64, "54", "");
		ui_interface->declare(&fCheckbox64, "motionName", "dos_down");
		ui_interface->addCheckButton("dos_downOn", &fCheckbox64);
		ui_interface->declare(&fCheckbox65, "55", "");
		ui_interface->declare(&fCheckbox65, "motionName", "dos_up");
		ui_interface->addCheckButton("dos_upOn", &fCheckbox65);
		ui_interface->declare(&fCheckbox71, "56", "");
		ui_interface->declare(&fCheckbox71, "motionName", "brasD_cour");
		ui_interface->addCheckButton("brasD_courOn", &fCheckbox71);
		ui_interface->declare(&fCheckbox72, "57", "");
		ui_interface->declare(&fCheckbox72, "motionName", "brasD_rear");
		ui_interface->addCheckButton("brasD_rearOn", &fCheckbox72);
		ui_interface->declare(&fCheckbox73, "58", "");
		ui_interface->declare(&fCheckbox73, "motionName", "brasD_jardin");
		ui_interface->addCheckButton("brasD_jardinOn", &fCheckbox73);
		ui_interface->declare(&fCheckbox74, "59", "");
		ui_interface->declare(&fCheckbox74, "motionName", "brasD_front");
		ui_interface->addCheckButton("brasD_frontOn", &fCheckbox74);
		ui_interface->declare(&fCheckbox75, "60", "");
		ui_interface->declare(&fCheckbox75, "motionName", "brasD_down");
		ui_interface->addCheckButton("brasD_downOn", &fCheckbox75);
		ui_interface->declare(&fCheckbox76, "61", "");
		ui_interface->declare(&fCheckbox76, "motionName", "brasD_up");
		ui_interface->addCheckButton("brasD_upOn", &fCheckbox76);
		ui_interface->declare(&fCheckbox77, "62", "");
		ui_interface->declare(&fCheckbox77, "motionName", "tete_cour");
		ui_interface->addCheckButton("tete_courOn", &fCheckbox77);
		ui_interface->declare(&fCheckbox78, "63", "");
		ui_interface->declare(&fCheckbox78, "motionName", "tete_rear");
		ui_interface->addCheckButton("tete_rearOn", &fCheckbox78);
		ui_interface->declare(&fCheckbox79, "64", "");
		ui_interface->declare(&fCheckbox79, "motionName", "tete_jardin");
		ui_interface->addCheckButton("tete_jardinOn", &fCheckbox79);
		ui_interface->declare(&fCheckbox80, "65", "");
		ui_interface->declare(&fCheckbox80, "motionName", "tete_front");
		ui_interface->addCheckButton("tete_frontOn", &fCheckbox80);
		ui_interface->declare(&fCheckbox81, "66", "");
		ui_interface->declare(&fCheckbox81, "motionName", "tete_down");
		ui_interface->addCheckButton("tete_downOn", &fCheckbox81);
		ui_interface->declare(&fCheckbox82, "67", "");
		ui_interface->declare(&fCheckbox82, "motionName", "tete_up");
		ui_interface->addCheckButton("tete_upOn", &fCheckbox82);
		ui_interface->declare(&fCheckbox86, "68", "");
		ui_interface->declare(&fCheckbox86, "motionName", "ventre_cour");
		ui_interface->addCheckButton("ventre_courOn", &fCheckbox86);
		ui_interface->declare(&fCheckbox91, "69", "");
		ui_interface->declare(&fCheckbox91, "motionName", "ventre_rear");
		ui_interface->addCheckButton("ventre_rearOn", &fCheckbox91);
		ui_interface->declare(&fCheckbox87, "70", "");
		ui_interface->declare(&fCheckbox87, "motionName", "ventre_jardin");
		ui_interface->addCheckButton("ventre_jardinOn", &fCheckbox87);
		ui_interface->declare(&fCheckbox88, "71", "");
		ui_interface->declare(&fCheckbox88, "motionName", "ventre_front");
		ui_interface->addCheckButton("ventre_frontOn", &fCheckbox88);
		ui_interface->declare(&fCheckbox89, "72", "");
		ui_interface->declare(&fCheckbox89, "motionName", "ventre_down");
		ui_interface->addCheckButton("ventre_downOn", &fCheckbox89);
		ui_interface->declare(&fCheckbox90, "73", "");
		ui_interface->declare(&fCheckbox90, "motionName", "ventre_up");
		ui_interface->addCheckButton("ventre_upOn", &fCheckbox90);
		ui_interface->declare(&fCheckbox8, "74", "");
		ui_interface->declare(&fCheckbox8, "motionName", "ixpn");
		ui_interface->addCheckButton("ixpnOn", &fCheckbox8);
		ui_interface->declare(&fCheckbox10, "75", "");
		ui_interface->declare(&fCheckbox10, "motionName", "iypn");
		ui_interface->addCheckButton("iypnOn", &fCheckbox10);
		ui_interface->declare(&fCheckbox13, "76", "");
		ui_interface->declare(&fCheckbox13, "motionName", "izpn");
		ui_interface->addCheckButton("izpnOn", &fCheckbox13);
		ui_interface->declare(&fCheckbox7, "77", "");
		ui_interface->declare(&fCheckbox7, "motionName", "ixpn_sym");
		ui_interface->addCheckButton("ixpn_symOn", &fCheckbox7);
		ui_interface->declare(&fCheckbox11, "78", "");
		ui_interface->declare(&fCheckbox11, "motionName", "iypn_sym");
		ui_interface->addCheckButton("iypn_symOn", &fCheckbox11);
		ui_interface->declare(&fCheckbox14, "79", "");
		ui_interface->declare(&fCheckbox14, "motionName", "izpn_sym");
		ui_interface->addCheckButton("izpn_symOn", &fCheckbox14);
		ui_interface->declare(&fCheckbox66, "80", "");
		ui_interface->declare(&fCheckbox66, "motionName", "dosx");
		ui_interface->addCheckButton("dosxOn", &fCheckbox66);
		ui_interface->declare(&fCheckbox68, "81", "");
		ui_interface->declare(&fCheckbox68, "motionName", "dosy");
		ui_interface->addCheckButton("dosyOn", &fCheckbox68);
		ui_interface->declare(&fCheckbox67, "82", "");
		ui_interface->declare(&fCheckbox67, "motionName", "coox");
		ui_interface->addCheckButton("cooxOn", &fCheckbox67);
		ui_interface->declare(&fCheckbox69, "83", "");
		ui_interface->declare(&fCheckbox69, "motionName", "cooy");
		ui_interface->addCheckButton("cooyOn", &fCheckbox69);
		ui_interface->declare(&fCheckbox70, "84", "");
		ui_interface->declare(&fCheckbox70, "motionName", "cooz");
		ui_interface->addCheckButton("coozOn", &fCheckbox70);
		ui_interface->declare(&fCheckbox83, "85", "");
		ui_interface->declare(&fCheckbox83, "motionName", "cooxT");
		ui_interface->addCheckButton("cooxTOn", &fCheckbox83);
		ui_interface->declare(&fCheckbox84, "86", "");
		ui_interface->declare(&fCheckbox84, "motionName", "cooyT");
		ui_interface->addCheckButton("cooyTOn", &fCheckbox84);
		ui_interface->declare(&fCheckbox85, "87", "");
		ui_interface->declare(&fCheckbox85, "motionName", "coozT");
		ui_interface->addCheckButton("coozTOn", &fCheckbox85);
		ui_interface->declare(&fCheckbox51, "88", "");
		ui_interface->declare(&fCheckbox51, "motionName", "cooxBG");
		ui_interface->addCheckButton("cooxBGOn", &fCheckbox51);
		ui_interface->declare(&fCheckbox52, "89", "");
		ui_interface->declare(&fCheckbox52, "motionName", "cooyBG");
		ui_interface->addCheckButton("cooyBGOn", &fCheckbox52);
		ui_interface->declare(&fCheckbox53, "90", "");
		ui_interface->declare(&fCheckbox53, "motionName", "coozBG");
		ui_interface->addCheckButton("coozBGOn", &fCheckbox53);
		ui_interface->declare(&fCheckbox38, "91", "");
		ui_interface->declare(&fCheckbox38, "motionName", "gyro_xy");
		ui_interface->addCheckButton("gyro_xyOn", &fCheckbox38);
		ui_interface->declare(&fHslider24, "acc", "0 0 -30 0 30");
		ui_interface->declare(&fHslider24, "hidden", "1");
		ui_interface->addHorizontalSlider("acc_x", &fHslider24, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider28, "acc", "1 0 -30 0 30");
		ui_interface->declare(&fHslider28, "hidden", "1");
		ui_interface->addHorizontalSlider("acc_y", &fHslider28, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider29, "acc", "2 0 -30 0 30");
		ui_interface->declare(&fHslider29, "hidden", "1");
		ui_interface->addHorizontalSlider("acc_z", &fHslider29, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider31, "gyr", "0 0 -35 0 35");
		ui_interface->declare(&fHslider31, "hidden", "1");
		ui_interface->addHorizontalSlider("gx", &fHslider31, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider35, "gyr", "1 0 -35 0 35");
		ui_interface->declare(&fHslider35, "hidden", "1");
		ui_interface->addHorizontalSlider("gy", &fHslider35, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider36, "gyr", "2 0 -35 0 35");
		ui_interface->declare(&fHslider36, "hidden", "1");
		ui_interface->addHorizontalSlider("gz", &fHslider36, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider13, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fHslider13, "hidden", "1");
		ui_interface->addHorizontalSlider("ixn", &fHslider13, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider10, "acc", "0 0 -10 0 10");
		ui_interface->declare(&fHslider10, "hidden", "1");
		ui_interface->addHorizontalSlider("ixp", &fHslider10, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider14, "acc", "1 1 -10 0 10");
		ui_interface->declare(&fHslider14, "hidden", "1");
		ui_interface->addHorizontalSlider("iyn", &fHslider14, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider11, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider11, "hidden", "1");
		ui_interface->addHorizontalSlider("iyp", &fHslider11, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider15, "acc", "2 1 -10 0 10");
		ui_interface->declare(&fHslider15, "hidden", "1");
		ui_interface->addHorizontalSlider("izn", &fHslider15, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider12, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fHslider12, "hidden", "1");
		ui_interface->addHorizontalSlider("izp", &fHslider12, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider20, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fHslider20, "hidden", "1");
		ui_interface->addHorizontalSlider("pixn", &fHslider20, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider17, "acc", "0 0 -10 0 10");
		ui_interface->declare(&fHslider17, "hidden", "1");
		ui_interface->addHorizontalSlider("pixp", &fHslider17, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider21, "acc", "1 1 -10 0 10");
		ui_interface->declare(&fHslider21, "hidden", "1");
		ui_interface->addHorizontalSlider("piyn", &fHslider21, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider18, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider18, "hidden", "1");
		ui_interface->addHorizontalSlider("piyp", &fHslider18, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider22, "acc", "2 1 -10 0 10");
		ui_interface->declare(&fHslider22, "hidden", "1");
		ui_interface->addHorizontalSlider("pizn", &fHslider22, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider19, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fHslider19, "hidden", "1");
		ui_interface->addHorizontalSlider("pizp", &fHslider19, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fHslider6, "acc", "0 1 -30 0 30");
		ui_interface->declare(&fHslider6, "hidden", "1");
		ui_interface->addHorizontalSlider("sxn", &fHslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(-3.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->declare(&fHslider1, "acc", "0 0 -30 0 30");
		ui_interface->declare(&fHslider1, "hidden", "1");
		ui_interface->addHorizontalSlider("sxp", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-3.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->declare(&fHslider7, "acc", "1 1 -30 0 30");
		ui_interface->declare(&fHslider7, "hidden", "1");
		ui_interface->addHorizontalSlider("syn", &fHslider7, FAUSTFLOAT(0.0f), FAUSTFLOAT(-3.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->declare(&fHslider4, "acc", "1 0 -30 0 30");
		ui_interface->declare(&fHslider4, "hidden", "1");
		ui_interface->addHorizontalSlider("syp", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(-3.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->declare(&fHslider8, "acc", "2 1 -30 0 30");
		ui_interface->declare(&fHslider8, "hidden", "1");
		ui_interface->addHorizontalSlider("szn", &fHslider8, FAUSTFLOAT(0.0f), FAUSTFLOAT(-3.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->declare(&fHslider5, "acc", "2 0 -30 0 30");
		ui_interface->declare(&fHslider5, "hidden", "1");
		ui_interface->addHorizontalSlider("szp", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(-3.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* input6 = inputs[6];
		FAUSTFLOAT* input7 = inputs[7];
		FAUSTFLOAT* input8 = inputs[8];
		FAUSTFLOAT* input9 = inputs[9];
		FAUSTFLOAT* input10 = inputs[10];
		FAUSTFLOAT* input11 = inputs[11];
		FAUSTFLOAT* input12 = inputs[12];
		FAUSTFLOAT* input13 = inputs[13];
		FAUSTFLOAT* input14 = inputs[14];
		FAUSTFLOAT* input15 = inputs[15];
		FAUSTFLOAT* input16 = inputs[16];
		FAUSTFLOAT* input17 = inputs[17];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		FAUSTFLOAT* output8 = outputs[8];
		FAUSTFLOAT* output9 = outputs[9];
		FAUSTFLOAT* output10 = outputs[10];
		FAUSTFLOAT* output11 = outputs[11];
		FAUSTFLOAT* output12 = outputs[12];
		FAUSTFLOAT* output13 = outputs[13];
		FAUSTFLOAT* output14 = outputs[14];
		FAUSTFLOAT* output15 = outputs[15];
		FAUSTFLOAT* output16 = outputs[16];
		FAUSTFLOAT* output17 = outputs[17];
		FAUSTFLOAT* output18 = outputs[18];
		FAUSTFLOAT* output19 = outputs[19];
		FAUSTFLOAT* output20 = outputs[20];
		FAUSTFLOAT* output21 = outputs[21];
		FAUSTFLOAT* output22 = outputs[22];
		FAUSTFLOAT* output23 = outputs[23];
		FAUSTFLOAT* output24 = outputs[24];
		FAUSTFLOAT* output25 = outputs[25];
		FAUSTFLOAT* output26 = outputs[26];
		FAUSTFLOAT* output27 = outputs[27];
		FAUSTFLOAT* output28 = outputs[28];
		FAUSTFLOAT* output29 = outputs[29];
		FAUSTFLOAT* output30 = outputs[30];
		FAUSTFLOAT* output31 = outputs[31];
		FAUSTFLOAT* output32 = outputs[32];
		FAUSTFLOAT* output33 = outputs[33];
		FAUSTFLOAT* output34 = outputs[34];
		FAUSTFLOAT* output35 = outputs[35];
		FAUSTFLOAT* output36 = outputs[36];
		FAUSTFLOAT* output37 = outputs[37];
		FAUSTFLOAT* output38 = outputs[38];
		FAUSTFLOAT* output39 = outputs[39];
		FAUSTFLOAT* output40 = outputs[40];
		FAUSTFLOAT* output41 = outputs[41];
		FAUSTFLOAT* output42 = outputs[42];
		FAUSTFLOAT* output43 = outputs[43];
		FAUSTFLOAT* output44 = outputs[44];
		FAUSTFLOAT* output45 = outputs[45];
		FAUSTFLOAT* output46 = outputs[46];
		FAUSTFLOAT* output47 = outputs[47];
		FAUSTFLOAT* output48 = outputs[48];
		FAUSTFLOAT* output49 = outputs[49];
		FAUSTFLOAT* output50 = outputs[50];
		FAUSTFLOAT* output51 = outputs[51];
		FAUSTFLOAT* output52 = outputs[52];
		FAUSTFLOAT* output53 = outputs[53];
		FAUSTFLOAT* output54 = outputs[54];
		FAUSTFLOAT* output55 = outputs[55];
		FAUSTFLOAT* output56 = outputs[56];
		FAUSTFLOAT* output57 = outputs[57];
		FAUSTFLOAT* output58 = outputs[58];
		FAUSTFLOAT* output59 = outputs[59];
		FAUSTFLOAT* output60 = outputs[60];
		FAUSTFLOAT* output61 = outputs[61];
		FAUSTFLOAT* output62 = outputs[62];
		FAUSTFLOAT* output63 = outputs[63];
		FAUSTFLOAT* output64 = outputs[64];
		FAUSTFLOAT* output65 = outputs[65];
		FAUSTFLOAT* output66 = outputs[66];
		FAUSTFLOAT* output67 = outputs[67];
		FAUSTFLOAT* output68 = outputs[68];
		FAUSTFLOAT* output69 = outputs[69];
		FAUSTFLOAT* output70 = outputs[70];
		FAUSTFLOAT* output71 = outputs[71];
		FAUSTFLOAT* output72 = outputs[72];
		FAUSTFLOAT* output73 = outputs[73];
		FAUSTFLOAT* output74 = outputs[74];
		FAUSTFLOAT* output75 = outputs[75];
		FAUSTFLOAT* output76 = outputs[76];
		FAUSTFLOAT* output77 = outputs[77];
		FAUSTFLOAT* output78 = outputs[78];
		FAUSTFLOAT* output79 = outputs[79];
		FAUSTFLOAT* output80 = outputs[80];
		FAUSTFLOAT* output81 = outputs[81];
		FAUSTFLOAT* output82 = outputs[82];
		FAUSTFLOAT* output83 = outputs[83];
		FAUSTFLOAT* output84 = outputs[84];
		FAUSTFLOAT* output85 = outputs[85];
		FAUSTFLOAT* output86 = outputs[86];
		FAUSTFLOAT* output87 = outputs[87];
		FAUSTFLOAT* output88 = outputs[88];
		FAUSTFLOAT* output89 = outputs[89];
		FAUSTFLOAT* output90 = outputs[90];
		FAUSTFLOAT* output91 = outputs[91];
		float fSlow0 = float(fCheckbox0);
		int iSlow1 = fSlow0 != 0.0f;
		float fSlow2 = std::tan(fConst1 * float(fHslider0));
		float fSlow3 = 1.0f / fSlow2;
		float fSlow4 = fSlow3 + 1.0f;
		float fSlow5 = 0.0f - 1.0f / (fSlow2 * fSlow4);
		float fSlow6 = std::max<float>(0.0f, float(fHslider1));
		float fSlow7 = 1.0f / fSlow4;
		float fSlow8 = 1.0f - fSlow3;
		float fSlow9 = fSlow6 / fSlow2;
		float fSlow10 = float(fHslider2);
		int iTemp0 = iTempPerm0;
		int iTemp1 = iTempPerm1;
		int iTemp2 = iTempPerm2;
		float fSlow11 = float(fHslider3);
		int iTemp3 = iTempPerm3;
		float fTemp4 = fTempPerm4;
		float fSlow12 = float(fCheckbox1);
		int iSlow13 = fSlow12 != 0.0f;
		float fSlow14 = std::max<float>(0.0f, float(fHslider4));
		float fSlow15 = fSlow14 / fSlow2;
		int iTemp5 = iTempPerm5;
		int iTemp6 = iTempPerm6;
		int iTemp7 = iTempPerm7;
		int iTemp8 = iTempPerm8;
		float fTemp9 = fTempPerm9;
		float fSlow16 = float(fCheckbox2);
		int iSlow17 = fSlow16 != 0.0f;
		float fSlow18 = std::max<float>(0.0f, float(fHslider5));
		float fSlow19 = fSlow18 / fSlow2;
		int iTemp10 = iTempPerm10;
		int iTemp11 = iTempPerm11;
		int iTemp12 = iTempPerm12;
		int iTemp13 = iTempPerm13;
		float fTemp14 = fTempPerm14;
		float fSlow20 = float(fCheckbox3);
		int iSlow21 = fSlow20 != 0.0f;
		float fSlow22 = std::max<float>(0.0f, float(fHslider6));
		float fSlow23 = fSlow22 / fSlow2;
		int iTemp15 = iTempPerm15;
		int iTemp16 = iTempPerm16;
		int iTemp17 = iTempPerm17;
		int iTemp18 = iTempPerm18;
		float fTemp19 = fTempPerm19;
		float fSlow24 = float(fCheckbox4);
		int iSlow25 = fSlow24 != 0.0f;
		float fSlow26 = std::max<float>(0.0f, float(fHslider7));
		float fSlow27 = fSlow26 / fSlow2;
		int iTemp20 = iTempPerm20;
		int iTemp21 = iTempPerm21;
		int iTemp22 = iTempPerm22;
		int iTemp23 = iTempPerm23;
		float fTemp24 = fTempPerm24;
		float fSlow28 = float(fCheckbox5);
		int iSlow29 = fSlow28 != 0.0f;
		float fSlow30 = std::max<float>(0.0f, float(fHslider8));
		float fSlow31 = fSlow30 / fSlow2;
		int iTemp25 = iTempPerm25;
		int iTemp26 = iTempPerm26;
		int iTemp27 = iTempPerm27;
		int iTemp28 = iTempPerm28;
		float fTemp29 = fTempPerm29;
		float fSlow32 = float(fCheckbox6);
		int iSlow33 = fSlow32 != 0.0f;
		float fSlow34 = float(fCheckbox7);
		int iSlow35 = fSlow34 != 0.0f;
		float fSlow36 = float(fCheckbox8);
		int iSlow37 = fSlow36 != 0.0f;
		float fSlow38 = 1.0f / std::tan(fConst1 * float(fHslider9));
		float fSlow39 = 1.0f / (fSlow38 + 1.0f);
		float fSlow40 = 1.0f - fSlow38;
		float fSlow41 = std::max<float>(0.0f, float(fHslider10));
		float fTemp30 = fTempPerm30;
		float fTemp31 = fTempPerm31;
		float fSlow42 = float(fCheckbox9);
		int iSlow43 = fSlow42 != 0.0f;
		float fSlow44 = float(fCheckbox10);
		int iSlow45 = fSlow44 != 0.0f;
		float fSlow46 = float(fCheckbox11);
		int iSlow47 = fSlow46 != 0.0f;
		float fSlow48 = std::max<float>(0.0f, float(fHslider11));
		float fTemp32 = fTempPerm32;
		float fTemp33 = fTempPerm33;
		float fSlow49 = float(fCheckbox12);
		int iSlow50 = fSlow49 != 0.0f;
		float fSlow51 = float(fCheckbox13);
		int iSlow52 = fSlow51 != 0.0f;
		float fSlow53 = float(fCheckbox14);
		int iSlow54 = fSlow53 != 0.0f;
		float fSlow55 = std::max<float>(0.0f, float(fHslider12));
		float fTemp34 = fTempPerm34;
		float fTemp35 = fTempPerm35;
		float fSlow56 = float(fCheckbox15);
		int iSlow57 = fSlow56 != 0.0f;
		float fSlow58 = std::max<float>(0.0f, float(fHslider13));
		float fTemp36 = fTempPerm36;
		float fTemp37 = fTempPerm37;
		float fSlow59 = float(fCheckbox16);
		int iSlow60 = fSlow59 != 0.0f;
		float fSlow61 = std::max<float>(0.0f, float(fHslider14));
		float fTemp38 = fTempPerm38;
		float fTemp39 = fTempPerm39;
		float fSlow62 = float(fCheckbox17);
		int iSlow63 = fSlow62 != 0.0f;
		float fSlow64 = std::max<float>(0.0f, float(fHslider15));
		float fTemp40 = fTempPerm40;
		float fTemp41 = fTempPerm41;
		float fSlow65 = float(fCheckbox18);
		int iSlow66 = fSlow65 != 0.0f;
		float fSlow67 = float(fHslider16);
		float fSlow68 = fSlow67 + 1.0f;
		float fSlow69 = float(fHslider17);
		float fTemp42 = fTempPerm42;
		float fSlow70 = float(fCheckbox19);
		int iSlow71 = fSlow70 != 0.0f;
		float fSlow72 = float(fHslider18);
		float fTemp43 = fTempPerm43;
		float fSlow73 = float(fCheckbox20);
		int iSlow74 = fSlow73 != 0.0f;
		float fSlow75 = float(fHslider19);
		float fTemp44 = fTempPerm44;
		float fSlow76 = float(fCheckbox21);
		int iSlow77 = fSlow76 != 0.0f;
		float fSlow78 = float(fHslider20);
		float fTemp45 = fTempPerm45;
		float fSlow79 = float(fCheckbox22);
		int iSlow80 = fSlow79 != 0.0f;
		float fSlow81 = float(fHslider21);
		float fTemp46 = fTempPerm46;
		float fSlow82 = float(fCheckbox23);
		int iSlow83 = fSlow82 != 0.0f;
		float fSlow84 = float(fHslider22);
		float fTemp47 = fTempPerm47;
		float fSlow85 = float(fCheckbox24);
		int iSlow86 = fSlow85 != 0.0f;
		float fSlow87 = float(fHslider23);
		float fSlow88 = float(fCheckbox25);
		int iSlow89 = fSlow88 != 0.0f;
		float fSlow90 = float(fCheckbox26);
		int iSlow91 = fSlow90 != 0.0f;
		float fSlow92 = float(fCheckbox27);
		int iSlow93 = fSlow92 != 0.0f;
		float fSlow94 = float(fHslider24);
		float fSlow95 = float(fHslider25);
		float fTemp48 = fTempPerm48;
		float fSlow96 = 0.00100000005f * float(fHslider26);
		int iSlow97 = std::fabs(fSlow96) < 1.1920929e-07f;
		float fThen19 = std::exp(0.0f - fConst2 / ((iSlow97) ? 1.0f : fSlow96));
		float fSlow98 = ((iSlow97) ? 0.0f : fThen19);
		float fSlow99 = 0.00100000005f * float(fHslider27);
		int iSlow100 = std::fabs(fSlow99) < 1.1920929e-07f;
		float fThen21 = std::exp(0.0f - fConst2 / ((iSlow100) ? 1.0f : fSlow99));
		float fSlow101 = ((iSlow100) ? 0.0f : fThen21);
		float fTemp49 = fTempPerm49;
		float fTemp50 = fTempPerm50;
		float fSlow102 = float(fCheckbox28);
		int iSlow103 = fSlow102 != 0.0f;
		float fSlow104 = float(fCheckbox29);
		int iSlow105 = fSlow104 != 0.0f;
		float fSlow106 = float(fCheckbox30);
		int iSlow107 = fSlow106 != 0.0f;
		float fSlow108 = float(fHslider28);
		float fTemp51 = fTempPerm51;
		float fTemp52 = fTempPerm52;
		float fTemp53 = fTempPerm53;
		float fSlow109 = float(fCheckbox31);
		int iSlow110 = fSlow109 != 0.0f;
		float fSlow111 = float(fCheckbox32);
		int iSlow112 = fSlow111 != 0.0f;
		float fSlow113 = float(fCheckbox33);
		int iSlow114 = fSlow113 != 0.0f;
		float fSlow115 = float(fHslider29);
		float fTemp54 = fTempPerm54;
		float fTemp55 = fTempPerm55;
		float fTemp56 = fTempPerm56;
		float fTemp57 = fTempPerm57;
		float fTemp58 = fTempPerm58;
		float fTemp59 = fTempPerm59;
		float fTemp60 = fTempPerm60;
		float fTemp61 = fTempPerm61;
		float fTemp62 = fTempPerm62;
		float fTemp63 = fTempPerm63;
		float fTemp64 = fTempPerm64;
		float fTemp65 = fTempPerm65;
		float fTemp66 = fTempPerm66;
		float fTemp67 = fTempPerm67;
		float fTemp68 = fTempPerm68;
		float fTemp69 = fTempPerm69;
		float fTemp70 = fTempPerm70;
		float fTemp71 = fTempPerm71;
		float fTemp72 = fTempPerm72;
		float fTemp73 = fTempPerm73;
		float fTemp74 = fTempPerm74;
		float fTemp75 = fTempPerm75;
		float fTemp76 = fTempPerm76;
		float fTemp77 = fTempPerm77;
		float fSlow116 = float(fCheckbox34);
		int iSlow117 = fSlow116 != 0.0f;
		float fSlow118 = float(fHslider30);
		float fSlow119 = float(fCheckbox35);
		int iSlow120 = fSlow119 != 0.0f;
		float fSlow121 = float(fCheckbox36);
		int iSlow122 = fSlow121 != 0.0f;
		float fSlow123 = float(fCheckbox37);
		int iSlow124 = fSlow123 != 0.0f;
		float fSlow125 = float(fCheckbox38);
		int iSlow126 = fSlow125 != 0.0f;
		float fSlow127 = fConst6 * float(fHslider31);
		float fSlow128 = float(fHslider32);
		float fTemp78 = fTempPerm78;
		float fSlow129 = 0.00100000005f * float(fHslider33);
		int iSlow130 = std::fabs(fSlow129) < 1.1920929e-07f;
		float fThen33 = std::exp(0.0f - fConst2 / ((iSlow130) ? 1.0f : fSlow129));
		float fSlow131 = ((iSlow130) ? 0.0f : fThen33);
		float fSlow132 = 0.00100000005f * float(fHslider34);
		int iSlow133 = std::fabs(fSlow132) < 1.1920929e-07f;
		float fThen35 = std::exp(0.0f - fConst2 / ((iSlow133) ? 1.0f : fSlow132));
		float fSlow134 = ((iSlow133) ? 0.0f : fThen35);
		float fTemp79 = fTempPerm79;
		float fTemp80 = fTempPerm80;
		float fSlow135 = float(fCheckbox39);
		int iSlow136 = fSlow135 != 0.0f;
		float fSlow137 = float(fCheckbox40);
		int iSlow138 = fSlow137 != 0.0f;
		float fSlow139 = float(fCheckbox41);
		int iSlow140 = fSlow139 != 0.0f;
		float fSlow141 = fConst6 * float(fHslider35);
		float fTemp81 = fTempPerm81;
		float fTemp82 = fTempPerm82;
		float fTemp83 = fTempPerm83;
		float fSlow142 = float(fCheckbox42);
		int iSlow143 = fSlow142 != 0.0f;
		float fSlow144 = float(fCheckbox43);
		int iSlow145 = fSlow144 != 0.0f;
		float fSlow146 = float(fCheckbox44);
		int iSlow147 = fSlow146 != 0.0f;
		float fSlow148 = fConst6 * float(fHslider36);
		float fTemp84 = fTempPerm84;
		float fTemp85 = fTempPerm85;
		float fTemp86 = fTempPerm86;
		float fTemp87 = fTempPerm87;
		float fTemp88 = fTempPerm88;
		float fTemp89 = fTempPerm89;
		float fTemp90 = fTempPerm90;
		float fTemp91 = fTempPerm91;
		float fTemp92 = fTempPerm92;
		float fTemp93 = fTempPerm93;
		float fTemp94 = fTempPerm94;
		float fTemp95 = fTempPerm95;
		float fTemp96 = fTempPerm96;
		float fTemp97 = fTempPerm97;
		float fTemp98 = fTempPerm98;
		float fTemp99 = fTempPerm99;
		float fTemp100 = fTempPerm100;
		float fTemp101 = fTempPerm101;
		float fTemp102 = fTempPerm102;
		float fTemp103 = fTempPerm103;
		float fTemp104 = fTempPerm104;
		float fTemp105 = fTempPerm105;
		float fTemp106 = fTempPerm106;
		float fTemp107 = fTempPerm107;
		float fTemp108 = fTempPerm108;
		float fSlow149 = float(fCheckbox45);
		int iSlow150 = fSlow149 != 0.0f;
		float fSlow151 = float(fHslider37);
		float fSlow152 = float(fCheckbox46);
		int iSlow153 = fSlow152 != 0.0f;
		float fSlow154 = float(fCheckbox47);
		int iSlow155 = fSlow154 != 0.0f;
		float fSlow156 = float(fCheckbox48);
		int iSlow157 = fSlow156 != 0.0f;
		float fSlow158 = float(fCheckbox49);
		int iSlow159 = fSlow158 != 0.0f;
		float fSlow160 = float(fCheckbox50);
		int iSlow161 = fSlow160 != 0.0f;
		float fSlow162 = float(fCheckbox51);
		int iSlow163 = fSlow162 != 0.0f;
		float fTemp109 = fTempPerm109;
		float fSlow164 = float(fCheckbox52);
		int iSlow165 = fSlow164 != 0.0f;
		float fTemp110 = fTempPerm110;
		float fTemp111 = fTempPerm111;
		float fSlow166 = float(fCheckbox53);
		int iSlow167 = fSlow166 != 0.0f;
		float fTemp112 = fTempPerm112;
		float fTemp113 = fTempPerm113;
		float fTemp114 = fTempPerm114;
		float fSlow168 = float(fHslider38);
		float fTemp115 = fTempPerm115;
		float fTemp116 = fTempPerm116;
		float fTemp117 = fTempPerm117;
		float fSlow169 = float(fHslider39);
		float fTemp118 = fTempPerm118;
		float fSlow170 = float(fHslider40);
		float fTemp119 = fTempPerm119;
		float fSlow171 = float(fHslider41);
		float fTemp120 = fTempPerm120;
		float fTemp121 = fTempPerm121;
		float fSlow172 = float(fHslider42);
		float fTemp122 = fTempPerm122;
		float fSlow173 = float(fCheckbox54);
		int iSlow174 = fSlow173 != 0.0f;
		float fSlow175 = float(fCheckbox55);
		int iSlow176 = fSlow175 != 0.0f;
		float fSlow177 = float(fCheckbox56);
		int iSlow178 = fSlow177 != 0.0f;
		float fSlow179 = float(fCheckbox57);
		int iSlow180 = fSlow179 != 0.0f;
		float fSlow181 = float(fCheckbox58);
		int iSlow182 = fSlow181 != 0.0f;
		float fSlow183 = float(fCheckbox59);
		int iSlow184 = fSlow183 != 0.0f;
		float fTemp123 = fTempPerm123;
		float fTemp124 = fTempPerm124;
		float fTemp125 = fTempPerm125;
		float fTemp126 = fTempPerm126;
		float fTemp127 = fTempPerm127;
		float fTemp128 = fTempPerm128;
		float fTemp129 = fTempPerm129;
		float fTemp130 = fTempPerm130;
		float fTemp131 = fTempPerm131;
		float fTemp132 = fTempPerm132;
		float fTemp133 = fTempPerm133;
		float fTemp134 = fTempPerm134;
		float fTemp135 = fTempPerm135;
		float fTemp136 = fTempPerm136;
		float fSlow185 = float(fCheckbox60);
		int iSlow186 = fSlow185 != 0.0f;
		float fSlow187 = float(fCheckbox61);
		int iSlow188 = fSlow187 != 0.0f;
		float fSlow189 = float(fCheckbox62);
		int iSlow190 = fSlow189 != 0.0f;
		float fSlow191 = float(fCheckbox63);
		int iSlow192 = fSlow191 != 0.0f;
		float fSlow193 = float(fCheckbox64);
		int iSlow194 = fSlow193 != 0.0f;
		float fSlow195 = float(fCheckbox65);
		int iSlow196 = fSlow195 != 0.0f;
		float fSlow197 = float(fCheckbox66);
		int iSlow198 = fSlow197 != 0.0f;
		float fSlow199 = float(fCheckbox67);
		int iSlow200 = fSlow199 != 0.0f;
		float fTemp137 = fTempPerm137;
		float fSlow201 = float(fCheckbox68);
		int iSlow202 = fSlow201 != 0.0f;
		float fSlow203 = float(fCheckbox69);
		int iSlow204 = fSlow203 != 0.0f;
		float fTemp138 = fTempPerm138;
		float fTemp139 = fTempPerm139;
		float fSlow205 = float(fCheckbox70);
		int iSlow206 = fSlow205 != 0.0f;
		float fTemp140 = fTempPerm140;
		float fTemp141 = fTempPerm141;
		float fTemp142 = fTempPerm142;
		float fTemp143 = fTempPerm143;
		float fTemp144 = fTempPerm144;
		float fTemp145 = fTempPerm145;
		float fTemp146 = fTempPerm146;
		float fTemp147 = fTempPerm147;
		float fTemp148 = fTempPerm148;
		float fTemp149 = fTempPerm149;
		float fTemp150 = fTempPerm150;
		float fSlow207 = float(fCheckbox71);
		int iSlow208 = fSlow207 != 0.0f;
		float fSlow209 = float(fCheckbox72);
		int iSlow210 = fSlow209 != 0.0f;
		float fSlow211 = float(fCheckbox73);
		int iSlow212 = fSlow211 != 0.0f;
		float fSlow213 = float(fCheckbox74);
		int iSlow214 = fSlow213 != 0.0f;
		float fSlow215 = float(fCheckbox75);
		int iSlow216 = fSlow215 != 0.0f;
		float fSlow217 = float(fCheckbox76);
		int iSlow218 = fSlow217 != 0.0f;
		float fTemp151 = fTempPerm151;
		float fTemp152 = fTempPerm152;
		float fTemp153 = fTempPerm153;
		float fTemp154 = fTempPerm154;
		float fTemp155 = fTempPerm155;
		float fTemp156 = fTempPerm156;
		float fTemp157 = fTempPerm157;
		float fTemp158 = fTempPerm158;
		float fTemp159 = fTempPerm159;
		float fTemp160 = fTempPerm160;
		float fTemp161 = fTempPerm161;
		float fTemp162 = fTempPerm162;
		float fTemp163 = fTempPerm163;
		float fTemp164 = fTempPerm164;
		float fSlow219 = float(fCheckbox77);
		int iSlow220 = fSlow219 != 0.0f;
		float fSlow221 = float(fCheckbox78);
		int iSlow222 = fSlow221 != 0.0f;
		float fSlow223 = float(fCheckbox79);
		int iSlow224 = fSlow223 != 0.0f;
		float fSlow225 = float(fCheckbox80);
		int iSlow226 = fSlow225 != 0.0f;
		float fSlow227 = float(fCheckbox81);
		int iSlow228 = fSlow227 != 0.0f;
		float fSlow229 = float(fCheckbox82);
		int iSlow230 = fSlow229 != 0.0f;
		float fSlow231 = float(fCheckbox83);
		int iSlow232 = fSlow231 != 0.0f;
		float fTemp165 = fTempPerm165;
		float fSlow233 = float(fCheckbox84);
		int iSlow234 = fSlow233 != 0.0f;
		float fTemp166 = fTempPerm166;
		float fTemp167 = fTempPerm167;
		float fSlow235 = float(fCheckbox85);
		int iSlow236 = fSlow235 != 0.0f;
		float fTemp168 = fTempPerm168;
		float fTemp169 = fTempPerm169;
		float fTemp170 = fTempPerm170;
		float fTemp171 = fTempPerm171;
		float fTemp172 = fTempPerm172;
		float fTemp173 = fTempPerm173;
		float fTemp174 = fTempPerm174;
		float fTemp175 = fTempPerm175;
		float fTemp176 = fTempPerm176;
		float fTemp177 = fTempPerm177;
		float fTemp178 = fTempPerm178;
		float fSlow237 = float(fCheckbox86);
		int iSlow238 = fSlow237 != 0.0f;
		float fSlow239 = float(fCheckbox87);
		int iSlow240 = fSlow239 != 0.0f;
		float fSlow241 = float(fCheckbox88);
		int iSlow242 = fSlow241 != 0.0f;
		float fSlow243 = float(fCheckbox89);
		int iSlow244 = fSlow243 != 0.0f;
		float fSlow245 = float(fCheckbox90);
		int iSlow246 = fSlow245 != 0.0f;
		float fSlow247 = float(fCheckbox91);
		int iSlow248 = fSlow247 != 0.0f;
		float fTemp179 = fTempPerm179;
		float fTemp180 = fTempPerm180;
		float fTemp181 = fTempPerm181;
		float fTemp182 = fTempPerm182;
		float fTemp183 = fTempPerm183;
		float fTemp184 = fTempPerm184;
		float fTemp185 = fTempPerm185;
		float fTemp186 = fTempPerm186;
		float fTemp187 = fTempPerm187;
		float fTemp188 = fTempPerm188;
		float fTemp189 = fTempPerm189;
		float fTemp190 = fTempPerm190;
		float fTemp191 = fTempPerm191;
		float fTemp192 = fTempPerm192;
		float fTemp193 = fTempPerm193;
		float fTemp194 = fTempPerm194;
		float fTemp195 = fTempPerm195;
		float fTemp196 = fTempPerm196;
		float fTemp197 = fTempPerm197;
		float fTemp198 = fTempPerm198;
		float fTemp199 = fTempPerm199;
		float fTemp200 = fTempPerm200;
		float fTemp201 = fTempPerm201;
		float fTemp202 = fTempPerm202;
		float fTemp203 = fTempPerm203;
		float fTemp204 = fTempPerm204;
		float fTemp205 = fTempPerm205;
		float fTemp206 = fTempPerm206;
		float fTemp207 = fTempPerm207;
		float fTemp208 = fTempPerm208;
		float fTemp209 = fTempPerm209;
		float fSlow249 = 5.0f * fSlow125;
		float fTemp210 = fTempPerm210;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			int iRec1 = 0;
			int iRec6 = 0;
			int iRec11 = 0;
			int iRec16 = 0;
			int iRec21 = 0;
			int iRec26 = 0;
			if ((iSlow1)) {
				fVec0[0] = fSlow6;
				fRec3[0] = fSlow5 * fVec0[1] - fSlow7 * (fSlow8 * fRec3[1] - fSlow9);
				iTemp0 = fRec3[0] > fSlow10;
				iVec1[0] = iTemp0;
				iTemp1 = iTemp0 > iVec1[1];
			}
			int iElse0 = iRec2[1] + 1;
			if ((iSlow1)) {
				iRec2[0] = ((iTemp1) ? iElse0 : iRec2[1]);
			}
			int iElse2 = ((std::min<int>(1, iRec2[0]) == 1) ? iTemp1 : 0);
			if ((iSlow1)) {
				iTemp2 = ((iRec0[1]) ? iElse2 : 1);
				fRec4[0] = (fConst2 + fRec4[1]) * float(iTemp2);
				iTemp3 = iTemp2 * (1000.0f * fRec4[0] < fSlow11);
				iRec0[0] = iTemp3 == 0;
				iRec1 = iTemp3;
				fTemp4 = fSlow0 * float(iRec1);
			}
			output0[i0] = FAUSTFLOAT(fTemp4);
			if ((iSlow13)) {
				fVec2[0] = fSlow14;
				fRec8[0] = fSlow5 * fVec2[1] - fSlow7 * (fSlow8 * fRec8[1] - fSlow15);
				iTemp5 = fRec8[0] > fSlow10;
				iVec3[0] = iTemp5;
				iTemp6 = iTemp5 > iVec3[1];
			}
			int iElse3 = iRec7[1] + 1;
			if ((iSlow13)) {
				iRec7[0] = ((iTemp6) ? iElse3 : iRec7[1]);
			}
			int iElse5 = ((std::min<int>(1, iRec7[0]) == 1) ? iTemp6 : 0);
			if ((iSlow13)) {
				iTemp7 = ((iRec5[1]) ? iElse5 : 1);
				fRec9[0] = (fConst2 + fRec9[1]) * float(iTemp7);
				iTemp8 = iTemp7 * (1000.0f * fRec9[0] < fSlow11);
				iRec5[0] = iTemp8 == 0;
				iRec6 = iTemp8;
				fTemp9 = fSlow12 * float(iRec6);
			}
			output1[i0] = FAUSTFLOAT(fTemp9);
			if ((iSlow17)) {
				fVec4[0] = fSlow18;
				fRec13[0] = fSlow5 * fVec4[1] - fSlow7 * (fSlow8 * fRec13[1] - fSlow19);
				iTemp10 = fRec13[0] > fSlow10;
				iVec5[0] = iTemp10;
				iTemp11 = iTemp10 > iVec5[1];
			}
			int iElse6 = iRec12[1] + 1;
			if ((iSlow17)) {
				iRec12[0] = ((iTemp11) ? iElse6 : iRec12[1]);
			}
			int iElse8 = ((std::min<int>(1, iRec12[0]) == 1) ? iTemp11 : 0);
			if ((iSlow17)) {
				iTemp12 = ((iRec10[1]) ? iElse8 : 1);
				fRec14[0] = (fConst2 + fRec14[1]) * float(iTemp12);
				iTemp13 = iTemp12 * (1000.0f * fRec14[0] < fSlow11);
				iRec10[0] = iTemp13 == 0;
				iRec11 = iTemp13;
				fTemp14 = fSlow16 * float(iRec11);
			}
			output2[i0] = FAUSTFLOAT(fTemp14);
			if ((iSlow21)) {
				fVec6[0] = fSlow22;
				fRec18[0] = fSlow5 * fVec6[1] - fSlow7 * (fSlow8 * fRec18[1] - fSlow23);
				iTemp15 = fRec18[0] > fSlow10;
				iVec7[0] = iTemp15;
				iTemp16 = iTemp15 > iVec7[1];
			}
			int iElse9 = iRec17[1] + 1;
			if ((iSlow21)) {
				iRec17[0] = ((iTemp16) ? iElse9 : iRec17[1]);
			}
			int iElse11 = ((std::min<int>(1, iRec17[0]) == 1) ? iTemp16 : 0);
			if ((iSlow21)) {
				iTemp17 = ((iRec15[1]) ? iElse11 : 1);
				fRec19[0] = (fConst2 + fRec19[1]) * float(iTemp17);
				iTemp18 = iTemp17 * (1000.0f * fRec19[0] < fSlow11);
				iRec15[0] = iTemp18 == 0;
				iRec16 = iTemp18;
				fTemp19 = fSlow20 * float(iRec16);
			}
			output3[i0] = FAUSTFLOAT(fTemp19);
			if ((iSlow25)) {
				fVec8[0] = fSlow26;
				fRec23[0] = fSlow5 * fVec8[1] - fSlow7 * (fSlow8 * fRec23[1] - fSlow27);
				iTemp20 = fRec23[0] > fSlow10;
				iVec9[0] = iTemp20;
				iTemp21 = iTemp20 > iVec9[1];
			}
			int iElse12 = iRec22[1] + 1;
			if ((iSlow25)) {
				iRec22[0] = ((iTemp21) ? iElse12 : iRec22[1]);
			}
			int iElse14 = ((std::min<int>(1, iRec22[0]) == 1) ? iTemp21 : 0);
			if ((iSlow25)) {
				iTemp22 = ((iRec20[1]) ? iElse14 : 1);
				fRec24[0] = (fConst2 + fRec24[1]) * float(iTemp22);
				iTemp23 = iTemp22 * (1000.0f * fRec24[0] < fSlow11);
				iRec20[0] = iTemp23 == 0;
				iRec21 = iTemp23;
				fTemp24 = fSlow24 * float(iRec21);
			}
			output4[i0] = FAUSTFLOAT(fTemp24);
			if ((iSlow29)) {
				fVec10[0] = fSlow30;
				fRec28[0] = fSlow5 * fVec10[1] - fSlow7 * (fSlow8 * fRec28[1] - fSlow31);
				iTemp25 = fRec28[0] > fSlow10;
				iVec11[0] = iTemp25;
				iTemp26 = iTemp25 > iVec11[1];
			}
			int iElse15 = iRec27[1] + 1;
			if ((iSlow29)) {
				iRec27[0] = ((iTemp26) ? iElse15 : iRec27[1]);
			}
			int iElse17 = ((std::min<int>(1, iRec27[0]) == 1) ? iTemp26 : 0);
			if ((iSlow29)) {
				iTemp27 = ((iRec25[1]) ? iElse17 : 1);
				fRec29[0] = (fConst2 + fRec29[1]) * float(iTemp27);
				iTemp28 = iTemp27 * (1000.0f * fRec29[0] < fSlow11);
				iRec25[0] = iTemp28 == 0;
				iRec26 = iTemp28;
				fTemp29 = fSlow28 * float(iRec26);
			}
			output5[i0] = FAUSTFLOAT(fTemp29);
			if ((iSlow35 | (iSlow37 | iSlow33))) {
				fVec12[0] = fSlow41;
				fRec30[0] = 0.0f - fSlow39 * (fSlow40 * fRec30[1] - (fSlow41 + fVec12[1]));
				fTemp30 = std::min<float>(1.0f, std::max<float>(0.0f, fRec30[0]));
			}
			if ((iSlow33)) {
				fTemp31 = fSlow32 * fTemp30;
			}
			output6[i0] = FAUSTFLOAT(fTemp31);
			if ((iSlow45 | (iSlow47 | iSlow43))) {
				fVec13[0] = fSlow48;
				fRec31[0] = 0.0f - fSlow39 * (fSlow40 * fRec31[1] - (fSlow48 + fVec13[1]));
				fTemp32 = std::min<float>(1.0f, std::max<float>(0.0f, fRec31[0]));
			}
			if ((iSlow43)) {
				fTemp33 = fSlow42 * fTemp32;
			}
			output7[i0] = FAUSTFLOAT(fTemp33);
			if ((iSlow52 | (iSlow54 | iSlow50))) {
				fVec14[0] = fSlow55;
				fRec32[0] = 0.0f - fSlow39 * (fSlow40 * fRec32[1] - (fSlow55 + fVec14[1]));
				fTemp34 = std::min<float>(1.0f, std::max<float>(0.0f, fRec32[0]));
			}
			if ((iSlow50)) {
				fTemp35 = fSlow49 * fTemp34;
			}
			output8[i0] = FAUSTFLOAT(fTemp35);
			if ((iSlow35 | (iSlow37 | iSlow57))) {
				fVec15[0] = fSlow58;
				fRec33[0] = 0.0f - fSlow39 * (fSlow40 * fRec33[1] - (fSlow58 + fVec15[1]));
				fTemp36 = std::min<float>(1.0f, std::max<float>(0.0f, fRec33[0]));
			}
			if ((iSlow57)) {
				fTemp37 = fSlow56 * fTemp36;
			}
			output9[i0] = FAUSTFLOAT(fTemp37);
			if ((iSlow45 | (iSlow47 | iSlow60))) {
				fVec16[0] = fSlow61;
				fRec34[0] = 0.0f - fSlow39 * (fSlow40 * fRec34[1] - (fSlow61 + fVec16[1]));
				fTemp38 = std::min<float>(1.0f, std::max<float>(0.0f, fRec34[0]));
			}
			if ((iSlow60)) {
				fTemp39 = fSlow59 * fTemp38;
			}
			output10[i0] = FAUSTFLOAT(fTemp39);
			if ((iSlow52 | (iSlow54 | iSlow63))) {
				fVec17[0] = fSlow64;
				fRec35[0] = 0.0f - fSlow39 * (fSlow40 * fRec35[1] - (fSlow64 + fVec17[1]));
				fTemp40 = std::min<float>(1.0f, std::max<float>(0.0f, fRec35[0]));
			}
			if ((iSlow63)) {
				fTemp41 = fSlow62 * fTemp40;
			}
			output11[i0] = FAUSTFLOAT(fTemp41);
			if ((iSlow66)) {
				fVec18[0] = fSlow69;
				fRec36[0] = 0.0f - fSlow39 * (fSlow40 * fRec36[1] - (fSlow69 + fVec18[1]));
				fTemp42 = fSlow65 * std::min<float>(1.0f, std::max<float>(0.0f, fSlow68 * std::max<float>(0.0f, 0.5f * (0.636619747f * std::asin(std::min<float>(1.0f, std::max<float>(-1.0f, fRec36[0]))) + 1.0f) - fSlow67)));
			}
			output12[i0] = FAUSTFLOAT(fTemp42);
			if ((iSlow71)) {
				fVec19[0] = fSlow72;
				fRec37[0] = 0.0f - fSlow39 * (fSlow40 * fRec37[1] - (fSlow72 + fVec19[1]));
				fTemp43 = fSlow70 * std::min<float>(1.0f, std::max<float>(0.0f, fSlow68 * std::max<float>(0.0f, 0.5f * (0.636619747f * std::asin(std::min<float>(1.0f, std::max<float>(-1.0f, fRec37[0]))) + 1.0f) - fSlow67)));
			}
			output13[i0] = FAUSTFLOAT(fTemp43);
			if ((iSlow74)) {
				fVec20[0] = fSlow75;
				fRec38[0] = 0.0f - fSlow39 * (fSlow40 * fRec38[1] - (fSlow75 + fVec20[1]));
				fTemp44 = fSlow73 * std::min<float>(1.0f, std::max<float>(0.0f, fSlow68 * std::max<float>(0.0f, 0.5f * (0.636619747f * std::asin(std::min<float>(1.0f, std::max<float>(-1.0f, fRec38[0]))) + 1.0f) - fSlow67)));
			}
			output14[i0] = FAUSTFLOAT(fTemp44);
			if ((iSlow77)) {
				fVec21[0] = fSlow78;
				fRec39[0] = 0.0f - fSlow39 * (fSlow40 * fRec39[1] - (fSlow78 + fVec21[1]));
				fTemp45 = fSlow76 * std::min<float>(1.0f, std::max<float>(0.0f, fSlow68 * std::max<float>(0.0f, 0.5f * (0.636619747f * std::asin(std::min<float>(1.0f, std::max<float>(-1.0f, fRec39[0]))) + 1.0f) - fSlow67)));
			}
			output15[i0] = FAUSTFLOAT(fTemp45);
			if ((iSlow80)) {
				fVec22[0] = fSlow81;
				fRec40[0] = 0.0f - fSlow39 * (fSlow40 * fRec40[1] - (fSlow81 + fVec22[1]));
				fTemp46 = fSlow79 * std::min<float>(1.0f, std::max<float>(0.0f, fSlow68 * std::max<float>(0.0f, 0.5f * (0.636619747f * std::asin(std::min<float>(1.0f, std::max<float>(-1.0f, fRec40[0]))) + 1.0f) - fSlow67)));
			}
			output16[i0] = FAUSTFLOAT(fTemp46);
			if ((iSlow83)) {
				fVec23[0] = fSlow84;
				fRec41[0] = 0.0f - fSlow39 * (fSlow40 * fRec41[1] - (fSlow84 + fVec23[1]));
				fTemp47 = fSlow82 * std::min<float>(1.0f, std::max<float>(0.0f, fSlow68 * std::max<float>(0.0f, 0.5f * (0.636619747f * std::asin(std::min<float>(1.0f, std::max<float>(-1.0f, fRec41[0]))) + 1.0f) - fSlow67)));
			}
			output17[i0] = FAUSTFLOAT(fTemp47);
			if ((iSlow86 | (iSlow89 | (iSlow91 | iSlow93)))) {
				fVec24[0] = fSlow94;
				fRec44[0] = fConst4 * (fSlow94 - fVec24[1] + fConst5 * fRec44[1]);
			}
			if ((iSlow86)) {
				fTemp48 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, std::fabs(fRec44[0]) - fSlow95)));
				fTemp49 = ((fRec42[1] > fTemp48) ? fSlow101 : fSlow98);
				fRec43[0] = fTemp48 * (1.0f - fTemp49) + fTemp49 * fRec43[1];
				fRec42[0] = fRec43[0];
				fTemp50 = fSlow85 * fRec42[0];
			}
			output18[i0] = FAUSTFLOAT(fTemp50);
			if ((iSlow103 | (iSlow105 | (iSlow107 | iSlow93)))) {
				fVec25[0] = fSlow108;
				fRec47[0] = fConst4 * (fSlow108 - fVec25[1] + fConst5 * fRec47[1]);
			}
			if ((iSlow103)) {
				fTemp51 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, std::fabs(fRec47[0]) - fSlow95)));
				fTemp52 = ((fRec45[1] > fTemp51) ? fSlow101 : fSlow98);
				fRec46[0] = fTemp51 * (1.0f - fTemp52) + fTemp52 * fRec46[1];
				fRec45[0] = fRec46[0];
				fTemp53 = fSlow102 * fRec45[0];
			}
			output19[i0] = FAUSTFLOAT(fTemp53);
			if ((iSlow110 | (iSlow112 | (iSlow114 | iSlow93)))) {
				fVec26[0] = fSlow115;
				fRec50[0] = fConst4 * (fSlow115 - fVec26[1] + fConst5 * fRec50[1]);
			}
			if ((iSlow110)) {
				fTemp54 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, std::fabs(fRec50[0]) - fSlow95)));
				fTemp55 = ((fRec48[1] > fTemp54) ? fSlow101 : fSlow98);
				fRec49[0] = fTemp54 * (1.0f - fTemp55) + fTemp55 * fRec49[1];
				fRec48[0] = fRec49[0];
				fTemp56 = fSlow109 * fRec48[0];
			}
			output20[i0] = FAUSTFLOAT(fTemp56);
			if ((iSlow89)) {
				fTemp57 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, fRec44[0] - fSlow95)));
				fTemp58 = ((fRec51[1] > fTemp57) ? fSlow101 : fSlow98);
				fRec52[0] = fTemp57 * (1.0f - fTemp58) + fTemp58 * fRec52[1];
				fRec51[0] = fRec52[0];
				fTemp59 = fSlow88 * fRec51[0];
			}
			output21[i0] = FAUSTFLOAT(fTemp59);
			if ((iSlow105)) {
				fTemp60 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, fRec47[0] - fSlow95)));
				fTemp61 = ((fRec53[1] > fTemp60) ? fSlow101 : fSlow98);
				fRec54[0] = fTemp60 * (1.0f - fTemp61) + fTemp61 * fRec54[1];
				fRec53[0] = fRec54[0];
				fTemp62 = fSlow104 * fRec53[0];
			}
			output22[i0] = FAUSTFLOAT(fTemp62);
			if ((iSlow112)) {
				fTemp63 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, fRec50[0] - fSlow95)));
				fTemp64 = ((fRec55[1] > fTemp63) ? fSlow101 : fSlow98);
				fRec56[0] = fTemp63 * (1.0f - fTemp64) + fTemp64 * fRec56[1];
				fRec55[0] = fRec56[0];
				fTemp65 = fSlow111 * fRec55[0];
			}
			output23[i0] = FAUSTFLOAT(fTemp65);
			if ((iSlow91)) {
				fTemp66 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, 0.0f - (fSlow95 + fRec44[0]))));
				fTemp67 = ((fRec57[1] > fTemp66) ? fSlow101 : fSlow98);
				fRec58[0] = fTemp66 * (1.0f - fTemp67) + fTemp67 * fRec58[1];
				fRec57[0] = fRec58[0];
				fTemp68 = fSlow90 * fRec57[0];
			}
			output24[i0] = FAUSTFLOAT(fTemp68);
			if ((iSlow107)) {
				fTemp69 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, 0.0f - (fSlow95 + fRec47[0]))));
				fTemp70 = ((fRec59[1] > fTemp69) ? fSlow101 : fSlow98);
				fRec60[0] = fTemp69 * (1.0f - fTemp70) + fTemp70 * fRec60[1];
				fRec59[0] = fRec60[0];
				fTemp71 = fSlow106 * fRec59[0];
			}
			output25[i0] = FAUSTFLOAT(fTemp71);
			if ((iSlow114)) {
				fTemp72 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, 0.0f - (fSlow95 + fRec50[0]))));
				fTemp73 = ((fRec61[1] > fTemp72) ? fSlow101 : fSlow98);
				fRec62[0] = fTemp72 * (1.0f - fTemp73) + fTemp73 * fRec62[1];
				fRec61[0] = fRec62[0];
				fTemp74 = fSlow113 * fRec61[0];
			}
			output26[i0] = FAUSTFLOAT(fTemp74);
			if ((iSlow93)) {
				fTemp75 = std::fabs(std::min<float>(1.0f, fSlow87 * std::max<float>(0.0f, std::sqrt(mydsp2_faustpower2_f(fRec44[0]) + mydsp2_faustpower2_f(fRec47[0]) + mydsp2_faustpower2_f(fRec50[0])) - fSlow95)));
				fTemp76 = ((fRec63[1] > fTemp75) ? fSlow101 : fSlow98);
				fRec64[0] = fTemp75 * (1.0f - fTemp76) + fTemp76 * fRec64[1];
				fRec63[0] = fRec64[0];
				fTemp77 = fSlow92 * fRec63[0];
			}
			output27[i0] = FAUSTFLOAT(fTemp77);
			if ((iSlow117 | (iSlow120 | (iSlow122 | (iSlow124 | iSlow126))))) {
				fRec67[0] = fSlow127 + fConst7 * fRec67[1];
			}
			if ((iSlow117)) {
				fTemp78 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, std::fabs(fRec67[0]) - fSlow128)));
				fTemp79 = ((fRec65[1] > fTemp78) ? fSlow134 : fSlow131);
				fRec66[0] = fTemp78 * (1.0f - fTemp79) + fTemp79 * fRec66[1];
				fRec65[0] = fRec66[0];
				fTemp80 = fSlow116 * fRec65[0];
			}
			output28[i0] = FAUSTFLOAT(fTemp80);
			if ((iSlow136 | (iSlow138 | (iSlow140 | (iSlow124 | iSlow126))))) {
				fRec70[0] = fSlow141 + fConst7 * fRec70[1];
			}
			if ((iSlow136)) {
				fTemp81 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, std::fabs(fRec70[0]) - fSlow128)));
				fTemp82 = ((fRec68[1] > fTemp81) ? fSlow134 : fSlow131);
				fRec69[0] = fTemp81 * (1.0f - fTemp82) + fTemp82 * fRec69[1];
				fRec68[0] = fRec69[0];
				fTemp83 = fSlow135 * fRec68[0];
			}
			output29[i0] = FAUSTFLOAT(fTemp83);
			if ((iSlow143 | (iSlow145 | (iSlow147 | iSlow124)))) {
				fRec73[0] = fSlow148 + fConst7 * fRec73[1];
			}
			if ((iSlow143)) {
				fTemp84 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, std::fabs(fRec73[0]) - fSlow128)));
				fTemp85 = ((fRec71[1] > fTemp84) ? fSlow134 : fSlow131);
				fRec72[0] = fTemp84 * (1.0f - fTemp85) + fTemp85 * fRec72[1];
				fRec71[0] = fRec72[0];
				fTemp86 = fSlow142 * fRec71[0];
			}
			output30[i0] = FAUSTFLOAT(fTemp86);
			if ((iSlow120)) {
				fTemp87 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, fRec67[0] - fSlow128)));
				fTemp88 = ((fRec74[1] > fTemp87) ? fSlow134 : fSlow131);
				fRec75[0] = fTemp87 * (1.0f - fTemp88) + fTemp88 * fRec75[1];
				fRec74[0] = fRec75[0];
				fTemp89 = fSlow119 * fRec74[0];
			}
			output31[i0] = FAUSTFLOAT(fTemp89);
			if ((iSlow138)) {
				fTemp90 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, fRec70[0] - fSlow128)));
				fTemp91 = ((fRec76[1] > fTemp90) ? fSlow134 : fSlow131);
				fRec77[0] = fTemp90 * (1.0f - fTemp91) + fTemp91 * fRec77[1];
				fRec76[0] = fRec77[0];
				fTemp92 = fSlow137 * fRec76[0];
			}
			output32[i0] = FAUSTFLOAT(fTemp92);
			if ((iSlow145)) {
				fTemp93 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, fRec73[0] - fSlow128)));
				fTemp94 = ((fRec78[1] > fTemp93) ? fSlow134 : fSlow131);
				fRec79[0] = fTemp93 * (1.0f - fTemp94) + fTemp94 * fRec79[1];
				fRec78[0] = fRec79[0];
				fTemp95 = fSlow144 * fRec78[0];
			}
			output33[i0] = FAUSTFLOAT(fTemp95);
			if ((iSlow122)) {
				fTemp96 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, 0.0f - (fSlow128 + fRec67[0]))));
				fTemp97 = ((fRec80[1] > fTemp96) ? fSlow134 : fSlow131);
				fRec81[0] = fTemp96 * (1.0f - fTemp97) + fTemp97 * fRec81[1];
				fRec80[0] = fRec81[0];
				fTemp98 = fSlow121 * fRec80[0];
			}
			output34[i0] = FAUSTFLOAT(fTemp98);
			if ((iSlow140)) {
				fTemp99 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, 0.0f - (fSlow128 + fRec70[0]))));
				fTemp100 = ((fRec82[1] > fTemp99) ? fSlow134 : fSlow131);
				fRec83[0] = fTemp99 * (1.0f - fTemp100) + fTemp100 * fRec83[1];
				fRec82[0] = fRec83[0];
				fTemp101 = fSlow139 * fRec82[0];
			}
			output35[i0] = FAUSTFLOAT(fTemp101);
			if ((iSlow147)) {
				fTemp102 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, 0.0f - (fSlow128 + fRec73[0]))));
				fTemp103 = ((fRec84[1] > fTemp102) ? fSlow134 : fSlow131);
				fRec85[0] = fTemp102 * (1.0f - fTemp103) + fTemp103 * fRec85[1];
				fRec84[0] = fRec85[0];
				fTemp104 = fSlow146 * fRec84[0];
			}
			output36[i0] = FAUSTFLOAT(fTemp104);
			if ((iSlow124 | iSlow126)) {
				fTemp105 = mydsp2_faustpower2_f(fRec67[0]) + mydsp2_faustpower2_f(fRec70[0]);
			}
			if ((iSlow124)) {
				fTemp106 = std::fabs(std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, std::sqrt(fTemp105 + mydsp2_faustpower2_f(fRec73[0])) - fSlow128)));
				fTemp107 = ((fRec86[1] > fTemp106) ? fSlow134 : fSlow131);
				fRec87[0] = fTemp106 * (1.0f - fTemp107) + fTemp107 * fRec87[1];
				fRec86[0] = fRec87[0];
				fTemp108 = fSlow123 * fRec86[0];
			}
			output37[i0] = FAUSTFLOAT(fTemp108);
			if ((iSlow150 | (iSlow153 | (iSlow155 | (iSlow157 | (iSlow159 | (iSlow161 | iSlow163))))))) {
				fTemp109 = float(input0[i0]);
			}
			if ((iSlow150 | (iSlow153 | (iSlow155 | (iSlow157 | (iSlow159 | (iSlow161 | iSlow165))))))) {
				fTemp110 = float(input1[i0]);
			}
			if ((iSlow150 | (iSlow155 | (iSlow159 | iSlow161)))) {
				fTemp111 = mydsp2_faustpower2_f(fTemp110);
			}
			if ((iSlow150 | (iSlow153 | (iSlow155 | (iSlow157 | (iSlow159 | (iSlow161 | iSlow167))))))) {
				fTemp112 = float(input2[i0]);
			}
			if ((iSlow150 | (iSlow153 | (iSlow155 | iSlow157)))) {
				fTemp113 = mydsp2_faustpower2_f(fTemp112);
			}
			if ((iSlow150)) {
				fRec88[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow151 * std::sqrt(mydsp2_faustpower2_f(fTemp109 + 1.0f) + fTemp111 + fTemp113)) + fConst8 * fRec88[1];
				fTemp114 = fSlow149 * fRec88[0];
			}
			output38[i0] = FAUSTFLOAT(fTemp114);
			if ((iSlow153 | (iSlow157 | (iSlow159 | iSlow161)))) {
				fTemp115 = mydsp2_faustpower2_f(fTemp109);
			}
			if ((iSlow153 | iSlow157)) {
				fTemp116 = fTemp113 + fTemp115;
			}
			if ((iSlow153)) {
				fRec89[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow168 * std::sqrt(mydsp2_faustpower2_f(fTemp110 + 1.0f) + fTemp116)) + fConst8 * fRec89[1];
				fTemp117 = fSlow152 * fRec89[0];
			}
			output39[i0] = FAUSTFLOAT(fTemp117);
			if ((iSlow155)) {
				fRec90[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow169 * std::sqrt(mydsp2_faustpower2_f(fTemp109 + -1.0f) + fTemp111 + fTemp113)) + fConst8 * fRec90[1];
				fTemp118 = fSlow154 * fRec90[0];
			}
			output40[i0] = FAUSTFLOAT(fTemp118);
			if ((iSlow157)) {
				fRec91[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow170 * std::sqrt(fTemp116 + mydsp2_faustpower2_f(fTemp110 + -1.0f))) + fConst8 * fRec91[1];
				fTemp119 = fSlow156 * fRec91[0];
			}
			output41[i0] = FAUSTFLOAT(fTemp119);
			if ((iSlow159 | iSlow161)) {
				fTemp120 = fTemp111 + fTemp115;
			}
			if ((iSlow159)) {
				fRec92[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow171 * std::sqrt(fTemp120 + mydsp2_faustpower2_f(fTemp112 + 1.0f))) + fConst8 * fRec92[1];
				fTemp121 = fSlow158 * fRec92[0];
			}
			output42[i0] = FAUSTFLOAT(fTemp121);
			if ((iSlow161)) {
				fRec93[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow172 * std::sqrt(fTemp120 + mydsp2_faustpower2_f(fTemp112 + -1.0f))) + fConst8 * fRec93[1];
				fTemp122 = fSlow160 * fRec93[0];
			}
			output43[i0] = FAUSTFLOAT(fTemp122);
			if ((iSlow174 | (iSlow176 | (iSlow178 | (iSlow180 | (iSlow182 | iSlow184)))))) {
				fTemp123 = float(input3[i0]);
				fTemp124 = float(input4[i0]);
			}
			if ((iSlow174 | (iSlow178 | (iSlow182 | iSlow184)))) {
				fTemp125 = mydsp2_faustpower2_f(fTemp124);
			}
			if ((iSlow174 | (iSlow176 | (iSlow178 | (iSlow180 | (iSlow182 | iSlow184)))))) {
				fTemp126 = float(input5[i0]);
			}
			if ((iSlow174 | (iSlow176 | (iSlow178 | iSlow180)))) {
				fTemp127 = mydsp2_faustpower2_f(fTemp126);
			}
			if ((iSlow174)) {
				fRec94[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow151 * std::sqrt(mydsp2_faustpower2_f(fTemp123 + 1.0f) + fTemp125 + fTemp127)) + fConst8 * fRec94[1];
				fTemp128 = fSlow173 * fRec94[0];
			}
			output44[i0] = FAUSTFLOAT(fTemp128);
			if ((iSlow176 | (iSlow180 | (iSlow182 | iSlow184)))) {
				fTemp129 = mydsp2_faustpower2_f(fTemp123);
			}
			if ((iSlow176 | iSlow180)) {
				fTemp130 = fTemp127 + fTemp129;
			}
			if ((iSlow176)) {
				fRec95[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow168 * std::sqrt(mydsp2_faustpower2_f(fTemp124 + 1.0f) + fTemp130)) + fConst8 * fRec95[1];
				fTemp131 = fSlow175 * fRec95[0];
			}
			output45[i0] = FAUSTFLOAT(fTemp131);
			if ((iSlow178)) {
				fRec96[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow169 * std::sqrt(mydsp2_faustpower2_f(fTemp123 + -1.0f) + fTemp125 + fTemp127)) + fConst8 * fRec96[1];
				fTemp132 = fSlow177 * fRec96[0];
			}
			output46[i0] = FAUSTFLOAT(fTemp132);
			if ((iSlow180)) {
				fRec97[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow170 * std::sqrt(fTemp130 + mydsp2_faustpower2_f(fTemp124 + -1.0f))) + fConst8 * fRec97[1];
				fTemp133 = fSlow179 * fRec97[0];
			}
			output47[i0] = FAUSTFLOAT(fTemp133);
			if ((iSlow182 | iSlow184)) {
				fTemp134 = fTemp125 + fTemp129;
			}
			if ((iSlow182)) {
				fRec98[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow171 * std::sqrt(fTemp134 + mydsp2_faustpower2_f(fTemp126 + 1.0f))) + fConst8 * fRec98[1];
				fTemp135 = fSlow181 * fRec98[0];
			}
			output48[i0] = FAUSTFLOAT(fTemp135);
			if ((iSlow184)) {
				fRec99[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow172 * std::sqrt(fTemp134 + mydsp2_faustpower2_f(fTemp126 + -1.0f))) + fConst8 * fRec99[1];
				fTemp136 = fSlow183 * fRec99[0];
			}
			output49[i0] = FAUSTFLOAT(fTemp136);
			if ((iSlow186 | (iSlow188 | (iSlow190 | (iSlow192 | (iSlow194 | (iSlow196 | (iSlow198 | iSlow200)))))))) {
				fTemp137 = float(input6[i0]);
			}
			if ((iSlow186 | (iSlow188 | (iSlow190 | (iSlow192 | (iSlow194 | (iSlow196 | (iSlow202 | iSlow204)))))))) {
				fTemp138 = float(input7[i0]);
			}
			if ((iSlow186 | (iSlow190 | (iSlow194 | iSlow196)))) {
				fTemp139 = mydsp2_faustpower2_f(fTemp138);
			}
			if ((iSlow186 | (iSlow188 | (iSlow190 | (iSlow192 | (iSlow194 | (iSlow196 | iSlow206))))))) {
				fTemp140 = float(input8[i0]);
			}
			if ((iSlow186 | (iSlow188 | (iSlow190 | iSlow192)))) {
				fTemp141 = mydsp2_faustpower2_f(fTemp140);
			}
			if ((iSlow186)) {
				fRec100[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow151 * std::sqrt(mydsp2_faustpower2_f(fTemp137 + 1.0f) + fTemp139 + fTemp141)) + fConst8 * fRec100[1];
				fTemp142 = fSlow185 * fRec100[0];
			}
			output50[i0] = FAUSTFLOAT(fTemp142);
			if ((iSlow188 | (iSlow192 | (iSlow194 | iSlow196)))) {
				fTemp143 = mydsp2_faustpower2_f(fTemp137);
			}
			if ((iSlow188 | iSlow192)) {
				fTemp144 = fTemp141 + fTemp143;
			}
			if ((iSlow188)) {
				fRec101[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow168 * std::sqrt(mydsp2_faustpower2_f(fTemp138 + 1.0f) + fTemp144)) + fConst8 * fRec101[1];
				fTemp145 = fSlow187 * fRec101[0];
			}
			output51[i0] = FAUSTFLOAT(fTemp145);
			if ((iSlow190)) {
				fRec102[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow169 * std::sqrt(mydsp2_faustpower2_f(fTemp137 + -1.0f) + fTemp139 + fTemp141)) + fConst8 * fRec102[1];
				fTemp146 = fSlow189 * fRec102[0];
			}
			output52[i0] = FAUSTFLOAT(fTemp146);
			if ((iSlow192)) {
				fRec103[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow170 * std::sqrt(fTemp144 + mydsp2_faustpower2_f(fTemp138 + -1.0f))) + fConst8 * fRec103[1];
				fTemp147 = fSlow191 * fRec103[0];
			}
			output53[i0] = FAUSTFLOAT(fTemp147);
			if ((iSlow194 | iSlow196)) {
				fTemp148 = fTemp139 + fTemp143;
			}
			if ((iSlow194)) {
				fRec104[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow171 * std::sqrt(fTemp148 + mydsp2_faustpower2_f(fTemp140 + 1.0f))) + fConst8 * fRec104[1];
				fTemp149 = fSlow193 * fRec104[0];
			}
			output54[i0] = FAUSTFLOAT(fTemp149);
			if ((iSlow196)) {
				fRec105[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow172 * std::sqrt(fTemp148 + mydsp2_faustpower2_f(fTemp140 + -1.0f))) + fConst8 * fRec105[1];
				fTemp150 = fSlow195 * fRec105[0];
			}
			output55[i0] = FAUSTFLOAT(fTemp150);
			if ((iSlow208 | (iSlow210 | (iSlow212 | (iSlow214 | (iSlow216 | iSlow218)))))) {
				fTemp151 = float(input9[i0]);
				fTemp152 = float(input10[i0]);
			}
			if ((iSlow208 | (iSlow212 | (iSlow216 | iSlow218)))) {
				fTemp153 = mydsp2_faustpower2_f(fTemp152);
			}
			if ((iSlow208 | (iSlow210 | (iSlow212 | (iSlow214 | (iSlow216 | iSlow218)))))) {
				fTemp154 = float(input11[i0]);
			}
			if ((iSlow208 | (iSlow210 | (iSlow212 | iSlow214)))) {
				fTemp155 = mydsp2_faustpower2_f(fTemp154);
			}
			if ((iSlow208)) {
				fRec106[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow151 * std::sqrt(mydsp2_faustpower2_f(fTemp151 + 1.0f) + fTemp153 + fTemp155)) + fConst8 * fRec106[1];
				fTemp156 = fSlow207 * fRec106[0];
			}
			output56[i0] = FAUSTFLOAT(fTemp156);
			if ((iSlow210 | (iSlow214 | (iSlow216 | iSlow218)))) {
				fTemp157 = mydsp2_faustpower2_f(fTemp151);
			}
			if ((iSlow210 | iSlow214)) {
				fTemp158 = fTemp155 + fTemp157;
			}
			if ((iSlow210)) {
				fRec107[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow168 * std::sqrt(mydsp2_faustpower2_f(fTemp152 + 1.0f) + fTemp158)) + fConst8 * fRec107[1];
				fTemp159 = fSlow209 * fRec107[0];
			}
			output57[i0] = FAUSTFLOAT(fTemp159);
			if ((iSlow212)) {
				fRec108[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow169 * std::sqrt(mydsp2_faustpower2_f(fTemp151 + -1.0f) + fTemp153 + fTemp155)) + fConst8 * fRec108[1];
				fTemp160 = fSlow211 * fRec108[0];
			}
			output58[i0] = FAUSTFLOAT(fTemp160);
			if ((iSlow214)) {
				fRec109[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow170 * std::sqrt(fTemp158 + mydsp2_faustpower2_f(fTemp152 + -1.0f))) + fConst8 * fRec109[1];
				fTemp161 = fSlow213 * fRec109[0];
			}
			output59[i0] = FAUSTFLOAT(fTemp161);
			if ((iSlow216 | iSlow218)) {
				fTemp162 = fTemp153 + fTemp157;
			}
			if ((iSlow216)) {
				fRec110[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow171 * std::sqrt(fTemp162 + mydsp2_faustpower2_f(fTemp154 + 1.0f))) + fConst8 * fRec110[1];
				fTemp163 = fSlow215 * fRec110[0];
			}
			output60[i0] = FAUSTFLOAT(fTemp163);
			if ((iSlow218)) {
				fRec111[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow172 * std::sqrt(fTemp162 + mydsp2_faustpower2_f(fTemp154 + -1.0f))) + fConst8 * fRec111[1];
				fTemp164 = fSlow217 * fRec111[0];
			}
			output61[i0] = FAUSTFLOAT(fTemp164);
			if ((iSlow220 | (iSlow222 | (iSlow224 | (iSlow226 | (iSlow228 | (iSlow230 | iSlow232))))))) {
				fTemp165 = float(input12[i0]);
			}
			if ((iSlow220 | (iSlow222 | (iSlow224 | (iSlow226 | (iSlow228 | (iSlow230 | iSlow234))))))) {
				fTemp166 = float(input13[i0]);
			}
			if ((iSlow220 | (iSlow224 | (iSlow228 | iSlow230)))) {
				fTemp167 = mydsp2_faustpower2_f(fTemp166);
			}
			if ((iSlow220 | (iSlow222 | (iSlow224 | (iSlow226 | (iSlow228 | (iSlow230 | iSlow236))))))) {
				fTemp168 = float(input14[i0]);
			}
			if ((iSlow220 | (iSlow222 | (iSlow224 | iSlow226)))) {
				fTemp169 = mydsp2_faustpower2_f(fTemp168);
			}
			if ((iSlow220)) {
				fRec112[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow151 * std::sqrt(mydsp2_faustpower2_f(fTemp165 + 1.0f) + fTemp167 + fTemp169)) + fConst8 * fRec112[1];
				fTemp170 = fSlow219 * fRec112[0];
			}
			output62[i0] = FAUSTFLOAT(fTemp170);
			if ((iSlow222 | (iSlow226 | (iSlow228 | iSlow230)))) {
				fTemp171 = mydsp2_faustpower2_f(fTemp165);
			}
			if ((iSlow222 | iSlow226)) {
				fTemp172 = fTemp169 + fTemp171;
			}
			if ((iSlow222)) {
				fRec113[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow168 * std::sqrt(mydsp2_faustpower2_f(fTemp166 + 1.0f) + fTemp172)) + fConst8 * fRec113[1];
				fTemp173 = fSlow221 * fRec113[0];
			}
			output63[i0] = FAUSTFLOAT(fTemp173);
			if ((iSlow224)) {
				fRec114[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow169 * std::sqrt(mydsp2_faustpower2_f(fTemp165 + -1.0f) + fTemp167 + fTemp169)) + fConst8 * fRec114[1];
				fTemp174 = fSlow223 * fRec114[0];
			}
			output64[i0] = FAUSTFLOAT(fTemp174);
			if ((iSlow226)) {
				fRec115[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow170 * std::sqrt(fTemp172 + mydsp2_faustpower2_f(fTemp166 + -1.0f))) + fConst8 * fRec115[1];
				fTemp175 = fSlow225 * fRec115[0];
			}
			output65[i0] = FAUSTFLOAT(fTemp175);
			if ((iSlow228 | iSlow230)) {
				fTemp176 = fTemp167 + fTemp171;
			}
			if ((iSlow228)) {
				fRec116[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow171 * std::sqrt(fTemp176 + mydsp2_faustpower2_f(fTemp168 + 1.0f))) + fConst8 * fRec116[1];
				fTemp177 = fSlow227 * fRec116[0];
			}
			output66[i0] = FAUSTFLOAT(fTemp177);
			if ((iSlow230)) {
				fRec117[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow172 * std::sqrt(fTemp176 + mydsp2_faustpower2_f(fTemp168 + -1.0f))) + fConst8 * fRec117[1];
				fTemp178 = fSlow229 * fRec117[0];
			}
			output67[i0] = FAUSTFLOAT(fTemp178);
			if ((iSlow240 | (iSlow242 | (iSlow244 | (iSlow246 | (iSlow238 | iSlow248)))))) {
				fTemp179 = float(input15[i0]);
				fTemp180 = float(input16[i0]);
			}
			if ((iSlow240 | (iSlow244 | (iSlow246 | iSlow238)))) {
				fTemp181 = mydsp2_faustpower2_f(fTemp180);
			}
			if ((iSlow240 | (iSlow242 | (iSlow244 | (iSlow246 | (iSlow238 | iSlow248)))))) {
				fTemp182 = float(input17[i0]);
			}
			if ((iSlow240 | (iSlow242 | (iSlow238 | iSlow248)))) {
				fTemp183 = mydsp2_faustpower2_f(fTemp182);
			}
			if ((iSlow238)) {
				fRec118[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow151 * std::sqrt(mydsp2_faustpower2_f(fTemp179 + 1.0f) + fTemp181 + fTemp183)) + fConst8 * fRec118[1];
				fTemp184 = fSlow237 * fRec118[0];
			}
			output68[i0] = FAUSTFLOAT(fTemp184);
			if ((iSlow242 | (iSlow244 | (iSlow246 | iSlow248)))) {
				fTemp185 = mydsp2_faustpower2_f(fTemp179);
			}
			if ((iSlow242 | iSlow248)) {
				fTemp186 = fTemp183 + fTemp185;
			}
			if ((iSlow248)) {
				fRec119[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow168 * std::sqrt(mydsp2_faustpower2_f(fTemp180 + 1.0f) + fTemp186)) + fConst8 * fRec119[1];
				fTemp187 = fSlow247 * fRec119[0];
			}
			output69[i0] = FAUSTFLOAT(fTemp187);
			if ((iSlow240)) {
				fRec120[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow169 * std::sqrt(mydsp2_faustpower2_f(fTemp179 + -1.0f) + fTemp181 + fTemp183)) + fConst8 * fRec120[1];
				fTemp188 = fSlow239 * fRec120[0];
			}
			output70[i0] = FAUSTFLOAT(fTemp188);
			if ((iSlow242)) {
				fRec121[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow170 * std::sqrt(fTemp186 + mydsp2_faustpower2_f(fTemp180 + -1.0f))) + fConst8 * fRec121[1];
				fTemp189 = fSlow241 * fRec121[0];
			}
			output71[i0] = FAUSTFLOAT(fTemp189);
			if ((iSlow244 | iSlow246)) {
				fTemp190 = fTemp181 + fTemp185;
			}
			if ((iSlow244)) {
				fRec122[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow171 * std::sqrt(fTemp190 + mydsp2_faustpower2_f(fTemp182 + 1.0f))) + fConst8 * fRec122[1];
				fTemp191 = fSlow243 * fRec122[0];
			}
			output72[i0] = FAUSTFLOAT(fTemp191);
			if ((iSlow246)) {
				fRec123[0] = fConst9 * std::max<float>(0.0f, 1.0f - fSlow172 * std::sqrt(fTemp190 + mydsp2_faustpower2_f(fTemp182 + -1.0f))) + fConst8 * fRec123[1];
				fTemp192 = fSlow245 * fRec123[0];
			}
			output73[i0] = FAUSTFLOAT(fTemp192);
			if ((iSlow37)) {
				fTemp193 = fSlow36 * std::min<float>(1.0f, std::max<float>(0.0f, 0.0f - 0.5f * (fTemp36 - (fTemp30 + 1.0f))));
			}
			output74[i0] = FAUSTFLOAT(fTemp193);
			if ((iSlow45)) {
				fTemp194 = fSlow44 * std::min<float>(1.0f, std::max<float>(0.0f, 0.0f - 0.5f * (fTemp38 - (fTemp32 + 1.0f))));
			}
			output75[i0] = FAUSTFLOAT(fTemp194);
			if ((iSlow52)) {
				fTemp195 = fSlow51 * std::min<float>(1.0f, std::max<float>(0.0f, 0.0f - 0.5f * (fTemp40 - (fTemp34 + 1.0f))));
			}
			output76[i0] = FAUSTFLOAT(fTemp195);
			if ((iSlow35)) {
				fTemp196 = fSlow34 * std::min<float>(1.0f, std::max<float>(0.0f, 1.0f - (fTemp30 + fTemp36)));
			}
			output77[i0] = FAUSTFLOAT(fTemp196);
			if ((iSlow47)) {
				fTemp197 = fSlow46 * std::min<float>(1.0f, std::max<float>(0.0f, 1.0f - (fTemp32 + fTemp38)));
			}
			output78[i0] = FAUSTFLOAT(fTemp197);
			if ((iSlow54)) {
				fTemp198 = fSlow53 * std::min<float>(1.0f, std::max<float>(0.0f, 1.0f - (fTemp34 + fTemp40)));
			}
			output79[i0] = FAUSTFLOAT(fTemp198);
			if ((iSlow198)) {
				fTemp199 = fSlow197 * std::min<float>(1.0f, 1.66666663f * std::max<float>(0.0f, 0.5f * (1.0f - fTemp137) + -0.200000003f));
			}
			output80[i0] = FAUSTFLOAT(fTemp199);
			if ((iSlow202)) {
				fTemp200 = fSlow201 * std::min<float>(1.0f, 1.66666663f * std::max<float>(0.0f, 0.5f * (1.0f - fTemp138) + -0.200000003f));
			}
			output81[i0] = FAUSTFLOAT(fTemp200);
			if ((iSlow200)) {
				fTemp201 = fSlow199 * fTemp137;
			}
			output82[i0] = FAUSTFLOAT(fTemp201);
			if ((iSlow204)) {
				fTemp202 = fSlow203 * fTemp138;
			}
			output83[i0] = FAUSTFLOAT(fTemp202);
			if ((iSlow206)) {
				fTemp203 = fSlow205 * fTemp140;
			}
			output84[i0] = FAUSTFLOAT(fTemp203);
			if ((iSlow232)) {
				fTemp204 = fSlow231 * fTemp165;
			}
			output85[i0] = FAUSTFLOAT(fTemp204);
			if ((iSlow234)) {
				fTemp205 = fSlow233 * fTemp166;
			}
			output86[i0] = FAUSTFLOAT(fTemp205);
			if ((iSlow236)) {
				fTemp206 = fSlow235 * fTemp168;
			}
			output87[i0] = FAUSTFLOAT(fTemp206);
			if ((iSlow163)) {
				fTemp207 = fSlow162 * fTemp109;
			}
			output88[i0] = FAUSTFLOAT(fTemp207);
			if ((iSlow165)) {
				fTemp208 = fSlow164 * fTemp110;
			}
			output89[i0] = FAUSTFLOAT(fTemp208);
			if ((iSlow167)) {
				fTemp209 = fSlow166 * fTemp112;
			}
			output90[i0] = FAUSTFLOAT(fTemp209);
			if ((iSlow126)) {
				fTemp210 = fSlow249 * std::min<float>(1.0f, fSlow118 * std::max<float>(0.0f, std::sqrt(fTemp105) - fSlow128));
			}
			output91[i0] = FAUSTFLOAT(fTemp210);
			if ((iSlow1)) {
				fVec0[1] = fVec0[0];
				fRec3[1] = fRec3[0];
				iVec1[1] = iVec1[0];
				iRec2[1] = iRec2[0];
				fRec4[1] = fRec4[0];
				iRec0[1] = iRec0[0];
			}
			if ((iSlow13)) {
				fVec2[1] = fVec2[0];
				fRec8[1] = fRec8[0];
				iVec3[1] = iVec3[0];
				iRec7[1] = iRec7[0];
				fRec9[1] = fRec9[0];
				iRec5[1] = iRec5[0];
			}
			if ((iSlow17)) {
				fVec4[1] = fVec4[0];
				fRec13[1] = fRec13[0];
				iVec5[1] = iVec5[0];
				iRec12[1] = iRec12[0];
				fRec14[1] = fRec14[0];
				iRec10[1] = iRec10[0];
			}
			if ((iSlow21)) {
				fVec6[1] = fVec6[0];
				fRec18[1] = fRec18[0];
				iVec7[1] = iVec7[0];
				iRec17[1] = iRec17[0];
				fRec19[1] = fRec19[0];
				iRec15[1] = iRec15[0];
			}
			if ((iSlow25)) {
				fVec8[1] = fVec8[0];
				fRec23[1] = fRec23[0];
				iVec9[1] = iVec9[0];
				iRec22[1] = iRec22[0];
				fRec24[1] = fRec24[0];
				iRec20[1] = iRec20[0];
			}
			if ((iSlow29)) {
				fVec10[1] = fVec10[0];
				fRec28[1] = fRec28[0];
				iVec11[1] = iVec11[0];
				iRec27[1] = iRec27[0];
				fRec29[1] = fRec29[0];
				iRec25[1] = iRec25[0];
			}
			if ((iSlow35 | (iSlow37 | iSlow33))) {
				fVec12[1] = fVec12[0];
				fRec30[1] = fRec30[0];
			}
			if ((iSlow45 | (iSlow47 | iSlow43))) {
				fVec13[1] = fVec13[0];
				fRec31[1] = fRec31[0];
			}
			if ((iSlow52 | (iSlow54 | iSlow50))) {
				fVec14[1] = fVec14[0];
				fRec32[1] = fRec32[0];
			}
			if ((iSlow35 | (iSlow37 | iSlow57))) {
				fVec15[1] = fVec15[0];
				fRec33[1] = fRec33[0];
			}
			if ((iSlow45 | (iSlow47 | iSlow60))) {
				fVec16[1] = fVec16[0];
				fRec34[1] = fRec34[0];
			}
			if ((iSlow52 | (iSlow54 | iSlow63))) {
				fVec17[1] = fVec17[0];
				fRec35[1] = fRec35[0];
			}
			if ((iSlow66)) {
				fVec18[1] = fVec18[0];
				fRec36[1] = fRec36[0];
			}
			if ((iSlow71)) {
				fVec19[1] = fVec19[0];
				fRec37[1] = fRec37[0];
			}
			if ((iSlow74)) {
				fVec20[1] = fVec20[0];
				fRec38[1] = fRec38[0];
			}
			if ((iSlow77)) {
				fVec21[1] = fVec21[0];
				fRec39[1] = fRec39[0];
			}
			if ((iSlow80)) {
				fVec22[1] = fVec22[0];
				fRec40[1] = fRec40[0];
			}
			if ((iSlow83)) {
				fVec23[1] = fVec23[0];
				fRec41[1] = fRec41[0];
			}
			if ((iSlow86 | (iSlow89 | (iSlow91 | iSlow93)))) {
				fVec24[1] = fVec24[0];
				fRec44[1] = fRec44[0];
			}
			if ((iSlow86)) {
				fRec43[1] = fRec43[0];
				fRec42[1] = fRec42[0];
			}
			if ((iSlow103 | (iSlow105 | (iSlow107 | iSlow93)))) {
				fVec25[1] = fVec25[0];
				fRec47[1] = fRec47[0];
			}
			if ((iSlow103)) {
				fRec46[1] = fRec46[0];
				fRec45[1] = fRec45[0];
			}
			if ((iSlow110 | (iSlow112 | (iSlow114 | iSlow93)))) {
				fVec26[1] = fVec26[0];
				fRec50[1] = fRec50[0];
			}
			if ((iSlow110)) {
				fRec49[1] = fRec49[0];
				fRec48[1] = fRec48[0];
			}
			if ((iSlow89)) {
				fRec52[1] = fRec52[0];
				fRec51[1] = fRec51[0];
			}
			if ((iSlow105)) {
				fRec54[1] = fRec54[0];
				fRec53[1] = fRec53[0];
			}
			if ((iSlow112)) {
				fRec56[1] = fRec56[0];
				fRec55[1] = fRec55[0];
			}
			if ((iSlow91)) {
				fRec58[1] = fRec58[0];
				fRec57[1] = fRec57[0];
			}
			if ((iSlow107)) {
				fRec60[1] = fRec60[0];
				fRec59[1] = fRec59[0];
			}
			if ((iSlow114)) {
				fRec62[1] = fRec62[0];
				fRec61[1] = fRec61[0];
			}
			if ((iSlow93)) {
				fRec64[1] = fRec64[0];
				fRec63[1] = fRec63[0];
			}
			if ((iSlow117 | (iSlow120 | (iSlow122 | (iSlow124 | iSlow126))))) {
				fRec67[1] = fRec67[0];
			}
			if ((iSlow117)) {
				fRec66[1] = fRec66[0];
				fRec65[1] = fRec65[0];
			}
			if ((iSlow136 | (iSlow138 | (iSlow140 | (iSlow124 | iSlow126))))) {
				fRec70[1] = fRec70[0];
			}
			if ((iSlow136)) {
				fRec69[1] = fRec69[0];
				fRec68[1] = fRec68[0];
			}
			if ((iSlow143 | (iSlow145 | (iSlow147 | iSlow124)))) {
				fRec73[1] = fRec73[0];
			}
			if ((iSlow143)) {
				fRec72[1] = fRec72[0];
				fRec71[1] = fRec71[0];
			}
			if ((iSlow120)) {
				fRec75[1] = fRec75[0];
				fRec74[1] = fRec74[0];
			}
			if ((iSlow138)) {
				fRec77[1] = fRec77[0];
				fRec76[1] = fRec76[0];
			}
			if ((iSlow145)) {
				fRec79[1] = fRec79[0];
				fRec78[1] = fRec78[0];
			}
			if ((iSlow122)) {
				fRec81[1] = fRec81[0];
				fRec80[1] = fRec80[0];
			}
			if ((iSlow140)) {
				fRec83[1] = fRec83[0];
				fRec82[1] = fRec82[0];
			}
			if ((iSlow147)) {
				fRec85[1] = fRec85[0];
				fRec84[1] = fRec84[0];
			}
			if ((iSlow124)) {
				fRec87[1] = fRec87[0];
				fRec86[1] = fRec86[0];
			}
			if ((iSlow150)) {
				fRec88[1] = fRec88[0];
			}
			if ((iSlow153)) {
				fRec89[1] = fRec89[0];
			}
			if ((iSlow155)) {
				fRec90[1] = fRec90[0];
			}
			if ((iSlow157)) {
				fRec91[1] = fRec91[0];
			}
			if ((iSlow159)) {
				fRec92[1] = fRec92[0];
			}
			if ((iSlow161)) {
				fRec93[1] = fRec93[0];
			}
			if ((iSlow174)) {
				fRec94[1] = fRec94[0];
			}
			if ((iSlow176)) {
				fRec95[1] = fRec95[0];
			}
			if ((iSlow178)) {
				fRec96[1] = fRec96[0];
			}
			if ((iSlow180)) {
				fRec97[1] = fRec97[0];
			}
			if ((iSlow182)) {
				fRec98[1] = fRec98[0];
			}
			if ((iSlow184)) {
				fRec99[1] = fRec99[0];
			}
			if ((iSlow186)) {
				fRec100[1] = fRec100[0];
			}
			if ((iSlow188)) {
				fRec101[1] = fRec101[0];
			}
			if ((iSlow190)) {
				fRec102[1] = fRec102[0];
			}
			if ((iSlow192)) {
				fRec103[1] = fRec103[0];
			}
			if ((iSlow194)) {
				fRec104[1] = fRec104[0];
			}
			if ((iSlow196)) {
				fRec105[1] = fRec105[0];
			}
			if ((iSlow208)) {
				fRec106[1] = fRec106[0];
			}
			if ((iSlow210)) {
				fRec107[1] = fRec107[0];
			}
			if ((iSlow212)) {
				fRec108[1] = fRec108[0];
			}
			if ((iSlow214)) {
				fRec109[1] = fRec109[0];
			}
			if ((iSlow216)) {
				fRec110[1] = fRec110[0];
			}
			if ((iSlow218)) {
				fRec111[1] = fRec111[0];
			}
			if ((iSlow220)) {
				fRec112[1] = fRec112[0];
			}
			if ((iSlow222)) {
				fRec113[1] = fRec113[0];
			}
			if ((iSlow224)) {
				fRec114[1] = fRec114[0];
			}
			if ((iSlow226)) {
				fRec115[1] = fRec115[0];
			}
			if ((iSlow228)) {
				fRec116[1] = fRec116[0];
			}
			if ((iSlow230)) {
				fRec117[1] = fRec117[0];
			}
			if ((iSlow238)) {
				fRec118[1] = fRec118[0];
			}
			if ((iSlow248)) {
				fRec119[1] = fRec119[0];
			}
			if ((iSlow240)) {
				fRec120[1] = fRec120[0];
			}
			if ((iSlow242)) {
				fRec121[1] = fRec121[0];
			}
			if ((iSlow244)) {
				fRec122[1] = fRec122[0];
			}
			if ((iSlow246)) {
				fRec123[1] = fRec123[0];
			}
		}
		iTempPerm0 = iTemp0;
		iTempPerm1 = iTemp1;
		iTempPerm2 = iTemp2;
		iTempPerm3 = iTemp3;
		fTempPerm4 = fTemp4;
		iTempPerm5 = iTemp5;
		iTempPerm6 = iTemp6;
		iTempPerm7 = iTemp7;
		iTempPerm8 = iTemp8;
		fTempPerm9 = fTemp9;
		iTempPerm10 = iTemp10;
		iTempPerm11 = iTemp11;
		iTempPerm12 = iTemp12;
		iTempPerm13 = iTemp13;
		fTempPerm14 = fTemp14;
		iTempPerm15 = iTemp15;
		iTempPerm16 = iTemp16;
		iTempPerm17 = iTemp17;
		iTempPerm18 = iTemp18;
		fTempPerm19 = fTemp19;
		iTempPerm20 = iTemp20;
		iTempPerm21 = iTemp21;
		iTempPerm22 = iTemp22;
		iTempPerm23 = iTemp23;
		fTempPerm24 = fTemp24;
		iTempPerm25 = iTemp25;
		iTempPerm26 = iTemp26;
		iTempPerm27 = iTemp27;
		iTempPerm28 = iTemp28;
		fTempPerm29 = fTemp29;
		fTempPerm30 = fTemp30;
		fTempPerm31 = fTemp31;
		fTempPerm32 = fTemp32;
		fTempPerm33 = fTemp33;
		fTempPerm34 = fTemp34;
		fTempPerm35 = fTemp35;
		fTempPerm36 = fTemp36;
		fTempPerm37 = fTemp37;
		fTempPerm38 = fTemp38;
		fTempPerm39 = fTemp39;
		fTempPerm40 = fTemp40;
		fTempPerm41 = fTemp41;
		fTempPerm42 = fTemp42;
		fTempPerm43 = fTemp43;
		fTempPerm44 = fTemp44;
		fTempPerm45 = fTemp45;
		fTempPerm46 = fTemp46;
		fTempPerm47 = fTemp47;
		fTempPerm48 = fTemp48;
		fTempPerm49 = fTemp49;
		fTempPerm50 = fTemp50;
		fTempPerm51 = fTemp51;
		fTempPerm52 = fTemp52;
		fTempPerm53 = fTemp53;
		fTempPerm54 = fTemp54;
		fTempPerm55 = fTemp55;
		fTempPerm56 = fTemp56;
		fTempPerm57 = fTemp57;
		fTempPerm58 = fTemp58;
		fTempPerm59 = fTemp59;
		fTempPerm60 = fTemp60;
		fTempPerm61 = fTemp61;
		fTempPerm62 = fTemp62;
		fTempPerm63 = fTemp63;
		fTempPerm64 = fTemp64;
		fTempPerm65 = fTemp65;
		fTempPerm66 = fTemp66;
		fTempPerm67 = fTemp67;
		fTempPerm68 = fTemp68;
		fTempPerm69 = fTemp69;
		fTempPerm70 = fTemp70;
		fTempPerm71 = fTemp71;
		fTempPerm72 = fTemp72;
		fTempPerm73 = fTemp73;
		fTempPerm74 = fTemp74;
		fTempPerm75 = fTemp75;
		fTempPerm76 = fTemp76;
		fTempPerm77 = fTemp77;
		fTempPerm78 = fTemp78;
		fTempPerm79 = fTemp79;
		fTempPerm80 = fTemp80;
		fTempPerm81 = fTemp81;
		fTempPerm82 = fTemp82;
		fTempPerm83 = fTemp83;
		fTempPerm84 = fTemp84;
		fTempPerm85 = fTemp85;
		fTempPerm86 = fTemp86;
		fTempPerm87 = fTemp87;
		fTempPerm88 = fTemp88;
		fTempPerm89 = fTemp89;
		fTempPerm90 = fTemp90;
		fTempPerm91 = fTemp91;
		fTempPerm92 = fTemp92;
		fTempPerm93 = fTemp93;
		fTempPerm94 = fTemp94;
		fTempPerm95 = fTemp95;
		fTempPerm96 = fTemp96;
		fTempPerm97 = fTemp97;
		fTempPerm98 = fTemp98;
		fTempPerm99 = fTemp99;
		fTempPerm100 = fTemp100;
		fTempPerm101 = fTemp101;
		fTempPerm102 = fTemp102;
		fTempPerm103 = fTemp103;
		fTempPerm104 = fTemp104;
		fTempPerm105 = fTemp105;
		fTempPerm106 = fTemp106;
		fTempPerm107 = fTemp107;
		fTempPerm108 = fTemp108;
		fTempPerm109 = fTemp109;
		fTempPerm110 = fTemp110;
		fTempPerm111 = fTemp111;
		fTempPerm112 = fTemp112;
		fTempPerm113 = fTemp113;
		fTempPerm114 = fTemp114;
		fTempPerm115 = fTemp115;
		fTempPerm116 = fTemp116;
		fTempPerm117 = fTemp117;
		fTempPerm118 = fTemp118;
		fTempPerm119 = fTemp119;
		fTempPerm120 = fTemp120;
		fTempPerm121 = fTemp121;
		fTempPerm122 = fTemp122;
		fTempPerm123 = fTemp123;
		fTempPerm124 = fTemp124;
		fTempPerm125 = fTemp125;
		fTempPerm126 = fTemp126;
		fTempPerm127 = fTemp127;
		fTempPerm128 = fTemp128;
		fTempPerm129 = fTemp129;
		fTempPerm130 = fTemp130;
		fTempPerm131 = fTemp131;
		fTempPerm132 = fTemp132;
		fTempPerm133 = fTemp133;
		fTempPerm134 = fTemp134;
		fTempPerm135 = fTemp135;
		fTempPerm136 = fTemp136;
		fTempPerm137 = fTemp137;
		fTempPerm138 = fTemp138;
		fTempPerm139 = fTemp139;
		fTempPerm140 = fTemp140;
		fTempPerm141 = fTemp141;
		fTempPerm142 = fTemp142;
		fTempPerm143 = fTemp143;
		fTempPerm144 = fTemp144;
		fTempPerm145 = fTemp145;
		fTempPerm146 = fTemp146;
		fTempPerm147 = fTemp147;
		fTempPerm148 = fTemp148;
		fTempPerm149 = fTemp149;
		fTempPerm150 = fTemp150;
		fTempPerm151 = fTemp151;
		fTempPerm152 = fTemp152;
		fTempPerm153 = fTemp153;
		fTempPerm154 = fTemp154;
		fTempPerm155 = fTemp155;
		fTempPerm156 = fTemp156;
		fTempPerm157 = fTemp157;
		fTempPerm158 = fTemp158;
		fTempPerm159 = fTemp159;
		fTempPerm160 = fTemp160;
		fTempPerm161 = fTemp161;
		fTempPerm162 = fTemp162;
		fTempPerm163 = fTemp163;
		fTempPerm164 = fTemp164;
		fTempPerm165 = fTemp165;
		fTempPerm166 = fTemp166;
		fTempPerm167 = fTemp167;
		fTempPerm168 = fTemp168;
		fTempPerm169 = fTemp169;
		fTempPerm170 = fTemp170;
		fTempPerm171 = fTemp171;
		fTempPerm172 = fTemp172;
		fTempPerm173 = fTemp173;
		fTempPerm174 = fTemp174;
		fTempPerm175 = fTemp175;
		fTempPerm176 = fTemp176;
		fTempPerm177 = fTemp177;
		fTempPerm178 = fTemp178;
		fTempPerm179 = fTemp179;
		fTempPerm180 = fTemp180;
		fTempPerm181 = fTemp181;
		fTempPerm182 = fTemp182;
		fTempPerm183 = fTemp183;
		fTempPerm184 = fTemp184;
		fTempPerm185 = fTemp185;
		fTempPerm186 = fTemp186;
		fTempPerm187 = fTemp187;
		fTempPerm188 = fTemp188;
		fTempPerm189 = fTemp189;
		fTempPerm190 = fTemp190;
		fTempPerm191 = fTemp191;
		fTempPerm192 = fTemp192;
		fTempPerm193 = fTemp193;
		fTempPerm194 = fTemp194;
		fTempPerm195 = fTemp195;
		fTempPerm196 = fTemp196;
		fTempPerm197 = fTemp197;
		fTempPerm198 = fTemp198;
		fTempPerm199 = fTemp199;
		fTempPerm200 = fTemp200;
		fTempPerm201 = fTemp201;
		fTempPerm202 = fTemp202;
		fTempPerm203 = fTemp203;
		fTempPerm204 = fTemp204;
		fTempPerm205 = fTemp205;
		fTempPerm206 = fTemp206;
		fTempPerm207 = fTemp207;
		fTempPerm208 = fTemp208;
		fTempPerm209 = fTemp209;
		fTempPerm210 = fTemp210;
	}

};

//**************************************************************
// Polyphony
//**************************************************************

/************************** BEGIN faust-poly-engine.h *******************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

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
#include <assert.h>

/************************** BEGIN audio.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

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

        /**
         * Init the DSP.
         * @param name - the DSP name to be given to the audio driven
         * (could appear as a JACK client for instance)
         * @param dsp - the dsp that will be initialized with the driver sample rate
         *
         * @return true is sucessful, false in case of driver failure.
         **/
        virtual bool init(const char* name, dsp* dsp) = 0;
    
        /**
         * Start audio processing.
         * @return true is sucessful, false if case of driver failure.
         **/
        virtual bool start() = 0;
    
        /**
         * Stop audio processing.
         **/
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
            for (const auto& it : fComputeCallbackList) {
                it.first(it.second);
            }
        }
    
        // Return buffer size in frames.
        virtual int getBufferSize() = 0;
    
        // Return the driver sample rate in Hz.
        virtual int getSampleRate() = 0;

        // Return the driver hardware inputs number.
        virtual int getNumInputs() = 0;
    
        // Return the driver hardware outputs number.
        virtual int getNumOutputs() = 0;
    
        /**
         * @return Returns the average proportion of available CPU
         * being spent inside the audio callbacks (between 0.0 and 1.0).
         **/
        virtual float getCPULoad() { return 0.f; }
};
					
#endif
/**************************  END  audio.h **************************/
/************************** BEGIN APIUI.h *****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

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
#include <stdio.h>
#include <map>


typedef unsigned int uint;

class APIUI : public PathBuilder, public Meta, public UI
{
    public:
        enum ItemType { kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph };
        enum Type { kAcc = 0, kGyr = 1, kNoType };

    protected:

        enum Mapping { kLin = 0, kLog = 1, kExp = 2 };

        struct Item {
            std::string fPath;
            std::string fLabel;
            ValueConverter* fConversion;
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fInit;
            FAUSTFLOAT fMin;
            FAUSTFLOAT fMax;
            FAUSTFLOAT fStep;
            ItemType fItemType;
        };
        std::vector<Item> fItems;

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

            // handle scale metadata
            ValueConverter* converter = nullptr;
            switch (fCurrentScale) {
                case kLin:
                    converter = new LinearValueConverter(0, 1, min, max);
                    break;
                case kLog:
                    converter = new LogValueConverter(0, 1, min, max);
                    break;
                case kExp:
                    converter = new ExpValueConverter(0, 1, min, max);
                    break;
            }
            fCurrentScale = kLin;

            fItems.push_back({path, label, converter, zone, init, min, max, step, type });
       
            if (fCurrentAcc.size() > 0 && fCurrentGyr.size() > 0) {
                fprintf(stderr, "warning : 'acc' and 'gyr' metadata used for the same %s parameter !!\n", label);
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
                    fprintf(stderr, "incorrect acc metadata : %s \n", fCurrentAcc.c_str());
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
                    fprintf(stderr, "incorrect gyr metadata : %s \n", fCurrentGyr.c_str());
                }
                fCurrentGyr = "";
            }

            // handle screencolor metadata "...[screencolor:red|green|blue|white]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == nullptr)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == nullptr)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == nullptr)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == nullptr) && (fGreenReader == nullptr) && (fBlueReader == nullptr)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    fprintf(stderr, "incorrect screencolor metadata : %s \n", fCurrentColor.c_str());
                }
            }
            fCurrentColor = "";

            fMetaData.push_back(fCurrentMetadata);
            fCurrentMetadata.clear();
        }

        int getZoneIndex(std::vector<ZoneControl*>* table, int p, int val)
        {
            FAUSTFLOAT* zone = fItems[uint(p)].fZone;
            for (size_t i = 0; i < table[val].size(); i++) {
                if (zone == table[val][i]->getZone()) return int(i);
            }
            return -1;
        }

        void setConverter(std::vector<ZoneControl*>* table, int p, int val, int curve, double amin, double amid, double amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);

            // Deactivates everywhere..
            if (id1 != -1) table[0][uint(id1)]->setActive(false);
            if (id2 != -1) table[1][uint(id2)]->setActive(false);
            if (id3 != -1) table[2][uint(id3)]->setActive(false);

            if (val == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getZoneIndex(table, p, val);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                  table[val][uint(id4)]->setMappingValues(curve, amin, amid, amax, fItems[uint(p)].fMin, fItems[uint(p)].fInit, fItems[uint(p)].fMax);
                  table[val][uint(id4)]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fItems[uint(p)].fZone;
                    table[val].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fItems[uint(p)].fMin, fItems[uint(p)].fInit, fItems[uint(p)].fMax));
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
                curve = table[val][uint(id1)]->getCurve();
                table[val][uint(id1)]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                val = 1;
                curve = table[val][uint(id2)]->getCurve();
                table[val][uint(id2)]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                val = 2;
                curve = table[val][uint(id3)]->getCurve();
                table[val][uint(id3)]->getMappingValues(amin, amid, amax);
            } else {
                val = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }

    public:

        APIUI() : fHasScreenControl(false), fRedReader(nullptr), fGreenReader(nullptr), fBlueReader(nullptr), fCurrentScale(kLin)
        {}

        virtual ~APIUI()
        {
            for (const auto& it : fItems) delete it.fConversion;
            for (int i = 0; i < 3; i++) {
                for (const auto& it : fAcc[i]) delete it;
                for (const auto& it : fGyr[i]) delete it;
            }
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }

        // -- widget's layouts

        virtual void openTabBox(const char* label) { pushLabel(label); }
        virtual void openHorizontalBox(const char* label) { pushLabel(label); }
        virtual void openVerticalBox(const char* label) { pushLabel(label); }
        virtual void closeBox() { popLabel(); }

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
            addParameter(label, zone, min, min, max, (max-min)/1000.0f, kHBargraph);
        }

        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0f, kVBargraph);
        }

        // -- soundfiles

        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            // Keep metadata
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
        int getParamsCount() { return int(fItems.size()); }

        int getParamIndex(const char* path)
        {
            auto it1 = find_if(fItems.begin(), fItems.end(), [=](const Item& it) { return it.fPath == std::string(path); });
            if (it1 != fItems.end()) {
                return int(it1 - fItems.begin());
            }

            auto it2 = find_if(fItems.begin(), fItems.end(), [=](const Item& it) { return it.fLabel == std::string(path); });
            if (it2 != fItems.end()) {
                return int(it2 - fItems.begin());
            }

            return -1;
        }
        const char* getParamAddress(int p) { return fItems[uint(p)].fPath.c_str(); }
        const char* getParamLabel(int p) { return fItems[uint(p)].fLabel.c_str(); }
        std::map<const char*, const char*> getMetadata(int p)
        {
            std::map<const char*, const char*> res;
            std::map<std::string, std::string> metadata = fMetaData[uint(p)];
            for (const auto& it : metadata) {
                res[it.first.c_str()] = it.second.c_str();
            }
            return res;
        }

        const char* getMetadata(int p, const char* key)
        {
            return (fMetaData[uint(p)].find(key) != fMetaData[uint(p)].end()) ? fMetaData[uint(p)][key].c_str() : "";
        }
        FAUSTFLOAT getParamMin(int p) { return fItems[uint(p)].fMin; }
        FAUSTFLOAT getParamMax(int p) { return fItems[uint(p)].fMax; }
        FAUSTFLOAT getParamStep(int p) { return fItems[uint(p)].fStep; }
        FAUSTFLOAT getParamInit(int p) { return fItems[uint(p)].fInit; }

        FAUSTFLOAT* getParamZone(int p) { return fItems[uint(p)].fZone; }

        FAUSTFLOAT getParamValue(int p) { return *fItems[uint(p)].fZone; }
        FAUSTFLOAT getParamValue(const char* path)
        {
            int index = getParamIndex(path);
            return (index >= 0) ? getParamValue(index) : FAUSTFLOAT(0);
        }

        void setParamValue(int p, FAUSTFLOAT v) { *fItems[uint(p)].fZone = v; }
        void setParamValue(const char* path, FAUSTFLOAT v)
        {
            int index = getParamIndex(path);
            if (index >= 0) {
                setParamValue(index, v);
            } else {
                fprintf(stderr, "setParamValue : '%s' not found\n", (path == nullptr ? "NULL" : path));
            }
        }

        double getParamRatio(int p) { return fItems[uint(p)].fConversion->faust2ui(*fItems[uint(p)].fZone); }
        void setParamRatio(int p, double r) { *fItems[uint(p)].fZone = FAUSTFLOAT(fItems[uint(p)].fConversion->ui2faust(r)); }

        double value2ratio(int p, double r)    { return fItems[uint(p)].fConversion->faust2ui(r); }
        double ratio2value(int p, double r)    { return fItems[uint(p)].fConversion->ui2faust(r); }

        /**
         * Return the control type (kAcc, kGyr, or -1) for a given parameter.
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
         * Return the Item type (kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph) for a given parameter.
         *
         * @param p - the UI parameter index
         *
         * @return the Item type
         */
        ItemType getParamItemType(int p)
        {
            return fItems[uint(p)].fItemType;
        }

        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant FAUSTFLOAT* zones.
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
         * Set a new value coming from an gyroscope, propagate it to all relevant FAUSTFLOAT* zones.
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

        /**
         * Get the number of FAUSTFLOAT* zones controlled with the accelerometer.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @return the number of zones
         *
         */
        int getAccCount(int acc)
        {
            return (acc >= 0 && acc < 3) ? int(fAcc[acc].size()) : 0;
        }

        /**
         * Get the number of FAUSTFLOAT* zones controlled with the gyroscope.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param the number of zones
         *
         */
        int getGyrCount(int gyr)
        {
            return (gyr >= 0 && gyr < 3) ? int(fGyr[gyr].size()) : 0;
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
/**************************  END  APIUI.h **************************/
/************************** BEGIN MidiUI.h ****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

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
#include <cstdlib>
#include <cmath>

/************************** BEGIN midi.h *******************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

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

/**
 * A timestamped short MIDI message used with SOUL.
 */

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/**
 * For timestamped MIDI messages.
 */
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

/**
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, keyOff, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 * MIDI channel is numbered in [0..15] in this layer.
 */
class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 0)
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
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
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
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
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
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/**
 * A class to decode NRPN and RPN messages, adapted from JUCE forum message:
 * https://forum.juce.com/t/14bit-midi-controller-support/11517
 */
class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};

/**
 * A pure interface for MIDI handlers that can send/receive MIDI messages to/from 'midi' objects.
 */
struct midi_interface {
    virtual void addMidiIn(midi* midi_dsp)      = 0;
    virtual void removeMidiIn(midi* midi_dsp)   = 0;
    virtual ~midi_interface() {}
};

/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/
class midi_handler : public midi, public midi_interface {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):midi_interface(), fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

#endif // __midi__
/**************************  END  midi.h **************************/

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/**
 * Helper code for MIDI meta and polyphonic 'nvoices' parsing.
 */
struct MidiMeta : public Meta, public std::map<std::string, std::string> {
    
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
    
    static void analyse(dsp* mono_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        mono_dsp->buildUserInterface(&jsonui);
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
        mono_dsp->metadata(&meta);
        bool found_voices = false;
        // If "options" metadata is used
        std::string options = meta.get("options", "");
        if (options != "") {
            std::map<std::string, std::string> metadata;
            std::string res;
            MetaDataUI::extractMetadata(options, res, metadata);
            if (metadata.find("nvoices") != metadata.end()) {
                nvoices = std::atoi(metadata["nvoices"].c_str());
                found_voices = true;
            }
        }
        // Otherwise test for "nvoices" metadata
        if (!found_voices) {
            std::string numVoices = meta.get("nvoices", "0");
            nvoices = std::atoi(numVoices.c_str());
        }
        nvoices = std::max<int>(0, nvoices);
    #endif
    }
    
    static bool checkPolyphony(dsp* mono_dsp)
    {
        MapUI map_ui;
        mono_dsp->buildUserInterface(&map_ui);
        bool has_freq = false;
        bool has_gate = false;
        bool has_gain = false;
        for (int i = 0; i < map_ui.getParamsCount(); i++) {
            std::string path = map_ui.getParamAddress(i);
            has_freq |= MapUI::endsWith(path, "/freq");
            has_gate |= MapUI::endsWith(path, "/gate");
            has_gain |= MapUI::endsWith(path, "/gain");
        }
        return (has_freq && has_gate && has_gain);
    }
    
};

/**
 * uiMidi : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrlChange, keyOn/keyOff, keyPress, progChange, chanPress, pitchWheel/pitchBend
 * start/stop/clock meta data is handled.
 * MIDI channel is numbered in [1..16] in this layer.
 * Channel 0 means "all channels" when receiving or sending.
 */
class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        bool inRange(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT v) { return (min <= v && v <= max); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = 0):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/**
 * Base class for MIDI aware UI items.
 */
class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/**
 * Base class for MIDI aware UI items with timestamp support.
 */
class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

/**
 * MIDI sync.
 */
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

class uiMidiStop : public uiMidiTimedItem {
  
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

class uiMidiClock : public uiMidiTimedItem {

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

/**
 * Standard MIDI events.
 */

/**
 * uiMidiProgChange uses the [min...max] range.
 */
class uiMidiProgChange : public uiMidiTimedItem {
    
    public:
    
        FAUSTFLOAT fMin, fMax;
    
        uiMidiProgChange(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fMin(min), fMax(max)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (inRange(fMin, fMax, v)) {
                if (fChan == 0) {
                    // Send on [0..15] channels on the MIDI layer
                    for (int chan = 0; chan < 16; chan++) {
                        fMidiOut->progChange(chan, v);
                    }
                } else {
                    fMidiOut->progChange(fChan - 1, v);
                }
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiItem::modifyZone(v);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiMidiTimedItem::modifyZone(date, v);
            }
        }
        
};

/**
 * uiMidiChanPress.
 */
class uiMidiChanPress : public uiMidiTimedItem, public uiConverter {
    
    public:
    
        uiMidiChanPress(midi* midi_out, GUI* ui,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min, FAUSTFLOAT max,
                        bool input = true,
                        MetaDataUI::Scale scale = MetaDataUI::kLin,
                        int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->chanPress(chan, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->chanPress(fChan - 1, fConverter->faust2ui(v));
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
        
};

/**
 * uiMidiCtrlChange does scale (kLin/kLog/kExp) mapping.
 */
class uiMidiCtrlChange : public uiMidiTimedItem, public uiConverter {
    
    private:
    
        int fCtrl;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fCtrl(ctrl)
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->ctrlChange(chan, fCtrl, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->ctrlChange(fChan - 1, fCtrl, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
};

class uiMidiPitchWheel : public uiMidiTimedItem {

    private:
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan)
        {
            if (min <= 0 && max >= 0) {
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min), 0., double(max));
            } else {
                // Degenerated case...
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min),double(min + (max - min)/FAUSTFLOAT(2)), double(max));
            }
        }
    
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->pitchWheel(chan, fConverter.faust2ui(v));
                }
            } else {
                fMidiOut->pitchWheel(fChan - 1, fConverter.faust2ui(v));
            }
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
                uiMidiTimedItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void setRange(int val)
        {
            double semi = (val / 128) + ((val % 128) / 100.);
            fConverter.setMappingValues(0., 8191., 16383., -semi, 0., semi);
        }
 
};

/**
 * uiMidiKeyOn does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyOn : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOn;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui,
                    FAUSTFLOAT* zone,
                    FAUSTFLOAT min, FAUSTFLOAT max,
                    bool input = true,
                    MetaDataUI::Scale scale = MetaDataUI::kLin,
                    int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOn(key)
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOn, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOn, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/**
 * uiMidiKeyOff does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyOff : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOff;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOff(key)
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOff, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOff, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/**
 * uiMidiKeyPress does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyPress : public uiMidiTimedItem, public uiConverter {

    private:
    
        int fKey;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui,
                       FAUSTFLOAT* zone,
                       FAUSTFLOAT min, FAUSTFLOAT max,
                       bool input = true,
                       MetaDataUI::Scale scale = MetaDataUI::kLin,
                       int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKey(key)
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKey, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKey, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrlChange, keyOn/keyOff, keyPress, progChange, chanPress, pitchWheel/pitchBend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi, public midi_interface, public MetaDataUI {

    // Add uiItem subclasses objects are deallocated by the inherited GUI class
    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::vector<uiMidiProgChange*>                  TProgChangeTable;
    typedef std::vector<uiMidiChanPress*>                   TChanPressTable;
    typedef std::map <int, std::vector<uiMidiKeyOn*> >      TKeyOnTable;
    typedef std::map <int, std::vector<uiMidiKeyOff*> >     TKeyOffTable;
    typedef std::map <int, std::vector<uiMidiKeyPress*> >   TKeyPressTable;
    typedef std::vector<uiMidiPitchWheel*>                  TPitchWheelTable;
    
    protected:
    
        TCtrlChangeTable fCtrlChangeTable;
        TProgChangeTable fProgChangeTable;
        TChanPressTable  fChanPressTable;
        TKeyOnTable      fKeyOnTable;
        TKeyOffTable     fKeyOffTable;
        TKeyOnTable      fKeyTable;
        TKeyPressTable   fKeyPressTable;
        TPitchWheelTable fPitchWheelTable;
        
        std::vector<uiMidiStart*> fStartTable;
        std::vector<uiMidiStop*>  fStopTable;
        std::vector<uiMidiClock*> fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    unsigned chan;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u %u", &num, &chan) == 2) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &chan) == 1) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input, chan));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "pgm") == 0) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &chan) == 1) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone), chan));
                        } else if ((fMetaAux[i].second == "chanpress")) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone)));
                        } else if ((gsscanf(fMetaAux[i].second.c_str(), "pitchwheel %u", &chan) == 1) || (gsscanf(fMetaAux[i].second.c_str(), "pitchbend %u", &chan) == 1)) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input, chan));
                        } else if ((fMetaAux[i].second == "pitchwheel") || (fMetaAux[i].second == "pitchbend")) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
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
    
        template <typename TABLE>
        void updateTable1(TABLE& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                // channel_aux == 0 means "all channels"
                if (channel_aux == 0 || channel == channel_aux - 1) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename TABLE>
        void updateTable2(TABLE& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    // channel_aux == 0 means "all channels"
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        if (fTimeStamp) {
                            table[val1][i]->modifyZone(date, FAUSTFLOAT(val2));
                        } else {
                            table[val1][i]->modifyZone(FAUSTFLOAT(val2));
                        }
                    }
                }
            }
        }
    
    public:
    
        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            // TODO: use shared_ptr based implementation
            fDelete = delete_handler;
            fTimeStamp = false;
        }
 
        virtual ~MidiUI() 
        {
            // Remove from fMidiHandler
            fMidiHandler->removeMidiIn(this);
            // TODO: use shared_ptr based implementation
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
            MetaDataUI::declare(zone, key, val);
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API
    
        void key(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyTable, date, channel, note, velocity);
        }
    
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyOnTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOn
            key(date, channel, note, velocity);
            return nullptr;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOffTable>(fKeyOffTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            key(date, channel, note, 0);
        }
        
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            updateTable2<TCtrlChangeTable>(fCtrlChangeTable, date, channel, ctrl, value);
        }
    
        void rpn(double date, int channel, int ctrl, int value)
        {
            if (ctrl == midi::PITCH_BEND_RANGE) {
                for (size_t i = 0; i < fPitchWheelTable.size(); i++) {
                    // channel_aux == 0 means "all channels"
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable1<TProgChangeTable>(fProgChangeTable, date, channel, pgm);
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            updateTable1<TPitchWheelTable>(fPitchWheelTable, date, channel, wheel);
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            updateTable2<TKeyPressTable>(fKeyPressTable, date, channel, pitch, press);
        }
        
        void chanPress(double date, int channel, int press)
        {
            updateTable1<TChanPressTable>(fChanPressTable, date, channel, press);
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (size_t i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (size_t i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (size_t i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/**************************  END  MidiUI.h **************************/
/************************** BEGIN poly-dsp.h *************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*********************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <float.h>
#include <assert.h>

/************************** BEGIN dsp-combiner.h **************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <string>
#include <assert.h>
#include <sstream>


// Base class and common code for binary combiners

enum Layout { kVerticalGroup, kHorizontalGroup, kTabGroup };

class dsp_binary_combiner : public dsp {

    protected:

        dsp* fDSP1;
        dsp* fDSP2;
        int fBufferSize;
        Layout fLayout;
        std::string fLabel;

        void buildUserInterfaceAux(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }

        FAUSTFLOAT** allocateChannels(int num)
        {
            FAUSTFLOAT** channels = new FAUSTFLOAT*[num];
            for (int chan = 0; chan < num; chan++) {
                channels[chan] = new FAUSTFLOAT[fBufferSize];
                memset(channels[chan], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            return channels;
        }

        void deleteChannels(FAUSTFLOAT** channels, int num)
        {
            for (int chan = 0; chan < num; chan++) {
                delete [] channels[chan];
            }
            delete [] channels;
        }

     public:

        dsp_binary_combiner(dsp* dsp1, dsp* dsp2, int buffer_size, Layout layout, const std::string& label)
        :fDSP1(dsp1), fDSP2(dsp2), fBufferSize(buffer_size), fLayout(layout), fLabel(label)
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
        virtual void init(int sample_rate)
        {
            fDSP1->init(sample_rate);
            fDSP2->init(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            fDSP1->instanceInit(sample_rate);
            fDSP2->instanceInit(sample_rate);
        }
        virtual void instanceConstants(int sample_rate)
        {
            fDSP1->instanceConstants(sample_rate);
            fDSP2->instanceConstants(sample_rate);
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

        FAUSTFLOAT** fDSP1Outputs;

    public:

        dsp_sequencer(dsp* dsp1, dsp* dsp2,
                      int buffer_size = 4096,
                      Layout layout = Layout::kTabGroup,
                      const std::string& label = "Sequencer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
        }

        virtual ~dsp_sequencer()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);
            fDSP2->compute(count, fDSP1Outputs, outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_parallelizer(dsp* dsp1, dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Parallelizer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fDSP2Outputs = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
        }

        virtual ~dsp_parallelizer()
        {
            delete [] fDSP2Inputs;
            delete [] fDSP2Outputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);

            // Shift inputs/outputs channels for fDSP2
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                fDSP2Inputs[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                fDSP2Outputs[chan] = outputs[fDSP1->getNumOutputs() + chan];
            }

            fDSP2->compute(count, fDSP2Inputs, fDSP2Outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two 'compatible' DSP in splitter

class dsp_splitter : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

    public:

        dsp_splitter(dsp* dsp1, dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Splitter")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_splitter()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_splitter(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);

            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                 fDSP2Inputs[chan] = fDSP1Outputs[chan % fDSP1->getNumOutputs()];
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in merger

class dsp_merger : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

        void mix(int count, FAUSTFLOAT* dst, FAUSTFLOAT* src)
        {
            for (int frame = 0; frame < count; frame++) {
                dst[frame] += src[frame];
            }
        }

    public:

        dsp_merger(dsp* dsp1, dsp* dsp2,
                   int buffer_size = 4096,
                   Layout layout = Layout::kTabGroup,
                   const std::string& label = "Merger")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_merger()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_merger(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, fDSP1Inputs, fDSP1Outputs);

            memset(fDSP2Inputs, 0, sizeof(FAUSTFLOAT*) * fDSP2->getNumInputs());

            for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                int mchan = chan % fDSP2->getNumInputs();
                if (fDSP2Inputs[mchan]) {
                    mix(count, fDSP2Inputs[mchan], fDSP1Outputs[chan]);
                } else {
                    fDSP2Inputs[mchan] = fDSP1Outputs[chan];
                }
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in a recursive way

class dsp_recursiver : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_recursiver(dsp* dsp1, dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Recursiver")
        :dsp_binary_combiner(dsp1, dsp2, 1, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = allocateChannels(fDSP2->getNumInputs());
            fDSP2Outputs = allocateChannels(fDSP2->getNumOutputs());
        }

        virtual ~dsp_recursiver()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            deleteChannels(fDSP2Inputs, fDSP2->getNumInputs());
            deleteChannels(fDSP2Outputs, fDSP2->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() - fDSP2->getNumOutputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual dsp* clone()
        {
            return new dsp_recursiver(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int frame = 0; (frame < count); frame++) {

                for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan][0] = fDSP2Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP1->getNumInputs() - fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan + fDSP2->getNumOutputs()][0] = inputs[chan][frame];
                }

                fDSP1->compute(1, fDSP1Inputs, fDSP1Outputs);

                for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                    outputs[chan][frame] = fDSP1Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                    fDSP2Inputs[chan][0] = fDSP1Outputs[chan][0];
                }

                fDSP2->compute(1, fDSP2Inputs, fDSP2Outputs);
            }
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

/*
 Crossfade between two DSP.
 When fCrossfade = 1, the first DSP only is computed, when fCrossfade = 0,
 the second DSP only is computed, otherwise both DSPs are computed and mixed.
*/

class dsp_crossfader: public dsp_binary_combiner {

    private:
    
        FAUSTFLOAT fCrossfade;
        FAUSTFLOAT** fDSPOutputs1;
        FAUSTFLOAT** fDSPOutputs2;
    
    public:
    
        dsp_crossfader(dsp* dsp1, dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Crossfade")
        :dsp_binary_combiner(dsp1, dsp2, 4096, layout, label),fCrossfade(FAUSTFLOAT(0.5))
        {
            fDSPOutputs1 = allocateChannels(fDSP1->getNumOutputs());
            fDSPOutputs2 = allocateChannels(fDSP1->getNumOutputs());
        }
    
        virtual ~dsp_crossfader()
        {
            deleteChannels(fDSPOutputs1, fDSP1->getNumInputs());
            deleteChannels(fDSPOutputs2, fDSP1->getNumOutputs());
        }
    
        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        void buildUserInterface(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("Crossfade");
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }
    
        virtual dsp* clone()
        {
            return new dsp_crossfader(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (fCrossfade == FAUSTFLOAT(1)) {
                fDSP1->compute(count, inputs, outputs);
            } else if (fCrossfade == FAUSTFLOAT(0)) {
                fDSP2->compute(count, inputs, outputs);
            } else {
                // Compute each effect
                fDSP1->compute(count, inputs, fDSPOutputs1);
                fDSP2->compute(count, inputs, fDSPOutputs2);
                // Mix between the two effects
                FAUSTFLOAT gain1 = fCrossfade;
                FAUSTFLOAT gain2 = FAUSTFLOAT(1) - gain1;
                for (int frame = 0; (frame < count); frame++) {
                    for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                        outputs[chan][frame] = fDSPOutputs1[chan][frame] * gain1 + fDSPOutputs2[chan][frame] * gain2;
                    }
                }
            }
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

#ifndef __dsp_algebra_api__
#define __dsp_algebra_api__

// DSP algebra API
/*
 Each operation takes two DSP and a optional Layout and Label parameters, returns the combined DSPs, or null if failure with an error message.
 */

static dsp* createDSPSequencer(dsp* dsp1, dsp* dsp2,
                               std::string& error,
                               Layout layout = Layout::kTabGroup,
                               const std::string& label = "Sequencer")
{
    if (dsp1->getNumOutputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_sequencer : the number of outputs ("
                  << dsp1->getNumOutputs() << ") of A "
                  << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    }
}

static dsp* createDSPParallelizer(dsp* dsp1, dsp* dsp2,
                                  std::string& error,
                                  Layout layout = Layout::kTabGroup,
                                  const std::string& label = "Parallelizer")
{
    return new dsp_parallelizer(dsp1, dsp2, 4096, layout, label);
}

static dsp* createDSPSplitter(dsp* dsp1, dsp* dsp2, std::string& error, Layout layout = Layout::kTabGroup, const std::string& label = "Splitter")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_splitter : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_splitter : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() % dsp1->getNumOutputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_splitter : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a divisor of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_splitter(dsp1, dsp2, 4096, layout, label);
    }
}

static dsp* createDSPMerger(dsp* dsp1, dsp* dsp2,
                            std::string& error,
                            Layout layout = Layout::kTabGroup,
                            const std::string& label = "Merger")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_merger : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_merger : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp1->getNumOutputs() % dsp2->getNumInputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_merger : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a multiple of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_merger(dsp1, dsp2, 4096, layout, label);
    }
}

static dsp* createDSPRecursiver(dsp* dsp1, dsp* dsp2,
                                std::string& error,
                                Layout layout = Layout::kTabGroup,
                                const std::string& label = "Recursiver")
{
    if ((dsp2->getNumInputs() > dsp1->getNumOutputs()) || (dsp2->getNumOutputs() > dsp1->getNumInputs())) {
        std::stringstream error_aux;
        error_aux << "Connection error in : dsp_recursiver" << std::endl;
        if (dsp2->getNumInputs() > dsp1->getNumOutputs()) {
            error_aux << "The number of outputs " << dsp1->getNumOutputs()
                      << " of the first expression should be greater or equal to the number of inputs ("
                      << dsp2->getNumInputs()
                      << ") of the second expression" << std::endl;
        }
        if (dsp2->getNumOutputs() > dsp1->getNumInputs()) {
            error_aux << "The number of inputs " << dsp1->getNumInputs()
                      << " of the first expression should be greater or equal to the number of outputs ("
                      << dsp2->getNumOutputs()
                      << ") of the second expression" << std::endl;
        }
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_recursiver(dsp1, dsp2, layout, label);
    }
}

static dsp* createDSPCrossfader(dsp* dsp1, dsp* dsp2,
                                 std::string& error,
                                 Layout layout = Layout::kTabGroup,
                                 const std::string& label = "Crossfade")
{
    if (dsp1->getNumInputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_crossfader : the number of inputs ("
        << dsp1->getNumInputs() << ") of A "
        << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp1->getNumOutputs() != dsp2->getNumOutputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_crossfader : the number of outputs ("
        << dsp1->getNumOutputs() << ") of A "
        << "must be equal to the number of outputs (" << dsp2->getNumOutputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_crossfader(dsp1, dsp2, layout, label);
    }
}

#endif

#endif
/************************** END dsp-combiner.h **************************/
/************************** BEGIN proxy-dsp.h ***************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>


/**
 * Proxy dsp definition created from the DSP JSON description.
 * This class allows a 'proxy' dsp to control a real dsp
 * possibly running somewhere else.
 */
class proxy_dsp : public dsp {

    protected:
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
        }
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
          
        proxy_dsp(dsp* dsp)
        {
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            fSampleRate = dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
    
        virtual int getNumInputs() { return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy dsp 
        virtual void init(int sample_rate)
        {
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int sample_rate) { fSampleRate = sample_rate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif
/************************** END proxy-dsp.h **************************/

/************************** BEGIN DecoratorUI.h **************************
 FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*************************************************************************/

#ifndef Decorator_UI_H
#define Decorator_UI_H


//----------------------------------------------------------------
//  Generic UI empty implementation
//----------------------------------------------------------------

class GenericUI : public UI
{
    
    public:
        
        GenericUI() {}
        virtual ~GenericUI() {}
        
        // -- widget's layouts
        virtual void openTabBox(const char* label) {}
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
        virtual void addSoundfile(const char* label, const char* soundpath, Soundfile** sf_zone) {}
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
    
};

//----------------------------------------------------------------
//  Generic UI decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    
    protected:
        
        UI* fUI;
        
    public:
        
        DecoratorUI(UI* ui = 0):fUI(ui) {}
        virtual ~DecoratorUI() { delete fUI; }
        
        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addNumEntry(label, zone, init, min, max, step); }
        
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addVerticalBargraph(label, zone, min, max); }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) { fUI->addSoundfile(label, filename, sf_zone); }
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }
    
};

// Defined here to simplify header #include inclusion 
class SoundUIInterface : public GenericUI {};

#endif
/**************************  END  DecoratorUI.h **************************/
/************************** BEGIN JSONControl.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef __JSON_CONTROL__
#define __JSON_CONTROL__

#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct JSONControl {
    
    virtual std::string getJSON() { return ""; }

    virtual void setParamValue(const std::string& path, FAUSTFLOAT value) {}

    virtual FAUSTFLOAT getParamValue(const std::string& path) { return 0; }
    
    virtual ~JSONControl()
    {}
    
};

#endif
/**************************  END  JSONControl.h **************************/

#define kActiveVoice    0
#define kFreeVoice     -1
#define kReleaseVoice  -2
#define kLegatoVoice   -3
#define kNoVoice       -4

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

/**
 * Allows to control zones in a grouped manner.
 */
class GroupUI : public GUI, public PathBuilder {

    private:

        std::map<std::string, uiGroupItem*> fLabelZoneMap;

        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            if (!MapUI::endsWith(label, "/gate")
                && !MapUI::endsWith(label, "/freq")
                && !MapUI::endsWith(label, "/key")
                && !MapUI::endsWith(label, "/gain")
                && !MapUI::endsWith(label, "/vel")
                && !MapUI::endsWith(label, "/velocity")) {

                // Groups all controllers except 'freq/key', 'gate', and 'gain/vel|velocity'
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
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
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
    
    typedef std::function<double(int)> TransformFunction;
  
    static double midiToFreq(double note)
    {
        return 440.0 * std::pow(2.0, (note-69.0)/12.0);
    }
    
    int fCurNote;                       // Playing note pitch
    int fNextNote;                      // In kLegatoVoice state, next note to play
    int fNextVel;                       // In kLegatoVoice state, next velocity to play
    int fDate;                          // KeyOn date
    int fRelease;                       // Current number of samples used in release mode to detect end of note
    FAUSTFLOAT fLevel;                  // Last audio block level
    double fReleaseLengthSec;           // Maximum release length in seconds (estimated time to silence after note release)
    std::vector<std::string> fGatePath; // Paths of 'gate' control
    std::vector<std::string> fGainPath; // Paths of 'gain/vel|velocity' control
    std::vector<std::string> fFreqPath; // Paths of 'freq/key' control
    TransformFunction        fKeyFun;   // MIDI key to freq conversion function
    TransformFunction        fVelFun;   // MIDI velocity to gain conversion function
    
    FAUSTFLOAT** fInputsSlice;
    FAUSTFLOAT** fOutputsSlice;
 
    dsp_voice(dsp* dsp):decorator_dsp(dsp)
    {
        // Default versions
        fVelFun = [](int velocity) { return double(velocity)/127.0; };
        fKeyFun = [](int pitch) { return midiToFreq(pitch); };
        dsp->buildUserInterface(this);
        fCurNote = kFreeVoice;
        fNextNote = fNextVel = -1;
        fLevel = FAUSTFLOAT(0);
        fDate = fRelease = 0;
        fReleaseLengthSec = 0.5;  // A half second is a reasonable default maximum release length.
        extractPaths(fGatePath, fFreqPath, fGainPath);
    }
    virtual ~dsp_voice()
    {}
    
    void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        FAUSTFLOAT** inputsSlice = static_cast<FAUSTFLOAT**>(alloca(sizeof(FAUSTFLOAT*) * getNumInputs()));
        for (int chan = 0; chan < getNumInputs(); chan++) {
            inputsSlice[chan] = &(inputs[chan][offset]);
        }
        FAUSTFLOAT** outputsSlice = static_cast<FAUSTFLOAT**>(alloca(sizeof(FAUSTFLOAT*) * getNumOutputs()));
        for (int chan = 0; chan < getNumOutputs(); chan++) {
            outputsSlice[chan] = &(outputs[chan][offset]);
        }
        compute(slice, inputsSlice, outputsSlice);
    }
    
    void computeLegato(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        int slice = count/2;
        
        // Reset envelops
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        // Compute current voice on half buffer
        computeSlice(0, slice, inputs, outputs);
         
        // Start next keyOn
        keyOn(fNextNote, fNextVel);
        
        // Compute on second half buffer
        computeSlice(slice, slice, inputs, outputs);
    }

    void extractPaths(std::vector<std::string>& gate, std::vector<std::string>& freq, std::vector<std::string>& gain)
    {
        // Keep gain/vel|velocity, freq/key and gate labels
        for (const auto& it : getMap()) {
            std::string path = it.first;
            if (endsWith(path, "/gate")) {
                gate.push_back(path);
            } else if (endsWith(path, "/freq")) {
                fKeyFun = [](int pitch) { return midiToFreq(pitch); };
                freq.push_back(path);
            } else if (endsWith(path, "/key")) {
                fKeyFun = [](int pitch) { return pitch; };
                freq.push_back(path);
            } else if (endsWith(path, "/gain")) {
                fVelFun = [](int velocity) { return double(velocity)/127.0; };
                gain.push_back(path);
            } else if (endsWith(path, "/vel") || endsWith(path, "/velocity")) {
                fVelFun = [](int velocity) { return double(velocity); };
                gain.push_back(path);
            }
        }
    }
    
    void reset()
    {
        init(getSampleRate());
    }
 
    void instanceClear()
    {
        decorator_dsp::instanceClear();
        fCurNote = kFreeVoice;
        fNextNote = fNextVel = -1;
        fLevel = FAUSTFLOAT(0);
        fDate = fRelease = 0;
    }
    
    // Keep 'pitch' and 'velocity' to fadeOut the current voice and start next one in the next buffer
    void keyOn(int pitch, int velocity, bool legato = false)
    {
        if (legato) {
            fNextNote = pitch;
            fNextVel = velocity;
        } else {
            keyOn(pitch, fVelFun(velocity));
        }
    }

    // Normalized MIDI velocity [0..1]
    void keyOn(int pitch, double velocity)
    {
        for (size_t i = 0; i < fFreqPath.size(); i++) {
            setParamValue(fFreqPath[i], fKeyFun(pitch));
        }
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(1));
        }
        for (size_t i = 0; i < fGainPath.size(); i++) {
            setParamValue(fGainPath[i], velocity);
        }
        
        fCurNote = pitch;
    }

    void keyOff(bool hard = false)
    {
        // No use of velocity for now...
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        if (hard) {
            // Immediately stop voice
            fCurNote = kFreeVoice;
        } else {
            // Release voice
            fRelease = fReleaseLengthSec * fDSP->getSampleRate();
            fCurNote = kReleaseVoice;
        }
    }
 
    // Change the voice release
    void setReleaseLength(double sec)
    {
        fReleaseLengthSec = sec;
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
    
    void instanceResetUserInterface()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->instanceResetUserInterface();
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
            if (!fGroupControl || dynamic_cast<SoundUIInterface*>(ui_interface)) {
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
 * Base class for MIDI controllable polyphonic DSP.
 */
#ifdef EMCC
#endif

class dsp_poly : public decorator_dsp, public midi, public JSONControl {

    protected:
    
    #ifdef EMCC
        MapUI fMapUI;
        std::string fJSON;
        midi_handler fMidiHandler;
        MidiUI fMIDIUI;
    #endif
    
    public:
    
    #ifdef EMCC
        dsp_poly(dsp* dsp):decorator_dsp(dsp), fMIDIUI(&fMidiHandler)
        {
            JSONUI jsonui(getNumInputs(), getNumOutputs());
            buildUserInterface(&jsonui);
            fJSON = jsonui.JSON(true);
            buildUserInterface(&fMapUI);
            buildUserInterface(&fMIDIUI);
        }
    #else
        dsp_poly(dsp* dsp):decorator_dsp(dsp)
        {}
    #endif
    
        virtual ~dsp_poly() {}
    
        // Reimplemented for EMCC
    #ifdef EMCC
        virtual int getNumInputs() { return decorator_dsp::getNumInputs(); }
        virtual int getNumOutputs() { return decorator_dsp::getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { decorator_dsp::buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return decorator_dsp::getSampleRate(); }
        virtual void init(int sample_rate) { decorator_dsp::init(sample_rate); }
        virtual void instanceInit(int sample_rate) { decorator_dsp::instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { decorator_dsp::instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { decorator_dsp::instanceResetUserInterface(); }
        virtual void instanceClear() { decorator_dsp::instanceClear(); }
        virtual dsp_poly* clone() { return new dsp_poly(fDSP->clone()); }
        virtual void metadata(Meta* m) { decorator_dsp::metadata(m); }
    
        // Additional API
        std::string getJSON()
        {
            return fJSON;
        }
    
        virtual void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            fMapUI.setParamValue(path, value);
            GUI::updateAllGuis();
        }
        
        virtual FAUSTFLOAT getParamValue(const std::string& path) { return fMapUI.getParamValue(path); }

        virtual void computeJS(int count, uintptr_t inputs, uintptr_t outputs)
        {
            decorator_dsp::compute(count, reinterpret_cast<FAUSTFLOAT**>(inputs),reinterpret_cast<FAUSTFLOAT**>(outputs));
        }
    #endif
    
        virtual MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return midi::keyOn(channel, pitch, velocity);
        }
        virtual void keyOff(int channel, int pitch, int velocity)
        {
            midi::keyOff(channel, pitch, velocity);
        }
        virtual void keyPress(int channel, int pitch, int press)
        {
            midi::keyPress(channel, pitch, press);
        }
        virtual void chanPress(int channel, int press)
        {
            midi::chanPress(channel, press);
        }
        virtual void ctrlChange(int channel, int ctrl, int value)
        {
            midi::ctrlChange(channel, ctrl, value);
        }
        virtual void ctrlChange14bits(int channel, int ctrl, int value)
        {
            midi::ctrlChange14bits(channel, ctrl, value);
        }
        virtual void pitchWheel(int channel, int wheel)
        {
        #ifdef EMCC
            fMIDIUI.pitchWheel(0., channel, wheel);
            GUI::updateAllGuis();
        #else
            midi::pitchWheel(channel, wheel);
        #endif
        }
        virtual void progChange(int channel, int pgm)
        {
            midi::progChange(channel, pgm);
        }
    
        // Change the voice release
        virtual void setReleaseLength(double seconds)
        {}
    
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
        FAUSTFLOAT** fOutBuffer;
        midi_interface* fMidiHandler; // The midi_interface the DSP is connected to
        int fDate;
    
        void fadeOut(int count, FAUSTFLOAT** outBuffer)
        {
            // FadeOut on half buffer
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                double factor = 1., step = 1./double(count);
                for (int frame = 0; frame < count; frame++) {
                    outBuffer[chan][frame] *= factor;
                    factor -= step;
                }
            }
        }
    
        FAUSTFLOAT mixCheckVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            FAUSTFLOAT level = 0;
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    level = std::max<FAUSTFLOAT>(level, (FAUSTFLOAT)fabs(mixChannel[frame]));
                    outChannel[frame] += mixChannel[frame];
                }
            }
            return level;
        }
    
        void mixVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    outChannel[frame] += mixChannel[frame];
                }
            }
        }
    
        void copy(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memcpy(outBuffer[chan], mixBuffer[chan], count * sizeof(FAUSTFLOAT));
            }
        }

        void clear(int count, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memset(outBuffer[chan], 0, count * sizeof(FAUSTFLOAT));
            }
        }
    
        int getPlayingVoice(int pitch)
        {
            int voice_playing = kNoVoice;
            int oldest_date_playing = INT_MAX;
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == pitch) {
                    // Keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
            
            return voice_playing;
        }
    
        int allocVoice(int voice, int type)
        {
            fVoiceTable[voice]->fDate++;
            fVoiceTable[voice]->fCurNote = type;
            return voice;
        }
    
        // Always returns a voice
        int getFreeVoice()
        {
            // Looks for the first available voice
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == kFreeVoice) {
                    return allocVoice(i, kActiveVoice);
                }
            }

            // Otherwise steal one
            int voice_release = kNoVoice;
            int voice_playing = kNoVoice;
            int oldest_date_release = INT_MAX;
            int oldest_date_playing = INT_MAX;

            // Scan all voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == kReleaseVoice) {
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
                fprintf(stderr, "Steal release voice : voice_date = %d cur_date = %d voice = %d \n",
                        fVoiceTable[voice_release]->fDate,
                        fDate,
                        voice_release);
                return allocVoice(voice_release, kLegatoVoice);
            } else if (oldest_date_playing != INT_MAX) {
                fprintf(stderr, "Steal playing voice : voice_date = %d cur_date = %d voice = %d \n",
                        fVoiceTable[voice_playing]->fDate,
                        fDate,
                        voice_release);
                return allocVoice(voice_playing, kLegatoVoice);
            } else {
                assert(false);
                return kNoVoice;
            }
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
                fprintf(stderr, "DSP is not polyphonic...\n");
                return false;
            }
        }

    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be used for one voice. Beware: mydsp2_poly will use and finally delete the pointer.
         * @param nvoices - number of polyphony voices, should be at least 1
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
         *                If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *
         */
        mydsp2_poly(dsp* dsp,
                   int nvoices,
                   bool control = false,
                   bool group = true)
        : dsp_voice_group(panic, this, control, group), dsp_poly(dsp) // dsp parameter is deallocated by ~dsp_poly
        {
            fDate = 0;
            fMidiHandler = nullptr;

            // Create voices
            assert(nvoices > 0);
            for (int i = 0; i < nvoices; i++) {
                addVoice(new dsp_voice(dsp->clone()));
            }

            // Init audio output buffers
            fMixBuffer = new FAUSTFLOAT*[getNumOutputs()];
            fOutBuffer = new FAUSTFLOAT*[getNumOutputs()];
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                fMixBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
                fOutBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }

            dsp_voice_group::init();
        }

        virtual ~mydsp2_poly()
        {
            // Remove from fMidiHandler
            if (fMidiHandler) fMidiHandler->removeMidiIn(this);
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                delete[] fMixBuffer[chan];
                delete[] fOutBuffer[chan];
            }
            delete[] fMixBuffer;
            delete[] fOutBuffer;
            
        }

        // DSP API
        void buildUserInterface(UI* ui_interface)
        {
            // MidiUI ui_interface contains the midi_handler connected to the MIDI driver
            if (dynamic_cast<midi_interface*>(ui_interface)) {
                fMidiHandler = dynamic_cast<midi_interface*>(ui_interface);
                fMidiHandler->addMidiIn(this);
            }
            dsp_voice_group::buildUserInterface(ui_interface);
        }

        void init(int sample_rate)
        {
            decorator_dsp::init(sample_rate);
            fVoiceGroup->init(sample_rate);
            fPanic = FAUSTFLOAT(0);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate)
        {
            decorator_dsp::instanceConstants(sample_rate);
            fVoiceGroup->instanceConstants(sample_rate);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceConstants(sample_rate);
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

            // First clear the intermediate fOutBuffer
            clear(count, fOutBuffer);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fCurNote == kLegatoVoice) {
                        // Play from current note and next note
                        voice->computeLegato(count, inputs, fMixBuffer);
                        // FadeOut on first half buffer
                        fadeOut(count/2, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                    } else if (voice->fCurNote != kFreeVoice) {
                        // Compute current note
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                        // Check the level to possibly set the voice in kFreeVoice again
                        voice->fRelease -= count;
                        if ((voice->fCurNote == kReleaseVoice)
                            && (voice->fRelease < 0)
                            && (voice->fLevel < VOICE_STOP_LEVEL)) {
                            voice->fCurNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, fOutBuffer);
                }
            }
            
            // Finally copy intermediate buffer to outputs
            copy(count, fOutBuffer, outputs);
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
            auto it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                dsp_voice* voice = *it;
                voice->keyOff();
                voice->reset();
            } else {
                fprintf(stderr, "Voice not found\n");
            }
        }

        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getFreeVoice();
                fVoiceTable[voice]->keyOn(pitch, velocity, fVoiceTable[voice]->fCurNote == kLegatoVoice);
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
                    fprintf(stderr, "Playing pitch = %d not found\n", pitch);
                }
            }
        }

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

        // Change the voice release
        void setReleaseLength(double seconds)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->setReleaseLength(seconds);
            }
        }

};

/**
 * Polyphonic DSP with an integrated effect.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
    
        // fPolyDSP will respond to MIDI messages.
        dsp_poly* fPolyDSP;
        
    public:
        
        dsp_poly_effect(dsp_poly* voice, dsp* combined)
        :dsp_poly(combined), fPolyDSP(voice)
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
    
        // Change the voice release
        void setReleaseLength(double sec)
        {
            fPolyDSP->setReleaseLength(sec);
        }
    
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */
struct dsp_poly_factory : public dsp_factory {
    
    dsp_factory* fProcessFactory;
    dsp_factory* fEffectFactory;
    
    dsp* adaptDSP(dsp* dsp, bool is_double)
    {
        return (is_double) ? new dsp_sample_adapter<double, float>(dsp) : dsp;
    }

    dsp_poly_factory(dsp_factory* process_factory = nullptr,
                     dsp_factory* effect_factory = nullptr):
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

    std::string getEffectCode(const std::string& dsp_content)
    {
        std::stringstream effect_code;
        effect_code << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        effect_code << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        effect_code << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        return effect_code.str();
    }

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
     * @param nvoices - number of polyphony voices, should be at least 1
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     * @param is_double - if true, internally allocated DSPs will be adapted to receive 'double' samples.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group, bool is_double = false)
    {
        dsp_poly* dsp_poly = new mydsp2_poly(adaptDSP(fProcessFactory->createDSPInstance(), is_double), nvoices, control, group);
        if (fEffectFactory) {
            // the 'dsp_poly' object has to be controlled with MIDI, so kept separated from new dsp_sequencer(...) object
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, adaptDSP(fEffectFactory->createDSPInstance(), is_double)));
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
/************************** END poly-dsp.h **************************/
/************************** BEGIN faust-engine.h ***********************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

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

    uintptr_t keyOn(void*, int, int);
    int keyOff(void*, int);
    
    void propagateMidi(void*, int, double, int, int, int, int);

    const char* getJSONUI(void*);
    const char* getJSONMeta(void*);

    int getParamsCount(void*);

    void setParamValue(void*, const char*, float);
    float getParamValue(void*, const char*);
    
    void setParamIdValue(void*, int, float);
    float getParamIdValue(void*, int);

    void setVoiceParamValue(void*, const char*, uintptr_t, float);
    float getVoiceParamValue(void*, const char*, uintptr_t);

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
/************************** END faust-engine.h **************************/

//**************************************************************
// Mono or polyphonic audio DSP engine
//**************************************************************

using namespace std;

class FaustPolyMotionEngine {
        
    protected:

        mydsp2_poly* fPolyDSP;     // the polyphonic Faust object
        dsp* fFinalDSP;           // the "final" dsp object submitted to the audio driver
    
        APIUI fAPIUI;             // the UI description

        string fJSONUI;
        string fJSONMeta;
        bool fRunning;
        audio* fDriver;
    
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
    
        void init(dsp* mono_dsp, audio* driver, midi_handler* handler)
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
            
            if (nvoices > 0) {
                
                fPolyDSP = new mydsp2_poly(mono_dsp, nvoices, true);
                
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
                fPolyDSP = nullptr;
                fFinalDSP = mono_dsp;
            }
            
            fFinalDSP->buildUserInterface(&fMidiUI);
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
            if (handler) handler->setName(meta.fName);
            
            if (driver) {
                // If driver cannot be initialized, start will fail later on...
                if (!driver->init(meta.fName.c_str(), fFinalDSP)) {
                    delete driver;
                    fDriver = nullptr;
                } else {
                    fDriver = driver;
                }
            } else {
                fDriver = nullptr;
            }
        }
    
    public:
    
        FaustPolyMotionEngine(dsp* mono_dsp, audio* driver = nullptr, midi_handler* midi = nullptr):fMidiUI(&fMidiHandler)
        {
            assert(mono_dsp);
            init(mono_dsp, driver, midi);
        }
    
        virtual ~FaustPolyMotionEngine()
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
    
        /*
         * keyOn(pitch, velocity)
         * Instantiates a new polyphonic voice where velocity
         * and pitch are MIDI numbers (0-127). keyOn can only
         * be used if nvoices > 0. keyOn will return 0 if the
         * object is not polyphonic and the allocated voice otherwise.
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
         * used if nvoices > 0. keyOff will return 0 if the
         * object is not polyphonic and 1 otherwise.
         */
        int keyOff(int pitch, int velocity = 0)
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
         * deleteVoice(uintptr_t voice)
         * Delete a voice based on its MapUI* casted as a uintptr_t.
         */
        int deleteVoice(uintptr_t voice)
        {
            return deleteVoice(reinterpret_cast<MapUI*>(voice));
        }
        
        /*
         * allNotesOff()
         * Terminates all the active voices, gently (with release when hard = false or immediately when hard = true)
         */
        void allNotesOff(bool hard = false)
        {
            if (fPolyDSP) {
                fPolyDSP->allNotesOff(hard);
            }
        }
    
        /*
         * Propagate MIDI data to the Faust object.
         */
        void propagateMidi(int count, double time, int type, int channel, int data1, int data2)
        {
            if (count == 3) fMidiHandler.handleData2(time, type, channel, data1, data2);
            else if (count == 2) fMidiHandler.handleData1(time, type, channel, data1);
            else if (count == 1) fMidiHandler.handleSync(time, type);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
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
         * buildUserInterface(UI* ui_interface)
         * Calls the polyphonic or monophonic buildUserInterface with the ui_interface parameter.
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
                setParamValue(id, value);
            } else {
                fprintf(stderr, "setParamValue : '%s' not found\n", (address == nullptr ? "NULL" : address));
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
            if (id >= 0) {
                return fAPIUI.getParamValue(id);
            } else {
                fprintf(stderr, "getParamValue : '%s' not found\n", (address == nullptr ? "NULL" : address));
                return 0.f;
            }
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
         * used if nvoices > 0.
         */
        void setVoiceParamValue(const char* address, uintptr_t voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }

        /*
         * setVoiceParamValue(id, voice, value)
         * Sets the value of the parameter associated with the id for
         * the voice. setVoiceParamValue can only be
         * used if nvoices > 0.
         */
        void setVoiceParamValue(int id, uintptr_t voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(reinterpret_cast<MapUI*>(voice)->getParamAddress(id), value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if nvoices > 0.
         */
        float getVoiceParamValue(const char* address, uintptr_t voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(address);
        }

        /*
         * getVoiceParamValue(id, voice)
         * Gets the parameter value associated with the id for the voice.
         * getVoiceParamValue can only be used if nvoices > 0.
         */
        float getVoiceParamValue(int id, uintptr_t voice)
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
        const char* getVoiceParamAddress(int id, uintptr_t voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamAddress1(id);
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
            // In POLY mode, update all voices
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
            // In POLY mode, update all voices
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
         * c < 0 : no screen color requested (keep regular UI)
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
    
    void destroy(void* dsp) { delete reinterpret_cast<FaustPolyMotionEngine*>(dsp); }

    bool start(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->start(); }
    void stop(void* dsp) { reinterpret_cast<FaustPolyMotionEngine*>(dsp)->stop(); }
    
    bool isRunning(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->isRunning(); }

    uintptr_t keyOn(void* dsp, int pitch, int velocity) { return (uintptr_t)reinterpret_cast<FaustPolyMotionEngine*>(dsp)->keyOn(pitch, velocity); }
    int keyOff(void* dsp, int pitch) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->keyOff(pitch); }
    
    void propagateMidi(void* dsp, int count, double time, int type, int channel, int data1, int data2)
    {
        reinterpret_cast<FaustPolyMotionEngine*>(dsp)->propagateMidi(count, time, type, channel, data1, data2);
    }

    const char* getJSONUI(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getJSONUI(); }
    const char* getJSONMeta(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getJSONMeta(); }

    int getParamsCount(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getParamsCount(); }
    
    void setParamValue(void* dsp, const char* address, float value)
    {
        reinterpret_cast<FaustPolyMotionEngine*>(dsp)->setParamValue(address, value);
    }
    float getParamValue(void* dsp, const char* address) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getParamValue(address); }
   
    void setParamIdValue(void* dsp, int id, float value) { reinterpret_cast<FaustPolyMotionEngine*>(dsp)->setParamValue(id, value); }
    float getParamIdValue(void* dsp, int id) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getParamValue(id); }
    
    void setVoiceParamValue(void* dsp, const char* address, uintptr_t voice, float value)
    {
        reinterpret_cast<FaustPolyMotionEngine*>(dsp)->setVoiceParamValue(address, voice, value);
    }
    float getVoiceParamValue(void* dsp, const char* address, uintptr_t voice)
    {
        return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getVoiceParamValue(address, voice);
    }
    
    const char* getParamAddress(void* dsp, int id) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getParamAddress(id); }

    void propagateAcc(void* dsp, int acc, float v) { reinterpret_cast<FaustPolyMotionEngine*>(dsp)->propagateAcc(acc, v); }
    void setAccConverter(void* dsp, int p, int acc, int curve, float amin, float amid, float amax)
    {
        reinterpret_cast<FaustPolyMotionEngine*>(dsp)->setAccConverter(p, acc, curve, amin, amid, amax);
    }
    void propagateGyr(void* dsp, int acc, float v) { reinterpret_cast<FaustPolyMotionEngine*>(dsp)->propagateGyr(acc, v); }
    void setGyrConverter(void* dsp, int p, int gyr, int curve, float amin, float amid, float amax)
    {
        reinterpret_cast<FaustPolyMotionEngine*>(dsp)->setGyrConverter(p, gyr, curve, amin, amid, amax);
    }

    float getCPULoad(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getCPULoad(); }
    int getScreenColor(void* dsp) { return reinterpret_cast<FaustPolyMotionEngine*>(dsp)->getScreenColor(); }
    
#ifdef __cplusplus
}
#endif

#endif // __faust_poly_engine__
/************************** END faust-poly-engine.h **************************/
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


class FaustMotionEngine : public FaustPolyMotionEngine
{

public:

    myaudio* fDriver;

    FaustMotionEngine(dsp* mono_dsp, myaudio* driver = NULL) : FaustPolyMotionEngine(mono_dsp,driver)
    {
        //init(((mono_dsp) ? mono_dsp : new mydsp2()), driver, NULL);
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
    
    myaudio* driver2= new motion_audio(sample_rate, buffer_size, 0, false, false);
    
    init(driver2);
}

void DspFaustMotion::init(myaudio* driver){
    
    fMotionEngine = new FaustMotionEngine(new mydsp2(),driver);
    
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
        argv[10] = "0";
        fMotionOSCUI = new OSCUI("Faust", 11, (char**)argv);
        driver->addControlCallback(osc_compute_callback, fMotionOSCUI);
        fMotionEngine->buildUserInterface(fMotionOSCUI);
    #endif
    
}


DspFaustMotion::~DspFaustMotion(){
    delete fMotionEngine;
    
    #if OSCCTRL
        delete fMotionOSCUI;
    #endif

}

bool DspFaustMotion::start(){
    #if OSCCTRL
        fMotionOSCUI->run();
    #endif

    return fMotionEngine->start();
    
    
}

void DspFaustMotion::stop(){
    #if OSCCTRL
        fMotionOSCUI->stop();
    #endif

    fMotionEngine->stop();
    
    
}
    
void DspFaustMotion::setOSCValue(const char* address, const char* inPort, const char* outPort){

#if OSCCTRL
    if (isRunning()) {
    } else {
#if OSCALL
        oscfaust::OSCControler::gXmit = 1;
#endif
#if OSCALIAS
        oscfaust::OSCControler::gXmit = 2;
#endif
        fMotionOSCUI->setUDPPort(atoi(inPort));
        fMotionOSCUI->setUDPOut(atoi(outPort));
        fMotionOSCUI->setDestAddress(address);
    }
#endif


}

bool DspFaustMotion::setOSCValue(const char* address, int inPort, int outPort){

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
        fMotionOSCUI->setUDPPort(inPort);
        fMotionOSCUI->setUDPOut(outPort);
        fMotionOSCUI->setDestAddress(address);
        return true;
    }

#else
    return false;
#endif

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

#endif
