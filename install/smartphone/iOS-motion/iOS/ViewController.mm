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

#define SR 44100
#define bufferSize 256


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
    
    dspFaust = new DspFaust(SR,bufferSize);
    
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
    //other Initialization  OSC / CUE
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
    
    if (cueIsOn) {
        _touch.hidden=false;
        _cue.hidden=false;
        _cueNext.hidden=false;
        _init.hidden=false;
        _cueText.hidden=false;
        _nextCueText.hidden=false;
        _tips.hidden=false;
        _prevCue.hidden=false;
        _nextCue.hidden=false;
    } else {
        _touch.hidden=true;
        _cue.hidden=true;
        _cueNext.hidden=true;
        _init.hidden=true;
        _cueText.hidden=true;
        _nextCueText.hidden=true;
        _tips.hidden=true;
        _prevCue.hidden=true;
        _nextCue.hidden=true;
    }
    
    
    
    [self startMotion];
    
    [self startRotationMatrix];
    
    [self startUpdate];

    [self displayTitle];
    
    
    _pikerView.delegate = self;
    _pikerView.dataSource = self;
    
    _motionParamArray = [[NSMutableArray alloc] init];
    
    NSArray *ParamArray = @[@"hp",@"shok_thr",@"antirebon",@"lp",@"tacc_thr",
                          @"tacc_gain",@"tacc_up",@"tacc_down",@"tgyr_thr",
                          @"tgyr_gain",@"tgyr_up",@"tgyr_down",@"osfproj"];
    
    [_motionParamArray addObjectsFromArray:ParamArray];
    
    
    
    myCueNumArrary = [[NSMutableArray alloc] init];
    
    // load cues
    NSString *pathCue = [NSString stringWithFormat:@"%@/cueNums.txt", [[NSBundle mainBundle] resourcePath]];
    
    NSString *myTextCues = [NSString stringWithContentsOfFile:pathCue encoding:NSUTF8StringEncoding error:nil];
    
    NSArray *myCues = [myTextCues componentsSeparatedByString:@";\n"];
    
    NSLog(@"Cue:%@",myCues);
    [myCueNumArrary addObjectsFromArray:myCues];
    
    cueIndex = 0;
    cueNum = [[myCueNumArrary objectAtIndex:cueIndex] integerValue];
    cueIndexNext = 1;
    cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
    _cue.text = [NSString stringWithFormat:@"%ld",(long)cueNum];
    _cueNext.text = [NSString stringWithFormat:@"%ld",(long)cueNumNext];
    
    
    
    
    myCueTipsArrary = [[NSMutableArray alloc] init];
    
    // load cue Tips
    NSString *pathTips = [NSString stringWithFormat:@"%@/cueTips.txt", [[NSBundle mainBundle] resourcePath]];
    
    NSString *myTextTips = [NSString stringWithContentsOfFile:pathTips encoding:NSUTF8StringEncoding error:nil];
    
    NSArray *myTips = [myTextTips componentsSeparatedByString:@";\n"];
    
    NSLog(@"Tips:%@",myTips);
    [myCueTipsArrary addObjectsFromArray:myTips];
    
    if ([myCueTipsArrary count] != [myCueNumArrary count]) {
        _tips.text = @"!Num of cue and tips must be same!";
    } else {
        _tips.text = [myCueTipsArrary objectAtIndex:0];
    }
    

}


-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:.3];
    [UIView setAnimationBeginsFromCurrentState:TRUE];
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y -250., self.view.frame.size.width, self.view.frame.size.height);
    
    [UIView commitAnimations];
    
    
}


-(void)textFieldDidEndEditing:(UITextField *)textField
{
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:.3];
    [UIView setAnimationBeginsFromCurrentState:TRUE];
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y +250., self.view.frame.size.width, self.view.frame.size.height);
    
    [UIView commitAnimations];
    
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
        } else if ([data hasSuffix:@"/brasG_cours"]) {
            brasGcoursIsOn = true;
            brasGcoursAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasG_coursOn", 1);
        } else if ([data hasSuffix:@"/brasG_rear"]) {
            brasGrearIsOn = true;
            brasGrearAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasG_rearOn", 1);
        } else if ([data hasSuffix:@"/brasG_jardin"]) {
            brasGjardinIsOn = true;
            brasGjardinAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasG_jardinOn", 1);
        } else if ([data hasSuffix:@"/brasG_front"]) {
            brasGfrontIsOn = true;
            brasGfrontAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasG_frontOn", 1);
        } else if ([data hasSuffix:@"/brasG_down"]) {
            brasGdownIsOn = true;
            brasGdownAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasG_downOn", 1);
        } else if ([data hasSuffix:@"/brasG_up"]) {
            brasGupIsOn = true;
            brasGupAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasG_upOn", 1);
        } else if ([data hasSuffix:@"/pieds_cours"]) {
            piedscoursIsOn = true;
            piedscoursAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pieds_coursOn", 1);
        } else if ([data hasSuffix:@"/pieds_rear"]) {
            piedsrearIsOn = true;
            piedsrearAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pieds_rearOn", 1);
        } else if ([data hasSuffix:@"/pieds_jardin"]) {
            piedsjardinIsOn = true;
            piedsjardinAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pieds_jardinOn", 1);
        } else if ([data hasSuffix:@"/pieds_front"]) {
            piedsfrontIsOn = true;
            piedsfrontAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pieds_frontOn", 1);
        } else if ([data hasSuffix:@"/pieds_down"]) {
            piedsdownIsOn = true;
            piedsdownAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pieds_downOn", 1);
        } else if ([data hasSuffix:@"/pieds_up"]) {
            piedsupIsOn = true;
            piedsupAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/pieds_upOn", 1);
        } else if ([data hasSuffix:@"/dos_cours"]) {
            doscoursIsOn = true;
            doscoursAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/dos_coursOn", 1);
        } else if ([data hasSuffix:@"/dos_rear"]) {
            dosrearIsOn = true;
            dosrearAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/dos_rearOn", 1);
        } else if ([data hasSuffix:@"/dos_jardin"]) {
            dosjardinIsOn = true;
            dosjardinAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/dos_jardinOn", 1);
        } else if ([data hasSuffix:@"/dos_front"]) {
            dosfrontIsOn = true;
            dosfrontAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/dos_frontOn", 1);
        } else if ([data hasSuffix:@"/dos_down"]) {
            dosdownIsOn = true;
            dosdownAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/dos_downOn", 1);
        } else if ([data hasSuffix:@"/dos_up"]) {
            dosupIsOn = true;
            dosupAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/dos_upOn", 1);
        } else if ([data hasSuffix:@"/brasD_cours"]) {
            brasDcoursIsOn = true;
            brasDcoursAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasD_coursOn", 1);
        } else if ([data hasSuffix:@"/brasD_rear"]) {
            brasDrearIsOn = true;
            brasDrearAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasD_rearOn", 1);
        } else if ([data hasSuffix:@"/brasD_jardin"]) {
            brasDjardinIsOn = true;
            brasDjardinAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasD_jardinOn", 1);
        } else if ([data hasSuffix:@"/brasD_front"]) {
            brasDfrontIsOn = true;
            brasDfrontAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasD_frontOn", 1);
        } else if ([data hasSuffix:@"/brasD_down"]) {
            brasDdownIsOn = true;
            brasDdownAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasD_downOn", 1);
        } else if ([data hasSuffix:@"/brasD_up"]) {
            brasDupIsOn = true;
            brasDupAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/brasD_upOn", 1);
        } else if ([data hasSuffix:@"/tete_cours"]) {
            tetecoursIsOn = true;
            tetecoursAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/tete_coursOn", 1);
        } else if ([data hasSuffix:@"/tete_rear"]) {
            teterearIsOn = true;
            teterearAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/tete_rearOn", 1);
        } else if ([data hasSuffix:@"/tete_jardin"]) {
            tetejardinIsOn = true;
            tetejardinAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/tete_jardinOn", 1);
        } else if ([data hasSuffix:@"/tete_front"]) {
            tetefrontIsOn = true;
            tetefrontAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/tete_frontOn", 1);
        } else if ([data hasSuffix:@"/tete_down"]) {
            tetedownIsOn = true;
            tetedownAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/tete_downOn", 1);
        } else if ([data hasSuffix:@"/tete_up"]) {
            teteupIsOn = true;
            teteupAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/tete_upOn", 1);
        }else if ([data hasSuffix:@"/ventre_cours"]) {
            ventrecoursIsOn = true;
            ventrecoursAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ventre_coursOn", 1);
        } else if ([data hasSuffix:@"/ventre_rear"]) {
            ventrerearIsOn = true;
            ventrerearAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ventre_rearOn", 1);
        } else if ([data hasSuffix:@"/ventre_jardin"]) {
            ventrejardinIsOn = true;
            ventrejardinAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ventre_jardinOn", 1);
        } else if ([data hasSuffix:@"/ventre_front"]) {
            ventrefrontIsOn = true;
            ventrefrontAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ventre_frontOn", 1);
        } else if ([data hasSuffix:@"/ventre_down"]) {
            ventredownIsOn = true;
            ventredownAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ventre_downOn", 1);
        } else if ([data hasSuffix:@"/ventre_up"]) {
            ventreupIsOn = true;
            ventreupAddress = dspFaust->getParamAddress(i);
            dspFaustMotion->setParamValue("/Motion/ventre_upOn", 1);
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

- (void)startUpdate
{
    
    _sensorTimer = [NSTimer scheduledTimerWithTimeInterval:1./(SR/bufferSize) target:self
                                            selector:@selector(updateMotion) userInfo:nil repeats:YES];
    
}

// Stop updating
- (void)stopUpdate
{
    
    [_sensorTimer invalidate];
    
    
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
        [_motionManager stopDeviceMotionUpdates];
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
    if (brasGcoursIsOn) {
        dspFaust->setParamValue(brasGcoursAddress, dspFaustMotion->getParamValue("/Motion/brasG_cours"));
    }
    if (brasGrearIsOn) {
        dspFaust->setParamValue(brasGrearAddress, dspFaustMotion->getParamValue("/Motion/bras_Grear"));
    }
    if (brasGjardinIsOn) {
        dspFaust->setParamValue(brasGjardinAddress, dspFaustMotion->getParamValue("/Motion/brasG_jardin"));
    }
    if (brasGfrontIsOn) {
        dspFaust->setParamValue(brasGfrontAddress, dspFaustMotion->getParamValue("/Motion/brasG_front"));
    }
    if (brasGdownIsOn) {
        dspFaust->setParamValue(brasGdownAddress, dspFaustMotion->getParamValue("/Motion/brasG_down"));
    }
    if (brasGupIsOn) {
        dspFaust->setParamValue(brasGupAddress, dspFaustMotion->getParamValue("/Motion/brasG_up"));
    }
    if (piedscoursIsOn) {
        dspFaust->setParamValue(piedscoursAddress, dspFaustMotion->getParamValue("/Motion/pieds_cours"));
    }
    if (piedsrearIsOn) {
        dspFaust->setParamValue(piedsrearAddress, dspFaustMotion->getParamValue("/Motion/pieds_Grear"));
    }
    if (piedsjardinIsOn) {
        dspFaust->setParamValue(piedsjardinAddress, dspFaustMotion->getParamValue("/Motion/pieds_jardin"));
    }
    if (piedsfrontIsOn) {
        dspFaust->setParamValue(piedsfrontAddress, dspFaustMotion->getParamValue("/Motion/pieds_front"));
    }
    if (piedsdownIsOn) {
        dspFaust->setParamValue(piedsdownAddress, dspFaustMotion->getParamValue("/Motion/pieds_down"));
    }
    if (piedsupIsOn) {
        dspFaust->setParamValue(piedsupAddress, dspFaustMotion->getParamValue("/Motion/pieds_up"));
    }
    if (doscoursIsOn) {
        dspFaust->setParamValue(doscoursAddress, dspFaustMotion->getParamValue("/Motion/dos_cours"));
    }
    if (dosrearIsOn) {
        dspFaust->setParamValue(dosrearAddress, dspFaustMotion->getParamValue("/Motion/dos_Grear"));
    }
    if (dosjardinIsOn) {
        dspFaust->setParamValue(dosjardinAddress, dspFaustMotion->getParamValue("/Motion/dos_jardin"));
    }
    if (dosfrontIsOn) {
        dspFaust->setParamValue(dosfrontAddress, dspFaustMotion->getParamValue("/Motion/dos_front"));
    }
    if (dosdownIsOn) {
        dspFaust->setParamValue(dosdownAddress, dspFaustMotion->getParamValue("/Motion/dos_down"));
    }
    if (dosupIsOn) {
        dspFaust->setParamValue(dosupAddress, dspFaustMotion->getParamValue("/Motion/dos_up"));
    }
    if (brasDcoursIsOn) {
        dspFaust->setParamValue(brasDcoursAddress, dspFaustMotion->getParamValue("/Motion/brasD_cours"));
    }
    if (brasDrearIsOn) {
        dspFaust->setParamValue(brasDrearAddress, dspFaustMotion->getParamValue("/Motion/brasD_Grear"));
    }
    if (brasDjardinIsOn) {
        dspFaust->setParamValue(brasDjardinAddress, dspFaustMotion->getParamValue("/Motion/brasD_jardin"));
    }
    if (brasDfrontIsOn) {
        dspFaust->setParamValue(brasDfrontAddress, dspFaustMotion->getParamValue("/Motion/brasD_front"));
    }
    if (brasDdownIsOn) {
        dspFaust->setParamValue(brasDdownAddress, dspFaustMotion->getParamValue("/Motion/brasD_down"));
    }
    if (brasDupIsOn) {
        dspFaust->setParamValue(brasDupAddress, dspFaustMotion->getParamValue("/Motion/brasD_up"));
    }
    if (tetecoursIsOn) {
        dspFaust->setParamValue(tetecoursAddress, dspFaustMotion->getParamValue("/Motion/tete_cours"));
    }
    if (teterearIsOn) {
        dspFaust->setParamValue(teterearAddress, dspFaustMotion->getParamValue("/Motion/tete_Grear"));
    }
    if (tetejardinIsOn) {
        dspFaust->setParamValue(tetejardinAddress, dspFaustMotion->getParamValue("/Motion/tete_jardin"));
    }
    if (tetefrontIsOn) {
        dspFaust->setParamValue(tetefrontAddress, dspFaustMotion->getParamValue("/Motion/tete_front"));
    }
    if (tetedownIsOn) {
        dspFaust->setParamValue(tetedownAddress, dspFaustMotion->getParamValue("/Motion/tete_down"));
    }
    if (teteupIsOn) {
        dspFaust->setParamValue(teteupAddress, dspFaustMotion->getParamValue("/Motion/tete_up"));
    }
    if (ventrecoursIsOn) {
        dspFaust->setParamValue(ventrecoursAddress, dspFaustMotion->getParamValue("/Motion/ventre_cours"));
    }
    if (ventrerearIsOn) {
        dspFaust->setParamValue(ventrerearAddress, dspFaustMotion->getParamValue("/Motion/ventre_Grear"));
    }
    if (ventrejardinIsOn) {
        dspFaust->setParamValue(ventrejardinAddress, dspFaustMotion->getParamValue("/Motion/ventre_jardin"));
    }
    if (ventrefrontIsOn) {
        dspFaust->setParamValue(ventrefrontAddress, dspFaustMotion->getParamValue("/Motion/ventre_front"));
    }
    if (ventredownIsOn) {
        dspFaust->setParamValue(ventredownAddress, dspFaustMotion->getParamValue("/Motion/ventre_down"));
    }
    if (ventreupIsOn) {
        dspFaust->setParamValue(ventreupAddress, dspFaustMotion->getParamValue("/Motion/ventre_up"));
    }
}

- (void)startRotationMatrix
{
    
    CGFloat updateInterval = 1./(SR/bufferSize);
    //referenceAttitude = _motionManager.deviceMotion.attitude;
    // delay pour init frame
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self initFrame];
    });
    [_motionManager setDeviceMotionUpdateInterval:updateInterval];
    NSOperationQueue *motionQueue = [[NSOperationQueue alloc] init];
    [_motionManager startDeviceMotionUpdatesToQueue: motionQueue
                                       withHandler:^(CMDeviceMotion* motion, NSError* error){
                                           
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            
            referenceMatrix = motion.attitude.rotationMatrix;
            
            matrixA[0][0] =motion.attitude.rotationMatrix.m11;
            matrixA[0][1] =motion.attitude.rotationMatrix.m12;
            matrixA[0][2] =motion.attitude.rotationMatrix.m13;
            
            matrixA[1][0] =motion.attitude.rotationMatrix.m21;
            matrixA[1][1] =motion.attitude.rotationMatrix.m22;
            matrixA[1][2] =motion.attitude.rotationMatrix.m23;
            
            matrixA[2][0] =motion.attitude.rotationMatrix.m31;
            matrixA[2][1] =motion.attitude.rotationMatrix.m32;
            matrixA[2][2] =motion.attitude.rotationMatrix.m33;
            
            vDSP_mmul(&matrixA[0][0], 1, &matrixB[0][0], 1, &matrixC[0][0], 1, 3, 3, 3);
            
            dspFaustMotion->setParamValue("/Motion/brasG_x", matrixC[0][0]);
            dspFaustMotion->setParamValue("/Motion/brasG_y", matrixC[0][1]);
            dspFaustMotion->setParamValue("/Motion/brasG_z", matrixC[0][2]);
            
            dspFaustMotion->setParamValue("/Motion/pieds_x", matrixC[1][0]);
            dspFaustMotion->setParamValue("/Motion/pieds_y", matrixC[1][1]);
            dspFaustMotion->setParamValue("/Motion/pieds_z", matrixC[1][2]);
            
            dspFaustMotion->setParamValue("/Motion/dos_x", matrixC[2][0]);
            dspFaustMotion->setParamValue("/Motion/dos_y", matrixC[2][1]);
            dspFaustMotion->setParamValue("/Motion/dos_z", matrixC[2][2]);
            
            dspFaustMotion->setParamValue("/Motion/brasD_x", (-1)*matrixC[0][0]);
            dspFaustMotion->setParamValue("/Motion/brasD_y", (-1)*matrixC[0][1]);
            dspFaustMotion->setParamValue("/Motion/brasD_z", (-1)*matrixC[0][2]);
            
            dspFaustMotion->setParamValue("/Motion/tete_x", (-1)*matrixC[1][0]);
            dspFaustMotion->setParamValue("/Motion/tete_y", (-1)*matrixC[1][1]);
            dspFaustMotion->setParamValue("/Motion/tete_z", (-1)*matrixC[1][2]);
            
            dspFaustMotion->setParamValue("/Motion/ventre_x", (-1)*matrixC[2][0]);
            dspFaustMotion->setParamValue("/Motion/ventre_y", (-1)*matrixC[2][1]);
            dspFaustMotion->setParamValue("/Motion/ventre_z", (-1)*matrixC[2][2]);
            
            /* crash... comment for now
            if (referenceAttitude != nil) {
                [motion.attitude multiplyByInverseOfAttitude:referenceAttitude];
                }

                dspFaustMotion->setParamValue("/Motion/brasG_x", motion.attitude.rotationMatrix.m11);
                dspFaustMotion->setParamValue("/Motion/brasG_y", motion.attitude.rotationMatrix.m12);
                dspFaustMotion->setParamValue("/Motion/brasG_z", motion.attitude.rotationMatrix.m13);
            
                dspFaustMotion->setParamValue("/Motion/pieds_x", motion.attitude.rotationMatrix.m21);
                dspFaustMotion->setParamValue("/Motion/pieds_y", motion.attitude.rotationMatrix.m22);
                dspFaustMotion->setParamValue("/Motion/pieds_z", motion.attitude.rotationMatrix.m23);
            
                dspFaustMotion->setParamValue("/Motion/dos_x", motion.attitude.rotationMatrix.m31);
                dspFaustMotion->setParamValue("/Motion/dos_y", motion.attitude.rotationMatrix.m32);
                dspFaustMotion->setParamValue("/Motion/dos_z", motion.attitude.rotationMatrix.m33);
            
                dspFaustMotion->setParamValue("/Motion/brasD_x", (-1)*motion.attitude.rotationMatrix.m11);
                dspFaustMotion->setParamValue("/Motion/brasD_y", (-1)*motion.attitude.rotationMatrix.m12);
                dspFaustMotion->setParamValue("/Motion/brasD_z", (-1)*motion.attitude.rotationMatrix.m13);
            
                dspFaustMotion->setParamValue("/Motion/tete_x", (-1)*motion.attitude.rotationMatrix.m21);
                dspFaustMotion->setParamValue("/Motion/tete_y", (-1)*motion.attitude.rotationMatrix.m22);
                dspFaustMotion->setParamValue("/Motion/tete_z", (-1)*motion.attitude.rotationMatrix.m23);
            
                dspFaustMotion->setParamValue("/Motion/ventre_x", (-1)*motion.attitude.rotationMatrix.m31);
                dspFaustMotion->setParamValue("/Motion/ventre_y", (-1)*motion.attitude.rotationMatrix.m32);
                dspFaustMotion->setParamValue("/Motion/ventre_z", (-1)*motion.attitude.rotationMatrix.m33);
             */
            
            }];
    }];
    
}

-(void) initFrame {
    
    // referenceAttitude is an instance variable
    if (_motionManager!=nil) {
        
        // inverse matrix the matrix reference
        float a11 = referenceMatrix.m11;
        float a12 = referenceMatrix.m12;
        float a13 = referenceMatrix.m13;
        float a21 = referenceMatrix.m21;
        float a22 = referenceMatrix.m22;
        float a23 = referenceMatrix.m23;
        float a31 = referenceMatrix.m31;
        float a32 = referenceMatrix.m32;
        float a33 = referenceMatrix.m33;
        
        float detA=a11*a22*a33+a21*a32*a13+a31*a12*a23-a11*a32*a23-a31*a22*a13-a21*a12*a33;
        
        matrixB[0][0] =(1/detA)*(a22*a33-a23*a32);
        matrixB[0][1] =(1/detA)*(a13*a32-a12*a33);
        matrixB[0][2] =(1/detA)*(a12*a23-a13*a22);
        
        matrixB[1][0] =(1/detA)*(a23*a31-a21*a33);
        matrixB[1][1] =(1/detA)*(a11*a33-a13*a31);
        matrixB[1][2] =(1/detA)*(a13*a21-a11*a23);
        
        matrixB[2][0] =(1/detA)*(a21*a32-a22*a31);
        matrixB[2][1] =(1/detA)*(a12*a31-a11*a32);
        matrixB[2][2] =(1/detA)*(a11*a22-a12*a21);
        //referenceAttitude = _motionManager.deviceMotion.attitude;
        
    }
    
    
}

- (IBAction)setRef:(id)sender {
    
    [self initFrame];
    
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
    CGFloat pointY = point.y/(screenHeight/2);
    
    if (cueIsOn) {
    
    if (point.y < screenHeight/2) {
        
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
    CGFloat pointY = point.y/(screenHeight/2.0f);
    
    if (cueIsOn) {
        
    if (point.y < screenHeight/2) {
        
        if (screenXIsOn) {
        dspFaust->setParamValue(screenXAddress, (float)pointX);
        }
        if (screenYIsOn) {
        dspFaust->setParamValue(screenYAddress, pointY);
        }
 
    }
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
    CGFloat pointY = point.y/(screenHeight/2);
    
    if (cueIsOn) {
        
    if (point.y < screenHeight/2) {
        if (touchGateIsOn) {
    
        dspFaust->setParamValue(touchGateAddress, 0);
        _touch.alpha=0.1;
        }
        
        if (point.y < screenHeight/2) {
            if (screenXIsOn) {
                dspFaust->setParamValue(screenXAddress, pointX);
            }
            if (screenYIsOn) {
                dspFaust->setParamValue(screenYAddress, pointY);
            }
        }
    }
    }
}


-(void) counter {
    
    
    cueIndex = cueIndexNext;
    cueNum = [[myCueNumArrary objectAtIndex:cueIndex] integerValue];
    _cue.text= [NSString stringWithFormat:@"%ld",(long)cueNum];
    _tips.text = [myCueTipsArrary objectAtIndex:cueIndex];
    if (cueIsOn) {
        dspFaust->setParamValue(cueAddress, cueNum);
    }
    if (cueIndexNext < [myCueNumArrary count] -1) {
    cueIndexNext++;
    cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
    _cueNext.text= [NSString stringWithFormat:@"%ld",(long)cueNumNext];
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
        _pikerView.hidden= false;
        _motionParam.hidden=false;
        _motionParamSend.hidden=false;
        _initParam.hidden=false;
        _setRefrence.hidden=false;
        
    } else {
        _ip.hidden=true;
        _inPort.hidden=true;
        _outPort.hidden=true;
        _setOSC.hidden=true;
        _initParam.hidden=true;
        _pikerView.hidden= true;
        _motionParam.hidden=true;
        _motionParamSend.hidden=true;
        _setRefrence.hidden=true;
    
    }
    
}

- (IBAction)initCue:(id)sender {
    
    cueIndex = 0;
    cueNum = [[myCueNumArrary objectAtIndex:cueIndex] integerValue];
    _cue.text= [NSString stringWithFormat:@"%ld",(long)cueNum];
    cueIndexNext = 1;
    cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
    _cueNext.text= [NSString stringWithFormat:@"%ld",(long)cueNumNext];
    if (cueIsOn) {
        dspFaust->setParamValue(cueAddress, cueNum);
    }
    _tips.text = [myCueTipsArrary objectAtIndex:0];
    
}



- (IBAction)nextCue:(id)sender {
    
    if (cueIndexNext < [myCueNumArrary count] -1) {
        cueIndexNext++;
        cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
        _cueNext.text= [NSString stringWithFormat:@"%ld",(long)cueNumNext];
        _tips.text = [myCueTipsArrary objectAtIndex:cueIndexNext];
    }
    
}

- (IBAction)prevCue:(id)sender {
    
    if (cueIndexNext > 0) {
    cueIndexNext--;
    cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
    _cueNext.text= [NSString stringWithFormat:@"%ld",(long)cueNumNext];
    _tips.text = [myCueTipsArrary objectAtIndex:cueIndexNext];
    }
}


- (IBAction)defautParam:(id)sender {

    
    [_ip resignFirstResponder];
    [_inPort resignFirstResponder];
    [_outPort resignFirstResponder];
    [_motionParam resignFirstResponder];

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
    
    label.text = [_motionParamArray objectAtIndex:row];
    return label;
}



-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    
    
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
    
   
    return _motionParamArray.count;
}


- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component{
    
    
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
    [_initParam release];
    [_nextCue release];
    [_prevCue release];
    [_cueNext release];
    [_nextCueText release];
    [_cueText release];
    [_setRefrence release];
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
