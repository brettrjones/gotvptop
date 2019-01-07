/*
 * Copyright (C) 2008-2012 Free Software Foundation, Inc.
 *
 * Author: Nikos Mavrogiannopoulos
 *
 * This file is part of GnuTLS.
 *
 * The GnuTLS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

#pragma once

#include "crypto.h"
#include <crypto-backend.h>

extern int crypto_rnd_prio;
extern void *gnutls_rnd_ctx;
extern gnutls_crypto_rnd_st _gnutls_rnd_ops;

int _gnutls_rnd(gnutls_rnd_level_t level, void *data, size_t len);
void _gnutls_rnd_refresh(void);


void _gnutls_rnd_deinit(void);
int _gnutls_rnd_init(void);

int _gnutls_rnd_check(void);

#ifndef TARGET_OS_WINDOWS
extern int _gnutls_urandom_fd;
#endif

