#pragma once

#ifdef TARGET_OS_WINDOWS
# include "vpx_scale_rtcd_win.h"
#else
# include "vpx_scale_rtcd_linux.h"
#endif // TARGET_OS_WINDOWS