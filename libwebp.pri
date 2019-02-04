#NOTE $NDK_MODULE_PATH must be set to build android or will not find cpu-features.h
android{
INCLUDEPATH += $NDK_MODULE_PATH
INCLUDEPATH += $NDK_MODULE_PATH
}

HEADERS += 	$$PWD/GoTvCompilerConfig.h \
    $$PWD/GoTvCpuArchDefines.h \
    $$PWD/GoTvDependLibrariesConfig.h \
    $$PWD/GoTvTargetOsConfig.h \
    $$PWD/DependLibs/libwebp/config_libwebp.h \
    $$PWD/DependLibs/libwebp/src/dec/alphai_dec.h \
    $$PWD/DependLibs/libwebp/src/dec/common_dec.h \
    $$PWD/DependLibs/libwebp/src/dec/vp8_dec.h \
    $$PWD/DependLibs/libwebp/src/dec/vp8i_dec.h \
    $$PWD/DependLibs/libwebp/src/dec/vp8li_dec.h \
    $$PWD/DependLibs/libwebp/src/dec/webpi_dec.h \
    $$PWD/DependLibs/libwebp/src/dsp/common_sse2.h \
    $$PWD/DependLibs/libwebp/src/dsp/dsp.h \
    $$PWD/DependLibs/libwebp/src/dsp/lossless.h \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_common.h \
    $$PWD/DependLibs/libwebp/src/dsp/mips_macro.h \
    $$PWD/DependLibs/libwebp/src/dsp/msa_macro.h \
    $$PWD/DependLibs/libwebp/src/dsp/neon.h \
    $$PWD/DependLibs/libwebp/src/dsp/yuv.h \
    $$PWD/DependLibs/libwebp/src/enc/backward_references_enc.h \
    $$PWD/DependLibs/libwebp/src/enc/cost_enc.h \
    $$PWD/DependLibs/libwebp/src/enc/delta_palettization_enc.h \
    $$PWD/DependLibs/libwebp/src/enc/histogram_enc.h \
    $$PWD/DependLibs/libwebp/src/enc/vp8i_enc.h \
    $$PWD/DependLibs/libwebp/src/enc/vp8li_enc.h \
    $$PWD/DependLibs/libwebp/src/mux/animi.h \
    $$PWD/DependLibs/libwebp/src/mux/muxi.h \
    $$PWD/DependLibs/libwebp/src/utils/bit_reader_inl_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/bit_reader_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/bit_writer_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/color_cache_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/endian_inl_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/filters_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/huffman_encode_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/huffman_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/quant_levels_dec_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/quant_levels_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/random_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/rescaler_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/thread_utils.h \
    $$PWD/DependLibs/libwebp/src/utils/utils.h \
    $$PWD/DependLibs/libwebp/src/webp/decode.h \
    $$PWD/DependLibs/libwebp/src/webp/demux.h \
    $$PWD/DependLibs/libwebp/src/webp/encode.h \
    $$PWD/DependLibs/libwebp/src/webp/format_constants.h \
    $$PWD/DependLibs/libwebp/src/webp/mux.h \
    $$PWD/DependLibs/libwebp/src/webp/mux_types.h \
    $$PWD/DependLibs/libwebp/src/webp/types.h

SOURCES += 	$$PWD/DependLibs/libwebp/src/dec/alpha_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/buffer_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/frame_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/idec_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/io_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/quant_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/tree_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/vp8_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/vp8l_dec.c \
    $$PWD/DependLibs/libwebp/src/dec/webp_dec.c \
    $$PWD/DependLibs/libwebp/src/demux/anim_decode.c \
    $$PWD/DependLibs/libwebp/src/demux/demux.c \
    $$PWD/DependLibs/libwebp/src/dsp/alpha_processing.c \
    $$PWD/DependLibs/libwebp/src/dsp/alpha_processing_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/alpha_processing_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/alpha_processing_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/alpha_processing_sse41.c \
    $$PWD/DependLibs/libwebp/src/dsp/argb.c \
    $$PWD/DependLibs/libwebp/src/dsp/argb_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/argb_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/cost.c \
    $$PWD/DependLibs/libwebp/src/dsp/cost_mips32.c \
    $$PWD/DependLibs/libwebp/src/dsp/cost_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/cost_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/cpu.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_clip_tables.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_mips32.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/dec_sse41.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_avx2.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_mips32.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/enc_sse41.c \
    $$PWD/DependLibs/libwebp/src/dsp/filters.c \
    $$PWD/DependLibs/libwebp/src/dsp/filters_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/filters_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/filters_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/filters_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc_mips32.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_enc_sse41.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/lossless_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/rescaler.c \
    $$PWD/DependLibs/libwebp/src/dsp/rescaler_mips32.c \
    $$PWD/DependLibs/libwebp/src/dsp/rescaler_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/rescaler_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/rescaler_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/rescaler_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/ssim.c \
    $$PWD/DependLibs/libwebp/src/dsp/ssim_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/upsampling.c \
    $$PWD/DependLibs/libwebp/src/dsp/upsampling_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/upsampling_msa.c \
    $$PWD/DependLibs/libwebp/src/dsp/upsampling_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/upsampling_sse2.c \
    $$PWD/DependLibs/libwebp/src/dsp/yuv.c \
    $$PWD/DependLibs/libwebp/src/dsp/yuv_mips32.c \
    $$PWD/DependLibs/libwebp/src/dsp/yuv_mips_dsp_r2.c \
    $$PWD/DependLibs/libwebp/src/dsp/yuv_neon.c \
    $$PWD/DependLibs/libwebp/src/dsp/yuv_sse2.c \
    $$PWD/DependLibs/libwebp/src/enc/alpha_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/analysis_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/backward_references_cost_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/backward_references_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/config_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/cost_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/delta_palettization_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/filter_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/frame_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/histogram_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/iterator_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/near_lossless_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/picture_csp_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/picture_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/picture_psnr_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/picture_rescale_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/picture_tools_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/predictor_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/quant_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/syntax_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/token_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/tree_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/vp8l_enc.c \
    $$PWD/DependLibs/libwebp/src/enc/webp_enc.c \
    $$PWD/DependLibs/libwebp/src/mux/anim_encode.c \
    $$PWD/DependLibs/libwebp/src/mux/muxedit.c \
    $$PWD/DependLibs/libwebp/src/mux/muxinternal.c \
    $$PWD/DependLibs/libwebp/src/mux/muxread.c \
    $$PWD/DependLibs/libwebp/src/utils/bit_reader_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/bit_writer_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/color_cache_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/filters_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/huffman_encode_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/huffman_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/quant_levels_dec_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/quant_levels_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/random_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/rescaler_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/thread_utils.c \
    $$PWD/DependLibs/libwebp/src/utils/utils.c
