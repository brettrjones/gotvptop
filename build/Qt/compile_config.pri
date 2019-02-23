
#even if not building lib these need defined so included headers are defined correctly
DEFINES += LIB_STATIC HAVE_CONFIG_H

DEFINES += FT_DEBUG_LEVEL_ERROR FT_DEBUG_LEVEL_TRACE FT2_BUILD_LIBRARY FT_MAKE_OPTION_SINGLE_OBJECT


#win32{
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2o
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2o/inc32
#}

#android{
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2p
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2p/include
#}

#unix{
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2p
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2p/include
#}

#macx{
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2p
#    INCLUDEPATH += ./../../DependLibs/openssl-1.0.2p/include
#}

#QMAKE_EXTRA_COMPILERS += yasm
#NASMEXTRAFLAGS = -f elf64 -g -F dwarf
#OTHER_FILES += $$NASM_SOURCES
#nasm.output = ${QMAKE_FILE_BASE}.o
#nasm.commands = yasm $$NASMEXTRAFLAGS -o ${QMAKE_FILE_BASE}.o ${QMAKE_FILE_NAME}
#nasm.input = NASM_SOURCES



unix:QMAKE_CXXFLAGS += -std=c++11
unix:QMAKE_CXXFLAGS += -fpermissive
unix:QMAKE_CXXFLAGS += -Wno-unused-variable
unix:QMAKE_CXXFLAGS += -Wno-unused-function
unix:QMAKE_CXXFLAGS += -Wno-unused-parameter
unix:QMAKE_CXXFLAGS += -Wno-attributes
unix:QMAKE_CXXFLAGS += -Wno-sign-compare
unix:QMAKE_CXXFLAGS += -Wno-parentheses
unix:QMAKE_CXXFLAGS += -Wno-missing-field-initializers
unix:QMAKE_CXXFLAGS += -Wno-switch


unix:QMAKE_CFLAGS += -Wno-unused-variable
unix:QMAKE_CFLAGS += -Wno-unused-function
unix:QMAKE_CFLAGS += -Wno-unused-parameter
unix:QMAKE_CFLAGS += -Wno-attributes
unix:QMAKE_CFLAGS += -Wno-sign-compare
unix:QMAKE_CFLAGS += -Wno-parentheses
unix:QMAKE_CFLAGS += -Wno-pointer-sign
unix:QMAKE_CFLAGS += -Wno-missing-field-initializers
unix:QMAKE_CFLAGS += -Wno-switch


CONFIG(debug, debug|release){
 message(Project is built in DEBUG mode.)
    DEFINES += DEBUG
}

CONFIG(release, debug|release){
 message(Project is built in RELEASE mode.)
}

CONFIG(release, debug|release){
    DEFINES += NDEBUG
    DEFINES += RELEASE
    linux:!android: message(Disabling UNIX debug output.)
    win32: message(Disabling WIN32 debug output.)
    android: message(Disabling ANDROID debug output.)
    DEFINES += QT_NO_DEBUG_OUTPUT
}

CONFIG(debug, debug|release){
    DEFINES += _DEBUG
    DEFINES += DEBUG
    linux:!android: message(Enabling UNIX debug output.)
    win32: message(Enabling WIN32 debug output.)
    android: message(Enabling ANDROID debug output.)
}


