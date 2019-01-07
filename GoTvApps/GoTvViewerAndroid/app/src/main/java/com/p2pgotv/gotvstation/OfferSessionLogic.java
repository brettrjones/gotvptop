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

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.util.Log;
import android.widget.Toast;

public class OfferSessionLogic
{
	
	class ECallState
	{
		static public final int eCallStateInvalid = 0;
		static public final int eCallStateWaiting = 1;
		static public final int eCallStateCalling = 2;
		static public final int eCallStateInCall = 3;
		static public final int eCallStateHangedUp = 4;
	};

	/*
	static public final int eSessionStateUnknown					= 0;
	static public final int eSessionStateWaitingResponse			= 1;
	static public final int eSessionStateRejected					= 2;
	static public final int eSessionStateInSession					= 3;
	static public final int eSessionStateSessionEnded				= 4;
	static public final int eSessionContactOffline					= 5;
	static public final int eSessionUserExitedSession				= 6;
*/
	private static final String LOG_TAG 				= "OfferSessionLogic:";
	
	private MyApp 				m_MyApp 				= null;
	private Activity			m_Activity 				= null;
	private OfferSessionCallbackInterface m_OfferCallback = null;
	private int					m_ePluginType 			= Constants.ePluginTypeInvalid;	
	private VxNetIdent 			m_HisIdent 				= null;
	private VxNetIdent 			m_MyIdent 				= null;
	private VxGUID				m_LclSessionId			= new VxGUID();
	//private GuidId			m_RmtSessionId			= null;
	private VxGUID				m_OfferSessionId		= new VxGUID();
	private GuiOfferSession		m_GuiOfferSession 		= null;
	private VxSha1Hash			m_FileHashId			= new VxSha1Hash();

	private boolean 			m_IsOffer 				= false;
	private boolean 			m_IsMyself 				= false;
	private boolean 			m_IsServerSession 		= false;
    private String 				m_strOfferText			= "";
    private String 				m_strOfferFileName		= "";
    private int					m_iUserData 			= 0;	
    private boolean 			m_SessionEndIsHandled	= false;
    private boolean 			m_IsInSession 			= false;
    private OffersMgr 			m_OffersMgr 			= null;


	//======================================================================== 
	OfferSessionLogic( Activity activity,  OfferSessionCallbackInterface callbackInterface, MyApp myApp, int ePluginType, VxNetIdent hisIdent, GuiOfferSession offerSession )
	{
		m_Activity 					= activity;
		m_MyApp						= myApp;
		m_OffersMgr					= m_MyApp.getOffersMgr();
		m_OfferCallback 			= callbackInterface;
		m_MyIdent					= m_MyApp.getMyIdentity();
		m_ePluginType 				= ePluginType;	
		m_HisIdent 					= hisIdent;
		m_GuiOfferSession 			= offerSession;
		VxGUID myOnlineId 			= m_MyIdent.getMyOnlineId();
		VxGUID hisOnlineId 			= m_HisIdent.getOnlineId() ;
		
		m_IsMyself 					= ( 0 == myOnlineId.compareTo( hisOnlineId ) ) ? true : false;
		if( null != m_GuiOfferSession )
		{
			m_IsOffer = true;
			m_LclSessionId		= m_GuiOfferSession.assuredValidLclSessionId();
			m_OfferSessionId	= m_GuiOfferSession.getOfferSessionId();
		}
		else
		{
			m_IsOffer = false;
			m_GuiOfferSession = new GuiOfferSession();
			m_GuiOfferSession.setPluginType( ePluginType );
			m_GuiOfferSession.setHisIdent( m_HisIdent );
			m_GuiOfferSession.setIsRemoteInitiated( false );			
			m_LclSessionId			= m_GuiOfferSession.assuredValidLclSessionId();
			m_OfferSessionId		= m_GuiOfferSession.getOfferSessionId();
		}
		
		m_iUserData 				= m_GuiOfferSession.getUserData();
		m_FileHashId.setHashData( m_GuiOfferSession.m_FileHash );
	}
	
	public boolean 				isSessionOffer()								{ return m_IsOffer; }
	public void 				setIsServerSession( boolean isServerSession )	{ m_IsServerSession = isServerSession; }
	public boolean 				getIsServerSession()							{ return m_IsServerSession; }
	public void 				setIsInSession( boolean isInSession )			{ m_IsInSession = isInSession; }
	public boolean 				getIsInSession()								{ return m_IsInSession; }
	public boolean 				getIsMyself()									{ return m_IsMyself; }
	public void 				setOfferText( String strOfferText )				{ m_strOfferText = strOfferText; }
	public String 				getOfferText()									{ return m_strOfferText; }
	public void 				setOfferFileName( String strOfferFileName )		{ m_strOfferFileName = strOfferFileName; }
	public String 				getOfferFileName()								{ return m_strOfferFileName; }
	public void 				setUserData( int iUserData )					{ m_iUserData = iUserData; }
	public int 					getUserData()									{ return m_iUserData; }
    public VxGUID 				getLclSessionId()								{ return m_LclSessionId;    }
    public VxGUID 				getOfferSessionId()								{ return m_OfferSessionId;    }

  //============================================================================
    private String getHisOnlineName()
    {
    	return m_HisIdent.getOnlineName();
    }

    //============================================================================
    private String describePlugin()
    {
    	return GuiHelpers.describePlugin( m_ePluginType, m_IsOffer );
    }

    //============================================================================
    private void postStatusMsg( String statusMsg )
    {
    	if( null != statusMsg )
    	{
    		NativeRxFrom.toGuiStatusMessage( statusMsg );
    	}
    }
	
	//======================================================================== 
    private boolean isOurSessionType( GuiOfferSession offerSession )
	{
		if( ( offerSession.m_ePluginType == m_ePluginType )
				&& ( null != m_HisIdent ) )
		{
				return true;
		}
		
		return false;
	}

	//======================================================================== 
	public boolean isOurSessionInstance( GuiOfferSession offerSession )
	{
		if( isOurSessionType( offerSession ) )
		{
			if( GuiHelpers.isPluginSingleSession( offerSession.getPluginType() ) )
			{
				if(  offerSession.getHisIdent().getMyOnlineId().equals( m_HisIdent.getMyOnlineId() ) )
				{
					return true;
				}				
			}
			else if(  offerSession.getOfferSessionId().equals( m_OfferSessionId ) )
			{
				return true;
			}
		}
		
		return false;
	}
	
	//======================================================================== 
	public void onInSession( boolean isInSession )
	{
		String sessionMsg = isInSession ? "In " : "Ended ";
		postStatusMsg( sessionMsg + describePlugin() + " Session" );
		if( isInSession )
		{
			m_SessionEndIsHandled = false;
		}

		m_OfferCallback.onInSession( isInSession );
		m_OffersMgr.onIsInSession( m_ePluginType, m_LclSessionId, m_HisIdent, isInSession );
	}
	
	//======================================================================== 
	public void toGuiRxedPluginOffer( GuiOfferSession offerSessionIn ) 
	{
		if( isOurSessionType( offerSessionIn ) )
		{		
			final GuiOfferSession offerSession = offerSessionIn;	
			try 
			{
				m_Activity.runOnUiThread(new Runnable() 
				{	
					@Override
					public void run() 
					{
						if( GuiHelpers.isPluginSingleSession( m_ePluginType )  )
						{
							// special case for multisession. and other single session use online id instead of session id and auto accept
							if( offerSession.getHisIdent().getMyOnlineId().equals( m_HisIdent.getMyOnlineId() ) )
							{
								// already in session with this user
								// use new session id if valid
								if( true == offerSession.getOfferSessionId().isOnlineIdValid() )
								{
									m_OfferSessionId = offerSession.getOfferSessionId();
								}
								
								m_OffersMgr.removeOfferByOnlineId( m_ePluginType, m_HisIdent.getMyOnlineId() );
								NativeTxTo.fromGuiToPluginOfferReply( 	m_ePluginType, m_HisIdent.m_u64IdHiPart, m_HisIdent.m_u64IdLoPart, 0, Constants.eOfferResponseAccept,
										m_OfferSessionId.m_u64IdHiPart, m_OfferSessionId.m_u64IdLoPart );
								if( !m_IsInSession )
								{
									m_IsInSession = true;
									NativeTxTo.fromGuiStartPluginSession( 	m_ePluginType, 
																			m_HisIdent.m_u64IdHiPart, 
																			m_HisIdent.m_u64IdLoPart, 
																			m_OfferSessionId.m_u64IdHiPart, 
																			m_OfferSessionId.m_u64IdLoPart, 0 );
									onInSession( true );
								}
							}
							else
							{
								// already in session with someone else
								if( null == offerSession.getLclSessionId() )
								{
									NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
																			offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart, 
																			0, 
																			Constants.eOfferResponseBusy,
																			0, 0 );	
									
									m_OffersMgr.sentOfferReply( m_ePluginType, null, offerSession.getHisIdent(), Constants.eOfferResponseBusy );
								}
								else if( false == offerSession.getLclSessionId().isOnlineIdValid() )
								{
									NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
											offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart, 
											0, 
											Constants.eOfferResponseBusy,
											offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart );									
											m_OffersMgr.sentOfferReply( m_ePluginType, offerSession.getHisIdent().getMyOnlineId(), offerSession.getHisIdent(), Constants.eOfferResponseBusy );					
								
								}
								else
								{
									NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
																			offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart, 
																			0, 
																			Constants.eOfferResponseBusy,
																			offerSession.getLclSessionId().m_u64IdHiPart, 
																			offerSession.getLclSessionId().m_u64IdLoPart );									
									m_OffersMgr.sentOfferReply( m_ePluginType, offerSession.getOfferSessionId(), offerSession.getHisIdent(), Constants.eOfferResponseBusy );					
								}
							}						
						}
						else
						{
											
							if( offerSession.getOfferSessionId().equals( m_OfferSessionId ) )
							{
								// already in session with this user
								NativeTxTo.fromGuiToPluginOfferReply( 	m_ePluginType, m_HisIdent.m_u64IdHiPart, m_HisIdent.m_u64IdLoPart, 0, Constants.eOfferResponseAccept,
										m_OfferSessionId.m_u64IdHiPart, m_OfferSessionId.m_u64IdLoPart );
								if( !m_IsInSession )
								{
									m_IsInSession = true;
									NativeTxTo.fromGuiStartPluginSession( 	m_ePluginType, 
																			m_HisIdent.m_u64IdHiPart, 
																			m_HisIdent.m_u64IdLoPart, 
																			m_OfferSessionId.m_u64IdHiPart, 
																			m_OfferSessionId.m_u64IdLoPart, 0 );
									onInSession( true );
								}
							}
							else
							{
								// already in session with someone else
								if( null == offerSession.getLclSessionId() )
								{
									NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
																			offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart, 
																			0, 
																			Constants.eOfferResponseBusy,
																			0, 0 );	
									
									m_OffersMgr.sentOfferReply( m_ePluginType, null, offerSession.getHisIdent(), Constants.eOfferResponseBusy );
								}
								else if( false == offerSession.getLclSessionId().isOnlineIdValid() )
								{
									NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
											offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart, 
											0, 
											Constants.eOfferResponseBusy,
											offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart );									
											m_OffersMgr.sentOfferReply( m_ePluginType, offerSession.getHisIdent().getMyOnlineId(), offerSession.getHisIdent(), Constants.eOfferResponseBusy );					
								
								}
								else
								{
									NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
																			offerSession.getHisIdent().m_u64IdHiPart, offerSession.getHisIdent().m_u64IdLoPart, 
																			0, 
																			Constants.eOfferResponseBusy,
																			offerSession.getLclSessionId().m_u64IdHiPart, 
																			offerSession.getLclSessionId().m_u64IdLoPart );									
									m_OffersMgr.sentOfferReply( m_ePluginType, offerSession.getOfferSessionId(), offerSession.getHisIdent(), Constants.eOfferResponseBusy );					
								}
							}
						} // end if multissesion
					}// end run
				});
			}
			catch (Exception e) 
			{
				e.printStackTrace();
			}// end try
		}// end if
	}// end function

	//======================================================================== 
	public void toGuiRxedOfferReply( GuiOfferSession offerSession ) 
	{
		if( isOurSessionInstance( offerSession ) )
		{
			final int offerResponse 		= offerSession.m_eOfferResponse;			
			offerSession.assuredValidLclSessionId();			
			final VxGUID offerSessionId 	= offerSession.getOfferSessionId();			
			try 
			{
				m_Activity.runOnUiThread(new Runnable() 
				{	
					@Override
					public void run() 
					{
						if( Constants.eOfferResponseAccept == offerResponse )
						{
							if( !m_IsInSession )
							{
								m_IsInSession = true;
								NativeTxTo.fromGuiStartPluginSession( m_ePluginType, m_HisIdent.m_u64IdHiPart, m_HisIdent.m_u64IdLoPart, 
										offerSessionId.m_u64IdHiPart, offerSessionId.m_u64IdLoPart, 0 );
								m_OffersMgr.startedSessionInReply( m_ePluginType, offerSessionId, m_HisIdent );
								onInSession( true );
							}
						}
						else 
						{
							handleSessionEnded( offerResponse );
						}
					}
				});
			} 
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	}

	//======================================================================== 
	public void toGuiPluginSessionEnded( GuiOfferSession offerSession ) 
	{
		if( isOurSessionInstance( offerSession ) )
		{
			final int offerResponse = offerSession.m_eOfferResponse;	
			try 
			{
				m_Activity.runOnUiThread(new Runnable() 
				{	
					@Override
					public void run() 
					{
						m_OffersMgr.recievedSessionEnd( m_ePluginType, m_OfferSessionId, m_HisIdent, offerResponse );
						handleSessionEnded( offerResponse );
					}
				});
			} 
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	}
	
	//============================================================================
	public void toGuiContactOnline( VxNetIdent hisIdent, boolean newContact ) 
	{
		if( ( null != m_HisIdent ) 
			&& ( null != hisIdent ) 
			&& hisIdent.getOnlineId().equals( m_HisIdent.getOnlineId() ) )
		{
			try 
			{
				m_Activity.runOnUiThread(new Runnable() 
				{	
					@Override
					public void run() 
					{	
						m_HisIdent.setIsOnline( true );
						NativeRxFrom.toGuiStatusMessage( m_HisIdent.getOnlineName() + " is now online" );
						m_OfferCallback.onContactOnline();
					}
				});
			} 
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}	
	}

	//======================================================================== 
	public void toGuiContactOffline( VxNetIdent hisIdent ) 
	{
		if( ( null != m_HisIdent )
			&& ( null != hisIdent ) 	
			&& hisIdent.getOnlineId().equals( m_HisIdent.getOnlineId() ) )
		{
			try 
			{
				m_Activity.runOnUiThread(new Runnable() 
				{	
					@Override
					public void run() 
					{	
						m_HisIdent.setIsOnline( false );
						NativeRxFrom.toGuiStatusMessage( m_HisIdent.getOnlineName() + " is now offline" );
						m_OffersMgr.contactWentOffline( m_HisIdent );
						handleSessionEnded( Constants.eOfferResponseUserOffline );
					}
				});
			} 
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	}

	//========================================================================
	public boolean sendOfferOrResponse()
	{
		if( getIsServerSession() )
		{
			return true;
		}
		
		boolean sentOk = true;
	    if( m_IsOffer )
	    {
	    	Log.d( LOG_TAG, "Sending Accept to " + m_HisIdent.getOnlineName() );
			if (false == NativeTxTo.fromGuiToPluginOfferReply(	m_ePluginType, 
												        		m_HisIdent.m_u64IdHiPart,
												        		m_HisIdent.m_u64IdLoPart, 
												        		getUserData(), 
												        		Constants.eOfferResponseAccept,
												        		m_OfferSessionId.m_u64IdHiPart, 
												        		m_OfferSessionId.m_u64IdLoPart ) )
			{
				showOfflineMsg();
				sentOk = false;
			} 
			else
			{
				startPluginSessionIfIsSessionOffer();
			}
	    }
	    else
	    {
			if (false == NativeTxTo.fromGuiMakePluginOffer(	m_ePluginType, 
											        		m_HisIdent.m_u64IdHiPart,
											        		m_HisIdent.m_u64IdLoPart, 
											        		getUserData(), 
											        		getOfferText(), 
											        		getOfferFileName(),
											        		m_OfferSessionId.m_u64IdHiPart,
											        		m_OfferSessionId.m_u64IdLoPart ) )
			{
				showOfflineMsg();
				sentOk = false;
			}
			else
			{
	    		m_OffersMgr.sentOffer( m_ePluginType, m_OfferSessionId, m_HisIdent );
	    		postStatusMsg( "Waiting Reply Offer " + describePlugin() + " From " + getHisOnlineName() );
			}
	    }
	    
	    return sentOk;
	}

	//============================================================================  
	void onStop()
	{
		if( Constants.ePluginTypeRelay == m_ePluginType )
		{
			return;
		}
		
		m_OffersMgr.onSessionExit( m_ePluginType, m_LclSessionId, m_HisIdent );
	 	if( false == getIsServerSession() )
		{
			setCallState( ECallState.eCallStateHangedUp );
			if( false == m_SessionEndIsHandled )
	 		{
				m_SessionEndIsHandled = true;
				onInSession( false );
			    if( null != m_HisIdent )
		        {
			   			NativeTxTo.fromGuiToPluginOfferReply( 	m_ePluginType, 
															m_HisIdent.m_u64IdHiPart, 
															m_HisIdent.m_u64IdLoPart, 
															0, 
															Constants.eOfferResponseEndSession, 
															m_OfferSessionId.m_u64IdHiPart,
															m_OfferSessionId.m_u64IdLoPart );
			    		m_OffersMgr.sentOfferReply( m_ePluginType, m_OfferSessionId, m_HisIdent, Constants.eOfferResponseEndSession );
		        }
	 		}
	
		    if( null != m_HisIdent )
	        {
	    		NativeTxTo.fromGuiStopPluginSession( 	m_ePluginType, 
														m_HisIdent.m_u64IdHiPart, 
														m_HisIdent.m_u64IdLoPart,
														m_OfferSessionId.m_u64IdHiPart,
														m_OfferSessionId.m_u64IdLoPart, 
														0 );		    	
	        }
		}
	 	
   		NativeTxTo.fromGuiMuteSpeaker( false );
	}
	
	//============================================================================  
	boolean startPluginSessionIfIsSessionOffer()
	{
        if( isSessionOffer() )
        {
    		setIsInSession( true );
    		NativeTxTo.fromGuiStartPluginSession( 		m_ePluginType, m_HisIdent.m_u64IdHiPart, m_HisIdent.m_u64IdLoPart, 
									    				m_OfferSessionId.m_u64IdHiPart,
									    				m_OfferSessionId.m_u64IdLoPart, 
									    				0 );
    		m_OffersMgr.startedSessionInReply( m_ePluginType, m_OfferSessionId, m_HisIdent );
  			onInSession( true );
       		return true;
        }
        
        return false;
	}
	
	//============================================================================  
	void setCallState( int eCallState )
	{
		switch( eCallState )
		{
		case ECallState.eCallStateCalling:
			startPhoneRinging();
			break;
			
		case ECallState.eCallStateInCall:
			break;
	
		case ECallState.eCallStateHangedUp:
			stopPhoneRinging();
			break;
	
		default:
			break;
		}
	}

	//========================================================================
	boolean handleOfferResponse( GuiOfferSession  poSession )
	{
		boolean bResponesOk = false;
		if( ( poSession.m_ePluginType == m_ePluginType ) &&
			( poSession.getHisIdent().getMyOnlineId() == m_HisIdent.getMyOnlineId() )) 
		{
			stopPhoneRinging();
			bResponesOk = handleOfferResponseCode( poSession.getOfferResponse()  );
		}
		
		return bResponesOk;
	}

	//========================================================================
	boolean handleOfferResponseCode( int responseCode )
	{
		boolean responesOk = false;
		if( responseCode != Constants.eOfferResponseAccept )
		{
			if( Constants.ePluginTypeMultiSession != m_ePluginType )
			{
				errMsgBox( true, GuiHelpers.describeResponse( responseCode ) );
				m_Activity.finish();
			}
			else
			{
				handleSessionEnded( responseCode );
			}
		}
		else
		{
			responesOk = true;
		}
		
		return responesOk;
	}
	
	//============================================================================   
	void handleSessionEnded( GuiOfferSession offerSession )
	{
		if( isOurSessionInstance( offerSession ) ) 
		{
			handleSessionEnded( offerSession.m_eOfferResponse );
		}
	}
	
	//========================================================================
	public void handleSessionEnded( int eOfferResponse)
    {
		if( false == m_SessionEndIsHandled )
		{
			m_SessionEndIsHandled = true;
    		setCallState( ECallState.eCallStateHangedUp );
			if( m_IsInSession )
			{
				m_IsInSession = false;
				onInSession( false );
				if( Constants.ePluginTypeMultiSession != m_ePluginType )
				{
					NativeTxTo.fromGuiStopPluginSession( m_ePluginType, m_HisIdent.m_u64IdHiPart, m_HisIdent.m_u64IdLoPart, 
							m_OfferSessionId.m_u64IdHiPart, m_OfferSessionId.m_u64IdLoPart, 0 );
				}
			}
			
			if( eOfferResponse ==  Constants.eOfferResponseUserOffline )
			{
				m_OfferCallback.onContactOffline();
			}
			
			if( ( Constants.ePluginTypeMultiSession != m_ePluginType )
				&& ( Constants.ePluginTypeCamServer != m_ePluginType ) )
			{
    	    	String responseDesc = GuiHelpers.describeResponse( eOfferResponse );
			    AlertDialog.Builder dlgAlert  = new AlertDialog.Builder( m_Activity );                       
			    dlgAlert.setTitle("Session Has Ended");  
			    dlgAlert.setMessage( responseDesc );  
			    dlgAlert.setPositiveButton("OK",new DialogInterface.OnClickListener() 
			    { 
			        public void onClick(DialogInterface dialog, int whichButton) 
			        { 
		  			   	m_MyApp.playButtonClick();
		  			   	m_OfferCallback.onSessionActivityShouldExit();
			        } 
			    }); 
			    
			    dlgAlert.setCancelable(true); 
			    dlgAlert.create().show(); 
			}
    	}
	} 
	
	//========================================================================
	void handleUserWentOffline()
	{
		setCallState( ECallState.eCallStateHangedUp );
		errMsgBox( true, m_HisIdent.getOnlineName() + " is offline" );	
	}
	
	//========================================================================
	void startPhoneRinging()
	{
		
	}
	
	//========================================================================
	void stopPhoneRinging()
	{
		
	}
	//========================================================================
	void showOfflineMsg()
	{
		m_OffersMgr.contactWentOffline( m_HisIdent );
        Toast.makeText( m_Activity, m_HisIdent.getOnlineName() + " Is Offline.", Toast.LENGTH_SHORT).show();		
	}
	
	//============================================================================
	//! show error message box to user
	void errMsgBox( boolean bExitWhenClicked, String strMsg )
	{
		final boolean exitWhenClicked = bExitWhenClicked;
		AlertDialog.Builder dialog = new AlertDialog.Builder( m_Activity ); 
		dialog.setTitle("Session Error Message")
		.setMessage(strMsg) 
		       .setPositiveButton("Ok", new DialogInterface.OnClickListener() 
		       {
		    	   @Override
		           public void onClick(DialogInterface dialog, int id) 
		           { 
		               // Handle Ok 
	    			   m_MyApp.playButtonClick();
		        	   if( exitWhenClicked )
		        	   {
		        		   m_OfferCallback.onSessionActivityShouldExit();
		        	   }
		           } 
		       }); 
		       /*
		       .setNegativeButton("Cancel", new DialogInterface.OnClickListener() 
		       { 
		           public void onClick(DialogInterface dialog, int id) { 
		               // Handle Cancel 
	    			   m_MyApp.playButtonClick();
		           } 
		       }) 
		       */
		dialog.show(); 	
	}
}





