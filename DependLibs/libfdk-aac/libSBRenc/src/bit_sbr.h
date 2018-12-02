
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

/*!
  \file
  \brief  SBR bit writing  
*/
#ifndef __BIT_SBR_H
#define __BIT_SBR_H

#include "sbr_def.h"
#include "cmondata.h"
#include "fram_gen.h"

struct SBR_ENV_DATA;

struct SBR_BITSTREAM_DATA
{
  int32_t TotalBits;
  int32_t PayloadBits;
  int32_t FillBits;
  int32_t HeaderActive;
  int32_t NrSendHeaderData;            /**< input from commandline */
  int32_t CountSendHeaderData;         /**< modulo count. If < 0 then no counting is done (no SBR headers) */
};

typedef struct SBR_BITSTREAM_DATA  *HANDLE_SBR_BITSTREAM_DATA;

struct SBR_HEADER_DATA
{
  AMP_RES sbr_amp_res;
  int32_t sbr_start_frequency;
  int32_t sbr_stop_frequency;
  int32_t sbr_xover_band;
  int32_t sbr_noise_bands;
  int32_t sbr_data_extra;
  int32_t header_extra_1;
  int32_t header_extra_2;
  int32_t sbr_lc_stereo_mode;
  int32_t sbr_limiter_bands;
  int32_t sbr_limiter_gains;
  int32_t sbr_interpol_freq;
  int32_t sbr_smoothing_length;
  int32_t alterScale;
  int32_t freqScale;

  /*
    element of channelpairelement
  */
  int32_t coupling;
  int32_t prev_coupling;

  /*
    element of singlechannelelement
  */

};
typedef struct SBR_HEADER_DATA *HANDLE_SBR_HEADER_DATA;

struct SBR_ENV_DATA
{

  int32_t sbr_xpos_ctrl;
  FREQ_RES freq_res_fixfix[2];
  uint8_t fResTransIsLow;

  INVF_MODE sbr_invf_mode;
  INVF_MODE sbr_invf_mode_vec[MAX_NUM_NOISE_VALUES];

  XPOS_MODE sbr_xpos_mode;

  int32_t ienvelope[MAX_ENVELOPES][MAX_FREQ_COEFFS];

  int32_t codeBookScfLavBalance;
  int32_t codeBookScfLav;
  const int32_t *hufftableTimeC;
  const int32_t *hufftableFreqC;
  const uint8_t *hufftableTimeL;
  const uint8_t *hufftableFreqL;

  const int32_t *hufftableLevelTimeC;
  const int32_t *hufftableBalanceTimeC;
  const int32_t *hufftableLevelFreqC;
  const int32_t *hufftableBalanceFreqC;
  const uint8_t *hufftableLevelTimeL;
  const uint8_t *hufftableBalanceTimeL;
  const uint8_t *hufftableLevelFreqL;
  const uint8_t *hufftableBalanceFreqL;


  const uint8_t *hufftableNoiseTimeL;
  const int32_t *hufftableNoiseTimeC;
  const uint8_t *hufftableNoiseFreqL;
  const int32_t *hufftableNoiseFreqC;

  const uint8_t *hufftableNoiseLevelTimeL;
  const int32_t *hufftableNoiseLevelTimeC;
  const uint8_t *hufftableNoiseBalanceTimeL;
  const int32_t *hufftableNoiseBalanceTimeC;
  const uint8_t *hufftableNoiseLevelFreqL;
  const int32_t *hufftableNoiseLevelFreqC;
  const uint8_t *hufftableNoiseBalanceFreqL;
  const int32_t *hufftableNoiseBalanceFreqC;

  HANDLE_SBR_GRID hSbrBSGrid;

  int32_t noHarmonics;
  int32_t addHarmonicFlag;
  uint8_t addHarmonic[MAX_FREQ_COEFFS];


  /* calculated helper vars */
  int32_t si_sbr_start_env_bits_balance;
  int32_t si_sbr_start_env_bits;
  int32_t si_sbr_start_noise_bits_balance;
  int32_t si_sbr_start_noise_bits;

  int32_t noOfEnvelopes;
  int32_t noScfBands[MAX_ENVELOPES];
  int32_t domain_vec[MAX_ENVELOPES];
  int32_t domain_vec_noise[MAX_ENVELOPES];
  int8_t sbr_noise_levels[MAX_FREQ_COEFFS];
  int32_t noOfnoisebands;

  int32_t balance;
  AMP_RES init_sbr_amp_res;
  AMP_RES currentAmpResFF;
  FIXP_DBL ton_HF[SBR_GLOBAL_TONALITY_VALUES]; /* tonality is scaled by 2^19/0.524288f (fract part of RELAXATION) */
  FIXP_DBL global_tonality;

  /* extended data */
  int32_t extended_data;
  int32_t extension_size;
  int32_t extension_id;
  uint8_t extended_data_buffer[SBR_EXTENDED_DATA_MAX_CNT];

  uint8_t ldGrid;
};
typedef struct SBR_ENV_DATA *HANDLE_SBR_ENV_DATA;



int32_t FDKsbrEnc_WriteEnvSingleChannelElement(struct SBR_HEADER_DATA    *sbrHeaderData,
                                 struct T_PARAMETRIC_STEREO *hParametricStereo,
                                 struct SBR_BITSTREAM_DATA *sbrBitstreamData,
                                 struct SBR_ENV_DATA       *sbrEnvData,
                                 struct COMMON_DATA        *cmonData,
                                 uint32_t                       sbrSyntaxFlags);


int32_t FDKsbrEnc_WriteEnvChannelPairElement(struct SBR_HEADER_DATA    *sbrHeaderData,
                               struct T_PARAMETRIC_STEREO *hParametricStereo,
                               struct SBR_BITSTREAM_DATA *sbrBitstreamData,
                               struct SBR_ENV_DATA       *sbrEnvDataLeft,
                               struct SBR_ENV_DATA       *sbrEnvDataRight,
                               struct COMMON_DATA        *cmonData,
                               uint32_t                       sbrSyntaxFlags);



int32_t FDKsbrEnc_CountSbrChannelPairElement (struct SBR_HEADER_DATA     *sbrHeaderData,
                                struct T_PARAMETRIC_STEREO *hParametricStereo,
                                struct SBR_BITSTREAM_DATA  *sbrBitstreamData,
                                struct SBR_ENV_DATA        *sbrEnvDataLeft,
                                struct SBR_ENV_DATA        *sbrEnvDataRight,
                                struct COMMON_DATA         *cmonData,
                                uint32_t                        sbrSyntaxFlags);



/* debugging and tuning functions */

/*#define SBR_ENV_STATISTICS */


/*#define SBR_PAYLOAD_MONITOR*/

#endif
