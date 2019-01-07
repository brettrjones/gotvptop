/*****************************************************************************
 * gotvptop_probe.h: service probing interface
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

#ifndef GOTV_PROBE_H
# define GOTV_PROBE_H 1

# include <stdlib.h>

/**
 * \file
 * This file defines functions and structures to run-time probe GOTV extensions
 */

# ifdef __cplusplus
extern "C" {
# endif

void *gotvptop_probe (gotvptop_object_t *, const char *, size_t *);
#define gotvptop_probe(obj, cap, pcount) \
        gotvptop_probe(GOTV_OBJECT(obj), cap, pcount)

struct gotvptop_probe_t
{
    struct gotvptop_common_members obj;

    void  *list;
    size_t count;
};

typedef struct gotvptop_probe_t gotvptop_probe_t;

static inline int gotvptop_probe_add(gotvptop_probe_t *obj, const void *data,
                                size_t len)
{
    char *tab = (char *)realloc (obj->list, (obj->count + 1) * len);

    if (unlikely(tab == NULL))
        return GOTV_ENOMEM;
    memcpy(tab + (obj->count * len), data, len);
    obj->list = tab;
    obj->count++;
    return GOTV_SUCCESS;
}

# define GOTV_PROBE_CONTINUE GOTV_EGENERIC
# define GOTV_PROBE_STOP     GOTV_SUCCESS

# ifdef __cplusplus
}
# endif

#endif
