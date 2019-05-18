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
// http://www.gotvptop.net
//============================================================================

#include "InputVoiceWidget.h"
#include "ChatEntryWidget.h"
#include "AppCommon.h"
#include "MyIcons.h"

#include <QDebug>

//============================================================================
InputVoiceWidget::InputVoiceWidget( QWidget * parent )
: InputBaseWidget( GetAppInstance(), parent )
, m_IsRecording( false )
{
	qDebug() << "InputVoiceWidget::InputVoiceWidget ";
	m_AssetInfo.setAssetType( eAssetTypeAudio );

	ui.setupUi( this );

	ui.m_RecVoiceButton->setIcons( eMyIconMicrophoneOn );
	ui.m_RecVoiceButton->setIsSlideLeftButton( true );
	ui.m_RecVoiceButton->setPressedSound( eSndDefNone );
	ui.m_CancelVoiceButton->setIcons( eMyIconMicrophoneCancelNormal );
	ui.m_CancelVoiceButton->setPressedSound( eSndDefCancel );
	ui.m_ShredderButton->setVisible( false );

	//connect( ui.m_RecVoiceButton,		SIGNAL(pressed()),				this, SLOT(slotBeginRecord()) );
	connect( ui.m_RecVoiceButton,		SIGNAL(clicked()),				this, SLOT(slotBeginRecord()) );
	//connect( ui.m_RecVoiceButton,		SIGNAL(released()),				this, SLOT(slotEndRecord()) );
	connect( ui.m_RecVoiceButton,		SIGNAL(slideLeftCompleted()),	this, SLOT(slotRecVoiceCancel()) );
	connect( ui.m_CancelVoiceButton,	SIGNAL(clicked()),				this, SLOT(slotRecVoiceCancel()) );
	connect( ui.m_ShredderButton,		SIGNAL(animationCompleted()),	this, SLOT(slotShredComplete()) );
}

//============================================================================
void InputVoiceWidget::slotBeginRecord( void )
{
	if( m_IsRecording )
	{
		m_IsRecording = false;
		voiceRecord( eAssetActionRecordEnd );
		ui.m_RecVoiceButton->setIcon( eMyIconMicrophoneOn );
	}
	else
	{
		m_IsRecording = true;
		voiceRecord( eAssetActionRecordBegin );
		ui.m_RecVoiceButton->setIcon( eMyIconMicrophoneOff );
	}
}

//============================================================================
void InputVoiceWidget::slotEndRecord( void )
{
	voiceRecord( eAssetActionRecordEnd );
}

//============================================================================
void InputVoiceWidget::slotRecVoiceCancel( void )
{
	ui.m_CancelVoiceButton->setVisible( false );
	ui.m_ShredderButton->setVisible( true );
	ui.m_ShredderButton->playSndAndAnimation( 4 );
	voiceRecord( eAssetActionRecordCancel );
}

//============================================================================
void InputVoiceWidget::slotShredComplete( void )
{
	if( m_ChatEntryWidget )
	{
		this->setVisible( false );
		m_ChatEntryWidget->setEntryMode( eAssetTypeUnknown );
	}
}