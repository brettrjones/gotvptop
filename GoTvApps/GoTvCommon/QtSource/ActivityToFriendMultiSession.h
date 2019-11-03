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

#include "ActivityToFriendBase.h"
#include "ui_ActivityToFriendMultiSession.h"
#include "MultiSessionState.h"
#include "TodGameLogic.h"

class P2PEngine;
class GuiOfferSession;
class EngineSettings;
class MultiSessionState;

class ActivityToFriendMultiSession : public ActivityToFriendBase
{
	Q_OBJECT
public:
	ActivityToFriendMultiSession(	AppCommon&			app,
									VxNetIdent *			netIdent, 
									QWidget *				parent = NULL );

	ActivityToFriendMultiSession(	AppCommon&			app,
									GuiOfferSession *		poOffer, 
									QWidget *				parent = NULL );
	virtual ~ActivityToFriendMultiSession() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

	virtual void				toGuiClientPlayVideoFrame(	void *			userData, 
															VxGUID&			onlineId, 
															uint8_t *			pu8Jpg, 
															uint32_t				u32JpgDataLen,
															int				motion0To100000 );
	virtual void				toGuiMultiSessionAction( void * callbackData, EMSessionAction mSessionAction, VxGUID& onlineId, int pos0to100000 );

	virtual void				onActivityFinish( void );

signals:
	void						signalToGuiMultiSessionAction( VxGuidQt onlineId, EMSessionAction mSessionAction, int pos );

protected slots:
	void						slotToGuiMultiSessionAction( VxGuidQt onlineId, EMSessionAction mSessionAction, int pos );
	void						slotToGuiPluginSessionEnded(GuiOfferSession * offerSession );
	void						slotToGuiContactOnlineMultisession( VxNetIdent * hisIdent, bool newContact );
	void						slotToGuiContactOfflineMultisession( VxNetIdent * hisIdent );

	void						slotUserInputButtonClicked( void );

protected:
	virtual void				showEvent( QShowEvent * ev );
	virtual void				hideEvent( QHideEvent * ev );

	// override of ToGuiActivityInterface
	virtual void				doToGuiRxedPluginOffer( void * callbackData, GuiOfferSession * offer );
	virtual void				doToGuiRxedOfferReply( void * callbackData, GuiOfferSession * offer );

	virtual bool 				checkForSendAccess( bool sendOfferIfPossible );
	virtual void				showReasonAccessNotAllowed( void );

	virtual void 				onSessionStateChange( ESessionState eSessionState );	
	// called from session logic
	virtual void				onInSession( bool isInSession );

	void						setupMultiSessionActivity(  VxNetIdent * hisIdent );
	void						setStatusMsg( QString strStatus );

	void						toGuiSetGameValueVar(	void *		userData, 
														EPluginType ePluginType, 
														VxGUID&		onlineId, 
														int32_t			s32VarId, 
														int32_t			s32VarValue );

	void						toGuiSetGameActionVar(	void *		userData, 
														EPluginType ePluginType, 
														VxGUID&		onlineId, 
														int32_t			s32VarId, 
														int32_t			s32VarValue );
	void						setup( void );
	//virtual bool				handleOfferResponse( EOfferResponse offerResponse, QWidget * parent );
    //void						onInSessionResponse( bool bResponseOk );

	MultiSessionState *			getMSessionState( EMSessionType sessionType );

	//=== vars ===//
	Ui::ToFriendMultiSessionDialog	ui;
	QFrame *					m_OffersFrame;
	QFrame *					m_ResponseFrame;
	QFrame *					m_HangupSessionFrame;
	TodGameWidget *				m_TodGameWidget;
	VidWidget *					m_VidChatWidget;
	TodGameLogic				m_TodGameLogic;
	QVector<MultiSessionState*> m_MSessionsList;
	bool						m_IsInitialized;
	bool						m_OfferOrResponseIsSent;
	bool						m_CanSend;
};

