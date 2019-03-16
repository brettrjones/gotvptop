/* dsa-sha256-sign.c

   The DSA publickey algorithm, using SHA-256 (FIPS186-3).

   Copyright (C) 2010 Niels Möller

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

#include "config_nettle.h"

#include "nettle_dsa-compat.h"

int
dsa_sha256_sign_digest(const struct dsa_public_key *pub,
		       const struct dsa_private_key *key,
		       void *random_ctx, nettle_random_func *randomFunc,
		       const uint8_t *digest,
		       struct dsa_signature *signature)
{
  return dsa_sign((const struct dsa_params *) pub, key->x,
		  random_ctx, randomFunc,
		  SHA256_DIGEST_SIZE, digest, signature);
}

int
dsa_sha256_sign(const struct dsa_public_key *pub,
		const struct dsa_private_key *key,
		void *random_ctx, nettle_random_func *randomFunc,
		struct sha256_ctx *hash,
		struct dsa_signature *signature)
{
  uint8_t digest[SHA256_DIGEST_SIZE];
  sha256_digest(hash, sizeof(digest), digest);

  return dsa_sign((const struct dsa_params *) pub, key->x,
		  random_ctx, randomFunc,
		  sizeof(digest), digest, signature);
}