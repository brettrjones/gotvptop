//============================================================================
// Copyright (C) 2016 Brett R. Jones
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
import java.nio.ByteBuffer;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.Semaphore;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.hardware.Camera.Size;
import android.os.SystemClock;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.ImageView;

@SuppressWarnings("deprecation")
public class CamCaptureMgr extends Thread implements ToGuiHardwareControlInterface
{
	private static final String LOG_TAG = "CamCapture:";
	private static int			VID_CAPTURE_BUFFERS 	= 4;
	private static int			ELAPSE_MS_PER_FRAME 	= 80;
   
	//========================================================================
	@SuppressWarnings("deprecation")
	private class CamFrameCatcher implements Camera.PreviewCallback 
	{
		public CamCaptureMgr 			m_MgrCamCapture = null;
		private long					m_LastFrameTimeMs = 0;
		
        @SuppressLint("NewApi") @SuppressWarnings("deprecation")
		@Override
        public void onPreviewFrame(byte[] data, Camera camera) 
        {
    	   	long timeNowMs = System.currentTimeMillis();		
    		if( ( timeNowMs - m_LastFrameTimeMs ) >= ELAPSE_MS_PER_FRAME )
    		{
    			//Log.v(LOG_TAG, "onPreviewFrame Time="+ ( timeNowMs - m_LastFrameTimeMs ) + " rot=" + m_iCamRotation + " w=" + m_MgrCamCapture.m_CaptureWidth + " h=" + m_MgrCamCapture.m_CaptureHeight );		
    			m_LastFrameTimeMs = timeNowMs;
    			if( ( null != m_MgrCamCapture )
    				&& CamCaptureMgr.wantCamFrames()
    				&& m_MgrCamCapture.isCamReady() )
    			{
    	   		   	NativeTxTo.fromGuiVideoData( m_MgrCamCapture.m_iPixelFormat, data, m_MgrCamCapture.m_CaptureWidth, m_MgrCamCapture.m_CaptureHeight, m_MgrCamCapture.m_iCamRotation );   				
     			}
    			
       			if( CamCaptureMgr.wantCamFrames() )
    			{
       				camera.addCallbackBuffer(data);
    			}
       			
    	   		//timeNowMs = System.currentTimeMillis();
    			//Log.d( LOG_TAG, "processCamCaptureImage convert time ms " + (timeNowMs - m_LastFrameTimeMs) );
    		}
    		else
    		{
    	   		long timeDiff = ELAPSE_MS_PER_FRAME - (timeNowMs - m_LastFrameTimeMs);
    			if( timeDiff > 60  )
    			{
    				timeDiff = 60;
    			}
    			
    			//Log.v(LOG_TAG, "onPreviewFrame Skipping Frame Time=" + (timeNow - m_s64LastFrameTime) );
				SystemClock.sleep(timeDiff);
      			if( CamCaptureMgr.wantCamFrames() )
    			{
      				camera.addCallbackBuffer(data);
    			}
    		}
        }
    }
	 
	static int 					m_PreviewBufSize 		= 0;
	
	MyApp 						m_MyApp 				= null;
	
	Camera 						m_oCamera				= null;
	int 						m_CaptureWidth 			= 320;
	int 						m_CaptureHeight 		= 240;
	int 						m_iPixelFormat 			= 0;
	
	public Activity 			m_oCamPreviewActivity 	= null;
	private FrameLayout			m_PreviewFrame 			= null;
	private ImageView			m_NoPreviewImage 		= null;
	private CameraPreviewSurface   m_oPreviewSurface 	= null;
	private CamFrameCatcher 	m_FrameCatcher 			= null;
	private SurfaceHolder 		m_CreatedSurfaceHolder	= null;
	private boolean				m_PreviewStarted		= false;
	private boolean				m_PreviewFrameVisible	= false;

	int 						m_iCamRotation 			= 0;
	int 						m_iWhichCam 			= Constants.eCameraBack;
	
	int							m_CurrentCamActive		= Constants.eCameraBack;
	private int 				m_SurfaceCreated 		= 0;
	private final Set<byte[]> 	m_QueuedBuffers 		= new HashSet<byte[]>();
	private static boolean 		m_WantCamCapture 		= false;
	private static boolean 		m_KeepHardwareAlive 	= true;
	
	private volatile boolean 	m_UpdateTimerEnable 	= false;
	private volatile boolean 	m_ThreadStarted 		= false;	
	private volatile boolean 	m_CamIsReady 			= false;
	private static Semaphore 	m_CamMutex 				= new Semaphore(1); 
	
	//========================================================================
	CamCaptureMgr(MyApp oMyApp) 
	{
		super( "CamCaptureMgr" );
		m_MyApp = oMyApp;
	}
	
	//========================================================================
	public void lockCamMutex()
	{
		try 
		{
			//Log.d( LOG_TAG, "lockCamMutex acquire" );
			m_CamMutex.acquire();
			//Log.d( LOG_TAG, "lockCamMutex acquired" );
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//========================================================================
	public void unlockCamMutex()
	{
		//Log.d( LOG_TAG, "unlockCamMutex release" );
		m_CamMutex.release();
	}


	//========================================================================
	void startupCamCaptureMgr() 
	{
		if( false == this.m_ThreadStarted )
		{	
			m_ThreadStarted 		= true;
			m_iWhichCam 			= m_MyApp.getMySettings().getActiveCamSourceId();	
			m_iCamRotation 			= m_MyApp.getMySettings().getCamRotation( m_iWhichCam );
			if( m_iCamRotation != 0 && m_iCamRotation != 90 && m_iCamRotation != 270 && m_iCamRotation != 180 )
			{
				m_iCamRotation = 0;
			}
			
			NativeRxFrom.wantToGuiHardwareControl( this, true );
			this.start();
		}
	}

	//========================================================================
	void shutdownCamCaptureMgr() 
	{
		m_WantCamCapture = false;
		enableCameraUpdateTimer( false );
		NativeRxFrom.wantToGuiHardwareControl( this, false );
		releaseCamera();
		m_KeepHardwareAlive = false;
		if( true == m_ThreadStarted )
		{
			m_ThreadStarted = false;
			joinThread();
		}
	}
	
	//========================================================================
	public static boolean wantCamFrames()
	{
		return m_WantCamCapture;
	}
	
	//========================================================================
	public boolean isCamReady()
	{
		return m_CamIsReady;
	}
	
	//========================================================================
	private void enableCameraUpdateTimer( boolean enable )
	{
		m_UpdateTimerEnable = enable;
	}

	//========================================================================
	public void joinThread()
	{
		m_KeepHardwareAlive = false;
		while( isAlive() )
		{
			try
			{
				join();
			}
			catch( InterruptedException e )
			{
				// Ignore.
			}
		}
	}

	//========================================================================
	@Override
	public void run()
	{
	    final String orgName = Thread.currentThread().getName();
	    Thread.currentThread().setName( orgName + " CamCaptureMgr" );		
		while( true == m_KeepHardwareAlive )
		{
			try
			{
				sleep( 1000 );
			}
			catch( InterruptedException e )
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			if( false == m_KeepHardwareAlive )
			{
				break;
			}

	    	lockCamMutex();
	    	if( ( false == m_WantCamCapture ) 
	    		|| ( false == m_UpdateTimerEnable ) )
	    	{
	    		// don't want to open camera any more
	    		unlockCamMutex();
	    		continue;
	    	}
    	
	    	if( false == startCamCapture() )
	    	{
	    		// failed to start.. probably cam surface not yet ready so try again later
	    		unlockCamMutex();
	    		continue;       		
	    	}
	    	
	    	unlockCamMutex();
	    	// success.. don't need timer any more
	    	m_UpdateTimerEnable = false;
		}	
		
		Log.d( LOG_TAG, "CamCaptureMgr exiting thread" );
    }

	//========================================================================
	@Override
	public void doGuiShutdownHardware()
	{
		doGuiWantVideoCapture( false );
		m_KeepHardwareAlive = false;
	}

	//========================================================================
	@Override
	public void doGuiWantMicrophoneRecording( boolean wantMicInput )
	{
	}

	//========================================================================
	@Override
	public void doGuiWantSpeakerOutput( boolean wantSpeakerOutput )
	{
	}

	//========================================================================
	@Override
	public void doGuiWantVideoCapture( boolean wantVideoCapture )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		if( m_WantCamCapture != wantVideoCapture )
		{
			lockCamMutex();
			m_WantCamCapture = wantVideoCapture;
			if( false == wantVideoCapture )
			{
				m_CamIsReady = false;
			}
			
			setPreviewVisible( m_WantCamCapture );
			Log.d( LOG_TAG, "CamCaptureMgr doGuiWantVideoCapture updateCapture" );
			updateCapture();
			unlockCamMutex();
			Log.d( LOG_TAG, "CamCaptureMgr doGuiWantVideoCapture" );
		}
	}
	
	//========================================================================
	public void setRotation( int iCamRotation )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		if( iCamRotation != m_iCamRotation )
		{		
			m_iCamRotation = iCamRotation;
			
			if( m_iCamRotation != 0 && m_iCamRotation != 90 && m_iCamRotation != 270 && m_iCamRotation != 180 )
			{
				m_iCamRotation = 0;
			}
			
			m_MyApp.getMySettings().setCamRotation( m_iWhichCam, m_iCamRotation );
			updateCapture();
		}
	}
	
	//========================================================================
	public int getRotation()
	{
		return m_iCamRotation;
	}
	
	//========================================================================
	public void incrementRotation()
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		int newRot = m_iCamRotation;
		
		if( newRot < 90 )
		{
			newRot = 0;
		}
		
		newRot += 90;
		if( newRot >= 360 )
		{
			newRot -= 360;
		}
		
		setRotation( newRot );
	}
	
	//========================================================================
	public void switchCameras()
	{		
		if( Constants.eCameraFront == m_iWhichCam )
		{
			setWhichCamera( Constants.eCameraBack );
		}
		else
		{
			setWhichCamera( Constants.eCameraFront );			
		}
	}
	
	//========================================================================
	public void setWhichCamera( int iWhichCamPreference )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		if( iWhichCamPreference != m_iWhichCam )
		{
			m_iWhichCam = iWhichCamPreference;
			m_MyApp.getMySettings().setActiveCamSourceId( m_iWhichCam );	
			m_iCamRotation 			= m_MyApp.getMySettings().getCamRotation( m_iWhichCam );		
			updateCapture();
		}
	}
	
	//========================================================================
	public int getWhichCamera()
	{
		return m_iWhichCam;
	}
	
	//========================================================================
	@SuppressLint("NewApi") @SuppressWarnings("deprecation")
	private int getNumberOfCameras()
	{
		return Camera.getNumberOfCameras();
	}
	
	//========================================================================
	public int getCameraListCount()
	{
		return getNumberOfCameras();
	}

	//========================================================================
	public void setCamActivity( Activity curActivity, int previewSurfaceId, int noPreviewResourceId )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		// NOTE: on droidx if preview surface is not at least 80px x 60px then will get waiting for buffers errors instead of preview so 80px x 60px is min surface size
		if( m_oCamPreviewActivity != curActivity )
		{
			Log.d( LOG_TAG, "CamCaptureMgr setCamActivity start" );
			lockCamMutex();
			m_oPreviewSurface 		= null;
			m_SurfaceCreated		= 0;
			m_CreatedSurfaceHolder	= null;
			m_PreviewStarted		= false;
			m_PreviewFrameVisible 	= false;
			m_PreviewFrame  		= null;
			m_NoPreviewImage  		= null;
			
			m_oCamPreviewActivity = curActivity;
			if( null != m_oCamPreviewActivity )
			{
				m_PreviewFrame = (FrameLayout)m_oCamPreviewActivity.findViewById( previewSurfaceId );
				m_NoPreviewImage = (ImageView)m_oCamPreviewActivity.findViewById( noPreviewResourceId );
				if( null != m_PreviewFrame )
				{				
					m_oPreviewSurface = new CameraPreviewSurface( m_oCamPreviewActivity );
					m_oPreviewSurface.m_oCameraMgr = this;
					m_PreviewFrame.addView( m_oPreviewSurface );
				}
				else
				{
					Log.e( LOG_TAG, "ERROR setCamActivity NULL preview Frame ERROR ");					
				}
				
				// this forces the preview surface to be created else callbackSurfaceCreated and callbackSurfaceDestroyed will not be called if not already in capture mode
				setPreviewVisible( m_WantCamCapture );
				updateCapture();
				Log.d( LOG_TAG, "CamCaptureMgr setCamActivity done" );
			}
			
			unlockCamMutex();
		}
	}
	
	//========================================================================
	public void	updateCapture()
	{	
		enableCameraUpdateTimer( false );
		releaseCamera();
		
		setPreviewVisible( m_WantCamCapture );
		if( false == m_WantCamCapture ) 
		{
			return;
		}
		
		if( false == m_KeepHardwareAlive )
		{
			// don't try to restart camera
			return;
		}
		
		if( ( false == isCameraSurfaceReady() )
			|| ( false == startCamCapture() ) )
		{
			// cannot yet start cam capture.. start timer to keep checking until we can
			enableCameraUpdateTimer( true );
		}
	}
	
	//========================================================================
	private boolean	isCameraSurfaceReady()
	{
		if( ( null == m_oCamPreviewActivity )
			|| ( null == m_oPreviewSurface )
			|| ( 0 >= m_SurfaceCreated ) )
		{
			return false;
		}
		
		return true;
	}
	
	
	//========================================================================
	@SuppressLint("NewApi") private boolean startCamCapture()
	{
		if( false == isCameraSurfaceReady() )
		{
			return false;
		}
			
		if( null == m_oPreviewSurface.getHolder() )
		{
			// this should never happen
			Log.e(LOG_TAG, "null m_oPreviewSurface.getHolder() " );
			return false;
		}
		
		if( false == m_PreviewStarted )		
		{
			Log.e( LOG_TAG, "startCamCapture 1" );
	        int whichCam = m_iWhichCam;	        
	        if( ( Camera.getNumberOfCameras() == 1 )
	        	&& ( whichCam == Constants.eCameraFront ) )	
	        {
	        	// don't have a front camera
	        	whichCam = Constants.eCameraBack;
	         }

	        m_oCamera = Camera.open( whichCam );
	        if( null == m_oCamera )
	        {
	        	Log.e(LOG_TAG, "Could not open camera " + whichCam );
	        	return false;
	        }

	        try 
	        {        	
				m_oCamera.setPreviewCallbackWithBuffer(null);
				m_oCamera.setPreviewDisplay( m_oPreviewSurface.m_oHolder );
			} 
	        catch (IOException e) 
	        {
				Log.e( LOG_TAG, "startCamCapture exception" );
				e.printStackTrace();
				return false;
			} 

			Camera.Parameters parameters = m_oCamera.getParameters();
		
			parameters.setPreviewSize( m_CaptureWidth, m_CaptureHeight );
	        parameters.setPreviewFormat( ImageFormat.NV21 );
	        
        	parameters.setPreviewFrameRate( 12 );
	        List<String> focusModes = parameters.getSupportedFocusModes();
	        if (focusModes.contains(android.hardware.Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO)) 
	        {
	        	parameters.setFocusMode(android.hardware.Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);
	        }
	        
	        Log.e( LOG_TAG, "startCamCapture 2" );
	        parameters.setRecordingHint(true);
	        m_oCamera.setParameters(parameters);
	        parameters = m_oCamera.getParameters();
			Size actualSize 			= parameters.getPreviewSize();
			//int actualPreviewFormat 	= parameters.getPreviewFormat();
			//int actualPictureFormat 	= parameters.getPictureFormat();	
            // Log.e( LOG_TAG, "Actual cam size x=" + actualSize.width + " y=" + actualSize.height + 
            //		" preview format " + actualPreviewFormat + " picture format " + actualPictureFormat );
	        if( actualSize.width != m_CaptureWidth || actualSize.height != m_CaptureHeight ) 
	        {
	            Log.e( LOG_TAG, "Bad reported size, wanted " + m_CaptureWidth + "x" + m_CaptureHeight + ", got " +
	            		actualSize.width + "x" + actualSize.height );
	            releaseCamera();
	            return false;
	        }

	        m_iPixelFormat = parameters.getPreviewFormat();
	        if( ( m_iPixelFormat != ImageFormat.NV21 ) 
	        	&& ( m_iPixelFormat != ImageFormat.NV16 )
	        	&& ( m_iPixelFormat != ImageFormat.YUY2 )
	        	&& ( m_iPixelFormat != ImageFormat.YV12 ) )
	        {
	        	Log.e( LOG_TAG, "Bad reported image format, wanted NV21 (" + ImageFormat.NV21 + ") got " + m_iPixelFormat );
	            releaseCamera();
	            return false;
	        }       

	        //m_oCamera.setPreviewCallbackWithBuffer(null);
	        Log.e( LOG_TAG, "startCamCapture 3" );	        
	        int previewBufSize = m_CaptureWidth * m_CaptureHeight *  ImageFormat.getBitsPerPixel( m_iPixelFormat ) / 8;
	     	m_FrameCatcher = new CamFrameCatcher();
	     	m_FrameCatcher.m_MgrCamCapture = CamCaptureMgr.this;
	     	
	     	Log.e( LOG_TAG, "startCamCapture 4" );	   
	     	setupCamFrameCallback( m_oCamera, m_FrameCatcher, previewBufSize );  
             
			m_oCamera.startPreview();
			m_PreviewStarted = true;
			m_CamIsReady = true;
			Log.e( LOG_TAG, "startCamCapture done" );	 
		}
		
		return true;
	}

	//========================================================================
	private void setPreviewVisible( boolean visible )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		if( m_PreviewFrameVisible != visible )
		{
			m_PreviewFrameVisible = visible;			
			if( null != m_NoPreviewImage )
			{
				m_NoPreviewImage.setVisibility( visible ? View.GONE : View.VISIBLE );
			}
			
			if( null != m_PreviewFrame )
			{
				m_PreviewFrame.setVisibility( visible ? View.VISIBLE : View.GONE );
			}
		}
	}
	
	//========================================================================
    @SuppressLint("NewApi") private void setupCamFrameCallback(Camera camera, CamFrameCatcher catcher, int bufferSize) 
    {
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		      
       	m_PreviewBufSize = bufferSize;
        for (int i = 0; i < VID_CAPTURE_BUFFERS; i++) 
        {
            final ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
            m_QueuedBuffers.add(buffer.array());
            camera.addCallbackBuffer(buffer.array());
        }
        
        camera.setPreviewCallbackWithBuffer(catcher);
    }
	
	//========================================================================
    protected void onPause() 
    {
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		Log.d(LOG_TAG, "onPause");  		
 		releaseCamera();
    }

	//========================================================================
    protected void onResume() 
    {
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		Log.d(LOG_TAG, "onResume");
 		updateCapture();
    }
	
	//========================================================================
	public void onDestroy() 
	{		
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		Log.d(LOG_TAG, "onDestroy");
		releaseCamera();
		m_oPreviewSurface = null;
		m_CreatedSurfaceHolder = null;
		m_oCamPreviewActivity = null;	
	}
	
	//========================================================================
	@SuppressLint("NewApi") void releaseCamera()
	{
	   	Log.d(LOG_TAG, "releaseCamera");  
	   	m_CamIsReady = false;
		if( null != m_oCamera )
		{
			// Surface will be destroyed when we return, so stop the preview.
			// Because the CameraDevice object is not a shared resource, it's very
			// important to release it when the activity is paused.
			m_oCamera.setPreviewCallbackWithBuffer(null);
			m_oCamera.stopPreview();
			try 
			{
				m_oCamera.setPreviewDisplay(null);
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}	
			//clearPreviewCallbackWithBuffer();
			m_oCamera.release();
		}

		m_oCamera = null;
	    m_QueuedBuffers.clear();
	    m_PreviewStarted = false;
	   	Log.d(LOG_TAG, "releaseCamera done");  
	}

	//========================================================================
	public void callbackSurfaceCreated(SurfaceHolder holder) 
	{	
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		//Log.i(LOG_TAG, "callbackSurfaceCreated");
		if( null == m_CreatedSurfaceHolder )
		{
			m_CreatedSurfaceHolder = holder;
			m_SurfaceCreated = 1;
		}
	}

	//========================================================================
	public void callbackSurfaceDestroyed(SurfaceHolder holder) 
	{	
		if( ( null == m_CreatedSurfaceHolder ) || ( m_CreatedSurfaceHolder == holder ) )
		{
			//Log.i(LOG_TAG, "callbackSurfaceDestroyed");
			m_SurfaceCreated = 0;
		}
	}

	//========================================================================
	public void callbackSurfaceChanged(SurfaceHolder holder, int format, int width, int height) 
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		//Log.i(LOG_TAG, "callbackSurfaceChanged width " + width + " height " + height );
		if( 0 != width && 0 != height )
		{
			//updateCapture();
		}
	}
}    

