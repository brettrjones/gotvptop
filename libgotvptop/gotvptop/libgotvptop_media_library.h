/*****************************************************************************
 * libgotvptop_media_library.h:  libgotvptop external API
 *****************************************************************************
 * Copyright (C) 1998-2009 GOTV authors and VideoLAN
 * $Id: facbf813aa16140461c6e72f166d2985c52b1d6f $
 *
 * Authors: Clément Stenac <zorglub@videolan.org>
 *          Jean-Paul Saman <jpsaman@videolan.org>
 *          Pierre d'Herbemont <pdherbemont@videolan.org>
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

#ifndef GOTV_LIBGOTV_MEDIA_LIBRARY_H
#define GOTV_LIBGOTV_MEDIA_LIBRARY_H 1

/** \defgroup libgotvptop_media_library LibGOTV media library
 * \ingroup libgotvptop
 * @{
 * \file
 * LibGOTV media library external API
 */

typedef struct libgotvptop_media_library_t libgotvptop_media_library_t;

/**
 * Create an new Media Library object
 *
 * \param p_instance the libgotvptop instance
 * \return a new object or NULL on error
 */
LIBGOTV_API libgotvptop_media_library_t *
    libgotvptop_media_library_new( libgotvptop_instance_t * p_instance );

/**
 * Release media library object. This functions decrements the
 * reference count of the media library object. If it reaches 0,
 * then the object will be released.
 *
 * \param p_mlib media library object
 */
LIBGOTV_API void
    libgotvptop_media_library_release( libgotvptop_media_library_t * p_mlib );

/**
 * Retain a reference to a media library object. This function will
 * increment the reference counting for this object. Use
 * libgotvptop_media_library_release() to decrement the reference count.
 *
 * \param p_mlib media library object
 */
LIBGOTV_API void
    libgotvptop_media_library_retain( libgotvptop_media_library_t * p_mlib );

/**
 * Load media library.
 *
 * \param p_mlib media library object
 * \return 0 on success, -1 on error
 */
LIBGOTV_API int
    libgotvptop_media_library_load( libgotvptop_media_library_t * p_mlib );

/**
 * Get media library subitems.
 *
 * \param p_mlib media library object
 * \return media list subitems
 */
LIBGOTV_API libgotvptop_media_list_t *
    libgotvptop_media_library_media_list( libgotvptop_media_library_t * p_mlib );



#endif /* GOTV_LIBGOTV_MEDIA_LIBRARY_H */
