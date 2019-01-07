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

public interface ToGuiActivityInterface 
{
	public void	toGuiRxedPluginOffer( GuiOfferSession offerSession );
	public void	toGuiRxedOfferReply( GuiOfferSession offerSession );
	public void toGuiPluginSessionEnded( GuiOfferSession offerSession );
	
	public void toGuiContactOnline( VxNetIdent friendIdent, boolean newContact );
	public void toGuiContactOffline( VxNetIdent friendIdent );
	
	public void toGuiPlayVideoFrame( VxGUID guidId, byte[] pu8Jpg, int jpgDataLen, int motion0to100000 );	
	
	public void	toGuiInstMsg( VxNetIdent friendIdent, int ePluginType, String strMsg );
	
	public void toGuiMultiSessionAction( int eMSessionAction, VxGUID onlineId, int actionParam );
	public void toGuiSetGameActionVar( int iPlugin, VxGUID sessionId, int s32ActionId, int s32VarValue );
	public void toGuiSetGameValueVar( int iPlugin, VxGUID sessionId, int s32VarId, int s32VarValue );
		
};
