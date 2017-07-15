# Faust Android API

This API allows to interact with a natively compiled Faust object and its associated audio engine at a very high level from the JAVA layer of an Android app. The idea is that all the audio part of the app is implemented in Faust allowing developers to focus on the design of the app itself. 

This api keep most funtions of "faust2api -android", for more details, check that documentation.

### App Set-Up

Very little work has to be done to integrate this package to your Android app. Once this is done, you will be able to interact with the Faust DSP module from JAVA without having to write a line of native C++ code.

This package contains 2 folder: `/cpp` and `/java`. `cpp` hosts the native C++ elements that should be placed in the NDK folder of your app. `/java` contains the JAVA classes that should be placed in the `java` folder of your app in accordance with the JAVA package that was configured when `faust2api` was ran. The default package name is `com.DspFaust`, thus, in that case, the content of `/java` should be placed in `java/com/DspFaust`. You can check the [faust2api documentation](https://ccrma.stanford.edu/~rmichon/faust2api/) to get more information about that. 

In order for things to compile, your Gradle file should have an `externalNativeBuild` with something like that in it:

```
externalNativeBuild {
	cmake {
		cppFlags "-O3 -fexceptions -frtti -lOpenSLES"
	}
}
```

Also, the NDK CMake file should look like this:

```
cmake_minimum_required(VERSION 3.4.1)
add_library( 
	dsp_faust 
	SHARED 
	src/main/cpp/java_interface_wrap.cpp 
	src/main/cpp/DspFaust.cpp 
)
find_library( log-lib log )
target_link_libraries( dsp_faust ${log-lib} )

```

****If using libOSCFaust:****

Compile libOSCFaust for Android

```

    cd to /faust/architecture/osclib

    make android

    cd to /faust

    sudo make install

```

Link libOSCFaust in Android Studio

in Gradle build

```

def OSCCTRL=false

if(OSCCTRL) {
sourceSets {
main {
// let gradle pack the shared library into apk
jniLibs.srcDirs = ['/usr/local/share/faust/osclib/android/libs']
    }
           }
}

```

Cmake

```

set(OSCCTRL false)

cmake_minimum_required(VERSION 3.4.1)
add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp src/main/cpp/DspFaustMotion.cpp)
if(OSCCTRL)
add_library( libOSCFaust SHARED IMPORTED )
set_target_properties( libOSCFaust PROPERTIES IMPORTED_LOCATION /usr/local/share/faust/osclib/android/libs/${ANDROID_ABI}/libOSCFaust.so )
endif(OSCCTRL)
find_library( log-lib log )
if(OSCCTRL)
target_link_libraries( dsp_faust libOSCFaust ${log-lib} )
elseif(NOT OSCCTRL)
target_link_libraries( dsp_faust ${log-lib} )
endif(OSCCTRL)

``


Finally, since your Faust object might need to access the audio input of your device, the following line should be added to the manifest of your app (typically before the `application` tag):

	<uses-permission android:name="android.permission.RECORD_AUDIO"/>

    [After API 23] ADD RUNTIME-PERMISSION IN YOUR CODE

After this, re-synchronize Gradle and try to compile the Android app. Hopefully, things should go well!

### Using the JAVA API

    same as "faust2api -android"

