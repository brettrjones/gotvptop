//============================================================================
// Copyright (C) 2018 Brett R. Jones
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

#include "AudioTestGenerator.h"

#include <qmath.h>
#include <qendian.h>

namespace // anonymous
{
    const int DurationSeconds = 0.800;
    const int ToneSampleRateHz = 800;
    const int DataSampleRateHz = 48000;
    const int BufferSize = 15360 * 10;
};

//============================================================================
AudioTestGenerator::AudioTestGenerator( const QAudioFormat &format,
                                        qint64 durationUs,
                                        int sampleRate,
                                        QObject *parent )
: QIODevice( parent )
, m_pos( 0 )
{
    if( format.isValid() )
    {
        generateData( format, durationUs, sampleRate );
    }
}

//============================================================================
void AudioTestGenerator::start()
{
    open( QIODevice::ReadOnly );
}

//============================================================================
void AudioTestGenerator::stop()
{
    m_pos = 0;
    close();
}

//============================================================================
void AudioTestGenerator::generateData( const QAudioFormat &format, qint64 durationUs, int sampleRate )
{
    const int channelBytes = format.sampleSize() / 8;
    const int sampleBytes = format.channelCount() * channelBytes;

    qint64 length = ( format.sampleRate() * format.channelCount() * ( format.sampleSize() / 8 ) ) * durationUs / 100000;

    Q_ASSERT( length % sampleBytes == 0 );
    Q_UNUSED( sampleBytes ) // suppress warning in release builds

    m_buffer.resize( length );
    unsigned char *ptr = reinterpret_cast< unsigned char * >( m_buffer.data() );

    int sampleIndex = 0;

    while( length ) 
    {
        const qreal x = qSin( 2 * M_PI * sampleRate * qreal( sampleIndex % format.sampleRate() ) / format.sampleRate() );
        for( int i = 0; i < format.channelCount(); ++i ) 
        {
            if( format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt ) 
            {
                const quint8 value = static_cast< quint8 >( ( 1.0 + x ) / 2 * 255 );
                *reinterpret_cast< quint8* >( ptr ) = value;
            }
            else if( format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt ) 
            {
                const qint8 value = static_cast< qint8 >( x * 127 );
                *reinterpret_cast< quint8* >( ptr ) = value;
            }
            else if( format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt ) 
            {
                quint16 value = static_cast< quint16 >( ( 1.0 + x ) / 2 * 65535 );
                if( format.byteOrder() == QAudioFormat::LittleEndian )
                    qToLittleEndian<quint16>( value, ptr );
                else
                    qToBigEndian<quint16>( value, ptr );
            }
            else if( format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt ) 
            {
                qint16 value = static_cast< qint16 >( x * 32767 );
                if( format.byteOrder() == QAudioFormat::LittleEndian )
                    qToLittleEndian<qint16>( value, ptr );
                else
                    qToBigEndian<qint16>( value, ptr );
            }

            ptr += channelBytes;
            length -= channelBytes;
        }

        ++sampleIndex;
    }
}

//============================================================================
qint64 AudioTestGenerator::readData( char *data, qint64 len )
{
    qint64 total = 0;
    if( !m_buffer.isEmpty() ) 
    {
        while( len - total > 0 ) 
        {
            const qint64 chunk = qMin( ( m_buffer.size() - m_pos ), len - total );
            memcpy( data + total, m_buffer.constData() + m_pos, chunk );
            m_pos = ( m_pos + chunk ) % m_buffer.size();
            total += chunk;
        }
    }

    return total;
}


//============================================================================
qint64 AudioTestGenerator::readData( QByteArray& retData, qint64 len )
{
    qint64 total = 0;
    if( !m_buffer.isEmpty() )
    {
        while( len - total > 0 )
        {
            const qint64 chunk = qMin( ( m_buffer.size() - m_pos ), len - total );
            memcpy( retData.data() + total, m_buffer.constData() + m_pos, chunk );
            m_pos = ( m_pos + chunk ) % m_buffer.size();
            total += chunk;
        }
    }

    return total;
}

//============================================================================
qint64 AudioTestGenerator::writeData( const char *data, qint64 len )
{
    Q_UNUSED( data );
    Q_UNUSED( len );

    return 0;
}

//============================================================================
qint64 AudioTestGenerator::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}
