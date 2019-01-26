

INCLUDEPATH += $$PWD/DependLibs/ffmpeg/libavresample
INCLUDEPATH += $$PWD/DependLibs/ffmpeg
INCLUDEPATH += $$PWD/DependLibs/libcurl/include
INCLUDEPATH += $$PWD/DependLibs/libcurl/lib


HEADERS += 	$$PWD/DependLibs/ffmpeg/libavresample/audio_convert.h \
    $$PWD/DependLibs/ffmpeg/libavresample/audio_data.h \
    $$PWD/DependLibs/ffmpeg/libavresample/audio_mix.h \
    $$PWD/DependLibs/ffmpeg/libavresample/avresample.h \
    $$PWD/DependLibs/ffmpeg/libavresample/avresample_internal.h \
    $$PWD/DependLibs/ffmpeg/libavresample/dither.h \
    $$PWD/DependLibs/ffmpeg/libavresample/resample.h \
    $$PWD/DependLibs/ffmpeg/libavresample/version.h

SOURCES += 	$$PWD/DependLibs/ffmpeg/libavresample/audio_convert.c \
    $$PWD/DependLibs/ffmpeg/libavresample/audio_data.c \
    $$PWD/DependLibs/ffmpeg/libavresample/audio_mix.c \
    $$PWD/DependLibs/ffmpeg/libavresample/audio_mix_matrix.c \
    $$PWD/DependLibs/ffmpeg/libavresample/dither.c \
    $$PWD/DependLibs/ffmpeg/libavresample/options.c \
    $$PWD/DependLibs/ffmpeg/libavresample/resample.c \
    $$PWD/DependLibs/ffmpeg/libavresample/resample_template.c \
    $$PWD/DependLibs/ffmpeg/libavresample/utils.c

