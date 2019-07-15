#pragma once
//============================================================================
// Copyright (C) 2017 Brett R. Jones
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

#include "ActivityBase.h"
#include <GoTvCore/GoTvP2P/AssetMgr/AssetInfo.h>


class AppletBase : public ActivityBase
{
	Q_OBJECT
public:
	AppletBase( const char * ObjName, AppCommon& app, QWidget * parent );
	virtual ~AppletBase(){};

    void						setTitleBarAppletIcon( EMyIcons appletIcon );

	virtual void				setAssetInfo( AssetInfo& assetInfo ) { m_AssetInfo = assetInfo; }
	virtual AssetInfo&			getAssetInfo( void ) { return m_AssetInfo; }

signals:
	void						signalPlayProgress( int pos );
	void						signalPlayEnd( void );

protected slots:
	virtual void				slotToGuiAssetAction( EAssetAction assetAction, int pos );

protected:
	void						initAppletBase( void );

	//=== vars ===//
	AssetInfo					m_AssetInfo;
	bool						m_ActivityCallbacksEnabled;
	bool						m_IsPlaying;
	bool						m_SliderIsPressed;
};


