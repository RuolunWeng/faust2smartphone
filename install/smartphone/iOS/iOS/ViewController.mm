//
//  ViewController.m
//  FaustAPInew
//
//  Created by Allen on 08/12/2016.
//  Copyright © 2016 Allen. All rights reserved.
//

#import "ViewController.h"
#import "DspFaust.h"
#import <CoreMotion/CoreMotion.h>

#define kMotionUpdateRate 30
#define kGUIUpdateRate 30
#define ONE_G 9.81

@interface ViewController ()

@end

@implementation ViewController{
    DspFaust *dspFaust;
    CMMotionManager* _motionManager;
    NSTimer* _motionTimer;
    NSTimer* _guiTimer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // no sleep mode
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    const int SR = 44100;
    const int bufferSize = 256;
    
    dspFaust = new DspFaust(SR,bufferSize);
    
    //////////////////////////////////////////////
    //Cheeck the MetaData in console
    //Choose the parameter address correspantant
    //////////////////////////////////////////////
    
    NSLog(@"Faust Metadata: %s", dspFaust->getJSONUI());
    dspFaust->start();
    
    //#error FIXME: fix now! and comment me!
    //////////////////////////////////////////////
    //Change the parameter address and value to initialize
    //////////////////////////////////////////////
    
    dspFaust->setParamValue("/Oscillator/volume", -30);
    dspFaust->setParamValue("/Oscillator/freq", 440);
    
    
    [self startMotion];
    [self startUpdate];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}


- (void)startMotion
{
    if (_motionManager == nil)
    {
        _motionManager = [[CMMotionManager alloc] init];
        [_motionManager startAccelerometerUpdates];
        [_motionManager startGyroUpdates];
    }
    _motionTimer = [NSTimer scheduledTimerWithTimeInterval:1./kMotionUpdateRate target:self
                                                  selector:@selector(updateMotion) userInfo:nil repeats:YES];
}

// Stop updating sensors
- (void)stopMotion
{
    if (_motionManager != nil)
    {
        [_motionManager stopAccelerometerUpdates];
        [_motionManager stopGyroUpdates];
        _motionManager = nil;
        [_motionTimer invalidate];
    }
}

- (void)updateMotion
{
    dspFaust->propagateAcc(0, _motionManager.accelerometerData.acceleration.x * ONE_G);
    dspFaust->propagateAcc(1, _motionManager.accelerometerData.acceleration.y * ONE_G);
    dspFaust->propagateAcc(2, _motionManager.accelerometerData.acceleration.z * ONE_G);
    dspFaust->propagateGyr(0, _motionManager.gyroData.rotationRate.x);
    dspFaust->propagateGyr(1, _motionManager.gyroData.rotationRate.y);
    dspFaust->propagateGyr(2, _motionManager.gyroData.rotationRate.z);
}


- (void)startUpdate
{
    _guiTimer = [NSTimer scheduledTimerWithTimeInterval:1./kGUIUpdateRate target:self
                                               selector:@selector(updateGUI) userInfo:nil repeats:YES];
}

// Stop updating sensors
- (void)stopUpdate
{
    
    [_guiTimer invalidate];
    
}

- (void)updateGUI
{
    //#error FIXME: fix now! and comment me!
    //////////////////////////////////////////////
    //Change the parameter address and value to update UI
    //////////////////////////////////////////////
    float param1 = dspFaust->getParamValue("/Oscillator/freq");
    float param2 = dspFaust->getParamValue("/Oscillator/volume");
    _freq.value=param1;
    _volume.value=param2;
    _freqValue.text=[NSString stringWithFormat: @"%.1fHz", param1];
    _volumeValue.text=[NSString stringWithFormat: @"%.1fdB",param2];
}


- (void)dealloc {
    [_freq release];
    [_freqValue release];
    [_volumeValue release];
    [_volume release];
    [_freqLabel release];
    [_volumeLabel release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setFreq:nil];
    [super viewDidUnload];
}



//#error FIXME: fix now! and comment me!
//////////////////////////////////////////////
//Bulid your own interface
//(Main.storyboard / viewController.h)
//Change the parameter address and value
//////////////////////////////////////////////

- (IBAction)volumeOut:(id)sender {
    dspFaust->setParamValue("/Oscillator/volume", self.volume.value);
    _volumeValue.text=[NSString stringWithFormat: @"%.1fdB", self.volume.value];
}

- (IBAction)freqOut:(id)sender {
    dspFaust->setParamValue("/Oscillator/freq", self.freq.value);
    _freqValue.text=[NSString stringWithFormat: @"%.1fHz", self.freq.value];
}
@end
