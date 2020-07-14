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
    _pikerView.delegate = self;
    _pikerView.dataSource = self;
    
    ////////////////////
    // init faust motor
    ////////////////////
    
    //dspFaustMotion = new DspFaustMotion(SR/bufferSize,1);   //trop lent
    dspFaustMotion = new DspFaustMotion(SR, bufferSize);
    
    dspFaust = new DspFaust(dspFaustMotion,SR,bufferSize);
    
    ////////////////////////////////
    //Check the MetaData in console
    ///////////////////////////////
    
    NSLog(@"Faust Metadata: %s", dspFaust->getJSONUI());
    NSLog(@"Motion Metadata: %s", dspFaustMotion->getJSONUI());
    
    //////////////////////////
    // start FAUST
    ///////////////////////////
    dspFaust->start();
    dspFaustMotion->start();
    
    ///////////////////////////////////
    // check motion key word in address
    ///////////////////////////////////
    
    dspFaust->checkAdress();
    [self checkAddress];
    
    // LOAD preset
    [self loadDefaultParams];
    
    
    ///////////////////////
    //other Initialization
    ///////////////////////
    //There are two methods to receive data from CMMotionManager: push and pull.
    //Using push for now
    
    [self startMotion];
    
    [self startRotationMatrix];
    
    [self startAccelerometer];
    
    [self startGyroscope];
    
    [self startUpdateGUI];
    
    [self displayTitle];
    
    
    
    if (cueIsOn) {
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
    
    if (dspFaust->getOSCIsOn()) {
        _ip.enabled=true;
        _inPort.enabled=true;
        _outPort.enabled=true;
        _setOSC.enabled=true;
        _ip.alpha=1;
        _inPort.alpha=1;
        _outPort.alpha=1;
        _setOSC.alpha=1;
        _ip.text=oscAddress;
        _inPort.text=oscInPort;
        _outPort.text=oscOutPort;
    } else {
        _ip.hidden=false;
        _inPort.enabled=false;
        _outPort.enabled=false;
        _setOSC.enabled=false;
        _ip.alpha=0;
        _inPort.alpha=0;
        _outPort.alpha=0;
        _setOSC.alpha=0;
        _ip.text=@"NO";
        _inPort.text=@"NO";
        _outPort.text=@"NO";
    }
    
    if (cueIsOn) {
        _cue.hidden=false;
        _cueNext.hidden=false;
        
        _cueText.hidden=false;
        _nextCueText.hidden=false;
        
        _prevCue.hidden=false;
        _nextCue.hidden=false;
    } else {
        _cue.hidden=true;
        _cueNext.hidden=true;
        
        _cueText.hidden=true;
        _nextCueText.hidden=true;
        
        _prevCue.hidden=true;
        _nextCue.hidden=true;
    }
    
    if (cueIsOn or touchGateIsOn or screenXIsOn or screenYIsOn) {
        _touch.hidden=false;
    } else {
        _touch.hidden=true;
    }
    
    if (cueIsOn or stateIsOn) {
        _init.hidden=false;
        _tips.hidden=false;
    } else {
        _init.hidden=true;
        _tips.hidden=true;
    }
    

    
    
}

- (BOOL) connectedToInternet
{
    NSString *URLString = [NSString stringWithContentsOfURL:[NSURL URLWithString:@"http://www.bing.com"]];
    return ( URLString != NULL ) ? YES : NO;
}


-(void) loadDefaultParams {
    
    NSMutableDictionary *appDefaultsDictionary = [NSMutableDictionary dictionaryWithCapacity:_motionParamAddress.count];
 
    for (int i=0; i<_motionParamAddress.count; i++) {
        [appDefaultsDictionary setValue:
         [NSNumber numberWithFloat:dspFaust->getParamInit([_motionParamAddress[i] UTF8String])] forKey:_motionParamArray[i]];
    }
    
    [appDefaultsDictionary setValue:@"192.168.1.20" forKey:@"oscAddress"];
    [appDefaultsDictionary setValue:@"5510" forKey:@"oscInPort"];
    [appDefaultsDictionary setValue:@"5511" forKey:@"oscOutPort"];
    
    [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaultsDictionary];
    
    for (int i=0; i<_motionParamAddress.count; i++) {
        
        dspFaust->setParamValue([_motionParamAddress[i] UTF8String],
                                      (float)[[NSUserDefaults standardUserDefaults] floatForKey:_motionParamArray[i]]);
        
    }
    
    for (int i=0; i<_motionParamAddress.count; i++) {
        
        dspFaust->setParamValue([_motionParamAddress[i] UTF8String],
                                      (float)[[NSUserDefaults standardUserDefaults] floatForKey:_motionParamArray[i]]);
        
    }
    
    if (dspFaust->getOSCIsOn()) {
        
        [self connectedToInternet];
        
        oscAddress = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscAddress"];
        oscInPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscInPort"];
        oscOutPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscOutPort"];
        
        dspFaust->setOSCValue([oscAddress cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscInPort cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscOutPort cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    }
    
}


-(void) resetDefaultParams {
    
    NSDictionary* dict = [[NSUserDefaults standardUserDefaults] dictionaryRepresentation];
    NSArray* keysArray = [dict allKeys];
    int i = 0;
    NSString* key = nil;
    
    for (i = 0; i < [keysArray count]; ++i)
    {
        key = ((NSString*)[keysArray objectAtIndex:i]);
        [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
    }
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    if (dspFaust->getOSCIsOn()) {
        oscAddress = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscAddress"];
        oscInPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscInPort"];
        oscOutPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscOutPort"];
        
        _ip.text=oscAddress;
        _inPort.text=oscInPort;
        _outPort.text=oscOutPort;
        
        dspFaust->setOSCValue([oscAddress cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscInPort cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscOutPort cStringUsingEncoding:[NSString defaultCStringEncoding]]);
        
        _tips.hidden=false;
        _tips.text = @"RESTART APP for New Setting";
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
    
    std::vector<std::string>motionParamNames;
    std::vector<std::string>motionParamAddress;
    _motionParamArray = [[NSMutableArray alloc] init];
    _motionParamAddress = [[NSMutableArray alloc] init];
    
    for (int i=0; i<dspFaust->getParamsCount(); i++) {
        const char *dataParamMotion = dspFaust->getMetadata(i, "showName");
        if (strcmp(dataParamMotion,"") != 0) {
            motionParamNames.push_back(dataParamMotion);
            motionParamAddress.push_back(dspFaust->getParamAddress(i));
        }
    }
    for (int i=0; i<motionParamNames.size(); i++) {
        //printf("%i=%s",i,motionParamNames[i].c_str());
        [_motionParamArray addObject:[NSString stringWithUTF8String:motionParamNames[i].c_str()]];
        [_motionParamAddress addObject:[NSString stringWithUTF8String:motionParamAddress[i].c_str()]];
    }
    
    paramsOn = new BOOL[_motionParamAddress.count];
    
    for(int i=0; i<dspFaust->getParamsCount(); i++){
        NSString *data = [NSString stringWithUTF8String:dspFaust->getParamAddress(i)];
        if ([data hasSuffix:@"/touchgate"]) {
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
        } else if ([data hasSuffix:@"/yaw"]) {
            yawIsOn = true;
            yawAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/pitch"]) {
            pitchIsOn = true;
            pitchAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/roll"]) {
            rollIsOn = true;
            rollAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/useraccx"]) {
            useraccxIsOn = true;
            useraccxAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/useraccy"]) {
            useraccyIsOn = true;
            useraccyAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/useraccz"]) {
            useracczIsOn = true;
            useracczAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/quaternionw"]) {
            quaternionwIsOn = true;
            quaternionwAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/quaternionx"]) {
            quaternionxIsOn = true;
            quaternionxAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/quaterniony"]) {
            quaternionyIsOn = true;
            quaternionyAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/quaternionz"]) {
            quaternionzIsOn = true;
            quaternionzAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/cue"]) {
            cueIsOn = true;
            cueAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/state"]) {
            stateIsOn = true;
            stateAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/setref_comp"]) {
            setref_compIsOn = true;
            setref_compAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/setref_rota"]) {
            setref_rotaIsOn = true;
            setref_rotaAddress = dspFaust->getParamAddress(i);
        }
        
        //comment init part for now
        //else if ([data hasSuffix:@"/init"]) {
        //initAddress = dspFaust->getParamAddress(i);
        //}
        
    }
    
}

- (void)startMotion
{
    if (_motionManager == nil)
    {
        _motionManager = [[CMMotionManager alloc] init];
        //[_motionManager startAccelerometerUpdates];
        //[_motionManager startGyroUpdates];
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
    
}

/*
 - (void)startUpdate
 {
 
 _sensorTimer = [NSTimer scheduledTimerWithTimeInterval:1.f/(SR/bufferSize) target:self
 selector:@selector(updateMotion) userInfo:nil repeats:YES];
 
 }
 
 // Stop updating
 - (void)stopUpdate
 {
 
 [_sensorTimer invalidate];
 
 
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
 
 
 }
 */

- (void)startAccelerometer
{
    
    CGFloat updateInterval = 1.f/(SR/bufferSize);
    [_motionManager setAccelerometerUpdateInterval:updateInterval];
    NSOperationQueue *AccelerometerQueue = [[NSOperationQueue alloc] init];
    [_motionManager startAccelerometerUpdatesToQueue: AccelerometerQueue
                                         withHandler:^(CMAccelerometerData *accelerometerData, NSError *error){
                                             [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                                                 
                                                 dspFaust->propagateAcc(0, accelerometerData.acceleration.x * ONE_G);
                                                 dspFaust->propagateAcc(1, accelerometerData.acceleration.y * ONE_G);
                                                 dspFaust->propagateAcc(2, accelerometerData.acceleration.z * ONE_G);
                                                 dspFaustMotion->propagateAcc(0, accelerometerData.acceleration.x * ONE_G);
                                                 dspFaustMotion->propagateAcc(1, accelerometerData.acceleration.y * ONE_G);
                                                 dspFaustMotion->propagateAcc(2, accelerometerData.acceleration.z * ONE_G);
                                                 
                                             }];
                                         }];
    
}

- (void)startGyroscope
{
    
    CGFloat updateInterval = 1.f/(SR/bufferSize);
    [_motionManager setGyroUpdateInterval:updateInterval];
    NSOperationQueue *GyroscopeQueue = [[NSOperationQueue alloc] init];
    [_motionManager startGyroUpdatesToQueue: GyroscopeQueue
                                withHandler:^(CMGyroData *gyroData, NSError *error){
                                    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                                        
                                        dspFaust->propagateGyr(0, gyroData.rotationRate.x);
                                        dspFaust->propagateGyr(1, gyroData.rotationRate.y);
                                        dspFaust->propagateGyr(2, gyroData.rotationRate.z);
                                        dspFaustMotion->propagateGyr(0, gyroData.rotationRate.x);
                                        dspFaustMotion->propagateGyr(1, gyroData.rotationRate.y);
                                        dspFaustMotion->propagateGyr(2, gyroData.rotationRate.z);
                                        
                                    }];
                                }];
    
}


- (void)startRotationMatrix
{
    
    CGFloat updateInterval = 1.f/(SR/bufferSize);
    //referenceAttitude = _motionManager.deviceMotion.attitude;
    // delay pour init frame
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self initFrame];
    });
    [_motionManager setDeviceMotionUpdateInterval:updateInterval];
    NSOperationQueue *rotationMatrixQueue = [[NSOperationQueue alloc] init];
    [_motionManager startDeviceMotionUpdatesToQueue: rotationMatrixQueue
                                        withHandler:^(CMDeviceMotion* motion, NSError* error){
                                            
                                            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                                                
                                                dspFaust->motionRender(motion.attitude.rotationMatrix.m11,motion.attitude.rotationMatrix.m12,motion.attitude.rotationMatrix.m13,motion.attitude.rotationMatrix.m21,motion.attitude.rotationMatrix.m22,motion.attitude.rotationMatrix.m23,motion.attitude.rotationMatrix.m31,motion.attitude.rotationMatrix.m32,motion.attitude.rotationMatrix.m33);
                                                
                                                // set reference frame
                                                if (referenceAttitude != nil) {
                                                    [motion.attitude multiplyByInverseOfAttitude:referenceAttitude];
                                                }
                                                
                                                if (yawIsOn) {
                                                    dspFaust->setParamValue(yawAddress, motion.attitude.yaw);
                                                }
                                                if (pitchIsOn) {
                                                    dspFaust->setParamValue(pitchAddress, motion.attitude.pitch);
                                                }
                                                if (rollIsOn) {
                                                    dspFaust->setParamValue(rollAddress, motion.attitude.roll);
                                                }
                                                if (useraccxIsOn) {
                                                    dspFaust->setParamValue(useraccxAddress, motion.userAcceleration.x);
                                                }
                                                if (useraccyIsOn) {
                                                    dspFaust->setParamValue(useraccyAddress, motion.userAcceleration.y);
                                                }
                                                if (useracczIsOn) {
                                                    dspFaust->setParamValue(useracczAddress, motion.userAcceleration.z);
                                                }
                                                if (quaternionwIsOn) {
                                                    dspFaust->setParamValue(quaternionwAddress, motion.attitude.quaternion.w);
                                                }
                                                if (quaternionxIsOn) {
                                                    dspFaust->setParamValue(quaternionxAddress, motion.attitude.quaternion.x);
                                                }
                                                if (quaternionyIsOn) {
                                                    dspFaust->setParamValue(quaternionyAddress, motion.attitude.quaternion.y);
                                                }
                                                if (quaternionzIsOn) {
                                                    dspFaust->setParamValue(quaternionzAddress, motion.attitude.quaternion.z);
                                                }
                                                
                                            }];
                                        }];
    
}

-(void) initFrame {
    
    if (_motionManager!=nil) {
        
        // using the calcul de matrix for rotation matrix(compatible with previous version), using the global reference way for others(yaw/quatarnion)
        dspFaust->initFrame();
        referenceAttitude = [_motionManager.deviceMotion.attitude copy];
    }
    
    
}

- (IBAction)setRef:(id)sender {
    
    [self initFrame];
    
    
}



- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading{
    
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
    
    if (magneticHeadingIsOn) {
        dspFaust->setParamValue(magneticHeadingAddress, magneticNew);
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
    if (stateIsOn) {
        _tips.text = [NSString stringWithFormat:@"State = %1.f", dspFaust->getParamValue(stateAddress)];
    }
    
    if (setref_compIsOn && dspFaust->getParamValue(setref_compAddress)==1) {
        
        if (cnt<2) {
            offset = magnetic;
            NSLog(@"initCompass");
            cnt++;
        }
    } else{
        cnt=1;
    }
    
    if (setref_rotaIsOn && dspFaust->getParamValue(setref_rotaAddress)==1) {
        if (cnt2<2) {
            [self initFrame];
            NSLog(@"initRotation");
            cnt2++;
        }
    } else{
        cnt2=1;
    }
    
}

- (void) touchesBegan:(NSSet *)touches
            withEvent:(UIEvent *)event {
    
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self.view];
    
    CGFloat screenWidth = [[UIScreen mainScreen] bounds].size.width;
    CGFloat screenHeight = [[UIScreen mainScreen] bounds].size.height;
    
    if (point.y < screenHeight/2) {
        
        CGFloat pointX = point.x/screenWidth;
        CGFloat pointY = point.y/(screenHeight/2);
        
        if (touchGateIsOn) {
            dspFaust->setParamValue(touchGateAddress, 1);
            _touch.alpha=1;
        }
        if (cueIsOn) {
            [self counter];
            _touch.alpha=1;
        }
        
        if (screenXIsOn) {
            dspFaust->setParamValue(screenXAddress, pointX);
            _touch.alpha=1;
        }
        if (screenYIsOn) {
            dspFaust->setParamValue(screenYAddress, (1.f-pointY));
            _touch.alpha=1;
        }
        
    }
    
}

- (void) touchesMoved:(NSSet *)touches
            withEvent:(UIEvent *)event {
    
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self.view];
    
    CGFloat screenWidth = [[UIScreen mainScreen] bounds].size.width;
    CGFloat screenHeight = [[UIScreen mainScreen] bounds].size.height;
    
    if (point.y < screenHeight/2) {
        
        CGFloat pointX = point.x/screenWidth;
        CGFloat pointY = point.y/(screenHeight/2);
        
        if (screenXIsOn) {
            dspFaust->setParamValue(screenXAddress, pointX);
        }
        if (screenYIsOn) {
            dspFaust->setParamValue(screenYAddress, (1.f-pointY));
        }
        
    }
    
    
}

- (void) touchesEnded:(NSSet *)touches
            withEvent:(UIEvent *)event {
    
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self.view];
    
    CGFloat screenWidth = [[UIScreen mainScreen] bounds].size.width;
    CGFloat screenHeight = [[UIScreen mainScreen] bounds].size.height;
    
    if (point.y < screenHeight/2) {
        
        CGFloat pointX = point.x/screenWidth;
        CGFloat pointY = point.y/(screenHeight/2);
        
        if (touchGateIsOn) {
            dspFaust->setParamValue(touchGateAddress, 0);
            _touch.alpha=0.1;
        }
        
        if (screenXIsOn) {
            dspFaust->setParamValue(screenXAddress, pointX);
            _touch.alpha=0.1;
        }
        
        if (screenYIsOn) {
            dspFaust->setParamValue(screenYAddress, (1.f-pointY));
            _touch.alpha=0.1;
        }
    } else {
        
        if (touchGateIsOn) {
            _touch.alpha=0.1;
        }
        
        if (screenXIsOn) {
            _touch.alpha=0.1;
        }
        
        if (screenYIsOn) {
            _touch.alpha=0.1;
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
    
    _tips.hidden=false;
    _tips.text = @"RESTART APP for New Setting";
    
    [[NSUserDefaults standardUserDefaults] setObject:_oscIPOutputText forKey:@"oscAddress"];
    [[NSUserDefaults standardUserDefaults] setObject:_oscInputPortText forKey:@"oscInPort"];
    [[NSUserDefaults standardUserDefaults] setObject:_oscOutputPortText forKey:@"oscOutPort"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (IBAction)setParam:(id)sender {
    
    if (_setParam.isOn) {
        _ip.hidden=false;
        _inPort.hidden=false;
        _outPort.hidden=false;
        _setOSC.hidden=false;
        if (_motionParamArray.count != 0) {
            _pikerView.hidden = false;
            _motionParam.hidden=false;
            _motionParamSend.hidden=false;
            _initParam.hidden=false;
        }
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
    
    if (cueIsOn) {
        cueIndex = 0;
        cueNum = [[myCueNumArrary objectAtIndex:cueIndex] integerValue];
        _cue.text= [NSString stringWithFormat:@"%ld",(long)cueNum];
        cueIndexNext = 1;
        cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
        _cueNext.text= [NSString stringWithFormat:@"%ld",(long)cueNumNext];
        
        dspFaust->setParamValue(cueAddress, cueNum);
        
        _tips.text = [myCueTipsArrary objectAtIndex:0];
    }
    
    /*  comment init part for now
     if (stateIsOn) {
     dspFaust->setParamValue(initAddress, 1);
     // delay pour init
     dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC));
     dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
     dspFaust->setParamValue(initAddress, 0);
     });
     }
     */
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
    
    for (int i=0; i<dspFaustMotion->getParamsCount(); i++) {
        dspFaustMotion->setParamValue(i, dspFaustMotion->getParamInit(i));
    }
    
    for (int i=0; i<dspFaust->getParamsCount(); i++) {
        dspFaust->setParamValue(i, dspFaust->getParamInit(i));
    }
    
    _motionParam.text = @"Done";
    
    dspFaust->checkAdress();
    [self checkAddress];
    
    [self resetDefaultParams];
    
    
}


- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, pickerView.frame.size.width, 44)];
    label.backgroundColor = [UIColor grayColor];
    label.textColor = [UIColor whiteColor];
    label.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:17];
    
    label.text = [_motionParamArray objectAtIndex:row];
    return label;
}


-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    
    for (int i=0; i< _motionParamArray.count; i++) {
        paramsOn[i]=false;
    }
    
    paramsOn[row]=true;
    
    _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaust->getParamValue([_motionParamAddress[row] UTF8String])];
    
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
    /*
     for (int i=0; i< _motionParamArray.count; i++) {
     if (paramsOn[i]) {
     dspFaustMotion->setParamValue([_motionParamAddress[i] UTF8String], [_motionParam.text floatValue]);
     [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:_motionParamArray[i]];
     }
     }
     */
    // Find the label index of the edited parameter
    int i = -1;
    for (i=0; i<_motionParamArray.count; i++) {
        if (paramsOn[i]) {
            break;
        }
    }
    
    // Find the label of the edited parameter using its index
    std::string param = [_motionParamArray[i] UTF8String];
    
    // Change value of all addresses with the same label
    for (int i=0; i<_motionParamArray.count; i++) {
        if ([_motionParamArray[i] UTF8String] ==  param) {
            dspFaust->setParamValue([_motionParamAddress[i] UTF8String], [_motionParam.text floatValue]);
            [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:_motionParamArray[i]];
        }
    }
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
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
    
    if (!titleString) titleString = @"faust2smartphone | Allen";
    
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
