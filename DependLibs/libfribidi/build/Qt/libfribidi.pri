
INCLUDEPATH += $$PWD/../../lib
INCLUDEPATH += $$PWD/../../charset

HEADERS += 	$$PWD/../../lib/bidi-types.h \
    $$PWD/../../lib/fribidi_common.h \
	$$PWD/../../lib/debug.h \
	$$PWD/../../lib/fribidi-arabic.h \
	$$PWD/../../lib/fribidi-begindecls.h \
	$$PWD/../../lib/fribidi-bidi-types-list.h \
	$$PWD/../../lib/fribidi-bidi-types.h \
	$$PWD/../../lib/fribidi-bidi.h \
	$$PWD/../../lib/fribidi-common.h \
	$$PWD/../../lib/fribidi-config.h \
	$$PWD/../../lib/fribidi-deprecated.h \
	$$PWD/../../lib/fribidi-enddecls.h \
	$$PWD/../../lib/fribidi-flags.h \
	$$PWD/../../lib/fribidi-joining-types-list.h \
	$$PWD/../../lib/fribidi-joining-types.h \
	$$PWD/../../lib/fribidi-joining.h \
	$$PWD/../../lib/fribidi-mirroring.h \
	$$PWD/../../lib/fribidi-shape.h \
	$$PWD/../../lib/fribidi-types.h \
	$$PWD/../../lib/fribidi-unicode-version.h \
	$$PWD/../../lib/fribidi-unicode.h \
	$$PWD/../../lib/fribidi.h \
	$$PWD/../../lib/joining-types.h \
	$$PWD/../../lib/mem.h \
	$$PWD/../../lib/run.h \
    $$PWD/../../charset/fribidi-char-sets.h \
    $$PWD/../../charset/fribidi-char-sets-cap-rtl.h \
    $$PWD/../../charset/fribidi-char-sets-cp1255.h \
    $$PWD/../../charset/fribidi-char-sets-cp1256.h \
    $$PWD/../../charset/fribidi-char-sets-iso8859-6.h \
    $$PWD/../../charset/fribidi-char-sets-iso8859-8.h \
    $$PWD/../../charset/fribidi-char-sets-list.h \
    $$PWD/../../charset/fribidi-char-sets-utf8.h

SOURCES += 	$$PWD/../../lib/fribidi-arabic.c \
	$$PWD/../../lib/fribidi-bidi-types.c \
	$$PWD/../../lib/fribidi-bidi.c \
	$$PWD/../../lib/fribidi-deprecated.c \
	$$PWD/../../lib/fribidi-joining-types.c \
	$$PWD/../../lib/fribidi-joining.c \
	$$PWD/../../lib/fribidi-mem.c \
	$$PWD/../../lib/fribidi-mirroring.c \
	$$PWD/../../lib/fribidi-run.c \
	$$PWD/../../lib/fribidi-shape.c \
	$$PWD/../../lib/fribidi.c \
    $$PWD/../../charset/fribidi-char-sets.c \
    $$PWD/../../charset/fribidi-char-sets-cap-rtl.c \
    $$PWD/../../charset/fribidi-char-sets-cp1255.c \
    $$PWD/../../charset/fribidi-char-sets-cp1256.c \
    $$PWD/../../charset/fribidi-char-sets-iso8859-6.c \
    $$PWD/../../charset/fribidi-char-sets-iso8859-8.c \
    $$PWD/../../charset/fribidi-char-sets-utf8.c

