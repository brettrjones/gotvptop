# Global
TEMPLATE = lib

TARGET_NAME = kodi

include(config_version.pri)
include(config_os_detect.pri)
include(config_compiler.pri)

QT       -= gui
CONFIG += staticlib

android:{
    QT += androidextras
}

DESTDIR = $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}

DEFINES += LIB_STATIC _LIB


TARGET_LIB_APPEND = .lib

CONFIG(debug, debug|release) {
win32 {
    TARGET_LIB_APPEND =  D.lib
}

unix: {
    TARGET_LIB_APPEND =  D
}

}

CONFIG(release, debug|release) {
win32 {
    TARGET_LIB_APPEND =  .lib
}

unix: {
    TARGET_LIB_APPEND =
}

}

TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}
#kodi fails because command line limit in windoz is 32,768.. so
#short obj path so does not overflow windows command line limit "make (e=87): The parameter is incorrect"
CONFIG(debug, debug|release){
    OBJECTS_DIR=.kd
}

CONFIG(release, debug|release){
    OBJECTS_DIR=.kr
}

include(libkodi.pri)
