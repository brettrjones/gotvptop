
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

/*!
  \file
  \brief  Defines structures for RVLC
  \author Robert Weidner
*/
#ifndef RVLC_INFO_H
#define RVLC_INFO_H



#define FWD                           0     /* bitstream decoding direction forward (RVL coded part) */
#define BWD                           1     /* bitstream decoding direction backward (RVL coded part) */

#define MAX_RVL                       7     /* positive RVLC escape */
#define MIN_RVL                      -7     /* negative RVLC escape */
#define MAX_ALLOWED_DPCM_INDEX       14     /* the maximum allowed index of a decoded dpcm value (offset 'TABLE_OFFSET' incl --> must be subtracted) */
#define TABLE_OFFSET                  7     /* dpcm offset of valid output values of rvl table decoding, the rvl table ouly returns positive values, therefore the offset */
#define MAX_LEN_RVLC_CODE_WORD        9     /* max length of a RVL codeword in bits */
#define MAX_LEN_RVLC_ESCAPE_WORD     20     /* max length of huffman coded RVLC escape word in bits */

#define DPCM_NOISE_NRG_BITS           9
#define SF_OFFSET                   100     /* offset for correcting scf value */

#define CONCEAL_MAX_INIT           1311     /* arbitrary value */
#define CONCEAL_MIN_INIT          -1311     /* arbitrary value */

#define RVLC_MAX_SFB              ((8) * (16))

/* sideinfo of RVLC */
typedef struct
{
  /* ------- ESC 1 Data: --------- */     /* order of RVLC-bitstream components in bitstream (RVLC-initialization), every component appears only once in bitstream */
  int32_t        sf_concealment;              /* 1          */
  int32_t        rev_global_gain;             /* 2          */
  int16_t      length_of_rvlc_sf;           /* 3          */  /* original value, gets modified (subtract 9) in case of noise (PNS); is kept for later use */
  int32_t        dpcm_noise_nrg;              /* 4 optional */
  int32_t        sf_escapes_present;          /* 5          */
  int16_t      length_of_rvlc_escapes;      /* 6 optional */
  int32_t        dpcm_noise_last_position;    /* 7 optional */

  int32_t        dpcm_is_last_position;

  int16_t      length_of_rvlc_sf_fwd;       /* length_of_rvlc_sf used for forward decoding */
  int16_t      length_of_rvlc_sf_bwd;       /* length_of_rvlc_sf used for backward decoding */

  /* for RVL-Codeword decoder to distinguish between fwd and bwd decoding */
  int16_t     *pRvlBitCnt_RVL;
  uint16_t    *pBitstrIndxRvl_RVL;

  uint8_t      numWindowGroups;
  uint8_t      maxSfbTransmitted;
  uint8_t      first_noise_group;
  uint8_t      first_noise_band;
  uint8_t      direction;

  /* bitstream indices */
  uint16_t     bitstreamIndexRvlFwd;        /* base address of RVL-coded-scalefactor data (ESC 2) for forward  decoding */
  uint16_t     bitstreamIndexRvlBwd;        /* base address of RVL-coded-scalefactor data (ESC 2) for backward decoding */
  uint16_t     bitstreamIndexEsc;           /* base address where RVLC-escapes start (ESC 2) */

  /* decoding trees */
  const uint32_t *pHuffTreeRvlCodewds;
  const uint32_t *pHuffTreeRvlcEscape;

  /* escape counters */
  uint8_t      numDecodedEscapeWordsFwd;    /* when decoding RVL-codes forward  */
  uint8_t      numDecodedEscapeWordsBwd;    /* when decoding RVL-codes backward */
  uint8_t      numDecodedEscapeWordsEsc;    /* when decoding the escape-Words */

  int8_t      noise_used;
  int8_t      intensity_used;
  int8_t      sf_used;

  int16_t      firstScf;
  int16_t      lastScf;
  int16_t      firstNrg;
  int16_t      lastNrg;
  int16_t      firstIs;
  int16_t      lastIs;

  /* ------ RVLC error detection ------ */
  uint32_t       errorLogRvlc;                /* store RVLC errors  */
  int16_t      conceal_min;                 /* is set at backward decoding  */
  int16_t      conceal_max;                 /* is set at forward  decoding  */
  int16_t      conceal_min_esc;             /* is set at backward decoding  */
  int16_t      conceal_max_esc;             /* is set at forward  decoding  */
} CErRvlcInfo;

typedef CErRvlcInfo RVLC_INFO; /* temp */



#endif /* RVLC_INFO_H */
