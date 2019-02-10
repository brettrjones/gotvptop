
QT       -= gui

CONFIG -= staticlib
CONFIG += shared

DEFINES -= STATIC_LIB
DEFINES += SHARED_LIB

DEFINES -= _LIB
DEFINES += Py_ENABLE_SHARED

#DESTDIR = $$PWD/build-sharedlibs
DEPENDPATH += $$PWD/build-sharedlibs
DEPENDPATH += $$PWD/build-staticlibs

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
# OBJECTS_DIR = $$PWD/objs/$${TARGET_NAME}$${TARGET_OS_NAME}

#message($$[QT_INSTALL_BINS])
#message($$[QT_INSTALL_LIBS])
#message($$OUT_PWD)

#message("copy src");
#message($$OUT_PWD/$${TARGET_NAME}$${TARGET_OS_NAME}$${SHARED_LIB_APPEND})
#message("copy dest");
#message($$PWD/build-sharedlibs/)

#copy to local directory so can easily be linked to
copydata.commands = $(COPY_DIR) $$OUT_PWD/*.so $$PWD/build-sharedlibs/
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata





