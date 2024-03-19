#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol CustomSettingViewDelegate <NSObject>

- (void)customSettingViewSetOSCWithAddress:(NSString *)ip inPort:(NSString *)inPort outPort:(NSString *)outPort;

- (void)customSettingViewSetParamWithValue:(NSString *)value;
- (void)customSettingViewSetMotionLibParamWithValue:(NSString *)value;

-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component;

-(void) initFrame;

- (IBAction)defaultMotionAudioParam:(id)sender;
- (IBAction)defaultMotionLibParam:(id)sender;

- (void)endButtonTapped:(UIButton *)sender;

@end

@interface CustomSettingView : UIView <UITextFieldDelegate>

@property (nonatomic, weak) id<CustomSettingViewDelegate> delegate;

@property (nonatomic, strong) UITextField *ip;
@property (nonatomic, strong) UITextField *inPort;
@property (nonatomic, strong) UITextField *outPort;
@property (nonatomic, strong) UIButton *setOSC;
@property (nonatomic, strong) UIButton *setRef;
@property (nonatomic, strong) UIPickerView *pickerView1;
@property (nonatomic, strong) UITextField *param1;
@property (nonatomic, strong) UIButton *paramSend1;
@property (nonatomic, strong) UIButton *paramResetSend1;
@property (nonatomic, strong) UIPickerView *pickerView2;
@property (nonatomic, strong) UITextField *param2;
@property (nonatomic, strong) UIButton *paramSend2;
@property (nonatomic, strong) UIButton *paramResetSend2;

//@property (nonatomic, strong) NSMutableArray *paramArray1;
//@property (nonatomic, strong) NSMutableArray *paramArray2;

@end

NS_ASSUME_NONNULL_END
