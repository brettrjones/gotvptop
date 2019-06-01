#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T11:11:14
#
#-------------------------------------------------

QT       += core gui svg widgets

TARGET = QtHelloWorld
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        $$PWD/QtHelloWorld/main.cpp \
        $$PWD/QtHelloWorld/mainwindow.cpp

HEADERS += \
        $$PWD/QtHelloWorld/mainwindow.h

FORMS += \
        $$PWD/QtHelloWorld/mainwindow.ui

android:{
CONFIG += mobility
MOBILITY = 

#os libs
LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
}

message($$[QT_INSTALL_BINS])

DISTFILES += \
    androidhelloworld/AndroidManifest.xml \
    androidhelloworld/build.gradle \
    androidhelloworld/gradle.properties \
    androidhelloworld/gradlew \
    androidhelloworld/gradlew.bat \
    androidhelloworld/local.properties \
    androidhelloworld/res/drawable/icon.png \
    androidhelloworld/res/values/strings.xml
