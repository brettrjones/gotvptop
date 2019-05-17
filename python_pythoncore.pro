# Global
TEMPLATE = lib
TARGET_NAME = pythoncore

include(config_python_lib.pri)

include(config_openssl_lib.pri)
include(config_opensslp_include.pri)

include(python_pythoncore.pri)


$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/GoTvOpenSslLib.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libgnu.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libbz2.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libcorelib.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libcrossguid.pro


$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/libgnu.pro
$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/libbz2.pro
$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/libcorelib.pro
$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/GoTvOpenSslLib.pro



PRE_TARGETDEPS +=  $${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}

LIBS +=  $${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}

LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}


#copy to local directory so can easily be linked to
win:{
CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.dll) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug)
}

CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.dll) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release)
 }
 first.depends = $(first) copydata
 export(first.depends)
 export(copydata.commands)
 QMAKE_EXTRA_TARGETS += first copydata
}

android:{
 CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR) $$OUT_PWD/*.so $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
 }

 CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$OUT_PWD/*.so) $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
 }
 first.depends = $(first) copydata
 export(first.depends)
 export(copydata.commands)
 QMAKE_EXTRA_TARGETS += first copydata
}

CONFIG(debug, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/debug
}

CONFIG(release, debug|release){
    OBJECTS_DIR=.objs/$${TARGET_NAME}/release
}

DISTFILES += \
    config_copy_shared_lib.pri


#copy python core to bin directory
 CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR)  $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug/* $${DEST_PYTHON_EXE_DIR}

 CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release/* $${DEST_PYTHON_EXE_DIR}
 }

 first.depends = $(first) copydata
 export(first.depends)
 export(copydata.commands)
 QMAKE_EXTRA_TARGETS += first copydata
}

