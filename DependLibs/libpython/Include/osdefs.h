#ifndef Py_OSDEFS_H
#define Py_OSDEFS_H
#include <GoTvDependLibrariesConfig.h>
#ifdef __cplusplus
extern "C" {
#endif


/* Operating system dependencies */

/* Mod by chrish: QNX has WATCOM, but isn't DOS */
#if !defined(__QNX__)
# if defined(TARGET_OS_WINDOWS) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__DJGPP__) || defined(PYOS_OS2)
#  if  defined(TARGET_OS_WINDOWS) || ( defined(PYOS_OS2) && defined(PYCC_GCC) )
#   ifdef _MSC_VER
#    define MAXPATHLEN MAX_PATH
#   else
#    define MAXPATHLEN 260
#   endif // _MSC_VER
#  else
#   define MAXPATHLEN 256
#  endif
#   define DELIM ';'
# endif
#endif // !defined(__QNX__)

#ifdef RISCOS
#define SEP '.'
#define MAXPATHLEN 256
#define DELIM ','
#endif


/* Filename separator */
#if defined(TARGET_OS_WINDOWS)
# define SEP '\\'
# define ALTSEP '/'
#else
# ifndef SEP
#  define SEP '/'
# endif // ifndef SEP
#endif // defined(TARGET_OS_WINDOWS)

/* Max pathname length */
#ifdef __hpux
#include <sys/param.h>
#include <limits.h>
#ifndef PATH_MAX
#define PATH_MAX MAXPATHLEN
#endif
#endif

#ifndef MAXPATHLEN
#if defined(PATH_MAX) && PATH_MAX > 1024
#define MAXPATHLEN PATH_MAX
#else
#define MAXPATHLEN 1024
#endif
#endif

/* Search path entry delimiter */
#ifndef DELIM
#define DELIM ':'
#endif

#ifdef __cplusplus
}
#endif
#endif /* !Py_OSDEFS_H */
