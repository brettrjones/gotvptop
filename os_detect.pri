

android{
    DEFINES += TARGET_OS_ANDROID
    DEFINES += TARGET_POSIX
}

win32{
    DEFINES += TARGET_OS_WINDOWS
    DEFINES += WIN32
    DEFINES += _WIN32
}

unix:!android{
    DEFINES += TARGET_OS_LINUX
    DEFINES += TARGET_POSIX
}

macx{
    DEFINES += TARGET_OS_APPLE
    DEFINES += TARGET_POSIX
}

win32:TARGET_OS_NAME = Windows
unix:!android: TARGET_OS_NAME = Linux
android: TARGET_OS_NAME = Android
macx: TARGET_OS_NAME = Apple