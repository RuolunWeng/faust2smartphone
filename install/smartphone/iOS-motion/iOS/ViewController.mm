//
//  ViewController.m
//  FaustAPInew
//
//  Created by Allen on 03/2017.
//  Copyright © 2016-2024 Allen. All rights reserved.
//

#import "ViewController.h"

#define ONE_G 9.81
#define kGUIUpdateRate 30

#define SR 48000
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
    
    dspFaustMotion = new DspFaustMotion(SR/bufferSize,1);
    //dspFaustMotion = new DspFaustMotion(SR, bufferSize);
    
    dspFaust = new DspFaust(dspFaustMotion,SR,bufferSize);
    
    
    self.view.alpha = 0;
    
    
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    self.view.alpha = 1;
    
    _pikerView.delegate = self;
    _pikerView.dataSource = self;
    ////////////////////////////////
    //Check the MetaData in console
    ///////////////////////////////
    
    NSLog(@"Faust Metadata: %s", dspFaust->getJSONUI());
    NSLog(@"Motion Metadata: %s", dspFaustMotion->getJSONUI());
    
    
    
    // 创建另一个标签页
    // between tips and setting button
    // between tips and setting button
    CGFloat additionalButtonViewY = self.tips.frame.origin.y + self.tips.frame.size.height;
    CGFloat additionalButtonViewYMax = self.customSettingButton.frame.origin.y;
    //CGFloat additionalButtonViewYMax = self.ip.frame.origin.y;
    CGFloat additionalButtonViewHeight = additionalButtonViewYMax - additionalButtonViewY;
    
    // 创建一个 CustomTabView 实例
    self.customTabView = [[CustomTabView alloc] initWithFrame:CGRectMake(0, additionalButtonViewY, self.view.frame.size.width, additionalButtonViewHeight)];
    self.customTabView.delegate = self;
    [self.view addSubview:self.customTabView];
    
    
    // create default dictionary for preset
    [self loadDefaultParams];
    // load possible OSC preset before start
    [self loadPossibleOSC];
    
    //////////////////////////
    // start FAUST
    ///////////////////////////
    dspFaust->start();
    dspFaustMotion->start();
    
    // load possible preset after start (crash before start with osc)
    [self loadPossiblePreset];
    
    ///////////////////////////////////
    // check motion key word in address
    ///////////////////////////////////
    dspFaust->checkAdress();
    [self checkAddress];
    
    
    if (checkPass) {
        
        
        ///////////////////////
        //other Initialization ( motion sensor + etc )
        ///////////////////////
        //There are two methods to receive data from CMMotionManager: push and pull.
        //Using push for now
        
        [self startMotion];
        
        [self startRotationMatrix];
        
        [self startAccelerometer];
        
        [self startGyroscope];
        
        [self startUpdateGUI];
        
        [self displayTitle];
        
        
        
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
        
        if (stateIsOn) {
            //if (cueIsOn or stateIsOn) {
            _init.hidden=false;
            _tips.hidden=false;
        } else {
            _init.hidden=true;
            _tips.hidden=true;
        }
        
        
        //
        //if (cueIsOn) {
        if ((cueIsOn and !newCueIsOn and !newCounterIsOn)) {
            _cue.hidden=false;
            _cueNext.hidden=false;
            
            _cueText.hidden=false;
            _nextCueText.hidden=false;
            
            _prevCue.hidden=false;
            _nextCue.hidden=false;
            _init.hidden=false;
        } else {
            _cue.hidden=true;
            _cueNext.hidden=true;
            
            _cueText.hidden=true;
            _nextCueText.hidden=true;
            _init.hidden=true;
            _prevCue.hidden=true;
            _nextCue.hidden=true;
        }
        
        
        //if (cueIsOn or touchGateIsOn or screenXIsOn or screenYIsOn) {
        //if (touchGateIsOn or screenXIsOn or screenYIsOn) {
        if (touchGateIsOn or screenYIsOn or screenXIsOn or (cueIsOn and !newCueIsOn and !newCounterIsOn)) {
            _touch.hidden=false;
        } else {
            _touch.hidden=true;
        }
        
        
        if (cueIsOn or newCounterIsOn) {
            _tips.hidden=false;
        } else {
            _tips.hidden=true;
        }
        
    }
    
}

- (void)buttonTappedWithPath:(NSString *)path value:(CGFloat)value {
    // 调用 DSP 相关方法，传递参数
    CGFloat scaledValue = scaleValue(value, dspFaust->getParamMin([path UTF8String]),
                                     dspFaust->getParamMax([path UTF8String]));
    
    dspFaust->setParamValue([path UTF8String], scaledValue);
    //NSLog(@"Button tapped Up with path: %@", path);
    
    // Save Motion UI Preset
    [[NSUserDefaults standardUserDefaults] setFloat:scaledValue forKey:path];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)buttonTappedCue {
    if (cueIsOn and newCueIsOn) {
        [self counter];
    }
}


- (void)buttonTappedNextCue {
    if (cueIsOn) {
        [self nextCue:nil];
    }
}

- (void)buttonTappedPrevCue {
    if (cueIsOn) {
        [self prevCue:nil];
    }
}

- (void)buttonTappedInitCue {
    if (cueIsOn) {
        [self initCue:nil];
    }
}
- (void)buttonTappedSetRef{
    [self initFrame];
}

- (void)buttonTappedCounter:(NSString *)path tag:(NSInteger)ButtonTag {
    
    [[self.customCounters objectForKey:@(ButtonTag)] increment];
    // 调用 DSP 相关方法，传递参数
    dspFaust->setParamValue([path UTF8String], [[self.customCounters objectForKey:@(ButtonTag)] currentValue]);
    _tips.text = [NSString stringWithFormat:@"Counter_%@: %0.2f", [path lastPathComponent],[[self.customCounters objectForKey:@(ButtonTag)] currentValue]];
    
}

- (void)buttonCounterReset:(NSString *)path tag:(NSInteger)ButtonTag {
    
    [[self.customCounters objectForKey:@(ButtonTag)] reset];
    // 调用 DSP 相关方法，传递参数
    dspFaust->setParamValue([path UTF8String], [[self.customCounters objectForKey:@(ButtonTag)] currentValue]);
    _tips.text = [NSString stringWithFormat:@"Counter_%@: %0.2f", [path lastPathComponent],[[self.customCounters objectForKey:@(ButtonTag)] currentValue]];
    
}

- (void)sendValueToVumeter:(CustomButton *)vumeterButton  {
    // Fetch the value from your data source
    CGFloat newValue = scaleBackValue(dspFaust->getParamValue([vumeterButton.pathForButton UTF8String]), dspFaust->getParamMin([vumeterButton.pathForButton UTF8String]), dspFaust->getParamMax([vumeterButton.pathForButton UTF8String]));
    [vumeterButton updateBargraphWithValue:newValue];
}

- (void)sendValueToTouchUI:(CustomButton *)TouchUIButton  {
    
    // current init value scale to 0-1
    NSMutableArray *buttonValues = [NSMutableArray array];
    
    if (![TouchUIButton.customButtonType isEqualToString:@"pad"]) {
        // Fetch the value from your data source
        CGFloat newValue = scaleBackValue(dspFaust->getParamValue([TouchUIButton.pathForButton UTF8String]), dspFaust->getParamMin([TouchUIButton.pathForButton UTF8String]), dspFaust->getParamMax([TouchUIButton.pathForButton UTF8String]));
        [buttonValues addObject:@(newValue)];
        [TouchUIButton updateTouchUIWithValue:buttonValues];
    } else {
        
        // Fetch the value from your data source
        CGFloat padValue = scaleBackValue(dspFaust->getParamValue([TouchUIButton.pathForButton UTF8String]), dspFaust->getParamMin([TouchUIButton.pathForButton UTF8String]), dspFaust->getParamMax([TouchUIButton.pathForButton UTF8String]));
        [buttonValues addObject:@(padValue)];
        
        CGFloat padXValue = scaleBackValue(dspFaust->getParamValue([[NSString stringWithFormat:@"%@_X",TouchUIButton.pathForButton] UTF8String]), dspFaust->getParamMin([[NSString stringWithFormat:@"%@_X",TouchUIButton.pathForButton] UTF8String]), dspFaust->getParamMax([[NSString stringWithFormat:@"%@_X",TouchUIButton.pathForButton] UTF8String]));
        
        [buttonValues addObject:@(padXValue)];
        
        CGFloat padYValue = scaleBackValue(dspFaust->getParamValue([[NSString stringWithFormat:@"%@_Y",TouchUIButton.pathForButton] UTF8String]), dspFaust->getParamMin([[NSString stringWithFormat:@"%@_Y",TouchUIButton.pathForButton] UTF8String]), dspFaust->getParamMax([[NSString stringWithFormat:@"%@_Y",TouchUIButton.pathForButton] UTF8String]));
        [buttonValues addObject:@(padYValue)];
        
        [TouchUIButton updateTouchUIWithValue:buttonValues];
        
    }
    
}

// 将0到1之间的浮点数值映射到给定范围内的浮点数值
CGFloat scaleValue(CGFloat value, CGFloat min, CGFloat max) {
    return min + (max - min) * value;
}

// 将给定范围内的浮点数值映射到0到1之间的浮点数值
CGFloat scaleBackValue(CGFloat value, CGFloat min, CGFloat max) {
    return (value - min) / (max - min);
}

- (IBAction)showCustomSetting:(id)sender {
//    if (self.dspFaust->isRunningDsp(self.currentDSP)) {
//        self.dspFaust->stopDsp(self.currentDSP);
//    }
    // Initialize UIView
    // between tips and setting button
    CGFloat additionalSettingViewY = self.tips.frame.origin.y + self.tips.frame.size.height;
    CGFloat additionalSettingViewHeight = self.view.frame.size.height - additionalSettingViewY;
    
//    self.myCustomSettingView= [[CustomSettingView alloc] initWithFrame:self.view.bounds];
    self.myCustomSettingView= nil;
    self.myCustomSettingView= [[CustomSettingView alloc] initWithFrame:CGRectMake(0,additionalSettingViewY,self.view.frame.size.width, additionalSettingViewHeight)];
    self.myCustomSettingView.backgroundColor = [UIColor blackColor];
    self.myCustomSettingView.alpha = 0.95;
    
    if (dspFaust->getOSCIsOn()) {
        
        self.myCustomSettingView.ip.text=[[NSUserDefaults standardUserDefaults] stringForKey:@"oscAddress"];
        self.myCustomSettingView.inPort.text=[[NSUserDefaults standardUserDefaults] stringForKey:@"oscInPort"];
        self.myCustomSettingView.outPort.text=[[NSUserDefaults standardUserDefaults] stringForKey:@"oscOutPort"];
        
    } else {
        
        self.myCustomSettingView.ip.hidden = true;
        self.myCustomSettingView.inPort.hidden = true;
        self.myCustomSettingView.outPort.hidden = true;
        self.myCustomSettingView.setOSC.hidden = true;
    }
    
    
//
//    self.myCustomSettingView.paramArray1 = self._motionLibParamArray;// [self._motionLibParamArray copy];
//    self.myCustomSettingView.paramArray2 = self._motionAudioParamArray;// [self._motionAudioParamArray copy];
    
    [self.view addSubview:self.myCustomSettingView];
    self.myCustomSettingView.delegate = self;
    self.myCustomSettingView.pickerView1.delegate = self;
//    self.myCustomSettingView.pickerView1.dataSource = self;
    self.myCustomSettingView.pickerView2.delegate = self;
//    self.myCustomSettingView.pickerView2.dataSource = self;
//
    if (self._motionLibParamArray.count != 0) {
        // Select the first row by default
        //[self.myCustomSettingView.pickerView1 selectRow:0 inComponent:0 animated:NO];
        //[self pickerView:self.myCustomSettingView.pickerView1 didSelectRow:0 inComponent:0];
    }  else {
        self.myCustomSettingView.pickerView1.hidden = YES;
        self.myCustomSettingView.param1.hidden = YES;
        self.myCustomSettingView.paramSend1.hidden = YES;
        self.myCustomSettingView.paramResetSend1.hidden = YES;
    }
//
    if (self._motionAudioParamArray.count != 0) {
        // Select the first row by default
        //[self.myCustomSettingView.pickerView2 selectRow:0 inComponent:0 animated:NO];
        //[self pickerView:self.myCustomSettingView.pickerView2 didSelectRow:0 inComponent:0];
    }  else {
        self.myCustomSettingView.pickerView2.hidden = YES;
        self.myCustomSettingView.param2.hidden = YES;
        self.myCustomSettingView.paramSend2.hidden = YES;
        self.myCustomSettingView.paramResetSend2.hidden = YES;
    }
    
}

- (BOOL) connectedToInternet
{
    NSString *URLString = [NSString stringWithContentsOfURL:[NSURL URLWithString:@"http://www.bing.com"]];
    return ( URLString != NULL ) ? YES : NO;
}


-(void) loadDefaultParams {
    
//    std::vector<std::string>motionParamNames;
//    std::vector<std::string>motionParamAddress;
//    _motionParamArray = [[NSMutableArray alloc] init];
//    _motionParamAddress = [[NSMutableArray alloc] init];
//    
//    for (int i=0; i<dspFaust->getParamsCount(); i++) {
//        const char *dataParamMotion = dspFaust->getMetadata(i, "showName");
//        if (strcmp(dataParamMotion,"") != 0) {
//            motionParamNames.push_back(dataParamMotion);
//            motionParamAddress.push_back(dspFaust->getParamAddress(i));
//        }
//    }
//    for (int i=0; i<motionParamNames.size(); i++) {
//        //printf("%i=%s",i,motionParamNames[i].c_str());
//        [_motionParamArray addObject:[NSString stringWithUTF8String:motionParamNames[i].c_str()]];
//        [_motionParamAddress addObject:[NSString stringWithUTF8String:motionParamAddress[i].c_str()]];
//    }
    
    //    NSMutableDictionary *appDefaultsDictionary = [NSMutableDictionary dictionaryWithCapacity:_motionParamAddress.count];
        // Default ()
        NSMutableDictionary *appDefaultsDictionary = [NSMutableDictionary dictionaryWithCapacity:100];
     
    //    for (int i=0; i<_motionParamAddress.count; i++) {
    //        [appDefaultsDictionary setValue:
    //         [NSNumber numberWithFloat:dspFaust->getParamInit([_motionParamAddress[i] UTF8String])] forKey:_motionParamArray[i]];
    //    }
        
        [appDefaultsDictionary setValue:@"192.168.1.20" forKey:@"oscAddress"];
        [appDefaultsDictionary setValue:@"5510" forKey:@"oscInPort"];
        [appDefaultsDictionary setValue:@"5511" forKey:@"oscOutPort"];
        
        [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaultsDictionary];
    
    // INIT MOTION LIB ShowName
    std::vector<std::string>motionLibParamNames;
    std::vector<std::string>motionLibParamAddress;
    
    self._motionLibParamArray = [[NSMutableArray alloc] init];
    self._motionLibParamAddress = [[NSMutableArray alloc] init];
    
    motionLibParamsOn = new BOOL[self._motionLibParamAddress.count];
    
    for (int i=0; i<dspFaustMotion->getParamsCount(); i++) {
        const char *dataParamMotionLib = dspFaustMotion->getMetadata(i, "showName");
        if (dataParamMotionLib &&  strcmp(dataParamMotionLib,"") != 0) {
            motionLibParamNames.push_back(dataParamMotionLib);
            motionLibParamAddress.push_back(dspFaustMotion->getParamAddress(i));
        }
    }
    for (int i=0; i<motionLibParamNames.size(); i++) {
        //printf("%i=%s",i,motionParamNames[i].c_str());
        [self._motionLibParamArray addObject:[NSString stringWithUTF8String:motionLibParamNames[i].c_str()]];
        [self._motionLibParamAddress addObject:[NSString stringWithUTF8String:motionLibParamAddress[i].c_str()]];
    }
    
    std::vector<std::string>motionAudioParamNames;
    std::vector<std::string>motionAudioParamAddress;
    
    //std::vector<std::string>motionLibParamNames;
    //std::vector<std::string>motionLibParamAddress;
    
    
    self._motionAudioParamArray = [[NSMutableArray alloc] init];
    self._motionAudioParamAddress = [[NSMutableArray alloc] init];
    
    //self._motionLibParamArray = [[NSMutableArray alloc] init];
    //self._motionLibParamAddress = [[NSMutableArray alloc] init];
    
    motionAudioParamsOn = new BOOL[self._motionAudioParamAddress.count];
    
    //motionLibParamsOn = new BOOL[self._motionLibParamAddress.count];
    
    for (int i=0; i<dspFaust->getParamsCount(); i++) {
        const char *dataParamMotionAudio = dspFaust->getMetadata(i, "showName");
        if (dataParamMotionAudio && strcmp(dataParamMotionAudio,"") != 0) {
            motionAudioParamNames.push_back(dataParamMotionAudio);
            motionAudioParamAddress.push_back(dspFaust->getParamAddress(i));
        }
    }
    for (int i=0; i<motionAudioParamNames.size(); i++) {
        //printf("%i=%s",i,motionParamNames[i].c_str());
        [self._motionAudioParamArray addObject:[NSString stringWithUTF8String:motionAudioParamNames[i].c_str()]];
        [self._motionAudioParamAddress addObject:[NSString stringWithUTF8String:motionAudioParamAddress[i].c_str()]];
    }
    
    
}

-(void) loadPossibleOSC {
    
    if (dspFaust->getOSCIsOn()) {
        
        //[self connectedToInternet];
        
        oscAddress = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscAddress"];
        oscInPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscInPort"];
        oscOutPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscOutPort"];
        
        dspFaust->setOSCValue([oscAddress cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscInPort cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscOutPort cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    }
    
}

-(void) loadPossiblePreset {
    
//    for (int i=0; i<_motionParamAddress.count; i++) {
//        
//        dspFaust->setParamValue([_motionParamAddress[i] UTF8String],
//                                      (float)[[NSUserDefaults standardUserDefaults] floatForKey:_motionParamArray[i]]);
//        
//    }
    
    // load possible preset for motion lib
    for (int i=0; i<self._motionLibParamArray.count; i++) {
        // 从NSUserDefaults中检索motionLibParamAddress的值
        NSString *motionLibParamValue = [[NSUserDefaults standardUserDefaults] stringForKey:self._motionLibParamArray[i]];
        // 检查返回的值是否为nil
        if (motionLibParamValue != nil) {
            // 键存在并且具有一个相应的值
            //NSLog(@"Value for motionLibParamAddress exists: %@", motionLibParamAddressValue);
            dspFaustMotion->setParamValue([self._motionLibParamAddress[i] UTF8String], [motionLibParamValue floatValue]);
        } else {
            // 键不存在或者值为nil
            //NSLog(@"Value for motionLibParamAddress does not exist or is nil");
        }
        
    }
    
    // load possible preset for motion lib
    for (int i=0; i<self._motionAudioParamArray.count; i++) {
        // 从NSUserDefaults中检索motionLibParamAddress的值
        NSString *motionAudioParamValue = [[NSUserDefaults standardUserDefaults] stringForKey:self._motionAudioParamArray[i]];
        // 检查返回的值是否为nil
        if (motionAudioParamValue != nil) {
            // 键存在并且具有一个相应的值
            //NSLog(@"Value for motionLibParamAddress exists: %@", motionLibParamAddressValue);
            dspFaust->setParamValue([self._motionAudioParamAddress[i] UTF8String], [motionAudioParamValue floatValue]);
        } else {
            // 键不存在或者值为nil
            //NSLog(@"Value for motionLibParamAddress does not exist or is nil");
        }
        
    }
    
    for (int i=0; i<dspFaust->getParamsCount(); i++) {
        // 从NSUserDefaults中检索touchUIAddress的值
        NSString *touchUIParamValue = [[NSUserDefaults standardUserDefaults] stringForKey:[NSString stringWithUTF8String:dspFaust->getParamAddress(i)]];
        
        // 检查返回的值是否为nil
        if (touchUIParamValue != nil) {
            // 键存在并且具有一个相应的值
            //NSLog(@"Value for motionLibParamAddress exists: %@", [NSString stringWithUTF8String:dspFaust->getParamAddress(i)]);
            dspFaust->setParamValue(dspFaust->getParamAddress(i), [touchUIParamValue floatValue]);
        } else {
            // 键不存在或者值为nil
            //NSLog(@"Value for motionLibParamAddress does not exist or is nil");
        }
        
    }
    
//    if (_motionParamAddress.count>0) {
//        _motionParam.text = [NSString stringWithFormat:@"%.2f",[[NSUserDefaults standardUserDefaults] floatForKey:_motionParamArray[0]]];
//    }
    
    
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
    
    self.customCounters = [[NSMutableDictionary alloc] init];
    
    // Preset array of button names
    NSArray *typeButtonNames = @[@"button", @"checkbox", @"trigCue", @"nextCue", @"prevCue", @"initCue", @"setRef", @"hslider", @"vslider",@"trigCounter", @"pad", @"hbargraph", @"vbargraph"];
    
    for(int i=0; i<dspFaust->getParamsCount(); i++){
        const char *dataParamMotionButton = dspFaust->getMetadata(i, "SHCUI");
        if (dataParamMotionButton && strcmp(dataParamMotionButton,"") != 0) {
            const char *param = dataParamMotionButton;
            // Convert the const char* parameter to an NSString
            NSString *paramMetaString = [NSString stringWithUTF8String:param];

            // Split the string by space
            NSArray *components = [paramMetaString componentsSeparatedByString:@" "];
            
            // Check if the number of components is correct
            if (components.count == 10) {
                // Extract the values
                NSString *buttonType = components[1];
                // Check if buttonName is in the preset array
                if (![typeButtonNames containsObject:buttonType]) {
                    // Button name is not in the preset array
                    NSLog(@"UI TYPE is not valid");
                    _tips.text= @"UI TYPE is not valid"; // or handle the error as needed
                    return;
                }
                
                if ([buttonType isEqual:@"trigCue"]) {
                    newCueIsOn = true;
                }
                
                if ([buttonType isEqual:@"trigCounter"]) {
                    newCounterIsOn = true;
                    
                    // 创建一个计数器，范围为 0 到 10，步长为 1，初始值为 0
                    CustomCounter *counter = [[CustomCounter alloc] initWithRangeMin:dspFaust->getParamMin(i) max:dspFaust->getParamMax(i) step:dspFaust->getParamStep(i) init:dspFaust->getParamValue(i)];
                    
                    [self.customCounters setObject:counter forKey:@(i)];
                }
                
                // Extract the values
                NSString *tabViewName = components[0];
                
                // Use NSScanner to check the type of each component
                NSScanner *scanner = [NSScanner scannerWithString:components[2]];
                int x;
                if (![scanner scanInt:&x]) {
                    NSLog(@"Invalid type for x: %@", components[2]);
                    _tips.text= @"Invalid type for button x";
                    return;
                } else {
                    if (x < 0 || x > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", x);
                        _tips.text= @"Invalid integer button x value"; // or handle the error as needed
                        return;
                    }
                }
                
                scanner = [NSScanner scannerWithString:components[3]];
                int y;
                if (![scanner scanInt:&y]) {
                    NSLog(@"Invalid type for y: %@", components[3]);
                    _tips.text= @"Invalid type for button y";
                    return;
                } else {
                    if (y < 0 || y > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", y);
                        _tips.text= @"Invalid integer button x value"; // or handle the error as needed
                        return;
                    }
                }
                
                scanner = [NSScanner scannerWithString:components[4]];
                int width;
                if (![scanner scanInt:&width]) {
                    NSLog(@"Invalid type for width: %@", components[4]);
                    _tips.text= @"Invalid type for button width";
                    return;
                } else {
                    if (width < 0 || width > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", width);
                        _tips.text= @"Invalid integer button width value"; // or handle the error as needed
                        return;
                    }
                }
                
                scanner = [NSScanner scannerWithString:components[5]];
                int height;
                if (![scanner scanInt:&height]) {
                    NSLog(@"Invalid type for height: %@", components[5]);
                    _tips.text= @"Invalid type for button height";
                    return;
                } else {
                    if (height < 0 || height > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", height);
                        _tips.text= @"Invalid integer button height value"; // or handle the error as needed
                        return;
                    }
                }

                scanner = [NSScanner scannerWithString:components[6]];
                int colorR;
                if (![scanner scanInt:&colorR]) {
                    NSLog(@"Invalid type for colorR: %@", components[6]);
                    _tips.text= @"Invalid type for button colorR";
                    return;
                } else {
                    if (colorR < 0 || colorR > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorR);
                        _tips.text= @"Invalid integer button colorR value"; // or handle the error as needed
                        return;
                    }
                }
                scanner = [NSScanner scannerWithString:components[7]];
                int colorG;
                if (![scanner scanInt:&colorG]) {
                    NSLog(@"Invalid type for colorG: %@", components[7]);
                    _tips.text= @"Invalid type for button colorG";
                    return;
                } else {
                    if (colorG < 0 || colorG > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorG);
                        _tips.text= @"Invalid integer button colorG value"; // or handle the error as needed
                        return;
                    }
                }
                scanner = [NSScanner scannerWithString:components[8]];
                int colorB;
                if (![scanner scanInt:&colorB]) {
                    NSLog(@"Invalid type for colorB: %@", components[8]);
                    _tips.text= @"Invalid type for button colorB";
                    return;
                } else {
                    if (colorB < 0 || colorB > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorB);
                        _tips.text= @"Invalid integer button colorB value"; // or handle the error as needed
                        return;
                    }
                }
                scanner = [NSScanner scannerWithString:components[9]];
                int colorA;
                if (![scanner scanInt:&colorA]) {
                    NSLog(@"Invalid type for colorA: %@", components[9]);
                    _tips.text= @"Invalid type for button colorA";
                } else {
                    if (colorA < 0 || colorA > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorA);
                        _tips.text= @"Invalid integer button colorA value range"; // or handle the error as needed
                    }
                }
                // Now you have the button name and the coordinates (x, y) and size (width, height) (R G B)
                // Convert the const char* parameter to an NSString
                NSString *paramShortName = [NSString stringWithUTF8String:dspFaust->getParamShortName(i)];
                // Convert the const char* parameter to an NSString
                NSString *paramPath = [NSString stringWithUTF8String:dspFaust->getParamAddress(i)];
                
                // current init value scale to 0-1
                NSMutableArray *initValues = [NSMutableArray array];
                
                if ([buttonType isEqual:@"pad"]) {
                    NSString *padXPath = [NSString stringWithFormat:@"%@_X",paramPath];
                    NSString *padYPath = [NSString stringWithFormat:@"%@_Y",paramPath];
                    float initValueX = scaleBackValue(dspFaust->getParamValue([padXPath UTF8String]), dspFaust->getParamMin([padXPath UTF8String]), dspFaust->getParamMax([padXPath UTF8String]));
                    [initValues addObject:@(initValueX)];
                    float initValueY = scaleBackValue(dspFaust->getParamValue([padYPath UTF8String]), dspFaust->getParamMin([padYPath UTF8String]), dspFaust->getParamMax([padYPath UTF8String]));
                    [initValues addObject:@(initValueY)];
                } else {
                    float initValue = scaleBackValue(dspFaust->getParamValue(i), dspFaust->getParamMin(i), dspFaust->getParamMax(i));
                    [initValues addObject:@(initValue)];
                }
                
                
                //NSLog(@"initValue %@: %0.2f",paramShortName, initValue);
                
                [self.customTabView setContentViewWithButtonType:buttonType X:x Y:y Width:width Height:height name:paramShortName path:paramPath tag:i selectedColorRed:colorR green:colorG blue:colorB alpha:colorA initValues:initValues ContentViewName:tabViewName];
                
            }
            
            else {
                // Handle incorrect format
                NSLog(@"Incorrect format: %@", paramMetaString);
                _tips.text= @"Incorrect MotionButton metadata format";
                return;
            }
            
        }
    }
    

    
    //paramsOn = new BOOL[_motionParamAddress.count];
    
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
        } else if ([data hasSuffix:@"/state"]) {
            stateIsOn = true;
            stateAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/setref_comp"]) {
            setref_compIsOn = true;
            setref_compAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/setref_rota"]) {
            setref_rotaIsOn = true;
            setref_rotaAddress = dspFaust->getParamAddress(i);
        } else if ([data hasSuffix:@"/cue"]) {
            
            cueIsOn = true;
            cueAddress = dspFaust->getParamAddress(i);
            
            // TEST
            myCueNumArrary = [[NSMutableArray alloc] init];
            myCueTipsArrary = [[NSMutableArray alloc] init];
            
            if (strcmp(dspFaust->getMetadata(i, "SHCUI"),"") != 0) {
                // Convert the const char* parameter to an NSString
                NSString *paramMetaString = [NSString stringWithUTF8String:dspFaust->getMetadata(i, "SHCUI")];

                // Split the string by space
                NSArray *components = [paramMetaString componentsSeparatedByString:@" "];
                
                // Extract the values
                NSString *buttonType = components[1];
                
                if (![buttonType isEqual:@"trigCue"]) {
                    _tips.text= @"Cue metadata Only Support 'trigCue' option";
                    return;
                }
                
            }
            
            if (strcmp(dspFaust->getMetadata(i, "touchCueManager"),"") != 0) {
                
                const char *dataParamMotionCue = dspFaust->getMetadata(i, "touchCueManager");
                //  "{1: 'low'; 2:'mid'; 3: 'hi'}";
                
                NSString *inputNSString = [NSString stringWithUTF8String:dataParamMotionCue];
                
                // 删除多余字符
                NSCharacterSet *characterSet = [NSCharacterSet characterSetWithCharactersInString:@"{}'"];
                NSString *cleanedString = [[inputNSString componentsSeparatedByCharactersInSet:characterSet] componentsJoinedByString:@""];
                
                // 分割字符串为键值对数组
                NSArray *pairs = [cleanedString componentsSeparatedByString:@";"];
                
                // 遍历键值对数组，并将键和值分别添加到相应的数组中
                for (NSString *pair in pairs) {
                    NSArray *components = [pair componentsSeparatedByString:@":"];
                    if (components.count == 2) {
                        // 获取键和值
                        NSString *key = [components[0] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
                        //                        NSString *value = [components[1] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
                        // 获取值并添加 "Tips: " 字符串
                        NSString *rawValue = [components[1] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
                        NSString *value = [NSString stringWithFormat:@" %@", rawValue];
                        
                        // 检查键是否是大于等于0的整数
                        NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
                        NSNumber *number = [formatter numberFromString:key];
                        if (number && number.intValue >= dspFaust->getParamMin(i) && number.intValue <= dspFaust->getParamMax(i)) {
                            
                            [myCueNumArrary addObject:key];
                            [myCueTipsArrary addObject:value];
                        } else {
                            // Integer is not within the valid range
                            NSLog(@"Invalid integer value: %d", number.intValue);
                            _tips.text= @"Invalid integer Cue meatadata value";
                            return;
                        }
                    } else {
                        // Handle incorrect format
                        NSLog(@"Incorrect format: %@", pair);
                        _tips.text= @"Incorrect Cue metadata format";
                        return;
                    }
                }
                
                
            } else {
                
                // load cues
                NSString *pathCue = [NSString stringWithFormat:@"%@/cueNums.txt", [[NSBundle mainBundle] resourcePath]];
                
                NSString *myTextCues = [NSString stringWithContentsOfFile:pathCue encoding:NSUTF8StringEncoding error:nil];
                
                NSArray *myCues = [myTextCues componentsSeparatedByString:@";\n"];
                
                [myCueNumArrary addObjectsFromArray:myCues];
                
                // load cue Tips
                NSString *pathTips = [NSString stringWithFormat:@"%@/cueTips.txt", [[NSBundle mainBundle] resourcePath]];
                
                NSString *myTextTips = [NSString stringWithContentsOfFile:pathTips encoding:NSUTF8StringEncoding error:nil];
                
                NSArray *myTips = [myTextTips componentsSeparatedByString:@";\n"];
                
                [myCueTipsArrary addObjectsFromArray:myTips];
                
            }
            
            
            if ([myCueTipsArrary count] != [myCueNumArrary count]) {
                _tips.text= @"!Num of cue and tips must be same!";
                return;
            }
            
        
        }
        
    }
    
    if (!cueIsOn ) {
        if (newCueIsOn) {
            _tips.text= @"You're using Cue, but forgot to declare /cue ?";
            return;
        }
    }
    
    [self initCue:nil];
    
    checkPass = true;
}


- (void)customSettingViewSetOSCWithAddress:(nonnull NSString *)ip inPort:(nonnull NSString *)inPort outPort:(nonnull NSString *)outPort {
    
    dspFaust->setOSCValue([ip cStringUsingEncoding:[NSString defaultCStringEncoding]], [inPort cStringUsingEncoding:[NSString defaultCStringEncoding]], [outPort cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    
    _tips.hidden=false;
    _tips.text = @"Run Piece Again for New OSC Config";
    
    [[NSUserDefaults standardUserDefaults] setObject:ip forKey:@"oscAddress"];
    [[NSUserDefaults standardUserDefaults] setObject:inPort forKey:@"oscInPort"];
    [[NSUserDefaults standardUserDefaults] setObject:outPort forKey:@"oscOutPort"];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
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
    
    
    //Vumeter
    for (CustomButton *button in self.customTabView.customBargraphs) {
        [self sendValueToVumeter:button];
    }
    
    if (dspFaust->getOSCIsOn() or dspFaust->getMIDIIsOn()) {
        for (CustomButton *button in self.customTabView.customButtons) {
            if (![self.customTabView.customBargraphs containsObject:button]) {
                // Perform actions for buttons not in customBargraphs
                //NSLog(@"Button not in customBargraphs: %@", button);
                [self sendValueToTouchUI:button];
            }
        }
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
        
        if (cueIsOn and !newCueIsOn) {
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
        
        if (cueIsOn and !newCueIsOn) {
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
    _tips.text = [NSString stringWithFormat:@"Current Cue: %@", [myCueTipsArrary objectAtIndex:cueIndex]];
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
        if (self._motionAudioParamArray.count != 0) {
            // Select the first row by default
            [_pikerView selectRow:0 inComponent:0 animated:NO];
                // Manually call the delegate method to initialize based on the selected row
            [self pickerView:_pikerView didSelectRow:0 inComponent:0];
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
        [_ip resignFirstResponder];
        [_inPort resignFirstResponder];
        [_outPort resignFirstResponder];
        [_motionParam resignFirstResponder];
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
        
        _tips.text = [NSString stringWithFormat:@"Current Cue: %@", [myCueTipsArrary objectAtIndex:cueIndex]];
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
        _tips.text = [NSString stringWithFormat:@"Next Cue: %@", [myCueTipsArrary objectAtIndex:cueIndexNext]];
    }
    
}

- (IBAction)prevCue:(id)sender {
    
    if (cueIndexNext > 0) {
        cueIndexNext--;
        cueNumNext = [[myCueNumArrary objectAtIndex:cueIndexNext] integerValue];
        _cueNext.text= [NSString stringWithFormat:@"%ld",(long)cueNumNext];
        _tips.text = [NSString stringWithFormat:@"Next Cue: %@", [myCueTipsArrary objectAtIndex:cueIndexNext]];
    }
}

- (IBAction)defaultMotionLibParam:(id)sender {

    // Find the label index of the edited parameter
    int i = -1;
    for (i=0; i<self._motionLibParamArray.count; i++) {
        if (motionLibParamsOn[i]) {
            break;
        }
    }
    
    // Find the label of the edited parameter using its index
    std::string param = [self._motionLibParamArray[i] UTF8String];
    
    // Change value of all addresses with the same label
    for (int i=0; i<self._motionLibParamArray.count; i++) {
        if ([self._motionLibParamArray[i] UTF8String] ==  param) {
            dspFaustMotion->setParamValue([self._motionLibParamAddress[i] UTF8String], dspFaustMotion->getParamInit([self._motionLibParamAddress[i] UTF8String]));
            
            [[NSUserDefaults standardUserDefaults] setFloat:dspFaustMotion->getParamInit([self._motionLibParamAddress[i] UTF8String]) forKey:self._motionLibParamArray[i]];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
    }
    
    
    [self.myCustomSettingView.pickerView1 selectRow:0 inComponent:0 animated:NO];
    
    // Manually call the delegate method to initialize based on the selected row
    [self pickerView:self.myCustomSettingView.pickerView1 didSelectRow:0 inComponent:0];
    
}

- (IBAction)defaultMotionAudioParam:(id)sender {
    
    
    [_ip resignFirstResponder];
    [_inPort resignFirstResponder];
    [_outPort resignFirstResponder];
    [_motionParam resignFirstResponder];
    
//    for (int i=0; i<self.dspFaustMotion->getParamsCount(); i++) {
//        self.dspFaustMotion->setParamValue(i, self.dspFaustMotion->getParamInit(i));
//    }
    
    for (int i=0; i<dspFaust->getParamsCount(); i++) {
        dspFaust->setParamValue(i, dspFaust->getParamInit(i));
    }
    
    _motionParam.text = @"Done";
    [_pikerView selectRow:0 inComponent:0 animated:NO];
    
    // Find the label index of the edited parameter
    int i = -1;
    for (i=0; i<self._motionAudioParamArray.count; i++) {
        if (motionAudioParamsOn[i]) {
            break;
        }
    }
    
    // Find the label of the edited parameter using its index
    std::string param = [self._motionAudioParamArray[i] UTF8String];
    
    // Change value of all addresses with the same label
    for (int i=0; i<self._motionAudioParamArray.count; i++) {
        if ([self._motionAudioParamArray[i] UTF8String] ==  param) {
            dspFaust->setParamValue([self._motionAudioParamAddress[i] UTF8String], dspFaust->getParamInit([self._motionAudioParamAddress[i] UTF8String]));
            
            [[NSUserDefaults standardUserDefaults] setFloat:dspFaust->getParamInit([self._motionAudioParamAddress[i] UTF8String]) forKey:self._motionAudioParamArray[i]];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
    }
    
    // Manually call the delegate method to initialize based on the selected row
    [self pickerView:_pikerView didSelectRow:0 inComponent:0];
    

    [self.myCustomSettingView.pickerView2 selectRow:0 inComponent:0 animated:NO];
    
    // Manually call the delegate method to initialize based on the selected row
    [self pickerView:self.myCustomSettingView.pickerView2 didSelectRow:0 inComponent:0];
    
    
    [self.customTabView removeFromSuperview];
    self.customTabView = nil;
    
    // between tips and setting button
    CGFloat additionalButtonViewY = self.tips.frame.origin.y + self.tips.frame.size.height;
    CGFloat additionalButtonViewYMax = self.customSettingButton.frame.origin.y;
    //CGFloat additionalButtonViewYMax = self.ip.frame.origin.y;
    CGFloat additionalButtonViewHeight = additionalButtonViewYMax - additionalButtonViewY;
    
    // 创建一个 CustomTabView 实例
    self.customTabView = [[CustomTabView alloc] initWithFrame:CGRectMake(0, additionalButtonViewY, self.view.frame.size.width, additionalButtonViewHeight)];
    self.customTabView.delegate = self;
    [self.view addSubview:self.customTabView];
    
    
    dspFaust->checkAdress();
    [self checkAddress];
    
    // 将第一个子视图移到最前面显示
    [self.view bringSubviewToFront:self.myCustomSettingView];
    
    //[self resetDefaultParams];
    
    
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
    
    //_motionParam.text = @"Done";
    

   
    [self.additionalButtonView removeFromSuperview];
    
    // 创建另一个标签页
    // between tips and setting button
//    CGFloat additionalButtonViewY = self.tips.frame.origin.y + self.tips.frame.size.height;
//    CGFloat additionalButtonViewYMax = self.ip.frame.origin.y;
//    CGFloat additionalButtonViewHeight = additionalButtonViewYMax - additionalButtonViewY;
    // between tips and setting button
    CGFloat additionalButtonViewY = self.tips.frame.origin.y + self.tips.frame.size.height;
    CGFloat additionalButtonViewYMax = self.customSettingButton.frame.origin.y;
    //CGFloat additionalButtonViewYMax = self.ip.frame.origin.y;
    CGFloat additionalButtonViewHeight = additionalButtonViewYMax - additionalButtonViewY;
    
    // 创建一个 CustomTabView 实例
    self.customTabView = [[CustomTabView alloc] initWithFrame:CGRectMake(0, additionalButtonViewY, self.view.frame.size.width, additionalButtonViewHeight)];
    self.customTabView.delegate = self;
    [self.view addSubview:self.customTabView];
    
    dspFaust->checkAdress();
    [self checkAddress];
    
    [self resetDefaultParams];
    
    // Select the first row by default
    [_pikerView selectRow:0 inComponent:0 animated:NO];
        
        // Manually call the delegate method to initialize based on the selected row
    [self pickerView:_pikerView didSelectRow:0 inComponent:0];
    
    
}


- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, pickerView.frame.size.width, 44)];
    label.backgroundColor = [UIColor grayColor];
    label.textColor = [UIColor whiteColor];
    label.textAlignment = NSTextAlignmentCenter;
    label.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:15];
    label.adjustsFontSizeToFitWidth = YES;
    
    // for setting view
    if (pickerView.tag == 2) {
        label.text = [self._motionAudioParamArray objectAtIndex:row];
    } else if (pickerView.tag == 1) {
        label.text = [self._motionLibParamArray objectAtIndex:row];
    } else {
        label.text = [self._motionAudioParamArray objectAtIndex:row];
    }
    
    return label;
}


-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    
    
    // for setting view
    if (pickerView.tag == 1) {
        
        for (int i=0; i< self._motionLibParamArray.count; i++) {
            motionLibParamsOn[i]=false;
        }
        
        motionLibParamsOn[row]=true;
        
        self.myCustomSettingView.param1.text = [NSString stringWithFormat:@"%.2f", dspFaustMotion->getParamValue([self._motionLibParamAddress[row] UTF8String])];
        
    } else if (pickerView.tag == 2) {
        
        for (int i=0; i< self._motionAudioParamArray.count; i++) {
            motionAudioParamsOn[i]=false;
        }
        
        motionAudioParamsOn[row]=true;
        
        [self.myCustomSettingView.param2 setText: [NSString stringWithFormat:@"%.2f", dspFaust->getParamValue([self._motionAudioParamAddress[row] UTF8String])]];
        
        
    } else  {
        for (int i=0; i< self._motionAudioParamArray.count; i++) {
            motionAudioParamsOn[i]=false;
        }
        
        motionAudioParamsOn[row]=true;
        
        _motionParam.text = [NSString stringWithFormat:@"%.2f", dspFaust->getParamValue([self._motionAudioParamAddress[row] UTF8String])];
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
    
    // for setting view
    if (pickerView.tag == 2) {
        
        return self._motionAudioParamArray.count;
        
    } else if (pickerView.tag == 1) {
        
        return self._motionLibParamArray.count;
        
    } else {
        return self._motionAudioParamArray.count;
    }
    
    
}


- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component{
    
    // for setting view
    if (pickerView.tag == 2) {
        
        return self._motionAudioParamArray[row];
        
    } else if (pickerView.tag == 1) {
        
        return self._motionLibParamArray[row];
        
    } else {
        return self._motionAudioParamArray[row];
    }
    //return nil;
}


- (IBAction)motionParamSend:(id)sender {
//    
    [_motionParam resignFirstResponder];
    /*
     for (int i=0; i< self._motionAudioParamArray.count; i++) {
     if (paramsOn[i]) {
     self.dspFaustMotion->setParamValue([self._motionAudioParamAddress[i] UTF8String], [_motionParam.text floatValue]);
     [[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:self._motionAudioParamArray[i]];
     }
     }
     */
    // Find the label index of the edited parameter
    int i = -1;
    for (i=0; i<self._motionAudioParamArray.count; i++) {
        if (motionAudioParamsOn[i]) {
            break;
        }
    }
    
    // Find the label of the edited parameter using its index
    std::string param = [self._motionAudioParamArray[i] UTF8String];
    
    // Change value of all addresses with the same label
    for (int i=0; i<self._motionAudioParamArray.count; i++) {
        if ([self._motionAudioParamArray[i] UTF8String] ==  param) {
            dspFaust->setParamValue([self._motionAudioParamAddress[i] UTF8String], [_motionParam.text floatValue]);
            //[[NSUserDefaults standardUserDefaults] setFloat:[_motionParam.text floatValue] forKey:self._motionAudioParamArray[i]];
        }
    }
    
}

- (void)customSettingViewSetMotionLibParamWithValue:(NSString *)value{
    
    // Find the label index of the edited parameter
    int i = -1;
    for (i=0; i<self._motionLibParamArray.count; i++) {
        if (motionLibParamsOn[i]) {
            break;
        }
    }
    
    // Find the label of the edited parameter using its index
    std::string param = [self._motionLibParamArray[i] UTF8String];
    
    // Change value of all addresses with the same label
    for (int i=0; i<self._motionLibParamArray.count; i++) {
        if ([self._motionLibParamArray[i] UTF8String] ==  param) {
            dspFaustMotion->setParamValue([self._motionLibParamAddress[i] UTF8String], [value floatValue]);
            [[NSUserDefaults standardUserDefaults] setFloat:[value floatValue] forKey:self._motionLibParamArray[i]];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
    }
    
}

- (void)customSettingViewSetParamWithValue:(NSString *)value {
    
    // Find the label index of the edited parameter
    int i = -1;
    for (i=0; i<self._motionAudioParamArray.count; i++) {
        if (motionAudioParamsOn[i]) {
            break;
        }
    }
    
    // Find the label of the edited parameter using its index
    std::string param = [self._motionAudioParamArray[i] UTF8String];
    
    // Change value of all addresses with the same label
    for (int i=0; i<self._motionAudioParamArray.count; i++) {
        if ([self._motionAudioParamArray[i] UTF8String] ==  param) {
            dspFaust->setParamValue([self._motionAudioParamAddress[i] UTF8String], [value floatValue]);
            [[NSUserDefaults standardUserDefaults] setFloat:[value floatValue] forKey:self._motionAudioParamArray[i]];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
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
    
    if (!titleString) titleString = @"faust2smartphone | Allen";
    
    _titleApp.text = titleString;
    _titleApp.textAlignment = NSTextAlignmentCenter;
    _titleApp.adjustsFontSizeToFitWidth = YES;
    
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
