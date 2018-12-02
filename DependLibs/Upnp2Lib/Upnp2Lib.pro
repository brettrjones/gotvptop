#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Upnp2Lib
TEMPLATE = lib
CONFIG += staticlib

Upnp2Lib.depends = CoreLib
Upnp2Lib.depends += NetLib
Upnp2Lib.depends += TinyXmlLib

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

SOURCES += ./AltXmlParser.cpp \
    UpnpTcpSkt.cpp \
    UpnpService.cpp \
    UpnpRootDevice.cpp \
    UpnpPortForward.cpp \
    UpnpParser.cpp

 
HEADERS += ./AltXmlParser.h \
    UpnpTcpSkt.h \
    UpnpStateVariable.h \
    UpnpService.h \
    UpnpRootDevice.h \
    UpnpPortForward.h \
    UpnpParser.h \
    UpnpClientInterface.h \
    UpnpAllowedValue.h \
    UpnpAction.h \

 
