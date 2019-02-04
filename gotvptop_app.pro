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




# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

#INCLUDEPATH += $$PWD/build/QtSandbox/QtSimpleTestLib

#SOURCES += \
#        $$PWD/build/QtSandbox/QtSimpleTestApp/main.cpp \
#        $$PWD/build/QtSandbox/QtSimpleTestApp/mainwindow.cpp

#HEADERS += \
#        $$PWD/build/QtSandbox/QtSimpleTestApp/mainwindow.h

#FORMS += \
#        $$PWD/build/QtSandbox/QtSimpleTestApp/mainwindow.ui


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


include(version.pri)
include(os_detect.pri)
include(compile_config.pri)


include(gotvptop_app.pri)


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

include(gotvptop_app_link.pri)
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

android:{
    LIBS +=  $${LIBPREFIX}pythonstatic$${LIBSUFFIX}
    LIBS +=  -ldl -lm -landroid -lEGL -lGLESv3
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
    android/gradlew.bat
