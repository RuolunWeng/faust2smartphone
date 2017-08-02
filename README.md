# faust2smartphone
A tool for musical mobile application using FAUST API.


============

INSTALLATION

============

_Make sure you are already installed FAUST first. -> https://github.com/grame-cncm/faust

_Get from GitHub, " git clone https://github.com/RuolunWeng/faust2smartphone.git ".
 
_Open your terminal, cd to “install” folder, tap “sudo make install”.

_Done!


============

How To Use

============

_Open your terminal, cd to the folder you work, tap "faust2smartphone -help" to know more.


1) For Simple Project

    fasut2smartphone -ios/-android toto.dsp
   
   _in Xcode or Android Studio project, DspFaust is added, create your own interface. 

2) For specific function

    "-osc" for OSC support
    
    "-soloios" to generate a project with Motion support for iOS.

    "-soloandroid" to generate a project with Motion support for Android.

    [Motion.lib created by Christophe Lebreton].

    --------------------------------------------------------------

    _in your .dsp file, declare motion controller you need, like:
        
           ***************************
           ** simple motion support **
           ***************************

        // Active Motion controller

        titi = hslider("ixp",0,0,1,0.01);

        toto = hslider("brasG_cours",0,0,1,0.01);

        tata = hslider("ventre_front",0,0,1,0.01);
        
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


    -------------------------------------------------------------

    "./updatecue toto" to update your cue manager.

    "-iosplugin" to generate a project with Faust Plugin for iOS.

    "-androidplugin" to generate a project with Faust Plugin for Android.
    
3) Compile Application
    
    ./compile -ios/android toto

    _after edit your project, compile your app for your device.


