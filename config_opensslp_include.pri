
win32{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2o
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2o/inc32
    INCLUDEPATH += $$PWD/sysheaders
}

android{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
}

unix{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
}

macx{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
}
