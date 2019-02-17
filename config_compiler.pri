
#even if not building lib these need defined so included headers are defined correctly
DEFINES += LIB_STATIC HAVE_CONFIG_H

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


INCLUDEPATH += $$PWD/DependLibs

win32{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2o
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2o/inc32
    INCLUDEPATH += $$PWD/sysheaders
}

android{
    DEFINES += BIONIC_IOCTL_NO_SIGNEDNESS_OVERLOAD
#    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
#    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
}

unix{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
}

macx{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
}

#QMAKE_EXTRA_COMPILERS += yasm
#NASMEXTRAFLAGS = -f elf64 -g -F dwarf
#OTHER_FILES += $$NASM_SOURCES
#nasm.output = ${QMAKE_FILE_BASE}.o
#nasm.commands = yasm $$NASMEXTRAFLAGS -o ${QMAKE_FILE_BASE}.o ${QMAKE_FILE_NAME}
#nasm.input = NASM_SOURCES



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


