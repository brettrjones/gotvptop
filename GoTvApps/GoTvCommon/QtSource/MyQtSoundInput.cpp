//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include "MyQtSoundInput.h"
#include "MySndMgr.h"
#include "AppCommon.h"
#include "VxWaveIn.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <QtCore/qendian.h>
//============================================================================
MyQtSoundInput::MyQtSoundInput( MySndMgr *parent)
    : QObject(parent)
	, m_SndMgr(parent)
	, m_MyApp( parent->getApp() )
	, m_Engine( m_MyApp.getEngine() )
	, m_maxAmplitude(0)
	, m_iSndInBufferIdx(0)
{

    m_maxAmplitude = 32767;

//	g_poMyQtSoundInput = this;
//#ifdef TARGET_OS_WINDOWS
//	if( g_poWave )
//	{
//		g_poWave->setMicrophoneSoundCallback( MicrophoneCallbackGlobal );
//	}
//#endif // TARGET_OS_WINDOWS
}

//============================================================================
MyQtSoundInput::~MyQtSoundInput()
{
	//g_poMyQtSoundInput = NULL;
}

//============================================================================
void MyQtSoundInput::start()
{
#ifdef TARGET_OS_WINDOWS
	//if( g_poWave )
	//{
	//	g_poWave->startWaveInput();
	//}
#endif // TARGET_OS_WINDOWS
}

//============================================================================
void MyQtSoundInput::stop()
{
#ifdef TARGET_OS_WINDOWS
	//if( g_poWave )
	//{
	//	g_poWave->stopWaveInput();
	//}
#endif // TARGET_OS_WINDOWS
}

//============================================================================
qint64 MyQtSoundInput::readData(char *data, qint64 maxlen)
{
	Q_UNUSED(data)
	Q_UNUSED(maxlen)

	return 0;
}

//============================================================================
qint64 MyQtSoundInput::writeData( const char *data, qint64 lenIn )
{
	return lenIn;
}
#ifdef TARGET_OS_WINDOWS
//class VxWaveWriter
//{
//public:
//	//=== vars ===//
//	HMMIO			m_hFile;
//	MMCKINFO		m_MMCKInfoData;
//	MMCKINFO		m_MMCKInfoParent;
//	MMCKINFO		m_MMCKInfoChild;
//	DWORD			m_dwPcmDataSize;
//	bool			m_bIsClosed;
//
//	WAVEFORMATEX	m_Format;
//
//	VxWaveWriter()
//		: m_hFile(NULL)
//		, m_dwPcmDataSize(0)
//		, m_bIsClosed(false)
//	{
//	}
//
//	~VxWaveWriter()
//	{
//		CloseFile();
//	}
//
//	bool OpenWaveFileToWriteTo( void )
//	{
//
//		memset(&m_Format, 0, sizeof( WAVEFORMATEX));
//		m_Format.wFormatTag	= WAVE_FORMAT_PCM;
//		m_Format.nChannels		= 1;
//        m_Format.cbSize		= 0; // size of _extra_ info
//
//		m_Format.nSamplesPerSec	= 8000;
//		m_Format.nAvgBytesPerSec	= m_Format.nSamplesPerSec * m_Format.nChannels;
//		m_Format.wBitsPerSample	= 16;
//		m_Format.nBlockAlign		= (m_Format.wBitsPerSample >> 3) * m_Format.nChannels;
//
//
//		ZeroMemory(&m_MMCKInfoParent,sizeof(MMCKINFO));
//		ZeroMemory(&m_MMCKInfoChild,sizeof(MMCKINFO));
//		ZeroMemory(&m_MMCKInfoData,sizeof(MMCKINFO));
//
//		if(m_hFile) 
//			return false; 
//
//		// open file
//		m_hFile = ::mmioOpenA("F:\\crap.wav",NULL, MMIO_CREATE|MMIO_WRITE|MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
//		if(m_hFile == NULL) 
//		{
//
//			return false;
//		}
//
//		ZeroMemory(&m_MMCKInfoParent, sizeof(MMCKINFO));
//		m_MMCKInfoParent.fccType = mmioFOURCC('W','A','V','E');
//
//		MMRESULT mmResult = ::mmioCreateChunk( m_hFile,&m_MMCKInfoParent, MMIO_CREATERIFF);
//
//		ZeroMemory(&m_MMCKInfoChild, sizeof(MMCKINFO));
//		m_MMCKInfoChild.ckid = mmioFOURCC('f','m','t',' ');
//		m_MMCKInfoChild.cksize = sizeof(WAVEFORMATEX) + m_Format.cbSize;
//		mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
//		mmResult = ::mmioWrite(m_hFile, (char*)&m_Format, sizeof(WAVEFORMATEX) + m_Format.cbSize); 
//		mmResult = ::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
//		m_MMCKInfoChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
//		mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
//
//		return true;
//	}
//
//	void CloseFile( void )
//	{
//		if( ( false == m_bIsClosed ) && m_hFile )
//		{
//			::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
//			::mmioAscend(m_hFile, &m_MMCKInfoParent, 0);
//		
//			::mmioClose(m_hFile, 0);
//			m_hFile = NULL;
//			m_bIsClosed = true;
//		}
//	}
//	void writeSound(const char * buf, int dataLen)
//	{
//		if( false == m_bIsClosed )
//		{
//			if( NULL == m_hFile )
//			{
//				OpenWaveFileToWriteTo();
//			}
//			m_dwPcmDataSize += dataLen;
//
//			int length = mmioWrite(m_hFile, buf, dataLen);
//			if(length > 0 )
//			{
//				m_dwPcmDataSize += length;
//				if( m_dwPcmDataSize > 200000 )
//				{
//					CloseFile();
//				}
//			}
//		}
//	}
//};
//
//VxWaveWriter g_oWaveWriter;
#endif // TARGET_OS_WINDOWS

//============================================================================
void MyQtSoundInput::sendAudioData( const char * buf, int dataLen )
{
//#ifdef TARGET_OS_WINDOWS
//	g_oWaveWriter.writeSound( buf, dataLen );
//#endif // TARGET_OS_WINDOWS
	//m_Engine.fromGuiMicrophoneData( (uint16_t *)buf, dataLen );
	//QByteArray audioData( buf, dataLen );
	//m_SndMgr->sendingAudioData( audioData );
}

