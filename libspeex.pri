INCLUDEPATH += $$PWD/DependLibs/libspeex

HEADERS += 	$$PWD/GoTvCompilerConfig.h \
    $$PWD/GoTvCpuArchDefines.h \
    $$PWD/GoTvDependLibrariesConfig.h \
    $$PWD/DependLibs/libspeex/_kiss_fft_guts.h \
    $$PWD/DependLibs/libspeex/arch.h \
    $$PWD/DependLibs/libspeex/cb_search.h \
    $$PWD/DependLibs/libspeex/cb_search_arm4.h \
    $$PWD/DependLibs/libspeex/cb_search_bfin.h \
    $$PWD/DependLibs/libspeex/cb_search_sse.h \
    $$PWD/DependLibs/libspeex/config_speex.h \
    $$PWD/DependLibs/libspeex/fftwrap.h \
    $$PWD/DependLibs/libspeex/filterbank.h \
    $$PWD/DependLibs/libspeex/filters.h \
    $$PWD/DependLibs/libspeex/filters_arm4.h \
    $$PWD/DependLibs/libspeex/filters_bfin.h \
    $$PWD/DependLibs/libspeex/filters_sse.h \
    $$PWD/DependLibs/libspeex/fixed_arm4.h \
    $$PWD/DependLibs/libspeex/fixed_arm5e.h \
    $$PWD/DependLibs/libspeex/fixed_bfin.h \
    $$PWD/DependLibs/libspeex/fixed_debug.h \
    $$PWD/DependLibs/libspeex/fixed_generic.h \
    $$PWD/DependLibs/libspeex/kiss_fft.h \
    $$PWD/DependLibs/libspeex/kiss_fftr.h \
    $$PWD/DependLibs/libspeex/lpc.h \
    $$PWD/DependLibs/libspeex/lpc_bfin.h \
    $$PWD/DependLibs/libspeex/lsp.h \
    $$PWD/DependLibs/libspeex/lsp_bfin.h \
    $$PWD/DependLibs/libspeex/ltp.h \
    $$PWD/DependLibs/libspeex/ltp_arm4.h \
    $$PWD/DependLibs/libspeex/ltp_bfin.h \
    $$PWD/DependLibs/libspeex/ltp_sse.h \
    $$PWD/DependLibs/libspeex/math_approx.h \
    $$PWD/DependLibs/libspeex/misc_bfin.h \
    $$PWD/DependLibs/libspeex/modes.h \
    $$PWD/DependLibs/libspeex/nb_celp.h \
    $$PWD/DependLibs/libspeex/os_support.h \
    $$PWD/DependLibs/libspeex/pseudofloat.h \
    $$PWD/DependLibs/libspeex/quant_lsp.h \
    $$PWD/DependLibs/libspeex/quant_lsp_bfin.h \
    $$PWD/DependLibs/libspeex/resample_sse.h \
    $$PWD/DependLibs/libspeex/sb_celp.h \
    $$PWD/DependLibs/libspeex/smallft.h \
    $$PWD/DependLibs/libspeex/speex/speex.h \
    $$PWD/DependLibs/libspeex/speex/speex_bits.h \
    $$PWD/DependLibs/libspeex/speex/speex_buffer.h \
    $$PWD/DependLibs/libspeex/speex/speex_callbacks.h \
    $$PWD/DependLibs/libspeex/speex/speex_echo.h \
    $$PWD/DependLibs/libspeex/speex/speex_header.h \
    $$PWD/DependLibs/libspeex/speex/speex_jitter.h \
    $$PWD/DependLibs/libspeex/speex/speex_preprocess.h \
    $$PWD/DependLibs/libspeex/speex/speex_resampler.h \
    $$PWD/DependLibs/libspeex/speex/speex_stereo.h \
    $$PWD/DependLibs/libspeex/speex/speex_types.h \
    $$PWD/DependLibs/libspeex/stack_alloc.h \
    $$PWD/DependLibs/libspeex/vbr.h \
    $$PWD/DependLibs/libspeex/vorbis_psy.h \
    $$PWD/DependLibs/libspeex/vq.h \
    $$PWD/DependLibs/libspeex/vq_arm4.h \
    $$PWD/DependLibs/libspeex/vq_bfin.h \
    $$PWD/DependLibs/libspeex/vq_sse.h

SOURCES += 	$$PWD/DependLibs/libspeex/bits.c \
    $$PWD/DependLibs/libspeex/buffer.c \
    $$PWD/DependLibs/libspeex/cb_search.c \
    $$PWD/DependLibs/libspeex/exc_10_16_table.c \
    $$PWD/DependLibs/libspeex/exc_10_32_table.c \
    $$PWD/DependLibs/libspeex/exc_20_32_table.c \
    $$PWD/DependLibs/libspeex/exc_5_256_table.c \
    $$PWD/DependLibs/libspeex/exc_5_64_table.c \
    $$PWD/DependLibs/libspeex/exc_8_128_table.c \
    $$PWD/DependLibs/libspeex/fftwrap.c \
    $$PWD/DependLibs/libspeex/filterbank.c \
    $$PWD/DependLibs/libspeex/filters.c \
    $$PWD/DependLibs/libspeex/gain_table.c \
    $$PWD/DependLibs/libspeex/gain_table_lbr.c \
    $$PWD/DependLibs/libspeex/hexc_10_32_table.c \
    $$PWD/DependLibs/libspeex/hexc_table.c \
    $$PWD/DependLibs/libspeex/high_lsp_tables.c \
    $$PWD/DependLibs/libspeex/jitter.c \
    $$PWD/DependLibs/libspeex/kiss_fft.c \
    $$PWD/DependLibs/libspeex/kiss_fftr.c \
    $$PWD/DependLibs/libspeex/lpc.c \
    $$PWD/DependLibs/libspeex/lsp.c \
    $$PWD/DependLibs/libspeex/lsp_tables_nb.c \
    $$PWD/DependLibs/libspeex/ltp.c \
    $$PWD/DependLibs/libspeex/mdf.c \
    $$PWD/DependLibs/libspeex/modes.c \
    $$PWD/DependLibs/libspeex/modes_wb.c \
    $$PWD/DependLibs/libspeex/nb_celp.c \
    $$PWD/DependLibs/libspeex/preprocess.c \
    $$PWD/DependLibs/libspeex/quant_lsp.c \
    $$PWD/DependLibs/libspeex/resample.c \
    $$PWD/DependLibs/libspeex/sb_celp.c \
    $$PWD/DependLibs/libspeex/scal.c \
    $$PWD/DependLibs/libspeex/smallft.c \
    $$PWD/DependLibs/libspeex/speex.c \
    $$PWD/DependLibs/libspeex/speex_callbacks.c \
    $$PWD/DependLibs/libspeex/speex_header.c \
    $$PWD/DependLibs/libspeex/speex_window.c \
    $$PWD/DependLibs/libspeex/stereo.c \
    $$PWD/DependLibs/libspeex/vbr.c \
    $$PWD/DependLibs/libspeex/vq.c
