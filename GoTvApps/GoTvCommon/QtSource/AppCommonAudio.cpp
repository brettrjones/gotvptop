//============================================================================
// Copyright (C) 2009 Brett R. Jones 
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

#include "AppCommon.h"
#include "MySndMgr.h"

#include "ActivityScanWebCams.h"
#include "ToGuiHardwareControlInterface.h"

#include <CoreLib/VxGlobals.h>

//============================================================================
void AppCommon::toGuiWantMicrophoneRecording( bool wantMicInput )
{
	LogMsg( LOG_INFO, "#### AppCommon::toGuiWantMicrophoneRecording %d\n", wantMicInput );
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	emit signalEnableMicrophoneRecording( wantMicInput );
}

//============================================================================
void AppCommon::slotEnableMicrophoneRecording( bool enableMicInput )
{
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	LogMsg( LOG_INFO, "#### AppCommon::slotEnableMicrophoneRecording %d start\n", enableMicInput );
	toGuiHardwareCtrlLock();
	m_MicrophoneHardwareEnabled = enableMicInput;
	std::vector<ToGuiHardwareCtrlClient>::iterator hardwareIter;
	for( hardwareIter = m_ToGuiHardwareCtrlList.begin(); hardwareIter != m_ToGuiHardwareCtrlList.end(); ++hardwareIter )
	{
		ToGuiHardwareCtrlClient& toGuiClient = *hardwareIter;
		toGuiClient.m_Callback->doGuiWantMicrophoneRecording( m_MicrophoneHardwareEnabled );
	}

	toGuiHardwareCtrlUnlock();
	LogMsg( LOG_INFO, "#### AppCommon::slotEnableMicrophoneRecording %d done\n", enableMicInput );
}

//============================================================================
//! called when microphone recoding not needed
void AppCommon::toGuiWantSpeakerOutput( bool wantSpeakerOutput )
{
	LogMsg( LOG_INFO, "#### AppCommon::toGuiWantSpeakerOutput %d\n", wantSpeakerOutput );
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	emit signalEnableSpeakerOutput( wantSpeakerOutput );
}

//============================================================================
void AppCommon::slotEnableSpeakerOutput( bool enableSpeakerOutput )
{
	// do nothing.. always on for windows. for android save power by stopping wave output
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	toGuiHardwareCtrlLock();
	m_SpeakerHardwareEnabled = 	enableSpeakerOutput;
	std::vector<ToGuiHardwareCtrlClient>::iterator hardwareIter;
	for( hardwareIter = m_ToGuiHardwareCtrlList.begin(); hardwareIter != m_ToGuiHardwareCtrlList.end(); ++hardwareIter )
	{
		ToGuiHardwareCtrlClient& toGuiClient = *hardwareIter;
		toGuiClient.m_Callback->doGuiWantSpeakerOutput(	m_SpeakerHardwareEnabled );
	}

	toGuiHardwareCtrlUnlock();
}

//============================================================================
//! playback audio
void AppCommon::toGuiPlayAudio( int16_t * pu16PcmData, int pcmDataLenInBytes )
{
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	//LogMsg( LOG_INFO, "slotPlayAudio %d len %d from %s\n", ePluginType, u16PcmDataLen, netIdent->getOnlineName());
	m_MySndMgr.recievedAudioData( (char *)pu16PcmData, pcmDataLenInBytes );
}

//============================================================================
//! playback audio
int AppCommon::toGuiPlayAudio( EAppModule appModule, int16_t * pu16PcmData, int pcmDataLenInBytes )
{
    if( VxIsAppShuttingDown() )
    {
        return 0;
    }

    return m_AudioOut.toGuiPlayAudio( appModule, pu16PcmData, pcmDataLenInBytes );
}

//============================================================================
//! playback audio
double AppCommon::toGuiGetAudioDelaySeconds( )
{
    if( VxIsAppShuttingDown() )
    {
        return 0;
    }

    return m_AudioOut.getAudioDelaySeconds( );
}

//============================================================================
double AppCommon::toGuiGetAudioCacheTotalSeconds()
{
    if( VxIsAppShuttingDown() )
    {
        return 0;
    }

    return m_AudioOut.toGuiGetAudioCacheTotalSeconds();
}

//============================================================================
int AppCommon::toGuiGetAudioCacheFreeSpace( EAppModule appModule )
{
    if( VxIsAppShuttingDown() )
    {
        return 0;
    }

    return m_AudioOut.toGuiGetAudioCacheFreeSpace( appModule );
}

