// CustomTabView.h

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CustomTabViewDelegate <NSObject>

- (void)buttonTappedWithPath:(NSString *)path value:(CGFloat)ButtonValue;

- (void)buttonTappedCue;

- (void)buttonTappedCounter:(NSString *)path tag:(NSInteger)ButtonTag;

- (void)buttonCounterReset:(NSString *)path tag:(NSInteger)ButtonTag;

@end

@interface CustomTabView : UIView

@property (nonatomic, weak) id<CustomTabViewDelegate> delegate;

@property (nonatomic, strong) NSMutableDictionary<NSString *, UIView *> *contentViews;
@property (nonatomic, strong) NSMutableArray *buttons;
@property (nonatomic, strong) NSMutableDictionary *nameForButton;
@property (nonatomic, strong) NSMutableDictionary *pathForButton;

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
                     ContentViewName:(NSString *)contentViewName;

@end

NS_ASSUME_NONNULL_END

