
/* -----------------------------------------------------------------------------------------------------------
Software License for The Fraunhofer FDK AAC Codec Library for Android

© Copyright  1995 - 2013 Fraunhofer-Gesellschaft zur Förderung der angewandten Forschung e.V.
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

/******************************** MPEG Audio Encoder **************************

   Initial author:       M.Werner
   contents/description: Noiseless coder module

******************************************************************************/

#ifndef __DYN_BITS_H
#define __DYN_BITS_H

#include "common_fix.h"

#include "psy_const.h"
#include "aacenc_tns.h"

#define MAX_SECTIONS          MAX_GROUPED_SFB
#define SECT_ESC_VAL_LONG    31
#define SECT_ESC_VAL_SHORT    7
#define CODE_BOOK_BITS        4
#define SECT_BITS_LONG        5
#define SECT_BITS_SHORT       3
#define PNS_PCM_BITS          9

typedef struct
{
  int32_t codeBook;
  int32_t sfbStart;
  int32_t sfbCnt;
  int32_t sectionBits;              /* huff + si ! */
} SECTION_INFO;


typedef struct
{
  int32_t blockType;
  int32_t noOfGroups;
  int32_t sfbCnt;
  int32_t maxSfbPerGroup;
  int32_t sfbPerGroup;
  int32_t noOfSections;
  SECTION_INFO huffsection[MAX_SECTIONS];
  int32_t sideInfoBits;             /* sectioning bits       */
  int32_t huffmanBits;              /* huffman    coded bits */
  int32_t scalefacBits;             /* scalefac   coded bits */
  int32_t noiseNrgBits;             /* noiseEnergy coded bits */
  int32_t firstScf;                 /* first scf to be coded */
} SECTION_DATA;


struct BITCNTR_STATE
{
  int32_t *bitLookUp;
  int32_t *mergeGainLookUp;
};


int32_t  FDKaacEnc_BCNew(BITCNTR_STATE **phBC
          ,uint8_t* dynamic_RAM
          );

void FDKaacEnc_BCClose(BITCNTR_STATE **phBC);

#if defined(PNS_PRECOUNT_ENABLE)
int32_t  noisePreCount(const int32_t *noiseNrg, int32_t maxSfb);
#endif

int32_t FDKaacEnc_dynBitCount(
        BITCNTR_STATE* const         hBC,
        const int16_t* const           quantSpectrum,
        const uint32_t* const            maxValueInSfb,
        const int32_t* const             scalefac,
        const int32_t                    blockType,
        const int32_t                    sfbCnt,
        const int32_t                    maxSfbPerGroup,
        const int32_t                    sfbPerGroup,
        const int32_t* const             sfbOffset,
        SECTION_DATA* const RESTRICT sectionData,
        const int32_t* const             noiseNrg,
        const int32_t* const             isBook,
        const int32_t* const             isScale,
        const uint32_t                   syntaxFlags
        );

#endif
