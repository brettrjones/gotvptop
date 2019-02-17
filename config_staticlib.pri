
QT       -= gui
CONFIG += staticlib

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
}

CONFIG(release, debug|release){
    DESTDIR = $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
}


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

CONFIG(debug, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/debug
}

CONFIG(release, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/release
}


