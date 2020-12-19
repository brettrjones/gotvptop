
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

SOURCES += 	\
    $$PWD/DependLibs/libxml2/tree_xml2.c \
    $$PWD/DependLibs/libxml2/error_xml2.c \
    $$PWD/DependLibs/libxml2/list_xml2.c \
    $$PWD/DependLibs/libxml2/threads_xml2.c \
    $$PWD/DependLibs/libxml2/hash_xml2.c \
    $$PWD/DependLibs/libxml2/dict_xml2.c \
    $$PWD/DependLibs/libxml2/c14n_xml2.c \
    $$PWD/DependLibs/libxml2/catalog_xml2.c \
    $$PWD/DependLibs/libxml2/chvalid_xml2.c \
    $$PWD/DependLibs/libxml2/debugXML_xml2.c \
    $$PWD/DependLibs/libxml2/DOCBparser_xml2.c \
    $$PWD/DependLibs/libxml2/encoding_xml2.c \
    $$PWD/DependLibs/libxml2/entities_xml2.c \
    $$PWD/DependLibs/libxml2/globals_xml2.c \
    $$PWD/DependLibs/libxml2/HTMLparser_xml2.c \
    $$PWD/DependLibs/libxml2/HTMLtree_xml2.c \
    $$PWD/DependLibs/libxml2/legacy_xml2.c \
    $$PWD/DependLibs/libxml2/nanoftp_xml2.c \
    $$PWD/DependLibs/libxml2/nanohttp_xml2.c \
    $$PWD/DependLibs/libxml2/parser_xml2.c \
    $$PWD/DependLibs/libxml2/parserInternals_xml2.c \
    $$PWD/DependLibs/libxml2/pattern_xml2.c \
    $$PWD/DependLibs/libxml2/relaxng_xml2.c \
    $$PWD/DependLibs/libxml2/SAX_xml2.c \
    $$PWD/DependLibs/libxml2/SAX2_xml2.c \
    $$PWD/DependLibs/libxml2/schematron_xml2.c \
    $$PWD/DependLibs/libxml2/trio_xml2.c \
#    $$PWD/DependLibs/libxml2/trionan_xml2.c \
    $$PWD/DependLibs/libxml2/triostr_xml2.c \
    $$PWD/DependLibs/libxml2/uri_xml2.c \
    $$PWD/DependLibs/libxml2/valid_xml2.c \
    $$PWD/DependLibs/libxml2/xinclude_xml2.c \
    $$PWD/DependLibs/libxml2/xlink_xml2.c \
    $$PWD/DependLibs/libxml2/xmlIO_xml2.c \
#    $$PWD/DependLibs/libxml2/xmllint_xml2.c \
    $$PWD/DependLibs/libxml2/xmlmemory_xml2.c \
    $$PWD/DependLibs/libxml2/xmlmodule_xml2.c \
    $$PWD/DependLibs/libxml2/xmlreader_xml2.c \
    $$PWD/DependLibs/libxml2/xmlregexp_xml2.c \
    $$PWD/DependLibs/libxml2/xmlsave_xml2.c \
    $$PWD/DependLibs/libxml2/xmlschemas_xml2.c \
    $$PWD/DependLibs/libxml2/xmlschemastypes_xml2.c \
    $$PWD/DependLibs/libxml2/xmlstring_xml2.c \
    $$PWD/DependLibs/libxml2/xmlunicode_xml2.c \
    $$PWD/DependLibs/libxml2/xmlwriter_xml2.c \
    $$PWD/DependLibs/libxml2/xpath_xml2.c \
    $$PWD/DependLibs/libxml2/xpointer_xml2.c

