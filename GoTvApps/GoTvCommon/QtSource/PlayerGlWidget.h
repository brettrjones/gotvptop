#pragma once
//============================================================================
// Copyright (C) 2018 Brett R. Jones
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

#include "config_gotvapps.h"

#include <QDebug>
#include <QTimer>
#include <QFile>

#include "ui_PlayerGlWidget.h"
#include <CoreLib/VxGUID.h>


class AppCommon;
class AppSettings;
class P2PEngine;

class PlayerGlWidget : public QWidget
{
	Q_OBJECT

public:
	PlayerGlWidget(QWidget *parent=0);

	AppCommon&					getMyApp( void ) { return m_MyApp; }
	MyIcons&					getMyIcons( void );

	void						setVideoFeedId( VxGUID& feedOnlineId );
	VxGUID&						getFeedId( void )								{ return m_VideoFeedId; }

	void						setRecordFriendName( QString friendName )		{ m_RecFriendName = friendName; }
	QString&					getRecordFriendName( void )						{ return m_RecFriendName; }
	void						setRecordFilePath( QString filePath )			{ m_RecFilePath = filePath; }
	QString&					getRecordFilePath( void )						{ return m_RecFilePath; }
	void						setRecordFileName( QString fileName )			{ m_RecFileName = fileName; }
	QString&					getRecordFileName( void )						{ return m_RecFileName; }

	void						setVidImageRotation( int imageRotation );
	int							getVidImageRotation( void );

	void						showOfflineImage( void );
	void						setImageFromFile( QString fileName );
	VxLabel *					getVideoScreen( void );

    void                        showUserMsgLabel( bool showCtrls );
	void						showAllControls( bool showCtrls );
	void						showFeedControls( bool showCtrls );
	bool						isFeedControlsVisible( void );
	void						showRecordControls( bool showCtrls );
	bool						isRecordControlsVisible( void );
	void						showMotionSensitivityControls( bool showCtrls );
	bool						isMotionSensitivityControlsVisible( void );
	void						disablePreview( bool disable );
	void						disableRecordControls( bool disable )					{ m_DisableRecordControls = disable; }
	void						enableCamSourceControls( bool enable );
	void						enableCamFeedControls( bool enable );

	void						playVideoFrame( VxGUID&	feedOnlineId, unsigned char * pu8Jpg, unsigned long u32JpgLen, int motion0To100000 );
    int                         playVideoFrame( VxGUID& feedOnlineId, uint8_t * picBuf, uint32_t picBufLen, int picWidth, int picHeight );

    void                        setAspectRatio( float aspectRatio );

signals:			
	void						clicked();
	void						recordBegin();
	void						recordEnd();
	void						playBegin();
	void						playEnd();
	void						signalVidFeedMotion( int motion0To100000 );

protected slots:
	void						slotStatusMsg( QString userMsg );
	void						slotWidgetClicked( void );
	void						slotCamPreviewButtonClicked( void );
	void						slotCamRotateButtonClicked( void );
	void						slotFeedRotateButtonClicked( void );

	void						slotVidFilesButtonClicked( void );

	void						slotPictureSnapshotButton( void );
	void						slotMotionAlarmButtonClicked( void );
	void						slotRecMotionButtonClicked( void );
	void						slotRecNormalButtonClicked( void );
	void						slotVidFeedMotion( int motion0To100000 );

	void						slotIconToggleTimeout( void );
	void						slotMotionAlarmTimeout( void );
	void						slotMotionRecordTimeout( void );

protected:
	virtual void				showEvent( QShowEvent * ev );
	virtual void				hideEvent( QHideEvent * ev );
	void						updatePreviewVisibility( void );
	void						updateVidFeedImageRotation( void );
	void						updateCamRotation( void );
	void						playMotionAlarm( void );
	void						updateMotionBarColor( void );
	void						showMotion( int motion0To100000 );
	void						enableVidFilesButton( bool enable );

	//=== vars ===//
	Ui::PlayerGlWidgetClass		ui;
	AppCommon&				    m_MyApp;
	P2PEngine&					m_Engine;
	AppSettings&				m_AppSettings;
	VxGUID&						m_MyOnlineId; 
	VxLabel *					m_ThumbnailPreview;
	VxGUID						m_VideoFeedId; 
	bool						m_DisablePreview;
	bool						m_DisableRecordControls;
	QString						m_RecFriendName;
	QString						m_RecFilePath;
	QString						m_RecFileName;
	bool						m_IconToggle;
	QTimer *					m_IconToggleTimer;
	bool						m_MotionAlarmOn;
	bool						m_MotionAlarmDetected;
	QTimer *					m_MotionAlarmExpireTimer;
	bool						m_MotionRecordOn;
	bool						m_MotionRecordDetected;
	QTimer *					m_MotionRecordExpireTimer;
	bool						m_InNormalRecord;
};
