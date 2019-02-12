
TEMPLATE = lib

TARGET = qtsimpletestsharedlib

SOURCES += \
        $$PWD/qttestsharedlib3.cpp

HEADERS += \
        $$PWD/qttestsharedlib3.h


    copydata.commands = $(COPY_DIR) $$OUT_PWD/*.so $$PWD/../androidsimpletest/res/lib/armeabi-v7a/
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
