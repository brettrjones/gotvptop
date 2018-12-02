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

import java.util.ArrayList;
import java.util.List;

import android.net.Uri;

public class PhoneContactInfo
{
	//private static final String LOG_TAG = "PhoneContactInfo:";
	public String 				m_ContactId				= "";
	public String 				m_DisplayName			= "";
	public Uri 					m_ContactPhotoUri		= null;
	public List<String> 		m_PhoneNumList			= new ArrayList<String>();
	public List<String> 		m_EmailAddress			= new ArrayList<String>();
	
	int getPhoneNumberCount()
	{
		return m_PhoneNumList.size();
	}
	
	String getPhoneNumbers()
	{
		String phoneNums = "";
		int phoneNumCnt = getPhoneNumberCount();
		if( 0 < phoneNumCnt )
		{
			for( int position = 0; position < phoneNumCnt; position++ )
			{
				phoneNums += m_PhoneNumList.get( position );
				if( position + 1 < phoneNumCnt )
				{
					// there will be at least one more so add comma between
					phoneNums += ",";
				}
			}
		}
		
		return phoneNums;
	}
	
	int getEmailAddressCount()
	{
		return m_EmailAddress.size();
	}
	
	String getEmailAddresses()
	{
		String emailAddresses = "";
		int emailAddressCnt = getEmailAddressCount();
		if( 0 < emailAddressCnt )
		{
			for( int position = 0; position < emailAddressCnt; position++ )
			{
				emailAddresses += m_EmailAddress.get( position );
				if( position + 1 < emailAddressCnt )
				{
					// there will be at least one more so add comma between
					emailAddresses += ",";
				}
			}
		}
		
		return emailAddresses;
	}
};

