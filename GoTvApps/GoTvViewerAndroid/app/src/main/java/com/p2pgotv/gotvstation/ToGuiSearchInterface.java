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

public interface ToGuiSearchInterface 
{
	public void	toGuiScanSearchComplete( int eScanType );
	public void	toGuiScanSearchResultSuccess( int eScanType, VxNetIdent	netIdent );
	public void	toGuiScanSearchResultError( int eScanType, VxNetIdent netIdent, int errCode );
	public void	toGuiSearchResultProfilePic( VxNetIdent	netIdent, byte[] jpgData, int jpgDataLen );
	public void	toGuiSearchResultFileSearch( 	VxNetIdent		netIdent, 		
												VxGUID			fileInstanceId, 
												int				fileType, 
												long			fileLen, 
												String			fileName );
	public void toGuiPhoneShakeStatus( String formatedMsg );
};

