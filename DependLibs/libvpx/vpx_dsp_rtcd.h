#pragma once

#ifdef TARGET_OS_WINDOWS
# include "vpx_dsp_rtcd_win.h"
#else
# include "vpx_dsp_rtcd_linux.h"
#endif // TARGET_OS_WINDOWS