//============================================================================
// Copyright (C) 2003-2009 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#ifdef TARGET_OS_WINDOWS
#include "VxWaveOut.h"
#include <CoreLib/VxDebug.h>
#include <windowsx.h>
#include <mmsystem.h>

//============================================================================
static void CALLBACK MultiWaveOutSpeakerCallbackGlobal(
					HWAVEOUT _hWaveOut, 
					UINT uMsg, 
					DWORD dwInstance,
					DWORD dwParam1, 
					DWORD dwParam2)
{
	switch (uMsg)
	{
	case WOM_OPEN:
		//fprintf (stderr, "SpeakerCallback : WOM_OPEN\n");
		break;
	case WOM_CLOSE:
		//fprintf (stderr, "SpeakerCallback : WOM_CLOSE\n");
		break;
	case WOM_DONE:
		//fprintf (stderr, "SpeakerCallback : WOM_DONE\n");
		if( dwInstance )
		{
			((VxWaveOut *)dwInstance)->waveOutMMDoneCallback(dwInstance, dwParam1, dwParam2);
		}
		break;
	default:
		break;
	}
}

//============================================================================
VxWaveOut::VxWaveOut()
: m_hWaveOut(NULL)
, m_bOutputActive(NULL)
, m_bOutputTerminate(false)
, m_CirBufHeadIdx( 0 )
, m_CirBufTailIdx( 0 )
, m_WaveBufUsedCnt( 0 )
, m_MaxAvailBuffers( WAVE_OUT_HDR_COUNT - 1)
, waAudioOutDevice((UINT) WAVE_MAPPER)	// Default audio output device
{
	for( int i = 0; i < WAVE_OUT_HDR_COUNT; i++ )
	{
		m_WaveDataBufs[i] = new char[ WAVE_OUT_BUFFER_SIZE ];
	}

	waveOutStartup();
}

//============================================================================
VxWaveOut::~VxWaveOut()
{
	stopWaveOutput();
	for( int i = 0; i < WAVE_OUT_HDR_COUNT; i++ )
	{
		delete m_WaveDataBufs[i];
	}
}

//============================================================================
int VxWaveOut::waveOutStartup( void )
{
	setOutputRate( 8000, 16, 1 );
	return 0;
}

//============================================================================
void VxWaveOut::waveOutShutdown( void )
{
}

//============================================================================
void VxWaveOut::setWaveOutCallback( VxWaveOutCallback * waveOutCallback, void * userData )
{
	m_UserData		= userData;
	m_WaveCallback	= waveOutCallback;
}

//============================================================================
void VxWaveOut::waveOutMMDoneCallback( DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
	WAVEHDR *wHdr = (WAVEHDR *) dwParam1;
	MMRESULT mr = NOERROR;

	//int lenToCopy = WAVE_OUT_BUFFER_SIZE;

	if( m_bOutputActive && ( false == m_bOutputTerminate ) )
	{
		if( wHdr != &m_aoWaveOutHeaders[m_CirBufTailIdx] )
		{
			for( int i = 0; i < WAVE_OUT_HDR_COUNT; i++ )
			{
				if( wHdr == &m_aoWaveOutHeaders[i] )
				{
					LogMsg( LOG_ERROR, "waveOutMMDoneCallback idx should be %d instead of %d\n", i, m_CirBufTailIdx );
					break;
				}
			}
		}


		mr = waveOutWrite( m_hWaveOut, wHdr, sizeof(WAVEHDR) );
		if(mr)
		{
			char et[MAXERRORLENGTH];

			waveInGetErrorTextA(mr, et, sizeof et);
			LogMsg( LOG_ERROR, "Can't Write Wave Audio Out %s\n", et );
		}

		m_SndMutex.lock();
		m_CirBufTailIdx++;
		if( WAVE_OUT_HDR_COUNT <= m_CirBufTailIdx )
		{
			m_CirBufTailIdx = 0;
		}

		if( 0 == m_WaveBufUsedCnt )
		{
			// even though no user input data we keep incrementing as if there was but fill with silence
			memset( m_WaveDataBufs[ m_CirBufHeadIdx ], 0, WAVE_OUT_BUFFER_SIZE );
			m_CirBufHeadIdx++;
			if( WAVE_OUT_HDR_COUNT <= m_CirBufHeadIdx )
			{
				m_CirBufHeadIdx = 0;
			}
		}

		if( m_WaveBufUsedCnt )
		{
			m_WaveBufUsedCnt--;
		}

		int lclUsedCnt = m_WaveBufUsedCnt;
		m_SndMutex.unlock();

		if( m_WaveCallback )
		{
			m_WaveCallback->waveOutSpaceAvail( (m_MaxAvailBuffers - lclUsedCnt) * WAVE_OUT_BUFFER_SIZE, m_UserData );
		}
	}
}

//============================================================================
const char * VxWaveOut::describeErr(	int rc )
{
	switch( rc )
	{
	case MMSYSERR_ALLOCATED:
		return " VxWaveOut error..Specified resource is already allocated.";
	case MMSYSERR_BADDEVICEID:
		return " VxWaveOut error..Specified device identifier is out of range."; 
	case MMSYSERR_NODRIVER:
		return " VxWaveOut error..No device driver is present.";
	case MMSYSERR_NOMEM:
		return " VxWaveOut error..Unable to allocate or lock memory.";
	case WAVERR_BADFORMAT:
		return " VxWaveOut error..Attempted to open with an unsupported waveform-audio format.";
	default:
		return " VxWaveOut error..Unknown Wave Error";
	}
}

//============================================================================							
int VxWaveOut::startWaveOutput( void )
{
	stopWaveOutput();    
    if( !m_bOutputActive ) 
	{
		//	Input initialization   	
		MMRESULT woo;
		WAVEFORMATEX wfi;
		memset(&wfi, 0, sizeof(WAVEFORMATEX));
		wfi.wFormatTag		= WAVE_FORMAT_PCM;
		wfi.nChannels		= m_iOutAudioChannels;
		wfi.cbSize			= 0; // size of _extra_ info 

		wfi.nSamplesPerSec	= m_iOutSamplesPerSecond;
		wfi.nAvgBytesPerSec = m_iOutBytesPerSecond;
		wfi.wBitsPerSample	= m_iOutBitsPerSample;
		wfi.nBlockAlign		= (wfi.wBitsPerSample >> 3) * wfi.nChannels;

		//	if ((woo = waveInOpen( &hWaveIn, waAudioInDevice,
		//		(LPWAVEFORMATEX) &wfi, (DWORD) (UINT) hwnd, 0L, (DWORD) CALLBACK_WINDOW)) != 0) 
		woo = waveOutOpen(	&m_hWaveOut, 
							waAudioOutDevice, 
							(LPWAVEFORMATEX ) &wfi,
							(DWORD_PTR) MultiWaveOutSpeakerCallbackGlobal, 
							(DWORD_PTR)this, 
							CALLBACK_FUNCTION);
		if( woo )
		{
			char et[MAXERRORLENGTH];

			waveInGetErrorTextA(woo, et, sizeof et);
			LogMsg( LOG_ERROR, "Can't Open Wave Audio Out %s\n", et );
			return woo;
		}

		// Set up the wave header.
		memset(&m_aoWaveOutHeaders, 0, sizeof(m_aoWaveOutHeaders));

		for( int i = 0; i < WAVE_OUT_HDR_COUNT; i++ ) 
		{
			m_aoWaveOutHeaders[i].lpData = m_WaveDataBufs[i];
			// so has silence when started
			memset( m_aoWaveOutHeaders[i].lpData, 0, WAVE_OUT_BUFFER_SIZE );
			m_aoWaveOutHeaders[i].dwBufferLength = WAVE_OUT_BUFFER_SIZE;
			waveOutPrepareHeader( m_hWaveOut, &m_aoWaveOutHeaders[i], sizeof(WAVEHDR));
		}

		// Start playback.
		m_CirBufHeadIdx			= WAVE_OUT_HDR_COUNT - 1;
		m_CirBufTailIdx			= 0;
		m_WaveBufUsedCnt		= 1;

		for( int i = 0; i < WAVE_OUT_HDR_COUNT; i++ ) 
		{
			woo = waveOutWrite( m_hWaveOut, &m_aoWaveOutHeaders[i], sizeof(WAVEHDR) );
			if( woo )
			{
				char et[MAXERRORLENGTH];

				waveInGetErrorTextA(woo, et, sizeof et);
				LogMsg( LOG_ERROR, "Can't write Wave Audio Out %s\n", et );
				return woo;
			}
		}

 		m_bOutputActive = true;
	}

    return true;
}

//============================================================================
//	WAVEOUTSHUTDOWN  --  Shutdown wave audio output, if open. 
//	returns true if was active						 
bool VxWaveOut::stopWaveOutput( void )
{
    bool bWasActive = m_bOutputActive;
	if( m_bOutputActive ) 
	{
		m_bOutputTerminate = true;

		waveOutClose( m_hWaveOut );
		waveOutReset( m_hWaveOut );
		m_bOutputTerminate = false;
		m_bOutputActive = false;
	}

	return bWasActive;
}

//============================================================================
void VxWaveOut::setOutputRate(		int iSamplesPerSecond,	//number of samples per second
									int iBitsPerSample,		//number of bits per sample
									int iChannels )			//number of audio channels
{
	stopWaveOutput();
	m_iOutAudioChannels		= iChannels;				// Audio channels
	m_iOutSamplesPerSecond	= iSamplesPerSecond;		// Sound sampling rate
	m_iOutBitsPerSample		= iBitsPerSample;			// Bits per sample
	m_iOutSampleAlignment	= iBitsPerSample >> 3;		// Sample frame size
	m_iOutBytesPerSecond	= m_iOutSamplesPerSecond * m_iOutSampleAlignment * iChannels;		// Sample bytes per second
}

//============================================================================
void VxWaveOut::sendAudioDataToSpeaker( const char * data, int dataLen )
{
	m_SndMutex.lock();
	int bufsFreeCnt		= m_MaxAvailBuffers - m_WaveBufUsedCnt;
	int dataFreeSpace	= bufsFreeCnt * WAVE_OUT_BUFFER_SIZE;
	if( dataLen <= dataFreeSpace )
	{
		while( WAVE_OUT_BUFFER_SIZE <= dataLen )
		{
			fillNextWaveBuffer( data, WAVE_OUT_BUFFER_SIZE );
			data	+= WAVE_OUT_BUFFER_SIZE;
			dataLen -= WAVE_OUT_BUFFER_SIZE;
		}

		if( dataLen )
		{
			// partial buffer length
			fillNextWaveBuffer( data, dataLen );
		}
	}
	else
	{
		LogMsg( LOG_INFO, "!!!!VxWaveOut::sendAudioDataToSpeaker buffer overflow free space %d required %d\n", dataFreeSpace, dataLen );
	}

	m_SndMutex.unlock();
}

//============================================================================
void VxWaveOut::fillNextWaveBuffer( const char * data, int dataLen )
{
	char * waveBuf = m_WaveDataBufs[ m_CirBufHeadIdx ];
	memcpy( waveBuf, data, dataLen );
	if( dataLen < WAVE_OUT_BUFFER_SIZE )
	{
		// fill remainder with silence
		int remainderLen = WAVE_OUT_BUFFER_SIZE - dataLen;
		memset( &waveBuf[dataLen], 0, remainderLen );
	}

	m_WaveBufUsedCnt++;
	m_CirBufHeadIdx++;
	if( WAVE_OUT_HDR_COUNT <= m_CirBufHeadIdx )
	{
		m_CirBufHeadIdx = 0;
	}
}

#endif // TARGET_OS_WINDOWS

