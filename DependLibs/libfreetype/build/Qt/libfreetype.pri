
DEFINES += FT_DEBUG_LEVEL_ERROR FT_DEBUG_LEVEL_TRACE FT2_BUILD_LIBRARY

INCLUDEPATH += $$PWD/../../include

HEADERS += 	$$PWD/../../include/freetype/config/ftconfig.h \
	$$PWD/../../include/freetype/config/ftconfig_android.h \
	$$PWD/../../include/freetype/config/ftconfig_linux.h \
	$$PWD/../../include/freetype/config/ftconfig_windows.h \
	$$PWD/../../include/freetype/config/ftheader.h \
	$$PWD/../../include/freetype/config/ftmodule.h \
	$$PWD/../../include/freetype/config/ftoption.h \
	$$PWD/../../include/freetype/config/ftstdlib.h \
	$$PWD/../../include/ft2build.h

SOURCES += 	$$PWD/../../src/autofit/autofit.c \
	$$PWD/../../src/base/ftbase.c \
	$$PWD/../../src/base/ftbbox.c \
	$$PWD/../../src/base/ftbitmap.c \
	$$PWD/../../src/base/ftgasp.c \
	$$PWD/../../src/base/ftglyph.c \
	$$PWD/../../src/base/ftinit.c \
	$$PWD/../../src/base/ftmm.c \
	$$PWD/../../src/base/ftpfr.c \
	$$PWD/../../src/base/ftstroke.c \
	$$PWD/../../src/base/ftsynth.c \
	$$PWD/../../src/base/ftsystem.c \
	$$PWD/../../src/base/fttype1.c \
	$$PWD/../../src/base/ftwinfnt.c \
	$$PWD/../../src/bdf/bdf.c \
	$$PWD/../../src/cache/ftcache.c \
	$$PWD/../../src/cff/cff.c \
	$$PWD/../../src/cid/type1cid.c \
	$$PWD/../../src/gzip/ftgzip.c \
	$$PWD/../../src/lzw/ftlzw.c \
	$$PWD/../../src/pcf/pcf.c \
	$$PWD/../../src/pfr/pfr.c \
	$$PWD/../../src/psaux/psaux.c \
	$$PWD/../../src/pshinter/pshinter.c \
	$$PWD/../../src/psnames/psmodule.c \
	$$PWD/../../src/raster/raster.c \
	$$PWD/../../src/sfnt/sfnt.c \
	$$PWD/../../src/smooth/smooth.c \
	$$PWD/../../src/truetype/truetype.c \
	$$PWD/../../src/type1/type1.c \
	$$PWD/../../src/type42/type42.c \
	$$PWD/../../src/winfonts/winfnt.c

