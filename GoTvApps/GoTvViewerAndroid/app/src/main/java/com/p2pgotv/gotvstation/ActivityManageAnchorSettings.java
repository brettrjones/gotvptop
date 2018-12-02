//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

public class ActivityManageAnchorSettings  extends ActivityBase implements OnItemSelectedListener
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityManageAnchorSetttings:";
	   
	//=== vars ===//
	private Spinner  			m_SettingsNameSpinner 		= null;
	private ArrayAdapter<String> m_SettingsNameAdaper 		= null;
	private ArrayList<String> 	m_SettingsNameList 			= null;
	
	private EditText  			m_AnchorUrlEdit 			= null;
	private EditText  			m_NetworkNameEdit 			= null;
	
	private CheckBox  			m_IsDeviceAnAnchorCheckBox 	= null;
	private EditText  			m_ConnectionTestUrlEdit 	= null;
	private EditText  			m_NewSettingNameEdit 		= null;
	private Button 				m_SaveSettingBut 			= null;
	private Button 				m_DeleteSettingBut 			= null;
	
    //========================================================================
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_manage_anchor_settings);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_manage_anchor_settings_title);
        // keep keyboard from popping up
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); 
 	 	
 	 	
	    this.m_SettingsNameSpinner 		= (Spinner)this.findViewById(R.id.anchor_settings_name_spinner);	
	    this.m_SettingsNameList			= new ArrayList<String>();
	    this.m_SettingsNameAdaper		= new ArrayAdapter<String>(ActivityManageAnchorSettings.this,android.R.layout.simple_dropdown_item_1line,m_SettingsNameList);
	    m_SettingsNameSpinner.setAdapter( m_SettingsNameAdaper );
	    m_SettingsNameSpinner.setOnItemSelectedListener(this);
	    
	    this.m_AnchorUrlEdit 			= (EditText)this.findViewById(R.id.anchor_url_edit);	 	 	
	    this.m_NetworkNameEdit 			= (EditText)this.findViewById(R.id.anchor_settings_network_name_edit);	
	    this.m_IsDeviceAnAnchorCheckBox	= (CheckBox)this.findViewById(R.id.check_box_make_anchor);	
	    this.m_ConnectionTestUrlEdit 	= (EditText)this.findViewById(R.id.connection_test_url_edit);	

	    this.m_NewSettingNameEdit 		= (EditText)this.findViewById(R.id.anchor_settings_new_name_edit);	
	    this.m_SaveSettingBut = (Button)this.findViewById(R.id.anchor_settings_save_button);
	 	this.m_SaveSettingBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onSaveSettingButClick(v);
	 		}
	 	});	

	    this.m_DeleteSettingBut = (Button)this.findViewById(R.id.anchor_settings_delete_button);
	 	this.m_DeleteSettingBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onDeleteSettingButClick(v);
	 		}
	 	});	
	 	
	    updateDlgFromSettings(); 
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
		super.onDestroy();
	}

	//============================================================================
    void updateDlgFromSettings()
    {
    	// clear spinner
    	m_SettingsNameList.clear();
    	m_SettingsNameAdaper.notifyDataSetChanged();

    	boolean validDbSettings = false;
    	DataHelper dataHelper = m_MyApp.getDataHelper();
    	ArrayList<AnchorSetting> anchorSettingList = new ArrayList<AnchorSetting>();
    	String lastSettingsName = dataHelper.getLastAnchorSettingName();
    	int currentSettingIdx = 0;
    	int selectedIdx = 0;
    	AnchorSetting selectedAnchorSetting = null;
    	if( ( null != lastSettingsName )
        	&& ( 0 != lastSettingsName.length() )
    		&& dataHelper.getAllAnchorSettings( anchorSettingList )
    		&& ( 0 != anchorSettingList.size() ) )
    	{
    		for( AnchorSetting anchorSetting : anchorSettingList )
    		{
    			m_SettingsNameList.add( anchorSetting.getAnchorSettingName() );
    			if( 0 == anchorSetting.getAnchorSettingName().compareTo( lastSettingsName ) )
    			{
    				// found last settings used
    				validDbSettings = true;
    				selectedAnchorSetting = anchorSetting; 
    				selectedIdx = currentSettingIdx;
     			}

    			currentSettingIdx++;
    		}
    	}
    	
    	if( currentSettingIdx > 0 )
    	{
    		// at least one was added to spinner list
    	   	m_SettingsNameAdaper.notifyDataSetChanged();  
     	}

    	if( validDbSettings )
    	{
    		m_SettingsNameSpinner.setSelection( selectedIdx );
 			populateDlgFromAnchorSetting( selectedAnchorSetting );
    	}
    	else if( 0 != anchorSettingList.size() )
    	{
    		m_SettingsNameList.add( anchorSettingList.get(0).getAnchorSettingName() );
    	   	m_SettingsNameAdaper.notifyDataSetChanged();  		
    		populateDlgFromAnchorSetting( anchorSettingList.get(0) );
    		dataHelper.updateLastAnchorSettingName( anchorSettingList.get(0).getAnchorSettingName() );
    	}
    	else
    	{
    		m_SettingsNameList.add( "default" );
    		m_NewSettingNameEdit.setText("default");
    		m_SettingsNameAdaper.notifyDataSetChanged();
    		
        	MySettings mySettings = m_MyApp.getMySettings();
    	
      		String strValue = mySettings.getAnchorWebsiteUrl();
      		m_AnchorUrlEdit.setText( strValue );

      		strValue = mySettings.getNetworkName( );
    		m_NetworkNameEdit.setText( strValue );

    		strValue = mySettings.getConnectionTestWebsiteUrl();
    		m_ConnectionTestUrlEdit.setText( strValue );

    		m_IsDeviceAnAnchorCheckBox.setChecked( mySettings.getIsDeviceAnAnchor() );
    	}
    }

    //============================================================================
    void populateDlgFromAnchorSetting( AnchorSetting anchorSetting )
    {
    	m_NewSettingNameEdit.setText( anchorSetting.getAnchorSettingName() );
      	m_AnchorUrlEdit.setText( anchorSetting.getAnchorWebsiteUrl() );
      	m_NetworkNameEdit.setText( anchorSetting.getNetworkName() );
      	m_ConnectionTestUrlEdit.setText( anchorSetting.getNetServiceWebsiteUrl() );
      	m_IsDeviceAnAnchorCheckBox.setChecked( anchorSetting.getIsDeviceAnAnchor() );
    }

    //============================================================================
    void updateSettingsFromDlg()
    {
      	AnchorSetting anchorSetting = new AnchorSetting();
    	fillAnchorSettingFromDialog( anchorSetting );
    	saveAnchorSetting( anchorSetting );
    }
    
    //============================================================================
    void saveAnchorSetting( AnchorSetting anchorSetting )
    { 
    	MySettings g_oMySettings = m_MyApp.getMySettings();
     	g_oMySettings.setAnchorWebsiteUrl( anchorSetting.getAnchorWebsiteUrl() );
    	g_oMySettings.setNetworkName( anchorSetting.getNetworkName() );
  	    g_oMySettings.setIsDeviceAnAnchor( anchorSetting.getIsDeviceAnAnchor() );
  	    g_oMySettings.setConnectionTestWebsiteUrl( anchorSetting.getNetServiceWebsiteUrl() );
    	
  	    m_MyApp.getDataHelper().updateAnchorSetting( anchorSetting );
  	    m_MyApp.getDataHelper().updateLastAnchorSettingName( anchorSetting.getAnchorSettingName() );
    }
    
    //========================================================================
  	public void fillAnchorSettingFromDialog( AnchorSetting anchorSetting )
  	{
  	   	String strValue = (String)m_SettingsNameSpinner.getSelectedItem();
  	   	if( ( null != strValue ) && ( 0 < strValue.length() ) )
  	   	{
  	   		anchorSetting.setAnchorSettingName( strValue );
  	  	
	  	   	strValue = m_AnchorUrlEdit.getText().toString();
	  	   	anchorSetting.setAnchorWebsiteUrl( strValue );
	
	    	strValue = m_NetworkNameEdit.getText().toString();
	    	anchorSetting.setNetworkName( strValue );
	  	
	    	boolean isAnchor = m_IsDeviceAnAnchorCheckBox.isChecked();
	    	anchorSetting.setIsDeviceAnAnchor( isAnchor );
	
	    	strValue = m_ConnectionTestUrlEdit.getText().toString();
	    	anchorSetting.setNetServiceWebsiteUrl( strValue );	
  	   	}
  	   	else
  	   	{
  			Toast.makeText(this, "No Anchor Setting Is Selected.", Toast.LENGTH_SHORT).show();;	   		
  	   	}
  	}
   
    //========================================================================
  	public void onSaveSettingButClick(View v) 
    {
     	Log.i(LOG_TAG, "onSaveSettingButClick ");	
  	   	String strValue = m_NewSettingNameEdit.getText().toString();
  	   	if( ( null == strValue ) || ( 0 >= strValue.length() ) )
  	   	{
			Toast.makeText(this, "Invalid New Anchor Setting Name.", Toast.LENGTH_SHORT).show();
  	   		return;
  	   	}
  	   	
      	AnchorSetting anchorSetting = new AnchorSetting();
    	fillAnchorSettingFromDialog( anchorSetting );

   		anchorSetting.setAnchorSettingName( strValue );
    	saveAnchorSetting( anchorSetting );
    	updateDlgFromSettings();
		Toast.makeText(this, "Anchor Settings Was Saved.", Toast.LENGTH_SHORT).show();
 	}  	
    
    //========================================================================
  	public void onDeleteSettingButClick(View v) 
    {
     	Log.i(LOG_TAG, "onDeleteSettingButClick ");	
    	updateSettingsFromDlg();
    	if( 1 >= m_SettingsNameSpinner.getAdapter().getCount() )
    	{
    		Toast.makeText(this, "You cannot delete the last anchor setting.", Toast.LENGTH_LONG).show();;
    		return;
    	}
    	
  	   	String strValue = (String)m_SettingsNameSpinner.getSelectedItem();
 	   	if( ( null != strValue ) && ( 0 < strValue.length() ) )
  	   	{
    		m_MyApp.getDataHelper().removeAnchorSettingByName( strValue );
    		int itemPos = m_SettingsNameSpinner.getSelectedItemPosition();
    		m_SettingsNameList.remove(itemPos);
    		
    		updateDlgFromSettings();	   		
  	   	}
 	   	else
 	   	{
  			Toast.makeText(this, "No Anchor Setting Is Selected.", Toast.LENGTH_SHORT).show();;	   			   		
 	   	}
  	}

	//========================================================================
	@Override
	public void onItemSelected(AdapterView<?> parent, View view, int position, long id) 
	{
		if( (position >= 0) && (position < m_SettingsNameList.size() ) )
		{
			String settingName = m_SettingsNameList.get(position);
			AnchorSetting anchorSetting = new AnchorSetting();
			if( m_MyApp.getDataHelper().getAnchorSettingByName( settingName, anchorSetting ) )
			{
		  		m_MyApp.getDataHelper().updateLastAnchorSettingName( settingName );
		  		populateDlgFromAnchorSetting( anchorSetting );	  		 		
			}			
		}
	}

	//========================================================================
	@Override
	public void onNothingSelected(AdapterView<?> parent) 
	{
		// TODO Auto-generated method stub	
	}  	
}
