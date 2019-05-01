
QT       += core gui opengl widgets svg

DEFINES += QT_SVG_LIB QT_OPENGL_LIB QT_WIDGETS_LIB QT_GUI_LIB QT_CORE_LIB QT_MULTIMEDIA_LIB
win32:{
DEFINES += TARGET_OS_WINDOWS
}
unix:!android:{
DEFINES += TARGET_OS_LINUX
}
android:{
DEFINES += TARGET_OS_ANDROID
}

TARGET = QtOpenglThreadTestApp
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$PWD/QtOpenglThreadTest


SOURCES += \
        $$PWD/QtOpenglThreadTest/main.cpp \
        $$PWD/QtOpenglThreadTest/mainwindow.cpp \
    $$PWD/QtOpenglThreadTest/RenderGlThread.cpp \
    $$PWD/QtOpenglThreadTest/RenderGlWidget.cpp \
    $$PWD/QtOpenglThreadTest/RenderGlOffScreenSurface.cpp \
    $$PWD/QtOpenglThreadTest/LogoRenderer.cpp \
    $$PWD/QtOpenglThreadTest/RenderLogoShaders.cpp \
    $$PWD/QtOpenglThreadTest/RenderGlShaders.cpp \
    $$PWD/QtOpenglThreadTest/RenderShaderQt.cpp \
    $$PWD/QtOpenglThreadTest/RenderGlLogic.cpp \
    $$PWD/QtOpenglThreadTest/VxDebug.cpp \
    $$PWD/QtOpenglThreadTest/RenderShaderDefsGl.cpp

HEADERS += \
        $$PWD/QtOpenglThreadTest/mainwindow.h \
    $$PWD/QtOpenglThreadTest/RenderGlThread.h \
    $$PWD/QtOpenglThreadTest/RenderGlWidget.h \
    $$PWD/QtOpenglThreadTest/RenderGlOffScreenSurface.h \
    $$PWD/QtOpenglThreadTest/GlTestCommon.h \
    $$PWD/QtOpenglThreadTest/LogoRenderer.h \
    $$PWD/QtOpenglThreadTest/RenderLogoShaders.h \
    $$PWD/QtOpenglThreadTest/RenderGlShaders.h \
    $$PWD/QtOpenglThreadTest/RenderShaderQt.h \
    $$PWD/QtOpenglThreadTest/RenderGlLogic.h \
    $$PWD/QtOpenglThreadTest/VxDebug.h

FORMS += \
        $$PWD/QtOpenglThreadTest/mainwindow.ui

#include "mainwindow.moc"
#include "RenderGlThread.moc"
#include "RenderGlWidget.moc"
#include "RenderGlLogic.moc"
#include "RenderGlOffScreenSurface.moc"

unix:!android:{
    LIBS +=  -lpthread -ldl -lGLU -lGL -lm -luuid -lrt
}

android:{
    LIBS +=  -ldl -lm -landroid -lEGL -lGLESv2  -lc -lstdc++ -llog -ljnigraphics
}

win32:{
    LIBS +=  opengl32.lib
	LIBS +=  glu32.lib
    LIBS +=  ole32.lib
    LIBS +=  winmm.lib
    LIBS +=  Rpcrt4.lib
}