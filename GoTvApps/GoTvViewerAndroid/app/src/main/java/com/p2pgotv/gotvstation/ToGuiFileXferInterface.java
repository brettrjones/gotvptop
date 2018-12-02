//============================================================================
// Copyright (C) 2015 Brett R. Jones
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

import android.view.View;

public interface ToGuiFileXferInterface 
{
	public void toGuiFileList( VxFileInfo fileInfo );
	public void toGuiFileListReply(	GuiFileXferSession xferSession );
	public void toGuiStartUpload( GuiFileXferSession xferSession );
	public void toGuiStartDownload( GuiFileXferSession xferSession );

	public void toGuiFileXferState( VxGUID lclSession, int eXferState, int param1, int param2 );
	public void toGuiFileDownloadComplete( VxGUID lclSession, String newFileName, int xferError );
	public void toGuiFileUploadComplete( VxGUID lclSession, int xferError );
	
	public void onFileXferFileIconButClick( View v );
	public void onFileXferAcceptButClick( View v );
	public void onFileXferPlayButClick( View v );
	public void onFileXferLibraryButClick( View v );
	public void onFileXferShareButClick( View v );
	public void onFileXferShredButClick( View v );

}
