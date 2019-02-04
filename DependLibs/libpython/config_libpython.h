#pragma once

#include <GoTvDependLibrariesConfig.h>

#ifdef TARGET_OS_WINDOWS
# include <libpython/PC/pyconfig_windows.h>
#elif TARGET_OS_APPLE
# include <libpython/Include/pymacconfig.h>
#elif TARGET_OS_ANDROID
# include <libpython/platform/android/pyconfig.h>
#elif TARGET_OS_LINUX
# include <libpython/platform/linux/pyconfig.h>
#endif //


