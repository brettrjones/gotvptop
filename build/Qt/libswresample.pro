# Global
TEMPLATE = lib

TARGET_NAME = ffmpegswresample

CONFIG += qt thread silent

QT += network

DEFINES += QT_NO_CAST_TO_ASCII
# Fast concatenation (Qt >= 4.6)
DEFINES += QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS

INCLUDEPATH += ./../../
INCLUDEPATH += ./../../DependLibs
INCLUDEPATH += ./../../DependLibs/libcurl/include
INCLUDEPATH += ./../../DependLibs/libcurl/lib
INCLUDEPATH += ./../../DependLibs/ffmpeg


include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_libstatic.pri)


TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./../../lib/

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc
RCC_DIR = ./.qrc
UI_DIR = ./.ui

QMAKE_CFLAGS_YACC   = -Wno-unused -Wno-parentheses
QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions
QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers


#include(../../DependLibs/ffmpeg/libavcodec/build/Qt/libavcodec.pri)
#include(../../DependLibs/ffmpeg/libavdevice/build/Qt/libavdevice.pri)
#include(../../DependLibs/ffmpeg/libavfilter/build/Qt/libavfilter.pri)
#include(../../DependLibs/ffmpeg/libavformat/build/Qt/libavformat.pri)
#include(../../DependLibs/ffmpeg/libavresample/build/Qt/libavresample.pri)
#include(../../DependLibs/ffmpeg/libavutil/build/Qt/libavutil.pri)
#include(../../DependLibs/ffmpeg/libpostproc/build/Qt/libpostproc.pri)
include(../../DependLibs/ffmpeg/libswresample/build/Qt/libswresample.pri)
#include(../../DependLibs/ffmpeg/libswscale/build/Qt/libswscale.pri)





