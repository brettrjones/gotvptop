INCLUDEPATH += $$PWD/DependLibs/libx264/

HEADERS += 	$$PWD/GoTvCompilerConfig.h \
    $$PWD/GoTvCpuArchDefines.h \
    $$PWD/GoTvDependLibrariesConfig.h \
    $$PWD/GoTvTargetOsConfig.h \
    $$PWD/DependLibs/libx264/common/bitstream.h \
    $$PWD/DependLibs/libx264/common/cabac.h \
    $$PWD/DependLibs/libx264/common/common.h \
    $$PWD/DependLibs/libx264/common/cpu.h \
    $$PWD/DependLibs/libx264/common/dct.h \
    $$PWD/DependLibs/libx264/common/frame.h \
    $$PWD/DependLibs/libx264/common/macroblock.h \
    $$PWD/DependLibs/libx264/common/mc.h \
    $$PWD/DependLibs/libx264/common/opencl.h \
    $$PWD/DependLibs/libx264/common/osdep.h \
    $$PWD/DependLibs/libx264/common/pixel.h \
    $$PWD/DependLibs/libx264/common/predict.h \
    $$PWD/DependLibs/libx264/common/quant.h \
    $$PWD/DependLibs/libx264/common/rectangle.h \
    $$PWD/DependLibs/libx264/common/set.h \
    $$PWD/DependLibs/libx264/common/threadpool.h \
    $$PWD/DependLibs/libx264/common/win32thread.h \
    $$PWD/DependLibs/libx264/config_libx264.h \
    $$PWD/DependLibs/libx264/x264.h \
    $$PWD/DependLibs/libx264/x264cli.h

SOURCES += 	$$PWD/DependLibs/libx264/common/bitstream.c \
    $$PWD/DependLibs/libx264/common/cabac.c \
    $$PWD/DependLibs/libx264/common/common.c \
    $$PWD/DependLibs/libx264/common/cpu.c \
    $$PWD/DependLibs/libx264/common/dct.c \
    $$PWD/DependLibs/libx264/common/deblock.c \
    $$PWD/DependLibs/libx264/common/frame.c \
    $$PWD/DependLibs/libx264/common/macroblock.c \
    $$PWD/DependLibs/libx264/common/mc.c \
    $$PWD/DependLibs/libx264/common/mvpred.c \
    $$PWD/DependLibs/libx264/common/opencl.c \
    $$PWD/DependLibs/libx264/common/osdep.c \
    $$PWD/DependLibs/libx264/common/pixel.c \
    $$PWD/DependLibs/libx264/common/predict.c \
    $$PWD/DependLibs/libx264/common/quant.c \
    $$PWD/DependLibs/libx264/common/rectangle.c \
    $$PWD/DependLibs/libx264/common/set.c \
    $$PWD/DependLibs/libx264/common/threadpool.c \
    $$PWD/DependLibs/libx264/common/vlc.c \
    $$PWD/DependLibs/libx264/common/win32thread.c \
    $$PWD/DependLibs/libx264/x264.c

