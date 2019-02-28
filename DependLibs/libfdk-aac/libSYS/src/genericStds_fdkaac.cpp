
/* -----------------------------------------------------------------------------------------------------------
Software License for The Fraunhofer FDK AAC Codec Library for Android

© Copyright  1995 - 2015 Fraunhofer-Gesellschaft zur Förderung der angewandten Forschung e.V.
  All rights reserved.

 1.    INTRODUCTION
The Fraunhofer FDK AAC Codec Library for Android ("FDK AAC Codec") is software that implements
the MPEG Advanced Audio Coding ("AAC") encoding and decoding scheme for digital audio.
This FDK AAC Codec software is intended to be used on a wide variety of Android devices.

AAC's HE-AAC and HE-AAC v2 versions are regarded as today's most efficient general perceptual
audio codecs. AAC-ELD is considered the best-performing full-bandwidth communications codec by
independent studies and is widely deployed. AAC has been standardized by ISO and IEC as part
of the MPEG specifications.

Patent licenses for necessary patent claims for the FDK AAC Codec (including those of Fraunhofer)
may be obtained through Via Licensing (www.vialicensing.com) or through the respective patent owners
individually for the purpose of encoding or decoding bit streams in products that are compliant with
the ISO/IEC MPEG audio standards. Please note that most manufacturers of Android devices already license
these patent claims through Via Licensing or directly from the patent owners, and therefore FDK AAC Codec
software may already be covered under those patent licenses when it is used for those licensed purposes only.

Commercially-licensed AAC software libraries, including floating-point versions with enhanced sound quality,
are also available from Fraunhofer. Users are encouraged to check the Fraunhofer website for additional
applications information and documentation.

2.    COPYRIGHT LICENSE

Redistribution and use in source and binary forms, with or without modification, are permitted without
payment of copyright license fees provided that you satisfy the following conditions:

You must retain the complete text of this software license in redistributions of the FDK AAC Codec or
your modifications thereto in source code form.

You must retain the complete text of this software license in the documentation and/or other materials
provided with redistributions of the FDK AAC Codec or your modifications thereto in binary form.
You must make available free of charge copies of the complete source code of the FDK AAC Codec and your
modifications thereto to recipients of copies in binary form.

The name of Fraunhofer may not be used to endorse or promote products derived from this library without
prior written permission.

You may not charge copyright license fees for anyone to use, copy or distribute the FDK AAC Codec
software or your modifications thereto.

Your modified versions of the FDK AAC Codec must carry prominent notices stating that you changed the software
and the date of any change. For modified versions of the FDK AAC Codec, the term
"Fraunhofer FDK AAC Codec Library for Android" must be replaced by the term
"Third-Party Modified Version of the Fraunhofer FDK AAC Codec Library for Android."

3.    NO PATENT LICENSE

NO EXPRESS OR IMPLIED LICENSES TO ANY PATENT CLAIMS, including without limitation the patents of Fraunhofer,
ARE GRANTED BY THIS SOFTWARE LICENSE. Fraunhofer provides no warranty of patent non-infringement with
respect to this software.

You may use this FDK AAC Codec software or modifications thereto only for purposes that are authorized
by appropriate patent licenses.

4.    DISCLAIMER

This FDK AAC Codec software is provided by Fraunhofer on behalf of the copyright holders and contributors
"AS IS" and WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, including but not limited to the implied warranties
of merchantability and fitness for a particular purpose. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE for any direct, indirect, incidental, special, exemplary, or consequential damages,
including but not limited to procurement of substitute goods or services; loss of use, data, or profits,
or business interruption, however caused and on any theory of liability, whether in contract, strict
liability, or tort (including negligence), arising in any way out of the use of this software, even if
advised of the possibility of such damage.

5.    CONTACT INFORMATION

Fraunhofer Institute for Integrated Circuits IIS
Attention: Audio and Multimedia Departments - FDK AAC LL
Am Wolfsmantel 33
91058 Erlangen, Germany

www.iis.fraunhofer.de/amm
amm-info@iis.fraunhofer.de
----------------------------------------------------------------------------------------------------------- */

/**************************  Fraunhofer IIS FDK SysLib  **********************

   Author(s):
   Description: - Generic memory, stdio, string, etc. function wrappers or
                  builtins.
                - OS dependant function wrappers.

******************************************************************************/

#include <libfdk-aac/include/aacdecoder_lib.h>

#include "genericStds.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


/* library info */
#define SYS_LIB_VL0 1
#define SYS_LIB_VL1 3
#define SYS_LIB_VL2 8
#define SYS_LIB_TITLE "System Integration Library"
#ifdef __ANDROID__
#define SYS_LIB_BUILD_DATE ""
#define SYS_LIB_BUILD_TIME ""
#else
#define SYS_LIB_BUILD_DATE __DATE__
#define SYS_LIB_BUILD_TIME __TIME__
#endif



/***************************************************************
 * memory allocation monitoring variables
 ***************************************************************/


/* Include OS/System specific implementations. */
#if defined(__linux__) && !defined(__ANDROID__) /* cppp replaced: elif */
  #include "linux/genericStds_linux_fdkaac.cpp"
#endif


#if !(defined(USE_BUILTIN_STRING_FUNCTIONS) || defined(__SYMBIAN32__))
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef FUNCTION_FDKprintf
void  FDKprintf( const char* szFmt, ...)    {
  va_list ap;
  va_start(ap, szFmt);
  vprintf(szFmt, ap);
  va_end(ap);
#ifdef ARCH_WA_FLUSH_CONSOLE
  fflush(stdout);
#endif
}
#endif

#ifndef FUNCTION_FDKprintfErr
void  FDKprintfErr( const char* szFmt, ...) {
  va_list ap;
  va_start(ap, szFmt);
#if defined(ARCH_WA_SLOWCON)
  vprintf(szFmt, ap);
#else
  vfprintf(stderr, szFmt, ap);
#endif
  va_end(ap);
#ifdef ARCH_WA_FLUSH_CONSOLE
  fflush(stderr);
#endif
}
#endif

int FDKgetchar(void) { return getchar(); }

int32_t  FDKfprintf(FDKFILE  *stream,  const  char *format, ...) {
  int32_t chars = 0;
  va_list ap;
  va_start(ap, format);
  chars += vfprintf((FILE*)stream, format, ap);
  va_end(ap);
  return chars;
}

#ifndef FUNCTION_FDKsprintf
int32_t  FDKsprintf(char *str, const char *format, ...) {
  int32_t chars = 0;
  va_list ap;
  va_start(ap, format);
  chars += vsprintf(str, format, ap);
  va_end(ap);
  return chars;
}
#endif

#else

void FDKprintf( const char* szFmt, ...) { /* stub! */; }
void FDKprintfErr( const char* szFmt, ...) { /* stub! */; }
int32_t  FDKfprintf(FILE  *stream,  const  char *format, ...) { /*stub ! */; }
int32_t  FDKsprintf(char *str, const char *format, ...) { /* stub! */; }

#endif

/************************************************************************************************/


const char *FDKstrchr(const char *s, int32_t c)                       { return strchr(s, c); }
const char *FDKstrstr(const char *haystack, const char *needle)   { return strstr(haystack, needle); }
#ifndef FUNCTION_FDKstrcpy
char *FDKstrcpy(char *dest, const char *src)                      { return strcpy(dest, src); }
#endif
char *FDKstrncpy(char *dest, const char *src, uint32_t n)             { return strncpy(dest, src, n); }

/*************************************************************************
 * DYNAMIC MEMORY management (heap)
 *************************************************************************/

#ifndef FUNCTION_FDKcalloc
void *FDKcalloc (const uint32_t n, const uint32_t size)
{
  void* ptr;

  ptr = calloc(n, size);

  return ptr;
}
#endif

#ifndef FUNCTION_FDKmalloc
void *FDKmalloc (const uint32_t size)
{
  void* ptr;

  ptr = malloc(size);

  return ptr;
}
#endif

#ifndef FUNCTION_FDKfree
void  FDKfree (void *ptr)
{
  /* FDKprintf("f, heapSize: %d\n", heapSizeCurr); */
  free((int32_t*)ptr);
}
#endif

#ifndef FUNCTION_FDKaalloc
void *FDKaalloc(const uint32_t size, const uint32_t alignment)
{
  void *addr, *result=NULL;
  addr = FDKcalloc(1, size + alignment + sizeof(void*));               /* Malloc and clear memory.         */

  if (addr!=NULL)
  {
    result = ALIGN_PTR((unsigned char*)addr + sizeof(void*));    /* Get aligned memory base address. */
    *(((void**)result) - 1) = addr;                /* Save malloc'ed memory pointer.   */
  }

  return result;                                 /* Return aligned address.          */
}
#endif

#ifndef FUNCTION_FDKafree
void  FDKafree (void *ptr)
{
  void *addr;
  addr = *(((void**)ptr)-1); /* Get pointer to malloc'ed memory. */
  FDKfree(addr);                /* Free malloc'ed memory area.      */
}
#endif


#ifndef FUNCTION_FDKcalloc_L

/*--------------------------------------------------------------------------*
 * DATA MEMORY L1/L2 (fallback)
 *--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*
 * FDKcalloc_L
 *--------------------------------------------------------------------------*/
void *FDKcalloc_L(const uint32_t dim, const uint32_t size, MEMORY_SECTION s)
{
  int a_size;

  if (s == SECT_DATA_EXTERN)
    goto fallback;

  a_size = ((dim*size+3)&0xfffffffc); /* force 4 byte alignment (1111 .... 1111 1100) */





  //printf("Warning, out of internal memory\n");

fallback:
  return FDKcalloc(dim, size);
}
#endif /* FUNCTION_FDKcalloc_L */

#ifndef FUNCTION_FDKfree_L
void  FDKfree_L (void *p)
{

    FDKfree(p);
}
#endif /* FUNCTION_FDKfree_L */

#ifndef FUNCTION_FDKaalloc_L
void *FDKaalloc_L(const uint32_t size, const uint32_t alignment, MEMORY_SECTION s)
{
  void *addr, *result=NULL;
  addr = FDKcalloc_L(1, size + alignment + sizeof(void*), s);       /* Malloc and clear memory.         */

  if (addr!=NULL)
  {
    result = ALIGN_PTR((unsigned char *)addr + sizeof(void*));    /* Get aligned memory base address. */
    *(((void**)result) - 1) = addr;                /* Save malloc'ed memory pointer.   */
  }

  return result;                                 /* Return aligned address.          */
}
#endif

#ifndef FUNCTION_FDKafree_L
void  FDKafree_L (void *ptr)
{
  void *addr;

  addr = *(((void**)ptr)-1); /* Get pointer to malloc'ed memory. */
  FDKfree_L(addr);                /* Free malloc'ed memory area.      */
}
#endif



/*---------------------------------------------------------------------------------------
 * FUNCTION:    FDKmemcpy
 * DESCRIPTION: - copies memory from "src" to "dst" with length "size" bytes
 *              - compiled with FDK_DEBUG will give you warnings
 *---------------------------------------------------------------------------------------*/
void FDKmemcpy(void *dst, const void *src, const uint32_t size)
{

  /* do the copy */
  memcpy(dst, src, size);
}

void FDKmemmove(void *dst, const void *src, const uint32_t size)     { memmove(dst, src, size); }
void FDKmemset(void *memPtr, const int32_t value, const uint32_t size)   { memset(memPtr, value, size); }
void FDKmemclear(void *memPtr, const uint32_t size)                  { FDKmemset(memPtr,0,size); }
uint32_t FDKstrlen(const char *s)                                    { return (uint32_t)strlen(s); }

/* Compare function wrappers */
int32_t FDKmemcmp(const void *s1, const void *s2, const uint32_t size)  { return memcmp(s1, s2, size); }
int32_t FDKstrcmp(const char *s1, const char *s2)                   { return strcmp(s1, s2); }
int32_t FDKstrncmp(const char *s1, const char *s2, const uint32_t size) { return strncmp(s1, s2, size); }


/* Math function wrappers. Only intended for compatibility, not to be highly optimized. */

int32_t FDKabs(int32_t j) { return abs(j); }
double FDKfabs(double x) { return fabs(x); }
double FDKpow(double x, double y) { return pow(x,y); }
double FDKsqrt(double x) { return sqrt(x); }
double FDKatan(double x) { return atan(x); }
double FDKlog(double x) { return log(x); }
double FDKsin(double x) { return sin(x); }
double FDKcos(double x) { return cos(x); }
double FDKexp(double x) { return exp(x); }
double FDKatan2(double y, double x) { return atan2(y, x); }
double FDKacos(double x) { return acos(x); }
double FDKtan(double x) { return tan(x); }
double FDKfloor(double x) { return floor(x); }
double FDKceil(double x) { return ceil(x); }

int32_t   FDKatoi(const char *nptr) { return atoi(nptr); }
long  FDKatol(const char *nptr) { return atol(nptr); }
float FDKatof(const char *nptr) { return (float)atof(nptr); }


/* ==================== FILE I/O ====================== */

#if !defined(FUNCTION_FDKfopen)
FDKFILE *FDKfopen(const char *filename, const char *mode) { return fopen(filename, mode); }
#endif
#if !defined(FUNCTION_FDKfclose)
int32_t FDKfclose(FDKFILE *fp) { return fclose((FILE*)fp);}
#endif
#if !defined(FUNCTION_FDKfseek)
int32_t FDKfseek(FDKFILE *fp, int32_t OFFSET, int WHENCE) { return fseek((FILE*)fp, OFFSET, WHENCE);}
#endif
#if !defined(FUNCTION_FDKftell)
int32_t FDKftell(FDKFILE *fp) { return ftell((FILE*)fp); }
#endif
#if !defined(FUNCTION_FDKfflush)
int32_t FDKfflush(FDKFILE *fp) { return fflush((FILE*)fp); }
#endif
const int32_t FDKSEEK_SET = SEEK_SET;
const int32_t FDKSEEK_CUR = SEEK_CUR;
const int32_t FDKSEEK_END = SEEK_END;

#if !defined(FUNCTION_FDKfwrite)
uint32_t FDKfwrite(void *ptrf, int32_t size, uint32_t nmemb, FDKFILE *fp) { return fwrite(ptrf, size, nmemb, (FILE*)fp); }
#endif
#if !defined(FUNCTION_FDKfread)
uint32_t FDKfread(void *dst, int32_t size, uint32_t nmemb, FDKFILE *fp) { return fread(dst, size, nmemb, (FILE*)fp); }
#endif
#if !defined(FUNCTION_FDKfgets)
char* FDKfgets(void *dst, int32_t size, FDKFILE *fp) { return fgets((char *)dst, size, (FILE*)fp); }
#endif
#if !defined(FUNCTION_FDKrewind)
void FDKrewind(FDKFILE *fp) { FDKfseek((FILE*)fp,0,FDKSEEK_SET); }
#endif


uint32_t FDKfwrite_EL(void *ptrf, int32_t size, uint32_t nmemb, FDKFILE *fp) {

    if (IS_LITTLE_ENDIAN()) {
      FDKfwrite(ptrf, size, nmemb, fp);
    } else {
      uint32_t n;
      int32_t s;

      uint8_t *ptr = (uint8_t*) ptrf;

      for (n=0; n<nmemb; n++) {
        for (s=size-1; s>=0; s--) {
          //FDKprintf("char = %c\n", (char)*(ptr+s));
          FDKfwrite(ptr + s, 1, 1, fp);
        }
        ptr = ptr + size;
      }
    }
    return nmemb;
}


uint32_t FDKfread_EL(void *dst, int32_t size, uint32_t nmemb, FDKFILE *fp) {
  uint32_t n, s0, s1, err;
  uint8_t tmp, *ptr;
  uint8_t tmp24[3];

  /* Enforce alignment of 24 bit data. */
  if (size == 3) {
    ptr = (uint8_t*)dst;
    err = 0;
    for (n=0; n<nmemb; n++) {
      if ((err = FDKfread(tmp24, 1, 3, fp)) != 3) {
        return err;
      }
      *ptr++ = tmp24[0];
      *ptr++ = tmp24[1];
      *ptr++ = tmp24[2];
      /* Sign extension */
      if (tmp24[2] & 0x80) {
        *ptr++ = 0xff;
      } else {
        *ptr++ = 0;
      }
    }
    err = nmemb;
    size = sizeof(int32_t);
  } else {
    if ((err = FDKfread(dst, size, nmemb, fp)) != nmemb) {
      return err;
    }
  }
  if (!IS_LITTLE_ENDIAN() && size > 1) {
    ptr = (uint8_t*)dst;
    for (n=0; n<nmemb; n++) {
      for (s0=0, s1=size-1; s0 < s1; s0++, s1--) {
        tmp = ptr[s0];
        ptr[s0] = ptr[s1];
        ptr[s1] = tmp;
      }
      ptr += size;
    }
  }
  return err;
}

int32_t FDKfeof(FDKFILE *fp) { return feof((FILE*)fp); }

/* Global initialization/cleanup */

#if defined(_DEBUG) && defined(_WIN32) && !defined(_WIN32_WCE)
  //#define _CRTDBG_MAP_ALLOC // causes definition conflict
  #include <crtdbg.h>
#endif




void FDKprintDisclaimer(void)
{
  FDKprintf(
  "This program is protected by copyright law and international treaties.\n"  \
  "Any reproduction or distribution of this program, or any portion\n"        \
  "of it, may result in severe civil and criminal penalties, and will be\n"   \
  "prosecuted to the maximum extent possible under law.\n\n");
}

