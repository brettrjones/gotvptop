/*
 * Copyright (c) 2011 Mans Rullgard
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <ffmpeg/config_ffmpeg.h>

#include "libavutil/avutil_attributes.h"
#include "libavutil/thread.h"
#include "mpegaudiodsp.h"
#include "dct.h"
#include "dct32.h"

static AVOnce mpadsp_float_table_init = AV_ONCE_INIT;
static AVOnce mpadsp_fixed_table_init = AV_ONCE_INIT;

av_cold void ff_mpadsp_init(MPADSPContext *s)
{
    DCTContext dct;

    ff_dct_init(&dct, 5, DCT_II);
    ff_thread_once(&mpadsp_float_table_init, &ff_init_mpadsp_tabs_float);
    ff_thread_once(&mpadsp_fixed_table_init, &ff_init_mpadsp_tabs_fixed);

    s->apply_window_float = ff_mpadsp_apply_window_float;
    s->apply_window_fixed = ff_mpadsp_apply_window_fixed;

    s->dct32_float = dct.dct32;
    s->dct32_fixed = ff_dct32_fixed;

    s->imdct36_blocks_float = ff_imdct36_blocks_float;
    s->imdct36_blocks_fixed = ff_imdct36_blocks_fixed;

#if ARCH_AARCH64
	ff_mpadsp_init_aarch64( s );
#endif //ARCH_AARCH64
#if ARCH_ARM && HAVE_ARM_ASM
	ff_mpadsp_init_arm( s );
#endif //ARCH_ARM
#if ARCH_PPC
	ff_mpadsp_init_ppc( s );
#endif //ARCH_PPC
#if ARCH_X86 && HAVE_X86_ASM
	ff_mpadsp_init_x86( s );
#endif //ARCH_X86
#if HAVE_MIPSFPU
	ff_mpadsp_init_mipsfpu( s );
#endif // HAVE_MIPSFPU
#if HAVE_MIPSDSP
	ff_mpadsp_init_mipsdsp( s );
#endif // HAVE_MIPSDSP

}
