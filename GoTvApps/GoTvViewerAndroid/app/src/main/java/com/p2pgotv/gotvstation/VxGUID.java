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

import java.util.UUID;

public class VxGUID implements Comparable<VxGUID> 
{
	//=== vars ===//
	long m_u64IdHiPart;
	long m_u64IdLoPart;
	
	//========================================================================
	VxGUID()
	{
		m_u64IdHiPart = 0;
		m_u64IdLoPart = 0;
	}
	
	//========================================================================
	VxGUID( long u64IdHiPart, long u64IdLoPart )
	{
		m_u64IdHiPart = u64IdHiPart;
		m_u64IdLoPart = u64IdLoPart;
	}
	
	//========================================================================
	public static VxGUID generateNewGUID()
	{
   		UUID uuidTmp = UUID.randomUUID(); 
   	 	return new VxGUID( uuidTmp.getMostSignificantBits(),  uuidTmp.getLeastSignificantBits() );
 	}
	
	//========================================================================
	public void initializeWithNewGUID()
	{
		UUID uuidTmp 	= UUID.randomUUID(); 
		m_u64IdHiPart 	= uuidTmp.getMostSignificantBits();
		m_u64IdLoPart 	= uuidTmp.getLeastSignificantBits();
	}
	
	//========================================================================
	@Override
	public int hashCode() 
	{ 
		return (int) m_u64IdLoPart; 
	}
	
	//========================================================================
	//@Override
	public int compareTo( VxGUID another ) 
	{
		if( (another == this) 
			|| ((another.m_u64IdHiPart == this.m_u64IdHiPart) && (another.m_u64IdLoPart == this.m_u64IdLoPart)) )
		{
			return 0;
		}
		
		if( m_u64IdLoPart >  another.m_u64IdLoPart )
		{
			return 1;
		}
		
		return -1;
	}
	
	//========================================================================
	// required override for has lookup
	@Override 
	public boolean equals( Object o ) 
	{ 
		if( o == null || !( o instanceof VxGUID ) ) 
			return false; 
		if( o == this ) 
			return true; 
		VxGUID cp = VxGUID.class.cast( o ); 
		return ( ( cp.m_u64IdHiPart == this.m_u64IdHiPart ) 
				&& ( cp.m_u64IdLoPart == this.m_u64IdLoPart ) ); 
	} 
	
	//========================================================================
	 @Override 
    public String toString() 
    { 
       return toOnlineIdHexString(); 
    } 

	//========================================================================
	public boolean		isOnlineIdValid()					
	{ 
		return ((m_u64IdLoPart != 0 ) && (m_u64IdHiPart != 0 ));
	}
	
	//========================================================================
	public boolean		isVxGUIDValid()					
	{ 
		return ((m_u64IdLoPart != 0 ) && (m_u64IdHiPart != 0 ));
	}
	
	//========================================================================
	//! return id as string
	public String		toOnlineIdHexString()		
	{ 
		String strId = VxParseUtil.longToHexString(m_u64IdHiPart) + VxParseUtil.longToHexString(m_u64IdLoPart);
		return strId; 
	} 
	
	//========================================================================
	public String describeId()
	{
		String strId = " 0x" + VxParseUtil.longToHexString(m_u64IdHiPart) + " 0x" + VxParseUtil.longToHexString(m_u64IdLoPart);
		return strId;
	}	
	
	//========================================================================
	//! set online id by converting hex string into U128
	//public void			fromOnlineIdHexString( String pHexString );
	
	//========================================================================
	//! get low part of online id
	long getOnlineIdLoPart()							{ return m_u64IdLoPart; }
	
	//========================================================================
	//! get high part of online id
	long getOnlineIdHiPart()							{ return m_u64IdHiPart; }
	
	//========================================================================
	//! set users online id
	void setOnlineId( VxGUID oId )					
	{ 
		m_u64IdHiPart = oId.m_u64IdHiPart; 
		m_u64IdLoPart = oId.m_u64IdLoPart; 
	}
	
	//========================================================================
	//! set users online id
	void setOnlineId( long u64HiPart, long u64LoPart )	
	{ 
		m_u64IdHiPart = u64HiPart; 
		m_u64IdLoPart = u64LoPart; 
	}
};

