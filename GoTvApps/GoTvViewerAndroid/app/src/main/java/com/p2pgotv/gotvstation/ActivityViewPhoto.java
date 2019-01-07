package com.p2pgotv.gotvstation;

import com.p2pgotv.gotvstation.rteditor.api.RTMediaFactory;
import com.p2pgotv.gotvstation.rteditor.api.media.RTAudio;
import com.p2pgotv.gotvstation.rteditor.api.media.RTImage;
import com.p2pgotv.gotvstation.rteditor.api.media.RTVideo;
import com.p2pgotv.gotvstation.rteditor.utils.Constants.MediaAction;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;

public class ActivityViewPhoto extends ActivityBase 
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityViewPhoto:";
	   
	//=== vars ===//
	private Button 					m_AcceptBut 				= null;
	private Button  				m_CancelBut 				= null;
	private VxFileInfo  			m_FileInfo 					= null;
	private ReuseFileDisplayLogic  	m_FileDisplayLogic 			= new ReuseFileDisplayLogic();
	private ImageView				m_PhotoView					= null;
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_view_photo);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_view_photo_title );
        m_FileInfo = m_MyApp.getCurrentFileInfo();
        if( null != m_FileInfo )
        {
        	m_FileDisplayLogic.fillFileDisplayGui( this, m_FileInfo );
        }
 	 	
		this.m_AcceptBut = (Button)this.findViewById(R.id.reuse_accept_but);
		if( null != m_AcceptBut )
		{
		 	this.m_AcceptBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
		        	m_MyApp.playButtonClick();
		 			onAcceptButClick();
		 		}
		 	});			
		}
	 	
		this.m_CancelBut = (Button)this.findViewById(R.id.reuse_cancel_but);
		if( null != m_CancelBut )
		{
		 	this.m_CancelBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
		        	m_MyApp.playButtonClick();
		 			onCancelButClick();
		 		}
		 	});	
		}
		
	
		m_PhotoView = (ImageView)this.findViewById(R.id.reuse_photo_view);
		if( ( null != m_PhotoView ) && ( null != m_FileInfo ) )
		{
			// if image it to big it will crash android so resize before setting
			Bitmap myBitmap = VxImageUtil.getSizedImageFromFile( m_FileInfo.getFullFileName(), 320, 240 );
			if( null != myBitmap )
			{
				m_PhotoView.setImageBitmap( myBitmap );
			}
			else
			{
				NativeRxFrom.toGuiUserMessage( "Could Not Decode Image" );
			}
		}
		
        Bundle extras = getIntent().getExtras();
        if (extras != null) 
        {
            String hideAcceptReject = extras.getString( Constants.PARAM_HIDE_ACCEPT_REJECT );
            if( ( null != hideAcceptReject ) && ( 0 != hideAcceptReject.length() ) )
            {
            	LinearLayout acceptLayout = (LinearLayout)this.findViewById(R.id.reuse_accept_cancel_layout);
            	if( null != acceptLayout )
            	{
            		acceptLayout.setVisibility( View.GONE );
            	}     	
            }
        }
    }
	
	//========================================================================
	public void onAcceptButClick() 
	{
		Intent resultIntent = getIntent();
		setResult(Activity.RESULT_OK, resultIntent);
		finish();
	}

	//========================================================================
	public void onCancelButClick() 
	{
		onBackButtonPressed();
	}
}
