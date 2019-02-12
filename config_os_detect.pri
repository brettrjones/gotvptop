
TARGET_ARCH_NAME=

android{
    DEFINES += TARGET_OS_ANDROID
    DEFINES += TARGET_POSIX

    ANDROID_ARM64 = 0
    ANDROID_ARMv7 = 0
    ANDROID_x86 = 0
    ANDROID_x86_64 = 0

    contains(ANDROID_TARGET_ARCH,armeabi-v8a) {
        ANDROID_ARM64 = 1
        TARGET_ARCH_NAME=armeabi-v8a
    }
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_ARMv7 = 1
        TARGET_ARCH_NAME=armeabi-v7a
    }
    contains(ANDROID_TARGET_ARCH,x86) {
        ANDROID_x86 = 1
        TARGET_ARCH_NAME=x86
    }
    contains(ANDROID_TARGET_ARCH,x86_64) {
        ANDROID_x86_64 = 1
        TARGET_ARCH_NAME=x86_64
    }
}

win32{
    DEFINES += TARGET_OS_WINDOWS
    DEFINES += WIN32
    DEFINES += _WIN32
TARGET_ARCH_NAME=x86
}

unix:!android{
    DEFINES += TARGET_OS_LINUX
    DEFINES += TARGET_POSIX
TARGET_ARCH_NAME=x86_64
}

macx{
    DEFINES += TARGET_OS_APPLE
    DEFINES += TARGET_POSIX
}

win32:TARGET_OS_NAME = Windows
unix:!android: TARGET_OS_NAME = Linux
android: TARGET_OS_NAME = Android
macx: TARGET_OS_NAME = Apple
