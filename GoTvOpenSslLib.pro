

TEMPLATE     = subdirs
CONFIG += no_docs_target

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered

include(config_os_detect.pri)

SUBDIRS += $$PWD/libssl.pro
