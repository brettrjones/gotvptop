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

public class XferFileItemInfo
{
	public String			m_FileName;
	public String			m_FileDesc;
	public int				m_EPrevState 		= Constants.eXferFileStateUnknown;
	public int				m_ENewState 		= Constants.eXferFileStateUnknown;
	public int				m_PercentProgress 	= 0;
	public int				m_Error = 0;
	public int				m_Position = 0;

    //============================================================================
	XferFileItemInfo()
	{
	}
	
	public void 			setFileName( String fileName )	{ m_FileName = fileName; }
	public String 			getFileName()					{ return m_FileName; }
	
	public void 			setProgress( int progress )		{ m_PercentProgress = progress; }	
	public int 				getProgress()					{ return m_PercentProgress;		}
	
	public void 			setPrevState( int prevState )	{ m_EPrevState = prevState; }
	public int 				getPrevState() 					{ return m_EPrevState; }
	
	public void 			setNewState( int newState ) 	{ m_ENewState = newState; }
	public int 				getNewState()					{ return m_ENewState; }

	public String 			getFileDesc()					{ return m_FileDesc; }

    //============================================================================
	public int getXferDirection()
	{
		if( m_ENewState < 200 )
		{
			return Constants.eXferToMe;
		}
		
		return Constants.eXferToHim;
	}
	
    //============================================================================
	public int getIconPos1()
	{
		int iconRes = R.drawable.ic_folder;
		return iconRes;
	}
};
