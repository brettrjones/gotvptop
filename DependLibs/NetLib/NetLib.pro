#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = NetLib
TEMPLATE = lib
CONFIG += staticlib

NetLib.depends += CoreLib
NetLib.depends += PktLib

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
    INSTALLS += target
}

INCLUDEPATH += ../

SOURCES += ./VxSktBuf.cpp \
    VxUrl.cpp \
    VxSktWaitingList.cpp \
    VxSktUtil.cpp \
    VxSktUdpBroadcast.cpp \
    VxSktUdp.cpp \
    VxSktThrottle.cpp \
    VxSktCrypto.cpp \
    VxSktConnectSimple.cpp \
    VxSktConnect.cpp \
    VxSktBaseMgr.cpp \
    VxSktBase.cpp \
    VxSktAccept.cpp \
    VxServerMgr.cpp \
    VxResolveHost.cpp \
    VxProxy.cpp \
    VxPeerMgr.cpp \
    VxParseUrlComponents.cpp \
    VxHttpValuePair.cpp \
    VxHttpRequest.cpp \
    VxHttpParse.cpp \
    VxGetRandomPort.cpp \
    VxGetExternalIps.cpp \
    VxFileXferInfo.cpp \
    VxClientMgr.cpp \
    VxBaseSktInfo.cpp \
	AnchorSetting.cpp \
    NetSettings.cpp \
    InetAddress.cpp
 
HEADERS += ./VxSktBuf.h \
    VxUrl.h \
    VxSktWaitingList.h \
    VxSktUtil.h \
    VxSktUdpBroadcast.h \
    VxSktUdp.h \
    VxSktThrottle.h \
    VxSktRandomData.h \
    VxSktInfo.h \
    VxSktDefs.h \
    VxSktCrypto.h \
    VxSktConnectSimple.h \
    VxSktConnect.h \
    VxSktBaseMgr.h \
    VxSktBase.h \
    VxSktAccept.h \
    VxServerMgr.h \
    VxResolveHost.h \
    VxProxy.h \
    VxPeerMgr.h \
    VxParseUrlComponents.h \
    VxHttpValuePair.h \
    VxHttpRequest.h \
    VxHttpParse.h \
    VxGetRandomPort.h \
    VxGetExternalIps.h \
    VxFileXferInfo.h \
    VxClientMgr.h \
    VxBaseSktInfo.h \
    VxAnyRandomPort.h \
	AnchorSetting.h \
    NetSettings.h \
    InetAddress.h
 

