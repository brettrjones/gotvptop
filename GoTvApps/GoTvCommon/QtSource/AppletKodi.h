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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AppletBase.h"

#include "ui_AppletKodi.h"

class AppletKodi : public AppletBase
{
	Q_OBJECT
public:
	AppletKodi( AppCommon& app, QWidget * parent );
	virtual ~AppletKodi() = default;

    RenderGlWidget *            getRenderConsumer( void );


//	virtual void				setAssetInfo( AssetInfo& assetInfo ) override;
//
//	virtual void				toGuiClientPlayVideoFrame( void * userData, VxGUID& onlineId, uint8_t * pu8Jpg, uint32_t u32JpgDataLen, int motion0To100000 );
//    virtual int	    			toGuiClientPlayVideoFrame( void * userData, VxGUID& onlineId, uint8_t * picBuf, uint32_t picBufLen, int picWidth, int picHeight );
//
//	virtual void				showShredder( bool show );
//	virtual void				showXferProgress( bool show );
//	virtual void				setXferProgress( int sendProgress );
//
protected slots:
    void                        slotMenuItemSelected( int menuId, EMenuItemType menuItemType );
//	virtual void				slotToGuiAssetAction( EAssetAction assetAction, int pos0to100000 );
//	void						slotPlayButtonClicked( void );
//	void						slotShredAsset( void );
//	void						slotSliderPressed( void );
//	void						slotSliderReleased( void );
//
//	void						slotPlayProgress( int pos0to100000 );
//	void						slotPlayEnd( void );

protected:
	void						initAppletKodi( void );
	void						onAppletStop( void );

    void                        startKodiModule( void );
    void                        stopKodiModule( void );


    void                        setupBottomMenu( VxMenuButton * menuButton );

	void						showEvent( QShowEvent * ev );
    void						hideEvent( QHideEvent * ev );
	void						resizeEvent( QResizeEvent * ev );

	void						setReadyForCallbacks( bool isReady );
	//void						updateGuiPlayControls( bool isPlaying );
	//void						startMediaPlay( int startPos );
	//void						stopMediaIfPlaying( void );

	////=== vars ===//
	bool						m_ActivityCallbacksEnabled;
	//bool						m_IsPlaying;
	//bool						m_SliderIsPressed;

	Ui::AppletKodiClass	        ui;
};
