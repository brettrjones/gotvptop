# Global
TEMPLATE = lib
TARGET_NAME = pythoncore

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_sharedlib.pri)

include(python_pythoncore.pri)

include(config_link.pri)

LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}iconv$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}ssl$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}netlib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}pktlib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}intl$${SHARED_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}expat$${SHARED_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}ffi$${SHARED_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}expat$${SHARED_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}util$${SHARED_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}ssl$${SHARED_LIB_SUFFIX}
#LIBS +=  $${SHARED_LIB_PREFIX}crypto$${SHARED_LIB_SUFFIX}

#-lintl

unix:!android:{
    LIBS +=  -ldl -lGLU -lGL -lm -luuid -lrt -lpthread -lpython2.7
}

android:{
    LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog
}
