/*****************************************************************************
 * Copyright (C) 2013-2017 MulticoreWare, Inc
 *
 * Authors: Dnyaneshwar Gorade <dnyaneshwar@multicorewareinc.com>
 *          Praveen Kumar Tiwari <praveen@multicorewareinc.com>
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

#ifndef X265_LOOPFILTER_H
#define X265_LOOPFILTER_H

#define DECL_SAO(cpu) \
    void PFX_X265(saoCuOrgE0_ ## cpu)(pixel * rec, int8_t * offsetEo, int endX, int8_t* signLeft, intptr_t stride); \
    void PFX_X265(saoCuOrgE1_ ## cpu)(pixel* rec, int8_t* upBuff1, int8_t* offsetEo, intptr_t stride, int width); \
    void PFX_X265(saoCuOrgE1_2Rows_ ## cpu)(pixel* rec, int8_t* upBuff1, int8_t* offsetEo, intptr_t stride, int width); \
    void PFX_X265(saoCuOrgE2_ ## cpu)(pixel* rec, int8_t* pBufft, int8_t* pBuff1, int8_t* offsetEo, int lcuWidth, intptr_t stride); \
    void PFX_X265(saoCuOrgE2_ ## cpu)(pixel* rec, int8_t* pBufft, int8_t* pBuff1, int8_t* offsetEo, int lcuWidth, intptr_t stride); \
    void PFX_X265(saoCuOrgE2_32_ ## cpu)(pixel* rec, int8_t* pBufft, int8_t* pBuff1, int8_t* offsetEo, int lcuWidth, intptr_t stride); \
    void PFX_X265(saoCuOrgE3_ ## cpu)(pixel *rec, int8_t *upBuff1, int8_t *m_offsetEo, intptr_t stride, int startX, int endX); \
    void PFX_X265(saoCuOrgE3_32_ ## cpu)(pixel *rec, int8_t *upBuff1, int8_t *m_offsetEo, intptr_t stride, int startX, int endX); \
    void PFX_X265(saoCuOrgB0_ ## cpu)(pixel* rec, const int8_t* offsetBo, int ctuWidth, int ctuHeight, intptr_t stride); \
    void PFX_X265(saoCuStatsBO_ ## cpu)(const int16_t *diff, const pixel *rec, intptr_t stride, int endX, int endY, int32_t *stats, int32_t *count); \
    void PFX_X265(saoCuStatsE0_ ## cpu)(const int16_t *diff, const pixel *rec, intptr_t stride, int endX, int endY, int32_t *stats, int32_t *count); \
    void PFX_X265(saoCuStatsE1_ ## cpu)(const int16_t *diff, const pixel *rec, intptr_t stride, int8_t *upBuff1, int endX, int endY, int32_t *stats, int32_t *count); \
    void PFX_X265(saoCuStatsE2_ ## cpu)(const int16_t *diff, const pixel *rec, intptr_t stride, int8_t *upBuff1, int8_t *upBufft, int endX, int endY, int32_t *stats, int32_t *count); \
    void PFX_X265(saoCuStatsE3_ ## cpu)(const int16_t *diff, const pixel *rec, intptr_t stride, int8_t *upBuff1, int endX, int endY, int32_t *stats, int32_t *count); \
    void PFX_X265(calSign_ ## cpu)(int8_t *dst, const pixel *src1, const pixel *src2, const int endX);

DECL_SAO(sse4);
DECL_SAO(avx2);

void PFX_X265(pelFilterLumaStrong_V_sse4)(pixel* src, intptr_t srcStep, intptr_t offset, int32_t tcP, int32_t tcQ);
void PFX_X265(pelFilterLumaStrong_H_sse4)(pixel* src, intptr_t srcStep, intptr_t offset, int32_t tcP, int32_t tcQ);
void PFX_X265(pelFilterChroma_V_sse4)(pixel* src, intptr_t srcStep, intptr_t offset, int32_t tc, int32_t maskP, int32_t maskQ);
void PFX_X265(pelFilterChroma_H_sse4)(pixel* src, intptr_t srcStep, intptr_t offset, int32_t tc, int32_t maskP, int32_t maskQ);

#endif // ifndef X265_LOOPFILTER_H
