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

CONFIG += mobility
MOBILITY = 

SHARED_LIB_RES_DIR = $$PWD/androidsimpletest/res/lib/armeabi-v7a/

ANDROID_EXTRA_LIBS = \
        $$PWD/androidsimpletest/res/lib/armeabi-v7a/libqtsimpletestsharedlib.so

#static libs
LIBS += -l$$PWD/build-staticlibs/armeabi-v7a/libqtsimpleteststaticlib.a

#shared libs
LIBS += -l$$PWD/androidsimpletest/res/lib/armeabi-v7a/libqtsimpletestsharedlib.so

#os libs
LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

message($$[QT_INSTALL_BINS])