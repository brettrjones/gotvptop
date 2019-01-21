# Global
TEMPLATE = lib

TARGET_NAME = ssl

CONFIG += qt thread silent

QT += network

DEFINES += QT_NO_CAST_TO_ASCII
# Fast concatenation (Qt >= 4.6)
DEFINES += QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS

INCLUDEPATH += ./../../
INCLUDEPATH += ./../../DependLibs

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(library_config.pri)

TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

DESTDIR = ./../../lib/

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc
RCC_DIR = ./.qrc
UI_DIR = ./.ui


android{
    include(../../DependLibs/openssl-1.0.2p/build/Qt/libssl.pri)
}

unix{
    include(../../DependLibs/openssl-1.0.2p/build/Qt/libssl.pri)
}

macx{
    include(../../DependLibs/openssl-1.0.2p/build/Qt/libssl.pri)
}
