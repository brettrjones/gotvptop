
include(config_sharedlib_defines.pri)

unix:!android:{
 QMAKE_CXXFLAGS += -fPIC
 QMAKE_CFLAGS += -fPIC

  DESTDIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
 }

android:{
    QMAKE_CXXFLAGS += -fPIC
    QMAKE_CFLAGS += -fPIC
#    !contains(QMAKE_HOST.os,Windows){
        #part of workaround for QTBUG-69255 .. do not define DESTDIR because uses $$PWD_OUT as root of path
        DESTDIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
#    }
}

#do not append os name to name so can have standard python name
TARGET=$${TARGET_NAME}$${SHARED_LIB_APPEND}

