#pragma once

#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>

#include <QMainWindow>

namespace Ui {
class MainWindowUi;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void setCamera( const QCameraInfo &cameraInfo );

    void startCamera();
    void stopCamera();

    void record();
    void pause();
    void stop();
    void setMuted( bool );

    void toggleLock();
    void takeImage();
    void displayCaptureError( int, QCameraImageCapture::Error, const QString &errorString );

    void configureCaptureSettings();
    void configureVideoSettings();
    void configureImageSettings();

    void displayRecorderError();
    void displayCameraError();

    void updateCameraDevice( QAction *action );

    void updateCameraState( QCamera::State );
    void updateCaptureMode( int );
    void updateRecorderState( QMediaRecorder::State state );
    void setExposureCompensation( int index );

    void updateRecordTime();

    void processCapturedImage( int requestId, const QImage &img );
    void updateLockStatus( QCamera::LockStatus, QCamera::LockChangeReason );

    void displayViewfinder();
    void displayCapturedImage();

    void readyForCapture( bool ready );
    void imageSaved( int id, const QString &fileName );

    void slotTakeSnapshot( void );

protected:
    void keyPressEvent( QKeyEvent *event ) override;
    void keyReleaseEvent( QKeyEvent *event ) override;
    void closeEvent( QCloseEvent *event ) override;

private:
    Ui::MainWindowUi*           ui;
    QTimer *                    m_SnapshotTimer{ nullptr };

    QScopedPointer<QCamera>     m_camera;
    QScopedPointer<QCameraImageCapture> m_imageCapture;
    //QScopedPointer<QMediaRecorder> m_mediaRecorder;

    QImageEncoderSettings       m_imageSettings;
    QAudioEncoderSettings       m_audioSettings;
    //QVideoEncoderSettings       m_videoSettings;
    //QString                     m_videoContainerFormat;
    bool                        m_isCapturingImage = false;
    bool                        m_applicationExiting = false;
};
