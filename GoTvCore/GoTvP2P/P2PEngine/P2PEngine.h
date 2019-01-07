#pragma once
//============================================================================
// Copyright (C) 2009 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "config_gotvcore.h"

#include "P2PConnectList.h"
#include "EngineSettings.h"
#include "EngineParams.h"

#include <GoTvCore/GoTvP2P/AssetMgr/AssetCallbackInterface.h>

#include <GoTvInterface/IFromGui.h>

#include <GoTvCore/GoTvP2P/Search/RcScan.h>

#include <GoTvCore/GoTvP2P/BigListLib/BigListMgr.h>
#include <NetLib/VxSktDefs.h>
#include <PktLib/PktAnnounce.h>
#include <PktLib/PktSysHandlerBase.h>
#include <PktLib/PktsImAlive.h>

class IToGui;
class IGoTv;
class FileShareSettings;
class VxPeerMgr;
class PluginMgr;
class AssetMgr;
class AnchorTest;
class IsPortOpenTest;
class RcConnectInfo;
class PluginRelay;
class PluginFileShare;
class PluginNetServices;
class ConnectRequest;
class MediaProcessor;
class NetworkMgr;
class NetworkStateMachine;
class NetConnector;
class NetworkMonitor;
class NetServicesMgr;

class P2PEngine :	public IFromGui,
					public PktHandlerBase,
					public AssetCallbackInterface,
					public MediaCallbackInterface
{
public:
	P2PEngine(	IToGui&			toGui,
				VxPeerMgr&		peerMgr );
	virtual ~P2PEngine();

	void						startupEngine( void );
	void						shutdownEngine( void );

	IToGui&						getToGuiInterface( void )						{ return m_ToGui; }
	IFromGui&					getFromGuiInterface( void )						{ return *this; }
	AssetMgr&					getAssetMgr( void )								{ return m_AssetMgr; }	
	EngineSettings&				getEngineSettings( void )						{ return m_EngineSettings; }
	EngineParams&				getEngineParams( void )							{ return m_EngineParams; }
	BigListMgr&					getBigListMgr( void )							{ return m_BigListMgr; }
	P2PConnectList&				getConnectList( void )							{ return m_ConnectionList; }
	NetworkMgr&					getNetworkMgr( void )							{ return m_NetworkMgr; } 
	NetConnector&				getNetConnector( void )							{ return m_NetConnector; } 
	NetworkMonitor&				getNetworkMonitor( void )						{ return m_NetworkMonitor; } 
	NetServicesMgr&				getNetServicesMgr( void )						{ return m_NetServicesMgr; }
	PluginMgr&					getPluginMgr( void )							{ return m_PluginMgr; }
	MediaProcessor&				getMediaProcesser( void )						{ return m_MediaProcessor; }
	VxPeerMgr&					getPeerMgr( void )								{ return m_PeerMgr; }
	RcScan&						getRcScan( void )								{ return m_RcScan; }
	NetworkStateMachine&		getNetworkStateMachine( void )					{ return m_NetworkStateMachine; }
	bool						isAppPaused( void )								{ return m_AppIsPaused; }
	bool						isP2POnline( void );

	void						lockAnnouncePktAccess( void )					{ m_AnnouncePktMutex.lock(); }
	PktAnnounce&				getMyPktAnnounce( void )						{ return m_PktAnn; }
	VxGUID&						getMyOnlineId( void )							{ return m_PktAnn.getMyOnlineId(); }
	void						unlockAnnouncePktAccess( void )					{ m_AnnouncePktMutex.unlock(); }

	PluginRelay&				getPluginRelay( void )							{ return * m_PluginRelay; }
	PluginFileShare&			getPluginFileShare( void )						{ return * m_PluginFileShare; }
	PluginNetServices&			getPluginNetServices( void )					{ return * m_PluginNetServices; }

	virtual void				setPluginPermission( EPluginType ePluginType, int iPluginPermission );
	virtual int					getPluginPermission( int iPluginType );

	virtual void				setHasPicture( int bHasPicture );
	virtual void				setHasSharedWebCam( int bHasShaeredWebCam );
	bool						isContactConnected( VxGUID& onlineId );
	bool						isSystemPlugin( EPluginType	ePluginType );

	//========================================================================
	// from gui
	//========================================================================
	void						assureUserSpecificDirIsSet( const char * checkReason );

	virtual void				fromGuiSetIsAppCommercial( bool isCommercial );
	virtual bool				fromGuiGetIsAppCommercial( void );
	virtual uint16_t			fromGuiGetAppVersionBinary( void );
	const char *				fromGuiGetAppVersionString( void );
	virtual const char *		fromGuiGetAppName( void );
	virtual const char *		fromGuiGetAppNameNoSpaces( void );
	virtual void				fromGuiAppStartup( const char * assetDir, const char * rootDataDir  );

	virtual void				fromGuiKickWatchdog( void );
	virtual void				fromGuiSetUserSpecificDir( const char * userSpecificDir  );
	virtual void				fromGuiSetUserXferDir( const char * userXferDir  );
	virtual uint64_t			fromGuiGetDiskFreeSpace( void  ); 
	virtual void				fromGuiAppShutdown( void  );
	virtual void				fromGuiAppIdle( void  );
	virtual void				fromGuiAppPause( void );
	virtual void				fromGuiAppResume( void );

	virtual void				fromGuiUserLoggedOn( VxNetIdent * netIdent );
	virtual void				fromGuiOnlineNameChanged( const char * newOnlineName );
	virtual void				fromGuiMoodMessageChanged( const char * newMoodMessage );
	virtual void				fromGuiSetUserHasProfilePicture( bool haveProfilePick );
	virtual void				fromGuiUpdateMyIdent( VxNetIdent * netIdent, bool permissionAndStatsOnly = false );
	virtual void				fromGuiQueryMyIdent( VxNetIdent * poRetIdent );
	virtual void				fromGuiSetIdentHasTextOffers( VxGUID& onlineId, bool hasTextOffers ); 

	virtual bool				fromGuiOrientationEvent( float f32RotX, float f32RotY, float f32RotZ  );
	virtual bool				fromGuiMouseEvent( EMouseButtonType eMouseButType, EMouseEventType eMouseEventType, int iMouseXPos, int iMouseYPos  );
	virtual bool				fromGuiMouseWheel( float f32MouseWheelDist ); 
	virtual bool				fromGuiKeyEvent( EKeyEventType eKeyEventType, EKeyCode eKey, int iFlags = 0 );

	virtual void				fromGuiNativeGlInit( void );
	virtual void				fromGuiNativeGlResize( int w, int h );
	virtual int					fromGuiNativeGlRender( void );
	virtual void				fromGuiNativeGlPauseRender( void );
	virtual void				fromGuiNativeGlResumeRender( void );
	virtual void				fromGuiNativeGlDestroy( void );

	virtual void				fromGuiMicrophoneData( int16_t * pu16PcmData, uint16_t pcmDataLenBytes );
	virtual void				fromGuiMicrophoneDataWithInfo( int16_t * pcmData, int pcmDataLenBytes, int totalDelayTimeMs, int clockDrift );
	virtual void				fromGuiMuteMicrophone( bool muteMic ); 
	virtual bool				fromGuiIsMicrophoneMuted( void ); 
	virtual void				fromGuiMuteSpeaker(	bool muteSpeaker ); 
	virtual bool				fromGuiIsSpeakerMuted( void ); 
	virtual void				fromGuiEchoCancelEnable( bool enableEchoCancel ); 
	virtual bool				fromGuiIsEchoCancelEnabled( void ); 

	virtual void				fromGuiAudioOutSpaceAvail( int freeSpaceLen );

	virtual bool				fromGuiSndRecord( ESndRecordState eRecState, VxGUID& feedId, const char * fileName );
	virtual bool				fromGuiVideoRecord( EVideoRecordState eRecState, VxGUID& feedId, const char * fileName );
	virtual bool				fromGuiPlayLocalMedia( const char * fileName, uint64_t fileLen, uint8_t fileType, int pos0to100000 = 0 );


	virtual bool				fromGuiAssetAction( EAssetAction assetAction, AssetInfo& assetInfo, int pos0to100000 = 0 );
	virtual bool				fromGuiAssetAction( EAssetAction assetAction, VxGUID& assetId, int pos0to100000 = 0 );
	virtual bool				fromGuiSendAsset( AssetInfo& assetInfo );

	virtual void				fromGuiWantMediaInput( EMediaInputType mediaType, MediaCallbackInterface * callback, void * userData, bool wantInput );
	virtual void				fromGuiWantMediaInput( VxGUID& onlineId, EMediaInputType mediaType, bool wantInput );

	virtual void				fromGuiVideoData( uint32_t u32FourCc, uint8_t * pu8VidDataIn, int iWidth, int iHeight, uint32_t u32VidDataLen, int iRotation );
	virtual bool				fromGuiMovieDone( void )							{ return true; };

	virtual void				fromGuiNetworkAvailable( const char * lclIp = NULL, bool isCellularNetwork = false );
	virtual void				fromGuiNetworkLost( void );
	virtual void				fromGuiNetworkSettingsChanged( void );

	virtual void				fromGuiVerifyAnchorSettings( void );
	virtual void				fromGuiRunIsPortOpenTest( uint16_t port );

	virtual void				fromGuiUpdateWebPageProfile(	const char *	pProfileDir,	// directory containing user profile
																const char *	strGreeting,	// greeting text
																const char *	aboutMe,		// about me text
																const char *	url1,			// favorite url 1
																const char *	url2,			// favorite url 2
																const char *	url3 );			// favorite url 3

	virtual void				fromGuiSetNetSettings( NetSettings& netSettings );
	virtual void				fromGuiGetNetSettings( NetSettings& netSettings );
	virtual void				fromGuiSetRelaySettings( int userRelayMaxCnt, int systemRelayMaxCnt );

	virtual void				fromGuiGetFileShareSettings( FileShareSettings& fileShareSettings );
	virtual void				fromGuiSetFileShareSettings( FileShareSettings& fileShareSettings );

	virtual void				fromGuiSetPluginPermission( EPluginType ePluginType, EFriendState eFriendState );
	virtual int					fromGuiGetPluginPermission( EPluginType ePluginType );
	virtual EPluginServerState	fromGuiGetPluginServerState( EPluginType ePluginType );

	virtual void				fromGuiStartPluginSession( EPluginType ePluginType, VxGUID& onlineId, int pvUserData = 0, VxGUID lclSessionId = VxGUID::nullVxGUID() );
	virtual void				fromGuiStopPluginSession( EPluginType ePluginType, VxGUID& onlineId, int pvUserData = 0, VxGUID lclSessionId = VxGUID::nullVxGUID()  );
	virtual bool				fromGuiIsPluginInSession( EPluginType ePluginType, VxNetIdent * netIdent = NULL, int pvUserData = 0, VxGUID lclSessionId = VxGUID::nullVxGUID() );

	virtual bool				fromGuiMakePluginOffer(	EPluginType		ePluginType, 
														VxGUID&			onlineId,
														int				pvUserData,
														const char *	pOfferMsg, 
														const char *	pFileName = NULL,
														uint8_t *			fileHashId = 0,
														VxGUID			lclSessionId = VxGUID::nullVxGUID() );

	virtual bool				fromGuiToPluginOfferReply(	EPluginType		ePluginType,
															VxGUID&			onlineId,
															  int			pvUserData,
															int				iOfferResponse,
															VxGUID			lclSessionId );

	virtual int					fromGuiPluginControl(	EPluginType		ePluginType, 
														VxGUID&			onlineId, 
														const char *	pControl, 
														const char *	pAction,
														uint32_t				u32ActionData,
														VxGUID&			fileId = VxGUID::nullVxGUID(),
														uint8_t *			fileHashId = 0 );

	virtual bool				fromGuiInstMsg(		EPluginType		ePluginType, 
													VxGUID&			onlineId, 
													const char *	pMsg ); 

	virtual bool				fromGuiChangeMyFriendshipToHim(	VxGUID&			onlineId, 
																EFriendState	eMyFriendshipToHim,
																EFriendState	eHisFriendshipToMe );
	virtual void				fromGuiSendContactList( EFriendViewType eFriendView, int MaxContactsToSend );
	virtual void				fromGuiRefreshContactList( int MaxContactsToSend );

	virtual void				fromGuiRequireRelay( bool bRequireRelay );
	virtual void				fromGuiUseRelay( VxGUID& onlineId, bool bUseAsRelay = true );
	virtual void				fromGuiRelayPermissionCount( int userPermittedCount, int anonymousCount ); 

	virtual void				fromGuiStartScan( EScanType eScanType, uint8_t searchFlags, uint8_t fileTypeFlags, const char * pSearchPattern = "" );
	virtual void				fromGuiNextScan( EScanType eScanType );
	virtual void				fromGuiStopScan( EScanType eScanType );

	virtual InetAddress			fromGuiGetMyIPv4Address( void );
	virtual InetAddress			fromGuiGetMyIPv6Address( void );

	virtual void				fromGuiUserModifiedStoryboard( void );

	virtual void				fromGuiCancelDownload( VxGUID& fileInstance );
	virtual void				fromGuiCancelUpload( VxGUID& fileInstance );

	virtual bool				fromGuiSetGameValueVar( EPluginType	ePluginType, 
														VxGUID&		onlineId, 
														int32_t			varId, 
														int32_t			varValue );

	virtual bool				fromGuiSetGameActionVar(	EPluginType	ePluginType, 
															VxGUID&		onlineId, 
															int32_t			actionId, 
															int32_t			actionValue );

	virtual bool				fromGuiTestCmd(	ETestParam1		eTestParam1, 
												int				testParam2 = 0, 
												const char *	testParam3 = NULL );

	virtual uint16_t			fromGuiGetRandomTcpPort( void );
#ifdef TARGET_OS_ANDROID
	virtual int					fromGuiMulitcastPkt( unsigned char * data, int len );
#endif // TARGET_OS_ANDROID
	virtual void				fromGuiDebugSettings( uint32_t u32LogFlags, const char *	pLogFileName = NULL );
	virtual void				fromGuiSendLog( uint32_t u32LogFlags );
	virtual bool				fromGuiBrowseFiles(	const char * dir, bool lookupShareStatus, uint8_t fileFilterMask = VXFILE_TYPE_ALLNOTEXE | VXFILE_TYPE_DIRECTORY ); 
	virtual bool				fromGuiGetSharedFiles( uint8_t fileTypeFilter );
	virtual bool				fromGuiSetFileIsShared( const char * fileName, bool isShared, uint8_t * fileHashId = 0 );
	virtual bool				fromGuiGetIsFileShared( const char * fileName );
	// returns -1 if unknown else percent downloaded
	virtual int					fromGuiGetFileDownloadState( uint8_t * fileHashId );
	virtual bool				fromGuiAddFileToLibrary( const char * fileName, bool addFile, uint8_t * fileHashId = 0 );
	virtual void				fromGuiGetFileLibraryList( uint8_t fileTypeFilter );
	virtual bool				fromGuiGetIsFileInLibrary( const char * fileName );
	virtual bool				fromGuiIsMyP2PWebVideoFile( const char * fileName );
	virtual bool				fromGuiIsMyP2PWebAudioFile( const char * fileName );

	virtual int					fromGuiDeleteFile( const char * fileName, bool shredFile );

	virtual void				fromGuiQuerySessionHistory( VxGUID& historyId );
	virtual bool				fromGuiMultiSessionAction( EMSessionAction mSessionAction, VxGUID& onlineId, int pos0to100000, VxGUID lclSessionId = VxGUID::nullVxGUID() );

	//========================================================================
	// to gui
	//========================================================================
	void						sendToGuiStatusMessage( const char * statusMsg, ... );
	void						toGuiPluginPermissionChange( PktAnnounce * poPktAnn );

	void						toGuiContactDescChange( PktAnnounce * poPktAnn );
	void						toGuiContactNameChange( PktAnnounce * poPktAnn );
	void						toGuiContactMyFriendshipChange( PktAnnounce * poPktAnn );
	void						toGuiContactHisFriendshipChange( PktAnnounce * poPktAnn );
	void						toGuiContactSearchFlagsChange( PktAnnounce * poPktAnn );
	void						toGuiContactConnectionChange( PktAnnounce * poPktAnn );
	void						toGuiContactAnythingChange( PktAnnounce * poPktAnn );

	int 						toGuiSendAdministratorList( int iSentCnt, int iMaxSendCnt );
	int 						toGuiSendFriendList( int iSentCnt, int iMaxSendCnt );
	int 						toGuiSendGuestList( int iSentCnt, int iMaxSendCnt );
	int							toGuiSendAnonymousList( int iSentCnt, int iMaxSendCnt );
	int							toGuiSendIgnoreList( int iSentCnt, int iMaxSendCnt );
	int							toGuiSendMyProxiesList( int iSentCnt, int iMaxSendCnt );
	int							toGuiSendAllProxiesList( int iSentCnt, int iMaxSendCnt );
	//========================================================================
	// asset mgr callbacks
	//========================================================================
	virtual void				callbackFileWasShredded( std::string& fileName );
	virtual void				callbackAssetAdded( AssetInfo * assetInfo );
	virtual void				callbackAssetRemoved( AssetInfo * assetInfo );

	virtual void				callbackSharedFileTypesChanged( uint16_t fileTypes );
	virtual void				callbackSharedPktFileListUpdated( void );

	virtual void				callbackAssetHistory( void * userData, AssetInfo * assetInfo );
	//========================================================================
	// media processor callbacks
	//========================================================================
	virtual void				callbackVideoJpgBig( void * userData, VxGUID& vidFeedId, uint8_t * jpgData, uint32_t jpgDataLen );
	virtual void				callbackVideoJpgSmall(	void * userData, VxGUID& vidFeedId, uint8_t * jpgData, uint32_t jpgDataLen, int motion0to100000 );

	//========================================================================
	//========================================================================
	void						onOncePerSecond( void );
	void						onOncePer30Seconds( void );
	void						onOncePerMinute( void );
	void						onOncePerHour( void );

	void						onBigListInfoRestored( BigListInfo * poInfo ); 
	void						onBigListLoadComplete( RCODE rc );
	void						onBigListInfoDelete( BigListInfo * poInfo );

	virtual	void				onContactConnected		( RcConnectInfo * poInfo, bool connectionListLocked, bool newContact = false );
	virtual	void				onContactDisconnected	( RcConnectInfo * poInfo, bool connectionListLocked );
	virtual	void				onContactNearby			( BigListInfo * poBigListInfo );
	virtual	void				onContactNotNearby		( BigListInfo * poBigListInfo );

	void						onConnectionLost( VxSktBase * sktBase );
	void						onSessionStart( EPluginType ePluginType, VxNetIdent * netIdent );
	//========================================================================
	//========================================================================

	void						handleTcpData( VxSktBase * sktBase );
	void						handleMulticastData( VxSktBase * sktBase );

	std::string					describeContact( BigListInfo * bigListInfo );
	std::string					describeContact( VxConnectInfo& connectInfo );
	std::string					describeContact( ConnectRequest& connectRequest );

	void						broadcastSystemPkt( VxPktHdr * pkt, bool onlyIncludeMyContacts );
	void						broadcastSystemPkt( VxPktHdr * pkt, VxGUIDList& retIdsSentPktTo );

	virtual bool				txSystemPkt(	VxNetIdentBase *	netIdent,
												VxSktBase *			sktBase, 
												VxPktHdr *			poPkt, 
												bool				bDisconnectAfterSend = false );

	virtual bool				txSystemPkt(	VxGUID&				destOnlineId, 
												VxSktBase *			sktBase, 
												VxPktHdr *			poPkt, 
												bool				bDisconnectAfterSend = false );

	virtual bool				txImAlivePkt(	VxGUID&				destOnlineId, 
												VxSktBase *			sktBase );

	virtual void				replaceConnection( VxNetIdent * netIdent, VxSktBase * poOldSkt, VxSktBase * poNewSkt );

	bool						connectToContact(	VxConnectInfo&		connectInfo, 
													VxSktBase **		ppoRetSkt,
													bool&				retIsNewConnection,
													EConnectReason		connectReason = eConnectReasonStayConnected );

	virtual void				doPktAnnHasChanged( bool connectionListIsLocked );

	bool						shouldInfoBeInDatabase( BigListInfo * poInfo );

	//! called if hacker offense is detected
	void						hackerOffense(	VxNetIdent *	poContactIdent,			// users identity info ( may be null if not known then use ipAddress )
												uint32_t				u32HackLevel,			// 1=severe 2=medium 3=suspicious
												InetAddress		IpAddr,					// ip address if identity not known
												const char *	pMsg, ... );			// message about the offense

	virtual void				onPotentialRelayServiceAvailable( RcConnectInfo * poConnection, bool connectionListIsLocked );
	virtual void				onRelayServiceAvailable( RcConnectInfo * poConnection, bool connectionListIsLocked );
	virtual void				onRelayServiceUnavailable( RcConnectInfo * poConnection, bool connectionListIsLocked );
protected:
	//========================================================================
	// pkt handlers
	//========================================================================

	virtual void				onPktUnhandled					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktInvalid					( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktAnnList					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAnnounce					( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktLogReq						( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktLogReply					( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktSearchReq					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktSearchReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktPluginOfferReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktPluginOfferReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktChatReq					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktChatReply					( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktVoiceReq					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktVoiceReply					( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktVideoFeedReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktVideoFeedStatus			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktVideoFeedPic				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktVideoFeedPicChunk			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktVideoFeedPicAck			( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktFileGetReq					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileGetReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileSendReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileSendReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktFindFileReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFindFileReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktFileListReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileListReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktFileInfoReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktFileChunkReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileChunkReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileSendCompleteReq		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileSendCompleteReply		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileGetCompleteReq			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileGetCompleteReply		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktFileShareErr				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktAssetSendReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAssetSendReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAssetChunkReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAssetChunkReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAssetSendCompleteReq		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAssetSendCompleteReply		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktAssetXferErr				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktMultiSessionReq			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktMultiSessionReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktSessionStartReq			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktSessionStartReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktSessionStopReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktSessionStopReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktRelayServiceReq			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayServiceReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayConnectReq			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayConnectReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayDisconnect			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelaySessionReq			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelaySessionReply			( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayConnectToUserReq		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayConnectToUserReply	( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayUserDisconnect		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayTestReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktRelayTestReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktMyPicSendReq				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktMyPicSendReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktWebServerPicChunkTx		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktWebServerPicChunkAck		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktWebServerGetChunkTx		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktWebServerGetChunkAck		( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktWebServerPutChunkTx		( VxSktBase * sktBase, VxPktHdr * poPktHdrt );
	virtual void				onPktWebServerPutChunkAck		( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktTodGameStats				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktTodGameAction				( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktTodGameValue				( VxSktBase * sktBase, VxPktHdr * pktHdr );

	virtual void				onPktTcpPunch					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktPingReq					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktPingReply					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktImAliveReq					( VxSktBase * sktBase, VxPktHdr * pktHdr );
	virtual void				onPktImAliveReply				( VxSktBase * sktBase, VxPktHdr * pktHdr );

    //========================================================================
    //========================================================================
    void						iniitializePtoPEngine( void );
	void						bigListLoadComplete( RCODE rc );

	virtual bool				txPluginPkt( 	EPluginType			ePluginType, 
												VxNetIdentBase *	netIdent, 
												VxSktBase *			sktBase, 
												VxPktHdr *			poPkt, 
												bool				bDisconnectAfterSend );

	virtual void				doAppStateChange( EAppState eAppState );
	virtual bool				shouldNotifyGui( VxNetIdent * netIdent );

	// pkt ann has changed and needs to be re announced
	void						doPktAnnConnectionInfoChanged( bool connectionListIsLocked );
	virtual	void				attemptConnectionToRelayService( BigListInfo * poInfo );
	void						handleIncommingRelayData( VxSktBase * sktBase, VxPktHdr * pktHdr );
	void						sendToGuiTheContactList( int maxContactsToSend );

	//=== vars ===//
	IToGui&						m_ToGui;
	VxPeerMgr&					m_PeerMgr;

	PktAnnounce					m_PktAnn;
	VxMutex						m_AnnouncePktMutex;
	EngineSettings				m_EngineSettings;
	EngineParams				m_EngineParams;
	AssetMgr&					m_AssetMgr;
	BigListMgr					m_BigListMgr;
	P2PConnectList				m_ConnectionList;
	NetworkMgr&					m_NetworkMgr;
	NetworkMonitor&				m_NetworkMonitor;
	NetServicesMgr&				m_NetServicesMgr;
	NetConnector&				m_NetConnector;
	NetworkStateMachine&		m_NetworkStateMachine;
	AnchorTest&					m_AnchorTest;

	PluginMgr&					m_PluginMgr;
	MediaProcessor&				m_MediaProcessor;
	PluginRelay *				m_PluginRelay;
	PluginFileShare *			m_PluginFileShare;
	PluginNetServices *			m_PluginNetServices;
	IsPortOpenTest&				m_IsPortOpenTest;

	RcScan						m_RcScan;

	EAppState					m_eAppState;

	EFriendViewType				m_eFriendView;
	unsigned int				m_iCurPreferredRelayConnectIdx;
	VxGUID						m_NextFileInstance;
	time_t						m_LastTimeAnnounceFromContactListCalled;
	bool						m_AppStartupCalled;
	bool						m_AppIsPaused;
	bool						m_IsUserSpecificDirSet;
    bool                        m_EngineInitialized;

	PktImAliveReq				m_PktImAliveReq;

private:
	P2PEngine(); // don't allow default constructor
	P2PEngine( const P2PEngine& ); // don't allow copy constructor

};

