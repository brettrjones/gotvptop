
TEMPLATE = lib
CONFIG += staticlib

TARGET=qtsimpleteststaticlib

SOURCES += \
        $$PWD/qtteststaticlib3.cpp

HEADERS += \
        $$PWD/qtteststaticlib3.h


android:{
    copydata.commands = $(COPY_DIR) $$OUT_PWD/*.a $$PWD/../build-staticlibs/armeabi-v7a/
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}


win32:{
    copydata.commands = $(COPY_DIR)  $$shell_path($$OUT_PWD/*.lib) $$shell_path($$PWD/../../build-staticlibs/Windows/x64/)
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}


