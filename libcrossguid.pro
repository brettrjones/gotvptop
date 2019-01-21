# Global
TEMPLATE = lib

TARGET_NAME = crossguid

CONFIG += qt thread silent

QT += network

INCLUDEPATH += $$PWD

unix:QMAKE_CFLAGS += __ANDROID_API__=21
unix:QMAKE_CXXFLAGS += __ANDROID_API__=21

#include(version.pri)
#include(os_detect.pri)
#include(compile_config.pri)

include(library_config.pri)

TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./libs


#include(libcrossguid.pri)
SOURCES += ./DependLibs/libcrossguid/guid.cpp

