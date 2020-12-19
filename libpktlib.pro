# Global
TEMPLATE = lib
QT       -= gui
CONFIG += staticlib
CONFIG -= sharedlib

TARGET_NAME = pktlib

include(config_static_dependlib.pri)

include(libpktlib.pri)

pktlib.depends += $$PWD/libcorelib.pro




