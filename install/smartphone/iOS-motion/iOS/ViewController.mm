//
//  ViewController.m
//  FaustAPInew
//
//  Created by Allen on 03/2017.
//  Copyright © 2016 Allen. All rights reserved.
//

#import "ViewController.h"

#define ONE_G 9.81
#define kGUIUpdateRate 30


@interface ViewController ()

@end



@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    
    // no sleep mode
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    
    ////////////////////
    // init faust motor
    ////////////////////
    
    const int SR = 44100;
    const int bufferSize = 256;
    
    dspFaust = new DspFaust(SR,bufferSize,updateMotionCallback, self);
    
    dspFaustMotion = new DspFaustMotion(SR/bufferSize,1);
    
    ////////////////////////////////
    //Check the MetaData in console
    ///////////////////////////////
    
    NSLog(@"Faust Metadata: %s", dspFaust->getJSONUI());
    NSLog(@"Motion Metadata: %s", dspFaustMotion->getJSONUI());
    
    
    ///////////////////////////////////
    // check motion key word in address
    ///////////////////////////////////
    
    dspFaust->start();
    dspFaustMotion->start();
    
    [self checkAddress];
    
    
    /////////////////////////////////////////////////////
    //Change the parameter address and value to initialize
    /////////////////////////////////////////////////////
    
    if (dspFaust->getOSCIsOn()) {
        _ip.enabled=true;
        _inPort.enabled=true;
        _outPort.enabled=true;
        _setOSC.enabled=true;
        _ip.text=@"192.168.1.20";
        _inPort.text=@"5510";
        _outPort.text=@"5511";
    } else {
        _ip.enabled=false;
        _inPort.enabled=false;
        _outPort.enabled=false;
        _setOSC.enabled=false;
        _ip.text=@"NO";
        _inPort.text=@"NO";
        _outPort.text=@"NO";
    }
    
    
    [self startMotion];

    [self displayTitle];
    
    cueNum = 0;
    _pikerView.delegate = self;
    _pikerView.dataSource = self;
    

}



- (void) checkAddress {

    for(int i=0; i<dspFaust->getParamsCount(); i++){
        NSString *data = [NSString stringWithUTF8String:dspFaust->getParamAddress(i)];
        if ([data hasSuffix:@"/totalaccel"]) {
            totalAccelIsOn = true;
            totalAccelAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/totalaccelOn", 1);
        } else if ([data hasSuffix:@"/totalgyro"]) {
            totalGyroIsOn = true;
            totalGyroAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/totalgyroOn", 1);
        } else if ([data hasSuffix:@"/sxp"]) {
            sxpIsOn = true;
            sxpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/sxpOn", 1);
        } else if ([data hasSuffix:@"/syp"]) {
            sypIsOn = true;
            sypAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/sypOn", 1);
        } else if ([data hasSuffix:@"/szp"]) {
            szpIsOn = true;
            szpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/szpOn", 1);
        } else if ([data hasSuffix:@"/sxn"]) {
            sxnIsOn = true;
            sxnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/sxnOn", 1);
        } else if ([data hasSuffix:@"/syn"]) {
            synIsOn = true;
            synAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/synOn", 1);
        } else if ([data hasSuffix:@"/szn"]) {
            sznIsOn = true;
            sznAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/sznOn", 1);
        } else if ([data hasSuffix:@"/ixp"]) {
            ixpIsOn = true;
            ixpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ixpOn", 1);
        } else if ([data hasSuffix:@"/iyp"]) {
            iypIsOn = true;
            iypAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/iypOn", 1);
        } else if ([data hasSuffix:@"/izp"]) {
            izpIsOn = true;
            izpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/izpOn", 1);
        } else if ([data hasSuffix:@"/ixn"]) {
            ixnIsOn = true;
            ixnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ixnOn", 1);
        } else if ([data hasSuffix:@"/iyn"]) {
            iynIsOn = true;
            iynAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/iynOn", 1);
        } else if ([data hasSuffix:@"/izn"]) {
            iznIsOn = true;
            iznAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/iznOn", 1);
        } else if ([data hasSuffix:@"/pixp"]) {
            pixpIsOn = true;
            pixpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pixpOn", 1);
        } else if ([data hasSuffix:@"/piyp"]) {
            piypIsOn = true;
            piypAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/piypOn", 1);
        } else if ([data hasSuffix:@"/pizp"]) {
            pizpIsOn = true;
            pizpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pizpOn", 1);
        } else if ([data hasSuffix:@"/pixn"]) {
            pixnIsOn = true;
            pixnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pixnOn", 1);
        } else if ([data hasSuffix:@"/piyn"]) {
            piynIsOn = true;
            piynAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/piynOn", 1);
        } else if ([data hasSuffix:@"/pizn"]) {
            piznIsOn = true;
            piznAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/piznOn", 1);
        } else if ([data hasSuffix:@"/axpn"]) {
            axpnIsOn = true;
            axpnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/axpnOn", 1);
        } else if ([data hasSuffix:@"/aypn"]) {
            aypnIsOn = true;
            aypnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/aypnOn", 1);
        } else if ([data hasSuffix:@"/azpn"]) {
            azpnIsOn = true;
            azpnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/azpnOn", 1);
        } else if ([data hasSuffix:@"/axp"]) {
            axpIsOn = true;
            axpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/axpOn", 1);
        } else if ([data hasSuffix:@"/ayp"]) {
            aypIsOn = true;
            aypAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/aypOn", 1);
        } else if ([data hasSuffix:@"/azp"]) {
            azpIsOn = true;
            azpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/azpOn", 1);
        } else if ([data hasSuffix:@"/axn"]) {
            axnIsOn = true;
            axnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/axnOn", 1);
        } else if ([data hasSuffix:@"/ayn"]) {
            aynIsOn = true;
            aynAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/aynOn", 1);
        } else if ([data hasSuffix:@"/azn"]) {
            aznIsOn = true;
            aznAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/aznOn", 1);
        } else if ([data hasSuffix:@"/gxpn"]) {
            gxpnIsOn = true;
            gxpnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gxpnOn", 1);
        } else if ([data hasSuffix:@"/gypn"]) {
            gypnIsOn = true;
            gypnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gypnOn", 1);
        } else if ([data hasSuffix:@"/gzpn"]) {
            gzpnIsOn = true;
            gzpnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gzpnOn", 1);
        } else if ([data hasSuffix:@"/gxp"]) {
            gxpIsOn = true;
            gxpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gxpOn", 1);
        } else if ([data hasSuffix:@"/gyp"]) {
            gypIsOn = true;
            gypAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gypOn", 1);
        } else if ([data hasSuffix:@"/gzp"]) {
            gzpIsOn = true;
            gzpAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gzpOn", 1);
        } else if ([data hasSuffix:@"/gxn"]) {
            gxnIsOn = true;
            gxnAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gxnOn", 1);
        } else if ([data hasSuffix:@"/gyn"]) {
            gynIsOn = true;
            gynAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gynOn", 1);
        } else if ([data hasSuffix:@"/gzn"]) {
            gznIsOn = true;
            gznAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/gznOn", 1);
        } else if ([data hasSuffix:@"/touchgate"]) {
            touchGateIsOn = true;
            touchGateAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/screenx"]) {
            screenXIsOn = true;
            screenXAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/screeny"]) {
            screenYIsOn = true;
            screenYAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/compass"]) {
            magneticHeadingIsOn = true;
            magneticHeadingAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/cue"]) {
            cueIsOn = true;
            cueAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/tip"]) {
            tipIsOn = true;
            [self startUpdateGUI];
            tipAddress = dspFaust->getParamAddress(i);
        }

    }


}



// Audio control callback
void updateMotionCallback(void* arg)
{
    ViewController* interface = static_cast<ViewController*>(arg);
    [interface updateMotion];
}

- (void)startMotion
{
    if (_motionManager == nil)
    {
        _motionManager = [[CMMotionManager alloc] init];
        [_motionManager startAccelerometerUpdates];
        [_motionManager startGyroUpdates];
    }
    
    if (magneticHeadingIsOn) {
    if (_locationManager == nil) {
        
        _locationManager = [[CLLocationManager alloc] init];
        _locationManager.delegate = self;
        _locationManager.desiredAccuracy = kCLLocationAccuracyBest;
        _locationManager.distanceFilter = kCLHeadingFilterNone;
        _locationManager.headingFilter = 5;//kCLHeadingFilterNone;
        magnetic = 0;
        offset = 0;
        [_locationManager startUpdatingHeading];
    }
    }
}

// Stop updating sensors
- (void)stopMotion
{
    if (_motionManager != nil)
    {
        [_motionManager stopAccelerometerUpdates];
        [_motionManager stopGyroUpdates];
        _motionManager = nil;
        
    }
    
    if (magneticHeadingIsOn) {
    if (_locationManager != nil) {
        
        [_locationManager stopUpdatingHeading];
        _locationManager = nil;
    }
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
    [self stopUpdateGUI];
    [self stopMotion];
    dspFaust->stop();
    dspFaustMotion->stop();
    delete dspFaust;
    delete dspFaustMotion;
}


- (void)updateMotion
{
    
    dspFaust->propagateAcc(0, _motionManager.accelerometerData.acceleration.x * ONE_G);
    dspFaust->propagateAcc(1, _motionManager.accelerometerData.acceleration.y * ONE_G);
    dspFaust->propagateAcc(2, _motionManager.accelerometerData.acceleration.z * ONE_G);
    dspFaust->propagateGyr(0, _motionManager.gyroData.rotationRate.x);
    dspFaust->propagateGyr(1, _motionManager.gyroData.rotationRate.y);
    dspFaust->propagateGyr(2, _motionManager.gyroData.rotationRate.z);
    
    dspFaustMotion->propagateAcc(0, _motionManager.accelerometerData.acceleration.x * ONE_G);
    dspFaustMotion->propagateAcc(1, _motionManager.accelerometerData.acceleration.y * ONE_G);
    dspFaustMotion->propagateAcc(2, _motionManager.accelerometerData.acceleration.z * ONE_G);
    dspFaustMotion->propagateGyr(0, _motionManager.gyroData.rotationRate.x);
    dspFaustMotion->propagateGyr(1, _motionManager.gyroData.rotationRate.y);
    dspFaustMotion->propagateGyr(2, _motionManager.gyroData.rotationRate.z);
    
    dspFaustMotion->render();
    
    [self sendMotion];
    
}

- (void) sendMotion  {
    
    if (totalAccelIsOn) {
        dspFaust->setParamValue(totalAccelAddress, dspFaustMotion->getParamValue("/Motion/Mtotalaccel"));
    }
    if (totalGyroIsOn) {
        dspFaust->setParamValue(totalGyroAddress, dspFaustMotion->getParamValue("/Motion/Mtotalgyro"));
    }
    if (sxpIsOn) {
        dspFaust->setParamValue(sxpAddress, dspFaustMotion->getParamValue("/Motion/Msxp"));
    }
    if (sypIsOn) {
        dspFaust->setParamValue(sypAddress, dspFaustMotion->getParamValue("/Motion/Msyp"));
    }
    if (szpIsOn) {
        dspFaust->setParamValue(szpAddress, dspFaustMotion->getParamValue("/Motion/Mszp"));
    }
    if (sxnIsOn) {
        dspFaust->setParamValue(sxnAddress, dspFaustMotion->getParamValue("/Motion/Msxn"));
    }
    if (synIsOn) {
        dspFaust->setParamValue(synAddress, dspFaustMotion->getParamValue("/Motion/Msyn"));
    }
    if (sznIsOn) {
        dspFaust->setParamValue(sznAddress, dspFaustMotion->getParamValue("/Motion/Mszn"));
    }
    if (ixpIsOn) {
        dspFaust->setParamValue(ixpAddress, dspFaustMotion->getParamValue("/Motion/Mixp"));
    }
    if (iypIsOn) {
        dspFaust->setParamValue(iypAddress, dspFaustMotion->getParamValue("/Motion/Miyp"));
    }
    if (izpIsOn) {
        dspFaust->setParamValue(izpAddress, dspFaustMotion->getParamValue("/Motion/Mizp"));
    }
    if (ixnIsOn) {
        dspFaust->setParamValue(ixnAddress, dspFaustMotion->getParamValue("/Motion/Mixn"));
    }
    if (iynIsOn) {
        dspFaust->setParamValue(iynAddress, dspFaustMotion->getParamValue("/Motion/Miyn"));
    }
    if (iznIsOn) {
        dspFaust->setParamValue(iznAddress, dspFaustMotion->getParamValue("/Motion/Mizn"));
    }
    if (pixpIsOn) {
        dspFaust->setParamValue(pixpAddress, dspFaustMotion->getParamValue("/Motion/Mpixp"));
    }
    if (piypIsOn) {
        dspFaust->setParamValue(piypAddress, dspFaustMotion->getParamValue("/Motion/Mpiyp"));
    }
    if (pizpIsOn) {
        dspFaust->setParamValue(pizpAddress, dspFaustMotion->getParamValue("/Motion/Mpizp"));
    }
    if (pixnIsOn) {
        dspFaust->setParamValue(pixnAddress, dspFaustMotion->getParamValue("/Motion/Mpixn"));
    }
    if (piynIsOn) {
        dspFaust->setParamValue(piynAddress, dspFaustMotion->getParamValue("/Motion/Mpiyn"));
    }
    if (piznIsOn) {
        dspFaust->setParamValue(piznAddress, dspFaustMotion->getParamValue("/Motion/Mpizn"));
    }
    if (axpnIsOn) {
        dspFaust->setParamValue(axpnAddress, dspFaustMotion->getParamValue("/Motion/Maxpn"));
    }
    if (aypnIsOn) {
        dspFaust->setParamValue(aypnAddress, dspFaustMotion->getParamValue("/Motion/Maypn"));
    }
    if (azpnIsOn) {
        dspFaust->setParamValue(azpnAddress, dspFaustMotion->getParamValue("/Motion/Mazpn"));
    }
    if (axpIsOn) {
        dspFaust->setParamValue(axpAddress, dspFaustMotion->getParamValue("/Motion/Maxp"));
    }
    if (aypIsOn) {
        dspFaust->setParamValue(aypAddress, dspFaustMotion->getParamValue("/Motion/Mayp"));
    }
    if (azpIsOn) {
        dspFaust->setParamValue(azpAddress, dspFaustMotion->getParamValue("/Motion/Mazp"));
    }
    if (axnIsOn) {
        dspFaust->setParamValue(axnAddress, dspFaustMotion->getParamValue("/Motion/Maxn"));
    }
    if (aynIsOn) {
        dspFaust->setParamValue(aynAddress, dspFaustMotion->getParamValue("/Motion/Mayn"));
    }
    if (aznIsOn) {
        dspFaust->setParamValue(aznAddress, dspFaustMotion->getParamValue("/Motion/Mazn"));
    }
    if (gxpnIsOn) {
        dspFaust->setParamValue(gxpnAddress, dspFaustMotion->getParamValue("/Motion/Mgxpn"));
    }
    if (gypnIsOn) {
        dspFaust->setParamValue(gypnAddress, dspFaustMotion->getParamValue("/Motion/Mgypn"));
    }
    if (gzpnIsOn) {
        dspFaust->setParamValue(gzpnAddress, dspFaustMotion->getParamValue("/Motion/Mgzpn"));
    }
    if (gxpIsOn) {
        dspFaust->setParamValue(gxpAddress, dspFaustMotion->getParamValue("/Motion/Mgxp"));
    }
    if (gypIsOn) {
        dspFaust->setParamValue(gypAddress, dspFaustMotion->getParamValue("/Motion/Mgyp"));
    }
    if (gzpIsOn) {
        dspFaust->setParamValue(gzpAddress, dspFaustMotion->getParamValue("/Motion/Mgzp"));
    }
    if (gypIsOn) {
        dspFaust->setParamValue(gypAddress, dspFaustMotion->getParamValue("/Motion/Mgyp"));
    }
    if (gxnIsOn) {
        dspFaust->setParamValue(gxnAddress, dspFaustMotion->getParamValue("/Motion/Mgxn"));
    }
    if (gynIsOn) {
        dspFaust->setParamValue(gynAddress, dspFaustMotion->getParamValue("/Motion/Mgyn"));
    }
    if (gznIsOn) {
        dspFaust->setParamValue(gznAddress, dspFaustMotion->getParamValue("/Motion/Mgzn"));
    }
    
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading{
    
    //NSLog(@"MagneticHeading:%0.2f", newHeading.magneticHeading);
    magnetic = newHeading.magneticHeading;
    
    if (magnetic-offset>0) {
        magneticNormal = magnetic-offset;
    } else {
        magneticNormal = magnetic-offset+360.00f;
    }
    
    if (magneticNormal<=180) {
        magneticNew = magneticNormal/180.00f;
    } else {
        magneticNew = (360.00f - magneticNormal)/180.00f;
    }
    
    if (touchGateIsOn) {
        if (magneticHeadingIsOn) {
            dspFaust->setParamValue(magneticHeadingAddress, magneticNew);
            //NSLog(@"MagneticHeading:%0.2f", magneticNew);
        }
    }
    
}

- (void)startUpdateGUI
{
    
    _guiTimer = [NSTimer scheduledTimerWithTimeInterval:1./kGUIUpdateRate target:self
                                                  selector:@selector(updateGUI) userInfo:nil repeats:YES];
    
}

// Stop updating
- (void)stopUpdateGUI
{
    
    [_guiTimer invalidate];
    
    
}


- (void)updateGUI
{
    
    if (tipIsOn) {
        switch ((int)dspFaust->getParamValue(tipAddress)) {
            case 1:
                _tips.text = @"FaustTips:part1";
                break;
            case 2:
                _tips.text = @"FaustTips:part2";
                break;
            case 3:
                _tips.text = @"FaustTips:part4";
                break;
            case 4:
                _tips.text = @"FaustTips:part4";
                break;
        }
    }
    
}

- (void) touchesBegan:(NSSet *)touches
            withEvent:(UIEvent *)event {
    
    //NSUInteger touchCount = [touches count];
    
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self.view];
    
    CGFloat screenWidth = [[UIScreen mainScreen] bounds].size.width;
    CGFloat screenHeight = [[UIScreen mainScreen] bounds].size.height;
     
    CGFloat pointX = point.x/screenWidth;
    CGFloat pointY = point.y/screenHeight;
    
    if (touchGateIsOn) {
        dspFaust->setParamValue(touchGateAddress, 1);
        [self counter];
        _touch.alpha=1;
        if (magneticHeadingIsOn) {
            offset = magnetic;
        }
    }
    if (screenXIsOn) {
        dspFaust->setParamValue(screenXAddress, pointX);
    }
    if (screenYIsOn) {
        dspFaust->setParamValue(screenYAddress, pointY);
    }
    
    
}

- (void) touchesMoved:(NSSet *)touches
            withEvent:(UIEvent *)event {
    //NSUInteger touchCount = [touches count];
    
     UITouch *touch = [touches anyObject];
     CGPoint point = [touch locationInView:self.view];
    
    CGFloat screenWidth = [[UIScreen mainScreen] bounds].size.width;
    CGFloat screenHeight = [[UIScreen mainScreen] bounds].size.height;
     
    CGFloat pointX = point.x/screenWidth;
    CGFloat pointY = point.y/screenHeight;
    
    if (screenXIsOn) {
        dspFaust->setParamValue(screenXAddress, (float)pointX);
    }
    if (screenYIsOn) {
        dspFaust->setParamValue(screenYAddress, pointY);
    }
 
    
}

- (void) touchesEnded:(NSSet *)touches
            withEvent:(UIEvent *)event {
   //NSUInteger touchCount = [touches count];
    
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self.view];
    
    CGFloat screenWidth = [[UIScreen mainScreen] bounds].size.width;
    CGFloat screenHeight = [[UIScreen mainScreen] bounds].size.height;
     
    CGFloat pointX = point.x/screenWidth;
    CGFloat pointY = point.y/screenHeight;
    
    
    if (touchGateIsOn) {
        dspFaust->setParamValue(touchGateAddress, 0);
        _touch.alpha=0.1;
    }
    if (screenXIsOn) {
        dspFaust->setParamValue(screenXAddress, pointX);
    }
    if (screenYIsOn) {
        dspFaust->setParamValue(screenYAddress, pointY);
    }
    
}


-(void) counter {
    
    cueNum++;
    _cue.text= [NSString stringWithFormat:@"Cue:%d",cueNum];
    if (cueIsOn) {
        dspFaust->setParamValue(cueAddress, cueNum);
    }

}



- (IBAction)setOSC:(id)sender {
  
    [_ip resignFirstResponder];
    [_inPort resignFirstResponder];
    [_outPort resignFirstResponder];
 
   NSString* _oscIPOutputText = _ip.text;
   NSString* _oscInputPortText = _inPort.text;
   NSString* _oscOutputPortText = _outPort.text;
    
   dspFaust->setOSCValue([_oscIPOutputText cStringUsingEncoding:[NSString defaultCStringEncoding]], [_oscInputPortText cStringUsingEncoding:[NSString defaultCStringEncoding]], [_oscOutputPortText cStringUsingEncoding:[NSString defaultCStringEncoding]]);
}

- (IBAction)setParam:(id)sender {
    
    if (_setParam.isOn) {
        _ip.hidden=false;
        _inPort.hidden=false;
        _outPort.hidden=false;
        _setOSC.hidden=false;
        _init.hidden = false;
        _pikerView.hidden= false;
        _motionParam.hidden=false;
        _motionParamSend.hidden=false;
    } else {
        _ip.hidden=true;
        _inPort.hidden=true;
        _outPort.hidden=true;
        _setOSC.hidden=true;
        
        _init.hidden=true;
        _pikerView.hidden= true;
        _motionParam.hidden=true;
        _motionParamSend.hidden=true;
    }
    
}

- (IBAction)initCue:(id)sender {
    
    [_ip resignFirstResponder];
    [_inPort resignFirstResponder];
    [_outPort resignFirstResponder];
    [_motionParam resignFirstResponder];
    
    cueNum = 0;
    _cue.text= [NSString stringWithFormat:@"Cue:%d",cueNum];
    if (cueIsOn) {
        dspFaust->setParamValue(cueAddress, cueNum);
    }
    if (dspFaust->getOSCIsOn()) {
        _ip.text = @"192.168.1.20";
        _inPort.text = @"5510";
        _outPort.text = @"5511";
        dspFaust->setOSCValue("192.168.1.20","5510","5511");
    }
    
    for (int i=0; i<dspFaustMotion->getParamsCount(); i++) {
        dspFaustMotion->setParamValue(i, dspFaustMotion->getParamInit(i));
    }
    
    [self checkAddress];
}



- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, pickerView.frame.size.width, 44)];
    label.backgroundColor = [UIColor grayColor];
    label.textColor = [UIColor whiteColor];
    label.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:18];
    _motionParamArray = @[@"hp",@"shok_thr",@"antirebon",@"lp",@"tacc_thr",
                          @"tacc_gain",@"tacc_up",@"tacc_down",@"tgyr_thr",
                          @"tgyr_gain",@"tgyr_up",@"tgyr_down",@"osfproj"];
    label.text = [_motionParamArray objectAtIndex:row];
    return label;
}



-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    
    _motionParamArray = @[@"hp",@"shok_thr",@"antirebon",@"lp",@"tacc_thr",
                          @"tacc_gain",@"tacc_up",@"tacc_down",@"tgyr_thr",
                          @"tgyr_gain",@"tgyr_up",@"tgyr_down",@"osfproj"];
    NSString *seletedParam = [_motionParamArray objectAtIndex:row];

    if ([seletedParam isEqualToString:@"lp"]) {
        lpIsOn = true;
         hpIsOn = false;
         shok_thrIsOn= false;
         antirebonIsOn= false;
         osfprojIsOn= false;
         tacc_thrIsOn= false;
         tacc_gainIsOn= false;
         tacc_upIsOn= false;
         tacc_downIsOn= false;
         tgyr_thrIsOn= false;
         tgyr_gainIsOn= false;
         tgyr_upIsOn= false;
         tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/lp")];
    } else if ([seletedParam isEqualToString:@"shok_thr"]) {
        lpIsOn = false;
        hpIsOn = false;
        shok_thrIsOn= true;
        antirebonIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/shok_thr")];
    } else if ([seletedParam isEqualToString:@"hp"]) {
        hpIsOn = true;
        lpIsOn = false;
        shok_thrIsOn= false;
        antirebonIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/hp")];
    } else if ([seletedParam isEqualToString:@"antirebon"]) {
        antirebonIsOn = true;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/antirebon")];
    } else if ([seletedParam isEqualToString:@"tacc_thr"]) {
        tacc_thrIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tacc_thr")];
    } else if ([seletedParam isEqualToString:@"tacc_gain"]) {
        tacc_gainIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tacc_gain")];
    } else if ([seletedParam isEqualToString:@"tacc_up"]) {
        tacc_upIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tacc_up")];
    } else if ([seletedParam isEqualToString:@"tacc_down"]) {
        tacc_downIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tacc_down")];
    } else if ([seletedParam isEqualToString:@"tgyr_thr"]) {
        tgyr_thrIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tgyr_thr")];
    } else if ([seletedParam isEqualToString:@"tgyr_gain"]) {
        tgyr_gainIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tgyr_gain")];
    } else if ([seletedParam isEqualToString:@"tgyr_up"]) {
        tgyr_upIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tgyr_up")];
    } else if ([seletedParam isEqualToString:@"tgyr_down"]) {
        tgyr_downIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        osfprojIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/tgyr_down")];
    } else if ([seletedParam isEqualToString:@"osfproj"]) {
        osfprojIsOn = true;
        antirebonIsOn = false;
        hpIsOn = false;
        lpIsOn = false;
        shok_thrIsOn= false;
        tacc_thrIsOn= false;
        tacc_gainIsOn= false;
        tacc_upIsOn= false;
        tacc_downIsOn= false;
        tgyr_thrIsOn= false;
        tgyr_gainIsOn= false;
        tgyr_upIsOn= false;
        tgyr_downIsOn= false;
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue("/Motion/osfproj")];
    }


}

// number Of Components
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

// number Of Rows In Component
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:   (NSInteger)component
{
    
    _motionParamArray = @[@"hp",@"shok_thr",@"antirebon",@"lp",@"tacc_thr",
                          @"tacc_gain",@"tacc_up",@"tacc_down",@"tgyr_thr",
                          @"tgyr_gain",@"tgyr_up",@"tgyr_down",@"osfproj"];
    return _motionParamArray.count;
}


- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component{
    
    _motionParamArray = @[@"hp",@"shok_thr",@"antirebon",@"lp",@"tacc_thr",
                          @"tacc_gain",@"tacc_up",@"tacc_down",@"tgyr_thr",
                          @"tgyr_gain",@"tgyr_up",@"tgyr_down",@"osfproj"];
    return _motionParamArray[row];

}

- (IBAction)motionParamSend:(id)sender {
    
    [_motionParam resignFirstResponder];
    
    if (lpIsOn) {
        dspFaustMotion->setParamValue("/Motion/lp", [_motionParam.text floatValue]);
    }else if (hpIsOn) {
        dspFaustMotion->setParamValue("/Motion/hp", [_motionParam.text floatValue]);
    }else if (shok_thrIsOn) {
        dspFaustMotion->setParamValue("/Motion/shok_thr", [_motionParam.text floatValue]);
    }else if (antirebonIsOn) {
        dspFaustMotion->setParamValue("/Motion/antirebon", [_motionParam.text floatValue]);
    }else if (tacc_thrIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_thr", [_motionParam.text floatValue]);
    }else if (tacc_gainIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_gain", [_motionParam.text floatValue]);
    }else if (tacc_upIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_up", [_motionParam.text floatValue]);
    }else if (tacc_downIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_down", [_motionParam.text floatValue]);
    }else if (tgyr_thrIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_thr", [_motionParam.text floatValue]);
    }else if (tgyr_gainIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_gain", [_motionParam.text floatValue]);
    }else if (tgyr_upIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_up", [_motionParam.text floatValue]);
    }else if (tgyr_downIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_down", [_motionParam.text floatValue]);
    }else if (osfprojIsOn) {
        dspFaustMotion->setParamValue("/Motion/osfproj", [_motionParam.text floatValue]);
        
    }
    
}


- (void)dealloc {
    [_touch release];
    [_cue release];
    [_tips release];
    [_ip release];
    [_inPort release];
    [_outPort release];
    [_setParam release];
    [_setOSC release];
    [_titleApp release];
    [_init release];
    [_pikerView release];
    [_motionParam release];
    [_motionParamSend release];
    [super dealloc];
}
- (void)viewDidUnload {
    [super viewDidUnload];
    [self stopMotion];
    [self stopUpdateGUI];
}




// Display the title
- (void)displayTitle
{
    NSString* titleString = nil;
    
    
    if (dspFaust->getMeta("name") != NULL)
    {
        const char* name = dspFaust->getMeta("name");
        titleString = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
    }
    
    if (dspFaust->getMeta("author") != NULL)
    {
        const char* name = dspFaust->getMeta("author");
        if (titleString)
        {
            titleString = [titleString stringByAppendingFormat:@" | %s", name];
        }
        else
        {
            titleString = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
        }
    }
    
    if (!titleString) titleString = @"Faust | Grame";
    
    _titleApp.text = titleString;
    
}




- (NSUInteger) supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

- (UIInterfaceOrientation) preferredInterfaceOrientationForPresentation {
    return UIInterfaceOrientationPortrait;
}
-(BOOL)prefersStatusBarHidden{
    return YES;
}


@end
