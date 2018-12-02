package com.p2pgotv.gotvstation;

import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.content.Context;

public class CameraPreviewSurface extends SurfaceView implements SurfaceHolder.Callback 
{
	private static final String LOG_TAG = "CameraPreviewSurface:";
    public SurfaceHolder 		m_oHolder 		= null;
    public CamCaptureMgr 		m_oCameraMgr 	= null;
    Context 					m_oContext 		= null;

    //========================================================================
	public CameraPreviewSurface(Context context) 
	{
		this(context, null);
		m_oContext = context;
		m_oHolder = getHolder();
		m_oHolder.addCallback(this);
		m_oHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

    //========================================================================
	public CameraPreviewSurface(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
		m_oContext = context;
		m_oHolder = getHolder();
		m_oHolder.addCallback(this);
		m_oHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	/*	
	@Override
    protected void onMeasure( int widthMeasureSpec, int heightMeasureSpec )
    {  
    	// keep aspect ratio
    	float aspectRatio = 240.0f / 320.0f; 	
    	int width = MeasureSpec.getSize(widthMeasureSpec);	
    	int height = (int)( width * aspectRatio );
    	
        //this.setMeasuredDimension( 32, 24 );  
        this.setMeasuredDimension( width, height );  
    }
    */
    
    //========================================================================
	@Override
    public void surfaceCreated( SurfaceHolder holder ) 
    {
    	if( null != m_oCameraMgr )
    	{
    		m_oCameraMgr.callbackSurfaceCreated( holder );
    	}
    	else
    	{
    		Log.e( LOG_TAG, "CameraPreviewSurface Created without manager " );
    	}
    }

    //========================================================================
    @Override
    public void surfaceDestroyed(SurfaceHolder holder) 
    {
    	if( null != m_oCameraMgr )
    	{
    		m_oCameraMgr.callbackSurfaceDestroyed( holder );
    	}
    }

    //========================================================================
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) 
    {
    	if( null != m_oCameraMgr )
    	{
    		m_oCameraMgr.callbackSurfaceChanged( holder, format, w, h );
    	}
    }
}
