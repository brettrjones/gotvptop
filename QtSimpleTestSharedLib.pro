
TEMPLATE = lib

TARGET_NAME = qtsimpletestsharedlib

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_sharedlib.pri)

INCLUDEPATH += $$PWD/build/QtSandbox/QtSimpleTestSharedLib

SOURCES += \
        $$PWD/build/QtSandbox/QtSimpleTestSharedLib/qttestsharedlib2.cpp

HEADERS += \
        $$PWD/build/QtSandbox/QtSimpleTestSharedLib/qttestsharedlib2.h


