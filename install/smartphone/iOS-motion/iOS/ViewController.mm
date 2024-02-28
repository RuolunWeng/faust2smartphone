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
    

    self.nameForButton = [[NSMutableDictionary alloc] init];
    self.pathForButton = [[NSMutableDictionary alloc] init];
   
    // 创建另一个标签页
    // CGFloat offsetHeight = self.tips.frame.size.height;
    CGFloat additionalButtonViewY = self.tips.frame.origin.y;
    CGFloat additionalButtonViewHeight = self.view.frame.size.height/2 - additionalButtonViewY;
    self.additionalButtonView = [[UIView alloc] initWithFrame:CGRectMake(0, additionalButtonViewY, self.view.frame.size.width, additionalButtonViewHeight)];
    
    [self.view addSubview:self.additionalButtonView];
    

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
        
        //if (cueIsOn or touchGateIsOn or screenXIsOn or screenYIsOn) {
        if (touchGateIsOn or screenYIsOn or screenXIsOn or (cueIsOn and !newCueIsOn)) {
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
    
}

- (void)createButtonWithType:(NSString *)buttonType
                          X:(int)coordinationX
                          Y:(int)coordinationY
                      Width:(int)widthPercent
                     Height:(int)heightPercent
                       name:(NSString *)name
                       path:(NSString *)path
                        tag:(NSInteger)tag
                   inTabView:(UIView *)tabView
            selectedColorRed:(int)selectedRedInt
                        green:(int)selectedGreenInt
                         blue:(int)selectedBlueInt

{
    
    // 创建按钮
    UIButton *button;
    CGFloat selectedRed = selectedRedInt / 255.0;
    CGFloat selectedGreen = selectedGreenInt / 255.0;
    CGFloat selectedBlue = selectedBlueInt / 255.0;

    if ([buttonType isEqualToString:@"toggle"]) {
        button = [UIButton buttonWithType:UIButtonTypeCustom];
        // 设置按钮的选中状态颜色
        [button setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1.0]] forState:UIControlStateSelected];
        [button setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0.5  blue:0.5  alpha:1.0]] forState:UIControlStateNormal];
        [button addTarget:self action:@selector(toggleButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
    } else if ([buttonType isEqualToString:@"button"]) {
        button = [UIButton buttonWithType:UIButtonTypeSystem];
        [button addTarget:self action:@selector(buttonTouchDown:event:)  forControlEvents:UIControlEventTouchDown];
        [button addTarget:self action:@selector(buttonTouchUpInside:event:)  forControlEvents:UIControlEventTouchUpInside];
        [button setBackgroundColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1.0]];
//        [button setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1.0]] forState:UIControlStateHighlighted];
//        [button setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0.5  blue:0.5  alpha:1.0]] forState:UIControlStateNormal];
    } else if ([buttonType isEqualToString:@"trigCue"]) {
        button = [UIButton buttonWithType:UIButtonTypeSystem];
        [button addTarget:self action:@selector(buttonTouchDownCue:event:)  forControlEvents:UIControlEventTouchDown];
        [button addTarget:self action:@selector(buttonTouchUpInsideCue:event:)  forControlEvents:UIControlEventTouchUpInside];
        [button setBackgroundColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1.0]];
    } else if ([buttonType isEqualToString:@"touchScreenX"]) {
        button = [UIButton buttonWithType:UIButtonTypeSystem];
        [button addTarget:self action:@selector(buttonTouchDownX:event:)  forControlEvents:UIControlEventTouchDown];
        [button addTarget:self action:@selector(buttonTouchUpInsideX:event:)  forControlEvents:UIControlEventTouchUpInside];
        [button addTarget:self action:@selector(buttonTouchDragInsideX:event:)  forControlEvents:UIControlEventTouchDragInside];
        [button setBackgroundColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1]];
        button.alpha = 0.3;
    } else if ([buttonType isEqualToString:@"touchScreenY"]) {
        button = [UIButton buttonWithType:UIButtonTypeSystem];
        [button addTarget:self action:@selector(buttonTouchDownY:event:)  forControlEvents:UIControlEventTouchDown];
        [button addTarget:self action:@selector(buttonTouchUpInsideY:event:)  forControlEvents:UIControlEventTouchUpInside];
        [button addTarget:self action:@selector(buttonTouchDragInsideY:event:)  forControlEvents:UIControlEventTouchDragInside];
        [button setBackgroundColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1]];
        button.alpha = 0.3;
    }
    
    // 计算百分比值对应的具体坐标位置
    CGFloat x = coordinationX * tabView.frame.size.width / 100;
    CGFloat y = coordinationY * tabView.frame.size.height / 100;
    CGFloat width = widthPercent * tabView.frame.size.width / 100;
    CGFloat height = heightPercent * tabView.frame.size.height / 100;

    // 设置按钮的 frame
    button.frame = CGRectMake(x, y, width, height);
    if ([buttonType isEqualToString:@"trigCue"]) {
        [button setTitle:@"TrigCue" forState:UIControlStateNormal];
    } else {
        [button setTitle:name forState:UIControlStateNormal];
    }
    
    // Set adjustsFontSizeToFitWidth to true
    button.titleLabel.adjustsFontSizeToFitWidth = YES;
    
    UIFont *font = [UIFont systemFontOfSize:MIN(button.frame.size.width * 0.3, button.frame.size.height * 0.3)];

    // Set the adjusted font for the button's title label
    button.titleLabel.font = font;


    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    button.layer.cornerRadius = 5.0; // 圆角
    // Make sure to enable masksToBounds to apply the corner radius
    button.layer.masksToBounds = YES;
    button.tag = tag; // 设置按钮的标签
    
    // 添加按钮到选项卡视图中
    [tabView addSubview:button];
    
    // 保存按钮名称和标签的对应关系
    [self.nameForButton setObject:name forKey:@(tag)];
    [self.pathForButton setObject:path forKey:@(tag)];
    
    dspFaust->setParamValue([path UTF8String], 0);
}

- (void)buttonTouchUpInside:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSLog(@"Button tapped Up with name: %@", buttonName);
    dspFaust->setParamValue([buttonPath UTF8String], 0);
    
    sender.alpha += 0.3;

}

- (void)buttonTouchDown:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSLog(@"Button tapped Down with name: %@", buttonName);
    dspFaust->setParamValue([buttonPath UTF8String], 1);
    
    sender.alpha -= 0.3;

}

- (void)buttonTouchDownCue:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSLog(@"Button tapped Down for Cue with name: %@", buttonName);
    sender.alpha -= 0.3;

    if (cueIsOn and newCueIsOn) {
        [self counter];
    }
}

- (void)buttonTouchUpInsideCue:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSLog(@"Button tapped Up for Cue with name: %@", buttonName);
    sender.alpha += 0.3;

}

- (void)buttonTouchUpInsideY:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / sender.frame.size.height min:0 max:1];
    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Up: Y = %f (Normalised：Y = %f)", buttonName, touchPoint.y, normalisedY);
    dspFaust->setParamValue([buttonPath UTF8String], normalisedY);
    
    //sender.alpha += 0.3;
    sender.alpha = normalisedY;
    sender.alpha += 0.3;

}


- (void)buttonTouchUpInsideX:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedX = [self clampValue:touchPoint.x / sender.frame.size.width min:0 max:1];

    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Up: X = %f,(Normalised: X = %f)", buttonName, touchPoint.x, normalisedX);
    dspFaust->setParamValue([buttonPath UTF8String], normalisedX);

    //sender.alpha += 0.3;
    sender.alpha = normalisedX;
    sender.alpha += 0.3;
    
}

- (void)buttonTouchDownY:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / sender.frame.size.height min:0 max:1];
    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Down: Y = %f (Normalised：Y = %f)", buttonName, touchPoint.y, normalisedY);
    dspFaust->setParamValue([buttonPath UTF8String], normalisedY);

    //sender.alpha -= 0.3;
    sender.alpha = normalisedY;
    sender.alpha += 0.3;
}


- (void)buttonTouchDownX:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedX = [self clampValue:touchPoint.x / sender.frame.size.width min:0 max:1];

    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Down: X = %f,(Normalised: X = %f)", buttonName, touchPoint.x, normalisedX);
    dspFaust->setParamValue([buttonPath UTF8String], normalisedX);

    //sender.alpha -= 0.3;
    sender.alpha = normalisedX;
    sender.alpha += 0.3;
}

- (void)buttonTouchDragInsideY:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / sender.frame.size.height min:0 max:1];
    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Drag Inside: Y = %f (Normalised：Y = %f)", buttonName, touchPoint.y, normalisedY);
    dspFaust->setParamValue([buttonPath UTF8String], normalisedY);

    sender.alpha = normalisedY;
    sender.alpha += 0.3;
}


- (void)buttonTouchDragInsideX:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedX = [self clampValue:touchPoint.x / sender.frame.size.width min:0 max:1];

    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Drag Inside: X = %f,(Normalised: X = %f)", buttonName, touchPoint.x, normalisedX);
    
    dspFaust->setParamValue([buttonPath UTF8String], normalisedX);
    
    sender.alpha = normalisedX;
    sender.alpha += 0.3;

}



- (CGFloat)clampValue:(CGFloat)value min:(CGFloat)min max:(CGFloat)max {
    return fmin(fmax(value, min), max);
}

- (void)toggleButtonTapped:(UIButton *)sender {
    sender.selected = !sender.selected;
    // 获取按钮名称
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    if (sender.isSelected) {
        NSLog(@"Toggled button isSelected with name: %@", buttonName);
        dspFaust->setParamValue([buttonPath UTF8String], 1);
    } else {
        NSLog(@"Toggled button isNotSelected with name: %@", buttonName);
        dspFaust->setParamValue([buttonPath UTF8String], 0);
    }
    
}


// 定义一个方法，用于生成指定颜色的背景图片
- (UIImage *)imageWithColor:(UIColor *)color {
    CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}


- (BOOL) connectedToInternet
{
    NSString *URLString = [NSString stringWithContentsOfURL:[NSURL URLWithString:@"http://www.bing.com"]];
    return ( URLString != NULL ) ? YES : NO;
}


-(void) loadDefaultParams {
    
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
    
    NSMutableDictionary *appDefaultsDictionary = [NSMutableDictionary dictionaryWithCapacity:_motionParamAddress.count];
 
    for (int i=0; i<_motionParamAddress.count; i++) {
        [appDefaultsDictionary setValue:
         [NSNumber numberWithFloat:dspFaust->getParamInit([_motionParamAddress[i] UTF8String])] forKey:_motionParamArray[i]];
    }
    
    [appDefaultsDictionary setValue:@"192.168.1.20" forKey:@"oscAddress"];
    [appDefaultsDictionary setValue:@"5510" forKey:@"oscInPort"];
    [appDefaultsDictionary setValue:@"5511" forKey:@"oscOutPort"];
    
    [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaultsDictionary];
    
}

-(void) loadPossibleOSC {
    
    if (dspFaust->getOSCIsOn()) {
        
        [self connectedToInternet];
        
        oscAddress = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscAddress"];
        oscInPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscInPort"];
        oscOutPort = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscOutPort"];
        
        dspFaust->setOSCValue([oscAddress cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscInPort cStringUsingEncoding:[NSString defaultCStringEncoding]], [oscOutPort cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    }
    
}

-(void) loadPossiblePreset {
    
    for (int i=0; i<_motionParamAddress.count; i++) {
        
        dspFaust->setParamValue([_motionParamAddress[i] UTF8String],
                                      (float)[[NSUserDefaults standardUserDefaults] floatForKey:_motionParamArray[i]]);
        
    }
    
    if (_motionParamAddress.count>0) {
        _motionParam.text = [NSString stringWithFormat:@"%.2f",[[NSUserDefaults standardUserDefaults] floatForKey:_motionParamArray[0]]];
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
    
    
    // Preset array of button names
    NSArray *typeButtonNames = @[@"button", @"toggle", @"trigCue", @"touchScreenX", @"touchScreenY"];
    
    for(int i=0; i<dspFaust->getParamsCount(); i++){
        const char *dataParamMotionButton = dspFaust->getMetadata(i, "motionButton");
        if (strcmp(dataParamMotionButton,"") != 0) {
            const char *param = dataParamMotionButton;
            // Convert the const char* parameter to an NSString
            NSString *paramMetaString = [NSString stringWithUTF8String:param];
            // Convert the const char* parameter to an NSString
            NSString *paramShortName = [NSString stringWithUTF8String:dspFaust->getParamShortName(i)];
            // Convert the const char* parameter to an NSString
            NSString *paramPath = [NSString stringWithUTF8String:dspFaust->getParamAddress(i)];

            // Split the string by space
            NSArray *components = [paramMetaString componentsSeparatedByString:@" "];
            
            // Check if the number of components is correct
            if (components.count == 8) {
                // Extract the values
                NSString *buttonType = components[0];
                // Check if buttonName is in the preset array
                if (![typeButtonNames containsObject:buttonType]) {
                    // Button name is not in the preset array
                    NSLog(@"Button name is not valid");
                    _tips.hidden=false;
                    _tips.text = @"Button name is not valid";
                    return; // or handle the error as needed
                }
                
                if ([buttonType isEqual:@"trigCue"]) {
                    newCueIsOn = true;
                }
                
                // Use NSScanner to check the type of each component
                NSScanner *scanner = [NSScanner scannerWithString:components[1]];
                int x;
                if (![scanner scanInt:&x]) {
                    NSLog(@"Invalid type for x: %@", components[1]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for x";
                    return;
                } else {
                    if (x < 0 || x > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", x);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for x";
                        return; // or handle the error as needed
                    }
                }
                
                scanner = [NSScanner scannerWithString:components[2]];
                int y;
                if (![scanner scanInt:&y]) {
                    NSLog(@"Invalid type for y: %@", components[2]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for y";
                    return;
                } else {
                    if (y < 0 || y > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", y);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for y";
                        return; // or handle the error as needed
                    }
                }
                
                scanner = [NSScanner scannerWithString:components[3]];
                int width;
                if (![scanner scanInt:&width]) {
                    NSLog(@"Invalid type for width: %@", components[3]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for width";
                    return;
                } else {
                    if (width < 0 || width > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", width);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for width";
                        return; // or handle the error as needed
                    }
                }
                
                scanner = [NSScanner scannerWithString:components[4]];
                int height;
                if (![scanner scanInt:&height]) {
                    NSLog(@"Invalid type for height: %@", components[4]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for height";
                    return;
                } else {
                    if (height < 0 || height > 100) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", height);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for height";
                        return; // or handle the error as needed
                    }
                }

                scanner = [NSScanner scannerWithString:components[5]];
                int colorR;
                if (![scanner scanInt:&colorR]) {
                    NSLog(@"Invalid type for colorR: %@", components[5]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for colorR";
                    return;
                } else {
                    if (colorR < 0 || colorR > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorR);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for colorR";
                        return; // or handle the error as needed
                    }
                }
                scanner = [NSScanner scannerWithString:components[6]];
                int colorG;
                if (![scanner scanInt:&colorG]) {
                    NSLog(@"Invalid type for colorG: %@", components[6]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for colorG";
                    return;
                } else {
                    if (colorG < 0 || colorG > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorG);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for colorG";
                        return; // or handle the error as needed
                    }
                }
                scanner = [NSScanner scannerWithString:components[7]];
                int colorB;
                if (![scanner scanInt:&colorB]) {
                    NSLog(@"Invalid type for height: %@", components[7]);
                    _tips.hidden=false;
                    _tips.text = @"Button Invalid type for colorB";
                    return;
                } else {
                    if (colorB < 0 || colorB > 255) {
                        // Integer is not within the valid range
                        NSLog(@"Invalid integer value: %d", colorB);
                        _tips.hidden=false;
                        _tips.text = @"Button Invalid value for colorB";
                        return; // or handle the error as needed
                    }
                }
                // Now you have the button name and the coordinates (x, y) and size (width, height) (R G B)
                
                [self createButtonWithType:buttonType X:x Y:y Width:width Height:height name:paramShortName path:paramPath tag:i inTabView:self.additionalButtonView selectedColorRed:colorR green:colorG blue:colorB];

                
            } else {
                // Handle incorrect format
                NSLog(@"Incorrect format: %@", paramMetaString);
            }
            
        }
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
            
            // TEST
            myCueNumArrary = [[NSMutableArray alloc] init];
            myCueTipsArrary = [[NSMutableArray alloc] init];
            
            if (strcmp(dspFaust->getMetadata(i, "motionButton"),"") != 0) {
                // Convert the const char* parameter to an NSString
                NSString *paramMetaString = [NSString stringWithUTF8String:dspFaust->getMetadata(i, "motionButton")];

                // Split the string by space
                NSArray *components = [paramMetaString componentsSeparatedByString:@" "];
                
                // Extract the values
                NSString *buttonType = components[0];
                
                if (![buttonType isEqual:@"trigCue"]) {
                    _tips.hidden=false;
                    _tips.text = @"Cue metadata Only Support 'trigCue' option";
                    return;
                }
                
            }
            
            if (strcmp(dspFaust->getMetadata(i, "motionCueManage"),"") != 0) {
                
                const char *dataParamMotionCue = dspFaust->getMetadata(i, "motionCueManage");
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
                            //NSString *value = [NSString stringWithFormat:@"Tips: %@", rawValue];
                        
                        // 检查键是否是大于等于0的整数
                        NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
                        NSNumber *number = [formatter numberFromString:key];
                        if (number && number.intValue >= dspFaust->getParamMin(i) && number.intValue <= dspFaust->getParamMax(i)) {
                            
                            [myCueNumArrary addObject:key];
                            [myCueTipsArrary addObject:rawValue];
                        } else {
                            // Integer is not within the valid range
                            NSLog(@"Invalid integer value: %d", number.intValue);
                            _tips.hidden=false;
                            _tips.text = @"Invalid value for CUE";
                            return;
                        }
                    } else {
                        // Handle incorrect format
                        NSLog(@"Incorrect format: %@", pair);
                        _tips.hidden=false;
                        _tips.text = @"Incorrect Cue metadata format";
                        return ;
                    }
                }
                
                // 输出结果
                NSLog(@"Cue: %@", myCueNumArrary);
                NSLog(@"Tips: %@", myCueTipsArrary);
                
            } else {
                
                // load cues
                NSString *pathCue = [NSString stringWithFormat:@"%@/cueNums.txt", [[NSBundle mainBundle] resourcePath]];
                
                NSString *myTextCues = [NSString stringWithContentsOfFile:pathCue encoding:NSUTF8StringEncoding error:nil];
                
                NSArray *myCues = [myTextCues componentsSeparatedByString:@";\n"];
                
                NSLog(@"Cue:%@",myCues);
                [myCueNumArrary addObjectsFromArray:myCues];

                // load cue Tips
                NSString *pathTips = [NSString stringWithFormat:@"%@/cueTips.txt", [[NSBundle mainBundle] resourcePath]];
                
                NSString *myTextTips = [NSString stringWithContentsOfFile:pathTips encoding:NSUTF8StringEncoding error:nil];
                
                NSArray *myTips = [myTextTips componentsSeparatedByString:@";\n"];
                
                NSLog(@"Tips:%@",myTips);
                [myCueTipsArrary addObjectsFromArray:myTips];
                    
            }
            
            if ([myCueTipsArrary count] != [myCueNumArrary count]) {
                _tips.text = @"!Num of cue and tips must be same!";
                return;
            } else {
                _tips.text = [myCueTipsArrary objectAtIndex:0];
            }
            
            [self initCue:nil];
            
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
    
    if (!cueIsOn ) {
        if (newCueIsOn) {
            _tips.hidden=false;
            _tips.text = @"Using Cue, but forgot to declare /cue?";
            return ;
        }
    }
    
    checkPass = true;
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
        if (_motionParamArray.count != 0) {
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
    
    self.nameForButton = [[NSMutableDictionary alloc] init];
    self.pathForButton = [[NSMutableDictionary alloc] init];
   
    [self.additionalButtonView removeFromSuperview];
    // 创建另一个标签页
    // CGFloat offsetHeight = self.tips.frame.size.height;
    CGFloat additionalButtonViewY = self.tips.frame.origin.y;
    CGFloat additionalButtonViewHeight = self.view.frame.size.height/2 - additionalButtonViewY;
    self.additionalButtonView = [[UIView alloc] initWithFrame:CGRectMake(0, additionalButtonViewY, self.view.frame.size.width, additionalButtonViewHeight)];
    
    [self.view addSubview:self.additionalButtonView];
    
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
    label.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:15];
    
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
