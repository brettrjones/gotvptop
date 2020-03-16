# Global
TEMPLATE = lib
QT       -= gui
CONFIG += staticlib
CONFIG -= sharedlib

TARGET_NAME = corelib

include(config_static_dependlib.pri)

include(libcorelib.pri)

PRE_TARGETDEPS += $$PWD/libcrossguid.pro
