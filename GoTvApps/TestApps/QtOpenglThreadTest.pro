
QT       += core gui opengl widgets

TARGET = QtOpenglThreadTestApp
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$PWD/QtOpenglThreadTest


SOURCES += \
        $$PWD/QtOpenglThreadTest/main.cpp \
        $$PWD/QtOpenglThreadTest/mainwindow.cpp \
    QtOpenglThreadTest/RenderGlThread.cpp \
    QtOpenglThreadTest/RenderGlWidget.cpp \
    QtOpenglThreadTest/RenderGlLogic.cpp

HEADERS += \
        $$PWD/QtOpenglThreadTest/mainwindow.h \
    QtOpenglThreadTest/RenderGlThread.h \
    QtOpenglThreadTest/RenderGlWidget.h \
    QtOpenglThreadTest/GlTestCommon.h \
    QtOpenglThreadTest/RenderGlLogic.h

FORMS += \
        $$PWD/QtOpenglThreadTest/mainwindow.ui

