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


import java.util.ArrayList;
import java.util.concurrent.Semaphore;

import android.util.Log;


public class LogHandler 
{
	//=== constants ===//
	public static final String 		LOG_TAG			= "LogHandler:";
	public static final int 		LOG_VERBOSE 	= (0x0001);
	public static final int 		LOG_FATAL		= (0x0002);
	public static final int 		LOG_SEVERE		= (0x0004);
	public static final int 		LOG_ASSERT		= (0x0008);
	public static final int 		LOG_ERROR		= (0x0010);
	public static final int 		LOG_WARN		= (0x0020);
	public static final int 		LOG_INFO		= (0x0040);
	public static final int 		LOG_DEBUG		= (0x0080);	
	private static Semaphore 		m_LogMutex 		= new Semaphore(1); 
	 	
	//=== vars ===//
	public static final ArrayList<String> 	m_LogQue = new ArrayList<String>();

	//========================================================================
	LogHandler()
	{
	}
	
	//========================================================================
	public static void lockLogHandler()
	{
		try 
		{
			m_LogMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//========================================================================
	public static void unlockLogHandler()
	{
		m_LogMutex.release();
	}

	
	//========================================================================
	public static void			logMsg( int logLevel, String msg )
	{
		/* BRJ.. may be causing lock ups
		lockLogHandler();
		m_LogQue.add( msg );
		if( m_LogQue.size() > 1000 )
		{
			m_LogQue.remove(0);
		}
		
		unlockLogHandler();
		*/
		
		switch( logLevel )
		{
		case LOG_FATAL:
		case LOG_SEVERE:			
		case LOG_ASSERT:			
		case LOG_ERROR:
			Log.e( LOG_TAG, msg );
			break;
		case LOG_WARN:
			Log.w( LOG_TAG, msg );
			break;		
		case LOG_DEBUG:
			Log.d( LOG_TAG, msg );
			break;
			
		default:
			Log.i( LOG_TAG, msg ); 
		}	
	}
	
	//========================================================================
	public static void			appErr( int errorNum, String errMsg )
	{
		String formatedErrMsg;
		if( null != errMsg )
		{
			formatedErrMsg = "#App Error " +  errorNum +  " " + errMsg;
		}
		else
		{
			formatedErrMsg = "#App Error " +  errorNum;
		}
		
		logMsg( LOG_ERROR, formatedErrMsg );
	}
}

