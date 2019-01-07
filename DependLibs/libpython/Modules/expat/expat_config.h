/*
 * Expat configuration for python. This file is not part of the expat
 * distribution.
 */
#ifndef EXPAT_CONFIG_H
#define EXPAT_CONFIG_H

#include <pyconfig.h>
#if GOTV_ARCH_BIGENDIAN
# define WORDS_BIGENDIAN 1
# define BYTEORDER 4321
#else
# undef WORDS_BIGENDIAN
# define BYTEORDER 1234
#endif

#define XML_NS 1
#define XML_DTD 1
#define XML_CONTEXT_BYTES 1024

#endif /* EXPAT_CONFIG_H */
