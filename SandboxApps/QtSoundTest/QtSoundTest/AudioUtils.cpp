
#include <QAudioFormat>
#include "AudioUtils.h"

qint64 AudioUtils::audioDuration(const QAudioFormat &format, qint64 bytes)
{
    return (bytes * 1000000) /
        (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8));
}

qint64 AudioUtils::audioLength(const QAudioFormat &format, qint64 microSeconds)
{
   qint64 result = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
       * microSeconds / 1000000;
   result -= result % (format.channelCount() * format.sampleSize());
   return result;
}

qreal AudioUtils::nyquistFrequency(const QAudioFormat &format)
{
    return format.sampleRate() / 2;
}

QString AudioUtils::formatToString(const QAudioFormat &format)
{
    QString result;

    if (QAudioFormat() != format) {
        if (format.codec() == "audio/pcm") {
            Q_ASSERT(format.sampleType() == QAudioFormat::SignedInt);

            const QString formatEndian = (format.byteOrder() == QAudioFormat::LittleEndian)
                ?   QString("LE") : QString("BE");

            QString formatType;
            switch (format.sampleType()) {
            case QAudioFormat::SignedInt:
                formatType = "signed";
                break;
            case QAudioFormat::UnSignedInt:
                formatType = "unsigned";
                break;
            case QAudioFormat::Float:
                formatType = "float";
                break;
            case QAudioFormat::Unknown:
                formatType = "unknown";
                break;
            }

            QString formatChannels = QString("%1 channels").arg(format.channelCount());
            switch (format.channelCount()) {
            case 1:
                formatChannels = "mono";
                break;
            case 2:
                formatChannels = "stereo";
                break;
            }

            result = QString("%1 Hz %2 bit %3 %4 %5")
                .arg(format.sampleRate())
                .arg(format.sampleSize())
                .arg(formatType)
                .arg(formatEndian)
                .arg(formatChannels);
        } else {
            result = format.codec();
        }
    }

    return result;
}

bool AudioUtils::isPCM(const QAudioFormat &format)
{
    return (format.codec() == "audio/pcm");
}


bool AudioUtils::isPCMS16LE(const QAudioFormat &format)
{
    return isPCM(format) &&
           format.sampleType() == QAudioFormat::SignedInt &&
           format.sampleSize() == 16 &&
           format.byteOrder() == QAudioFormat::LittleEndian;
}

const qint16  PCMS16MaxValue     =  32767;
const quint16 PCMS16MaxAmplitude =  32768; // because minimum is -32768

qreal AudioUtils::pcmToReal(qint16 pcm)
{
    return qreal(pcm) / PCMS16MaxAmplitude;
}

float AudioUtils::pcmToFloat( int16_t pcm )
{
    return float(pcm) / PCMS16MaxAmplitude;
}


qint16 AudioUtils::realToPcm(qreal real)
{
    return real * PCMS16MaxValue;
}

int16_t AudioUtils::floatToPcm( float val )
{
    return val * PCMS16MaxValue;
}
