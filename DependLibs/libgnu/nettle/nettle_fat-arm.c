/* fat-arm.c

   Copyright (C) 2015 Niels Möller

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
#ifdef TARGET_OS_ANDROID
#ifndef BUILD_NETTLE_GENERIC

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nettle-types.h"

#include "nettle_aes-internal.h"
#include "nettle_fat-setup.h"

struct arm_features
{
  /* /proc/cpuinfo "CPU Architecture" doesn't correspond exactly to
     ARM architecture version, but it's good enough for our purposes.
     Will be set to 5, 6, 7 or 8. */
  unsigned arch_version;
  int have_neon;
};

#define SKIP(s, slen, literal, llen)				\
  (((slen) >= (llen) && memcmp ((s), (literal), llen) == 0)	\
   ? ((slen) -= (llen), (s) += (llen), 1) : 0)
#define MATCH(s, slen, literal, llen)				\
  ((slen) == (llen) && memcmp ((s), (literal), llen) == 0)

static void
get_arm_features (struct arm_features *features)
{
  const char *s;
  features->arch_version = 5;
  features->have_neon = 0;

  s = secure_getenv (ENV_OVERRIDE);
  if (s)
    for (;;)
      {
	const char *sep = strchr (s, ',');
	size_t length = sep ? (size_t) (sep - s) : strlen(s);

	if (SKIP (s, length, "arch:", 5))
	  {
	    if (length == 1 && *s >= '0' && *s <= '9')
	      features->arch_version = *s - '0';
	  }
	else if (MATCH (s, length, "neon", 4))
	  features->have_neon = 1;
	if (!sep)
	  break;
	s = sep + 1;
      }
  else
    {
      FILE *f;
      char line[200];
      int seen_arch = 0;
      int seen_features = 0;

      f = fopen ("/proc/cpuinfo", "r");
      if (!f)
	return;
      while (seen_features + seen_arch < 2
	     && fgets (line, sizeof(line), f))
	{
	  char *sep;
	  char *p;
	  sep = strchr (line, ':');
	  if (!sep)
	    continue;
	  for (p = sep; p - line > 0 && p[-1] == '\t'; p--)
	    ;

	  *p = '\0';
	  p = sep+1;

	  if (strcmp (line, "Features") == 0)
	    {
	      features->have_neon = (strstr (p, " neon ") != NULL);
	      seen_features = 1;
	    }
	  else if (strcmp (line, "CPU architecture") == 0)
	    {
	      /* Don't use strtol, since it's locale dependent. */
	      while (p[0] == ' ')
		p++;
	      if (p[0] > '5' && p[0] <= '9')
		features->arch_version = p[0] - '0';
	      else if (strcmp (p, "AArch64") == 0)
		features->arch_version = 8;
	      seen_arch = 1;
	    }
	}
      if (features->arch_version >= 8)
	{
	  /* Neon is not required, and maybe not listed in feature flags */
	  features->have_neon = 1;
	}
      fclose (f);
    }
}



//DECLARE_FAT_FUNC(_nettle_aes_encrypt, aes_crypt_internal_func)
aes_crypt_internal_func _nettle_aes_encrypt;
static aes_crypt_internal_func _nettle_aes_encrypt_init;
static aes_crypt_internal_func * _nettle_aes_encrypt_vec = _nettle_aes_encrypt_init;

//DECLARE_FAT_FUNC_VAR(nettle_aes_encrypt, aes_crypt_internal_func, arm)
aes_crypt_internal_func _nettle_aes_encrypt_arm;

//DECLARE_FAT_FUNC_VAR(_nettle_aes_encrypt, aes_crypt_internal_func, armv6)
aes_crypt_internal_func _nettle_aes_encrypt_armv6;

//DECLARE_FAT_FUNC(_nettle_aes_decrypt, aes_crypt_internal_func)
aes_crypt_internal_func _nettle_aes_decrypt;
static aes_crypt_internal_func _nettle_aes_decrypt_init;
static aes_crypt_internal_func * _nettle_aes_decrypt_vec = _nettle_aes_decrypt_init;

//DECLARE_FAT_FUNC_VAR(_nettle_aes_decrypt, aes_crypt_internal_func, arm)
aes_crypt_internal_func nettle_aes_decrypt_arm;

//DECLARE_FAT_FUNC_VAR(_nettle_aes_decrypt, aes_crypt_internal_func, armv6)
aes_crypt_internal_func _nettle_aes_decrypt_armv6;

//DECLARE_FAT_FUNC(_nettle_salsa20_core, salsa20_core_func)
salsa20_core_func _nettle_salsa20_core;
static salsa20_core_func _nettle_salsa20_core_init;
static salsa20_core_func * _nettle_salsa20_core_vec = _nettle_salsa20_core_init;

//DECLARE_FAT_FUNC_VAR(salsa20_core, salsa20_core_func, c)
salsa20_core_func _nettle_salsa20_core_c;

//DECLARE_FAT_FUNC_VAR(salsa20_core, salsa20_core_func, neon)
salsa20_core_func _nettle_salsa20_core_neon;

//DECLARE_FAT_FUNC(_nettle_sha1_compress, sha1_compress_func)
sha1_compress_func _nettle_sha1_compress;
static sha1_compress_func _nettle_sha1_compress_init;
static sha1_compress_func * _nettle_sha1_compress_vec = _nettle_sha1_compress_init;

//DECLARE_FAT_FUNC_VAR(sha1_compress, sha1_compress_func, c)
sha1_compress_func sha1_compress_c;

//DECLARE_FAT_FUNC_VAR(sha1_compress, sha1_compress_func, armv6)
sha1_compress_func sha1_compress_armv6;

//DECLARE_FAT_FUNC(_nettle_sha256_compress, sha256_compress_func)
sha256_compress_func _nettle_sha256_compress;
static sha256_compress_func _nettle_sha256_compress_init;
static sha256_compress_func * _nettle_sha256_compress_vec = _nettle_sha256_compress_init;

//DECLARE_FAT_FUNC_VAR(sha256_compress, sha256_compress_func, c)
sha256_compress_func sha256_compress_c;

//DECLARE_FAT_FUNC_VAR(sha256_compress, sha256_compress_func, armv6)
sha256_compress_func sha256_compress_armv6;

//DECLARE_FAT_FUNC(_nettle_sha512_compress, sha512_compress_func)
sha512_compress_func _nettle_sha512_compress;
static sha512_compress_func _nettle_sha512_compress_init;
static sha512_compress_func * _nettle_sha512_compress_vec = _nettle_sha512_compress_init;

//DECLARE_FAT_FUNC_VAR(sha512_compress, sha512_compress_func, c)
sha512_compress_func sha512_compress_c;

//DECLARE_FAT_FUNC_VAR(sha512_compress, sha512_compress_func, neon)
sha512_compress_func sha512_compress_neon;

//DECLARE_FAT_FUNC(nettle_sha3_permute, sha3_permute_func)
sha3_permute_func nettle_sha3_permute;
static sha3_permute_func nettle_sha3_permute_init;
static sha3_permute_func * nettle_sha3_permute_vec = nettle_sha3_permute_init;

//DECLARE_FAT_FUNC_VAR(sha3_permute, sha3_permute_func, c)
sha3_permute_func sha3_permute_c;

//DECLARE_FAT_FUNC_VAR(sha3_permute, sha3_permute_func, neon)
sha3_permute_func sha3_permute_neon;

//DECLARE_FAT_FUNC(_nettle_umac_nh, umac_nh_func)
umac_nh_func _nettle_umac_nh;
static umac_nh_func _nettle_umac_nh_init;
static umac_nh_func * _nettle_umac_nh_vec = _nettle_umac_nh_init;

//DECLARE_FAT_FUNC_VAR(umac_nh, umac_nh_func, c);
umac_nh_func umac_nh_c;

//DECLARE_FAT_FUNC_VAR(umac_nh, umac_nh_func, neon);
umac_nh_func umac_nh_neon;

//DECLARE_FAT_FUNC(_nettle_umac_nh_n, umac_nh_n_func)
umac_nh_n_func _nettle_umac_nh_n;
static umac_nh_n_func _nettle_umac_nh_n_init;
static umac_nh_n_func * _nettle_umac_nh_n_vec = _nettle_umac_nh_n_init;

//DECLARE_FAT_FUNC_VAR(umac_nh_n, umac_nh_n_func, c);
umac_nh_n_func umac_nh_n_c;

//DECLARE_FAT_FUNC_VAR(umac_nh_n, umac_nh_n_func, neon);
umac_nh_n_func umac_nh_n_neon;



static void CONSTRUCTOR
nettle_fat_init (void)
{
  struct arm_features features;
  int verbose;

  get_arm_features (&features);

  verbose = getenv (ENV_VERBOSE) != NULL;
  if (verbose)
    fprintf (stderr, "libnettle: cpu features: arch:%d%s\n",
	     features.arch_version,
	     features.have_neon ? ",neon" : "");

  if (features.arch_version >= 6)
    {
      if (verbose)
	fprintf (stderr, "libnettle: enabling armv6 code.\n");
      _nettle_aes_encrypt_vec = _nettle_aes_encrypt_armv6;
      _nettle_aes_decrypt_vec = _nettle_aes_decrypt_armv6;
      _nettle_sha1_compress_vec = _nettle_sha1_compress_armv6;
      _nettle_sha256_compress_vec = _nettle_sha256_compress_armv6;
    }
  else
    {
      if (verbose)
	fprintf (stderr, "libnettle: not enabling armv6 code.\n");
      _nettle_aes_encrypt_vec = _nettle_aes_encrypt_arm;
      _nettle_aes_decrypt_vec = _nettle_aes_decrypt_arm;
      _nettle_sha1_compress_vec = _nettle_sha1_compress_c;
      _nettle_sha256_compress_vec = _nettle_sha256_compress_c;
    }
  if (features.have_neon)
    {
      if (verbose)
	fprintf (stderr, "libnettle: enabling neon code.\n");
      _nettle_salsa20_core_vec = _nettle_salsa20_core_neon;
      _nettle_sha512_compress_vec = _nettle_sha512_compress_neon;
      nettle_sha3_permute_vec = _nettle_sha3_permute_neon;
      _nettle_umac_nh_vec = _nettle_umac_nh_neon;
      _nettle_umac_nh_n_vec = _nettle_umac_nh_n_neon;
    }
  else
    {
      if (verbose)
	fprintf (stderr, "libnettle: not enabling neon code.\n");
      _nettle_salsa20_core_vec = _nettle_salsa20_core_c;
      _nettle_sha512_compress_vec = _nettle_sha512_compress_c;
      nettle_sha3_permute_vec = _nettle_sha3_permute_c;
      _nettle_umac_nh_vec = _nettle_umac_nh_c;
      _nettle_umac_nh_n_vec = _nettle_umac_nh_n_c;
    }
}
  
#endif //#ifndef BUILD_NETTLE_GENERIC

#endif // TARGET_OS_ANDROID

