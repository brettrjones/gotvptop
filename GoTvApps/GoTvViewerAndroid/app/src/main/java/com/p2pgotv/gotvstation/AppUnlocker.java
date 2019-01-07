//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

import java.util.Iterator;
import java.util.List;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

public class AppUnlocker 
{
	//=== constants ===//
	public static final String LOG_TAG = "NativeTxTo:"; 

	static boolean isUnlockerInstalled(Context context) 
	{ 
		// the packagename of the 'key' app 
		String proPackage = "com.p2pgotv.gotvstation.unlocker"; 
		// get the package manager 
		final PackageManager pm = context.getPackageManager(); 
		// get a list of installed packages 
		List<PackageInfo> list = pm.getInstalledPackages(PackageManager.GET_DISABLED_COMPONENTS); 
		// let's iterate through the list 
		Iterator<PackageInfo> i = list.iterator(); 
		while(i.hasNext()) 
		{ 
			PackageInfo p = i.next(); 
			// check if proPackage is in the list AND whether that package is signed 
			 //  with the same signature as THIS package 
			if((p.packageName.equals(proPackage)) && 
					(pm.checkSignatures(context.getPackageName(), p.packageName) == PackageManager.SIGNATURE_MATCH)) 
			{
				return true;
			}
		} 
		return false; 
	} 
}
