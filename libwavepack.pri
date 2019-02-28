
DEFINES += ENABLE_DSD

HEADERS += 	$$PWD/DependLibs/libwavepack/config_libwavepack.h \
    $$PWD/DependLibs/libwavepack/src/decorr_tables.h \
    $$PWD/DependLibs/libwavepack/src/unpack3.h \
    $$PWD/DependLibs/libwavepack/src/wavpack_local.h \
    $$PWD/DependLibs/libwavepack/src/wavpack_version.h

SOURCES += 	\
    $$PWD/DependLibs/libwavepack/src/pack_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/common_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/decorr_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/entropy_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/extra1_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/extra2_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/open_filename_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/open_legacy_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/open_raw_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/open_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/pack_dns_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/pack_dsd_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/pack_floats_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/pack_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/read_words_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/tag_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/tags_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack3_open_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack_dsd_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack3_seek_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack3_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack_floats_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack_seek_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack_utils_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/unpack_wavepack_wavepack.c \
    $$PWD/DependLibs/libwavepack/src/write_words_wavepack.c

