declare name 		"SoloDemo_SHCUI_Cue";
declare version 	"3.6";
declare author 		"Allen";




process = rainGen, windGen, sinusGen :>_,(_ 
											<:attach(_,trigNextCue),
											attach(_,trigPrevCue),
											attach(_,trigInitCue),
											attach(_,trigsetRef):>/(4));



// declare connection UI
cueNum = nentry("cue [SHCUI: Cue trigCue 0 0 50 30 255 0 0 150] [touchCueManager: {0:'init'; 1:'rainGen'; 2:'windGen'; 3: 'sinusGen'}]",0,0,3,1);
trigNextCue = button("goNext [SHCUI: Cue nextCue 50 30 50 30 255 255 0 150]");
trigPrevCue = button("goPrev [SHCUI: Cue prevCue 0 30 50 30 255 255 0 150]");
trigInitCue = button("initCue [SHCUI: Cue initCue 50 0 50 30 255 255 255 150]");

trigsetRef = button("setref_rota[osc:/setRef][SHCUI: Master setRef 50 0 50 25 0 0 255 255]");

touchGate = checkbox("OnOff [SHCUI: Master checkbox 0 0 50 25 0 255 0 150]");
volume = hslider("MasterVol [SHCUI: Master hslider 0 25 100 25 0 255 255 150]",0,0,1,0.01);
param = hslider("param[motion:AmpZ]",0,0,1,0.01);


//----------------------`rain`--------------------------
// A very simple rain simulator
//
// #### Usage
//
// ```
//  rain(d,l) : _,_
// ```
//
// Where:
//
// * `d`: is the density of the rain: between 0 and 1
// * `l`: is the level (volume) of the rain: between 0 and 1
//
//----------------------------------------------------------

import("stdfaust.lib");

rain(density,level) = no.multinoise(2) : par(i, 2, drop) : par(i, 2, *(level))
	with {
		drop = _ <: @(1), (abs < density) : *;
	};

rainGen  = 	rain (
				hslider("v:rain/density [showName: rain/density]", 0.3, 0, 1, 0.01),
				param*(cueNum==1)* touchGate * volume
				//hslider("v:rain/volume", 0.5, 0, 1, 0.01)
			);


//----------------------`wind`--------------------------
// A very simple wind simulator, based on a filtered white noise
//
// #### Usage
//
// ```
//  wind(f) : _
// ```
//
// Where:
//
// * `f`: is the force of the wind: between 0 and 1
//
//----------------------------------------------------------

import("stdfaust.lib");

wind(force,level) = no.multinoise(2) : par(i, 2, ve.moog_vcf_2bn(force,freq)) : par(i, 2, *(force)) : par(i, 2, *(level))
	with {
		freq = (force*87)+1 : ba.pianokey2hz;
	};

windGen = //wind ( hslider("v:wind/force",0.66,0,1,0.01) : si.smooth (0.997) );
		wind ( param : si.smooth (0.997) , volume * (cueNum == 2) * touchGate ) ;


//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------

import("stdfaust.lib");

vol 			= volume * (cueNum == 3) * touchGate : si.smoo ;//hslider("volume [unit:dB]", 0, -96, 0, 0.1) : ba.db2linear : si.smoo ;
freq 			= param*880+440; //hslider("freq [unit:Hz]", 1000, 20, 24000, 1);

sinusGen 		= os.osc(freq) <: _* vol, _* vol;
