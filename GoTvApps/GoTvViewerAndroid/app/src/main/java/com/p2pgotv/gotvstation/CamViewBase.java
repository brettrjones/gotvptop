package com.p2pgotv.gotvstation;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewTreeObserver;
import android.widget.ImageView;

//============================================================================
public class CamViewBase extends ImageView implements MediaCallbackInterface
{
	private static final String LOG_TAG = "CHAT:";

	int 						m_iFinalHeight 			= 0;
	int 						m_iFinalWidth 			= 0;
	ImageView					m_oImageView 			= null;
	ViewTreeObserver			m_oViewObserver 		= null;
	boolean						m_bIsInitialized 		= false;
	float 						m_f32AspectRatio 		= 0.75f;
	int							m_iRotation 			= 0;
	int							m_iBmpWidth 			= 0;
	int							m_iBmpHeight 			= 0;
	float						m_f32ViewScale 			= 1.0f;
	private VxGUID 				m_VidFeedId				= null;
	private int					m_RequestMediaType  	= Constants.eMediaInputNone;
	private boolean				m_LastWantMedia 		= false;
	Bitmap 						m_LastBitmap			= null;
	
	//============================================================================
	public CamViewBase(Context context) 
	{
		super(context);
		setImageView( this );
		//Log.i(LOG_TAG, "CamViewBase create" );
	}

	//============================================================================
	public CamViewBase(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
		setImageView( this );
		//Log.i(LOG_TAG, "CamViewBase create" );
	}

	//============================================================================
	public CamViewBase(Context context, AttributeSet attrs, int defStyle) 
	{
		super(context, attrs, defStyle);
		setImageView( this );
		//Log.i(LOG_TAG, "CamViewBase create" );
	}

	//============================================================================
	public Bitmap getLastBitmap()
	{
		return m_LastBitmap;
	}
	
	//============================================================================
	void setAspectRatio( float f32AspectRatio )
	{
		m_f32AspectRatio = f32AspectRatio;
	}
	
	//============================================================================
	void setViewScale( float f32ViewScale )
	{
		m_f32ViewScale = f32ViewScale;
	}
	
	//============================================================================
	void setVideoFeedId( VxGUID feedId )
	{
		m_VidFeedId = feedId;
	}
	
	//============================================================================
	void setFeedMediaType( int reqestMediaType )
	{
		m_RequestMediaType = reqestMediaType;
	}
	
	//============================================================================
	VxGUID getVideoFeedId()
	{
		return m_VidFeedId;
	}
	
	//============================================================================
	void requestVideoFeed()
	{
		if( null == m_VidFeedId )
		{
			Log.e( LOG_TAG, "ERROR requesting Video Feed without Id" );
			return;
		}
		
		try 
		{
			NativeRxFrom.wantMediaCallbackClient( this, true );
			if( Constants.eMediaInputNone != m_RequestMediaType )
			{
				if( false == m_LastWantMedia )
				{
					m_LastWantMedia = true;
					NativeTxTo.fromGuiWantMediaInput( m_VidFeedId.m_u64IdHiPart, m_VidFeedId.m_u64IdLoPart, m_RequestMediaType, m_LastWantMedia );					
				}
			}
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//============================================================================
	void stopVideoFeed()
	{
		if( null == m_VidFeedId )
		{
			return;
		}
		
		try 
		{
			NativeRxFrom.wantMediaCallbackClient( this, false );
			if( Constants.eMediaInputNone != m_RequestMediaType )
			{
				if( true == m_LastWantMedia )
				{
					m_LastWantMedia = false;				
					NativeTxTo.fromGuiWantMediaInput( m_VidFeedId.m_u64IdHiPart, m_VidFeedId.m_u64IdLoPart, m_RequestMediaType,  m_LastWantMedia );
				}
			}
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//============================================================================
	void requestVideoFeed( int reqestMediaType )
	{
		m_RequestMediaType = reqestMediaType;
		requestVideoFeed();
	}
	
	//============================================================================
	void requestVideoFeed( VxGUID feedId )
	{
		m_VidFeedId = feedId;
		requestVideoFeed();
	}
	
	//============================================================================
	void requestVideoFeed( VxGUID feedId, int reqestMediaType )
	{
		m_VidFeedId = feedId;
		m_RequestMediaType = reqestMediaType;
		requestVideoFeed();
	}
	   
	//============================================================================
	@Override
	protected void onWindowVisibilityChanged( int visiblity ) 
    {
        super.onWindowVisibilityChanged(visiblity);
		//Log.i( LOG_TAG, "CamViewBase onWindowVisibilityChanged " + visiblity );
	
		if( ( null != m_VidFeedId )
			&& ( Constants.eMediaInputNone != m_RequestMediaType )
			&& m_LastWantMedia )
		{
			boolean wantMedia =  ( View.VISIBLE == visiblity );
			NativeTxTo.fromGuiWantMediaInput( m_VidFeedId.m_u64IdHiPart, m_VidFeedId.m_u64IdLoPart, m_RequestMediaType,  wantMedia );
		}
    } 

	//============================================================================
	void setImageView( ImageView view )
	{
		m_oImageView = view;
		m_oImageView.setScaleType(ScaleType.MATRIX);   //required
		m_oViewObserver = m_oImageView.getViewTreeObserver();
		m_oViewObserver.addOnPreDrawListener(new ViewTreeObserver.OnPreDrawListener() 
		{
		    public boolean onPreDraw() 
		    {
		    	m_iFinalWidth 		= m_oImageView.getMeasuredWidth();
		    	m_iFinalHeight 		= m_oImageView.getMeasuredHeight();
			    m_bIsInitialized 	= true;		    			
		        return true;
		    }
		});
	}

	//============================================================================
	boolean scaleAndRotateToView( Bitmap myBitmap, int rotation )
	{
		if( ( false == m_bIsInitialized ) || ( null == myBitmap ) )
		{
			return false;
		}
		
		int iBmpWidth = myBitmap.getWidth();
		int iBmpHeight = myBitmap.getHeight();
		if(( 0 >= iBmpWidth ) || ( 0 >= iBmpHeight ) )
		{
			return false;
		}
		if( rotation >= 360 )
		{
			rotation -= 360;
		}
				
		if( ( m_iRotation != rotation ) || 
			( m_iBmpWidth != iBmpWidth ) ||
			( m_iBmpHeight != iBmpHeight ) )
		{
			m_iRotation = rotation; 
			m_iBmpWidth = iBmpWidth;
			m_iBmpHeight = iBmpHeight;
		
			float f32ViewWidth = (float)m_iFinalWidth * m_f32ViewScale;
			float f32ViewHeight = (float)m_iFinalHeight * m_f32ViewScale;
			
			float f32ImageScale = f32ViewWidth / (float)iBmpWidth;
			if( ( 90 == rotation ) || ( 270 == rotation ) )
			{
				f32ImageScale =  f32ViewHeight / (float)iBmpWidth;
			}
			
			Matrix matrix = new Matrix();	
			matrix.preScale( f32ImageScale, f32ImageScale );

			float iFinalScaledBmpWidth = f32ImageScale * (float)iBmpWidth; 
			float iFinalScaledBmpHeight = f32ImageScale * (float)iBmpHeight; 
	
			if( 0 != rotation )
			{
				matrix.postRotate( (float)rotation, iFinalScaledBmpWidth/2, iFinalScaledBmpHeight/2 );
				if( ( 270 == rotation ) || ( 90 == rotation ) )
				{
					matrix.postTranslate( (f32ViewWidth - iFinalScaledBmpWidth)/2, (f32ViewHeight - iFinalScaledBmpHeight)/2 );
				}
			}
			
			m_oImageView.setImageMatrix( matrix );
		}
			
		m_LastBitmap = myBitmap;
		m_oImageView.setImageBitmap( myBitmap );
		return true;
	}
	
	//============================================================================
	public 	boolean isMyVideoFeed( VxGUID guidId )
	{
		if( ( null != m_VidFeedId )
			&& m_VidFeedId.equals( guidId )  )
		{
			return true;
		}	
		
		return false;
	}
	//========================================================================
	void playVideoFrame( byte[] pu8Jpg, int jpgDataLen )
	{
    	if( ( null != m_oImageView  ) && ( 0 != m_iFinalWidth ) && ( 0 != m_iFinalHeight ) )
    	{	
	    	final Bitmap lclBitmap = BitmapFactory.decodeByteArray( pu8Jpg, 0, jpgDataLen );
			post( new Runnable() 
    		{ 
    			public void run() 
    			{
    				scaleAndRotateToView( lclBitmap, 0 );
     			}
    		});
	    }
	}

	//============================================================================
	@Override
	public 	void toGuiPlayVideoFrame( VxGUID guidId, byte[] pu8Jpg, int jpgDataLen, int motion0to100000 )
	{
		if( isMyVideoFeed( guidId ) )
		{
			playVideoFrame( pu8Jpg, jpgDataLen );
		}		
	}
}


