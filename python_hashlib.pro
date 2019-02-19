# Global
TEMPLATE = lib
TARGET_NAME = hashlib

include(config_python_dll.pri)

include(python_hashlib.pri)


include(config_link.pri)


LIBS +=  $${STATIC_LIB_PREFIX}libeay$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}ssleay$${STATIC_LIB_SUFFIX}

CONFIG(debug, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore_d.so
}

CONFIG(release, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore.so
}


#copy to local directory so can easily be linked to
CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug)
}

CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release)
 }

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

