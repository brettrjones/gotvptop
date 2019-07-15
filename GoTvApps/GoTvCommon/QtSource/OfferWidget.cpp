//============================================================================
// Copyright (C) 2013 Brett R. Jones 
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

#include "OfferWidget.h"
#include "MyIcons.h"
#include "AppCommon.h"

//============================================================================
OfferWidget::OfferWidget( QWidget * parent )
: QWidget( parent )
, m_MyApp( GetAppInstance() )
{
	SubWidget = new QPushButton( parent );
	ui.setupUi( SubWidget );
	setOnlineState( true );
	ui.m_AcceptButton->setIcon( eMyIconAcceptNormal );
	ui.m_RejectButton->setIcon( eMyIconCancelNormal );

	connect( SubWidget,			SIGNAL(pressed()),		this, SLOT(listButtonPressed()) );
	connect( SubWidget,			SIGNAL(released()),		this, SLOT(listButtonReleased()) );
	connect( ui.m_FriendButton,	SIGNAL(pressed()),		this, SLOT(iconButtonPressed()) );
	connect( ui.m_FriendButton,	SIGNAL(released()),		this, SLOT(iconButtonReleased()) );
	connect( ui.m_AcceptButton,	SIGNAL(pressed()),		this, SLOT(slotAcceptButtonPressed()) );
	connect( ui.m_RejectButton,	SIGNAL(pressed()),		this, SLOT(slotRejectButtonReleased()) );
}

//============================================================================
OfferWidget::~OfferWidget()
{
}

//============================================================================
MyIcons&  OfferWidget::getMyIcons( void )
{
	return m_MyApp.getMyIcons();
}

//============================================================================
void OfferWidget::iconButtonPressed()
{
	SubWidget->setDown(true);
	emit listButtonClicked( this );
}

//============================================================================
void OfferWidget::iconButtonReleased()
{
	SubWidget->setDown(false);
}

//============================================================================
void OfferWidget::listButtonPressed()
{
	emit listButtonClicked( this );
}

//============================================================================
void OfferWidget::listButtonReleased()
{
}

//============================================================================
void OfferWidget::slotAcceptButtonPressed( void )
{
	emit acceptButtonClicked( this );
}

//============================================================================
void OfferWidget::slotRejectButtonReleased( void )
{
	emit rejectButtonClicked( this );
}

//============================================================================
void OfferWidget::setOnlineState( bool isOnline )
{
	if( m_IsOnline != isOnline )
	{
		m_IsOnline = isOnline;
		if( m_IsOnline )
		{
			SubWidget->setStyleSheet("border-image: 0; background-color: rgb(184, 231, 249); color: rgb(0, 0, 0); font: 14px;\n");
		}
		else
		{
			ui.m_AcceptButton->setIcon( eMyIconAcceptDisabled );
			ui.m_AcceptButton->setEnabled( false );
			SubWidget->setStyleSheet("border-image: 0; background-color: rgb(192, 192, 192); color: rgb(0, 0, 0); font: 14px;\n");
		}
	}
}

//============================================================================
void OfferWidget::setAvailable( bool available )
{
	return ui.m_AcceptButton->setEnabled( available );
}

//============================================================================
bool OfferWidget::isOfferAvailable( void )
{
	return ui.m_AcceptButton->isEnabled();
}

//============================================================================
void OfferWidget::setMissedCalls( int missedCallCnt )
{
	if( 0 == missedCallCnt )
	{
		ui.m_MissedCallsLabel->setVisible( false );
		ui.m_MissedCallCntLabel->setVisible( false );
	}
	else
	{
		ui.m_MissedCallsLabel->setVisible( true );
		ui.m_MissedCallCntLabel->setVisible( true );
		ui.m_MissedCallCntLabel->setText( QString("%1").arg(missedCallCnt) );
	}
}
