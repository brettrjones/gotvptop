
QT       -= gui

CONFIG -= staticlib

DEFINES -= STATIC_LIB
DEFINES -= _LIB
DEFINES += SHARED_LIB
DEFINES += Py_ENABLE_SHARED

#DESTDIR = $$PWD/build-sharedlibs

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


TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${SHARED_LIB_APPEND}
