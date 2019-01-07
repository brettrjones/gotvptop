#pragma once

#ifdef TARGET_OS_WINDOWS
#include "config_ffmpeg.h"
# include <atomics/win32/stdatomic.h>
#else
# include_next <stdatomic.h>
#endif // TARGET_OS_WINDOWS
