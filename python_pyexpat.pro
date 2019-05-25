# Global
TEMPLATE = lib
TARGET_NAME = pyexpat

INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/Modules/expat
DEFINES += PYEXPAT_EXPORTS XML_STATIC


include(config_python_lib.pri)

include(python_pyexpat.pri)

include(config_link.pri)

LIBS +=  $${SHARED_LIB_PREFIX}pythoncore$${SHARED_PYTHON_LIB_SUFFIX}

include(config_move_python_lib.pri)

