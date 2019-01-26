# Global
TEMPLATE = lib

TARGET_NAME = compress

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(library_config.pri)

TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}


include(liblzma.pri)
include(liblzo.pri)

include(libbzip2.pri)

include(libzip.pri)




