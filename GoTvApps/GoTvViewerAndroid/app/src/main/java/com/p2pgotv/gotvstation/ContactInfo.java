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

import android.graphics.Bitmap;

public class ContactInfo
{	
	//=== vars ===//
	private String				m_DisplayName				= "Not Set";
	private VxGUID				m_OnlineId					= new VxGUID();
	private String				m_MobilePhoneNum			= "";
	private String				m_UserNotes					= "";
	private String				m_OrigPicFileName			= "";
	private Bitmap				m_AvatarBitmap				= null;
	
	//========================================================================
	ContactInfo()
	{	
	}

	//========================================================================
	public void setDisplayName( String displayName )
	{
		m_DisplayName = displayName;
	}
	
	//========================================================================
	public String getDisplayName()
	{
		return m_DisplayName;
	}

	//========================================================================
	public void setOnlineId( long idHighPart, long idLowPart )
	{
		m_OnlineId.setOnlineId( idHighPart, idLowPart );
	}
	
	//========================================================================
	public VxGUID getOnlineId()
	{
		return m_OnlineId;
	}

	//========================================================================
	public void setMobilePhoneNum( String phoneNum )
	{
		m_MobilePhoneNum = phoneNum;
	}
	
	//========================================================================
	public String getMobilePhoneNum()
	{
		return m_MobilePhoneNum;
	}
	
	//========================================================================
	public void setUserNotes( String userNotes )
	{
		m_UserNotes = userNotes;
	}
	
	//========================================================================
	public String getUserNotes()
	{
		return m_UserNotes;
	}

	//========================================================================
	public void setAvatarBitmap( Bitmap avatarBitmap )
	{
		m_AvatarBitmap = avatarBitmap;
	}
	
	//========================================================================
	public Bitmap getAvatarBitmap()
	{
		return m_AvatarBitmap;
	}
		
	//========================================================================
	public boolean isAvatarPicValid()
	{
		return ( ( null != m_AvatarBitmap ) && ( 0 < m_AvatarBitmap.getWidth() ) );
	}

	//========================================================================
	public void setOrigPicFileName( String origPicFileName ) 
	{
		this.m_OrigPicFileName = origPicFileName;
	}

	//========================================================================
	public String getOrigPicFileName() 
	{
		return m_OrigPicFileName;
	}
};
