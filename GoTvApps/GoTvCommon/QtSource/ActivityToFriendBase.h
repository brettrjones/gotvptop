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

#include "ActivityBase.h"
#include "ui_ActivityToFriendBase.h"

#include <PktLib/VxCommon.h>

class GuiOfferSession;
class VidWidget;
class VxLabel;
class TitleBarWidget;
class VxPushButton;

class ActivityToFriendBase : public ActivityBase
{
	Q_OBJECT

public:
	ActivityToFriendBase(	const char *			objName,
							AppCommon&				app,
							EPluginType				ePluginType,
							VxNetIdent *			netIdent, 
							QWidget *				parent	= NULL,
                            EApplet                 eAppletType = eAppletMessenger, 
							Qt::WindowFlags			flags	= 0 );

	ActivityToFriendBase(	const char *			objName,
							AppCommon&				app,
							EPluginType				ePluginType,
							GuiOfferSession *		poOffer, 
							QWidget *				parent	= NULL,
                            EApplet                 eAppletType = eAppletMessenger,
							Qt::WindowFlags			flags	= 0 );

	virtual ~ActivityToFriendBase();

	void						setupBaseWidgets(	TitleBarWidget *	titleBarWidget, 
													IdentWidget *		friendIdentWidget = 0, 
													VxPushButton *		permissionButton = 0, 
													QLabel *			permissionLabel = 0 );
	void						setupTitleBarWidget( TitleBarWidget * titleBarWidget );

	void						enableAudioControls( bool enable );
	void						enableVideoControls( bool enable );

	void						setVidCamWidget( VidWidget * camWidget )			{ m_VidCamWidget = camWidget; }
	VidWidget *					getVidCamWidget( void )								{ return m_VidCamWidget; }

	virtual bool				fromGuiSetGameValueVar(	int32_t varId, int32_t varValue );
	virtual bool				fromGuiSetGameActionVar( int32_t actionId, int32_t actionValue );

	virtual void				onActivityFinish( void );

signals:
	void						signalToGuiSetGameValueVar( long varId, long varValue );
	void						signalToGuiSetGameActionVar( long actionId, long actionValue );
	void						signalToGuiRxedPluginOffer( GuiOfferSession * offerSession );
	void						signalToGuiRxedOfferReply( GuiOfferSession * offerSession );
	void						signalToGuiPluginSessionEnded( GuiOfferSession * offerSession );
	void						signalToGuiContactOnline( VxNetIdent * hisIdent, bool newContact );
	void						signalToGuiContactOffline( VxNetIdent * hisIdent );

public slots:
	void						slotMuteMicButtonClicked( bool muteMic );
	void						slotMuteSpeakerButtonClicked( bool muteSpeaker );
	void						slotCameraSnapshotButtonClicked( bool enableEchoCancel );
	void						slotCamPreviewClicked( void );

protected slots:
	void						slotToGuiRxedPluginOffer( GuiOfferSession * offerSession );
	void						slotToGuiRxedOfferReply( GuiOfferSession * offerSession );
	void						slotToGuiPluginSessionEnded( GuiOfferSession * offerSession );
	void						slotToGuiContactOffline( VxNetIdent * hisIdent );

private:
	void						setupActivityToFriendBase( void );

protected:
	virtual void				toGuiRxedPluginOffer( void * callbackData, GuiOfferSession * offer ); 
	virtual void				toGuiRxedOfferReply( void * callbackData, GuiOfferSession * offerReply ); 
	virtual void				toGuiPluginSessionEnded(void * callbackData, GuiOfferSession * offer ); 
	virtual void				toGuiContactOnline( void * callbackData, VxNetIdent * friendIdent, bool newContact ); 
	virtual void				toGuiContactOffline( void * callbackData, VxNetIdent * friendIdent ); 
	virtual void				toGuiClientPlayVideoFrame(	void *			userData, 
															VxGUID&			onlineId, 
															uint8_t *			pu8Jpg, 
															uint32_t				u32JpgDataLen,
															int				motion0To100000 );

	virtual void				toGuiSetGameValueVar(	void *		userData, 
														EPluginType ePluginType, 
														VxGUID&		onlineId, 
														int32_t			s32VarId, 
														int32_t			s32VarValue );

	virtual void				toGuiSetGameActionVar(	void *		userData, 
														EPluginType ePluginType, 
														VxGUID&		onlineId, 
														int32_t			s32VarId, 
														int32_t			s32VarValue );

	virtual void				showEvent( QShowEvent * ev );
	virtual void				hideEvent( QHideEvent * ev );
	virtual void				closeEvent( QCloseEvent * ev );

	QString						describePluginOffer( EPluginType ePluginType );


	//=== vars ===//
	bool						m_bFirstMsg;
	VidWidget *					m_VidCamWidget;
	TitleBarWidget *			m_TitleBarWidget;
	OfferSessionLogic			m_OfferSessionLogic;

};
