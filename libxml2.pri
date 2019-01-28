
DEFINES += LIBXML_STATIC

INCLUDEPATH += $$PWD/DependLibs/libxml2/

HEADERS += 	$$PWD/DependLibs/libxml2/DOCBparser.h \
    $$PWD/DependLibs/libxml2/HTMLparser.h \
    $$PWD/DependLibs/libxml2/HTMLtree.h \
    $$PWD/DependLibs/libxml2/SAX.h \
    $$PWD/DependLibs/libxml2/SAX2.h \
    $$PWD/DependLibs/libxml2/acconfig.h \
    $$PWD/DependLibs/libxml2/c14n.h \
    $$PWD/DependLibs/libxml2/catalog.h \
    $$PWD/DependLibs/libxml2/chvalid.h \
    $$PWD/DependLibs/libxml2/debugXML.h \
    $$PWD/DependLibs/libxml2/dict.h \
    $$PWD/DependLibs/libxml2/elfgcchack.h \
    $$PWD/DependLibs/libxml2/encoding.h \
    $$PWD/DependLibs/libxml2/entities.h \
    $$PWD/DependLibs/libxml2/globals.h \
    $$PWD/DependLibs/libxml2/hash.h \
    $$PWD/DependLibs/libxml2/libxml.h \
    $$PWD/DependLibs/libxml2/libxml2_config.h \
    $$PWD/DependLibs/libxml2/libxml2_config_android.h \
    $$PWD/DependLibs/libxml2/libxml2_config_linux.h \
    $$PWD/DependLibs/libxml2/libxml2_config_windows.h \
    $$PWD/DependLibs/libxml2/list.h \
    $$PWD/DependLibs/libxml2/nanoftp.h \
    $$PWD/DependLibs/libxml2/nanohttp.h \
    $$PWD/DependLibs/libxml2/parser.h \
    $$PWD/DependLibs/libxml2/parserInternals.h \
    $$PWD/DependLibs/libxml2/pattern.h \
    $$PWD/DependLibs/libxml2/relaxng.h \
    $$PWD/DependLibs/libxml2/schemasInternals.h \
    $$PWD/DependLibs/libxml2/schematron.h \
    $$PWD/DependLibs/libxml2/threads.h \
    $$PWD/DependLibs/libxml2/tree.h \
    $$PWD/DependLibs/libxml2/trio.h \
    $$PWD/DependLibs/libxml2/triodef.h \
    $$PWD/DependLibs/libxml2/trionan.h \
    $$PWD/DependLibs/libxml2/triop.h \
    $$PWD/DependLibs/libxml2/triostr.h \
    $$PWD/DependLibs/libxml2/uri.h \
    $$PWD/DependLibs/libxml2/valid.h \
    $$PWD/DependLibs/libxml2/win32config.h \
    $$PWD/DependLibs/libxml2/wsockcompat.h \
    $$PWD/DependLibs/libxml2/xinclude.h \
    $$PWD/DependLibs/libxml2/xlink.h \
    $$PWD/DependLibs/libxml2/xmlIO.h \
    $$PWD/DependLibs/libxml2/xmlautomata.h \
    $$PWD/DependLibs/libxml2/xmlerror.h \
    $$PWD/DependLibs/libxml2/xmlexports.h \
    $$PWD/DependLibs/libxml2/xmlmemory.h \
    $$PWD/DependLibs/libxml2/xmlmodule.h \
    $$PWD/DependLibs/libxml2/xmlreader.h \
    $$PWD/DependLibs/libxml2/xmlregexp.h \
    $$PWD/DependLibs/libxml2/xmlsave.h \
    $$PWD/DependLibs/libxml2/xmlschemas.h \
    $$PWD/DependLibs/libxml2/xmlschemastypes.h \
    $$PWD/DependLibs/libxml2/xmlstring.h \
    $$PWD/DependLibs/libxml2/xmlunicode.h \
    $$PWD/DependLibs/libxml2/xmlversion.h \
    $$PWD/DependLibs/libxml2/xmlwriter.h \
    $$PWD/DependLibs/libxml2/xpath.h \
    $$PWD/DependLibs/libxml2/xpathInternals.h

SOURCES += 	$$PWD/DependLibs/libxml2/DOCBparser.c \
    $$PWD/DependLibs/libxml2/HTMLparser.c \
    $$PWD/DependLibs/libxml2/HTMLtree.c \
    $$PWD/DependLibs/libxml2/SAX.c \
    $$PWD/DependLibs/libxml2/SAX2.c \
    $$PWD/DependLibs/libxml2/c14n.c \
    $$PWD/DependLibs/libxml2/catalog.c \
    $$PWD/DependLibs/libxml2/chvalid.c \
    $$PWD/DependLibs/libxml2/debugXML.c \
    $$PWD/DependLibs/libxml2/dict.c \
    $$PWD/DependLibs/libxml2/encoding.c \
    $$PWD/DependLibs/libxml2/entities.c \
    $$PWD/DependLibs/libxml2/error.c \
    $$PWD/DependLibs/libxml2/globals.c \
    $$PWD/DependLibs/libxml2/hash.c \
    $$PWD/DependLibs/libxml2/legacy.c \
    $$PWD/DependLibs/libxml2/list.c \
    $$PWD/DependLibs/libxml2/nanoftp.c \
    $$PWD/DependLibs/libxml2/nanohttp.c \
    $$PWD/DependLibs/libxml2/parser.c \
    $$PWD/DependLibs/libxml2/parserInternals.c \
    $$PWD/DependLibs/libxml2/pattern.c \
    $$PWD/DependLibs/libxml2/relaxng.c \
    $$PWD/DependLibs/libxml2/schematron.c \
    $$PWD/DependLibs/libxml2/threads.c \
    $$PWD/DependLibs/libxml2/tree.c \
    $$PWD/DependLibs/libxml2/trio.c \
    $$PWD/DependLibs/libxml2/trionan.c \
    $$PWD/DependLibs/libxml2/triostr.c \
    $$PWD/DependLibs/libxml2/uri.c \
    $$PWD/DependLibs/libxml2/valid.c \
    $$PWD/DependLibs/libxml2/xinclude.c \
    $$PWD/DependLibs/libxml2/xlink.c \
    $$PWD/DependLibs/libxml2/xmlIO.c \
    $$PWD/DependLibs/libxml2/xmllint.c \
    $$PWD/DependLibs/libxml2/xmlmemory.c \
    $$PWD/DependLibs/libxml2/xmlmodule.c \
    $$PWD/DependLibs/libxml2/xmlreader.c \
    $$PWD/DependLibs/libxml2/xmlregexp.c \
    $$PWD/DependLibs/libxml2/xmlsave.c \
    $$PWD/DependLibs/libxml2/xmlschemas.c \
    $$PWD/DependLibs/libxml2/xmlschemastypes.c \
    $$PWD/DependLibs/libxml2/xmlstring.c \
    $$PWD/DependLibs/libxml2/xmlunicode.c \
    $$PWD/DependLibs/libxml2/xmlwriter.c \
    $$PWD/DependLibs/libxml2/xpath.c \
    $$PWD/DependLibs/libxml2/xpointer.c

