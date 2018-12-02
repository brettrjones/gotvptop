/* lib/fribidi-config.h.  Generated from fribidi-config.h.in by configure. */
/* Not copyrighted, in public domain. */
#ifndef FRIBIDI_CONFIG_H
#define FRIBIDI_CONFIG_H

#ifdef TARGET_OS_WINDOWS
#include "fribidi-config_windows.h"
#elif TARGET_OS_ANDROID
#include "fribidi-config_android.h"
#elif TARGET_OS_LINUX
#include "fribidi-config_linux.h"
#else
echo error no target os defined
#endif 


#endif /* FRIBIDI_CONFIG_H */
