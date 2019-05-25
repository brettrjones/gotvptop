
QT       -= gui

CONFIG -= staticlib
CONFIG += shared

DEFINES -= STATIC_LIB
DEFINES += SHARED_LIB

DEFINES -= _LIB
DEFINES += Py_ENABLE_SHARED
DEFINES += _USRDLL

CONFIG(debug, debug|release){
    DEPENDPATH += $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
    DEPENDPATH += $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
}

CONFIG(release, debug|release){
    DEPENDPATH += $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
    DEPENDPATH += $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
}

SHARED_LIB_APPEND = .dll

CONFIG(debug, debug|release) {
    win32 {
        SHARED_LIB_APPEND =  _d.dll
    }

    unix: {
        SHARED_LIB_APPEND =  _d
    }
}

CONFIG(release, debug|release) {
    win32 {
        SHARED_LIB_APPEND =  .dll
    }

    unix: {
        SHARED_LIB_APPEND =
    }
}

CONFIG(debug, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/$${TARGET_OS_NAME}/$${BUILD_TYPE}
}

CONFIG(release, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/$${TARGET_OS_NAME}/$${BUILD_TYPE}
}


TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${SHARED_LIB_APPEND}


#message($$[QT_INSTALL_BINS])
#message($$[QT_INSTALL_LIBS])
#message($$OUT_PWD)




