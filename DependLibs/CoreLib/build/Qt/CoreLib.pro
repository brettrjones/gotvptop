# Global
TEMPLATE = lib
CONFIG += qt thread silent

# C++11 support
#CONFIG += c++11

QT += network

DEFINES += QT_NO_CAST_TO_ASCII
# Fast concatenation (Qt >= 4.6)
DEFINES += QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS


INCLUDEPATH += ./../../
INCLUDEPATH += ./../../../../
INCLUDEPATH += ./../../../../build/Qt
INCLUDEPATH += ./../../../../DependLibs
INCLUDEPATH += ./../../../../GoTvCore
INCLUDEPATH += ./../../../../GoTvCore/xbmc


include(../../../../build/Qt/version.pri)
include(../../../../build/Qt/os_detect.pri)
include(../../../../build/Qt/compile_config.pri)

include(../../../../build/Qt/config_libstatic.pri)

CONFIG(debug, debug|release){
 message(Project is built in DEBUG mode.)
}

CONFIG(release, debug|release){
 message(Project is built in RELEASE mode.)
}

CONFIG(release, debug|release){
    DEFINES += _DEBUG
    linux:!android: message(Disabling UNIX debug output.)
    win32: message(Disabling WIN32 debug output.)
    android: message(Disabling ANDROID debug output.)
    DEFINES += QT_NO_DEBUG_OUTPUT
}

CONFIG(debug, debug|release){
    DEFINES += NDEBUG
    linux:!android: message(Enabling UNIX debug output.)
    win32: message(Enabling WIN32 debug output.)
    android: message(Enabling ANDROID debug output.)
}

TARGET_NAME = CoreLib


TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./../../lib/

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc
RCC_DIR = ./.qrc
UI_DIR = ./.ui

QMAKE_CFLAGS_YACC   = -Wno-unused -Wno-parentheses
QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions
QMAKE_CXXFLAGS += -Wno-unused -Wno-parentheses -Wno-attributes  -Wno-ignored-qualifiers

include(CoreLib.pri)

#SOURCES +=

DISTFILES += \
    ../../../../build/Qt/config_libstatic.pri




