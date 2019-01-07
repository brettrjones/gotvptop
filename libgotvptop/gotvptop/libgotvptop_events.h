/*****************************************************************************
 * libgotvptop_events.h:  libgotvptop_events external API structure
 *****************************************************************************
 * Copyright (C) 1998-2010 GOTV authors and VideoLAN
 * $Id $
 *
 * Authors: Filippo Carone <littlejohn@videolan.org>
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

#ifndef LIBGOTV_EVENTS_H
#define LIBGOTV_EVENTS_H 1

/**
 * \file
 * This file defines libgotvptop_event external API
 */

typedef struct libgotvptop_renderer_item_t libgotvptop_renderer_item_t;

/**
 * \ingroup libgotvptop_event
 * @{
 */

/**
 * Event types
 */
enum libgotvptop_event_e {
    /* Append new event types at the end of a category.
     * Do not remove, insert or re-order any entry.
     * Keep this in sync with lib/event.c:libgotvptop_event_type_name(). */
    libgotvptop_MediaMetaChanged=0,
    libgotvptop_MediaSubItemAdded,
    libgotvptop_MediaDurationChanged,
    libgotvptop_MediaParsedChanged,
    libgotvptop_MediaFreed,
    libgotvptop_MediaStateChanged,
    libgotvptop_MediaSubItemTreeAdded,

    libgotvptop_MediaPlayerMediaChanged=0x100,
    libgotvptop_MediaPlayerNothingSpecial,
    libgotvptop_MediaPlayerOpening,
    libgotvptop_MediaPlayerBuffering,
    libgotvptop_MediaPlayerPlaying,
    libgotvptop_MediaPlayerPaused,
    libgotvptop_MediaPlayerStopped,
    libgotvptop_MediaPlayerForward,
    libgotvptop_MediaPlayerBackward,
    libgotvptop_MediaPlayerEndReached,
    libgotvptop_MediaPlayerEncounteredError,
    libgotvptop_MediaPlayerTimeChanged,
    libgotvptop_MediaPlayerPositionChanged,
    libgotvptop_MediaPlayerSeekableChanged,
    libgotvptop_MediaPlayerPausableChanged,
    libgotvptop_MediaPlayerTitleChanged,
    libgotvptop_MediaPlayerSnapshotTaken,
    libgotvptop_MediaPlayerLengthChanged,
    libgotvptop_MediaPlayerVout,
    libgotvptop_MediaPlayerScrambledChanged,
    libgotvptop_MediaPlayerESAdded,
    libgotvptop_MediaPlayerESDeleted,
    libgotvptop_MediaPlayerESSelected,
    libgotvptop_MediaPlayerCorked,
    libgotvptop_MediaPlayerUncorked,
    libgotvptop_MediaPlayerMuted,
    libgotvptop_MediaPlayerUnmuted,
    libgotvptop_MediaPlayerAudioVolume,
    libgotvptop_MediaPlayerAudioDevice,
    libgotvptop_MediaPlayerChapterChanged,

    libgotvptop_MediaListItemAdded=0x200,
    libgotvptop_MediaListWillAddItem,
    libgotvptop_MediaListItemDeleted,
    libgotvptop_MediaListWillDeleteItem,
    libgotvptop_MediaListEndReached,

    libgotvptop_MediaListViewItemAdded=0x300,
    libgotvptop_MediaListViewWillAddItem,
    libgotvptop_MediaListViewItemDeleted,
    libgotvptop_MediaListViewWillDeleteItem,

    libgotvptop_MediaListPlayerPlayed=0x400,
    libgotvptop_MediaListPlayerNextItemSet,
    libgotvptop_MediaListPlayerStopped,

    /**
     * \deprecated Useless event, it will be triggered only when calling
     * libgotvptop_media_discoverer_start()
     */
    libgotvptop_MediaDiscovererStarted=0x500,
    /**
     * \deprecated Useless event, it will be triggered only when calling
     * libgotvptop_media_discoverer_stop()
     */
    libgotvptop_MediaDiscovererEnded,

    libgotvptop_RendererDiscovererItemAdded,
    libgotvptop_RendererDiscovererItemDeleted,

    libgotvptop_VlmMediaAdded=0x600,
    libgotvptop_VlmMediaRemoved,
    libgotvptop_VlmMediaChanged,
    libgotvptop_VlmMediaInstanceStarted,
    libgotvptop_VlmMediaInstanceStopped,
    libgotvptop_VlmMediaInstanceStatusInit,
    libgotvptop_VlmMediaInstanceStatusOpening,
    libgotvptop_VlmMediaInstanceStatusPlaying,
    libgotvptop_VlmMediaInstanceStatusPause,
    libgotvptop_VlmMediaInstanceStatusEnd,
    libgotvptop_VlmMediaInstanceStatusError
};

/**
 * A LibGOTV event
 */
typedef struct libgotvptop_event_t
{
    int   type; /**< Event type (see @ref libgotvptop_event_e) */
    void *p_obj; /**< Object emitting the event */
    union
    {
        /* media descriptor */
        struct
        {
            libgotvptop_meta_t meta_type;
        } media_meta_changed;
        struct
        {
            libgotvptop_media_t * new_child;
        } media_subitem_added;
        struct
        {
            int64_t new_duration;
        } media_duration_changed;
        struct
        {
            int new_status; /**< see @ref libgotvptop_media_parsed_status_t */
        } media_parsed_changed;
        struct
        {
            libgotvptop_media_t * md;
        } media_freed;
        struct
        {
            int new_state; /**< see @ref libgotvptop_state_t */
        } media_state_changed;
        struct
        {
            libgotvptop_media_t * item;
        } media_subitemtree_added;

        /* media instance */
        struct
        {
            float new_cache;
        } media_player_buffering;
        struct
        {
            int new_chapter;
        } media_player_chapter_changed;
        struct
        {
            float new_position;
        } media_player_position_changed;
        struct
        {
            libgotvptop_time_t new_time;
        } media_player_time_changed;
        struct
        {
            int new_title;
        } media_player_title_changed;
        struct
        {
            int new_seekable;
        } media_player_seekable_changed;
        struct
        {
            int new_pausable;
        } media_player_pausable_changed;
        struct
        {
            int new_scrambled;
        } media_player_scrambled_changed;
        struct
        {
            int new_count;
        } media_player_vout;

        /* media list */
        struct
        {
            libgotvptop_media_t * item;
            int index;
        } media_list_item_added;
        struct
        {
            libgotvptop_media_t * item;
            int index;
        } media_list_will_add_item;
        struct
        {
            libgotvptop_media_t * item;
            int index;
        } media_list_item_deleted;
        struct
        {
            libgotvptop_media_t * item;
            int index;
        } media_list_will_delete_item;

        /* media list player */
        struct
        {
            libgotvptop_media_t * item;
        } media_list_player_next_item_set;

        /* snapshot taken */
        struct
        {
             char* psz_filename ;
        } media_player_snapshot_taken ;

        /* Length changed */
        struct
        {
            libgotvptop_time_t   new_length;
        } media_player_length_changed;

        /* VLM media */
        struct
        {
            const char * psz_media_name;
            const char * psz_instance_name;
        } vlm_media_event;

        /* Extra MediaPlayer */
        struct
        {
            libgotvptop_media_t * new_media;
        } media_player_media_changed;

        struct
        {
            libgotvptop_track_type_t i_type;
            int                 i_id;
        } media_player_es_changed;

        struct
        {
            float volume;
        } media_player_audio_volume;

        struct
        {
            const char *device;
        } media_player_audio_device;

        struct
        {
            libgotvptop_renderer_item_t *item;
        } renderer_discoverer_item_added;
        struct
        {
            libgotvptop_renderer_item_t *item;
        } renderer_discoverer_item_deleted;
    } u; /**< Type-dependent event description */
} libgotvptop_event_t;



#endif /* _LIBGOTV_EVENTS_H */
