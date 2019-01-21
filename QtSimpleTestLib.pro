
QT       -= gui

TARGET_NAME = qtsimpletestlib
#TARGET = qtsimpletestlib
TEMPLATE = lib
CONFIG += staticlib


include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(library_config.pri)

TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

#INCLUDEPATH += ./
INCLUDEPATH += $$PWD/build/QtSandbox/QtSimpleTestLib

SOURCES += \
        $$PWD/build/QtSandbox/QtSimpleTestLib/qttestlib2.cpp

HEADERS += \
        $$PWD/build/QtSandbox/QtSimpleTestLib/qttestlib2.h


