set(OSCCTRL false)
set(SOUNDFILE false)

  cmake_minimum_required(VERSION 3.4.1)

 if(OSCCTRL)
     add_library( libOSCFaust SHARED IMPORTED )
     set_target_properties( libOSCFaust PROPERTIES IMPORTED_LOCATION /usr/local/share/faust/osclib/android/libs/${ANDROID_ABI}/libOSCFaust.so )
 endif(OSCCTRL)

 if(SOUNDFILE)
    add_library( libsndfile SHARED IMPORTED )
    include_directories( lib/libsndfile/include )
    set_target_properties( libsndfile PROPERTIES IMPORTED_LOCATION ../../../../lib/libsndfile/lib/${ANDROID_ABI}/libsndfile.so )
endif(SOUNDFILE)

add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp )



  find_library( log-lib log )

  if(OSCCTRL)
  if(SOUNDFILE)
  target_link_libraries( dsp_faust libOSCFaust libsndfile ${log-lib})
  elseif(NOT SOUNDFILE)
  target_link_libraries( dsp_faust libOSCFaust ${log-lib} )
  endif(SOUNDFILE)
  elseif(NOT OSCCTRL)
  if(SOUNDFILE)
  target_link_libraries( dsp_faust libsndfile ${log-lib})
  elseif(NOT SOUNDFILE)
  target_link_libraries( dsp_faust ${log-lib} )
  endif(SOUNDFILE)
  endif(OSCCTRL)
