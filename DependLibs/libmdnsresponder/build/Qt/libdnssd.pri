win32{
DEFINES += WINDOWS
}

unix{
    DEFINES += NOT_HAVE_SA_LEN
}

INCLUDEPATH += $$PWD/../../

HEADERS += 	$$PWD/../../config_libmdnsresponder.h \
	$$PWD/../../mDNSShared/CommonServices.h \
	$$PWD/../../mDNSShared/DebugServices.h \
	$$PWD/../../mDNSShared/GenLinkedList.h \
	$$PWD/../../mDNSShared/dns_sd.h \
	$$PWD/../../mDNSShared/dnssd_ipc.h \
	$$PWD/resource.h

SOURCES += 	$$PWD/../../mDNSShared/DebugServices.c \
	$$PWD/../../mDNSShared/GenLinkedList.c \
	$$PWD/../../mDNSShared/dnssd_clientlib.c \
	$$PWD/../../mDNSShared/dnssd_clientstub.c \
	$$PWD/../../mDNSShared/dnssd_ipc.c \
#	$$PWD/dllmain.c

