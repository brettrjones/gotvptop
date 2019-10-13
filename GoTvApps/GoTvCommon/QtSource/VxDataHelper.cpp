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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "VxDataHelper.h"

#include <CoreLib/sqlite3.h>
#include <PktLib/VxCommon.h>
#include <NetLib/NetHostSetting.h>

#include <stdio.h>

namespace
{
	std::string 		DATABASE_NAME 					= "gotvptop_acct.db";
	const int 			DATABASE_VERSION 				= 1;

	std::string 		TABLE_LAST_LOGIN	 			= "last_login";
	std::string 		TABLE_ACCOUNT_LOGIN	 			= "account_login";
	std::string 		TABLE_ACCOUNT_PROFILE			= "account_profile";
	std::string 		TABLE_FRIENDS	 				= "friends";

	std::string 		TABLE_LAST_ANCHOR_SETTING	 	= "last_anchor_setting";
	std::string 		TABLE_ANCHOR_SETTINGS	 		= "anchor_settings";

	std::string 		COLUMNS_LAST_LOGIN				= " online_name ";
	std::string 		CREATE_COLUMNS_LAST_LOGIN		= " (id INTEGER PRIMARY KEY AUTOINCREMENT, online_name  TEXT) ";
	std::string 		COLUMNS_ACOUNT_LOGIN			= "online_id,online_name,ident";
	std::string 		CREATE_COLUMNS_ACOUNT_LOGIN		= " (online_id TEXT PRIMARY KEY, online_name TEXT, ident BLOB)";
	std::string 		COLUMNS_ACOUNT_PROFILE  		= "online_id,greeting,about,picture,url1,url2,url3,donation";
	std::string 		CREATE_COLUMNS_ACOUNT_PROFILE  	= " (online_id TEXT PRIMARY KEY, greeting TEXT, greet TEXT, about TEXT, picture TEXT, url1 TEXT, url2 TEXT, url3 TEXT, donation TEXT) ";
	std::string 		COLUMNS_FRIENDS  				= "online_id,his_friendship,my_friendship,ident";
	std::string 		CREATE_COLUMNS_FRIENDS  		= " (online_id TEXT PRIMARY KEY, his_friendship TINYINT, my_friendship TINYINT, ident BLOB ) ";

	std::string 		CREATE_COLUMNS_LAST_ANCHOR_SETTING		= " (anchor_setting_name TEXT PRIMARY KEY) ";
	std::string 		COLUMNS_LAST_ANCHOR_SETTING		= "anchor_setting_name";

	std::string 		CREATE_COLUMNS_ANCHOR_SETTINGS	= " (anchor_setting_name TEXT PRIMARY KEY, network_name TEXT, anchor_url TEXT, connect_test_url TEXT, is_anchor_node INTEGER, exclude_me INTEGER )  ";
	std::string 		COLUMNS_ANCHOR_SETTINGS			= "anchor_setting_name,network_name,anchor_url,connect_test_url,is_anchor_node,exclude_me";
}

//============================================================================
//=== globals ===//
//============================================================================
VxDataHelper g_oDataHelper;

//============================================================================
VxDataHelper::VxDataHelper()
: DbBase( "DataHelperDb" )
{
}

//============================================================================
VxDataHelper::~VxDataHelper()
{
}

//============================================================================
//! create tables in database 
RCODE VxDataHelper::onCreateTables( int iDbVersion )
{
    std::string exeStr = "CREATE TABLE " + TABLE_LAST_LOGIN + CREATE_COLUMNS_LAST_LOGIN;
    RCODE rc = sqlExec(exeStr);
    exeStr = "CREATE TABLE " + TABLE_ACCOUNT_LOGIN + CREATE_COLUMNS_ACOUNT_LOGIN;
    rc |= sqlExec( exeStr );
    exeStr = "CREATE TABLE " + TABLE_ACCOUNT_PROFILE + CREATE_COLUMNS_ACOUNT_PROFILE;
    rc |= sqlExec( exeStr );
    exeStr = "CREATE TABLE " + TABLE_FRIENDS + CREATE_COLUMNS_FRIENDS;
    rc |= sqlExec( exeStr );
	exeStr = "CREATE TABLE " + TABLE_LAST_ANCHOR_SETTING + CREATE_COLUMNS_LAST_ANCHOR_SETTING;
	rc |= sqlExec( exeStr );
	exeStr = "CREATE TABLE " + TABLE_ANCHOR_SETTINGS + CREATE_COLUMNS_ANCHOR_SETTINGS;
	rc |= sqlExec( exeStr );
	return rc;
}

//============================================================================
// delete tables in database
RCODE VxDataHelper::onDeleteTables( int oldVersion ) 
{
    RCODE rc = sqlExec("DROP TABLE IF EXISTS last_login" );
    rc |= sqlExec("DROP TABLE IF EXISTS account_login" );
    rc |= sqlExec("DROP TABLE IF EXISTS account_profile" );
    rc |= sqlExec("DROP TABLE IF EXISTS friends" );
	rc |= sqlExec("DROP TABLE IF EXISTS last_anchor_setting" );
	rc |= sqlExec("DROP TABLE IF EXISTS anchor_settings" );
	return rc;
}

//============================================================================
//! return true if online id exists in table
bool VxDataHelper::onlineUidExistsInTable( VxGUID& onlineId, std::string& strTableName )
{
	bool bExists = false;
	std::string strOnlineIdHex = onlineId.toVxGUIDHexString();

	DbCursor * cursor = startQueryInsecure(  "SELECT * FROM %s WHERE online_id='%s'", strTableName.c_str(), strOnlineIdHex.c_str() );
	if( NULL != cursor )
	{
		if( cursor->getNextRow() )
		{
			bExists = true;
		}
	}
	cursor->close();
	return bExists;
}

//=========================================================================
// login
//=========================================================================
//============================================================================
//! update last login name
bool VxDataHelper::updateLastLogin( const char * pThingName ) 
{
	DbBindList bindList( pThingName );
	RCODE rc = sqlExec(  "DELETE FROM last_login" );
	rc |= sqlExec(  "INSERT INTO last_login (online_name) values(?)", bindList );
	return rc ? false : true;
}

//============================================================================
//! get last login name.. return "" if doesn't exist
std::string VxDataHelper::getLastLogin() 
{
	std::string strThingName = "";
	DbCursor * cursor = startQueryInsecure("SELECT * FROM %s", TABLE_LAST_LOGIN.c_str() );
	if( NULL != cursor )
	{
		if(  cursor->getNextRow() )
		{
			strThingName = cursor->getString(1);
		}

		cursor->close();
	}

	return strThingName;
}

//=========================================================================
// accounts
//=========================================================================
//============================================================================
//! insert new account
bool VxDataHelper::insertAccount( VxNetIdent& oUserAccount ) 
{
	std::string strOnlineNameHex = oUserAccount.getMyOnlineId().toVxGUIDHexString();
	DbBindList bindList( oUserAccount.getOnlineName() );
	sqlExec(  "DELETE FROM account_login WHERE online_name=?", bindList );
	bindList.add( &oUserAccount, sizeof( VxNetIdent ) );
	bindList.add( strOnlineNameHex.c_str() );

	RCODE rc = sqlExec( "INSERT INTO account_login (online_name,ident,online_id) values(?,?,?)", bindList );
	if( rc )
	{
		LogMsg( LOG_ERROR, "VxDataHelper::insertAccount: ERROR %d %s\n", rc, sqlite3_errmsg(m_Db) );
	}
	
	return rc ? false : true;
}

//============================================================================
//! update existing account
bool VxDataHelper::updateAccount( VxNetIdent& oUserAccount ) 
{
	bool bResult = false;
	sqlite3_stmt * poSqlStatement;
	char SQL_Statement[2048];
	std::string strOnlineNameHex = oUserAccount.getMyOnlineId().toVxGUIDHexString();

	sprintf(SQL_Statement, "UPDATE account_login SET online_name=?, ident=? WHERE online_id='%s'",
			strOnlineNameHex.c_str() );
	RCODE rc = dbOpen();
	if( 0 == rc )
	{
		if( SQLITE_OK == sqlite3_prepare(m_Db, SQL_Statement, (int)strlen(SQL_Statement), &poSqlStatement, NULL) )
		{
			if( (SQLITE_OK == sqlite3_bind_text( poSqlStatement, 1, oUserAccount.getOnlineName(), (int)strlen( oUserAccount.getOnlineName() ), NULL ) ) &&
				(SQLITE_OK == sqlite3_bind_blob( poSqlStatement, 2, &oUserAccount, sizeof( VxNetIdent ), NULL ) ) )
			{
				if( SQLITE_DONE == sqlite3_step( poSqlStatement ) )
				{
					if( SQLITE_OK == sqlite3_finalize( poSqlStatement ) )
					{
						bResult = true;
					}
				}
				else
				{
					LogMsg( LOG_ERROR, "VxDataHelper::updateAccount: ERROR %s stepping\n", sqlite3_errmsg(m_Db) );
				}
			}
			else
			{
				LogMsg( LOG_ERROR, "VxDataHelper::updateAccount: ERROR %s\n", sqlite3_errmsg(m_Db) );
			}
		}
		else
		{
			LogMsg( LOG_ERROR, "VxDataHelper::updateAccount: ERROR %s\n", sqlite3_errmsg(m_Db) );
		}

        sqlite3_exec( m_Db, "END", NULL, NULL, NULL );
        dbClose();
	}

	return bResult;
}

//============================================================================
//! retrieve account by name
bool VxDataHelper::getAccountByName(const char * name, VxNetIdent& oUserAccount ) 
{
    if( NULL == name )
    {
        LogMsg( LOG_ERROR, "VxDataHelper::getAccountByName: null name\n" );
        return false;
    }

	bool bResult = false;
	DbCursor * cursor = startQueryInsecure( "SELECT ident FROM account_login WHERE online_name='%s'", name );
	if( NULL != cursor )
	{
		if( cursor->getNextRow() )
		{
			int iBlobLen = 0;
			VxNetIdent * netIdent = (VxNetIdent *)cursor->getBlob(0, &iBlobLen );
			if( iBlobLen == sizeof( VxNetIdent ) )
			{
				memcpy( &oUserAccount, netIdent, sizeof( VxNetIdent ));
				bResult = true;
			}
			else
			{
				LogMsg( LOG_ERROR, "VxDataHelper::getAccountByName: incorrect blob len in db.. was code changed????\n");
				cursor->close();
				// remove the invalid blob
				DbBindList bindList( name );
				RCODE rc = sqlExec(  "DELETE FROM account_login WHERE online_name=?", bindList );
				if( rc )
				{
					LogMsg( LOG_ERROR, "VxDataHelper::getAccountByName: could not remove login by name %s\n", name );
				}

				return false;
			}
		}

		cursor->close();
	}

	return bResult;
}

//============================================================================
//! remove account by name
bool VxDataHelper::removeAccountByName(const char * name ) 
{
	DbBindList bindList( name );
	RCODE rc = sqlExec( "DELETE FROM account_login WHERE online_name=?", bindList );
	if( rc == SQLITE_OK )
	{
		return true;
	}

	return false;
}

//=========================================================================
// friends
//=========================================================================
//============================================================================
//! get all known about friend
bool VxDataHelper::getUserProfile( VxNetIdent& oUserAccount, UserProfile& oProfile ) 
{
	bool bResult = false;
	std::string strOnlineIdHex = oUserAccount.getMyOnlineId().toVxGUIDHexString();

	DbCursor * cursor = startQueryInsecure("SELECT greeting,about,picture,url1,url2,url3,donation FROM account_profile WHERE online_id='%s'",
		strOnlineIdHex.c_str() );
	if( NULL != cursor )
	{
		if( cursor->getNextRow() )
		{
			if( 0 != cursor->getString(0) )
			{
				oProfile.m_strGreeting = cursor->getString(0);
				if( 0 == oProfile.m_strGreeting.length() )
				{
					oProfile.m_strGreeting = oUserAccount.getOnlineDescription();
				}
			}
			else
			{
				oProfile.m_strGreeting = oUserAccount.getOnlineDescription();
			}

			if( 0 != cursor->getString(1) )
			{
				oProfile.m_strAboutMe = cursor->getString(1);
			}
			else
			{
				oProfile.m_strAboutMe = "";
			}

			if( 0 != cursor->getString(2) )
			{
				oProfile.m_strPicturePath = cursor->getString(2);
			}
			else
			{
				oProfile.m_strPicturePath = "";
			}

			if( 0 != cursor->getString(3) )
			{
				oProfile.m_strUrl1 = cursor->getString(3);
			}
			else
			{
				oProfile.m_strUrl1 = "";
			}

			if( 0 != cursor->getString(4) )
			{
				oProfile.m_strUrl2 = cursor->getString(4);
			}
			else
			{
				oProfile.m_strUrl2 = "";
			}

			if( 0 != cursor->getString(5) )
			{
				oProfile.m_strUrl3 = cursor->getString(5);
			}
			else
			{
				oProfile.m_strUrl3 = "";
			}

            if( 0 != cursor->getString( 6 ) )
            {
                oProfile.m_strDonation = cursor->getString( 6 );
            }
            else
            {
                oProfile.m_strDonation = "";
            }

			bResult = true;
		}

		cursor->close();
	}

	return bResult;
}

//============================================================================
//! update friend profile
bool VxDataHelper::updateUserProfile( VxNetIdent& oUserAccount, UserProfile& oProfile ) 
{
	RCODE rc = 0;
	std::string strOnlineIdHex = oUserAccount.getMyOnlineId().toVxGUIDHexString();
	DbBindList bindList( (const char *)oProfile.m_strGreeting.toUtf8().constData() );
	bindList.add( (const char *)oProfile.m_strAboutMe.toUtf8().constData() );
	bindList.add( (const char *)oProfile.m_strPicturePath.toUtf8().constData() );
	bindList.add( (const char *)oProfile.m_strUrl1.toUtf8().constData() );
	bindList.add( (const char *)oProfile.m_strUrl2.toUtf8().constData() );
	bindList.add( (const char *)oProfile.m_strUrl3.toUtf8().constData() );
    bindList.add( (const char *)oProfile.m_strDonation.toUtf8().constData() );
	bindList.add( strOnlineIdHex.c_str() );

	if( onlineUidExistsInTable( oUserAccount.getMyOnlineId(), TABLE_ACCOUNT_PROFILE ))
	{
		DbBindList bindList2( strOnlineIdHex.c_str() );
		bindList2.add( oUserAccount.getMyOnlineIdHiPart() );
		rc = sqlExec(  "DELETE FROM account_profile WHERE online_id=?", bindList2 );

		//rc = sqlExec( "UPDATE account_profile SET greeting=?, about=?, picture=?, url1=?, url2=?, url3=? WHERE online_id=?", bindList );
	}
	
	rc |= sqlExec( "INSERT INTO account_profile (greeting,about,picture,url1,url2,url3,donation,online_id) values(?,?,?,?,?,?,?,?)", bindList );


	return ( 0 == rc ) ? true : false;
}

//============================================================================
//! get list of friend with give friendship
void VxDataHelper::getFriendList(uint8_t u8MyFrienship,  std::vector<VxNetIdent>& aoIdent ) 
{
    DbCursor * cursor = startQueryInsecure("SELECT ident FROM friends WHERE my_frienship = %d;", u8MyFrienship );
	VxNetIdent oIdent;
	if( NULL != cursor )
	{
		while( cursor->getNextRow() ) 
		{
			int iBlobLen = 0;
			VxNetIdent * netIdent = (VxNetIdent *)cursor->getBlob(0, &iBlobLen );
			vx_assert( iBlobLen == sizeof( VxNetIdent ));
			memcpy( &oIdent, netIdent, sizeof( VxNetIdent ));
			aoIdent.push_back(oIdent); 
		}

		cursor->close();
	}
}

//============================================================================
//! update net info about friend
bool VxDataHelper::updateFriend( VxNetIdent& oIdent ) 
{
	RCODE rc;
	std::string strOnlineIdHex = oIdent.getMyOnlineId().toVxGUIDHexString();
	DbBindList bindList( oIdent.getHisFriendshipToMe() );
	bindList.add( oIdent.getMyFriendshipToHim() );
	bindList.add( &oIdent, sizeof( VxNetIdent ) );
	bindList.add( strOnlineIdHex.c_str() );

	if( onlineUidExistsInTable( oIdent.getMyOnlineId(), TABLE_FRIENDS ))
	{
		rc = sqlExec( "UPDATE friends SET his_friendship=?, my_friendship=?, ident=? WHERE online_id=?", bindList );
	}
	else
	{
		rc = sqlExec( "INSERT INTO friends (his_friendship,my_friendship,ident,online_id) values(?,?,?,?)", bindList );
	}

	return ( 0 == rc ) ? true : false;
}


//============================================================================
bool VxDataHelper::updateNetHostSetting( NetHostSetting& anchorSetting )
{
	removeNetHostSettingByName( anchorSetting.getNetHostSettingName().c_str() );

	DbBindList bindList( anchorSetting.getNetHostSettingName().c_str() );
	bindList.add( anchorSetting.getNetworkKey().c_str() );
	bindList.add( anchorSetting.getNetHostWebsiteUrl().c_str() );
	bindList.add( anchorSetting.getNetServiceWebsiteUrl().c_str() );
	bindList.add( anchorSetting.getIsThisNodeAnNetHost() );
	bindList.add( anchorSetting.getExcludeMeFromNetHostList() );

	RCODE rc = sqlExec( "INSERT INTO anchor_settings (anchor_setting_name,network_name,anchor_url,connect_test_url,is_anchor_node,exclude_me) values(?,?,?,?,?,?)", bindList );
	return ( 0 == rc ) ? true : false;
}

//============================================================================
bool VxDataHelper::getNetHostSettingByName( const char * name, NetHostSetting& anchorSetting )
{
	bool bResult = false;
	DbCursor * cursor = startQueryInsecure( "SELECT * FROM anchor_settings WHERE anchor_setting_name='%s'", name );
	if( NULL != cursor )
	{
		if( cursor->getNextRow() )
		{
			anchorSetting.setNetHostSettingName( name );
			anchorSetting.setNetworkKey( cursor->getString(1) );
			anchorSetting.setNetHostWebsiteUrl( cursor->getString(2) );
			anchorSetting.setNetServiceWebsiteUrl( cursor->getString(3) );
			anchorSetting.setIsThisNodeAnNetHost(  ( 0 == cursor->getS32(4) ) ? false : true );
			anchorSetting.setExcludeMeFromNetHostList(  ( 0 == cursor->getS32(5) ) ? false : true );

			bResult = true;
		}

		cursor->close();
	}

	return bResult;
}

//============================================================================
bool VxDataHelper::getAllNetHostSettings( std::vector<NetHostSetting>& anchorSettingList )
{
	bool bResult = false;
	DbCursor * cursor = startQueryInsecure( "SELECT * FROM anchor_settings" );
	if( NULL != cursor )
	{
		while( cursor->getNextRow() )
		{
			NetHostSetting anchorSetting;

			anchorSetting.setNetHostSettingName( cursor->getString(0) );
			anchorSetting.setNetworkKey( cursor->getString(1) );
			anchorSetting.setNetHostWebsiteUrl( cursor->getString(2) );
			anchorSetting.setNetServiceWebsiteUrl( cursor->getString(3) );
			anchorSetting.setIsThisNodeAnNetHost(  ( 0 == cursor->getS32(4) ) ? false : true );
			anchorSetting.setExcludeMeFromNetHostList(  ( 0 == cursor->getS32(5) ) ? false : true );
			anchorSettingList.push_back( anchorSetting );

			bResult = true;
		}

		cursor->close();
	}

	return bResult;
}

//============================================================================
bool VxDataHelper::removeNetHostSettingByName( const char * name )
{
	DbBindList bindList( name );
	RCODE rc = sqlExec(  "DELETE FROM anchor_settings WHERE anchor_setting_name=?", bindList );
	return rc ? false : true;
}

//============================================================================
bool VxDataHelper::updateLastNetHostSettingName( const char * name )
{
	DbBindList bindList( name );
	RCODE rc = sqlExec(  "DELETE FROM last_anchor_setting" );
	rc |= sqlExec(  "INSERT INTO last_anchor_setting (anchor_setting_name) values(?)", bindList );
	return rc ? false : true;
}

//============================================================================
std::string VxDataHelper::getLastNetHostSettingName( void )
{
	std::string strSettingName = "";
	DbCursor * cursor = startQueryInsecure("SELECT * FROM %s", TABLE_LAST_ANCHOR_SETTING.c_str() );
	if( NULL != cursor )
	{
		if( cursor->getNextRow() )
		{
			if( cursor->getString(0) )
			{
				strSettingName = cursor->getString(0);
			}
		}

		cursor->close();
	}

	return strSettingName;
}
