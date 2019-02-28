
INCLUDEPATH += $$PWD/DependLibs/bzlib

HEADERS += 	$$PWD/DependLibs/bzlib/bzlib.h \
        $$PWD/DependLibs/bzlib/bzlib_private.h

SOURCES += 	\
    $$PWD/DependLibs/bzlib/blocksort_bz2.c \
    $$PWD/DependLibs/bzlib/bzlib_bz2.c \
    $$PWD/DependLibs/bzlib/compress_bz2.c \
    $$PWD/DependLibs/bzlib/crctable_bz2.c \
    $$PWD/DependLibs/bzlib/decompress_bz2.c \
    $$PWD/DependLibs/bzlib/huffman_bz2.c \
    $$PWD/DependLibs/bzlib/randtable_bz2.c

