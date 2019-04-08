#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T11:11:14
#
#-------------------------------------------------

QT       += core gui svg widgets

TARGET = QtSimpleTestApp
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$PWD/../QtSimpleTestStaticLib
INCLUDEPATH += $$PWD/../QtSimpleTestSharedLib

SOURCES += \
        $$PWD/main.cpp \
        $$PWD/mainwindow.cpp

HEADERS += \
        $$PWD/mainwindow.h

FORMS += \
        $$PWD/mainwindow.ui

CONFIG += mobility
MOBILITY = 


#static libs
LIBS += -lqtsimpleteststaticlibAndroidD

#shared libs
LIBS += -lqtsimpletestsharedlibAndroid

#os libs
LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog
