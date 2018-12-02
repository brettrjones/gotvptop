package com.p2pgotv.gotvstation;

import android.annotation.SuppressLint;

public class VxParseUtil
{
	
    
    //============================================================================
    public static String makeHttpLink( String strUrl )
    {
    	String strLink = "<a href=\"" + strUrl + "\">" + strUrl + "</a><br>";
    	return strLink;
    }

	//-----------------------------------------------------------
	// handle hex
	//-----------------------------------------------------------	
	//========================================================================
	private final static char[] m_as8HexChars = {
		    '0', '1', '2', '3', '4', '5', '6', '7',
		    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
		  };
	 
	//========================================================================
	public static byte[] hexStringToByteArray(String s) 
	{
	    int len = s.length();
	    byte[] data = new byte[len / 2];
	    for (int i = 0; i < len; i += 2) 
	    {
	        data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
	                             + Character.digit(s.charAt(i+1), 16));
	    }
	    
	    return data;
	}

	//========================================================================
	public static String byteArrayToHexString( byte[] bytes ) 
	{
	    char[] hexChars = new char[bytes.length * 2];
	    for ( int j = 0; j < bytes.length; j++ ) 
	    {
	        int v = bytes[j] & 0xFF;
	        hexChars[j * 2] = m_as8HexChars[v >>> 4];
	        hexChars[j * 2 + 1] = m_as8HexChars[v & 0x0F];
	    }
	    
	    return new String(hexChars);
	}
	
	//========================================================================
	// convert long to hex string without leading 0x
	public static String longToHexString(long s64Value) 
	{
		char[] hexs;
		int i;
		int c;

		hexs = new char[16];
		for (i = 0; i < 16; i++) 
		{
			c = (int)(s64Value & 0xf);
		    hexs[16-i-1] = m_as8HexChars[c];
		    s64Value = s64Value >> 4;
		}
		return new String(hexs);
	}
	
	//========================================================================
	// convert int to hex string without leading 0x
	public static String intToHexString(int s32Value) 
	{
		char[] hexs;
		int i;
		int c;

		hexs = new char[8];
		for (i = 0; i < 8; i++) 
		{
			c = (int)(s32Value & 0xf);
		    hexs[8-i-1] = m_as8HexChars[c];
		    s32Value = s32Value >> 4;
		}
		return new String(hexs);
	}
	
	//========================================================================
	// convert short to hex string without leading 0x
	public static String shortToHexString(short s16Value) 
	{
		char[] hexs;
		int i;
		int c;

		hexs = new char[4];
		for (i = 0; i < 4; i++) 
		{
			c = (int)(s16Value & 0xf);
		    hexs[4-i-1] = m_as8HexChars[c];
		    s16Value = (short) (s16Value >> 4);
		}
		return new String(hexs);
	}
	
	//========================================================================
	// convert short to hex string without leading 0x
	public static String byteToHexString(byte u8Value) 
	{
		char[] hexs;
		int i;
		int c;

		hexs = new char[2];
		for (i = 0; i < 2; i++) 
		{
			c = (int)(u8Value & 0xf);
		    hexs[2-i-1] = m_as8HexChars[c];
		    u8Value = (byte) (u8Value >> 4);
		}
		return new String(hexs);
	}
	
	//========================================================================
	@SuppressLint("DefaultLocale")
	public static long hexStringToLong(String hexadecimal) throws NumberFormatException
	{
	    char[] chars;
	    char c;
	    long value;
	    int i;

	    if (hexadecimal == null)
	    	throw new IllegalArgumentException();

	    chars = hexadecimal.toLowerCase().toCharArray();
	    if (chars.length != 16)
	    	throw new NumberFormatException("hexStringToLong: Incomplete hex value");

	    value = 0;
	    for (i = 0; i < 16; i++) 
	    {
	    	c = chars[i];
	    	if (c >= '0' && c <= '9') 
	    	{
	    		value = ((value << 4) | (0xff & (c - '0')));
	    	}
	    	else if (c >= 'a' && c <= 'f') 
	    	{
	    		value = ((value << 4) | (0xff & (c - 'a' + 10)));
	    	} 
	    	else 
	    	{
	    		throw new NumberFormatException("hexStringToLong: Invalid hex character: " + c);
	    	}
	    }
	    
	    return value;
	}

}
