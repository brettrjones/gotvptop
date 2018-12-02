/*****************************************************************************
 * libgotvptop_media_list.h:  libgotvptop_media_list API
 *****************************************************************************
 * Copyright (C) 1998-2008 GOTV authors and VideoLAN
 * $Id: fa3b90932be8c3a9cce27925d4867aeddde748d7 $
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

#ifndef LIBGOTV_MEDIA_LIST_H
#define LIBGOTV_MEDIA_LIST_H 1


/** \defgroup libgotvptop_media_list LibGOTV media list
 * \ingroup libgotvptop
 * A LibGOTV media list holds multiple @ref libgotvptop_media_t media descriptors.
 * @{
 * \file
 * LibGOTV media list (playlist) external API
 */

typedef struct libgotvptop_media_list_t libgotvptop_media_list_t;

/**
 * Create an empty media list.
 *
 * \param p_instance libgotvptop instance
 * \return empty media list, or NULL on error
 */
LIBGOTV_API libgotvptop_media_list_t *
    libgotvptop_media_list_new( libgotvptop_instance_t *p_instance );

/**
 * Release media list created with libgotvptop_media_list_new().
 *
 * \param p_ml a media list created with libgotvptop_media_list_new()
 */
LIBGOTV_API void
    libgotvptop_media_list_release( libgotvptop_media_list_t *p_ml );

/**
 * Retain reference to a media list
 *
 * \param p_ml a media list created with libgotvptop_media_list_new()
 */
LIBGOTV_API void
    libgotvptop_media_list_retain( libgotvptop_media_list_t *p_ml );

/**
 * Associate media instance with this media list instance.
 * If another media instance was present it will be released.
 * The libgotvptop_media_list_lock should NOT be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \param p_md media instance to add
 */
LIBGOTV_API void
libgotvptop_media_list_set_media( libgotvptop_media_list_t *p_ml, libgotvptop_media_t *p_md );

/**
 * Get media instance from this media list instance. This action will increase
 * the refcount on the media instance.
 * The libgotvptop_media_list_lock should NOT be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \return media instance
 */
LIBGOTV_API libgotvptop_media_t *
    libgotvptop_media_list_media( libgotvptop_media_list_t *p_ml );

/**
 * Add media instance to media list
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \param p_md a media instance
 * \return 0 on success, -1 if the media list is read-only
 */
LIBGOTV_API int
libgotvptop_media_list_add_media( libgotvptop_media_list_t *p_ml, libgotvptop_media_t *p_md );

/**
 * Insert media instance in media list on a position
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \param p_md a media instance
 * \param i_pos position in array where to insert
 * \return 0 on success, -1 if the media list is read-only
 */
LIBGOTV_API int
libgotvptop_media_list_insert_media( libgotvptop_media_list_t *p_ml,
                                libgotvptop_media_t *p_md, int i_pos );

/**
 * Remove media instance from media list on a position
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \param i_pos position in array where to insert
 * \return 0 on success, -1 if the list is read-only or the item was not found
 */
LIBGOTV_API int
libgotvptop_media_list_remove_index( libgotvptop_media_list_t *p_ml, int i_pos );

/**
 * Get count on media list items
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \return number of items in media list
 */
LIBGOTV_API int
    libgotvptop_media_list_count( libgotvptop_media_list_t *p_ml );

/**
 * List media instance in media list at a position
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \param i_pos position in array where to insert
 * \return media instance at position i_pos, or NULL if not found.
 * In case of success, libgotvptop_media_retain() is called to increase the refcount
 * on the media.
 */
LIBGOTV_API libgotvptop_media_t *
    libgotvptop_media_list_item_at_index( libgotvptop_media_list_t *p_ml, int i_pos );
/**
 * Find index position of List media instance in media list.
 * Warning: the function will return the first matched position.
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 * \param p_md media instance
 * \return position of media instance or -1 if media not found
 */
LIBGOTV_API int
    libgotvptop_media_list_index_of_item( libgotvptop_media_list_t *p_ml,
                                     libgotvptop_media_t *p_md );

/**
 * This indicates if this media list is read-only from a user point of view
 *
 * \param p_ml media list instance
 * \return 1 on readonly, 0 on readwrite
 *
 * \libgotvptop_return_bool
 */
LIBGOTV_API int
    libgotvptop_media_list_is_readonly( libgotvptop_media_list_t * p_ml );

/**
 * Get lock on media list items
 *
 * \param p_ml a media list instance
 */
LIBGOTV_API void
    libgotvptop_media_list_lock( libgotvptop_media_list_t *p_ml );

/**
 * Release lock on media list items
 * The libgotvptop_media_list_lock should be held upon entering this function.
 *
 * \param p_ml a media list instance
 */
LIBGOTV_API void
    libgotvptop_media_list_unlock( libgotvptop_media_list_t *p_ml );

/**
 * Get libgotvptop_event_manager from this media list instance.
 * The p_event_manager is immutable, so you don't have to hold the lock
 *
 * \param p_ml a media list instance
 * \return libgotvptop_event_manager
 */
LIBGOTV_API libgotvptop_event_manager_t *
    libgotvptop_media_list_event_manager( libgotvptop_media_list_t *p_ml );

#endif /* _LIBGOTV_MEDIA_LIST_H */
