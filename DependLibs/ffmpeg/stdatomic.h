#pragma once
#include "config_ffmpeg.h"

#ifdef TARGET_OS_WINDOWS
# include <atomics/win32/stdatomic.h>
#else
# include <atomics/gcc/stdatomic.h>
#endif // TARGET_OS_WINDOWS
