package com.p2pgotv.gotvstation;

import android.app.*;
import android.content.*;
import android.util.*;
import android.view.*;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import android.os.Bundle;
import android.net.Uri;

public class ActivityPickImage extends ActivityBase 
{
	private static final String LOG_TAG = "ActivityPickImage:";
	
	private static final int 	SELECT_IMAGE_FROM_GALLERY 	= 979; // selector for image gallery call
	private int					m_eFileFilterType			= Constants.eFileFilterTypePhoto;
	
	private ImageViewWithSizer	m_PhotoView					= null;
	
	private Button 				m_SnapshotBut 				= null;
	private TextView 			m_SnapshotText 				= null;
	private Button 				m_GalleryBut 				= null;
	private TextView 			m_GalleryText 				= null;
	private Button 				m_LibraryBut 				= null;
	private TextView 			m_LibraryText 				= null;
	private Button 				m_BrowseBut 				= null;
	private TextView 			m_BrowseText 				= null;
	
	private Button 				m_AcceptBut 				= null;
	private Button 				m_CancelBut 				= null;
 	
	private Uri					m_UriPic					= null;
	private String				m_PicFileNameIn				= "";
	private String				m_PickedFileName 			= "";
	private String				m_CameraFileName 			= "";
	private int					m_eMediaSrc					= Constants.eMediaSrcUnknown;
	private boolean				m_ImageFileIsValid			= false;


	//============================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
    	requestWindowFeature(Window.FEATURE_NO_TITLE); 
        setContentView(R.layout.activity_pick_image);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_pick_image_title );
        Log.i(LOG_TAG, "onCreateCalled");
        Bundle extras = getIntent().getExtras(); 
        if( null != extras ) 
        { 
        	m_PicFileNameIn = extras.getString( Constants.PARAM_FILE_NAME );
        } 
            
        m_PhotoView		= (ImageViewWithSizer)this.findViewById(R.id.pick_image_photo_view);
         
    	m_SnapshotBut 	= (Button)this.findViewById(R.id.pick_image_camera_button);
	 	m_SnapshotBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onSnapshotButClick(v);
	 		}
	 	});
        
		m_SnapshotText 	= (TextView)this.findViewById(R.id.pick_image_camera_text);
		m_SnapshotText.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onSnapshotButClick(v);
	 		}
	 	});

    	m_GalleryBut = (Button)this.findViewById(R.id.pick_image_gallery_button);
	 	m_GalleryBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onGalleryButClick(v);
	 		}
	 	});
	 	
	 	m_GalleryText 	= (TextView)this.findViewById(R.id.pick_image_gallery_text);
	 	m_GalleryText.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onGalleryButClick(v);
	 		}
	 	});

		m_LibraryBut = (Button)this.findViewById(R.id.pick_image_library_button);
    	m_LibraryBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onLibraryButClick(v);
	 		}
	 	});
 	
    	m_LibraryText 	= (TextView)this.findViewById(R.id.pick_image_library_text);
    	m_LibraryText.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onLibraryButClick(v);
	 		}
	 	});


	 	m_BrowseBut = (Button)this.findViewById(R.id.pick_image_browse_button);
	 	m_BrowseBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onBrowseButClick(v);
	 		}
	 	});
	 	
	 	m_BrowseText 	= (TextView)this.findViewById(R.id.pick_image_browse_text);
	 	m_BrowseText.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onBrowseButClick(v);
	 		}
	 	});
	 	
    	m_AcceptBut = (Button)this.findViewById( R.id.reuse_accept_but );
    	m_AcceptBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onAcceptButClick(v);
	 		}
	 	});
    	
	 	
    	m_CancelBut = (Button)this.findViewById( R.id.reuse_cancel_but );
    	m_CancelBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onCancelButClick(v);
	 		}
	 	});

     	// load pic from external sdcard
    	//m_MyApp.getVxImageUtil().setImageViewFromPath( m_oPicMe, m_strDefaultPicPath );
    }

    //========================================================================
    @Override
    public void onBackButtonPressed() 
    {
     	Intent resultIntent = new Intent();
     	setResult( Activity.RESULT_CANCELED, resultIntent );
     	finish();
    } 
     
    //============================================================================
	public void onAcceptButClick(View v) 
	{ 
	 	Intent resultIntent = new Intent();
	 	if( m_ImageFileIsValid )
	 	{
        	resultIntent.putExtra( Constants.PARAM_FILE_NAME, m_PickedFileName );
        	resultIntent.putExtra( Constants.PARAM_FILE_TYPE_MASK, Constants.VXFILE_TYPE_PHOTO );
        	resultIntent.putExtra( Constants.PARAM_MEDIA_SRC, m_eMediaSrc );
	 		setResult( Activity.RESULT_OK, resultIntent );
	 	}
	 	else
	 	{
	     	setResult( Activity.RESULT_CANCELED, resultIntent );	 		
	 	}
	 	
	  	finish();
	}

	//============================================================================
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) 
    {
    	super.onActivityResult(requestCode, resultCode, data);
      	if( SELECT_IMAGE_FROM_GALLERY == requestCode )
      	{
      		if( Activity.RESULT_OK == resultCode ) 
      	    {
      			m_UriPic = data.getData();
      			if( null != m_UriPic )
      			{
      				String fileName = VxFileUtil.getRealPathFromURI(  this, m_UriPic );
      				//File galleryFile = new File( m_UriPic.getPath() );
      				//String fileName = galleryFile.getAbsolutePath();
        	        applyImageFile( fileName, Constants.eMediaSrcGallery );      					
      			}
       	    }
        } 
  		else if( Constants.ACTIVITY_CAMERA_SNAPSHOT == requestCode  )
 		{
  			if( Activity.RESULT_OK == resultCode ) 
      	    {
       	        Bundle extras = data.getExtras();
    	        if( null != extras ) 
    	        {	        	
    	        	applyImageFile( extras.getString( Constants.PARAM_FILE_NAME ), Constants.eMediaSrcCamera );
        	    }
      	    }
 		}
  		else if( Constants.ACTIVITY_VIEW_LIBRARY_FILES == requestCode )
 		{
  			if( Activity.RESULT_OK == resultCode ) 
      	    {
       	        Bundle extras = data.getExtras();
    	        if( null != extras ) 
    	        {	
       	        	applyImageFile( extras.getString( Constants.PARAM_FILE_NAME ), Constants.eMediaSrcLibrary );
     	        }
      	    }
 		}
  		else if( Constants.ACTIVITY_BROWSE_DEVICE_FILES == requestCode )
 		{
  			if( Activity.RESULT_OK == resultCode ) 
      	    {
       	        Bundle extras = data.getExtras();
    	        if( null != extras ) 
    	        {	        	
     	        	int fileTypeMask		= extras.getInt( Constants.PARAM_FILE_TYPE_MASK );
    	            if( Constants.VXFILE_TYPE_PHOTO == fileTypeMask )
    	            {
           	        	applyImageFile( extras.getString( Constants.PARAM_FILE_NAME ), Constants.eMediaSrcDeviceFiles );
    	            }
    	        }
      	    }
 		}
    	
		setCamCaptureActivity( this );
    }
    
	//============================================================================
    public void applyImageFile( String fileName, int eMediaSrc )
    {
    	m_ImageFileIsValid = false;
        if( (null == fileName) || fileName.isEmpty() )
        {
        	return;
        }
        
		if( false == m_PhotoView.loadImageFromFile( fileName ) )
		{
			return;
  		}
		
      	m_PickedFileName 	= fileName;
      	m_eMediaSrc			= eMediaSrc;
      	m_ImageFileIsValid	= true;
      	if( Constants.eMediaSrcLibrary != m_eMediaSrc )
      	{
      		NativeTxTo.fromGuiAddFileToLibrary( m_PickedFileName, true, null );
      	}
    }
   
	//============================================================================
    public void onSnapshotButClick(View v) 
    {
    	Intent myIntent = new Intent( ActivityPickImage.this, ActivityCameraSnapshot.class );
        // create personal file name
		m_CameraFileName = VxFileUtil.generatePersonalFileName( m_MyApp );
        m_CameraFileName += ".jpg";	   		
    	
    	myIntent.putExtra(  Constants.PARAM_FILE_NAME, m_CameraFileName );
    	startActivityForResult( myIntent, Constants.ACTIVITY_CAMERA_SNAPSHOT );
    }

	//============================================================================
    public void onGalleryButClick(View v) 
    { 
    	startActivityForResult(new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.INTERNAL_CONTENT_URI), SELECT_IMAGE_FROM_GALLERY );
    }

	//============================================================================
    public void onLibraryButClick(View v) 
    { 
		Intent myIntent = new Intent( ActivityPickImage.this, ActivityViewLibraryFiles.class );
		myIntent.putExtra(  Constants.PARAM_SELECT_FILE_MODE, true );
		myIntent.putExtra(  Constants.PARAM_FILE_FILTER_TYPE, m_eFileFilterType );
		ActivityPickImage.this.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_LIBRARY_FILES );
    }

	//============================================================================
    public void onBrowseButClick(View v) 
    { 
		Intent myIntent = new Intent( ActivityPickImage.this, ActivityBrowseFiles.class );
		myIntent.putExtra(  Constants.PARAM_SELECT_FILE_MODE, true );
		myIntent.putExtra(  Constants.PARAM_FILE_FILTER_TYPE, m_eFileFilterType );
		ActivityPickImage.this.startActivityForResult( myIntent, Constants.ACTIVITY_BROWSE_DEVICE_FILES );
    }
    
 	//============================================================================
    public void onCancelButClick(View v) 
    { 
     	onBackButtonPressed();
    }
        
	//============================================================================
    public String ValidateString(CharSequence charSeq )
    {
    	return charSeq.toString();    	
    }
}
