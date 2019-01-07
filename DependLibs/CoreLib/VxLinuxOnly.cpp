//============================================================================
// Copyright (C) 2013 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================
#include "config_corelib.h"

#ifndef TARGET_OS_WINDOWS
#include "VxLinuxOnly.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
// helper
static void strreversehelper(char* begin, char* end)
{
    char aux;
    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}

//============================================================================
//! convert int to ascii string
char * itoa(int value, char* str, int base)
{
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    *wstr = 0;
    int sign;
    div_t res;

    // Validate base
    if (base<2 || base>35)
    {
        *wstr='\0';
        return str;
    }

    // Take care of sign
    if ((sign=value) < 0)
        value = -value;

    // Conversion. Number is reversed.
    do
    {
        res = div(value,base);
        *wstr++ = num[res.rem];
    }while( 0 != (value = res.quot) );
    if(sign<0)
        *wstr++='-';
    *wstr='\0';

    // Reverse string
    strreversehelper(str,wstr-1);
    return str;
}
//============================================================================
//! convert long to ascii string
char * ltoa(long value, char* str, int base)
{
    return itoa( (int)value, str, base );
}
//============================================================================
//! convert unsigned long to ascii string
char * ultoa(unsigned long value, char* str, int base)
{
    return itoa( (int)value, str, base );
}
//============================================================================
//! convert string to upper case
void strupr( char * pStr )
{
    while( * pStr )
    {
         * pStr = toupper( *pStr );
         pStr++;
    }
}
//============================================================================
//! convert string to lower case
void strlwr( char * pStr )
{
    while( * pStr )
    {
         * pStr = tolower( *pStr );
         pStr++;
    }
}
//============================================================================
//! case insensitive string compare
int stricmp( const char * pStr1, const char * pStr2 )
{
    return strcasecmp( pStr1, pStr2 );
}

//============================================================================
//! case insensitive string compare
int strnicmp( const char * pStr1, const char * pStr2, int n )
{
    return strncasecmp( pStr1, pStr2, n );
}

#endif // TARGET_OS_WINDOWS

