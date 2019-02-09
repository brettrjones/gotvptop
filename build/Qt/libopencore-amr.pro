# Global
TEMPLATE = lib

TARGET_NAME = opencore-amr

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_libstatic.pri)



TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./../../lib/

QMAKE_CFLAGS_YACC   = -Wno-unused -Wno-parentheses
QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions
QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers


include(../../DependLibs/libopencore-amr/build/Qt/libopencore-amr.pri)
