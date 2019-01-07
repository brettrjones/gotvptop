/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
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

#include "DllLibbluray.h"

#if USE_STATIC_LIBS
extern "C"
{
#include "libbluray/src/file/file.h"
}

#include <CoreLib/VxDebug.h>

#include <string.h>

DllLibbluray::DllLibbluray()
: StaticDll( DLL_PATH_LIBBLURAY )
{
}

DllLibbluray::~DllLibbluray()
{
}

uint32_t DllLibbluray::bd_get_titles( BLURAY *p1, uint8_t p2, uint32_t p3 )
{
    return ::bd_get_titles( p1, p2, p3 );
}

BLURAY_TITLE_INFO* DllLibbluray::bd_get_title_info( BLURAY *p1, uint32_t p2, unsigned p3 )
{
    return ::bd_get_title_info( p1, p2, p3 );
}

BLURAY_TITLE_INFO* DllLibbluray::bd_get_playlist_info( BLURAY *p1, uint32_t p2, unsigned p3 )
{
    return ::bd_get_playlist_info( p1, p2, p3 );
}

void DllLibbluray::bd_free_title_info( BLURAY_TITLE_INFO *p1 )
{
    ::bd_free_title_info( p1 );
}

BLURAY* DllLibbluray::bd_open( const char* p1, const char* p2 )
{
    return ::bd_open( p1, p2 );
}

int DllLibbluray::bd_open_disc( BLURAY *p1, const char *p2, const char *p3 )
{
    return ::bd_open_disc( p1, p2, p3 );
}

int DllLibbluray::bd_open_stream( BLURAY *p1, void *p2, read_blocks_f p3 )
{
    return ::bd_open_stream( p1, p2, p3 );
}

int DllLibbluray::bd_open_files( BLURAY *p1, void *p2, open_dir_f p3, open_file_f p4 )
{
    return ::bd_open_files( p1, p2, p3, p4 );
}

BLURAY* DllLibbluray::bd_init()
{
    return ::bd_init();
}

void DllLibbluray::bd_close( BLURAY *p1 )
{
    ::bd_close( p1 );
}

int64_t DllLibbluray::bd_seek( BLURAY *p1, uint64_t p2 )
{
    return ::bd_seek( p1, p2 );
}

int64_t DllLibbluray::bd_seek_time( BLURAY *p1, uint64_t p2 )
{
    return ::bd_seek_time( p1, p2 );
}

int DllLibbluray::bd_read( BLURAY *p1, unsigned char *p2, int p3 )
{
    return ::bd_read( p1, p2, p3 );
}

int64_t DllLibbluray::bd_seek_chapter( BLURAY *p1, unsigned p2 )
{
    return ::bd_seek_chapter( p1, p2 );
}

int64_t DllLibbluray::bd_chapter_pos( BLURAY *p1, unsigned p2 )
{
    return ::bd_chapter_pos( p1, p2 );
}

uint32_t DllLibbluray::bd_get_current_chapter( BLURAY *p1 )
{
    return ::bd_get_current_chapter( p1 );
}

int64_t DllLibbluray::bd_seek_mark( BLURAY *p1, unsigned p2 )
{
    return ::bd_seek_mark( p1, p2 );
}

int DllLibbluray::bd_select_playlist( BLURAY *p1, uint32_t p2 )
{
    return ::bd_select_playlist( p1, p2 );
}

int DllLibbluray::bd_select_title( BLURAY *p1, uint32_t p2 )
{
    return ::bd_select_title( p1, p2 );
}

int DllLibbluray::bd_select_angle( BLURAY *p1, unsigned p2 )
{
    return ::bd_select_angle( p1, p2 );
}

void DllLibbluray::bd_seamless_angle_change( BLURAY *p1, unsigned p2 )
{
    ::bd_seamless_angle_change( p1, p2 );
}

uint64_t DllLibbluray::bd_get_title_size( BLURAY *p1 )
{
    return ::bd_get_title_size( p1 );
}

uint32_t DllLibbluray::bd_get_current_title( BLURAY *p1 )
{
    return ::bd_get_current_title( p1 );
}

unsigned DllLibbluray::bd_get_current_angle( BLURAY *p1 )
{
    return ::bd_get_current_angle( p1 );
}

uint64_t DllLibbluray::bd_tell( BLURAY *p1 )
{
    return ::bd_tell( p1 );
}

uint64_t DllLibbluray::bd_tell_time( BLURAY *p1 )
{
    return ::bd_tell_time( p1 );
}

BD_FILE_OPEN DllLibbluray::bd_register_file( BD_FILE_OPEN p1 )
{
    return ::bd_register_file( p1 );
}

BD_DIR_OPEN DllLibbluray::bd_register_dir( BD_DIR_OPEN p1 )
{
    return ::bd_register_dir( p1 );
}

void DllLibbluray::bd_set_debug_handler( BD_LOG_FUNC p1 )
{
    ::bd_set_debug_handler( p1 );
}

void DllLibbluray::bd_set_debug_mask( uint32_t p1 )
{
    return ::bd_set_debug_mask( p1 );
}

uint32_t DllLibbluray::bd_get_debug_mask()
{
    return ::bd_get_debug_mask( );
}

const BLURAY_DISC_INFO* DllLibbluray::bd_get_disc_info( BLURAY *p1 )
{
    return ::bd_get_disc_info( p1 );
}

int DllLibbluray::bd_get_event( BLURAY *p1, BD_EVENT *p2 )
{
    return ::bd_get_event( p1, p2 );
}

int DllLibbluray::bd_play( BLURAY *p1 )
{
    return ::bd_play( p1 );
}

int DllLibbluray::bd_read_ext( BLURAY *p1, unsigned char *p2, int p3, BD_EVENT *p4 )
{
    return ::bd_read_ext( p1, p2, p3, p4 );
}

int DllLibbluray::bd_read_skip_still( BLURAY *p1 )
{
    return ::bd_read_skip_still( p1 );
}

int DllLibbluray::bd_user_input( BLURAY *p1, int64_t p2, uint32_t p3 )
{
    return ::bd_user_input( p1, p2, p3 );
}

int DllLibbluray::bd_set_player_setting( BLURAY *p1, uint32_t p2, uint32_t p3 )
{
    return ::bd_set_player_setting( p1, p2, p3 );
}

int DllLibbluray::bd_set_player_setting_str( BLURAY *p1, uint32_t p2, const char *p3 )
{
    return ::bd_set_player_setting_str( p1, p2, p3 );
}

void DllLibbluray::bd_register_overlay_proc( BLURAY *p1, void *p2, bd_overlay_proc_f p3 )
{
    ::bd_register_overlay_proc( p1, p2, p3 );
}

#ifdef HAVE_LIBBLURAY_BDJ
void DllLibbluray::bd_register_argb_overlay_proc( BLURAY *p1, void *p2, bd_argb_overlay_proc_f p3, struct bd_argb_buffer_s *p4 )
{
    ::bd_register_argb_overlay_proc( p1, p2, p3, p4 );
}
#endif

int DllLibbluray::bd_menu_call( BLURAY *p1, int64_t p2 )
{
    return ::bd_menu_call( p1, p2 );
}

int DllLibbluray::bd_mouse_select( BLURAY *p1, int64_t p2, uint16_t p3, uint16_t p4 )
{
    return ::bd_mouse_select( p1, p2, p3, p4 );
}

int DllLibbluray::bd_get_sound_effect( BLURAY *p1, unsigned p2, struct bd_sound_effect* p3 )
{
    return ::bd_get_sound_effect( p1, p2, p3 );
}


// static functions NOTE these are defined in xbmc DVDInputStreamBluray.cpp
/*
void       DllLibbluray::file_close( BD_FILE_H *file )
{
    ::file_close( file );
}

int64_t    DllLibbluray::file_seek( BD_FILE_H *file, int64_t offset, int32_t origin )
{
    return ::file_seek( file, offset, origin );
}

int64_t    DllLibbluray::file_tell( BD_FILE_H *file )
{
    return ::file_tell( file );
}

int        DllLibbluray::file_eof( BD_FILE_H *file )
{
    return file->eof( file );
}

int64_t    DllLibbluray::file_read( BD_FILE_H *file, uint8_t *buf, int64_t size )
{
    return ::file_read( file, buf, size );
}

int64_t    DllLibbluray::file_write( BD_FILE_H *file, const uint8_t *buf, int64_t size )
{
    return file->write( file, buf, size );
}

void      DllLibbluray::dir_close( BD_DIR_H * dir )
{
    ((struct bd_dir_s *) dir)->close( dir );
}

int       DllLibbluray::dir_read( BD_DIR_H *dir, BD_DIRENT *entry )
{
    return dir->read( dir, entry );
}
*/

/* located in DVDInputStreamBluray.cpp
BD_FILE_H *DllLibbluray::file_open( void * handle, const char * rel_path )
{
    return ::file_open( handle, rel_path );
}
*/

/* located in DVDInputStreamBluray.cpp
BD_DIR_H *DllLibbluray::dir_open( void * handle, const char * rel_path )
{
    return ::dir_open( handle, rel_path );
}
*/

/*
void      DllLibbluray::bluray_logger( const char* msg )
{
    LogMsg( LOG_DEBUG, msg );
}
*/



#endif // USE_STATIC_LIBS

