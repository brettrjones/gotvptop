#pragma once
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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include <PktLib/VxCommon.h>

#include "ui_ActivityWebCamClient.h"
#include "ActivityToFriendBase.h"

class AppCommon;
class P2PEngine;
class VxNetIdent;
class QLabel;
class QImage;

class ActivityWebCamClient : public ActivityToFriendBase
{
	Q_OBJECT
public:

	ActivityWebCamClient(	AppCommon&			app,
							VxNetIdent *			netIdent, 
							QWidget *				parent = NULL );

	virtual ~ActivityWebCamClient();

	void						playVideoFrame( VxGUID& feedId, unsigned char * pu8Jpg, unsigned long u32JpgLen, int motion0To100000 );

	void						webCamSourceOffline();

signals:
	void						signalPlayVideoFrame( QPixmap oPicBitmap, int iRotate );
	void						signalPlayAudio( unsigned short * pu16PcmData, unsigned short u16PcmDataLen );

protected slots:
	//void						slotMuteMicButtonClicked( bool muteMicrophone );
	//void						slotMuteSpeakerButtonClicked( bool muteSpeaker );
	void						onAboutToDestroyDialog( void ); 
	void						slotToGuiRxedOfferReply( GuiOfferSession * offerSession );
	void						slotToGuiSessionEnded( GuiOfferSession * offerSession );
	void						slotToGuiContactOffline( VxNetIdent * hisIdent );

protected:
	virtual void				showEvent( QShowEvent * ev );
	virtual void				hideEvent( QHideEvent * ev );
	virtual void				closeEvent( QCloseEvent * ev );

	void						setupActivityWebCamClient();
	void						resizeBitmapToFitScreen( QLabel * VideoScreen, QImage& oPicBitmap );
	void						setMuteSpeakerVisibility( bool visible );
	void						setMuteMicrophoneVisibility( bool visible );
	void						setCameraButtonVisibility( bool visible );

	//=== vars ===//
	Ui::WebCamClientDlgClass	ui;
	bool						m_bIsMyself;
};

