

#link dependent library


#link dependent libraries
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
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/lib
  STATIC_LIB_SUFFIX=LinuxD.a

  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/lib
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

unix:!android:{
  LIBS +=-L$$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=Linux.so

  LIBS +=  -L$$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/
  SHARED_LIB_PREFIX=LIBS += -l
  SHARED_LIB_SUFFIX=Linux.so
  SHARED_PYTHON_LIB_SUFFIX=.so
 }
}

message("**TARGET_OS_NAME-> "$${TARGET_OS_NAME})
message("**TARGET_ARCH_NAME-> "$${TARGET_ARCH_NAME})
message("**STATIC_LIB_PREFIX-> "$${STATIC_LIB_PREFIX})
message("**STATIC_LIB_SUFFIX-> "$${STATIC_LIB_SUFFIX})
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

