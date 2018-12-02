/*****************************************************************************
 * libgotvptop_renderer_discoverer.h:  libgotvptop external API
 *****************************************************************************
 * Copyright © 2016 GOTV authors and VideoLAN
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

#ifndef GOTV_LIBGOTV_RENDERER_DISCOVERER_H
#define GOTV_LIBGOTV_RENDERER_DISCOVERER_H 1

/**
 * @defgroup libgotvptop_renderer_discoverer LibGOTV renderer discoverer
 * @ingroup libgotvptop
 * LibGOTV renderer discoverer finds available renderers available on the local
 * network
 * @{
 * @file
 * LibGOTV renderer discoverer external API
 */

typedef struct libgotvptop_renderer_discoverer_t libgotvptop_renderer_discoverer_t;

/**
 * Renderer discoverer description
 *
 * \see libgotvptop_renderer_discoverer_list_get()
 */
typedef struct libgotvptop_rd_description_t
{
    char *psz_name;
    char *psz_longname;
} libgotvptop_rd_description_t;

/** The renderer can render audio */
#define LIBGOTV_RENDERER_CAN_AUDIO 0x0001
/** The renderer can render video */
#define LIBGOTV_RENDERER_CAN_VIDEO 0x0002

/**
 * Renderer item
 *
 * This struct is passed by a @ref libgotvptop_event_t when a new renderer is added
 * or deleted.
 *
 * An item is valid until the @ref libgotvptop_RendererDiscovererItemDeleted event
 * is called with the same pointer.
 *
 * \see libgotvptop_renderer_discoverer_event_manager()
 */
typedef struct libgotvptop_renderer_item_t libgotvptop_renderer_item_t;


/**
 * Hold a renderer item, i.e. creates a new reference
 *
 * This functions need to called from the libgotvptop_RendererDiscovererItemAdded
 * callback if the libgotvptop user wants to use this item after. (for display or
 * for passing it to the mediaplayer for example).
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \return the current item
 */
LIBGOTV_API libgotvptop_renderer_item_t *
libgotvptop_renderer_item_hold(libgotvptop_renderer_item_t *p_item);

/**
 * Releases a renderer item, i.e. decrements its reference counter
 *
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API void
libgotvptop_renderer_item_release(libgotvptop_renderer_item_t *p_item);

/**
 * Get the human readable name of a renderer item
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \return the name of the item (can't be NULL, must *not* be freed)
 */
LIBGOTV_API const char *
libgotvptop_renderer_item_name(const libgotvptop_renderer_item_t *p_item);

/**
 * Get the type (not translated) of a renderer item. For now, the type can only
 * be "chromecast" ("upnp", "airplay" may come later).
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \return the type of the item (can't be NULL, must *not* be freed)
 */
LIBGOTV_API const char *
libgotvptop_renderer_item_type(const libgotvptop_renderer_item_t *p_item);

/**
 * Get the icon uri of a renderer item
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \return the uri of the item's icon (can be NULL, must *not* be freed)
 */
LIBGOTV_API const char *
libgotvptop_renderer_item_icon_uri(const libgotvptop_renderer_item_t *p_item);

/**
 * Get the flags of a renderer item
 *
 * \see LIBGOTV_RENDERER_CAN_AUDIO
 * \see LIBGOTV_RENDERER_CAN_VIDEO
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \return bitwise flag: capabilities of the renderer, see
 */
LIBGOTV_API int
libgotvptop_renderer_item_flags(const libgotvptop_renderer_item_t *p_item);

/**
 * Create a renderer discoverer object by name
 *
 * After this object is created, you should attach to events in order to be
 * notified of the discoverer events.
 *
 * You need to call libgotvptop_renderer_discoverer_start() in order to start the
 * discovery.
 *
 * \see libgotvptop_renderer_discoverer_event_manager()
 * \see libgotvptop_renderer_discoverer_start()
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \param p_inst libgotvptop instance
 * \param psz_name service name; use libgotvptop_renderer_discoverer_list_get() to
 * get a list of the discoverer names available in this libGOTV instance
 * \return media discover object or NULL in case of error
 */
LIBGOTV_API libgotvptop_renderer_discoverer_t *
libgotvptop_renderer_discoverer_new( libgotvptop_instance_t *p_inst,
                                const char *psz_name );

/**
 * Release a renderer discoverer object
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \param p_rd renderer discoverer object
 */
LIBGOTV_API void
libgotvptop_renderer_discoverer_release( libgotvptop_renderer_discoverer_t *p_rd );

/**
 * Start renderer discovery
 *
 * To stop it, call libgotvptop_renderer_discoverer_stop() or
 * libgotvptop_renderer_discoverer_release() directly.
 *
 * \see libgotvptop_renderer_discoverer_stop()
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \param p_rd renderer discoverer object
 * \return -1 in case of error, 0 otherwise
 */
LIBGOTV_API int
libgotvptop_renderer_discoverer_start( libgotvptop_renderer_discoverer_t *p_rd );

/**
 * Stop renderer discovery.
 *
 * \see libgotvptop_renderer_discoverer_start()
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \param p_rd renderer discoverer object
 */
LIBGOTV_API void
libgotvptop_renderer_discoverer_stop( libgotvptop_renderer_discoverer_t *p_rd );

/**
 * Get the event manager of the renderer discoverer
 *
 * The possible events to attach are @ref libgotvptop_RendererDiscovererItemAdded
 * and @ref libgotvptop_RendererDiscovererItemDeleted.
 *
 * The @ref libgotvptop_renderer_item_t struct passed to event callbacks is owned by
 * GOTV, users should take care of holding/releasing this struct for their
 * internal usage.
 *
 * \see libgotvptop_event_t.u.renderer_discoverer_item_added.item
 * \see libgotvptop_event_t.u.renderer_discoverer_item_removed.item
 *
 * \version LibGOTV 3.0.0 or later
 *
 * \return a valid event manager (can't fail)
 */
LIBGOTV_API libgotvptop_event_manager_t *
libgotvptop_renderer_discoverer_event_manager( libgotvptop_renderer_discoverer_t *p_rd );

/**
 * Get media discoverer services
 *
 * \see libgotvptop_renderer_list_release()
 *
 * \version LibGOTV 3.0.0 and later
 *
 * \param p_inst libgotvptop instance
 * \param ppp_services address to store an allocated array of renderer
 * discoverer services (must be freed with libgotvptop_renderer_list_release() by
 * the caller) [OUT]
 *
 * \return the number of media discoverer services (0 on error)
 */
LIBGOTV_API size_t
libgotvptop_renderer_discoverer_list_get( libgotvptop_instance_t *p_inst,
                                     libgotvptop_rd_description_t ***ppp_services );

/**
 * Release an array of media discoverer services
 *
 * \see libgotvptop_renderer_discoverer_list_get()
 *
 * \version LibGOTV 3.0.0 and later
 *
 * \param pp_services array to release
 * \param i_count number of elements in the array
 */
LIBGOTV_API void
libgotvptop_renderer_discoverer_list_release( libgotvptop_rd_description_t **pp_services,
                                         size_t i_count );

/** @} */

#endif
