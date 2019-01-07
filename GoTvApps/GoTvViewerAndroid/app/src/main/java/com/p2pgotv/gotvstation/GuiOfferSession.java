//============================================================================
// Copyright (C) 2016 Brett R. Jones 
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason 
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================
package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.List;

public class GuiOfferSession 
{

	//=== vars ===//
	public int					m_ePluginType 		= 0;
	public VxNetIdent			m_HisIdent 			= null;
	public int					m_pvUserData 		= 0;
	public boolean				m_bRmtInitiated 	= false;
	public boolean				m_bHasBeenViewed 	= false;
	public int					m_iProgress 		= 0;
	public boolean				m_bRequiresReply 	= false;
	public String				m_strMsg			= "";
	public String				m_strFileName		= "";
	public byte[] 				m_FileHash			= null;
	public boolean				m_IsSessionEnded	= false;
	public int					m_eOfferResponse 	= 0;
	public int					m_MissedCallCount 	= 0;
	private VxGUID				m_LclSessionId 		= null;
	private VxGUID				m_RmtSessionId 		= null;
	private VxGUID				m_OfferSessionId 	= null;
	private EOfferState			m_EOfferState		= EOfferState.eOfferStateUnknown;
	
	List<String> 				m_aoQuedMessages = new ArrayList<String>();
	
	GuiOfferSession()
	{
	}
	
	void			setPluginType( int ePluginType ) 					{ m_ePluginType = ePluginType; }
	int 			getPluginType()										{ return m_ePluginType; }
	void			setIsRemoteInitiated( boolean bIsRemoteInitiated ) 	{ m_bRmtInitiated = bIsRemoteInitiated; }
	boolean			isRemoteInititated()								{ return m_bRmtInitiated; }
	void			setHisIdent( VxNetIdent netIdent ) 					{ m_HisIdent = netIdent; }
	VxNetIdent		getHisIdent()										{ return m_HisIdent; }
	void			setProgress( int iProgress )						{ m_iProgress = iProgress; }
	int				getProgress()										{ return m_iProgress; }
	void			setHasBeenViewed( boolean bHasBeenViewed ) 			{ m_bHasBeenViewed = bHasBeenViewed; }
	boolean			hasBeenViewed()										{ return m_bHasBeenViewed; }
	void			setRequiresReply( boolean bRequiresReply ) 			{ m_bRequiresReply = bRequiresReply; }
	boolean			requiresReply()										{ return m_bRequiresReply; }
	boolean			hasNewResponse()									{ return m_bRequiresReply; }
	void			setHasNewResponse( boolean bNewResponse ) 			{ m_bRequiresReply = bNewResponse; }
	void			setOfferResponse( int eOfferResponse ) 				{ m_eOfferResponse = eOfferResponse; m_IsSessionEnded = isOfferAccepted(); }
	int				getOfferResponse()									{ return m_eOfferResponse; }
	boolean			isOfferAccepted()									{ return (m_eOfferResponse == Constants.eOfferResponseAccept); }
	boolean			isOfferRejected()									{ return (m_eOfferResponse == Constants.eOfferResponseReject)||(m_eOfferResponse == Constants.eOfferResponseEndSession); }	
	void			incMissedCallCount()								{ m_MissedCallCount++; }
	void			setMissedCallCount( int missedCnt )					{ m_MissedCallCount = missedCnt; }
	int				getMissedCallCount()								{ return m_MissedCallCount; }
	void 			setIsSessionEnded( boolean isEnded )				{ m_IsSessionEnded = isEnded; }
	boolean			getIsSessionEnded()									{ return m_IsSessionEnded; }
	void 			setLclSessionId( VxGUID sessionId )					{ m_LclSessionId = sessionId; }
	VxGUID			getLclSessionId()									{ return m_LclSessionId; }
	void 			setRmtSessionId( VxGUID sessionId )					{ m_RmtSessionId = sessionId; }
	VxGUID			getRmtSessionId()									{ return m_RmtSessionId; }
	VxGUID			getOfferSessionId()									{ return m_OfferSessionId; }
	int				getUserData()										{ return m_pvUserData; }
	
	void 			setOfferState( EOfferState eOfferState )			{ m_EOfferState = eOfferState; }
	EOfferState		getOfferState()										{ return m_EOfferState; }

	//======================================================================== 
	public VxGUID   assuredValidLclSessionId() 
	{
      	if( null == m_LclSessionId )
      	{
      		m_LclSessionId = new VxGUID();
      		m_LclSessionId.initializeWithNewGUID();
      	}
      	else if( false == m_LclSessionId.isOnlineIdValid() )
      	{
      		m_LclSessionId.initializeWithNewGUID();
      	}
      	
      	if( GuiHelpers.isPluginSingleSession( m_ePluginType ) )
      	{
      		m_OfferSessionId = m_HisIdent.getMyOnlineId();
      	}
      	else
      	{
      		m_OfferSessionId = m_LclSessionId;
      	}

      	return m_LclSessionId;
	}
	
	//======================================================================== 
	boolean			isAvailableAndActiveOffer()
	{
		boolean isActive = false;
		if( ( false == m_IsSessionEnded )
			&& ( null != m_HisIdent )
			&& ( m_HisIdent.isOnline() ) )
		{
			isActive = true;
		}
		
		return isActive;
	}

	//======================================================================== 
	void addMsg( String strMsg )
	{
		m_aoQuedMessages.add( strMsg );
	}

	//======================================================================== 
	public String getOfferMsg() 
	{
		String offerMsg = "";
		if( m_strFileName.length() > 0 )
		{
			offerMsg = "File: " + m_strFileName;
		}
		else
		{
			offerMsg = m_strMsg;
		}

		return offerMsg;
	}
	
	//========================================================================
	String 			describePlugin()
	{
		return GuiHelpers.describePlugin( getPluginType(), m_bRmtInitiated );	
	}
	
	//========================================================================
	String 			describeOffer()
	{
		return m_HisIdent.getOnlineName() + " Offers " + GuiHelpers.describePlugin( getPluginType(), m_bRmtInitiated );	
	}
	
	//========================================================================
	String 			getOnlineName()
	{
		return m_HisIdent.getOnlineName();	
	}

};
