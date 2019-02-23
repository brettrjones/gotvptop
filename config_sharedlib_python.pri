
include(config_sharedlib_defines.pri)

unix:!android:{
 QMAKE_CXXFLAGS += -fPIC
 QMAKE_CFLAGS += -fPIC

 CONFIG(debug, debug|release){
    DESTDIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
 }

 CONFIG(release, debug|release){
    DESTDIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
 }
}

#do not append os name to name so can have standard python name
TARGET=$${TARGET_NAME}$${SHARED_LIB_APPEND}


#message($$[QT_INSTALL_BINS])
#message($$[QT_INSTALL_LIBS])
#message($$OUT_PWD)
