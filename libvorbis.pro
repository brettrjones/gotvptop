# Global
TEMPLATE = lib

TARGET_NAME = vorbis2 # added 2 because otherwise linux links the .so system lib

include(config_static_dependlib.pri)

include(libvorbis.pri)
