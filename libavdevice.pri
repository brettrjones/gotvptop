

INCLUDEPATH += $$PWD/DependLibs/libcurl/include
INCLUDEPATH += $$PWD/DependLibs/libcurl/lib
INCLUDEPATH += $$PWD/DependLibs/ffmpeg

HEADERS += 	$$PWD/DependLibs/ffmpeg/libavdevice/alsa.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/avdevice.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/avdevice_internal.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_common.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_common_c.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_dec.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_enc.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_capture.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/dv1394.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/fbdev_common.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/opengl_enc_shaders.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/oss.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/pulse_audio_common.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/sndio.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/timefilter.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/v4l2-common.h \
    $$PWD/DependLibs/ffmpeg/libavdevice/version.h

SOURCES += 	$$PWD/DependLibs/ffmpeg/libavdevice/alldevices.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/alsa.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/alsa_dec.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/alsa_enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/avdevice.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/bktr.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/caca.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_common.cpp \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_dec.cpp \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_dec_c.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_enc.cpp \
    $$PWD/DependLibs/ffmpeg/libavdevice/decklink_enc_c.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_common.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_crossbar.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_enummediatypes.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_enumpins.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_filter.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dshow_pin.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/dv1394.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/fbdev_common.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/fbdev_dec.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/fbdev_enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/file_open.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/gdigrab.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/iec61883.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/jack.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/lavfi.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/libcdio.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/libdc1394.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/openal-dec.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/opengl_enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/oss.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/oss_dec.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/oss_enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/pulse_audio_common.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/pulse_audio_dec.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/pulse_audio_enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/sndio.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/sndio_dec.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/sndio_enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/timefilter.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/utils.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/v4l2-common.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/v4l2.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/v4l2enc.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/vfwcap.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/x11grab.c \
    $$PWD/DependLibs/ffmpeg/libavdevice/xcbgrab.c \
#	$$PWD/DependLibs/ffmpeg/libavdevice/xv.c

