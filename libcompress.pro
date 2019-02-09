# Global
TEMPLATE = lib

TARGET_NAME = compress

include(version.pri)
include(os_detect.pri)
include(compile_config.pri)

include(config_libstatic.pri)

include(liblzma.pri)
include(liblzo.pri)

include(libbzip2.pri)

include(libzip.pri)




