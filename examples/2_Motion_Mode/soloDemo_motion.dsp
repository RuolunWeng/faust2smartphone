declare name 		"SoloDemo_motion:MYzpos";
declare version 	"2.0";
declare author 		"Allen";




process = rainGen :>_,_ ;


// declare connection UI
volume = hslider("volume[motion:MYzpos]",0,0,1,0.01);
param = hslider("param[motion:MYzpos]",0,0,1,0.01);


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
				volume
				//hslider("v:rain/density", 300, 0, 1000, 1) / 1000,
				//hslider("v:rain/volume", 0.5, 0, 1, 0.01)
			);
