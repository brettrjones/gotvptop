# Global
TEMPLATE = lib
TARGET_NAME = unicodedata

include(config_python_lib.pri)

include(python_unicodedata.pri)


include(config_link.pri)

CONFIG(debug, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore_d.so
}

CONFIG(release, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore.so
}

include(config_copy_shared_lib.pri)

