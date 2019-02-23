
INCLUDEPATH += $$PWD/DependLibs/libflac/
INCLUDEPATH += $$PWD/DependLibs/libflac/FLAC

HEADERS += 	$$PWD/DependLibs/libflac/config_libflac.h \
    $$PWD/DependLibs/libflac/FLAC/all.h \
    $$PWD/DependLibs/libflac/FLAC/callback.h \
    $$PWD/DependLibs/libflac/FLAC/export.h \
    $$PWD/DependLibs/libflac/FLAC/format.h \
    $$PWD/DependLibs/libflac/FLAC/metadata.h \
    $$PWD/DependLibs/libflac/FLAC/ordinals.h \
    $$PWD/DependLibs/libflac/FLAC/stream_decoder.h \
    $$PWD/DependLibs/libflac/FLAC/stream_encoder.h

SOURCES += 	$$PWD/DependLibs/libflac/bitmath.c \
    $$PWD/DependLibs/libflac/bitreader.c \
    $$PWD/DependLibs/libflac/bitwriter.c \
    $$PWD/DependLibs/libflac/cpu.c \
    $$PWD/DependLibs/libflac/crc.c \
    $$PWD/DependLibs/libflac/fixed.c \
    $$PWD/DependLibs/libflac/fixed_intrin_sse2.c \
    $$PWD/DependLibs/libflac/fixed_intrin_ssse3.c \
    $$PWD/DependLibs/libflac/float.c \
    $$PWD/DependLibs/libflac/format.c \
    $$PWD/DependLibs/libflac/lpc.c \
    $$PWD/DependLibs/libflac/lpc_intrin_avx2.c \
    $$PWD/DependLibs/libflac/lpc_intrin_sse.c \
    $$PWD/DependLibs/libflac/lpc_intrin_sse2.c \
    $$PWD/DependLibs/libflac/lpc_intrin_sse41.c \
    $$PWD/DependLibs/libflac/md5.c \
    $$PWD/DependLibs/libflac/memory.c \
    $$PWD/DependLibs/libflac/metadata_iterators.c \
    $$PWD/DependLibs/libflac/metadata_object.c \
    $$PWD/DependLibs/libflac/ogg_decoder_aspect.c \
    $$PWD/DependLibs/libflac/ogg_encoder_aspect.c \
    $$PWD/DependLibs/libflac/ogg_helper.c \
    $$PWD/DependLibs/libflac/ogg_mapping.c \
    $$PWD/DependLibs/libflac/stream_decoder.c \
    $$PWD/DependLibs/libflac/stream_encoder.c \
    $$PWD/DependLibs/libflac/stream_encoder_framing.c \
    $$PWD/DependLibs/libflac/stream_encoder_intrin_avx2.c \
    $$PWD/DependLibs/libflac/stream_encoder_intrin_sse2.c \
    $$PWD/DependLibs/libflac/stream_encoder_intrin_ssse3.c \
    $$PWD/DependLibs/libflac/window.c \
    $$PWD/DependLibs/libflac/windows_unicode_filenames.c

