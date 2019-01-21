win32{
DEFINES += _WINDOWS
}

DEFINES += HAVE_MPGLIB HAVE_CONFIG_H

INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../mpglib
INCLUDEPATH += $$PWD/../../include
INCLUDEPATH += $$PWD/../../libmp3lame

HEADERS += 	$$PWD/../../include/lame.h \
    $$PWD/../../libmp3lame/VbrTag.h \
    $$PWD/../../libmp3lame/bitstream.h \
    $$PWD/../../libmp3lame/encoder.h \
    $$PWD/../../libmp3lame/fft.h \
    $$PWD/../../libmp3lame/gain_analysis.h \
    $$PWD/../../libmp3lame/i386/nasm.h \
    $$PWD/../../libmp3lame/id3tag.h \
    $$PWD/../../libmp3lame/l3side.h \
    $$PWD/../../libmp3lame/lame-analysis.h \
    $$PWD/../../libmp3lame/lame_global_flags.h \
    $$PWD/../../libmp3lame/lameerror.h \
    $$PWD/../../libmp3lame/machine.h \
    $$PWD/../../libmp3lame/newmdct.h \
    $$PWD/../../libmp3lame/psymodel.h \
    $$PWD/../../libmp3lame/quantize.h \
    $$PWD/../../libmp3lame/quantize_pvt.h \
    $$PWD/../../libmp3lame/reservoir.h \
    $$PWD/../../libmp3lame/set_get.h \
    $$PWD/../../libmp3lame/tables.h \
    $$PWD/../../libmp3lame/util.h \
    $$PWD/../../libmp3lame/vbrquantize.h \
    $$PWD/../../libmp3lame/vector/lame_intrin.h \
    $$PWD/../../libmp3lame/version.h \
    $$PWD/../../mpglib/common.h \
    $$PWD/../../mpglib/dct64_i386.h \
    $$PWD/../../mpglib/decode_i386.h \
    $$PWD/../../mpglib/huffman.h \
    $$PWD/../../mpglib/interface.h \
    $$PWD/../../mpglib/l2tables.h \
    $$PWD/../../mpglib/layer1.h \
    $$PWD/../../mpglib/layer2.h \
    $$PWD/../../mpglib/layer3.h \
    $$PWD/../../mpglib/mpg123.h \
    $$PWD/../../mpglib/mpglib.h \
    $$PWD/../../mpglib/tabinit.h \
    $$PWD/../../configMS.h

SOURCES += 	$$PWD/../../libmp3lame/VbrTag.c \
    $$PWD/../../libmp3lame/bitstream.c \
    $$PWD/../../libmp3lame/encoder.c \
    $$PWD/../../libmp3lame/fft.c \
    $$PWD/../../libmp3lame/gain_analysis.c \
    $$PWD/../../libmp3lame/id3tag.c \
    $$PWD/../../libmp3lame/lame.c \
    $$PWD/../../libmp3lame/mpglib_interface.c \
    $$PWD/../../libmp3lame/newmdct.c \
    $$PWD/../../libmp3lame/presets.c \
    $$PWD/../../libmp3lame/psymodel.c \
    $$PWD/../../libmp3lame/quantize.c \
    $$PWD/../../libmp3lame/quantize_pvt.c \
    $$PWD/../../libmp3lame/reservoir.c \
    $$PWD/../../libmp3lame/set_get.c \
    $$PWD/../../libmp3lame/tables.c \
    $$PWD/../../libmp3lame/takehiro.c \
    $$PWD/../../libmp3lame/util.c \
    $$PWD/../../libmp3lame/vbrquantize.c \
    $$PWD/../../libmp3lame/vector/xmm_quantize_sub.c \
    $$PWD/../../libmp3lame/version.c \
    $$PWD/../../mpglib/common.c \
    $$PWD/../../mpglib/dct64_i386.c \
    $$PWD/../../mpglib/decode_i386.c \
    $$PWD/../../mpglib/interface.c \
    $$PWD/../../mpglib/layer1.c \
    $$PWD/../../mpglib/layer2.c \
    $$PWD/../../mpglib/layer3.c \
    $$PWD/../../mpglib/tabinit.c

