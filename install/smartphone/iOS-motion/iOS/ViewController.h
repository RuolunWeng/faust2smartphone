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

@interface ViewController : UIViewController < CLLocationManagerDelegate,UIPickerViewDelegate,UIPickerViewDataSource > {

    DspFaust *dspFaust;
    DspFaustMotion *dspFaustMotion;
    CMMotionManager* _motionManager;
    CLLocationManager* _locationManager;
    
    NSTimer* _guiTimer;
    
    float magnetic;
    float magneticNormal;
    float magneticNew;
    float offset;
    
    const char* totalAccelAddress;
    const char* totalGyroAddress;
    const char* sxpAddress;
    const char* sypAddress;
    const char* szpAddress;
    const char* sxnAddress;
    const char* synAddress;
    const char* sznAddress;
    const char* ixpAddress;
    const char* iypAddress;
    const char* izpAddress;
    const char* ixnAddress;
    const char* iynAddress;
    const char* iznAddress;
    const char* pixpAddress;
    const char* piypAddress;
    const char* pizpAddress;
    const char* pixnAddress;
    const char* piynAddress;
    const char* piznAddress;
    const char* axpnAddress;
    const char* aypnAddress;
    const char* azpnAddress;
    const char* axpAddress;
    const char* aypAddress;
    const char* azpAddress;
    const char* axnAddress;
    const char* aynAddress;
    const char* aznAddress;
    const char* gxpnAddress;
    const char* gypnAddress;
    const char* gzpnAddress;
    const char* gxpAddress;
    const char* gypAddress;
    const char* gzpAddress;
    const char* gxnAddress;
    const char* gynAddress;
    const char* gznAddress;
    
    const char* touchGateAddress;
    const char* screenXAddress;
    const char* screenYAddress;
    const char* magneticHeadingAddress;
    
    const char* cueAddress;
    const char* tipAddress;
    
    BOOL totalAccelIsOn;
    BOOL totalGyroIsOn;
    BOOL sxpIsOn;
    BOOL sypIsOn;
    BOOL szpIsOn;
    BOOL sxnIsOn;
    BOOL synIsOn;
    BOOL sznIsOn;
    BOOL ixpIsOn;
    BOOL iypIsOn;
    BOOL izpIsOn;
    BOOL ixnIsOn;
    BOOL iynIsOn;
    BOOL iznIsOn;
    BOOL pixpIsOn;
    BOOL piypIsOn;
    BOOL pizpIsOn;
    BOOL pixnIsOn;
    BOOL piynIsOn;
    BOOL piznIsOn;
    BOOL axpnIsOn;
    BOOL aypnIsOn;
    BOOL azpnIsOn;
    BOOL axpIsOn;
    BOOL aypIsOn;
    BOOL azpIsOn;
    BOOL axnIsOn;
    BOOL aynIsOn;
    BOOL aznIsOn;
    BOOL gxpnIsOn;
    BOOL gypnIsOn;
    BOOL gzpnIsOn;
    BOOL gxpIsOn;
    BOOL gypIsOn;
    BOOL gzpIsOn;
    BOOL gxnIsOn;
    BOOL gynIsOn;
    BOOL gznIsOn;
    
    BOOL touchGateIsOn;
    BOOL screenXIsOn;
    BOOL screenYIsOn;
    BOOL magneticHeadingIsOn;
    
    BOOL cueIsOn;
    BOOL tipIsOn;
    
    int cueNum;
    
    NSArray *_motionParamArray;
    
    BOOL hpIsOn;
    BOOL shok_thrIsOn;
    BOOL antirebonIsOn;
    BOOL lpIsOn;
    BOOL osfprojIsOn;
    BOOL tacc_thrIsOn;
    BOOL tacc_gainIsOn;
    BOOL tacc_upIsOn;
    BOOL tacc_downIsOn;
    BOOL tgyr_thrIsOn;
    BOOL tgyr_gainIsOn;
    BOOL tgyr_upIsOn;
    BOOL tgyr_downIsOn;
    
    
}

@property (retain, nonatomic) IBOutlet UIPickerView *pikerView;
@property (retain, nonatomic) IBOutlet UITextField *motionParam;
- (IBAction)motionParamSend:(id)sender;
@property (retain, nonatomic) IBOutlet UIButton *motionParamSend;

@property (retain, nonatomic) IBOutlet UIImageView *touch;
@property (retain, nonatomic) IBOutlet UILabel *cue;
@property (retain, nonatomic) IBOutlet UILabel *tips;
- (IBAction)initCue:(id)sender;
@property (retain, nonatomic) IBOutlet UIButton *init;
@property (retain, nonatomic) IBOutlet UIButton *initParam;


@property (retain, nonatomic) IBOutlet UIButton *nextCue;
- (IBAction)nextCue:(id)sender;

@property (retain, nonatomic) IBOutlet UITextField *nextNum;


- (IBAction)defautParam:(id)sender;

@property (retain, nonatomic) IBOutlet UILabel *titleApp;

@property (retain, nonatomic) IBOutlet UITextField *ip;
@property (retain, nonatomic) IBOutlet UITextField *inPort;
@property (retain, nonatomic) IBOutlet UITextField *outPort;
- (IBAction)setOSC:(id)sender;
- (IBAction)setParam:(id)sender;
@property (retain, nonatomic) IBOutlet UISwitch *setParam;
@property (retain, nonatomic) IBOutlet UIButton *setOSC;

@end

