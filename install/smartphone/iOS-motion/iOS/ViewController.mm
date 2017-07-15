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
#define bufferSize 512


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
    
    dspFaustMotion = new DspFaustMotion(SR/bufferSize,1);
    
    dspFaust = new DspFaust(dspFaustMotion,SR,bufferSize);
    
    ////////////////////////////////
    //Check the MetaData in console
    ///////////////////////////////
    
    NSLog(@"Faust Metadata: %s", dspFaust->getJSONUI());
    NSLog(@"Motion Metadata: %s", dspFaustMotion->getJSONUI());
    
    dspFaust->start();
    dspFaustMotion->start();
    
    ///////////////////////////////////
    // check motion key word in address
    ///////////////////////////////////
    
    dspFaust->checkAdress();
    [self checkAddress];
    
    
    ///////////////////////
    //other Initialization
    ///////////////////////
    
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
    
    [self loadDefaultParams];
    
    
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
    
    
    if (dspFaust->getOSCIsOn()) {
        _ip.enabled=true;
        _inPort.enabled=true;
        _outPort.enabled=true;
        _setOSC.enabled=true;
        _ip.text=oscAddress;
        _inPort.text=oscInPort;
        _outPort.text=oscOutPort;
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
    

}


-(void) loadDefaultParams {
    
    // Default setting for params of motion
    NSDictionary *appDefaults = [NSDictionary dictionaryWithObjectsAndKeys:
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/hp")], @"/Motion/hp",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/shok_thr")], @"/Motion/shok_thr",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/antirebon")], @"/Motion/antirebon",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/lp")], @"/Motion/lp",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tacc_thr")], @"/Motion/tacc_thr",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tacc_gain")], @"/Motion/tacc_gain",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tacc_up")], @"/Motion/tacc_up",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tacc_down")], @"/Motion/tacc_down",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tgyr_thr")], @"/Motion/tgyr_thr",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tgyr_gain")], @"/Motion/tgyr_gain",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tgyr_up")], @"/Motion/tgyr_up",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/tgyr_down")], @"/Motion/tgyr_down",
                                 [NSNumber numberWithFloat:dspFaustMotion->getParamInit("/Motion/osfproj")], @"/Motion/osfproj",
                                 @"192.168.1.20", @"oscAddress",
                                 @"5510", @"oscInPort",
                                 @"5511", @"oscOutPort",
                                 nil];
    [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaults];
    
    hpValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/hp"];
    shok_thrValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/shok_thr"];
    antirebonValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/antirebon"];
    lpValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/lp"];
    tacc_thrValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tacc_thr"];
    tacc_gainValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tacc_gain"];
    tacc_upValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tacc_up"];
    tacc_downValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tacc_down"];
    tgyr_thrValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tgyr_thr"];
    tgyr_gainValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tgyr_gain"];
    tgyr_upValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tgyr_up"];
    tgyr_downValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/tgyr_down"];
    osfprojValue = (float)[[NSUserDefaults standardUserDefaults] floatForKey:@"/Motion/osfproj"];
    
    
    dspFaustMotion->setParamValue("/Motion/hp", hpValue);
    dspFaustMotion->setParamValue("/Motion/shok_thr", shok_thrValue);
    dspFaustMotion->setParamValue("/Motion/antirebon", antirebonValue);
    dspFaustMotion->setParamValue("/Motion/tacc_thr", tacc_thrValue);
    dspFaustMotion->setParamValue("/Motion/tacc_gain", tacc_gainValue);
    dspFaustMotion->setParamValue("/Motion/tacc_up", tacc_upValue);
    dspFaustMotion->setParamValue("/Motion/tacc_down", tacc_downValue);
    dspFaustMotion->setParamValue("/Motion/tgyr_thr", tgyr_thrValue);
    dspFaustMotion->setParamValue("/Motion/tgyr_gain", tgyr_gainValue);
    dspFaustMotion->setParamValue("/Motion/tgyr_up", tgyr_upValue);
    dspFaustMotion->setParamValue("/Motion/tgyr_down", tgyr_downValue);
    dspFaustMotion->setParamValue("/Motion/lp", lpValue);
    dspFaustMotion->setParamValue("/Motion/osfproj", osfprojValue);
    
    if (dspFaust->getOSCIsOn()) {
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
        //if ([key compare:@"sampleRate"] != NSOrderedSame)
        //{
        [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
        //}
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
        } else if ([data hasSuffix:@"/cue"]) {
            cueIsOn = true;
            cueAddress = dspFaust->getParamAddress(i);
        } 
        
    }
    
    
}

- (void)startUpdate
{
    
    _sensorTimer = [NSTimer scheduledTimerWithTimeInterval:1./(SR/bufferSize) target:self
                                            selector:@selector(updateAccGyo) userInfo:nil repeats:YES];
    
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
    
    [self stopUpdate];
    [self stopMotion];
    dspFaust->stop();
    dspFaustMotion->stop();
    delete dspFaust;
    delete dspFaustMotion;
}


- (void)updateAccGyo
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
            
            dspFaust->motionRender(motion.attitude.rotationMatrix.m11,motion.attitude.rotationMatrix.m12,motion.attitude.rotationMatrix.m13,motion.attitude.rotationMatrix.m21,motion.attitude.rotationMatrix.m22,motion.attitude.rotationMatrix.m23,motion.attitude.rotationMatrix.m31,motion.attitude.rotationMatrix.m32,motion.attitude.rotationMatrix.m33);
            
            
        }];
    }];
    
}

-(void) initFrame {
    
    if (_motionManager!=nil) {
        
        dspFaust->initFrame();
        
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
    
    for (int i=0; i<dspFaustMotion->getParamsCount(); i++) {
        dspFaustMotion->setParamValue(i, dspFaustMotion->getParamInit(i));
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
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/lp"];
    }else if (hpIsOn) {
        dspFaustMotion->setParamValue("/Motion/hp", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/hp"];
    }else if (shok_thrIsOn) {
        dspFaustMotion->setParamValue("/Motion/shok_thr", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/shok_thr"];
    }else if (antirebonIsOn) {
        dspFaustMotion->setParamValue("/Motion/antirebon", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/antirebon"];
    }else if (tacc_thrIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_thr", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tacc_thr"];
    }else if (tacc_gainIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_gain", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tacc_gain"];
    }else if (tacc_upIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_up", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tacc_up"];
    }else if (tacc_downIsOn) {
        dspFaustMotion->setParamValue("/Motion/tacc_down", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tacc_down"];
    }else if (tgyr_thrIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_thr", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tgyr_thr"];
    }else if (tgyr_gainIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_gain", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tgyr_gain"];
    }else if (tgyr_upIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_up", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tgyr_up"];
    }else if (tgyr_downIsOn) {
        dspFaustMotion->setParamValue("/Motion/tgyr_down", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/tgyr_down"];
    }else if (osfprojIsOn) {
        dspFaustMotion->setParamValue("/Motion/osfproj", [_motionParam.text floatValue]);
        [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:@"/Motion/osfproj"];
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
