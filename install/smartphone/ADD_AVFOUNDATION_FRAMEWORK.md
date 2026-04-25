# Adding AVFoundation Framework to faust2smartphone iOS Templates

## Problem
The iOS templates are missing the AVFoundation framework, which causes linker errors:
```
Undefined symbol: _AVAudioSessionCategoryPlayback
Undefined symbol: _OBJC_CLASS_$_AVAudioSession
```

## Solution
You need to add the AVFoundation framework to all three iOS template projects.

## Method 1: Using Xcode (Recommended)

For each of the three templates:
1. **iOS (Basic Mode)**: `faust2smartphone/install/smartphone/iOS/iOS.xcodeproj`
2. **iOS-motion (Motion Sensor Mode)**: `faust2smartphone/install/smartphone/iOS-motion/iOS.xcodeproj`
3. **iOS-plugin (Plugin Mode)**: `faust2smartphone/install/smartphone/iOS-plugin/iOS.xcodeproj`

Follow these steps:

1. Open the `.xcodeproj` file in Xcode
2. Select the project in the Project Navigator (left sidebar)
3. Select the target (usually named "iOS" or "FaustAPI")
4. Go to the "Build Phases" tab
5. Expand "Link Binary With Libraries"
6. Click the "+" button
7. Search for "AVFoundation.framework"
8. Select it and click "Add"
9. Save the project (Cmd+S)

## Method 2: Manual Project File Editing

If you prefer to edit the project files directly, you need to add AVFoundation framework references to each `project.pbxproj` file.

### For iOS (Basic Mode)
File: `faust2smartphone/install/smartphone/iOS/iOS.xcodeproj/project.pbxproj`

1. Add a PBXBuildFile entry (in the section with other framework build files):
```
F6AB770B2F7FF268007001A4 /* AVFoundation.framework in Frameworks */ = {isa = PBXBuildFile; fileRef = F6AB770A2F7FF268007001A4 /* AVFoundation.framework */; };
```

2. Add a PBXFileReference entry (in the section with other framework file references):
```
F6AB770A2F7FF268007001A4 /* AVFoundation.framework */ = {isa = PBXFileReference; lastKnownFileType = wrapper.framework; name = AVFoundation.framework; path = System/Library/Frameworks/AVFoundation.framework; sourceTree = SDKROOT; };
```

3. Add to the Frameworks PBXGroup (in the children array of the Frameworks group):
```
F6AB770A2F7FF268007001A4 /* AVFoundation.framework */,
```

4. Add to the PBXFrameworksBuildPhase (in the files array):
```
F6AB770B2F7FF268007001A4 /* AVFoundation.framework in Frameworks */,
```

**Note**: The UUIDs (like `F6AB770B2F7FF268007001A4`) should be unique. You can generate new ones or use these as they are unlikely to conflict.

### For iOS-motion and iOS-plugin
Repeat the same process for:
- `faust2smartphone/install/smartphone/iOS-motion/iOS.xcodeproj/project.pbxproj`
- `faust2smartphone/install/smartphone/iOS-plugin/iOS.xcodeproj/project.pbxproj`

## Verification

After adding the framework, rebuild the project. The linker errors should be resolved.

## Why This Is Needed

The code now uses AVAudioSession APIs to configure audio properly for iOS 26:
- `[[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback ...]`
- `[[AVAudioSession sharedInstance] setActive:YES ...]`

These APIs require linking against the AVFoundation framework.
