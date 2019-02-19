

#link dependent library


win32:TARGET_OS_NAME=Windows
unix:!android: TARGET_OS_NAME=Linux
android: TARGET_OS_NAME=Android
macx: TARGET_OS_NAME=Apple

TARGET_ARCH_NAME="armeabi-v7a"

android:{
    DEFINES += TARGET_OS_ANDROID
    DEFINES += TARGET_POSIX

    ANDROID_ARM64 = 0
    ANDROID_ARMv7 = 0
    ANDROID_x86 = 0
    ANDROID_x86_64 = 0

    contains(ANDROID_TARGET_ARCH,armeabi-v8a) {
        ANDROID_ARM64 = 1
        TARGET_ARCH_NAME=armeabi-v8a
    }
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_ARMv7 = 1
        TARGET_ARCH_NAME="armeabi-v7a"
    }
    contains(ANDROID_TARGET_ARCH,x86) {
        ANDROID_x86 = 1
        TARGET_ARCH_NAME=x86
    }
    contains(ANDROID_TARGET_ARCH,x86_64) {
        ANDROID_x86_64 = 1
        TARGET_ARCH_NAME=x86_64
    }
}

#link dependent librarys
CONFIG(debug, debug|release){
 message(Link in DEBUG mode.)
 android:{
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/lib
  STATIC_LIB_SUFFIX=AndroidD.a
  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/lib
  SHARED_LIB_SUFFIX=Android_d.so
  SHARED_PYTHON_LIB_SUFFIX=_d.so
 }

 unix:!android:{
  LIBS +=  -L$$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=LinuxD.a

  LIBS +=  -L$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/
  SHARED_LIB_PREFIX=LIBS += -l
  SHARED_LIB_SUFFIX=Linux_d.so
  SHARED_PYTHON_LIB_SUFFIX=_d.so
 }
}

CONFIG(release, debug|release){
 message(Link in RELEASE mode.)
 android:{
  STATIC_LIB_PREFIX=$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/lib
  STATIC_LIB_SUFFIX=Android.a
  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/lib
  SHARED_LIB_SUFFIX=Android.so
  SHARED_PYTHON_LIB_SUFFIX=.so
 }

 !android:{
  LIBS +=-L$$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=
  LIBS +=  -L$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/
  SHARED_LIB_PREFIX=LIBS += -l
  SHARED_LIB_SUFFIX=Linux.so
  SHARED_PYTHON_LIB_SUFFIX=.so
 }
}

message("**TARGET_OS_NAME-> "$${TARGET_OS_NAME})
message("**TARGET_ARCH_NAME-> "$${TARGET_ARCH_NAME})
message("**STATIC_LIB_PREFIX-> "$${STATIC_LIB_PREFIX})
message("**SHARED_LIB_PREFIX-> "$${SHARED_LIB_PREFIX})
message("**SHARED_PYTHON_LIB_SUFFIX-> "$${SHARED_PYTHON_LIB_SUFFIX})

SHARED_LIB_APPEND = .dll

CONFIG(debug, debug|release) {
win32 {
    SHARED_LIB_APPEND =  _d.dll
}

unix: {
    SHARED_LIB_APPEND =  _d
}
}

CONFIG(release, debug|release) {
win32 {
    SHARED_LIB_APPEND =  .dll
}

unix: {
    SHARED_LIB_APPEND =
}
}

