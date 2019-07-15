#pragma once
//============================================================================
// Copyright (C) 2003 Brett R. Jones 
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
#include "IVxWaveOut.h"

#include <WinSock2.h>
#include <windows.h>
#include "MMSystem.h"

#include <CoreLib/VxMutex.h>

#define WAVE_OUT_HDR_COUNT		4
#define WAVE_OUT_BUFFER_SIZE	1280

class VxWaveOut : public IVxWaveOut
{
public:
public:
	VxWaveOut();
	virtual ~VxWaveOut();

	int 						waveOutStartup( void );
	void						waveOutShutdown( void );

	int							startWaveOutput( void );
	bool						stopWaveOutput( void );	//shuts down wave out and returns TRUE if was active

	virtual void				setWaveOutCallback( VxWaveOutCallback * waveOutCallback, void * userData = 0 );

	void						sendAudioDataToSpeaker( const char * data, int dataLen );

	void						waveOutMMDoneCallback(DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
protected:
	void						setOutputRate(	int iSamplesPerSecond,	//number of samples per second
												int iBitsPerSample,		//number of bits per sample
												int iChannels );		//number of audio channels
	void						fillNextWaveBuffer( const char * data, int dataLen );
	const char * 				describeErr( int rc );

	HWAVEOUT					m_hWaveOut;				// Wave output handle
    bool						m_bOutputActive;		// Is wave output open ?
	bool						m_bOutputTerminate;

	UINT						waAudioOutDevice;			// Default audio output device

	//===	Audio hardware wave configuration ===//
	int							m_iOutAudioChannels;		// Output Audio channels
	int							m_iOutSamplesPerSecond;		// Output Sound sampling rate
	int							m_iOutBytesPerSecond;		// Output Sample bytes per second
	int							m_iOutSampleAlignment;		// Output Sample frame size
	int							m_iOutBitsPerSample;		// Output Bits per sample

	WAVEHDR						m_aoWaveOutHeaders[WAVE_OUT_HDR_COUNT];
	char *						m_WaveDataBufs[WAVE_OUT_HDR_COUNT];
	int							m_CirBufHeadIdx;
	int							m_CirBufTailIdx;
	int							m_WaveBufUsedCnt;
	int							m_MaxAvailBuffers;

	VxMutex						m_SndMutex;
	void *						m_UserData;
	VxWaveOutCallback *			m_WaveCallback;
};

#endif // TARGET_OS_WINDOWS

