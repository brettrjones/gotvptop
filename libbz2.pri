
INCLUDEPATH += $$PWD/DependLibs/bzlib

HEADERS += 	$$PWD/DependLibs/bzlib/bzlib.h \
        $$PWD/DependLibs/bzlib/bzlib_private.h

SOURCES += 	$$PWD/DependLibs/bzlib/blocksort.c \
        $$PWD/DependLibs/bzlib/bzlib.c \
        $$PWD/DependLibs/bzlib/compress.c \
        $$PWD/DependLibs/bzlib/crctable.c \
        $$PWD/DependLibs/bzlib/decompress.c \
        $$PWD/DependLibs/bzlib/huffman.c \
        $$PWD/DependLibs/bzlib/randtable.c

