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
// http://www.gotvptop.net
//============================================================================

#ifdef TARGET_OS_WINDOWS
#include <WinSock2.h>
#include <windows.h>
#include "MMSystem.h"
#include <CoreLib/VxMutex.h>


class VxWaveInCallback
{
public:
	virtual void				waveInPcmDataAvail( char * sndData, int dataLen, void * userData ) = 0;
};


#define WAVE_IN_HDR_COUNT		4
#define WAVE_IN_BUFFER_SIZE		1280

//typedef long (*MIC_SND_CALLBACK_FUNCTION)( char * sndData, int dataLen );  

class VxWaveIn
{
public:
	VxWaveIn();
	~VxWaveIn();

	int 						waveInStartup( void );
	void						waveInShutdown( void );
	
	//void						setMicrophoneSoundCallback( MIC_SND_CALLBACK_FUNCTION func );
	void						setWaveInCallback( VxWaveInCallback * waveInCallback, void * userData = 0 );

	int							startWaveInput( void );
	bool						stopWaveInput( void );		//shuts down wave input and returns TRUE if was active


	void						WaveInMMDataCallback(DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

protected:
	const char *				describeErr( int rc );
	void						setInputRate(	int iSamplesPerSecond,	//number of samples per second
												int iBitsPerSample,		//number of bits per sample
												int iChannels );		//number of audio channels


	//MIC_SND_CALLBACK_FUNCTION	m_funcWaveInCallback;

	HWAVEIN						m_hWaveIn;              // Wave input handle

	bool						m_bInputActive;			// Is wave input open ?
	bool						m_bInputTerminate;

	UINT						waAudioInDevice;			// Default audio input device

	//===	Audio hardware wave configuration ===//
	int							m_iInAudioChannels;			// Input Audio input channels
	int							m_iInSamplesPerSecond;		// Input Sound sampling rate
	int							m_iInBytesPerSecond;		// Input Sample bytes per second
	int							m_iInSampleAlignment;		// Input Sample frame size
	int							m_iInBitsPerSample;			// Input Bits per sample

	WAVEHDR						m_aoWaveInHeaders[WAVE_IN_HDR_COUNT];	// Pointers to wave input buffers
	bool						m_bWaveOutHdrPrepared;

	int							m_iInBufLen;
	VxMutex						m_SndMutex;
	void *						m_UserData;
	VxWaveInCallback *			m_UserCallback;

};

VxWaveIn&		GetVxWaveInInstance( void );
#endif // TARGET_OS_WINDOWS
