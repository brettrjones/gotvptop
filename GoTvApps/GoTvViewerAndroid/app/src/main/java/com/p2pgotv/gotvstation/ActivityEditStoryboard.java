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

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;

import com.p2pgotv.gotvstation.materialdialogs.MaterialDialog;
import com.p2pgotv.gotvstation.rteditor.RTManager;
import com.p2pgotv.gotvstation.rteditor.RTToolbar;
import com.p2pgotv.gotvstation.rteditor.api.RTApi;
import com.p2pgotv.gotvstation.rteditor.api.RTMediaFactoryImpl;
import com.p2pgotv.gotvstation.rteditor.api.RTProxyImpl;
import com.p2pgotv.gotvstation.rteditor.api.format.RTFormat;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Toast;

public class ActivityEditStoryboard extends ActivityBase
{
	public static final String 	LOG_TAG = "ActivityEditStoryboard:";
	private static final int 	REQUEST_LOAD_FILE 	= 1;
	private static final int 	REQUEST_SAVE_FILE 	= 2;

	private static final int 	REQUEST_PERMISSION = 3;
	private static final String PREFERENCE_PERMISSION_DENIED = "PREFERENCE_PERMISSION_DENIED";

	// === vars ===//
	private VxHtmlEditor 		m_HtmlEditor 					= null;
	private RTManager 			m_RTManager 					= null;

	private boolean 			m_UseDarkTheme					= false;
	private boolean 			m_SplitToolbar					= false;
    private AtomicBoolean 		m_RequestPermissionsInProcess 	= new AtomicBoolean();
    private String				m_RootWebServerPath				= "";
    private String 				m_StoryboardFileName			= "";
    private RTMediaFactoryImpl	m_MediaFactory;

	//================================================================================
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		Log.i( LOG_TAG, "onCreate 1" );
		requestWindowFeature( Window.FEATURE_NO_TITLE );
		setTheme( R.style.ThemeLight );
		setContentView( R.layout.activity_edit_story_board );
		super.onCreate( savedInstanceState );
		setPageTitle( R.string.activity_edit_storyboard_title );
		Log.i( LOG_TAG, "onCreate 2" );

		m_RootWebServerPath = m_MyApp.getUserProfileDir();
		m_StoryboardFileName = m_RootWebServerPath + "story_board.htm";

		m_MediaFactory = new RTMediaFactoryImpl( this, true );
		m_MediaFactory.setRootPath( m_RootWebServerPath );
		RTApi rtApi = new RTApi( this, new RTProxyImpl( this ), m_MediaFactory );
		m_RTManager = new RTManager( rtApi, savedInstanceState );

		ViewGroup toolbarContainer = ( ViewGroup ) findViewById( R.id.rte_toolbar_container );

		// register toolbar 0 (if it exists)
		RTToolbar rtToolbar0 = ( RTToolbar ) findViewById( R.id.rte_toolbar );
		if( rtToolbar0 != null )
		{
			m_RTManager.registerToolbar( toolbarContainer, rtToolbar0 );
		}

		m_HtmlEditor = ( VxHtmlEditor ) this.findViewById( R.id.html_editor );
		m_HtmlEditor.initVxHtmlEditor( getRootPath(), m_StoryboardFileName );
		m_RTManager.registerEditor( m_HtmlEditor, true );

		registerForContextMenu( m_HtmlEditor );
		m_HtmlEditor.loadFromFile();
		m_HtmlEditor.requestFocus();
	}
	
	//========================================================================
	public String getRootPath()
	{
		return m_RootWebServerPath;
	}

	//========================================================================
	@Override
	public void onDestroy()
	{
		super.onDestroy();
		if( m_RTManager != null )
		{
			m_RTManager.onDestroy( true );
		}
	}

	//========================================================================
	@Override
	protected void onSaveInstanceState( Bundle outState )
	{
		super.onSaveInstanceState( outState );

		m_RTManager.onSaveInstanceState( outState );

		outState.putBoolean( "UseDarkTheme", m_UseDarkTheme );
		outState.putBoolean( "SplitToolbar", m_SplitToolbar );
		outState.putBoolean( "RequestPermissionsInProcess", m_RequestPermissionsInProcess.get() );
	}

	//========================================================================
	@Override
	protected void onActivityResult( int requestCode, int resultCode,
			Intent data )
	{
		if( m_RTManager != null
			&& m_RTManager.onActivityResult( requestCode, resultCode, data ) )
		{
			return;
		}
		
		if( resultCode == Activity.RESULT_OK && data != null
				&& data.getData() != null && data.getData().getPath() != null )
		{
			if( requestCode == REQUEST_SAVE_FILE )
			{
				saveStoryboard();
			}
			else if( requestCode == REQUEST_LOAD_FILE )
			{
				loadStoryboard();
			}
		}
	}
	
	//========================================================================
	public void loadStoryboard() 
	{
		if( null != m_HtmlEditor )
		{
			m_HtmlEditor.loadFromFile();
		}
		// m_RichTextEditor.initializeHtml( m_MyApp, storyBoardFile );
		String htmlContent = VxFileUtil.readTextFile( m_StoryboardFileName, false );
		if( ( null == htmlContent ) || htmlContent.isEmpty() )
		{
			htmlContent = "";
		}
		// m_HtmlEditor.setRichTextEditing( true, htmContent );
		String emptyContent = "test message";
		m_HtmlEditor.setRichTextEditing( getRootPath(), true, emptyContent );
	}
	
	//========================================================================
	public void saveStoryboard() 
	{
		if( null == VxFileUtil.writeTextFile( this, m_StoryboardFileName,  m_HtmlEditor.getText( RTFormat.HTML ) ) )
		{
			String toastMsg = getString( R.string.save_as_failure, m_StoryboardFileName );
			Toast.makeText( this, toastMsg, Toast.LENGTH_LONG ).show();					
		}
		else
		{
			String toastMsg = getString( R.string.save_as_success, m_StoryboardFileName );
			Toast.makeText( this, toastMsg, Toast.LENGTH_LONG ).show();
		}
	}

	//========================================================================
	@Override
	public boolean onCreateOptionsMenu( Menu menu )
	{
		MenuInflater inflater = getMenuInflater();
		inflater.inflate( R.menu.main_menu, menu );
		return true;
	}

	//========================================================================
	@Override
	public boolean onPrepareOptionsMenu( Menu menu )
	{
		// configure theme item
		MenuItem item = menu.findItem( R.id.theme );
		item.setTitle( m_UseDarkTheme ? R.string.menu_light_theme : R.string.menu_dark_theme );
		// configure split toolbar item
		item = menu.findItem( R.id.split_toolbar );
		item.setTitle( m_SplitToolbar ? R.string.menu_single_toolbar : R.string.menu_split_toolbar );

		return true;
	}

	//========================================================================
	@Override
	public boolean onOptionsItemSelected( MenuItem item )
	{
		int itemId = item.getItemId();
		if( itemId == R.id.load )
		{
			loadStoryboard();
			return true;
		}
		else if( itemId == R.id.save )
		{
			saveStoryboard();
			return true;
		}
		else if( itemId == R.id.theme )
		{
			m_UseDarkTheme = !m_UseDarkTheme;
			restart();
			return true;
		}
		else if( itemId == R.id.split_toolbar )
		{
			m_SplitToolbar = !m_SplitToolbar;
			restart();
			return true;
		}
		return false;
	}

	//========================================================================
	private void restart()
	{
		String content = m_HtmlEditor.getText( RTFormat.HTML );
		Intent intent = new Intent( this, getClass() )
				.putExtra( "UseDarkTheme", m_UseDarkTheme )
				.putExtra( "SplitToolbar", m_SplitToolbar )
				.putExtra( "content", content );
		startActivity( intent );
		finish();
	}

	//========================================================================
	// ****************************************** Check Storage Permissions
	private void checkPermissions( String[] permissions )
	{
		if( Build.VERSION.SDK_INT >= Build.VERSION_CODES.M )
		{
			checkPermissionInternal( permissions );
		}
	}

	//========================================================================
	@TargetApi(Build.VERSION_CODES.M)
	private boolean checkPermissionInternal( String[] permissions )
	{
		ArrayList<String> requestPerms = new ArrayList<String>();
		for( String permission : permissions )
		{
			if( checkSelfPermission( permission ) == PackageManager.PERMISSION_DENIED
					&& !userDeniedPermissionAfterRationale( permission ) )
			{
				requestPerms.add( permission );
			}
		}
		if( requestPerms.size() > 0
				&& !m_RequestPermissionsInProcess.getAndSet( true ) )
		{
			// We do not have this essential permission, ask for it
			requestPermissions(
					requestPerms.toArray( new String[requestPerms.size()] ),
					REQUEST_PERMISSION );
			return true;
		}

		return false;
	}

	//========================================================================
	@Override
	public void onRequestPermissionsResult( int requestCode,
			String[] permissions, int[] grantResults )
	{
		if( requestCode == REQUEST_PERMISSION )
		{
			for( int i = 0, len = permissions.length; i < len; i++ )
			{
				String permission = permissions[i];
				if( grantResults[i] == PackageManager.PERMISSION_DENIED )
				{
					if( Manifest.permission.WRITE_EXTERNAL_STORAGE.equals( permission ) )
					{
						showRationale( permission, R.string.permission_denied_storage );
					}
				}
			}
		}
	}

	//========================================================================
	@TargetApi(Build.VERSION_CODES.M)
	private void showRationale( final String permission, int promptResId )
	{
		if( shouldShowRequestPermissionRationale( permission )
				&& !userDeniedPermissionAfterRationale( permission ) )
		{

			// Notify the user of the reduction in functionality and possibly
			// exit (app dependent)
			MaterialDialog dialog = new MaterialDialog.Builder( this )
					.title( getString( R.string.permission_denied ) )
					.content( promptResId )
					.positiveText( R.string.permission_deny )
					.negativeText( R.string.permission_retry )
					.autoDismiss( false )
					.callback( new MaterialDialog.ButtonCallback()
					{
						@Override
						public void onPositive( MaterialDialog dialog )
						{
							try
							{
								dialog.dismiss();
							}
							catch( Exception ignore )
							{
							}
							setUserDeniedPermissionAfterRationale( permission );
							m_RequestPermissionsInProcess.set( false );
						}

						@Override
						public void onNegative( MaterialDialog dialog )
						{
							try
							{
								dialog.dismiss();
							}
							catch( Exception ignore )
							{
							}
							m_RequestPermissionsInProcess.set( false );
							checkPermissions( new String[]
							{ permission } );
						}
					} ).show();
		}
		else
		{
			m_RequestPermissionsInProcess.set( false );
		}
	}

	//========================================================================
	private boolean userDeniedPermissionAfterRationale( String permission )
	{
		SharedPreferences sharedPrefs = getSharedPreferences( getClass()
				.getSimpleName(), Context.MODE_PRIVATE );
		return sharedPrefs.getBoolean( PREFERENCE_PERMISSION_DENIED
				+ permission, false );
	}

	//========================================================================
	private void setUserDeniedPermissionAfterRationale( String permission )
	{
		SharedPreferences.Editor editor = getSharedPreferences(
				getClass().getSimpleName(), Context.MODE_PRIVATE ).edit();
		editor.putBoolean( PREFERENCE_PERMISSION_DENIED + permission, true )
				.commit();
	}
}
