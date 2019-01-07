/*****************************************************************************
 * libgotvptop_media.h:  libgotvptop external API
 *****************************************************************************
 * Copyright (C) 1998-2009 GOTV authors and VideoLAN
 * $Id: 383f366b6940f7b3d89f5945e015793833ea541f $
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

#ifndef GOTV_LIBGOTV_MEDIA_H
#define GOTV_LIBGOTV_MEDIA_H 1

#include "config_gotvcore.h"

/** \defgroup libgotvptop_media LibGOTV media
 * \ingroup libgotvptop
 * @ref libgotvptop_media_t is an abstract representation of a playable media.
 * It consists of a media location and various optional meta data.
 * @{
 * \file
 * LibGOTV media item/descriptor external API
 */

typedef struct libgotvptop_media_t libgotvptop_media_t;

/** Meta data types */
typedef enum libgotvptop_meta_t {
    libgotvptop_meta_Title,
    libgotvptop_meta_Artist,
    libgotvptop_meta_Genre,
    libgotvptop_meta_Copyright,
    libgotvptop_meta_Album,
    libgotvptop_meta_TrackNumber,
    libgotvptop_meta_Description,
    libgotvptop_meta_Rating,
    libgotvptop_meta_Date,
    libgotvptop_meta_Setting,
    libgotvptop_meta_URL,
    libgotvptop_meta_Language,
    libgotvptop_meta_NowPlaying,
    libgotvptop_meta_Publisher,
    libgotvptop_meta_EncodedBy,
    libgotvptop_meta_ArtworkURL,
    libgotvptop_meta_TrackID,
    libgotvptop_meta_TrackTotal,
    libgotvptop_meta_Director,
    libgotvptop_meta_Season,
    libgotvptop_meta_Episode,
    libgotvptop_meta_ShowName,
    libgotvptop_meta_Actors,
    libgotvptop_meta_AlbumArtist,
    libgotvptop_meta_DiscNumber,
    libgotvptop_meta_DiscTotal
    /* Add new meta types HERE */
} libgotvptop_meta_t;

/**
 * Note the order of libgotvptop_state_t enum must match exactly the order of
 * \see mediacontrol_PlayerStatus, \see input_state_e enums,
 * and VideoLAN.LibGOTV.State (at bindings/cil/src/media.cs).
 *
 * Expected states by web plugins are:
 * IDLE/CLOSE=0, OPENING=1, PLAYING=3, PAUSED=4,
 * STOPPING=5, ENDED=6, ERROR=7
 */
typedef enum libgotvptop_state_t
{
    libgotvptop_NothingSpecial=0,
    libgotvptop_Opening,
    libgotvptop_Buffering, /* XXX: Deprecated value. Check the
                       * libgotvptop_MediaPlayerBuffering event to know the
                       * buffering state of a libgotvptop_media_player */
    libgotvptop_Playing,
    libgotvptop_Paused,
    libgotvptop_Stopped,
    libgotvptop_Ended,
    libgotvptop_Error
} libgotvptop_state_t;

enum
{
    libgotvptop_media_option_trusted = 0x2,
    libgotvptop_media_option_unique = 0x100
};

typedef enum libgotvptop_track_type_t
{
    libgotvptop_track_unknown   = -1,
    libgotvptop_track_audio     = 0,
    libgotvptop_track_video     = 1,
    libgotvptop_track_text      = 2
} libgotvptop_track_type_t;

typedef struct libgotvptop_media_stats_t
{
    /* Input */
    int         i_read_bytes;
    float       f_input_bitrate;

    /* Demux */
    int         i_demux_read_bytes;
    float       f_demux_bitrate;
    int         i_demux_corrupted;
    int         i_demux_discontinuity;

    /* Decoders */
    int         i_decoded_video;
    int         i_decoded_audio;

    /* Video Output */
    int         i_displayed_pictures;
    int         i_lost_pictures;

    /* Audio output */
    int         i_played_abuffers;
    int         i_lost_abuffers;

    /* Stream output */
    int         i_sent_packets;
    int         i_sent_bytes;
    float       f_send_bitrate;
} libgotvptop_media_stats_t;

typedef struct libgotvptop_media_track_info_t
{
    /* Codec fourcc */
    uint32_t    i_codec;
    int         i_id;
    libgotvptop_track_type_t i_type;

    /* Codec specific */
    int         i_profile;
    int         i_level;

    union {
        struct {
            /* Audio specific */
            unsigned    i_channels;
            unsigned    i_rate;
        } audio;
        struct {
            /* Video specific */
            unsigned    i_height;
            unsigned    i_width;
        } video;
    } u;

} libgotvptop_media_track_info_t;


typedef struct libgotvptop_audio_track_t
{
    unsigned    i_channels;
    unsigned    i_rate;
} libgotvptop_audio_track_t;

typedef enum libgotvptop_video_orient_t
{
    libgotvptop_video_orient_top_left,       /**< Normal. Top line represents top, left column left. */
    libgotvptop_video_orient_top_right,      /**< Flipped horizontally */
    libgotvptop_video_orient_bottom_left,    /**< Flipped vertically */
    libgotvptop_video_orient_bottom_right,   /**< Rotated 180 degrees */
    libgotvptop_video_orient_left_top,       /**< Transposed */
    libgotvptop_video_orient_left_bottom,    /**< Rotated 90 degrees clockwise (or 270 anti-clockwise) */
    libgotvptop_video_orient_right_top,      /**< Rotated 90 degrees anti-clockwise */
    libgotvptop_video_orient_right_bottom    /**< Anti-transposed */
} libgotvptop_video_orient_t;

typedef enum libgotvptop_video_projection_t
{
    libgotvptop_video_projection_rectangular,
    libgotvptop_video_projection_equirectangular, /**< 360 spherical */

    libgotvptop_video_projection_cubemap_layout_standard = 0x100,
} libgotvptop_video_projection_t;

/**
 * Viewpoint
 *
 * \warning allocate using libgotvptop_video_new_viewpoint()
 */
typedef struct libgotvptop_video_viewpoint_t
{
    float f_yaw;           /**< view point yaw in degrees  ]-180;180] */
    float f_pitch;         /**< view point pitch in degrees  ]-90;90] */
    float f_roll;          /**< view point roll in degrees ]-180;180] */
    float f_field_of_view; /**< field of view in degrees ]0;180[ (default 80.)*/
} libgotvptop_video_viewpoint_t;

typedef struct libgotvptop_video_track_t
{
    unsigned    i_height;
    unsigned    i_width;
    unsigned    i_sar_num;
    unsigned    i_sar_den;
    unsigned    i_frame_rate_num;
    unsigned    i_frame_rate_den;

    libgotvptop_video_orient_t       i_orientation;
    libgotvptop_video_projection_t   i_projection;
    libgotvptop_video_viewpoint_t    pose; /**< Initial view point */
} libgotvptop_video_track_t;

typedef struct libgotvptop_subtitle_track_t
{
    char *psz_encoding;
} libgotvptop_subtitle_track_t;

typedef struct libgotvptop_media_track_t
{
    /* Codec fourcc */
    uint32_t    i_codec;
    uint32_t    i_original_fourcc;
    int         i_id;
    libgotvptop_track_type_t i_type;

    /* Codec specific */
    int         i_profile;
    int         i_level;

    union {
        libgotvptop_audio_track_t *audio;
        libgotvptop_video_track_t *video;
        libgotvptop_subtitle_track_t *subtitle;
    };

    unsigned int i_bitrate;
    char *psz_language;
    char *psz_description;

} libgotvptop_media_track_t;

/**
 * Media type
 *
 * \see libgotvptop_media_get_type
 */
typedef enum libgotvptop_media_type_t {
    libgotvptop_media_type_unknown,
    libgotvptop_media_type_file,
    libgotvptop_media_type_directory,
    libgotvptop_media_type_disc,
    libgotvptop_media_type_stream,
    libgotvptop_media_type_playlist,
} libgotvptop_media_type_t;

/**
 * Parse flags used by libgotvptop_media_parse_with_options()
 *
 * \see libgotvptop_media_parse_with_options
 */
typedef enum libgotvptop_media_parse_flag_t
{
    /**
     * Parse media if it's a local file
     */
    libgotvptop_media_parse_local    = 0x00,
    /**
     * Parse media even if it's a network file
     */
    libgotvptop_media_parse_network  = 0x01,
    /**
     * Fetch meta and covert art using local resources
     */
    libgotvptop_media_fetch_local    = 0x02,
    /**
     * Fetch meta and covert art using network resources
     */
    libgotvptop_media_fetch_network  = 0x04,
    /**
     * Interact with the user (via libgotvptop_dialog_cbs) when preparsing this item
     * (and not its sub items). Set this flag in order to receive a callback
     * when the input is asking for credentials.
     */
    libgotvptop_media_do_interact    = 0x08,
} libgotvptop_media_parse_flag_t;

/**
 * Parse status used sent by libgotvptop_media_parse_with_options() or returned by
 * libgotvptop_media_get_parsed_status()
 *
 * \see libgotvptop_media_parse_with_options
 * \see libgotvptop_media_get_parsed_status
 */
typedef enum libgotvptop_media_parsed_status_t
{
    libgotvptop_media_parsed_status_skipped = 1,
    libgotvptop_media_parsed_status_failed,
    libgotvptop_media_parsed_status_timeout,
    libgotvptop_media_parsed_status_done,
} libgotvptop_media_parsed_status_t;

/**
 * Type of a media slave: subtitle or audio.
 */
typedef enum libgotvptop_media_slave_type_t
{
    libgotvptop_media_slave_type_subtitle,
    libgotvptop_media_slave_type_audio,
} libgotvptop_media_slave_type_t;

/**
 * A slave of a libgotvptop_media_t
 * \see libgotvptop_media_slaves_get
 */
typedef struct libgotvptop_media_slave_t
{
    char *                          psz_uri;
    libgotvptop_media_slave_type_t       i_type;
    unsigned int                    i_priority;
} libgotvptop_media_slave_t;

/**
 * Callback prototype to open a custom bitstream input media.
 *
 * The same media item can be opened multiple times. Each time, this callback
 * is invoked. It should allocate and initialize any instance-specific
 * resources, then store them in *datap. The instance resources can be freed
 * in the @ref libgotvptop_media_close_cb callback.
 *
 * \param opaque private pointer as passed to libgotvptop_media_new_callbacks()
 * \param datap storage space for a private data pointer [OUT]
 * \param sizep byte length of the bitstream or UINT64_MAX if unknown [OUT]
 *
 * \note For convenience, *datap is initially NULL and *sizep is initially 0.
 *
 * \return 0 on success, non-zero on error. In case of failure, the other
 * callbacks will not be invoked and any value stored in *datap and *sizep is
 * discarded.
 */
typedef int (*libgotvptop_media_open_cb)(void *opaque, void **datap,
                                    uint64_t *sizep);

/**
 * Callback prototype to read data from a custom bitstream input media.
 *
 * \param opaque private pointer as set by the @ref libgotvptop_media_open_cb
 *               callback
 * \param buf start address of the buffer to read data into
 * \param len bytes length of the buffer
 *
 * \return strictly positive number of bytes read, 0 on end-of-stream,
 *         or -1 on non-recoverable error
 *
 * \note If no data is immediately available, then the callback should sleep.
 * \warning The application is responsible for avoiding deadlock situations.
 * In particular, the callback should return an error if playback is stopped;
 * if it does not return, then libgotvptop_media_player_stop() will never return.
 */
typedef ssize_t (*libgotvptop_media_read_cb)(void *opaque, unsigned char *buf,
                                        size_t len);

/**
 * Callback prototype to seek a custom bitstream input media.
 *
 * \param opaque private pointer as set by the @ref libgotvptop_media_open_cb
 *               callback
 * \param offset absolute byte offset to seek to
 * \return 0 on success, -1 on error.
 */
typedef int (*libgotvptop_media_seek_cb)(void *opaque, uint64_t offset);

/**
 * Callback prototype to close a custom bitstream input media.
 *
 * \param opaque private pointer as set by the @ref libgotvptop_media_open_cb
 *               callback
 */
typedef void (*libgotvptop_media_close_cb)(void *opaque);

/**
 * Create a media with a certain given media resource location,
 * for instance a valid URL.
 *
 * \note To refer to a local file with this function,
 * the file://... URI syntax <b>must</b> be used (see IETF RFC3986).
 * We recommend using libgotvptop_media_new_path() instead when dealing with
 * local files.
 *
 * \see libgotvptop_media_release
 *
 * \param p_instance the instance
 * \param psz_mrl the media location
 * \return the newly created media or NULL on error
 */
LIBGOTV_API libgotvptop_media_t *libgotvptop_media_new_location(
                                   libgotvptop_instance_t *p_instance,
                                   const char * psz_mrl );

/**
 * Create a media for a certain file path.
 *
 * \see libgotvptop_media_release
 *
 * \param p_instance the instance
 * \param path local filesystem path
 * \return the newly created media or NULL on error
 */
LIBGOTV_API libgotvptop_media_t *libgotvptop_media_new_path(
                                   libgotvptop_instance_t *p_instance,
                                   const char *path );

/**
 * Create a media for an already open file descriptor.
 * The file descriptor shall be open for reading (or reading and writing).
 *
 * Regular file descriptors, pipe read descriptors and character device
 * descriptors (including TTYs) are supported on all platforms.
 * Block device descriptors are supported where available.
 * Directory descriptors are supported on systems that provide fdopendir().
 * Sockets are supported on all platforms where they are file descriptors,
 * i.e. all except Windows.
 *
 * \note This library will <b>not</b> automatically close the file descriptor
 * under any circumstance. Nevertheless, a file descriptor can usually only be
 * rendered once in a media player. To render it a second time, the file
 * descriptor should probably be rewound to the beginning with lseek().
 *
 * \see libgotvptop_media_release
 *
 * \version LibGOTV 1.1.5 and later.
 *
 * \param p_instance the instance
 * \param fd open file descriptor
 * \return the newly created media or NULL on error
 */
LIBGOTV_API libgotvptop_media_t *libgotvptop_media_new_fd(
                                   libgotvptop_instance_t *p_instance,
                                   int fd );

/**
 * Create a media with custom callbacks to read the data from.
 *
 * \param instance LibGOTV instance
 * \param open_cb callback to open the custom bitstream input media
 * \param read_cb callback to read data (must not be NULL)
 * \param seek_cb callback to seek, or NULL if seeking is not supported
 * \param close_cb callback to close the media, or NULL if unnecessary
 * \param opaque data pointer for the open callback
 *
 * \return the newly created media or NULL on error
 *
 * \note If open_cb is NULL, the opaque pointer will be passed to read_cb,
 * seek_cb and close_cb, and the stream size will be treated as unknown.
 *
 * \note The callbacks may be called asynchronously (from another thread).
 * A single stream instance need not be reentrant. However the open_cb needs to
 * be reentrant if the media is used by multiple player instances.
 *
 * \warning The callbacks may be used until all or any player instances
 * that were supplied the media item are stopped.
 *
 * \see libgotvptop_media_release
 *
 * \version LibGOTV 3.0.0 and later.
 */
LIBGOTV_API libgotvptop_media_t *libgotvptop_media_new_callbacks(
                                   libgotvptop_instance_t *instance,
                                   libgotvptop_media_open_cb open_cb,
                                   libgotvptop_media_read_cb read_cb,
                                   libgotvptop_media_seek_cb seek_cb,
                                   libgotvptop_media_close_cb close_cb,
                                   void *opaque );

/**
 * Create a media as an empty node with a given name.
 *
 * \see libgotvptop_media_release
 *
 * \param p_instance the instance
 * \param psz_name the name of the node
 * \return the new empty media or NULL on error
 */
LIBGOTV_API libgotvptop_media_t *libgotvptop_media_new_as_node(
                                   libgotvptop_instance_t *p_instance,
                                   const char * psz_name );

/**
 * Add an option to the media.
 *
 * This option will be used to determine how the media_player will
 * read the media. This allows to use GOTV's advanced
 * reading/streaming options on a per-media basis.
 *
 * \note The options are listed in 'gotvptop --long-help' from the command line,
 * e.g. "-sout-all". Keep in mind that available options and their semantics
 * vary across LibGOTV versions and builds.
 * \warning Not all options affects libgotvptop_media_t objects:
 * Specifically, due to architectural issues most audio and video options,
 * such as text renderer options, have no effects on an individual media.
 * These options must be set through libgotvptop_new() instead.
 *
 * \param p_md the media descriptor
 * \param psz_options the options (as a string)
 */
LIBGOTV_API void libgotvptop_media_add_option(
                                   libgotvptop_media_t *p_md,
                                   const char * psz_options );

/**
 * Add an option to the media with configurable flags.
 *
 * This option will be used to determine how the media_player will
 * read the media. This allows to use GOTV's advanced
 * reading/streaming options on a per-media basis.
 *
 * The options are detailed in gotvptop --long-help, for instance
 * "--sout-all". Note that all options are not usable on medias:
 * specifically, due to architectural issues, video-related options
 * such as text renderer options cannot be set on a single media. They
 * must be set on the whole libgotvptop instance instead.
 *
 * \param p_md the media descriptor
 * \param psz_options the options (as a string)
 * \param i_flags the flags for this option
 */
LIBGOTV_API void libgotvptop_media_add_option_flag(
                                   libgotvptop_media_t *p_md,
                                   const char * psz_options,
                                   unsigned i_flags );


/**
 * Retain a reference to a media descriptor object (libgotvptop_media_t). Use
 * libgotvptop_media_release() to decrement the reference count of a
 * media descriptor object.
 *
 * \param p_md the media descriptor
 */
LIBGOTV_API void libgotvptop_media_retain( libgotvptop_media_t *p_md );

/**
 * Decrement the reference count of a media descriptor object. If the
 * reference count is 0, then libgotvptop_media_release() will release the
 * media descriptor object. It will send out an libgotvptop_MediaFreed event
 * to all listeners. If the media descriptor object has been released it
 * should not be used again.
 *
 * \param p_md the media descriptor
 */
LIBGOTV_API void libgotvptop_media_release( libgotvptop_media_t *p_md );


/**
 * Get the media resource locator (mrl) from a media descriptor object
 *
 * \param p_md a media descriptor object
 * \return string with mrl of media descriptor object
 */
LIBGOTV_API char *libgotvptop_media_get_mrl( libgotvptop_media_t *p_md );

/**
 * Duplicate a media descriptor object.
 *
 * \param p_md a media descriptor object.
 */
LIBGOTV_API libgotvptop_media_t *libgotvptop_media_duplicate( libgotvptop_media_t *p_md );

/**
 * Read the meta of the media.
 *
 * If the media has not yet been parsed this will return NULL.
 *
 * \see libgotvptop_media_parse
 * \see libgotvptop_media_parse_with_options
 * \see libgotvptop_MediaMetaChanged
 *
 * \param p_md the media descriptor
 * \param e_meta the meta to read
 * \return the media's meta
 */
LIBGOTV_API char *libgotvptop_media_get_meta( libgotvptop_media_t *p_md,
                                             libgotvptop_meta_t e_meta );

/**
 * Set the meta of the media (this function will not save the meta, call
 * libgotvptop_media_save_meta in order to save the meta)
 *
 * \param p_md the media descriptor
 * \param e_meta the meta to write
 * \param psz_value the media's meta
 */
LIBGOTV_API void libgotvptop_media_set_meta( libgotvptop_media_t *p_md,
                                           libgotvptop_meta_t e_meta,
                                           const char *psz_value );


/**
 * Save the meta previously set
 *
 * \param p_md the media desriptor
 * \return true if the write operation was successful
 */
LIBGOTV_API int libgotvptop_media_save_meta( libgotvptop_media_t *p_md );


/**
 * Get current state of media descriptor object. Possible media states are
 * libgotvptop_NothingSpecial=0, libgotvptop_Opening, libgotvptop_Playing, libgotvptop_Paused,
 * libgotvptop_Stopped, libgotvptop_Ended, libgotvptop_Error.
 *
 * \see libgotvptop_state_t
 * \param p_md a media descriptor object
 * \return state of media descriptor object
 */
LIBGOTV_API libgotvptop_state_t libgotvptop_media_get_state(
                                   libgotvptop_media_t *p_md );


/**
 * Get the current statistics about the media
 * \param p_md: media descriptor object
 * \param p_stats: structure that contain the statistics about the media
 *                 (this structure must be allocated by the caller)
 * \return true if the statistics are available, false otherwise
 *
 * \libgotvptop_return_bool
 */
LIBGOTV_API int libgotvptop_media_get_stats( libgotvptop_media_t *p_md,
                                           libgotvptop_media_stats_t *p_stats );

/* The following method uses libgotvptop_media_list_t, however, media_list usage is optionnal
 * and this is here for convenience */
#define GOTV_FORWARD_DECLARE_OBJECT(a) struct a

/**
 * Get subitems of media descriptor object. This will increment
 * the reference count of supplied media descriptor object. Use
 * libgotvptop_media_list_release() to decrement the reference counting.
 *
 * \param p_md media descriptor object
 * \return list of media descriptor subitems or NULL
 */
LIBGOTV_API GOTV_FORWARD_DECLARE_OBJECT(libgotvptop_media_list_t *)
libgotvptop_media_subitems( libgotvptop_media_t *p_md );

/**
 * Get event manager from media descriptor object.
 * NOTE: this function doesn't increment reference counting.
 *
 * \param p_md a media descriptor object
 * \return event manager object
 */
LIBGOTV_API libgotvptop_event_manager_t *
    libgotvptop_media_event_manager( libgotvptop_media_t *p_md );

/**
 * Get duration (in ms) of media descriptor object item.
 *
 * \param p_md media descriptor object
 * \return duration of media item or -1 on error
 */
LIBGOTV_API libgotvptop_time_t
   libgotvptop_media_get_duration( libgotvptop_media_t *p_md );

/**
 * Parse the media asynchronously with options.
 *
 * This fetches (local or network) art, meta data and/or tracks information.
 * This method is the extended version of libgotvptop_media_parse_with_options().
 *
 * To track when this is over you can listen to libgotvptop_MediaParsedChanged
 * event. However if this functions returns an error, you will not receive any
 * events.
 *
 * It uses a flag to specify parse options (see libgotvptop_media_parse_flag_t). All
 * these flags can be combined. By default, media is parsed if it's a local
 * file.
 *
 * \note Parsing can be aborted with libgotvptop_media_parse_stop().
 *
 * \see libgotvptop_MediaParsedChanged
 * \see libgotvptop_media_get_meta
 * \see libgotvptop_media_tracks_get
 * \see libgotvptop_media_get_parsed_status
 * \see libgotvptop_media_parse_flag_t
 *
 * \param p_md media descriptor object
 * \param parse_flag parse options:
 * \param timeout maximum time allowed to preparse the media. If -1, the
 * default "preparse-timeout" option will be used as a timeout. If 0, it will
 * wait indefinitely. If > 0, the timeout will be used (in milliseconds).
 * \return -1 in case of error, 0 otherwise
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API int
libgotvptop_media_parse_with_options( libgotvptop_media_t *p_md,
                                 libgotvptop_media_parse_flag_t parse_flag,
                                 int timeout );

/**
 * Stop the parsing of the media
 *
 * When the media parsing is stopped, the libgotvptop_MediaParsedChanged event will
 * be sent with the libgotvptop_media_parsed_status_timeout status.
 *
 * \see libgotvptop_media_parse_with_options
 *
 * \param p_md media descriptor object
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API void
libgotvptop_media_parse_stop( libgotvptop_media_t *p_md );

/**
 * Get Parsed status for media descriptor object.
 *
 * \see libgotvptop_MediaParsedChanged
 * \see libgotvptop_media_parsed_status_t
 *
 * \param p_md media descriptor object
 * \return a value of the libgotvptop_media_parsed_status_t enum
 * \version LibGOTV 3.0.0 or later
 */
LIBGOTV_API libgotvptop_media_parsed_status_t
   libgotvptop_media_get_parsed_status( libgotvptop_media_t *p_md );

/**
 * Sets media descriptor's user_data. user_data is specialized data
 * accessed by the host application, GOTV.framework uses it as a pointer to
 * an native object that references a libgotvptop_media_t pointer
 *
 * \param p_md media descriptor object
 * \param p_new_user_data pointer to user data
 */
LIBGOTV_API void
    libgotvptop_media_set_user_data( libgotvptop_media_t *p_md, void *p_new_user_data );

/**
 * Get media descriptor's user_data. user_data is specialized data
 * accessed by the host application, GOTV.framework uses it as a pointer to
 * an native object that references a libgotvptop_media_t pointer
 *
 * \param p_md media descriptor object
 */
LIBGOTV_API void *libgotvptop_media_get_user_data( libgotvptop_media_t *p_md );

/**
 * Get media descriptor's elementary streams description
 *
 * Note, you need to call libgotvptop_media_parse() or play the media at least once
 * before calling this function.
 * Not doing this will result in an empty array.
 *
 * \version LibGOTV 2.1.0 and later.
 *
 * \param p_md media descriptor object
 * \param tracks address to store an allocated array of Elementary Streams
 *        descriptions (must be freed with libgotvptop_media_tracks_release
          by the caller) [OUT]
 *
 * \return the number of Elementary Streams (zero on error)
 */
LIBGOTV_API
unsigned libgotvptop_media_tracks_get( libgotvptop_media_t *p_md,
                                  libgotvptop_media_track_t ***tracks );

/**
 * Get codec description from media elementary stream
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \see libgotvptop_media_track_t
 *
 * \param i_type i_type from libgotvptop_media_track_t
 * \param i_codec i_codec or i_original_fourcc from libgotvptop_media_track_t
 *
 * \return codec description
 */
LIBGOTV_API
const char *libgotvptop_media_get_codec_description( libgotvptop_track_type_t i_type,
                                                uint32_t i_codec );

/**
 * Release media descriptor's elementary streams description array
 *
 * \version LibGOTV 2.1.0 and later.
 *
 * \param p_tracks tracks info array to release
 * \param i_count number of elements in the array
 */
LIBGOTV_API
void libgotvptop_media_tracks_release( libgotvptop_media_track_t **p_tracks,
                                  unsigned i_count );

/**
 * Get the media type of the media descriptor object
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \see libgotvptop_media_type_t
 *
 * \param p_md media descriptor object
 *
 * \return media type
 */
LIBGOTV_API
libgotvptop_media_type_t libgotvptop_media_get_type( libgotvptop_media_t *p_md );

/**
 * Add a slave to the current media.
 *
 * A slave is an external input source that may contains an additional subtitle
 * track (like a .srt) or an additional audio track (like a .ac3).
 *
 * \note This function must be called before the media is parsed (via
 * libgotvptop_media_parse_with_options()) or before the media is played (via
 * libgotvptop_media_player_play())
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \param p_md media descriptor object
 * \param i_type subtitle or audio
 * \param i_priority from 0 (low priority) to 4 (high priority)
 * \param psz_uri Uri of the slave (should contain a valid scheme).
 *
 * \return 0 on success, -1 on error.
 */
LIBGOTV_API
int libgotvptop_media_slaves_add( libgotvptop_media_t *p_md,
                             libgotvptop_media_slave_type_t i_type,
                             unsigned int i_priority,
                             const char *psz_uri );

/**
 * Clear all slaves previously added by libgotvptop_media_slaves_add() or
 * internally.
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \param p_md media descriptor object
 */
LIBGOTV_API
void libgotvptop_media_slaves_clear( libgotvptop_media_t *p_md );

/**
 * Get a media descriptor's slave list
 *
 * The list will contain slaves parsed by GOTV or previously added by
 * libgotvptop_media_slaves_add(). The typical use case of this function is to save
 * a list of slave in a database for a later use.
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \see libgotvptop_media_slaves_add
 *
 * \param p_md media descriptor object
 * \param ppp_slaves address to store an allocated array of slaves (must be
 * freed with libgotvptop_media_slaves_release()) [OUT]
 *
 * \return the number of slaves (zero on error)
 */
LIBGOTV_API
unsigned int libgotvptop_media_slaves_get( libgotvptop_media_t *p_md,
                                      libgotvptop_media_slave_t ***ppp_slaves );

/**
 * Release a media descriptor's slave list
 *
 * \version LibGOTV 3.0.0 and later.
 *
 * \param pp_slaves slave array to release
 * \param i_count number of elements in the array
 */
LIBGOTV_API
void libgotvptop_media_slaves_release( libgotvptop_media_slave_t **pp_slaves,
                                  unsigned int i_count );

#endif /* GOTV_LIBGOTV_MEDIA_H */
