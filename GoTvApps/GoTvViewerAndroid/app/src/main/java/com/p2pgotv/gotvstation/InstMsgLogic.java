//============================================================================
// Copyright (C) 2015 Brett R. Jones
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
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

class InstMsgLogic
{
	//private static final String LOG_TAG 					= "InstMsgLogic:";
	
	//=== vars ===//
	private	MyApp				m_MyApp						= null;
	private int 				m_ePluginType				= Constants.ePluginTypeInvalid;
	private VxNetIdent 			m_HisIdent 					= null;
	
	private Button				m_SendButton 				= null;
	private Button				m_ShredButton 				= null;
	
	private EditText			m_SayEditText 				= null;
	private EditText			m_HistoryText 				= null;

	//============================================================================
	InstMsgLogic( 	MyApp 					myApp, 
					int 					pluginType,
					VxNetIdent				hisIdent,				
					EditText				sayEditText,
					EditText				historyEditText,
					Button					sendButton,
					Button					shredButton )
	{
		m_MyApp 							= myApp;
		m_ePluginType 						= pluginType;
		m_HisIdent 							= hisIdent;
		m_SendButton						= sendButton;
		m_ShredButton						= shredButton;
	    if( null != m_ShredButton )
	    {
	    	m_ShredButton.setOnClickListener(new OnClickListener() 
	    	{
	            public void onClick(View v) 
	            {
		        	m_MyApp.playButtonClick();
	            	onShredButtonClicked();
	            }
	        });     
	    }    
	    
		m_SayEditText						= sayEditText;
		m_HistoryText						= historyEditText;
		
        if( null != m_SendButton )
        {
        	m_SendButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
		        	m_MyApp.playButtonClick();
	            	onSendButtonClicked();
	            }
	        });     
        }
        
        if( null != m_HistoryText )
        {
        	m_HistoryText.setBackgroundResource( R.color.inst_msg_history_bkg_color );
        }
 	}	
 
 	//============================================================================
 	void onShredButtonClicked()
 	{
		if( null != m_HistoryText )
		{
			m_HistoryText.setText("");
			m_MyApp.playSound( ESndDef.eSndDefPaperShredder );
		} 		
 	}
 	
 	//============================================================================
 	void onSendButtonClicked()
 	{
 		if( null != m_SayEditText )
 		{
 			m_MyApp.playButtonClick();
 			String strChatMsg = m_SayEditText.getText().toString();
 			if(0 != strChatMsg.length())
 			{
 				boolean sentMsg = NativeTxTo.fromGuiInstMsg( m_HisIdent.m_u64IdHiPart, m_HisIdent.m_u64IdLoPart, m_ePluginType, strChatMsg );
 				if( false == sentMsg )
 				{
 					addHistoryMsg( m_HisIdent.getOnlineName() + ": is Offline" );
 				}
 				else
 				{
 					addHistoryMsg( m_MyApp.getUserAccount().getOnlineName() + ": " + strChatMsg );
 				}
			}
 		}
 		
 		m_SayEditText.setText("");
  	}

 	//============================================================================
 	void addHistoryMsg( String historyMsg )
 	{
		if( null != m_HistoryText )
		{
			m_HistoryText.append( "\n" + historyMsg );
		}
 	}

	//========================================================================
 	void toGuiInstMsg( String strMsg ) 
	{
		String strHistoryMsg = m_HisIdent.getOnlineName() + VxTimeUtil.getChatHourMinTimeStamp() + ": " + strMsg;
		addHistoryMsg( strHistoryMsg );
		m_MyApp.playSound( ESndDef.eSndDefOfferArrived );
	}	
}
