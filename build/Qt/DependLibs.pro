# Global
TEMPLATE = lib
CONFIG += qt thread silent

# C++11 support
#CONFIG += c++11

QT += xml concurrent network

DEFINES += QT_NO_CAST_TO_ASCII
# Fast concatenation (Qt >= 4.6)
DEFINES += QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS

include(version.pri)
include(os_detect.pri)

# Windows specific configuration
win32{
    include(winconf_lib.pri)
}else{
    include(unixconf_lib.pri)
}

CONFIG(debug, debug|release){
 message(Project is built in DEBUG mode.)
}

CONFIG(release, debug|release){
 message(Project is built in RELEASE mode.)
}

CONFIG(release, debug|release){
    DEFINES += _DEBUG
    linux:!android: message(Disabling UNIX debug output.)
    win32: message(Disabling WIN32 debug output.)
    android: message(Disabling ANDROID debug output.)
    DEFINES += QT_NO_DEBUG_OUTPUT
}

CONFIG(debug, debug|release){
    DEFINES += NDEBUG
    linux:!android: message(Enabling UNIX debug output.)
    win32: message(Enabling WIN32 debug output.)
    android: message(Enabling ANDROID debug output.)
}

TARGET_LIB_APPEND = .lib

CONFIG(debug, debug|release) {
    DESTDIR = ../../debug
   TARGET_LIB_APPEND =  D.lib
}

CONFIG(release, debug|release) {
    DESTDIR = ../../release
    $$TARGET_LIB_APPEND = .lib
}

TARGET_NAME = DependLibs


TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./../../lib/

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc
RCC_DIR = ./.qrc
UI_DIR = ./.ui

INCLUDEPATH += ./../../
INCLUDEPATH += ./../../DependLibs
INCLUDEPATH += ./../../GoTvCore
INCLUDEPATH += ./../../GoTvCore/xbmc

QMAKE_CFLAGS_YACC   = -Wno-unused -Wno-parentheses
QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions
QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers


#include(../../DependLibs/bzlib/build/Qt/libbz2.pri)
include(../../GoTvCore/build/Qt/libGoTvCore.pri)


#include(../../DependLibs/CoreLib/build/Qt/CoreLib.pri)
#include(../../DependLibs/db-4.7.25.0/buildQt/db_static.pri)

win32{
#include(../../DependLibs/EasyHookLib/build/Qt/EasyHook.pri)
#include(../../DependLibs/Effects11/build/Qt/Effects11.pri)
}

#include(../../DependLibs/ffmpeg/libavcodec/build/Qt/FfmpegAvCodec.pri)
#include(../../DependLibs/ffmpeg/libavdevice/build/Qt/FfmpegAvDevice.pri)
#include(../../DependLibs/ffmpeg/libavfilter/build/Qt/FfmpegAvFilterLib.pri)
#include(../../DependLibs/ffmpeg/libavformat/build/Qt/FfmpegAvFormatLib.pri)
#include(../../DependLibs/ffmpeg/libavresample/build/Qt/FfmpegAvResampleLib.pri)
#include(../../DependLibs/ffmpeg/libavutil/build/Qt/FfmpegAvUtilLib.pri)
#include(../../DependLibs/ffmpeg/libpostproc/build/Qt/FfmpegPostProcLib.pri)
#include(../../DependLibs/ffmpeg/libswresample/build/Qt/FfmpegSwResampleLib.pri)
#include(../../DependLibs/ffmpeg/libswscale/build/Qt/FfmpegSwScaleLib.pri)
#include(../../DependLibs/ffmpeg/build/Qt/libffmpeg.pri)

#include(../../DependLibs/libasprintf/buildQt/libasprintf.pri)

#include(../../DependLibs/libass/build/Qt/libass.pri)

#include(../../DependLibs/libbzip2/build/Qt/libbzip2.pri)

#include(../../DependLibs/libcpluff/build/Qt/libcpluff.pri)
#include(../../DependLibs/libcroco/build/Qt/libcroco.pri)
#include(../../DependLibs/libcrossguid/build/Qt/libcrossguid.pri)
#include(../../DependLibs/libcrystalhd/build/Qt/libcrystalhd.pri)
#include(../../DependLibs/libcurl/build/Qt/libcurl.pri)

#include(../../DependLibs/libexif/build/Qt/libexif.pri)
#include(../../DependLibs/libexpat/build/Qt/libexpat.pri)

#include(../../DependLibs/libfaac/build/Qt/libfaac.pri)
#include(../../DependLibs/libfdk-aac/build/Qt/libfdk-aac.pri)
#include(../../DependLibs/libflac/build/Qt/libflac.pri)
#include(../../DependLibs/libfreetype/build/Qt/libfreetype.pri)
#include(../../DependLibs/libfribid/build/Qt/libfribid.pri)

#include(../../DependLibs/libglew/build/Qt/libglew.pri)
#include(../../DependLibs/libgnu/build/Qt/libgnu.pri)
#include(../../DependLibs/libgsm/build/Qt/libgsm.pri)

#include(../../DependLibs/libiconv/build/Qt/libiconv.pri)
#include(../../DependLibs/libilbc/build/Qt/libilbc.pri)
##include(../../DependLibs/libirrlicht/build/Qt/libirrlicht.pri)
#include(../../DependLibs/libkvazaar/build/Qt/libkvazaar.pri)

#include(../../DependLibs/liblame/build/Qt/liblame.pri)
##include(../../DependLibs/liblinuxsim/build/Qt/liblinuxsim.pri)
#include(../../DependLibs/liblzo/build/Qt/liblzo.pri)
#include(../../DependLibs/libmdnsresponder/build/Qt/libmdnsresponder.pri)
#include(../../DependLibs/libmicrohttpd/build/Qt/libmicrohttpd.pri)

#include(../../DependLibs/libogg/build/Qt/libogg.pri)
#include(../../DependLibs/libopencore-amrwb/build/Qt/libopencore-amrwb.pri)
#include(../../DependLibs/libopenh264/build/Qt/libopenh264.pri)
#include(../../DependLibs/libopenjpeg/build/Qt/libopenjpeg.pri)
#include(../../DependLibs/libopus/build/Qt/libopus.pri)

#include(../../DependLibs/libpcre/build/Qt/libpcre.pri)
#include(../../DependLibs/libpng/build/Qt/libpng.pri)
#include(../../DependLibs/libpthread/build/Qt/libpthread.pri)

#include(../../DependLibs/librsvg/build/Qt/librsvg.pri)
#include(../../DependLibs/libsdl/build/Qt/libsdl.pri)
#include(../../DependLibs/libshine/build/Qt/libshine.pri)
#include(../../DependLibs/libsnappy/build/Qt/libsnappy.pri)
#include(../../DependLibs/libspeex/build/Qt/libspeex.pri)
#include(../../DependLibs/libssh/build/Qt/libssh.pri)

#include(../../DependLibs/libtheora/build/Qt/libtheora.pri)
#include(../../DependLibs/libtwolame/build/Qt/libtwolame.pri)
#include(../../DependLibs/libUPnP/build/Qt/libUPnP.pri)

#include(../../DependLibs/libvo-amrwbenc/build/Qt/libvo-amrwbenc.pri)
#include(../../DependLibs/libvorbis/build/Qt/libvorbis.pri)
#include(../../DependLibs/libvpx/build/Qt/libvpx.pri)

#include(../../DependLibs/libwavepack/build/Qt/libwavepack.pri)
#include(../../DependLibs/libwebp/build/Qt/libwebp.pri)
#include(../../DependLibs/libvpx/build/Qt/libvpx.pri)

#include(../../DependLibs/libx264/build/Qt/libx264.pri)
#include(../../DependLibs/libx265/build/Qt/libx265.pri)
#include(../../DependLibs/libxavs/build/Qt/libxavs.pri)
#include(../../DependLibs/libxml/build/Qt/libxml.pri)
#include(../../DependLibs/libxml2/build/Qt/libxml2.pri)
#include(../../DependLibs/libxslt/build/Qt/libxslt.pri)
#include(../../DependLibs/libxvid/build/Qt/libxvid.pri)

#include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)
#include(../../DependLibs/MediaToolsLib/build/Qt/libmediatools.pri)

#include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)
#include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)
#include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)
#include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)
#include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)

#SOURCES +=



