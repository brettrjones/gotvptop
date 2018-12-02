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

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.widget.TextView;

public class GuiHelpers 
{
	//============================================================================
	static void setupTitle( Context context, int ePluginType, TextView oTitleText, boolean bIsMyself )
	{
		if(null != oTitleText)
	    {       
			Drawable img = context.getResources().getDrawable( MyIcons.getPluginIcon( ePluginType, Constants.ePluginAccessOk) ); 
			if( ( false == bIsMyself ) && (Constants.ePluginTypeCamServer == ePluginType ))
			{
				img = context.getResources().getDrawable( MyIcons.getIcon( Constants.eMyIconWebCamClient ) ); 	        	
			}
	        img.setBounds( 0, 0, 50, 50 ); 
	        oTitleText.setCompoundDrawables( img, null, null, null ); 
	        
	        switch(ePluginType)
	        {
	        case Constants.ePluginTypeWebServer:
	        	oTitleText.setText( R.string.activity_web_server );
	        	break;
	        case Constants.ePluginTypeRelay:
	        	oTitleText.setText( R.string.activity_to_friend_request_relay_name );
	        	break;
	        case Constants.ePluginTypeFileServer:
	        	oTitleText.setText(R.string.activity_file_server);
	        	break;
	        case Constants.ePluginTypeFileOffer:
	        	oTitleText.setText(R.string.activity_file_offer);
	        	break;
	        case Constants.ePluginTypeCamServer:
	        	if( bIsMyself )
	        	{
	        		oTitleText.setText( R.string.activity_cam_server );
	        	}
	        	else
	        	{
	        		oTitleText.setText( R.string.activity_cam_client );
	        	}
	        	break;
	        case Constants.ePluginTypeMultiSession:
	        	oTitleText.setText(R.string.activity_to_friend_multisession_title);
	        	break;
	        case Constants.ePluginTypeVoicePhone:
	        	oTitleText.setText(R.string.activity_to_friend_voice_phone_name);
	        	break;
	        case Constants.ePluginTypeVideoPhone:
	        	oTitleText.setText(R.string.activity_to_friend_video_phone_name);
	        	break;
	        case Constants.ePluginTypeTruthOrDare:
	        	oTitleText.setText(R.string.activity_to_friend_tod_game_name);
	        	break;
	       case Constants.ePluginTypeStoryBoard: 
	    	   oTitleText.setText(R.string.activity_to_friend_story_board_name);
	       		break;	
	        }
	    }
	}

	//============================================================================
	static String getWhoPermissionText( int ePluginType )
	{
		String strPermissionText = "UNKNOWN";

        switch(ePluginType)
        {
        case Constants.ePluginTypeWebServer:
        	strPermissionText = "Who can view my profile";
        	break;
        case Constants.ePluginTypeRelay:
        	strPermissionText = "Who can use my device as relay";
        	break;
        case Constants.ePluginTypeCamServer:
        	strPermissionText = "Who can view my shared web cam";
        	break;
        case Constants.ePluginTypeMultiSession:
        	strPermissionText = "Who can offer chat session";
        	break;
        case Constants.ePluginTypeVoicePhone:
        	strPermissionText = "Who can offer voice phone (VOIP)";
        	break;
        case Constants.ePluginTypeVideoPhone:
        	strPermissionText = "Who can offer video chat";
        	break;
        case Constants.ePluginTypeTruthOrDare:
        	strPermissionText = "Who can offer play Truth or Dare";
        	break;
       case Constants.ePluginTypeStoryBoard: 
       		strPermissionText = "Who can view my storyboard";
       		break;	
       case Constants.ePluginTypeFileServer:
       		strPermissionText = "Who can access my shared files";
       		break;
       case Constants.ePluginTypeFileOffer:
       		strPermissionText = "Who can send me a file";
       		break;
        }
        
        return strPermissionText;
	}

	//============================================================================
	static String describeResponse(int eOfferResponse) 
	{
		switch( eOfferResponse )
		{
		case Constants.eOfferResponseAccept:
			return "Offer Accepted";

		case Constants.eOfferResponseReject:
			return "Offer Rejected";

		case Constants.eOfferResponseBusy:
			return "Busy";

		case Constants.eOfferResponseCancelSession:
			return "Session Canceled";

		case Constants.eOfferResponseEndSession:
			return "User Ended Session";

		case Constants.eOfferResponseUserOffline:
			return "User Is Offline";

		default:
			return "Session Ended";
		}
	}
	
	//============================================================================
	static String describePluginPermission( int ePluginPermission )
	{
		switch(ePluginPermission)
		{
		case Constants.eFriendStateIgnore:
			return "Disabled";
		case Constants.eFriendStateAnonymous:
			return "Anonymous";
		case Constants.eFriendStateGuest:
			return "Guest";
		case Constants.eFriendStateFriend:
			return "Friends";
		default:
			return "Unknown";
		}
	}
	
	//============================================================================
	static boolean isPluginSingleSession( int ePluginType )
	{
		boolean isSingleSessionPlugin = false;
        switch(ePluginType)
        {
        case Constants.ePluginTypeVoicePhone:
        case Constants.ePluginTypeVideoPhone:
        case Constants.ePluginTypeTruthOrDare:
        case Constants.ePluginTypeMultiSession:
        case Constants.ePluginTypeCamServer:
        case Constants.ePluginTypeAdmin:
        	isSingleSessionPlugin = true;
        	break;
        case Constants.ePluginTypeWebServer:
        case Constants.ePluginTypeRelay:
        case Constants.ePluginTypeStoryBoard: 
        case Constants.ePluginTypeFileServer:
        case Constants.ePluginTypeFileOffer:
    	default:
       		break;
        }
		
        return isSingleSessionPlugin;
	}
	
	//============================================================================
	static String describePlugin( int ePluginType, boolean rmtInitiated )
	{
		String strPluginDesc = "UNKNOWN PLUGIN";

        switch(ePluginType)
        {
        case Constants.ePluginTypeAdmin:
        	strPluginDesc = "Admin Server";
        	break;
         case Constants.ePluginTypeWebServer:
        	if( rmtInitiated )
        	{
        		strPluginDesc = "About Me Web Page";
        	}
        	else
        	{
        		strPluginDesc = "Web Server";       		
        	}
        	break;
        case Constants.ePluginTypeRelay:
        	strPluginDesc = "Relay";
        	break;
        case Constants.ePluginTypeCamServer:
        	if( rmtInitiated )
        	{
        		strPluginDesc = "Cam Client";
        	}
        	else
        	{
        		strPluginDesc = "Cam Server";       		
        	}
        	break;
        case Constants.ePluginTypeMultiSession:
        	strPluginDesc = "Text Chat";
        	break;
        case Constants.ePluginTypeVoicePhone:
        	strPluginDesc = "Voice Phone (VOIP)";
        	break;
        case Constants.ePluginTypeVideoPhone:
        	strPluginDesc = "Video Chat";
        	break;
        case Constants.ePluginTypeTruthOrDare:
        	strPluginDesc = "Truth or Dare";
        	break;
       case Constants.ePluginTypeStoryBoard: 
    	    strPluginDesc = "Storyboard";
       		break;	
       case Constants.ePluginTypeFileServer:
    	    strPluginDesc = "Shared Files";
       		break;
       case Constants.ePluginTypeFileOffer:
    	   strPluginDesc = "File Send";
       		break;
        }
        
        return strPluginDesc;
	}

	//========================================================================
	static public String describeEXferState( int xferState )
	{
		switch( xferState )
		{
		case Constants.eXferStateUploadNotStarted:
			return "Upload Not Started";
		case Constants.eXferStateWaitingOfferResponse:
			return "Waiting Response";
		case Constants.eXferStateInUploadQue:
			return "In Upload Que";
		case Constants.eXferStateBeginUpload:
			return "Start Upload";
		case Constants.eXferStateInUploadXfer:
			return "Uploading";
		case Constants.eXferStateCompletedUpload:
			return "Upload Completed";
		case Constants.eXferStateUserCanceledUpload:
			return "Upload Canceled";
		case Constants.eXferStateUploadOfferRejected:
			return "Offer Rejected";
		case Constants.eXferStateUploadError:
			return "ERROR";
			
		case Constants.eXferStateDownloadNotStarted:
			return "Download Not Started";
		case Constants.eXferStateInDownloadQue:
			return "In Download Que";
		case Constants.eXferStateBeginDownload:
			return "Start Download";
		case Constants.eXferStateInDownloadXfer:
			return "Downloading";
		case Constants.eXferStateCompletedDownload:
			return "Download Completed";
		case Constants.eXferStateUserCanceledDownload:
			return "Download Canceled";
		case Constants.eXferStateDownloadError:
			return "ERROR";
		case Constants.eXferStateUnknown:
		default:
			return "Unknown State";
		}
	}

	//============================================================================
	public static String describeEXferError( int xferError )
	{
		switch( xferError )
		{
		case Constants.eXferErrorNone:
			return "No Error";
		case Constants.eXferErrorDisconnected:
			return "Disconnected";
		case Constants.eXferErrorPermission:
			return "Permission Error";
		case Constants.eXferErrorFileNotFound:
			return "File Not Found";
		case Constants.eXferErrorCanceled:
			return "Canceled";
		case Constants.eXferErrorBadParam:
			return "Bad Param";
		case Constants.eXferErrorAtSrc:
			return "Error At Source";
		case Constants.eXferErrorBusy:
			return "Busy";
		case Constants.eXferErrorAlreadyDownloading:
			return "Already Downloading";
		case Constants.eXferErrorAlreadyDownloaded:
			return "Already Downloaded";
		case Constants.eXferErrorAlreadyUploading:
			return "Already Uploading";
		case Constants.eXferErrorFileCreateError:
			return "File Create Error";
		case Constants.eXferErrorFileOpenAppendError:
			return "File Append Error";
		case Constants.eXferErrorFileOpenError:
			return "File Open Error";
		case Constants.eXferErrorFileSeekError:
			return "Seek Error";
		case Constants.eXferErrorFileReadError:
			return "Read Error";
		case Constants.eXferErrorFileWriteError:
			return "Write Error";
		case Constants.eXferErrorFileMoveError:
			return "Move File Error";
		default:
			return "Unknown Error";
		}
	}
}