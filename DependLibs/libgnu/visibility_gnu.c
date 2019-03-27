/* visibility.c - Wrapper for all public functions.
 * Copyright (C) 2007, 2008, 2011  Free Software Foundation, Inc.
 * Copyright (C) 2013  g10 Code GmbH
 *
 * This file is part of Libgcrypt.
 *
 * Libgcrypt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Libgcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <libgnu/config_libgnu.h>
#include <CoreLib/VxDebug.h>

#ifdef _MSC_VER
# include <mbstring.h>
#endif // _MSC_VER

#include <stdarg.h>

#define _GCRY_INCLUDED_BY_VISIBILITY_C
#include "g10lib.h"
#include "cipher-proto.h"
#include "context.h"
#include "mpi.h"
#include "gpgrt-int.h"
const char *
gpg_strerror( gpg_error_t err )
{
	return _gpg_strerror( err );
}

int
gpg_strerror_r( gpg_error_t err, char *buf, size_t buflen )
{
	return _gpg_strerror_r( err, buf, buflen );
}

const char *
gpg_strsource( gpg_error_t err )
{
	return _gpg_strsource( err );
}

gpg_err_code_t
gpg_err_code_from_errno( int err )
{
	return _gpg_err_code_from_errno( err );
}

int
gpg_err_code_to_errno( gpg_err_code_t code )
{
	return _gpg_err_code_to_errno( code );
}

gpg_err_code_t
gpg_err_code_from_syserror( void )
{
	return _gpg_err_code_from_syserror();
}

void
gpg_err_set_errno( int err )
{
	_gpg_err_set_errno( err );
}


gpg_error_t
gpg_err_init( void )
{
	return _gpg_err_init();
}

void
gpg_err_deinit( int mode )
{
	_gpg_err_deinit( mode );
}

const char *
gpg_error_check_version( const char *req_version )
{
	return _gpg_error_check_version( req_version );
}

const char *
gpgrt_check_version( const char *req_version )
{
	return _gpg_error_check_version( req_version );
}

void
gpgrt_set_syscall_clamp( void( *pre )( void ), void( *post )( void ) )
{
	_gpgrt_set_syscall_clamp( pre, post );
}

void
gpgrt_set_alloc_func( void *( *f )( void *a, size_t n ) )
{
	_gpgrt_set_alloc_func( f );
}


gpg_err_code_t
gpgrt_lock_gnu_init( gpgrt_lock_gnu_t *lockhd )
{
	return _gpgrt_lock_gnu_init( lockhd );
}

gpg_err_code_t
gpgrt_lock_gnu_lock( gpgrt_lock_gnu_t *lockhd )
{
	return _gpgrt_lock_gnu_lock( lockhd );
}

gpg_err_code_t
gpgrt_lock_gnu_trylock( gpgrt_lock_gnu_t *lockhd )
{
	return _gpgrt_lock_gnu_trylock( lockhd );
}

gpg_err_code_t
gpgrt_lock_gnu_unlock( gpgrt_lock_gnu_t *lockhd )
{
	return _gpgrt_lock_gnu_unlock( lockhd );
}

gpg_err_code_t
gpgrt_lock_gnu_destroy( gpgrt_lock_gnu_t *lockhd )
{
	return _gpgrt_lock_gnu_destroy( lockhd );
}

gpg_err_code_t
gpgrt_yield( void )
{
	return _gpgrt_yield();
}



estream_t
gpgrt_fopen( const char *_GPGRT__RESTRICT path,
			 const char *_GPGRT__RESTRICT mode )
{
	return _gpgrt_fopen( path, mode );
}

estream_t
gpgrt_mopen( void *_GPGRT__RESTRICT data, size_t data_n, size_t data_len,
			 unsigned int grow,
			 void *( *func_realloc ) ( void *mem, size_t size ),
			 void( *func_free ) ( void *mem ),
			 const char *_GPGRT__RESTRICT mode )
{
	return _gpgrt_mopen( data, data_n, data_len, grow, func_realloc, func_free,
						 mode );
}

estream_t
gpgrt_fopenmem( size_t memlimit, const char *_GPGRT__RESTRICT mode )
{
	return _gpgrt_fopenmem( memlimit, mode );
}

estream_t
gpgrt_fopenmem_init( size_t memlimit, const char *_GPGRT__RESTRICT mode,
					 const void *data, size_t datalen )
{
	return _gpgrt_fopenmem_init( memlimit, mode, data, datalen );
}

estream_t
gpgrt_fdopen( int filedes, const char *mode )
{
	return _gpgrt_fdopen( filedes, mode );
}

estream_t
gpgrt_fdopen_nc( int filedes, const char *mode )
{
	return _gpgrt_fdopen_nc( filedes, mode );
}

estream_t
gpgrt_sysopen( es_syshd_t *syshd, const char *mode )
{
	return _gpgrt_sysopen( syshd, mode );
}

estream_t
gpgrt_sysopen_nc( es_syshd_t *syshd, const char *mode )
{
	return _gpgrt_sysopen_nc( syshd, mode );
}

estream_t
gpgrt_fpopen( FILE *fp, const char *mode )
{
	return _gpgrt_fpopen( fp, mode );
}

estream_t
gpgrt_fpopen_nc( FILE *fp, const char *mode )
{
	return _gpgrt_fpopen_nc( fp, mode );
}

estream_t
gpgrt_freopen( const char *_GPGRT__RESTRICT path,
			   const char *_GPGRT__RESTRICT mode,
			   estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_freopen( path, mode, stream );
}

estream_t
gpgrt_fopencookie( void *_GPGRT__RESTRICT cookie,
				   const char *_GPGRT__RESTRICT mode,
				   gpgrt_cookie_io_functions_t functions )
{
	return _gpgrt_fopencookie( cookie, mode, functions );
}

int
gpgrt_fclose( estream_t stream )
{
	return _gpgrt_fclose( stream );
}

int
gpgrt_fclose_snatch( estream_t stream, void **r_buffer, size_t *r_buflen )
{
	return _gpgrt_fclose_snatch( stream, r_buffer, r_buflen );
}

int
gpgrt_onclose( estream_t stream, int mode,
			   void( *fnc ) ( estream_t, void* ), void *fnc_value )
{
	return _gpgrt_onclose( stream, mode, fnc, fnc_value );
}

int
gpgrt_fileno( estream_t stream )
{
	return _gpgrt_fileno( stream );
}

int
gpgrt_fileno_unlocked( estream_t stream )
{
	return _gpgrt_fileno_unlocked( stream );
}

int
gpgrt_syshd( estream_t stream, es_syshd_t *syshd )
{
	return _gpgrt_syshd( stream, syshd );
}

int
gpgrt_syshd_unlocked( estream_t stream, es_syshd_t *syshd )
{
	return _gpgrt_syshd_unlocked( stream, syshd );
}

void
_gpgrt_set_std_fd( int no, int fd )
{
	_gpgrt__set_std_fd( no, fd );  /* (double dash in name) */
}

estream_t
_gpgrt_get_std_stream( int fd )
{
	return _gpgrt__get_std_stream( fd );  /* (double dash in name) */
}

void
gpgrt_flockfile( estream_t stream )
{
	_gpgrt_flockfile( stream );
}

int
gpgrt_ftrylockfile( estream_t stream )
{
	return _gpgrt_ftrylockfile( stream );
}

void
gpgrt_funlockfile( estream_t stream )
{
	_gpgrt_funlockfile( stream );
}

int
_gpgrt_pending( estream_t stream )
{
	return _gpgrt__pending( stream );
}

int
_gpgrt_pending_unlocked( estream_t stream )
{
	return _gpgrt__pending_unlocked( stream );
}

int
gpgrt_feof( estream_t stream )
{
	return _gpgrt_feof( stream );
}

int
gpgrt_feof_unlocked( estream_t stream )
{
	return _gpgrt_feof_unlocked( stream );
}

int
gpgrt_ferror( estream_t stream )
{
	return _gpgrt_ferror( stream );
}

int
gpgrt_ferror_unlocked( estream_t stream )
{
	return _gpgrt_ferror_unlocked( stream );
}

void
gpgrt_clearerr( estream_t stream )
{
	_gpgrt_clearerr( stream );
}

void
gpgrt_clearerr_unlocked( estream_t stream )
{
	_gpgrt_clearerr_unlocked( stream );
}

int
gpgrt_fflush( estream_t stream )
{
	return _gpgrt_fflush( stream );
}

int
gpgrt_fseek( estream_t stream, long int offset, int whence )
{
	return _gpgrt_fseek( stream, offset, whence );
}

int
gpgrt_fseeko( estream_t stream, gpgrt_off_t offset, int whence )
{
	return _gpgrt_fseeko( stream, offset, whence );
}

long int
gpgrt_ftell( estream_t stream )
{
	return _gpgrt_ftell( stream );
}

gpgrt_off_t
gpgrt_ftello( estream_t stream )
{
	return _gpgrt_ftello( stream );
}

void
gpgrt_rewind( estream_t stream )
{
	_gpgrt_rewind( stream );
}

int
gpgrt_fgetc( estream_t stream )
{
	return _gpgrt_fgetc( stream );
}

int
_gpgrt_getc_underflow( estream_t stream )
{
	return _gpgrt__getc_underflow( stream );
}

int
gpgrt_fputc( int c, estream_t stream )
{
	return _gpgrt_fputc( c, stream );
}

int
_gpgrt_putc_overflow( int c, estream_t stream )
{
	return _gpgrt__putc_overflow( c, stream );
}

int
gpgrt_ungetc( int c, estream_t stream )
{
	return _gpgrt_ungetc( c, stream );
}

int
gpgrt_read( estream_t _GPGRT__RESTRICT stream,
			void *_GPGRT__RESTRICT buffer, size_t bytes_to_read,
			size_t *_GPGRT__RESTRICT bytes_read )
{
	return _gpgrt_read( stream, buffer, bytes_to_read, bytes_read );
}

int
gpgrt_write( estream_t _GPGRT__RESTRICT stream,
			 const void *_GPGRT__RESTRICT buffer, size_t bytes_to_write,
			 size_t *_GPGRT__RESTRICT bytes_written )
{
	return _gpgrt_write( stream, buffer, bytes_to_write, bytes_written );
}

int
gpgrt_write_sanitized( estream_t _GPGRT__RESTRICT stream,
					   const void * _GPGRT__RESTRICT buffer, size_t length,
					   const char * delimiters,
					   size_t * _GPGRT__RESTRICT bytes_written )
{
	return _gpgrt_write_sanitized( stream, buffer, length, delimiters,
								   bytes_written );
}

int
gpgrt_write_hexstring( estream_t _GPGRT__RESTRICT stream,
					   const void *_GPGRT__RESTRICT buffer, size_t length,
					   int reserved, size_t *_GPGRT__RESTRICT bytes_written )
{
	return _gpgrt_write_hexstring( stream, buffer, length, reserved,
								   bytes_written );
}

size_t
gpgrt_fread( void *_GPGRT__RESTRICT ptr, size_t size, size_t nitems,
			 estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_fread( ptr, size, nitems, stream );
}

size_t
gpgrt_fwrite( const void *_GPGRT__RESTRICT ptr, size_t size, size_t nitems,
			  estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_fwrite( ptr, size, nitems, stream );
}

char *
gpgrt_fgets( char *_GPGRT__RESTRICT buffer, int length,
			 estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_fgets( buffer, length, stream );
}

int
gpgrt_fputs( const char *_GPGRT__RESTRICT s, estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_fputs( s, stream );
}

int
gpgrt_fputs_unlocked( const char *_GPGRT__RESTRICT s,
					  estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_fputs_unlocked( s, stream );
}

gpgrt_ssize_t
gpgrt_getline( char *_GPGRT__RESTRICT *_GPGRT__RESTRICT lineptr,
			   size_t *_GPGRT__RESTRICT n, estream_t _GPGRT__RESTRICT stream )
{
	return _gpgrt_getline( lineptr, n, stream );
}

gpgrt_ssize_t
gpgrt_read_line( estream_t stream,
				 char **addr_of_buffer, size_t *length_of_buffer,
				 size_t *max_length )
{
	return _gpgrt_read_line( stream, addr_of_buffer, length_of_buffer,
							 max_length );
}

void
gpgrt_free( void *a )
{
	if( a )
		_gpgrt_free( a );
}

int
gpgrt_vfprintf( estream_t _GPGRT__RESTRICT stream,
				const char *_GPGRT__RESTRICT format,
				va_list ap )
{
	return _gpgrt_vfprintf( stream, format, ap );
}

int
gpgrt_vfprintf_unlocked( estream_t _GPGRT__RESTRICT stream,
						 const char *_GPGRT__RESTRICT format,
						 va_list ap )
{
	return _gpgrt_vfprintf_unlocked( stream, format, ap );
}

int
gpgrt_printf( const char *_GPGRT__RESTRICT format, ... )
{
	va_list ap;
	int rc;

	va_start( ap, format );
	rc = _gpgrt_vfprintf( es_stdout, format, ap );
	va_end( ap );

	return rc;
}

int
gpgrt_printf_unlocked( const char *_GPGRT__RESTRICT format, ... )
{
	va_list ap;
	int rc;

	va_start( ap, format );
	rc = _gpgrt_vfprintf_unlocked( es_stdout, format, ap );
	va_end( ap );

	return rc;
}

int
gpgrt_fprintf( estream_t _GPGRT__RESTRICT stream,
			   const char *_GPGRT__RESTRICT format, ... )
{
	va_list ap;
	int rc;

	va_start( ap, format );
	rc = _gpgrt_vfprintf( stream, format, ap );
	va_end( ap );

	return rc;
}

int
gpgrt_fprintf_unlocked( estream_t _GPGRT__RESTRICT stream,
						const char *_GPGRT__RESTRICT format, ... )
{
	va_list ap;
	int rc;

	va_start( ap, format );
	rc = _gpgrt_vfprintf_unlocked( stream, format, ap );
	va_end( ap );

	return rc;
}

int
gpgrt_setvbuf( estream_t _GPGRT__RESTRICT stream,
			   char *_GPGRT__RESTRICT buf, int type, size_t size )
{
	return _gpgrt_setvbuf( stream, buf, type, size );
}

void
gpgrt_setbuf( estream_t _GPGRT__RESTRICT stream, char *_GPGRT__RESTRICT buf )
{
	_gpgrt_setvbuf( stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ );
}

void
gpgrt_set_binary( estream_t stream )
{
	_gpgrt_set_binary( stream );
}

estream_t
gpgrt_tmpfile( void )
{
	return _gpgrt_tmpfile();
}

void
gpgrt_opaque_set( estream_t stream, void *opaque )
{
	_gpgrt_opaque_set( stream, opaque );
}

void *
gpgrt_opaque_get( estream_t stream )
{
	return _gpgrt_opaque_get( stream );
}

void
gpgrt_fname_set( estream_t stream, const char *fname )
{
	_gpgrt_fname_set( stream, fname );
}

const char *
gpgrt_fname_get( estream_t stream )
{
	return _gpgrt_fname_get( stream );
}

int
gpgrt_asprintf( char **r_buf, const char *_GPGRT__RESTRICT format, ... )
{
	va_list ap;
	int rc;

	va_start( ap, format );
	rc = _gpgrt_estream_vasprintf( r_buf, format, ap );
	va_end( ap );

	return rc;
}

int
gpgrt_vasprintf( char **r_buf, const char *_GPGRT__RESTRICT format, va_list ap )
{
	return _gpgrt_estream_vasprintf( r_buf, format, ap );
}

char *
gpgrt_bsprintf( const char *_GPGRT__RESTRICT format, ... )
{
	int rc;
	va_list ap;
	char *buf;

	va_start( ap, format );
	rc = _gpgrt_estream_vasprintf( &buf, format, ap );
	va_end( ap );
	if( rc < 0 )
		return NULL;
	return buf;
}

char *
gpgrt_vbsprintf( const char *_GPGRT__RESTRICT format, va_list ap )
{
	int rc;
	char *buf;

	rc = _gpgrt_estream_vasprintf( &buf, format, ap );
	if( rc < 0 )
		return NULL;
	return buf;
}

int
gpgrt_snprintf( char *buf, size_t bufsize, const char *format, ... )
{
	int rc;
	va_list arg_ptr;

	va_start( arg_ptr, format );
	rc = _gpgrt_estream_vsnprintf( buf, bufsize, format, arg_ptr );
	va_end( arg_ptr );

	return rc;
}

int
gpgrt_vsnprintf( char *buf, size_t bufsize,
				 const char *format, va_list arg_ptr )
{
	return _gpgrt_estream_vsnprintf( buf, bufsize, format, arg_ptr );
}

const char *
gcry_strerror( gcry_error_t err )
{
	return _gcry_strerror( err );
}

const char *
gcry_strsource( gcry_error_t err )
{
	return _gcry_strsource( err );
}

gcry_err_code_t
gcry_err_code_from_errno( int err )
{
	return _gcry_err_code_from_errno( err );
}

int
gcry_err_code_to_errno( gcry_err_code_t code )
{
	return _gcry_err_code_to_errno( code );
}

gcry_error_t
gcry_err_make_from_errno( gcry_err_source_t source, int err )
{
	return _gcry_err_make_from_errno( source, err );
}

gcry_err_code_t
gcry_error_from_errno( int err )
{
	return _gcry_error_from_errno( err );
}

const char *
gcry_check_version( const char *req_version )
{
	return _gcry_check_version( req_version );
}

gcry_error_t
gcry_control( enum gcry_ctl_cmds cmd, ... )
{
	gcry_error_t err;
	va_list arg_ptr;

	va_start( arg_ptr, cmd );
	err = gpg_error( _gcry_vcontrol( cmd, arg_ptr ) );
	va_end( arg_ptr );
	return err;
}

gcry_error_t
gcry_sexp_new( gcry_sexp_t *retsexp,
			   const void *buffer, size_t length,
			   int autodetect )
{
	return gpg_error( _gcry_sexp_new( retsexp, buffer, length, autodetect ) );
}

gcry_error_t
gcry_sexp_create( gcry_sexp_t *retsexp,
				  void *buffer, size_t length,
				  int autodetect, void( *freefnc ) ( void * ) )
{
	return gpg_error( _gcry_sexp_create( retsexp, buffer, length,
										 autodetect, freefnc ) );
}

gcry_error_t
gcry_sexp_sscan( gcry_sexp_t *retsexp, size_t *erroff,
				 const char *buffer, size_t length )
{
	return gpg_error( _gcry_sexp_sscan( retsexp, erroff, buffer, length ) );
}

gcry_error_t
gcry_sexp_build( gcry_sexp_t *retsexp, size_t *erroff,
				 const char *format, ... )
{
	gcry_err_code_t rc;
	va_list arg_ptr;

	va_start( arg_ptr, format );
	rc = _gcry_sexp_vbuild( retsexp, erroff, format, arg_ptr );
	va_end( arg_ptr );
	return gpg_error( rc );
}

gcry_error_t
gcry_sexp_build_array( gcry_sexp_t *retsexp, size_t *erroff,
					   const char *format, void **arg_list )
{
	return gpg_error( _gcry_sexp_build_array( retsexp, erroff, format, arg_list ) );
}

void
gcry_sexp_release( gcry_sexp_t sexp )
{
	_gcry_sexp_release( sexp );
}

size_t
gcry_sexp_canon_len( const unsigned char *buffer, size_t length,
					 size_t *erroff, gcry_error_t *errcode )
{
	size_t n;
	gpg_err_code_t rc;

	n = _gcry_sexp_canon_len( buffer, length, erroff, &rc );
	if( errcode )
		*errcode = gpg_error( rc );
	return n;
}

size_t
gcry_sexp_sprint( gcry_sexp_t sexp, int mode, void *buffer, size_t maxlength )
{
	return _gcry_sexp_sprint( sexp, mode, buffer, maxlength );
}

void
gcry_sexp_dump( const gcry_sexp_t a )
{
	_gcry_sexp_dump( a );
}

gcry_sexp_t
gcry_sexp_cons( const gcry_sexp_t a, const gcry_sexp_t b )
{
	return _gcry_sexp_cons( a, b );
}

gcry_sexp_t
gcry_sexp_alist( const gcry_sexp_t *array )
{
	return _gcry_sexp_alist( array );
}

gcry_sexp_t
gcry_sexp_vlist( const gcry_sexp_t a, ... )
{
	/* This is not yet implemented in sexp.c.  */
	( void )a;
	BUG();
	return NULL;
}

gcry_sexp_t
gcry_sexp_append( const gcry_sexp_t a, const gcry_sexp_t n )
{
	return _gcry_sexp_append( a, n );
}

gcry_sexp_t
gcry_sexp_prepend( const gcry_sexp_t a, const gcry_sexp_t n )
{
	return _gcry_sexp_prepend( a, n );
}


gcry_sexp_t
gcry_sexp_find_token( gcry_sexp_t list, const char *tok, size_t toklen )
{
	return _gcry_sexp_find_token( list, tok, toklen );
}

int
gcry_sexp_length( const gcry_sexp_t list )
{
	return _gcry_sexp_length( list );
}

gcry_sexp_t
gcry_sexp_nth( const gcry_sexp_t list, int number )
{
	return _gcry_sexp_nth( list, number );
}

gcry_sexp_t
gcry_sexp_car( const gcry_sexp_t list )
{
	return _gcry_sexp_car( list );
}

gcry_sexp_t
gcry_sexp_cdr( const gcry_sexp_t list )
{
	return _gcry_sexp_cdr( list );
}

gcry_sexp_t
gcry_sexp_cadr( const gcry_sexp_t list )
{
	return _gcry_sexp_cadr( list );
}

const char *
gcry_sexp_nth_data( const gcry_sexp_t list, int number, size_t *datalen )
{
	return _gcry_sexp_nth_data( list, number, datalen );
}

void *
gcry_sexp_nth_buffer( const gcry_sexp_t list, int number, size_t *rlength )
{
	return _gcry_sexp_nth_buffer( list, number, rlength );
}

char *
gcry_sexp_nth_string( gcry_sexp_t list, int number )
{
	return _gcry_sexp_nth_string( list, number );
}

gcry_mpi_t
gcry_sexp_nth_mpi( gcry_sexp_t list, int number, int mpifmt )
{
	return _gcry_sexp_nth_mpi( list, number, mpifmt );
}

gpg_error_t
gcry_sexp_extract_param( gcry_sexp_t sexp, const char *path,
						 const char *list, ... )
{
	gcry_err_code_t rc;
	va_list arg_ptr;

	va_start( arg_ptr, list );
	rc = _gcry_sexp_vextract_param( sexp, path, list, arg_ptr );
	va_end( arg_ptr );
	return gpg_error( rc );
}



gcry_mpi_t
gcry_mpi_new( unsigned int nbits )
{
	return _gcry_mpi_new( nbits );
}

gcry_mpi_t
gcry_mpi_snew( unsigned int nbits )
{
	return _gcry_mpi_snew( nbits );
}

void
gcry_mpi_release( gcry_mpi_t a )
{
	_gcry_mpi_release( a );
}

gcry_mpi_t
gcry_mpi_copy( const gcry_mpi_t a )
{
	return _gcry_mpi_copy( a );
}

void gcry_mpi_snatch( gcry_mpi_t w, const gcry_mpi_t u )
{
	_gcry_mpi_snatch( w, u );
}

gcry_mpi_t
gcry_mpi_set( gcry_mpi_t w, const gcry_mpi_t u )
{
	return _gcry_mpi_set( w, u );
}

gcry_mpi_t
gcry_mpi_set_ui( gcry_mpi_t w, unsigned long u )
{
	return _gcry_mpi_set_ui( w, u );
}

gcry_error_t
gcry_mpi_get_ui( gcry_mpi_t w, unsigned long *u )
{
	return gpg_error( _gcry_mpi_get_ui( w, u ) );
}

void
gcry_mpi_swap( gcry_mpi_t a, gcry_mpi_t b )
{
	_gcry_mpi_swap( a, b );
}

int
gcry_mpi_is_neg( gcry_mpi_t a )
{
	return _gcry_mpi_is_neg( a );
}

void
gcry_mpi_neg( gcry_mpi_t w, gcry_mpi_t u )
{
	_gcry_mpi_neg( w, u );
}

void
gcry_mpi_abs( gcry_mpi_t w )
{
	_gcry_mpi_abs( w );
}

int
gcry_mpi_cmp( const gcry_mpi_t u, const gcry_mpi_t v )
{
	return _gcry_mpi_cmp( u, v );
}

int
gcry_mpi_cmp_ui( const gcry_mpi_t u, unsigned long v )
{
	return _gcry_mpi_cmp_ui( u, v );
}

gcry_error_t
gcry_mpi_scan( gcry_mpi_t *ret_mpi, enum gcry_mpi_format format,
			   const void *buffer, size_t buflen,
			   size_t *nscanned )
{
	return gpg_error( _gcry_mpi_scan( ret_mpi, format, buffer, buflen, nscanned ) );
}

gcry_error_t
gcry_mpi_print( enum gcry_mpi_format format,
				unsigned char *buffer, size_t buflen,
				size_t *nwritten,
				const gcry_mpi_t a )
{
	return gpg_error( _gcry_mpi_print( format, buffer, buflen, nwritten, a ) );
}

gcry_error_t
gcry_mpi_aprint( enum gcry_mpi_format format,
				 unsigned char **buffer, size_t *nwritten,
				 const gcry_mpi_t a )
{
	return gpg_error( _gcry_mpi_aprint( format, buffer, nwritten, a ) );
}

void
gcry_mpi_dump( const gcry_mpi_t a )
{
	_gcry_log_printmpi( NULL, a );
}

void
gcry_mpi_add( gcry_mpi_t w, gcry_mpi_t u, gcry_mpi_t v )
{
	_gcry_mpi_add( w, u, v );
}

void
gcry_mpi_add_ui( gcry_mpi_t w, gcry_mpi_t u, unsigned long v )
{
	_gcry_mpi_add_ui( w, u, v );
}

void
gcry_mpi_addm( gcry_mpi_t w, gcry_mpi_t u, gcry_mpi_t v, gcry_mpi_t m )
{
	_gcry_mpi_addm( w, u, v, m );
}

void
gcry_mpi_sub( gcry_mpi_t w, gcry_mpi_t u, gcry_mpi_t v )
{
	_gcry_mpi_sub( w, u, v );
}

void
gcry_mpi_sub_ui( gcry_mpi_t w, gcry_mpi_t u, unsigned long v )
{
	_gcry_mpi_sub_ui( w, u, v );
}

void
gcry_mpi_subm( gcry_mpi_t w, gcry_mpi_t u, gcry_mpi_t v, gcry_mpi_t m )
{
	_gcry_mpi_subm( w, u, v, m );
}

void
gcry_mpi_mul( gcry_mpi_t w, gcry_mpi_t u, gcry_mpi_t v )
{
	_gcry_mpi_mul( w, u, v );
}

void
gcry_mpi_mul_ui( gcry_mpi_t w, gcry_mpi_t u, unsigned long v )
{
	_gcry_mpi_mul_ui( w, u, v );
}

void
gcry_mpi_mulm( gcry_mpi_t w, gcry_mpi_t u, gcry_mpi_t v, gcry_mpi_t m )
{
	_gcry_mpi_mulm( w, u, v, m );
}

void
gcry_mpi_mul_2exp( gcry_mpi_t w, gcry_mpi_t u, unsigned long cnt )
{
	_gcry_mpi_mul_2exp( w, u, cnt );
}

void
gcry_mpi_div( gcry_mpi_t q, gcry_mpi_t r,
			  gcry_mpi_t dividend, gcry_mpi_t divisor, int round )
{
	_gcry_mpi_div( q, r, dividend, divisor, round );
}

void
gcry_mpi_mod( gcry_mpi_t r, gcry_mpi_t dividend, gcry_mpi_t divisor )
{
	_gcry_mpi_mod( r, dividend, divisor );
}

void
gcry_mpi_powm( gcry_mpi_t w, const gcry_mpi_t b, const gcry_mpi_t e,
			   const gcry_mpi_t m )
{
	_gcry_mpi_powm( w, b, e, m );
}

int
gcry_mpi_gcd( gcry_mpi_t g, gcry_mpi_t a, gcry_mpi_t b )
{
	return _gcry_mpi_gcd( g, a, b );
}

int
gcry_mpi_invm( gcry_mpi_t x, gcry_mpi_t a, gcry_mpi_t m )
{
	return _gcry_mpi_invm( x, a, m );
}

gcry_mpi_point_t
gcry_mpi_point_new( unsigned int nbits )
{
	return _gcry_mpi_point_new( nbits );
}

void
gcry_mpi_point_release( gcry_mpi_point_t point )
{
	_gcry_mpi_point_release( point );
}

void
gcry_mpi_point_get( gcry_mpi_t x, gcry_mpi_t y, gcry_mpi_t z,
					gcry_mpi_point_t point )
{
	_gcry_mpi_point_get( x, y, z, point );
}

void
gcry_mpi_point_snatch_get( gcry_mpi_t x, gcry_mpi_t y, gcry_mpi_t z,
						   gcry_mpi_point_t point )
{
	_gcry_mpi_point_snatch_get( x, y, z, point );
}

gcry_mpi_point_t
gcry_mpi_point_set( gcry_mpi_point_t point,
					gcry_mpi_t x, gcry_mpi_t y, gcry_mpi_t z )
{
	return _gcry_mpi_point_set( point, x, y, z );
}

gcry_mpi_point_t
gcry_mpi_point_snatch_set( gcry_mpi_point_t point,
						   gcry_mpi_t x, gcry_mpi_t y, gcry_mpi_t z )
{
	return _gcry_mpi_point_snatch_set( point, x, y, z );
}

gpg_error_t
gcry_mpi_ec_new( gcry_ctx_t *r_ctx,
				 gcry_sexp_t keyparam, const char *curvename )
{
	return gpg_error( _gcry_mpi_ec_new( r_ctx, keyparam, curvename ) );
}

gcry_mpi_t
gcry_mpi_ec_get_mpi( const char *name, gcry_ctx_t ctx, int copy )
{
	return _gcry_mpi_ec_get_mpi( name, ctx, copy );
}

gcry_mpi_point_t
gcry_mpi_ec_get_point( const char *name, gcry_ctx_t ctx, int copy )
{
	return _gcry_mpi_ec_get_point( name, ctx, copy );
}

gpg_error_t
gcry_mpi_ec_set_mpi( const char *name, gcry_mpi_t newvalue, gcry_ctx_t ctx )
{
	return gpg_error( _gcry_mpi_ec_set_mpi( name, newvalue, ctx ) );
}

gpg_error_t
gcry_mpi_ec_set_point( const char *name, gcry_mpi_point_t newvalue,
					   gcry_ctx_t ctx )
{
	return gpg_error( _gcry_mpi_ec_set_point( name, newvalue, ctx ) );
}

int
gcry_mpi_ec_get_affine( gcry_mpi_t x, gcry_mpi_t y, gcry_mpi_point_t point,
						gcry_ctx_t ctx )
{
	return _gcry_mpi_ec_get_affine( x, y, point,
									_gcry_ctx_get_pointer( ctx, CONTEXT_TYPE_EC ) );
}

void
gcry_mpi_ec_dup( gcry_mpi_point_t w, gcry_mpi_point_t u, gcry_ctx_t ctx )
{
	_gcry_mpi_ec_dup_point( w, u, _gcry_ctx_get_pointer( ctx, CONTEXT_TYPE_EC ) );
}

void
gcry_mpi_ec_add( gcry_mpi_point_t w,
				 gcry_mpi_point_t u, gcry_mpi_point_t v, gcry_ctx_t ctx )
{
	_gcry_mpi_ec_add_points( w, u, v,
							 _gcry_ctx_get_pointer( ctx, CONTEXT_TYPE_EC ) );
}

void
gcry_mpi_ec_mul( gcry_mpi_point_t w, gcry_mpi_t n, gcry_mpi_point_t u,
				 gcry_ctx_t ctx )
{
	_gcry_mpi_ec_mul_point( w, n, u,
							_gcry_ctx_get_pointer( ctx, CONTEXT_TYPE_EC ) );
}

int
gcry_mpi_ec_curve_point( gcry_mpi_point_t point, gcry_ctx_t ctx )
{
	return _gcry_mpi_ec_curve_point
	( point, _gcry_ctx_get_pointer( ctx, CONTEXT_TYPE_EC ) );
}

unsigned int
gcry_mpi_get_nbits( gcry_mpi_t a )
{
	return _gcry_mpi_get_nbits( a );
}

int
gcry_mpi_test_bit( gcry_mpi_t a, unsigned int n )
{
	return _gcry_mpi_test_bit( a, n );
}

void
gcry_mpi_set_bit( gcry_mpi_t a, unsigned int n )
{
	_gcry_mpi_set_bit( a, n );
}

void
gcry_mpi_clear_bit( gcry_mpi_t a, unsigned int n )
{
	_gcry_mpi_clear_bit( a, n );
}

void
gcry_mpi_set_highbit( gcry_mpi_t a, unsigned int n )
{
	_gcry_mpi_set_highbit( a, n );
}

void
gcry_mpi_clear_highbit( gcry_mpi_t a, unsigned int n )
{
	_gcry_mpi_clear_highbit( a, n );
}

void
gcry_mpi_rshift( gcry_mpi_t x, gcry_mpi_t a, unsigned int n )
{
	_gcry_mpi_rshift( x, a, n );
}

void
gcry_mpi_lshift( gcry_mpi_t x, gcry_mpi_t a, unsigned int n )
{
	_gcry_mpi_lshift( x, a, n );
}

gcry_mpi_t
gcry_mpi_set_opaque( gcry_mpi_t a, void *p, unsigned int nbits )
{
	return _gcry_mpi_set_opaque( a, p, nbits );
}

gcry_mpi_t
gcry_mpi_set_opaque_copy( gcry_mpi_t a, const void *p, unsigned int nbits )
{
	return _gcry_mpi_set_opaque_copy( a, p, nbits );
}

void *
gcry_mpi_get_opaque( gcry_mpi_t a, unsigned int *nbits )
{
	return _gcry_mpi_get_opaque( a, nbits );
}

void
gcry_mpi_set_flag( gcry_mpi_t a, enum gcry_mpi_flag flag )
{
	_gcry_mpi_set_flag( a, flag );
}

void
gcry_mpi_clear_flag( gcry_mpi_t a, enum gcry_mpi_flag flag )
{
	_gcry_mpi_clear_flag( a, flag );
}

int
gcry_mpi_get_flag( gcry_mpi_t a, enum gcry_mpi_flag flag )
{
	return _gcry_mpi_get_flag( a, flag );
}

gcry_mpi_t
_gcry_mpi_get_const( int no )
{
	switch( no )
	{
	case 1: return _gcry_mpi_const( MPI_C_ONE );
	case 2: return _gcry_mpi_const( MPI_C_TWO );
	case 3: return _gcry_mpi_const( MPI_C_THREE );
	case 4: return _gcry_mpi_const( MPI_C_FOUR );
	case 8: return _gcry_mpi_const( MPI_C_EIGHT );
	default: LogMsg( LOG_ERROR, "unsupported GCRYMPI_CONST_ macro used\n" );
		return 0;
	}
}

gcry_error_t
gcry_cipher_open( gcry_cipher_hd_t *handle,
				  int algo, int mode, unsigned int flags )
{
	if( !fips_is_operational() )
	{
		*handle = NULL;
		return gpg_error( fips_not_operational() );
	}

	return gpg_error( _gcry_cipher_open( handle, algo, mode, flags ) );
}

void
gcry_cipher_close( gcry_cipher_hd_t h )
{
	_gcry_cipher_close( h );
}

gcry_error_t
gcry_cipher_setkey( gcry_cipher_hd_t hd, const void *key, size_t keylen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gcry_error( _gcry_cipher_setkey( hd, key, keylen ) );
}

gcry_error_t
gcry_cipher_setiv( gcry_cipher_hd_t hd, const void *iv, size_t ivlen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gcry_error( _gcry_cipher_setiv( hd, iv, ivlen ) );
}

gpg_error_t
gcry_cipher_setctr( gcry_cipher_hd_t hd, const void *ctr, size_t ctrlen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gcry_error( _gcry_cipher_setctr( hd, ctr, ctrlen ) );
}

gcry_error_t
gcry_cipher_authenticate( gcry_cipher_hd_t hd, const void *abuf, size_t abuflen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_cipher_authenticate( hd, abuf, abuflen ) );
}

gcry_error_t
gcry_cipher_gettag( gcry_cipher_hd_t hd, void *outtag, size_t taglen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_cipher_gettag( hd, outtag, taglen ) );
}

gcry_error_t
gcry_cipher_checktag( gcry_cipher_hd_t hd, const void *intag, size_t taglen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_cipher_checktag( hd, intag, taglen ) );
}


gcry_error_t
gcry_cipher_ctl( gcry_cipher_hd_t h, int cmd, void *buffer, size_t buflen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_cipher_ctl( h, cmd, buffer, buflen ) );
}

gcry_error_t
gcry_cipher_info( gcry_cipher_hd_t h, int what, void *buffer, size_t *nbytes )
{
	return gpg_error( _gcry_cipher_info( h, what, buffer, nbytes ) );
}

gcry_error_t
gcry_cipher_algo_info( int algo, int what, void *buffer, size_t *nbytes )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_cipher_algo_info( algo, what, buffer, nbytes ) );
}

const char *
gcry_cipher_algo_name( int algorithm )
{
	return _gcry_cipher_algo_name( algorithm );
}

int
gcry_cipher_map_name( const char *name )
{
	return _gcry_cipher_map_name( name );
}

int
gcry_cipher_mode_from_oid( const char *string )
{
	return _gcry_cipher_mode_from_oid( string );
}

gcry_error_t
gcry_cipher_encrypt( gcry_cipher_hd_t h,
					 void *out, size_t outsize,
					 const void *in, size_t inlen )
{
	if( !fips_is_operational() )
	{
		/* Make sure that the plaintext will never make it to OUT. */
		if( out )
			memset( out, 0x42, outsize );
		return gpg_error( fips_not_operational() );
	}

	return gpg_error( _gcry_cipher_encrypt( h, out, outsize, in, inlen ) );
}

gcry_error_t
gcry_cipher_decrypt( gcry_cipher_hd_t h,
					 void *out, size_t outsize,
					 const void *in, size_t inlen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_cipher_decrypt( h, out, outsize, in, inlen ) );
}

size_t
gcry_cipher_get_algo_keylen( int algo )
{
	return _gcry_cipher_get_algo_keylen( algo );
}

size_t
gcry_cipher_get_algo_blklen( int algo )
{
	return _gcry_cipher_get_algo_blklen( algo );
}

gcry_error_t
gcry_mac_algo_info( int algo, int what, void *buffer, size_t *nbytes )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_algo_info( algo, what, buffer, nbytes ) );
}

const char *
gcry_mac_algo_name( int algorithm )
{
	return _gcry_mac_algo_name( algorithm );
}

int
gcry_mac_map_name( const char *string )
{
	return _gcry_mac_map_name( string );
}

unsigned int
gcry_mac_get_algo_maclen( int algo )
{
	return _gcry_mac_get_algo_maclen( algo );
}

unsigned int
gcry_mac_get_algo_keylen( int algo )
{
	return _gcry_mac_get_algo_keylen( algo );
}

gcry_error_t
gcry_mac_open( gcry_mac_hd_t *handle, int algo, unsigned int flags,
			   gcry_ctx_t ctx )
{
	if( !fips_is_operational() )
	{
		*handle = NULL;
		return gpg_error( fips_not_operational() );
	}

	return gpg_error( _gcry_mac_open( handle, algo, flags, ctx ) );
}

void
gcry_mac_close( gcry_mac_hd_t hd )
{
	_gcry_mac_close( hd );
}

gcry_error_t
gcry_mac_setkey( gcry_mac_hd_t hd, const void *key, size_t keylen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_setkey( hd, key, keylen ) );
}

gcry_error_t
gcry_mac_setiv( gcry_mac_hd_t hd, const void *iv, size_t ivlen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_setiv( hd, iv, ivlen ) );
}

gcry_error_t
gcry_mac_write( gcry_mac_hd_t hd, const void *buf, size_t buflen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_write( hd, buf, buflen ) );
}

gcry_error_t
gcry_mac_read( gcry_mac_hd_t hd, void *outbuf, size_t *outlen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_read( hd, outbuf, outlen ) );
}

gcry_error_t
gcry_mac_verify( gcry_mac_hd_t hd, const void *buf, size_t buflen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_verify( hd, buf, buflen ) );
}

gcry_error_t
gcry_mac_ctl( gcry_mac_hd_t h, int cmd, void *buffer, size_t buflen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_mac_ctl( h, cmd, buffer, buflen ) );
}

gcry_error_t
gcry_pk_encrypt( gcry_sexp_t *result, gcry_sexp_t data, gcry_sexp_t pkey )
{
	if( !fips_is_operational() )
	{
		*result = NULL;
		return gpg_error( fips_not_operational() );
	}
	return gpg_error( _gcry_pk_encrypt( result, data, pkey ) );
}

gcry_error_t
gcry_pk_decrypt( gcry_sexp_t *result, gcry_sexp_t data, gcry_sexp_t skey )
{
	if( !fips_is_operational() )
	{
		*result = NULL;
		return gpg_error( fips_not_operational() );
	}
	return gpg_error( _gcry_pk_decrypt( result, data, skey ) );
}

gcry_error_t
gcry_pk_sign( gcry_sexp_t *result, gcry_sexp_t data, gcry_sexp_t skey )
{
	if( !fips_is_operational() )
	{
		*result = NULL;
		return gpg_error( fips_not_operational() );
	}
	return gpg_error( _gcry_pk_sign( result, data, skey ) );
}

gcry_error_t
gcry_pk_verify( gcry_sexp_t sigval, gcry_sexp_t data, gcry_sexp_t pkey )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );
	return gpg_error( _gcry_pk_verify( sigval, data, pkey ) );
}

gcry_error_t
gcry_pk_testkey( gcry_sexp_t key )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );
	return gpg_error( _gcry_pk_testkey( key ) );
}

gcry_error_t
gcry_pk_genkey( gcry_sexp_t *r_key, gcry_sexp_t s_parms )
{
	if( !fips_is_operational() )
	{
		*r_key = NULL;
		return gpg_error( fips_not_operational() );
	}
	return gpg_error( _gcry_pk_genkey( r_key, s_parms ) );
}

gcry_error_t
gcry_pk_ctl( int cmd, void *buffer, size_t buflen )
{
	return gpg_error( _gcry_pk_ctl( cmd, buffer, buflen ) );
}

gcry_error_t
gcry_pk_algo_info( int algo, int what, void *buffer, size_t *nbytes )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_pk_algo_info( algo, what, buffer, nbytes ) );
}

const char *
gcry_pk_algo_name( int algorithm )
{
	return _gcry_pk_algo_name( algorithm );
}

int
gcry_pk_map_name( const char *name )
{
	return _gcry_pk_map_name( name );
}

unsigned int
gcry_pk_get_nbits( gcry_sexp_t key )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		return 0;
	}

	return _gcry_pk_get_nbits( key );
}

unsigned char *
gcry_pk_get_keygrip( gcry_sexp_t key, unsigned char *array )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		return NULL;
	}
	return _gcry_pk_get_keygrip( key, array );
}

const char *
gcry_pk_get_curve( gcry_sexp_t key, int iterator, unsigned int *r_nbits )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		return NULL;
	}
	return _gcry_pk_get_curve( key, iterator, r_nbits );
}

gcry_sexp_t
gcry_pk_get_param( int algo, const char *name )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		return NULL;
	}
	return _gcry_pk_get_param( algo, name );
}

gcry_error_t
gcry_pubkey_get_sexp( gcry_sexp_t *r_sexp, int mode, gcry_ctx_t ctx )
{
	if( !fips_is_operational() )
	{
		*r_sexp = NULL;
		return gpg_error( fips_not_operational() );
	}
	return gpg_error( _gcry_pubkey_get_sexp( r_sexp, mode, ctx ) );
}

gcry_error_t
gcry_md_open( gcry_md_hd_t *h, int algo, unsigned int flags )
{
	if( !fips_is_operational() )
	{
		*h = NULL;
		return gpg_error( fips_not_operational() );
	}

	return gpg_error( _gcry_md_open( h, algo, flags ) );
}

void
gcry_md_close( gcry_md_hd_t hd )
{
	_gcry_md_close( hd );
}

gcry_error_t
gcry_md_enable( gcry_md_hd_t hd, int algo )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );
	return gpg_error( _gcry_md_enable( hd, algo ) );
}

gcry_error_t
gcry_md_copy( gcry_md_hd_t *bhd, gcry_md_hd_t ahd )
{
	if( !fips_is_operational() )
	{
		*bhd = NULL;
		return gpg_error( fips_not_operational() );
	}
	return gpg_error( _gcry_md_copy( bhd, ahd ) );
}

void
gcry_md_reset( gcry_md_hd_t hd )
{
	_gcry_md_reset( hd );
}

gcry_error_t
gcry_md_ctl( gcry_md_hd_t hd, int cmd, void *buffer, size_t buflen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );
	return gpg_error( _gcry_md_ctl( hd, cmd, buffer, buflen ) );
}

void
gcry_md_write( gcry_md_hd_t hd, const void *buffer, size_t length )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		return;
	}
	_gcry_md_write( hd, buffer, length );
}

unsigned char *
gcry_md_read( gcry_md_hd_t hd, int algo )
{
	return _gcry_md_read( hd, algo );
}

void
gcry_md_hash_buffer( int algo, void *digest,
					 const void *buffer, size_t length )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_error( "called in non-operational state" );
	}
	_gcry_md_hash_buffer( algo, digest, buffer, length );
}

gpg_error_t
gcry_md_hash_buffers( int algo, unsigned int flags, void *digest,
					  const gcry_buffer_t *iov, int iovcnt )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_error( "called in non-operational state" );
	}
	return gpg_error( _gcry_md_hash_buffers( algo, flags, digest, iov, iovcnt ) );
}

int
gcry_md_get_algo( gcry_md_hd_t hd )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_error( "used in non-operational state" );
		return 0;
	}
	return _gcry_md_get_algo( hd );
}

unsigned int
gcry_md_get_algo_dlen( int algo )
{
	return _gcry_md_get_algo_dlen( algo );
}

int
gcry_md_is_enabled( gcry_md_hd_t a, int algo )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		return 0;
	}

	return _gcry_md_is_enabled( a, algo );
}

int
gcry_md_is_secure( gcry_md_hd_t a )
{
	return _gcry_md_is_secure( a );
}

gcry_error_t
gcry_md_info( gcry_md_hd_t h, int what, void *buffer, size_t *nbytes )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );

	return gpg_error( _gcry_md_info( h, what, buffer, nbytes ) );
}

gcry_error_t
gcry_md_algo_info( int algo, int what, void *buffer, size_t *nbytes )
{
	return gpg_error( _gcry_md_algo_info( algo, what, buffer, nbytes ) );
}

const char *
gcry_md_algo_name( int algo )
{
	return _gcry_md_algo_name( algo );
}

int
gcry_md_map_name( const char* name )
{
	return _gcry_md_map_name( name );
}

gcry_error_t
gcry_md_setkey( gcry_md_hd_t hd, const void *key, size_t keylen )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );
	return gpg_error( _gcry_md_setkey( hd, key, keylen ) );
}

void
gcry_md_debug( gcry_md_hd_t hd, const char *suffix )
{
	_gcry_md_debug( hd, suffix );
}

gpg_error_t
gcry_kdf_derive( const void *passphrase, size_t passphraselen,
				 int algo, int hashalgo,
				 const void *salt, size_t saltlen,
				 unsigned long iterations,
				 size_t keysize, void *keybuffer )
{
	return gpg_error( _gcry_kdf_derive( passphrase, passphraselen, algo, hashalgo,
										salt, saltlen, iterations,
										keysize, keybuffer ) );
}

void
gcry_randomize( void *buffer, size_t length, enum gcry_random_level level )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_fatal_error( "called in non-operational state" );
		fips_noreturn();
	}
	_gcry_randomize( buffer, length, level );
}

gcry_error_t
gcry_random_add_bytes( const void *buffer, size_t length, int quality )
{
	if( !fips_is_operational() )
		return gpg_error( fips_not_operational() );
	return gpg_error( _gcry_random_add_bytes( buffer, length, quality ) );
}

void *
gcry_random_bytes( size_t nbytes, enum gcry_random_level level )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_fatal_error( "called in non-operational state" );
		fips_noreturn();
	}

	return _gcry_random_bytes( nbytes, level );
}

void *
gcry_random_bytes_secure( size_t nbytes, enum gcry_random_level level )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_fatal_error( "called in non-operational state" );
		fips_noreturn();
	}

	return _gcry_random_bytes_secure( nbytes, level );
}

void
gcry_mpi_randomize( gcry_mpi_t w,
					unsigned int nbits, enum gcry_random_level level )
{
	_gcry_mpi_randomize( w, nbits, level );
}

void
gcry_create_nonce( void *buffer, size_t length )
{
	if( !fips_is_operational() )
	{
		( void )fips_not_operational();
		fips_signal_fatal_error( "called in non-operational state" );
		fips_noreturn();
	}
	_gcry_create_nonce( buffer, length );
}

gcry_error_t
gcry_prime_generate( gcry_mpi_t *prime,
					 unsigned int prime_bits,
					 unsigned int factor_bits,
					 gcry_mpi_t **factors,
					 gcry_prime_check_func_t cb_func,
					 void *cb_arg,
					 gcry_random_level_t random_level,
					 unsigned int flags )
{
	return gpg_error( _gcry_prime_generate( prime, prime_bits, factor_bits,
											factors, cb_func, cb_arg,
											random_level, flags ) );
}

gcry_error_t
gcry_prime_group_generator( gcry_mpi_t *r_g,
							gcry_mpi_t prime, gcry_mpi_t *factors,
							gcry_mpi_t start_g )
{
	return gpg_error( _gcry_prime_group_generator( r_g, prime, factors, start_g ) );
}

void
gcry_prime_release_factors( gcry_mpi_t *factors )
{
	_gcry_prime_release_factors( factors );
}

gcry_error_t
gcry_prime_check( gcry_mpi_t x, unsigned int flags )
{
	return gpg_error( _gcry_prime_check( x, flags ) );
}

void
gcry_ctx_release( gcry_ctx_t ctx )
{
	_gcry_ctx_release( ctx );
}

void
gcry_log_debug( const char *fmt, ... )
{
	va_list arg_ptr;

	va_start( arg_ptr, fmt );
	_gcry_logv( GCRY_LOG_DEBUG, fmt, arg_ptr );
	va_end( arg_ptr );
}

void
gcry_log_debughex( const char *text, const void *buffer, size_t length )
{
	_gcry_log_printhex( text, buffer, length );
}

void
gcry_log_debugmpi( const char *text, gcry_mpi_t mpi )
{
	_gcry_log_printmpi( text, mpi );
}

void
gcry_log_debugpnt( const char *text, mpi_point_t point, gcry_ctx_t ctx )
{
	mpi_ec_t ec = ctx ? _gcry_ctx_get_pointer( ctx, CONTEXT_TYPE_EC ) : NULL;

	_gcry_mpi_point_log( text, point, ec );
}

void
gcry_log_debugsxp( const char *text, gcry_sexp_t sexp )
{
	_gcry_log_printsxp( text, sexp );
}

void
gcry_set_progress_handler( gcry_handler_progress_t cb, void *cb_data )
{
	_gcry_set_progress_handler( cb, cb_data );
}

void
gcry_set_allocation_handler( gcry_handler_alloc_t func_alloc,
							 gcry_handler_alloc_t func_alloc_secure,
							 gcry_handler_secure_check_t func_secure_check,
							 gcry_handler_realloc_t func_realloc,
							 gcry_handler_free_t func_free )
{
	_gcry_set_allocation_handler( func_alloc, func_alloc_secure,
								  func_secure_check, func_realloc, func_free );
}

void
gcry_set_outofcore_handler( gcry_handler_no_mem_t h, void *opaque )
{
	_gcry_set_outofcore_handler( h, opaque );
}

void
gcry_set_fatalerror_handler( gcry_handler_error_t fnc, void *opaque )
{
	_gcry_set_fatalerror_handler( fnc, opaque );
}

void
gcry_set_log_handler( gcry_handler_log_t f, void *opaque )
{
	_gcry_set_log_handler( f, opaque );
}

void
gcry_set_gettext_handler( const char *( *f )( const char* ) )
{
	_gcry_set_gettext_handler( f );
}

void *
gcry_malloc( size_t n )
{
	return _gcry_malloc( n );
}

void *
gcry_calloc( size_t n, size_t m )
{
	return _gcry_calloc( n, m );
}

void *
gcry_malloc_secure( size_t n )
{
	return _gcry_malloc_secure( n );
}

void *
gcry_calloc_secure( size_t n, size_t m )
{
	return _gcry_calloc_secure( n, m );
}

void *
gcry_realloc( void *a, size_t n )
{
	return _gcry_realloc( a, n );
}

char *
gcry_strdup( const char *string )
{
	return _gcry_strdup( string );
}

void *
gcry_xmalloc( size_t n )
{
	return _gcry_xmalloc( n );
}

void *
gcry_xcalloc( size_t n, size_t m )
{
	return _gcry_xcalloc( n, m );
}

void *
gcry_xmalloc_secure( size_t n )
{
	return _gcry_xmalloc_secure( n );
}

void *
gcry_xcalloc_secure( size_t n, size_t m )
{
	return _gcry_xcalloc_secure( n, m );
}

void *
gcry_xrealloc( void *a, size_t n )
{
	return _gcry_xrealloc( a, n );
}

char *
gcry_xstrdup( const char *a )
{
	return _gcry_xstrdup( a );
}

void
gcry_free( void *a )
{
	_gcry_free( a );
}

int
gcry_is_secure( const void *a )
{
	return _gcry_is_secure( a );
}
