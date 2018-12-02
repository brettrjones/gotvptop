//============================================================================
// Copyright (C) 2016 Brett R. Jones 
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

public class IdentImagePair
{
	//=== vars ===//
	VxNetIdent					m_NetIdent	= null;
	Bitmap						m_Image		= null;

	//============================================================================
	IdentImagePair( VxNetIdent netIdent, Bitmap image )
	{
		m_NetIdent 	= netIdent;
		m_Image		= image;
	}

	//============================================================================
	Bitmap getImage()
	{
		return m_Image;
	}

	//============================================================================
	void setImage( Bitmap bitmap )
	{
		m_Image = bitmap;
	}

	//============================================================================
	VxNetIdent getNetIdent()
	{
		return m_NetIdent;
	}

	//============================================================================
	void setNetIdent( VxNetIdent netIdent )
	{
		m_NetIdent = netIdent;
	}
};

