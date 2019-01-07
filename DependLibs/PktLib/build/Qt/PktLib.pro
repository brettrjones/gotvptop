#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = PktLib
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
    INSTALLS += target
    debug {
        DEFINES += "DEBUG"
    }
    release {
        DEFINES += "RELEASE"
    }
}

INCLUDEPATH += ../

SOURCES +=     ./VxSearchFlags.cpp \
    VxRelayFlags.cpp \
    VxPktHdr.cpp \
    VxOnlineStatusFlags.cpp \
    VxNetIdentBase.cpp \
    VxFriendMatch.cpp \
    VxConnectInfo.cpp \
    VxConnectId.cpp \
    VxCommon.cpp \
    PktVoiceReq.cpp \
    PktVoiceReply.cpp \
    PktSysHandlerBase.cpp \
    PktsWebServer.cpp \
    PktsVideoFeed.cpp \
    PktsTodGame.cpp \
    PktsStoryBoard.cpp \
    PktsSession.cpp \
    PktsRelay.cpp \
    PktsMultisession.cpp \
    PktsPluginOffer.cpp \
    PktsFileShare.cpp \
    PktSearch.cpp \
    PktPluginHandlerBase.cpp \
    PktLogReq.cpp \
    PktLogReply.cpp \
    PktDebugHelpers.cpp \
    PktChatReq.cpp \
    PktsFileList.cpp \
    PktAnnounce.cpp \
    PktAnnList.cpp \
    PktTcpPunch.cpp \
    PktsPing.cpp \
    PktsImAlive.cpp \
    PktsAssetXfer.cpp
 

HEADERS += \     
    VxSearchFlags.h \
    VxSearchDefs.h \
    VxRelayFlags.h \
    VxPktHdr.h \
    VxOnlineStatusFlags.h \
    VxNetIdentBase.h \
    VxFriendMatch.h \
    VxConnectInfo.h \
    VxConnectId.h \
    VxCommon.h \
    PktVoiceReq.h \
    PktVoiceReply.h \
    PktTypes.h \
    PktSysHandlerBase.h \
    PktsWebServer.h \
    PktsVideoFeed.h \
    PktsTodGame.h \
    PktsStoryBoard.h \
    PktsSession.h \
    PktsRelay.h \
    PktsMultisession.h \
    PktsPluginOffer.h \
    PktsFileShare.h \
    PktSearch.h \
    PktPluginHandlerBase.h \
    PktLogReq.h \
    PktLogReply.h \
    PktDebugHelpers.h \
    PktChatReq.h \
    PktsFileList.h \
    PktAnnounce.h \
    PktAnnList.h \
    AllPkts.h \
    PktTcpPunch.h \
    PktsPing.h \
    PktsImAlive.h \
    PktsAssetXfer.h


