DEFINES += GLEW_STATIC DO_NOT_DEFINE_BOOL

INCLUDEPATH += $$PWD/DependLibs/libglew/include/

HEADERS += 	$$PWD/DependLibs/libglew/include/GL/glew.h \
    $$PWD/DependLibs/libglew/include/GL/wglew.h

SOURCES += 	$$PWD/DependLibs/libglew/src/glew.c

