#pragma once
#include <GoTvDependLibrariesConfig.h>

#ifdef _MSC_VER
# include <wchar.h>
# include <sys/utime.h>
struct utimbuf
{
	time_t  actime;  /* access time (unused on FAT filesystems) */
	time_t  modtime; /* modification time */
};

#else
# include_next <utime.h>
#endif // _MSC_VER

