

HEADERS += $$PWD/../../VxRescaleRgb.h \
    $$PWD/../../VxVideoLib.h \
    $$PWD/../../VxVideoConvert.h \
    $$PWD/../../VxVidCapImp.h \
    $$PWD/../../VxVidCap.h \
    $$PWD/../../IVxVidCap.h \
    $$PWD/../../GdvBufferUtil.h



SOURCES += 	$$PWD/../../VxRescaleRgb.cpp \
    $$PWD/../../VxVideoConvert.cpp \
    $$PWD/../../GdvBufferUtil.cpp

win32:{
    SOURCES += 	$$PWD/../../VxVidCapImp.cpp \
        $$PWD/../../VxVidCap.cpp
}

 


