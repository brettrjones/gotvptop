//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.graphics.Bitmap;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class DataHelper  extends SQLiteOpenHelper
{
    //=== constants ===//
	private static final String 	LOG_TAG 						= "DataHelper";
	private static final String 	DATABASE_NAME 					= "myp2p_acct.db";
	private static final int 		DATABASE_VERSION 				= 4;
   
	private static final String 	TABLE_LAST_LOGIN	 			= "last_login";
	private static final String 	TABLE_ACCOUNT_LOGIN	 			= "account_login";
	private static final String 	TABLE_ACCOUNT_PROFILE			= "account_profile";
	private static final String 	TABLE_PLUGIN	 				= "plugins";
	private static final String 	TABLE_FRIENDS	 				= "friends";
	private static final String 	TABLE_OPTIONS	 				= "options";
	private static final String 	TABLE_LAST_ANCHOR_SETTING	 	= "last_anchor_setting";
	private static final String 	TABLE_ANCHOR_SETTINGS	 		= "anchor_settings";
	private static final String 	TABLE_CONTACT_INFO	 			= "contact_info";

	private static final String		COLUMNS_LAST_LOGIN				= " name ";
	private static final String		CREATE_COLUMNS_LAST_LOGIN		= " (id INTEGER PRIMARY KEY AUTOINCREMENT, name  TEXT) ";
	private static final String		COLUMNS_ACOUNT_LOGIN			= "uid_lopart,uid_hipart,name,desc,friend_match,search_flags,shared_files,ip_port,local_ipv4,online_ipv4,online_ipv6,permissions,truth_cnt,dare_cnt,rejected_truth_cnt,rejected_dare_cnt,network";
	
	private static final String		CREATE_COLUMNS_ACOUNT_LOGIN		= " (id INTEGER PRIMARY KEY AUTOINCREMENT, uid_lopart BIGINT, uid_hipart BIGINT, name TEXT, desc TEXT, friend_match TINYINT, search_flags TINYINT, shared_files TINYINT, " +
																			"ip_port INTEGER, local_ipv4 TEXT, online_ipv4 TEXT, online_ipv6 TEXT, permissions BLOB, " +
																			"truth_cnt INTEGER, dare_cnt INTEGER, rejected_truth_cnt INTEGER, rejected_dare_cnt INTEGER, network TEXT ) ";
 	
	private static final String		COLUMNS_ACOUNT_PROFILE  		= "uid_lopart,uid_hipart,greeting,about,picture,url1,url2,url3";
	private static final String		CREATE_COLUMNS_ACOUNT_PROFILE  	= " (id INTEGER PRIMARY KEY AUTOINCREMENT, uid_lopart BIGINT, uid_hipart BIGINT, greeting TEXT, greet TEXT, about TEXT, picture TEXT, url1 TEXT, url2 TEXT, url3 TEXT) ";

	private static final String		CREATE_COLUMNS_PLUGIN  			= " (id INTEGER PRIMARY KEY AUTOINCREMENT, plugin_id, permission INTEGER, share_folder TEXT) ";
	private static final String		COLUMNS_FRIENDS_UPDATE  		= "name,desc,friend_match,search_flags,ip_port,ip_address,permissions,network,his_friendship,my_friendship,last_contact,truth_cnt,dare_cnt,rejected_truth_cnt,rejected_dare_cnt";
	private static final String		COLUMNS_FRIENDS  				= "uid_lopart,uid_hipart," + COLUMNS_FRIENDS_UPDATE;
	
	private static final String		CREATE_COLUMNS_FRIENDS  		= " (id INTEGER PRIMARY KEY AUTOINCREMENT, uid_lopart BIGINT, uid_hipart BIGINT, name TEXT, desc TEXT, friend_match TINYINT, search_flags TINYINT, shared_files TINYINT," +
																			"ip_port INTEGER, local_ipv4 INTEGER, online_ipv4 INTEGER, online_ipv6 INTEGER, permissions BLOB, " +
																			"his_friendship TINYINT, my_friendship TINYINT, last_contact INTEGER, truth_cnt INTEGER, dare_cnt INTEGER, rejected_truth_cnt INTEGER, rejected_dare_cnt INTEGER, network TEXT ) ";
	//private static final String		COLUMNS_OPTIONS  				= "setting,value";
	private static final String		CREATE_COLUMNS_OPTIONS  		= " (id INTEGER PRIMARY KEY AUTOINCREMENT, setting TEXT, value TEXT ) ";

	private static final String		CREATE_COLUMNS_LAST_ANCHOR_SETTING		= " (anchor_setting_name TEXT PRIMARY KEY) ";

	private static final String		CREATE_COLUMNS_ANCHOR_SETTINGS	= " (anchor_setting_name TEXT PRIMARY KEY, network_name TEXT, anchor_url TEXT, connect_test_url TEXT, is_anchor_node INTEGER ) ";
	
	private static final String		CREATE_COLUMNS_CONTACT_INFO		= " (uid_lopart BIGINT, uid_hipart BIGINT, display_name TEXT, phone_num TEXT, user_notes TEXT, avatar_pic BLOB, pic_file_name TEXT ) ";
	private static final String		COLUMNS_CONTACT_INFO			= "uid_lopart,uid_hipart,display_name,phone_num,user_notes,avatar_pic,pic_file_name";
   
    //========================================================================
   	//=== methods ===//
    //========================================================================
	// manage open/create/update database
	public DataHelper(Context context) 
	{
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
	}

	//========================================================================
    @Override
    public void onCreate(SQLiteDatabase db) 
    {
    	createTables(db);
    }

    //========================================================================
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) 
    {
    	Log.w(LOG_TAG, "Upgrading database, this will drop tables and recreate.");
    	DataHelper.deleteTables(db);
        onCreate(db);
    }
    
    //========================================================================
    public SQLiteDatabase getMyWriteableDb()
    {
    	return this.getWritableDatabase();
    }

    //========================================================================
    public SQLiteDatabase getMyReadableDb()
    {
    	return this.getReadableDatabase();
    }
    
    //========================================================================
	void createTables( SQLiteDatabase db ) 
	{
    	db.execSQL("CREATE TABLE " + TABLE_LAST_LOGIN + CREATE_COLUMNS_LAST_LOGIN);
    	db.execSQL("CREATE TABLE " + TABLE_ACCOUNT_LOGIN + CREATE_COLUMNS_ACOUNT_LOGIN);
    	db.execSQL("CREATE TABLE " + TABLE_ACCOUNT_PROFILE + CREATE_COLUMNS_ACOUNT_PROFILE);
    	db.execSQL("CREATE TABLE " + TABLE_PLUGIN + CREATE_COLUMNS_PLUGIN );
    	db.execSQL("CREATE TABLE " + TABLE_FRIENDS + CREATE_COLUMNS_FRIENDS );
    	db.execSQL("CREATE TABLE " + TABLE_OPTIONS + CREATE_COLUMNS_OPTIONS );	
    	db.execSQL("CREATE TABLE " + TABLE_LAST_ANCHOR_SETTING + CREATE_COLUMNS_LAST_ANCHOR_SETTING );	
    	db.execSQL("CREATE TABLE " + TABLE_ANCHOR_SETTINGS + CREATE_COLUMNS_ANCHOR_SETTINGS );	
    	db.execSQL("CREATE TABLE " + TABLE_CONTACT_INFO + CREATE_COLUMNS_CONTACT_INFO );
    }
	
    //========================================================================
	static void deleteTables( SQLiteDatabase db ) 
	{
    	db.execSQL("DROP TABLE IF EXISTS " + TABLE_LAST_LOGIN );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ACCOUNT_LOGIN );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ACCOUNT_PROFILE );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PLUGIN );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_FRIENDS );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_OPTIONS );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_LAST_ANCHOR_SETTING );
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ANCHOR_SETTINGS );
    	db.execSQL("DROP TABLE IF EXISTS " + TABLE_CONTACT_INFO );
    }

    //========================================================================
	public void deleteAllData() 
	{
		SQLiteDatabase db=this.getWritableDatabase();
		db.delete(TABLE_LAST_LOGIN, null, null);
		db.delete(TABLE_ACCOUNT_LOGIN, null, null);
		db.delete(TABLE_ACCOUNT_PROFILE, null, null);
		db.delete(TABLE_PLUGIN, null, null);
		db.delete(TABLE_FRIENDS, null, null);
		db.delete(TABLE_OPTIONS, null, null);
		db.delete(TABLE_LAST_ANCHOR_SETTING, null, null);
		db.delete(TABLE_ANCHOR_SETTINGS, null, null);
		db.delete(TABLE_CONTACT_INFO, null, null);
	}
		
	//=========================================================================
    public boolean updateContactInfo( ContactInfo contactInfo ) 
    {
    	long rowsAffected 	= 0;
		SQLiteDatabase db 	= this.getWritableDatabase();
		VxGUID onlineId 	= contactInfo.getOnlineId();
        ContentValues args 	= new ContentValues();
        putContactInfo( args, contactInfo );
        
		if( onlineUidExistsInTable( db, onlineId.m_u64IdLoPart, onlineId.m_u64IdHiPart, TABLE_CONTACT_INFO ))
		{
			// update
	        rowsAffected = db.update( TABLE_CONTACT_INFO, 
					        			args, 
					        			"uid_lopart = " + onlineId.m_u64IdLoPart + " AND uid_hipart = " + onlineId.m_u64IdHiPart,
					        			null );
		}
		else
		{
			// insert
	        rowsAffected = db.insert( TABLE_CONTACT_INFO, null, args );
		}
		
		if( 0 == rowsAffected )
		{
			Log.w( LOG_TAG, "updateContactInfo database ERROR ." + rowsAffected );		
		}
		
		return true;
    }
    
	//=========================================================================
    public boolean getContactInfo( long idLoPart, long idHiPart, ContactInfo contactInfo ) 
    {
    	boolean result 		= false;
		SQLiteDatabase db 	= this.getReadableDatabase();
		VxGUID onlineId 	= new VxGUID( idLoPart, idHiPart );
		if( onlineUidExistsInTable( db, onlineId.m_u64IdLoPart, onlineId.m_u64IdHiPart, TABLE_CONTACT_INFO ))
		{
			Cursor cursor = db.rawQuery("SELECT " + COLUMNS_CONTACT_INFO + " FROM " + TABLE_CONTACT_INFO +
		    		  " WHERE uid_lopart = " + onlineId.m_u64IdLoPart + " AND uid_hipart = " + onlineId.m_u64IdHiPart, null );
			if( null != cursor )
			{
				if (cursor.getCount() > 0 )
				{
					cursor.moveToFirst();
					result = true;
				}
				
			    cursor.close();				
			}
		}
		
		return result;
    }
    
	//========================================================================
	//! sets values of FriendBase into args returns args put count
	//! NOTE: does not put ids in args
	int putContactInfo( ContentValues args, ContactInfo contactInfo )
	{
		args.put("uid_lopart", 			contactInfo.getOnlineId().getOnlineIdLoPart() );
	    args.put("uid_hipart", 			contactInfo.getOnlineId().getOnlineIdHiPart());
	    args.put("display_name", 		contactInfo.getDisplayName() );
	    args.put("mobile_phone_num", 	contactInfo.getMobilePhoneNum() );
	    args.put("user_notes", 			contactInfo.getUserNotes() );
	    
	    byte[] picBlobArray = null;
	    if( contactInfo.isAvatarPicValid() )
	    {
		    args.put("avatar_pic", 		0 );    	
	    }
	    else
	    {
	    	picBlobArray = VxImageUtil.bitmapToBlob( contactInfo.getAvatarBitmap() );	    	
	    	if( ( null != picBlobArray ) && ( 0 != picBlobArray.length ) )
	    	{
			    args.put("avatar_pic", 		picBlobArray );  	    		
	    	}
	    	else
	    	{
			    args.put("avatar_pic", 		0 );  	    		
	    	}	    	
	    }

	    args.put("pic_file_name", 		contactInfo.getOrigPicFileName() );
	    return 7;
	}
	 
	//========================================================================	
	// returns args get count
	int getContactInfo( Cursor cursor, ContactInfo contactInfo )
	{
		contactInfo.setOnlineId( cursor.getLong(0),  cursor.getLong(1) );
		contactInfo.setDisplayName( cursor.getString(2) );
		contactInfo.setMobilePhoneNum( cursor.getString(3) );
		contactInfo.setUserNotes( cursor.getString(4) );
		contactInfo.setAvatarBitmap( null );	
		byte[] picBlobArray = cursor.getBlob(5);	
		if( ( null != picBlobArray ) && ( 0 < picBlobArray.length ) )
		{
			Bitmap picBitmap = VxImageUtil.blobToBitmap( picBlobArray );
			if( ( null != picBitmap ) && ( 0 < picBitmap.getWidth() ) )
			{
				contactInfo.setAvatarBitmap( picBitmap );				
			}		
		}

		contactInfo.setOrigPicFileName( cursor.getString(6) );
		return 7;
	}
	
    //========================================================================
	boolean onlineUidExistsInTable( SQLiteDatabase db, long u64IdLoPart, long u64IdHiPart, String strTableName )
	{
		boolean bExists = false;
		Cursor cursor = db.rawQuery(  "SELECT uid_lopart FROM " + strTableName +  " WHERE uid_lopart = " + u64IdLoPart + " AND uid_hipart = " + u64IdHiPart, null );
		if( cursor.getCount() > 0 )
		{
			bExists = true;
		}
		
	    cursor.close();	
		return bExists;
	}
	
	//========================================================================
	//! sets values of FriendBase into args returns args put count
	//! NOTE: does not put ids in args
	int putFriendBase( ContentValues args, VxNetIdent oFriendBase )
	{
		args.put("name", 			oFriendBase.m_as8OnlineName );
	    args.put("desc", 			oFriendBase.m_as8OnlineDesc);
	    args.put("friend_match", 	oFriendBase.m_u8FriendMatch );
	    args.put("search_flags", 	oFriendBase.m_u8SearchFlags );
	    args.put("shared_files", 	oFriendBase.m_u8FileTypeFlags );
	    args.put("ip_port", 		oFriendBase.getOnlinePort() );
	    args.put("local_ipv4", 		oFriendBase.m_as8LocalIPv4 );
	    args.put("online_ipv4", 	oFriendBase.m_as8OnlineIPv4 );
	    args.put("online_ipv6", 	oFriendBase.m_as8OnlineIPv6 );
	    args.put("permissions", 	oFriendBase.m_au8Permissions );
	    args.put("truth_cnt", 		oFriendBase.m_u32TruthCnt );
	    args.put("dare_cnt", 		oFriendBase.m_u32DareCnt );
	    args.put("rejected_truth_cnt", 	oFriendBase.m_RejectedTruthCnt );
	    args.put("rejected_dare_cnt", 	oFriendBase.m_RejectedDareCnt );
 	    return 10;
	}
	
	//========================================================================	
	// returns args get count
	int getFriendBase( Cursor cursor, VxNetIdent oFriendBase )
	{
		oFriendBase.m_u64IdLoPart 		= cursor.getLong(0);
		oFriendBase.m_u64IdHiPart 		= cursor.getLong(1);
		oFriendBase.m_as8OnlineName 	= cursor.getString(2);
		oFriendBase.m_as8OnlineDesc 	= cursor.getString(3);
		oFriendBase.m_u8FriendMatch 	= (byte)cursor.getShort(4);
		oFriendBase.m_u8SearchFlags 	= (byte)cursor.getShort(5);
		oFriendBase.m_u8FileTypeFlags 	= (byte)cursor.getShort(6);
		oFriendBase.setOnlinePort( cursor.getInt(7) );
		oFriendBase.setLocalIPv4( cursor.getString(8) );
		oFriendBase.setOnlineIPv4( cursor.getString(9) );
		oFriendBase.setOnlineIPv6( cursor.getString(10) );
		oFriendBase.m_au8Permissions = cursor.getBlob(11);
	    oFriendBase.m_u32TruthCnt 		= cursor.getInt( 12 );
	    oFriendBase.m_u32DareCnt 		= cursor.getInt( 13 );
	    oFriendBase.m_RejectedTruthCnt 	= cursor.getInt( 14 );
	    oFriendBase.m_RejectedDareCnt 	= cursor.getInt( 15 );
		
		return 14;
	}

	//=========================================================================
	public boolean updateLastLogin( String strRogueName ) 
	{
		SQLiteDatabase db=this.getWritableDatabase();
		db.delete(TABLE_LAST_LOGIN, null, null);
	   
		db.execSQL( "INSERT INTO " + TABLE_LAST_LOGIN + "("+COLUMNS_LAST_LOGIN + ") values('" +
			   strRogueName + "')" );
		return true;
	}
	
	//=========================================================================
	public String getLastLogin() 
	{
		SQLiteDatabase db=this.getReadableDatabase();
		String strRogueName = "";
		Cursor cursor = db.rawQuery( "SELECT * FROM " + TABLE_LAST_LOGIN, null );
		if (cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
			strRogueName = cursor.getString(1);
		}
		
		cursor.close();
		return strRogueName;
	}

	//=========================================================================
	// accounts
	//=========================================================================
	
	//=========================================================================
	public boolean updateAccount( UserAccount oUserAccount ) 
	{
		if( null == oUserAccount )
		{
		   	Log.e(LOG_TAG, "updateAccount oUserAccount is null.");
			return false;
		}
		
		SQLiteDatabase db=this.getWritableDatabase();
		long s64Result;
        ContentValues args = new ContentValues();
        
		if( onlineUidExistsInTable( db, oUserAccount.m_u64IdLoPart, oUserAccount.m_u64IdHiPart, TABLE_ACCOUNT_LOGIN ))
		{
			// update
			putFriendBase( args, oUserAccount );
	        s64Result = db.update(TABLE_ACCOUNT_LOGIN, 
	        			args, 
	        			"uid_lopart = " + oUserAccount.m_u64IdLoPart + " AND uid_hipart = " + oUserAccount.m_u64IdHiPart,
	        			null );
		}
		else
		{
	        args.put("uid_lopart", oUserAccount.m_u64IdLoPart );
	        args.put("uid_hipart", oUserAccount.m_u64IdHiPart );
	        putFriendBase( args, oUserAccount );
			s64Result = db.insert(TABLE_ACCOUNT_LOGIN, null, args);
		}
       
		return (s64Result >= 0 );
	}

	//========================================================================
	public boolean getAccountByName(String name, UserAccount oUserAccount ) 
	{
		boolean bResult = false;
		SQLiteDatabase db=this.getReadableDatabase();
		String strSql = "SELECT " + COLUMNS_ACOUNT_LOGIN + " FROM " + TABLE_ACCOUNT_LOGIN +  " WHERE name = '" + name + "'" ;
		Cursor cursor = db.rawQuery( strSql, null );
		if (cursor.getCount() > 0 )
		{
			cursor.moveToFirst();	
			oUserAccount.m_u64IdLoPart 			= cursor.getLong(0);
			oUserAccount.m_u64IdHiPart 			= cursor.getLong(1);
			oUserAccount.m_as8OnlineName 		= cursor.getString(2);
			oUserAccount.m_as8OnlineDesc 		= cursor.getString(3);
			oUserAccount.m_u8FriendMatch 		= (byte)cursor.getShort(4);
			oUserAccount.m_u8SearchFlags 		= (byte)cursor.getShort(5);
			oUserAccount.m_u8FileTypeFlags 		= (byte)cursor.getShort(6);
			oUserAccount.setOnlinePort( cursor.getInt(7) );
			oUserAccount.setLocalIPv4( cursor.getString(8) );
			oUserAccount.setOnlineIPv4( cursor.getString(9) );
			oUserAccount.setOnlineIPv6( cursor.getString(10) );
			oUserAccount.m_au8Permissions 		= cursor.getBlob(11);
			oUserAccount.m_u32TruthCnt 			= cursor.getInt(12 );
			oUserAccount.m_u32DareCnt 			= cursor.getInt(13 );
			oUserAccount.m_RejectedTruthCnt 	= cursor.getInt( 14 );
			oUserAccount.m_RejectedDareCnt 		= cursor.getInt( 15 );

			bResult = true;
		}
		
	    cursor.close();
		return bResult;
	}
	
	//=========================================================================
	// friends
	//=========================================================================
	public boolean getUserProfile( UserAccount oUserAccount, UserProfile oProfile ) 
	{
		boolean bResult = false;
		SQLiteDatabase db=this.getReadableDatabase();
		Cursor cursor = db.rawQuery("SELECT " + COLUMNS_ACOUNT_PROFILE + " FROM " + TABLE_ACCOUNT_PROFILE +
	    		  " WHERE uid_lopart = " + oUserAccount.m_u64IdLoPart + " AND uid_hipart = " + oUserAccount.m_u64IdHiPart, null );
		if (cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
		   
			oProfile.m_strGreeting = cursor.getString(2);
			oProfile.m_strAboutMe = cursor.getString(3);
			oProfile.m_strPicturePath = cursor.getString(4);
			oProfile.m_strUrl1 = cursor.getString(5);
			oProfile.m_strUrl2 = cursor.getString(6);
			oProfile.m_strUrl3 = cursor.getString(7);
	    	   
			bResult = true;
		}
	    cursor.close();
		return bResult;
	}
	
	//========================================================================
	public boolean updateUserProfile( UserAccount oUserAccount, UserProfile oProfile ) 
	{
		SQLiteDatabase db=this.getWritableDatabase();
		if( onlineUidExistsInTable( db, oUserAccount.m_u64IdLoPart, oUserAccount.m_u64IdHiPart, TABLE_ACCOUNT_PROFILE ))
		{
			// update
			long rowsAffected = 0;
	        ContentValues args = new ContentValues();
	        args.put("greeting", oProfile.m_strGreeting );
	        args.put("picture", oProfile.m_strPicturePath );
	        args.put("about", oProfile.m_strAboutMe);
	        args.put("url1", oProfile.m_strUrl1 );
	        args.put("url2", oProfile.m_strUrl2);
	        args.put("url3", oProfile.m_strUrl3);
	        rowsAffected = db.update(TABLE_ACCOUNT_PROFILE, 
	        			args, 
	        			"uid_lopart = " + oUserAccount.m_u64IdLoPart + " AND uid_hipart = " + oUserAccount.m_u64IdHiPart,
	        			null );
	        return (rowsAffected > 0);
		}
		else
		{
			// insert
			long rowId = -1;
	        ContentValues args  = new ContentValues();
	        args.put("uid_lopart", oUserAccount.m_u64IdLoPart );
	        args.put("uid_hipart", oUserAccount.m_u64IdHiPart );
	        args.put("greeting", oProfile.m_strGreeting );
	        args.put("about", oProfile.m_strAboutMe);
	        args.put("picture", oProfile.m_strPicturePath );
	        args.put("url1", oProfile.m_strUrl1 );
	        args.put("url2", oProfile.m_strUrl2);
	        args.put("url3", oProfile.m_strUrl3);
	        rowId = db.insert(TABLE_ACCOUNT_PROFILE, null, args);
			return (rowId >= 0);		
		}
	}

	//=========================================================================
	// friends
	//=========================================================================
	public Boolean getFriendList(byte u8MyFriendship,  ArrayList<FriendIdent> aoIdent ) 
	{
		SQLiteDatabase db=this.getReadableDatabase();
		Cursor cursor = db.rawQuery("SELECT" + COLUMNS_FRIENDS + " FROM " + TABLE_FRIENDS +
	    		  " WHERE my_frienship = " + u8MyFriendship + ";", null );
		if (cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
			do 
			{
				FriendIdent oIdent = new FriendIdent();
				getFriendBase(cursor, oIdent);
				aoIdent.add(oIdent); 
			} while (cursor.moveToNext());
		   
			if( false == cursor.isClosed()) 
			{
		         cursor.close();
			}
			return true;
		}
		if( false == cursor.isClosed()) 
		{
	         cursor.close();
		}
		return false;
    }
	
	//=========================================================================
    public boolean updateFriend( FriendIdent oIdent ) 
    {
    	long rowsAffected = 0;
		SQLiteDatabase db=this.getWritableDatabase();
		if( onlineUidExistsInTable( db, oIdent.m_u64IdLoPart, oIdent.m_u64IdHiPart, TABLE_FRIENDS ))
		{
			// update
	        ContentValues args = new ContentValues();
	        putFriendBase( args, oIdent );
	        args.put("his_friendship",  oIdent.getHisFriendshipToMeFlags());
	        args.put("my_friendship",  oIdent.getMyFriendshipToHimFlags());

	        rowsAffected = db.update(TABLE_FRIENDS, 
	        			args, 
	        			"uid_lopart = " + oIdent.m_u64IdLoPart + " AND uid_hipart = " + oIdent.m_u64IdHiPart,
	        			null );
		}
		else
		{
			// insert
	        ContentValues args = new ContentValues();
	        args.put("uid_lopart", oIdent.m_u64IdLoPart );
	        args.put("uid_hipart", oIdent.m_u64IdLoPart );
	        putFriendBase( args, oIdent );
	        args.put("his_friendship",  oIdent.getHisFriendshipToMeFlags());
	        args.put("my_friendship",  oIdent.getMyFriendshipToHimFlags());
	        rowsAffected = db.insert(TABLE_FRIENDS, null, args);
		}
		
		if( 0 == rowsAffected )
		{
			Log.w( LOG_TAG, "updateFriend database ERROR ." + rowsAffected );		
		}
		
		return true;
    }

    //=========================================================================
    // options
    //=========================================================================  
    public List<String> selectAll() 
    {
    	SQLiteDatabase db=this.getReadableDatabase();
	    List<String> list = new ArrayList<String>();
	    Cursor cursor = db.query(TABLE_ACCOUNT_LOGIN, new String[] { "name" }, null, null, null, null, "name desc");
	    if( cursor.moveToFirst() ) 
	    {
	         do 
	         {
	        	 list.add(cursor.getString(0)); 
	         } while (cursor.moveToNext());
	    }
	    
	    if (cursor != null && !cursor.isClosed()) 
	    {
	         cursor.close();
	    }
	    
	    return list;
    }

    //========================================================================
	boolean anchorSettingExistsInTable( SQLiteDatabase db, String anchorSettingName, String strTableName )
	{
		boolean bExists = false;
		Cursor cursor = db.rawQuery(  "SELECT anchor_setting_name FROM " + strTableName +  " WHERE anchor_setting_name = '" + anchorSettingName + "'", null );
		if (cursor.getCount() > 0 )
		{
			bExists = true;
		}
	    cursor.close();	
		return bExists;
	}

    //============================================================================
    boolean updateAnchorSetting( AnchorSetting anchorSetting )
    {
 		SQLiteDatabase db=this.getWritableDatabase();
		if( anchorSettingExistsInTable( db, anchorSetting.getAnchorSettingName(), TABLE_ANCHOR_SETTINGS ))
		{
			// update
		   	long rowsAffected = 0;
	        ContentValues args = new ContentValues();
	    	//anchor_url,connect_test_url,is_anchor_node";

	        args.put("network_name",  anchorSetting.getNetworkName() );
	        args.put("anchor_url",  anchorSetting.getAnchorWebsiteUrl() );
	        args.put("connect_test_url",  anchorSetting.getNetServiceWebsiteUrl() );
	        args.put("is_anchor_node",  anchorSetting.getIsDeviceAnAnchor() );

	        rowsAffected = db.update(TABLE_ANCHOR_SETTINGS, 
	        			args, 
	        			"anchor_setting_name = '" + anchorSetting.getAnchorSettingName() + "'",
	        			null );
	        return (rowsAffected > 0);
		}
		else
		{
			// insert
			long rowId = -1;
			ContentValues args = new ContentValues();
	        args.put("anchor_setting_name",  anchorSetting.getAnchorSettingName() );
	        args.put("network_name",  anchorSetting.getNetworkName() );
	        args.put("anchor_url",  anchorSetting.getAnchorWebsiteUrl() );
	        args.put("connect_test_url",  anchorSetting.getNetServiceWebsiteUrl() );
	        args.put("is_anchor_node",  anchorSetting.getIsDeviceAnAnchor() );
	        rowId = db.insert(TABLE_ANCHOR_SETTINGS, null, args);
	        return (rowId >= 0);
		}
    }

    //============================================================================
    boolean getAnchorSettingByName( String name, AnchorSetting anchorSetting )
    {
		boolean bResult = false;
		SQLiteDatabase db=this.getReadableDatabase();
		String strSql = "SELECT * FROM " + TABLE_ANCHOR_SETTINGS +  " WHERE anchor_setting_name = '" + name + "'" ;
		Cursor cursor = db.rawQuery( strSql, null );
		if( cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
   			anchorSetting.setAnchorSettingName( name );
			anchorSetting.setNetworkName( cursor.getString(1) );
			anchorSetting.setAnchorWebsiteUrl( cursor.getString(2) );
			anchorSetting.setNetServiceWebsiteUrl( cursor.getString(3) );
			anchorSetting.setIsDeviceAnAnchor(  ( 0 == cursor.getLong(4) ) ? false : true );

			bResult = true;
		}
		
	    cursor.close();
		return bResult;
    }

    //============================================================================
    boolean getAllAnchorSettings( ArrayList<AnchorSetting> anchorSettingList )
    {
    	boolean bResult = false;
		SQLiteDatabase db=this.getReadableDatabase();
		String strSql = "SELECT * FROM " + TABLE_ANCHOR_SETTINGS;
		Cursor cursor = db.rawQuery( strSql, null );
		if( cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
			
			bResult = true;
	        do 
	        {
	  			AnchorSetting anchorSetting = new AnchorSetting();

    			anchorSetting.setAnchorSettingName( cursor.getString(0) );
    			anchorSetting.setNetworkName( cursor.getString(1) );
    			anchorSetting.setAnchorWebsiteUrl( cursor.getString(2) );
    			anchorSetting.setNetServiceWebsiteUrl( cursor.getString(3) );
    			anchorSetting.setIsDeviceAnAnchor(  ( 0 == cursor.getLong(4) ) ? false : true );
    			anchorSettingList.add( anchorSetting );

	        } while( cursor.moveToNext() );
	    }
	    
	    if (cursor != null && !cursor.isClosed()) 
	    {
	         cursor.close();
	    }
			
    	return bResult;
    }

    //============================================================================
    boolean removeAnchorSettingByName( String name )
    {
    	String strSql = "DELETE FROM anchor_settings WHERE anchor_setting_name = '" + name + "'";
		SQLiteDatabase db=this.getReadableDatabase();
    	db.execSQL( strSql );
    	return true;
    }

    //============================================================================
    boolean updateLastAnchorSettingName( String name )
    {
		SQLiteDatabase db=this.getReadableDatabase();
		db.execSQL(  "DELETE FROM last_anchor_setting" );
		
        ContentValues args = new ContentValues();
        args.put("anchor_setting_name", name );
        long rowId = db.insert( TABLE_LAST_ANCHOR_SETTING, null, args );
        return ( rowId >= 0 );
    }

    //============================================================================
    String getLastAnchorSettingName()
    {
		SQLiteDatabase db=this.getReadableDatabase();
    	String strSettingName = "";
		String strSql = "SELECT * FROM " + TABLE_LAST_ANCHOR_SETTING;
		Cursor cursor = db.rawQuery( strSql, null );
		if( cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
			strSettingName = cursor.getString(0);
	    }
	    
	    if (cursor != null && !cursor.isClosed()) 
	    {
	         cursor.close();
	    }

    	return strSettingName;
    }
}
