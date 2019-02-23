# Global
TEMPLATE = lib
TARGET_NAME = hashlib

include(config_python_lib.pri)

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

include(config_copy_shared_lib.pri)

