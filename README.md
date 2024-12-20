# faust2smartphone


=========================================

**What is Faust?**

[Faust](https://faust.grame.fr) (Functional Audio Stream) is a functional programming language for sound synthesis and audio processing with a strong focus on the design of synthesizers, musical instruments, audio effects, etc. Faust targets high-performance signal processing applications and audio plug-ins for a variety of platforms and standards.

**What is faust2smartphone?**

faust2smartphone is a tool to generate interactive musical mobile application embeded Faust API.

=========================================


## Installation

### -Make sure you have already installed FAUST first
Check [Faust Quick Start](https://faust.grame.fr/doc/manual/index.html#quick-start) for the language usage,
and follow the installation instruction on its [Github](https://github.com/grame-cncm/faust)

### -Get faust2smartphone from GitHub
`   git clone https://github.com/RuolunWeng/faust2smartphone.git`
 
### -Install all the sources
`   cd install`

`   sudo make install`

**Done!**



## How To Use

**Open your terminal, cd to the folder you work, tap "faust2smartphone -help" to know more.**

### 1) For Simple Project
`       fasut2smartphone -ios/-android toto.dsp`

In Xcode or Android Studio project, DspFaust is added, create your own interface. 

**Please check the exmaple code in examples/1_Simple_Mode**
********
********

### 2) For Motion lib support Project
`       fasut2smartphone -iosmotion/-androidmotion toto.dsp`

In Xcode or Android Studio project, DspFaust and DspFaustMotion is added, create your own interface or use the default. 
(Like this mode is specially designed for projet [Smart Hand Computer](https://www.lisilog.com/en/shc-2/), so the CueManager interface is ready to call by -cuemanager)

*Motion.lib created by Christophe Lebreton*

>
    
    // Of cause you could always call accelerometer/gyroscope in UI with traditional Faust syndax:

        parameter = nentry("UIparamName [acc/gro: a b c d e]",def,min,max,step);

    // And you could call mobile device attitude sensor value:
    // [yaw, raw, pitch, quaternionw, quaternionx, quaterniony, quaternionz]

        parameter = nentry("yaw",def,min,max,step);

    // Or if you want use the methode in Motion.lib with the syndax

        parameter = nentry("UIparamName [motion: descriptorName]",def,min,max,step);

    // If you want show some parameters in the UI, declare showName in the metada

        parameter = nentry("UIparamName [showName: paramName]",def,min,max,step);

>
**Here is motion descriptor list you can call in you code:**  
>

    //============= ACCELEROMETER SHOCK TRIGGER ===============
	// setting of user sensibility to trig with a antirebond
    // s->shock, p->positive axe, n->nagative axe
    - 
        + sxp syp szp
        + sxn syn szn
    //============= INCLINOMETER ===============
    // simple inclinometer for one axe as vector compared to gravity
    // i->inclinometer, p->positive axe, n->nagative axe
    - 
        + ixp iyp izp
        + ixn iyn izn
        + ixpn iypn izpn
    //============= ACCELERATION ===============
    // a->acceleration, p->positive axe, n->nagative axe, with gravity removed
	// totalaccel does not depends on specific acceleration, only the quantity of global acceleration create a modulation
    - 
        + axp ayp azp
        + axn ayn azn
        + axpn aypn azpn
        + totalaccel
    //============= GYROSCOPES ===============
    // g->gyroscope, p->positive axe, n->nagative axe
    // totalgyro does not depends on specific orientation, only the quantity of global orientation create a modulation
    - 
        + gxp gyp gzp
        + gxn gyn gzn
        + gxpn gypn gzpn
        + totalgyro
	//=======================================
	// TREATMENT FOR ROTATION MATRIX 
	//=======================================
    // Calculation of distance for one axe as vector (X Y Z) compared to another axe (x y z)
    // M->Rotation Matrix; raw->full axe, normalised from -1 to 1; pos->positive axe; neg->nagative axe
    - 
        + MXzraw MXzpos MXzneg
        + MYzraw MYzpos MYzneg
        + MZzraw MZzpos MZzneg
    //  ... ...

>

In your .dsp file, declare motion controller you need, like:
```      
***************************
** simple motion support **
***************************

// Active Motion controller

titi = hslider("titi[motion:ixp]",0,0,1,0.01);

toto = hslider("toto[motion:totalgyro]",0,0,1,0.01);

tata = hslider("tata[motion:MXzneg]",0,0,1,0.01);

**********************************
** motion support + cue manager **
**********************************

// Active Cue

cue = nentry("cue",0,0,3,1);

// Active Touch Screen

touchGate = checkbox("touchgate");

// Active Touch Pad X,Y

touchX = hslider("screenx",0,0,1,0.01);

touchY = hslider("screeny",0,0,1,0.01);
        
```
==NEW==

**[SHCUI] interface support in iOS Motion Mode && Android Motion Mode**

In your FAUST .dsp file, declare [SHCUI] interface you need in metadata, which will positioned in the screen. [SHCUI] interface's types have normal types and special funtions:


###### [SHCUI] metadata format:
```
[SHCUI:TabTitle Types X Y W H R G B A]
```
***TabTitle***
=> [SHCUI] could be put in several tabs or the same tab if they have the same title name

***X Y W H R G B A***
=> [SHCUI] frame Coordination X/Y; Width/Height [in percent 0-100]
=> [SHCUI] frame Color in Red/Green/Blue/Alpha [0-255]

###### [SHCUI] interface types:
//_Normal FaustUI-like types_

***"button"***
=>  touch down->1, touch up->0
```
button01 = button("B1 [SHCUI: Buttons button 0 0 50 50 0 255 0 200] [osc:/button01]");
```
***"checkbox"***
=>  touched up->1 (selected), touched up again->0 (unselected), verse versa
```
toggle02 = checkbox("T2 [SHCUI: Toggles checkbox 50 0 50 50 0 255 0 200] [osc:/toggle02]");
```
***"hslider"***
=>  touch move in the UI horizontally, scaled from MIN to MAX 
```
hslider03 = hslider("hslider03 [SHCUI: Hsliders hslider 0 50 100 25 255 255 0 200] [osc:/hslider03]",0,0,1,0.001);
```
***"vslider"***
=>  touch move in the UI vertically, scaled from MIN to MAX 
```
vslider04 = vslider("vslider04 [SHCUI: Vsliders vslider 75 0 25 100 255 255 255 200] [osc:/vslider04]",0,0,1,0.001);
```
***"hbargraph"***
=>  a vumeter horizontally, scaled from MIN to MAX 
```
hbargraph01= hslider("MYzpos [SHCUI: Hbargraphs hbargraph 0 66 100 33 255 255 0 200]",0,0,1,0.0001);
```
***"vbargraph"***
=>  a vumeter vertically, scaled from MIN to MAX 
```
vbargraph01= hslider("MXzraw [SHCUI: Vbargraphs vbargraph 0 0 33 100 0 255 255 200]",0,-1,1,0.0001);
```

//_Special FaustUI-like types_

***"trigCounter"***
=>  "button" trigger, touched up to advance a counter from MIN to MAX in loop
```
select_sample = nentry("Trig_Your_Sample [SHCUI:SmartFaust trigCounter 50 0 50 50 255 0 0 255]", 1, 1, 10, 1);
```
***"pad"***
touch Pad depending touch position
=> touch down->1 , touch up->0 (send to FaustUI which declares "pad")
=> touch move in the UI, coordination X scaled from MIN to MAX sent to FaustUI which declares ending with "_X", coordination Y scaled from MIN to MAX sent to FaustUI which declares ending with "_Y"
```
touchGate01 = checkbox("Pad1 [SHCUI: Pads pad 0 0 50 50 0 255 255 200] [osc:/pad01]");
touch01X = hslider("Pad1_X [osc:/pad01x]",0,0,1,0.001);
touch01Y = hslider("Pad1_Y [osc:/pad01y]",0,0,1,0.001);
```

//_Special Motion mode actions types_

***"trigCue"***

NOTA: an altenative way to not use original Cue Manager interface, Faust UI "/cue" must be declared to activate Cue Manager

=>  "button" trigger, touched up to trigger "goCue"
***"nextCue"***
=>  "button" trigger, touched up to trigger "nextCue"
***"prevCue"***
=>  "button" trigger, touched up to trigger "prevCue"
***"initCue"***
=>  "button" trigger, touched up to trigger "initCue"

NOTA: special metadata [touchCueManager:] could be declared in Faust UI "/cue" to map Cue Tips and Cue Orders

```
cueNum = nentry("cue [SHCUI: Cue trigCue 0 0 50 30 255 0 0 150] [touchCueManager: {0:'init'; 1:'rainGen'; 2:'windGen'; 3: 'sinusGen'}]",0,0,3,1);
trigNextCue = button("goNext [SHCUI: Cue nextCue 50 30 50 30 255 255 0 150]");
trigPrevCue = button("goPrev [SHCUI: Cue prevCue 0 30 50 30 255 255 0 150]");
trigInitCue = button("initCue [SHCUI: Cue initCue 50 0 50 30 255 255 255 150]");
```

***"setRef"***

NOTA: an altenative way to setRef of motion.lib, Faust UI "/setref_rota" need to be declared only if you want to using OSC for example

=>  "button" trigger, touched up to trigger "setRef"
```
trigsetRef = button("setref_rota[osc:/setRef][SHCUI: Master setRef 50 0 50 25 0 0 255 255]");
```

***Please check the exmaple code in examples/2_Motion_Mode***

********
********
### 3) For Faust Non-audio Plugin Support Project
`       fasut2smartphone -iosplugin/-androidplugin toto.dsp`

In Xcode or Android Studio project, DspFaust is added, create your own interface and plug it to your process. 
**Please check the exmaple code in examples/3_Plugin_Mode**

### 4) For Specific Functions

"-osc" for OSC support.**(Make sure you have dependecies installed)**
    
"-soundfile" for build-in soundfile support.**(Make sure you have dependecies installed)**
 
"-cuemanager" for using Cue Maneger system

"./updatecue toto" to update your cue manager.
    
### 5) Compile Application
After edit your project, compile your app for your device using the command below or launch via you IDE.

`   ./compile -ios/android toto `



## Reference

- TALK & PAPER @ International FAUST Conference ([IFC2018](http://www.ifc18.uni-mainz.de/))
    * https://www.youtube.com/watch?v=nePEYdMrcPg
    * http://www.ifc18.uni-mainz.de/papers/weng.pdf

