#pragma once

#include <GoTvDependLibrariesConfig.h>

#ifdef TARGET_OS_WINDOWS
# include <libpython/PC/pyconfig_windows.h>
#elif TARGET_OS_APPLE
# include <libpython/Include/pymacconfig.h>
#else
# include <libpython/pyconfig_notwindows.h>
#endif //


