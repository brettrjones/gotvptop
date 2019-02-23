# Global
TEMPLATE = lib
TARGET_NAME = bsddb

include(config_python_lib.pri)

include(python_bsddb.pri)

win:{
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/db-4.7.25.0/build_windows
}

unix:{
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/db-4.7.25.0/build_unix
}

INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/db-4.7.25.0

include(config_link.pri)

CONFIG(debug, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore_d.so
}

CONFIG(release, debug|release){
    LIBS +=  $${SHARED_LIB_PREFIX}pythoncore.so
}


#copy to local directory so can easily be linked to
CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug)
}

CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release)
 }

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

