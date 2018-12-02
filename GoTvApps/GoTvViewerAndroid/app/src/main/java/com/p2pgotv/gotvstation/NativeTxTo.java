package com.p2pgotv.gotvstation;

import java.nio.ByteBuffer;

import android.content.Context;

public class NativeTxTo 
{
	public static native void 		fromGuiSetupContext( Context applicationContext );

	public static native void 		fromGuiCacheAudioParameters( 	int sampleRate,
																	int channels, boolean hardwareAEC, boolean hardwareAGC,
																	boolean hardwareNS, boolean lowLatencyOutput, int outputBufferSize,
																	int inputBufferSize, long nativeAudioManager );
	public static native void 		fromGuiCacheRecordDirectBufferAddress( ByteBuffer byteBuffer, long nativeAudioRecord );
	public static native void 		fromGuiDataIsRecorded( int bytes, long nativeAudioRecord );

	public static native void 		fromGuiCachePlayoutDirectBufferAddress( ByteBuffer byteBuffer, long nativeAudioRecord );
	public static native void 		fromGuiGetPlayoutData( int bytes, long nativeAudioRecord );

	public static native void		fromGuiSetIsAppCommercial( boolean isPaid ); 
	public static native boolean	fromGuiGetIsAppCommercial(); 
	public static native int		fromGuiGetAppVersionBinary(); 
	public static native String		fromGuiGetAppVersionString(); 
	public static native String		fromGuiGetAppName(); 
	public static native String		fromGuiGetAppNameNoSpaces(); 

	public static native void 		fromGuiAppStartup(	String strAssetsDir, String strRootDataDir );
	public static native void 		fromGuiSetUserXferDir( String strUserXferDir );
	public static native void 		fromGuiSetUserSpecificDir( String strUserSpecificDir );
	public static native long 		fromGuiGetDiskFreeSpace();
	public static native void		fromGuiAppShutdown();  
	
	public static native void		fromGuiAppIdle(); 
	public static native void		fromGuiAppPauseOrResume( boolean m_AppIsPaused );
		
	//=== user gui input actions ===//
	public static native boolean	fromGuiOrientationEvent( float f32RotX, float f32RotY, float f32RotZ  ); 
	public static native boolean	fromGuiTouchEvent( int iAction, int iMouseXPos, int iMouseYPos  );
	public static native boolean	fromGuiKeyEvent( int eKeyEventType, int eKey );
	
	//public static native void 		fromGuiNativeGlInit();
	//public static native void 		fromGuiNativeGlResize( int width, int height );
	//public static native int 		fromGuiNativeGlRender();
	//public static native void 		fromGuiNativeGlPauseRender();
	//public static native void 		fromGuiNativeGlResumeRender();	
	//public static native void 		fromGuiNativeGlDestroy();
	
	//public static native int		fromGuiAudioOutSpaceAvail( int freeSpace );
	//public static native void		fromGuiNeedMorePlayData( ByteBuffer pcmData, int pcmDataLenInBytes );
	public static native void		fromGuiMicrophoneData( ByteBuffer pcmData, int pcmDataLenInBytes );
	public static native void		fromGuiMuteMicrophone( boolean bMute );
	public static native void		fromGuiMuteSpeaker( boolean bMute );
	public static native void		fromGuiEchoCancelEnable( boolean enableEchoCancel );
	public static native boolean	fromGuiIsMicrophoneMuted();	
	public static native boolean	fromGuiIsSpeakerMuted();	
	public static native boolean	fromGuiIsEchoCancelEnabled();	

	public static native int		fromGuiWantMediaInput(  long u64IdHiPart, long u64IdLoPart, int iMediaType, boolean wantInput );  
	public static native void 		fromGuiVideoData( long iVideoFormat, byte[] vidData, int iWidth, int iHeight, int iRotate );  
	public static native void 		fromGuiYUV420CaptureImage( byte[] yBytes, byte[] uBytes, byte[] vBytes, 
															int yRowStride, int uRowStride, int vRowStride, 
															int yPixStride, int uPixStride, int vPixStride, 
															int width, int height, int iRotate );
	//! called when cut scene movie has finished playing
	public static native boolean	fromGuiMovieDone();

	public static native void		fromGuiUserLoggedOn( VxNetIdent myIdent );  
	public static native void		fromGuiOnlineNameChanged( String newOnlineName );
	public static native void		fromGuiMoodMessageChanged( String newMoodMessage );	
	public static native void		fromGuiSetUserHasProfilePicture( boolean haveProfilePick );
	public static native void		fromGuiUpdateMyIdent( VxNetIdent myIdent, boolean permissionAndStatsOnly );  
	public static native void		fromGuiSetIdentHasTextOffers( long u64IdHiPart, long u64IdLoPart, boolean hasOffer );
	public static native void		fromGuiQueryMyIdent( VxNetIdent myIdent );  
	
	public static native void		fromGuiChangeMyFriendshipToHim( long u64IdHiPart, long u64IdLoPart, int eMyFriendshipToHim, int eHisFriendshipToMe ); 
	
	public static native void 		fromGuiSetNetSettings( NetSettings netSettings );
	public static native void 		fromGuiGetNetSettings( NetSettings netSettings );
	public static native void 		fromGuiNetworkSettingsChanged();
	public static native void 		fromGuiSetRelaySettings( int userRelayMaxCnt, int systemRelayMaxCnt );	

	public static native void 		fromGuiNetworkAvailable( String lclIp, boolean isCellularNetwork );
	public static native void 		fromGuiNetworkLost();
	
	public static native void 		fromGuiVerifyAnchorSettings();
	public static native void 		fromGuiRunIsPortOpenTest( int port );

	public static native void 		fromGuiSetFileShareSettings( FileShareSettings fileShareSettings );
	public static native void 		fromGuiGetFileShareSettings( FileShareSettings fileShareSettings );
	
	public static native int 		fromGuiGetNextFileInstanceId();
	
	public static native void 		fromGuiUpdateWebPageProfile(	String	pProfileDir,	// directory containing user profile
																	String	strGreeting,	// greeting text
																	String	aboutMe,		// about me text
																	String	url1,			// favorite url 1
																	String	url2,			// favorite url 2
																	String	url3 );		// favorite url 3
	
	public static native void 		fromGuiSetPluginPermission( int ePluginType, int eFriendState );
	public static native int		fromGuiGetPluginPermission( int ePluginType );
	public static native int		fromGuiGetPluginServerState( int ePluginType );

	public static native void 		fromGuiStartPluginSession( int ePluginType, long u64IdHiPart, long u64IdLoPart, long sessionIdHiPart, long sessionIdLoPart, int pvUserData );
	public static native void 		fromGuiStopPluginSession( int ePluginType, long u64IdHiPart, long u64IdLoPart, long sessionIdHiPart, long sessionIdLoPart, int pvUserData  );
	public static native boolean 	fromGuiIsPluginInSession( int ePluginType, long u64IdHiPart, long u64IdLoPart, long sessionIdHiPart, long sessionIdLoPart, int pvUserData );

	public static native boolean	fromGuiMakePluginOffer(	int iPlugin, long u64OnlineIdHiPart, long u64OnlineIdLoPart, int iUserData, String strOfferMsg, String strFileName, long lclSessionIdHiPart, long lclSessionIdLoPart );	
	public static native boolean	fromGuiToPluginOfferReply( int iPlugin, long u64IdHiPart, long u64IdLoPart, int iUserData, int iResponse, long lclSessionIdHiPart, long lclSessionIdLoPart );
	public static native int		fromGuiPluginControl( 	int iPlugin, long u64IdHiPart, long u64IdLoPart, 
															String strControl, String strAction, int u32ActionData, 
															long lclSessionIdHiPart, long lclSessionIdLoPart, byte[] fileHashId );
	public static native boolean	fromGuiInstMsg( long u64IdHiPart, long u64IdLoPart, int iPlugin, String strMsg );
	      
	public static native void		fromGuiRequireRelay( boolean bRequireRelay );
	public static native void		fromGuiUseRelay( long u64IdHiPart, long u64IdLoPart, boolean bUseAsRelay ); 
	
	//! request list of contacts
	public static native void		fromGuiSendContactList( int iFriendViewType );  
	public static native void		fromGuiRefreshContactList();  
	
	public static native void 		fromGuiStartScan( int eScanType, int searchFlags, int fileTypeFlags, String strSearchPattern );
	public static native void 		fromGuiNextScan( int eScanType );
	public static native void 		fromGuiStopScan( int eScanType );
	
	//============================================================================
	// misc
	//============================================================================
	public static native String		fromGuiGetMyIPv4Address();
	public static native String		fromGuiGetMyIPv6Address();

	public static native void 		fromGuiUserModifiedStoryboard();

	public static native void 		fromGuiCancelDownload( long lclSessionIdHiPart, long lclSessionIdLoPart );
	public static native void 		fromGuiCancelUpload( long lclSessionIdHiPart, long lclSessionIdLoPart );
	
	public static native boolean	fromGuiSetGameValueVar( int iPlugin, long u64IdHiPart, long u64IdLoPart, int s32VarId, int s32VarValue );
	public static native boolean	fromGuiSetGameActionVar( int iPlugin, long u64IdHiPart, long u64IdLoPart, int s32VarId, int s32VarValue );


	public static native boolean	fromGuiTestCmd(	int			eTestParam1, 
													int			testParam2, 
													String		testParam3 );
	//! request random tcp port
	public static native int		fromGuiGetRandomTcpPort();
	public static native int		fromGuiMulitcastPkt( byte[] data, int len );		
	
	public static native boolean	fromGuiBrowseFiles(	String dir, boolean lookupShareStatus, int fileFilterMask );
	public static native boolean	fromGuiGetSharedFiles( int fileTypeFilter );
	public static native boolean	fromGuiSetFileIsShared( String fileName, boolean isShared, byte[] fileHashId );
	public static native boolean	fromGuiGetIsFileShared( String fileName );
	
	public static native int		fromGuiGetFileDownloadState( byte[] fileHashId );
	public static native void		fromGuiGetFileLibraryList( int fileTypeFilter );
	public static native boolean	fromGuiAddFileToLibrary( String fileName, boolean addFile, byte[] fileHashId );
	public static native boolean	fromGuiGetIsFileInLibrary( String fileName );
	public static native boolean	fromGuiIsMyP2PWebVideoFile( String fileName );
	public static native boolean	fromGuiIsMyP2PWebAudioFile( String fileName );
	
	public static native int		fromGuiDeleteFile( String fileName, boolean shredFile );

	public static native boolean	fromGuiAssetAction( int assetAction, AssetGuiInfo assetInfo, int actionParam );
	// can't have 2 functions with same name
	public static native boolean	fromGuiAssetActionById( int assetAction, long assetIdHiPart, long assetIdLoPart, int actionParam );

	public static native boolean	fromGuiVideoRecord( int eRecState, long feedIdHiPart, long feedIdLoPart, String fileName );
	public static native boolean	fromGuiSndRecord( int eRecState, long feedIdHiPart, long feedIdLoPart, String fileName );
	
	public static native void		fromGuiQuerySessionHistory( long historyIdHiPart, long historyIdLoPart );
	public static native boolean	fromGuiMultiSessionAction( int sessionAction, long onlineIdHiPart, long onlineIdLoPart, int actionParam );
	
	public static native void		fromGuiGetFileDownloadsList();
	public static native void		fromGuiGetFileUploadsList();

	public static native void		fromGuiKickWatchdog();
	
};



