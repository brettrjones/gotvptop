/* uint64_t-like operations that work even on hosts lacking uint64_t

   Copyright (C) 2006, 2009-2017 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert.  */

#include <stdint.h>

#ifndef _GL_INLINE_HEADER_BEGIN
 #error "Please include config.h first."
#endif
_GL_INLINE_HEADER_BEGIN
#ifndef _GL_U64_INLINE
# define _GL_U64_INLINE _GL_INLINE
#endif

/* Return X rotated left by N bits, where 0 < N < 64.  */
#define u64rol(x, n) u64or (u64shl (x, n), u64shr (x, 64 - n))

#ifdef UINT64_MAX

/* Native implementations are trivial.  See below for comments on what
   these operations do.  */
typedef uint64_t uint64_t;
# define u64hilo(hi, lo) ((uint64_t) (((uint64_t) (hi) << 32) + (lo)))
# define u64init(hi, lo) u64hilo (hi, lo)
# define u64lo(x) ((uint64_t) (x))
# define u64size(x) u64lo (x)
# define u64lt(x, y) ((x) < (y))
# define u64and(x, y) ((x) & (y))
# define u64or(x, y) ((x) | (y))
# define u64xor(x, y) ((x) ^ (y))
# define u64plus(x, y) ((x) + (y))
# define u64shl(x, n) ((x) << (n))
# define u64shr(x, n) ((x) >> (n))

#else

/* uint64_t is a 64-bit unsigned integer value.
   u64init (HI, LO), is like u64hilo (HI, LO), but for use in
   initializer contexts.  */
# ifdef WORDS_BIGENDIAN
typedef struct { uint32_t hi, lo; } uint64_t;
#  define u64init(hi, lo) { hi, lo }
# else
typedef struct { uint32_t lo, hi; } uint64_t;
#  define u64init(hi, lo) { lo, hi }
# endif

/* Given the high and low-order 32-bit quantities HI and LO, return a uint64_t
   value representing (HI << 32) + LO.  */
_GL_U64_INLINE uint64_t
u64hilo (uint32_t hi, uint32_t lo)
{
  uint64_t r;
  r.hi = hi;
  r.lo = lo;
  return r;
}

/* Return a uint64_t value representing LO.  */
_GL_U64_INLINE uint64_t
u64lo (uint32_t lo)
{
  uint64_t r;
  r.hi = 0;
  r.lo = lo;
  return r;
}

/* Return a uint64_t value representing SIZE.  */
_GL_U64_INLINE uint64_t
u64size (size_t size)
{
  uint64_t r;
  r.hi = size >> 31 >> 1;
  r.lo = size;
  return r;
}

/* Return X < Y.  */
_GL_U64_INLINE int
u64lt (uint64_t x, uint64_t y)
{
  return x.hi < y.hi || (x.hi == y.hi && x.lo < y.lo);
}

/* Return X & Y.  */
_GL_U64_INLINE uint64_t
u64and (uint64_t x, uint64_t y)
{
  uint64_t r;
  r.hi = x.hi & y.hi;
  r.lo = x.lo & y.lo;
  return r;
}

/* Return X | Y.  */
_GL_U64_INLINE uint64_t
u64or (uint64_t x, uint64_t y)
{
  uint64_t r;
  r.hi = x.hi | y.hi;
  r.lo = x.lo | y.lo;
  return r;
}

/* Return X ^ Y.  */
_GL_U64_INLINE uint64_t
u64xor (uint64_t x, uint64_t y)
{
  uint64_t r;
  r.hi = x.hi ^ y.hi;
  r.lo = x.lo ^ y.lo;
  return r;
}

/* Return X + Y.  */
_GL_U64_INLINE uint64_t
u64plus (uint64_t x, uint64_t y)
{
  uint64_t r;
  r.lo = x.lo + y.lo;
  r.hi = x.hi + y.hi + (r.lo < x.lo);
  return r;
}

/* Return X << N.  */
_GL_U64_INLINE uint64_t
u64shl (uint64_t x, int n)
{
  uint64_t r;
  if (n < 32)
    {
      r.hi = (x.hi << n) | (x.lo >> (32 - n));
      r.lo = x.lo << n;
    }
  else
    {
      r.hi = x.lo << (n - 32);
      r.lo = 0;
    }
  return r;
}

/* Return X >> N.  */
_GL_U64_INLINE uint64_t
u64shr (uint64_t x, int n)
{
  uint64_t r;
  if (n < 32)
    {
      r.hi = x.hi >> n;
      r.lo = (x.hi << (32 - n)) | (x.lo >> n);
    }
  else
    {
      r.hi = 0;
      r.lo = x.hi >> (n - 32);
    }
  return r;
}

#endif

_GL_INLINE_HEADER_END
