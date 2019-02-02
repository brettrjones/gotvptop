
#link dependent library

CONFIG(debug, debug|release){
 message(Link in DEBUG mode.)
 android:{
  LIBPREFIX=$$PWD/build-libs/lib
  LIBSUFFIX=AndroidD.a
 }

 unix:!android:{
  LIBS +=  -L$$PWD/build-libs
  LIBPREFIX=LIBS += -l
  LIBSUFFIX=$${LIBSUFFIX}
 }
}

CONFIG(release, debug|release){
 message(Link in RELEASE mode.)
 android:{
  LIBPREFIX=$$PWD/build-libs/lib
  LIBSUFFIX=Android.a
 }

 !android:{
  LIBS +=-L$$PWD/build-libs
  LIBPREFIX=LIBS += -l
  LIBSUFFIX=
 }
}


#NOTE: link order is important.. otherwise you will get link errors like libvorbisenc.so.2: error adding symbols: DSO missing from command line
    CONFIG(debug, debug|release){
        LIBS +=  $${LIBPREFIX}kodi$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegavdevice$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegavfilter$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegavformat$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegavcodec$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegpostproc$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegswresample$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegswscale$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ffmpegavutil$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}nfs$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}cdio$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}pcre$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}armrwbenc$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}fdk-aac$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}opencore-amr$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}openmpt-full$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}vpx$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}x264$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}x265$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}vorbis$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ogg$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}opus$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}speex$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ptopengine$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}mediatools$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}lame$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}microhttpd$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}gnu$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}depends$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}curl$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ssh$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}ssl$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}pktlib$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}fribidi$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}iconv$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}freetype$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}png$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}tinyxml$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}xml2$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}compress$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}corelib$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}crossguid$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}bz2$${LIBSUFFIX}
        LIBS +=  $${LIBPREFIX}zlib$${LIBSUFFIX}
    }

unix:!android:{
    LIBS +=  -ldl -lGLU -lGL -lm -luuid -lrt -lpthread -lpython2.7
}

android{
    LIBS +=  -ldl -lm
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
