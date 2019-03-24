
android:{
    DEFINES += TARGET_OS_ANDROID
    DEFINES += TARGET_POSIX
    ANDROID_ARM64 = 0
    ANDROID_ARMv7 = 0
    ANDROID_x86 = 0
    ANDROID_x86_64 = 0

    DEST_EXE_DIR = $$PWD/android/
    DEST_SHARED_LIBS_DIR = $$PWD/bin-Linux
    DEST_PYTHON_EXE_DIR = $$PWD/bin-Linux
    DEST_PYTHON_DLL_DIR = $$PWD/bin-Linux/assets/kodi/system/Python/DLLs
    DEST_PYTHON_LIB_DIR = $$PWD/bin-Linux/assets/kodi/system/Python/Lib

    contains(ANDROID_TARGET_ARCH,armeabi-v8a) {
        DEFINES += TARGET_CPU_64BIT
        DEFINES += TARGET_CPU_ARM
        ANDROID_ARM64 = 1
        TARGET_ARCH_NAME=armeabi-v8a
        TARGET_CPU_BITS=64
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0

        DEST_SHARED_LIBS_DIR = $$PWD/android/lib/armeabi-v8a
        DEST_EXE_DIR = $$PWD/android/lib/armeabi-v8a
        DEST_PYTHON_EXE_DIR = $$PWD/android/lib/armeabi-v8a
        DEST_PYTHON_DLL_DIR = $$PWD/android/assets/python2.7/lib/python2.7
        DEST_PYTHON_LIB_DIR = $$PWD/android/assets/python2.7/lib/python2.7
    }

    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        DEFINES += TARGET_CPU_32BIT
        DEFINES += TARGET_CPU_ARM
        ANDROID_ARMv7 = 1
        TARGET_ARCH_NAME=armeabi-v7a
        TARGET_CPU_BITS=32
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0

        DEST_SHARED_LIBS_DIR = $$PWD/android/lib/armeabi-v7a
        DEST_EXE_DIR = $$PWD/android/lib/armeabi-v7a
        DEST_PYTHON_EXE_DIR = $$PWD/android/lib/armeabi-v7a
        DEST_PYTHON_DLL_DIR = $$PWD/android/assets/python2.7/lib/python2.7
        DEST_PYTHON_LIB_DIR = $$PWD/android/assets/python2.7/lib/python2.7
    }

    contains(ANDROID_TARGET_ARCH,x86) {
        DEFINES += TARGET_CPU_32BIT
        DEFINES += TARGET_CPU_X86
        ANDROID_x86 = 1
        TARGET_ARCH_NAME=x86
        TARGET_CPU_BITS=32
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0

        DEST_SHARED_LIBS_DIR = $$PWD/android/lib/x86
        DEST_EXE_DIR = $$PWD/android/lib/x86
        DEST_PYTHON_EXE_DIR = $$PWD/android/lib/x86
        DEST_PYTHON_DLL_DIR = $$PWD/android/assets/python2.7/lib/python2.7
        DEST_PYTHON_LIB_DIR = $$PWD/android/assets/python2.7/lib/python2.7

    }

    contains(ANDROID_TARGET_ARCH,x86_64) {
        DEFINES += TARGET_CPU_64BIT
        DEFINES += TARGET_CPU_X86_64
        ANDROID_x86_64 = 1
        TARGET_ARCH_NAME=x86_64
        TARGET_CPU_BITS=64
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0

        DEST_SHARED_LIBS_DIR = $$PWD/android/lib/x86_64
        DEST_EXE_DIR = $$PWD/android/lib/x86_64
        DEST_PYTHON_EXE_DIR = $$PWD/android/lib/x86_64
        DEST_PYTHON_DLL_DIR = $$PWD/android/assets/python2.7/lib/python2.7
        DEST_PYTHON_LIB_DIR = $$PWD/android/assets/python2.7/lib/python2.7
    }
}

win32:{
    DEFINES += TARGET_OS_WINDOWS
    DEFINES += WIN64
    DEFINES += _WIN64
    DEFINES += TARGET_CPU_64BIT
    DEFINES += TARGET_CPU_X86_64
    TARGET_ARCH_NAME=x86_64
    TARGET_CPU_BITS=64
    TARGET_ENDIAN_LITTLE=1
    TARGET_ENDIAN_BIG=0

    DEST_SHARED_LIBS_DIR = $$PWD/bin-Windows/
    DEST_EXE_DIR = $$PWD/bin-Windows/
    DEST_PYTHON_EXE_DIR = $$PWD/bin-Windows/
    DEST_PYTHON_DLL_DIR = $$PWD/bin-Windows/assets/kodi/system/Python/DLLs/
    DEST_PYTHON_LIB_DIR = $$PWD/bin-Windows/assets/kodi/system/Python/Lib/
}

unix:!android:{
    DEFINES += TARGET_OS_LINUX
    DEFINES += TARGET_POSIX
    DEFINES += TARGET_CPU_64BIT
    DEFINES += TARGET_CPU_X86_64
    TARGET_ARCH_NAME=x86_64
    TARGET_CPU_BITS=64
    TARGET_ENDIAN_LITTLE=1
    TARGET_ENDIAN_BIG=0

    DEST_SHARED_LIBS_DIR = $$PWD/bin-Linux/
    DEST_EXE_DIR = $$PWD/bin-Linux/
    DEST_PYTHON_EXE_DIR = $$PWD/bin-Linux/
    DEST_PYTHON_DLL_DIR = $$PWD/bin-Linux/assets/kodi/system/Python/DLLs/
    DEST_PYTHON_LIB_DIR = $$PWD/bin-Linux/assets/kodi/system/Python/Lib/
}

macx{
    DEFINES += TARGET_OS_APPLE
    DEFINES += TARGET_POSIX
    DEFINES += TARGET_CPU_64BIT
    TARGET_CPU_BITS=64
    TARGET_ENDIAN_LITTLE=0
    TARGET_ENDIAN_BIG=1
}

win32:TARGET_OS_NAME = Windows
unix:!android: TARGET_OS_NAME = Linux
android: TARGET_OS_NAME = Android
macx: TARGET_OS_NAME = Apple

CONFIG(debug, debug|release){
    BUILD_TYPE=Debug
}

CONFIG(release, debug|release){
    BUILD_TYPE=Release
}

#contains( TARGET_CPU_BITS, 64 ) {
#    message(Building $${TARGET_OS_NAME} $${BUILD_TYPE} 64 bit $${TARGET_ARCH_NAME} )
#}

#contains( TARGET_CPU_BITS, 32 ) {
#    message(Building $${TARGET_OS_NAME} $${BUILD_TYPE} 32 bit $${TARGET_ARCH_NAME}  )
#}
