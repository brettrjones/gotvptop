DEFINES += _BIND_TO_CURRENT_CRT_VERSION LIBTHEORA_EXPORTS
# OC_X86_ASM

INCLUDEPATH += $$PWD/DependLibs/libtheora/
INCLUDEPATH += $$PWD/DependLibs/libtheora/include
INCLUDEPATH += $$PWD/DependLibs/libtheora/lib
INCLUDEPATH += $$PWD/DependLibs/libogg/include

HEADERS += 	$$PWD/DependLibs/libtheora/include/theora/codec.h \
    $$PWD/DependLibs/libtheora/include/theora/theora.h \
    $$PWD/DependLibs/libtheora/include/theora/theoradec.h \
    $$PWD/DependLibs/libtheora/lib/apiwrapper.h \
    $$PWD/DependLibs/libtheora/lib/bitpack.h \
    $$PWD/DependLibs/libtheora/lib/cpu.h \
    $$PWD/DependLibs/libtheora/lib/dct.h \
    $$PWD/DependLibs/libtheora/lib/decint.h \
    $$PWD/DependLibs/libtheora/lib/dequant.h \
    $$PWD/DependLibs/libtheora/lib/encint.h \
    $$PWD/DependLibs/libtheora/lib/enquant.h \
    $$PWD/DependLibs/libtheora/lib/huffdec.h \
    $$PWD/DependLibs/libtheora/lib/huffenc.h \
    $$PWD/DependLibs/libtheora/lib/huffman.h \
    $$PWD/DependLibs/libtheora/lib/internal.h \
    $$PWD/DependLibs/libtheora/lib/mathops.h \
    $$PWD/DependLibs/libtheora/lib/modedec.h \
    $$PWD/DependLibs/libtheora/lib/ocintrin.h \
    $$PWD/DependLibs/libtheora/lib/quant.h

SOURCES += 	$$PWD/DependLibs/libtheora/lib/analyze.c \
    $$PWD/DependLibs/libtheora/lib/apiwrapper.c \
    $$PWD/DependLibs/libtheora/lib/bitpack.c \
    $$PWD/DependLibs/libtheora/lib/cpu.c \
    $$PWD/DependLibs/libtheora/lib/decapiwrapper.c \
    $$PWD/DependLibs/libtheora/lib/decinfo.c \
    $$PWD/DependLibs/libtheora/lib/decode.c \
    $$PWD/DependLibs/libtheora/lib/dequant.c \
    $$PWD/DependLibs/libtheora/lib/encapiwrapper.c \
    $$PWD/DependLibs/libtheora/lib/encfrag.c \
    $$PWD/DependLibs/libtheora/lib/encinfo.c \
    $$PWD/DependLibs/libtheora/lib/encode.c \
    $$PWD/DependLibs/libtheora/lib/encoder_disabled.c \
    $$PWD/DependLibs/libtheora/lib/enquant.c \
    $$PWD/DependLibs/libtheora/lib/fdct.c \
    $$PWD/DependLibs/libtheora/lib/fragment.c \
    $$PWD/DependLibs/libtheora/lib/huffdec.c \
    $$PWD/DependLibs/libtheora/lib/huffenc.c \
    $$PWD/DependLibs/libtheora/lib/idct.c \
    $$PWD/DependLibs/libtheora/lib/info.c \
    $$PWD/DependLibs/libtheora/lib/internal.c \
    $$PWD/DependLibs/libtheora/lib/mathops.c \
    $$PWD/DependLibs/libtheora/lib/mcenc.c \
    $$PWD/DependLibs/libtheora/lib/quant.c \
    $$PWD/DependLibs/libtheora/lib/rate.c \
    $$PWD/DependLibs/libtheora/lib/state.c \
    $$PWD/DependLibs/libtheora/lib/tokenize.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxencfrag.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxfdct.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxfrag.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxidct.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxstate.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/x86enc.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/x86state.c

