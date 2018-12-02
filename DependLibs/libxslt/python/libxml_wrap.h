#include <Python-2.7.10/Include/Python.h>
#include <libxml2/tree.h>
#include <libxml2/parser.h>
#include <libxml2/parserInternals.h>
#include <libxml2/catalog.h>
#include <libxml2/threads.h>
#include <libxml2/nanoftp.h>
#include <libxml2/nanohttp.h>
#include <libxml2/uri.h>
#include <libxml2/xpath.h>
#include <libxml2/xpathInternals.h>
#include <libxml2/debugXML.h>
#include <libxml2/HTMLparser.h>
#include <libxml2/HTMLtree.h>
#include <libxml2/xinclude.h>
#include <libxml2/xpointer.h>

#define PyxmlNode_Get(v) (((v) == Py_None) ? NULL : \
	(((PyxmlNode_Object *)(v))->obj))

typedef struct {
    PyObject_HEAD
    xmlNodePtr obj;
} PyxmlNode_Object;

#define PyxmlXPathContext_Get(v) (((v) == Py_None) ? NULL : \
	(((PyxmlXPathContext_Object *)(v))->obj))

typedef struct {
    PyObject_HEAD
    xmlXPathContextPtr obj;
} PyxmlXPathContext_Object;

#define PyxmlXPathParserContext_Get(v) (((v) == Py_None) ? NULL : \
	(((PyxmlXPathParserContext_Object *)(v))->obj))

typedef struct {
    PyObject_HEAD
    xmlXPathParserContextPtr obj;
} PyxmlXPathParserContext_Object;

#define PyparserCtxt_Get(v) (((v) == Py_None) ? NULL : \
        (((PyparserCtxt_Object *)(v))->obj))

typedef struct {
    PyObject_HEAD
    xmlParserCtxtPtr obj;
} PyparserCtxt_Object;

#define Pycatalog_Get(v) (((v) == Py_None) ? NULL : \
        (((Pycatalog_Object *)(v))->obj))

typedef struct {
    PyObject_HEAD
    xmlCatalogPtr obj;
} Pycatalog_Object;

#define PyFile_Get(v) (((v) == Py_None) ? NULL : \
	(PyFile_Check(v) ? (PyFile_AsFile(v)) : stdout))

PyObject * libxml_intWrap(int val);
PyObject * libxml_longWrap(long val);
PyObject * libxml_xmlCharPtrWrap(xmlChar *str);
PyObject * libxml_constxmlCharPtrWrap(const xmlChar *str);
PyObject * libxml_charPtrWrap(char *str);
PyObject * libxml_constcharPtrWrap(const char *str);
PyObject * libxml_charPtrConstWrap(const char *str);
PyObject * libxml_xmlCharPtrConstWrap(const xmlChar *str);
PyObject * libxml_xmlDocPtrWrap(xmlDocPtr doc);
PyObject * libxml_xmlNodePtrWrap(xmlNodePtr node);
PyObject * libxml_xmlAttrPtrWrap(xmlAttrPtr attr);
PyObject * libxml_xmlNsPtrWrap(xmlNsPtr ns);
PyObject * libxml_xmlAttributePtrWrap(xmlAttributePtr ns);
PyObject * libxml_xmlElementPtrWrap(xmlElementPtr ns);
PyObject * libxml_doubleWrap(double val);
PyObject * libxml_xmlXPathContextPtrWrap(xmlXPathContextPtr ctxt);
PyObject * libxml_xmlParserCtxtPtrWrap(xmlParserCtxtPtr ctxt);
PyObject * libxml_xmlXPathParserContextPtrWrap(xmlXPathParserContextPtr ctxt);
PyObject * libxml_xmlXPathObjectPtrWrap(xmlXPathObjectPtr obj);
PyObject * libxml_xmlCatalogPtrWrap(xmlCatalogPtr obj);
PyObject * libxml_xmlURIPtrWrap(xmlURIPtr uri);
PyObject * libxml_xmlOutputBufferPtrWrap(xmlOutputBufferPtr buffer);
PyObject * libxml_xmlParserInputBufferPtrWrap(xmlParserInputBufferPtr buffer);
PyObject * libxml_xmlRegexpPtrWrap(xmlRegexpPtr regexp);

xmlXPathObjectPtr libxml_xmlXPathObjectPtrConvert(PyObject * obj);
