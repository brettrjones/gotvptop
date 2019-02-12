# Global
TEMPLATE = app
TARGET_NAME = python

include(config_pythonlib.pri)

TARGET=$${TARGET_NAME}$${TARGET_LIB_APPEND}

include(python_bz2.pri)

include(config_link.pri)
    LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
    LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}

unix:!android:{
    LIBS +=  -ldl -lGLU -lGL -lm -luuid -lrt -lpthread
}

android:{
    LIBS +=  -ldl -lm -landroid
}

