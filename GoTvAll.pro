

TEMPLATE     = subdirs
CONFIG += no_docs_target

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered

SUBDIRS += $$PWD/GoTvDependLibs.pro
SUBDIRS += $$PWD/GoTvPythonLib.pro
SUBDIRS += $$PWD/GoTvCoreLibs.pro
SUBDIRS += $$PWD/GoTvPtoP_App.pro
