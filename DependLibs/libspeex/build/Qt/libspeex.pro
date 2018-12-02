#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       -= gui

TARGET = VxSpeexLib
TEMPLATE = lib
CONFIG += staticlib

DEFINES += FIXED_POINT
DEFINES += HAVE_CONFIG_H


DEFINES += "STATICLIB"

win32 {
    CharacterSet=2
    DEFINES -= UNICODE
    DEFINES += "WIN_PLATFORM"
    DEFINES += "WIN32"
    DEFINES += "_WINDOWS"
    DEFINES += "_CRT_SECURE_NO_WARNINGS"
    debug {
        DEFINES += "DEBUG"
        DESTDIR = "../lib/debugWin32/"
        LIBS += -L"../lib/debugWin32/" -lVxUtilLib
    }
    release {
        DEFINES += "RELEASE"
        DESTDIR = "../lib/releaseWin32/"
        LIBS += -L"../lib/releaseWin32/" -lVxUtilLib
    }
}

unix:!symbian {
    maemo5 {
        target.path = ../lib/debugLinux/
    } else {
        QMAKE_CXXFLAGS += -Wno-unused-parameter
        CONFIG(declarative_debug, debug|declarative_debug) {
            message(Debug build pass)
            DESTDIR = "../lib/debugLinux/"
            DEFINES += "DEBUG"
            target.path =  ../lib/debugLinux/
        } else {
            message(Release build pass)
            DESTDIR = "../lib/releaseLinux/"
            DEFINES += "RELEASE"
            target.path =  ../lib/releaseLinux/
        }
    }
    INSTALLS += target
}

INCLUDEPATH += ./speex/include/
INCLUDEPATH += ../

SOURCES +=  ./VxSpeex.cpp \
    ./speex/libspeex/bits.c \
    ./speex/libspeex/buffer.c \
    ./speex/libspeex/cb_search.c \
    ./speex/libspeex/exc_10_16_table.c \
    ./speex/libspeex/exc_10_32_table.c \
    ./speex/libspeex/exc_20_32_table.c \
    ./speex/libspeex/exc_5_256_table.c \
    ./speex/libspeex/exc_5_64_table.c \
    ./speex/libspeex/exc_8_128_table.c \
    ./speex/libspeex/fftwrap.c \
    ./speex/libspeex/filterbank.c \
    ./speex/libspeex/filters.c \
    ./speex/libspeex/gain_table.c \
    ./speex/libspeex/gain_table_lbr.c \
    ./speex/libspeex/hexc_10_32_table.c \
    ./speex/libspeex/hexc_table.c \
    ./speex/libspeex/high_lsp_tables.c \
    ./speex/libspeex/jitter.c \
    ./speex/libspeex/kiss_fft.c \
    ./speex/libspeex/kiss_fftr.c \
    ./speex/libspeex/lpc.c \
    ./speex/libspeex/lsp.c \
    ./speex/libspeex/lsp_tables_nb.c \
    ./speex/libspeex/ltp.c \
    ./speex/libspeex/mdf.c \
    ./speex/libspeex/modes.c \
    ./speex/libspeex/modes_wb.c \
    ./speex/libspeex/nb_celp.c \
    ./speex/libspeex/preprocess.c \
    ./speex/libspeex/quant_lsp.c \
    ./speex/libspeex/resample.c \
    ./speex/libspeex/sb_celp.c \
    ./speex/libspeex/scal.c \
    ./speex/libspeex/smallft.c \
    ./speex/libspeex/speex.c \
    ./speex/libspeex/speex_callbacks.c \
    ./speex/libspeex/speex_header.c \
    ./speex/libspeex/stereo.c \
    ./speex/libspeex/vbr.c \
    ./speex/libspeex/vq.c \
    ./speex/libspeex/window.c

HEADERS += ./VxSpeex.h \
    ./VxSpeexCore.h \
    ./VxSpeexLib.h \
    ./speex/libspeex/_kiss_fft_guts.h \
    ./speex/libspeex/arch.h \
    ./speex/libspeex/cb_search.h \
    ./speex/libspeex/cb_search_arm4.h \
    ./speex/libspeex/cb_search_bfin.h \
    ./speex/libspeex/cb_search_sse.h \
    ./speex/libspeex/config.h \
    ./speex/libspeex/fftwrap.h \
    ./speex/libspeex/filterbank.h \
    ./speex/libspeex/filters.h \
    ./speex/libspeex/filters_arm4.h \
    ./speex/libspeex/filters_bfin.h \
    ./speex/libspeex/filters_sse.h \
    ./speex/libspeex/fixed_arm4.h \
    ./speex/libspeex/fixed_arm5e.h \
    ./speex/libspeex/fixed_bfin.h \
    ./speex/libspeex/fixed_debug.h \
    ./speex/libspeex/fixed_generic.h \
    ./speex/libspeex/kiss_fft.h \
    ./speex/libspeex/kiss_fftr.h \
    ./speex/libspeex/lpc.h \
    ./speex/libspeex/lpc_bfin.h \
    ./speex/libspeex/lsp.h \
    ./speex/libspeex/lsp_bfin.h \
    ./speex/libspeex/ltp.h \
    ./speex/libspeex/ltp_arm4.h \
    ./speex/libspeex/ltp_bfin.h \
    ./speex/libspeex/ltp_sse.h \
    ./speex/libspeex/math_approx.h \
    ./speex/libspeex/misc_bfin.h \
    ./speex/libspeex/modes.h \
    ./speex/libspeex/nb_celp.h \
    ./speex/libspeex/os_support.h \
    ./speex/libspeex/pseudofloat.h \
    ./speex/libspeex/quant_lsp.h \
    ./speex/libspeex/quant_lsp_bfin.h \
    ./speex/libspeex/resample_sse.h \
    ./speex/libspeex/sb_celp.h \
    ./speex/libspeex/smallft.h \
    ./speex/libspeex/stack_alloc.h \
    ./speex/libspeex/vbr.h \
    ./speex/libspeex/vorbis_psy.h \
    ./speex/libspeex/vq.h \
    ./speex/libspeex/vq_arm4.h \
    ./speex/libspeex/vq_bfin.h \
    ./speex/libspeex/vq_sse.h \
    ./speex/libspeex/VxSpeexConfig_android.h \
    ./speex/libspeex/VxSpeexConfig_w32.h \



