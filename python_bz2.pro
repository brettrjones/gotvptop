# Global
TEMPLATE = lib
TARGET_NAME = bz2

include(config_python_lib.pri)

include(python_bz2.pri)


include(config_link.pri)

CONFIG(debug, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore_d.so
}

CONFIG(release, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore.so
}

include(config_copy_shared_lib.pri)
