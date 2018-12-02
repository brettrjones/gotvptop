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

public class VxSha1Hash 
{
	private static final int 	SHA1_HASH_LEN 					= 20;
	
	private byte				m_HashId[]						= new byte[ SHA1_HASH_LEN ];
	
	byte[]						getHashData()					{ return m_HashId; }
	
	//========================================================================
	VxSha1Hash()
	{
		for( int i = 0; i < SHA1_HASH_LEN; i++ )
		{
			m_HashId[i] = 0;
		}
	}
	
	//========================================================================
	void setHashData( byte[] hashData )
	{
		if( null != hashData )
		{
			for( int i = 0; i < SHA1_HASH_LEN; i++ )
			{
				m_HashId[i] = hashData[i];
			}			
		}
	}
	
	//========================================================================
	boolean	isHashValid()
	{
		for( int i = 0; i < SHA1_HASH_LEN; i++ )
		{
			if( 0 != m_HashId[i] )
			{
				return true;
			}
		}

		return false;		
	}
	
	//========================================================================
	boolean	isEqualTo( byte[] hashData )
	{
		if( null == hashData )
		{		
			return false;
		}
		
		for( int i = 0; i < SHA1_HASH_LEN; i++ )
		{
			if( hashData[i] != m_HashId[i] )
			{
				return false;
			}
		}	
		
		return true;
	}	
}
