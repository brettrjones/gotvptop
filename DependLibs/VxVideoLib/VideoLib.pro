#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = VideoLib
TEMPLATE = lib
CONFIG += staticlib

VxNetLib.depends += CoreLib

win32 {
    CharacterSet=2
    DEFINES -= UNICODE
    DEFINES += "WIN_PLATFORM"
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

SOURCES += ./VxRescaleRgb.cpp \
    VxVideoConvert.cpp \
    VxVidCapImp.cpp \
    VxVidCap.cpp \
    GdvBufferUtil.cpp

 
HEADERS += ./VxRescaleRgb.h \
    VxVideoLib.h \
    VxVideoConvert.h \
    VxVidCapImp.h \
    VxVidCap.h \
    IVxVidCap.h \
    GdvBufferUtil.h

 


