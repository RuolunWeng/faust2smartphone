# faust2smartphone


=========================================

A tool for musical mobile application using FAUST API.

=========================================


## INSTALLATION 

### -Make sure you have already installed FAUST first
Check [Faust Website](https://faust.grame.fr/) and follow the instruction on its [github](https://github.com/grame-cncm/faust)

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

### 2) For Motion lib support Project
`       fasut2smartphone -iosmotion/-androidmotion toto.dsp`

In Xcode or Android Studio project, DspFaust and DspFaustMotion is added, create your own interface or use the default. 
(Like this mode is specially designed for projet [Smart Hand Computer](https://www.lisilog.com/en/shc-2/), so the CueManager interface is ready to call)

*Motion.lib created by Christophe Lebreton*

>
    
    // Of cause you could always call accelerometer/gyroscope in UI with traditional Faust syndax:

        parameter = nentry("UIparamName[acc/gro: a b c d e]",def,min,max,step);

    // And you could call mobile device attitude sensor value:
    // [yaw, raw, pitch, quaternionw, quaternionx, quaterniony, quaternionz]

        parameter = nentry("yaw",def,min,max,step);

    // Or if you want use the methode in Motion.lib with the syndax

        parameter = nentry("UIparamName[motion: descriptorName]",def,min,max,step);
>
**Here is motion descriptor list you can call in you code:**  
>

    //============= ACCELEROMETER SHOCK TRIGGER ===============
	// setting of user sensibility to trig with a antirebond , p->positive axe; n->nagative axe
    - 
        + sxp syp szp
        + sxn syn szn
    //============= INCLINOMETER TO GRAVITY ===============
    // accelerometer -> inclinometer
    - 
        + ixp iyp izp
        + ixn iyn izn
        + ixpn iypn izpn
    //accelerometer -> inclinometer positive & negative axe sens combined to compare gravity symetric 0->1->0
    - 
        + ixpn_sym iypn_sym izpn_sym
	// accelerometer -> inclinometer -> projection to gravity positive axe sens
    - 
        + pixp piyp pizp
        + pixn piyn pizn
    //============= ACCELEROMETER TOTAL ACCELERATION with gravity removed ===============
	// totalmotion don't dpeant of specific orientation, only the quantity of global acceleration create a modulation
	// normalized 0 to 1
    - 
        + axpn aypn azpn
        + axp ayp azp
        + axn ayn azn
        + totalaccel
    //============= GYROSCOPES ===============
	// les gyroscopes des iPhones ont un range max de +/- 2000deg/sec => 34,906 radians.s-1
	// les valeurs reçues par le smartphone sont en radian.s-1
	// pour un iPhoneSE on obsverve un bruit de +/- 0.01 radian.s-1 ce qui inférieur à 1 degré ( 1 dégré ~ 0.017 radian)
	// smooth is need to remove artefact from signal/vector_size setting
    - 
        + gxpn gypn gzpn
        + gxp gyp gzp
        + gxn gyn gzn
        + totalgyro

	//--------------------------------------------------
	// TREATMENT FOR ROTATION MATRIX 
	//--------------------------------------------------
    // Calculate distance for each axe compared to 6 poles
    // Left Hand => brasG; Right Hand => brasD; Head => tete; Foot => pieds; Chest => ventre; Back => dos
    // State left => jardin; State right => cour; State up => up; State down => down; State front => front; State back => rear;
    - 
        + brasG_cour brasG_rear brasG_jardin brasG_front brasG_down brasG_up
        + pieds_cour pieds_rear pieds_jardin pieds_front pieds_down pieds_up
        + dos_cour dos_rear dos_jardin dos_front dos_down dos_up
        + brasD_cour brasD_rear brasD_jardin brasD_front brasD_down brasD_up
        + tete_cour tete_rear tete_jardin tete_front tete_down tete_up
        + ventre_cour ventre_rear ventre_jardin ventre_front ventre_down ventre_up

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
        
```
**Please check the exmaple code in examples/2_Motion_Mode**

### 3) For Faust Non-audio Plugin Support Project
`       fasut2smartphone -iosplugin/-androidplugin toto.dsp`

In Xcode or Android Studio project, DspFaust is added, create your own interface and plug it to your process. 
**Please check the exmaple code in examples/3_Plugin_Mode**

### 4) For Specific Functions

"-osc" for OSC support.**(Make sure you have dependecies installed)**
    
"-soundfile" for build-in soundfile support.**(Make sure you have dependecies installed)**
 
"./updatecue toto" to update your cue manager.
    
### 5) Compile Application
After edit your project, compile your app for your device using the command below or launch via you IDE.

`   ./compile -ios/android toto `



## REFERENCE

- TALK & PAPER @ International FAUST Conference ([IFC2018](http://www.ifc18.uni-mainz.de/))
    * https://www.youtube.com/watch?v=nePEYdMrcPg
    * http://www.ifc18.uni-mainz.de/papers/weng.pdf

