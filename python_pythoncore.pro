# Global
TEMPLATE = lib
TARGET_NAME = pythoncore


include(config_openssl_lib.pri)
include(config_opensslp_include.pri)

include(python_pythoncore.pri)

include(config_copy_shared_lib.pri)

INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/Include
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/Modules/expat
INCLUDEPATH += $$PWD/DependLibs/libgnu


$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/GoTvOpenSslLib.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libbz2.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libcorelib.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libcrossguid.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libdepends.pro
$${TARGET_NAME}$${SHARED_LIB_APPEND}.depends += $$PWD/libgnu.pro


$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/libgnu.pro
$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/libbz2.pro
$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/libcorelib.pro
$${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}.depends += $$PWD/GoTvOpenSslLib.pro



PRE_TARGETDEPS +=  $${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
PRE_TARGETDEPS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}

LIBS +=  $${SHARED_LIB_PREFIX}ssl$${SHARED_PYTHON_LIB_SUFFIX}

LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}

OBJECTS_DIR=.objs/$${TARGET_NAME}/$${BUILD_TYPE}

#copy to local directory so can easily be linked to

unix:!android{
    copydata.commands = $(COPY_DIR) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}/*.so $$shell_path(${DEST_EXE_DIR}) )
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

#FIXME post link occures before QMAKE_EXTRA_TARGETS so have to build twice
#android:{
    #for android we need the extra step of moving the shared libs to android/lib/arch
#    PYTHON_CORE_COPY_CMD = $(COPY_DIR) $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE} $${DEST_EXE_DIR}
#    contains(QMAKE_HOST.os,Windows){
#       PYTHON_CORE_COPY_CMD = $(COPY_DIR) $$PWD//build-sharedlibs//$${TARGET_OS_NAME}//$${TARGET_ARCH_NAME}//$${BUILD_TYPE}//*.so $$shell_path($${DEST_EXE_DIR})
       #PYTHON_CORE_COPY_CMD ~= s,/,\\,g # replace / with \
#    }

#    message("**android copy libs $$quote($${PYTHON_CORE_COPY_CMD})")

#    QMAKE_POST_LINK = $$quote($${PYTHON_CORE_COPY_CMD})
#}



