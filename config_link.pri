

#link dependent library

STATIC_LIB_PREFIX=
STATIC_LIB_SUFFIX=

CONFIG(debug, debug|release){
 message(config link in DEBUG mode.)
 android:{
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/lib
  STATIC_LIB_SUFFIX=AndroidD.a
  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/lib
  SHARED_LIB_SUFFIX=.so
 }

 unix:!android:{
  LIBS +=  -L$$PWD/build-staticlibs/lib
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=D
  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/lib
  SHARED_LIB_SUFFIX=.so
 }
}

CONFIG(release, debug|release){
 message(config link in RELEASE mode.)
win32 {
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/
  STATIC_LIB_SUFFIX=.lib
  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/
  SHARED_LIB_SUFFIX=.lib
}

 android:{
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/lib
  STATIC_LIB_SUFFIX=Android.a
  SHARED_LIB_PREFIX=$$PWD/build-sharedlibs/lib
  SHARED_LIB_SUFFIX=.so
 }

 !android:{
  LIBS +=-L$$PWD/build-staticlibs/
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=
 }
}

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

