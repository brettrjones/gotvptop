#pragma once
//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include <PktLib/VxCommon.h>

#include <QString>

class Friend : public VxNetIdent
{
public:
	Friend();
	~Friend(); //BRJ do not make virtual so we can get away with casting VxNetIdent to Friend even though not really a Friend object

	void getFriendName( QString& strName )					{ strName.fromUtf8( getOnlineName() ); }
    void setFriendName( QString& strName )					{ setOnlineName( strName.toUtf8() );}
	void getFriendDescription( QString& strDescription )	{ strDescription.fromUtf8( getOnlineDescription() ); };
    void setFriendDescription( QString& strDescription )	{ setOnlineDescription( strDescription.toUtf8() );};
};
