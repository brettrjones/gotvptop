/*****************************************************************************
 * deprecated.h:  libgotvptop deprecated API
 *****************************************************************************
 * Copyright (C) 1998-2008 GOTV authors and VideoLAN
 * $Id: 27323a434498604ca281900c3e4087a42d22a5d8 $
 *
 * Authors: Clément Stenac <zorglub@videolan.org>
 *          Jean-Paul Saman <jpsaman@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef LIBGOTV_DEPRECATED_H
#define LIBGOTV_DEPRECATED_H 1

/**
 * \ingroup libgotvptop libgotvptop_media_player
 * @{
 */

/**
 * Get movie fps rate
 *
 * This function is provided for backward compatibility. It cannot deal with
 * multiple video tracks. In LibGOTV versions prior to 3.0, it would also fail
 * if the file format did not convey the frame rate explicitly.
 *
 * \deprecated Consider using libgotvptop_media_tracks_get() instead.
 *
 * \param p_mi the Media Player
 * \return frames per second (fps) for this playing movie, or 0 if unspecified
 */
LIBGOTV_DEPRECATED
LIBGOTV_API float libgotvptop_media_player_get_fps( libgotvptop_media_player_t *p_mi );

/** end bug */

/**
 * \deprecated Use libgotvptop_media_player_set_nsobject() instead
 */
LIBGOTV_DEPRECATED
LIBGOTV_API void libgotvptop_media_player_set_agl ( libgotvptop_media_player_t *p_mi, uint32_t drawable );

/**
 * \deprecated Use libgotvptop_media_player_get_nsobject() instead
 */
LIBGOTV_DEPRECATED
LIBGOTV_API uint32_t libgotvptop_media_player_get_agl ( libgotvptop_media_player_t *p_mi );

/**
 * \deprecated Use libgotvptop_track_description_list_release() instead
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_track_description_release( libgotvptop_track_description_t *p_track_description );

/** @}*/

/**
 * \ingroup libgotvptop libgotvptop_video
 * @{
 */

/**
 * Get current video height.
 * \deprecated Use libgotvptop_video_get_size() instead.
 *
 * \param p_mi the media player
 * \return the video pixel height or 0 if not applicable
 */
LIBGOTV_DEPRECATED LIBGOTV_API
int libgotvptop_video_get_height( libgotvptop_media_player_t *p_mi );

/**
 * Get current video width.
 * \deprecated Use libgotvptop_video_get_size() instead.
 *
 * \param p_mi the media player
 * \return the video pixel width or 0 if not applicable
 */
LIBGOTV_DEPRECATED LIBGOTV_API
int libgotvptop_video_get_width( libgotvptop_media_player_t *p_mi );

/**
 * Get the description of available titles.
 *
 * \param p_mi the media player
 * \return list containing description of available titles.
 * It must be freed with libgotvptop_track_description_list_release()
 */
LIBGOTV_DEPRECATED LIBGOTV_API libgotvptop_track_description_t *
        libgotvptop_video_get_title_description( libgotvptop_media_player_t *p_mi );

/**
 * Get the description of available chapters for specific title.
 *
 * \param p_mi the media player
 * \param i_title selected title
 * \return list containing description of available chapter for title i_title.
 * It must be freed with libgotvptop_track_description_list_release()
 */
LIBGOTV_DEPRECATED LIBGOTV_API libgotvptop_track_description_t *
        libgotvptop_video_get_chapter_description( libgotvptop_media_player_t *p_mi, int i_title );

/**
 * Set new video subtitle file.
 * \deprecated Use libgotvptop_media_player_add_slave() instead.
 *
 * \param p_mi the media player
 * \param psz_subtitle new video subtitle file
 * \return the success status (boolean)
 */
LIBGOTV_DEPRECATED LIBGOTV_API int
libgotvptop_video_set_subtitle_file( libgotvptop_media_player_t *p_mi, const char *psz_subtitle );

/**
 * Toggle teletext transparent status on video output.
 * \deprecated use libgotvptop_video_set_teletext() instead.
 *
 * \param p_mi the media player
 */
LIBGOTV_DEPRECATED LIBGOTV_API void
libgotvptop_toggle_teletext( libgotvptop_media_player_t *p_mi );

/** @}*/

/**
 * \ingroup libgotvptop libgotvptop_audio
 * @{
 */

/**
 * Backward compatibility stub. Do not use in new code.
 * \deprecated Use libgotvptop_audio_output_device_list_get() instead.
 * \return always 0.
 */
LIBGOTV_DEPRECATED LIBGOTV_API
int libgotvptop_audio_output_device_count( libgotvptop_instance_t *p_instance, const char *psz_audio_output );

/**
 * Backward compatibility stub. Do not use in new code.
 * \deprecated Use libgotvptop_audio_output_device_list_get() instead.
 * \return always NULL.
 */
LIBGOTV_DEPRECATED LIBGOTV_API
char *libgotvptop_audio_output_device_longname( libgotvptop_instance_t *p_instance, const char *psz_output,
                                           int i_device );

/**
 * Backward compatibility stub. Do not use in new code.
 * \deprecated Use libgotvptop_audio_output_device_list_get() instead.
 * \return always NULL.
 */
LIBGOTV_DEPRECATED LIBGOTV_API
char *libgotvptop_audio_output_device_id( libgotvptop_instance_t *p_instance, const char *psz_audio_output, int i_device );

/**
 * Stub for backward compatibility.
 * \return always -1.
 */
LIBGOTV_DEPRECATED
LIBGOTV_API int libgotvptop_audio_output_get_device_type( libgotvptop_media_player_t *p_mi );

/**
 * Stub for backward compatibility.
 */
LIBGOTV_DEPRECATED
LIBGOTV_API void libgotvptop_audio_output_set_device_type( libgotvptop_media_player_t *p_mp,
                                                     int device_type );

/** @}*/

/**
 * \ingroup libgotvptop libgotvptop_media
 * @{
 */

/**
 * Parse a media.
 *
 * This fetches (local) art, meta data and tracks information.
 * The method is synchronous.
 *
 * \deprecated This function could block indefinitely.
 *             Use libgotvptop_media_parse_with_options() instead
 *
 * \see libgotvptop_media_parse_with_options
 * \see libgotvptop_media_get_meta
 * \see libgotvptop_media_get_tracks_info
 *
 * \param p_md media descriptor object
 */
LIBGOTV_DEPRECATED LIBGOTV_API void
libgotvptop_media_parse( libgotvptop_media_t *p_md );

/**
 * Parse a media.
 *
 * This fetches (local) art, meta data and tracks information.
 * The method is the asynchronous of libgotvptop_media_parse().
 *
 * To track when this is over you can listen to libgotvptop_MediaParsedChanged
 * event. However if the media was already parsed you will not receive this
 * event.
 *
 * \deprecated You can't be sure to receive the libgotvptop_MediaParsedChanged
 *             event (you can wait indefinitely for this event).
 *             Use libgotvptop_media_parse_with_options() instead
 *
 * \see libgotvptop_media_parse
 * \see libgotvptop_MediaParsedChanged
 * \see libgotvptop_media_get_meta
 * \see libgotvptop_media_get_tracks_info
 *
 * \param p_md media descriptor object
 */
LIBGOTV_DEPRECATED LIBGOTV_API void
libgotvptop_media_parse_async( libgotvptop_media_t *p_md );

/**
 * Return true is the media descriptor object is parsed
 *
 * \deprecated This can return true in case of failure.
 *             Use libgotvptop_media_get_parsed_status() instead
 *
 * \see libgotvptop_MediaParsedChanged
 *
 * \param p_md media descriptor object
 * \return true if media object has been parsed otherwise it returns false
 *
 * \libgotvptop_return_bool
 */
LIBGOTV_DEPRECATED LIBGOTV_API int
   libgotvptop_media_is_parsed( libgotvptop_media_t *p_md );

/**
 * Get media descriptor's elementary streams description
 *
 * Note, you need to call libgotvptop_media_parse() or play the media at least once
 * before calling this function.
 * Not doing this will result in an empty array.
 *
 * \deprecated Use libgotvptop_media_tracks_get() instead
 *
 * \param p_md media descriptor object
 * \param tracks address to store an allocated array of Elementary Streams
 *        descriptions (must be freed by the caller) [OUT]
 *
 * \return the number of Elementary Streams
 */
LIBGOTV_DEPRECATED LIBGOTV_API
int libgotvptop_media_get_tracks_info( libgotvptop_media_t *p_md,
                                  libgotvptop_media_track_info_t **tracks );

/** @}*/

/**
 * \ingroup libgotvptop libgotvptop_media_list
 * @{
 */

LIBGOTV_DEPRECATED int
    libgotvptop_media_list_add_file_content( libgotvptop_media_list_t * p_ml,
                                        const char * psz_uri );

/** @}*/

/**
 * \ingroup libgotvptop libgotvptop_media_discoverer
 * @{
 */

/**
 * \deprecated Use libgotvptop_media_discoverer_new() and libgotvptop_media_discoverer_start().
 */
LIBGOTV_DEPRECATED LIBGOTV_API libgotvptop_media_discoverer_t *
libgotvptop_media_discoverer_new_from_name( libgotvptop_instance_t * p_inst,
                                       const char * psz_name );

/**
 * Get media service discover object its localized name.
 *
 * \deprecated Useless, use libgotvptop_media_discoverer_list_get() to get the
 * longname of the service discovery.
 *
 * \param p_mdis media discover object
 * \return localized name or NULL if the media_discoverer is not started
 */
LIBGOTV_DEPRECATED LIBGOTV_API char *
libgotvptop_media_discoverer_localized_name( libgotvptop_media_discoverer_t * p_mdis );

/**
 * Get event manager from media service discover object.
 *
 * \deprecated Useless, media_discoverer events are only triggered when calling
 * libgotvptop_media_discoverer_start() and libgotvptop_media_discoverer_stop().
 *
 * \param p_mdis media service discover object
 * \return event manager object.
 */
LIBGOTV_DEPRECATED LIBGOTV_API libgotvptop_event_manager_t *
libgotvptop_media_discoverer_event_manager( libgotvptop_media_discoverer_t * p_mdis );

/** @}*/

/**
 * \ingroup libgotvptop libgotvptop_core
 * @{
 */

/**
 * Waits until an interface causes the instance to exit.
 * You should start at least one interface first, using libgotvptop_add_intf().
 *
 * \param p_instance the instance
 * \warning This function wastes one thread doing basically nothing.
 * libgotvptop_set_exit_handler() should be used instead.
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_wait( libgotvptop_instance_t *p_instance );


/** @}*/

/**
 * \ingroup libgotvptop_core
 * \defgroup libgotvptop_log_deprecated LibGOTV logging (legacy)
 * @{
 */

/** This structure is opaque. It represents a libgotvptop log iterator */
typedef struct libgotvptop_log_iterator_t libgotvptop_log_iterator_t;

typedef struct libgotvptop_log_message_t
{
    int         i_severity;   /* 0=INFO, 1=ERR, 2=WARN, 3=DBG */
    const char *psz_type;     /* module type */
    const char *psz_name;     /* module name */
    const char *psz_header;   /* optional header */
    const char *psz_message;  /* message */
} libgotvptop_log_message_t;

/**
 * Always returns minus one.
 * This function is only provided for backward compatibility.
 *
 * \param p_instance ignored
 * \return always -1
 */
LIBGOTV_DEPRECATED LIBGOTV_API
unsigned libgotvptop_get_log_verbosity( const libgotvptop_instance_t *p_instance );

/**
 * This function does nothing.
 * It is only provided for backward compatibility.
 *
 * \param p_instance ignored
 * \param level ignored
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_set_log_verbosity( libgotvptop_instance_t *p_instance, unsigned level );

/**
 * This function does nothing useful.
 * It is only provided for backward compatibility.
 *
 * \param p_instance libgotvptop instance
 * \return an unique pointer or NULL on error
 */
LIBGOTV_DEPRECATED LIBGOTV_API
libgotvptop_log_t *libgotvptop_log_open( libgotvptop_instance_t *p_instance );

/**
 * Frees memory allocated by libgotvptop_log_open().
 *
 * \param p_log libgotvptop log instance or NULL
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_log_close( libgotvptop_log_t *p_log );

/**
 * Always returns zero.
 * This function is only provided for backward compatibility.
 *
 * \param p_log ignored
 * \return always zero
 */
LIBGOTV_DEPRECATED LIBGOTV_API
unsigned libgotvptop_log_count( const libgotvptop_log_t *p_log );

/**
 * This function does nothing.
 * It is only provided for backward compatibility.
 *
 * \param p_log ignored
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_log_clear( libgotvptop_log_t *p_log );

/**
 * This function does nothing useful.
 * It is only provided for backward compatibility.
 *
 * \param p_log ignored
 * \return an unique pointer or NULL on error or if the parameter was NULL
 */
LIBGOTV_DEPRECATED LIBGOTV_API
libgotvptop_log_iterator_t *libgotvptop_log_get_iterator( const libgotvptop_log_t *p_log );

/**
 * Frees memory allocated by libgotvptop_log_get_iterator().
 *
 * \param p_iter libgotvptop log iterator or NULL
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_log_iterator_free( libgotvptop_log_iterator_t *p_iter );

/**
 * Always returns zero.
 * This function is only provided for backward compatibility.
 *
 * \param p_iter ignored
 * \return always zero
 */
LIBGOTV_DEPRECATED LIBGOTV_API
int libgotvptop_log_iterator_has_next( const libgotvptop_log_iterator_t *p_iter );

/**
 * Always returns NULL.
 * This function is only provided for backward compatibility.
 *
 * \param p_iter libgotvptop log iterator or NULL
 * \param p_buf ignored
 * \return always NULL
 */
LIBGOTV_DEPRECATED LIBGOTV_API
libgotvptop_log_message_t *libgotvptop_log_iterator_next( libgotvptop_log_iterator_t *p_iter,
                                                libgotvptop_log_message_t *p_buf );

/** @}*/

/**
 * \ingroup libgotvptop
 * \defgroup libgotvptop_playlist LibGOTV playlist (legacy)
 * @deprecated Use @ref libgotvptop_media_list instead.
 * @{
 * \file
 * LibGOTV deprecated playlist API
 */

/**
 * Start playing (if there is any item in the playlist).
 *
 * Additionnal playlist item options can be specified for addition to the
 * item before it is played.
 *
 * \param p_instance the playlist instance
 * \param i_id the item to play. If this is a negative number, the next
 *        item will be selected. Otherwise, the item with the given ID will be
 *        played
 * \param i_options the number of options to add to the item
 * \param ppsz_options the options to add to the item
 */
LIBGOTV_DEPRECATED LIBGOTV_API
void libgotvptop_playlist_play( libgotvptop_instance_t *p_instance, int i_id,
                           int i_options, char **ppsz_options );


#endif /* _LIBGOTV_DEPRECATED_H */
