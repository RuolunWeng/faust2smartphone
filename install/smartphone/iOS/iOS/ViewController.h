//
//  ViewController.h
//  FaustAPInew
//
//  Created by Allen on 08/12/2016.
//  Copyright © 2016 Allen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property (retain, nonatomic) IBOutlet UILabel *freqLabel;
@property (retain, nonatomic) IBOutlet UILabel *volumeLabel;

@property (retain, nonatomic) IBOutlet UISlider *freq;
@property (retain, nonatomic) IBOutlet UISlider *volume;

- (IBAction)volumeOut:(id)sender;
- (IBAction)freqOut:(id)sender;

@property (retain, nonatomic) IBOutlet UILabel *freqValue;
@property (retain, nonatomic) IBOutlet UILabel *volumeValue;

@end

