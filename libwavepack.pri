
DEFINES += ENABLE_DSD

HEADERS += 	$$PWD/DependLibs/libwavepack/config_libwavepack.h \
    $$PWD/DependLibs/libwavepack/src/decorr_tables.h \
    $$PWD/DependLibs/libwavepack/src/unpack3.h \
    $$PWD/DependLibs/libwavepack/src/wavpack_local.h \
    $$PWD/DependLibs/libwavepack/src/wavpack_version.h

SOURCES += 	$$PWD/DependLibs/libwavepack/src/common_utils.c \
    $$PWD/DependLibs/libwavepack/src/decorr_utils.c \
    $$PWD/DependLibs/libwavepack/src/entropy_utils.c \
    $$PWD/DependLibs/libwavepack/src/extra1.c \
    $$PWD/DependLibs/libwavepack/src/extra2.c \
    $$PWD/DependLibs/libwavepack/src/open_filename.c \
    $$PWD/DependLibs/libwavepack/src/open_legacy.c \
    $$PWD/DependLibs/libwavepack/src/open_raw.c \
    $$PWD/DependLibs/libwavepack/src/open_utils.c \
    $$PWD/DependLibs/libwavepack/src/pack.c \
    $$PWD/DependLibs/libwavepack/src/pack_dns.c \
    $$PWD/DependLibs/libwavepack/src/pack_dsd.c \
    $$PWD/DependLibs/libwavepack/src/pack_floats.c \
    $$PWD/DependLibs/libwavepack/src/pack_utils.c \
    $$PWD/DependLibs/libwavepack/src/read_words.c \
    $$PWD/DependLibs/libwavepack/src/tag_utils.c \
    $$PWD/DependLibs/libwavepack/src/tags.c \
    $$PWD/DependLibs/libwavepack/src/unpack.c \
    $$PWD/DependLibs/libwavepack/src/unpack3.c \
    $$PWD/DependLibs/libwavepack/src/unpack3_open.c \
    $$PWD/DependLibs/libwavepack/src/unpack3_seek.c \
    $$PWD/DependLibs/libwavepack/src/unpack_dsd.c \
    $$PWD/DependLibs/libwavepack/src/unpack_floats.c \
    $$PWD/DependLibs/libwavepack/src/unpack_seek.c \
    $$PWD/DependLibs/libwavepack/src/unpack_utils.c \
    $$PWD/DependLibs/libwavepack/src/write_words.c

