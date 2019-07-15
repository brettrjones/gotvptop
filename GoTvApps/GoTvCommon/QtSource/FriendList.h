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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "Friend.h"

class FriendList
{
public:
	FriendList();
	virtual ~FriendList();

	void						setFriendViewType( EFriendViewType eWhichFriendsToShow );
	EFriendViewType				getFriendViewType( void );

	virtual void				onFriendAdded( VxNetIdent * poFriend ) {};
	virtual void				onFriendUpdated( VxNetIdent * poFriend ) {};
	virtual void				onFriendRemoved( VxNetIdent * poFriend ) {};

	//! find friend by id.. returns NULL if not found
	Friend *					findFriend( VxGUID& oId );

protected:
	//! update friend in list
	void						updateFriendList( VxNetIdent * netIdent, bool sessionTimeChange );
	//! remove friend from list.. return non zero if should not be removed
	RCODE						removeFriendFromList( VxGUID& oId );

	//=== vars ===//
	std::vector<Friend *>		m_aoFriends;
	EFriendViewType				m_eFriendViewType;
};