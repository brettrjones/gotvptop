package com.p2pgotv.gotvstation;

public class TimerPro 
{
	VxTimer						m_ElapsedTimer				= new VxTimer();
	double						m_ExpireTimeMs				= 0;
	boolean						m_Enabled					= false;
	
	//========================================================================
	TimerPro()
	{
	}
	
	//========================================================================
	TimerPro( double expireTimeMs )
	{
		m_ExpireTimeMs = expireTimeMs;
	}
	
	//========================================================================
	void setInterval( double expireTimeMs )
	{
		m_ExpireTimeMs = expireTimeMs;
		m_ElapsedTimer.startTimer();
	}
	
	//========================================================================
	void start()
	{
		m_ElapsedTimer.startTimer();
		m_Enabled = true;		
	}
	
	//========================================================================
	void start( double expireTimeMs )
	{
		m_ExpireTimeMs = expireTimeMs;
		m_ElapsedTimer.startTimer();
		m_Enabled = true;		
	}
	
	//========================================================================
	void stop()
	{
		m_Enabled = false;		
	}
	
	//========================================================================
	boolean checkForExpire()
	{
		boolean expired = false;
		if( m_Enabled && ( m_ElapsedTimer.elapsedMilliSec() > m_ExpireTimeMs ) )
		{
			expired = true;
			m_ElapsedTimer.startTimer();		
		}
		
		return expired;
	}
	
}
