/*****************************************************************************
 * libgotvptop_media_discoverer.h:  libgotvptop external API
 *****************************************************************************
 * Copyright (C) 1998-2009 GOTV authors and VideoLAN
 * $Id: 96c0515ffec98f439867814d68525288b2702b0f $
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

#ifndef GOTV_LIBGOTV_MEDIA_DISCOVERER_H
#define GOTV_LIBGOTV_MEDIA_DISCOVERER_H 1

/**
 * Category of a media discoverer
 * \see libgotvptop_media_discoverer_list_get()
 */
typedef enum libgotvptop_media_discoverer_category_t {
    /** devices, like portable music player */
    libgotvptop_media_discoverer_devices,
    /** LAN/WAN services, like Upnp, SMB, or SAP */
    libgotvptop_media_discoverer_lan,
    /** Podcasts */
    libgotvptop_media_discoverer_podcasts,
    /** Local directories, like Video, Music or Pictures directories */
    libgotvptop_media_discoverer_localdirs,
} libgotvptop_media_discoverer_category_t;

/**
 * Media discoverer description
 * \see libgotvptop_media_discoverer_list_get()
 */
typedef struct libgotvptop_media_discoverer_description_t {
    char *psz_name;
    char *psz_longname;
    libgotvptop_media_discoverer_category_t i_cat;
} libgotvptop_media_discoverer_description_t;

/** \defgroup libgotvptop_media_discoverer LibGOTV media discovery
 * \ingroup libgotvptop
 * LibGOTV media discovery finds available media via various means.
 * This corresponds to the service discovery functionality in GOTV media player.
 * Different plugins find potential medias locally (e.g. user media directory),
 * from peripherals (e.g. video capture device), on the local network
 * (e.g. SAP) or on the Internet (e.g. Internet radios).
 * @{
 * \file
 * LibGOTV media discovery external API
 */

typedef struct libgotvptop_media_discoverer_t libgotvptop_media_discoverer_t;

/**
 * Create a media discoverer object by name.
 *
 * After this object is created, you should attach to media_list events in
 * order to be notified of new items discovered.
 *
 * You need to call libgotvptop_media_discoverer_start() in order to start the
 * discovery.
 *
 * \see libgotvptop_media_discoverer_media_list
 * \see libgotvptop_media_discoverer_event_manager
 * \see libgotvptop_media_discoverer_start
 *
 * \param p_inst libgotvptop instance
 * \param psz_name service name; use libgotvptop_media_discoverer_list_get() to get
 * a list of the discoverer names available in this libGOTV instance
 * \return media discover object or NULL in case of error
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API libgotvptop_media_discoverer_t *
libgotvptop_media_discoverer_new( libgotvptop_instance_t * p_inst,
                             const char * psz_name );

/**
 * Start media discovery.
 *
 * To stop it, call libgotvptop_media_discoverer_stop() or
 * libgotvptop_media_discoverer_list_release() directly.
 *
 * \see libgotvptop_media_discoverer_stop
 *
 * \param p_mdis media discover object
 * \return -1 in case of error, 0 otherwise
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API int
libgotvptop_media_discoverer_start( libgotvptop_media_discoverer_t * p_mdis );

/**
 * Stop media discovery.
 *
 * \see libgotvptop_media_discoverer_start
 *
 * \param p_mdis media discover object
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API void
libgotvptop_media_discoverer_stop( libgotvptop_media_discoverer_t * p_mdis );

/**
 * Release media discover object. If the reference count reaches 0, then
 * the object will be released.
 *
 * \param p_mdis media service discover object
 */
LIBGOTV_API void
libgotvptop_media_discoverer_release( libgotvptop_media_discoverer_t * p_mdis );

/**
 * Get media service discover media list.
 *
 * \param p_mdis media service discover object
 * \return list of media items
 */
LIBGOTV_API libgotvptop_media_list_t *
libgotvptop_media_discoverer_media_list( libgotvptop_media_discoverer_t * p_mdis );

/**
 * Query if media service discover object is running.
 *
 * \param p_mdis media service discover object
 * \return true if running, false if not
 *
 * \libgotvptop_return_bool
 */
LIBGOTV_API int
libgotvptop_media_discoverer_is_running( libgotvptop_media_discoverer_t * p_mdis );

/**
 * Get media discoverer services by category
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \param p_inst libgotvptop instance
 * \param i_cat category of services to fetch
 * \param ppp_services address to store an allocated array of media discoverer
 * services (must be freed with libgotvptop_media_discoverer_list_release() by
 * the caller) [OUT]
 *
 * \return the number of media discoverer services (0 on error)
 */
LIBGOTV_API size_t
libgotvptop_media_discoverer_list_get( libgotvptop_instance_t *p_inst,
                                  libgotvptop_media_discoverer_category_t i_cat,
                                  libgotvptop_media_discoverer_description_t ***ppp_services );

/**
 * Release an array of media discoverer services
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \see libgotvptop_media_discoverer_list_get()
 *
 * \param pp_services array to release
 * \param i_count number of elements in the array
 */
LIBGOTV_API void
libgotvptop_media_discoverer_list_release( libgotvptop_media_discoverer_description_t **pp_services,
                                      size_t i_count );


#endif /* <gotvptop/libgotvptop.h> */
