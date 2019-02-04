HEADERS += 	$$PWD/GoTvCompilerConfig.h \
    $$PWD/GoTvCpuArchDefines.h \
    $$PWD/GoTvDependLibrariesConfig.h \
    $$PWD/GoTvTargetOsConfig.h \
    $$PWD/DependLibs/liblzma/api/lzma.h \
    $$PWD/DependLibs/liblzma/api/lzma/base.h \
    $$PWD/DependLibs/liblzma/api/lzma/bcj.h \
    $$PWD/DependLibs/liblzma/api/lzma/block.h \
    $$PWD/DependLibs/liblzma/api/lzma/check.h \
    $$PWD/DependLibs/liblzma/api/lzma/container.h \
    $$PWD/DependLibs/liblzma/api/lzma/delta.h \
    $$PWD/DependLibs/liblzma/api/lzma/filter.h \
    $$PWD/DependLibs/liblzma/api/lzma/hardware.h \
    $$PWD/DependLibs/liblzma/api/lzma/index.h \
    $$PWD/DependLibs/liblzma/api/lzma/index_hash.h \
    $$PWD/DependLibs/liblzma/api/lzma/lzma.h \
    $$PWD/DependLibs/liblzma/api/lzma/stream_flags.h \
    $$PWD/DependLibs/liblzma/api/lzma/version.h \
    $$PWD/DependLibs/liblzma/api/lzma/vli.h \
    $$PWD/DependLibs/liblzma/check/check.h \
    $$PWD/DependLibs/liblzma/check/crc32_table_be.h \
    $$PWD/DependLibs/liblzma/check/crc32_table_le.h \
    $$PWD/DependLibs/liblzma/check/crc64_table_be.h \
    $$PWD/DependLibs/liblzma/check/crc64_table_le.h \
    $$PWD/DependLibs/liblzma/check/crc_macros.h \
    $$PWD/DependLibs/liblzma/common/alone_decoder.h \
    $$PWD/DependLibs/liblzma/common/block_decoder.h \
    $$PWD/DependLibs/liblzma/common/block_encoder.h \
    $$PWD/DependLibs/liblzma/common/common_lzma.h \
    $$PWD/DependLibs/liblzma/common/easy_preset.h \
    $$PWD/DependLibs/liblzma/common/filter_common.h \
    $$PWD/DependLibs/liblzma/common/filter_decoder.h \
    $$PWD/DependLibs/liblzma/common/filter_encoder.h \
    $$PWD/DependLibs/liblzma/common/index.h \
    $$PWD/DependLibs/liblzma/common/index_encoder.h \
    $$PWD/DependLibs/liblzma/common/stream_decoder.h \
    $$PWD/DependLibs/liblzma/common/stream_encoder.h \
    $$PWD/DependLibs/liblzma/common/stream_flags_common.h \
    $$PWD/DependLibs/liblzma/common/sysdefs_lzma.h \
    $$PWD/DependLibs/liblzma/common/tuklib_integer.h \
    $$PWD/DependLibs/liblzma/config_liblzma.h \
    $$PWD/DependLibs/liblzma/delta/delta_common.h \
    $$PWD/DependLibs/liblzma/delta/delta_decoder.h \
    $$PWD/DependLibs/liblzma/delta/delta_encoder.h \
    $$PWD/DependLibs/liblzma/delta/delta_private.h \
    $$PWD/DependLibs/liblzma/lz/lz_decoder.h \
    $$PWD/DependLibs/liblzma/lz/lz_encoder.h \
    $$PWD/DependLibs/liblzma/lz/lz_encoder_hash.h \
    $$PWD/DependLibs/liblzma/lz/lz_encoder_hash_table.h \
    $$PWD/DependLibs/liblzma/lzma/fastpos.h \
    $$PWD/DependLibs/liblzma/lzma/lzma2_decoder.h \
    $$PWD/DependLibs/liblzma/lzma/lzma2_encoder.h \
    $$PWD/DependLibs/liblzma/lzma/lzma_common.h \
    $$PWD/DependLibs/liblzma/lzma/lzma_decoder.h \
    $$PWD/DependLibs/liblzma/lzma/lzma_encoder.h \
    $$PWD/DependLibs/liblzma/lzma/lzma_encoder_private.h \
    $$PWD/DependLibs/liblzma/rangecoder/price.h \
    $$PWD/DependLibs/liblzma/rangecoder/range_common.h \
    $$PWD/DependLibs/liblzma/rangecoder/range_decoder.h \
    $$PWD/DependLibs/liblzma/rangecoder/range_encoder.h \
    $$PWD/DependLibs/liblzma/simple/simple_coder.h \
    $$PWD/DependLibs/liblzma/simple/simple_decoder.h \
    $$PWD/DependLibs/liblzma/simple/simple_encoder.h \
    $$PWD/DependLibs/liblzma/simple/simple_private.h

SOURCES += 	$$PWD/DependLibs/liblzma/check/check.c \
    $$PWD/DependLibs/liblzma/check/crc32_fast.c \
    $$PWD/DependLibs/liblzma/check/crc32_small.c \
    $$PWD/DependLibs/liblzma/check/crc32_table.c \
    $$PWD/DependLibs/liblzma/check/crc32_tablegen.c \
    $$PWD/DependLibs/liblzma/check/crc64_fast.c \
    $$PWD/DependLibs/liblzma/check/crc64_small.c \
    $$PWD/DependLibs/liblzma/check/crc64_table.c \
    $$PWD/DependLibs/liblzma/check/crc64_tablegen.c \
    $$PWD/DependLibs/liblzma/check/sha256.c \
    $$PWD/DependLibs/liblzma/common/alone_decoder.c \
    $$PWD/DependLibs/liblzma/common/alone_encoder.c \
    $$PWD/DependLibs/liblzma/common/auto_decoder.c \
    $$PWD/DependLibs/liblzma/common/block_buffer_decoder.c \
    $$PWD/DependLibs/liblzma/common/block_buffer_encoder.c \
    $$PWD/DependLibs/liblzma/common/block_decoder.c \
    $$PWD/DependLibs/liblzma/common/block_encoder.c \
    $$PWD/DependLibs/liblzma/common/block_header_decoder.c \
    $$PWD/DependLibs/liblzma/common/block_header_encoder.c \
    $$PWD/DependLibs/liblzma/common/block_util.c \
    $$PWD/DependLibs/liblzma/common/common_lzma.c \
    $$PWD/DependLibs/liblzma/common/easy_buffer_encoder.c \
    $$PWD/DependLibs/liblzma/common/easy_decoder_memusage.c \
    $$PWD/DependLibs/liblzma/common/easy_encoder.c \
    $$PWD/DependLibs/liblzma/common/easy_encoder_memusage.c \
    $$PWD/DependLibs/liblzma/common/easy_preset.c \
    $$PWD/DependLibs/liblzma/common/filter_buffer_decoder.c \
    $$PWD/DependLibs/liblzma/common/filter_buffer_encoder.c \
    $$PWD/DependLibs/liblzma/common/filter_common.c \
    $$PWD/DependLibs/liblzma/common/filter_decoder.c \
    $$PWD/DependLibs/liblzma/common/filter_encoder.c \
    $$PWD/DependLibs/liblzma/common/filter_flags_decoder.c \
    $$PWD/DependLibs/liblzma/common/filter_flags_encoder.c \
    $$PWD/DependLibs/liblzma/common/hardware_physmem.c \
    $$PWD/DependLibs/liblzma/common/index.c \
    $$PWD/DependLibs/liblzma/common/index_decoder.c \
    $$PWD/DependLibs/liblzma/common/index_encoder.c \
    $$PWD/DependLibs/liblzma/common/index_hash.c \
    $$PWD/DependLibs/liblzma/common/stream_buffer_decoder.c \
    $$PWD/DependLibs/liblzma/common/stream_buffer_encoder.c \
    $$PWD/DependLibs/liblzma/common/stream_decoder.c \
    $$PWD/DependLibs/liblzma/common/stream_encoder.c \
    $$PWD/DependLibs/liblzma/common/stream_flags_common.c \
    $$PWD/DependLibs/liblzma/common/stream_flags_decoder.c \
    $$PWD/DependLibs/liblzma/common/stream_flags_encoder.c \
    $$PWD/DependLibs/liblzma/common/vli_decoder.c \
    $$PWD/DependLibs/liblzma/common/vli_encoder.c \
    $$PWD/DependLibs/liblzma/common/vli_size.c \
    $$PWD/DependLibs/liblzma/delta/delta_common.c \
    $$PWD/DependLibs/liblzma/delta/delta_decoder.c \
    $$PWD/DependLibs/liblzma/delta/delta_encoder.c \
    $$PWD/DependLibs/liblzma/lz/lz_decoder.c \
    $$PWD/DependLibs/liblzma/lz/lz_encoder.c \
    $$PWD/DependLibs/liblzma/lz/lz_encoder_mf.c \
    $$PWD/DependLibs/liblzma/lzma/fastpos_table.c \
    $$PWD/DependLibs/liblzma/lzma/fastpos_tablegen.c \
    $$PWD/DependLibs/liblzma/lzma/lzma2_decoder.c \
    $$PWD/DependLibs/liblzma/lzma/lzma2_encoder.c \
    $$PWD/DependLibs/liblzma/lzma/lzma_decoder.c \
    $$PWD/DependLibs/liblzma/lzma/lzma_encoder.c \
    $$PWD/DependLibs/liblzma/lzma/lzma_encoder_optimum_fast.c \
    $$PWD/DependLibs/liblzma/lzma/lzma_encoder_optimum_normal.c \
    $$PWD/DependLibs/liblzma/lzma/lzma_encoder_presets.c \
    $$PWD/DependLibs/liblzma/rangecoder/price_table.c \
    $$PWD/DependLibs/liblzma/rangecoder/price_tablegen.c \
    $$PWD/DependLibs/liblzma/simple/arm.c \
    $$PWD/DependLibs/liblzma/simple/armthumb.c \
    $$PWD/DependLibs/liblzma/simple/ia64.c \
    $$PWD/DependLibs/liblzma/simple/powerpc.c \
    $$PWD/DependLibs/liblzma/simple/simple_coder.c \
    $$PWD/DependLibs/liblzma/simple/simple_decoder.c \
    $$PWD/DependLibs/liblzma/simple/simple_encoder.c \
    $$PWD/DependLibs/liblzma/simple/sparc.c \
    $$PWD/DependLibs/liblzma/simple/x86.c
