# Global
TEMPLATE = lib
TARGET_NAME = ssl

include(config_openssl_lib.pri)
include(config_opensslp_include.pri)

include(libssl.pri)


LIBS +=  $${STATIC_LIB_PREFIX}gnu$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}iconv$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}bz2$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}depends$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}curl$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}netlib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}pktlib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}corelib$${STATIC_LIB_SUFFIX}
LIBS +=  $${STATIC_LIB_PREFIX}crossguid$${STATIC_LIB_SUFFIX}
