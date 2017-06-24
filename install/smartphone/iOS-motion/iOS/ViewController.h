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

@interface ViewController : UIViewController < CLLocationManagerDelegate,UIPickerViewDelegate,UIPickerViewDataSource,UITextFieldDelegate > {

    DspFaust *dspFaust;
    DspFaustMotion *dspFaustMotion;
    CMMotionManager* _motionManager;
    CLLocationManager* _locationManager;
    
    CMAttitude *referenceAttitude;
    
    CMRotationMatrix referenceMatrix;
    
    float matrixA[3][3];
    float matrixB[3][3];
    float matrixC[3][3];
    
    NSTimer* _guiTimer;
    NSTimer *_sensorTimer;
    
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
    
    const char* brasGcoursAddress;
    const char* brasGrearAddress;
    const char* brasGjardinAddress;
    const char* brasGfrontAddress;
    const char* brasGdownAddress;
    const char* brasGupAddress;
    
    const char* piedscoursAddress;
    const char* piedsrearAddress;
    const char* piedsjardinAddress;
    const char* piedsfrontAddress;
    const char* piedsdownAddress;
    const char* piedsupAddress;
    
    const char* doscoursAddress;
    const char* dosrearAddress;
    const char* dosjardinAddress;
    const char* dosfrontAddress;
    const char* dosdownAddress;
    const char* dosupAddress;
    
    const char* brasDcoursAddress;
    const char* brasDrearAddress;
    const char* brasDjardinAddress;
    const char* brasDfrontAddress;
    const char* brasDdownAddress;
    const char* brasDupAddress;
    
    const char* tetecoursAddress;
    const char* teterearAddress;
    const char* tetejardinAddress;
    const char* tetefrontAddress;
    const char* tetedownAddress;
    const char* teteupAddress;
    
    const char* ventrecoursAddress;
    const char* ventrerearAddress;
    const char* ventrejardinAddress;
    const char* ventrefrontAddress;
    const char* ventredownAddress;
    const char* ventreupAddress;
    
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
    
    BOOL brasGcoursIsOn;
    BOOL brasGrearIsOn;
    BOOL brasGjardinIsOn;
    BOOL brasGfrontIsOn;
    BOOL brasGdownIsOn;
    BOOL brasGupIsOn;
    
    BOOL piedscoursIsOn;
    BOOL piedsrearIsOn;
    BOOL piedsjardinIsOn;
    BOOL piedsfrontIsOn;
    BOOL piedsdownIsOn;
    BOOL piedsupIsOn;
    
    BOOL doscoursIsOn;
    BOOL dosrearIsOn;
    BOOL dosjardinIsOn;
    BOOL dosfrontIsOn;
    BOOL dosdownIsOn;
    BOOL dosupIsOn;
    
    BOOL brasDcoursIsOn;
    BOOL brasDrearIsOn;
    BOOL brasDjardinIsOn;
    BOOL brasDfrontIsOn;
    BOOL brasDdownIsOn;
    BOOL brasDupIsOn;
    
    BOOL tetecoursIsOn;
    BOOL teterearIsOn;
    BOOL tetejardinIsOn;
    BOOL tetefrontIsOn;
    BOOL tetedownIsOn;
    BOOL teteupIsOn;
    
    BOOL ventrecoursIsOn;
    BOOL ventrerearIsOn;
    BOOL ventrejardinIsOn;
    BOOL ventrefrontIsOn;
    BOOL ventredownIsOn;
    BOOL ventreupIsOn;
    
    BOOL touchGateIsOn;
    BOOL screenXIsOn;
    BOOL screenYIsOn;
    BOOL magneticHeadingIsOn;
    
    BOOL cueIsOn;
    BOOL tipIsOn;
    
    
    NSMutableArray *_motionParamArray;
    
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
    
    NSMutableArray *myCueNumArrary;
    NSInteger cueNum;
    NSInteger cueIndex;
    NSInteger cueNumNext;
    NSInteger cueIndexNext;
    
    
    NSMutableArray *myCueTipsArrary;
    
}



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

@end

