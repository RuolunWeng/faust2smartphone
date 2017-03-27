#define OSCCTRL 0
/************************************************************************
 ************************************************************************
 FAUST API Architecture File
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2014-2016 GRAME, Centre National de Creation Musicale
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

#if OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#include <math.h>
#include <cmath>

//**************************************************************
// Intrinsic
//**************************************************************

//----------------------------------------------------------
// name: "Faust Motion Library"
// version: "0.01"
//
// Code generated with Faust 0.9.96ec (http://faust.grame.fr)
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
    float 	fRec2[2];
    FAUSTFLOAT 	fslider2;
    int 	iTempPerm0;
    int 	iVec1[2];
    int 	iTempPerm1;
    float 	fConst2;
    float 	fRec3[2];
    FAUSTFLOAT 	fslider3;
    int 	iTempPerm2;
    int 	iRec0[2];
    float 	fTempPerm3;
    FAUSTFLOAT 	fbargraph0;
    FAUSTFLOAT 	fcheckbox1;
    FAUSTFLOAT 	fslider4;
    float 	fVec2[2];
    float 	fRec6[2];
    int 	iTempPerm4;
    int 	iVec3[2];
    int 	iTempPerm5;
    float 	fRec7[2];
    int 	iTempPerm6;
    int 	iRec4[2];
    float 	fTempPerm7;
    FAUSTFLOAT 	fbargraph1;
    FAUSTFLOAT 	fcheckbox2;
    FAUSTFLOAT 	fslider5;
    float 	fVec4[2];
    float 	fRec10[2];
    int 	iTempPerm8;
    int 	iVec5[2];
    int 	iTempPerm9;
    float 	fRec11[2];
    int 	iTempPerm10;
    int 	iRec8[2];
    float 	fTempPerm11;
    FAUSTFLOAT 	fbargraph2;
    FAUSTFLOAT 	fcheckbox3;
    FAUSTFLOAT 	fslider6;
    float 	fVec6[2];
    float 	fRec14[2];
    int 	iTempPerm12;
    int 	iVec7[2];
    int 	iTempPerm13;
    float 	fRec15[2];
    int 	iTempPerm14;
    int 	iRec12[2];
    float 	fTempPerm15;
    FAUSTFLOAT 	fbargraph3;
    FAUSTFLOAT 	fcheckbox4;
    FAUSTFLOAT 	fslider7;
    float 	fVec8[2];
    float 	fRec18[2];
    int 	iTempPerm16;
    int 	iVec9[2];
    int 	iTempPerm17;
    float 	fRec19[2];
    int 	iTempPerm18;
    int 	iRec16[2];
    float 	fTempPerm19;
    FAUSTFLOAT 	fbargraph4;
    FAUSTFLOAT 	fcheckbox5;
    FAUSTFLOAT 	fslider8;
    float 	fVec10[2];
    float 	fRec22[2];
    int 	iTempPerm20;
    int 	iVec11[2];
    int 	iTempPerm21;
    float 	fRec23[2];
    int 	iTempPerm22;
    int 	iRec20[2];
    float 	fTempPerm23;
    FAUSTFLOAT 	fbargraph5;
    FAUSTFLOAT 	fcheckbox6;
    FAUSTFLOAT 	fslider9;
    FAUSTFLOAT 	fslider10;
    float 	fVec12[2];
    float 	fRec24[2];
    float 	fTempPerm24;
    FAUSTFLOAT 	fbargraph6;
    FAUSTFLOAT 	fcheckbox7;
    FAUSTFLOAT 	fslider11;
    float 	fVec13[2];
    float 	fRec25[2];
    float 	fTempPerm25;
    FAUSTFLOAT 	fbargraph7;
    FAUSTFLOAT 	fcheckbox8;
    FAUSTFLOAT 	fslider12;
    float 	fVec14[2];
    float 	fRec26[2];
    float 	fTempPerm26;
    FAUSTFLOAT 	fbargraph8;
    FAUSTFLOAT 	fcheckbox9;
    FAUSTFLOAT 	fslider13;
    float 	fVec15[2];
    float 	fRec27[2];
    float 	fTempPerm27;
    FAUSTFLOAT 	fbargraph9;
    FAUSTFLOAT 	fcheckbox10;
    FAUSTFLOAT 	fslider14;
    float 	fVec16[2];
    float 	fRec28[2];
    float 	fTempPerm28;
    FAUSTFLOAT 	fbargraph10;
    FAUSTFLOAT 	fcheckbox11;
    FAUSTFLOAT 	fslider15;
    float 	fVec17[2];
    float 	fRec29[2];
    float 	fTempPerm29;
    FAUSTFLOAT 	fbargraph11;
    FAUSTFLOAT 	fcheckbox12;
    FAUSTFLOAT 	fslider16;
    FAUSTFLOAT 	fslider17;
    float 	fVec18[2];
    float 	fRec30[2];
    float 	fTempPerm30;
    FAUSTFLOAT 	fbargraph12;
    FAUSTFLOAT 	fcheckbox13;
    FAUSTFLOAT 	fslider18;
    float 	fVec19[2];
    float 	fRec31[2];
    float 	fTempPerm31;
    FAUSTFLOAT 	fbargraph13;
    FAUSTFLOAT 	fcheckbox14;
    FAUSTFLOAT 	fslider19;
    float 	fVec20[2];
    float 	fRec32[2];
    float 	fTempPerm32;
    FAUSTFLOAT 	fbargraph14;
    FAUSTFLOAT 	fcheckbox15;
    FAUSTFLOAT 	fslider20;
    float 	fVec21[2];
    float 	fRec33[2];
    float 	fTempPerm33;
    FAUSTFLOAT 	fbargraph15;
    FAUSTFLOAT 	fcheckbox16;
    FAUSTFLOAT 	fslider21;
    float 	fVec22[2];
    float 	fRec34[2];
    float 	fTempPerm34;
    FAUSTFLOAT 	fbargraph16;
    FAUSTFLOAT 	fcheckbox17;
    FAUSTFLOAT 	fslider22;
    float 	fVec23[2];
    float 	fRec35[2];
    float 	fTempPerm35;
    FAUSTFLOAT 	fbargraph17;
    FAUSTFLOAT 	fcheckbox18;
    FAUSTFLOAT 	fslider23;
    float 	fConst3;
    float 	fConst4;
    FAUSTFLOAT 	fslider24;
    FAUSTFLOAT 	fcheckbox19;
    FAUSTFLOAT 	fcheckbox20;
    FAUSTFLOAT 	fcheckbox21;
    float 	fVec24[2];
    float 	fConst5;
    float 	fRec38[2];
    FAUSTFLOAT 	fslider25;
    float 	fTempPerm36;
    float 	fConst6;
    FAUSTFLOAT 	fslider26;
    FAUSTFLOAT 	fslider27;
    float 	fTempPerm37;
    float 	fRec37[2];
    float 	fRec36[2];
    float 	fTempPerm38;
    FAUSTFLOAT 	fbargraph18;
    FAUSTFLOAT 	fcheckbox22;
    FAUSTFLOAT 	fslider28;
    FAUSTFLOAT 	fcheckbox23;
    FAUSTFLOAT 	fcheckbox24;
    float 	fVec25[2];
    float 	fRec41[2];
    float 	fTempPerm39;
    float 	fTempPerm40;
    float 	fRec40[2];
    float 	fRec39[2];
    float 	fTempPerm41;
    FAUSTFLOAT 	fbargraph19;
    FAUSTFLOAT 	fcheckbox25;
    FAUSTFLOAT 	fslider29;
    FAUSTFLOAT 	fcheckbox26;
    FAUSTFLOAT 	fcheckbox27;
    float 	fVec26[2];
    float 	fRec44[2];
    float 	fTempPerm42;
    float 	fTempPerm43;
    float 	fRec43[2];
    float 	fRec42[2];
    float 	fTempPerm44;
    FAUSTFLOAT 	fbargraph20;
    float 	fTempPerm45;
    float 	fTempPerm46;
    float 	fRec46[2];
    float 	fRec45[2];
    float 	fTempPerm47;
    FAUSTFLOAT 	fbargraph21;
    float 	fTempPerm48;
    float 	fTempPerm49;
    float 	fRec48[2];
    float 	fRec47[2];
    float 	fTempPerm50;
    FAUSTFLOAT 	fbargraph22;
    float 	fTempPerm51;
    float 	fTempPerm52;
    float 	fRec50[2];
    float 	fRec49[2];
    float 	fTempPerm53;
    FAUSTFLOAT 	fbargraph23;
    float 	fTempPerm54;
    float 	fTempPerm55;
    float 	fRec52[2];
    float 	fRec51[2];
    float 	fTempPerm56;
    FAUSTFLOAT 	fbargraph24;
    float 	fTempPerm57;
    float 	fTempPerm58;
    float 	fRec54[2];
    float 	fRec53[2];
    float 	fTempPerm59;
    FAUSTFLOAT 	fbargraph25;
    float 	fTempPerm60;
    float 	fTempPerm61;
    float 	fRec56[2];
    float 	fRec55[2];
    float 	fTempPerm62;
    FAUSTFLOAT 	fbargraph26;
    float 	fTempPerm63;
    float 	fTempPerm64;
    float 	fRec58[2];
    float 	fRec57[2];
    float 	fTempPerm65;
    FAUSTFLOAT 	fbargraph27;
    FAUSTFLOAT 	fcheckbox28;
    FAUSTFLOAT 	fslider30;
    FAUSTFLOAT 	fslider31;
    FAUSTFLOAT 	fcheckbox29;
    FAUSTFLOAT 	fcheckbox30;
    FAUSTFLOAT 	fcheckbox31;
    float 	fRec61[2];
    FAUSTFLOAT 	fslider32;
    float 	fTempPerm66;
    FAUSTFLOAT 	fslider33;
    FAUSTFLOAT 	fslider34;
    float 	fTempPerm67;
    float 	fRec60[2];
    float 	fRec59[2];
    float 	fTempPerm68;
    FAUSTFLOAT 	fbargraph28;
    FAUSTFLOAT 	fcheckbox32;
    FAUSTFLOAT 	fslider35;
    FAUSTFLOAT 	fcheckbox33;
    FAUSTFLOAT 	fcheckbox34;
    float 	fRec64[2];
    float 	fTempPerm69;
    float 	fTempPerm70;
    float 	fRec63[2];
    float 	fRec62[2];
    float 	fTempPerm71;
    FAUSTFLOAT 	fbargraph29;
    FAUSTFLOAT 	fcheckbox35;
    FAUSTFLOAT 	fslider36;
    FAUSTFLOAT 	fcheckbox36;
    FAUSTFLOAT 	fcheckbox37;
    float 	fRec67[2];
    float 	fTempPerm72;
    float 	fTempPerm73;
    float 	fRec66[2];
    float 	fRec65[2];
    float 	fTempPerm74;
    FAUSTFLOAT 	fbargraph30;
    float 	fTempPerm75;
    float 	fTempPerm76;
    float 	fRec69[2];
    float 	fRec68[2];
    float 	fTempPerm77;
    FAUSTFLOAT 	fbargraph31;
    float 	fTempPerm78;
    float 	fTempPerm79;
    float 	fRec71[2];
    float 	fRec70[2];
    float 	fTempPerm80;
    FAUSTFLOAT 	fbargraph32;
    float 	fTempPerm81;
    float 	fTempPerm82;
    float 	fRec73[2];
    float 	fRec72[2];
    float 	fTempPerm83;
    FAUSTFLOAT 	fbargraph33;
    float 	fTempPerm84;
    float 	fTempPerm85;
    float 	fRec75[2];
    float 	fRec74[2];
    float 	fTempPerm86;
    FAUSTFLOAT 	fbargraph34;
    float 	fTempPerm87;
    float 	fTempPerm88;
    float 	fRec77[2];
    float 	fRec76[2];
    float 	fTempPerm89;
    FAUSTFLOAT 	fbargraph35;
    float 	fTempPerm90;
    float 	fTempPerm91;
    float 	fRec79[2];
    float 	fRec78[2];
    float 	fTempPerm92;
    FAUSTFLOAT 	fbargraph36;
    float 	fTempPerm93;
    float 	fTempPerm94;
    float 	fRec81[2];
    float 	fRec80[2];
    float 	fTempPerm95;
    FAUSTFLOAT 	fbargraph37;
    int fSamplingFreq;
    
public:
    virtual void metadata(Meta* m) {
        m->declare("analyzers.lib/name", "Faust Analyzer Library");
        m->declare("analyzers.lib/version", "0.0");
        m->declare("basics.lib/name", "Faust Basic Element Library");
        m->declare("basics.lib/version", "0.0");
        m->declare("compressors.lib/name", "Faust Compressor Effect Library");
        m->declare("compressors.lib/version", "0.0");
        m->declare("delays.lib/name", "Faust Delay Library");
        m->declare("delays.lib/version", "0.0");
        m->declare("name", "Faust Motion Library");
        m->declare("version", "0.01");
        m->declare("envelopes.lib/name", "Faust Envelope Library");
        m->declare("envelopes.lib/version", "0.0");
        m->declare("envelopes.lib/author", "GRAME");
        m->declare("envelopes.lib/copyright", "GRAME");
        m->declare("envelopes.lib/license", "LGPL with exception");
        m->declare("filters.lib/name", "Faust Filters Library");
        m->declare("filters.lib/version", "0.0");
        m->declare("hoa.lib/name", "High Order Ambisonics library");
        m->declare("hoa.lib/author", "Pierre Guillot");
        m->declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
        m->declare("maths.lib/name", "Faust Math Library");
        m->declare("maths.lib/version", "2.0");
        m->declare("maths.lib/author", "GRAME");
        m->declare("maths.lib/copyright", "GRAME");
        m->declare("maths.lib/license", "LGPL with exception");
        m->declare("misceffects.lib/name", "Faust Math Library");
        m->declare("misceffects.lib/version", "2.0");
        m->declare("oscillators.lib/name", "Faust Oscillator Library");
        m->declare("oscillators.lib/version", "0.0");
        m->declare("noises.lib/name", "Faust Noise Generator Library");
        m->declare("noises.lib/version", "0.0");
        m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
        m->declare("phaflangers.lib/version", "0.0");
        m->declare("reverbs.lib/name", "Faust Reverb Library");
        m->declare("reverbs.lib/version", "0.0");
        m->declare("routes.lib/name", "Faust Signal Routing Library");
        m->declare("routes.lib/version", "0.0");
        m->declare("spats.lib/name", "Faust Spatialization Library");
        m->declare("spats.lib/version", "0.0");
        m->declare("signals.lib/name", "Faust Signal Routing Library");
        m->declare("signals.lib/version", "0.0");
        m->declare("synths.lib/name", "Faust Synthesizer Library");
        m->declare("synths.lib/version", "0.0");
        m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
        m->declare("vaeffects.lib/version", "0.0");
    }
    
    virtual int getNumInputs() { return 0; }
    virtual int getNumOutputs() { return 38; }
    static void classInit(int samplingFreq) {
    }
    virtual void instanceConstants(int samplingFreq) {
        fSamplingFreq = samplingFreq;
        fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
        fConst1 = (3.1415927f / fConst0);
        iTempPerm0 = 0;
        iTempPerm1 = 0;
        fConst2 = (1.0f / fConst0);
        iTempPerm2 = 0;
        fTempPerm3 = 0;
        iTempPerm4 = 0;
        iTempPerm5 = 0;
        iTempPerm6 = 0;
        fTempPerm7 = 0;
        iTempPerm8 = 0;
        iTempPerm9 = 0;
        iTempPerm10 = 0;
        fTempPerm11 = 0;
        iTempPerm12 = 0;
        iTempPerm13 = 0;
        iTempPerm14 = 0;
        fTempPerm15 = 0;
        iTempPerm16 = 0;
        iTempPerm17 = 0;
        iTempPerm18 = 0;
        fTempPerm19 = 0;
        iTempPerm20 = 0;
        iTempPerm21 = 0;
        iTempPerm22 = 0;
        fTempPerm23 = 0;
        fTempPerm24 = 0;
        fTempPerm25 = 0;
        fTempPerm26 = 0;
        fTempPerm27 = 0;
        fTempPerm28 = 0;
        fTempPerm29 = 0;
        fTempPerm30 = 0;
        fTempPerm31 = 0;
        fTempPerm32 = 0;
        fTempPerm33 = 0;
        fTempPerm34 = 0;
        fTempPerm35 = 0;
        fConst3 = (37.699112f / fConst0);
        fConst4 = (1.0f / (fConst3 + 1));
        fConst5 = (1 - fConst3);
        fTempPerm36 = 0;
        fConst6 = (1e+03f / fConst0);
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
        fTempPerm48 = 0;
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
    }
    virtual void instanceResetUserInterface() {
        fcheckbox0 = 0.0;
        fslider0 = 5e+01f;
        fslider1 = 0.0f;
        fslider2 = 0.75f;
        fslider3 = 1.4e+02f;
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
        fslider11 = 0.0f;
        fcheckbox8 = 0.0;
        fslider12 = 0.0f;
        fcheckbox9 = 0.0;
        fslider13 = 0.0f;
        fcheckbox10 = 0.0;
        fslider14 = 0.0f;
        fcheckbox11 = 0.0;
        fslider15 = 0.0f;
        fcheckbox12 = 0.0;
        fslider16 = 0.08f;
        fslider17 = 0.0f;
        fcheckbox13 = 0.0;
        fslider18 = 0.0f;
        fcheckbox14 = 0.0;
        fslider19 = 0.0f;
        fcheckbox15 = 0.0;
        fslider20 = 0.0f;
        fcheckbox16 = 0.0;
        fslider21 = 0.0f;
        fcheckbox17 = 0.0;
        fslider22 = 0.0f;
        fcheckbox18 = 0.0;
        fslider23 = 1.35f;
        fslider24 = 0.0f;
        fcheckbox19 = 0.0;
        fcheckbox20 = 0.0;
        fcheckbox21 = 0.0;
        fslider25 = 0.1f;
        fslider26 = 1e+01f;
        fslider27 = 1e+01f;
        fcheckbox22 = 0.0;
        fslider28 = 0.0f;
        fcheckbox23 = 0.0;
        fcheckbox24 = 0.0;
        fcheckbox25 = 0.0;
        fslider29 = 0.0f;
        fcheckbox26 = 0.0;
        fcheckbox27 = 0.0;
        fcheckbox28 = 0.0;
        fslider30 = 0.79f;
        fslider31 = 0.0f;
        fcheckbox29 = 0.0;
        fcheckbox30 = 0.0;
        fcheckbox31 = 0.0;
        fslider32 = 0.01f;
        fslider33 = 2.5e+02f;
        fslider34 = 1.5e+02f;
        fcheckbox32 = 0.0;
        fslider35 = 0.0f;
        fcheckbox33 = 0.0;
        fcheckbox34 = 0.0;
        fcheckbox35 = 0.0;
        fslider36 = 0.0f;
        fcheckbox36 = 0.0;
        fcheckbox37 = 0.0;
    }
    virtual void instanceClear() {
        for (int i=0; i<2; i++) fVec0[i] = 0;
        for (int i=0; i<2; i++) fRec2[i] = 0;
        for (int i=0; i<2; i++) iVec1[i] = 0;
        for (int i=0; i<2; i++) fRec3[i] = 0;
        for (int i=0; i<2; i++) iRec0[i] = 0;
        for (int i=0; i<2; i++) fVec2[i] = 0;
        for (int i=0; i<2; i++) fRec6[i] = 0;
        for (int i=0; i<2; i++) iVec3[i] = 0;
        for (int i=0; i<2; i++) fRec7[i] = 0;
        for (int i=0; i<2; i++) iRec4[i] = 0;
        for (int i=0; i<2; i++) fVec4[i] = 0;
        for (int i=0; i<2; i++) fRec10[i] = 0;
        for (int i=0; i<2; i++) iVec5[i] = 0;
        for (int i=0; i<2; i++) fRec11[i] = 0;
        for (int i=0; i<2; i++) iRec8[i] = 0;
        for (int i=0; i<2; i++) fVec6[i] = 0;
        for (int i=0; i<2; i++) fRec14[i] = 0;
        for (int i=0; i<2; i++) iVec7[i] = 0;
        for (int i=0; i<2; i++) fRec15[i] = 0;
        for (int i=0; i<2; i++) iRec12[i] = 0;
        for (int i=0; i<2; i++) fVec8[i] = 0;
        for (int i=0; i<2; i++) fRec18[i] = 0;
        for (int i=0; i<2; i++) iVec9[i] = 0;
        for (int i=0; i<2; i++) fRec19[i] = 0;
        for (int i=0; i<2; i++) iRec16[i] = 0;
        for (int i=0; i<2; i++) fVec10[i] = 0;
        for (int i=0; i<2; i++) fRec22[i] = 0;
        for (int i=0; i<2; i++) iVec11[i] = 0;
        for (int i=0; i<2; i++) fRec23[i] = 0;
        for (int i=0; i<2; i++) iRec20[i] = 0;
        for (int i=0; i<2; i++) fVec12[i] = 0;
        for (int i=0; i<2; i++) fRec24[i] = 0;
        for (int i=0; i<2; i++) fVec13[i] = 0;
        for (int i=0; i<2; i++) fRec25[i] = 0;
        for (int i=0; i<2; i++) fVec14[i] = 0;
        for (int i=0; i<2; i++) fRec26[i] = 0;
        for (int i=0; i<2; i++) fVec15[i] = 0;
        for (int i=0; i<2; i++) fRec27[i] = 0;
        for (int i=0; i<2; i++) fVec16[i] = 0;
        for (int i=0; i<2; i++) fRec28[i] = 0;
        for (int i=0; i<2; i++) fVec17[i] = 0;
        for (int i=0; i<2; i++) fRec29[i] = 0;
        for (int i=0; i<2; i++) fVec18[i] = 0;
        for (int i=0; i<2; i++) fRec30[i] = 0;
        for (int i=0; i<2; i++) fVec19[i] = 0;
        for (int i=0; i<2; i++) fRec31[i] = 0;
        for (int i=0; i<2; i++) fVec20[i] = 0;
        for (int i=0; i<2; i++) fRec32[i] = 0;
        for (int i=0; i<2; i++) fVec21[i] = 0;
        for (int i=0; i<2; i++) fRec33[i] = 0;
        for (int i=0; i<2; i++) fVec22[i] = 0;
        for (int i=0; i<2; i++) fRec34[i] = 0;
        for (int i=0; i<2; i++) fVec23[i] = 0;
        for (int i=0; i<2; i++) fRec35[i] = 0;
        for (int i=0; i<2; i++) fVec24[i] = 0;
        for (int i=0; i<2; i++) fRec38[i] = 0;
        for (int i=0; i<2; i++) fRec37[i] = 0;
        for (int i=0; i<2; i++) fRec36[i] = 0;
        for (int i=0; i<2; i++) fVec25[i] = 0;
        for (int i=0; i<2; i++) fRec41[i] = 0;
        for (int i=0; i<2; i++) fRec40[i] = 0;
        for (int i=0; i<2; i++) fRec39[i] = 0;
        for (int i=0; i<2; i++) fVec26[i] = 0;
        for (int i=0; i<2; i++) fRec44[i] = 0;
        for (int i=0; i<2; i++) fRec43[i] = 0;
        for (int i=0; i<2; i++) fRec42[i] = 0;
        for (int i=0; i<2; i++) fRec46[i] = 0;
        for (int i=0; i<2; i++) fRec45[i] = 0;
        for (int i=0; i<2; i++) fRec48[i] = 0;
        for (int i=0; i<2; i++) fRec47[i] = 0;
        for (int i=0; i<2; i++) fRec50[i] = 0;
        for (int i=0; i<2; i++) fRec49[i] = 0;
        for (int i=0; i<2; i++) fRec52[i] = 0;
        for (int i=0; i<2; i++) fRec51[i] = 0;
        for (int i=0; i<2; i++) fRec54[i] = 0;
        for (int i=0; i<2; i++) fRec53[i] = 0;
        for (int i=0; i<2; i++) fRec56[i] = 0;
        for (int i=0; i<2; i++) fRec55[i] = 0;
        for (int i=0; i<2; i++) fRec58[i] = 0;
        for (int i=0; i<2; i++) fRec57[i] = 0;
        for (int i=0; i<2; i++) fRec61[i] = 0;
        for (int i=0; i<2; i++) fRec60[i] = 0;
        for (int i=0; i<2; i++) fRec59[i] = 0;
        for (int i=0; i<2; i++) fRec64[i] = 0;
        for (int i=0; i<2; i++) fRec63[i] = 0;
        for (int i=0; i<2; i++) fRec62[i] = 0;
        for (int i=0; i<2; i++) fRec67[i] = 0;
        for (int i=0; i<2; i++) fRec66[i] = 0;
        for (int i=0; i<2; i++) fRec65[i] = 0;
        for (int i=0; i<2; i++) fRec69[i] = 0;
        for (int i=0; i<2; i++) fRec68[i] = 0;
        for (int i=0; i<2; i++) fRec71[i] = 0;
        for (int i=0; i<2; i++) fRec70[i] = 0;
        for (int i=0; i<2; i++) fRec73[i] = 0;
        for (int i=0; i<2; i++) fRec72[i] = 0;
        for (int i=0; i<2; i++) fRec75[i] = 0;
        for (int i=0; i<2; i++) fRec74[i] = 0;
        for (int i=0; i<2; i++) fRec77[i] = 0;
        for (int i=0; i<2; i++) fRec76[i] = 0;
        for (int i=0; i<2; i++) fRec79[i] = 0;
        for (int i=0; i<2; i++) fRec78[i] = 0;
        for (int i=0; i<2; i++) fRec81[i] = 0;
        for (int i=0; i<2; i++) fRec80[i] = 0;
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
        ui_interface->addHorizontalBargraph("Maxn", &fbargraph24, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Maxp", &fbargraph21, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Maxpn", &fbargraph18, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mayn", &fbargraph25, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mayp", &fbargraph22, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Maypn", &fbargraph19, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mazn", &fbargraph26, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mazp", &fbargraph23, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mazpn", &fbargraph20, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgxn", &fbargraph34, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgxp", &fbargraph31, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgxpn", &fbargraph28, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgyn", &fbargraph35, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgyp", &fbargraph32, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgypn", &fbargraph29, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgzn", &fbargraph36, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgzp", &fbargraph33, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mgzpn", &fbargraph30, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mixn", &fbargraph9, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mixp", &fbargraph6, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Miyn", &fbargraph10, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Miyp", &fbargraph7, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mizn", &fbargraph11, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mizp", &fbargraph8, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mpixn", &fbargraph15, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mpixp", &fbargraph12, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mpiyn", &fbargraph16, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mpiyp", &fbargraph13, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mpizn", &fbargraph17, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mpizp", &fbargraph14, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Msxn", &fbargraph3, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Msxp", &fbargraph0, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Msyn", &fbargraph4, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Msyp", &fbargraph1, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mszn", &fbargraph5, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mszp", &fbargraph2, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mtotalaccel", &fbargraph27, 0.0f, 1.0f);
        ui_interface->addHorizontalBargraph("Mtotalgyro", &fbargraph37, 0.0f, 1.0f);
        ui_interface->declare(&fslider24, "acc", "0 0 -30 0 30");
        ui_interface->declare(&fslider24, "hidden", "1");
        ui_interface->addHorizontalSlider("acc_x", &fslider24, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->declare(&fslider28, "acc", "1 0 -30 0 30");
        ui_interface->declare(&fslider28, "hidden", "1");
        ui_interface->addHorizontalSlider("acc_y", &fslider28, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->declare(&fslider29, "acc", "2 0 -30 0 30");
        ui_interface->declare(&fslider29, "hidden", "1");
        ui_interface->addHorizontalSlider("acc_z", &fslider29, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->declare(&fslider3, "hidden", "1");
        ui_interface->declare(&fslider3, "osc", "antirebon 0 500");
        ui_interface->declare(&fslider3, "unit", "ms");
        ui_interface->addHorizontalSlider("antirebon", &fslider3, 1.4e+02f, 0.0f, 5e+02f, 1.0f);
        ui_interface->addCheckButton("axnOn", &fcheckbox20);
        ui_interface->addCheckButton("axpOn", &fcheckbox19);
        ui_interface->addCheckButton("axpnOn", &fcheckbox18);
        ui_interface->addCheckButton("aynOn", &fcheckbox24);
        ui_interface->addCheckButton("aypOn", &fcheckbox23);
        ui_interface->addCheckButton("aypnOn", &fcheckbox22);
        ui_interface->addCheckButton("aznOn", &fcheckbox27);
        ui_interface->addCheckButton("azpOn", &fcheckbox26);
        ui_interface->addCheckButton("azpnOn", &fcheckbox25);
        ui_interface->declare(&fslider31, "gyr", "0 0 -35 0 35");
        ui_interface->declare(&fslider31, "hidden", "1");
        ui_interface->addHorizontalSlider("gx", &fslider31, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("gxnOn", &fcheckbox31);
        ui_interface->addCheckButton("gxpOn", &fcheckbox30);
        ui_interface->addCheckButton("gxpnOn", &fcheckbox28);
        ui_interface->declare(&fslider35, "gyr", "1 0 -35 0 35");
        ui_interface->declare(&fslider35, "hidden", "1");
        ui_interface->addHorizontalSlider("gy", &fslider35, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("gynOn", &fcheckbox33);
        ui_interface->addCheckButton("gypOn", &fcheckbox34);
        ui_interface->addCheckButton("gypnOn", &fcheckbox32);
        ui_interface->declare(&fslider36, "gyr", "2 0 -35 0 35");
        ui_interface->declare(&fslider36, "hidden", "1");
        ui_interface->addHorizontalSlider("gz", &fslider36, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("gznOn", &fcheckbox36);
        ui_interface->addCheckButton("gzpOn", &fcheckbox37);
        ui_interface->addCheckButton("gzpnOn", &fcheckbox35);
        ui_interface->declare(&fslider0, "hidden", "1");
        ui_interface->addHorizontalSlider("hp", &fslider0, 5e+01f, 1.0f, 5e+01f, 0.01f);
        ui_interface->declare(&fslider13, "acc", "0 1 -10 0 10");
        ui_interface->declare(&fslider13, "hidden", "1");
        ui_interface->addHorizontalSlider("ixn", &fslider13, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("ixnOn", &fcheckbox9);
        ui_interface->declare(&fslider10, "acc", "0 0 -10 0 10");
        ui_interface->declare(&fslider10, "hidden", "1");
        ui_interface->addHorizontalSlider("ixp", &fslider10, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("ixpOn", &fcheckbox6);
        ui_interface->declare(&fslider14, "acc", "1 1 -10 0 10");
        ui_interface->declare(&fslider14, "hidden", "1");
        ui_interface->addHorizontalSlider("iyn", &fslider14, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("iynOn", &fcheckbox10);
        ui_interface->declare(&fslider11, "acc", "1 0 -10 0 10");
        ui_interface->declare(&fslider11, "hidden", "1");
        ui_interface->addHorizontalSlider("iyp", &fslider11, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("iypOn", &fcheckbox7);
        ui_interface->declare(&fslider15, "acc", "2 1 -10 0 10");
        ui_interface->declare(&fslider15, "hidden", "1");
        ui_interface->addHorizontalSlider("izn", &fslider15, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("iznOn", &fcheckbox11);
        ui_interface->declare(&fslider12, "acc", "2 0 -10 0 10");
        ui_interface->declare(&fslider12, "hidden", "1");
        ui_interface->addHorizontalSlider("izp", &fslider12, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("izpOn", &fcheckbox8);
        ui_interface->declare(&fslider9, "hidden", "1");
        ui_interface->addHorizontalSlider("lp", &fslider9, 1.5f, 0.1f, 2e+01f, 0.01f);
        ui_interface->declare(&fslider16, "hidden", "1");
        ui_interface->addHorizontalSlider("osfproj", &fslider16, 0.08f, 0.0f, 0.33f, 0.01f);
        ui_interface->declare(&fslider20, "acc", "0 1 -10 0 10");
        ui_interface->declare(&fslider20, "hidden", "1");
        ui_interface->addHorizontalSlider("pixn", &fslider20, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("pixnOn", &fcheckbox15);
        ui_interface->declare(&fslider17, "acc", "0 0 -10 0 10");
        ui_interface->declare(&fslider17, "hidden", "1");
        ui_interface->addHorizontalSlider("pixp", &fslider17, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("pixpOn", &fcheckbox12);
        ui_interface->declare(&fslider21, "acc", "1 1 -10 0 10");
        ui_interface->declare(&fslider21, "hidden", "1");
        ui_interface->addHorizontalSlider("piyn", &fslider21, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("piynOn", &fcheckbox16);
        ui_interface->declare(&fslider18, "acc", "1 0 -10 0 10");
        ui_interface->declare(&fslider18, "hidden", "1");
        ui_interface->addHorizontalSlider("piyp", &fslider18, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("piypOn", &fcheckbox13);
        ui_interface->declare(&fslider22, "acc", "2 1 -10 0 10");
        ui_interface->declare(&fslider22, "hidden", "1");
        ui_interface->addHorizontalSlider("pizn", &fslider22, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("piznOn", &fcheckbox17);
        ui_interface->declare(&fslider19, "acc", "2 0 -10 0 10");
        ui_interface->declare(&fslider19, "hidden", "1");
        ui_interface->addHorizontalSlider("pizp", &fslider19, 0.0f, -1.0f, 1.0f, 0.001f);
        ui_interface->addCheckButton("pizpOn", &fcheckbox14);
        ui_interface->declare(&fslider2, "hidden", "1");
        ui_interface->declare(&fslider2, "osc", "shok_thr 0.1 3");
        ui_interface->addHorizontalSlider("shok_thr", &fslider2, 0.75f, 0.1f, 3.0f, 0.01f);
        ui_interface->declare(&fslider6, "acc", "0 1 -30 0 30");
        ui_interface->declare(&fslider6, "hidden", "1");
        ui_interface->addHorizontalSlider("sxn", &fslider6, 0.0f, -3.0f, 3.0f, 0.0001f);
        ui_interface->addCheckButton("sxnOn", &fcheckbox3);
        ui_interface->declare(&fslider1, "acc", "0 0 -30 0 30");
        ui_interface->declare(&fslider1, "hidden", "1");
        ui_interface->addHorizontalSlider("sxp", &fslider1, 0.0f, -3.0f, 3.0f, 0.0001f);
        ui_interface->addCheckButton("sxpOn", &fcheckbox0);
        ui_interface->declare(&fslider7, "acc", "1 1 -30 0 30");
        ui_interface->declare(&fslider7, "hidden", "1");
        ui_interface->addHorizontalSlider("syn", &fslider7, 0.0f, -3.0f, 3.0f, 0.0001f);
        ui_interface->addCheckButton("synOn", &fcheckbox4);
        ui_interface->declare(&fslider4, "acc", "1 0 -30 0 30");
        ui_interface->declare(&fslider4, "hidden", "1");
        ui_interface->addHorizontalSlider("syp", &fslider4, 0.0f, -3.0f, 3.0f, 0.0001f);
        ui_interface->addCheckButton("sypOn", &fcheckbox1);
        ui_interface->declare(&fslider8, "acc", "2 1 -30 0 30");
        ui_interface->declare(&fslider8, "hidden", "1");
        ui_interface->addHorizontalSlider("szn", &fslider8, 0.0f, -3.0f, 3.0f, 0.0001f);
        ui_interface->addCheckButton("sznOn", &fcheckbox5);
        ui_interface->declare(&fslider5, "acc", "2 0 -30 0 30");
        ui_interface->declare(&fslider5, "hidden", "1");
        ui_interface->addHorizontalSlider("szp", &fslider5, 0.0f, -3.0f, 3.0f, 0.0001f);
        ui_interface->addCheckButton("szpOn", &fcheckbox2);
        ui_interface->declare(&fslider26, "hidden", "1");
        ui_interface->declare(&fslider26, "osc", "tacc_envdown 0 5000");
        ui_interface->addHorizontalSlider("tacc_down", &fslider26, 1e+01f, 0.0f, 5e+03f, 1.0f);
        ui_interface->declare(&fslider23, "hidden", "1");
        ui_interface->declare(&fslider23, "osc", "tacc_gain 0 5");
        ui_interface->addHorizontalSlider("tacc_gain", &fslider23, 1.35f, 0.0f, 5.0f, 0.01f);
        ui_interface->declare(&fslider25, "hidden", "1");
        ui_interface->declare(&fslider25, "osc", "tacc_thr 0 1");
        ui_interface->addHorizontalSlider("tacc_thr", &fslider25, 0.1f, 0.0f, 1.0f, 0.01f);
        ui_interface->declare(&fslider27, "hidden", "1");
        ui_interface->declare(&fslider27, "osc", "tacc_envup 0 5000");
        ui_interface->addHorizontalSlider("tacc_up", &fslider27, 1e+01f, 0.0f, 5e+03f, 1.0f);
        ui_interface->declare(&fslider33, "hidden", "1");
        ui_interface->declare(&fslider33, "osc", "tgyr_envdown 0 5000");
        ui_interface->addHorizontalSlider("tgyr_down", &fslider33, 2.5e+02f, 0.0f, 5e+03f, 1.0f);
        ui_interface->declare(&fslider30, "hidden", "1");
        ui_interface->addHorizontalSlider("tgyr_gain", &fslider30, 0.79f, 0.0f, 5.0f, 0.01f);
        ui_interface->declare(&fslider32, "hidden", "1");
        ui_interface->addHorizontalSlider("tgyr_thr", &fslider32, 0.01f, 0.0f, 1.0f, 0.001f);
        ui_interface->declare(&fslider34, "hidden", "1");
        ui_interface->declare(&fslider34, "osc", "tgyr_envup 0 5000");
        ui_interface->addHorizontalSlider("tgyr_up", &fslider34, 1.5e+02f, 0.0f, 5e+03f, 1.0f);
        ui_interface->addCheckButton("totalaccelOn", &fcheckbox21);
        ui_interface->addCheckButton("totalgyroOn", &fcheckbox29);
        ui_interface->closeBox();
    }
    virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
        //zone1
        //zone2
        float 	fSlow0 = float(fcheckbox0);
        int 	iSlow1 = (fSlow0 > 0.0f);
        float 	fSlow2 = tanf((fConst1 * float(fslider0)));
        float 	fSlow3 = (1.0f / fSlow2);
        float 	fSlow4 = (fSlow3 + 1);
        float 	fSlow5 = (1.0f / fSlow4);
        float 	fSlow6 = max((float)0, float(fslider1));
        float 	fSlow7 = (fSlow6 / fSlow2);
        float 	fSlow8 = (0 - fSlow3);
        float 	fSlow9 = (0 - ((1 - fSlow3) / fSlow4));
        float 	fSlow10 = float(fslider2);
        float 	fSlow11 = float(fslider3);
        float 	fSlow12 = float(fcheckbox1);
        int 	iSlow13 = (fSlow12 > 0.0f);
        float 	fSlow14 = max((float)0, float(fslider4));
        float 	fSlow15 = (fSlow14 / fSlow2);
        float 	fSlow16 = float(fcheckbox2);
        int 	iSlow17 = (fSlow16 > 0.0f);
        float 	fSlow18 = max((float)0, float(fslider5));
        float 	fSlow19 = (fSlow18 / fSlow2);
        float 	fSlow20 = float(fcheckbox3);
        int 	iSlow21 = (fSlow20 > 0.0f);
        float 	fSlow22 = max((float)0, float(fslider6));
        float 	fSlow23 = (fSlow22 / fSlow2);
        float 	fSlow24 = float(fcheckbox4);
        int 	iSlow25 = (fSlow24 > 0.0f);
        float 	fSlow26 = max((float)0, float(fslider7));
        float 	fSlow27 = (fSlow26 / fSlow2);
        float 	fSlow28 = float(fcheckbox5);
        int 	iSlow29 = (fSlow28 > 0.0f);
        float 	fSlow30 = max((float)0, float(fslider8));
        float 	fSlow31 = (fSlow30 / fSlow2);
        float 	fSlow32 = float(fcheckbox6);
        int 	iSlow33 = (fSlow32 > 0.0f);
        float 	fSlow34 = (1.0f / tanf((fConst1 * float(fslider9))));
        float 	fSlow35 = (fSlow34 + 1);
        float 	fSlow36 = (1.0f / fSlow35);
        float 	fSlow37 = max((float)0, float(fslider10));
        float 	fSlow38 = (0 - ((1 - fSlow34) / fSlow35));
        float 	fSlow39 = float(fcheckbox7);
        int 	iSlow40 = (fSlow39 > 0.0f);
        float 	fSlow41 = max((float)0, float(fslider11));
        float 	fSlow42 = float(fcheckbox8);
        int 	iSlow43 = (fSlow42 > 0.0f);
        float 	fSlow44 = max((float)0, float(fslider12));
        float 	fSlow45 = float(fcheckbox9);
        int 	iSlow46 = (fSlow45 > 0.0f);
        float 	fSlow47 = max((float)0, float(fslider13));
        float 	fSlow48 = float(fcheckbox10);
        int 	iSlow49 = (fSlow48 > 0.0f);
        float 	fSlow50 = max((float)0, float(fslider14));
        float 	fSlow51 = float(fcheckbox11);
        int 	iSlow52 = (fSlow51 > 0.0f);
        float 	fSlow53 = max((float)0, float(fslider15));
        float 	fSlow54 = float(fcheckbox12);
        int 	iSlow55 = (fSlow54 > 0.0f);
        float 	fSlow56 = float(fslider16);
        float 	fSlow57 = (fSlow56 + 1);
        float 	fSlow58 = float(fslider17);
        float 	fSlow59 = float(fcheckbox13);
        int 	iSlow60 = (fSlow59 > 0.0f);
        float 	fSlow61 = float(fslider18);
        float 	fSlow62 = float(fcheckbox14);
        int 	iSlow63 = (fSlow62 > 0.0f);
        float 	fSlow64 = float(fslider19);
        float 	fSlow65 = float(fcheckbox15);
        int 	iSlow66 = (fSlow65 > 0.0f);
        float 	fSlow67 = float(fslider20);
        float 	fSlow68 = float(fcheckbox16);
        int 	iSlow69 = (fSlow68 > 0.0f);
        float 	fSlow70 = float(fslider21);
        float 	fSlow71 = float(fcheckbox17);
        int 	iSlow72 = (fSlow71 > 0.0f);
        float 	fSlow73 = float(fslider22);
        float 	fSlow74 = float(fcheckbox18);
        int 	iSlow75 = (fSlow74 > 0.0f);
        float 	fSlow76 = float(fslider23);
        float 	fSlow77 = float(fslider24);
        float 	fSlow78 = float(fcheckbox19);
        int 	iSlow79 = (fSlow78 > 0.0f);
        float 	fSlow80 = float(fcheckbox20);
        int 	iSlow81 = (fSlow80 > 0.0f);
        float 	fSlow82 = float(fcheckbox21);
        int 	iSlow83 = (fSlow82 > 0.0f);
        float 	fSlow84 = float(fslider25);
        float 	fSlow85 = expf((0 - (fConst6 / float(fslider26))));
        float 	fSlow86 = expf((0 - (fConst6 / float(fslider27))));
        float 	fSlow87 = float(fcheckbox22);
        int 	iSlow88 = (fSlow87 > 0.0f);
        float 	fSlow89 = float(fslider28);
        float 	fSlow90 = float(fcheckbox23);
        int 	iSlow91 = (fSlow90 > 0.0f);
        float 	fSlow92 = float(fcheckbox24);
        int 	iSlow93 = (fSlow92 > 0.0f);
        float 	fSlow94 = float(fcheckbox25);
        int 	iSlow95 = (fSlow94 > 0.0f);
        float 	fSlow96 = float(fslider29);
        float 	fSlow97 = float(fcheckbox26);
        int 	iSlow98 = (fSlow97 > 0.0f);
        float 	fSlow99 = float(fcheckbox27);
        int 	iSlow100 = (fSlow99 > 0.0f);
        float 	fSlow101 = float(fcheckbox28);
        int 	iSlow102 = (fSlow101 > 0.0f);
        float 	fSlow103 = float(fslider30);
        float 	fSlow104 = (0.001f * float(fslider31));
        float 	fSlow105 = float(fcheckbox29);
        int 	iSlow106 = (fSlow105 > 0.0f);
        float 	fSlow107 = float(fcheckbox30);
        int 	iSlow108 = (fSlow107 > 0.0f);
        float 	fSlow109 = float(fcheckbox31);
        int 	iSlow110 = (fSlow109 > 0.0f);
        float 	fSlow111 = float(fslider32);
        float 	fSlow112 = expf((0 - (fConst6 / float(fslider33))));
        float 	fSlow113 = expf((0 - (fConst6 / float(fslider34))));
        float 	fSlow114 = float(fcheckbox32);
        int 	iSlow115 = (fSlow114 > 0.0f);
        float 	fSlow116 = (0.001f * float(fslider35));
        float 	fSlow117 = float(fcheckbox33);
        int 	iSlow118 = (fSlow117 > 0.0f);
        float 	fSlow119 = float(fcheckbox34);
        int 	iSlow120 = (fSlow119 > 0.0f);
        float 	fSlow121 = float(fcheckbox35);
        int 	iSlow122 = (fSlow121 > 0.0f);
        float 	fSlow123 = (0.001f * float(fslider36));
        float 	fSlow124 = float(fcheckbox36);
        int 	iSlow125 = (fSlow124 > 0.0f);
        float 	fSlow126 = float(fcheckbox37);
        int 	iSlow127 = (fSlow126 > 0.0f);
        //zone2b
        //zone3
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
        //LoopGraphScalar
        for (int i=0; i<count; i++) {
            if (iSlow1) {
                fVec0[0] = fSlow6;
                fRec2[0] = ((fSlow5 * (fSlow7 + (fSlow8 * fVec0[1]))) + (fSlow9 * fRec2[1]));
                iTempPerm0 = (fRec2[0] > fSlow10);
                iVec1[0] = iTempPerm0;
                iTempPerm1 = ((int(iRec0[1]))?(iVec1[0] > iVec1[1]):1);
                fRec3[0] = ((fConst2 + fRec3[1]) * iTempPerm1);
                iTempPerm2 = (iTempPerm1 * ((1000 * fRec3[0]) < fSlow11));
                iRec0[0] = (iTempPerm2 == 0);
                int 	iRec1 = iTempPerm2;
                fTempPerm3 = (fSlow0 * iRec1);
            }
            fbargraph0 = fTempPerm3;
            output0[i] = (FAUSTFLOAT)fbargraph0;
            if (iSlow13) {
                fVec2[0] = fSlow14;
                fRec6[0] = ((fSlow5 * (fSlow15 + (fSlow8 * fVec2[1]))) + (fSlow9 * fRec6[1]));
                iTempPerm4 = (fRec6[0] > fSlow10);
                iVec3[0] = iTempPerm4;
                iTempPerm5 = ((int(iRec4[1]))?(iVec3[0] > iVec3[1]):1);
                fRec7[0] = ((fConst2 + fRec7[1]) * iTempPerm5);
                iTempPerm6 = (iTempPerm5 * ((1000 * fRec7[0]) < fSlow11));
                iRec4[0] = (iTempPerm6 == 0);
                int 	iRec5 = iTempPerm6;
                fTempPerm7 = (fSlow12 * iRec5);
            }
            fbargraph1 = fTempPerm7;
            output1[i] = (FAUSTFLOAT)fbargraph1;
            if (iSlow17) {
                fVec4[0] = fSlow18;
                fRec10[0] = ((fSlow5 * (fSlow19 + (fSlow8 * fVec4[1]))) + (fSlow9 * fRec10[1]));
                iTempPerm8 = (fRec10[0] > fSlow10);
                iVec5[0] = iTempPerm8;
                iTempPerm9 = ((int(iRec8[1]))?(iVec5[0] > iVec5[1]):1);
                fRec11[0] = ((fConst2 + fRec11[1]) * iTempPerm9);
                iTempPerm10 = (iTempPerm9 * ((1000 * fRec11[0]) < fSlow11));
                iRec8[0] = (iTempPerm10 == 0);
                int 	iRec9 = iTempPerm10;
                fTempPerm11 = (fSlow16 * iRec9);
            }
            fbargraph2 = fTempPerm11;
            output2[i] = (FAUSTFLOAT)fbargraph2;
            if (iSlow21) {
                fVec6[0] = fSlow22;
                fRec14[0] = ((fSlow5 * (fSlow23 + (fSlow8 * fVec6[1]))) + (fSlow9 * fRec14[1]));
                iTempPerm12 = (fRec14[0] > fSlow10);
                iVec7[0] = iTempPerm12;
                iTempPerm13 = ((int(iRec12[1]))?(iVec7[0] > iVec7[1]):1);
                fRec15[0] = ((fConst2 + fRec15[1]) * iTempPerm13);
                iTempPerm14 = (iTempPerm13 * ((1000 * fRec15[0]) < fSlow11));
                iRec12[0] = (iTempPerm14 == 0);
                int 	iRec13 = iTempPerm14;
                fTempPerm15 = (fSlow20 * iRec13);
            }
            fbargraph3 = fTempPerm15;
            output3[i] = (FAUSTFLOAT)fbargraph3;
            if (iSlow25) {
                fVec8[0] = fSlow26;
                fRec18[0] = ((fSlow5 * (fSlow27 + (fSlow8 * fVec8[1]))) + (fSlow9 * fRec18[1]));
                iTempPerm16 = (fRec18[0] > fSlow10);
                iVec9[0] = iTempPerm16;
                iTempPerm17 = ((int(iRec16[1]))?(iVec9[0] > iVec9[1]):1);
                fRec19[0] = ((fConst2 + fRec19[1]) * iTempPerm17);
                iTempPerm18 = (iTempPerm17 * ((1000 * fRec19[0]) < fSlow11));
                iRec16[0] = (iTempPerm18 == 0);
                int 	iRec17 = iTempPerm18;
                fTempPerm19 = (fSlow24 * iRec17);
            }
            fbargraph4 = fTempPerm19;
            output4[i] = (FAUSTFLOAT)fbargraph4;
            if (iSlow29) {
                fVec10[0] = fSlow30;
                fRec22[0] = ((fSlow5 * (fSlow31 + (fSlow8 * fVec10[1]))) + (fSlow9 * fRec22[1]));
                iTempPerm20 = (fRec22[0] > fSlow10);
                iVec11[0] = iTempPerm20;
                iTempPerm21 = ((int(iRec20[1]))?(iVec11[0] > iVec11[1]):1);
                fRec23[0] = ((fConst2 + fRec23[1]) * iTempPerm21);
                iTempPerm22 = (iTempPerm21 * ((1000 * fRec23[0]) < fSlow11));
                iRec20[0] = (iTempPerm22 == 0);
                int 	iRec21 = iTempPerm22;
                fTempPerm23 = (fSlow28 * iRec21);
            }
            fbargraph5 = fTempPerm23;
            output5[i] = (FAUSTFLOAT)fbargraph5;
            if (iSlow33) {
                fVec12[0] = fSlow37;
                fRec24[0] = ((fSlow36 * (fSlow37 + fVec12[1])) + (fSlow38 * fRec24[1]));
                fTempPerm24 = (fSlow32 * min((float)1, max((float)0, fRec24[0])));
            }
            fbargraph6 = fTempPerm24;
            output6[i] = (FAUSTFLOAT)fbargraph6;
            if (iSlow40) {
                fVec13[0] = fSlow41;
                fRec25[0] = ((fSlow36 * (fSlow41 + fVec13[1])) + (fSlow38 * fRec25[1]));
                fTempPerm25 = (fSlow39 * min((float)1, max((float)0, fRec25[0])));
            }
            fbargraph7 = fTempPerm25;
            output7[i] = (FAUSTFLOAT)fbargraph7;
            if (iSlow43) {
                fVec14[0] = fSlow44;
                fRec26[0] = ((fSlow36 * (fSlow44 + fVec14[1])) + (fSlow38 * fRec26[1]));
                fTempPerm26 = (fSlow42 * min((float)1, max((float)0, fRec26[0])));
            }
            fbargraph8 = fTempPerm26;
            output8[i] = (FAUSTFLOAT)fbargraph8;
            if (iSlow46) {
                fVec15[0] = fSlow47;
                fRec27[0] = ((fSlow36 * (fSlow47 + fVec15[1])) + (fSlow38 * fRec27[1]));
                fTempPerm27 = (fSlow45 * min((float)1, max((float)0, fRec27[0])));
            }
            fbargraph9 = fTempPerm27;
            output9[i] = (FAUSTFLOAT)fbargraph9;
            if (iSlow49) {
                fVec16[0] = fSlow50;
                fRec28[0] = ((fSlow36 * (fSlow50 + fVec16[1])) + (fSlow38 * fRec28[1]));
                fTempPerm28 = (fSlow48 * min((float)1, max((float)0, fRec28[0])));
            }
            fbargraph10 = fTempPerm28;
            output10[i] = (FAUSTFLOAT)fbargraph10;
            if (iSlow52) {
                fVec17[0] = fSlow53;
                fRec29[0] = ((fSlow36 * (fSlow53 + fVec17[1])) + (fSlow38 * fRec29[1]));
                fTempPerm29 = (fSlow51 * min((float)1, max((float)0, fRec29[0])));
            }
            fbargraph11 = fTempPerm29;
            output11[i] = (FAUSTFLOAT)fbargraph11;
            if (iSlow55) {
                fVec18[0] = fSlow58;
                fRec30[0] = ((fSlow36 * (fSlow58 + fVec18[1])) + (fSlow38 * fRec30[1]));
                fTempPerm30 = (fSlow54 * min((float)1, max((float)0, (fSlow57 * max((float)0, ((0.5f * ((0.63661975f * asinf(min((float)1, max((float)-1, fRec30[0])))) + 1)) - fSlow56))))));
            }
            fbargraph12 = fTempPerm30;
            output12[i] = (FAUSTFLOAT)fbargraph12;
            if (iSlow60) {
                fVec19[0] = fSlow61;
                fRec31[0] = ((fSlow36 * (fSlow61 + fVec19[1])) + (fSlow38 * fRec31[1]));
                fTempPerm31 = (fSlow59 * min((float)1, max((float)0, (fSlow57 * max((float)0, ((0.5f * ((0.63661975f * asinf(min((float)1, max((float)-1, fRec31[0])))) + 1)) - fSlow56))))));
            }
            fbargraph13 = fTempPerm31;
            output13[i] = (FAUSTFLOAT)fbargraph13;
            if (iSlow63) {
                fVec20[0] = fSlow64;
                fRec32[0] = ((fSlow36 * (fSlow64 + fVec20[1])) + (fSlow38 * fRec32[1]));
                fTempPerm32 = (fSlow62 * min((float)1, max((float)0, (fSlow57 * max((float)0, ((0.5f * ((0.63661975f * asinf(min((float)1, max((float)-1, fRec32[0])))) + 1)) - fSlow56))))));
            }
            fbargraph14 = fTempPerm32;
            output14[i] = (FAUSTFLOAT)fbargraph14;
            if (iSlow66) {
                fVec21[0] = fSlow67;
                fRec33[0] = ((fSlow36 * (fSlow67 + fVec21[1])) + (fSlow38 * fRec33[1]));
                fTempPerm33 = (fSlow65 * min((float)1, max((float)0, (fSlow57 * max((float)0, ((0.5f * ((0.63661975f * asinf(min((float)1, max((float)-1, fRec33[0])))) + 1)) - fSlow56))))));
            }
            fbargraph15 = fTempPerm33;
            output15[i] = (FAUSTFLOAT)fbargraph15;
            if (iSlow69) {
                fVec22[0] = fSlow70;
                fRec34[0] = ((fSlow36 * (fSlow70 + fVec22[1])) + (fSlow38 * fRec34[1]));
                fTempPerm34 = (fSlow68 * min((float)1, max((float)0, (fSlow57 * max((float)0, ((0.5f * ((0.63661975f * asinf(min((float)1, max((float)-1, fRec34[0])))) + 1)) - fSlow56))))));
            }
            fbargraph16 = fTempPerm34;
            output16[i] = (FAUSTFLOAT)fbargraph16;
            if (iSlow72) {
                fVec23[0] = fSlow73;
                fRec35[0] = ((fSlow36 * (fSlow73 + fVec23[1])) + (fSlow38 * fRec35[1]));
                fTempPerm35 = (fSlow71 * min((float)1, max((float)0, (fSlow57 * max((float)0, ((0.5f * ((0.63661975f * asinf(min((float)1, max((float)-1, fRec35[0])))) + 1)) - fSlow56))))));
            }
            fbargraph17 = fTempPerm35;
            output17[i] = (FAUSTFLOAT)fbargraph17;
            if (iSlow75 || iSlow79 || iSlow81 || iSlow83) {
                fVec24[0] = fSlow77;
                fRec38[0] = (fConst4 * (fSlow77 + ((fConst5 * fRec38[1]) - fVec24[1])));
            }
            if (iSlow75) {
                fTempPerm36 = fabsf(min((float)1, (fSlow76 * max((float)0, (fabsf(fRec38[0]) - fSlow84)))));
                fTempPerm37 = ((int((fRec36[1] > fTempPerm36)))?fSlow85:fSlow86);
                fRec37[0] = ((fRec37[1] * fTempPerm37) + (fTempPerm36 * (1.0f - fTempPerm37)));
                fRec36[0] = fRec37[0];
                fTempPerm38 = (fSlow74 * fRec36[0]);
            }
            fbargraph18 = fTempPerm38;
            output18[i] = (FAUSTFLOAT)fbargraph18;
            if (iSlow88 || iSlow91 || iSlow93 || iSlow83) {
                fVec25[0] = fSlow89;
                fRec41[0] = (fConst4 * (fSlow89 + ((fConst5 * fRec41[1]) - fVec25[1])));
            }
            if (iSlow88) {
                fTempPerm39 = fabsf(min((float)1, (fSlow76 * max((float)0, (fabsf(fRec41[0]) - fSlow84)))));
                fTempPerm40 = ((int((fRec39[1] > fTempPerm39)))?fSlow85:fSlow86);
                fRec40[0] = ((fRec40[1] * fTempPerm40) + (fTempPerm39 * (1.0f - fTempPerm40)));
                fRec39[0] = fRec40[0];
                fTempPerm41 = (fSlow87 * fRec39[0]);
            }
            fbargraph19 = fTempPerm41;
            output19[i] = (FAUSTFLOAT)fbargraph19;
            if (iSlow95 || iSlow98 || iSlow100 || iSlow83) {
                fVec26[0] = fSlow96;
                fRec44[0] = (fConst4 * (fSlow96 + ((fConst5 * fRec44[1]) - fVec26[1])));
            }
            if (iSlow95) {
                fTempPerm42 = fabsf(min((float)1, (fSlow76 * max((float)0, (fabsf(fRec44[0]) - fSlow84)))));
                fTempPerm43 = ((int((fRec42[1] > fTempPerm42)))?fSlow85:fSlow86);
                fRec43[0] = ((fRec43[1] * fTempPerm43) + (fTempPerm42 * (1.0f - fTempPerm43)));
                fRec42[0] = fRec43[0];
                fTempPerm44 = (fSlow94 * fRec42[0]);
            }
            fbargraph20 = fTempPerm44;
            output20[i] = (FAUSTFLOAT)fbargraph20;
            if (iSlow79) {
                fTempPerm45 = fabsf(min((float)1, (fSlow76 * max((float)0, (fRec38[0] - fSlow84)))));
                fTempPerm46 = ((int((fRec45[1] > fTempPerm45)))?fSlow85:fSlow86);
                fRec46[0] = ((fRec46[1] * fTempPerm46) + (fTempPerm45 * (1.0f - fTempPerm46)));
                fRec45[0] = fRec46[0];
                fTempPerm47 = (fSlow78 * fRec45[0]);
            }
            fbargraph21 = fTempPerm47;
            output21[i] = (FAUSTFLOAT)fbargraph21;
            if (iSlow91) {
                fTempPerm48 = fabsf(min((float)1, (fSlow76 * max((float)0, (fRec41[0] - fSlow84)))));
                fTempPerm49 = ((int((fRec47[1] > fTempPerm48)))?fSlow85:fSlow86);
                fRec48[0] = ((fRec48[1] * fTempPerm49) + (fTempPerm48 * (1.0f - fTempPerm49)));
                fRec47[0] = fRec48[0];
                fTempPerm50 = (fSlow90 * fRec47[0]);
            }
            fbargraph22 = fTempPerm50;
            output22[i] = (FAUSTFLOAT)fbargraph22;
            if (iSlow98) {
                fTempPerm51 = fabsf(min((float)1, (fSlow76 * max((float)0, (fRec44[0] - fSlow84)))));
                fTempPerm52 = ((int((fRec49[1] > fTempPerm51)))?fSlow85:fSlow86);
                fRec50[0] = ((fRec50[1] * fTempPerm52) + (fTempPerm51 * (1.0f - fTempPerm52)));
                fRec49[0] = fRec50[0];
                fTempPerm53 = (fSlow97 * fRec49[0]);
            }
            fbargraph23 = fTempPerm53;
            output23[i] = (FAUSTFLOAT)fbargraph23;
            if (iSlow81) {
                fTempPerm54 = fabsf(min((float)1, (fSlow76 * max((float)0, (0 - (fSlow84 + fRec38[0]))))));
                fTempPerm55 = ((int((fRec51[1] > fTempPerm54)))?fSlow85:fSlow86);
                fRec52[0] = ((fRec52[1] * fTempPerm55) + (fTempPerm54 * (1.0f - fTempPerm55)));
                fRec51[0] = fRec52[0];
                fTempPerm56 = (fSlow80 * fRec51[0]);
            }
            fbargraph24 = fTempPerm56;
            output24[i] = (FAUSTFLOAT)fbargraph24;
            if (iSlow93) {
                fTempPerm57 = fabsf(min((float)1, (fSlow76 * max((float)0, (0 - (fSlow84 + fRec41[0]))))));
                fTempPerm58 = ((int((fRec53[1] > fTempPerm57)))?fSlow85:fSlow86);
                fRec54[0] = ((fRec54[1] * fTempPerm58) + (fTempPerm57 * (1.0f - fTempPerm58)));
                fRec53[0] = fRec54[0];
                fTempPerm59 = (fSlow92 * fRec53[0]);
            }
            fbargraph25 = fTempPerm59;
            output25[i] = (FAUSTFLOAT)fbargraph25;
            if (iSlow100) {
                fTempPerm60 = fabsf(min((float)1, (fSlow76 * max((float)0, (0 - (fSlow84 + fRec44[0]))))));
                fTempPerm61 = ((int((fRec55[1] > fTempPerm60)))?fSlow85:fSlow86);
                fRec56[0] = ((fRec56[1] * fTempPerm61) + (fTempPerm60 * (1.0f - fTempPerm61)));
                fRec55[0] = fRec56[0];
                fTempPerm62 = (fSlow99 * fRec55[0]);
            }
            fbargraph26 = fTempPerm62;
            output26[i] = (FAUSTFLOAT)fbargraph26;
            if (iSlow83) {
                fTempPerm63 = fabsf(min((float)1, (fSlow76 * max((float)0, (sqrtf(((faustpower<2>(fRec38[0]) + faustpower<2>(fRec41[0])) + faustpower<2>(fRec44[0]))) - fSlow84)))));
                fTempPerm64 = ((int((fRec57[1] > fTempPerm63)))?fSlow85:fSlow86);
                fRec58[0] = ((fRec58[1] * fTempPerm64) + (fTempPerm63 * (1.0f - fTempPerm64)));
                fRec57[0] = fRec58[0];
                fTempPerm65 = (fSlow82 * fRec57[0]);
            }
            fbargraph27 = fTempPerm65;
            output27[i] = (FAUSTFLOAT)fbargraph27;
            if (iSlow106 || iSlow102 || iSlow108 || iSlow110) {
                fRec61[0] = (fSlow104 + (0.999f * fRec61[1]));
            }
            if (iSlow102) {
                fTempPerm66 = fabsf(min((float)1, (fSlow103 * max((float)0, (fabsf(fRec61[0]) - fSlow111)))));
                fTempPerm67 = ((int((fRec59[1] > fTempPerm66)))?fSlow112:fSlow113);
                fRec60[0] = ((fRec60[1] * fTempPerm67) + (fTempPerm66 * (1.0f - fTempPerm67)));
                fRec59[0] = fRec60[0];
                fTempPerm68 = (fSlow101 * fRec59[0]);
            }
            fbargraph28 = fTempPerm68;
            output28[i] = (FAUSTFLOAT)fbargraph28;
            if (iSlow118 || iSlow106 || iSlow115 || iSlow120) {
                fRec64[0] = (fSlow116 + (0.999f * fRec64[1]));
            }
            if (iSlow115) {
                fTempPerm69 = fabsf(min((float)1, (fSlow103 * max((float)0, (fabsf(fRec64[0]) - fSlow111)))));
                fTempPerm70 = ((int((fRec62[1] > fTempPerm69)))?fSlow112:fSlow113);
                fRec63[0] = ((fRec63[1] * fTempPerm70) + (fTempPerm69 * (1.0f - fTempPerm70)));
                fRec62[0] = fRec63[0];
                fTempPerm71 = (fSlow114 * fRec62[0]);
            }
            fbargraph29 = fTempPerm71;
            output29[i] = (FAUSTFLOAT)fbargraph29;
            if (iSlow125 || iSlow106 || iSlow122 || iSlow127) {
                fRec67[0] = (fSlow123 + (0.999f * fRec67[1]));
            }
            if (iSlow122) {
                fTempPerm72 = fabsf(min((float)1, (fSlow103 * max((float)0, (fabsf(fRec67[0]) - fSlow111)))));
                fTempPerm73 = ((int((fRec65[1] > fTempPerm72)))?fSlow112:fSlow113);
                fRec66[0] = ((fRec66[1] * fTempPerm73) + (fTempPerm72 * (1.0f - fTempPerm73)));
                fRec65[0] = fRec66[0];
                fTempPerm74 = (fSlow121 * fRec65[0]);
            }
            fbargraph30 = fTempPerm74;
            output30[i] = (FAUSTFLOAT)fbargraph30;
            if (iSlow108) {
                fTempPerm75 = fabsf(min((float)1, (fSlow103 * max((float)0, (fRec61[0] - fSlow111)))));
                fTempPerm76 = ((int((fRec68[1] > fTempPerm75)))?fSlow112:fSlow113);
                fRec69[0] = ((fRec69[1] * fTempPerm76) + (fTempPerm75 * (1.0f - fTempPerm76)));
                fRec68[0] = fRec69[0];
                fTempPerm77 = (fSlow107 * fRec68[0]);
            }
            fbargraph31 = fTempPerm77;
            output31[i] = (FAUSTFLOAT)fbargraph31;
            if (iSlow120) {
                fTempPerm78 = fabsf(min((float)1, (fSlow103 * max((float)0, (fRec64[0] - fSlow111)))));
                fTempPerm79 = ((int((fRec70[1] > fTempPerm78)))?fSlow112:fSlow113);
                fRec71[0] = ((fRec71[1] * fTempPerm79) + (fTempPerm78 * (1.0f - fTempPerm79)));
                fRec70[0] = fRec71[0];
                fTempPerm80 = (fSlow119 * fRec70[0]);
            }
            fbargraph32 = fTempPerm80;
            output32[i] = (FAUSTFLOAT)fbargraph32;
            if (iSlow127) {
                fTempPerm81 = fabsf(min((float)1, (fSlow103 * max((float)0, (fRec67[0] - fSlow111)))));
                fTempPerm82 = ((int((fRec72[1] > fTempPerm81)))?fSlow112:fSlow113);
                fRec73[0] = ((fRec73[1] * fTempPerm82) + (fTempPerm81 * (1.0f - fTempPerm82)));
                fRec72[0] = fRec73[0];
                fTempPerm83 = (fSlow126 * fRec72[0]);
            }
            fbargraph33 = fTempPerm83;
            output33[i] = (FAUSTFLOAT)fbargraph33;
            if (iSlow110) {
                fTempPerm84 = fabsf(min((float)1, (fSlow103 * max((float)0, (0 - (fSlow111 + fRec61[0]))))));
                fTempPerm85 = ((int((fRec74[1] > fTempPerm84)))?fSlow112:fSlow113);
                fRec75[0] = ((fRec75[1] * fTempPerm85) + (fTempPerm84 * (1.0f - fTempPerm85)));
                fRec74[0] = fRec75[0];
                fTempPerm86 = (fSlow109 * fRec74[0]);
            }
            fbargraph34 = fTempPerm86;
            output34[i] = (FAUSTFLOAT)fbargraph34;
            if (iSlow118) {
                fTempPerm87 = fabsf(min((float)1, (fSlow103 * max((float)0, (0 - (fSlow111 + fRec64[0]))))));
                fTempPerm88 = ((int((fRec76[1] > fTempPerm87)))?fSlow112:fSlow113);
                fRec77[0] = ((fRec77[1] * fTempPerm88) + (fTempPerm87 * (1.0f - fTempPerm88)));
                fRec76[0] = fRec77[0];
                fTempPerm89 = (fSlow117 * fRec76[0]);
            }
            fbargraph35 = fTempPerm89;
            output35[i] = (FAUSTFLOAT)fbargraph35;
            if (iSlow125) {
                fTempPerm90 = fabsf(min((float)1, (fSlow103 * max((float)0, (0 - (fSlow111 + fRec67[0]))))));
                fTempPerm91 = ((int((fRec78[1] > fTempPerm90)))?fSlow112:fSlow113);
                fRec79[0] = ((fRec79[1] * fTempPerm91) + (fTempPerm90 * (1.0f - fTempPerm91)));
                fRec78[0] = fRec79[0];
                fTempPerm92 = (fSlow124 * fRec78[0]);
            }
            fbargraph36 = fTempPerm92;
            output36[i] = (FAUSTFLOAT)fbargraph36;
            if (iSlow106) {
                fTempPerm93 = fabsf(min((float)1, (fSlow103 * max((float)0, (sqrtf(((faustpower<2>(fRec61[0]) + faustpower<2>(fRec64[0])) + faustpower<2>(fRec67[0]))) - fSlow111)))));
                fTempPerm94 = ((int((fRec80[1] > fTempPerm93)))?fSlow112:fSlow113);
                fRec81[0] = ((fRec81[1] * fTempPerm94) + (fTempPerm93 * (1.0f - fTempPerm94)));
                fRec80[0] = fRec81[0];
                fTempPerm95 = (fSlow105 * fRec80[0]);
            }
            fbargraph37 = fTempPerm95;
            output37[i] = (FAUSTFLOAT)fbargraph37;
            // post processing
            if (iSlow106) {
                fRec80[1] = fRec80[0];
                fRec81[1] = fRec81[0];
            }
            if (iSlow125) {
                fRec78[1] = fRec78[0];
                fRec79[1] = fRec79[0];
            }
            if (iSlow118) {
                fRec76[1] = fRec76[0];
                fRec77[1] = fRec77[0];
            }
            if (iSlow110) {
                fRec74[1] = fRec74[0];
                fRec75[1] = fRec75[0];
            }
            if (iSlow127) {
                fRec72[1] = fRec72[0];
                fRec73[1] = fRec73[0];
            }
            if (iSlow120) {
                fRec70[1] = fRec70[0];
                fRec71[1] = fRec71[0];
            }
            if (iSlow108) {
                fRec68[1] = fRec68[0];
                fRec69[1] = fRec69[0];
            }
            if (iSlow122) {
                fRec65[1] = fRec65[0];
                fRec66[1] = fRec66[0];
            }
            if (iSlow125 || iSlow106 || iSlow122 || iSlow127) {
                fRec67[1] = fRec67[0];
            }
            if (iSlow115) {
                fRec62[1] = fRec62[0];
                fRec63[1] = fRec63[0];
            }
            if (iSlow118 || iSlow106 || iSlow115 || iSlow120) {
                fRec64[1] = fRec64[0];
            }
            if (iSlow102) {
                fRec59[1] = fRec59[0];
                fRec60[1] = fRec60[0];
            }
            if (iSlow106 || iSlow102 || iSlow108 || iSlow110) {
                fRec61[1] = fRec61[0];
            }
            if (iSlow83) {
                fRec57[1] = fRec57[0];
                fRec58[1] = fRec58[0];
            }
            if (iSlow100) {
                fRec55[1] = fRec55[0];
                fRec56[1] = fRec56[0];
            }
            if (iSlow93) {
                fRec53[1] = fRec53[0];
                fRec54[1] = fRec54[0];
            }
            if (iSlow81) {
                fRec51[1] = fRec51[0];
                fRec52[1] = fRec52[0];
            }
            if (iSlow98) {
                fRec49[1] = fRec49[0];
                fRec50[1] = fRec50[0];
            }
            if (iSlow91) {
                fRec47[1] = fRec47[0];
                fRec48[1] = fRec48[0];
            }
            if (iSlow79) {
                fRec45[1] = fRec45[0];
                fRec46[1] = fRec46[0];
            }
            if (iSlow95) {
                fRec42[1] = fRec42[0];
                fRec43[1] = fRec43[0];
            }
            if (iSlow95 || iSlow98 || iSlow100 || iSlow83) {
                fRec44[1] = fRec44[0];
                fVec26[1] = fVec26[0];
            }
            if (iSlow88) {
                fRec39[1] = fRec39[0];
                fRec40[1] = fRec40[0];
            }
            if (iSlow88 || iSlow91 || iSlow93 || iSlow83) {
                fRec41[1] = fRec41[0];
                fVec25[1] = fVec25[0];
            }
            if (iSlow75) {
                fRec36[1] = fRec36[0];
                fRec37[1] = fRec37[0];
            }
            if (iSlow75 || iSlow79 || iSlow81 || iSlow83) {
                fRec38[1] = fRec38[0];
                fVec24[1] = fVec24[0];
            }
            if (iSlow72) {
                fRec35[1] = fRec35[0];
                fVec23[1] = fVec23[0];
            }
            if (iSlow69) {
                fRec34[1] = fRec34[0];
                fVec22[1] = fVec22[0];
            }
            if (iSlow66) {
                fRec33[1] = fRec33[0];
                fVec21[1] = fVec21[0];
            }
            if (iSlow63) {
                fRec32[1] = fRec32[0];
                fVec20[1] = fVec20[0];
            }
            if (iSlow60) {
                fRec31[1] = fRec31[0];
                fVec19[1] = fVec19[0];
            }
            if (iSlow55) {
                fRec30[1] = fRec30[0];
                fVec18[1] = fVec18[0];
            }
            if (iSlow52) {
                fRec29[1] = fRec29[0];
                fVec17[1] = fVec17[0];
            }
            if (iSlow49) {
                fRec28[1] = fRec28[0];
                fVec16[1] = fVec16[0];
            }
            if (iSlow46) {
                fRec27[1] = fRec27[0];
                fVec15[1] = fVec15[0];
            }
            if (iSlow43) {
                fRec26[1] = fRec26[0];
                fVec14[1] = fVec14[0];
            }
            if (iSlow40) {
                fRec25[1] = fRec25[0];
                fVec13[1] = fVec13[0];
            }
            if (iSlow33) {
                fRec24[1] = fRec24[0];
                fVec12[1] = fVec12[0];
            }
            if (iSlow29) {
                iRec20[1] = iRec20[0];
                fRec23[1] = fRec23[0];
                iVec11[1] = iVec11[0];
                fRec22[1] = fRec22[0];
                fVec10[1] = fVec10[0];
            }
            if (iSlow25) {
                iRec16[1] = iRec16[0];
                fRec19[1] = fRec19[0];
                iVec9[1] = iVec9[0];
                fRec18[1] = fRec18[0];
                fVec8[1] = fVec8[0];
            }
            if (iSlow21) {
                iRec12[1] = iRec12[0];
                fRec15[1] = fRec15[0];
                iVec7[1] = iVec7[0];
                fRec14[1] = fRec14[0];
                fVec6[1] = fVec6[0];
            }
            if (iSlow17) {
                iRec8[1] = iRec8[0];
                fRec11[1] = fRec11[0];
                iVec5[1] = iVec5[0];
                fRec10[1] = fRec10[0];
                fVec4[1] = fVec4[0];
            }
            if (iSlow13) {
                iRec4[1] = iRec4[0];
                fRec7[1] = fRec7[0];
                iVec3[1] = iVec3[0];
                fRec6[1] = fRec6[0];
                fVec2[1] = fVec2[0];
            }
            if (iSlow1) {
                iRec0[1] = iRec0[0];
                fRec3[1] = fRec3[0];
                iVec1[1] = iVec1[0];
                fRec2[1] = fRec2[0];
                fVec0[1] = fVec0[0];
            }
        }
    }
};





//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/faust-motion-engine.h"

//**************************************************************
// IOS Coreaudio
//**************************************************************

#include "faust/audio/motion-audio.h"


//**************************************************************
// Interface
//**************************************************************


#include "DspFaustMotion.h"


DspFaustMotion::DspFaustMotion(int sample_rate, int buffer_size){
	fMotionEngine = new FaustMotionEngine(new dummy_audio(sample_rate, buffer_size, 10));


//**************************************************************
// OSC TEST ALLEN
//**************************************************************

// OSC
#if OSCCTRL
    const char* argv[9];
    argv[0] = "0x00";//(char*)_name;
    argv[1] = "-xmit";
    argv[2] = "1";//transmit_value(transmit);
    argv[3] = "-desthost";
    argv[4] = "192.168.1.20";//[outputIPText cStringUsingEncoding:[NSString defaultCStringEncoding]];
    argv[5] = "-port";
    argv[6] = "5512";//[inputPortText cStringUsingEncoding:[NSString defaultCStringEncoding]];
    argv[7] = "-outport";
    argv[8] = "5513";//[outputPortText cStringUsingEncoding:[NSString defaultCStringEncoding]];
    fOSCUI = new OSCUI("0x00", 9, (char**)argv);
    fMotionEngine->buildUserInterface(fOSCUI);

#endif


}



DspFaustMotion::~DspFaustMotion(){
	delete fMotionEngine;

#if OSCCTRL
    delete fOSCUI;
#endif


}

bool DspFaustMotion::start(){

#if OSCCTRL
    fOSCUI->run();
#endif

	return fMotionEngine->start();
}

void DspFaustMotion::stop(){

#if OSCCTRL
    fOSCUI->stop();
#endif

	fMotionEngine->stop();
}


void DspFaustMotion::render(){

    
    fMotionEngine->render();
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

const char* DspFaustMotion::getParamTooltip(const char* address){
    return fMotionEngine->getParamTooltip(address);
}

const char* DspFaustMotion::getParamTooltip(int id){
    return fMotionEngine->getParamTooltip(id);
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
