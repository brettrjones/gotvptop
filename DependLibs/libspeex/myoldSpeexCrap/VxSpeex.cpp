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

#include "VxSpeexLib.h"	
#include "VxSpeexCore.h"



//---------------------------------------------------------------------------
VxSpeex::VxSpeex()
{ 
	//=== setup speex encoder ===//
	// Create a new encoder state in narrow band mode
	m_pvSpeexEncState = speex_encoder_init(&speex_nb_mode);

	// speex quality
	// 1	-	 4kbps	-	very noticeable artifacts, usually intelligible
	// 2	-	 6kbps	-	very noticeable artifacts, good intelligibility
	// 4	-	 8kbps	-	noticeable artifacts sometimes)
	// 6	-	 11kpbs	-	artifacts usually only noticeable with headphones
	// 8	-	 15kbps	-	artifacts not usually noticeable

	// Set the quality to 6 (11 kbps)
	int iSpeexQuality = 6;
	speex_encoder_ctl( m_pvSpeexEncState, SPEEX_SET_QUALITY, &iSpeexQuality );
	// Initialization of the structure that holds the encode bits
	speex_bits_init( &m_oSpeexEncBits );


	//=== setup speex decoder ===//
	// Create a new decoder state in narrow band mode
	m_pvSpeexDecState = speex_decoder_init( &speex_nb_mode );

	//// Set the perceptual enhancement on
	//tmp=0;
	//speex_decoder_ctl( m_pvSpeexDecState, SPEEX_SET_ENH, &tmp );

	// Initialization of the structure that holds the decode bits
	speex_bits_init( &m_oSpeexDecBits );

}
//---------------------------------------------------------------------------
VxSpeex::~VxSpeex()
{
	// Destroy the encoder state
    speex_encoder_destroy( m_pvSpeexEncState );
	// Destroy the bit-packing struct
	speex_bits_destroy( &m_oSpeexEncBits );

	// destroy the decoder
	speex_decoder_destroy( m_pvSpeexDecState );
	// Destroy the bit-stream struct
	speex_bits_destroy( &m_oSpeexDecBits );
}
#define nlSwaps(x) (uint16_t)(((((uint16_t)x) & 0x00ff) << 8) | ((((uint16_t)x) & 0xff00) >> 8))

#define nlSwapl(x) (unsigned long)(((((unsigned long)x) & 0x000000ff) << 24) | ((((unsigned long)x) & 0x0000ff00) << 8) | ((((unsigned long)x) & 0x00ff0000) >> 8) | ((((NLulong)x) & 0xff000000) >> 24))


//---------------------------------------------------------------------------
static void SwapSamples( short *buffer, int len)
{
    int i;

    for(i=0;i<len;i++)
    {
        buffer[i] = nlSwaps(buffer[i]);
    }
}


//---------------------------------------------------------------------------
//! compress audio using speex codec.. return length of encoded data
uint16_t VxSpeex::SpeexCompress(	char *		pas8DataIn,				// wave sample data ( 16 bit samples )
							int			iPcmDataLen,			// length of pcm data in bytes
							char *		pau8DataOut )			// encoded data out
{
	speex_bits_reset(&m_oSpeexEncBits);
	for( int i = 0; i < SPEEX_FRAMES_PER_PACKET; i++) 
	{
		speex_encode_int(m_pvSpeexEncState, (spx_int16_t *)pas8DataIn, &m_oSpeexEncBits);
		pas8DataIn += SPEEX_FRAME_LEN;
	}
	return speex_bits_write(&m_oSpeexEncBits, pau8DataOut, SPEEX_PACKET_MAX_COMPRESSED_LEN );
}

//---------------------------------------------------------------------------
//! decompress audio using speex codec.. return length of decoded data
uint16_t VxSpeex::SpeexDecompress(		char *		pau8DataIn,				// encoded data
									int			iEncodedDataLen,		// length of encoded data
									char *		pau8DataOut )			// decoded data out
{
	// Copy the data into the bit-stream struct
	speex_bits_read_from(&m_oSpeexDecBits, pau8DataIn, iEncodedDataLen );
	for( int i = 0; i < SPEEX_FRAMES_PER_PACKET; i++ )
	{
		// Decode the data
		speex_decode_int( m_pvSpeexDecState, &m_oSpeexDecBits, (spx_int16_t *)&pau8DataOut[i*SPEEX_FRAME_LEN] );
	}
	return SPEEX_PACKET_BUFFER_LEN;

}