#pragma once
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
// bjones.engineer@gmail.com
// http://www.nolimitconnect.com
//============================================================================


enum ECallState
{
	eCallStateInvalid = 0,
	eCallStateWaiting = 1,
	eCallStateCalling = 2,
	eCallStateInCall = 3,
	eCallStateHangedUp = 4,

	eMaxCallState
};

enum ESessionState
{ 
	eSessionStateUnknown					= 0,
	eSessionStateWaitingResponse			= 1,
	eSessionStateRejected					= 2,
	eSessionStateInSession					= 3,
	eSessionStateSessionEnded				= 4,
	eSessionContactOffline					= 5,
	eSessionUserExitedSession				= 6,

	eMaxSessionState
};

#include <PktLib/VxCommon.h>
#include <CoreLib/VxSha1Hash.h>

#include <string>

class ActivityBase;
class OffersMgr;
class OfferSessionCallbackInterface;
class AppCommon;
class VxNetIdent;
class GuiOfferSession;

class OfferSessionLogic
{
public:	
	OfferSessionLogic(	ActivityBase * activity,  
						OfferSessionCallbackInterface * callbackInterface, 
						AppCommon&	myApp, 
						EPluginType		ePluginType, 
						VxNetIdent *	hisIdent, 
						GuiOfferSession * offerSession );
	
	bool 						isSessionOffer( void )							{ return m_IsOffer; }
	bool 						isRmtInitiated( void )							{ return m_IsOffer; }
	void 						setIsServerSession( bool isServerSession )		{ m_IsServerSession = isServerSession; }
	bool 						getIsServerSession( void )						{ return m_IsServerSession; }
	void 						setIsInSession( bool isInSession )				{ m_IsInSession = isInSession; }
	bool 						getIsInSession()								{ return m_IsInSession; }
	bool 						getIsMyself( void )								{ return m_IsMyself; }
	void 						setOfferText( std::string strOfferText )		{ m_strOfferText = strOfferText; }
	std::string 				getOfferText( void )							{ return m_strOfferText; }
	void 						setOfferFileName( std::string strOfferFileName ){ m_strOfferFileName = strOfferFileName; }
	std::string 				getOfferFileName()								{ return m_strOfferFileName; }
	void 						setUserData( int userData )						{ m_UserData = userData; }
	int 						getUserData( void )								{ return m_UserData; }
    VxGUID& 					getLclSessionId( void )							{ return m_LclSessionId;    }
	VxGUID& 					getOfferSessionId( void )						{ return m_OfferSessionId;    }
	EPluginType 				getPluginType( void )							{ return m_ePluginType;    }
	VxNetIdent * 				getHisIdent( void )								{ return m_HisIdent;    }

	bool						isOurSessionType( GuiOfferSession * offerSession ); 
	bool						isOurSessionInstance( GuiOfferSession * offerSession ); 

	void						onInSession( bool isInSession ); 

	void						doToGuiRxedPluginOffer( GuiOfferSession * offerSession ); 
	void						doToGuiRxedOfferReply( GuiOfferSession * offerSession );

	void						toGuiPluginSessionEnded( GuiOfferSession * offerSession ); 
	void						toGuiContactOffline( VxNetIdent * friendIdent ); 

	bool						sendOfferOrResponse();
	bool						sendOfferReply( EOfferResponse offerResponse );

	void						onStop();
 
	bool						startPluginSessionIfIsSessionOffer();
 
	void						setCallState( int eCallState );

	std::string					getHisOnlineName( void );
	std::string					describePlugin( void );
	std::string					describeResponse( EOfferResponse eOfferResponse );
	void						postStatusMsg( const char * statusMsg, ... );
	void						postUserMsg( const char * userMsg, ... );

	bool						handleOfferResponse( GuiOfferSession  poSession );
	bool						handleOfferResponseCode( EOfferResponse responseCode ) ;
	void						handleSessionEnded( GuiOfferSession * offerSession );
	void						handleSessionEnded( EOfferResponse responseCode );
	void						handleUserWentOffline( void );
	void						startPhoneRinging( void );
	void						stopPhoneRinging( void );
	void						showOfflineMsg( bool bExitWhenClicked = true );
	//void						errMsgBox( bool bExitWhenClicked, std::string strMsg );

private:
	AppCommon& 				m_MyApp;
    OffersMgr& 					m_OffersMgr;
    ActivityBase *				m_Activity;
	OfferSessionCallbackInterface * m_OfferCallback;
	EPluginType					m_ePluginType;	
	VxNetIdent * 				m_HisIdent;
	VxNetIdent * 				m_MyIdent;
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	VxGUID						m_OfferSessionId;
	VxSha1Hash					m_FileHashId;
	GuiOfferSession *			m_GuiOfferSession;
	bool 						m_IsOffer;
	bool 						m_IsMyself;
	bool 						m_IsServerSession;
	bool 						m_IsPluginSingleSession;
	std::string 				m_strOfferText;
	std::string 				m_strOfferFileName;
	int							m_UserData;	
	bool 						m_SessionEndIsHandled;
	bool 						m_IsInSession;
	bool 						m_IsOnStopCalled;
};





