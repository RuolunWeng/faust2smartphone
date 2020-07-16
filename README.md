# faust2smartphone
A tool for musical mobile application using FAUST API.

======================================================

======================================================


## INSTALLATION 

### Make sure you are already installed FAUST first
Check [Faust Website](https://faust.grame.fr/) and follow the instruction on its [github](https://github.com/grame-cncm/faust)

### Get faust2smartphone from GitHub
`   git clone https://github.com/RuolunWeng/faust2smartphone.git`
 
### Install all the sources
`   cd install`

`   sudo make install`

**Done!**



## How To Use

**Open your terminal, cd to the folder you work, tap "faust2smartphone -help" to know more.**

### 1) For Simple Project
`       fasut2smartphone -ios/-android toto.dsp`

In Xcode or Android Studio project, DspFaust is added, create your own interface. 

### 2) For Motion lib support Project
`       fasut2smartphone -iosmotion/-androidmotion toto.dsp`

In Xcode or Android Studio project, DspFaust and DspFaustMotion is added, create your own interface or use the default. 
(Like this mode is specially designed for projet [Smart Hand Computer](https://www.lisilog.com/en/shc-2/), so the CueManager interface is ready to call)

*Motion.lib created by Christophe Lebreton*

**Here is some motion parameters list you can call in you code:**
>
    这是引用的内容
>

In your .dsp file, declare motion controller you need, like:
```      
           ***************************
           ** simple motion support **
           ***************************

        // Active Motion controller

        titi = hslider("titi[motion:ixp]",0,0,1,0.01);

        toto = hslider("toto[motion:brasG_cours]",0,0,1,0.01);

        tata = hslider("tata[motion:ventre_front]",0,0,1,0.01);
        
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
        
        // Active State + Init
        
        state = hbargraph("state",0,6);
        
        init = button("init");

```
### 3) For Faust Non-audio Plugin Support Project
`       fasut2smartphone -iosplugin/-androidplugin toto.dsp`

In Xcode or Android Studio project, DspFaust is added, create your own interface and plug it to your process. 
### 4) For Specific Functions

"-osc" for OSC support
    
"-soundfile" for build-in soundfile support.
 
"./updatecue toto" to update your cue manager.
    
### 5) Compile Application
After edit your project, compile your app for your device using the command below or launch via you IDE.

`   ./compile -ios/android toto `



## REFERENCE

- TALK & PAPER @ International FAUST Conference ([IFC2018](http://www.ifc18.uni-mainz.de/))
    * https://www.youtube.com/watch?v=nePEYdMrcPg
    * http://www.ifc18.uni-mainz.de/papers/weng.pdf

