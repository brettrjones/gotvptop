#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       -= gui

TARGET = JpgLib
TEMPLATE = lib
CONFIG += staticlib


DEFINES += "STATICLIB"

win32 {
    CharacterSet=2
    DEFINES -= UNICODE
    DEFINES += "TARGET_OS_WINDOWS"
    DEFINES += "WIN32"
    DEFINES += "_WINDOWS"
    DEFINES += "_CRT_SECURE_NO_WARNINGS"
    debug {
        DEFINES += "DEBUG"
    }
    release {
        DEFINES += "RELEASE"
    }
}

unix:!symbian {
    QMAKE_CXXFLAGS += -Wno-unused-parameter
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    debug {
        DEFINES += "DEBUG"
    }
    release {
        DEFINES += "RELEASE"
    }
    INSTALLS += target
}

INCLUDEPATH += ../

SOURCES +=  ./VxJpg.cpp \
    ./jcapimin.c \
    ./jcapistd.c \
    ./jccoefct.c \
    ./jccolor.c \
    ./jcdctmgr.c \
    ./jchuff.c \
    ./jcinit.c \
    ./jcmainct.c \
    ./jcmarker.c \
    ./jcmaster.c \
    ./jcomapi.c \
    ./jcparam.c \
    ./jcphuff.c \
    ./jcprepct.c \
    ./jcsample.c \
    ./jctrans.c \
    ./jdapimin.c \
    ./jdapistd.c \
    ./jdatadst.c \
    ./jdatasrc.c \
    ./jdcoefct.c \
    ./jdcolor.c \
    ./jddctmgr.c \
    ./jdhuff.c \
    ./jdinput.c \
    ./jdmainct.c \
    ./jdmarker.c \
    ./jdmaster.c \
    ./jdmerge.c \
    ./jdphuff.c \
    ./jdpostct.c \
    ./jdsample.c \
    ./jdtrans.c \
    ./jerror.c \
    ./jfdctflt.c \
    ./jfdctfst.c \
    ./jfdctint.c \
    ./jidctflt.c \
    ./jidctfst.c \
    ./jidctint.c \
    ./jidctred.c \
    ./jmemansi.c \
    ./jmemmgr.c \
    ./jquant1.c \
    ./jquant2.c \
    ./jutils.c \
    ./transupp.c \

HEADERS += ./jchuff.h \
    ./jconfig.h \
    ./jdct.h \
    ./jdhuff.h \
    ./jerror.h \
    ./jinclude.h \
    ./jmemsys.h \
    ./jmorecfg.h \
    ./jpegint.h \
    ./jpeglib.h \
    ./jversion.h \
    ./transupp.h \
    ./VxJpgLib.h




