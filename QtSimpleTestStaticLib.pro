
TEMPLATE = lib

TARGET_NAME = qtsimpleteststaticlib

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_staticlib.pri)


INCLUDEPATH += $$PWD/build/QtSandbox/QtSimpleTestLib

SOURCES += \
        $$PWD/build/QtSandbox/QtSimpleTestStaticLib/qtteststaticlib2.cpp

HEADERS += \
        $$PWD/build/QtSandbox/QtSimpleTestStaticLib/qtteststaticlib2.h


