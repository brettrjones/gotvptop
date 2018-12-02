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

public class VxFileName 
{
	private String 				m_FullPath;
	private static final char 	m_PathSeparator 		= '/';
	private static final char	m_ExtensionSeparator 	= '.';

	//========================================================================
	public VxFileName( String fullPath ) 
	{
		m_FullPath = fullPath;
	}

	//========================================================================
	public String getPathAndFileName() 
	{
		return m_FullPath;
	}

	//========================================================================
	public String geExtension() 
	{
		int extensionIdx = m_FullPath.lastIndexOf( m_ExtensionSeparator );
		return m_FullPath.substring( extensionIdx + 1 );
	}

	//========================================================================
	public String getJustFileName() 
	{ 
		int nameIdx = m_FullPath.lastIndexOf( m_PathSeparator );
		return m_FullPath.substring( nameIdx + 1 );
	}

	//========================================================================
	public String getJustPath() 
	{
		int nameIdx = m_FullPath.lastIndexOf( m_PathSeparator );
		return m_FullPath.substring( 0, nameIdx );
	}
}
