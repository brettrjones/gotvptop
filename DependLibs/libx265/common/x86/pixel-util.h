/*****************************************************************************
 * Copyright (C) 2013-2017 MulticoreWare, Inc
 *
 * Authors: Steve Borho <steve@borho.org>
;*          Min Chen <chenm003@163.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at license @ x265.com.
 *****************************************************************************/

#ifndef X265_PIXEL_UTIL_H
#define X265_PIXEL_UTIL_H

#define DEFINE_UTILS(cpu) \
    FUNCDEF_TU_S2(void, getResidual, cpu, const pixel* fenc, const pixel* pred, int16_t* residual, intptr_t stride); \
    FUNCDEF_TU_S2(void, transpose, cpu, pixel* dest, const pixel* src, intptr_t stride); \
    FUNCDEF_TU(int, count_nonzero, cpu, const int16_t* quantCoeff); \
    uint32_t PFX_X265(quant_ ## cpu(const int16_t* coef, const int32_t* quantCoeff, int32_t* deltaU, int16_t* qCoef, int qBits, int add, int numCoeff)); \
    uint32_t PFX_X265(nquant_ ## cpu(const int16_t* coef, const int32_t* quantCoeff, int16_t* qCoef, int qBits, int add, int numCoeff)); \
    void PFX_X265(dequant_normal_ ## cpu(const int16_t* quantCoef, int16_t* coef, int num, int scale, int shift)); \
    void PFX_X265(dequant_scaling_## cpu(const int16_t* src, const int32_t* dequantCoef, int16_t* dst, int num, int mcqp_miper, int shift)); \
    void PFX_X265(weight_pp_ ## cpu(const pixel* src, pixel* dst, intptr_t stride, int width, int height, int w0, int round, int shift, int offset)); \
    void PFX_X265(weight_sp_ ## cpu(const int16_t* src, pixel* dst, intptr_t srcStride, intptr_t dstStride, int width, int height, int w0, int round, int shift, int offset)); \
    void PFX_X265(scale1D_128to64_ ## cpu(pixel*, const pixel*)); \
    void PFX_X265(scale2D_64to32_ ## cpu(pixel*, const pixel*, intptr_t)); \
    uint32_t PFX_X265(costCoeffRemain_ ## cpu(uint16_t *absCoeff, int numNonZero, int idx)); \
    uint32_t PFX_X265(costC1C2Flag_sse2(uint16_t *absCoeff, intptr_t numNonZero, uint8_t *baseCtxMod, intptr_t ctxOffset)); \

DEFINE_UTILS(sse2);
DEFINE_UTILS(ssse3);
DEFINE_UTILS(sse4);
DEFINE_UTILS(avx2);

#undef DEFINE_UTILS

void PFX_X265(pixel_ssim_4x4x2_core_sse2(const pixel* pix1, intptr_t stride1, const pixel* pix2, intptr_t stride2, int sums[2][4]));
void PFX_X265(pixel_ssim_4x4x2_core_avx(const pixel* pix1, intptr_t stride1, const pixel* pix2, intptr_t stride2, int sums[2][4]));
float PFX_X265(pixel_ssim_end4_sse2(int sum0[5][4], int sum1[5][4], int width));
float PFX_X265(pixel_ssim_end4_avx(int sum0[5][4], int sum1[5][4], int width));

int PFX_X265(scanPosLast_x64(const uint16_t *scan, const coeff_t *coeff, uint16_t *coeffSign, uint16_t *coeffFlag, uint8_t *coeffNum, int numSig, const uint16_t* scanCG4x4, const int trSize));
int PFX_X265(scanPosLast_avx2_bmi2(const uint16_t *scan, const coeff_t *coeff, uint16_t *coeffSign, uint16_t *coeffFlag, uint8_t *coeffNum, int numSig, const uint16_t* scanCG4x4, const int trSize));
uint32_t PFX_X265(findPosFirstLast_ssse3(const int16_t *dstCoeff, const intptr_t trSize, const uint16_t scanTbl[16]));
uint32_t PFX_X265(costCoeffNxN_sse4(const uint16_t *scan, const coeff_t *coeff, intptr_t trSize, uint16_t *absCoeff, const uint8_t *tabSigCtx, uint32_t scanFlagMask, uint8_t *baseCtx, int offset, int scanPosSigOff, int subPosBase));
uint32_t PFX_X265(costCoeffNxN_avx2_bmi2(const uint16_t *scan, const coeff_t *coeff, intptr_t trSize, uint16_t *absCoeff, const uint8_t *tabSigCtx, uint32_t scanFlagMask, uint8_t *baseCtx, int offset, int scanPosSigOff, int subPosBase));

#endif // ifndef X265_PIXEL_UTIL_H
