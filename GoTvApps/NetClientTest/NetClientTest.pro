
QT       += core gui opengl widgets

TARGET = NetClientTest
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$PWD/NetClientTest


SOURCES += \
        $$PWD/NetClientTest/main.cpp \
        $$PWD/NetClientTest/mainwindow.cpp \
		$$PWD/NetClientTest/AppLogic.cpp \
		$$PWD/NetClientTest/AppSettings.cpp \
		$$PWD/NetClientTest/LogWidget.cpp \
		$$PWD/NetClientTest/NetTestUtil.cpp \
		$$PWD/NetClientTest/NetWidget.cpp \
		$$PWD/NetClientTest/NlcPingResponseServer.cpp \
		$$PWD/NetClientTest/NlcTestThread.cpp

HEADERS += \
        $$PWD/NetClientTest/mainwindow.h \
		$$PWD/NetClientTest/RenderGlThread.h \
		$$PWD/NetClientTest/AppLogic.h \
		$$PWD/NetClientTest/AppSettings.h \
		$$PWD/NetClientTest/LogWidget.h \
		$$PWD/NetClientTest/NetTestUtil.h \
		$$PWD/NetClientTest/NetWidget.h \
		$$PWD/NetClientTest/NlcPingResponseServer.h \
		$$PWD/NetClientTest/NlcTestCommon.h \
		$$PWD/NetClientTest/NlcTestThread.h

FORMS += \
        $$PWD/NetClientTest/mainwindow.ui \
		$$PWD/NetClientTest/LogWidget.ui \
		$$PWD/NetClientTest/NlcTestThread.ui 

