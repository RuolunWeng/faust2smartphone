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

    fasut2smartphone -ios/-android ***.dsp
   
   _in Xcode or Android Studio project, DspFaust is added, create your own interface. 

2) For iOS specific fuction

    "-osc" for OSC support
    
    "-iosmotion" to generate a project with Motion support.

    [Motion.lib created by Christophe Lebreton].

    --------------------------------------------------------------

    _in your .dsp file, declare motion controller you need, like:

        touchGate = checkbox("touchgate");

        ixp = hslider("ixp",0,0,1,0.01);

    -------------------------------------------------------------
    
3) Compile Application
    
    ./compile -ios/android ***.

    _after edit your project, compile your app for your device.


