/* Copyright (c) 2003-2008 Jean-Marc Valin
   Copyright (c) 2007-2008 CSIRO
   Copyright (c) 2007-2009 Xiph.Org Foundation
   Written by Jean-Marc Valin */
/**
   @file arch.h
   @brief Various architecture definitions for CELT
*/
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   
   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef ARCH_H
#define ARCH_H

#include "celt_types_libcelt.h"

#define CELT_SIG_SCALE 32768.f

#define libcelt_fatal(str) _libcelt_fatal(str, __FILE__, __LINE__);
#ifdef ENABLE_ASSERTIONS
#include <stdio.h>
#include <stdlib.h>
static inline void _libcelt_fatal(const char *str, const char *file, int line)
{
   fprintf (stderr, "Fatal (internal) error in %s, line %d: %s\n", file, line, str);
   abort();
}
#define libcelt_assert(cond) {if (!(cond)) {libcelt_fatal("assertion failed: " #cond);}}
#define libcelt_assert2(cond, message) {if (!(cond)) {libcelt_fatal("assertion failed: " #cond "\n" message);}}
#else
#define libcelt_assert(cond)
#define libcelt_assert2(cond, message)
#endif

#define IMUL32(a,b) ((a)*(b))
#define UMUL32(a,b) ((libcelt_int32)(a)*(libcelt_int32)(b))
#define UMUL16_16(a,b) ((libcelt_int32)(a)*(libcelt_int32)(b))

#define ABS(x) ((x) < 0 ? (-(x)) : (x))      /**< Absolute integer value. */
#define ABS16(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define MIN16(a,b) ((a) < (b) ? (a) : (b))   /**< Minimum 16-bit value.   */
#define MAX16(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 32-bit value.  */
#define MIN32(a,b) ((a) < (b) ? (a) : (b))   /**< Minimum 32-bit value.   */
#define MAX32(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 32-bit value.   */
#define IMIN(a,b) ((a) < (b) ? (a) : (b))   /**< Minimum int value.   */
#define IMAX(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum int value.   */
#define UADD32(a,b) ((a)+(b))
#define USUB32(a,b) ((a)-(b))

#define PRINT_MIPS(file)

#ifdef FIXED_POINT

typedef libcelt_int16 libcelt_word16;
typedef libcelt_int32 libcelt_word32;

typedef libcelt_word32 libcelt_sig;
typedef libcelt_word16 libcelt_norm;
typedef libcelt_word32 libcelt_ener;
typedef libcelt_word32 libcelt_mask;

#define Q15ONE 32767
#define Q30ONE 1073741823

#define SIG_SHIFT 12

#define NORM_SCALING 16384
#define NORM_SCALING_1 (1.f/16384.f)
#define NORM_SHIFT 14

#define ENER_SCALING 16384.f
#define ENER_SCALING_1 (1.f/16384.f)
#define ENER_SHIFT 14

#define PGAIN_SCALING 32768.f
#define PGAIN_SCALING_1 (1.f/32768.f)
#define PGAIN_SHIFT 15

#define DB_SHIFT 10

#define EPSILON 1
#define VERY_SMALL 0
#define VERY_LARGE32 ((libcelt_word32)2147483647)
#define VERY_LARGE16 ((libcelt_word16)32767)
#define Q15_ONE ((libcelt_word16)32767)
#define Q15_ONE_1 (1.f/32768.f)

#define SCALEIN(a)	(a)
#define SCALEOUT(a)	(a)

#ifdef FIXED_DEBUG
#include "fixed_debug_libcelt.h"
#else

#include "fixed_generic_libcelt.h"

#ifdef ARM5E_ASM
#include "fixed_arm5e_libcelt.h"
#elif defined (ARM4_ASM)
#include "fixed_arm4_libcelt.h"
#elif defined (BFIN_ASM)
#include "fixed_bfin_libcelt.h"
#elif defined (TI_C5X_ASM)
#include "fixed_c5x_libcelt.h"
#elif defined (TI_C6X_ASM)
#include "fixed_c6x_libcelt.h"
#endif

#endif


#else /* FIXED_POINT */

typedef float libcelt_word16;
typedef float libcelt_word32;

typedef float libcelt_sig;
typedef float libcelt_norm;
typedef float libcelt_ener;
typedef float libcelt_pgain;
typedef float libcelt_mask;

#define Q15ONE 1.0f
#define Q30ONE 1.0f

#define NORM_SCALING 1.f
#define NORM_SCALING_1 1.f
#define ENER_SCALING 1.f
#define ENER_SCALING_1 1.f
#define PGAIN_SCALING 1.f
#define PGAIN_SCALING_1 1.f

#define EPSILON 1e-15f
#define VERY_SMALL 1e-15f
#define VERY_LARGE32 1e15f
#define VERY_LARGE16 1e15f
#define Q15_ONE ((libcelt_word16)1.f)
#define Q15_ONE_1 ((libcelt_word16)1.f)

#define QCONST16(x,bits) (x)
#define QCONST32(x,bits) (x)

#define NEG16(x) (-(x))
#define NEG32(x) (-(x))
#define EXTRACT16(x) (x)
#define EXTEND32(x) (x)
#define SHR16(a,shift) (a)
#define SHL16(a,shift) (a)
#define SHR32(a,shift) (a)
#define SHL32(a,shift) (a)
#define PSHR16(a,shift) (a)
#define PSHR32(a,shift) (a)
#define VSHR32(a,shift) (a)
#define SATURATE16(x,a) (x)
#define SATURATE32(x,a) (x)

#define PSHR(a,shift)   (a)
#define SHR(a,shift)    (a)
#define SHL(a,shift)    (a)
#define SATURATE(x,a)   (x)

#define ROUND16(a,shift)  (a)
#define HALF32(x)       (.5f*(x))

#define ADD16(a,b) ((a)+(b))
#define SUB16(a,b) ((a)-(b))
#define ADD32(a,b) ((a)+(b))
#define SUB32(a,b) ((a)-(b))
#define MULT16_16_16(a,b)     ((a)*(b))
#define MULT16_16(a,b)     ((libcelt_word32)(a)*(libcelt_word32)(b))
#define MAC16_16(c,a,b)     ((c)+(libcelt_word32)(a)*(libcelt_word32)(b))

#define MULT16_32_Q11(a,b)     ((a)*(b))
#define MULT16_32_Q13(a,b)     ((a)*(b))
#define MULT16_32_Q14(a,b)     ((a)*(b))
#define MULT16_32_Q15(a,b)     ((a)*(b))
#define MULT16_32_Q16(a,b)     ((a)*(b))
#define MULT16_32_P15(a,b)     ((a)*(b))

#define MULT32_32_Q31(a,b)     ((a)*(b))

#define MAC16_32_Q11(c,a,b)     ((c)+(a)*(b))
#define MAC16_32_Q15(c,a,b)     ((c)+(a)*(b))

#define MAC16_16_Q11(c,a,b)     ((c)+(a)*(b))
#define MAC16_16_Q13(c,a,b)     ((c)+(a)*(b))
#define MAC16_16_P13(c,a,b)     ((c)+(a)*(b))
#define MULT16_16_Q11_32(a,b)     ((a)*(b))
#define MULT16_16_Q13(a,b)     ((a)*(b))
#define MULT16_16_Q14(a,b)     ((a)*(b))
#define MULT16_16_Q15(a,b)     ((a)*(b))
#define MULT16_16_P15(a,b)     ((a)*(b))
#define MULT16_16_P13(a,b)     ((a)*(b))
#define MULT16_16_P14(a,b)     ((a)*(b))

#define DIV32_16(a,b)     (((libcelt_word32)(a))/(libcelt_word16)(b))
#define PDIV32_16(a,b)     (((libcelt_word32)(a))/(libcelt_word16)(b))
#define DIV32(a,b)     (((libcelt_word32)(a))/(libcelt_word32)(b))
#define PDIV32(a,b)     (((libcelt_word32)(a))/(libcelt_word32)(b))

#define SCALEIN(a)	((a)*CELT_SIG_SCALE)
#define SCALEOUT(a)	((a)*(1/CELT_SIG_SCALE))

#endif /* !FIXED_POINT */


#if defined (CONFIG_TI_C54X) || defined (CONFIG_TI_C55X)

/* 2 on TI C5x DSP */
#define BYTES_PER_CHAR 2 
#define BITS_PER_CHAR 16
#define LOG2_BITS_PER_CHAR 4

#else /* CONFIG_TI_C54X */

#define BYTES_PER_CHAR 1
#define BITS_PER_CHAR 8
#define LOG2_BITS_PER_CHAR 3

#endif /* !CONFIG_TI_C54X */

#ifndef GLOBAL_STACK_SIZE 
#ifdef FIXED_POINT
#define GLOBAL_STACK_SIZE 100000
#else
#define GLOBAL_STACK_SIZE 100000
#endif
#endif 

#endif /* ARCH_H */
