#pragma once
#include <libvpx/config_libvpx.h>

#ifdef TARGET_OS_WINDOWS
# include <libvpx/vp9_rtcd.h>
#else
# include <libvpx/config/linux/generic/vp9_rtcd.h>
#endif // TARGET_OS_WINDOWS
