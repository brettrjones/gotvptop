
include(config_version.pri)
include(config_os_detect.pri)

DEFINES += FT_DEBUG_LEVEL_ERROR FT_DEBUG_LEVEL_TRACE FT2_BUILD_LIBRARY FT_MAKE_OPTION_SINGLE_OBJECT

DEFINES += QT_SVG_LIB QT_OPENGL_LIB QT_WIDGETS_LIB QT_GUI_LIB QT_CORE_LIB QT_MULTIMEDIA_LIB

DEFINES +=__ANDROID_API__=21

CONFIG(debug, debug|release){
    DEFINES += _DEBUG
    DEFINES += DEBUG
    linux:!android: message(Enabling UNIX debug output.)
    win32: message(Enabling WIN32 debug output.)
    android: message(Enabling ANDROID debug output.)
}

CONFIG(release, debug|release){
    DEFINES += NDEBUG
    DEFINES += RELEASE
    DEFINES += QT_NO_DEBUG_OUTPUT

    linux:!android: message(Disabling UNIX debug output.)
    win32: message(Disabling WIN32 debug output.)
    android: message(Disabling ANDROID debug output.)
}


QMAKE_CXXFLAGS += -Wno-unused-parameter
unix:QMAKE_CXXFLAGS += -std=c++11
unix:QMAKE_CXXFLAGS += -fpermissive
unix:QMAKE_CXXFLAGS += -Wno-unused-variable
unix:QMAKE_CXXFLAGS += -Wno-unused-function
unix:QMAKE_CXXFLAGS += -Wno-attributes
unix:QMAKE_CXXFLAGS += -Wno-sign-compare
unix:QMAKE_CXXFLAGS += -Wno-parentheses
unix:QMAKE_CXXFLAGS += -Wno-missing-field-initializers
unix:QMAKE_CXXFLAGS += -Wno-switch
#unix:!android:QMAKE_CXXFLAGS += -Wno-#pragma-messages

QMAKE_CFLAGS += -Wno-unused-parameter
unix:QMAKE_CFLAGS += -Wno-unused-variable
unix:QMAKE_CFLAGS += -Wno-unused-function
unix:QMAKE_CFLAGS += -Wno-attributes
unix:QMAKE_CFLAGS += -Wno-sign-compare
unix:QMAKE_CFLAGS += -Wno-parentheses
unix:QMAKE_CFLAGS += -Wno-pointer-sign
unix:QMAKE_CFLAGS += -Wno-missing-field-initializers
unix:QMAKE_CFLAGS += -Wno-switch

#QMAKE_CXXFLAGS_WARN_ON += -Wno-overload-virtual

#unix:!android:QMAKE_CFLAGS += -Wno-#pragma-messages

QMAKE_CFLAGS_WARN_OFF -= -Wunused-parameter
QMAKE_CFLAGS_WARN_ON += -Wno-unused-parameter

QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_OFF -= -Winconsistent-missing-override
QMAKE_CXXFLAGS_WARN_ON += -Wno-inconsistent-missing-override



QT       -= gui

CONFIG -= staticlib
CONFIG += shared

DEFINES -= STATIC_LIB
DEFINES += SHARED_LIB

DEFINES -= _LIB
DEFINES += Py_ENABLE_SHARED

CONFIG(debug, debug|release){
    DEPENDPATH += $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
    DEPENDPATH += $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
}

CONFIG(release, debug|release){
    DEPENDPATH += $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
    DEPENDPATH += $$PWD/build-staticlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
}

SHARED_LIB_APPEND = .so

CONFIG(debug, debug|release) {
    win32 {
        SHARED_LIB_APPEND =  _d.so
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
    OBJECTS_DIR=.objs/$${TARGET_NAME}/debug
}

CONFIG(release, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/release
}


TARGET=$${TARGET_NAME}$${SHARED_LIB_APPEND}

contains( TARGET_CPU_BITS, 64 ) {
    INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include64
}

contains( TARGET_CPU_BITS, 32 ) {
    INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include32
}


INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto/modes
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto/asn1
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto/evp




INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/Include
INCLUDEPATH += $$PWD/DependLibs/libgnu

