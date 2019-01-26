

HEADERS += $$PWD/DependLibs/vxvideolib/VxRescaleRgb.h \
    $$PWD/DependLibs/vxvideolib/VxVideoLib.h \
    $$PWD/DependLibs/vxvideolib/VxVideoConvert.h \
    $$PWD/DependLibs/vxvideolib/VxVidCapImp.h \
    $$PWD/DependLibs/vxvideolib/VxVidCap.h \
    $$PWD/DependLibs/vxvideolib/IVxVidCap.h \
    $$PWD/DependLibs/vxvideolib/GdvBufferUtil.h



SOURCES += 	$$PWD/DependLibs/vxvideolib/VxRescaleRgb.cpp \
    $$PWD/DependLibs/vxvideolib/VxVideoConvert.cpp \
    $$PWD/DependLibs/vxvideolib/GdvBufferUtil.cpp

win32:{
    SOURCES += 	$$PWD/DependLibs/vxvideolib/VxVidCapImp.cpp \
        $$PWD/DependLibs/vxvideolib/VxVidCap.cpp
}

 


