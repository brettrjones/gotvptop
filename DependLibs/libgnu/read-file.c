/* read-file.c -- read file contents into a string
   Copyright (C) 2006, 2009-2016 Free Software Foundation, Inc.
   Written by Simon Josefsson and Bruno Haible.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.  */

#include <libgnu/config_libgnu.h>

#include "read-file.h"
   /* Get fstat.  */
#include <sys/stat.h>
/* Get ftello.  */
#include <stdio.h>
/* Get SIZE_MAX.  */
#include <stdint.h>
/* Get malloc, realloc, free. */
#include <stdlib.h>
/* Get errno. */
#include <errno.h>

//============================================================================
//! returns file size or 0 if does not exist
uint64_t GnuFileExists( const char * pFileName )
{
	int result;
#ifdef TARGET_OS_WINDOWS
	struct __stat64 gStat;
	// Get data associated with the file
	result = _stat64( pFileName , &gStat );
#else
	struct stat64 gStat;
	// Get data associated with the file
	result = stat64( pFileName, &gStat );
#endif //TARGET_OS_WINDOWS

	// Check if statistics are valid:
	if( result != 0 )
	{
		//error getting file info
		return 0;
	}
	else
	{
		//return file size
		return gStat.st_size;
	}
}

//============================================================================
//! return true if directory exists
bool GnuDirectoryExists( const char * pDir )
{
	char acBuf[ VX_MAX_PATH ];
	strcpy( acBuf, pDir );
	bool bIsDir = true;
	struct stat oFileStat;

	if( strlen( acBuf ) > 3 )
	{
		//if not root of drive remove the trailing backslash
		if( ( '/' == acBuf[ strlen( acBuf ) - 1 ] ) ||
			( '\\' == acBuf[ strlen( acBuf ) - 1 ] ) )
		{
			acBuf[ strlen( acBuf ) - 1 ] = 0;
		}
	}
	memset( &oFileStat, 0, sizeof( struct stat ) );
#ifdef TARGET_OS_WINDOWS
	oFileStat.st_mode = _S_IFDIR; //check for dir not file
	if( 0 == stat( acBuf, &oFileStat ) )
	{
		if( false == ( oFileStat.st_mode & _S_IFDIR ) )
		{
			//path is not valid directory
			bIsDir = false;
		}
	}
	else
	{
		bIsDir = false;
	}
#else // LINUX
	oFileStat.st_mode = S_IFDIR; //check for dir not file
	if( 0 == stat( acBuf, &oFileStat ) )
	{
		if( false == ( oFileStat.st_mode & S_IFDIR ) )
		{
			//path is not valid directory
			bIsDir = false;
		}
	}
	else
	{
		bIsDir = false;
	}
#endif // LINUX
	return bIsDir;
}

//============================================================================
uint64_t GnuGetFileLen( const char * pFileName )
{
	return GnuFileExists( pFileName );
}


/* Read a STREAM and return a newly allocated string with the content,
   and set *LENGTH to the length of the string.  The string is
   zero-terminated, but the terminating zero byte is not counted in
   *LENGTH.  On errors, *LENGTH is undefined, errno preserves the
   values set by system functions (if any), and NULL is returned.  */

char * fread_file( FILE *stream, uint64_t fileLen, size_t * retLengthRead )
{
	char *buf = NULL;
	uint64_t size = 0; // number of bytes read so far
	int save_errno;

	// For a regular file, allocate a buffer that has exactly the right
    //	size.  This avoids the need to do dynamic reallocations later.


	if( !( buf = malloc( fileLen ) ) )
	{
		return NULL; // errno is ENOMEM.
	}


	for( ;;)
	{
		// This reads 1 more than the size of a regular file
		//   so that we get eof immediately.
		size_t requested = fileLen - size;
		size_t count = fread( buf + size, 1, requested, stream );
		size += count;

		if( count != requested )
		{
			save_errno = errno;
			if( ferror( stream ) )
				break;

			// Shrink the allocated memory if possible.
			if( size < fileLen - 1 )
			{
				char *smaller_buf = realloc( buf, size + 1 );
				if( smaller_buf != NULL )
					buf = smaller_buf;
			}

			buf[ size ] = '\0';
			*retLengthRead = size;
			return buf;
		}
	}

	free( buf );
	errno = save_errno;
	return NULL;
}

//============================================================================
static char * _gnutls_internal_read_file( const char *filename, size_t * length, const char *mode )
{
	uint64_t fileLen = GnuGetFileLen( filename );
	if( 0 == fileLen )
	{
		return 0;
	}

	FILE *stream = fopen( filename, mode );
	char *out;
	int save_errno;

	if( !stream )
		return NULL;

	out = fread_file( stream, fileLen, length );

	save_errno = errno;

	if( fclose( stream ) != 0 )
	{
		if( out )
		{
			save_errno = errno;
			free( out );
		}

		errno = save_errno;
		return NULL;
	}

	return out;
}

/* Open and read the contents of FILENAME, and return a newly
   allocated string with the content, and set *LENGTH to the length of
   the string.  The string is zero-terminated, but the terminating
   zero byte is not counted in *LENGTH.  On errors, *LENGTH is
   undefined, errno preserves the values set by system functions (if
   any), and NULL is returned.  */
char * _gnutls_read_file( const char *filename, size_t *length )
{
	return _gnutls_internal_read_file( filename, length, "r" );
}

/* Open (on non-POSIX systems, in binary mode) and read the contents
   of FILENAME, and return a newly allocated string with the content,
   and set LENGTH to the length of the string.  The string is
   zero-terminated, but the terminating zero byte is not counted in
   the LENGTH variable.  On errors, *LENGTH is undefined, errno
   preserves the values set by system functions (if any), and NULL is
   returned.  */
char *
_gnutls_read_binary_file( const char *filename, size_t *length )
{
	return _gnutls_internal_read_file( filename, length, "rb" );
}
