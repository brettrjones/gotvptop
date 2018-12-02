package com.p2pgotv.gotvstation;

import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Iterator;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.Spinner;

public class ActivityNetworkSettings  extends ActivityBase implements RadioGroup.OnCheckedChangeListener
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityNetworkSettings:";
	   
	//=== vars ===//
	public Button 				m_AnchorSettingsBut = null;
    protected static RadioGroup m_ProxyRadioGroup;	
	public EditText  			m_ExternalIpEdit = null;
	public Button  				m_ExternalIpHelpBut = null;
	
	public Spinner  			m_AdapterIpSpinner = null;
    private String 				m_ArrayAdapterIps[];
	
	public CheckBox  			m_EnableUpnpCheckBox = null;
	public EditText  			m_ListenPortEdit = null;
	public Button 				m_RandamizePortBut = null;
	public Button 				m_TestIsPortOpenBut = null;
	
	public int					m_iProxyDetectSetting = Constants.eFirewallTestUrlConnectionTest;
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_network_settings);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_network_settings_title );
        // keep keyboard from popping up
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); 
 	 	
		this.m_AnchorSettingsBut = (Button)this.findViewById(R.id.net_settings_button_anchor_settings);
	 	this.m_AnchorSettingsBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onAnchorSettingsButClick(v);
	 		}
	 	});	
	 	
	    m_ProxyRadioGroup = (RadioGroup)this.findViewById( R.id.require_proxy_radio_group );     
	    m_ProxyRadioGroup.setOnCheckedChangeListener(this);
	 	
	 	this.m_AdapterIpSpinner 	= (Spinner)this.findViewById( R.id.net_settings_network_adapter_ip_spinner );	
	    this.m_EnableUpnpCheckBox 	= (CheckBox)this.findViewById( R.id.net_settings_upnp_checkBox );	
	    this.m_ExternalIpEdit		= (EditText)this.findViewById( R.id.external_ip_edit );	

	    this.m_ListenPortEdit 		= (EditText)this.findViewById( R.id.net_settings_port_edit );		        
		this.m_RandamizePortBut 	= (Button)this.findViewById( R.id.net_settings_randomize_port_button );
	 	this.m_RandamizePortBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onRandomizePortClick(v);
	 		}
	 	});		
	 
		this.m_TestIsPortOpenBut = (Button)this.findViewById(R.id.net_settings_test_port_button);
	 	this.m_TestIsPortOpenBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onTestIsPortOpenClick(v);
	 		}
	 	});	
	 	 
		this.m_ExternalIpHelpBut = (Button)this.findViewById(R.id.external_ip_help_button);
	 	this.m_ExternalIpHelpBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onExternalIpHelpClick();
	 		}
	 	});	
	 	
	 	fillAdapterIps();
	    updateDlgFromSettings(); 
    }

	//========================================================================
	private void onExternalIpHelpClick() 
	{
		
	}

	//========================================================================
	public void onCloseButClick() 
	{
		onBackButtonPressed();
	}

	//========================================================================
	@Override
	public void onBackButtonPressed() 
	{
		Log.d( LOG_TAG, "Closing Dialog\n" );
		updateSettingsFromDlg();
		super.onBackButtonPressed();
	}

	//========================================================================
	@Override
	protected void onDestroy() 
	{
		Log.d(LOG_TAG, "onDestroy");
		updateSettingsFromDlg();
		m_MyApp.sendNetworkSettingsToNative();
		NativeTxTo.fromGuiNetworkSettingsChanged();
		super.onDestroy();
	}

    //============================================================================
    void fillAdapterIps()
    {
        VxSktUtil sktUtil = m_MyApp.getVxSktUtil();
        ArrayList<InetAddress> addressList = new ArrayList<InetAddress>();; 
    	int addrCount =  sktUtil.getLocalIPv4Addresses( addressList );
    	int totalComboListCount = addrCount + 1;
       	m_ArrayAdapterIps = new String[totalComboListCount];
    	m_ArrayAdapterIps[0]="default";
    	
 		Iterator<InetAddress> iter = addressList.iterator();
		//use hasNext() and next() methods of Iterator to iterate through the elements
 		int comboBoxIdx = 1;
		while( iter.hasNext() )
		{
			InetAddress addrInList = iter.next();
			String strAddr = addrInList.toString();
			if( 0 != strAddr.length() )
			{
				strAddr = strAddr.replace( "/", "" );
				m_ArrayAdapterIps[ comboBoxIdx ] = strAddr;
			}
			
			comboBoxIdx++;
		}   		
    	
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, m_ArrayAdapterIps );
        m_AdapterIpSpinner.setAdapter(adapter); 
    }

    //============================================================================
    void updateDlgFromSettings()
    {
    	MySettings g_oMySettings = m_MyApp.getMySettings();
    	
    	String strExternalIp = g_oMySettings.getExternalIp();
    	m_ExternalIpEdit.setText( strExternalIp );
  	
    	m_EnableUpnpCheckBox.setChecked( g_oMySettings.getUseUpnpPortForward() );

    	int tcpPort = g_oMySettings.getMyTcpInPort();
    	String strPort = String.valueOf( tcpPort );
    	m_ListenPortEdit.setText( strPort );

    	m_iProxyDetectSetting = g_oMySettings.getFirewallTestSetting();
    	updateProxyRadioButtons( m_iProxyDetectSetting );
    }

    //============================================================================
    void updateSettingsFromDlg()
    {
    	String strValue;	
  		MySettings g_oMySettings = m_MyApp.getMySettings();
  	
  		strValue = m_AdapterIpSpinner.getSelectedItem().toString();
  		g_oMySettings.setNetworkAdapterIp( strValue );

  		strValue = m_ExternalIpEdit.getText().toString();
  		g_oMySettings.setExternalIp( strValue );

  		g_oMySettings.setUseUpnpPortForward( m_EnableUpnpCheckBox.isChecked() );

  		strValue = m_ListenPortEdit.getText().toString();
  		int tcpPort = Integer.parseInt(strValue);
  		g_oMySettings.setMyTcpInPort( tcpPort );

  		g_oMySettings.setFirewallTestSetting( m_iProxyDetectSetting );
    }

  	//========================================================================
  	void onAnchorSettingsButClick(View v)
  	{
    	Log.i(LOG_TAG, "onAnchorSettingsButClick ");	
 		updateSettingsFromDlg();
		Intent myIntent = new Intent(ActivityNetworkSettings.this, ActivityAnchorSettings.class);
 		myIntent.putExtra("IsStartupTest", "false"); 
 		ActivityNetworkSettings.this.startActivityForResult(myIntent,
				Constants.ACTIVITY_ANCHOR_SETTINGS);		 		
 	}
     
  	//========================================================================
 	public void onTestIsPortOpenClick(View v) 
    {
     	Log.i(LOG_TAG, "onTestIsPortOpenClick ");	
 		updateSettingsFromDlg();
		Intent myIntent = new Intent(ActivityNetworkSettings.this, ActivityTestIsMyPortOpen.class);
 		myIntent.putExtra("IsStartupTest", "false"); 
 		ActivityNetworkSettings.this.startActivityForResult(myIntent,
				Constants.ACTIVITY_TEST_IS_PORT_OPEN);		 		
 	}  
    
    //========================================================================
 	public void onRandomizePortClick(View v) 
    {
     	Log.i(LOG_TAG, "onRandomizePortClick ");
     	int randomPort = NativeTxTo.fromGuiGetRandomTcpPort();
  		MySettings g_oMySettings = m_MyApp.getMySettings();
  		g_oMySettings.setMyTcpInPort( randomPort );
    	String strPort = String.valueOf( randomPort );
    	m_ListenPortEdit.setText( strPort );
	}  
 	
 	//========================================================================   
	//@Override
	public void onCheckedChanged(RadioGroup arg0, int checkedId) 
	{
		if( R.id.use_connection_test_radio == checkedId )
		{
			m_iProxyDetectSetting = Constants.eFirewallTestUrlConnectionTest;
		}
		else if(  R.id.assume_no_firewall_radio == checkedId )
		{
			m_iProxyDetectSetting = Constants.eFirewallTestAssumeNoFirewall;
		}
		else if( R.id.assume_firewall_radio == checkedId )
		{
			m_iProxyDetectSetting = Constants.eFirewallTestAssumeFirewalled;
		}
	}
  	
    //========================================================================
 	public void updateProxyRadioButtons( int iProxyDetectSetting )
 	{
 	 	switch( iProxyDetectSetting )
 	  	{
 	  	case Constants.eFirewallTestAssumeFirewalled:
 	  		m_ProxyRadioGroup.check( R.id.assume_firewall_radio );
 	  		break;
 	  	case Constants.eFirewallTestAssumeNoFirewall:
 	  		m_ProxyRadioGroup.check( R.id.assume_no_firewall_radio );
 	  		break;
 	  	default:
 	  		m_ProxyRadioGroup.check( R.id.use_connection_test_radio );
 	  		break;
 	  	}
  	}
}
