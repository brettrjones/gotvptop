HEADERS += 	$$PWD/../../rgb2rgb.h \
	$$PWD/../../swscale.h \
	$$PWD/../../swscale_internal.h \
	$$PWD/../../version.h

SOURCES += 	$$PWD/../../alphablend.c \
	$$PWD/../../bayer_template.c \
	$$PWD/../../gamma.c \
	$$PWD/../../hscale.c \
	$$PWD/../../hscale_fast_bilinear.c \
	$$PWD/../../input.c \
	$$PWD/../../log2_tab.c \
	$$PWD/../../options.c \
	$$PWD/../../output.c \
	$$PWD/../../rgb2rgb.c \
	$$PWD/../../rgb2rgb_template.c \
	$$PWD/../../slice.c \
	$$PWD/../../swscale.c \
	$$PWD/../../swscale_unscaled.c \
	$$PWD/../../utils.c \
	$$PWD/../../vscale.c \
	$$PWD/../../yuv2rgb.c

DISTFILES += \
    $$PWD/../../x86/input.asm \
    $$PWD/../../x86/input_x86.asm \
    $$PWD/../../x86/output.asm \
    $$PWD/../../x86/output_x86.asm \
    $$PWD/../../x86/scale.asm \
    $$PWD/../../x86/scale_x86.asm \
    $$PWD/../../x86/Makefile

