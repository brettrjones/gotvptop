/*
 *      Copyright (C) 2010-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "config_kodi.h"
#ifdef HAVE_QT_GUI

#include "AESinkQt.h"

#include <stdint.h>
#include <limits.h>
#include <unistd.h>

#include "cores/AudioEngine/AESinkFactory.h"
#include "cores/AudioEngine/Utils/AEUtil.h"
#include "cores/AudioEngine/Engines/ActiveAE/ActiveAE.h"

#include "utils/log.h"
#include "threads/SingleLock.h"
#include <sstream>

#include <sys/ioctl.h>

#include "GoTvInterface/IGoTv.h"
#include <CoreLib/VxDebug.h>

#define OSS_FRAMES 256

//static enum AEChannel QtChannelMap[ 9 ] = { AE_CH_FL, AE_CH_FR, AE_CH_BL, AE_CH_BR, AE_CH_FC, AE_CH_LFE, AE_CH_SL, AE_CH_SR, AE_CH_NULL };
static enum AEChannel QtChannelMap[ 9 ] = { AE_CH_FL, AE_CH_FR, AE_CH_NULL, AE_CH_NULL, AE_CH_NULL, AE_CH_NULL, AE_CH_NULL, AE_CH_NULL, AE_CH_NULL };

static const unsigned int PassthroughSampleRates[] = { 8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000, 88200, 96000, 176400, 192000 };


//============================================================================
CAESinkQt::CAESinkQt()
: m_IGoTv( IGoTv::getIGoTv() )
{
}

//============================================================================
CAESinkQt::~CAESinkQt()
{
    Deinitialize();
}

//============================================================================
void CAESinkQt::Register()
{
    AE::AESinkRegEntry entry;
    entry.sinkName = "AESinkQt";
    entry.createFunc = CAESinkQt::Create;
    entry.enumerateFunc = CAESinkQt::EnumerateDevicesEx;
    AE::CAESinkFactory::RegisterSink( entry );
}

//============================================================================
IAESink* CAESinkQt::Create( std::string &device, AEAudioFormat& desiredFormat )
{
    IAESink* sink = new CAESinkQt();
    if( sink->Initialize( desiredFormat, device ) )
        return sink;

    delete sink;
    return nullptr;
}

//============================================================================
std::string CAESinkQt::GetDeviceUse( const AEAudioFormat& format, const std::string &device )
{
    return device;
}

//============================================================================
bool CAESinkQt::Initialize( AEAudioFormat& desiredFormat, std::string &device )
{
    m_DesiredFormat = desiredFormat;
    m_AvailableFormat.m_channelLayout = AE_CH_LAYOUT_2_0;
    m_AvailableFormat.m_sampleRate = 48000;

#if OUTPUT_PCM_SAMPLES
    m_AvailableFormat.m_dataFormat = AE_FMT_S16LE;
    // m_frameSize is misnamed.. is really number of bytes per sample of all channels ie 2 channels * 16 bit samples = 4 or if float format then 2 channels * 4 bytes per sample = 8
    m_AvailableFormat.m_frameSize = 4;
    m_AvailableFormat.m_frames = 15360 / m_AvailableFormat.m_frameSize;  // 80 ms samples of 2 channel 4 bytes per sample * 48000 Hz
#else
    m_AvailableFormat.m_dataFormat = AE_FMT_FLOAT;
    // m_frameSize is misnamed.. is really number of bytes per sample of all channels ie 2 channels * 16 bit samples = 4 or if float format then 2 channels * 4 bytes per sample = 8
    m_AvailableFormat.m_frameSize = 2 * sizeof( float );
    // frames is misnamed.. is really number of samples per frame 
    m_AvailableFormat.m_frames = 48000 * 0.015;  // 15 ms samples
#endif // OUTPUT_PCM_SAMPLES

    desiredFormat = m_AvailableFormat;
    device = GetName();
    m_device = device;
    return true;
}

//============================================================================
void CAESinkQt::Deinitialize()
{
    Stop();
}

//============================================================================
inline CAEChannelInfo CAESinkQt::GetChannelLayout( const AEAudioFormat& format )
{
    int count = 2;
    CAEChannelInfo info;
    for( unsigned int i = 0; i < count; ++i )
    {
        info += QtChannelMap[ i ];
    }

    return info;
}

//============================================================================
void CAESinkQt::Stop()
{
}

//============================================================================
void CAESinkQt::GetDelay( AEDelayStatus& status )
{
    // return current cached data duration in seconds 
    status.SetDelay( m_IGoTv.toGuiGetAudioDelaySeconds() );
}

//============================================================================
double CAESinkQt::GetCacheTotal( )
{
    // return total possible cached data duration in seconds 
    return  m_IGoTv.toGuiGetAudioCacheTotalSeconds();
}

//============================================================================
unsigned int CAESinkQt::AddPackets( uint8_t **data, unsigned int frames, unsigned int offset )
{
    int size = frames * m_AvailableFormat.m_frameSize;

    void * buffer = data[ 0 ] + offset * m_AvailableFormat.m_frameSize;

    //static bool firstSample = true;
    //if( firstSample && ( frames > 16 ) )
    //{
    //    float * inSampleData = ( float * )buffer;
    //    testDataHasVolume( inSampleData, frames );
    //    if( g_BeginDebug )
    //    {
    //        firstSample = false;
    //        LogMsg( LOG_DEBUG, "CAESinkQt::AddPackets sample dump \n" );
    //        DumpFloat( LOG_DEBUG, inSampleData, 16 );
    //    }
    //}

	int retryCnt = 0;
    while( ( m_IGoTv.toGuiGetAudioCacheFreeSpace( eAppModuleKodi ) < size ) && ( retryCnt < 5 ) )
    {
        int requiredSpace = size - m_IGoTv.toGuiGetAudioCacheFreeSpace( eAppModuleKodi );
        if( requiredSpace > 0 )
        {
            VxSleep( 100 );
			retryCnt++;
        }
		else
		{
			break;
		}
    }

	if( retryCnt >= 5 )
	{
		LogMsg( LOG_DEBUG, "CAESinkQt::AddPackets timeout snd buf needs %d free space but has %d \n", size, m_IGoTv.toGuiGetAudioCacheFreeSpace( eAppModuleKodi )  );
	}

    //float* pBuffer = ( float* )data[ 0 ] + offset*m_AvailableFormat.m_frameSize;
    //static int frameCnt = 0;
    //if( pBuffer && frames > 16 )
    //{
    //    bool hasValue = false;
    //    for( int i = 0; i < 16; i++ )
    //    {
    //        hasValue = pBuffer[ i ] != 0.0f;
    //        if( hasValue )
    //        {
    //            break;
    //        }
    //    }

    //    if( hasValue )
    //    {
    //        frameCnt++;
    //        if( m_AvailableFormat.m_dataFormat == AE_FMT_U8 )
    //        {
    //            DumpInt8( LOG_DEBUG, ( int8_t * )data[ 0 ], 16, frameCnt, "sink add u8" );
    //        }
    //        else if( m_AvailableFormat.m_dataFormat == AE_FMT_S16LE || m_AvailableFormat.m_dataFormat == AE_FMT_S16NE )
    //        {
    //            DumpInt16( LOG_DEBUG, ( int16_t * )data[ 0 ], 16 * 2, frameCnt, "sink add s16" );
    //        }
    //        else if( m_AvailableFormat.m_dataFormat == AE_FMT_FLOATP || m_AvailableFormat.m_dataFormat == AE_FMT_FLOAT )
    //        {
    //            DumpFloat( LOG_DEBUG, ( float * )data[ 0 ], 16 * 4, frameCnt, "sink add float" );
    //        }
    //    }
    //}

    int wrote = m_IGoTv.toGuiPlayAudio( eAppModuleKodi, (int16_t *)buffer, size );
    if( wrote < 0 )
    {
        CLog::Log( LOGERROR, "CAESinkQt::AddPackets - Failed to write" );
        return INT_MAX;
    }
    else if( wrote != size )
    {
        CLog::Log( LOGERROR, "CAESinkQt::AddPackets - write not complete %d", wrote );
        return INT_MAX;
    }


    return wrote / m_AvailableFormat.m_frameSize; // number of frames used
}

//============================================================================
void CAESinkQt::Drain()
{
}

//============================================================================
void CAESinkQt::EnumerateDevicesEx( AEDeviceInfoList &list, bool force )
{
    // BRJ
    CAEDeviceInfo info;
    info.m_deviceName           = "AESinkQt";
    info.m_displayName          = "AESinkQt";

#if OUTPUT_PCM_SAMPLES
    info.m_dataFormats.push_back( AE_FMT_S16LE );
#else
    info.m_dataFormats.push_back( AE_FMT_FLOAT );
#endif // OUTPUT_PCM_SAMPLES

    info.m_deviceType           = AE_DEVTYPE_PCM;
    info.m_wantsIECPassthrough  = false;
    info.m_channels             = AE_CH_LAYOUT_2_0;
    info.m_sampleRates.push_back( 48000 );
    list.push_back( info );
}

#endif // HAVE_QT_GUI
