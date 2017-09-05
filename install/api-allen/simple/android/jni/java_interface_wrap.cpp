/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */


#ifndef SWIGJAVA
#define SWIGJAVA
#endif



#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigMovePointer {
    T *ptr;
    SwigMovePointer(T *p) : ptr(p) { }
    ~SwigMovePointer() { delete ptr; }
    SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
  operator T&() const { return *pointer.ptr; }
  T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
  return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif


/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
  typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
  SWIG_JavaOutOfMemoryError = 1, 
  SWIG_JavaIOException, 
  SWIG_JavaRuntimeException, 
  SWIG_JavaIndexOutOfBoundsException,
  SWIG_JavaArithmeticException,
  SWIG_JavaIllegalArgumentException,
  SWIG_JavaNullPointerException,
  SWIG_JavaDirectorPureVirtual,
  SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
  SWIG_JavaExceptionCodes code;
  const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
  jclass excep;
  static const SWIG_JavaExceptions_t java_exceptions[] = {
    { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
    { SWIG_JavaIOException, "java/io/IOException" },
    { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
    { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
    { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
    { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
    { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
    { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
    { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
    { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" }
  };
  const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

  while (except_ptr->code != code && except_ptr->code)
    except_ptr++;

  jenv->ExceptionClear();
  excep = jenv->FindClass(except_ptr->java_exception);
  if (excep)
    jenv->ThrowNew(excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else


#include "DspFaust.h"


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT jlong JNICALL Java_com_DspFaust_dsp_1faustJNI_new_1DspFaust(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2) {
  jlong jresult = 0 ;
  int arg1 ;
  int arg2 ;
  DspFaust *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  result = (DspFaust *)new DspFaust(arg1,arg2);
  *(DspFaust **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_delete_1DspFaust(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(DspFaust **)&jarg1; 
  delete arg1;
}


SWIGEXPORT jboolean JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1start(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jboolean jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  bool result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (bool)(arg1)->start();
  jresult = (jboolean)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1stop(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  (arg1)->stop();
}


SWIGEXPORT jboolean JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1isRunning(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jboolean jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  bool result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (bool)(arg1)->isRunning();
  jresult = (jboolean)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1keyOn(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  jint jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  int arg3 ;
  long result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  result = (long)(arg1)->keyOn(arg2,arg3);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1keyOff(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jint jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (int)(arg1)->keyOff(arg2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1newVoice(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  long result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (long)(arg1)->newVoice();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1deleteVoice(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jint jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  long arg2 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (long)jarg2; 
  result = (int)(arg1)->deleteVoice(arg2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1allNotesOff(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  (arg1)->allNotesOff();
}


SWIGEXPORT jstring JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getJSONUI(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jstring jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (char *)(arg1)->getJSONUI();
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getJSONMeta(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jstring jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (char *)(arg1)->getJSONMeta();
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamsCount(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (int)(arg1)->getParamsCount();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1setParamValue_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jfloat jarg3) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  float arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return ;
  }
  arg3 = (float)jarg3; 
  (arg1)->setParamValue((char const *)arg2,arg3);
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1setParamValue_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jfloat jarg3) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->setParamValue(arg2,arg3);
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamValue_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (float)(arg1)->getParamValue((char const *)arg2);
  jresult = (jfloat)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamValue_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (float)(arg1)->getParamValue(arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1setVoiceParamValue_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jint jarg3, jfloat jarg4) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  long arg3 ;
  float arg4 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return ;
  }
  arg3 = (long)jarg3; 
  arg4 = (float)jarg4; 
  (arg1)->setVoiceParamValue((char const *)arg2,arg3,arg4);
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1setVoiceParamValue_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3, jfloat jarg4) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  long arg3 ;
  float arg4 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (long)jarg3; 
  arg4 = (float)jarg4; 
  (arg1)->setVoiceParamValue(arg2,arg3,arg4);
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getVoiceParamValue_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jint jarg3) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  long arg3 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  arg3 = (long)jarg3; 
  result = (float)(arg1)->getVoiceParamValue((char const *)arg2,arg3);
  jresult = (jfloat)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getVoiceParamValue_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  long arg3 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (long)jarg3; 
  result = (float)(arg1)->getVoiceParamValue(arg2,arg3);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamAddress(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jstring jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (char *)(arg1)->getParamAddress(arg2);
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getVoiceParamAddress(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  jstring jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  long arg3 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (long)jarg3; 
  result = (char *)(arg1)->getVoiceParamAddress(arg2,arg3);
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamMin_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (float)(arg1)->getParamMin((char const *)arg2);
  jresult = (jfloat)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamMin_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (float)(arg1)->getParamMin(arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamMax_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (float)(arg1)->getParamMax((char const *)arg2);
  jresult = (jfloat)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamMax_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (float)(arg1)->getParamMax(arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamInit_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (float)(arg1)->getParamInit((char const *)arg2);
  jresult = (jfloat)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getParamInit_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (float)(arg1)->getParamInit(arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getMetadata_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jstring jarg3) {
  jstring jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  arg3 = 0;
  if (jarg3) {
    arg3 = (char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3) return 0;
  }
  result = (char *)(arg1)->getMetadata((char const *)arg2,(char const *)arg3);
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  if (arg3) jenv->ReleaseStringUTFChars(jarg3, (const char *)arg3);
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getMetadata_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jstring jarg3) {
  jstring jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  char *arg3 = (char *) 0 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = 0;
  if (jarg3) {
    arg3 = (char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3) return 0;
  }
  result = (char *)(arg1)->getMetadata(arg2,(char const *)arg3);
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  if (arg3) jenv->ReleaseStringUTFChars(jarg3, (const char *)arg3);
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1propagateAcc(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jfloat jarg3) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->propagateAcc(arg2,arg3);
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1setAccConverter(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3, jint jarg4, jfloat jarg5, jfloat jarg6, jfloat jarg7) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  int arg3 ;
  int arg4 ;
  float arg5 ;
  float arg6 ;
  float arg7 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (int)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (float)jarg7; 
  (arg1)->setAccConverter(arg2,arg3,arg4,arg5,arg6,arg7);
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1propagateGyr(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jfloat jarg3) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  float arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->propagateGyr(arg2,arg3);
}


SWIGEXPORT void JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1setGyrConverter(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3, jint jarg4, jfloat jarg5, jfloat jarg6, jfloat jarg7) {
  DspFaust *arg1 = (DspFaust *) 0 ;
  int arg2 ;
  int arg3 ;
  int arg4 ;
  float arg5 ;
  float arg6 ;
  float arg7 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (int)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (float)jarg7; 
  (arg1)->setGyrConverter(arg2,arg3,arg4,arg5,arg6,arg7);
}


SWIGEXPORT jfloat JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getCPULoad(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (float)(arg1)->getCPULoad();
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_DspFaust_dsp_1faustJNI_DspFaust_1getScreenColor(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  DspFaust *arg1 = (DspFaust *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(DspFaust **)&jarg1; 
  result = (int)(arg1)->getScreenColor();
  jresult = (jint)result; 
  return jresult;
}


#ifdef __cplusplus
}
#endif

