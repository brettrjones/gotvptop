/* getpid.c - Replacement for WindowsCE
   Copyright (C) 2010 Free Software Foundation, Inc.

   This file is free software; as a special exception the author gives
   unlimited permission to copy and/or distribute it, with or without
   modifications, as long as this notice is preserved.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY, to the extent permitted by law; without even
   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.  */

#include <libgnu/config_libgnu.h>

#ifdef TARGET_OS_WINDOWS
#include <sys/types.h>

pid_t
_gcry_getpid (void)
{
  return GetCurrentProcessId ();
}

#else
# error No replacement function for getpid known
#endif
