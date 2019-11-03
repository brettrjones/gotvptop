#pragma once
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
// http://www.nolimitconnect.com
//============================================================================

#include <CoreLib/AssetDefs.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetInfo.h>
#include <PktLib/VxCommon.h>

#include <QWidget>

class AppCommon;
class MyIcons;
class VxNetIdent;
class AssetInfo;
class ChatEntryWidget;

class InputBaseWidget : public QWidget
{
    Q_OBJECT

public:
	InputBaseWidget( AppCommon& app, QWidget * parent = 0 );

	AppCommon&					getMyApp( void )		{ return m_MyApp; }
	MyIcons&					getMyIcons( void );

	void						setIdents( VxNetIdent * myIdent, VxNetIdent * hisIdent );
	void						setIsPersonalRecorder( bool isPersonal );

signals:
	void						signalChatMessage( QString chatMsg );
	void						signalElapsedRecTime( QString elapsedSec );
	void						signalInputCompleted( void );

public slots:
	void						slotChatMessage( QString chatMsg );
	void						slotElapsedTimerTimeout( void );

protected:
	bool						voiceRecord( EAssetAction action );
	bool						videoRecord( EAssetAction action );
	void						generateFileName( EAssetType assetType, VxGUID& uniqueId );
	void						updateElapsedTime( void );

	//=== vars ===//
	AppCommon&				    m_MyApp;
	ChatEntryWidget *			m_ChatEntryWidget;
	VxNetIdent *				m_MyIdent;
	VxNetIdent *				m_HisIdent;
	AssetInfo					m_AssetInfo;
	std::string					m_FileName;
	int64_t						m_TimeRecStart;
    int64_t						m_TimeRecCurrent;
	QTimer *					m_ElapseTimer;
	bool						m_IsPersonalRecorder;
};
