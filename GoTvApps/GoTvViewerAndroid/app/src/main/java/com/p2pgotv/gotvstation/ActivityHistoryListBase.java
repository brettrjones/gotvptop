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

import java.util.ArrayList;
import android.support.v7.app.ActionBarActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.ListView;

public class ActivityHistoryListBase extends ActionBarActivity
{
	// === constants ===//
	//private static final String LOG_TAG = "ActivityHistoryListBase:";

	// === activity vars ===//
	public 	MyApp 					m_MyApp 			= null;
	//private ArrayList<AssetGuiInfo> m_AssetList 		= null;
	public  AssetGuiInfoAdapter 	m_oContactsAdapter 	= null;
	private Handler 				m_oMessageHandler 	= null;
	
	public int 						m_iWhoToViewInList 	= 0;

	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
 		super.onCreate(savedInstanceState);
 		m_MyApp = (MyApp) this.getApplication();
		// Log.i(LOG_TAG, "MainActivity m_HisIdentList");
		//this.m_AssetList = new ArrayList<AssetGuiInfo>();
		
		/*
		// Log.i(LOG_TAG, "MainActivity m_oContactsAdapter");
		//this.m_oContactsAdapter = new AssetGuiInfoAdapter( this, R.layout.contact_item, m_AssetList );
		//setListAdapter( this.m_oContactsAdapter );
		m_oMessageHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MSG_TYPE_UPDATE_HISTORY_LIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_UPDATE_HISTORY_LIST");
		    		//m_oContactsAdapter.doUpdateFriend( (FriendBase) msg.obj );
		    		m_oContactsAdapter.notifyDataSetChanged();
		    		break;
		    		
		    	//case Constants.MSG_TYPE_REFRESH_HISTORY_LIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_REFRESH_CONTACTS");
					//m_oContactsAdapter.clearList();
					//Log.i(LOG_TAG, "RefreshContacts: notifyDataSetChanged ");
					//m_oContactsAdapter.notifyDataSetChanged();
					//Log.i(LOG_TAG, "RefreshContacts: fromGuiSendContactList ");
					//NativeTxTo.fromGuiSendContactList( m_iWhoToViewInList );		    		
		    		//break;

		    	case Constants.MSG_TYPE_CLEAR_HISTORY_LIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_TYPE_CLEAR_CONTACTS");
					m_oContactsAdapter.clearList();
					//Log.i(LOG_TAG, "RefreshContacts: notifyDataSetChanged ");
					m_oContactsAdapter.notifyDataSetChanged();
		    		break;

		    	}
		    	super.handleMessage(msg);
		    }
		};
		*/
	}
	//========================================================================
	@Override
	public void onDestroy() 
	{
		m_oContactsAdapter.clearList();
		m_oMessageHandler = null;
 		super.onDestroy();
	}

	//========================================================================
	public void RefreshContacts() 
	{
		Message msg; 
		msg = Message.obtain(); 
		msg.what = Constants.MSG_TYPE_REFRESH_HISTORY_LIST;   
		m_oMessageHandler.sendMessage(msg); 
	}	  
    
	//========================================================================
	public void UpdateFriend( VxNetIdent oIdentIn ) 
	{
		Message msg; 
		msg = Message.obtain(); 
		msg.what = Constants.MSG_TYPE_UPDATE_HISTORY_LIST;   
		msg.obj = oIdentIn;
		m_oMessageHandler.sendMessage(msg); 
	}
    
	//========================================================================
	public void ClearContactList() 
	{
		Message msg; 
		msg = Message.obtain();
		msg.what = Constants.MSG_TYPE_CLEAR_HISTORY_LIST;   
		msg.obj = null;
		m_oMessageHandler.sendMessage(msg); 
	}

	
};