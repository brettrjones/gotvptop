/*
 * Expat configuration for python. This file is not part of the expat
 * distribution.
 */
#ifndef EXPAT_CONFIG_H
#define EXPAT_CONFIG_H

#include <pyconfig.h>
#ifdef WORDS_BIGENDIAN
#define BYTEORDER 4321
#else
#define BYTEORDER 1234
#endif

#define XML_NS 1
#define XML_DTD 1
#define XML_CONTEXT_BYTES 1024

#if defined(TARGET_OS_ANDROID)
# define HAVE_GETRANDOM
#elif defined(TARGET_OS_LINUX)
# define HAVE_SYSCALL_GETRANDOM
#endif // TARGET_OS_ANDROID

#endif /* EXPAT_CONFIG_H */