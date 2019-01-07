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

import android.app.*;
import android.app.ActivityManager.MemoryInfo;
import android.util.*;
import android.view.*;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import android.os.Build;
import android.os.Bundle;

public class ActivityAbout extends ActivityBase 
{
    //=== constants ===//
    public static final String LOG_TAG = "ActivityAbout:";
    //=== activity vars ===//
    
    //=== vars ===//
    private Button             		 	m_oOkBut = null;
    private TextView           		 	m_oMemoryText = null;
    private TextView           		 	m_DiskSpaceText = null;
	public VxNetIdent 					m_oMyIdent;
    
	//============================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        Log.i( LOG_TAG, "onCreate " );
        setContentView(R.layout.about_page);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_about_title );
        
        TextView appTitleText = (TextView)this.findViewById(R.id.app_title);
        if( null != appTitleText )
        {
        	appTitleText.setText(  NativeTxTo.fromGuiGetAppName() );
        }
        
        TextView appVersionText = (TextView)this.findViewById(R.id.app_version);
        if( null != appVersionText )
        {
        	appVersionText.setText(  NativeTxTo.fromGuiGetAppVersionString() );
        }
	    
        // launch Login activity
        this.m_oOkBut = (Button)this.findViewById(R.id.button_close);
        this.m_oOkBut.setOnClickListener(new OnClickListener() 
        {
        	public void onClick(View v) 
        	{
        		m_MyApp.playButtonClick();
        		OnOkButClick(v);
        	}
        });     
        
        this.m_oMemoryText = (TextView)this.findViewById(R.id.memory_usage);

		MemoryInfo mi = new MemoryInfo();
		ActivityManager activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
		activityManager.getMemoryInfo(mi);
		long availableMegs = mi.availMem / 1048576L;
		m_oMemoryText.setText( "Memory Available: " + availableMegs + " MB");
		
        m_DiskSpaceText = (TextView)this.findViewById(R.id.about_disk_space);
		long diskFreeSpace = NativeTxTo.fromGuiGetDiskFreeSpace();
		if( ( 0 != diskFreeSpace ) && ( diskFreeSpace < 1000000000 ) )
		{
			m_DiskSpaceText.setText( "Disk Space Available is low: " + VxFileUtil.describeFileLength( diskFreeSpace ) );
		}
		else
		{
			m_DiskSpaceText.setText( "Disk Space Available: " + VxFileUtil.describeFileLength( diskFreeSpace ) );	
		}
		
		m_MyApp.updateUserAccountFromEngine();
		m_oMyIdent = m_MyApp.getUserAccount();
		m_oMyIdent.debugDumpIdent();
		
		TextView textLine = (TextView)this.findViewById(R.id.textView1); 
		textLine.setText( "My Node Url: http://" + m_oMyIdent.m_as8OnlineIPv4 + ":" +  m_oMyIdent.getOnlinePort() );
		
		textLine = (TextView)this.findViewById(R.id.textView2); 
		textLine.setText( "Online Name: " + m_oMyIdent.m_as8OnlineName );
		
		textLine = (TextView)this.findViewById(R.id.textView3); 
		textLine.setText( "Local IPv4: " + m_oMyIdent.m_as8LocalIPv4  );

		textLine = (TextView)this.findViewById(R.id.textView4); 
		textLine.setText( "Local IPv6: " + m_oMyIdent.m_as8OnlineIPv6 );	
		
		textLine = (TextView)this.findViewById(R.id.textView5); 
		textLine.setText( "Relay IPv4: " + m_oMyIdent.m_as8RelayIPv4 + " Port " +  m_oMyIdent.getRelayPort() );

		textLine = (TextView)this.findViewById(R.id.textView6); 
		textLine.setText( "Relay IPv6: " + m_oMyIdent.m_as8RelayIPv6 );
		
		textLine = (TextView)this.findViewById(R.id.textView7); 
		textLine.setText( "RequiresRelay? " + m_oMyIdent.requiresRelay() + " Has Relay? " + m_oMyIdent.hasRelay() );
		
		textLine = (TextView)this.findViewById(R.id.textView8); 
		String deviceText = "Device: " + BuildInfo.getDeviceManufacturer() + " - " + BuildInfo.getDevice() + " - " + BuildInfo.getDeviceModel();
		textLine.setText( deviceText );
		
		textLine = (TextView)this.findViewById(R.id.textView9); 
		String productText = "Product: " + BuildInfo.getBrand() + " - " + BuildInfo.getProduct();
		textLine.setText( productText );

		textLine = (TextView)this.findViewById(R.id.textView10); 
		String versionText = "Version: " + BuildInfo.getAndroidBuildId() + " - " + BuildInfo.getBuildType() + " - " + BuildInfo.getBuildRelease() + " - " + BuildInfo.getSdkVersion();
		textLine.setText( versionText );
		

        Log.i(LOG_TAG, "ActivityAbout onCreate done");
    }
        
    //============================================================================
    public void OnOkButClick(View v) 
    {
    	finish();
    }     
};
