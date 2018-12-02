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
import java.util.ArrayList;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Camera;
import android.graphics.ImageFormat;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CaptureRequest;
import android.os.SystemClock;
import android.util.Log;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CaptureRequest;
import android.media.Image;
import android.media.Image.Plane;
import android.media.ImageReader;

import java.util.Arrays;


public class CamCaptureMgr2 implements ToGuiHardwareControlInterface
{
	private static final String LOG_TAG 				= "CamCapture2:";
	private static int			VID_CAPTURE_BUFFERS 	= 32;
	private static int			ELAPSE_MS_PER_FRAME 	= 80;
	
	MyApp 						m_MyApp 				= null;
	
	Camera 						m_oCamera				= null;
	int 						m_CaptureWidth 			= 320;
	int 						m_CaptureHeight 		= 240;
	int 						m_iPixelFormat 			= 0;
	
	public Activity 			m_oCamPreviewActivity 	= null;

	
	int 						m_iCamRotation 			= 0;
	int 						m_iWhichCam 			= Constants.eCameraBack;	
	int							m_CurrentCamActive		= Constants.eCameraBack;
	private static boolean 		m_WantCamCapture 		= false;
	private static boolean 		m_KeepHardwareAlive 	= true;
	private static boolean 		m_StartupWasCalled 		= false;
	
	private CameraManager 		m_CameraManager			= null;
    private CameraDevice 		m_CameraDevice			= null;
    private CameraCaptureSession m_CaptureSession		= null;
    private ImageReader 		m_ImageReader			= null;
    private boolean				m_CaptureEnabled		= false;
    private static long			m_LastFrameTimeMs 		= 0;
 
	//========================================================================
    private CameraDevice.StateCallback m_CameraStateCallback = new CameraDevice.StateCallback() 
    {
        @Override
        public void onOpened( CameraDevice cameraDevice ) 
        {
        	Log.d( LOG_TAG, "CameraDevice.StateCallback onOpened SUCCESS ");
        	CamCaptureMgr2.this.onCameraDeviceOpened( cameraDevice );
        }

        @Override
        public void onDisconnected( CameraDevice cameraDevice ) 
        {
        	Log.d( LOG_TAG, "CameraDevice.StateCallback onDisconnected ");
        }

        @Override
        public void onError( CameraDevice cameraDevice, int error) 
        {
        	Log.e( LOG_TAG, "CameraDevice.StateCallback onError " + error );
        }
    };

	//========================================================================
    private CameraCaptureSession.StateCallback m_SessionStateCallback = new CameraCaptureSession.StateCallback() 
    {
        @Override
        public void onConfigured(CameraCaptureSession session) 
        {
        	CamCaptureMgr2.this.m_CaptureSession = session;
            try 
            {
                session.setRepeatingRequest( createCaptureRequest(), null, null );
            } 
            catch (CameraAccessException e)
            {
                Log.e(LOG_TAG, e.getMessage());
            }
        }

        @Override
        public void onConfigureFailed(CameraCaptureSession session) 
        {
        	Log.e( LOG_TAG, "CameraCaptureSession onConfigureFailed" );
        }
    };

	//========================================================================
    private ImageReader.OnImageAvailableListener m_OnImageAvailableListener = new ImageReader.OnImageAvailableListener() 
    {
        @Override
        public void onImageAvailable(ImageReader reader)
        {
            Image img = reader.acquireLatestImage();
            if( null != img )
            {
	            //Log.d( LOG_TAG, "CamCaptureMgr ImageReader.OnImageAvailableListener acquired image" );
	            processCamCaptureImage( img );
	            img.close();
            }
            else
            {
            	Log.e( LOG_TAG, "CamCaptureMgr NULL ImageReader.OnImageAvailableListener image" );
            }
        }
    };	

	//========================================================================
	CamCaptureMgr2( MyApp oMyApp ) 
	{
		m_MyApp = oMyApp;
	}

	//========================================================================
	void startup() 
	{
		if( m_StartupWasCalled )
		{
			Log.e( LOG_TAG, "CamCaptureMgr startupCamCaptureMgr was already called" );
		}
		else
		{
			m_StartupWasCalled = true;
			m_iWhichCam 			= m_MyApp.getMySettings().getActiveCamSourceId();	
			m_iCamRotation 			= m_MyApp.getMySettings().getCamRotation( m_iWhichCam );
			if( m_iCamRotation != 0 && m_iCamRotation != 90 && m_iCamRotation != 270 && m_iCamRotation != 180 )
			{
				m_iCamRotation = 0;
			}

			m_CameraManager = (CameraManager) m_MyApp.getMainActivity().getSystemService(m_MyApp.getMainActivity().CAMERA_SERVICE);
			//Log.d( LOG_TAG, "CamCaptureMgr::startup Total Camera Count " + getCameraListCount() );
			NativeRxFrom.wantToGuiHardwareControl( this, true );
		}
	}

	//========================================================================
	void shutdown() 
	{
		m_WantCamCapture = false;
		stopCapture();
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
			m_WantCamCapture = wantVideoCapture;
			updateCapture();
		}
	}

	//========================================================================
    private void processCamCaptureImage( Image image )
    {
    	Log.e( LOG_TAG, "");
    	// we want about 12 frames per second = 1/12 = .083 or 83 ms
	   	long timeNowMs = System.currentTimeMillis();		
		if( ( timeNowMs - m_LastFrameTimeMs ) < ELAPSE_MS_PER_FRAME )
		{
			return; // don't process this frame.. not enough time elapsed
		}
		
		m_LastFrameTimeMs = timeNowMs;	
        // image is in YUV_420_888 android format.. 
		try
	    {
	        Image.Plane yPlane = image.getPlanes()[0]; 
	        Image.Plane uPlane = image.getPlanes()[1]; 
	        Image.Plane vPlane = image.getPlanes()[2]; 
	        ByteBuffer yBuf = yPlane.getBuffer();
	        ByteBuffer uBuf = uPlane.getBuffer();
	        ByteBuffer vBuf = vPlane.getBuffer();

	        byte[] yBytes = new byte[yBuf.remaining()];
	        yBuf.rewind();
	        yBuf.get(yBytes);
	        
	        byte[] uBytes = new byte[uBuf.remaining()];
	        uBuf.rewind();
	        uBuf.get(uBytes);
	        
	        byte[] vBytes = new byte[vBuf.remaining()];
	        vBuf.rewind();
	        vBuf.get(vBytes);

	        NativeTxTo.fromGuiYUV420CaptureImage( 	yBytes, uBytes, vBytes, 
	        									yPlane.getRowStride(), uPlane.getRowStride(), vPlane.getRowStride(), 
	        									yPlane.getPixelStride(), uPlane.getPixelStride(), vPlane.getPixelStride(),
	        									image.getWidth(), image.getHeight(), m_iCamRotation );
	    }
	    catch (Exception e)
	    {
	    	e.printStackTrace();
	    }
	
		//timeNowMs = System.currentTimeMillis();
		//Log.d( LOG_TAG, "processCamCaptureImage convert time ms " + (timeNowMs - m_LastFrameTimeMs) );
    }
     
	//========================================================================
	public void setRotation( int iCamRotation )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		m_iCamRotation = iCamRotation;
		
		if( m_iCamRotation != 0 && m_iCamRotation != 90 && m_iCamRotation != 270 && m_iCamRotation != 180 )
		{
			m_iCamRotation = 0;
		}
		
		m_MyApp.getMySettings().setCamRotation( m_iWhichCam, m_iCamRotation );
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
		
		if( m_iCamRotation < 90 )
		{
			m_iCamRotation = 0;
		}
		
		m_iCamRotation += 90;
		if( m_iCamRotation >= 360 )
		{
			m_iCamRotation -= 360;
		}
		
		setRotation( m_iCamRotation );
	}
	
	//========================================================================
	public void switchCameras()
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
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
	@SuppressLint("NewApi") public int getCameraListCount()
	{
		if( null !=  m_CameraManager )
		{
			try
			{
				return  m_CameraManager.getCameraIdList().length;
			}
			catch( CameraAccessException e )
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		return 0;
	}

	//========================================================================
	@SuppressLint("NewApi") public String getCurCameraId()
    {
    	String defaultCameraId = "";
        try 
        {
            for( String cameraId : m_CameraManager.getCameraIdList() ) 
            {
            	if( defaultCameraId.isEmpty() )
            	{
            		defaultCameraId = cameraId;
            	}
            	
                CameraCharacteristics characteristics = m_CameraManager.getCameraCharacteristics( cameraId );
                int cOrientation = characteristics.get( CameraCharacteristics.LENS_FACING );
                if( ( cOrientation ==  CameraCharacteristics.LENS_FACING_FRONT )
                	&& ( m_iWhichCam == Constants.eCameraFront ) )
                {
                    return cameraId;
                }
                
                if( ( cOrientation ==  CameraCharacteristics.LENS_FACING_BACK )
                	&& ( m_iWhichCam == Constants.eCameraBack ) )
                {
                    return cameraId;
                }
            }
        } 
        catch( CameraAccessException e )
        {
            e.printStackTrace();
        }
        
        return defaultCameraId;
    }

	//========================================================================
	public void	updateCapture()
	{
		stopCapture();
		if( false == m_WantCamCapture )
		{
			return;
		}
		
        try 
        {
            m_ImageReader = ImageReader.newInstance( 320, 240, ImageFormat.YUV_420_888, VID_CAPTURE_BUFFERS ); //fps * 10 min
            m_ImageReader.setOnImageAvailableListener( m_OnImageAvailableListener, null);
            Log.d( LOG_TAG, "updateCapture Opening Camera "  );
            m_CameraManager.openCamera( getCurCameraId(), m_CameraStateCallback, null);
        } 
        catch (CameraAccessException e)
        {
            Log.e( LOG_TAG, e.getMessage());
            return;
        }
	}
	
	//========================================================================
    public void onCameraDeviceOpened( CameraDevice cameraDevice )
    {   
		if( null != cameraDevice )
		{
	        try 
	        {
	        	m_CameraDevice = cameraDevice;
	        	if( null != m_ImageReader )
	        	{
	        		m_CameraDevice.createCaptureSession( Arrays.asList( m_ImageReader.getSurface()), m_SessionStateCallback, null );
	        		m_CaptureEnabled = true;
	        	}
	        } 
	        catch (CameraAccessException e)
	        {
	            Log.e(LOG_TAG, e.getMessage());
	        }
		}
    }
	
	//========================================================================
    private void stopCapture()
    {
    	if( m_CaptureEnabled )
    	{
    		m_CaptureEnabled = false;
    		try 
	        {
				if(  null != m_CaptureSession )
				{
			        m_CaptureSession.abortCaptures();
			        m_CaptureSession.close();	
			        m_CaptureSession = null;
				}
				
				if (null != m_ImageReader) 
				{
					m_ImageReader.close();
					m_ImageReader = null;
		        }
				
				if( null != m_CameraDevice )
				{
					m_CameraDevice.close();
					m_CameraDevice = null;
				}
		    } 
		    catch (CameraAccessException e)
		    {
		        Log.e( LOG_TAG, e.getMessage());
		    } 
    	}		
    }

	//========================================================================
    private CaptureRequest createCaptureRequest() 
    {
    	if( ( null != m_CameraDevice )
			&& ( null != m_ImageReader ) )
		{
    		try 
    		{
    			CaptureRequest.Builder requestBuilder = m_CameraDevice.createCaptureRequest( CameraDevice.TEMPLATE_RECORD );
    			requestBuilder.addTarget( m_ImageReader.getSurface() );
    			requestBuilder.set(CaptureRequest.EDGE_MODE,
    			        CaptureRequest.EDGE_MODE_OFF);
    			requestBuilder.set(
    			        CaptureRequest.LENS_OPTICAL_STABILIZATION_MODE,
    			        CaptureRequest.LENS_OPTICAL_STABILIZATION_MODE_ON);
    			requestBuilder.set(
    			        CaptureRequest.COLOR_CORRECTION_ABERRATION_MODE,
    			        CaptureRequest.COLOR_CORRECTION_ABERRATION_MODE_OFF);
    			requestBuilder.set(CaptureRequest.NOISE_REDUCTION_MODE,
    			        CaptureRequest.NOISE_REDUCTION_MODE_OFF);
    			requestBuilder.set(CaptureRequest.CONTROL_AF_TRIGGER,
    			        CaptureRequest.CONTROL_AF_TRIGGER_CANCEL);

    			requestBuilder.set(CaptureRequest.CONTROL_AE_LOCK, true);
    			requestBuilder.set(CaptureRequest.CONTROL_AWB_LOCK, true);
    			return requestBuilder.build();
    		} 
    		catch (CameraAccessException e) 
    		{
    			Log.e( LOG_TAG, e.getMessage());
    			return null;
    		}
		}
    	
    	return null;
    }

	//========================================================================
	public void setCamActivity( Activity curActivity, int previewSurfaceId, int noPreviewResourceId )
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
	}
	
	//========================================================================
    protected void onPause() 
    {
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		//Log.d(LOG_TAG, "onPause");  		
 		//releaseCamera();
    }

	//========================================================================
    protected void onResume() 
    {
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		
		//Log.d(LOG_TAG, "onResume");
 		//updateCapture();
    }
	
	//========================================================================
	public void onDestroy() 
	{
		if( false == m_KeepHardwareAlive )
		{
			return;
		}
		//Log.e(LOG_TAG, "onDestroy");
		//releaseSurface();
	}
	
}    

