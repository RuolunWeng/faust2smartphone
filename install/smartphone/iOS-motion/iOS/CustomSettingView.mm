#import "CustomSettingView.h"

@implementation CustomSettingView{
    id<CustomSettingViewDelegate> __unsafe_unretained _delegate;
    
}

- (void)setDelegate:(id<CustomSettingViewDelegate>)delegate {
    _delegate = delegate;
}

- (id<CustomSettingViewDelegate>)delegate {
    return _delegate;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialize and configure UI elements
        _delegate = nil; // 初始化代理为nil
        
        // Calculate the offset
        CGFloat offSet = CGRectGetWidth(frame)-320;
        
        // First part
        self.ip = [[UITextField alloc] initWithFrame:CGRectMake(offSet+30, 80, 120, 30)];
        self.ip.borderStyle = UITextBorderStyleRoundedRect;
        self.ip.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:15];
        [self addSubview:self.ip];
        
        //        self.inPort = [[UITextField alloc] initWithFrame:CGRectMake(20, 130, 60, 30)];
        self.inPort = [[UITextField alloc] initWithFrame:CGRectMake(offSet+160, 80, 60, 30)];
        self.inPort.borderStyle = UITextBorderStyleRoundedRect;
        self.inPort.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:15];
        [self addSubview:self.inPort];
        
        //        self.outPort = [[UITextField alloc] initWithFrame:CGRectMake(20, 180, 60, 30)];
        self.outPort = [[UITextField alloc] initWithFrame:CGRectMake(offSet+230, 80, 60, 30)];
        self.outPort.borderStyle = UITextBorderStyleRoundedRect;
        self.outPort.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:15];
        [self addSubview:self.outPort];
        
        self.setOSC = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        //self.setOSC.titleLabel.textAlignment = NSTextAlignmentLeft;
        [self.setOSC setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0.5 alpha:0.5]]; // Set a background
        //        [self.setOSC setFrame:CGRectMake(20, 230, 80, 50)];
        [self.setOSC setFrame:CGRectMake(offSet+210, 130, 80, 50)];
        [self.setOSC setTitle:@"Set OSC" forState:UIControlStateNormal];
        self.setOSC.titleLabel.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:16];
        [self.setOSC addTarget:self action:@selector(setOSC:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.setOSC];
        
        self.setRef = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        //self.setOSC.titleLabel.textAlignment = NSTextAlignmentLeft;
        [self.setRef setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0.5 alpha:0.5]]; // Set a background
        //        [self.setOSC setFrame:CGRectMake(20, 230, 80, 50)];
        [self.setRef setFrame:CGRectMake(offSet+30, 130, 80, 50)];
        [self.setRef setTitle:@"setRef" forState:UIControlStateNormal];
        self.setRef.titleLabel.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:16];
        [self.setRef addTarget:self action:@selector(setRef:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.setRef];
        
        // Second part - Picker 1
        self.pickerView1 = [[UIPickerView alloc] initWithFrame:CGRectMake(offSet+30, 200, 120, 100)];
//                self.pickerView1.delegate = self;
//                self.pickerView1.dataSource = self;
        self.pickerView1.tag = 1; // Set tag to distinguish between pickers
        [self addSubview:self.pickerView1];
        
        self.param1 = [[UITextField alloc] initWithFrame:CGRectMake(offSet+40, 300, 100, 30)];
        self.param1.tag = 1;
        self.param1.delegate = self;
        self.param1.borderStyle = UITextBorderStyleRoundedRect;
        [self addSubview:self.param1];
        
        self.paramSend1 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [self.paramSend1 setFrame:CGRectMake(offSet+30, 340, 120, 50)];
        self.paramSend1.titleLabel.adjustsFontSizeToFitWidth = YES;
        [self.paramSend1 setTitle:@"Set Param Motion" forState:UIControlStateNormal];
        self.paramSend1.titleLabel.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:16];
        [self.paramSend1 setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0.5 alpha:0.5]]; // Set a background
        [self.paramSend1 addTarget:self action:@selector(paramSend1:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.paramSend1];
        
        self.paramResetSend1 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [self.paramResetSend1 setFrame:CGRectMake(offSet+30, 410, 120, 50)];
        self.paramResetSend1.titleLabel.adjustsFontSizeToFitWidth = YES;
        [self.paramResetSend1 setTitle:@"ReSet Param Motion" forState:UIControlStateNormal];
        self.paramResetSend1.titleLabel.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:16];
        [self.paramResetSend1 setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0.5 alpha:0.8]]; // Set a background
        [self.paramResetSend1 addTarget:self action:@selector(paramResetSend1:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.paramResetSend1];
        
        // Second part - Picker 2
        self.pickerView2 = [[UIPickerView alloc] initWithFrame:CGRectMake(offSet+170, 200, 120, 100)];
//                self.pickerView2.delegate = self;
//                self.pickerView2.dataSource = self;
        self.pickerView2.tag = 2; // Set tag to distinguish between pickers
        [self addSubview:self.pickerView2];
        
        self.param2 = [[UITextField alloc] initWithFrame:CGRectMake(offSet+180, 300, 100, 30)];
        self.param2.tag = 2;
        self.param2.delegate = self;
        self.param2.borderStyle = UITextBorderStyleRoundedRect;
        [self addSubview:self.param2];
        
        self.paramSend2 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [self.paramSend2 setFrame:CGRectMake(offSet+170, 340, 120, 50)];
        self.paramSend2.titleLabel.adjustsFontSizeToFitWidth = YES;
        [self.paramSend2 setTitle:@"Set Param Faust" forState:UIControlStateNormal];
        self.paramSend2.titleLabel.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:16];
        [self.paramSend2 setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0.5 alpha:0.5]]; // Set a background
        [self.paramSend2 addTarget:self action:@selector(paramSend2:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.paramSend2];
        
        self.paramResetSend2 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [self.paramResetSend2 setFrame:CGRectMake(offSet+170, 410, 120, 50)];
        self.paramResetSend2.titleLabel.adjustsFontSizeToFitWidth = YES;
        [self.paramResetSend2 setTitle:@"ReSet Param Faust" forState:UIControlStateNormal];
        self.paramResetSend2.titleLabel.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:16];
        [self.paramResetSend2 setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0.5 alpha:0.8]]; // Set a background
        [self.paramResetSend2 addTarget:self action:@selector(paramResetSend2:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.paramResetSend2];
        
        // Close button
        UIButton *closeButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [closeButton setFrame:CGRectMake(offSet+250, 0, 60, 40)];
        [closeButton setTitle:@"Close" forState:UIControlStateNormal];
        closeButton.titleLabel.adjustsFontSizeToFitWidth = YES;
        [closeButton setBackgroundColor:[UIColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:0.4]]; // Set a background
        [closeButton addTarget:self action:@selector(closeButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:closeButton];
        
        // Initialize arrays
//        self.paramArray1 = [NSMutableArray array];
//        self.paramArray2 = [NSMutableArray array];
        
        
        // Additional configuration...
    }
    return self;
}

- (void)setOSC:(UIButton *)sender {
    // Handle setOSC button action
    [_ip resignFirstResponder];
    [_inPort resignFirstResponder];
    [_outPort resignFirstResponder];
    
    [self.delegate customSettingViewSetOSCWithAddress:_ip.text inPort:_inPort.text outPort:_outPort.text];
}

- (void)setRef:(UIButton *)sender {
    
    [self.delegate initFrame];
}

- (void)paramSend1:(UIButton *)sender {
    // Handle paramSend1 button action
    [self.param1 resignFirstResponder];
    
    [self.delegate customSettingViewSetMotionLibParamWithValue:self.param1.text];
    
}

- (void)paramSend2:(UIButton *)sender {
    // Handle paramSend2 button action
    
    [self.param2 resignFirstResponder];
    
    [self.delegate customSettingViewSetParamWithValue:self.param2.text];
}

- (void)paramResetSend1:(UIButton *)sender {
    // Handle paramResetSend1 button action
    [self.delegate defaultMotionLibParam:sender];
}


- (void)paramResetSend2:(UIButton *)sender {
    // Handle paramResetSend2 button action
    [self.delegate defaultMotionAudioParam:sender];
}

- (void)closeButtonTapped:(id)sender {
    
    //[self.delegate endButtonTapped:sender];
    [self removeFromSuperview];

}

#pragma mark - UIPickerViewDelegate

//- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
//    // Return the number of components in each picker view
//    return 1;
//}
//
//- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
//
//    
//    // Return the number of rows in each picker view
//    if (pickerView.tag == 1) {
//        return self.paramArray1.count;
//    } else if (pickerView.tag == 2) {
//        return self.paramArray2.count;
//    }
//    return 0;
//}
//
//- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
//    // Return the title for each row in each picker view
//    if (pickerView.tag == 1) {
//        return self.paramArray1[row];
//    } else if (pickerView.tag == 2) {
//        return self.paramArray2[row];
//    }
//    return nil;
//}
//
//- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view
//{
//    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, pickerView.frame.size.width, 44)];
//    label.backgroundColor = [UIColor blueColor];
//    label.textColor = [UIColor whiteColor];
//    label.textAlignment = NSTextAlignmentCenter;
//    label.font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:15];
//    label.adjustsFontSizeToFitWidth = YES;
//    // Return the number of rows in each picker view
//    if (pickerView.tag == 1) {
//        label.text = [self.paramArray1 objectAtIndex:row];
//    } else if (pickerView.tag == 2) {
//        label.text = [self.paramArray2 objectAtIndex:row];
//    }
//    
//    return label;
//}
//
//
//-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
//    
//    [self.delegate pickerView:pickerView didSelectRow:row inComponent:component];
//}

#pragma mark - UIPickerViewDataSource

// Implement UIPickerViewDataSource methods here

#pragma mark - UITextFieldDelegate

// Implement UITextFieldDelegate methods here
-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    if (textField.tag == 1 or textField.tag == 2) {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:.3];
        [UIView setAnimationBeginsFromCurrentState:TRUE];
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y -250., self.frame.size.width, self.frame.size.height);
        
        [UIView commitAnimations];
    }
    
}


-(void)textFieldDidEndEditing:(UITextField *)textField
{
    if (textField.tag == 1 or textField.tag == 2) {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:.3];
        [UIView setAnimationBeginsFromCurrentState:TRUE];
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y +250., self.frame.size.width, self.frame.size.height);
        
        [UIView commitAnimations];
    }
    
}
@end
