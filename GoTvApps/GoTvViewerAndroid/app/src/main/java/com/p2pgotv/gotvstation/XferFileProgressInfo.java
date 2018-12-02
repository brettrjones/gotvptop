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

public class XferFileProgressInfo
{
	public int				m_EProgressType;
	public String			m_FileName;
	public int				m_ProgressPercent;	
	
	XferFileProgressInfo( int eProgressType, String fileName, int percentComplete )
	{
		m_EProgressType = eProgressType;
		m_FileName = fileName;
		m_ProgressPercent = percentComplete; 
	}
	
	public void 	setFileName( String fileName )	{ m_FileName = fileName; }
	public String 	getFileName()					{ return m_FileName; }
	public void 	setProgress( int progress )		{	m_ProgressPercent = progress; }	
	public int 		getProgress()					{	return m_ProgressPercent;		}
	
	public int getXferDirection()
	{
		int direction = Constants.eXferToHim;
		if( 200 > m_EProgressType )
		{
			direction = Constants.eXferToMe;
		}

		return direction;
	}
}