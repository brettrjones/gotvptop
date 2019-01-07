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

public class VxTimer
{
	private	long				m_StartTime;
	
	//========================================================================
	VxTimer()
	{
		startTimer();
	}
	
	//========================================================================
	double						elapsedMilliSec()						
	{ 
		return (double)(System.currentTimeMillis() - m_StartTime); 
	}
	
	//========================================================================
	double						elapsedSec()
	{
		return elapsedMilliSec() / 1000.0;
	}
	
	//========================================================================
	//just sets start time for elapsed time
	void						startTimer()
	{
		m_StartTime = System.currentTimeMillis();
	}
};
