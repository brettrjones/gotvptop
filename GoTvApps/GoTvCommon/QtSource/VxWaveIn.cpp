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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================
#ifdef TARGET_OS_WINDOWS
#include "VxWaveIn.h"
#include <CoreLib/VxDebug.h>
#include <windowsx.h>
#include <mmsystem.h>

//namespace
//{
//	VxWaveIn *		g_poWave = 0;
//}
//
////============================================================================
//VxWaveIn&		GetVxWaveInInstance( void )
//{
//	if( 0 == g_poWave )
//	{
//		g_poWave = new VxWaveIn();
//	}
//
//	return *g_poWave;
//}
//

//============================================================================
static void CALLBACK WaveInCallbackGlobal(HWAVEIN hWaveIn, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch (uMsg)
	{
	case WIM_OPEN:
		/*	!	fprintf(stderr, "WaveInCallback : WIM_OPEN\n"); */
		break;

	case WIM_CLOSE:
		/*	!	fprintf(stderr, "WaveInCallback : WIM_CLOSE\n"); */
		break;

	case WIM_DATA:
		if( dwInstance )
		{
			((VxWaveIn *)dwInstance)->WaveInMMDataCallback(dwInstance, dwParam1, dwParam2);
		}

		break;

	default:
		break;
	}
}

//============================================================================
VxWaveIn::VxWaveIn()
: m_hWaveIn(NULL)
, m_bInputActive(NULL)
, m_bInputTerminate(false)
, m_bWaveOutHdrPrepared(false)
, waAudioInDevice((UINT) WAVE_MAPPER)	// Default audio input device
, m_UserData( 0 )
, m_UserCallback( 0 )
{
	m_iInBufLen			= WAVE_IN_BUFFER_SIZE;

	memset(&m_aoWaveInHeaders, 0, sizeof( m_aoWaveInHeaders ));

	waveInStartup();
}

//============================================================================
VxWaveIn::~VxWaveIn()
{
	//g_poWave = NULL;
	stopWaveInput();
}

//============================================================================
int VxWaveIn::waveInStartup( void )
{
	setInputRate( 8000, 16, 1 );
	return 0;
}

//============================================================================
void VxWaveIn::waveInShutdown( void )
{
}
//
////============================================================================
//void VxWaveIn::setMicrophoneSoundCallback( MIC_SND_CALLBACK_FUNCTION func )
//{
//	m_funcWaveInCallback = func;
//}

//============================================================================
void VxWaveIn::WaveInMMDataCallback( DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
	WAVEHDR *pHdr = (WAVEHDR *) dwParam1;
	MMRESULT mmReturn = NOERROR;

	if( m_bInputActive && ( false == m_bInputTerminate ) )
	{
		if( m_UserCallback )
		{
			m_UserCallback->waveInPcmDataAvail( (char *)pHdr->lpData, (int)pHdr->dwBytesRecorded, m_UserData );
		}

		mmReturn = ::waveInUnprepareHeader(m_hWaveIn, pHdr, sizeof(WAVEHDR));
		if(mmReturn)
		{
			char et[MAXERRORLENGTH];

            waveInGetErrorTextA( mmReturn, et, sizeof et );
			LogMsg( LOG_ERROR, "Wave Output Error %s\n", et );
			return;
		}
		
		if(m_bInputActive && (false == m_bInputTerminate))
		{
			// reuse the buffer:
			// prepare it again
            mmReturn = ::waveInPrepareHeader(m_hWaveIn, pHdr, sizeof(WAVEHDR));
			if(mmReturn)
			{
				char et[MAXERRORLENGTH];

                waveInGetErrorTextA( mmReturn, et, sizeof et );
				LogMsg( LOG_ERROR, "Wave Output Error %s\n", et );
				return;
			}
			else // no error
			{
				// add the input buffer to the queue again
				mmReturn = ::waveInAddBuffer(m_hWaveIn, pHdr, sizeof(WAVEHDR));
				if(mmReturn)
				{
					char et[MAXERRORLENGTH];

					waveInGetErrorTextA( mmReturn, et, sizeof et );
					LogMsg( LOG_ERROR, "Wave Output Error %s\n", et );
					return;
				}
			}
		}
	}
}

//============================================================================
const char * VxWaveIn::describeErr(	int rc )
{
	switch( rc )
	{
	case MMSYSERR_ALLOCATED:
		return " VxWaveIn error..Specified resource is already allocated.";
	case MMSYSERR_BADDEVICEID:
		return " VxWaveIn error..Specified device identifier is out of range."; 
	case MMSYSERR_NODRIVER:
		return " VxWaveIn error..No device driver is present.";
	case MMSYSERR_NOMEM:
		return " VxWaveIn error..Unable to allocate or lock memory.";
	case WAVERR_BADFORMAT:
		return " VxWaveIn error..Attempted to open with an unsupported waveform-audio format.";
	default:
		return " VxWaveIn error..Unknown Wave Error";
	}
}

//============================================================================
int VxWaveIn::startWaveInput()
{
    //	Attempt to initialize the audio input port
	stopWaveInput();    

	//	Input initialization   	
	MMRESULT woo;
	WAVEFORMATEX wfi;
	memset(&wfi, 0, sizeof( WAVEFORMATEX));
	wfi.wFormatTag	= WAVE_FORMAT_PCM;
	wfi.nChannels	= m_iInAudioChannels;
	wfi.cbSize		= 0; /* size of _extra_ info */

	wfi.nSamplesPerSec	= m_iInSamplesPerSecond;
	wfi.nAvgBytesPerSec = m_iInBytesPerSecond;
	wfi.wBitsPerSample	= m_iInBitsPerSample;
	wfi.nBlockAlign		= (wfi.wBitsPerSample >> 3) * wfi.nChannels;

	//	if ((woo = waveInOpen( &hWaveIn, waAudioInDevice,
	//		(LPWAVEFORMATEX) &wfi, (DWORD) (UINT) hwnd, 0L, (DWORD) CALLBACK_WINDOW)) != 0) 
	woo = waveInOpen(	&m_hWaveIn, 
		waAudioInDevice, 
		(LPWAVEFORMATEX ) &wfi,
		(DWORD) (UINT)WaveInCallbackGlobal, 
		(DWORD_PTR)this, 
		CALLBACK_FUNCTION);

	if(woo)
	{
		char et[MAXERRORLENGTH];

		waveInGetErrorTextA(woo, et, sizeof et);
		LogMsg( LOG_ERROR, "Can't Open Wave Audio In %s\n", et );
		return woo;
	}
	
	/*	Now allocate and prepare the sound input buffers.  Don't
	    you just love the code vomit Windows' inability to free
	    resources when a program terminates creates?  */
	
	memset(m_aoWaveInHeaders, 0, sizeof(m_aoWaveInHeaders) );
	for( int i = 0; i < WAVE_IN_HDR_COUNT; i++ ) 
	{
		m_aoWaveInHeaders[i].lpData			= (LPSTR) new char[ WAVE_IN_BUFFER_SIZE ];
		m_aoWaveInHeaders[i].dwBufferLength = WAVE_IN_BUFFER_SIZE;
		waveInPrepareHeader( m_hWaveIn, &m_aoWaveInHeaders[i], sizeof(WAVEHDR));
	}
	
	for( int i = 0; i < WAVE_IN_HDR_COUNT; i++ ) 
	{
		waveInAddBuffer( m_hWaveIn, &m_aoWaveInHeaders[i], sizeof(WAVEHDR)); 
	}

	waveInStart( m_hWaveIn );
	m_bInputActive = true;
    return 0;
}
                                      
/*  TERMINATEWAVEINPUT  --  Shut down wave input and release all
							resources associated with it.  */
//============================================================================							
bool VxWaveIn::stopWaveInput(void)
{
    bool bWasActive = m_bInputActive;
	if( m_bInputActive ) 
	{
		m_bInputTerminate = true;
		
		waveInReset( m_hWaveIn );
		waveInStop( m_hWaveIn );
		
	
		for( int i = 0; i < WAVE_IN_HDR_COUNT; i++ ) 
		{
			if( m_aoWaveInHeaders[i].lpData != NULL ) 
			{
				delete m_aoWaveInHeaders[i].lpData;
				m_aoWaveInHeaders[i].lpData = NULL;
			}
		}
		m_bInputTerminate = false;
		m_bInputActive = false;
	}
	return bWasActive;
}

//============================================================================
void VxWaveIn::setInputRate(	int iSamplesPerSecond,	//number of samples per second
								int iBitsPerSample,		//number of bits per sample
								int iChannels )			//number of audio channels
{
	stopWaveInput();
	m_iInAudioChannels		= iChannels;					// Audio channels
	m_iInSamplesPerSecond	= iSamplesPerSecond;		// Sound sampling rate
	m_iInBitsPerSample		= iBitsPerSample;			// Bits per sample
	m_iInSampleAlignment	= iBitsPerSample >> 3;		// Sample frame size
	m_iInBytesPerSecond		= m_iInSamplesPerSecond * m_iInSampleAlignment * iChannels;		// Sample bytes per second
}

//============================================================================
void VxWaveIn::setWaveInCallback( VxWaveInCallback * waveInCallback, void * userData )
{
	m_UserData = userData;
	m_UserCallback = waveInCallback;
}

#endif // TARGET_OS_WINDOWS

