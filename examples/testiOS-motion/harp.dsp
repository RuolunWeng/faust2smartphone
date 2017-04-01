declare name "harp";
declare author "Allen";

import("stdfaust.lib");


touchGate = checkbox("touchgate");
ixp =  hslider("screenx",0,0,1,0.01);
iyn =  hslider("screeny",0,0,1,0.01);

//ixp = hslider("ixp",0,0,1,0.01);
//iyn = hslider("iyn",0,0,1,0.01);//scale(0,1,1,2); // scale("iyn",0,1,1,2);
//================================ Instrument Parameters =================================
// Creates the connection between the synth and the mobile device
//========================================================================================

// the string resonance in second is controlled by the x axis of the accelerometer
//res = hslider("res[acc: 0 0 -10 0 10]",2,0.1,4,0.01);
// Smart Keyboard frequency parameter
//freq = hslider("freq",400,50,2000,0.01);
// Smart Keyboard gate parameter
//gate = button("gate");
res = iyn*3.9+0.1;
freq = ixp*1000+400;
gate = touchGate;

//=================================== Parameters Mapping =================================
//========================================================================================

stringFreq = freq;

//============================================ DSP =======================================
//========================================================================================

process = sy.combString(freq,res,gate);
