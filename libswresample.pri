HEADERS += 	$$PWD/../../audioconvert.h \
	$$PWD/../../resample.h \
	$$PWD/../../swresample.h \
	$$PWD/../../swresample_internal.h \
	$$PWD/../../version.h

SOURCES += 	$$PWD/../../audioconvert.c \
	$$PWD/../../dither.c \
	$$PWD/../../dither_template.c \
	$$PWD/../../log2_tab.c \
	$$PWD/../../noise_shaping_data.c \
	$$PWD/../../options.c \
	$$PWD/../../rematrix.c \
	$$PWD/../../rematrix_template.c \
	$$PWD/../../resample.c \
	$$PWD/../../resample_dsp.c \
	$$PWD/../../resample_template.c \
	$$PWD/../../soxr_resample.c \
	$$PWD/../../swresample.c \
	$$PWD/../../swresample_frame.c \
	$$PWD/../../x86/audio_convert_init.c \
	$$PWD/../../x86/rematrix_init.c \
	$$PWD/../../x86/resample_init.c \
	$$PWD/../../x86/w64xmmtest.c

