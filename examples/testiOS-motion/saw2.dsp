import("stdfaust.lib"); 


// declare motion parameter
ixp = hslider("ixp",0,0,1,0.001);
iyp = hslider("iyp",0,0,1,0.001);
touchgate = checkbox("touchgate");


freq = ixp*400+440;
gain = iyp;
gate = touchgate : si.smooth(0.999);
  
process = vgroup("saw",os.saw1(freq)*gain*gate);