INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../../
INCLUDEPATH += $$PWD/../../../DependLibs/
INCLUDEPATH += $$PWD/../../../GoTvCore/
INCLUDEPATH += $$PWD/../../../GoTvCore/xbmc/
INCLUDEPATH += $$PWD/../../../../
INCLUDEPATH += $$PWD/../../../../../

QMAKE_CXXFLAGS += -Wno-unused -Wno-unused-parameter -Wno-ignored-qualifiers -Wno-attributes

include($$PWD/gotvcoresources.pri)

#HEADERS += 	$$PWD/../../xbmc/Application.h
#SOURCES += 	$$PWD/../../xbmc/Application.cpp
