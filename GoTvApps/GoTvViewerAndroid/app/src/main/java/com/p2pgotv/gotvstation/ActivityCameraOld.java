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

import java.io.IOException;
import java.util.TimerTask;

import android.app.Activity;
import android.content.res.Configuration;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.hardware.Camera.AutoFocusCallback;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.ShutterCallback;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;

public class ActivityCameraOld extends Activity implements SurfaceHolder.Callback
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityCameraOld:";
	
	//=== activity vars ===//
	private MyApp 				m_MyApp;

	Camera 						camera;
	SurfaceView 				surfaceView;
	SurfaceHolder 				surfaceHolder;
	boolean 					previewing = false;
	LayoutInflater 				controlInflater = null;
	
	Button 						buttonTakePicture;
	
	final int 					RESULT_SAVEIMAGE = 0;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_old);
        
        m_MyApp = (MyApp) this.getApplication();
        
        getWindow().setFormat(PixelFormat.UNKNOWN);
        surfaceView = (SurfaceView)findViewById(R.id.camerapreview);
        surfaceHolder = surfaceView.getHolder();
        surfaceHolder.addCallback(this);
        surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        
        controlInflater = LayoutInflater.from(getBaseContext());
        View viewControl = controlInflater.inflate(R.layout.camera_control, null);
        LayoutParams layoutParamsControl = new LayoutParams( LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT );
        this.addContentView(viewControl, layoutParamsControl);
        
        buttonTakePicture = (Button)findViewById(R.id.takepicture);
        if( null != buttonTakePicture )
        {
        	buttonTakePicture.setOnClickListener(new Button.OnClickListener()
        	{
        		public void onClick(View arg0) 
        		{
        			m_MyApp.playSound( ESndDef.eSndDefCameraClick );
        			camera.takePicture(myShutterCallback, myPictureCallback_RAW, myPictureCallback_JPG);
        		}
        	});
        };
        
        LinearLayout layoutBackground = (LinearLayout)findViewById(R.id.background);
        if( null != layoutBackground )
        {
        	layoutBackground.setOnClickListener(new LinearLayout.OnClickListener(){
			public void onClick(View arg0) 
			{	
 			    m_MyApp.playButtonClick();
				if( null !=  camera )
				{
					buttonTakePicture.setEnabled(false);
					camera.autoFocus(myAutoFocusCallback);
				}
			}});
        }
    }
    public void onConfigurationChanged(Configuration newConfig) 
    {
    	// Ignore orientation change not to restart activity
    	super.onConfigurationChanged(newConfig);
    }
    
    AutoFocusCallback myAutoFocusCallback = new AutoFocusCallback(){
		public void onAutoFocus(boolean arg0, Camera arg1) {
			buttonTakePicture.setEnabled(true);
		}};
    
    ShutterCallback myShutterCallback = new ShutterCallback(){
		public void onShutter() {
		}};
		
	PictureCallback myPictureCallback_RAW = new PictureCallback(){
		public void onPictureTaken(byte[] arg0, Camera arg1) {
		}};
		
	PictureCallback myPictureCallback_JPG = new PictureCallback()
	{
		public void onPictureTaken(byte[] arg0, Camera arg1) 
		{	

			VxImageUtil.saveImageDataToStdSizeJpg(arg0, m_MyApp.getUserProfileDir() + "me.jpg");
			ActivityCameraOld.this.setResult(RESULT_OK);
			finish();
		}
	};

	
	class UpdateTimeTask extends TimerTask 
	{
		public void run() 
		{
			cancel();
			finish();
		}
	}

		//TODO set one shot to exit activity
	
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) 
	{
		if(previewing)
		{
			//camera.stopPreview();
			previewing = false;
		}
		
		if (camera != null)
		{
			try 
			{
				camera.setPreviewDisplay(surfaceHolder);
				camera.startPreview();
				previewing = true;
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
		}
	}

	public void surfaceCreated(SurfaceHolder holder) {
		camera = Camera.open();
	}

	public void surfaceDestroyed(SurfaceHolder holder) 
	{
		if( null != camera )
		{
			camera.stopPreview();
			camera.release();
			camera = null;
			previewing = false;
		}
	}
}