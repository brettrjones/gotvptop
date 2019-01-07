/*****************************************************************************
 * gotvptop_inhibit.h: GOTV screen saver inhibition
 *****************************************************************************
 * Copyright (C) 2009 Rémi Denis-Courmont
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

/**
 * \file
 * This file defines the interface for screen-saver inhibition modules
 */

#ifndef GOTV_INHIBIT_H
# define GOTV_INHIBIT_H 1

typedef struct gotvptop_inhibit gotvptop_inhibit_t;
typedef struct gotvptop_inhibit_sys gotvptop_inhibit_sys_t;

enum gotvptop_inhibit_flags
{
    GOTV_INHIBIT_NONE=0 /*< No inhibition */,
    GOTV_INHIBIT_SUSPEND=0x1 /*< Processor is in use - do not suspend */,
    GOTV_INHIBIT_DISPLAY=0x2 /*< Display is in use - do not blank/lock */,
#define GOTV_INHIBIT_AUDIO (GOTV_INHIBIT_SUSPEND)
#define GOTV_INHIBIT_VIDEO (GOTV_INHIBIT_SUSPEND|GOTV_INHIBIT_DISPLAY)
};

struct gotvptop_inhibit
{
    struct gotvptop_common_members obj;

    gotvptop_inhibit_sys_t *p_sys;
    void (*inhibit) (gotvptop_inhibit_t *, unsigned flags);
};

static inline void gotvptop_inhibit_Set (gotvptop_inhibit_t *ih, unsigned flags)
{
    ih->inhibit (ih, flags);
}

#endif
