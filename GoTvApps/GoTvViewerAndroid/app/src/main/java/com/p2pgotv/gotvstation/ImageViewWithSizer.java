package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.concurrent.Semaphore;

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
public class ImageViewWithSizer extends ImageView implements MediaCallbackInterface 
{
	private static final String LOG_TAG = "ImageViewWithSizer:";
	
	private int 				m_iFinalWidth 		= 0;
	private int 				m_iFinalHeight 		= 0;
	private ImageView			m_oImageView 		= null;
	ViewTreeObserver			m_oViewObserver 	= null;
	boolean						m_bIsInitialized 	= false;
	float 						m_f32AspectRatio 	= 0.75f;	
	int							m_CurRotation 		= 0;
	int							m_NewRotation 		= 0;
	int							m_iBmpWidth 		= 0;
	int							m_iBmpHeight 		= 0;
	float						m_f32ViewScale 		= 1.0f;
	private VxGUID 				m_VidFeedId			= null;
	private int					m_RequestMediaType  = Constants.eMediaInputVideoJpgSmall;
	private boolean				m_FeedRequested 	= false;
	private Semaphore 			m_ImageMutex 		= new Semaphore(1); 
	private ArrayList<Bitmap> 	m_ImageList 		= new ArrayList<Bitmap>();
	public boolean				m_IsThumbnail		= false;
	private Bitmap				m_LoadedBitmap		= null;
	boolean						m_WindowIsVisible 	= false;
	boolean						m_LastWantMedia 	= false;


	//============================================================================
	public ImageViewWithSizer(Context context) 
	{
		super(context);
		setImageView( this );
		Log.i(LOG_TAG, "ImageViewWithSizer create" );
	}

	//============================================================================
	public ImageViewWithSizer(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
		setImageView( this );
		Log.i(LOG_TAG, "ImageViewWithSizer create" );
	}

	//============================================================================
	public ImageViewWithSizer(Context context, AttributeSet attrs, int defStyle) 
	{
		super(context, attrs, defStyle);
		setImageView( this );
		Log.i(LOG_TAG, "ImageViewWithSizer create" );
	}
	
	//============================================================================
	public void setCamViewImage( int drawableResourceId )
	{
		if( null != m_oImageView )
		{
			m_LoadedBitmap =  BitmapFactory.decodeResource(getResources(), drawableResourceId );
			updateLoadedBitmap();
		}
	}

    //============================================================================
    void showOfflineImage()
    {
    	setCamViewImage( R.drawable.ic_cam_black );
    }
	
	//============================================================================
	void setVisible( boolean isVisible )
	{
		if( null != m_oImageView )
		{
			if( isVisible )
			{
				m_WindowIsVisible = true;
				m_oImageView.setVisibility( View.VISIBLE );
			}
			else
			{
				m_oImageView.setVisibility( View.GONE );
				m_WindowIsVisible = false;
			}
			
			updateWindowVisibilityChange();
		}
	}

    //============================================================================
    void setVidImageRotation( int imageRotation )
    {
    	m_NewRotation = imageRotation;
    }

    //============================================================================
    int getVidImageRotation()
    {
    	return m_NewRotation;
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
	VxGUID getVideoFeedId()
	{
		return m_VidFeedId;
	}

	//============================================================================
	public boolean isMyVideoFeed( VxGUID guidId )
	{
		if( ( null != m_VidFeedId )
			&& m_VidFeedId.equals( guidId )  )
		{
			return true;
		}	
		
		return false;
	}
	
	//============================================================================
	void setRequestMediaType( int mediaInputType )
	{
		m_RequestMediaType = mediaInputType;
	}
	
	//============================================================================
	int getRequestMediaType()
	{
		return m_RequestMediaType;
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
			if( Constants.eMediaInputNone != m_RequestMediaType )
			{
				m_FeedRequested = true;
				NativeRxFrom.wantMediaCallbackClient( this, true );
				m_LastWantMedia = true;
				NativeTxTo.fromGuiWantMediaInput( m_VidFeedId.m_u64IdHiPart, m_VidFeedId.m_u64IdLoPart, m_RequestMediaType,  m_LastWantMedia );
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
			if( Constants.eMediaInputNone != m_RequestMediaType )
			{
				m_FeedRequested = false;
				NativeRxFrom.wantMediaCallbackClient( this, false );
				m_LastWantMedia = false;
				NativeTxTo.fromGuiWantMediaInput( m_VidFeedId.m_u64IdHiPart, m_VidFeedId.m_u64IdLoPart, m_RequestMediaType,  m_LastWantMedia );
			}
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
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
		m_VidFeedId 		= feedId;
		m_RequestMediaType 	= reqestMediaType;
		requestVideoFeed();
	}
	   
	//============================================================================
	@Override
	protected void onWindowVisibilityChanged( int visiblity ) 
    {
		//Log.i( LOG_TAG, "ImageViewWithSizer onWindowVisibilityChanged " + visiblity );
		m_WindowIsVisible = (0 == visiblity);
        super.onWindowVisibilityChanged(visiblity);
        updateWindowVisibilityChange();
   }
	
	//============================================================================
	protected void updateWindowVisibilityChange()
	{
		if( ( null != m_VidFeedId ) 
			&& ( Constants.eMediaInputNone != m_RequestMediaType ) )
		{
			boolean isVisible = m_WindowIsVisible && ( m_iFinalWidth > 10 ) && ( m_iFinalHeight > 10 );
			boolean wantMedia = isVisible && m_FeedRequested;
			if( wantMedia != m_LastWantMedia )
			{	
				m_LastWantMedia = wantMedia;
				NativeTxTo.fromGuiWantMediaInput( m_VidFeedId.m_u64IdHiPart, m_VidFeedId.m_u64IdLoPart, m_RequestMediaType,  m_LastWantMedia );
			}
			
			if( m_FeedRequested )
			{
				try 
				{
					if( wantMedia )
					{
						NativeRxFrom.wantMediaCallbackClient( this, true );
					}
					else
					{
						NativeRxFrom.wantMediaCallbackClient( this, false );				
					}			
				} 
				catch (InterruptedException e) 
				{
					e.printStackTrace();
				}
			}
		}
		
    } 
	
	//============================================================================
    @Override
    protected void onMeasure( int widthMeasureSpec, int heightMeasureSpec )
    {  
    	// keep aspect ratio
    	int width = MeasureSpec.getSize(widthMeasureSpec);	
    	int height = (int)( width * m_f32AspectRatio ); 
        this.setMeasuredDimension( width, height );  
        if( ( width != m_iFinalWidth )
        	|| ( height != m_iFinalHeight ) )
        {
        	if( ( 0 != width ) && ( 0 != height ) )
        	{
               	m_iFinalHeight 		= height;
            	m_iFinalWidth 		= width;
            	updateLoadedBitmap();
            	updateWindowVisibilityChange();
        	}
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
	@Override
	public void setVisibility( int visibleFlag )
	{
		if( null != m_oImageView )
		{
			if( this != m_oImageView )
			{
				m_oImageView.setVisibility( visibleFlag );
			}
		}
		
		super.setVisibility( visibleFlag );
	}

	//============================================================================
	boolean scaleAndRotateToView( Bitmap myBitmap )
	{
		if( ( false == m_bIsInitialized )
			|| ( null == myBitmap ) )
		{
			return false;
		}
		
		int iBmpWidth = myBitmap.getWidth();
		int iBmpHeight = myBitmap.getHeight();
		if(( 0 >= iBmpWidth ) || ( 0 >= iBmpHeight ) )
		{
			return false;
		}
		
		if( m_NewRotation >= 360 )
		{
			m_NewRotation -= 360;
		}
				
		if( ( m_iBmpWidth != iBmpWidth ) 
			|| ( m_iBmpHeight != iBmpHeight )
			|| ( m_NewRotation != m_CurRotation ) )
		{
			m_iBmpWidth 	= iBmpWidth;
			m_iBmpHeight 	= iBmpHeight;
			m_CurRotation	= m_NewRotation;
		
			float f32ViewWidth 		= ((float)m_iFinalWidth) * m_f32ViewScale;
			float f32ViewHeight 	= ((float)m_iFinalHeight) * m_f32ViewScale;
			
			float f32ImageScale 	= f32ViewWidth / (float)iBmpWidth;
			if( ( 90 == m_CurRotation ) || ( 270 == m_CurRotation ) )
			{
				f32ImageScale =  f32ViewHeight / (float)iBmpWidth;
			}
			
			Matrix matrix = new Matrix();	
			matrix.preScale( f32ImageScale, f32ImageScale );
	
			if( 0 != m_CurRotation )
			{
				float iFinalScaledBmpWidth = f32ImageScale * (float)iBmpWidth; 
				float iFinalScaledBmpHeight = f32ImageScale * (float)iBmpHeight; 
				matrix.postRotate( (float)m_CurRotation, iFinalScaledBmpWidth/2, iFinalScaledBmpHeight/2 );
				if( ( 270 == m_CurRotation ) || ( 90 == m_CurRotation ) )
				{
					matrix.postTranslate( (f32ViewWidth - iFinalScaledBmpWidth)/2, (f32ViewHeight - iFinalScaledBmpHeight)/2 );
				}
			}
			
			m_oImageView.setImageMatrix( matrix );
		}
					
		setImageBitmap( myBitmap );
		return true;
	}
	
	//========================================================================
	void playVideoFrame( byte[] pu8Jpg, int jpgDataLen )
	{
    	if( ( null != m_oImageView  ) 
    		&& ( 0 != m_iFinalWidth ) 
    		&& ( 0 != m_iFinalHeight ) )
    	{	
    		if( 3 > m_ImageList.size() )
    		{
		    	Bitmap lclBitmap = BitmapFactory.decodeByteArray( pu8Jpg, 0, jpgDataLen );
		    	if( null != lclBitmap )
		    	{
		    		try 
		    		{
						m_ImageMutex.acquire();
				    	m_ImageList.add(lclBitmap);
				    	m_ImageMutex.release();	
					} 
		    		catch (InterruptedException e) 
					{
						e.printStackTrace();
					}

					post( new Runnable() 
		    		{ 
		    			public void run() 
		    			{
		    				if( 0 < m_ImageList.size() )
		    				{
					    		try 
					    		{
									m_ImageMutex.acquire();
							    	for( Bitmap lclBitmap:  m_ImageList )
							    	{
							    		scaleAndRotateToView( lclBitmap );
							    	}
							    	
							    	m_ImageList.clear();
							    	m_ImageMutex.release();	
								} 
					    		catch (InterruptedException e) 
								{
									e.printStackTrace();
								}
		    				}
		     			}
		    		});			    			    		
		    	}
    		}
	    }
	    else
	    {
	    	//Log.d(LOG_TAG, "ImageViewWithSizer playVideoFrame null == m_oCamView"); 
	    }
	}

	//============================================================================
	@Override
	public 	void toGuiPlayVideoFrame( VxGUID guidId, byte[] pu8Jpg, int jpgDataLen, int motion0to100000 )
	{
		//Log.d( LOG_TAG, "CamViewBase toGuiPlayVideoFrame" ); 
		if( isMyVideoFeed( guidId ) )
		{
			//if( ( jpgDataLen > 8000 ) && ( false == m_IsThumbnail ) )
			//{
			//	Log.d( LOG_TAG, "toGuiPlayVideoFrame" ); 			
			//}
			
			playVideoFrame( pu8Jpg, jpgDataLen );
		}
		
		/*
		else
		{
			Log.d( LOG_TAG, "CamViewBase playVideoFrame NOT SAME GUID myGuid " 
							+ m_VidFeedId.getOnlineIdHiPart() + " lo " + m_VidFeedId.getOnlineIdLoPart()
							+ " hi " + guidId.getOnlineIdHiPart() + " lo " + guidId.getOnlineIdLoPart() ); 
		}*/
	}

	//============================================================================
	public boolean loadImageFromFile( String fileName )
	{
		m_LoadedBitmap = VxImageUtil.getSizedImageFromFile( fileName, m_iFinalWidth, m_iFinalHeight );
		return updateLoadedBitmap();
	}
	
	//============================================================================
	public boolean updateLoadedBitmap()
	{
		if( null != m_LoadedBitmap )
		{
			int width = m_LoadedBitmap.getWidth();
			int height = m_LoadedBitmap.getHeight();
			if( ( width != 0 ) && ( height != 0 ) )
			{
				if( ( width != m_iFinalWidth )
					&& 	( height != m_iFinalHeight ) )
				{
					if( ( 0 != m_iFinalWidth ) &&  ( 0 != m_iFinalHeight ) )
					{
						// re scale image so at least one dimension is correct
						m_LoadedBitmap = VxImageUtil.getDesiredSizeBitmap( m_LoadedBitmap, m_iFinalWidth, m_iFinalHeight );
						width = m_LoadedBitmap.getWidth();
						height = m_LoadedBitmap.getHeight();
					}
				}

				
				if( ( width != m_iFinalWidth )
					|| 	( height != m_iFinalHeight ) )
				{
					Matrix matrix = new Matrix();	
					matrix.postTranslate( (m_iFinalWidth - width)/2, (m_iFinalHeight - height)/2 );
					m_oImageView.setImageMatrix( matrix );
					m_oImageView.setImageBitmap( m_LoadedBitmap );						
				}
				else
				{
					Matrix matrix = new Matrix();	
					m_oImageView.setImageMatrix( matrix );
					m_oImageView.setImageBitmap( m_LoadedBitmap );				
				}
				
				return true;
			}
		}	
		
		return false;
	}		
}


