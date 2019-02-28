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

SOURCES += 	\
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxencfrag_theora.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxfdct_theora.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxfrag_theora.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxidct_theora.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/mmxstate_theora.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/x86enc_theora.c \
    $$PWD/DependLibs/libtheora/lib/x86_vc/x86state_theora.c \
    $$PWD/DependLibs/libtheora/lib/analyze_theora.c \
    $$PWD/DependLibs/libtheora/lib/apiwrapper_theora.c \
    $$PWD/DependLibs/libtheora/lib/bitpack_theora.c \
    $$PWD/DependLibs/libtheora/lib/cpu_theora.c \
    $$PWD/DependLibs/libtheora/lib/decapiwrapper_theora.c \
    $$PWD/DependLibs/libtheora/lib/decinfo_theora.c \
    $$PWD/DependLibs/libtheora/lib/decode_theora.c \
    $$PWD/DependLibs/libtheora/lib/dequant_theora.c \
    $$PWD/DependLibs/libtheora/lib/encapiwrapper_theora.c \
    $$PWD/DependLibs/libtheora/lib/encfrag_theora.c \
    $$PWD/DependLibs/libtheora/lib/encinfo_theora.c \
    $$PWD/DependLibs/libtheora/lib/encode_theora.c \
    $$PWD/DependLibs/libtheora/lib/encoder_disabled_theora.c \
    $$PWD/DependLibs/libtheora/lib/enquant_theora.c \
    $$PWD/DependLibs/libtheora/lib/fdct_theora.c \
    $$PWD/DependLibs/libtheora/lib/fragment_theora.c \
    $$PWD/DependLibs/libtheora/lib/huffdec_theora.c \
    $$PWD/DependLibs/libtheora/lib/huffenc_theora.c \
    $$PWD/DependLibs/libtheora/lib/idct_theora.c \
    $$PWD/DependLibs/libtheora/lib/info_theora.c \
    $$PWD/DependLibs/libtheora/lib/internal_theora.c \
    $$PWD/DependLibs/libtheora/lib/mathops_theora.c \
    $$PWD/DependLibs/libtheora/lib/mcenc_theora.c \
    $$PWD/DependLibs/libtheora/lib/quant_theora.c \
    $$PWD/DependLibs/libtheora/lib/rate_theora.c \
    $$PWD/DependLibs/libtheora/lib/state_theora.c \
    $$PWD/DependLibs/libtheora/lib/tokenize_theora.c

