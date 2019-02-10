#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T11:11:14
#
#-------------------------------------------------

QT       += core gui svg widgets

TARGET = QtSimpleTestApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += $$PWD/build/QtSandbox/QtSimpleTestStaticLib
INCLUDEPATH += $$PWD/build/QtSandbox/QtSimpleTestSharedLib

SOURCES += \
        $$PWD/build/QtSandbox/QtSimpleTestApp/main.cpp \
        $$PWD/build/QtSandbox/QtSimpleTestApp/mainwindow.cpp

HEADERS += \
        $$PWD/build/QtSandbox/QtSimpleTestApp/mainwindow.h

FORMS += \
        $$PWD/build/QtSandbox/QtSimpleTestApp/mainwindow.ui

CONFIG += mobility
MOBILITY = 

SHARED_LIB_RES_DIR = $$PWD/androidsimpletest/res/lib/armeabi-v7a/

#contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    #copy shared libs from local directory to packaging directory
    copydata.commands = $(COPY_DIR) $$PWD/build-sharedlibs/*.so $$SHARED_LIB_RES_DIR
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
#}

#contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
#make libs it part of the android install package

#contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/androidsimpletest/res/lib/armeabi-v7a/libqtsimpletestsharedlibAndroid_d.so

    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/build/QtSandbox/QtSimpleTestApp
#}


#static libs
LIBS += -l$$PWD/build-staticlibs/libqtsimpleteststaticlibAndroidD.a

#shared libs
LIBS += -l$$SHARED_LIB_RES_DIR/libqtsimpletestsharedlibAndroid_d.so

#os libs
LIBS +=  -ldl -lm -landroid -lc -lstdc++ -llog


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

message($$[QT_INSTALL_BINS])

DISTFILES += \
    androidsimpletest/AndroidManifest.xml \
    androidsimpletest/gradle/wrapper/gradle-wrapper.jar \
    androidsimpletest/gradlew \
    androidsimpletest/res/values/libs.xml \
    androidsimpletest/build.gradle \
    androidsimpletest/gradle/wrapper/gradle-wrapper.properties \
    androidsimpletest/gradlew.bat \
    androidsimpletest/res/values/strings.xml


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/androidsimpletest/res/lib/armeabi-v7a/ -lqtsimpletestsharedlibAndroid_d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/androidsimpletest/res/lib/armeabi-v7a/ -lqtsimpletestsharedlibAndroid_dd
else:unix: LIBS += -L$$PWD/androidsimpletest/res/lib/armeabi-v7a/ -lqtsimpletestsharedlibAndroid_d

INCLUDEPATH += $$PWD/androidsimpletest/res/lib/armeabi-v7a
DEPENDPATH += $$PWD/androidsimpletest/res/lib/armeabi-v7a
