# Global
TEMPLATE = lib

TARGET_NAME = ptopengine

include(config_static_dependlib.pri)
include(config_opensslp_include.pri)

include(libptopengine.pri)

CONFIG(debug, debug|release) {
ptopengineD.depends += netlibD
ptopengineD.depends += pktlibD
ptopengineD.depends += corelibD
ptopengineD.depends += crossguidD
}

CONFIG(release, debug|release) {
ptopengine.depends += netlib
ptopengine.depends += pktlib
ptopengine.depends += corelib
ptopengine.depends += crossguid
}


