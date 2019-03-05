win32{
DEFINES += WINDOWS
}

unix{
    DEFINES += NOT_HAVE_SA_LEN
}

INCLUDEPATH += $$PWD/DependLibs/libmdnsresponder
INCLUDEPATH += $$PWD/DependLibs/libmdnsresponder/mDNSShared

HEADERS += 	$$PWD/DependLibs/libmdnsresponder/config_libmdnsresponder.h \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/CommonServices.h \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/DebugServices.h \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/GenLinkedList.h \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/dns_sd.h \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/dnssd_ipc.h

SOURCES += 	$$PWD/DependLibs/libmdnsresponder/mDNSShared/DebugServices.c \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/GenLinkedList.c \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/dnssd_clientlib.c \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/dnssd_clientstub.c \
    $$PWD/DependLibs/libmdnsresponder/mDNSShared/dnssd_ipc.c \
#	$$PWD/dllmain.c

