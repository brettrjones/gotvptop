

TEMPLATE     = subdirs
CONFIG += no_docs_target

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered

SUBDIRS += $$PWD/GoTvPythonLib.pro

SUBDIRS += $$PWD/GoTvPtoPAppLib.pro
SUBDIRS += $$PWD/GoTvDependLibs.pro

SUBDIRS += $$PWD/GoTvCoreLibs.pro


SUBDIRS += $$PWD/GoTvPtoP_App.pro

