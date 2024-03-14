// CustomTabView.m

#import "CustomTabView.h"

@implementation CustomTabView {
    id<CustomTabViewDelegate> __unsafe_unretained _delegate;
}

- (void)setDelegate:(id<CustomTabViewDelegate>)delegate {
    _delegate = delegate;
}

- (id<CustomTabViewDelegate>)delegate {
    return _delegate;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // 初始化操作
        _delegate = nil; // 初始化代理为nil
        self.contentViews = [[NSMutableDictionary alloc] init];
        self.buttons = [[NSMutableArray array] init];
        self.nameForButton = [[NSMutableDictionary alloc] init];
        self.pathForButton = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)setContentViews:(NSMutableDictionary<NSString *, UIView *> *)contentViews {
    _contentViews = contentViews;
    // 可以在这里根据 contentViews 来生成标签页，并将 ContentView 添加到 CustomTabView 中
    // 例如：
    for (NSString *title in contentViews.allKeys) {
        UIView *contentView = contentViews[title];
        [self addTabWithTitle:title contentView:contentView];
    }
}


- (void)addTabWithTitle:(NSString *)title contentView:(UIView *)contentView {
    // 创建按钮
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button setTitle:title forState:UIControlStateNormal];
    [button.titleLabel setFont:[UIFont fontWithName:@"HelveticaNeue-Bold" size:20]];//[UIFont systemFontOfSize:16.0]];
    // Set adjustsFontSizeToFitWidth to true
    button.titleLabel.adjustsFontSizeToFitWidth = YES;
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [button setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0.5  blue:0.5  alpha:0.25]] forState:UIControlStateNormal];
    [button setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:0.5 green:0  blue:0  alpha:1]] forState:UIControlStateSelected];
    button.layer.cornerRadius = 8.0; // 圆角
    button.layer.masksToBounds = YES;
    [button addTarget:self action:@selector(tabButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
    [self.buttons addObject:button];
    
    // 设置按钮的位置和大小
    CGFloat buttonWidth = self.frame.size.width / self.buttons.count;
    CGFloat buttonHeight = 40.0; // 设置按钮高度
    CGFloat buttonY = 0;
    
    // 对按钮的title进行排序
    NSArray *sortedButtons = [self.buttons sortedArrayUsingComparator:^NSComparisonResult(UIButton *button1, UIButton *button2) {
        return [button1.titleLabel.text compare:button2.titleLabel.text];
    }];


    
    // 重新设置按钮的frame
    for (int i = 0; i < sortedButtons.count; i++) {
        UIButton *currentButton = sortedButtons[i];
        CGFloat buttonX = i * buttonWidth;
        currentButton.frame = CGRectMake(buttonX, buttonY, buttonWidth, buttonHeight);
        [self addSubview:currentButton];
    }
    
    // 将 ContentView 添加到 contentViews 字典中
    [self.contentViews setObject:contentView forKey:title];
    
    for (UIButton *button in self.buttons) {
        [self tabButtonTapped:button];
    }
//    UIButton *firstButton = self.buttons.firstObject;
//    [self tabButtonTapped:firstButton];
    UIButton *lastButton = self.buttons.lastObject;
    [self tabButtonTapped:lastButton];

}

- (void)tabButtonTapped:(UIButton *)sender {
    NSUInteger index = [self.buttons indexOfObject:sender];
    //NSLog(@"index = %ld",index);
    
    if (index != NSNotFound && index < self.contentViews.allKeys.count) {
        //NSString *title = self.contentViews.allKeys[index];
        // 获取按钮对应的标题
        NSString *title = sender.titleLabel.text;
        UIView *contentView = self.contentViews[title];
        
        // 移除旧内容视图
        for (UIView *subview in self.subviews) {
            if ([subview isKindOfClass:[UIView class]] && ![self.buttons containsObject:subview]) {
                [subview removeFromSuperview];
            }
        }
        
        contentView.frame = CGRectMake(0, CGRectGetMaxY(sender.frame), self.frame.size.width, self.frame.size.height - CGRectGetMaxY(sender.frame));
        [self addSubview:contentView];
        
        
        // 更新按钮的选中状态
        for (UIButton *button in self.buttons) {
            button.selected = NO;
        }
        sender.selected = YES;
  
    }
}

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
                     ContentViewName:(NSString *)contentViewName {
    
    // 检查 contentViews 字典中是否已经存在该 contentViewName
    UIView *existingContentView;
//    UIView *existingContentView = self.contentViews[contentViewName];
    if (!self.contentViews[contentViewName]) {
        // 如果存在，直接在现有的 contentView 上进行添加操作
        // 可以根据需要在这里对现有的 contentView 进行更新或添加内容
//        existingContentView = [[UIView alloc] initWithFrame:CGRectMake(0, 44.0, self.frame.size.width, self.frame.size.height - 44.0)];
        existingContentView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
        existingContentView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;

        [self addTabWithTitle:contentViewName contentView:existingContentView];
    } else {
        existingContentView = self.contentViews[contentViewName];
    }
    
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
    } else if ([buttonType isEqualToString:@"pad"]) {
        button = [UIButton buttonWithType:UIButtonTypeSystem];
        [button addTarget:self action:@selector(buttonTouchDownXY:event:)  forControlEvents:UIControlEventTouchDown];
        [button addTarget:self action:@selector(buttonTouchUpInsideXY:event:)  forControlEvents:UIControlEventTouchUpInside];
        [button addTarget:self action:@selector(buttonTouchDragInsideXY:event:)  forControlEvents:UIControlEventTouchDragInside];
        [button setBackgroundColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1]];
        button.alpha = 0.3;
    } else if ([buttonType isEqualToString:@"trigCounter"]) {
        button = [UIButton buttonWithType:UIButtonTypeSystem];
        [button addTarget:self action:@selector(buttonTouchDownCounter:event:)  forControlEvents:UIControlEventTouchDown];
        [button addTarget:self action:@selector(buttonTouchUpInsideCue:event:)  forControlEvents:UIControlEventTouchUpInside];
        [button setBackgroundColor:[UIColor colorWithRed:selectedRed green:selectedGreen blue:selectedBlue alpha:1.0]];
    }
    
    // 计算百分比值对应的具体坐标位置
    CGFloat x = coordinationX * existingContentView.frame.size.width / 100;
    CGFloat y = coordinationY * existingContentView.frame.size.height / 100;
    CGFloat width = widthPercent * existingContentView.frame.size.width / 100;
    CGFloat height = heightPercent * existingContentView.frame.size.height / 100;

    // 设置按钮的 frame
    button.frame = CGRectMake(x, y, width, height);
    if ([buttonType isEqualToString:@"trigCue"]) {
        [button setTitle:@"TrigCue" forState:UIControlStateNormal];
    } else {
        [button setTitle:name forState:UIControlStateNormal];
    }
    
    // Set adjustsFontSizeToFitWidth to true
    button.titleLabel.adjustsFontSizeToFitWidth = YES;
    
    UIFont *font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:MIN(button.frame.size.width * 0.3, button.frame.size.height * 0.3)];

    // Set the adjusted font for the button's title label
    button.titleLabel.font = font;
    
    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    button.layer.cornerRadius = 5.0; // 圆角
    // Make sure to enable masksToBounds to apply the corner radius
    button.layer.masksToBounds = YES;
    button.tag = tag; // 设置按钮的标签
    
    // 添加按钮到选项卡视图中
    [existingContentView addSubview:button];
    
    // 保存按钮名称和标签的对应关系
    [self.nameForButton setObject:name forKey:@(tag)];
    [self.pathForButton setObject:path forKey:@(tag)];
    
    //init
    if ([buttonType isEqualToString:@"trigCounter"]) {
        [self.delegate buttonCounterReset:path tag:tag];
    } else {
        [self.delegate buttonTappedWithPath:path value:0];
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


- (void)buttonTouchUpInside:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSLog(@"Button tapped Up with name: %@", buttonName);
    
    // 调用代理方法，将参数传递给代理对象
    [self.delegate buttonTappedWithPath:buttonPath value:0];
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], 0);
    
    sender.alpha += 0.3;

}

- (void)buttonTouchDown:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSLog(@"Button tapped Down with name: %@", buttonName);
    [self.delegate buttonTappedWithPath:buttonPath value:1];
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], 1);
    
    sender.alpha -= 0.3;

}

- (void)buttonTouchDownCue:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
//    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    NSLog(@"Button tapped Down for Cue with name: %@", buttonName);
    sender.alpha -= 0.3;

    [self.delegate buttonTappedCue];
    

}

- (void)buttonTouchDownCounter:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *buttonPath = [self.pathForButton objectForKey:@(sender.tag)];
    NSLog(@"Button tapped Down for Counter with name: %@", buttonName);
    sender.alpha -= 0.3;

    [self.delegate buttonTappedCounter:buttonPath tag:sender.tag];
    

}


- (void)buttonTouchUpInsideCue:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSLog(@"Button tapped Up for Cue/CustomCounter with name: %@", buttonName);
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
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedY);
    [self.delegate buttonTappedWithPath:buttonPath value:normalisedY];
    
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
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedX);
    [self.delegate buttonTappedWithPath:buttonPath value:normalisedX];

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
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedY);
    [self.delegate buttonTappedWithPath:buttonPath value:normalisedY];

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
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedX);
    [self.delegate buttonTappedWithPath:buttonPath value:normalisedX];

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
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedY);
    [self.delegate buttonTappedWithPath:buttonPath value:normalisedY];

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
    
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedX);
    [self.delegate buttonTappedWithPath:buttonPath value:normalisedX];
    
    sender.alpha = normalisedX;
    sender.alpha += 0.3;

}

- (void)buttonTouchDownXY:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *padButtonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSString *padXPath = [NSString stringWithFormat:@"%@_X",padButtonPath];
    NSString *padYPath = [NSString stringWithFormat:@"%@_Y",padButtonPath];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedX = [self clampValue:touchPoint.x / sender.frame.size.width min:0 max:1];
    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / sender.frame.size.height min:0 max:1];

    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Down: X = %f,(Normalised: X = %f)", buttonName, touchPoint.x, normalisedX);
    NSLog(@"%@: Touch Down: Y = %f,(Normalised: Y = %f)", buttonName, touchPoint.y, normalisedY);
    
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedX);
    [self.delegate buttonTappedWithPath:padButtonPath value:1];
    [self.delegate buttonTappedWithPath:padXPath value:normalisedX];
    [self.delegate buttonTappedWithPath:padYPath value:normalisedY];

    //sender.alpha -= 0.3;
    sender.alpha = normalisedX*normalisedY;
    sender.alpha += 0.3;
}

- (void)buttonTouchDragInsideXY:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *padButtonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSString *padXPath = [NSString stringWithFormat:@"%@_X",padButtonPath];
    NSString *padYPath = [NSString stringWithFormat:@"%@_Y",padButtonPath];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedX = [self clampValue:touchPoint.x / sender.frame.size.width min:0 max:1];
    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / sender.frame.size.height min:0 max:1];

    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Drag Inside: X = %f,(Normalised: X = %f)", buttonName, touchPoint.x, normalisedX);
    NSLog(@"%@: Touch Drag Inside: Y = %f,(Normalised: Y = %f)", buttonName, touchPoint.y, normalisedY);
    
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedX);
    
    [self.delegate buttonTappedWithPath:padXPath value:normalisedX];
    [self.delegate buttonTappedWithPath:padYPath value:normalisedY];

    //sender.alpha -= 0.3;
    sender.alpha = normalisedX*normalisedY;
    sender.alpha += 0.3;
}

- (void)buttonTouchUpInsideXY:(UIButton *)sender event:(UIEvent *)event {
    // 处理普通按钮点击事件
    NSString *buttonName = [self.nameForButton objectForKey:@(sender.tag)];
    NSString *padButtonPath = [self.pathForButton objectForKey:@(sender.tag)];
    
    NSString *padXPath = [NSString stringWithFormat:@"%@_X",padButtonPath];
    NSString *padYPath = [NSString stringWithFormat:@"%@_Y",padButtonPath];
    
    // 获取按钮的触摸事件
    UITouch *touch = [[[event allTouches] allObjects] firstObject];
    // 获取触摸点位的坐标
    CGPoint touchPoint = [touch locationInView:sender];

    // 计算normalised坐标
    CGFloat normalisedX = [self clampValue:touchPoint.x / sender.frame.size.width min:0 max:1];
    CGFloat normalisedY = [self clampValue:1.0f - touchPoint.y / sender.frame.size.height min:0 max:1];

    // 输出触摸点位的x/y坐标
    NSLog(@"%@: Touch Up Inside: X = %f,(Normalised: X = %f)", buttonName, touchPoint.x, normalisedX);
    NSLog(@"%@: Touch Up Inside: Y = %f,(Normalised: Y = %f)", buttonName, touchPoint.y, normalisedY);
    
    //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], normalisedX);
    [self.delegate buttonTappedWithPath:padButtonPath value:0];
    [self.delegate buttonTappedWithPath:padXPath value:normalisedX];
    [self.delegate buttonTappedWithPath:padYPath value:normalisedY];

    //sender.alpha -= 0.3;
    sender.alpha = normalisedX*normalisedY;
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
        //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], 1);
        [self.delegate buttonTappedWithPath:buttonPath value:1];
    } else {
        NSLog(@"Toggled button isNotSelected with name: %@", buttonName);
        //self.dspFaust->setParamValueDsp(self.currentDSP,[buttonPath UTF8String], 0);
        [self.delegate buttonTappedWithPath:buttonPath value:0];
    }
    
}


@end

