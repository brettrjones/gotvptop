



INCLUDEPATH += $$PWD/../../

HEADERS += 	$$PWD/../../../../GoTvCompilerConfig.h \
	$$PWD/../../../../GoTvCpuArchDefines.h \
	$$PWD/../../../../GoTvDependLibrariesConfig.h \
	$$PWD/../../../../GoTvTargetOsConfig.h \
	$$PWD/../../common/bitstream.h \
	$$PWD/../../common/common.h \
	$$PWD/../../common/constants.h \
	$$PWD/../../common/contexts.h \
	$$PWD/../../common/cpu.h \
	$$PWD/../../common/cudata.h \
	$$PWD/../../common/deblock.h \
	$$PWD/../../common/frame.h \
	$$PWD/../../common/framedata.h \
	$$PWD/../../common/lowres.h \
	$$PWD/../../common/md5.h \
	$$PWD/../../common/mv.h \
	$$PWD/../../common/param.h \
	$$PWD/../../common/piclist.h \
	$$PWD/../../common/picyuv.h \
	$$PWD/../../common/predict.h \
	$$PWD/../../common/primitives.h \
	$$PWD/../../common/quant.h \
	$$PWD/../../common/scalinglist.h \
	$$PWD/../../common/shortyuv.h \
	$$PWD/../../common/slice.h \
	$$PWD/../../common/threading.h \
	$$PWD/../../common/threadpool.h \
	$$PWD/../../common/wavefront.h \
	$$PWD/../../common/winxp.h \
	$$PWD/../../common/yuv.h \
    $$PWD/../../config_libx265.h \
	$$PWD/../../encoder/analysis.h \
	$$PWD/../../encoder/bitcost.h \
	$$PWD/../../encoder/dpb.h \
	$$PWD/../../encoder/encoder.h \
	$$PWD/../../encoder/entropy.h \
	$$PWD/../../encoder/frameencoder.h \
	$$PWD/../../encoder/framefilter.h \
	$$PWD/../../encoder/level.h \
	$$PWD/../../encoder/motion.h \
	$$PWD/../../encoder/nal.h \
	$$PWD/../../encoder/ratecontrol.h \
	$$PWD/../../encoder/rdcost.h \
	$$PWD/../../encoder/reference.h \
	$$PWD/../../encoder/sao.h \
	$$PWD/../../encoder/search.h \
	$$PWD/../../encoder/sei.h \
	$$PWD/../../encoder/slicetype.h \
	$$PWD/../../x265.h \
	$$PWD/../../x265cli.h

SOURCES += 	$$PWD/../../common/bitstream.cpp \
	$$PWD/../../common/common.cpp \
	$$PWD/../../common/constants.cpp \
	$$PWD/../../common/cpu.cpp \
	$$PWD/../../common/cudata.cpp \
	$$PWD/../../common/dct.cpp \
	$$PWD/../../common/deblock.cpp \
	$$PWD/../../common/frame.cpp \
	$$PWD/../../common/framedata.cpp \
	$$PWD/../../common/intrapred.cpp \
	$$PWD/../../common/ipfilter.cpp \
	$$PWD/../../common/loopfilter.cpp \
	$$PWD/../../common/lowres.cpp \
	$$PWD/../../common/md5.cpp \
	$$PWD/../../common/param.cpp \
	$$PWD/../../common/piclist.cpp \
	$$PWD/../../common/picyuv.cpp \
	$$PWD/../../common/pixel.cpp \
	$$PWD/../../common/predict.cpp \
	$$PWD/../../common/primitives.cpp \
	$$PWD/../../common/quant.cpp \
	$$PWD/../../common/scalinglist.cpp \
	$$PWD/../../common/shortyuv.cpp \
	$$PWD/../../common/slice.cpp \
	$$PWD/../../common/threading.cpp \
	$$PWD/../../common/threadpool.cpp \
	$$PWD/../../common/version.cpp \
	$$PWD/../../common/wavefront.cpp \
	$$PWD/../../common/winxp.cpp \
	$$PWD/../../common/yuv.cpp \
	$$PWD/../../encoder/analysis.cpp \
	$$PWD/../../encoder/api.cpp \
	$$PWD/../../encoder/bitcost.cpp \
	$$PWD/../../encoder/dpb.cpp \
	$$PWD/../../encoder/encoder.cpp \
	$$PWD/../../encoder/entropy.cpp \
	$$PWD/../../encoder/frameencoder.cpp \
	$$PWD/../../encoder/framefilter.cpp \
	$$PWD/../../encoder/level.cpp \
	$$PWD/../../encoder/motion.cpp \
	$$PWD/../../encoder/nal.cpp \
	$$PWD/../../encoder/ratecontrol.cpp \
	$$PWD/../../encoder/reference.cpp \
	$$PWD/../../encoder/sao.cpp \
	$$PWD/../../encoder/search.cpp \
	$$PWD/../../encoder/sei.cpp \
	$$PWD/../../encoder/slicetype.cpp \
	$$PWD/../../encoder/weightPrediction.cpp \
	$$PWD/../../x265.cpp

