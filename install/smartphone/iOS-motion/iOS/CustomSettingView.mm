#import "CustomSettingView.h"

// ── Design tokens ────────────────────────────────────────────────────────────
static UIColor* BG()        { return [UIColor colorWithWhite:0.08 alpha:1]; }
static UIColor* CARD()      { return [UIColor colorWithWhite:0.13 alpha:1]; }
static UIColor* ACCENT()    { return [UIColor colorWithRed:0.24 green:0.24 blue:0.70 alpha:1]; }
static UIColor* ACCENT2()   { return [UIColor colorWithRed:0.16 green:0.40 blue:0.16 alpha:1]; }
static UIColor* DANGER()    { return [UIColor colorWithRed:0.40 green:0.16 blue:0.16 alpha:1]; }
static UIColor* TEXT()      { return [UIColor whiteColor]; }
static UIColor* SUBTEXT()   { return [UIColor colorWithWhite:0.60 alpha:1]; }
static CGFloat  ROW_H    = 44;
static CGFloat  BTN_H    = 40;
static CGFloat  PAD      = 16;

@implementation CustomSettingView {
    id<CustomSettingViewDelegate> __unsafe_unretained _delegate;
}

- (void)setDelegate:(id<CustomSettingViewDelegate>)d { _delegate = d; }
- (id<CustomSettingViewDelegate>)delegate { return _delegate; }

// ── Init ─────────────────────────────────────────────────────────────────────
- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (!self) return nil;
    self.backgroundColor = BG();
    self.layer.cornerRadius = 12;
    self.clipsToBounds = YES;

    // ── Top bar ──────────────────────────────────────────────────────────────
    UIView *topBar = [[UIView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, 50)];
    topBar.backgroundColor = [UIColor colorWithWhite:0.12 alpha:1];

    UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(PAD, 0, frame.size.width - 80, 50)];
    title.text = @"Settings";
    title.textColor = TEXT();
    title.font = [UIFont boldSystemFontOfSize:17];
    [topBar addSubview:title];

    UIButton *closeBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    closeBtn.frame = CGRectMake(frame.size.width - 60, 8, 50, 34);
    [closeBtn setTitle:@"✕" forState:UIControlStateNormal];
    [closeBtn setTitleColor:TEXT() forState:UIControlStateNormal];
    closeBtn.titleLabel.font = [UIFont systemFontOfSize:18];
    [closeBtn addTarget:self action:@selector(closeButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
    [topBar addSubview:closeBtn];
    [self addSubview:topBar];

    // ── Tab bar: hidden for iOS-motion template (no Info tab needed) ─────────
    self.segmentedControl = [[UISegmentedControl alloc] initWithItems:@[@"Setting", @"Info"]];
    self.segmentedControl.frame = CGRectMake(PAD, 56, frame.size.width - PAD*2, 32);
    self.segmentedControl.selectedSegmentIndex = 0;
    self.segmentedControl.hidden = YES;
    [self addSubview:self.segmentedControl];

    CGFloat contentY = 56; // move content up since tab bar is hidden
    CGFloat contentH = frame.size.height - contentY;

    // ── Settings page ─────────────────────────────────────────────────────────
    self.settingsView = [[UIView alloc] initWithFrame:CGRectMake(0, contentY, frame.size.width, contentH)];
    self.settingsView.backgroundColor = [UIColor clearColor];
    [self setupSettingsView:self.settingsView withFrame:frame];
    [self addSubview:self.settingsView];

    // ── Info page ─────────────────────────────────────────────────────────────
    self.infoView = [[UIView alloc] initWithFrame:CGRectMake(0, contentY, frame.size.width, contentH)];
    self.infoView.backgroundColor = [UIColor clearColor];
    [self setupInfoView:self.infoView withFrame:CGRectMake(0, 0, frame.size.width, contentH)];
    self.infoView.hidden = YES;
    [self addSubview:self.infoView];

    return self;
}

// ── Helpers ───────────────────────────────────────────────────────────────────
- (UILabel *)sectionLabel:(NSString *)text y:(CGFloat)y width:(CGFloat)w {
    UILabel *l = [[UILabel alloc] initWithFrame:CGRectMake(PAD, y, w - PAD*2, 22)];
    l.text = [text uppercaseString];
    l.textColor = SUBTEXT();
    l.font = [UIFont systemFontOfSize:11 weight:UIFontWeightSemibold];
    return l;
}

- (UIView *)cardAtY:(CGFloat)y height:(CGFloat)h width:(CGFloat)w {
    UIView *v = [[UIView alloc] initWithFrame:CGRectMake(PAD, y, w - PAD*2, h)];
    v.backgroundColor = CARD();
    v.layer.cornerRadius = 8;
    return v;
}

- (UITextField *)styledField:(CGRect)r placeholder:(NSString *)ph {
    UITextField *f = [[UITextField alloc] initWithFrame:r];
    f.placeholder = ph;
    f.textColor = TEXT();
    f.backgroundColor = [UIColor colorWithWhite:0.20 alpha:1];
    f.layer.cornerRadius = 6;
    f.font = [UIFont systemFontOfSize:14];
    f.leftView = [[UIView alloc] initWithFrame:CGRectMake(0,0,8,0)];
    f.leftViewMode = UITextFieldViewModeAlways;
    f.keyboardAppearance = UIKeyboardAppearanceDark;
    f.attributedPlaceholder = [[NSAttributedString alloc]
        initWithString:ph attributes:@{NSForegroundColorAttributeName: SUBTEXT()}];
    return f;
}

- (UIButton *)actionBtn:(NSString *)title color:(UIColor *)color frame:(CGRect)r {
    UIButton *b = [UIButton buttonWithType:UIButtonTypeSystem];
    b.frame = r;
    [b setTitle:title forState:UIControlStateNormal];
    [b setTitleColor:TEXT() forState:UIControlStateNormal];
    b.titleLabel.font = [UIFont systemFontOfSize:14 weight:UIFontWeightMedium];
    b.backgroundColor = color;
    b.layer.cornerRadius = 6;
    b.titleLabel.adjustsFontSizeToFitWidth = YES;
    return b;
}

// ── Settings page layout ──────────────────────────────────────────────────────
- (void)setupSettingsView:(UIView *)view withFrame:(CGRect)frame {
    CGFloat w = frame.size.width;
    CGFloat y = 0;
    CGFloat innerW = w - PAD*2;

    UIScrollView *sv = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, w, view.frame.size.height)];
    sv.showsVerticalScrollIndicator = YES;
    [view addSubview:sv];

    UIView *content = [[UIView alloc] initWithFrame:CGRectMake(0, 0, w, 0)];
    [sv addSubview:content];

    // ── Section: Motion Lib Parameters ───────────────────────────────────────
    [content addSubview:[self sectionLabel:@"Motion Lib Parameters" y:y width:w]];
    y += 26;

    UIView *card1 = [self cardAtY:y height:ROW_H*2 + BTN_H + 16 width:w];
    [content addSubview:card1];

    self.pickerView1 = [[UIPickerView alloc] initWithFrame:CGRectMake(0, 0, innerW, ROW_H*2)];
    self.pickerView1.tag = 1;
    self.pickerView1.backgroundColor = [UIColor colorWithWhite:0.18 alpha:1];
    [card1 addSubview:self.pickerView1];

    // "No parameters available" label for picker1 (shown when array is empty)
    self.noParamLabel1 = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, innerW, ROW_H*2)];
    self.noParamLabel1.text = @"No Motion Lib parameters available";
    self.noParamLabel1.textColor = [UIColor colorWithWhite:0.45 alpha:1];
    self.noParamLabel1.font = [UIFont systemFontOfSize:13];
    self.noParamLabel1.textAlignment = NSTextAlignmentCenter;
    self.noParamLabel1.hidden = YES;
    [card1 addSubview:self.noParamLabel1];

    CGFloat btnY = ROW_H*2 + 8;
    CGFloat halfW = (innerW - 8) / 2;
    self.param1 = [self styledField:CGRectMake(0, btnY, halfW, BTN_H) placeholder:@"Value"];
    self.param1.tag = 1;
    self.param1.delegate = self;
    [card1 addSubview:self.param1];

    self.paramSend1 = [self actionBtn:@"Set" color:ACCENT2()
                                frame:CGRectMake(halfW + 8, btnY, (halfW - 8)/2, BTN_H)];
    [self.paramSend1 addTarget:self action:@selector(paramSend1:) forControlEvents:UIControlEventTouchUpInside];
    [card1 addSubview:self.paramSend1];

    self.paramResetSend1 = [self actionBtn:@"↺ Reset" color:DANGER()
                                     frame:CGRectMake(halfW + 8 + (halfW-8)/2 + 4, btnY, (halfW-8)/2 - 4, BTN_H)];
    [self.paramResetSend1 addTarget:self action:@selector(paramResetSend1:) forControlEvents:UIControlEventTouchUpInside];
    [card1 addSubview:self.paramResetSend1];

    y += card1.frame.size.height + 16;

    // ── Section: DSP Parameters ───────────────────────────────────────────────
    [content addSubview:[self sectionLabel:@"DSP Parameters" y:y width:w]];
    y += 26;

    UIView *card2 = [self cardAtY:y height:ROW_H*2 + BTN_H + 16 width:w];
    [content addSubview:card2];

    self.pickerView2 = [[UIPickerView alloc] initWithFrame:CGRectMake(0, 0, innerW, ROW_H*2)];
    self.pickerView2.tag = 2;
    self.pickerView2.backgroundColor = [UIColor colorWithWhite:0.18 alpha:1];
    [card2 addSubview:self.pickerView2];

    // "No parameters available" label for picker2 (shown when array is empty)
    self.noParamLabel2 = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, innerW, ROW_H*2)];
    self.noParamLabel2.text = @"No DSP showName parameters available";
    self.noParamLabel2.textColor = [UIColor colorWithWhite:0.45 alpha:1];
    self.noParamLabel2.font = [UIFont systemFontOfSize:13];
    self.noParamLabel2.textAlignment = NSTextAlignmentCenter;
    self.noParamLabel2.hidden = YES;
    [card2 addSubview:self.noParamLabel2];

    self.param2 = [self styledField:CGRectMake(0, btnY, halfW, BTN_H) placeholder:@"Value"];
    self.param2.tag = 2;
    self.param2.delegate = self;
    [card2 addSubview:self.param2];

    self.paramSend2 = [self actionBtn:@"Set" color:ACCENT2()
                                frame:CGRectMake(halfW + 8, btnY, (halfW - 8)/2, BTN_H)];
    [self.paramSend2 addTarget:self action:@selector(paramSend2:) forControlEvents:UIControlEventTouchUpInside];
    [card2 addSubview:self.paramSend2];

    self.paramResetSend2 = [self actionBtn:@"↺ Reset" color:DANGER()
                                     frame:CGRectMake(halfW + 8 + (halfW-8)/2 + 4, btnY, (halfW-8)/2 - 4, BTN_H)];
    [self.paramResetSend2 addTarget:self action:@selector(paramResetSend2:) forControlEvents:UIControlEventTouchUpInside];
    [card2 addSubview:self.paramResetSend2];

    y += card2.frame.size.height + 16;

    // ── Section: Reference Orientation ───────────────────────────────────────
    [content addSubview:[self sectionLabel:@"Orientation" y:y width:w]];
    y += 26;

    UIView *card3 = [self cardAtY:y height:BTN_H + 16 width:w];
    [content addSubview:card3];

    self.setRef = [self actionBtn:@"Set Reference Orientation" color:ACCENT()
                            frame:CGRectMake(0, 8, innerW, BTN_H)];
    [self.setRef addTarget:self action:@selector(setRef:) forControlEvents:UIControlEventTouchUpInside];
    [card3 addSubview:self.setRef];

    y += card3.frame.size.height + 16;

    // ── Section: OSC ─────────────────────────────────────────────────────────
    [content addSubview:[self sectionLabel:@"OSC Configuration" y:y width:w]];
    y += 26;

    UIView *card4 = [self cardAtY:y height:ROW_H + BTN_H + 24 width:w];
    [content addSubview:card4];

    CGFloat fieldW = (innerW - 8) / 3;
    self.ip      = [self styledField:CGRectMake(0,              8, fieldW*2 - 4, ROW_H - 8) placeholder:@"IP Address"];
    self.inPort  = [self styledField:CGRectMake(fieldW*2 + 4,   8, fieldW/2 - 2, ROW_H - 8) placeholder:@"In"];
    self.outPort = [self styledField:CGRectMake(fieldW*2 + 4 + fieldW/2 + 2, 8, fieldW/2 - 2, ROW_H - 8) placeholder:@"Out"];
    self.ip.keyboardType = UIKeyboardTypeDecimalPad;
    self.inPort.keyboardType = UIKeyboardTypeNumberPad;
    self.outPort.keyboardType = UIKeyboardTypeNumberPad;
    self.ip.tag = 3;
    self.inPort.tag = 4;
    self.outPort.tag = 5;
    self.ip.delegate = self;
    self.inPort.delegate = self;
    self.outPort.delegate = self;
    [card4 addSubview:self.ip];
    [card4 addSubview:self.inPort];
    [card4 addSubview:self.outPort];

    self.setOSC = [self actionBtn:@"Set OSC" color:ACCENT()
                            frame:CGRectMake(0, ROW_H + 8, innerW, BTN_H)];
    [self.setOSC addTarget:self action:@selector(setOSC:) forControlEvents:UIControlEventTouchUpInside];
    [card4 addSubview:self.setOSC];

    y += card4.frame.size.height + 24;

    // ── Finalize scroll content ───────────────────────────────────────────────
    content.frame = CGRectMake(0, 0, w, y);
    sv.contentSize = CGSizeMake(w, y);
}

// ── Info page layout ──────────────────────────────────────────────────────────
- (void)setupInfoView:(UIView *)view withFrame:(CGRect)frame {
    UIScrollView *sv = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
    sv.showsVerticalScrollIndicator = YES;
    [view addSubview:sv];

    NSString *versionStr = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"] ?: @"";
    NSString *text = [NSString stringWithFormat:
        @"SHCdyna  v%@\n"
        @"Dynamic Faust DSP performance app for iOS\n\n"
        @"Documentation: https://github.com/RuolunWeng/SHCdyna/wiki/Manual_EN \n\n"
        @"Audio: 44100 Hz / 256 frames  ·  CoreAudio\n\n\n"

        @"── Navigation ──\n"
        @"All three top buttons require a double-tap.\n"
        @"• [Piece]   — select or delete a loaded piece\n"
        @"• [Load]    — import a .FaustPiece from Files / AirDrop\n"
        @"• [Setting] — open this settings panel\n\n"

        @"── .FaustPiece Format ──\n"
        @"A .FaustPiece is a ZIP archive. It must contain:\n"
        @"• A .dsp file with the same name as the archive\n"
        @"• Optional: .wav / .aif / .flac audio files\n"
        @"• Optional: additional .dsp library files\n"
        @"File name must not contain spaces.\n\n"

        @"── SHCUI Metadata ──\n"
        @"[SHCUI: <tab> <type> <x> <y> <w> <h> <R> <G> <B> <A>]\n"
        @"Types: button, checkbox, hslider, vslider,\n"
        @"  hbargraph, vbargraph, pad, trigCue, nextCue,\n"
        @"  prevCue, initCue, trigCounter, setRef\n"
        @"Coordinates and sizes are in %% of screen (0–100).\n\n"

        @"── Cue System ──\n"
        @"Declare /cue with [SHCUI: … trigCue …] and add\n"
        @"[touchCueManager: {1:tip1; 2:tip2; …}] metadata.\n\n"

        @"── Motion ──\n"
        @"Orientation, accelerometer and gyroscope are sent\n"
        @"to the DSP automatically.\n"
        @"Supported addresses: /yaw /pitch /roll\n"
        @"  /useraccX–Z /quaternionW–Z /compass\n\n"

        @"── OSC ──\n"
        @"Configure IP and ports in Setting.\n"
        @"Default: 192.168.1.5 / 5510 → 5511.\n\n"
        
        @"──────────\n"
        @"SHCdyna is part of the SHC project.\n\n"
        @"SHC project: https://www.lisilog.com/en/shc-2/ \n"
        @"Faust language: https://faust.grame.fr",
        versionStr];

    UITextView *label = [[UITextView alloc] initWithFrame:CGRectMake(PAD, PAD, frame.size.width - PAD*2, 0)];
    label.text = text;
    label.textColor = SUBTEXT();
    label.font = [UIFont systemFontOfSize:13];
    label.backgroundColor = [UIColor clearColor];
    label.editable = NO;
    label.scrollEnabled = NO;
    label.dataDetectorTypes = UIDataDetectorTypeLink;
    label.linkTextAttributes = @{
        NSForegroundColorAttributeName: [UIColor colorWithRed:0.4 green:0.6 blue:1.0 alpha:1],
        NSUnderlineStyleAttributeName: @(NSUnderlineStyleSingle)
    };

    CGSize sz = [label sizeThatFits:CGSizeMake(frame.size.width - PAD*2, CGFLOAT_MAX)];
    label.frame = CGRectMake(PAD, PAD, frame.size.width - PAD*2, sz.height);
    [sv addSubview:label];
    sv.contentSize = CGSizeMake(frame.size.width, sz.height + PAD*2);
}

// ── Tab switching ─────────────────────────────────────────────────────────────
- (void)segmentChanged:(UISegmentedControl *)sender {
    self.settingsView.hidden = (sender.selectedSegmentIndex != 0);
    self.infoView.hidden     = (sender.selectedSegmentIndex != 1);
}

// ── Actions ───────────────────────────────────────────────────────────────────
- (void)setOSC:(UIButton *)sender {
    [self.ip resignFirstResponder];
    [self.inPort resignFirstResponder];
    [self.outPort resignFirstResponder];
    [_delegate customSettingViewSetOSCWithAddress:self.ip.text
                                          inPort:self.inPort.text
                                         outPort:self.outPort.text];
}

- (void)setRef:(UIButton *)sender { [_delegate initFrame]; }

- (void)paramSend1:(UIButton *)sender {
    [self.param1 resignFirstResponder];
    [_delegate customSettingViewSetMotionLibParamWithValue:self.param1.text];
}

- (void)paramSend2:(UIButton *)sender {
    [self.param2 resignFirstResponder];
    [_delegate customSettingViewSetParamWithValue:self.param2.text];
}

- (void)paramResetSend1:(UIButton *)sender { [_delegate defaultMotionLibParam:sender]; }
- (void)paramResetSend2:(UIButton *)sender { [_delegate defaultMotionAudioParam:sender]; }
- (void)closeButtonTapped:(id)sender       { [self removeFromSuperview]; }

// ── Keyboard avoidance ────────────────────────────────────────────────────────
- (void)textFieldDidBeginEditing:(UITextField *)textField {
    if (textField.tag == 1 || textField.tag == 2 ||
        textField.tag == 3 || textField.tag == 4 || textField.tag == 5) {
        [UIView animateWithDuration:0.3 animations:^{
            self.frame = CGRectOffset(self.frame, 0, -220);
        }];
    }
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
    if (textField.tag == 1 || textField.tag == 2 ||
        textField.tag == 3 || textField.tag == 4 || textField.tag == 5) {
        [UIView animateWithDuration:0.3 animations:^{
            self.frame = CGRectOffset(self.frame, 0, 220);
        }];
    }
}

@end
