
bz2Dir = DependLibs/Python-2.7.14/externals/bzip2-1.0.6

INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/Include
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/bzip2-1.0.6

HEADERS += 	$$PWD/$${bz2Dir}/bzlib.h \
    $$PWD/$${bz2Dir}/bzlib_private.h \
    $$PWD/DependLibs/Python-2.7.14/pyconfig.h \
    $$PWD/DependLibs/Python-2.7.14/pyconfig_android.h \
    $$PWD/DependLibs/Python-2.7.14/pyconfig_linux.h \
    $$PWD/DependLibs/Python-2.7.14/pyconfig_windows.h

SOURCES += 	$$PWD/$${bz2Dir}/blocksort.c \
    $$PWD/$${bz2Dir}/bzlib.c \
    $$PWD/$${bz2Dir}/compress.c \
    $$PWD/$${bz2Dir}/crctable.c \
    $$PWD/$${bz2Dir}/decompress.c \
    $$PWD/$${bz2Dir}/huffman.c \
    $$PWD/$${bz2Dir}/randtable.c \
    $$PWD/DependLibs/Python-2.7.14/Modules/bz2module.c

