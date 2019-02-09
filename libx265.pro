# Global
TEMPLATE = lib

TARGET_NAME = x265

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_libstatic.pri)

include(libx265.pri)
