
#include "CamCamera.h"
#include "ui_camera.h"
#include "videosettings.h"
#include "imagesettings.h"

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>

#include <QMessageBox>
#include <QPalette>

#include <QtWidgets>
#include <QCameraImageCapture>
#include <QMediaService>

Q_DECLARE_METATYPE(QCameraInfo)

CamCamera::CamCamera() //: ui(new Ui::Camera)
{
    //ui->setupUi(this);

    //CamCamera devices:

    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        //ui->menuDevices->addAction(videoDeviceAction);
    }

    connect(videoDevicesGroup, &QActionGroup::triggered, this, &CamCamera::updateCameraDevice);
    //connect(ui->captureWidget, &QTabWidget::currentChanged, this, &CamCamera::updateCaptureMode);

    setCamera(QCameraInfo::defaultCamera());
}

void CamCamera::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &CamCamera::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &CamCamera::displayCameraError);

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &CamCamera::updateRecorderState);

    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &CamCamera::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &CamCamera::displayRecorderError);

    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

    //connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this, &CamCamera::setExposureCompensation);

    //m_camera->setViewfinder(ui->viewfinder);

    updateCameraState(m_camera->state());
    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &CamCamera::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &CamCamera::processCapturedImage);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &CamCamera::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &CamCamera::displayCaptureError);

    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &CamCamera::updateLockStatus);

    //ui->captureWidget->setTabEnabled(0, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
    //ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    updateCaptureMode();

    QCameraImageCapture *imagecapture = m_imageCapture.data();
    QImageEncoderSettings settings = imagecapture->encodingSettings();
    settings.setResolution( QSize( 320, 240 ) );
    m_imageCapture->setEncodingSettings( settings );

    m_camera->start();
}

void CamCamera::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        m_camera->searchAndLock();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (m_camera->captureMode() == QCamera::CaptureStillImage) {
            takeImage();
        } else {
            if (m_mediaRecorder->state() == QMediaRecorder::RecordingState)
                stop();
            else
                record();
        }
        event->accept();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void CamCamera::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        m_camera->unlock();
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void CamCamera::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
    //ui->statusbar->showMessage(str);
}

void CamCamera::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    //QImage scaledImage = img.scaled(ui->viewfinder->size(),
    //                                Qt::KeepAspectRatio,
    //                                Qt::SmoothTransformation);

    ////ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    //// Display captured image for 4 seconds.
    //displayCapturedImage();
    //QTimer::singleShot(4000, this, &CamCamera::displayViewfinder);
}

void CamCamera::configureCaptureSettings()
{
    switch (m_camera->captureMode()) {
    case QCamera::CaptureStillImage:
        configureImageSettings();
        break;
    case QCamera::CaptureVideo:
        configureVideoSettings();
        break;
    default:
        break;
    }
}

void CamCamera::configureVideoSettings()
{
    VideoSettings settingsDialog(m_mediaRecorder.data());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    settingsDialog.setAudioSettings(m_audioSettings);
    settingsDialog.setVideoSettings(m_videoSettings);
    settingsDialog.setFormat(m_videoContainerFormat);

    if (settingsDialog.exec()) {
        m_audioSettings = settingsDialog.audioSettings();
        m_videoSettings = settingsDialog.videoSettings();
        m_videoContainerFormat = settingsDialog.format();

        m_mediaRecorder->setEncodingSettings(
                    m_audioSettings,
                    m_videoSettings,
                    m_videoContainerFormat);

        m_camera->unload();
        m_camera->start();
    }
}

void CamCamera::configureImageSettings()
{
    ImageSettings settingsDialog(m_imageCapture.data());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    settingsDialog.setImageSettings(m_imageSettings);

    if (settingsDialog.exec()) {
        m_imageSettings = settingsDialog.imageSettings();
        m_imageCapture->setEncodingSettings(m_imageSettings);
    }
}

void CamCamera::record()
{
    m_mediaRecorder->record();
    updateRecordTime();
}

void CamCamera::pause()
{
    m_mediaRecorder->pause();
}

void CamCamera::stop()
{
    m_mediaRecorder->stop();
}

void CamCamera::setMuted(bool muted)
{
    m_mediaRecorder->setMuted(muted);
}

void CamCamera::toggleLock()
{
    switch (m_camera->lockStatus()) {
    case QCamera::Searching:
    case QCamera::Locked:
        m_camera->unlock();
        break;
    case QCamera::Unlocked:
        m_camera->searchAndLock();
    }
}

void CamCamera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    //QColor indicationColor = Qt::black;

    //switch (status) {
    //case QCamera::Searching:
    //    indicationColor = Qt::yellow;
    //    ui->statusbar->showMessage(tr("Focusing..."));
    //    ui->lockButton->setText(tr("Focusing..."));
    //    break;
    //case QCamera::Locked:
    //    indicationColor = Qt::darkGreen;
    //    ui->lockButton->setText(tr("Unlock"));
    //    ui->statusbar->showMessage(tr("Focused"), 2000);
    //    break;
    //case QCamera::Unlocked:
    //    indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
    //    ui->lockButton->setText(tr("Focus"));
    //    if (reason == QCamera::LockFailed)
    //        ui->statusbar->showMessage(tr("Focus Failed"), 2000);
    //}

    //QPalette palette = ui->lockButton->palette();
    //palette.setColor(QPalette::ButtonText, indicationColor);
    //ui->lockButton->setPalette(palette);
}

void CamCamera::takeImage()
{
    m_isCapturingImage = true;
    m_imageCapture->capture();
}

void CamCamera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void CamCamera::startCamera()
{
    m_camera->start();
}

void CamCamera::stopCamera()
{
    m_camera->stop();
}

void CamCamera::updateCaptureMode()
{
    //int tabIndex = ui->captureWidget->currentIndex();
    //QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;
    QCamera::CaptureModes captureMode = QCamera::CaptureStillImage;

    if (m_camera->isCaptureModeSupported(captureMode))
        m_camera->setCaptureMode(captureMode);
}

void CamCamera::updateCameraState(QCamera::State state)
{
    //switch (state) {
    //case QCamera::ActiveState:
    //    ui->actionStartCamera->setEnabled(false);
    //    ui->actionStopCamera->setEnabled(true);
    //    ui->captureWidget->setEnabled(true);
    //    ui->actionSettings->setEnabled(true);
    //    break;
    //case QCamera::UnloadedState:
    //case QCamera::LoadedState:
    //    ui->actionStartCamera->setEnabled(true);
    //    ui->actionStopCamera->setEnabled(false);
    //    ui->captureWidget->setEnabled(false);
    //    ui->actionSettings->setEnabled(false);
    //}
}

void CamCamera::updateRecorderState(QMediaRecorder::State state)
{
    //switch (state) {
    //case QMediaRecorder::StoppedState:
    //    ui->recordButton->setEnabled(true);
    //    ui->pauseButton->setEnabled(true);
    //    ui->stopButton->setEnabled(false);
    //    break;
    //case QMediaRecorder::PausedState:
    //    ui->recordButton->setEnabled(true);
    //    ui->pauseButton->setEnabled(false);
    //    ui->stopButton->setEnabled(true);
    //    break;
    //case QMediaRecorder::RecordingState:
    //    ui->recordButton->setEnabled(false);
    //    ui->pauseButton->setEnabled(true);
    //    ui->stopButton->setEnabled(true);
    //    break;
    //}
}

void CamCamera::setExposureCompensation(int index)
{
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void CamCamera::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void CamCamera::displayCameraError()
{
    QMessageBox::warning(this, tr("CamCamera Error"), m_camera->errorString());
}

void CamCamera::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void CamCamera::displayViewfinder()
{
    //ui->stackedWidget->setCurrentIndex(0);
}

void CamCamera::displayCapturedImage()
{
    //ui->stackedWidget->setCurrentIndex(1);
}

void CamCamera::readyForCapture(bool ready)
{
    //ui->takeImageButton->setEnabled(ready);
}

void CamCamera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    //ui->statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));

    m_isCapturingImage = false;
   // if (m_applicationExiting)
   //     close();
}

void CamCamera::closeEvent(QCloseEvent *event)
{
    if (m_isCapturingImage) {
        //setEnabled(false);
        m_applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}
