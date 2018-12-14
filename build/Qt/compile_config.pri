

QT       += core gui

unix:QMAKE_CXXFLAGS += -std=c++11
unix:QMAKE_CXXFLAGS += -Wno-unused-variable
unix:QMAKE_CXXFLAGS += -Wno-unused-function
unix:QMAKE_CXXFLAGS += -Wno-unused-parameter
unix:QMAKE_CXXFLAGS += -Wno-attributes
unix:QMAKE_CXXFLAGS += -Wno-sign-compare
unix:QMAKE_CXXFLAGS += -Wno-parentheses
unix:QMAKE_CXXFLAGS += -Wno-pointer-sign
unix:QMAKE_CXXFLAGS += -Wno-missing-field-initializers
unix:QMAKE_CXXFLAGS += -Wno-switch

unix:QMAKE_CFLAGS += -Wno-unused-variable
unix:QMAKE_CFLAGS += -Wno-unused-function
unix:QMAKE_CFLAGS += -Wno-unused-parameter
unix:QMAKE_CFLAGS += -Wno-attributes
unix:QMAKE_CFLAGS += -Wno-sign-compare
unix:QMAKE_CFLAGS += -Wno-parentheses
unix:QMAKE_CFLAGS += -Wno-pointer-sign
unix:QMAKE_CFLAGS += -Wno-missing-field-initializers
unix:QMAKE_CFLAGS += -Wno-switch


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

