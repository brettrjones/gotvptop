/********************************************************************
 * Copyright(c) 2006-2009 Broadcom Corporation.
 *
 *  Name: bc_dts_types.h
 *
 *  Description: Data types
 *
 *  AU
 *
 *  HISTORY:
 *
 ********************************************************************
 * This header is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 2.1 of the License.
 *
 * This header is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this header.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************/

#ifndef __BC_DTS_TYPES_H__
#define __BC_DTS_TYPES_H__

#include <libcrystalhd/include/config_libcrystalhd.h>

#include <stdint.h>
#include <stdbool.h>

#ifndef PVOID
typedef void *PVOID;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef _MSC_VER
#ifndef ULONG
typedef uint32_t ULONG;
#endif

#ifndef LONG
typedef int32_t LONG;
#endif

#ifndef DWORD
typedef uint32_t DWORD;
#endif

#ifndef LPDWORD
typedef uint32_t *LPDWORD;
#endif

#endif // _MSC_VER

#ifndef HANDLE
typedef void * HANDLE;
#endif

#ifndef VOID
typedef void VOID;
#endif

#ifndef LPVOID
typedef void *LPVOID;
#endif



#ifndef UINT32
typedef uint32_t UINT32;
#endif

#ifndef PUCHAR
typedef unsigned char *PUCHAR;
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#endif /* __BC_DTS_TYPES_H__ */
