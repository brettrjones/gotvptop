# Global
TEMPLATE = app
TARGET = gotvptop
TARGET_NAME = gotvptop

QT += gui core concurrent widgets network multimedia opengl xml svg


CONFIG += qt thread silent
# C++11 support
CONFIG += c++11

#DEFINES += BOOST_NO_CXX11_RVALUE_REFERENCES
#DEFINES += QT_NO_CAST_TO_ASCII
# Fast concatenation (Qt >= 4.6)
#DEFINES += QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS

win32: DEFINES += NOMINMAX

strace_win {
    DEFINES += STACKTRACE_WIN
    DEFINES += STACKTRACE_WIN_PROJECT_PATH=$$PWD
    DEFINES += STACKTRACE_WIN_MAKEFILE_PATH=$$OUT_PWD
}


# Resource files
QMAKE_RESOURCE_FLAGS += -compress 9 -threshold 5
RESOURCES += \
    ./../../GoTvApps/GoTvCommon/gotvcommon.qrc


# Translations
TRANSLATIONS += $$files(lang/gotvptop_*.ts)

DESTDIR = ./../../bin/

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc
RCC_DIR = ./.qrc
UI_DIR = ./.ui


QMAKE_CFLAGS_YACC   = -Wno-unused -Wno-parentheses
QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions
QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers


INCLUDEPATH += ./../../
INCLUDEPATH += ./../../GoTvApps/GoTvCommon
INCLUDEPATH += ./../../GoTvApps/GoTvCommon/QtSource
INCLUDEPATH += ./../../DependLibs
INCLUDEPATH += ./../../DependLibs/libcurl/include
INCLUDEPATH += ./../../DependLibs/libcurl/lib
INCLUDEPATH += ./../../DependLibs/ffmpeg
INCLUDEPATH += ./../../DependLibs/openssl-1.0.2o
INCLUDEPATH += ./../../DependLibs/openssl-1.0.2o/inc32
INCLUDEPATH += ./../../GoTvCore/xbmc/xbmc


include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(../../GoTvApps/GoTvPtoP/build/Qt/GoTvPtoP.pri)

unix{
    CONFIG(debug, debug|release){
        LIBS += -L./../lib/libarmrwbencLinuxD.a
        LIBS += -L./../lib/libdependsLinuxD.a
        LIBS += -L./../lib/libfdk-aacLinuxD.a
        LIBS += -L./../lib/libffmpegLinuxD.a
        LIBS += -L./../lib/libgnuLinuxD.a
        LIBS += -L./../lib/libkodiLinuxD.a
        LIBS += -L./../lib/libopencore-amrLinuxD.a
        LIBS += -L./../lib/libptopengineLinuxD.a
        LIBS += -L./../lib/libsshLinuxD.a
        LIBS += -L./../lib/libvorbisLinuxD.a
        LIBS += -L./../lib/libvpxLinuxD.a
        LIBS += -L./../lib/libx264LinuxD.a
        LIBS += -L./../lib/libx265LinuxD.a
    }

    CONFIG(release, debug|release){
        LIBS += -L./../lib/gnuLinux.a
    }
}

