// CustomTabView.h

#import <UIKit/UIKit.h>
#import <objc/runtime.h>

#import "CustomButton.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CustomTabViewDelegate <NSObject>

- (void)buttonTappedWithPath:(NSString *)path value:(CGFloat)ButtonValue;

- (void)buttonTappedCue;
- (void)buttonTappedNextCue;
- (void)buttonTappedPrevCue;
- (void)buttonTappedInitCue;

- (void)buttonTappedSetRef;

- (void)buttonTappedCounter:(NSString *)path tag:(NSInteger)ButtonTag;

- (void)buttonCounterReset:(NSString *)path tag:(NSInteger)ButtonTag;

@end

@interface CustomTabView : UIView < CustomButtonDelegate >

@property (nonatomic, weak) id<CustomTabViewDelegate> delegate;

@property (nonatomic, strong) NSMutableDictionary<NSString *, UIView *> *contentViews;
@property (nonatomic, strong) NSMutableArray *tabButtons;
//@property (nonatomic, strong) NSMutableDictionary *nameForButton;
//@property (nonatomic, strong) NSMutableDictionary *pathForButton;
//@property (nonatomic, strong) NSMutableArray *sliderButtons;
//@property (nonatomic, strong) NSMutableArray *padButtons;

- (void)setContentViewWithButtonType:(NSString *)buttonType
                                   X:(int)coordinationX
                                   Y:(int)coordinationY
                               Width:(int)widthPercent
                              Height:(int)heightPercent
                                name:(NSString *)name
                                path:(NSString *)path
                                 tag:(NSInteger)tag
                    selectedColorRed:(int)selectedRedInt
                                green:(int)selectedGreenInt
                                 blue:(int)selectedBlueInt
                                alpha:(int)selectedAlphaInt
                               initValues:(NSArray *)initValues
                     ContentViewName:(NSString *)contentViewName;

@end

NS_ASSUME_NONNULL_END

