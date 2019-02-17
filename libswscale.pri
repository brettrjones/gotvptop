
INCLUDEPATH += $$PWD/DependLibs/ffmpeg

HEADERS += 	$$PWD/DependLibs/ffmpeg/libswscale/rgb2rgb.h \
    $$PWD/DependLibs/ffmpeg/libswscale/swscale.h \
    $$PWD/DependLibs/ffmpeg/libswscale/swscale_internal.h \
    $$PWD/DependLibs/ffmpeg/libswscale/version.h

SOURCES += 	$$PWD/DependLibs/ffmpeg/libswscale/alphablend.c \
    $$PWD/DependLibs/ffmpeg/libswscale/bayer_template.c \
    $$PWD/DependLibs/ffmpeg/libswscale/gamma.c \
    $$PWD/DependLibs/ffmpeg/libswscale/hscale.c \
    $$PWD/DependLibs/ffmpeg/libswscale/hscale_fast_bilinear.c \
    $$PWD/DependLibs/ffmpeg/libswscale/input.c \
    $$PWD/DependLibs/ffmpeg/libswscale/log2_tab.c \
    $$PWD/DependLibs/ffmpeg/libswscale/options.c \
    $$PWD/DependLibs/ffmpeg/libswscale/output.c \
    $$PWD/DependLibs/ffmpeg/libswscale/rgb2rgb.c \
    $$PWD/DependLibs/ffmpeg/libswscale/rgb2rgb_template.c \
    $$PWD/DependLibs/ffmpeg/libswscale/slice.c \
    $$PWD/DependLibs/ffmpeg/libswscale/swscale.c \
    $$PWD/DependLibs/ffmpeg/libswscale/swscale_unscaled.c \
    $$PWD/DependLibs/ffmpeg/libswscale/vscale.c \
    $$PWD/DependLibs/ffmpeg/libswscale/yuv2rgb.c \
    $$PWD/DependLibs/ffmpeg/libswscale/utils_swscale.c

DISTFILES += \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/input.asm \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/input_x86.asm \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/output.asm \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/output_x86.asm \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/scale.asm \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/scale_x86.asm \
    $$PWD/DependLibs/ffmpeg/libswscale/x86/Makefile

