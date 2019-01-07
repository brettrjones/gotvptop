
DEFINES += __XAVS__


INCLUDEPATH += $$PWD/../../common
INCLUDEPATH += $$PWD/../../encoder
INCLUDEPATH += $$PWD/../../extras
INCLUDEPATH += $$PWD/../../

HEADERS += 	$$PWD/../../common/bs.h \
	$$PWD/../../common/common.h \
	$$PWD/../../common/cpu.h \
	$$PWD/../../common/csp.h \
	$$PWD/../../common/dct.h \
	$$PWD/../../common/frame.h \
	$$PWD/../../common/macroblock.h \
	$$PWD/../../common/mc.h \
	$$PWD/../../common/osdep.h \
	$$PWD/../../common/pixel.h \
	$$PWD/../../common/predict.h \
	$$PWD/../../common/quant.h \
	$$PWD/../../common/set.h \
	$$PWD/../../common/vlc.h \
	$$PWD/../../config_libxavs.h \
	$$PWD/../../encoder/analyse.h \
	$$PWD/../../encoder/macroblock.h \
	$$PWD/../../encoder/me.h \
	$$PWD/../../encoder/ratecontrol.h \
	$$PWD/../../encoder/set.h \
	$$PWD/../../extras/getopt.h

SOURCES += 	$$PWD/../../common/common.c \
	$$PWD/../../common/cpu.c \
	$$PWD/../../common/csp.c \
	$$PWD/../../common/dct.c \
	$$PWD/../../common/frame.c \
	$$PWD/../../common/macroblock.c \
	$$PWD/../../common/mc.c \
	$$PWD/../../common/mdate.c \
	$$PWD/../../common/pixel.c \
	$$PWD/../../common/predict.c \
	$$PWD/../../common/quant.c \
	$$PWD/../../common/set.c \
	$$PWD/../../encoder/analyse.c \
	$$PWD/../../encoder/cavlc.c \
	$$PWD/../../encoder/encoder.c \
	$$PWD/../../encoder/eval.c \
	$$PWD/../../encoder/lookahead.c \
	$$PWD/../../encoder/macroblock.c \
	$$PWD/../../encoder/me.c \
	$$PWD/../../encoder/ratecontrol.c \
	$$PWD/../../encoder/set.c \
	$$PWD/../../extras/getopt.c

