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

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Window;

public class Camcorder extends Activity 
{
	
	 private CamcorderView camcorderView; 
	 private boolean recording = false; 
	
	 /** Called when the activity is first created. */ 
	 @Override 
	 public void onCreate(Bundle savedInstanceState) 
	 { 
	      super.onCreate(savedInstanceState); 
	      requestWindowFeature(Window.FEATURE_NO_TITLE); 
	      setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE); 
	      setContentView(R.layout.activity_camcorder); 
	      
	      setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
	      camcorderView = (CamcorderView) findViewById(R.id.camcorder_preview); 
	 } 
	 
	 @Override 
	 public boolean onKeyDown(int keyCode, KeyEvent event) 
	 { 
	     if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER) 
	     { 
	   	  if (recording) { 
	   		  	camcorderView.stopRecording();
	            finish(); 
	        } else { 
	            recording = true; 
	            camcorderView.startRecording(); 
	        } 
	         return true; 
	     } 
	     return super.onKeyDown(keyCode, event); 
	 }	     
}