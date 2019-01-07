//============================================================================
// Copyright (C) 2011 Brett R. Jones
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

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
import java.util.List;
import java.util.Random;
import android.annotation.SuppressLint;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;

public class VxMiscUtil 
{
	//========================================================================
	public static final boolean IsPaidVersionInstalled( Context ctx )  
	{ 	
		String PaidPackageName = "com.my.paid.packagename"; 
		//Grab the Installed Application Info to try to find the one we are looking for  
		List<ApplicationInfo> list = ctx.getPackageManager().getInstalledApplications(PackageManager.GET_META_DATA);   
		//Loop through the packages and make sure the donate package is actually installed 
		list.size();
		int i = 0;  
		for( i = 0; i < list.size(); ++i )
		{  
			ApplicationInfo ai = list.get(i); 
			if (ai.packageName.equals(PaidPackageName))
			{  
				return true;  
			}  
		} 
		return false;  
	}

//	public void goToAppMarketToUpgrade()
//	{
//		Intent goToMarket = null; goToMarket = new Intent( Intent.ACTION_VIEW, Uri.parse("market://details?id=com.my.paid.packagename") );
//		startActivity(goToMarket);
//	}
	
	 //========================================================================
	 public static boolean runningOnApi21OrHigher() 
	 {
		 // API Level 21 is Lollipop
		 return Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP;
	 }

	//========================================================================
	public static long generateRandomLong() 
	{  
		Random oRand = new Random();
		long s64NewLong = oRand.nextLong();
		if( s64NewLong > 0 )
		{
			s64NewLong = -s64NewLong;
		}
		
		return s64NewLong;  
	}  
}
