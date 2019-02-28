
INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../include
INCLUDEPATH += $$PWD/../../../libogg/include

HEADERS += 	$$PWD/../../config_libvorbis.h \
	$$PWD/../../include/vorbis/codec.h \
    $$PWD/../../include/vorbis/vorbisenc_vorbis.h \
	$$PWD/../../include/vorbis/vorbisfile.h \
	$$PWD/../../lib/backends.h \
	$$PWD/../../lib/bitrate.h \
	$$PWD/../../lib/books/coupled/res_books_stereo.h \
	$$PWD/../../lib/books/floor/floor_books.h \
	$$PWD/../../lib/books/uncoupled/res_books_uncoupled.h \
	$$PWD/../../lib/codebook.h \
	$$PWD/../../lib/codec_internal.h \
	$$PWD/../../lib/envelope.h \
	$$PWD/../../lib/highlevel.h \
	$$PWD/../../lib/lookup.h \
	$$PWD/../../lib/lookup_data.h \
	$$PWD/../../lib/lpc.h \
	$$PWD/../../lib/lsp.h \
	$$PWD/../../lib/masking.h \
	$$PWD/../../lib/mdct.h \
	$$PWD/../../lib/misc.h \
	$$PWD/../../lib/modes/floor_all.h \
	$$PWD/../../lib/modes/psych_11.h \
	$$PWD/../../lib/modes/psych_16.h \
	$$PWD/../../lib/modes/psych_44.h \
	$$PWD/../../lib/modes/psych_8.h \
	$$PWD/../../lib/modes/residue_16.h \
	$$PWD/../../lib/modes/residue_44.h \
	$$PWD/../../lib/modes/residue_44u.h \
	$$PWD/../../lib/modes/residue_8.h \
	$$PWD/../../lib/modes/setup_11.h \
	$$PWD/../../lib/modes/setup_16.h \
	$$PWD/../../lib/modes/setup_22.h \
	$$PWD/../../lib/modes/setup_32.h \
	$$PWD/../../lib/modes/setup_44.h \
	$$PWD/../../lib/modes/setup_44u.h \
	$$PWD/../../lib/modes/setup_8.h \
	$$PWD/../../lib/modes/setup_X.h \
	$$PWD/../../lib/os.h \
	$$PWD/../../lib/psy.h \
	$$PWD/../../lib/registry.h \
	$$PWD/../../lib/scales.h \
	$$PWD/../../lib/smallft.h \
	$$PWD/../../lib/window.h

SOURCES += 	$$PWD/../../lib/analysis.c \
	$$PWD/../../lib/bitrate.c \
	$$PWD/../../lib/block.c \
	$$PWD/../../lib/codebook.c \
	$$PWD/../../lib/envelope.c \
	$$PWD/../../lib/floor0.c \
	$$PWD/../../lib/floor1.c \
	$$PWD/../../lib/info.c \
	$$PWD/../../lib/lookup.c \
	$$PWD/../../lib/lpc.c \
	$$PWD/../../lib/lsp.c \
	$$PWD/../../lib/mapping0.c \
	$$PWD/../../lib/mdct.c \
	$$PWD/../../lib/psy.c \
	$$PWD/../../lib/registry.c \
	$$PWD/../../lib/res0.c \
	$$PWD/../../lib/sharedbook.c \
	$$PWD/../../lib/smallft.c \
	$$PWD/../../lib/synthesis.c \
	$$PWD/../../lib/vorbisenc.c \
	$$PWD/../../lib/window.c

