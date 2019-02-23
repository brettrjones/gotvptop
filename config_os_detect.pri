
android:{
    message(Building Android)

    DEFINES += TARGET_OS_ANDROID
    DEFINES += TARGET_POSIX

    ANDROID_ARM64 = 0
    ANDROID_ARMv7 = 0
    ANDROID_x86 = 0
    ANDROID_x86_64 = 0

    contains(ANDROID_TARGET_ARCH,armeabi-v8a) {
        DEFINES += TARGET_CPU_64BIT
        DEFINES += TARGET_CPU_ARM
        ANDROID_ARM64 = 1
        TARGET_ARCH_NAME=armeabi-v8a
        TARGET_CPU_BITS=64
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0
    }

    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        DEFINES += TARGET_CPU_32BIT
        DEFINES += TARGET_CPU_ARM
        ANDROID_ARMv7 = 1
        TARGET_ARCH_NAME=armeabi-v7a
        TARGET_CPU_BITS=32
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0
    }

    contains(ANDROID_TARGET_ARCH,x86) {
        DEFINES += TARGET_CPU_32BIT
        DEFINES += TARGET_CPU_X86
        ANDROID_x86 = 1
        TARGET_ARCH_NAME=x86
        TARGET_CPU_BITS=32
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0
    }

    contains(ANDROID_TARGET_ARCH,x86_64) {
        DEFINES += TARGET_CPU_64BIT
        DEFINES += TARGET_CPU_X86_64
        ANDROID_x86_64 = 1
        TARGET_ARCH_NAME=x86_64
        TARGET_CPU_BITS=64
        TARGET_ENDIAN_LITTLE=1
        TARGET_ENDIAN_BIG=0
    }

}

win32{
    message(Building Windows 32 bit)
    DEFINES += TARGET_OS_WINDOWS
    DEFINES += WIN32
    DEFINES += _WIN32
    DEFINES += TARGET_CPU_32BIT
    DEFINES += TARGET_CPU_X86
    TARGET_ARCH_NAME=x86
    TARGET_CPU_BITS=32
    TARGET_ENDIAN_LITTLE=1
    TARGET_ENDIAN_BIG=0
}

unix:!android:{
    message(Building Linux)
    DEFINES += TARGET_OS_LINUX
    DEFINES += TARGET_POSIX
    DEFINES += TARGET_CPU_64BIT
    DEFINES += TARGET_CPU_X86_64
    TARGET_ARCH_NAME=x86_64
    TARGET_CPU_BITS=64
    TARGET_ENDIAN_LITTLE=1
    TARGET_ENDIAN_BIG=0
}

macx{
    message(Building Apple)
    DEFINES += TARGET_OS_APPLE
    DEFINES += TARGET_POSIX
    DEFINES += TARGET_CPU_64BIT
    TARGET_CPU_BITS=64
    TARGET_ENDIAN_LITTLE=0
    TARGET_ENDIAN_BIG=1
}

win:TARGET_OS_NAME = Windows
unix:!android: TARGET_OS_NAME = Linux
android: TARGET_OS_NAME = Android
macx: TARGET_OS_NAME = Apple

contains( TARGET_CPU_BITS, 64 ) {
    message(Building 64 bit )
}

contains( TARGET_CPU_BITS, 32 ) {
    message(Building 32 bit )
}
