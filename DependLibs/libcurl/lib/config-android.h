#pragma  once
#include <GoTvDependLibrariesConfig.h>
#ifdef TARGET_OS_WINDOWS
# include <libcurl/lib/config-win32.h>
#else
# include <libcurl/lib/config-android.h>
#endif
