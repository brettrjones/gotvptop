#pragma once

#include "config_ffmpeg.h"
#ifdef TARGET_OS_WINDOWS
# include <atomics/win32/stdatomic.h>
#else
# include_next <stdatomic.h>
#endif // TARGET_OS_WINDOWS
