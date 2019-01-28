



INCLUDEPATH += $$PWD/DependLibs/libx265/

HEADERS += 	$$PWD/GoTvCompilerConfig.h \
    $$PWD/GoTvCpuArchDefines.h \
    $$PWD/GoTvDependLibrariesConfig.h \
    $$PWD/GoTvTargetOsConfig.h \
    $$PWD/DependLibs/libx265/common/bitstream.h \
    $$PWD/DependLibs/libx265/common/common.h \
    $$PWD/DependLibs/libx265/common/constants.h \
    $$PWD/DependLibs/libx265/common/contexts.h \
    $$PWD/DependLibs/libx265/common/cpu.h \
    $$PWD/DependLibs/libx265/common/cudata.h \
    $$PWD/DependLibs/libx265/common/deblock.h \
    $$PWD/DependLibs/libx265/common/frame.h \
    $$PWD/DependLibs/libx265/common/framedata.h \
    $$PWD/DependLibs/libx265/common/lowres.h \
    $$PWD/DependLibs/libx265/common/md5.h \
    $$PWD/DependLibs/libx265/common/mv.h \
    $$PWD/DependLibs/libx265/common/param.h \
    $$PWD/DependLibs/libx265/common/piclist.h \
    $$PWD/DependLibs/libx265/common/picyuv.h \
    $$PWD/DependLibs/libx265/common/predict.h \
    $$PWD/DependLibs/libx265/common/primitives.h \
    $$PWD/DependLibs/libx265/common/quant.h \
    $$PWD/DependLibs/libx265/common/scalinglist.h \
    $$PWD/DependLibs/libx265/common/shortyuv.h \
    $$PWD/DependLibs/libx265/common/slice.h \
    $$PWD/DependLibs/libx265/common/threading.h \
    $$PWD/DependLibs/libx265/common/threadpool.h \
    $$PWD/DependLibs/libx265/common/wavefront.h \
    $$PWD/DependLibs/libx265/common/winxp.h \
    $$PWD/DependLibs/libx265/common/yuv.h \
    $$PWD/DependLibs/libx265/config_libx265.h \
    $$PWD/DependLibs/libx265/encoder/analysis.h \
    $$PWD/DependLibs/libx265/encoder/bitcost.h \
    $$PWD/DependLibs/libx265/encoder/dpb.h \
    $$PWD/DependLibs/libx265/encoder/encoder.h \
    $$PWD/DependLibs/libx265/encoder/entropy.h \
    $$PWD/DependLibs/libx265/encoder/frameencoder.h \
    $$PWD/DependLibs/libx265/encoder/framefilter.h \
    $$PWD/DependLibs/libx265/encoder/level.h \
    $$PWD/DependLibs/libx265/encoder/motion.h \
    $$PWD/DependLibs/libx265/encoder/nal.h \
    $$PWD/DependLibs/libx265/encoder/ratecontrol.h \
    $$PWD/DependLibs/libx265/encoder/rdcost.h \
    $$PWD/DependLibs/libx265/encoder/reference.h \
    $$PWD/DependLibs/libx265/encoder/sao.h \
    $$PWD/DependLibs/libx265/encoder/search.h \
    $$PWD/DependLibs/libx265/encoder/sei.h \
    $$PWD/DependLibs/libx265/encoder/slicetype.h \
    $$PWD/DependLibs/libx265/x265.h \
    $$PWD/DependLibs/libx265/x265cli.h

SOURCES += 	$$PWD/DependLibs/libx265/common/bitstream.cpp \
    $$PWD/DependLibs/libx265/common/common.cpp \
    $$PWD/DependLibs/libx265/common/constants.cpp \
    $$PWD/DependLibs/libx265/common/cpu.cpp \
    $$PWD/DependLibs/libx265/common/cudata.cpp \
    $$PWD/DependLibs/libx265/common/dct.cpp \
    $$PWD/DependLibs/libx265/common/deblock.cpp \
    $$PWD/DependLibs/libx265/common/frame.cpp \
    $$PWD/DependLibs/libx265/common/framedata.cpp \
    $$PWD/DependLibs/libx265/common/intrapred.cpp \
    $$PWD/DependLibs/libx265/common/ipfilter.cpp \
    $$PWD/DependLibs/libx265/common/loopfilter.cpp \
    $$PWD/DependLibs/libx265/common/lowres.cpp \
    $$PWD/DependLibs/libx265/common/md5.cpp \
    $$PWD/DependLibs/libx265/common/param.cpp \
    $$PWD/DependLibs/libx265/common/piclist.cpp \
    $$PWD/DependLibs/libx265/common/picyuv.cpp \
    $$PWD/DependLibs/libx265/common/pixel.cpp \
    $$PWD/DependLibs/libx265/common/predict.cpp \
    $$PWD/DependLibs/libx265/common/primitives.cpp \
    $$PWD/DependLibs/libx265/common/quant.cpp \
    $$PWD/DependLibs/libx265/common/scalinglist.cpp \
    $$PWD/DependLibs/libx265/common/shortyuv.cpp \
    $$PWD/DependLibs/libx265/common/slice.cpp \
    $$PWD/DependLibs/libx265/common/threading.cpp \
    $$PWD/DependLibs/libx265/common/threadpool.cpp \
    $$PWD/DependLibs/libx265/common/version.cpp \
    $$PWD/DependLibs/libx265/common/wavefront.cpp \
    $$PWD/DependLibs/libx265/common/winxp.cpp \
    $$PWD/DependLibs/libx265/common/yuv.cpp \
    $$PWD/DependLibs/libx265/encoder/analysis.cpp \
    $$PWD/DependLibs/libx265/encoder/api.cpp \
    $$PWD/DependLibs/libx265/encoder/bitcost.cpp \
    $$PWD/DependLibs/libx265/encoder/dpb.cpp \
    $$PWD/DependLibs/libx265/encoder/encoder.cpp \
    $$PWD/DependLibs/libx265/encoder/entropy.cpp \
    $$PWD/DependLibs/libx265/encoder/frameencoder.cpp \
    $$PWD/DependLibs/libx265/encoder/framefilter.cpp \
    $$PWD/DependLibs/libx265/encoder/level.cpp \
    $$PWD/DependLibs/libx265/encoder/motion.cpp \
    $$PWD/DependLibs/libx265/encoder/nal.cpp \
    $$PWD/DependLibs/libx265/encoder/ratecontrol.cpp \
    $$PWD/DependLibs/libx265/encoder/reference.cpp \
    $$PWD/DependLibs/libx265/encoder/sao.cpp \
    $$PWD/DependLibs/libx265/encoder/search.cpp \
    $$PWD/DependLibs/libx265/encoder/sei.cpp \
    $$PWD/DependLibs/libx265/encoder/slicetype.cpp \
    $$PWD/DependLibs/libx265/encoder/weightPrediction.cpp \
    $$PWD/DependLibs/libx265/x265.cpp

