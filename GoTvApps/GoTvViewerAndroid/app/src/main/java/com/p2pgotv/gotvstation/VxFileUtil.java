//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream; 
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Reader;
import java.io.StringReader;
import java.io.Writer;
import java.nio.channels.FileChannel;

import com.p2pgotv.gotvstation.rteditor.utils.Helper;
import com.p2pgotv.gotvstation.rteditor.utils.io.IOUtils;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.CursorLoader;
import android.content.Intent;
import android.content.res.Resources;
import android.database.Cursor;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.webkit.MimeTypeMap;
import android.widget.Toast;

public class VxFileUtil
{
	private static final String LOG_TAG = "VxFileUtil: ";
	
	 private static final int 	EOF 					= -1;
	 private static final char 	m_PathSeparator 		= '/';

	String 						m_strExternStorageDir	= "";
	String 						m_strSdcardDir			= "";
	File 						m_oSdCardFileIo;
	String 						m_strDataDir 			= "/data/data/packagename/";
	Resources 					m_oRes 					= null;
		
	//========================================================================
	void 		Startup( Resources res )
	{ 
		m_oRes = res;
		m_strExternStorageDir = Environment.getExternalStorageDirectory().getPath();
		m_oSdCardFileIo = new File(m_strExternStorageDir);
		m_strSdcardDir = m_oSdCardFileIo.getAbsolutePath();
	}
	
	//========================================================================
	String getSdCardDir()		
	{ 
		return m_strSdcardDir; 
	}
	
	//========================================================================
	static String getRealPathFromURI( Context mContext, Uri contentUri) 
	{
	    String[] proj = { MediaStore.Images.Media.DATA };
	    CursorLoader loader = new CursorLoader(mContext, contentUri, proj, null, null, null);
	    Cursor cursor = loader.loadInBackground();
	    int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
	    cursor.moveToFirst();
	    String result = cursor.getString(column_index);
	    cursor.close();
	    return result;
	}
	
	//========================================================================
	//! launch application and open/play a file
	static void viewFileInDefaultApplication( Activity activity, String filePathAndName )
	{	
		MimeTypeMap mimeTypeMap = MimeTypeMap.getSingleton();
		Intent newIntent = new Intent( Intent.ACTION_VIEW );
		String mimeType = mimeTypeMap.getMimeTypeFromExtension( getFileExtenstion( filePathAndName ).substring( 1 ) );
		
		File fileObj = new File( filePathAndName );
		if( fileObj.exists() )
		{
			newIntent.setDataAndType( Uri.fromFile( fileObj ), mimeType );
			newIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			try 
			{
				activity.startActivity(newIntent);
			} 
			catch (ActivityNotFoundException e) 
			{
			    Toast.makeText(activity, "No viewer found for this type of file.", Toast.LENGTH_LONG).show();
			}			
		}
		else
		{
		    Toast.makeText(activity, "File Does Not Exist " + filePathAndName, Toast.LENGTH_LONG).show();			
		}
	}
	
	//========================================================================
	static String generatePersonalFileName( MyApp myApp ) 
	{
        return generateFileName( myApp.getUserAccount(),  myApp.getPersonalRecordDir() );
 	}
	
	//========================================================================
	static String generateFileName(  VxNetIdent netIdent, String destDirectory ) 
	{
        String fileNameOut = destDirectory;
        fileNameOut += netIdent.getOnlineName();
        fileNameOut += "_";
        fileNameOut += VxTimeUtil.getFileNameCompatibleDateAndTime( VxTimeUtil.getCurrentTime() );
        fileNameOut += "#";
        VxGUID myId = netIdent.getOnlineId();
        fileNameOut += myId.toOnlineIdHexString();
        return fileNameOut;
	}

	//========================================================================
	//! determine if can write to sdcard
	boolean isExtenalStorageWritable()
	{
		boolean mExternalStorageAvailable = false;
		boolean mExternalStorageWriteable = false;
		String state = Environment.getExternalStorageState();
	
		//Log.i(LOG_TAG, "External storage state =  " + state ); 
		if (Environment.MEDIA_MOUNTED.equals(state)) 
		{
		    // We can read and write the media
		    mExternalStorageAvailable = mExternalStorageWriteable = true;
		} 
		else if (Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) 
		{
		    // We can only read the media
		    mExternalStorageAvailable = true;
		    mExternalStorageWriteable = false;
		}
		else 
		{
		    // Something else is wrong. It may be one of many other states, but all we need
		    //  to know is we can neither read nor write
		    mExternalStorageAvailable = mExternalStorageWriteable = false;
		}
		if( mExternalStorageAvailable && mExternalStorageWriteable )
		{
			return true;
		}
		return false;
	}
		
	//========================================================================
	//! determine if file exists.. return size of file
	int VxResourseFileExists( String strFileName )
	{
		int size = 0;
		InputStream oInputStream = null;
		try 
		{
			oInputStream = m_oRes.getAssets().open(strFileName);
		} 
		catch (IOException e) 
		{
            //Log.e(LOG_TAG, "ERROR: VxFileExists could not get file " + strFileName, e );  
			e.printStackTrace();
		}
        
        // We guarantee that the available method returns the total
        // size of the asset...  of course, this does mean that a single
        // asset can't be more than 2 gigs.
        try {
        	if( null != oInputStream)
        	{
        		size = oInputStream.available();
        		oInputStream.close();
        	}
		} 
        catch (IOException e) 
        {
            Log.e(LOG_TAG, "ERROR: VxResourseFileExists could not get file " + strFileName, e );  
			//e.printStackTrace();
		}
		
		return size;
	}
	
	//========================================================================
	//! determine if file exists.. return size of file
	int VxSdCardFileExists( String strFileName )
	{
		int iDestFileSize = 0;
		InputStream oInputStream = null;
		try 
		{
			File readFile = new File( strFileName);
			oInputStream = new FileInputStream(readFile);  ;
        	if( null != oInputStream)
        	{
        		iDestFileSize = oInputStream.available();
        		oInputStream.close();
        		return iDestFileSize;
        	}

		} 
		catch (IOException e) 
		{
            //Log.e(LOG_TAG, "ERROR: VxSdCardFileExists could not find file " + strFileName, e );  
			//e.printStackTrace();
		}
		return iDestFileSize;
	}
	
	//========================================================================
	static boolean createDirectory( String strDirPath )
	{
		File testDir = new File(strDirPath);  
		boolean dirCreated = testDir.exists();
		if( false == dirCreated )
		{
			dirCreated = testDir.mkdirs();
			if( false == dirCreated)
			{
				Log.e(LOG_TAG, "ERROR: Create Directory failed " + strDirPath);  
			}
		}
		
		return dirCreated;
	}
	
	//========================================================================
	static void copyFile(File src, File dst) throws IOException 
  	{
   	 	FileInputStream srcStream = new FileInputStream(src);
   	 	FileInputStream destStream = new FileInputStream(dst);
   	 	FileChannel inChannel = srcStream.getChannel();
        FileChannel outChannel = destStream.getChannel();
        try 
        {
           inChannel.transferTo(0, inChannel.size(), outChannel);
        } 
        finally 
        {
           if (inChannel != null)
              inChannel.close();
           if (outChannel != null)
              outChannel.close();
        }
        
        srcStream.close();
        destStream.close();
    }
	
	//========================================================================
	int VxCopyAsssetToSdcard( String strFileSrc, String strFileDest, boolean bDontCopyIfExistsAndSameSize )
	{
		int iSrcFileSize = 0;
		int iDestFileSize = 0;
		InputStream oInputStream = null;
		OutputStream oOutputStream = null;
		// get src file size and stream
		try 
		{
			oInputStream = m_oRes.getAssets().open(strFileSrc);
        	if( null != oInputStream)
        	{
        		iSrcFileSize = oInputStream.available();
        	}
        	else
        	{
                Log.e(LOG_TAG, "ERROR: VxCopyResourceToSdcard could not open file " + strFileSrc );  
        		return -1;
        	}
		} 
		catch (IOException e) 
		{
            Log.e(LOG_TAG, "ERROR: VxCopyResourceToSdcard could not open file " + strFileSrc );  
			e.printStackTrace();
    		return -1;
		}
		if( bDontCopyIfExistsAndSameSize )
		{
			// get dest file size and stream
			try 
			{
				InputStream oTmpStream = null;
				File readFile = new File( strFileDest); 
				oTmpStream = new FileInputStream(readFile);  ;
	        	if( null != oTmpStream)
	        	{
	        		iDestFileSize = oTmpStream.available();
	        		oTmpStream.close();
	        	}
			} 
			catch (IOException e) 
			{
	            //Log.e(LOG_TAG, "VxCopyAsssetToSdcard dest file doesnt exist.. will copy " + strFileDest );  
                Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcard could not get size of file " + strFileDest );  
			}
		}
		
 		if( bDontCopyIfExistsAndSameSize && ( iSrcFileSize == iDestFileSize))
		{
            //Log.i(LOG_TAG, "VxCopyAsssetToSdcard file exists " + strFileDest );
            try 
            {
				oInputStream.close();
			} 
            catch (IOException e) 
            {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
            return 0;
		}
 		
        //Log.e(LOG_TAG, "Copy src file " + strFileSrc + " dest file " + strFileDest + " size " + iSrcFileSize );  
       // Read the entire asset into a local byte buffer.
        byte[] buffer = new byte[iSrcFileSize];
        try 
        {
			oInputStream.read(buffer);
	        oInputStream.close();
		} 
        catch (IOException e) 
        {
            Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcard could not read file " + strFileSrc );  
			e.printStackTrace();
		}
		// write buffer to destination file
		try 
		{
			File oWriteFile = new File( strFileDest);
			try
			{  
				oWriteFile.createNewFile();  
			} 
			catch (IOException e) 
			{  
			   Log.e(LOG_TAG, "error creating file " + strFileDest, e);
   				e.printStackTrace();
			   return -1;
			}
			oOutputStream = new FileOutputStream(oWriteFile);  
			if (oOutputStream != null) 
			{  
			    try 
			    {  
					oOutputStream.write(buffer); 
			    	oOutputStream.flush();  
			    	oOutputStream.close();  
			    	//Log.i(LOG_TAG, "Success copying file " + strFileDest + " size " + iSrcFileSize );
			    } 
			    catch (IOException e) 
			    {  
	                Log.e(LOG_TAG, "ERROR: VxCopyResourceToSdcard could not write file " + strFileDest );  
	    			e.printStackTrace();
	        		return -1;
			    }  
			}
		}
		catch (IOException e) 
		{
			Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcard could not read file " + strFileSrc );  
			e.printStackTrace();
			return -1;
		}
		
		return 0;
	}
	
	//========================================================================
	int VxCopyAsssetToSdcardIfDoesntExist( String strFileSrc, String strFileDest )
	{
		VxCopyAsssetToSdcard( strFileSrc, strFileDest, true );
		/*
		if( 0 == VxSdCardFileExists(strFileDest))
		{
			int iSrcFileSize = 0;
			InputStream oInputStream = null;
			OutputStream oOutputStream = null;
			// get src file size and stream
			try 
			{
				oInputStream = m_oRes.getAssets().open(strFileSrc);
	        	if( null != oInputStream)
	        	{
	        		iSrcFileSize = oInputStream.available();
	        	}
	        	else
	        	{
	                Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcardIfDoesntExist could not open file " + strFileSrc );  
	        		return -1;
	        	}
			} 
			catch (IOException e) 
			{
	            Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcardIfDoesntExist could not open file " + strFileSrc );  
				e.printStackTrace();
	    		return -1;
			}
			
            Log.e(LOG_TAG, "Copy src file " + strFileSrc + " dest file " + strFileDest + " size " + iSrcFileSize );  
	        // Read the entire asset into a local byte buffer.
	        byte[] buffer = new byte[iSrcFileSize];
	        try 
	        {
				oInputStream.read(buffer);
		        oInputStream.close();
			} 
	        catch (IOException e) 
	        {
	            Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcardIfDoesntExist could not read file " + strFileSrc );  
				e.printStackTrace();
			}
			// write buffer to destination file
			try 
			{
				File oWriteFile = new File( strFileDest);
				try
				{  
					oWriteFile.createNewFile();  
				} 
				catch (IOException e) 
				{  
				   Log.e(LOG_TAG, "error creating file " + strFileDest, e);
	   				e.printStackTrace();
				   return -1;
				}
				oOutputStream = new FileOutputStream(oWriteFile);  
				if (oOutputStream != null) 
				{  
				    try 
				    {  
						oOutputStream.write(buffer); 
				    	oOutputStream.flush();  
				    	oOutputStream.close();  
				    	//Log.i(LOG_TAG, "Success copying file " + strFileDest + " size " + iSrcFileSize );
				    } 
				    catch (IOException e) 
				    {  
		                Log.e(LOG_TAG, "ERROR: VxCopyResourceToSdcard could not write file " + strFileDest );  
		    			e.printStackTrace();
		        		return -1;
				    }  
				}
			}
			catch (IOException e) 
			{
				Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcard could not read file " + strFileSrc );  
				e.printStackTrace();
				return -1;
			}
		}
		else
		{
			
		}*/
		
		return 0;
	}
	
	//========================================================================
	static String readTextFile( String fileName, boolean addTrailingZero )
	{
		String result = "";
		File readFile = new File( fileName ); 
		InputStream inputStreamSrc;
		try 
		{
			inputStreamSrc = new FileInputStream(readFile);
			if( null != inputStreamSrc )
			{
		       	int fileSize = inputStreamSrc.available();
		       	int bytesRead;
		       	while( fileSize > 0 )
		       	{
		       		if( addTrailingZero )
		       		{
						byte[] fileBuf = new byte[fileSize + 1];
						bytesRead =  inputStreamSrc.read(fileBuf);
						if( bytesRead > 0 )
						{
							fileBuf[ bytesRead ] = 0;
							result +=  new String(fileBuf);
							fileSize = inputStreamSrc.available();
						}
						else
						{
							break;
						}
		       		}
		       		else
		       		{
						byte[] fileBuf = new byte[fileSize];
						bytesRead =  inputStreamSrc.read(fileBuf);
						if( bytesRead > 0 )
						{
							result +=  new String(fileBuf);
							fileSize = inputStreamSrc.available();
						}
						else
						{
							break;
						}	       			
		       		}
		       	}
		       	
		       	inputStreamSrc.close();
			}
		} 
		catch (FileNotFoundException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	
		return result;	
	}
	
	//========================================================================
	public static String writeTextFile(Context context, String fileName, String textToWrite ) 
	{
		File destFile = new File( fileName );
		return writeTextFile( context, destFile, textToWrite );	
	}
	
	//========================================================================
	public static String writeTextFile(Context context, File outFile, String textToWrite ) 
	{
        Reader in = null;
        Writer out = null;

        try 
        {
            in = new StringReader( textToWrite );
            out = new FileWriter(outFile);
            char writeBuf[] = new char[4096];
            //long count = 0;
            int readCnt = 0;
            while( EOF != (readCnt = in.read( writeBuf ))) 
            {
            	out.write(writeBuf, 0, readCnt);
                //count += n;
            }
 
            return outFile.getAbsolutePath();
        } 
        catch (IOException ioe) 
        {
            String toastMsg = context.getString(R.string.save_as_failure, ioe.getMessage());
            Toast.makeText(context, toastMsg, Toast.LENGTH_LONG).show();
        } 
        finally 
        {
         	try
			{
                if( null != in )
                {
                	in.close();
                }
                
                if( null != out )
                {
                	out.close();
                }
			}
			catch( IOException e )
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }

        return null;
    }
	
	//========================================================================
	boolean VxCompareResFileToExternFiles(String strResFileSrc, String strFileDest)
	{
		int iSrcFileSize = 0;
		int iDestFileSize = 0;
		InputStream oInputStreamSrc = null;
		InputStream oInputStreamDest = null;
		// get src file size and stream
		try 
		{
			oInputStreamSrc = m_oRes.getAssets().open(strResFileSrc);
        	if( null != oInputStreamSrc)
        	{
        		iSrcFileSize = oInputStreamSrc.available();
        	}
        	else
        	{
                Log.e(LOG_TAG, "ERROR: VxCompareResFileToExternFiles could not open file " + strResFileSrc );  
        		return false;
        	}
		} 
		catch (IOException e) 
		{
            Log.e(LOG_TAG, "ERROR: VxCompareResFileToExternFiles could not open file " + strResFileSrc );  
			e.printStackTrace();
    		return false;
		}
		
		// get dest file size and stream
		try 
		{
			File readFile = new File( strFileDest); 
			oInputStreamDest = new FileInputStream(readFile);  ;
           	iDestFileSize = oInputStreamDest.available();
       	}
		catch (IOException e) 
		{
            //Log.e(LOG_TAG, "VxCopyAsssetToSdcard dest file doesnt exist.. will copy " + strFileDest );  
            Log.e(LOG_TAG, "ERROR: VxCompareResFileToExternFiles could not get size of file " + strFileDest );  
            return false;
		}
		
		// compare contents
		try 
		{
			if( iSrcFileSize != iDestFileSize)
			{
		        oInputStreamSrc.close();
		        oInputStreamDest.close();
	            return false;
			}
			byte[] buffer1 = new byte[1024];
			byte[] buffer2 = new byte[1024];
			int bytesRead1 = 0;
			int bytesRead2 = 0;
			while( (bytesRead1 = oInputStreamSrc.read(buffer1)) > 0)
			{
				if( (bytesRead2 = oInputStreamDest.read(buffer2)) > 0)
				{
					if( bytesRead1 != bytesRead2 )
					{
				        oInputStreamSrc.close();
				        oInputStreamDest.close();
			            return false;				
					}
					for( int i = 0; i < bytesRead1; i++ )
					{
						if( buffer1[i] != buffer2[i] )
						{
					        oInputStreamSrc.close();
					        oInputStreamDest.close();
				            return false;				
						}
					}
				}
			}
	        oInputStreamSrc.close();
	        oInputStreamDest.close();
		}
		catch (IOException e) 
		{
			Log.e(LOG_TAG, "ERROR: VxCopyAsssetToSdcard exception reading files " );  
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	//========================================================================
	int VxWriteExternFile( String strFileDest, String strTextToWrite )
	{
		return VxWriteExternFile( strFileDest, strTextToWrite.getBytes() );
	}
	
	//========================================================================
	static int VxWriteExternFile( String strFileDest, byte[] bytesToWrite )
	{
		int iDestFileSize = bytesToWrite.length;
		if( 0 < iDestFileSize  )
		{
			return writeBytesToFile( strFileDest, bytesToWrite, iDestFileSize );
		}
		
		return 0;
	}
		
	//========================================================================
	static int writeBytesToFile( String fileName, byte[] dataBytes, int dataLen )
	{	
		int dataWritten = 0;
		FileOutputStream outputStream;
		File oWriteFile = new File( fileName); 
		try
		{  
			oWriteFile.createNewFile();  
			outputStream = new FileOutputStream(fileName);  
		} 
		catch (IOException e) 
		{  
		   Log.e(LOG_TAG, "error creating file " + fileName, e);
			e.printStackTrace();
		   return -1;
		}
		
		if( outputStream != null ) 
		{  
		    try 
		    {  
		    	outputStream.write(dataBytes, 0, dataLen); 
		    	outputStream.flush();  
		    	outputStream.close();  
		    	dataWritten = dataLen;
		    	//Log.i(LOG_TAG, "Success writing file " + strFileDest + " size " + iSrcFileSize );
		    } 
		    catch (IOException e) 
		    {  
                Log.e(LOG_TAG, "ERROR: VxWriteExternFile could not write file " + fileName );  
    			e.printStackTrace();
        		return -1;
		    }  
		}

		return dataWritten;
	}

	//========================================================================
	public static long getFileLen( String fileName )
	{
		File testFile = new File( fileName );
		return testFile.length();	
	}

	//========================================================================
	public static void deleteFile( String fileName )
	{
		File testFile = new File( fileName );
		testFile.delete();	
	}

	//============================================================================
	public static boolean fileExists( String fileNameAndPath )
	{
		File testFile = new File( fileNameAndPath );
		return testFile.exists();	
	}

	//============================================================================
	public static boolean directoryExists( String directoryPath )
	{
		File testFile = new File( directoryPath );
		return testFile.exists() && testFile.isDirectory();	
	}

	//============================================================================
	public static String getUniqueFileName( String fileNameAndPath )
	{
		String retFileName = fileNameAndPath;
		File testFile = new File( fileNameAndPath );
		if( testFile.exists() )
		{
			String filePath = getFilePath( fileNameAndPath );
			String fileName = getJustFileName( fileNameAndPath );
			String fileExt	= getFileExtenstion( fileName );
			if( null == fileExt )
			{
				fileExt = "";
			}
			else
			{
				if( 0 != fileExt.length() )
				{
					fileName = fileName.substring( 0, fileName.length() - fileExt.length() );
					if( '.' != fileExt.charAt( 0 ) )
					{
						fileExt = "." + fileExt;
					}
				}
			}
			
			int cpyCnt = 0;
			do
			{
				cpyCnt++;
				retFileName = filePath + fileName + "(" + cpyCnt + ")" + fileExt;
				testFile = new File( retFileName );				
			}while( testFile.exists() );
		}
		
		return retFileName;
	}
	
	//============================================================================
	public static String getJustFileName( String fileNameAndPath )
	{
		String justFileName = "";
		if( !fileNameAndPath.isEmpty() )
		{
			int lastSlashIdx = fileNameAndPath.lastIndexOf( m_PathSeparator );
			if( lastSlashIdx >= 0 )
			{
				justFileName = fileNameAndPath.substring( lastSlashIdx + 1 );
			}
			else
			{
				justFileName = fileNameAndPath; // no slash found.. must be just file name already
			}
			
			if( justFileName.isEmpty() )
			{
				justFileName = "";
			}
		}

		return justFileName;
	}
	
	//========================================================================
	static String getFileExtenstion( String fileName ) 
	{
	    if( fileName.indexOf("?") > -1 ) 
	    {
	    	fileName = fileName.substring(0, fileName.indexOf("?"));
	    }
	    
	    if( fileName.lastIndexOf(".") == -1 ) 
	    {
	        return null;
	    } 
	    else 
	    {
	        String ext = fileName.substring(fileName.lastIndexOf("."));
	        if( ext.indexOf("%") > -1 ) 
	        {
	            ext = ext.substring(0, ext.indexOf("%"));
	        }
	        
	        if (ext.indexOf("/") > -1) 
	        {
	            ext = ext.substring(0, ext.indexOf("/"));
	        }
	        
	        return ext.toLowerCase();
	    }
	}	

	//============================================================================
	static String getFilePath( String fileNameAndPath )
	{
		String retPath = "";
		if( !fileNameAndPath.isEmpty() )
		{
			int lastSlashIdx = fileNameAndPath.lastIndexOf( m_PathSeparator );
			if( lastSlashIdx >= 0 )
			{
				retPath = fileNameAndPath.substring( 0, lastSlashIdx );
				retPath = assureTrailingDirectorySlash( retPath );
			}
			else
			{
				retPath = ""; // has no slash.. must be just file name
			}

			if( retPath.isEmpty() )
			{
				retPath = "";
			}			
		}
		
		return retPath;
	}

	//============================================================================
	public static String assureTrailingDirectorySlash( String dir ) 
	{
		int lastCharIdx = dir.length();
		if( lastCharIdx > 0 )
		{
			lastCharIdx--;
			int lastSlashIdx = dir.lastIndexOf( m_PathSeparator );
			if( lastCharIdx != lastSlashIdx )
			{
				dir += m_PathSeparator;
			}
		}	
		
		return dir;
	}
	
	//========================================================================
	static byte getMaskFromFileFilterType( int eFileFilterType )
	{
		switch( eFileFilterType )
		{
		case Constants.eFileFilterTypePhoto: 		//1
			return Constants.VXFILE_TYPE_PHOTO;
		case Constants.eFileFilterTypeAudio: 		//2 
			return Constants.VXFILE_TYPE_AUDIO;
		case Constants.eFileFilterTypeVideo: 		//3
			return Constants.VXFILE_TYPE_VIDEO;
		case Constants.eFileFilterTypeDocument: 	//4
			return Constants.VXFILE_TYPE_DOC;
		case Constants.eFileFilterTypeArchive: 		//5
			return Constants.VXFILE_TYPE_ARCHIVE_OR_ISO;
		case Constants.eFileFilterTypeOther: 		//6 
			return Constants.VXFILE_TYPE_OTHER;	
		case 0:
		default:
			return 0x5f; // all types
		}		
	}
	
	//========================================================================
	static String describeFileType( int eFileType )
	{
		switch( eFileType )
		{
		case Constants.VXFILE_TYPE_PHOTO: 
			return "Photo";
		case Constants.VXFILE_TYPE_AUDIO: 
			return "Music";
		case Constants.VXFILE_TYPE_VIDEO: 
			return "Video";
		case Constants.VXFILE_TYPE_DOC:
			return "Document";
		case Constants.VXFILE_TYPE_ARCHIVE_OR_ISO:
			return "Archive Or ISO";
		case Constants.VXFILE_TYPE_EXECUTABLE:
			return "Executeable";	
		case Constants.VXFILE_TYPE_DIRECTORY:
			return "Folder";			
		case Constants.VXFILE_TYPE_OTHER: 
		default:
			return "Other";
		}		
	}
	//========================================================================
	static int getFileIconResource( int eFileType )
	{
		switch( eFileType )
		{
		case Constants.VXFILE_TYPE_PHOTO: 
			return R.drawable.button_gallery_normal;
		case Constants.VXFILE_TYPE_AUDIO: 
			return R.drawable.button_music;
		case Constants.VXFILE_TYPE_VIDEO: 
			return R.drawable.button_video_normal;
		case Constants.VXFILE_TYPE_DOC:
			return R.drawable.button_doc_normal;
		case Constants.VXFILE_TYPE_ARCHIVE_OR_ISO:
			return R.drawable.button_archive_normal;
		case Constants.VXFILE_TYPE_EXECUTABLE:
			return R.drawable.ic_unknown;
		case Constants.VXFILE_TYPE_DIRECTORY:
			return R.drawable.button_file_browse_normal;		
		case Constants.VXFILE_TYPE_OTHER: 
		default:
			return R.drawable.button_other_normal;
		}		
	}
	
	//========================================================================
	static String describeFileLength( long fileLen )
	{
		String strLen;
		if( fileLen >= 1000000000000L )
		{
			strLen = String.format( "%.1f TB", (double)(fileLen) / 1000000000000.0);
		}
		else if( fileLen >= 1000000000L )
		{
			strLen = String.format( "%.1f GB", (double)(fileLen) / 1000000000.0);
		}
		else if( fileLen >= 1000000 )
		{
			strLen = String.format( "%.1f MB", (double)(fileLen) / 1000000.0);
		}
		else if( fileLen >= 1000 )
		{
			strLen = String.format( "%.1f KB", (double)(fileLen) / 1000.0);
		}
		else
		{
			strLen = String.format( "%.1f Bytes ", (double)fileLen );
		}

		return strLen;	
	}
}

