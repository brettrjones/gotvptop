# Global
TEMPLATE = lib

TARGET_NAME = fdk-aac

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_libstatic.pri)

TARGET=$${TARGET_NAME}$${TARGET_OS_NAME}$${TARGET_LIB_APPEND}

include(libfdk-aac.pri)

