# Global
TEMPLATE = lib
TARGET_NAME = pyexpat

INCLUDEPATH += $PWD/DependLibs/Python-2.7.14/Modules/expat

include(config_python_lib.pri)

include(python_pyexpat.pri)


include(config_link.pri)

CONFIG(debug, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore_d.so
}

CONFIG(release, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore.so
}

include(config_move_python_lib.pri)

