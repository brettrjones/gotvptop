contains( TARGET_CPU_BITS, 64 ) {
    message(python_ssl 64Bit)
    INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include64

HEADERS += \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include64/openssl/opensslconf.h \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include64/openssl/opensslconf_linux.h \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include64/openssl/opensslconf_windows.h
}

contains( TARGET_CPU_BITS, 32 ) {
    message(python_ssl 32Bit)
    INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include32
HEADERS += \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include32/openssl/opensslconf.h \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include32/openssl/opensslconf_linux.h \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include32/openssl/opensslconf_windows.h
}

INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k

SOURCES += 	$$PWD/DependLibs/Python-2.7.14/Modules/_ssl.c


