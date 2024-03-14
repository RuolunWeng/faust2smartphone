#import <Foundation/Foundation.h>

@interface CustomCounter : NSObject

@property (nonatomic, assign, readonly) float currentValue;

- (instancetype)initWithRangeMin:(float)min
                             max:(float)max
                            step:(float)step
                            init:(float)initValue;

- (void)increment;
- (void)decrement;
- (void)reset;

@end
