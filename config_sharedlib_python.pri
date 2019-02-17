
include(config_sharedlib_defines.pri)

#do not append os name to name so can have standard python name
TARGET=$${TARGET_NAME}$${SHARED_LIB_APPEND}


#message($$[QT_INSTALL_BINS])
#message($$[QT_INSTALL_LIBS])
#message($$OUT_PWD)

#copy to local directory so can easily be linked to
CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR) $$OUT_PWD/*.so $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
}

CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$OUT_PWD/*.so $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
 }

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

CONFIG(debug, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/debug
}

CONFIG(release, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/release
}




