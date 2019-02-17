# Global
TEMPLATE = lib
TARGET_NAME = pythonbz2

include(config_python_lib.pri)

include(python_bz2.pri)

include(config_link.pri)

    LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
    LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore$${SHARED_PYTHON_LIB_SUFFIX}

unix:!android:{
    LIBS +=  -ldl -lGLU -lGL -lm -luuid -lrt -lpthread
}

android:{
    LIBS +=  -ldl -lm -landroid
}

