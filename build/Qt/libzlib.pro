# Global
TEMPLATE = lib

TARGET_NAME = zlib


CONFIG += qt thread silent



include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_libstatic.pri)




TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./../../lib/

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc
RCC_DIR = ./.qrc
UI_DIR = ./.ui

QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers

include(../../DependLibs/libzlib/build/Qt/libzlib.pri)



