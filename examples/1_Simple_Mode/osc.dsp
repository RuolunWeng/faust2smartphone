declare name 		"osc";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------

import("stdfaust.lib");

vol 			= hslider("volume [unit:dB]", 0, -96, 0, 0.1) : ba.db2linear : si.smoo ;
freq 			= hslider("freq [acc:0 0 -10 -10 10] [unit:Hz]", 220, 220, 1000, 1);

process 		= vgroup("Oscillator", os.osc(freq) * vol)<:_,_,_,_;

