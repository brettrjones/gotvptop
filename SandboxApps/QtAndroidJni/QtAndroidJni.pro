#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T11:11:14
#
#-------------------------------------------------

QT       += core gui svg widgets
android:{
    QT += androidextras
    QT += gui-private
    DEFINES += TARGET_OS_ANDROID
}

TARGET = QtAndroidJni
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        $$PWD/QtAndroidJni/main.cpp \
        $$PWD/QtAndroidJni/mainwindow.cpp \
        $$PWD/QtAndroidJni/ApplicationInfo.cpp \
        $$PWD/QtAndroidJni/Build.cpp \
        $$PWD/QtAndroidJni/Context.cpp \
        $$PWD/QtAndroidJni/JNIBase.cpp \
        $$PWD/QtAndroidJni/JNIThreading.cpp \
        $$PWD/QtAndroidJni/jutils.cpp \
        $$PWD/QtAndroidJni/PackageItemInfo.cpp \
        $$PWD/QtAndroidJni/PackageManager.cpp \
        $$PWD/QtAndroidJni/VxJava.cpp \
        $$PWD/QtAndroidJni/VxDebug.cpp

HEADERS += \
        $$PWD/QtAndroidJni/mainwindow.h \
        $$PWD/QtAndroidJni/ApplicationInfo.h \
        $$PWD/QtAndroidJni/Build.h \
        $$PWD/QtAndroidJni/Context.h \
        $$PWD/QtAndroidJni/JNIBase.h \
        $$PWD/QtAndroidJni/JNIThreading.h \
        $$PWD/QtAndroidJni/jni.inc \
        $$PWD/QtAndroidJni/jutils.hpp \
        $$PWD/QtAndroidJni/jutils-details.hpp \
        $$PWD/QtAndroidJni/PackageItemInfo.h \
        $$PWD/QtAndroidJni/PackageManager.h \
        $$PWD/QtAndroidJni/VxJava.h \
        $$PWD/QtAndroidJni/VxDebug.h

FORMS += \
        $$PWD/QtAndroidJni/mainwindow.ui

android:{
CONFIG += mobility
MOBILITY = 

#os libs
LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog

    DEFINES += TARGET_OS_ANDROID

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
}

message($$[QT_INSTALL_BINS])

DISTFILES += \
    androidjnitest/AndroidManifest.xml \
    androidjnitest/build.gradle \
    androidjnitest/gradle.properties \
    androidjnitest/gradlew \
    androidjnitest/gradlew.bat \
    androidjnitest/local.properties \
    androidjnitest/res/drawable/icon.png \
    androidjnitest/res/values/strings.xml
