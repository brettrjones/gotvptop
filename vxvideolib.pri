

HEADERS += $$PWD/DependLibs/VxVideoLib/VxRescaleRgb.h \
    $$PWD/DependLibs/VxVideoLib/VxVideoLib.h \
    $$PWD/DependLibs/VxVideoLib/VxVideoConvert.h \
    $$PWD/DependLibs/VxVideoLib/VxVidCapImp.h \
    $$PWD/DependLibs/VxVideoLib/VxVidCap.h \
    $$PWD/DependLibs/VxVideoLib/IVxVidCap.h \
    $$PWD/DependLibs/VxVideoLib/GdvBufferUtil.h



SOURCES += 	$$PWD/DependLibs/VxVideoLib/VxRescaleRgb.cpp \
    $$PWD/DependLibs/VxVideoLib/VxVideoConvert.cpp \
    $$PWD/DependLibs/VxVideoLib/GdvBufferUtil.cpp

win32:{
    SOURCES += 	$$PWD/DependLibs/VxVideoLib/VxVidCapImp.cpp \
        $$PWD/DependLibs/VxVideoLib/VxVidCap.cpp
}

 


