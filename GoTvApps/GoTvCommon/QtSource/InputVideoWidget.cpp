//============================================================================
// Copyright (C) 2015 Brett R. Jones
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

#include "InputVideoWidget.h"
#include "AppCommon.h"
#include "AppSettings.h"

#include <CoreLib/VxGlobals.h>

#include <QDebug>

//============================================================================
InputVideoWidget::InputVideoWidget( QWidget * parent )
: InputBaseWidget( GetAppInstance(), parent )
, m_IsRecording( false )
{
	qDebug() << "InputVideoWidget::InputVideoWidget ";
	m_AssetInfo.setAssetType( eAssetTypeVideo );

	ui.setupUi( this );

	ui.m_CancelRecordButton->setIcons( eMyIconCamcorderCancel );
	//ui.m_CancelRecordButton->setVisible( false );

	ui.m_StartStopRecButton->setIsToggleButton( true );
	ui.m_StartStopRecButton->setIcons( eMyIconCamcorderNormal );
	ui.m_RotateCamButton->setIcons( eMyIconCamRotateNormal );
	ui.m_SelectVidSrcButton->setIcons( eMyIconCamSelectNormal );
	ui.m_SelectVidSrcButton->setEnabled( false );
	connect( ui.m_StartStopRecButton,		SIGNAL(clicked()),	this, SLOT(slotBeginRecord()) );
	connect( ui.m_RotateCamButton,			SIGNAL(clicked()),	this, SLOT(slotRotateCamButtonClicked()) );
	connect( ui.m_CancelRecordButton,		SIGNAL(clicked()),	this, SLOT(slotRecordCancelButtonClicked()) );
}

//============================================================================
void InputVideoWidget::showEvent(QShowEvent * showEvent)
{
	InputBaseWidget::showEvent(showEvent);
	if( ( 0 != m_MyIdent ) && ( false == VxIsAppShuttingDown() ) )
	{
		ui.m_VidWidget->setVideoFeedId( m_AssetInfo.getCreatorId() );
		m_MyApp.getEngine().fromGuiWantMediaInput( m_AssetInfo.getCreatorId(), eMediaInputVideoJpgSmall, true );
	}
}

//============================================================================
void InputVideoWidget::hideEvent(QHideEvent * hideEvent)
{
	if( ( 0 != m_MyIdent ) && ( false == VxIsAppShuttingDown() ) )
	{
		if( m_IsRecording )
		{
			m_IsRecording = false;
			videoRecord( eAssetActionRecordCancel );
			ui.m_StartStopRecButton->setToggleState( false );
		}

		ui.m_VidWidget->setVideoFeedId( m_AssetInfo.getCreatorId() );
		m_MyApp.getEngine().fromGuiWantMediaInput( m_AssetInfo.getCreatorId(), eMediaInputVideoJpgSmall, false );		
	}

	InputBaseWidget::hideEvent(hideEvent);
}

//============================================================================
void InputVideoWidget::slotRotateCamButtonClicked( void )
{
	uint32_t camId = m_MyApp.getAppSettings().getCamSourceId();
	int camRotation = m_MyApp.getAppSettings().getCamRotation( camId );
	camRotation += 90;
	if( camRotation >= 360 )
	{
		camRotation = 0;
	}

	m_MyApp.getAppSettings().setCamRotation( camId, camRotation );
	m_MyApp.setCamCaptureRotation( camRotation );
}

//============================================================================
void InputVideoWidget::slotBeginRecord( void )
{
	if( m_IsRecording )
	{
		m_IsRecording = false;
		videoRecord( eAssetActionRecordEnd );
		ui.m_StartStopRecButton->setToggleState( false );
		emit signalInputCompleted();
	}
	else
	{
		m_IsRecording = true;
		videoRecord( eAssetActionRecordBegin );
		ui.m_StartStopRecButton->setToggleState( true );
	}
}

//============================================================================
void InputVideoWidget::slotRecordCancelButtonClicked( void )
{
	if( m_IsRecording )
	{
		m_IsRecording = false;
		videoRecord( eAssetActionRecordCancel );
		ui.m_StartStopRecButton->setToggleState( false );
	}

	emit signalInputCompleted();
}

//============================================================================
void InputVideoWidget::playVideoFrame( VxGUID& onlineId, unsigned char * pu8Jpg, unsigned long u32JpgLen, int motion0To100000 )
{
	ui.m_VidWidget->playVideoFrame( onlineId, pu8Jpg, u32JpgLen, motion0To100000 );
}
