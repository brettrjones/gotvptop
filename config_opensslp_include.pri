
win32{
DEFINES += DSO_WIN32
}

#DEFINES += NO_SYSLOG MONOLITH OPENSSL_THREADS L_ENDIAN OPENSSL_BN_ASM_PART_WORDS OPENSSL_IA32_SSE2 OPENSSL_BN_ASM_MONT OPENSSL_NO_RC5 OPENSSL_NO_MD2 OPENSSL_NO_KB5 OPENSSL_NO_JPAKE OPENSSL_NO_DYNAMIC_ENGINE DEBUG_VTPOOLUPLOAD NO_WINDOWS_BRAINDEATH
DEFINES += OPENSSL_NO_EC_NISTP_64_GCC_128 OPENSSL_NO_GMP OPENSSL_NO_JPAKE OPENSSL_NO_LIBUNBOUND OPENSSL_NO_MD2 OPENSSL_NO_RC5
DEFINES += OPENSSL_NO_RFC3779 OPENSSL_NO_SCTP OPENSSL_NO_SSL_TRACE OPENSSL_NO_SSL2 OPENSSL_NO_STORE OPENSSL_NO_UNIT_TEST OPENSSL_NO_WEAK_SSL_CIPHERS
DEFINES += NO_SYSLOG OPENSSL_THREADS _REENTRANT DSO_DLFCN HAVE_DLFCN_H m64 L_ENDIAN
DEFINES += OPENSSL_NO_EC_NISTP_64_GCC_128

win32{
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p
    INCLUDEPATH += $$PWD/DependLibs/openssl-1.0.2p/include
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