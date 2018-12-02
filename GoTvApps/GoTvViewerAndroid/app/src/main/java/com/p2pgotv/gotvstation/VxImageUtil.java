//============================================================================
// Copyright (C) 2011 Brett R. Jones
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

import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.util.DisplayMetrics;
import android.util.Log;
import android.widget.ImageView;

public class VxImageUtil
{
	private static final String LOG_TAG = "VxImageUtil: ";
	
	//========================================================================
	public static boolean saveStdSizeBitmapToFile( Bitmap myBitmap, String fileNameAndPath )
	{
		if( null == myBitmap )
		{
			Log.e( LOG_TAG, "saveStdSizeBitmapToFile null bitmap "  + fileNameAndPath );
			return false;
		}
		
		Bitmap resizedBmp = getStdSizeBitmap( myBitmap );
		return saveBitmapToJpgFile( resizedBmp, fileNameAndPath );
 	}
	
	//========================================================================
	public static boolean saveBitmapToJpgFile( Bitmap myBitmap, String fileNameAndPath )
	{
		if( null == myBitmap )
		{
			Log.e( LOG_TAG, "saveBitmapToJpgFile null bitmap "  + fileNameAndPath );
			return false;
		}
		
		FileOutputStream fileOutputStream = null;
		try 
		{	
			int quality = 100;
			fileOutputStream = new FileOutputStream( fileNameAndPath );
			BufferedOutputStream bos = new BufferedOutputStream( fileOutputStream );
			myBitmap.compress( CompressFormat.JPEG, quality, bos );

			bos.flush();
			bos.close();
			return true;
		} 
		catch (FileNotFoundException e) 
		{
			Log.e(LOG_TAG, "saveImageDataToJpg failed" );
			e.printStackTrace();
		} 
		catch (IOException e) 
		{
			Log.e(LOG_TAG, "saveImageDataToJpg failed" );
			e.printStackTrace();
		}
		
		return false;
 	}
	
	//========================================================================
	public static boolean copyImageUrlToStdSizeBitmapFile( String imagePath, String destPathAndName )
	{
		Bitmap bmp = getStdSizeBitmapFromFile( imagePath );
		if( null != bmp )
		{
			return saveBitmapToFile( destPathAndName, bmp );
		}
		
		return false;
	}
	
	//========================================================================
	public static boolean saveBitmapToFile( String fileNameAndPath, Bitmap bmp )
	{
		String fileExt = VxFileUtil.getFileExtenstion( fileNameAndPath );
		File file = new File(fileNameAndPath);
	    FileOutputStream fOut = null;
	    boolean result = false;
		try
		{
			fOut = new FileOutputStream(file);
			Log.d( LOG_TAG, "saveBitmapToFile width " + bmp.getWidth() + " height " + bmp.getHeight() );
			if( fileExt.contains( "png" ) || fileExt.contains( "PNG" ) )
			{
				if( false == bmp.compress(Bitmap.CompressFormat.PNG, 85, fOut) )
				{
					Log.e( LOG_TAG, "saveBitmapToFile failed to compresss JPEG to " +  fileNameAndPath + " width " + bmp.getWidth() + " height " + bmp.getHeight() );
				}
				else
				{
					result = true;
				}
			}
			else
			{
				if( false == bmp.compress(Bitmap.CompressFormat.JPEG, 100, fOut) )
				{
					Log.e( LOG_TAG, "saveBitmapToFile failed to compresss JPEG to " +  fileNameAndPath + " width " + bmp.getWidth() + " height " + bmp.getHeight() );
				}
				else
				{
					result = true;
				}
			}
			
			fOut.flush();
			fOut.close();
			if( VxFileUtil.fileExists( fileNameAndPath ) )
			{
				Log.d( LOG_TAG, "SUCCESS saveBitmapToFile  " +  fileNameAndPath + " size " + file.length() + " width " + bmp.getWidth() + " height " + bmp.getHeight() );				
			}
			else
			{
				Log.e( LOG_TAG, "FAIL saveBitmapToFile  " +  fileNameAndPath + " width " + bmp.getWidth() + " height " + bmp.getHeight() );
			}
			
			return result;
		}
		catch( FileNotFoundException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		catch( IOException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return false;
	}
	
	//========================================================================
	public static Bitmap getStdSizeBitmapFromFile( String strPath )
	{
		return getSizedImageFromFile( strPath, Constants.IMAGE_DESIRED_WIDTH, Constants.IMAGE_DESIRED_HEIGHT );
	}
	
	//========================================================================
	public static int dpToPixels( Context context, int dp ) 
	{
	    DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
	    int px = Math.round(dp * (displayMetrics.xdpi / DisplayMetrics.DENSITY_DEFAULT));       
	    return px;
	}
	
	//========================================================================
	//Convert pixel to dp:
	public static int pixelsToDp( Context context, int px ) 
	{
	    DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
	    int dp = Math.round(px / (displayMetrics.xdpi / DisplayMetrics.DENSITY_DEFAULT));
	    return dp;
	}
	//========================================================================
	public static Bitmap getSizedImageFromFile( String strPath, int desiredWidth, int desiredHeight )
	{
		Bitmap myBitmap = null;
		if( ( null != strPath )
			&& ( 0 != strPath.length() ) )
		{
			long fileLen = VxFileUtil.getFileLen( strPath );
			if( 0 != fileLen )
			{
				Bitmap sizedBitmap = BitmapFactory.decodeFile(strPath); 
			    if( ( null != sizedBitmap )
			    		&& ( 1 < sizedBitmap.getHeight() )
			    		&& ( 1 < sizedBitmap.getWidth() )
			    		&& ( 0 != desiredWidth )
			    		&& ( 0 != desiredHeight ) )
			    {
			    	myBitmap = getDesiredSizeBitmap( sizedBitmap, desiredWidth, desiredHeight );
			    }
			    else
			    {
			    	Log.e( LOG_TAG, "getSizedImageFromFile could not decode " + strPath );
			    }
			}
		    else
		    {
		    	Log.e( LOG_TAG, "getSizedImageFromFile invalid " + strPath );
		    }
		}
		else
		{
	    	Log.e( LOG_TAG, "getSizedImageFromFile invalid file name " );			
		}
		
		return myBitmap;
	}
	
	//========================================================================
	public static Bitmap getStdSizeBitmap( Bitmap bm ) 
	{
		return getDesiredSizeBitmap( bm, Constants.IMAGE_DESIRED_WIDTH, Constants.IMAGE_DESIRED_HEIGHT );
 	}
	
	//========================================================================
	public static Bitmap getDesiredSizeBitmap( Bitmap bm, int desiredWidth, int desiredHeight ) 
	{
		int bmpWidth 	= bm.getWidth();
		int bmpHeight 	= bm.getHeight();
    	if( ( bmpWidth != desiredWidth )
        		|| ( bmpHeight != desiredHeight) )
        {
    		float scaling = determineBitmapScaling( bmpWidth, bmpHeight, desiredWidth, desiredHeight );
    		if( 1.0f != scaling  )
    		{
    			return getResizedBitmap( bm, (int)(bmpWidth * scaling), (int)(bmpHeight * scaling) );
    		}
    		else
    		{
        		return bm;  			
    		}
        }
    	else
    	{
    		return bm;
    	}
	}

	//========================================================================
	public static float determineDesiredStdBitmapScaling( int bmpWidth, int bmpHeight ) 
	{
		return determineBitmapScaling( bmpWidth, bmpHeight, Constants.IMAGE_DESIRED_WIDTH, Constants.IMAGE_DESIRED_HEIGHT );
	}
	
	//========================================================================
	public static float determineBitmapScaling( int bmpWidth, int bmpHeight, int desiredWidth, int desiredHeight ) 
	{
		float imageScale = 1.0f;
    	if( ( bmpWidth > desiredWidth )
				||( bmpHeight > desiredHeight) )
		{
			// scale down image
			float scaleWidth 		= ((float)desiredWidth) / ((float)bmpWidth );
			float scaleHeight 		= ((float)desiredHeight) / ((float)bmpHeight );
			if( scaleWidth < scaleHeight )
			{
				imageScale = scaleWidth;
			}
			else
			{
				imageScale = scaleHeight;						
			}
		}
		else if( ( bmpWidth < desiredWidth )
				||( bmpHeight < desiredHeight ) )
		{
			// scale up image
			float scaleWidth 		= ((float)desiredWidth) / ((float)bmpWidth );
			float scaleHeight 		= ((float)desiredHeight) / ((float)bmpHeight );
			if( scaleWidth < scaleHeight )
			{
				imageScale = scaleWidth;
			}
			else
			{
				imageScale = scaleHeight;						
			}
		}
    	
    	return imageScale;
	}

	//========================================================================
	public static Bitmap getResizedBitmap( Bitmap bm, int newWidth, int newHeight ) 
	{
	    int width = bm.getWidth();
	    int height = bm.getHeight();
	    float scaleWidth = ((float) newWidth) / width;
	    float scaleHeight = ((float) newHeight) / height;
	    // CREATE A MATRIX FOR THE MANIPULATION
	    Matrix matrix = new Matrix();
	    // RESIZE THE BIT MAP
	    matrix.postScale(scaleWidth, scaleHeight);

	    // "RECREATE" THE NEW BITMAP
	    Bitmap resizedBitmap = Bitmap.createBitmap( bm, 0, 0, width, height, matrix, false );
	    bm.recycle();
	    return resizedBitmap;
	}
	
	//========================================================================
	public static boolean saveImageDataToStdSizeJpg( byte[] imageData, String strFileNameAndPath ) 
	{
		BitmapFactory.Options options = new BitmapFactory.Options();
		options.inSampleSize = 1;				
		Bitmap myImage = BitmapFactory.decodeByteArray( imageData, 0, imageData.length, options );
		Bitmap resizedBmp = getStdSizeBitmap( myImage );
		return saveBitmapToJpgFile( resizedBmp, strFileNameAndPath );
	}
	
	//========================================================================
	public static boolean saveImageDataToJpg( byte[] imageData, String strFileNameAndPath ) 
	{
		BitmapFactory.Options options = new BitmapFactory.Options();
		options.inSampleSize = 1;				
		Bitmap myImage = BitmapFactory.decodeByteArray( imageData, 0, imageData.length, options );
		return saveBitmapToJpgFile( myImage, strFileNameAndPath );
	}
	
	//========================================================================
	public static boolean setImageViewFromPath( ImageView oImageView, String strPath )
	{
		Bitmap myBitmap = getStdSizeBitmapFromFile( strPath );
	    if( null != myBitmap )
	    {
	    	oImageView.setImageBitmap(myBitmap);
	    	return true;
	    }
		
		return false;
	}
	
	//========================================================================
	public static boolean saveImageViewToStdSizeJpg( ImageView imageView, String fileNameAndPath ) 
	{
		if( null == imageView )
		{
			return false;
		}
		
		Bitmap myImage = imageView.getDrawingCache();
		Bitmap resizedBmp = getStdSizeBitmap( myImage );
		return saveBitmapToJpgFile( resizedBmp, fileNameAndPath );
	}
	
	//========================================================================
	public static boolean saveImageViewToJpg( ImageView imageView, String fileNameAndPath ) 
	{
		if( null == imageView )
		{
			return false;
		}
		
		Bitmap myImage = imageView.getDrawingCache();
		return saveBitmapToJpgFile( myImage, fileNameAndPath );
	}
	
	//========================================================================
	public static byte[] bitmapToBlob( Bitmap bitmapImg )
	{
		byte[] retBlobArray = null;
		if( ( null != bitmapImg ) && ( 0 < bitmapImg.getWidth() ) )
		{
			ByteArrayOutputStream bos = new ByteArrayOutputStream();
			bitmapImg.compress(Bitmap.CompressFormat.PNG, 100, bos);
			retBlobArray = bos.toByteArray();			
		}

		return retBlobArray;
	}
	
	//========================================================================
	public static Bitmap blobToBitmap( byte[] blobArray )
	{	
		Bitmap retBitmapImg = null;
		if(( null != blobArray ) && ( 0 < blobArray.length ) )
		{
			retBitmapImg = BitmapFactory.decodeByteArray( blobArray, 0 ,blobArray.length );	
		}
		
		return retBitmapImg;
	}
};
	
	