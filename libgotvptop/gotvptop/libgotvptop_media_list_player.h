/*****************************************************************************
 * libgotvptop_media_list_player.h:  libgotvptop_media_list API
 *****************************************************************************
 * Copyright (C) 1998-2008 GOTV authors and VideoLAN
 * $Id: 04f7d9b9f0d47e1b8304b51ca20fd2b1045a0ff2 $
 *
 * Authors: Pierre d'Herbemont
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

#ifndef LIBGOTV_MEDIA_LIST_PLAYER_H
#define LIBGOTV_MEDIA_LIST_PLAYER_H 1


/** \defgroup libgotvptop_media_list_player LibGOTV media list player
 * \ingroup libgotvptop
 * The LibGOTV media list player plays a @ref libgotvptop_media_list_t list of media,
 * in a certain order.
 * This is required to especially support playlist files.
 * The normal @ref libgotvptop_media_player_t LibGOTV media player can only play a
 * single media, and does not handle playlist files properly.
 * @{
 * \file
 * LibGOTV media list player external API
 */

typedef struct libgotvptop_media_list_player_t libgotvptop_media_list_player_t;

/**
 *  Defines playback modes for playlist.
 */
typedef enum libgotvptop_playback_mode_t
{
    libgotvptop_playback_mode_default,
    libgotvptop_playback_mode_loop,
    libgotvptop_playback_mode_repeat
} libgotvptop_playback_mode_t;

/**
 * Create new media_list_player.
 *
 * \param p_instance libgotvptop instance
 * \return media list player instance or NULL on error
 */
LIBGOTV_API libgotvptop_media_list_player_t *
    libgotvptop_media_list_player_new( libgotvptop_instance_t * p_instance );

/**
 * Release a media_list_player after use
 * Decrement the reference count of a media player object. If the
 * reference count is 0, then libgotvptop_media_list_player_release() will
 * release the media player object. If the media player object
 * has been released, then it should not be used again.
 *
 * \param p_mlp media list player instance
 */
LIBGOTV_API void
    libgotvptop_media_list_player_release( libgotvptop_media_list_player_t * p_mlp );

/**
 * Retain a reference to a media player list object. Use
 * libgotvptop_media_list_player_release() to decrement reference count.
 *
 * \param p_mlp media player list object
 */
LIBGOTV_API void
    libgotvptop_media_list_player_retain( libgotvptop_media_list_player_t *p_mlp );

/**
 * Return the event manager of this media_list_player.
 *
 * \param p_mlp media list player instance
 * \return the event manager
 */
LIBGOTV_API libgotvptop_event_manager_t *
    libgotvptop_media_list_player_event_manager(libgotvptop_media_list_player_t * p_mlp);

/**
 * Replace media player in media_list_player with this instance.
 *
 * \param p_mlp media list player instance
 * \param p_mi media player instance
 */
LIBGOTV_API void
    libgotvptop_media_list_player_set_media_player(
                                     libgotvptop_media_list_player_t * p_mlp,
                                     libgotvptop_media_player_t * p_mi );

/**
 * Get media player of the media_list_player instance.
 *
 * \param p_mlp media list player instance
 * \return media player instance
 * \note the caller is responsible for releasing the returned instance
 */
LIBGOTV_API libgotvptop_media_player_t *
    libgotvptop_media_list_player_get_media_player(libgotvptop_media_list_player_t * p_mlp);

/**
 * Set the media list associated with the player
 *
 * \param p_mlp media list player instance
 * \param p_mlist list of media
 */
LIBGOTV_API void
    libgotvptop_media_list_player_set_media_list(
                                     libgotvptop_media_list_player_t * p_mlp,
                                     libgotvptop_media_list_t * p_mlist );

/**
 * Play media list
 *
 * \param p_mlp media list player instance
 */
LIBGOTV_API
void libgotvptop_media_list_player_play(libgotvptop_media_list_player_t * p_mlp);

/**
 * Toggle pause (or resume) media list
 *
 * \param p_mlp media list player instance
 */
LIBGOTV_API
void libgotvptop_media_list_player_pause(libgotvptop_media_list_player_t * p_mlp);

/**
 * Pause or resume media list
 *
 * \param p_mlp media list player instance
 * \param do_pause play/resume if zero, pause if non-zero
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API
void libgotvptop_media_list_player_set_pause(libgotvptop_media_list_player_t * p_mlp,
                                        int do_pause);

/**
 * Is media list playing?
 *
 * \param p_mlp media list player instance
 * \return true for playing and false for not playing
 *
 * \libgotvptop_return_bool
 */
LIBGOTV_API int
    libgotvptop_media_list_player_is_playing( libgotvptop_media_list_player_t * p_mlp );

/**
 * Get current libgotvptop_state of media list player
 *
 * \param p_mlp media list player instance
 * \return libgotvptop_state_t for media list player
 */
LIBGOTV_API libgotvptop_state_t
    libgotvptop_media_list_player_get_state( libgotvptop_media_list_player_t * p_mlp );

/**
 * Play media list item at position index
 *
 * \param p_mlp media list player instance
 * \param i_index index in media list to play
 * \return 0 upon success -1 if the item wasn't found
 */
LIBGOTV_API
int libgotvptop_media_list_player_play_item_at_index(libgotvptop_media_list_player_t * p_mlp,
                                                int i_index);

/**
 * Play the given media item
 *
 * \param p_mlp media list player instance
 * \param p_md the media instance
 * \return 0 upon success, -1 if the media is not part of the media list
 */
LIBGOTV_API
int libgotvptop_media_list_player_play_item(libgotvptop_media_list_player_t * p_mlp,
                                       libgotvptop_media_t * p_md);

/**
 * Stop playing media list
 *
 * \param p_mlp media list player instance
 */
LIBGOTV_API void
    libgotvptop_media_list_player_stop( libgotvptop_media_list_player_t * p_mlp);

/**
 * Play next item from media list
 *
 * \param p_mlp media list player instance
 * \return 0 upon success -1 if there is no next item
 */
LIBGOTV_API
int libgotvptop_media_list_player_next(libgotvptop_media_list_player_t * p_mlp);

/**
 * Play previous item from media list
 *
 * \param p_mlp media list player instance
 * \return 0 upon success -1 if there is no previous item
 */
LIBGOTV_API
int libgotvptop_media_list_player_previous(libgotvptop_media_list_player_t * p_mlp);



/**
 * Sets the playback mode for the playlist
 *
 * \param p_mlp media list player instance
 * \param e_mode playback mode specification
 */
LIBGOTV_API
void libgotvptop_media_list_player_set_playback_mode(libgotvptop_media_list_player_t * p_mlp,
                                                libgotvptop_playback_mode_t e_mode );


#endif /* LIBGOTV_MEDIA_LIST_PLAYER_H */
