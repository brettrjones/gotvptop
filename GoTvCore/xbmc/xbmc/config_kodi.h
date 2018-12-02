/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once
#include <config_gotvcore.h>


#ifdef TARGET_OS_LINUX
# include <xbmc/linux/PlatformInclude.h>
#endif // TARGET_OS_LINUX

#if defined(TARGET_POSIX)
# include <time.h>
# include <sys/time.h>
# include <sys/types.h>
# include <errno.h>
#endif

//#if defined(TARGET_OS_ANDROID)
//# undef HAS_LINUX_EVENTS
//# undef HAS_LIRC
//#endif


#ifdef HAS_DVD_DRIVE
# define HAS_CDDA_RIPPER
#endif


// Useful pixel colour manipulation macros
#define GET_A(color)            ((color >> 24) & 0xFF)
#define GET_R(color)            ((color >> 16) & 0xFF)
#define GET_G(color)            ((color >>  8) & 0xFF)
#define GET_B(color)            ((color >>  0) & 0xFF)


#ifdef TARGET_OS_WINDOWS
//# include <platform/win32/PlatformDefs.h> already included 
#elif defined(TARGET_OS_ANDROID)
# include <platform/overrides/android/PlatformAndroid.h>
#elif defined(TARGET_OS_LINUX)
# include <platform/linux/PlatformDefs.h>
#elif defined(TARGET_OS_APPLE)
echo error APPLE os is not supported
#endif
