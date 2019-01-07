package com.p2pgotv.gotvstation;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;

/*
class MyGlSurfaceView extends GLSurfaceView 
{
	private static final String LOG_TAG = "MyGlSurfaceView: ";

	ActivityAudioClip				m_oActivity = null;
    MyGlSurfaceRenderer 			m_oRenderer = null;
    
	//========================================================================
    public MyGlSurfaceView(Context context) 
    {
    	super(context);
    	//m_oContext = context;
    }
    
	//========================================================================
   	public MyGlSurfaceView (Context context, AttributeSet attrs) 
   	{ 
   		super(context, attrs); 
   		//m_oContext = context;
    } 

	//========================================================================
    public void Startup( ActivityAudioClip oActivity )
    {
    	m_oActivity = oActivity;
    	Log.e(LOG_TAG, "constructing renderer" );
    	m_oRenderer = new MyGlSurfaceRenderer(oActivity);
    	setRenderer(m_oRenderer);
    	Log.e(LOG_TAG, "constructing renderer done" );
    }

	//========================================================================
    public boolean onTouchEvent(final MotionEvent oEvent) 
    {
    	int iAction 	= oEvent.getAction();
    	int iPosX 		= (int) oEvent.getX();
    	int iPosY 		= (int) oEvent.getY();
        //Log.e(LOG_TAG, "Mouse event " +  iAction );  
        if( 0 == iAction )
        {
            //Log.e(LOG_TAG, "Mouse down " +  iPosX + " " + iPosY );        	
        }
        
        NativeTxTo.fromGuiTouchEvent( iAction, iPosX, iPosY );     
        return true;
    }    
}

//========================================================================
//========================================================================
class MyGlSurfaceRenderer implements GLSurfaceView.Renderer 
{ 
	//=== vars ===//
	ActivityAudioClip	m_oActivity;
	private static final String LOG_TAG = "MyGlSurfaceRenderer: ";
	
	//========================================================================
	MyGlSurfaceRenderer(ActivityAudioClip oActivity)
	{
		m_oActivity = oActivity;
	}
	
	//========================================================================
 	public void onSurfaceCreated(GL10 gl, EGLConfig config) 
    {
        Log.e(LOG_TAG, "onSurfaceCreated: calling fromGuiNativeGlInit" );
 		NativeTxTo.fromGuiNativeGlInit();
		NativeRxFrom.toGuiWantMicrophoneRecording( true );
        Log.e(LOG_TAG, "onSurfaceCreated: calling fromGuiNativeGlInit Done" );
    }
    
 	//========================================================================
	public void onSurfaceChanged(GL10 gl, int w, int h) 
    {
        Log.e(LOG_TAG, "onSurfaceChanged: width=" + w + "height=" + h );
    	NativeTxTo.fromGuiNativeGlResize(w, h);
        Log.e(LOG_TAG, "onSurfaceChanged: Done" );
    }
    
 	//========================================================================
	public void onSurfaceDestroyed(GL10 gl)
    {
		// BUG BUG this never gets called
        Log.e(LOG_TAG, "onSurfaceDestroyed:" );
       	m_oActivity.shutdownRequestedFromGl();
        Log.e(LOG_TAG, "onSurfaceDestroyed: done" );
    }
    
    //========================================================================
	public void onDrawFrame(GL10 gl) 
    {
    	if( null != m_oActivity )
    	{
	        //Log.e(LOG_TAG, "render start" );
    		int iShutdownRequested = NativeTxTo.fromGuiNativeGlRender();
    		if( -3 == iShutdownRequested )
    		{
    	        Log.e(LOG_TAG, "Shutdown requested" );
    			m_oActivity.shutdownRequestedFromGl();
    		}
	        //Log.e(LOG_TAG, "render done" );
    	}
    }
}
*/
