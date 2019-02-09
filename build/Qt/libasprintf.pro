# Global
TEMPLATE = lib

TARGET_NAME = depends


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
INCLUDEPATH += ./../../GoTvCore
INCLUDEPATH += ./../../GoTvCore/xbmc


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

QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers

### build seperately #include(../../GoTvCore/build/Qt/libptopengine.pri)
### build seperately #include(../../GoTvCore/build/Qt/libxbmc.pri)

### build seperately include(../../DependLibs/CoreLib/build/Qt/CoreLib.pri)

win32{
#include(../../DependLibs/EasyHookLib/build/Qt/EasyHook.pri)
#include(../../DependLibs/Effects11/build/Qt/Effects11.pri)
}

### build in libffmpeg
#include(../../DependLibs/ffmpeg/libavcodec/build/Qt/libavcodec.pri)
#include(../../DependLibs/ffmpeg/libavdevice/build/Qt/libavdevice.pri)
#include(../../DependLibs/ffmpeg/libavfilter/build/Qt/libavfilter.pri)
#include(../../DependLibs/ffmpeg/libavformat/build/Qt/libavformat.pri)
#include(../../DependLibs/ffmpeg/libavresample/build/Qt/libavresample.pri)
#include(../../DependLibs/ffmpeg/libavutil/build/Qt/libavutil.pri)
#include(../../DependLibs/ffmpeg/libpostproc/build/Qt/libpostproc.pri)
#include(../../DependLibs/ffmpeg/libswresample/build/Qt/libswresample.pri)
#include(../../DependLibs/ffmpeg/libswscale/build/Qt/libswscale.pri)

### build seperately include(../../DependLibs/libarmrwbenc/build/Qt/libarmrwbenc.pri)
include(../../DependLibs/libass/build/Qt/libass.pri)

include(../../DependLibs/libcpluff/build/Qt/libcpluff.pri)
include(../../DependLibs/libcroco/build/Qt/libcroco.pri)
### build seperately include(../../DependLibs/libcrossguid/build/Qt/libcrossguid.pri)
###include(../../DependLibs/libcrystalhd/build/Qt/libcrystalhd.pri)
### build seperately include(../../DependLibs/libcurl/build/Qt/libcurl.pri)

include(../../DependLibs/libexif/build/Qt/libexif.pri)
include(../../DependLibs/libexpat/build/Qt/libexpat.pri)

###include(../../DependLibs/libfaac/build/Qt/libfaac.pri)
### build seperately include(../../DependLibs/libfdk-aac/build/Qt/libfdk-aac.pri)
include(../../DependLibs/libflac/build/Qt/libflac.pri)
### build seperately include(../../DependLibs/libfreetype/build/Qt/libfreetype.pri)
include(../../DependLibs/libfribid/build/Qt/libfribidi.pri)

include(../../DependLibs/libglew/build/Qt/libglew.pri)
### build seperately include(../../DependLibs/libgnu/build/Qt/libgnu.pri)
include(../../DependLibs/libgsm/build/Qt/libgsm.pri)

include(../../DependLibs/libiconv/build/Qt/libiconv.pri)
include(../../DependLibs/libilbc/build/Qt/libilbc.pri)
include(../../DependLibs/libjpg/build/Qt/libjpg.pri)

###include(../../DependLibs/libirrlicht/build/Qt/libirrlicht.pri)
###include(../../DependLibs/libkvazaar/build/Qt/libkvazaar.pri)

### build seperately include(../../DependLibs/liblame/build/Qt/liblame.pri)

include(../../DependLibs/libmdnsresponder/build/Qt/libdnssd.pri)
### build seperately include(../../DependLibs/libmicrohttpd/build/Qt/libmicrohttpd.pri)

### build seperately include(../../DependLibs/libogg/build/Qt/libogg.pri)
### build seperately include(../../DependLibs/libopencore-amr/build/Qt/libopencore-amr.pri)
###include(../../DependLibs/libopenh264/build/Qt/libopenh264.pri)
include(../../DependLibs/libopenjpeg/build/Qt/libopenjpeg.pri)
### build seperately include(../../DependLibs/libopus/build/Qt/libopus.pri)

### build seperately include(../../DependLibs/libpcre/build/Qt/libpcre.pri)
### build seperately include(../../DependLibs/libpng/build/Qt/libpng.pri)
### build seperately include(../../DependLibs/libpthread/build/Qt/libpthread.pri)

###include(../../DependLibs/librsvg/build/Qt/librsvg.pri)
###include(../../DependLibs/libsdl/build/Qt/libsdl.pri)
include(../../DependLibs/libshine/build/Qt/libshine.pri)
include(../../DependLibs/libsnappy/build/Qt/libsnappy.pri)
include(../../DependLibs/libspeex/build/Qt/libspeex.pri)
### build seperately include(../../DependLibs/libssh/build/Qt/libssh.pri)
### build seperately include(../../DependLibs/openssl-1.0.2o/build/Qt/libssl.pri)

include(../../DependLibs/libtag/build/Qt/libtag.pri)
include(../../DependLibs/libtheora/build/Qt/libtheora.pri)
include(../../DependLibs/libtwolame/build/Qt/libtwolame.pri)
include(../../DependLibs/libUPnP/build/Qt/libUPnP.pri)

include(../../DependLibs/libvmaf/build/Qt/libvmaf.pri)
### build seperately include(../../DependLibs/libvorbis/build/Qt/libvorbis.pri)
### build seperately include(../../DependLibs/libvpx/build/Qt/libvpx.pri)

include(../../DependLibs/libwavepack/build/Qt/libwavepack.pri)
include(../../DependLibs/libwebp/build/Qt/libwebp.pri)

### build seperately include(../../DependLibs/libx264/build/Qt/libx264.pri)
### build seperately include(../../DependLibs/libx265/build/Qt/libx265.pri)
### build seperately include(../../DependLibs/libxavs/build/Qt/libxavs.pri)

###include(../../DependLibs/libxpm/build/Qt/libxpm.pri)
include(../../DependLibs/libxslt/build/Qt/libxslt.pri)
###include(../../DependLibs/libxvid/build/Qt/libxvid.pri)

include(../../DependLibs/libyajl/build/Qt/libyajl.pri)
include(../../DependLibs/libzvbi/build/Qt/libzvbi.pri)

### build seperately include(../../DependLibs/MediaToolsLib/build/Qt/libmediatools.pri)


include(../../DependLibs/NetLib/build/Qt/libnetlib.pri)
include(../../DependLibs/PktLib/build/Qt/libpktlib.pri)
include(../../DependLibs/Upnp2Lib/build/Qt/libupnp2lib.pri)

### build seperately include(../../DependLibs/libasprintf/build/Qt/libasprintf.pri)


#SOURCES +=







