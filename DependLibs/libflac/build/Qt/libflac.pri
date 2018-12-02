HEADERS += 	$$PWD/../../config_libflac.h \
	$$PWD/../../include/all.h \
	$$PWD/../../include/assert.h \
	$$PWD/../../include/callback.h \
	$$PWD/../../include/export.h \
	$$PWD/../../include/format.h \
	$$PWD/../../include/metadata.h \
	$$PWD/../../include/ordinals.h \
	$$PWD/../../include/stream_decoder.h \
	$$PWD/../../include/stream_encoder.h

SOURCES += 	$$PWD/../../bitmath.c \
	$$PWD/../../bitreader.c \
	$$PWD/../../bitwriter.c \
	$$PWD/../../cpu.c \
	$$PWD/../../crc.c \
	$$PWD/../../fixed.c \
	$$PWD/../../fixed_intrin_sse2.c \
	$$PWD/../../fixed_intrin_ssse3.c \
	$$PWD/../../float.c \
	$$PWD/../../format.c \
	$$PWD/../../lpc.c \
	$$PWD/../../lpc_intrin_avx2.c \
	$$PWD/../../lpc_intrin_sse.c \
	$$PWD/../../lpc_intrin_sse2.c \
	$$PWD/../../lpc_intrin_sse41.c \
	$$PWD/../../md5.c \
	$$PWD/../../memory.c \
	$$PWD/../../metadata_iterators.c \
	$$PWD/../../metadata_object.c \
	$$PWD/../../ogg_decoder_aspect.c \
	$$PWD/../../ogg_encoder_aspect.c \
	$$PWD/../../ogg_helper.c \
	$$PWD/../../ogg_mapping.c \
	$$PWD/../../stream_decoder.c \
	$$PWD/../../stream_encoder.c \
	$$PWD/../../stream_encoder_framing.c \
	$$PWD/../../stream_encoder_intrin_avx2.c \
	$$PWD/../../stream_encoder_intrin_sse2.c \
	$$PWD/../../stream_encoder_intrin_ssse3.c \
	$$PWD/../../window.c \
	$$PWD/../../windows_unicode_filenames.c

