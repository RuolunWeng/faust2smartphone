#define TARGET_OS_IPHONE 1
//----------------------------------------------------------
// name: "Faust Motion Library [Motion+RotationMatrix]"
// version: "0.7"
//
// Code generated with Faust 2.19.7 (https://faust.grame.fr)
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

/************************** BEGIN misc.h **************************/
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
#include <fstream>
#include <string>

/************************** BEGIN meta.h **************************/
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
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/

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
/************************** BEGIN UI.h **************************/
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

template <typename REAL>
class UIReal
{
    
    public:
        
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
};

class UI : public UIReal<FAUSTFLOAT>
{

    public:

        UI() {}
        virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN dsp.h **************************/
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
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
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
/**************************  END  dsp.h **************************/
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

        jsonfaustui(const char *name, const char* address, int port);
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
/************************** BEGIN JSONUI.h **************************/
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
#include <iomanip>
#include <sstream>
#include <algorithm>

/************************** BEGIN PathBuilder.h **************************/
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
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

template <typename REAL>
class JSONUIAux : public PathBuilder, public Meta, public UIReal<REAL>
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
        std::map<std::string, int> fPathTable;
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
     
        JSONUIAux(const std::string& name,
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
                  const std::map<std::string, int>& path_table)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table);
        }

        JSONUIAux(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }

        JSONUIAux(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
        
        JSONUIAux()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
 
        virtual ~JSONUIAux() {}
        
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
                  const std::map<std::string, int>& path_table,
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

class JSONUI : public JSONUIAux<FAUSTFLOAT>, public UI
{
    public :
    
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
               const std::map<std::string, int>& path_table):
        JSONUIAux<FAUSTFLOAT>(name, filename,
                              inputs, outputs,
                              sr_index,
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
    
        virtual void openTabBox(const char* label)
        {
            JSONUIAux<FAUSTFLOAT>::openTabBox(label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            JSONUIAux<FAUSTFLOAT>::openHorizontalBox(label);
        }
        virtual void openVerticalBox(const char* label)
        {
            JSONUIAux<FAUSTFLOAT>::openVerticalBox(label);
        }
        virtual void closeBox()
        {
            JSONUIAux<FAUSTFLOAT>::closeBox();
        }
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            JSONUIAux<FAUSTFLOAT>::addButton(label, zone);
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            JSONUIAux<FAUSTFLOAT>::addCheckButton(label, zone);
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            JSONUIAux<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            JSONUIAux<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            JSONUIAux<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            JSONUIAux<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            JSONUIAux<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
        }
        
        // -- soundfiles
        
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
        {
            JSONUIAux<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
        }
        
        // -- metadata declarations
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            JSONUIAux<FAUSTFLOAT>::declare(zone, key, val);
        }
    
        virtual void declare(const char* key, const char* val)
        {
            JSONUIAux<FAUSTFLOAT>::declare(key, val);
        }
    
        virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/
/************************** BEGIN MapUI.h **************************/
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
    
        static bool endsWith(std::string const& str, std::string const& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN GUI.h **************************/
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
            for (auto& it : fZoneMap) {
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
            for (auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        static void runAllGuis()
        {
            for (auto& g : fGuiList) {
                g->run();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        virtual void show() {};	
        virtual bool run() { return false; };

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
            for (auto& it : fZoneMap) {
                *it = v;
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
    for (auto& it : *cl) {
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    }
}

#endif
/**************************  END  GUI.h **************************/
/************************** BEGIN JSONUIDecoder.h **************************/
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
#include <functional>

/************************** BEGIN CGlue.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
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

#ifndef CGLUE_H
#define CGLUE_H

/************************** BEGIN CInterface.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
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
 * UI and Meta classes for C or LLVM generated code.
 ******************************************************************************/

// -- widget's layouts

typedef void (* openTabBoxFun) (void* ui_interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* ui_interface, const char* label);
typedef void (* openVerticalBoxFun) (void* ui_interface, const char* label);
typedef void (*closeBoxFun) (void* ui_interface);

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
typedef void (* deleteDspFun) (dsp_imp* dsp);
typedef void (* allocateDspFun) (dsp_imp* dsp);
typedef void (* destroyDspFun) (dsp_imp* dsp);
typedef int (* getNumInputsFun) (dsp_imp* dsp);
typedef int (* getNumOutputsFun) (dsp_imp* dsp);
typedef void (* buildUserInterfaceFun) (dsp_imp* dsp, UIGlue* ui);
typedef void (* initFun) (dsp_imp* dsp, int sample_rate);
typedef void (* clearFun) (dsp_imp* dsp);
typedef int (* getSampleRateFun) (dsp_imp* dsp);
typedef void (* computeFun) (dsp_imp* dsp, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
typedef void (* metadataFun) (MetaGlue* meta);
typedef void (* classInitFun) (int sample_rate);
typedef const char* (* getJSONFun) ();
    
/***************************************
 * DSP memory manager functions
 ***************************************/

typedef void* (* allocateFun) (void* manager_interface, size_t size);
typedef void (* destroyFun) (void* manager_interface, void* ptr);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} ManagerGlue;

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
    
class UITemplate
{
    
    private:
        
        void* fCPPInterface;
        
    public:
        
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

static void* allocateManagerGlue(void* cpp_interface, size_t size)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    return manager_interface->allocate(size);
}
    
static void destroyManagerGlue(void* cpp_interface, void* ptr)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    manager_interface->destroy(ptr);
}

static void buildManagerGlue(ManagerGlue* glue, dsp_memory_manager* manager)
{
    glue->managerInterface = manager;
    glue->allocate = allocateManagerGlue;
    glue->destroy = destroyManagerGlue;
}

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CGlue.h **************************/
/************************** BEGIN SimpleParser.h **************************/
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
    int index;
    double init;
    double min;
    double max;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), min(0.), max(0.), step(0.)
    {}
};

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
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
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
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
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
                        uiItems[numItems].min = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].max = dbl;
                    }
                }
                
                else if (label == "step"){
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
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
                            itemInfo item;
                            item.type = "close";
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

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//-------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface'
//-------------------------------------------------------------------

#define REAL_UI(ui_interface)  reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(offset)       reinterpret_cast<REAL*>(&memory_block[offset])
#define SOUNDFILE_ADR(offset)  reinterpret_cast<Soundfile**>(&memory_block[offset])

typedef std::function<void(double)> ReflectFunction;
typedef std::function<double()> ModifyFunction;

struct ExtZoneParam {

    virtual void reflectZone() = 0;
    virtual void modifyZone() = 0;
    
    virtual void setReflectZoneFun(ReflectFunction reflect) = 0;
    virtual void setModifyZoneFun(ModifyFunction modify) = 0;
    
    virtual ~ExtZoneParam()
    {}
    
};

template <typename REAL>
struct JSONUIDecoderAux {
    
    struct ZoneParam : public ExtZoneParam {
        
        REAL fZone;
        int fIndex;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(int index, ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fIndex(index), fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(int index, ReflectFunction reflect = [](REAL value) {}, ModifyFunction modify = []() { return REAL(-1); })
        :fIndex(index), fReflect(reflect), fModify(modify)
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
    
    Soundfile** fSoundfiles;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fSoundfileItems;
    int fDSPSize;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]

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

    JSONUIDecoderAux(const std::string& json)
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
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = getInt(meta_data1, "size");
        fNumInputs = getInt(meta_data1, "inputs");
        fNumOutputs = getInt(meta_data1, "outputs");
        fSRIndex = getInt(meta_data1, "sr_index");
       
        fSoundfileItems = 0;
        for (auto& it : fUiItems) {
            std::string type = it.type;
            if (isSoundfile(type)) {
                fSoundfileItems++;
            }
        }
        
        fSoundfiles = new Soundfile*[fSoundfileItems];
        
        // Prepare the fPathTable and init zone
        for (auto& it : fUiItems) {
            std::string type = it.type;
            // Meta data declaration for input items
            if (isInput(type)) {
                ZoneParam* param = new ZoneParam(it.index);
                fPathInputTable.push_back(param);
                param->fZone = it.init;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                ZoneParam* param = new ZoneParam(it.index);
                fPathOutputTable.push_back(param);
                param->fZone = REAL(0);
            }
        }
    }
    
    virtual ~JSONUIDecoderAux()
    {
        delete [] fSoundfiles;
    }
    
    void metadata(Meta* m)
    {
        for (auto& it : fMetadata) {
            m->declare(it.first.c_str(), it.second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        for (auto& it : fMetadata) {
            m->declare(m->metaInterface, it.first.c_str(), it.second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        int item = 0;
        for (auto& it : fUiItems) {
            if (isInput(it.type)) {
                static_cast<ZoneParam*>(fPathInputTable[item++])->fZone = it.init;
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        for (auto& it : fUiItems) {
            int offset = it.index;
            if (isInput(it.type)) {
                *REAL_ADR(offset) = it.init;
            } else if (isSoundfile(it.type)) {
                if (*SOUNDFILE_ADR(offset) == nullptr) {
                    *SOUNDFILE_ADR(offset) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
   
    void buildUserInterface(UI* ui_interface)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        setlocale(LC_ALL, "C");
        
        int countIn = 0;
        int countOut = 0;
        int countSound = 0;
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            REAL init = REAL(it.init);
            REAL min = REAL(it.min);
            REAL max = REAL(it.max);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
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
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), &fSoundfiles[countSound]);
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
            
            if (isInput(type)) {
                countIn++;
            } else if (isOutput(type)) {
                countOut++;
            } else if (isSoundfile(type)) {
                countSound++;
            }
        }
        
        setlocale(LC_ALL, tmp_local);
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        setlocale(LC_ALL, "C");
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            int offset = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.min);
            REAL max = REAL(it.max);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
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
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), REAL_ADR(offset));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(offset));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), REAL_ADR(offset));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
        }
        
        setlocale(LC_ALL, tmp_local);
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        // TODO
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

// Templated decoder

struct JSONUITemplatedDecoder
{

    virtual ~JSONUITemplatedDecoder()
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
    virtual std::vector<ExtZoneParam*>& getInputControls() = 0;
    virtual std::vector<ExtZoneParam*>& getOutputControls() = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

struct JSONUIFloatDecoder : public JSONUIDecoderAux<float>, public JSONUITemplatedDecoder
{
    JSONUIFloatDecoder(const std::string& json):JSONUIDecoderAux<float>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderAux<float>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderAux<float>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block)  { return JSONUIDecoderAux<float>::getSampleRate(memory_block); }
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        JSONUIDecoderAux<float>::setReflectZoneFun(index, fun);
    }
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        JSONUIDecoderAux<float>::setModifyZoneFun(index, fun);
    }
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderAux<float>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface)
    {
        JSONUIDecoderAux<float>::buildUserInterface(ui_interface);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<float>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<float>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderAux<float>::hasCompileOption(option); }
};

struct JSONUIDoubleDecoder : public JSONUIDecoderAux<double>, public JSONUITemplatedDecoder
{
    JSONUIDoubleDecoder(const std::string& json):JSONUIDecoderAux<double>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderAux<double>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderAux<double>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block) { return JSONUIDecoderAux<double>::getSampleRate(memory_block); }
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        JSONUIDecoderAux<double>::setReflectZoneFun(index, fun);
    }
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        JSONUIDecoderAux<double>::setModifyZoneFun(index, fun);
    }
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderAux<double>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface)
    {
        JSONUIDecoderAux<double>::buildUserInterface(ui_interface);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<double>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<double>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderAux<double>::hasCompileOption(option); }
};

// FAUSTFLOAT decoder

struct JSONUIDecoder : public JSONUIDecoderAux<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderAux<FAUSTFLOAT>(json)
    {}
};

static JSONUITemplatedDecoder* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDoubleDecoder(json);
    } else {
        return new JSONUIFloatDecoder(json);
    }
}

#endif
/**************************  END  JSONUIDecoder.h **************************/
/************************** BEGIN dsp-adapter.h **************************/
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
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses TYPE_INT
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses TYPE_INT
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
       }
};

#endif
/**************************  END  dsp-adapter.h **************************/


#include <math.h>
#include <cmath>


#if OSCCTRL
#define OSC_IP_ADDRESS  "192.168.0.101"
#define OSC_IN_PORT     "5510"
#define OSC_OUT_PORT    "5511"

/************************** BEGIN OSCUI.h **************************/
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
template <typename C> class FaustNode : public MessageDriven, public uiTypedItem<C>
{
	mapping<C>	fMapping;
    RootNode*   fRoot;
    bool        fInput;  // true for input nodes (slider, button...)
	
	//---------------------------------------------------------------------
	// Warning !!!
	// The cast (C *)fZone is necessary because the real size allocated is
	// only known at execution time. When the library is compiled, fZone is
	// uniquely defined by FAUSTFLOAT.
	//---------------------------------------------------------------------
	bool store(C val) { *(C *)this->fZone = fMapping.clip(val); return true; }
	void sendOSC() const;

	protected:
		FaustNode(RootNode* root, const char *name, C* zone, C init, C min, C max, const char* prefix, GUI* ui, bool initZone, bool input) 
			: MessageDriven(name, prefix), uiTypedItem<C>(ui, zone), fMapping(min, max), fRoot(root), fInput(input)
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
            char * ptr = buffer; int n=1;
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
        
        OSCUI(const char* /*applicationname*/, int argc, char* argv[], oscfaust::OSCIO* io = NULL, ErrorCallback errCallback = NULL, void* arg = NULL, bool init = true) : GUI()
        {
            fCtrl = new oscfaust::OSCControler(argc, argv, this, &fJSON, io, errCallback, arg, init);
            //		fCtrl->opengroup(applicationname);
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
        
        virtual void show() {}
        
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
	FAUSTFLOAT 	fcheckbox38;
	float 	fRec67[2];
	FAUSTFLOAT 	fslider32;
	float 	fTempPerm78;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	float 	fTempPerm79;
	float 	fRec66[2];
	float 	fRec65[2];
	float 	fTempPerm80;
	FAUSTFLOAT 	fcheckbox39;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fcheckbox40;
	FAUSTFLOAT 	fcheckbox41;
	float 	fRec70[2];
	float 	fTempPerm81;
	float 	fTempPerm82;
	float 	fRec69[2];
	float 	fRec68[2];
	float 	fTempPerm83;
	FAUSTFLOAT 	fcheckbox42;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fcheckbox43;
	FAUSTFLOAT 	fcheckbox44;
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
	float 	fTempPerm107;
	float 	fRec87[2];
	float 	fRec86[2];
	float 	fTempPerm108;
	FAUSTFLOAT 	fcheckbox45;
	float 	fConst7;
	float 	fConst8;
	FAUSTFLOAT 	fslider37;
	float 	fTempPerm109;
	FAUSTFLOAT 	fcheckbox46;
	FAUSTFLOAT 	fcheckbox47;
	FAUSTFLOAT 	fcheckbox48;
	FAUSTFLOAT 	fcheckbox49;
	FAUSTFLOAT 	fcheckbox50;
	FAUSTFLOAT 	fcheckbox51;
	float 	fTempPerm110;
	FAUSTFLOAT 	fcheckbox52;
	float 	fTempPerm111;
	float 	fTempPerm112;
	FAUSTFLOAT 	fcheckbox53;
	float 	fTempPerm113;
	float 	fRec88[2];
	float 	fTempPerm114;
	FAUSTFLOAT 	fslider38;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fRec89[2];
	float 	fTempPerm117;
	FAUSTFLOAT 	fslider39;
	float 	fRec90[2];
	float 	fTempPerm118;
	FAUSTFLOAT 	fslider40;
	float 	fRec91[2];
	float 	fTempPerm119;
	FAUSTFLOAT 	fslider41;
	float 	fTempPerm120;
	float 	fRec92[2];
	float 	fTempPerm121;
	FAUSTFLOAT 	fslider42;
	float 	fRec93[2];
	float 	fTempPerm122;
	FAUSTFLOAT 	fcheckbox54;
	float 	fTempPerm123;
	FAUSTFLOAT 	fcheckbox55;
	FAUSTFLOAT 	fcheckbox56;
	FAUSTFLOAT 	fcheckbox57;
	FAUSTFLOAT 	fcheckbox58;
	FAUSTFLOAT 	fcheckbox59;
	float 	fTempPerm124;
	float 	fTempPerm125;
	float 	fTempPerm126;
	float 	fTempPerm127;
	float 	fRec94[2];
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fRec95[2];
	float 	fTempPerm131;
	float 	fRec96[2];
	float 	fTempPerm132;
	float 	fRec97[2];
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fRec98[2];
	float 	fTempPerm135;
	float 	fRec99[2];
	float 	fTempPerm136;
	FAUSTFLOAT 	fcheckbox60;
	float 	fTempPerm137;
	FAUSTFLOAT 	fcheckbox61;
	FAUSTFLOAT 	fcheckbox62;
	FAUSTFLOAT 	fcheckbox63;
	FAUSTFLOAT 	fcheckbox64;
	FAUSTFLOAT 	fcheckbox65;
	FAUSTFLOAT 	fcheckbox66;
	FAUSTFLOAT 	fcheckbox67;
	float 	fTempPerm138;
	FAUSTFLOAT 	fcheckbox68;
	FAUSTFLOAT 	fcheckbox69;
	float 	fTempPerm139;
	float 	fTempPerm140;
	FAUSTFLOAT 	fcheckbox70;
	float 	fTempPerm141;
	float 	fRec100[2];
	float 	fTempPerm142;
	float 	fTempPerm143;
	float 	fTempPerm144;
	float 	fRec101[2];
	float 	fTempPerm145;
	float 	fRec102[2];
	float 	fTempPerm146;
	float 	fRec103[2];
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fRec104[2];
	float 	fTempPerm149;
	float 	fRec105[2];
	float 	fTempPerm150;
	FAUSTFLOAT 	fcheckbox71;
	float 	fTempPerm151;
	FAUSTFLOAT 	fcheckbox72;
	FAUSTFLOAT 	fcheckbox73;
	FAUSTFLOAT 	fcheckbox74;
	FAUSTFLOAT 	fcheckbox75;
	FAUSTFLOAT 	fcheckbox76;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fTempPerm155;
	float 	fRec106[2];
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fRec107[2];
	float 	fTempPerm159;
	float 	fRec108[2];
	float 	fTempPerm160;
	float 	fRec109[2];
	float 	fTempPerm161;
	float 	fTempPerm162;
	float 	fRec110[2];
	float 	fTempPerm163;
	float 	fRec111[2];
	float 	fTempPerm164;
	FAUSTFLOAT 	fcheckbox77;
	float 	fTempPerm165;
	FAUSTFLOAT 	fcheckbox78;
	FAUSTFLOAT 	fcheckbox79;
	FAUSTFLOAT 	fcheckbox80;
	FAUSTFLOAT 	fcheckbox81;
	FAUSTFLOAT 	fcheckbox82;
	FAUSTFLOAT 	fcheckbox83;
	float 	fTempPerm166;
	FAUSTFLOAT 	fcheckbox84;
	float 	fTempPerm167;
	float 	fTempPerm168;
	FAUSTFLOAT 	fcheckbox85;
	float 	fTempPerm169;
	float 	fRec112[2];
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fTempPerm172;
	float 	fRec113[2];
	float 	fTempPerm173;
	float 	fRec114[2];
	float 	fTempPerm174;
	float 	fRec115[2];
	float 	fTempPerm175;
	float 	fTempPerm176;
	float 	fRec116[2];
	float 	fTempPerm177;
	float 	fRec117[2];
	float 	fTempPerm178;
	FAUSTFLOAT 	fcheckbox86;
	float 	fTempPerm179;
	FAUSTFLOAT 	fcheckbox87;
	FAUSTFLOAT 	fcheckbox88;
	FAUSTFLOAT 	fcheckbox89;
	FAUSTFLOAT 	fcheckbox90;
	FAUSTFLOAT 	fcheckbox91;
	float 	fTempPerm180;
	float 	fTempPerm181;
	float 	fTempPerm182;
	float 	fTempPerm183;
	float 	fRec118[2];
	float 	fTempPerm184;
	float 	fTempPerm185;
	float 	fTempPerm186;
	float 	fRec119[2];
	float 	fTempPerm187;
	float 	fRec120[2];
	float 	fTempPerm188;
	float 	fRec121[2];
	float 	fTempPerm189;
	float 	fTempPerm190;
	float 	fRec122[2];
	float 	fTempPerm191;
	float 	fRec123[2];
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
	float 	fTempPerm209;
	float 	fTempPerm210;
	int fSampleRate;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
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
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
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
	virtual int getNumOutputs() { return 92; }
	static void classInit(int sample_rate) {
	}
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = min(192000.0f, max(1.0f, (float)fSampleRate));
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
		fTempPerm108 = 0;
		fConst7 = expf((0 - (100.0f / fConst0)));
		fConst8 = (1.0f - fConst7);
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
		fTempPerm209 = 0;
		fTempPerm210 = 0;
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
		fcheckbox38 = 0.0;
		fslider32 = 0.01f;
		fslider33 = 50.0f;
		fslider34 = 50.0f;
		fcheckbox39 = 0.0;
		fslider35 = 0.0f;
		fcheckbox40 = 0.0;
		fcheckbox41 = 0.0;
		fcheckbox42 = 0.0;
		fslider36 = 0.0f;
		fcheckbox43 = 0.0;
		fcheckbox44 = 0.0;
		fcheckbox45 = 0.0;
		fslider37 = 1.0f;
		fcheckbox46 = 0.0;
		fcheckbox47 = 0.0;
		fcheckbox48 = 0.0;
		fcheckbox49 = 0.0;
		fcheckbox50 = 0.0;
		fcheckbox51 = 0.0;
		fcheckbox52 = 0.0;
		fcheckbox53 = 0.0;
		fslider38 = 1.0f;
		fslider39 = 1.0f;
		fslider40 = 1.0f;
		fslider41 = 1.0f;
		fslider42 = 1.0f;
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
		fcheckbox91 = 0.0;
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
		ui_interface->addHorizontalSlider("tgyr_up_Param", &fslider34, 50.0f, 0.0f, 5000.0f, 1.0f);
		ui_interface->declare(&fslider33, "113", "");
		ui_interface->declare(&fslider33, "showName", "gyoEvDown");
		ui_interface->addHorizontalSlider("tgyr_down_Param", &fslider33, 50.0f, 0.0f, 5000.0f, 1.0f);
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
		ui_interface->declare(&fcheckbox39, "29", "");
		ui_interface->declare(&fcheckbox39, "motionName", "gypn");
		ui_interface->addCheckButton("gypnOn", &fcheckbox39);
		ui_interface->declare(&fcheckbox42, "30", "");
		ui_interface->declare(&fcheckbox42, "motionName", "gzpn");
		ui_interface->addCheckButton("gzpnOn", &fcheckbox42);
		ui_interface->declare(&fcheckbox35, "31", "");
		ui_interface->declare(&fcheckbox35, "motionName", "gxp");
		ui_interface->addCheckButton("gxpOn", &fcheckbox35);
		ui_interface->declare(&fcheckbox40, "32", "");
		ui_interface->declare(&fcheckbox40, "motionName", "gyp");
		ui_interface->addCheckButton("gypOn", &fcheckbox40);
		ui_interface->declare(&fcheckbox43, "33", "");
		ui_interface->declare(&fcheckbox43, "motionName", "gzp");
		ui_interface->addCheckButton("gzpOn", &fcheckbox43);
		ui_interface->declare(&fcheckbox36, "34", "");
		ui_interface->declare(&fcheckbox36, "motionName", "gxn");
		ui_interface->addCheckButton("gxnOn", &fcheckbox36);
		ui_interface->declare(&fcheckbox41, "35", "");
		ui_interface->declare(&fcheckbox41, "motionName", "gyn");
		ui_interface->addCheckButton("gynOn", &fcheckbox41);
		ui_interface->declare(&fcheckbox44, "36", "");
		ui_interface->declare(&fcheckbox44, "motionName", "gzn");
		ui_interface->addCheckButton("gznOn", &fcheckbox44);
		ui_interface->declare(&fcheckbox37, "37", "");
		ui_interface->declare(&fcheckbox37, "motionName", "totalgyro");
		ui_interface->addCheckButton("totalgyroOn", &fcheckbox37);
		ui_interface->declare(&fcheckbox45, "38", "");
		ui_interface->declare(&fcheckbox45, "motionName", "brasG_cour");
		ui_interface->addCheckButton("brasG_courOn", &fcheckbox45);
		ui_interface->declare(&fcheckbox46, "39", "");
		ui_interface->declare(&fcheckbox46, "motionName", "brasG_rear");
		ui_interface->addCheckButton("brasG_rearOn", &fcheckbox46);
		ui_interface->declare(&fcheckbox47, "40", "");
		ui_interface->declare(&fcheckbox47, "motionName", "brasG_jardin");
		ui_interface->addCheckButton("brasG_jardinOn", &fcheckbox47);
		ui_interface->declare(&fcheckbox48, "41", "");
		ui_interface->declare(&fcheckbox48, "motionName", "brasG_front");
		ui_interface->addCheckButton("brasG_frontOn", &fcheckbox48);
		ui_interface->declare(&fcheckbox49, "42", "");
		ui_interface->declare(&fcheckbox49, "motionName", "brasG_down");
		ui_interface->addCheckButton("brasG_downOn", &fcheckbox49);
		ui_interface->declare(&fcheckbox50, "43", "");
		ui_interface->declare(&fcheckbox50, "motionName", "brasG_up");
		ui_interface->addCheckButton("brasG_upOn", &fcheckbox50);
		ui_interface->declare(&fcheckbox54, "44", "");
		ui_interface->declare(&fcheckbox54, "motionName", "pieds_cour");
		ui_interface->addCheckButton("pieds_courOn", &fcheckbox54);
		ui_interface->declare(&fcheckbox55, "45", "");
		ui_interface->declare(&fcheckbox55, "motionName", "pieds_rear");
		ui_interface->addCheckButton("pieds_rearOn", &fcheckbox55);
		ui_interface->declare(&fcheckbox56, "46", "");
		ui_interface->declare(&fcheckbox56, "motionName", "pieds_jardin");
		ui_interface->addCheckButton("pieds_jardinOn", &fcheckbox56);
		ui_interface->declare(&fcheckbox57, "47", "");
		ui_interface->declare(&fcheckbox57, "motionName", "pieds_front");
		ui_interface->addCheckButton("pieds_frontOn", &fcheckbox57);
		ui_interface->declare(&fcheckbox58, "48", "");
		ui_interface->declare(&fcheckbox58, "motionName", "pieds_down");
		ui_interface->addCheckButton("pieds_downOn", &fcheckbox58);
		ui_interface->declare(&fcheckbox59, "49", "");
		ui_interface->declare(&fcheckbox59, "motionName", "pieds_up");
		ui_interface->addCheckButton("pieds_upOn", &fcheckbox59);
		ui_interface->declare(&fcheckbox60, "50", "");
		ui_interface->declare(&fcheckbox60, "motionName", "dos_cour");
		ui_interface->addCheckButton("dos_courOn", &fcheckbox60);
		ui_interface->declare(&fcheckbox61, "51", "");
		ui_interface->declare(&fcheckbox61, "motionName", "dos_rear");
		ui_interface->addCheckButton("dos_rearOn", &fcheckbox61);
		ui_interface->declare(&fcheckbox62, "52", "");
		ui_interface->declare(&fcheckbox62, "motionName", "dos_jardin");
		ui_interface->addCheckButton("dos_jardinOn", &fcheckbox62);
		ui_interface->declare(&fcheckbox63, "53", "");
		ui_interface->declare(&fcheckbox63, "motionName", "dos_front");
		ui_interface->addCheckButton("dos_frontOn", &fcheckbox63);
		ui_interface->declare(&fcheckbox64, "54", "");
		ui_interface->declare(&fcheckbox64, "motionName", "dos_down");
		ui_interface->addCheckButton("dos_downOn", &fcheckbox64);
		ui_interface->declare(&fcheckbox65, "55", "");
		ui_interface->declare(&fcheckbox65, "motionName", "dos_up");
		ui_interface->addCheckButton("dos_upOn", &fcheckbox65);
		ui_interface->declare(&fcheckbox71, "56", "");
		ui_interface->declare(&fcheckbox71, "motionName", "brasD_cour");
		ui_interface->addCheckButton("brasD_courOn", &fcheckbox71);
		ui_interface->declare(&fcheckbox72, "57", "");
		ui_interface->declare(&fcheckbox72, "motionName", "brasD_rear");
		ui_interface->addCheckButton("brasD_rearOn", &fcheckbox72);
		ui_interface->declare(&fcheckbox73, "58", "");
		ui_interface->declare(&fcheckbox73, "motionName", "brasD_jardin");
		ui_interface->addCheckButton("brasD_jardinOn", &fcheckbox73);
		ui_interface->declare(&fcheckbox74, "59", "");
		ui_interface->declare(&fcheckbox74, "motionName", "brasD_front");
		ui_interface->addCheckButton("brasD_frontOn", &fcheckbox74);
		ui_interface->declare(&fcheckbox75, "60", "");
		ui_interface->declare(&fcheckbox75, "motionName", "brasD_down");
		ui_interface->addCheckButton("brasD_downOn", &fcheckbox75);
		ui_interface->declare(&fcheckbox76, "61", "");
		ui_interface->declare(&fcheckbox76, "motionName", "brasD_up");
		ui_interface->addCheckButton("brasD_upOn", &fcheckbox76);
		ui_interface->declare(&fcheckbox77, "62", "");
		ui_interface->declare(&fcheckbox77, "motionName", "tete_cour");
		ui_interface->addCheckButton("tete_courOn", &fcheckbox77);
		ui_interface->declare(&fcheckbox78, "63", "");
		ui_interface->declare(&fcheckbox78, "motionName", "tete_rear");
		ui_interface->addCheckButton("tete_rearOn", &fcheckbox78);
		ui_interface->declare(&fcheckbox79, "64", "");
		ui_interface->declare(&fcheckbox79, "motionName", "tete_jardin");
		ui_interface->addCheckButton("tete_jardinOn", &fcheckbox79);
		ui_interface->declare(&fcheckbox80, "65", "");
		ui_interface->declare(&fcheckbox80, "motionName", "tete_front");
		ui_interface->addCheckButton("tete_frontOn", &fcheckbox80);
		ui_interface->declare(&fcheckbox81, "66", "");
		ui_interface->declare(&fcheckbox81, "motionName", "tete_down");
		ui_interface->addCheckButton("tete_downOn", &fcheckbox81);
		ui_interface->declare(&fcheckbox82, "67", "");
		ui_interface->declare(&fcheckbox82, "motionName", "tete_up");
		ui_interface->addCheckButton("tete_upOn", &fcheckbox82);
		ui_interface->declare(&fcheckbox86, "68", "");
		ui_interface->declare(&fcheckbox86, "motionName", "ventre_cour");
		ui_interface->addCheckButton("ventre_courOn", &fcheckbox86);
		ui_interface->declare(&fcheckbox87, "69", "");
		ui_interface->declare(&fcheckbox87, "motionName", "ventre_rear");
		ui_interface->addCheckButton("ventre_rearOn", &fcheckbox87);
		ui_interface->declare(&fcheckbox88, "70", "");
		ui_interface->declare(&fcheckbox88, "motionName", "ventre_jardin");
		ui_interface->addCheckButton("ventre_jardinOn", &fcheckbox88);
		ui_interface->declare(&fcheckbox89, "71", "");
		ui_interface->declare(&fcheckbox89, "motionName", "ventre_front");
		ui_interface->addCheckButton("ventre_frontOn", &fcheckbox89);
		ui_interface->declare(&fcheckbox90, "72", "");
		ui_interface->declare(&fcheckbox90, "motionName", "ventre_down");
		ui_interface->addCheckButton("ventre_downOn", &fcheckbox90);
		ui_interface->declare(&fcheckbox91, "73", "");
		ui_interface->declare(&fcheckbox91, "motionName", "ventre_up");
		ui_interface->addCheckButton("ventre_upOn", &fcheckbox91);
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
		ui_interface->declare(&fcheckbox66, "80", "");
		ui_interface->declare(&fcheckbox66, "motionName", "dosx");
		ui_interface->addCheckButton("dosxOn", &fcheckbox66);
		ui_interface->declare(&fcheckbox68, "81", "");
		ui_interface->declare(&fcheckbox68, "motionName", "dosy");
		ui_interface->addCheckButton("dosyOn", &fcheckbox68);
		ui_interface->declare(&fcheckbox67, "82", "");
		ui_interface->declare(&fcheckbox67, "motionName", "coox");
		ui_interface->addCheckButton("cooxOn", &fcheckbox67);
		ui_interface->declare(&fcheckbox69, "83", "");
		ui_interface->declare(&fcheckbox69, "motionName", "cooy");
		ui_interface->addCheckButton("cooyOn", &fcheckbox69);
		ui_interface->declare(&fcheckbox70, "84", "");
		ui_interface->declare(&fcheckbox70, "motionName", "cooz");
		ui_interface->addCheckButton("coozOn", &fcheckbox70);
		ui_interface->declare(&fcheckbox83, "85", "");
		ui_interface->declare(&fcheckbox83, "motionName", "cooxT");
		ui_interface->addCheckButton("cooxTOn", &fcheckbox83);
		ui_interface->declare(&fcheckbox84, "86", "");
		ui_interface->declare(&fcheckbox84, "motionName", "cooyT");
		ui_interface->addCheckButton("cooyTOn", &fcheckbox84);
		ui_interface->declare(&fcheckbox85, "87", "");
		ui_interface->declare(&fcheckbox85, "motionName", "coozT");
		ui_interface->addCheckButton("coozTOn", &fcheckbox85);
		ui_interface->declare(&fcheckbox51, "88", "");
		ui_interface->declare(&fcheckbox51, "motionName", "cooxBG");
		ui_interface->addCheckButton("cooxBGOn", &fcheckbox51);
		ui_interface->declare(&fcheckbox52, "89", "");
		ui_interface->declare(&fcheckbox52, "motionName", "cooyBG");
		ui_interface->addCheckButton("cooyBGOn", &fcheckbox52);
		ui_interface->declare(&fcheckbox53, "90", "");
		ui_interface->declare(&fcheckbox53, "motionName", "coozBG");
		ui_interface->addCheckButton("coozBGOn", &fcheckbox53);
		ui_interface->declare(&fcheckbox38, "91", "");
		ui_interface->declare(&fcheckbox38, "motionName", "gyro_xy");
		ui_interface->addCheckButton("gyro_xyOn", &fcheckbox38);
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
		float 	fSlow122 = float(fcheckbox38);
		int 	iSlow123 = (fSlow122 != 0.0f);
		float 	fSlow124 = float(fslider32);
		float 	fSlow125 = expf((0 - (fConst6 / float(fslider33))));
		float 	fSlow126 = expf((0 - (fConst6 / float(fslider34))));
		float 	fSlow127 = float(fcheckbox39);
		int 	iSlow128 = (fSlow127 != 0.0f);
		float 	fSlow129 = (0.0010000000000000009f * float(fslider35));
		float 	fSlow130 = float(fcheckbox40);
		int 	iSlow131 = (fSlow130 != 0.0f);
		float 	fSlow132 = float(fcheckbox41);
		int 	iSlow133 = (fSlow132 != 0.0f);
		float 	fSlow134 = float(fcheckbox42);
		int 	iSlow135 = (fSlow134 != 0.0f);
		float 	fSlow136 = (0.0010000000000000009f * float(fslider36));
		float 	fSlow137 = float(fcheckbox43);
		int 	iSlow138 = (fSlow137 != 0.0f);
		float 	fSlow139 = float(fcheckbox44);
		int 	iSlow140 = (fSlow139 != 0.0f);
		float 	fSlow141 = float(fcheckbox45);
		int 	iSlow142 = (fSlow141 != 0.0f);
		float 	fSlow143 = float(fslider37);
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
		float 	fSlow158 = float(fcheckbox53);
		int 	iSlow159 = (fSlow158 != 0.0f);
		float 	fSlow160 = float(fslider38);
		float 	fSlow161 = float(fslider39);
		float 	fSlow162 = float(fslider40);
		float 	fSlow163 = float(fslider41);
		float 	fSlow164 = float(fslider42);
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
		float 	fSlow239 = float(fcheckbox91);
		int 	iSlow240 = (fSlow239 != 0.0f);
		float 	fSlow241 = (5.0f * fSlow122);
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
		FAUSTFLOAT* output91 = output[91];
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
			if (iSlow113 || iSlow117 || iSlow119 || iSlow121 || iSlow123) {
				fRec67[0] = (fSlow115 + (0.999f * fRec67[1]));
			}
			if (iSlow113) {
				fTempPerm78 = fabsf(min((float)1, (fSlow114 * max((float)0, (fabsf(fRec67[0]) - fSlow124)))));
				fTempPerm79 = ((int((fRec65[1] > fTempPerm78)))?fSlow125:fSlow126);
				fRec66[0] = ((fRec66[1] * fTempPerm79) + (fTempPerm78 * (1.0f - fTempPerm79)));
				fRec65[0] = fRec66[0];
				fTempPerm80 = (fSlow112 * fRec65[0]);
			}
			output28[i] = (FAUSTFLOAT)fTempPerm80;
			if (iSlow128 || iSlow131 || iSlow133 || iSlow121 || iSlow123) {
				fRec70[0] = (fSlow129 + (0.999f * fRec70[1]));
			}
			if (iSlow128) {
				fTempPerm81 = fabsf(min((float)1, (fSlow114 * max((float)0, (fabsf(fRec70[0]) - fSlow124)))));
				fTempPerm82 = ((int((fRec68[1] > fTempPerm81)))?fSlow125:fSlow126);
				fRec69[0] = ((fRec69[1] * fTempPerm82) + (fTempPerm81 * (1.0f - fTempPerm82)));
				fRec68[0] = fRec69[0];
				fTempPerm83 = (fSlow127 * fRec68[0]);
			}
			output29[i] = (FAUSTFLOAT)fTempPerm83;
			if (iSlow135 || iSlow138 || iSlow140 || iSlow121) {
				fRec73[0] = (fSlow136 + (0.999f * fRec73[1]));
			}
			if (iSlow135) {
				fTempPerm84 = fabsf(min((float)1, (fSlow114 * max((float)0, (fabsf(fRec73[0]) - fSlow124)))));
				fTempPerm85 = ((int((fRec71[1] > fTempPerm84)))?fSlow125:fSlow126);
				fRec72[0] = ((fRec72[1] * fTempPerm85) + (fTempPerm84 * (1.0f - fTempPerm85)));
				fRec71[0] = fRec72[0];
				fTempPerm86 = (fSlow134 * fRec71[0]);
			}
			output30[i] = (FAUSTFLOAT)fTempPerm86;
			if (iSlow117) {
				fTempPerm87 = fabsf(min((float)1, (fSlow114 * max((float)0, (fRec67[0] - fSlow124)))));
				fTempPerm88 = ((int((fRec74[1] > fTempPerm87)))?fSlow125:fSlow126);
				fRec75[0] = ((fRec75[1] * fTempPerm88) + (fTempPerm87 * (1.0f - fTempPerm88)));
				fRec74[0] = fRec75[0];
				fTempPerm89 = (fSlow116 * fRec74[0]);
			}
			output31[i] = (FAUSTFLOAT)fTempPerm89;
			if (iSlow131) {
				fTempPerm90 = fabsf(min((float)1, (fSlow114 * max((float)0, (fRec70[0] - fSlow124)))));
				fTempPerm91 = ((int((fRec76[1] > fTempPerm90)))?fSlow125:fSlow126);
				fRec77[0] = ((fRec77[1] * fTempPerm91) + (fTempPerm90 * (1.0f - fTempPerm91)));
				fRec76[0] = fRec77[0];
				fTempPerm92 = (fSlow130 * fRec76[0]);
			}
			output32[i] = (FAUSTFLOAT)fTempPerm92;
			if (iSlow138) {
				fTempPerm93 = fabsf(min((float)1, (fSlow114 * max((float)0, (fRec73[0] - fSlow124)))));
				fTempPerm94 = ((int((fRec78[1] > fTempPerm93)))?fSlow125:fSlow126);
				fRec79[0] = ((fRec79[1] * fTempPerm94) + (fTempPerm93 * (1.0f - fTempPerm94)));
				fRec78[0] = fRec79[0];
				fTempPerm95 = (fSlow137 * fRec78[0]);
			}
			output33[i] = (FAUSTFLOAT)fTempPerm95;
			if (iSlow119) {
				fTempPerm96 = fabsf(min((float)1, (fSlow114 * max((float)0, (0 - (fSlow124 + fRec67[0]))))));
				fTempPerm97 = ((int((fRec80[1] > fTempPerm96)))?fSlow125:fSlow126);
				fRec81[0] = ((fRec81[1] * fTempPerm97) + (fTempPerm96 * (1.0f - fTempPerm97)));
				fRec80[0] = fRec81[0];
				fTempPerm98 = (fSlow118 * fRec80[0]);
			}
			output34[i] = (FAUSTFLOAT)fTempPerm98;
			if (iSlow133) {
				fTempPerm99 = fabsf(min((float)1, (fSlow114 * max((float)0, (0 - (fSlow124 + fRec70[0]))))));
				fTempPerm100 = ((int((fRec82[1] > fTempPerm99)))?fSlow125:fSlow126);
				fRec83[0] = ((fRec83[1] * fTempPerm100) + (fTempPerm99 * (1.0f - fTempPerm100)));
				fRec82[0] = fRec83[0];
				fTempPerm101 = (fSlow132 * fRec82[0]);
			}
			output35[i] = (FAUSTFLOAT)fTempPerm101;
			if (iSlow140) {
				fTempPerm102 = fabsf(min((float)1, (fSlow114 * max((float)0, (0 - (fSlow124 + fRec73[0]))))));
				fTempPerm103 = ((int((fRec84[1] > fTempPerm102)))?fSlow125:fSlow126);
				fRec85[0] = ((fRec85[1] * fTempPerm103) + (fTempPerm102 * (1.0f - fTempPerm103)));
				fRec84[0] = fRec85[0];
				fTempPerm104 = (fSlow139 * fRec84[0]);
			}
			output36[i] = (FAUSTFLOAT)fTempPerm104;
			if (iSlow121 || iSlow123) {
				fTempPerm105 = (faustpower<2>(fRec67[0]) + faustpower<2>(fRec70[0]));
			}
			if (iSlow121) {
				fTempPerm106 = fabsf(min((float)1, (fSlow114 * max((float)0, (sqrtf((fTempPerm105 + faustpower<2>(fRec73[0]))) - fSlow124)))));
				fTempPerm107 = ((int((fRec86[1] > fTempPerm106)))?fSlow125:fSlow126);
				fRec87[0] = ((fRec87[1] * fTempPerm107) + (fTempPerm106 * (1.0f - fTempPerm107)));
				fRec86[0] = fRec87[0];
				fTempPerm108 = (fSlow120 * fRec86[0]);
			}
			output37[i] = (FAUSTFLOAT)fTempPerm108;
			if (iSlow142 || iSlow145 || iSlow147 || iSlow149 || iSlow151 || iSlow153 || iSlow155) {
				fTempPerm109 = (float)input0[i];
			}
			if (iSlow142 || iSlow145 || iSlow147 || iSlow149 || iSlow151 || iSlow153 || iSlow157) {
				fTempPerm110 = (float)input1[i];
			}
			if (iSlow142 || iSlow147 || iSlow151 || iSlow153) {
				fTempPerm111 = faustpower<2>(fTempPerm110);
			}
			if (iSlow142 || iSlow145 || iSlow147 || iSlow149 || iSlow151 || iSlow153 || iSlow159) {
				fTempPerm112 = (float)input2[i];
			}
			if (iSlow142 || iSlow145 || iSlow147 || iSlow149) {
				fTempPerm113 = faustpower<2>(fTempPerm112);
			}
			if (iSlow142) {
				fRec88[0] = ((fConst7 * fRec88[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow143 * sqrtf(((faustpower<2>((fTempPerm109 + 1.0f)) + fTempPerm111) + fTempPerm113)))))));
				fTempPerm114 = (fSlow141 * fRec88[0]);
			}
			output38[i] = (FAUSTFLOAT)fTempPerm114;
			if (iSlow145 || iSlow149 || iSlow151 || iSlow153) {
				fTempPerm115 = faustpower<2>(fTempPerm109);
			}
			if (iSlow145 || iSlow149) {
				fTempPerm116 = (fTempPerm113 + fTempPerm115);
			}
			if (iSlow145) {
				fRec89[0] = ((fConst7 * fRec89[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((faustpower<2>((fTempPerm110 + 1.0f)) + fTempPerm116)))))));
				fTempPerm117 = (fSlow144 * fRec89[0]);
			}
			output39[i] = (FAUSTFLOAT)fTempPerm117;
			if (iSlow147) {
				fRec90[0] = ((fConst7 * fRec90[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((faustpower<2>((fTempPerm109 + -1.0f)) + (fTempPerm111 + fTempPerm113))))))));
				fTempPerm118 = (fSlow146 * fRec90[0]);
			}
			output40[i] = (FAUSTFLOAT)fTempPerm118;
			if (iSlow149) {
				fRec91[0] = ((fConst7 * fRec91[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm116 + faustpower<2>((fTempPerm110 + -1.0f)))))))));
				fTempPerm119 = (fSlow148 * fRec91[0]);
			}
			output41[i] = (FAUSTFLOAT)fTempPerm119;
			if (iSlow151 || iSlow153) {
				fTempPerm120 = (fTempPerm111 + fTempPerm115);
			}
			if (iSlow151) {
				fRec92[0] = ((fConst7 * fRec92[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow163 * sqrtf((fTempPerm120 + faustpower<2>((fTempPerm112 + 1.0f)))))))));
				fTempPerm121 = (fSlow150 * fRec92[0]);
			}
			output42[i] = (FAUSTFLOAT)fTempPerm121;
			if (iSlow153) {
				fRec93[0] = ((fConst7 * fRec93[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow164 * sqrtf((fTempPerm120 + faustpower<2>((fTempPerm112 + -1.0f)))))))));
				fTempPerm122 = (fSlow152 * fRec93[0]);
			}
			output43[i] = (FAUSTFLOAT)fTempPerm122;
			if (iSlow166 || iSlow168 || iSlow170 || iSlow172 || iSlow174 || iSlow176) {
				fTempPerm123 = (float)input3[i];
				fTempPerm124 = (float)input4[i];
			}
			if (iSlow166 || iSlow170 || iSlow174 || iSlow176) {
				fTempPerm125 = faustpower<2>(fTempPerm124);
			}
			if (iSlow166 || iSlow168 || iSlow170 || iSlow172 || iSlow174 || iSlow176) {
				fTempPerm126 = (float)input5[i];
			}
			if (iSlow166 || iSlow168 || iSlow170 || iSlow172) {
				fTempPerm127 = faustpower<2>(fTempPerm126);
			}
			if (iSlow166) {
				fRec94[0] = ((fConst7 * fRec94[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow143 * sqrtf(((faustpower<2>((fTempPerm123 + 1.0f)) + fTempPerm125) + fTempPerm127)))))));
				fTempPerm128 = (fSlow165 * fRec94[0]);
			}
			output44[i] = (FAUSTFLOAT)fTempPerm128;
			if (iSlow168 || iSlow172 || iSlow174 || iSlow176) {
				fTempPerm129 = faustpower<2>(fTempPerm123);
			}
			if (iSlow168 || iSlow172) {
				fTempPerm130 = (fTempPerm127 + fTempPerm129);
			}
			if (iSlow168) {
				fRec95[0] = ((fConst7 * fRec95[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((faustpower<2>((fTempPerm124 + 1.0f)) + fTempPerm130)))))));
				fTempPerm131 = (fSlow167 * fRec95[0]);
			}
			output45[i] = (FAUSTFLOAT)fTempPerm131;
			if (iSlow170) {
				fRec96[0] = ((fConst7 * fRec96[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((faustpower<2>((fTempPerm123 + -1.0f)) + (fTempPerm125 + fTempPerm127))))))));
				fTempPerm132 = (fSlow169 * fRec96[0]);
			}
			output46[i] = (FAUSTFLOAT)fTempPerm132;
			if (iSlow172) {
				fRec97[0] = ((fConst7 * fRec97[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm130 + faustpower<2>((fTempPerm124 + -1.0f)))))))));
				fTempPerm133 = (fSlow171 * fRec97[0]);
			}
			output47[i] = (FAUSTFLOAT)fTempPerm133;
			if (iSlow174 || iSlow176) {
				fTempPerm134 = (fTempPerm125 + fTempPerm129);
			}
			if (iSlow174) {
				fRec98[0] = ((fConst7 * fRec98[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow163 * sqrtf((fTempPerm134 + faustpower<2>((fTempPerm126 + 1.0f)))))))));
				fTempPerm135 = (fSlow173 * fRec98[0]);
			}
			output48[i] = (FAUSTFLOAT)fTempPerm135;
			if (iSlow176) {
				fRec99[0] = ((fConst7 * fRec99[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow164 * sqrtf((fTempPerm134 + faustpower<2>((fTempPerm126 + -1.0f)))))))));
				fTempPerm136 = (fSlow175 * fRec99[0]);
			}
			output49[i] = (FAUSTFLOAT)fTempPerm136;
			if (iSlow178 || iSlow180 || iSlow182 || iSlow184 || iSlow186 || iSlow188 || iSlow190 || iSlow192) {
				fTempPerm137 = (float)input6[i];
			}
			if (iSlow178 || iSlow180 || iSlow182 || iSlow184 || iSlow186 || iSlow188 || iSlow194 || iSlow196) {
				fTempPerm138 = (float)input7[i];
			}
			if (iSlow178 || iSlow182 || iSlow186 || iSlow188) {
				fTempPerm139 = faustpower<2>(fTempPerm138);
			}
			if (iSlow178 || iSlow180 || iSlow182 || iSlow184 || iSlow186 || iSlow188 || iSlow198) {
				fTempPerm140 = (float)input8[i];
			}
			if (iSlow178 || iSlow180 || iSlow182 || iSlow184) {
				fTempPerm141 = faustpower<2>(fTempPerm140);
			}
			if (iSlow178) {
				fRec100[0] = ((fConst7 * fRec100[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow143 * sqrtf(((faustpower<2>((fTempPerm137 + 1.0f)) + fTempPerm139) + fTempPerm141)))))));
				fTempPerm142 = (fSlow177 * fRec100[0]);
			}
			output50[i] = (FAUSTFLOAT)fTempPerm142;
			if (iSlow180 || iSlow184 || iSlow186 || iSlow188) {
				fTempPerm143 = faustpower<2>(fTempPerm137);
			}
			if (iSlow180 || iSlow184) {
				fTempPerm144 = (fTempPerm141 + fTempPerm143);
			}
			if (iSlow180) {
				fRec101[0] = ((fConst7 * fRec101[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((faustpower<2>((fTempPerm138 + 1.0f)) + fTempPerm144)))))));
				fTempPerm145 = (fSlow179 * fRec101[0]);
			}
			output51[i] = (FAUSTFLOAT)fTempPerm145;
			if (iSlow182) {
				fRec102[0] = ((fConst7 * fRec102[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((faustpower<2>((fTempPerm137 + -1.0f)) + (fTempPerm139 + fTempPerm141))))))));
				fTempPerm146 = (fSlow181 * fRec102[0]);
			}
			output52[i] = (FAUSTFLOAT)fTempPerm146;
			if (iSlow184) {
				fRec103[0] = ((fConst7 * fRec103[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm144 + faustpower<2>((fTempPerm138 + -1.0f)))))))));
				fTempPerm147 = (fSlow183 * fRec103[0]);
			}
			output53[i] = (FAUSTFLOAT)fTempPerm147;
			if (iSlow186 || iSlow188) {
				fTempPerm148 = (fTempPerm139 + fTempPerm143);
			}
			if (iSlow186) {
				fRec104[0] = ((fConst7 * fRec104[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow163 * sqrtf((fTempPerm148 + faustpower<2>((fTempPerm140 + 1.0f)))))))));
				fTempPerm149 = (fSlow185 * fRec104[0]);
			}
			output54[i] = (FAUSTFLOAT)fTempPerm149;
			if (iSlow188) {
				fRec105[0] = ((fConst7 * fRec105[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow164 * sqrtf((fTempPerm148 + faustpower<2>((fTempPerm140 + -1.0f)))))))));
				fTempPerm150 = (fSlow187 * fRec105[0]);
			}
			output55[i] = (FAUSTFLOAT)fTempPerm150;
			if (iSlow200 || iSlow202 || iSlow204 || iSlow206 || iSlow208 || iSlow210) {
				fTempPerm151 = (float)input9[i];
				fTempPerm152 = (float)input10[i];
			}
			if (iSlow200 || iSlow204 || iSlow208 || iSlow210) {
				fTempPerm153 = faustpower<2>(fTempPerm152);
			}
			if (iSlow200 || iSlow202 || iSlow204 || iSlow206 || iSlow208 || iSlow210) {
				fTempPerm154 = (float)input11[i];
			}
			if (iSlow200 || iSlow202 || iSlow204 || iSlow206) {
				fTempPerm155 = faustpower<2>(fTempPerm154);
			}
			if (iSlow200) {
				fRec106[0] = ((fConst7 * fRec106[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow143 * sqrtf(((faustpower<2>((fTempPerm151 + 1.0f)) + fTempPerm153) + fTempPerm155)))))));
				fTempPerm156 = (fSlow199 * fRec106[0]);
			}
			output56[i] = (FAUSTFLOAT)fTempPerm156;
			if (iSlow202 || iSlow206 || iSlow208 || iSlow210) {
				fTempPerm157 = faustpower<2>(fTempPerm151);
			}
			if (iSlow202 || iSlow206) {
				fTempPerm158 = (fTempPerm155 + fTempPerm157);
			}
			if (iSlow202) {
				fRec107[0] = ((fConst7 * fRec107[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((faustpower<2>((fTempPerm152 + 1.0f)) + fTempPerm158)))))));
				fTempPerm159 = (fSlow201 * fRec107[0]);
			}
			output57[i] = (FAUSTFLOAT)fTempPerm159;
			if (iSlow204) {
				fRec108[0] = ((fConst7 * fRec108[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((faustpower<2>((fTempPerm151 + -1.0f)) + (fTempPerm153 + fTempPerm155))))))));
				fTempPerm160 = (fSlow203 * fRec108[0]);
			}
			output58[i] = (FAUSTFLOAT)fTempPerm160;
			if (iSlow206) {
				fRec109[0] = ((fConst7 * fRec109[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm158 + faustpower<2>((fTempPerm152 + -1.0f)))))))));
				fTempPerm161 = (fSlow205 * fRec109[0]);
			}
			output59[i] = (FAUSTFLOAT)fTempPerm161;
			if (iSlow208 || iSlow210) {
				fTempPerm162 = (fTempPerm153 + fTempPerm157);
			}
			if (iSlow208) {
				fRec110[0] = ((fConst7 * fRec110[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow163 * sqrtf((fTempPerm162 + faustpower<2>((fTempPerm154 + 1.0f)))))))));
				fTempPerm163 = (fSlow207 * fRec110[0]);
			}
			output60[i] = (FAUSTFLOAT)fTempPerm163;
			if (iSlow210) {
				fRec111[0] = ((fConst7 * fRec111[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow164 * sqrtf((fTempPerm162 + faustpower<2>((fTempPerm154 + -1.0f)))))))));
				fTempPerm164 = (fSlow209 * fRec111[0]);
			}
			output61[i] = (FAUSTFLOAT)fTempPerm164;
			if (iSlow212 || iSlow214 || iSlow216 || iSlow218 || iSlow220 || iSlow222 || iSlow224) {
				fTempPerm165 = (float)input12[i];
			}
			if (iSlow212 || iSlow214 || iSlow216 || iSlow218 || iSlow220 || iSlow222 || iSlow226) {
				fTempPerm166 = (float)input13[i];
			}
			if (iSlow212 || iSlow216 || iSlow220 || iSlow222) {
				fTempPerm167 = faustpower<2>(fTempPerm166);
			}
			if (iSlow212 || iSlow214 || iSlow216 || iSlow218 || iSlow220 || iSlow222 || iSlow228) {
				fTempPerm168 = (float)input14[i];
			}
			if (iSlow212 || iSlow214 || iSlow216 || iSlow218) {
				fTempPerm169 = faustpower<2>(fTempPerm168);
			}
			if (iSlow212) {
				fRec112[0] = ((fConst7 * fRec112[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow143 * sqrtf(((faustpower<2>((fTempPerm165 + 1.0f)) + fTempPerm167) + fTempPerm169)))))));
				fTempPerm170 = (fSlow211 * fRec112[0]);
			}
			output62[i] = (FAUSTFLOAT)fTempPerm170;
			if (iSlow214 || iSlow218 || iSlow220 || iSlow222) {
				fTempPerm171 = faustpower<2>(fTempPerm165);
			}
			if (iSlow214 || iSlow218) {
				fTempPerm172 = (fTempPerm169 + fTempPerm171);
			}
			if (iSlow214) {
				fRec113[0] = ((fConst7 * fRec113[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((faustpower<2>((fTempPerm166 + 1.0f)) + fTempPerm172)))))));
				fTempPerm173 = (fSlow213 * fRec113[0]);
			}
			output63[i] = (FAUSTFLOAT)fTempPerm173;
			if (iSlow216) {
				fRec114[0] = ((fConst7 * fRec114[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((faustpower<2>((fTempPerm165 + -1.0f)) + (fTempPerm167 + fTempPerm169))))))));
				fTempPerm174 = (fSlow215 * fRec114[0]);
			}
			output64[i] = (FAUSTFLOAT)fTempPerm174;
			if (iSlow218) {
				fRec115[0] = ((fConst7 * fRec115[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm172 + faustpower<2>((fTempPerm166 + -1.0f)))))))));
				fTempPerm175 = (fSlow217 * fRec115[0]);
			}
			output65[i] = (FAUSTFLOAT)fTempPerm175;
			if (iSlow220 || iSlow222) {
				fTempPerm176 = (fTempPerm167 + fTempPerm171);
			}
			if (iSlow220) {
				fRec116[0] = ((fConst7 * fRec116[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow163 * sqrtf((fTempPerm176 + faustpower<2>((fTempPerm168 + 1.0f)))))))));
				fTempPerm177 = (fSlow219 * fRec116[0]);
			}
			output66[i] = (FAUSTFLOAT)fTempPerm177;
			if (iSlow222) {
				fRec117[0] = ((fConst7 * fRec117[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow164 * sqrtf((fTempPerm176 + faustpower<2>((fTempPerm168 + -1.0f)))))))));
				fTempPerm178 = (fSlow221 * fRec117[0]);
			}
			output67[i] = (FAUSTFLOAT)fTempPerm178;
			if (iSlow230 || iSlow232 || iSlow234 || iSlow236 || iSlow238 || iSlow240) {
				fTempPerm179 = (float)input15[i];
				fTempPerm180 = (float)input16[i];
			}
			if (iSlow230 || iSlow234 || iSlow238 || iSlow240) {
				fTempPerm181 = faustpower<2>(fTempPerm180);
			}
			if (iSlow230 || iSlow232 || iSlow234 || iSlow236 || iSlow238 || iSlow240) {
				fTempPerm182 = (float)input17[i];
			}
			if (iSlow230 || iSlow232 || iSlow234 || iSlow236) {
				fTempPerm183 = faustpower<2>(fTempPerm182);
			}
			if (iSlow230) {
				fRec118[0] = ((fConst7 * fRec118[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow143 * sqrtf(((faustpower<2>((fTempPerm179 + 1.0f)) + fTempPerm181) + fTempPerm183)))))));
				fTempPerm184 = (fSlow229 * fRec118[0]);
			}
			output68[i] = (FAUSTFLOAT)fTempPerm184;
			if (iSlow232 || iSlow236 || iSlow238 || iSlow240) {
				fTempPerm185 = faustpower<2>(fTempPerm179);
			}
			if (iSlow232 || iSlow236) {
				fTempPerm186 = (fTempPerm183 + fTempPerm185);
			}
			if (iSlow232) {
				fRec119[0] = ((fConst7 * fRec119[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow160 * sqrtf((faustpower<2>((fTempPerm180 + 1.0f)) + fTempPerm186)))))));
				fTempPerm187 = (fSlow231 * fRec119[0]);
			}
			output69[i] = (FAUSTFLOAT)fTempPerm187;
			if (iSlow234) {
				fRec120[0] = ((fConst7 * fRec120[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow161 * sqrtf((faustpower<2>((fTempPerm179 + -1.0f)) + (fTempPerm181 + fTempPerm183))))))));
				fTempPerm188 = (fSlow233 * fRec120[0]);
			}
			output70[i] = (FAUSTFLOAT)fTempPerm188;
			if (iSlow236) {
				fRec121[0] = ((fConst7 * fRec121[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow162 * sqrtf((fTempPerm186 + faustpower<2>((fTempPerm180 + -1.0f)))))))));
				fTempPerm189 = (fSlow235 * fRec121[0]);
			}
			output71[i] = (FAUSTFLOAT)fTempPerm189;
			if (iSlow238 || iSlow240) {
				fTempPerm190 = (fTempPerm181 + fTempPerm185);
			}
			if (iSlow238) {
				fRec122[0] = ((fConst7 * fRec122[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow163 * sqrtf((fTempPerm190 + faustpower<2>((fTempPerm182 + 1.0f)))))))));
				fTempPerm191 = (fSlow237 * fRec122[0]);
			}
			output72[i] = (FAUSTFLOAT)fTempPerm191;
			if (iSlow240) {
				fRec123[0] = ((fConst7 * fRec123[1]) + (fConst8 * max(0.0f, (1.0f - (fSlow164 * sqrtf((fTempPerm190 + faustpower<2>((fTempPerm182 + -1.0f)))))))));
				fTempPerm192 = (fSlow239 * fRec123[0]);
			}
			output73[i] = (FAUSTFLOAT)fTempPerm192;
			if (iSlow39) {
				fTempPerm193 = (fSlow38 * min((float)1, max((float)0, (0 - (0.5f * (fTempPerm36 - (fTempPerm30 + 1.0f)))))));
			}
			output74[i] = (FAUSTFLOAT)fTempPerm193;
			if (iSlow46) {
				fTempPerm194 = (fSlow45 * min((float)1, max((float)0, (0 - (0.5f * (fTempPerm38 - (fTempPerm32 + 1.0f)))))));
			}
			output75[i] = (FAUSTFLOAT)fTempPerm194;
			if (iSlow53) {
				fTempPerm195 = (fSlow52 * min((float)1, max((float)0, (0 - (0.5f * (fTempPerm40 - (fTempPerm34 + 1.0f)))))));
			}
			output76[i] = (FAUSTFLOAT)fTempPerm195;
			if (iSlow41) {
				fTempPerm196 = (fSlow40 * min((float)1, max((float)0, (1.0f - (fTempPerm30 + fTempPerm36)))));
			}
			output77[i] = (FAUSTFLOAT)fTempPerm196;
			if (iSlow48) {
				fTempPerm197 = (fSlow47 * min((float)1, max((float)0, (1.0f - (fTempPerm32 + fTempPerm38)))));
			}
			output78[i] = (FAUSTFLOAT)fTempPerm197;
			if (iSlow55) {
				fTempPerm198 = (fSlow54 * min((float)1, max((float)0, (1.0f - (fTempPerm34 + fTempPerm40)))));
			}
			output79[i] = (FAUSTFLOAT)fTempPerm198;
			if (iSlow190) {
				fTempPerm199 = (fSlow189 * min((float)1, (1.6666666666666665f * max((float)0, ((0.5f * (1.0f - fTempPerm137)) + -0.20000000000000001f)))));
			}
			output80[i] = (FAUSTFLOAT)fTempPerm199;
			if (iSlow194) {
				fTempPerm200 = (fSlow193 * min((float)1, (1.6666666666666665f * max((float)0, ((0.5f * (1.0f - fTempPerm138)) + -0.20000000000000001f)))));
			}
			output81[i] = (FAUSTFLOAT)fTempPerm200;
			if (iSlow192) {
				fTempPerm201 = (fSlow191 * fTempPerm137);
			}
			output82[i] = (FAUSTFLOAT)fTempPerm201;
			if (iSlow196) {
				fTempPerm202 = (fSlow195 * fTempPerm138);
			}
			output83[i] = (FAUSTFLOAT)fTempPerm202;
			if (iSlow198) {
				fTempPerm203 = (fSlow197 * fTempPerm140);
			}
			output84[i] = (FAUSTFLOAT)fTempPerm203;
			if (iSlow224) {
				fTempPerm204 = (fSlow223 * fTempPerm165);
			}
			output85[i] = (FAUSTFLOAT)fTempPerm204;
			if (iSlow226) {
				fTempPerm205 = (fSlow225 * fTempPerm166);
			}
			output86[i] = (FAUSTFLOAT)fTempPerm205;
			if (iSlow228) {
				fTempPerm206 = (fSlow227 * fTempPerm168);
			}
			output87[i] = (FAUSTFLOAT)fTempPerm206;
			if (iSlow155) {
				fTempPerm207 = (fSlow154 * fTempPerm109);
			}
			output88[i] = (FAUSTFLOAT)fTempPerm207;
			if (iSlow157) {
				fTempPerm208 = (fSlow156 * fTempPerm110);
			}
			output89[i] = (FAUSTFLOAT)fTempPerm208;
			if (iSlow159) {
				fTempPerm209 = (fSlow158 * fTempPerm112);
			}
			output90[i] = (FAUSTFLOAT)fTempPerm209;
			if (iSlow123) {
				fTempPerm210 = (fSlow241 * min((float)1, (fSlow114 * max((float)0, (sqrtf(fTempPerm105) - fSlow124)))));
			}
			output91[i] = (FAUSTFLOAT)fTempPerm210;
			// post processing
			if (iSlow240) {
				fRec123[1] = fRec123[0];
			}
			if (iSlow238) {
				fRec122[1] = fRec122[0];
			}
			if (iSlow236) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow234) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow232) {
				fRec119[1] = fRec119[0];
			}
			if (iSlow230) {
				fRec118[1] = fRec118[0];
			}
			if (iSlow222) {
				fRec117[1] = fRec117[0];
			}
			if (iSlow220) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow218) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow216) {
				fRec114[1] = fRec114[0];
			}
			if (iSlow214) {
				fRec113[1] = fRec113[0];
			}
			if (iSlow212) {
				fRec112[1] = fRec112[0];
			}
			if (iSlow210) {
				fRec111[1] = fRec111[0];
			}
			if (iSlow208) {
				fRec110[1] = fRec110[0];
			}
			if (iSlow206) {
				fRec109[1] = fRec109[0];
			}
			if (iSlow204) {
				fRec108[1] = fRec108[0];
			}
			if (iSlow202) {
				fRec107[1] = fRec107[0];
			}
			if (iSlow200) {
				fRec106[1] = fRec106[0];
			}
			if (iSlow188) {
				fRec105[1] = fRec105[0];
			}
			if (iSlow186) {
				fRec104[1] = fRec104[0];
			}
			if (iSlow184) {
				fRec103[1] = fRec103[0];
			}
			if (iSlow182) {
				fRec102[1] = fRec102[0];
			}
			if (iSlow180) {
				fRec101[1] = fRec101[0];
			}
			if (iSlow178) {
				fRec100[1] = fRec100[0];
			}
			if (iSlow176) {
				fRec99[1] = fRec99[0];
			}
			if (iSlow174) {
				fRec98[1] = fRec98[0];
			}
			if (iSlow172) {
				fRec97[1] = fRec97[0];
			}
			if (iSlow170) {
				fRec96[1] = fRec96[0];
			}
			if (iSlow168) {
				fRec95[1] = fRec95[0];
			}
			if (iSlow166) {
				fRec94[1] = fRec94[0];
			}
			if (iSlow153) {
				fRec93[1] = fRec93[0];
			}
			if (iSlow151) {
				fRec92[1] = fRec92[0];
			}
			if (iSlow149) {
				fRec91[1] = fRec91[0];
			}
			if (iSlow147) {
				fRec90[1] = fRec90[0];
			}
			if (iSlow145) {
				fRec89[1] = fRec89[0];
			}
			if (iSlow142) {
				fRec88[1] = fRec88[0];
			}
			if (iSlow121) {
				fRec86[1] = fRec86[0];
				fRec87[1] = fRec87[0];
			}
			if (iSlow140) {
				fRec84[1] = fRec84[0];
				fRec85[1] = fRec85[0];
			}
			if (iSlow133) {
				fRec82[1] = fRec82[0];
				fRec83[1] = fRec83[0];
			}
			if (iSlow119) {
				fRec80[1] = fRec80[0];
				fRec81[1] = fRec81[0];
			}
			if (iSlow138) {
				fRec78[1] = fRec78[0];
				fRec79[1] = fRec79[0];
			}
			if (iSlow131) {
				fRec76[1] = fRec76[0];
				fRec77[1] = fRec77[0];
			}
			if (iSlow117) {
				fRec74[1] = fRec74[0];
				fRec75[1] = fRec75[0];
			}
			if (iSlow135) {
				fRec71[1] = fRec71[0];
				fRec72[1] = fRec72[0];
			}
			if (iSlow135 || iSlow138 || iSlow140 || iSlow121) {
				fRec73[1] = fRec73[0];
			}
			if (iSlow128) {
				fRec68[1] = fRec68[0];
				fRec69[1] = fRec69[0];
			}
			if (iSlow128 || iSlow131 || iSlow133 || iSlow121 || iSlow123) {
				fRec70[1] = fRec70[0];
			}
			if (iSlow113) {
				fRec65[1] = fRec65[0];
				fRec66[1] = fRec66[0];
			}
			if (iSlow113 || iSlow117 || iSlow119 || iSlow121 || iSlow123) {
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

/************************** BEGIN faust-poly-engine.h **************************/
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

/************************** BEGIN audio.h **************************/
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
/**************************  END  audio.h **************************/
/************************** BEGIN APIUI.h **************************/
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

/************************** BEGIN ValueConverter.h **************************/
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
        LinearValueConverter(umin, umax, log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
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
            LinearValueConverter(umin, umax, exp(fmin), exp(fmax))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::exp(x)); }

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
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/

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

        virtual void openTabBox(const char* label)          { pushLabel(label); }
        virtual void openHorizontalBox(const char* label)   { pushLabel(label); }
        virtual void openVerticalBox(const char* label)     { pushLabel(label); }
        virtual void closeBox()                             { popLabel(); }

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
/**************************  END  APIUI.h **************************/
/************************** BEGIN MidiUI.h **************************/
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

/************************** BEGIN MetaDataUI.h **************************/
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

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <assert.h>


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
         * Limitation : long words exceeding n are not cut
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
                                    key="";
                                    value="";
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
                        std::cerr << "ERROR unrecognized state " << state << std::endl;
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions
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
/************************** BEGIN midi.h **************************/
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

/*************************************
 A time-stamped short MIDI message
**************************************/

#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

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

/*
 A class to decode NRPN and RPN messages, adapted from JUCE forum message: https://forum.juce.com/t/14bit-midi-controller-support/11517
*/

class MidiNRPN
{
    
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


/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/

class midi_handler : public midi {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
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
    
        // To be used in polling mode
        virtual int getMessages(std::vector<MIDIMessage>* message) { return 0; }
    
    
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
            } else if (type == MIDI_START) {
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
/**************************  END  midi.h **************************/

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

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data is handled.
 ******************************************************************************/

class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        int rangeChan() { return (((fChan < 0) || (fChan > 15)) ? 0 : fChan); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = -1):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/*****************************************************************************
 * Base class for MIDI aware UI items
 ******************************************************************************/

class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
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
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

//-----------
// MIDI sync
//-----------

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
    
        uiMidiProgChange(midi* midi_out, int pgm, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fPgm(pgm)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->progChange(rangeChan(), fPgm);
            }
        }
        
};

class uiMidiChanPress : public uiMidiTimedItem
{
    private:
        
        int fPress;
  
    public:
    
        uiMidiChanPress(midi* midi_out, int press, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fPress(press)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->chanPress(rangeChan(), fPress);
            }
        }
        
};

class uiMidiCtrlChange : public uiMidiTimedItem
{
    private:
    
        int fCtrl;
        LinearValueConverter fConverter;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fCtrl(ctrl), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->ctrlChange(rangeChan(), fCtrl, fConverter.faust2ui(v));
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
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true, int chan = -1)
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
            fMidiOut->pitchWheel(rangeChan(), fConverter.faust2ui(v));
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

class uiMidiKeyOn : public uiMidiTimedItem
{

    private:
        
        int fKeyOn;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fKeyOn(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOn(rangeChan(), fKeyOn, fConverter.faust2ui(v));
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
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fKeyOff(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOff(rangeChan(), fKeyOff, fConverter.faust2ui(v));
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
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fKey(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyPress(rangeChan(), fKey, fConverter.faust2ui(v));
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

    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::map <int, std::vector<uiMidiProgChange*> > TProgChangeTable;
    typedef std::map <int, std::vector<uiMidiChanPress*> >  TChanPressTable;
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
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u %u", &num, &chan) == 2) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiHandler, num, this, zone, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiHandler, num, this, zone, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u %u", &num, &chan) == 2) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiHandler, num, this, zone, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &num) == 1) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiHandler, num, this, zone, input));
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
    
        template <typename T>
        void updateTable1(T& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                if (channel_aux == -1 || channel == channel_aux) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename T>
        void updateTable2(T& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    if (channel_aux == -1 || channel == channel_aux) {
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
            fDelete = delete_handler;
            fTimeStamp = false;
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
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == -1 || channel == channel_aux) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable2<TProgChangeTable>(fProgChangeTable, date, channel, pgm, FAUSTFLOAT(1));
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
            updateTable2<TChanPressTable>(fChanPressTable, date, channel, press, FAUSTFLOAT(1));
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
/************************** BEGIN poly-dsp.h **************************/
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

/************************** BEGIN dsp-combiner.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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
#include <string>
#include <assert.h>
#include <sstream>


// Base class and common code for binary combiners

class dsp_binary_combiner : public dsp {

    protected:

        dsp* fDSP1;
        dsp* fDSP2;

        void buildUserInterfaceAux(UI* ui_interface, const char* name)
        {
            ui_interface->openTabBox(name);
            ui_interface->openVerticalBox("DSP1");
            fDSP1->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->openVerticalBox("DSP2");
            fDSP2->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->closeBox();
        }

        FAUSTFLOAT** allocateChannels(int num, int buffer_size)
        {
            FAUSTFLOAT** channels = new FAUSTFLOAT*[num];
            for (int chan = 0; chan < num; chan++) {
                channels[chan] = new FAUSTFLOAT[buffer_size];
                memset(channels[chan], 0, sizeof(FAUSTFLOAT) * buffer_size);
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

        dsp_sequencer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), buffer_size);
        }

        virtual ~dsp_sequencer()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface, "Sequencer");
        }

        virtual dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone());
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

        dsp_parallelizer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
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
            buildUserInterfaceAux(ui_interface, "Parallelizer");
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

        dsp_splitter(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), buffer_size);
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
            buildUserInterfaceAux(ui_interface, "Splitter");
        }

        virtual dsp* clone()
        {
            return new dsp_splitter(fDSP1->clone(), fDSP2->clone());
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

        dsp_merger(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs(), buffer_size);
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), buffer_size);
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
            buildUserInterfaceAux(ui_interface, "Merge");
        }

        virtual dsp* clone()
        {
            return new dsp_merger(fDSP1->clone(), fDSP2->clone());
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

        dsp_recursiver(dsp* dsp1, dsp* dsp2):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs(), 1);
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), 1);
            fDSP2Inputs = allocateChannels(fDSP2->getNumInputs(), 1);
            fDSP2Outputs = allocateChannels(fDSP2->getNumOutputs(), 1);
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
            buildUserInterfaceAux(ui_interface, "Recursiver");
        }

        virtual dsp* clone()
        {
            return new dsp_recursiver(fDSP1->clone(), fDSP2->clone());
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

#ifndef __dsp_algebra_api__
#define __dsp_algebra_api__
// DSP algebra API
/*
 Each operation takes two DSP as parameters, returns the combined DSPs, or null if failure with an error message.
 */

static dsp* createDSPSequencer(dsp* dsp1, dsp* dsp2, std::string& error)
{
    if (dsp1->getNumOutputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error int dsp_sequencer : the number of outputs ("
                  << dsp1->getNumOutputs() << ") of A "
                  << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_sequencer(dsp1, dsp2);
    }
}

static dsp* createDSPParallelize(dsp* dsp1, dsp* dsp2, std::string& error)
{
    return new dsp_parallelizer(dsp1, dsp2);
}

static dsp* createDSPSplitter(dsp* dsp1, dsp* dsp2, std::string& error)
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
        return new dsp_sequencer(dsp1, dsp2);
    } else {
        return new dsp_splitter(dsp1, dsp2);
    }
}

static dsp* createDSPMerger(dsp* dsp1, dsp* dsp2, std::string& error)
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
        return new dsp_sequencer(dsp1, dsp2);
    } else {
        return new dsp_merger(dsp1, dsp2);
    }
}

static dsp* createDSPRecursiver(dsp* dsp1, dsp* dsp2, std::string& error)
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
        return new dsp_recursiver(dsp1, dsp2);
    }
}
#endif

#endif
/**************************  END  dsp-combiner.h **************************/
/************************** BEGIN proxy-dsp.h **************************/
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
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
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
/**************************  END  proxy-dsp.h **************************/
/************************** BEGIN JSONControl.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#define kActiveVoice      0
#define kFreeVoice        -1
#define kReleaseVoice     -2
#define kNoVoice          -3

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

// endsWith(<str>,<end>) : returns true if <str> ends with <end>

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
            if (!MapUI::endsWith(label, "/gate")
                && !MapUI::endsWith(label, "/freq")
                && !MapUI::endsWith(label, "/gain")) {

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

    int fNote;                          // Playing note actual pitch
    int fDate;                          // KeyOn date
    int fRelease;                       // Current number of samples used in release mode to detect end of note
    int fMinRelease;                    // Max of samples used in release mode to detect end of note
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
        fMinRelease = dsp->getSampleRate()/2; // One 1/2 sec used in release mode to detect end of note
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
            fRelease = fMinRelease;
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

#ifdef EMCC
#endif

class dsp_poly : public decorator_dsp, public midi, public JSONControl {

    protected:
    
    #ifdef EMCC
        MapUI fMapUI;
        std::string fJSON;
        midi_handler fMIDIHandler;
        MidiUI fMIDIUI;
    #endif
    
    public:
    
    #ifdef EMCC
        dsp_poly(dsp* dsp):decorator_dsp(dsp), fMIDIUI(&fMIDIHandler)
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
    
        // Group API
        virtual void setGroup(bool group) {}
        virtual bool getGroup() { return false; }

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

        FAUSTFLOAT mixCheckVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer)
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
    
        void mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer)
        {
            for (int i = 0; i < getNumOutputs(); i++) {
                FAUSTFLOAT* mixChannel = mixBuffer[i];
                FAUSTFLOAT* outChannel = outputBuffer[i];
                for (int j = 0; j < count; j++) {
                    mixChannel[j] += outChannel[j];
                }
            }
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
         * @param nvoices - number of polyphony voices, should be at least 1
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

            // First clear the outputs
            clearOutput(count, outputs);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fNote != kFreeVoice) {
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, outputs);
                        // Check the level to possibly set the voice in kFreeVoice again
                        voice->fRelease -= count;
                        if ((voice->fNote == kReleaseVoice)
                            && (voice->fRelease < 0)
                            && (voice->fLevel < VOICE_STOP_LEVEL)) {
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
    
        // Group API
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

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

};

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
     * @param nvoices - number of polyphony voices, should be at least 1
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
/**************************  END  poly-dsp.h **************************/
/************************** BEGIN faust-engine.h **************************/
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
/**************************  END  faust-engine.h **************************/

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
    
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
    
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
            
            if (nvoices > 0) {
                
                fPolyDSP = new mydsp2_poly(mono_dsp, nvoices, true);
                fMidiHandler.addMidiIn(fPolyDSP);
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
    
        FaustPolyEngine(dsp* mono_dsp, audio* driver = NULL, midi_handler* midi = NULL):fMidiUI(&fMidiHandler)
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
        void setVoiceParamValue(const char* address, uintptr_t voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }

        /*
         * setVoiceParamValue(id, voice, value)
         * Sets the value of the parameter associated with the id for
         * the voice. setVoiceParamValue can only be
         * used if the [style:poly] metadata is used in the Faust code.
         */
        void setVoiceParamValue(int id, uintptr_t voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(reinterpret_cast<MapUI*>(voice)->getParamAddress(id), value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code.
         */
        float getVoiceParamValue(const char* address, uintptr_t voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(address);
        }

        /*
         * getVoiceParamValue(id, voice)
         * Gets the parameter value associated with the id for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code.
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
/**************************  END  faust-poly-engine.h **************************/
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
    
    myaudio* driver2= new motion_audio(sample_rate, buffer_size, 0, false, false);
    fMotionEngine = new FaustMotionEngine(NULL,driver2);
    
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
        driver2->addControlCallback(osc_compute_callback, fMotionOSCUI);
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
