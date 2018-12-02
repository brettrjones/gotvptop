//============================================================================
// Copyright (C) 2009 Brett R. Jones
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

import android.util.*;
import android.view.*;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import android.os.Bundle;

public class ActivityNetworkStatus extends ActivityBase implements ToGuiNetworkStateInterface 
{
    //=== constants ===//
    public static final String LOG_TAG = "ActivityNetworkStatus:";
 
    //=== vars ===//
    private Button             		 	m_CloseButton 					= null;
    
    private TextView 					m_CellNetworkStateLabel 		= null;
    private TextView 					m_InternetConnectedStateLabel	= null;
    private TextView 					m_IPAddressValueLabel			= null;
    private TextView 					m_TcpPortValueLabel				= null;
    private TextView 					m_MyNodeUrlValueLabel			= null;
    private TextView 					m_P2PWebNetStateValueLabel		= null;
     
    private TextView 					m_NetStatLine1					= null;
    private TextView 					m_NetStatLine2					= null;
    private TextView 					m_NetStatLine3					= null;
    private TextView 					m_NetStatLine4					= null;
    private TextView 					m_NetStatLine5					= null;
    private TextView 					m_NetStatLine6					= null;
    private TextView 					m_NetStatLine7					= null;
    private TextView 					m_NetStatLine8					= null;
    
    private int 						MAX_NET_HELP_LINES				= 8;				

    
	//========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        Log.i( LOG_TAG, "onCreate " );
        setContentView( R.layout.activity_network_status );
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.network_state );
	    
        // launch Login activity
        this.m_CloseButton = (Button)this.findViewById( R.id.button_close );
        this.m_CloseButton.setOnClickListener(new OnClickListener() 
        {
        	public void onClick(View v) 
        	{
        		m_MyApp.playButtonClick();
        		OnOkButClick(v);
        	}
        });     
 				
		m_CellNetworkStateLabel 		= (TextView)this.findViewById( R.id.network_cellular ); 
		m_InternetConnectedStateLabel 	= (TextView)this.findViewById( R.id.network_internet_connected ); 
		m_IPAddressValueLabel 			= (TextView)this.findViewById( R.id.network_state_ip_address ); 
		m_TcpPortValueLabel 			= (TextView)this.findViewById( R.id.network_state_tcp_port ); 
		m_MyNodeUrlValueLabel 			= (TextView)this.findViewById( R.id.network_mynodeurl ); 
		m_P2PWebNetStateValueLabel 		= (TextView)this.findViewById( R.id.network_state ); 
		
		m_NetStatLine1 = (TextView)this.findViewById( R.id.network_help1 ); 
		m_NetStatLine2 = (TextView)this.findViewById( R.id.network_help2 ); 
		m_NetStatLine3 = (TextView)this.findViewById( R.id.network_help3 ); 
		m_NetStatLine4 = (TextView)this.findViewById( R.id.network_help4 ); 
		m_NetStatLine5 = (TextView)this.findViewById( R.id.network_help5 ); 
		m_NetStatLine6 = (TextView)this.findViewById( R.id.network_help6 ); 
		m_NetStatLine7 = (TextView)this.findViewById( R.id.network_help7 );
		m_NetStatLine8 = (TextView)this.findViewById( R.id.network_help8 );
	
    	NativeRxFrom.wantToGuiNetworkState( this, true );
    	doGuiNetworkStateChange( m_MyApp.getNetworkState() );
        Log.i(LOG_TAG, "ActivityAbout onCreate done");
    }
	
	//========================================================================
    @Override
	public void onDestroy() 
    {
		Log.d(Constants.LIFETIME, "&&&&& ActivityNetworkStatus onDestroy");
	   	NativeRxFrom.wantToGuiNetworkState( this, false );
		super.onDestroy();
    }
        
	//========================================================================
    public void OnOkButClick(View v) 
    {
    	finish();
    }

	//========================================================================
	@Override
	public void doGuiNetworkStateChange( int networkState )
	{
	    VxNetIdent myIdent = new VxNetIdent();
		NativeTxTo.fromGuiQueryMyIdent( myIdent );
		
		String strOnlineIp = myIdent.getOnlineIPv4();
		int tcpPort = myIdent.getOnlinePort();
		String tcpPortAsString = String.valueOf( tcpPort );
	
		m_IPAddressValueLabel.setText( "IP Address: " + strOnlineIp );
		m_TcpPortValueLabel.setText( "TCP Port: " + tcpPortAsString );
		m_MyNodeUrlValueLabel.setText( "My Node Url: http://" + strOnlineIp + ":" + tcpPortAsString );
		m_P2PWebNetStateValueLabel.setText( "Network State: " + Constants.describeNetworkState( networkState ) );

		boolean networkConnected = true;
		switch( networkState )
		{
		case Constants.eNetworkStateTypeUnknown:
		case Constants.eNetworkStateTypeLost:
		case Constants.eNetworkStateTypeNoInternetConnection:
			showNoInternetHelp();
			networkConnected = false;
			break;

		case Constants.eNetworkStateTypeAvail:
		case Constants.eNetworkStateTypeTestConnection:
		case Constants.eNetworkStateTypeAnnounce:
			showDiscoverNetworkHelp();
			break;

		case Constants.eNetworkStateTypeGetRelayList:
		case Constants.eNetworkStateTypeRelaySearch:
			showRelaySearchHelp();
			break;

		case Constants.eNetworkStateTypeOnlineDirect:
			showDirectConnectMessage();
			break;

		case Constants.eNetworkStateTypeOnlineThroughRelay:
			showRelayConnectedHelp();
			break;

		case Constants.eNetworkStateTypeFailedResolveAnchor:
			showAnchorError();
			break;
		}

		if( networkConnected )
		{
			boolean isCellNetwork = m_MyApp.getMgrNetwork().getIsCellNetworkConnection();
			if( isCellNetwork )
			{
				m_CellNetworkStateLabel.setText( "Cellular Data Connected?: YES" );			
				m_InternetConnectedStateLabel.setText( "Wireless Connected?: NO" );					
			}
			else
			{
				m_CellNetworkStateLabel.setText( "Cellular Data Connected?: NO" );			
				m_InternetConnectedStateLabel.setText( "Wireless Connected?: YES" );					
			}
		}
		else
		{
			m_CellNetworkStateLabel.setText( "Cellular Data Connected?: NO" );			
			m_InternetConnectedStateLabel.setText( "Wireless Connected?: NO" );					
		}
	}

	//============================================================================
	void showNoInternetHelp()
	{
		clearHelpLines();
		setHelpLine( 0, "No internet yet available" );
	}

	//============================================================================
	void showDiscoverNetworkHelp()
	{
		clearHelpLines();
		setHelpLine( 0, "Internet connected and My P2P Web " );
		setHelpLine( 1, "is testing the network." );
	}

	//============================================================================
	void showRelaySearchHelp()
	{
		setHelpLine( 0, "Internet connected but incoming TCP Port is blocked. " );
		setHelpLine( 1, "This may be because UPNP is disable on the router or " );
		setHelpLine( 2, "your device has a firewall or anti-virus program that " );
		setHelpLine( 3, "blocks the TCP Port used by My P2P Web.  " );
		setHelpLine( 4, "My P2P Web is searching for another node to act as  " );
		setHelpLine( 5, "relay/proxy for this device. Check Website for more details " );
	}

	//============================================================================
	void showDirectConnectMessage()
	{
		setHelpLine( 0, "Internet is connected and TCP Port " ); 
		setHelpLine( 1, "can accept incoming connections. " );
		setHelpLine( 2, "You have the best possible connection!" );
	}

	//============================================================================
	void showRelayConnectedHelp()
	{
		setHelpLine( 0, "My P2P Web connected but incoming TCP Port is blocked. " );
		setHelpLine( 1, "This may be because UPNP is disable on the router or " );
		setHelpLine( 2, "your device has a firewall or anti-virus program that " );
		setHelpLine( 3, "blocks the TCP Port used by My P2P Web.  " );
		setHelpLine( 4, "My P2P Web is using another node to act as  " );
		setHelpLine( 5, "relay/proxy for this device which results in slow "  );
		setHelpLine( 6, "data transfer and unstable connectivity."  );
		setHelpLine( 7, "Visit My P2P Web Website for help on how to direct connect." );
	}

	//============================================================================
	void showAnchorError()
	{
		setHelpLine( 0, "My P2P Web connected but could not contact the Anchor Node. " );
		setHelpLine( 1, "Check your network setting and Anchor node url." );
		setHelpLine( 2, "Visit My P2P Web  Website for details." );
	}

	//============================================================================
	void clearHelpLines()
	{
		String emptyString = "";
		for( int i = 0; i < MAX_NET_HELP_LINES; i++ )
		{
			setHelpLine( i, emptyString );
		}
	}

	//============================================================================
	void setHelpLine( int lineIdx, String helpText )
	{
		switch( lineIdx )
		{
		case 0:
			m_NetStatLine1.setText( helpText );
			break;

		case 1:
			m_NetStatLine2.setText( helpText );
			break;

		case 2:
			m_NetStatLine3.setText( helpText );
			break;

		case 3:
			m_NetStatLine4.setText( helpText );
			break;

		case 4:
			m_NetStatLine5.setText( helpText );
			break;

		case 5:
			m_NetStatLine6.setText( helpText );
			break;

		case 6:
			m_NetStatLine7.setText( helpText );
			break;

		case 7:
			m_NetStatLine8.setText( helpText );
			break;

		}
	}

	@Override
	public void doGuiSetIdentHasTextOffers( VxNetIdent hisIdent,
			boolean haveTextOffer )
	{
		// TODO Auto-generated method stub
		
	}
}
