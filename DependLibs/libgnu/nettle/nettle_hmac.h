/* hmac.h

   HMAC message authentication code (RFC-2104).

   Copyright (C) 2001, 2002 Niels Möller

   This file is part of GNU Nettle.

   GNU Nettle is free software: you can redistribute it and/or
   modify it under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at your
       option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at your
       option) any later version.

   or both in parallel, as here.

   GNU Nettle is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see http://www.gnu.org/licenses/.
*/

#ifndef NETTLE_HMAC_H_INCLUDED
#define NETTLE_HMAC_H_INCLUDED

#include "nettle-meta.h"

#include "nettle_md5.h"
#include "nettle_ripemd160.h"
#include "nettle_sha1.h"
#include "nettle_sha2.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Namespace mangling */
	/*
#define nettle_hmac_set_key nettle_hmac_set_key
#define nettle_hmac_update nettle_hmac_update
#define nettle_hmac_digest nettle_hmac_digest
#define nettle_hmac_md5_set_key nettle_hmac_md5_set_key
#define nettle_hmac_md5_update nettle_hmac_md5_update
#define nettle_hmac_md5_digest nettle_hmac_md5_digest
#define nettle_hmac_ripemd160_set_key nettle_hmac_ripemd160_set_key
#define nettle_hmac_ripemd160_update nettle_hmac_ripemd160_update
#define nettle_hmac_ripemd160_digest nettle_hmac_ripemd160_digest
#define nettle_hmac_sha1_set_key nettle_hmac_sha1_set_key
#define nettle_hmac_sha1_update nettle_hmac_sha1_update
#define nettle_hmac_sha1_digest nettle_hmac_sha1_digest
#define nettle_hmac_sha224_set_key nettle_hmac_sha224_set_key
#define nettle_hmac_sha224_digest nettle_hmac_sha224_digest
#define nettle_hmac_sha256_set_key nettle_hmac_sha256_set_key
#define nettle_hmac_sha256_update nettle_hmac_sha256_update
#define nettle_hmac_sha256_digest nettle_hmac_sha256_digest
#define nettle_hmac_sha384_set_key nettle_hmac_sha384_set_key
#define nettle_hmac_sha384_digest nettle_hmac_sha384_digest
#define nettle_hmac_sha512_set_key nettle_hmac_sha512_set_key
#define nettle_hmac_sha512_update nettle_hmac_sha512_update
#define nettle_hmac_sha512_digest nettle_hmac_sha512_digest
*/

void
nettle_hmac_set_key(void *outer, void *inner, void *state,
	     const struct nettle_hash *hash,
	     size_t length, const uint8_t *key);

/* This function is not strictly needed, it's s just the same as the
 * hash update function. */
void
nettle_hmac_update(void *state,
	    const struct nettle_hash *hash,
	    size_t length, const uint8_t *data);

void
nettle_hmac_digest(const void *outer, const void *inner, void *state,
	    const struct nettle_hash *hash,
	    size_t length, uint8_t *digest);


#define HMAC_CTX(type) \
{ type outer; type inner; type state; }

#define HMAC_SET_KEY(ctx, hash, length, key)			\
  nettle_hmac_set_key( &(ctx)->outer, &(ctx)->inner, &(ctx)->state,	\
                (hash), (length), (key) )

#define HMAC_DIGEST(ctx, hash, length, digest)			\
  nettle_hmac_digest( &(ctx)->outer, &(ctx)->inner, &(ctx)->state,	\
               (hash), (length), (digest) )

/* HMAC using specific hash functions */

/* hmac-md5 */
struct nettle_hmac_md5_ctx HMAC_CTX(struct md5_ctx);

void
nettle_hmac_md5_set_key(struct nettle_hmac_md5_ctx *ctx,
		 size_t key_length, const uint8_t *key);

void
nettle_hmac_md5_update(struct nettle_hmac_md5_ctx *ctx,
		size_t length, const uint8_t *data);

void
nettle_hmac_md5_digest(struct nettle_hmac_md5_ctx *ctx,
		size_t length, uint8_t *digest);


/* hmac-ripemd160 */
struct nettle_hmac_ripemd160_ctx HMAC_CTX(struct ripemd160_ctx);

void
nettle_hmac_ripemd160_set_key(struct nettle_hmac_ripemd160_ctx *ctx,
		       size_t key_length, const uint8_t *key);

void
nettle_hmac_ripemd160_update(struct nettle_hmac_ripemd160_ctx *ctx,
		      size_t length, const uint8_t *data);

void
nettle_hmac_ripemd160_digest(struct nettle_hmac_ripemd160_ctx *ctx,
		      size_t length, uint8_t *digest);


/* hmac-sha1 */
struct nettle_hmac_sha1_ctx HMAC_CTX(struct sha1_ctx);

void
nettle_hmac_sha1_set_key(struct nettle_hmac_sha1_ctx *ctx,
		  size_t key_length, const uint8_t *key);

void
nettle_hmac_sha1_update(struct nettle_hmac_sha1_ctx *ctx,
		 size_t length, const uint8_t *data);

void
nettle_hmac_sha1_digest(struct nettle_hmac_sha1_ctx *ctx,
		 size_t length, uint8_t *digest);

/* hmac-sha256 */
struct nettle_hmac_sha256_ctx HMAC_CTX(struct sha256_ctx);

void
nettle_hmac_sha256_set_key(struct nettle_hmac_sha256_ctx *ctx,
		    size_t key_length, const uint8_t *key);

void
nettle_hmac_sha256_update(struct nettle_hmac_sha256_ctx *ctx,
		   size_t length, const uint8_t *data);

void
nettle_hmac_sha256_digest(struct nettle_hmac_sha256_ctx *ctx,
		   size_t length, uint8_t *digest);

/* hmac-sha224 */
#define nettle_hmac_sha224_ctx nettle_hmac_sha256_ctx

void
nettle_hmac_sha224_set_key(struct nettle_hmac_sha224_ctx *ctx,
		    size_t key_length, const uint8_t *key);

#define nettle_hmac_sha224_update nettle_hmac_sha256_update

void
nettle_hmac_sha224_digest(struct nettle_hmac_sha224_ctx *ctx,
		   size_t length, uint8_t *digest);

/* hmac-sha512 */
struct nettle_hmac_sha512_ctx HMAC_CTX(struct sha512_ctx);

void
nettle_hmac_sha512_set_key(struct nettle_hmac_sha512_ctx *ctx,
		    size_t key_length, const uint8_t *key);

void
nettle_hmac_sha512_update(struct nettle_hmac_sha512_ctx *ctx,
		   size_t length, const uint8_t *data);

void
nettle_hmac_sha512_digest(struct nettle_hmac_sha512_ctx *ctx,
		   size_t length, uint8_t *digest);

/* hmac-sha384 */
#define nettle_hmac_sha384_ctx nettle_hmac_sha512_ctx

void
nettle_hmac_sha384_set_key(struct nettle_hmac_sha512_ctx *ctx,
		    size_t key_length, const uint8_t *key);

#define nettle_hmac_sha384_update nettle_hmac_sha512_update

void
nettle_hmac_sha384_digest(struct nettle_hmac_sha512_ctx *ctx,
		   size_t length, uint8_t *digest);

#ifdef __cplusplus
}
#endif

#endif /* NETTLE_HMAC_H_INCLUDED */
