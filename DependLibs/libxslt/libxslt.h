/*
 * Summary: internal header only used during the compilation of libxslt
 * Description: internal header only used during the compilation of libxslt
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */

#ifndef __XSLT_LIBXSLT_H__
#define __XSLT_LIBXSLT_H__

#include <libxslt/libxslt_config.h>

#if !defined LIBXSLT_PUBLIC
#if (defined (__CYGWIN__) || defined _MSC_VER) && !defined IN_LIBXSLT && !defined LIBXSLT_STATIC && !defined(LIB_STATIC)
#define LIBXSLT_PUBLIC __declspec(dllimport)
#else
#define LIBXSLT_PUBLIC
#endif // (defined (__CYGWIN__) || defined _MSC_VER) && !defined IN_LIBXSLT && !defined LIBXSLT_STATIC
#endif // !defined LIBXSLT_PUBLIC

#include <libxml2/xmlversion.h>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <direct.h>
#endif // _MSC_VER

#endif // __XSLT_LIBXSLT_H__ 
