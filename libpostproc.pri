
INCLUDEPATH += $$PWD/DependLibs/ffmpeg

HEADERS += 	$$PWD/DependLibs/ffmpeg/libpostproc/postprocess.h \
    $$PWD/DependLibs/ffmpeg/libpostproc/postprocess_internal.h \
    $$PWD/DependLibs/ffmpeg/libpostproc/version.h

SOURCES += 	$$PWD/DependLibs/ffmpeg/libpostproc/postprocess.c \
    $$PWD/DependLibs/ffmpeg/libpostproc/postprocess_altivec_template.c \
    $$PWD/DependLibs/ffmpeg/libpostproc/postprocess_template.c

