win32{
DEFINES += _WINDOWS
}

DEFINES += HAVE_MPGLIB HAVE_CONFIG_H

INCLUDEPATH += $$PWD/DependLibs/liblame/
INCLUDEPATH += $$PWD/DependLibs/liblame/mpglib
INCLUDEPATH += $$PWD/DependLibs/liblame/include
INCLUDEPATH += $$PWD/DependLibs/liblame/libmp3lame

HEADERS += 	$$PWD/DependLibs/liblame/include/lame.h \
    $$PWD/DependLibs/liblame/libmp3lame/VbrTag.h \
    $$PWD/DependLibs/liblame/libmp3lame/bitstream.h \
    $$PWD/DependLibs/liblame/libmp3lame/encoder.h \
    $$PWD/DependLibs/liblame/libmp3lame/fft.h \
    $$PWD/DependLibs/liblame/libmp3lame/gain_analysis.h \
    $$PWD/DependLibs/liblame/libmp3lame/i386/nasm.h \
    $$PWD/DependLibs/liblame/libmp3lame/id3tag.h \
    $$PWD/DependLibs/liblame/libmp3lame/l3side.h \
    $$PWD/DependLibs/liblame/libmp3lame/lame-analysis.h \
    $$PWD/DependLibs/liblame/libmp3lame/lame_global_flags.h \
    $$PWD/DependLibs/liblame/libmp3lame/lameerror.h \
    $$PWD/DependLibs/liblame/libmp3lame/machine.h \
    $$PWD/DependLibs/liblame/libmp3lame/newmdct.h \
    $$PWD/DependLibs/liblame/libmp3lame/psymodel.h \
    $$PWD/DependLibs/liblame/libmp3lame/quantize.h \
    $$PWD/DependLibs/liblame/libmp3lame/quantize_pvt.h \
    $$PWD/DependLibs/liblame/libmp3lame/reservoir.h \
    $$PWD/DependLibs/liblame/libmp3lame/set_get.h \
    $$PWD/DependLibs/liblame/libmp3lame/tables.h \
    $$PWD/DependLibs/liblame/libmp3lame/util.h \
    $$PWD/DependLibs/liblame/libmp3lame/vbrquantize.h \
    $$PWD/DependLibs/liblame/libmp3lame/vector/lame_intrin.h \
    $$PWD/DependLibs/liblame/libmp3lame/version.h \
    $$PWD/DependLibs/liblame/mpglib/common.h \
    $$PWD/DependLibs/liblame/mpglib/dct64_i386.h \
    $$PWD/DependLibs/liblame/mpglib/decode_i386.h \
    $$PWD/DependLibs/liblame/mpglib/huffman.h \
    $$PWD/DependLibs/liblame/mpglib/interface.h \
    $$PWD/DependLibs/liblame/mpglib/l2tables.h \
    $$PWD/DependLibs/liblame/mpglib/layer1.h \
    $$PWD/DependLibs/liblame/mpglib/layer2.h \
    $$PWD/DependLibs/liblame/mpglib/layer3.h \
    $$PWD/DependLibs/liblame/mpglib/mpg123.h \
    $$PWD/DependLibs/liblame/mpglib/mpglib.h \
    $$PWD/DependLibs/liblame/mpglib/tabinit.h \
    $$PWD/DependLibs/liblame/configMS.h

SOURCES += 	$$PWD/DependLibs/liblame/libmp3lame/VbrTag.c \
    $$PWD/DependLibs/liblame/libmp3lame/bitstream.c \
    $$PWD/DependLibs/liblame/libmp3lame/encoder.c \
    $$PWD/DependLibs/liblame/libmp3lame/fft.c \
    $$PWD/DependLibs/liblame/libmp3lame/gain_analysis.c \
    $$PWD/DependLibs/liblame/libmp3lame/id3tag.c \
    $$PWD/DependLibs/liblame/libmp3lame/lame.c \
    $$PWD/DependLibs/liblame/libmp3lame/mpglib_interface.c \
    $$PWD/DependLibs/liblame/libmp3lame/newmdct.c \
    $$PWD/DependLibs/liblame/libmp3lame/presets.c \
    $$PWD/DependLibs/liblame/libmp3lame/psymodel.c \
    $$PWD/DependLibs/liblame/libmp3lame/quantize.c \
    $$PWD/DependLibs/liblame/libmp3lame/quantize_pvt.c \
    $$PWD/DependLibs/liblame/libmp3lame/reservoir.c \
    $$PWD/DependLibs/liblame/libmp3lame/set_get.c \
    $$PWD/DependLibs/liblame/libmp3lame/tables.c \
    $$PWD/DependLibs/liblame/libmp3lame/takehiro.c \
    $$PWD/DependLibs/liblame/libmp3lame/util.c \
    $$PWD/DependLibs/liblame/libmp3lame/vbrquantize.c \
    $$PWD/DependLibs/liblame/libmp3lame/vector/xmm_quantize_sub.c \
    $$PWD/DependLibs/liblame/libmp3lame/version.c \
    $$PWD/DependLibs/liblame/mpglib/common.c \
    $$PWD/DependLibs/liblame/mpglib/dct64_i386.c \
    $$PWD/DependLibs/liblame/mpglib/decode_i386.c \
    $$PWD/DependLibs/liblame/mpglib/interface.c \
    $$PWD/DependLibs/liblame/mpglib/layer1.c \
    $$PWD/DependLibs/liblame/mpglib/layer2.c \
    $$PWD/DependLibs/liblame/mpglib/layer3.c \
    $$PWD/DependLibs/liblame/mpglib/tabinit.c

