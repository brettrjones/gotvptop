# Global
TARGET = gotvptop
TEMPLATE = app

#TARGET_NAME = gotvptop

QT += gui core concurrent widgets network multimedia opengl xml svg

#CONFIG += qt thread silent
# C++11 support
CONFIG += c++11

CONFIG += mobility
MOBILITY =


#DEFINES += BOOST_NO_CXX11_RVALUE_REFERENCES
#DEFINES += QT_NO_CAST_TO_ASCII
# Fast concatenation (Qt >= 4.6)
#DEFINES += QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS

#win32: DEFINES += NOMINMAX

#strace_win {
#    DEFINES += STACKTRACE_WIN
#    DEFINES += STACKTRACE_WIN_PROJECT_PATH=$$PWD
#    DEFINES += STACKTRACE_WIN_MAKEFILE_PATH=$$OUT_PWD
#}

# Resource files
#QMAKE_RESOURCE_FLAGS += -compress 9 -threshold 5
#RESOURCES += $$PWD/GoTvApps/GoTvCommon/gotvcommon.qrc


# Translations
# TRANSLATIONS += $$files(lang/gotvptop_*.ts)


include(config_version.pri)
include(config_os_detect.pri)
include(config_compiler.pri)




include(GoTvPtoP_App.pri)


#DESTDIR = $$PWD/bin/


#MOC_DIR = $$PWD/.moc
#RCC_DIR = $$PWD/.qrc
#UI_DIR = $$PWD/.ui


#QMAKE_CFLAGS_YACC   = -Wno-unused -Wno-parentheses
#QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
#QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions
#QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers

#### for static linked qt libs only
#### QMAKE_LFLAGS += -static

#include(gotvptop_link.pri)
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

win32:TARGET_OS_NAME=Windows
unix:!android: TARGET_OS_NAME=Linux
android: TARGET_OS_NAME="Android"
macx: TARGET_OS_NAME=Apple

#link dependent library
message("TARGET_OS_NAME ")
message($$(TARGET_OS_NAME))
message("TARGET_ARCH_NAME ")
message($$(TARGET_ARCH_NAME))

CONFIG(debug, debug|release){
 message(Link in DEBUG mode.)
 android:{
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/$$(TARGET_ARCH_NAME)/lib
  STATIC_LIB_SUFFIX=AndroidD.a
 }

 unix:!android:{
  LIBS +=  -L$$PWD/build-staticlibs/$$(TARGET_ARCH_NAME)/lib
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=LinuxD.a
 }
}

CONFIG(release, debug|release){
 message(Link in RELEASE mode.)
 android:{
  STATIC_LIB_PREFIX=$$PWD/build-staticlibs/$$(TARGET_ARCH_NAME)
  STATIC_LIB_SUFFIX=Android.a
 }

 !android:{
  LIBS +=-L$$PWD/build-staticlibs/$$(TARGET_ARCH_NAME)
  STATIC_LIB_PREFIX=LIBS += -l
  STATIC_LIB_SUFFIX=
 }
}


#NOTE: link order is important.. otherwise you will get link errors like libvorbisenc.so.2: error adding symbols: DSO missing from command line
    CONFIG(debug, debug|release){
        LIBS +=  $${STATIC_LIB_PREFIX}kodi$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegavdevice$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegavfilter$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegavformat$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegavcodec$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegpostproc$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegswresample$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegswscale$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ffmpegavutil$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}nfs$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}cdio$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}pcre$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}armrwbenc$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}fdk-aac$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}opencore-amr$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}openmpt-full$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}vpx$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}x264$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}x265$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}vorbis$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ogg$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}opus$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}speex$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ptopengine$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}mediatools$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}lame$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}microhttpd$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ssh$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}ssl$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}pktlib$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}fribidi$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}iconv$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}freetype$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}png$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}tinyxml$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}xml2$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}compress$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
        LIBS +=  $${STATIC_LIB_PREFIX}zlib$${STATIC_LIB_SUFFIX}
    }

unix:!android:{
    LIBS +=  -ldl -lGLU -lGL -lm -luuid -lrt -lpthread -lpython2.7
}

android:{
    LIBS +=  $${STATIC_LIB_PREFIX}pythoncore$${STATIC_LIB_SUFFIX}
    LIBS +=  -ldl -lm -landroid -lEGL -lGLESv2  -lc -lstdc++ -llog
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../android/ndk-windows-x86-64/android-ndk-r19/platforms/android-21/arch-arm/usr/lib/libGLESv2.so

    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/res/values/strings.xml
