

android {
    DEFINES += TARGET_OS_ANDROID
}

win32 {
    DEFINES += TARGET_OS_WINDOWS
    DEFINES += WIN32
    DEFINES += _WIN32
}

unix:!android {
    DEFINES += TARGET_OS_LINUX
}

macx {
    DEFINES += TARGET_OS_APPLE
}

win32:TARGET_OS_NAME = Windows
linux:!android: TARGET_OS_NAME = Linux
android: TARGET_OS_NAME = Android
macx: TARGET_OS_NAME = Apple
