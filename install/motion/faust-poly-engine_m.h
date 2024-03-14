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

#ifndef __faust_poly_engine_m__
#define __faust_poly_engine_m__


//**************************************************************
// audio DSP engine modified from faust-poly-engine.h
//**************************************************************

using namespace std;

class MyFaustPolyEngine : public FaustPolyEngine
{

public:

   MY_Meta metadata;

    MyFaustPolyEngine(dsp* mono_dsp, audio* driver = NULL) : FaustPolyEngine(mono_dsp,driver)
    {
        //init(((mono_dsp) ? mono_dsp : new mydsp()), driver, NULL);
        mono_dsp->metadata(&metadata);
    }

    virtual ~MyFaustPolyEngine()
    {
        //delete fDriver;
        //delete fFinalDSP;
    }

    float getParamStep(int p){
        return fAPIUI.getParamStep(p);
    }
    
    const char* getMeta(const char* name)
    {

        const char* value= NULL;
            for (auto& pair : metadata) {
                //std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
                
                if (strcmp(name, pair.first) == 0) value= pair.second;
                
            }
        
        return value;
        
//            if ((*metadata.find(name)) != *metadata.end()) {
//                return (*metadata.find(name)).second;
//            } else {
//
//                return NULL;
//
//            }
    }

};



#endif // __faust_poly_engine_m__
