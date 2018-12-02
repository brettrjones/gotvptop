#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       += network

QT       -= gui


TARGET = CoreLib
TEMPLATE = lib
CONFIG += staticlib


DEFINES += "STATICLIB"
DEFINES += "SQLITE_OMIT_LOAD_EXTENSION"

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


SOURCES +=  ./VxTimer.cpp \
    VxXml.cpp \
    VxValuePair.cpp \
    VxTimeUtil.cpp \
    VxThread.cpp \
    VxTextStreamReader.cpp \
    VxShortcut.cpp \
    VxSettings.cpp \
    VxSemaphore.cpp \
    VxRefCount.cpp \
    VxProfile.cpp \
    VxParse.cpp \
    VxMutex.cpp \
    VxMathVec3f.cpp \
    VxLinuxOnly.cpp \
    VxGlobals.cpp \
    VxFileUtil.cpp \
    VxFileLists.cpp \
    VxFileIsTypeFunctions.cpp \
    VxFileCrc32.cpp \
    VxFileInfo.cpp \
	VxFileShredder.cpp \
	VxFileShredderDb.cpp \
	VxSha1Hash.cpp \
    VxGUID.cpp \
	VxGUIDList.cpp \
    VxDebug.cpp \
    VxCrypto.cpp \
    VxColorUtil.cpp \
    VxChopMap.cpp \
    VxChop.cpp \
    VxBuffer.cpp \
    sqlite3.c \
    rsa_gen.c \
    rsa_eay.c \
    md5.c \
    DbBase.cpp \
    Blowfish.cpp \
    AppErr.cpp \
    OsDetect.cpp \
    SHA1.cpp

HEADERS += \
    AssetDefs.h \
    VxXml.h \
    VxValuePair.h \
    VxTimer.h \
    VxTimeDefs.h \
    VxTimeUtil.h \
    VxThread.h \
    VxTextStreamReader.h \
    VxSupportedFiles.h \
    VxSingleton.h \
    VxShortcut.h \
    VxSettings.h \
    VxSemaphore.h \
    VxRefCount.h \
    VxProfile.h \
    VxParse.h \
    VxMutex.h \
    VxMathVec4f.h \
    VxMathVec3f.h \
    VxMathVec2f.h \
    VxMathDef.h \
    VxMacros.h \
    VxLinuxOnly.h \
    VxKeyDefs.h \
    VxGlobals.h \
    VxFileUtil.h \
    VxFileLists.h \
    VxFileIsTypeFunctions.h \
    VxFileCrc32.h \
    VxFileInfo.h \
    VxGUID.h \
	VxGUIDList.h \
	VxDefs.h \
    VxDebug.h \
    VxCrypto.h \
    VxColorUtil.h \
    VxChopMap.h \
    VxChop.h \
    VxBuffer.h \
    VarToString.h \
    sqlite3.h \
    rsa.h \
    md5.h \
    IsBigEndianCpu.h \
    DbBase.h \
    CompileConfig.h \
    Blowfish.h \
    AppErr.h \
    OsDetect.h \
    SHA1.h \
    VxFileShredder.h \
    VxFileShredderDb.h \
    MediaCallbackInterface.h \
    OnlineId.h




