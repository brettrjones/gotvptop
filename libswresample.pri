
INCLUDEPATH += $$PWD/DependLibs/ffmpeg

HEADERS += 	$$PWD/DependLibs/ffmpeg/libswresample/audioconvert.h \
    $$PWD/DependLibs/ffmpeg/libswresample/resample.h \
    $$PWD/DependLibs/ffmpeg/libswresample/swresample.h \
    $$PWD/DependLibs/ffmpeg/libswresample/swresample_internal.h \
    $$PWD/DependLibs/ffmpeg/libswresample/version.h

SOURCES += 	$$PWD/DependLibs/ffmpeg/libswresample/audioconvert.c \
    $$PWD/DependLibs/ffmpeg/libswresample/soxr_resample.c \
    $$PWD/DependLibs/ffmpeg/libswresample/swresample.c \
    $$PWD/DependLibs/ffmpeg/libswresample/dither_template.c \
    $$PWD/DependLibs/ffmpeg/libswresample/log2_tab.c \
    $$PWD/DependLibs/ffmpeg/libswresample/noise_shaping_data.c \
    $$PWD/DependLibs/ffmpeg/libswresample/rematrix.c \
    $$PWD/DependLibs/ffmpeg/libswresample/rematrix_template.c \
    $$PWD/DependLibs/ffmpeg/libswresample/resample_dsp.c \
    $$PWD/DependLibs/ffmpeg/libswresample/resample_template.c \
    $$PWD/DependLibs/ffmpeg/libswresample/swresample_frame.c \
    $$PWD/DependLibs/ffmpeg/libswresample/x86/audio_convert_init.c \
    $$PWD/DependLibs/ffmpeg/libswresample/x86/rematrix_init.c \
    $$PWD/DependLibs/ffmpeg/libswresample/x86/resample_init.c \
    $$PWD/DependLibs/ffmpeg/libswresample/x86/w64xmmtest.c \
    $$PWD/DependLibs/ffmpeg/libswresample/options_swresample.c \
    $$PWD/DependLibs/ffmpeg/libswresample/resample_swresample.c \
    $$PWD/DependLibs/ffmpeg/libswresample/dither_swresample.c

