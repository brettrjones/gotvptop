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
import android.util.Log;


public class VxSettings  extends SQLiteOpenHelper
{
	//=== constants ===//
	private static final String 	LOG_TAG 				= "VxSettings";
	private static final String 	DATABASE_NAME 			= "vxsettings.db";
	private static final int 		DATABASE_VERSION 		= 2;

	private static final String 	TABLE_U8			 	= "U8";
	private static final String 	TABLE_S16	 			= "S16";
	private static final String 	TABLE_S32	 			= "S32";
	private static final String 	TABLE_S64				= "S64";
	private static final String 	TABLE_F32				= "F32";
	private static final String 	TABLE_F64				= "F64";
	private static final String 	TABLE_STRING	 		= "string";
	private static final String 	TABLE_BLOB	 			= "blob";
	
	//private static final String 	COLUMNS_INI_VALUES	 	= "key,setting,value";
    //========================================================================
   	//=== overrides ===//
    //========================================================================
	// manage open/create/update database
	public VxSettings(Context context) 
	{
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
	}
    @Override
    public void onCreate(SQLiteDatabase db) 
    {
    	createTables(db);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) 
    {
    	Log.w(LOG_TAG, "Upgrading database, this will drop tables and recreate.");
    	DataHelper.deleteTables(db);
        onCreate(db);
    }
    //========================================================================
   	//=== helpers ===//
    //========================================================================
    public SQLiteDatabase getMyWriteableDb()
    {
    	return this.getWritableDatabase();
    }
    public SQLiteDatabase getMyReadableDb()
    {
    	return this.getReadableDatabase();
    }
 	// create tables in database
	void createTables( SQLiteDatabase db ) 
	{
    	db.execSQL("CREATE TABLE " + TABLE_U8 +  " (key TEXT, setting TEXT PRIMARY KEY, value TINYINT)");
    	db.execSQL("CREATE TABLE " + TABLE_S16 + " (key TEXT, setting TEXT PRIMARY KEY, value INTEGER)");
    	db.execSQL("CREATE TABLE " + TABLE_S32 + " (key TEXT, setting TEXT PRIMARY KEY, value INTEGER)");
    	db.execSQL("CREATE TABLE " + TABLE_S64 + " (key TEXT, setting TEXT PRIMARY KEY, value BIGINT)");
    	db.execSQL("CREATE TABLE " + TABLE_F32 + " (key TEXT, setting TEXT PRIMARY KEY, value REAL)");
    	db.execSQL("CREATE TABLE " + TABLE_F64 + " (key TEXT, setting TEXT PRIMARY KEY, value REAL)");
    	db.execSQL("CREATE TABLE " + TABLE_STRING + " (key TEXT, setting TEXT PRIMARY KEY, value TEXT)" );
    	db.execSQL("CREATE TABLE " + TABLE_BLOB + " (key TEXT, setting TEXT PRIMARY KEY, value BLOB)" );
	}
	// create tables in database
	static void deleteTables( SQLiteDatabase db ) 
	{
    	db.execSQL("DROP TABLE IF EXISTS " + TABLE_U8);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_S16);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_S32);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_S64);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_F32);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_F64);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_STRING);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_BLOB);
	}

	public void deleteAllData() 
	{
		SQLiteDatabase db=this.getWritableDatabase();
		db.delete(TABLE_U8, null, null);
		db.delete(TABLE_S32, null, null);
		db.delete(TABLE_S64, null, null);
		db.delete(TABLE_F32, null, null);
		db.delete(TABLE_F64, null, null);
		db.delete(TABLE_STRING, null, null);
		db.delete(TABLE_BLOB, null, null);
	}

    //========================================================================
   	//=== methods ===//
    //========================================================================
	//========================================================================
	//=== set value functions ===//
	//========================================================================
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, byte u8Value )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_U8, pKey, pSettingName );
		args.put("value", u8Value );
	    db.insert(TABLE_U8, null, args); 
	    db.close();
	}
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, short s16Value )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_S16, pKey, pSettingName );
		args.put("value", s16Value );
	    db.insert(TABLE_S16, null, args); 
	    db.close();		
	}
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, int s32Value )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_S32, pKey, pSettingName );
		args.put("value", s32Value );
	    db.insert(TABLE_S32, null, args); 
	    db.close();				
	}
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, long s64Value )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_S64, pKey, pSettingName );
		args.put("value", s64Value );
	    db.insert(TABLE_S64, null, args); 
	    db.close();				
	}
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, float f32Value )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_F32, pKey, pSettingName );
		args.put("value", f32Value );
	    db.insert(TABLE_F32, null, args); 
	    db.close();						
	}
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, double f64Value )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_F64, pKey, pSettingName );
		args.put("value", f64Value );
	    db.insert(TABLE_F64, null, args); 
	    db.close();						
	}
	//! set and save value to database
	public void			setIniValue( String pKey, String pSettingName, String pValue )
	{
		SQLiteDatabase db=this.getWritableDatabase();
	    ContentValues args  = prepareIniSet( db, TABLE_STRING, pKey, pSettingName );
		args.put("value", pValue );
	    db.insert(TABLE_STRING, null, args); 
	    db.close();								
	}
	//========================================================================
	//=== get value functions ===//
	//========================================================================

	//========================================================================
	//! get value from database.. return default if doesnt exist
	public byte getIniValueByte( String pKey, String pSettingName, byte u8Default )
	{
		byte u8Value;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_U8, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	u8Value = (byte)cursor.getInt(0);
		    cursor.close();
	    }
	    else
	    	u8Value = u8Default;
	    db.close();
	    return u8Value;
	}
	//! get value from database.. return default if doesnt exist
	public short			getIniValueShort( String pKey, String pSettingName, short s16Default )
	{
		short s16Value;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_S16, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	s16Value = (short)cursor.getInt(0);
		    cursor.close();
	    }
	    else
	    	s16Value = s16Default;
	    db.close();
	    return s16Value;
		
	}
	//! get value from database.. return default if doesnt exist
	public int			getIniValueInt( String pKey, String pSettingName, int s32Default )
	{
		int s32Value;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_S32, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	s32Value = cursor.getInt(0);
		    cursor.close();
	    }
	    else
	    	s32Value = s32Default;
	    db.close();
	    return s32Value;
		
	}
	//! get value from database.. return default if doesnt exist
	public long			getIniValueLong( String pKey, String pSettingName, long s64Default )
	{
		long s64Value;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_S64, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	s64Value = (int)cursor.getLong(0);
		    cursor.close();
	    }
	    else
	    	s64Value = s64Default;
	    db.close();
	    return s64Value;
	}
	//! get value from database.. return default if doesnt exist
	public float			getIniValueFloat( String pKey, String pSettingName, float f32Default )
	{
		float f32Value;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_F32, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	f32Value = cursor.getFloat(0);
		    cursor.close();
	    }
	    else
	    	f32Value = f32Default;
	    db.close();
	    return f32Value;
		
	}
	//! get value from database.. return default if doesnt exist
	public double			getIniValueDouble( String pKey, String pSettingName, double f64Default )
	{
		double f64Value;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_F64, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	f64Value = cursor.getDouble(0);
		    cursor.close();
	    }
	    else
	    	f64Value = f64Default;
	    db.close();
	    return f64Value;
		
	}
	//! get value from database.. return default if doesnt exist
	public String		getIniValueString( String pKey, String pSettingName, String pDefault )
	{
		String strValue;
		SQLiteDatabase db=this.getReadableDatabase();
	    Cursor cursor = prepareIniGet( db, TABLE_STRING, pKey, pSettingName );
	    if( null != cursor )
	    {
	    	strValue = cursor.getString(0);
		    cursor.close();
	    }
	    else
	    	strValue = pDefault;
	    db.close();
	    return strValue;
		
	}

	//! prepare sql statement set value
	private ContentValues	prepareIniSet(	SQLiteDatabase db,
											String	pTableName,
											String	pKey, 
											String	pSettingName )
	{
		
		String strDelete = "DELETE FROM " + pTableName + " WHERE key='" + pKey + "' AND setting='" + pSettingName + "'";
		db.execSQL(strDelete);
		
		ContentValues args = new ContentValues();
		args.put("key", pKey );
		args.put("setting", pSettingName );
		return args;
	}
		
	//! prepare sql statement set value
	private Cursor	prepareIniGet(	SQLiteDatabase db,
									String	pTableName,
									String	pKey, 
									String	pSettingName )
	{
		String strSql = "SELECT value FROM " + pTableName +  " WHERE key='" + pKey + "' AND setting='" + pSettingName + "'" ;
		Cursor cursor = db.rawQuery( strSql, null );
		if (cursor.getCount() > 0 )
		{
			cursor.moveToFirst();
			return cursor;
		}
	    cursor.close();
	    db.close();
		return null;
	}
};
