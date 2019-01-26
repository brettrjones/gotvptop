INCLUDEPATH += $$PWD/DependLibs/libgsm/inc
INCLUDEPATH += $$PWD/DependLibs/libgsm/src
INCLUDEPATH += $$PWD/DependLibs/libgsm/


HEADERS += 	$$PWD/DependLibs/libgsm/inc/config_gsm.h \
    $$PWD/DependLibs/libgsm/inc/gsm.h \
    $$PWD/DependLibs/libgsm/inc/private.h \
    $$PWD/DependLibs/libgsm/inc/proto.h \
    $$PWD/DependLibs/libgsm/inc/toast.h \
    $$PWD/DependLibs/libgsm/inc/unproto.h

SOURCES += 	$$PWD/DependLibs/libgsm/src/add.c \
    $$PWD/DependLibs/libgsm/src/code.c \
    $$PWD/DependLibs/libgsm/src/debug.c \
    $$PWD/DependLibs/libgsm/src/decode.c \
    $$PWD/DependLibs/libgsm/src/gsm_create.c \
    $$PWD/DependLibs/libgsm/src/gsm_decode.c \
    $$PWD/DependLibs/libgsm/src/gsm_destroy.c \
    $$PWD/DependLibs/libgsm/src/gsm_encode.c \
    $$PWD/DependLibs/libgsm/src/gsm_explode.c \
    $$PWD/DependLibs/libgsm/src/gsm_implode.c \
    $$PWD/DependLibs/libgsm/src/gsm_option.c \
    $$PWD/DependLibs/libgsm/src/gsm_print.c \
    $$PWD/DependLibs/libgsm/src/long_term.c \
    $$PWD/DependLibs/libgsm/src/lpc.c \
    $$PWD/DependLibs/libgsm/src/preprocess.c \
    $$PWD/DependLibs/libgsm/src/rpe.c \
    $$PWD/DependLibs/libgsm/src/short_term.c \
    $$PWD/DependLibs/libgsm/src/table.c \
    $$PWD/DependLibs/libgsm/src/toast.c \
    $$PWD/DependLibs/libgsm/src/toast_alaw.c \
    $$PWD/DependLibs/libgsm/src/toast_audio.c \
    $$PWD/DependLibs/libgsm/src/toast_lin.c \
    $$PWD/DependLibs/libgsm/src/toast_ulaw.c

