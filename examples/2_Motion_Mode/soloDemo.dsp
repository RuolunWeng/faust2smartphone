declare name 		"SoloDemo";
declare version 		"1.0";
declare author 		"Grame";




process = rainGen, windGen, sinusGen :>_,_ ;



// declare connection UI
cueNum = nentry("cue",0,0,3,1);
touchGate = checkbox("touchgate");
volume = hslider("screenx",0,0,1,0.01);
param = hslider("param[motion:ixp]",0,0,1,0.01);


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
				param,
				volume*(cueNum==1)*touchGate
				//hslider("v:rain/density", 300, 0, 1000, 1) / 1000,
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
