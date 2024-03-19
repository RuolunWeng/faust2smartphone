// CustomButton.h

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CustomButtonDelegate <NSObject>

- (void)buttonTappedWithPath:(NSString *)path value:(CGFloat)ButtonValue;

- (void)buttonTappedCue;
- (void)buttonTappedNextCue;
- (void)buttonTappedPrevCue;
- (void)buttonTappedInitCue;

- (void)buttonTappedSetRef;

- (void)buttonTappedCounter:(NSString *)path tag:(NSInteger)ButtonTag;

- (void)buttonCounterReset:(NSString *)path tag:(NSInteger)ButtonTag;

@end

@interface CustomButton : UIButton


@property (nonatomic, weak) id<CustomButtonDelegate> delegate;


@property (nonatomic, strong) NSString *customButtonType;
@property (nonatomic, strong) UIColor *selectedColor;
@property (nonatomic, assign) NSArray *lineInits;
@property (nonatomic, assign) CGFloat lineWidth;

@property (nonatomic, strong) NSString *nameForButton;
@property (nonatomic, strong) NSString *pathForButton;

- (instancetype)initWithButtonType:(NSString *)buttonType
                                 X:(int)X
                                 Y:(int)Y
                             Width:(int)width
                            Height:(int)height
                              name:(NSString *)name
                              path:(NSString *)path
                               tag:(NSInteger)tag
                      selectedColor:(UIColor *)selectedColor
                         lineInits:(NSArray *)lineInits;

- (void)initStatus;

@end

NS_ASSUME_NONNULL_END
