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

public class FileStateInfo
{
	public String			m_FileName;
	public int				m_EPrevState;
	public int				m_ENewState;	
	
	FileStateInfo(  String fileName, int prevState, int newState )
	{
		m_FileName = fileName;
		m_EPrevState = prevState;
		m_ENewState = newState;
	}
	
	public String 	getFileName() 		{ return m_FileName; }
	public int 		getPrevState() 		{ return m_EPrevState; }
	public int 		getNewState()		{ return m_ENewState; }
	
	public int getXferDirection()
	{
		if( m_ENewState > 50 )
		{
			return Constants.eXferToMe;
		}
		return Constants.eXferToHim;
	}
	
}
