// CustomButton.mm

#import <objc/runtime.h>

#import "CustomButton.h"


@implementation CustomButton {
    id<CustomButtonDelegate> __unsafe_unretained _delegate;
    
}

- (void)setDelegate:(id<CustomButtonDelegate>)delegate {
    _delegate = delegate;
}

- (id<CustomButtonDelegate>)delegate {
    return _delegate;
}



- (instancetype)initWithButtonType:(NSString *)buttonType
                                 X:(int)x
                                 Y:(int)y
                             Width:(int)width
                            Height:(int)height
                              name:(NSString *)name
                              path:(NSString *)path
                               tag:(NSInteger)tag
                      selectedColor:(UIColor *)selectedColor
                            lineInits:(NSArray *)lineInits
{
    
    self = [super init];
    if (self) {
        self.userInteractionEnabled = YES;
        self.multipleTouchEnabled = YES; // Enable multitouch for the entire view
        
        self.customButtonType = buttonType;
        self.selectedColor = selectedColor;
        self.lineInits = lineInits;    // TODO: button INIT
        self.lineWidth = 2;
        self.nameForButton = name;
        self.pathForButton = path;
        self.tag = tag; // 设置按钮的标签
        
        
        // 设置按钮的 frame
        self.frame = CGRectMake(x, y, width, height);

        if ([buttonType isEqualToString:@"checkbox"]) {
            [self setupToggleButton];
        } else if ([buttonType isEqualToString:@"button"]) {
            [self setupButton];
        } else if ([buttonType isEqualToString:@"trigCue"]) {
            [self setupTrigCueButton];
        } else if ([buttonType isEqualToString:@"nextCue"]) {
            [self setupNextCueButton];
        } else if ([buttonType isEqualToString:@"prevCue"]) {
            [self setupPrevCueButton];
        } else if ([buttonType isEqualToString:@"initCue"]) {
            [self setupInitCueButton];
        } else if ([buttonType isEqualToString:@"setRef"]) {
            [self setupSetRefButton];
        } else if ([buttonType isEqualToString:@"hslider"]) {
            [self setupTouchScreenXButton];
        } else if ([buttonType isEqualToString:@"vslider"]) {
            [self setupTouchScreenYButton];
        } else if ([buttonType isEqualToString:@"pad"]) {
            [self setupPadButton];
        } else if ([buttonType isEqualToString:@"trigCounter"]) {
            [self setupTrigCounterButton];
        }
        

        UIFont *font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:MIN(self.frame.size.width * 0.3, self.frame.size.height * 0.3)];

        // Set the adjusted font for the button's title label
        self.titleLabel.font = font;
        [self setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    
        self.layer.borderWidth = 2.0; // Set the border width as needed
        self.layer.borderColor = [UIColor blackColor].CGColor; // Set the border color as needed

        self.layer.cornerRadius = 5.0; // 圆角
        // Make sure to enable masksToBounds to apply the corner radius
        self.layer.masksToBounds = YES;
        
        // Set adjustsFontSizeToFitWidth to true
        self.titleLabel.adjustsFontSizeToFitWidth = YES;
//        [self.titleLabel sizeToFit];
//        
//        [self setNeedsDisplay];
        
        
    }
    return self;
}

- (void)initStatus {
    
    if ([self.customButtonType isEqualToString:@"trigCounter"]) {
        [self.delegate buttonCounterReset:self.pathForButton tag:self.tag];
    } else if ([self.customButtonType isEqualToString:@"hslider"]) {
        
        UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
        
        CGFloat lineInitX = mapValue([self.lineInits[0] floatValue], 0, 1, 0, self.frame.size.width);
        
        verticalLine.frame = CGRectMake(0, 0, lineInitX, self.frame.size.height);
           
        
    } else if ([self.customButtonType isEqualToString:@"vslider"]) {
        
        UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
        
        CGFloat lineInitY = mapValue([self.lineInits[0] floatValue], 0, 1, 0, self.frame.size.height);
        
        horizontalLine.frame = CGRectMake(0, self.frame.size.height-lineInitY, self.frame.size.width, lineInitY);
            
        
    } else if ([self.customButtonType isEqualToString:@"pad"]) {
        
        UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
        UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
        
        CGFloat lineInitX = mapValue([self.lineInits[0] floatValue], 0, 1, 0, self.frame.size.width);
        CGFloat lineInitY = mapValue([self.lineInits[1] floatValue], 0, 1, 0, self.frame.size.height);
        
        horizontalLine.frame = CGRectMake(0, self.frame.size.height- lineInitY, self.frame.size.width, self.lineWidth);
    
   
        verticalLine.frame = CGRectMake(lineInitX, 0, self.lineWidth, self.frame.size.height);
        
    }
    
    [self.titleLabel sizeToFit];
    [self setNeedsDisplay];
    
}

- (void)setupToggleButton {
    [self setTitle:self.nameForButton forState:UIControlStateNormal];
    [self setBackgroundImage:[self imageWithColor:self.selectedColor] forState:UIControlStateSelected];
    CGFloat red, green, blue, alpha;
    [self.selectedColor getRed:&red green:&green blue:&blue alpha:&alpha];
    [self setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0.5  blue:0.5  alpha:alpha]] forState:UIControlStateNormal];
    // init
    self.selected = [self.lineInits[0] intValue];
}

- (void)setupButton {
    [self setTitle:self.nameForButton forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
}

- (void)setupTrigCueButton {
    [self setTitle:@"TrigCue" forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
}

- (void)setupNextCueButton {
    [self setTitle:@"NextCue" forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
}

- (void)setupPrevCueButton {
    [self setTitle:@"PrevCue" forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
}

- (void)setupInitCueButton {
    [self setTitle:@"InitCue" forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
}

- (void)setupSetRefButton {
    [self setTitle:@"setRef" forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
}

- (void)setupTrigCounterButton {
    [self setTitle:self.nameForButton forState:UIControlStateNormal];
    [self setBackgroundColor:self.selectedColor];
    
}

- (void)setupTouchScreenXButton {
    // Implement setup for touchScreenXButton
    [self setTitle:self.nameForButton forState:UIControlStateNormal];
    
    UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
    
    CGFloat lineInitX = mapValue([self.lineInits[0] floatValue], 0, 1, 0, self.frame.size.width);
    
    if (!verticalLine) {
        verticalLine = [[UIView alloc] initWithFrame:CGRectMake(0, 0, lineInitX, self.frame.size.height)];
        verticalLine.backgroundColor = self.selectedColor;
        [self addSubview:verticalLine];
        objc_setAssociatedObject(self, "verticalLine", verticalLine, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }

    CGFloat red, green, blue, alpha;
    [self.selectedColor getRed:&red green:&green blue:&blue alpha:&alpha];
    [self setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0.5  blue:0.5  alpha:alpha]] forState:UIControlStateNormal];
   
}

- (void)setupTouchScreenYButton {
    // Implement setup for touchScreenYButton
    [self setTitle:self.nameForButton forState:UIControlStateNormal];
    UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
    
    CGFloat lineInitY = mapValue([self.lineInits[0] floatValue], 0, 1, 0, self.frame.size.height);
    
    if (!horizontalLine) {
        horizontalLine = [[UIView alloc] initWithFrame:CGRectMake(0, self.frame.size.height-lineInitY, self.frame.size.width, lineInitY)];
        horizontalLine.backgroundColor = self.selectedColor;
        [self addSubview:horizontalLine];
        objc_setAssociatedObject(self, "horizontalLine", horizontalLine, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }

    CGFloat red, green, blue, alpha;
    [self.selectedColor getRed:&red green:&green blue:&blue alpha:&alpha];
    [self setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0.5  blue:0.5  alpha:alpha]] forState:UIControlStateNormal];
    
}

- (void)setupPadButton {
    // Implement setup for padButton
    [self setTitle:self.nameForButton forState:UIControlStateNormal];
    
    UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
    UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
    
    CGFloat lineInitX = mapValue([self.lineInits[0] floatValue], 0, 1, 0, self.frame.size.width);
    CGFloat lineInitY = mapValue([self.lineInits[1] floatValue], 0, 1, 0, self.frame.size.height);
    
    if (!horizontalLine) {
//        horizontalLine = [[UIView alloc] initWithFrame:CGRectMake(0, self.frame.size.height-self.lineWidth*2, self.frame.size.width, self.lineWidth)];
        horizontalLine = [[UIView alloc] initWithFrame:CGRectMake(0, self.frame.size.height- lineInitY, self.frame.size.width, self.lineWidth)];
        horizontalLine.backgroundColor = [UIColor blackColor];
        [self addSubview:horizontalLine];
        objc_setAssociatedObject(self, "horizontalLine", horizontalLine, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    if (!verticalLine) {
//        verticalLine = [[UIView alloc] initWithFrame:CGRectMake(self.lineWidth, 0, self.lineWidth, self.frame.size.height)];
        verticalLine = [[UIView alloc] initWithFrame:CGRectMake(lineInitX, 0, self.lineWidth, self.frame.size.height)];
        verticalLine.backgroundColor = [UIColor blackColor];
        [self addSubview:verticalLine];
        objc_setAssociatedObject(self, "verticalLine", verticalLine, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }

    CGFloat red, green, blue, alpha;
    [self.selectedColor getRed:&red green:&green blue:&blue alpha:&alpha];
    
    [self setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:red green:green blue:blue alpha:alpha*0.5]] forState:UIControlStateSelected];
    
    [self setBackgroundImage:[self imageWithColor:self.selectedColor] forState:UIControlStateNormal];

}



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


// Another way to gerer multi touch
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    //[super touchesBegan:touches withEvent:event];
    
    for (UITouch *touch in touches) {
        CGPoint touchPoint = [touch locationInView:self];
        
        if ([self.customButtonType isEqual:@"button"]) {
            // Handle touch event for the button
            // 处理普通按钮点击事件

            //NSLog(@"Button tapped Down with name: %@, path: %@", self.nameForButton, self.pathForButton);
            [self.delegate buttonTappedWithPath:self.pathForButton value:1];
            
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;
            
            //self.alpha -= 0.5;
        } else if ([self.customButtonType isEqual:@"trigCue"]) {
            // Handle touch event for the button
            // 处理trigCue按钮点击事件

            //NSLog(@"Button tapped Down for Cue Action with name: %@, path: %@", self.nameForButton, self.pathForButton);
            
//            self.alpha -= 0.3;
            
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;

            [self.delegate buttonTappedCue];
            
        } else if ([self.customButtonType isEqual:@"nextCue"]) {
            // Handle touch event for the button
            // 处理trigCue按钮点击事件

            //NSLog(@"Button tapped Down for nextCue Action with name: %@, path: %@", self.nameForButton, self.pathForButton);
            
//            self.alpha -= 0.3;
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;

            [self.delegate buttonTappedNextCue];
            
        } else if ([self.customButtonType isEqual:@"prevCue"]) {
            // Handle touch event for the button
            // 处理prevCue按钮点击事件

            //NSLog(@"Button tapped Down for prevCue Action with name: %@, path: %@", self.nameForButton, self.pathForButton);
            
//            self.alpha -= 0.3;
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;

            [self.delegate buttonTappedPrevCue];
            
        } else if ([self.customButtonType isEqual:@"initCue"]) {
            // Handle touch event for the button
            // 处理initCue按钮点击事件

            //NSLog(@"Button tapped Down for initCue Action with name: %@, path: %@", self.nameForButton, self.pathForButton);
            
//            self.alpha -= 0.3;
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;

            [self.delegate buttonTappedInitCue];
            
        } else if ([self.customButtonType isEqual:@"setRef"]) {
            // Handle touch event for the button
            // 处理setRef按钮点击事件

            //NSLog(@"Button tapped Down for setRef Action with name: %@, path: %@", self.nameForButton, self.pathForButton);
            
//            self.alpha -= 0.3;
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;

            [self.delegate buttonTappedSetRef];
            
        } else if ([self.customButtonType isEqual:@"trigCounter"]) {
            // Handle touch event for the button
            // 处理trigCounter按钮点击事件

            //NSLog(@"Button tapped Down for Counter Action with name: %@, path: %@", self.nameForButton, self.pathForButton);
            
//            self.alpha -= 0.3;
            self.layer.borderColor= self.selectedColor.CGColor;
            
            // Get the current background color
            UIColor *currentColor = self.backgroundColor;
            
            // Extract the RGBA components from the current color
            CGFloat red, green, blue, alpha;
            [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

            // Create a new color with adjusted alpha value
            UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha / 2.0];

            // Assign the new color to the background color property
            self.backgroundColor = newColor;

            [self.delegate buttonTappedCounter:self.pathForButton tag:self.tag];
            
        } else if ([self.customButtonType isEqual:@"hslider"]) {
            
            UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");

                // 计算normalised坐标
                CGFloat normalisedX = [self clampValue:touchPoint.x / self.frame.size.width min:0 max:1];

                // 输出触摸点位的x/y坐标
                //NSLog(@"%@: touchScreenX Down: X = %f,(Normalised: X = %f)", self.nameForButton, touchPoint.x, normalisedX);
                
                verticalLine.frame = CGRectMake(0, 0, touchPoint.x, self.bounds.size.height);
        //        self.verticalLines[button].frame = CGRectMake(touchPoint.x, 0, 4, button.bounds.size.height);
                
                [self.delegate buttonTappedWithPath:self.pathForButton value:normalisedX];
                
        } else if ([self.customButtonType isEqual:@"vslider"]) {
            
            UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
            
                // 计算normalised坐标
                CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / self.frame.size.height min:0 max:1];
                
                // 输出触摸点位的x/y坐标
                //NSLog(@"%@: touchScreenY Down: Y = %f,(Normalised: Y = %f)", self.nameForButton, touchPoint.y, normalisedY);
                
                
                // Update the positions of the lines
                horizontalLine.frame = CGRectMake(0,
                                                  touchPoint.y, self.bounds.size.width, self.bounds.size.height-touchPoint.y);
                
                [self.delegate buttonTappedWithPath:self.pathForButton value:normalisedY];
            
        } else if ([self.customButtonType isEqual:@"pad"]) {
            // Get or create the horizontal and vertical lines associated with this button
            UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
            UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
                    
            self.selected = YES;
            [self.delegate buttonTappedWithPath:self.pathForButton value:1];
                    
            NSString *padXPath = [NSString stringWithFormat:@"%@_X",self.pathForButton];
            NSString *padYPath = [NSString stringWithFormat:@"%@_Y",self.pathForButton];

            // 计算normalised坐标
            CGFloat normalisedX = [self clampValue:touchPoint.x / self.frame.size.width min:0 max:1];
            CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / self.frame.size.height min:0 max:1];

            // 输出触摸点位的x/y坐标
            //NSLog(@"%@: Pad TochDown Inside: X = %f,(Normalised: X = %f)", self.nameForButton, touchPoint.x, normalisedX);
            //NSLog(@"%@: Pad TochDown Inside: Y = %f,(Normalised: Y = %f)", self.nameForButton, touchPoint.y, normalisedY);

            // Update the positions of the lines
            horizontalLine.frame = CGRectMake(0, touchPoint.y, self.bounds.size.width, self.lineWidth);
            verticalLine.frame = CGRectMake(touchPoint.x, 0, self.lineWidth, self.bounds.size.height);
            
            horizontalLine.backgroundColor = self.selectedColor;
            verticalLine.backgroundColor = self.selectedColor;
            
            [self.delegate buttonTappedWithPath:padXPath value:normalisedX];
            [self.delegate buttonTappedWithPath:padYPath value:normalisedY];
        }
        
    }
    
    //[self setNeedsDisplay];
}

- (void) touchesMoved:(NSSet *)touches
            withEvent:(UIEvent *)event {
    
    for (UITouch *touch in touches) {
        CGPoint touchPoint = [touch locationInView:self];
        
        // Determine if touch point is still inside button's bounds
        if (CGRectContainsPoint(self.bounds, touchPoint)) {
            
                if ([self.customButtonType isEqual:@"hslider"]) {
                    
                    UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");

                        // 计算normalised坐标
                        CGFloat normalisedX = [self clampValue:touchPoint.x / self.frame.size.width min:0 max:1];

                        // 输出触摸点位的x/y坐标
                        //NSLog(@"%@: touchScreenX Moved: X = %f,(Normalised: X = %f)", self.nameForButton, touchPoint.x, normalisedX);
                        
                        verticalLine.frame = CGRectMake(0, 0, touchPoint.x, self.bounds.size.height);
                //        self.verticalLines[button].frame = CGRectMake(touchPoint.x, 0, 4, button.bounds.size.height);
                        
                        [self.delegate buttonTappedWithPath:self.pathForButton value:normalisedX];
                        
                } else if ([self.customButtonType isEqual:@"vslider"]) {
                    
                    UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
                    
                        // 计算normalised坐标
                        CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / self.frame.size.height min:0 max:1];
                        
                        // 输出触摸点位的x/y坐标
                        //NSLog(@"%@: touchScreenY Moved: Y = %f,(Normalised: Y = %f)", self.nameForButton, touchPoint.y, normalisedY);
                        
                        
                        // Update the positions of the lines
                        horizontalLine.frame = CGRectMake(0,
                                                          touchPoint.y, self.bounds.size.width, self.bounds.size.height-touchPoint.y);
                        
                        [self.delegate buttonTappedWithPath:self.pathForButton value:normalisedY];
                    
                } else if ([self.customButtonType isEqual:@"pad"]) {
                    // Get or create the horizontal and vertical lines associated with this button
                    UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
                    UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
                            
                    NSString *padXPath = [NSString stringWithFormat:@"%@_X",self.pathForButton];
                    NSString *padYPath = [NSString stringWithFormat:@"%@_Y",self.pathForButton];

                    // 计算normalised坐标
                    CGFloat normalisedX = [self clampValue:touchPoint.x / self.frame.size.width min:0 max:1];
                    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / self.frame.size.height min:0 max:1];

                    // 输出触摸点位的x/y坐标
                    //NSLog(@"%@: Pad TochUp Inside: X = %f,(Normalised: X = %f)", self.nameForButton, touchPoint.x, normalisedX);
                    //NSLog(@"%@: Pad TochUp Inside: Y = %f,(Normalised: Y = %f)", self.nameForButton, touchPoint.y, normalisedY);

                    // Update the positions of the lines
                    horizontalLine.frame = CGRectMake(0, touchPoint.y, self.bounds.size.width, self.lineWidth);
                    verticalLine.frame = CGRectMake(touchPoint.x, 0, self.lineWidth, self.bounds.size.height);
                    horizontalLine.backgroundColor = self.selectedColor;
                    verticalLine.backgroundColor = self.selectedColor;
                    
                    [self.delegate buttonTappedWithPath:padXPath value:normalisedX];
                    [self.delegate buttonTappedWithPath:padYPath value:normalisedY];
                }
            
            
                
            }
        }
        
    //[self setNeedsDisplay];
    
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    //[super touchesEnded:touches withEvent:event];
    
    for (UITouch *touch in touches) {
        CGPoint touchPoint = [touch locationInView:self];
        
        // Determine if touch point is still inside button's bounds
        if (CGRectContainsPoint(self.bounds, touchPoint)) {
            if ([self.customButtonType isEqual:@"button"]) {
                // Handle touch event for the button
                // 处理普通按钮点击事件
                
                //NSLog(@"Button tapped Up with name: %@, path: %@", self.nameForButton, self.pathForButton);
                [self.delegate buttonTappedWithPath:self.pathForButton value:0];
                
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
                //self.alpha += 0.5;
            } else if ([self.customButtonType isEqual:@"checkbox"]) {
                // Handle touch event for the button
                // 处理TOGGLE按钮点击事件
                
                self.selected = !self.selected;
                
                if (self.isSelected) {
                    //NSLog(@"Toggled button isSelected with name: %@, path: %@", self.nameForButton, self.pathForButton);
                    [self.delegate buttonTappedWithPath:self.pathForButton value:1];
                } else {
                    //NSLog(@"Toggled button isNotSelected with name: %@, path: %@", self.nameForButton, self.pathForButton);
                    [self.delegate buttonTappedWithPath:self.pathForButton value:0];
                }
                
            } else if ([self.customButtonType isEqual:@"trigCue"]) {
                // Handle touch event for the button
                // 处理trigCue按钮点击事件
                
                //NSLog(@"Button tapped Up for Action Cue with name: %@, path: %@", self.nameForButton, self.pathForButton);
                
                //self.alpha += 0.3;
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
            } else if ([self.customButtonType isEqual:@"nextCue"]) {
                // Handle touch event for the button
                // 处理trigCue按钮点击事件
                
                //NSLog(@"Button tapped Up for Action nextCue with name: %@, path: %@", self.nameForButton, self.pathForButton);
                
                //self.alpha += 0.3;
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
            } else if ([self.customButtonType isEqual:@"prevCue"]) {
                // Handle touch event for the button
                // 处理trigCue按钮点击事件
                
                //NSLog(@"Button tapped Up for Action prevCue with name: %@, path: %@", self.nameForButton, self.pathForButton);
                
                //self.alpha += 0.3;
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
            } else if ([self.customButtonType isEqual:@"initCue"]) {
                // Handle touch event for the button
                // 处理trigCue按钮点击事件
                
                //NSLog(@"Button tapped Up for Action initCue with name: %@, path: %@", self.nameForButton, self.pathForButton);
                
                //self.alpha += 0.3;
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
            } else if ([self.customButtonType isEqual:@"setRef"]) {
                // Handle touch event for the button
                // 处理setRef按钮点击事件
                
                //NSLog(@"Button tapped Up for Action setRef with name: %@, path: %@", self.nameForButton, self.pathForButton);
                
                //self.alpha += 0.3;
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
            } else if ([self.customButtonType isEqual:@"trigCounter"]) {
                // Handle touch event for the button
                // 处理trigCounter按钮点击事件
                
                //NSLog(@"Button tapped Up for Action Counter with name: %@, path: %@", self.nameForButton, self.pathForButton);
                
                //self.alpha += 0.3;
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                
            } else if ([self.customButtonType isEqual:@"pad"]) {
                // Get or create the horizontal and vertical lines associated with this button
                UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
                UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
                
                self.selected = NO;
                [self.delegate buttonTappedWithPath:self.pathForButton value:0];
                
                NSString *padXPath = [NSString stringWithFormat:@"%@_X",self.pathForButton];
                NSString *padYPath = [NSString stringWithFormat:@"%@_Y",self.pathForButton];
                
                // 计算normalised坐标
                CGFloat normalisedX = [self clampValue:touchPoint.x / self.frame.size.width min:0 max:1];
                CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / self.frame.size.height min:0 max:1];
                
                // 输出触摸点位的x/y坐标
                //NSLog(@"%@: Pad TochUp Inside: X = %f,(Normalised: X = %f)", self.nameForButton, touchPoint.x, normalisedX);
                //NSLog(@"%@: Pad TochUp Inside: Y = %f,(Normalised: Y = %f)", self.nameForButton, touchPoint.y, normalisedY);
                
                // Update the positions of the lines
                horizontalLine.frame = CGRectMake(0, touchPoint.y, self.bounds.size.width, self.lineWidth);
                verticalLine.frame = CGRectMake(touchPoint.x, 0, self.lineWidth, self.bounds.size.height);
                horizontalLine.backgroundColor = [UIColor blackColor];
                verticalLine.backgroundColor = [UIColor blackColor];
                
                [self.delegate buttonTappedWithPath:padXPath value:normalisedX];
                [self.delegate buttonTappedWithPath:padYPath value:normalisedY];
            }
            
        } else {
            if ([self.customButtonType isEqual:@"pad"]) {
                self.selected = NO;
                UIView *horizontalLine = objc_getAssociatedObject(self, "horizontalLine");
                UIView *verticalLine = objc_getAssociatedObject(self, "verticalLine");
                horizontalLine.backgroundColor = [UIColor blackColor];
                verticalLine.backgroundColor = [UIColor blackColor];
                
                [self.delegate buttonTappedWithPath:self.pathForButton value:0];
            } else if ([self.customButtonType isEqual:@"checkbox"]) {
                
            } else if ([self.customButtonType isEqual:@"hslider"]) {
                
            } else if ([self.customButtonType isEqual:@"vslider"]) {
                
            } else {
                self.layer.borderColor = [UIColor blackColor].CGColor;
                // Get the current background color
                UIColor *currentColor = self.backgroundColor;
                
                // Extract the RGBA components from the current color
                CGFloat red, green, blue, alpha;
                [currentColor getRed:&red green:&green blue:&blue alpha:&alpha];

                // Create a new color with adjusted alpha value
                UIColor *newColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha* 2.0];

                // Assign the new color to the background color property
                self.backgroundColor = newColor;
                //self.alpha += 0.3;
                [self.delegate buttonTappedWithPath:self.pathForButton value:0];
            }
            
        }
        
    }
    
    
    //[self setNeedsDisplay];
}

- (CGFloat)clampValue:(CGFloat)value min:(CGFloat)min max:(CGFloat)max {
    return fmin(fmax(value, min), max);
}

CGFloat mapValue(CGFloat value, CGFloat fromInputMin, CGFloat fromInputMax, CGFloat toOutputMin, CGFloat toOutputMax) {
    // Calculate the normalized value within the input range
    CGFloat normalizedValue = (value - fromInputMin) / (fromInputMax - fromInputMin);
    
    // Map the normalized value to the output range
    CGFloat mappedValue = toOutputMin + normalizedValue * (toOutputMax - toOutputMin);
    
    // Ensure the mapped value is within the output range
    mappedValue = MAX(toOutputMin, MIN(toOutputMax, mappedValue));
    
    return mappedValue;
}
@end
