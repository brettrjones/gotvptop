
INCLUDEPATH += $$PWD/../../src/lib
INCLUDEPATH += $$PWD/../../src/lib/openjp2
INCLUDEPATH += $$PWD/../../


HEADERS += 	$$PWD/../../../../GoTvCompilerConfig.h \
	$$PWD/../../../../GoTvCpuArchDefines.h \
	$$PWD/../../../../GoTvDependLibrariesConfig.h \
	$$PWD/../../../../GoTvTargetOsConfig.h \
    $$PWD/../../config_libopenjpeg.h \
    $$PWD/../../src/lib/openjp2/bio.h \
    $$PWD/../../src/lib/openjp2/cidx_manager.h \
    $$PWD/../../src/lib/openjp2/cio.h \
    $$PWD/../../src/lib/openjp2/dwt.h \
    $$PWD/../../src/lib/openjp2/event.h \
    $$PWD/../../src/lib/openjp2/function_list.h \
    $$PWD/../../src/lib/openjp2/image.h \
    $$PWD/../../src/lib/openjp2/indexbox_manager.h \
    $$PWD/../../src/lib/openjp2/invert.h \
    $$PWD/../../src/lib/openjp2/j2k.h \
    $$PWD/../../src/lib/openjp2/jp2.h \
    $$PWD/../../src/lib/openjp2/mct.h \
    $$PWD/../../src/lib/openjp2/mqc.h \
    $$PWD/../../src/lib/openjp2/mqc_inl.h \
    $$PWD/../../src/lib/openjp2/openjpeg.h \
    $$PWD/../../src/lib/openjp2/opj_clock.h \
    $$PWD/../../src/lib/openjp2/opj_codec.h \
    $$PWD/../../src/lib/openjp2/opj_common.h \
    $$PWD/../../src/lib/openjp2/opj_includes.h \
    $$PWD/../../src/lib/openjp2/opj_intmath.h \
    $$PWD/../../src/lib/openjp2/opj_inttypes.h \
    $$PWD/../../src/lib/openjp2/opj_malloc.h \
    $$PWD/../../src/lib/openjp2/opj_stdint.h \
    $$PWD/../../src/lib/openjp2/pi.h \
    $$PWD/../../src/lib/openjp2/t1.h \
    $$PWD/../../src/lib/openjp2/t1_luts.h \
    $$PWD/../../src/lib/openjp2/t2.h \
    $$PWD/../../src/lib/openjp2/tcd.h \
    $$PWD/../../src/lib/openjp2/tgt.h \
    $$PWD/../../src/lib/openjp2/thread.h \
    $$PWD/../../src/lib/openjp2/tls_keys.h \
    $$PWD/../../thirdparty/include/zconf.h \
    $$PWD/../../thirdparty/include/zlib.h \
    $$PWD/../../thirdparty/liblcms2/include/lcms2.h \
    $$PWD/../../thirdparty/liblcms2/include/lcms2_plugin.h \
    $$PWD/../../thirdparty/liblcms2/src/lcms2_internal.h

SOURCES += 	$$PWD/../../src/lib/openjp2/bench_dwt.c \
    $$PWD/../../src/lib/openjp2/bio.c \
    $$PWD/../../src/lib/openjp2/cidx_manager.c \
    $$PWD/../../src/lib/openjp2/cio.c \
    $$PWD/../../src/lib/openjp2/dwt.c \
    $$PWD/../../src/lib/openjp2/event.c \
    $$PWD/../../src/lib/openjp2/function_list.c \
    $$PWD/../../src/lib/openjp2/image.c \
    $$PWD/../../src/lib/openjp2/invert.c \
    $$PWD/../../src/lib/openjp2/j2k.c \
    $$PWD/../../src/lib/openjp2/jp2.c \
    $$PWD/../../src/lib/openjp2/mct.c \
    $$PWD/../../src/lib/openjp2/mqc.c \
    $$PWD/../../src/lib/openjp2/openjpeg.c \
    $$PWD/../../src/lib/openjp2/opj_clock.c \
    $$PWD/../../src/lib/openjp2/opj_malloc.c \
    $$PWD/../../src/lib/openjp2/phix_manager.c \
    $$PWD/../../src/lib/openjp2/pi.c \
    $$PWD/../../src/lib/openjp2/ppix_manager.c \
    $$PWD/../../src/lib/openjp2/t1.c \
    $$PWD/../../src/lib/openjp2/t1_generate_luts.c \
    $$PWD/../../src/lib/openjp2/t2.c \
    $$PWD/../../src/lib/openjp2/tcd.c \
    $$PWD/../../src/lib/openjp2/tgt.c \
    $$PWD/../../src/lib/openjp2/thix_manager.c \
    $$PWD/../../src/lib/openjp2/thread.c \
    $$PWD/../../src/lib/openjp2/tpix_manager.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsalpha.c \
    $$PWD/../../thirdparty/liblcms2/src/cmscam02.c \
    $$PWD/../../thirdparty/liblcms2/src/cmscgats.c \
    $$PWD/../../thirdparty/liblcms2/src/cmscnvrt.c \
    $$PWD/../../thirdparty/liblcms2/src/cmserr.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsgamma.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsgmt.c \
    $$PWD/../../thirdparty/liblcms2/src/cmshalf.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsintrp.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsio0.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsio1.c \
    $$PWD/../../thirdparty/liblcms2/src/cmslut.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsmd5.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsmtrx.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsnamed.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsopt.c \
    $$PWD/../../thirdparty/liblcms2/src/cmspack.c \
    $$PWD/../../thirdparty/liblcms2/src/cmspcs.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsplugin.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsps2.c \
    $$PWD/../../thirdparty/liblcms2/src/cmssamp.c \
    $$PWD/../../thirdparty/liblcms2/src/cmssm.c \
    $$PWD/../../thirdparty/liblcms2/src/cmstypes.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsvirt.c \
    $$PWD/../../thirdparty/liblcms2/src/cmswtpnt.c \
    $$PWD/../../thirdparty/liblcms2/src/cmsxform.c

