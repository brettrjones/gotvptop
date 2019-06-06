TEMPLATE = lib
TARGET_NAME  = GoTvPtoPConfigHeaders

include(config_static_dependlib.pri)

HEADERS += 	$$PWD/GoTvAppConfig.h \
        $$PWD/GoTvCompilerConfig.h \
        $$PWD/GoTvCpuArchDefines.h \
        $$PWD/GoTvDependLibrariesConfig.h \
        $$PWD/GoTvDebugConfig.h \
        $$PWD/config_gotvapps.h \
        $$PWD/config_gotvcore.h \
        $$PWD/GoTvTargetOsConfig.h
