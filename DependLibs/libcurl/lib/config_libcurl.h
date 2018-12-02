
#pragma once
#include <GoTvDependLibrariesConfig.h>

#define HAVE_ZLIB_H 1
#define USE_OPENSSL 1
#define CURL_STATICLIB 1

#ifdef TARGET_OS_WINDOWS
# include <libcurl/lib/config-win32.h>
#else
# include <libcurl/lib/config-android.h>
#endif // TARGET_OS_WINDOWS
