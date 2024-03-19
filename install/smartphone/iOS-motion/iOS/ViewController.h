//
//  ViewController.h
//  FaustAPInew
//
//  Created by Allen on 08/12/2016.
//  Copyright © 2016 Allen. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "DspFaustMotion.h"
#import "DspFaust.h"
#import "faust/misc.h"

#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>
#import "Accelerate/Accelerate.h"

#import "CustomTabView.h"

#import "CustomCounter.h"

#import "CustomSettingView.h"

@interface ViewController : UIViewController < CLLocationManagerDelegate,UIPickerViewDelegate,UIPickerViewDataSource,UITextFieldDelegate,CustomTabViewDelegate, CustomSettingViewDelegate > {

    DspFaust *dspFaust;
    DspFaustMotion *dspFaustMotion;
    CMMotionManager* _motionManager;
    CLLocationManager* _locationManager;
    
    CMAttitude *referenceAttitude;
    
    NSTimer* _guiTimer;
    NSTimer *_sensorTimer;
    
    float magnetic;
    float magneticNormal;
    float magneticNew;
    float offset;
    
    
    const char* touchGateAddress;
    const char* screenXAddress;
    const char* screenYAddress;
    const char* magneticHeadingAddress;
    const char* yawAddress;
    const char* pitchAddress;
    const char* rollAddress;
    const char* useraccxAddress;
    const char* useraccyAddress;
    const char* useracczAddress;
    const char* quaternionwAddress;
    const char* quaternionxAddress;
    const char* quaternionyAddress;
    const char* quaternionzAddress;
    
    const char* cueAddress;
    const char* stateAddress;
    //const char* initAddress;
    
    const char* setref_compAddress;
    const char* setref_rotaAddress;
    
    BOOL touchGateIsOn;
    BOOL screenXIsOn;
    BOOL screenYIsOn;
    BOOL magneticHeadingIsOn;
    BOOL yawIsOn;
    BOOL pitchIsOn;
    BOOL rollIsOn;
    BOOL useraccxIsOn;
    BOOL useraccyIsOn;
    BOOL useracczIsOn;
    BOOL quaternionwIsOn;
    BOOL quaternionxIsOn;
    BOOL quaternionyIsOn;
    BOOL quaternionzIsOn;
    
    BOOL cueIsOn;
    BOOL stateIsOn;
    
    BOOL newCueIsOn;
    BOOL newCounterIsOn;
    
    BOOL checkPass;
    
    BOOL setref_compIsOn;
    BOOL setref_rotaIsOn;
    
    int cnt;
    int cnt2;
    
//    NSMutableArray *_motionParamArray;
//    NSMutableArray *_motionParamAddress;
//    
//    BOOL* paramsOn;
    BOOL* motionAudioParamsOn;
    BOOL* motionLibParamsOn;
    
    NSMutableArray *myCueNumArrary;
    NSInteger cueNum;
    NSInteger cueIndex;
    NSInteger cueNumNext;
    NSInteger cueIndexNext;
    
    NSMutableArray *myCueTipsArrary;

    NSString* oscAddress;
    NSString* oscInPort;
    NSString* oscOutPort;
    
}

@property (nonatomic, strong) UIView *additionalButtonView;

@property (nonatomic, strong) CustomSettingView *myCustomSettingView;

@property (nonatomic, strong) CustomTabView *customTabView;

@property (nonatomic, strong) NSMutableDictionary *customCounters;

@property (nonatomic, strong) NSMutableArray *_motionLibParamArray;
@property (nonatomic, strong) NSMutableArray *_motionLibParamAddress;

@property (nonatomic, strong) NSMutableArray *_motionAudioParamArray;
@property (nonatomic, strong) NSMutableArray *_motionAudioParamAddress;

@property (retain, nonatomic) IBOutlet UIPickerView *pikerView;
@property (retain, nonatomic) IBOutlet UITextField *motionParam;
- (IBAction)motionParamSend:(id)sender;
@property (retain, nonatomic) IBOutlet UIButton *motionParamSend;

@property (retain, nonatomic) IBOutlet UIImageView *touch;
@property (retain, nonatomic) IBOutlet UILabel *cue;
@property (retain, nonatomic) IBOutlet UILabel *cueNext;
@property (retain, nonatomic) IBOutlet UILabel *tips;
- (IBAction)initCue:(id)sender;
@property (retain, nonatomic) IBOutlet UIButton *init;
@property (retain, nonatomic) IBOutlet UIButton *initParam;


@property (retain, nonatomic) IBOutlet UIButton *nextCue;
- (IBAction)nextCue:(id)sender;
@property (retain, nonatomic) IBOutlet UIButton *prevCue;
- (IBAction)prevCue:(id)sender;

@property (retain, nonatomic) IBOutlet UILabel *nextCueText;
@property (retain, nonatomic) IBOutlet UILabel *cueText;

@property (retain, nonatomic) IBOutlet UIButton *setRefrence;

- (IBAction)setRef:(id)sender;

- (IBAction)defautParam:(id)sender;

@property (retain, nonatomic) IBOutlet UILabel *titleApp;

@property (retain, nonatomic) IBOutlet UITextField *ip;
@property (retain, nonatomic) IBOutlet UITextField *inPort;
@property (retain, nonatomic) IBOutlet UITextField *outPort;
- (IBAction)setOSC:(id)sender;
- (IBAction)setParam:(id)sender;
@property (retain, nonatomic) IBOutlet UISwitch *setParam;
@property (retain, nonatomic) IBOutlet UIButton *setOSC;
@property (retain, nonatomic) IBOutlet UIButton *customSettingButton;

@end

