#pragma once
//============================================================================
// Copyright (C) 2009-2012 Brett R. Jones 
// All Rights Reserved
//
// You may not modify or redistribute this code for any reason 
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.r.jones@gmail.com
// http://www.roguetreasure.com
//============================================================================

#include <VxUtilLib/VxDefs.h>

//NOTE all speex compress/decompress functions assume 16Bit PCM samples at 8Khz
#define SPEEX_FRAME_SAMPLE_CNT			160 // length of uncompressed frame in samples per frame (PCM 16 bit samples )
#define SPEEX_FRAME_LEN					320 // length of uncompressed frame in bytes
#define SPEEX_FRAMES_PER_PACKET			4	// number of frames to enc/dec at a time
#define SPEEX_PACKET_BUFFER_LEN			(SPEEX_FRAME_LEN * SPEEX_FRAMES_PER_PACKET) 	// length of buffer for each packet
#define SPEEX_PACKET_MAX_COMPRESSED_LEN		(SPEEX_PACKET_BUFFER_LEN/8)	// even at highest quality settings a 8 to 1 compression is achieved
