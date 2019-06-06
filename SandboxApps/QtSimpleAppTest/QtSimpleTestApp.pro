#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T11:11:14
#
#-------------------------------------------------

QT       += core gui svg widgets

TARGET = QtSimpleTestApp
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$PWD/QtSimpleTestStaticLib
INCLUDEPATH += $$PWD/QtSimpleTestSharedLib

SOURCES += \
        $$PWD/QtSimpleTestApp/main.cpp \
        $$PWD/QtSimpleTestApp/mainwindow.cpp

HEADERS += \
        $$PWD/QtSimpleTestApp/mainwindow.h

FORMS += \
        $$PWD/QtSimpleTestApp/mainwindow.ui

android:{
CONFIG += mobility
MOBILITY = 

#SHARED_LIB_RES_DIR = $$PWD/androidsimpletest/libs/armeabi-v7a/

ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/androidsimpletest

#static libs
LIBS += -l$$PWD/build-staticlibs/armeabi-v7a/libqtsimpleteststaticlib.a

#shared libs
LIBS += -l$$PWD/androidsimpletest/libs/armeabi-v7a/libqtsimpletestsharedlib.so

#os libs
LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
}

win32:{
    LIBS += -l$$PWD/../build-staticlibs/Windows/x64/qtsimpleteststaticlib
    LIBS += -l$$PWD/../build-sharedlibs/Windows/x64/qtsimpletestsharedlib
}

message($$[QT_INSTALL_BINS])
