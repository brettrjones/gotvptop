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

#include "VxSpeexDefs.h"
#include <VxSpeexLib/speex/include/speex/speex_bits.h>
#define USE_SPEEX_FIXED_POINT 1

class VxSpeex
{
protected:
	//=== speex vars ===//
	void *		m_pvSpeexEncState;				// Holds the state of the encoder
	SpeexBits	m_oSpeexEncBits;				// Holds bits so they can be read and written to by the Speex routines

	void *		m_pvSpeexDecState;				// Holds the state of the encoder
	SpeexBits	m_oSpeexDecBits;				// Holds bits so they can be read and written to by the Speex routines
#ifndef USE_SPEEX_FIXED_POINT
	float		m_af32EncodeBuf[ VXWAVE_MAX_BUF_LEN/2 ];
	float		m_af32DecodeBuf[ VXWAVE_MAX_BUF_LEN/2 ];
#endif

public:
	//=== constructor ===//
	VxSpeex();
	//=== destructor ===//
	~VxSpeex();

	//=== helpers ===//

	//=== overrides ===//

	//=== methods ===//
	//! compress audio using speex codec.. return length of decoded data
	//! NOTE: iPcmDataLen must be a multiple of  SPEEX_FRAME_LEN
	uint16_t SpeexCompress(	char *		pau8DataIn,					// wave sample data ( 16 bit PCM samples )
						int			iPcmDataLen,				// length of pcm data in bytes
						char *		pau8DataOut );				// encoded data out ( assumes length SPEEX_PACKET_MAX_COMPRESSED_LEN )

	//! decompress audio using speex codec
	uint16_t SpeexDecompress(	char *	pau8DataIn,					// encoded data
							int		iEncodedDataLen,			// number of frames to decode
							char *	pau8DataOut );				// decoded data out ( assumes length SPEEX_PACKET_BUFFER_LEN )

};

