#pragma once

#include <GoTvDependLibrariesConfig.h>

#if defined(TARGET_OS_WINDOWS)
# include <libpython/PC/pyconfig_windows.h>
#elif defined(TARGET_OS_APPLE)
# include <libpython/Include/pymacconfig.h>
#elif defined(TARGET_OS_ANDROID)
# include <libpython/platform/android/pyconfig.h>
#elif defined(TARGET_OS_LINUX)
# include <libpython/platform/linux/pyconfig.h>
#endif //


