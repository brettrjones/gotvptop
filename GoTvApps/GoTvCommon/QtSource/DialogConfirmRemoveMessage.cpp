//============================================================================
// Copyright (C) 2016 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "DialogConfirmRemoveMessage.h"
#include "MyIcons.h"
#include "AppCommon.h"

#include <GoTvCore/GoTvP2P/AssetMgr/AssetInfo.h>

//============================================================================
DialogConfirmRemoveMessage::DialogConfirmRemoveMessage( AssetInfo& assetInfo, QWidget * parent )
: QDialog( parent, Qt::Popup )
, m_MyApp( GetAppInstance() )
, m_AssetInfo( assetInfo )
, m_AssetAction( eAssetActionUnknown )
{
	ui.setupUi(this);
	//QRect oRect = parent->geometry();
	//oRect.setRight(oRect.right() - oRect.left());
	//oRect.setLeft(0);
	//oRect.setBottom(oRect.bottom() - oRect.top());
	//oRect.setTop(0);
	//this->setGeometry(oRect);

	ui.m_CancelButton->setIcon( eMyIconCancelNormal );
	ui.m_RemoveButton->setIcon( eMyIconTrash );
	ui.m_ShredButton->setIcon( eMyIconShredderNormal  );


	connect( ui.m_ExitDlgButton,		SIGNAL(clicked()), this, SLOT(reject()) );
	connect( ui.m_CancelButton,			SIGNAL(clicked()), this, SLOT(reject()) );
	connect( ui.m_RemoveButton,			SIGNAL(clicked()), this, SLOT(slotRemoveAssetButtonClicked()) );
	connect( ui.m_ShredButton,			SIGNAL(clicked()), this, SLOT(slotShredFileButtonClicked()) );
	if( false == m_AssetInfo.getIsFileAsset() )
	{
		ui.m_ShredButton->setVisible( false );
		ui.m_ShredTextLabel->setVisible( false );
	}
}

//============================================================================
DialogConfirmRemoveMessage::~DialogConfirmRemoveMessage()
{
}

//============================================================================
MyIcons&  DialogConfirmRemoveMessage::getMyIcons( void )
{
	return m_MyApp.getMyIcons();
}

//============================================================================
void DialogConfirmRemoveMessage::slotRemoveAssetButtonClicked( void )
{
	m_AssetAction = eAssetActionRemoveFromAssetMgr;
	accept();
}

//============================================================================
void DialogConfirmRemoveMessage::slotShredFileButtonClicked( void )
{
	m_AssetAction = eAssetActionShreadFile;
	accept();
}
