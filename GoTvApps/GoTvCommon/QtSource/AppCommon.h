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

#include "config_gotvapps.h"
#include "AppDefs.h"
#include "AppGlobals.h"
#include "VxAppDisplay.h"
#include "ToGuiActivityClient.h"
#include "ToGuiFileXferClient.h"
#include "ToGuiHardwareCtrlClient.h"
#include "GoTvInterface/IToGui.h"
#include "GoTvInterface/IGoTvRender.h"
#include "GoTvInterface/IGoTvEvents.h"
#include "AudioOutQt.h"

#include "HomeWindow.h"

#include "FriendList.h"

#include "VxGuidQt.h"

#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QDialog>
#include <QObject>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>


class IVxVidCap;
class ListEntryWidget;
class FileListReplySession;
class ActivityCreateProfile;
class ActivityOfferListDlg;
class ActivityDownloads;
class ActivityUploads;
class ActivityAbout;
class ActivityDebugSettings;
class ActivityShowHelp;
class GuiOfferSession;
class GuiFileXferSession;
class VxPeerMgr;
class PopupMenu;
class VxDataHelper;
class VxMyFileInfo;
class AppSettings;
class VxAppTheme;
class VxAppStyle;
class VxTilePositioner;
class AppletMgr;
class IGoTv;
class RenderGlWidget;
class KodiThread;


// media
class CRenderBuffer;


class AppCommon : public QWidget, public IToGui, public IGoTvRender, public IGoTvEvents
{
	Q_OBJECT

public:
	AppCommon(	QApplication&   myQApp,
				EDefaultAppMode appDefaultMode,
				AppSettings&    appSettings,
				VxDataHelper&   myDataHelper,
				IGoTv&		    gotv );
	virtual ~AppCommon();

    IFromGui&					getFromGuiInterface( void );
	QApplication&				getQApplication( void )						{ return m_QApp; }
	AppGlobals&					getAppGlobals( void )						{ return m_AppGlobals; }
	AppSettings&				getAppSettings( void )						{ return m_AppSettings; }
	VxDataHelper&				getDataHelper( void )						{ return m_DataHelper; }
    IGoTv&				        getGoTv( void )						        { return m_GoTv; }
	VxPeerMgr&					getPeerMgr( void )							{ return m_VxPeerMgr; }
	QString&					getAppTitle( void )							{ return m_AppTitle; }
	QString&					getAppShortName( void )						{ return m_AppShortName; }
	MyIcons&					getMyIcons( void )							{ return m_MyIcons; }
	VxAppTheme&					getAppTheme( void )							{ return m_AppTheme; }
	VxAppStyle&					getAppStyle( void )							{ return m_AppStyle; }
    VxAppDisplay&				getAppDisplay( void )                       { return m_AppDisplay; }

	P2PEngine&					getEngine( void )							{ return m_Engine; }
	MySndMgr&					getSoundMgr( void )							{ return m_MySndMgr; }
	HomeWindow&					getHomePage( void )							{ return m_HomePage; }
	VxTilePositioner&			getTilePositioner( void )					{ return m_TilePositioner; }

	OffersMgr&					getOffersMgr( void )						{ return m_OffersMgr; }

	QWidget *					getCentralWidget( void )					{ return 0; } // ui.centralWidget; }

    void                        setKodiThread( KodiThread * kodiThread )    { m_KodiThread = kodiThread; }
    KodiThread *                getKodiThread()                             { return m_KodiThread; }

	ActivityDownloads *			getActivityDownloads( void )				{ return m_Downloads; } 
	ENetworkStateType			getNetworkState( void )						{ return m_LastNetworkState; }
    RenderGlWidget *            getRenderConsumer( void );

	bool						getIsVidCaptureEnabled( void )				{ return m_VidCaptureEnabled; }
	bool						getIsMicrophoneHardwareEnabled( void )		{ return m_MicrophoneHardwareEnabled; }
	bool						getIsSpeakerHardwareEnabled( void )			{ return m_SpeakerHardwareEnabled; }

	void						setCamCaptureRotation( uint32_t rot );
	int							getCamCaptureRotation( void )				{ return m_CamCaptureRotation; }

	void 						setAccountUserName( const char * name )		{ m_strAccountUserName = name; } 
	std::string					getAccountUserName( void )					{ return m_strAccountUserName; } 
	VxNetIdent *				getMyIdentity( void );

	void						setIsMaxScreenSize(  bool isMessagerFrame, bool isFullSizeWindow );
	bool						getIsMaxScreenSize( bool isMessagerFrame );

	void						switchWindowFocus( QWidget * goTvButton );

	void						applySoundSettings( bool useDefaultsInsteadOfSettings = false );
	void						playSound( ESndDef sndDef );
	void						insertKeystroke( int keyNum );

	void						forceOrientationChange( void );

	virtual void				okMessageBox( QString title, QString msg );
	virtual void				okMessageBox2( QString title, const char * msg, ... );
	virtual bool				yesNoMessageBox( QString title, QString msg );
	virtual bool				yesNoMessageBox2( QString title, const char * msg, ... );
	virtual void				errMessageBox( QString title, QString msg );
	virtual void				errMessageBox2( QString title, const char * msg, ... );

	//=== app methods ===//
	virtual void				startupAppCommon( QFrame * appletFrame, QFrame * messangerFrame );
    virtual void				startLogin( void );
    virtual void				doLogin( void );
    virtual void				completeLogin( void );

	// prompt user to confirm wants to shutdown app.. caller must call appCommonShutdown if answer is yes
	virtual bool				confirmAppShutdown( QWidget * parentWindow );
	virtual void				shutdownAppCommon( void );

	void						loadAccountSpecificSettings( const char * userName );

	QFrame *					getAppletFrame( EApplet applet );
	void						launchApplet( EApplet applet, QWidget * parent );

	void						activityStateChange( ActivityBase * activity, bool isCreated );
	void						startActivity( EPluginType ePluginType, VxNetIdent * friendIdent, QWidget * parent = 0 );
	void						executeActivity( GuiOfferSession * offer, QWidget * parent );

	void						launchLibraryActivity( uint8_t fileTypeFilter = 0 );
	void						setIsLibraryActivityActive( bool isActive )						{ m_LibraryActivityActive = isActive; }
	bool						getIsLibraryActivityActive( void )								{ return m_LibraryActivityActive; }

	void						wantToGuiActivityCallbacks(	ToGuiActivityInterface *	callback, 
															void *						userData,
															bool						wantCallback );
	void						wantToGuiFileXferCallbacks( ToGuiFileXferInterface *	callback, 
															void *						userData,
															bool						wantCallback );
	void						wantToGuiHardwareCtrlCallbacks( ToGuiHardwareControlInterface *	callback, 
																bool							wantCallback );

	bool						getIsPluginVisible( EPluginType ePluginType );
	void						setPluginVisible( EPluginType ePluginType, bool isVisible );


    //============================================================================
    //=== to gotv lib events ===//
    //============================================================================
    virtual void                fromGuiKeyPressEvent( int moduleNum, int key, int mod );
    virtual void                fromGuiKeyReleaseEvent( int moduleNum, int key, int mod );

    virtual void                fromGuiMousePressEvent( int moduleNum, int mouseXPos, int mouseyPos, int mouseButton );
    virtual void                fromGuiMouseReleaseEvent( int moduleNum, int mouseXPos, int mouseyPos, int mouseButton );
    virtual void                fromGuiMouseMoveEvent( int moduleNum, int mouseXPos, int mouseyPos );

    virtual void                fromGuiResizeEvent( int moduleNum, int winWidth, int winHeight );
    virtual void                fromGuiCloseEvent( int moduleNum );
    virtual void                fromGuiVisibleEvent( int moduleNum, bool isVisible );

    //============================================================================
    //=== to gui media/render ===//
    //============================================================================

    //=== textures ===//
    void                        setActiveGlTexture( unsigned int activeTextureNum = 0 /* 0 == GL_TEXTURE0 , 1 == GL_TEXTURE1 etc*/ ) override;

    void                        createTextureObject( CQtTexture * texture ) override;
    void                        destroyTextureObject( CQtTexture * texture ) override;
    bool                        loadToGPU( CQtTexture * texture ) override;
    void                        bindToUnit( CQtTexture * texture, unsigned int unit ) override;

    void                        beginGuiTexture( CGUITextureQt * guiTexture, GoTvColor color ) override;
    void                        drawGuiTexture( CGUITextureQt * guiTexture, float * x, float * y, float * z, const GoTvRect& texture, const GoTvRect& diffuse, int orientation ) override;
    void                        endGuiTexture( CGUITextureQt * guiTexture ) override;
    void                        drawQuad( const GoTvRect &rect, GoTvColor color, CBaseTexture * texture, const GoTvRect * texCoords ) override;

    bool                        firstBegin( CGUIFontTTFQt * font )  override;
    void                        lastEnd( CGUIFontTTFQt * font ) override;
    CVertexBuffer               createVertexBuffer( CGUIFontTTFQt * font, const std::vector<SVertex> &vertices )  override;
    void                        destroyVertexBuffer( CGUIFontTTFQt * font, CVertexBuffer &buffer )  override;

    virtual void                deleteHardwareTexture( CGUIFontTTFQt * font )  override;
    virtual void                createStaticVertexBuffers( CGUIFontTTFQt * font )  override;
    virtual void                destroyStaticVertexBuffers( CGUIFontTTFQt * font )  override;

    //=== render ===//
    void                        captureScreen( CScreenshotSurface * screenCaptrue, GoTvRect& captureArea ) override;

    void                        toGuiRenderVideoFrame( int textureIdx, CRenderBuffer* videoBuffer );
    bool                        initRenderSystem() override;
    bool                        destroyRenderSystem() override;
    bool                        resetRenderSystem( int width, int height ) override;

    int                         getMaxTextureSize() override;

    bool                        beginRender() override;
    bool                        endRender() override;
    void                        presentRender( bool rendered, bool videoLayer ) override;
    bool                        clearBuffers( GoTvColor color ) override;
    bool                        isExtSupported( const char* extension ) override;

    void                        setVSync( bool vsync ) override;
    void                        resetVSync() override {  }

    void                        setViewPort( const GoTvRect& viewPort ) override;
    void                        getViewPort( GoTvRect& viewPort ) override;

    bool                        scissorsCanEffectClipping() override;
    GoTvRect                    clipRectToScissorRect( const GoTvRect &rect ) override;
    void                        setScissors( const GoTvRect& rect ) override;
    void                        resetScissors() override;

    void                        captureStateBlock() override;
    void                        applyStateBlock() override;

    void                        setCameraPosition( const GoTvPoint &camera, int screenWidth, int screenHeight, float stereoFactor = 0.0f ) override;

    void                        applyHardwareTransform( const TransformMatrix &matrix ) override;
    void                        restoreHardwareTransform() override;
    bool                        supportsStereo( RENDER_STEREO_MODE mode ) const override { return false; }

    bool                        testRender() override;

    void                        project( float &x, float &y, float &z ) override;

    //=== shaders ===//
    std::string                 getShaderPath( const std::string &filename ) override { return ""; }

    void                        initialiseShaders() override;
    void                        releaseShaders() override;
    bool                        enableShader( ESHADERMETHOD method ) override;
    bool                        isShaderValid( ESHADERMETHOD method ) override;
    void                        disableShader( ESHADERMETHOD method ) override;
    void                        disableGUIShader() override;

    int                         shaderGetPos()  override;
    int                         shaderGetCol()  override;
    int                         shaderGetModel()  override;
    int                         shaderGetCoord0()  override;
    int                         shaderGetCoord1()  override;
    int                         shaderGetUniCol()  override;

    // yuv shader
    virtual void                shaderSetField( ESHADERMETHOD shader, int field )   override;
    virtual void                shaderSetWidth( ESHADERMETHOD shader, int w )   override;
    virtual void                shaderSetHeight( ESHADERMETHOD shader, int h )  override;

    virtual void                shaderSetBlack( ESHADERMETHOD shader, float black ) override;
    virtual void                shaderSetContrast( ESHADERMETHOD shader, float contrast ) override;
    virtual void                shaderSetConvertFullColorRange( ESHADERMETHOD shader, bool convertFullRange ) override;

    virtual int                 shaderGetVertexLoc( ESHADERMETHOD shader ) override;
    virtual int                 shaderGetYcoordLoc( ESHADERMETHOD shader ) override;
    virtual int                 shaderGetUcoordLoc( ESHADERMETHOD shader ) override;
    virtual int                 shaderGetVcoordLoc( ESHADERMETHOD shader ) override;

    virtual void                shaderSetMatrices( ESHADERMETHOD shader, const float *p, const float *m ) override;
    virtual void                shaderSetAlpha( ESHADERMETHOD shader, float alpha ) override;

    virtual void                shaderSetFlags( ESHADERMETHOD shader, unsigned int flags ) override;
    virtual void                shaderSetFormat( ESHADERMETHOD shader, EShaderFormat format ) override;
    virtual void                shaderSourceTexture( ESHADERMETHOD shader, int ytex ) override;
    virtual void                shaderSetStepX( ESHADERMETHOD shader, float stepX ) override;
    virtual void                shaderSetStepY( ESHADERMETHOD shader, float stepY )  override;

    // filter shader
    virtual bool                shaderGetTextureFilter( ESHADERMETHOD shader, int& filter ) override;
    virtual int                 shaderGetcoordLoc( ESHADERMETHOD shader ) override;

    // renderqt
    virtual int                 shaderVertexAttribPointer( ESHADERMETHOD shader, unsigned int index, int size, int type, bool normalized, int stride, const void * pointer ) override;
    virtual void                shaderEnableVertexAttribArray( ESHADERMETHOD shader, int arrayId ) override;
    virtual void                shaderDisableVertexAttribArray( ESHADERMETHOD shader, int arrayId ) override;

    // frame buffers
    virtual void                frameBufferGen( int bufCount, unsigned int* fboId ) override;
    virtual void                frameBufferDelete( int bufCount, unsigned int* fboId ) override;
    virtual void                frameBufferTexture2D( int target, unsigned int texureId )  override;
    virtual void                frameBufferBind( unsigned int fboId ) override;
    virtual bool                frameBufferStatus() override;

    //============================================================================
    //=== end to gui media/render ===//
    //============================================================================



    //============================================================================
    //=== to gui ===//
    //============================================================================

    virtual void				toGuiLog( int logFlags, const char * pMsg ) override;
    virtual void				toGuiAppErr( EAppErr eAppErr, const char* errMsg = "" ) override;
    virtual void				toGuiStatusMessage( const char * errMsg ) override;
	// NOTE: toGuiUserMessage should be called from in gui on gui thread only
    virtual void				toGuiUserMessage( const char * userMsg, ... );

    virtual void				toGuiNetworkState( ENetworkStateType eNetworkState, const char* stateMsg = "" ) override;
    virtual void				toGuiMyRelayStatus( EMyRelayStatus eRelayStatus, const char * msg = "" ) override;
    virtual void				toGuiAnchorStatus( EAnchorTestStatus eAnchorStatus, const char * msg = "" ) override;
    virtual void				toGuiIsPortOpenStatus( EIsPortOpenStatus eIsPortOpenStatus, const char * msg = "" ) override;
    virtual void				toGuiPhoneShakeStatus( EPhoneShakeStatus ePhoneShakeStatus, const char * msg = "" ) override;

    virtual void				toGuiWantMicrophoneRecording( bool wantMicInput ) override;
    virtual void				toGuiWantSpeakerOutput( bool wantSpeakerOutput ) override;
    virtual void				toGuiPlayAudio( int16_t * pu16PcmData, int pcmDataLenInBytes ) override;
    virtual int				    toGuiPlayAudio( EAppModule appModule, int16_t * pu16PcmData, int pcmDataLenInBytes ) override;
    virtual double				toGuiGetAudioDelaySeconds( ) override;
    virtual double				toGuiGetAudioCacheTotalSeconds() override;
    virtual int				    toGuiGetAudioCacheFreeSpace( ) override;

    virtual void				toGuiWantVideoCapture( bool wantVidCapture ) override;
    virtual void				toGuiPlayVideoFrame( VxGUID& onlineId, uint8_t * pu8Jpg, uint32_t u32JpgDataLen, int motion0To100000 ) override;
    virtual int				    toGuiPlayVideoFrame( VxGUID& onlineId, uint8_t * picBuf, uint32_t picBufLen, int picWidth, int picHeight ) override;

    virtual void				toGuiContactOffline( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactOnline( VxNetIdent * netIdent, bool newContact = false ) override;
    virtual void				toGuiContactNearby( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactNotNearby( VxNetIdent * netIdent ) override;

    virtual void				toGuiContactNameChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactDescChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactMyFriendshipChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactHisFriendshipChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiPluginPermissionChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactSearchFlagsChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactConnectionChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactAnythingChange( VxNetIdent * netIdent ) override;
    virtual void				toGuiContactLastSessionTimeChange( VxNetIdent * netIdent ) override;

    virtual void				toGuiUpdateMyIdent( VxNetIdent * netIdent ) override;

	virtual void				toGuiRxedPluginOffer(	VxNetIdent *	netIdent,				// identity of friend
														EPluginType		ePluginType,			// plugin type
														const char *	pOfferMsg,				// offer message
														int				pvUserData,				// plugin defined data
														const char *	pFileName = NULL,		// filename if any
														uint8_t *		fileHashData = 0,
														VxGUID&			lclSessionId = VxGUID::nullVxGUID(),
                                                        VxGUID&			rmtSessionId = VxGUID::nullVxGUID()  ) override;

	virtual void				toGuiRxedOfferReply(	VxNetIdent *	netIdent, 
														EPluginType		ePluginType, 
														int				pvUserData, 
														EOfferResponse	eOfferResponse,
														const char *	pFileName = 0,
														uint8_t *		fileHashData = 0,
														VxGUID&			lclSessionId = VxGUID::nullVxGUID(),
                                                        VxGUID&			rmtSessionId = VxGUID::nullVxGUID() ) override;

	virtual void				toGuiPluginSessionEnded(	VxNetIdent *	netIdent, 
															EPluginType		ePluginType, 
															int				pvUserData, 
															EOfferResponse	eOfferResponse,
                                                            VxGUID&			lclSessionId = VxGUID::nullVxGUID() ) override;

	virtual void				toGuiPluginStatus(	EPluginType		ePluginType,
													int				statusType,
                                                    int				statusValue ) override;

	virtual void				toGuiInstMsg(	VxNetIdent *	netIdent,
												EPluginType		ePluginType,
                                                const char *	pMsg ) override;


	virtual bool				toGuiSetGameValueVar(	EPluginType	    ePluginType, 
														VxGUID&		    onlineId, 
														int32_t			s32VarId, 
                                                        int32_t			s32VarValue ) override;

	virtual bool				toGuiSetGameActionVar(	EPluginType	    ePluginType, 
														VxGUID&		    onlineId, 
														int32_t			s32VarId, 
                                                        int32_t			s32VarValue ) override;

	//=== to gui file ===//
	virtual void				toGuiFileListReply(		VxNetIdent *	netIdent, 
														EPluginType		ePluginType, 
														uint8_t			u8FileType, 
														uint64_t		u64FileLen, 
														const char *	pFileName,
                                                        uint8_t *		fileHashData ) override;

	virtual void				toGuiStartUpload(	VxNetIdent *	netIdent, 
													EPluginType		ePluginType, 
													VxGUID&			lclSessionId, 
													uint8_t			u8FileType, 
													uint64_t		u64FileLen, 
													const char *	pFileName,
                                                    uint8_t *		fileHashData ) override;

	virtual void				toGuiStartDownload(	VxNetIdent *	netIdent, 
													EPluginType		ePluginType, 
													VxGUID&			lclSessionId, 
													uint8_t			u8FileType, 
													uint64_t		u64FileLen, 
													const char *	pFileName,
                                                    uint8_t *		fileHashData ) override;

    virtual void				toGuiFileXferState( VxGUID& lclSession, EXferState eXferState, int param1, int param2 ) override;

    virtual void				toGuiFileDownloadComplete( VxGUID&	lclSessionId, const char * newFileName, EXferError xferError ) override;
    virtual void				toGuiFileUploadComplete( VxGUID& lclSessionId, EXferError xferError ) override;

	virtual void				toGuiFileList(	const char *	fileName, 
												uint64_t		fileLen, 
												uint8_t			fileType, 
												bool			isShared,
												bool			isInLibrary,
                                                uint8_t *		fileHashId = 0 ) override;
	//=== to gui search ===//
    virtual void				toGuiSearchResultSuccess( EScanType eScanType, VxNetIdent * netIdent ) override;
    virtual void				toGuiSearchResultError( EScanType eScanType, VxNetIdent * netIdent, int errCode ) override;
    virtual void				toGuiScanSearchComplete( EScanType eScanType ) override;

    virtual void				toGuiSearchResultProfilePic( VxNetIdent * netIdent, uint8_t * pu8JpgData, uint32_t u32JpgDataLen ) override;
	virtual void				toGuiSearchResultFileSearch(	VxNetIdent *	netIdent, 		
																VxGUID&			lclSessionId, 
																uint8_t			u8FileType, 
																uint64_t		u64FileLen, 
                                                                const char *	pFileName ) override;
	//=== to gui asset ===//
    virtual void				toGuiAssetAdded( AssetInfo * assetInfo ) override;
    virtual void				toGuiSessionHistory( AssetInfo * assetInfo ) override;
    virtual void				toGuiAssetAction( EAssetAction assetAction, VxGUID& assetId, int pos0to100000 ) override;
    virtual void				toGuiMultiSessionAction( EMSessionAction mSessionAction, VxGUID& onlineId, int pos0to100000 ) override;

    //============================================================================
    //=== implementation ===//
    //============================================================================

	virtual void				onFriendAdded( VxNetIdent * poFriend );
	virtual void				onFriendUpdated( VxNetIdent * poFriend );
	virtual void				onFriendRemoved( VxNetIdent * poFriend );

	virtual void				onToGuiRxedPluginOffer( GuiOfferSession * offerSession );
	virtual void				onToGuiRxedOfferReply( GuiOfferSession * offerSession );

	bool						userCanceled( void );

	// returns true if showed activity
	bool 						offerToFriendPluginSession( VxNetIdent * poFriend, EPluginType ePluginType, QWidget * parent = 0 );
	void						offerToFriendViewProfile( VxNetIdent * poFriend );
	void						offerToFriendViewStoryboard( VxNetIdent * poFriend );
	void						offerToFriendViewSharedFiles( VxNetIdent * poFriend );
	void						offerToFriendSendFile( VxNetIdent * poFriend );
	void						offerToFriendChangeFriendship( VxNetIdent * poFriend );
	void						offerToFriendUseAsRelay( VxNetIdent * poFriend );

	void						viewWebServerPage( VxNetIdentBase * netIdent, const char * webPageFileName );

	void						createAccountForUser( std::string& strUserName, VxNetIdent& userAccountIdent, const char * moodMsg );
	std::string					getUserXferDirectoryFromAccountUserName( const char * userName );
	std::string 				getUserSpecificDataDirectoryFromAccountUserName( const char * userName );

	void						refreshFriend( VxGUID& onlineId ); // called to emit signalRefreshFriend

signals:
	void						signalHomeFrameFullSize( bool isFullSize );
	void						signalFinishedLoadingGui( void );
	void						signalFinishedLoadingEngine( void );
	void						signalPlaySound( ESndDef sndDef );
	void						signalLog( int iPluginNum, QString strMsg );
	void						signalAppErr( EAppErr eAppErr, QString errMsg );
	void						signalStatusMsg( QString strMsg );
	void						signalUserMsg( QString strMsg );
	void						signalAnchorStatus( EAnchorTestStatus eAnchorStatus, QString strMsg );
	void						signalIsPortOpenStatus( EIsPortOpenStatus eIsPortOpenStatus, QString strMsg );
	void						signalPhoneShakeStatus( EPhoneShakeStatus ePhoneShakeStatus, QString strMsg );
	void						signalNetworkStateChanged( ENetworkStateType eNetworkState );

	void						signalRefreshFriend( VxGuidQt onlineId ); // emitted if friend has changed
	void						signalAssetViewMsgAction( EAssetAction, VxGuidQt onlineId, int pos0to100000 );
	void						signalMainWindowResized( void ); // emitted if main window is resized'

	void						signalToGuiInstMsg( VxNetIdent * netIdent, EPluginType ePluginType, QString pMsg );
	void						signalRemoveContact( VxNetIdent * netIdent );
	void						signalContactOnline( VxNetIdent * netIdent, bool newContact );
	void						signalContactOffline( VxNetIdent * netIdent );
	void						signalContactNearby( VxNetIdent * netIdent );
	void						signalContactNotNearby( VxNetIdent * netIdent );
	void						signalContactNameChange( VxNetIdent * netIdent );
	void						signalContactDescChange( VxNetIdent * netIdent );
	void						signalContactMyFriendshipChange( VxNetIdent * netIdent );
	void						signalContactHisFriendshipChange( VxNetIdent * netIdent );
	void						signalContactPluginPermissionChange( VxNetIdent * netIdent );
	void						signalContactSearchFlagsChange( VxNetIdent * netIdent );
	void						signalContactLastSessionTimeChange( VxNetIdent * netIdent );

	void						signalUpdateMyIdent( VxNetIdent * netIdent );

	void						signalEnableVideoCapture( bool enableCapture );
	void						signalEnableMicrophoneRecording( bool enableMicInput );
	void						signalEnableSpeakerOutput( bool enableSpeakerOutput );

	void						signalSetRelayHelpButtonVisibility( bool isVisible );
	void						signalMultiSessionAction( VxGuidQt idPro, EMSessionAction mSessionAction, int pos0to100000 );

	void						signalToGuiPluginStatus( EPluginType ePluginType, int statusType, int statusValue );

protected slots:

	void						slotPlaySound( ESndDef sndDef );
	void						slotStatusMsg( QString strMsg );
	void						slotAppErr( EAppErr eAppErr, QString errMsg );
	void						slotEnableVideoCapture( bool enableCapture );
	void						slotEnableMicrophoneRecording( bool enableMicInput );
	void						slotEnableSpeakerOutput( bool enableSpeakerOutput );

	void						slotOnNotifyIconFlashTimeout( bool bWhite );

	void						slotToGuiInstMsg( VxNetIdent * netIdent, EPluginType ePluginType, QString pMsg );

	void						slotSearchButtonClick( void );
	void						slotFileMenuButtonClick( void );
	void						slotServerButtonClick( void );
	void						slotOptionsButtonClick( void );
	void						slotNotifyButtonClick( void );
	void						slotRefreshListButtonClick( void );

	void						slotListViewTypeChanged( int viewSelectedIdx );

	void						slotRelayHelpButtonClicked( void );
	void						slotSetRelayHelpButtonVisibility( bool isVisible );
	void						slotNetworkStateChanged( ENetworkStateType eNetworkState );

	void						onMenuFileSelected( int iMenuId, QWidget * popupMenu );
	void						onMenuSearchSelected( int iMenuId, QWidget * popupMenu );
	void						onMenuServerSelected( int iMenuId, QWidget * popupMenu );
	void						onMenuOptionsSelected( int iMenuId, QWidget * popupMenu );
	void						onMenuNotifySelected( int iMenuId, QWidget * popupMenu );

	void						onVidCapTimer( void );
	void						onIdleTimer( void );
	void						onOncePerSecond( void );

	void						onEditPermissionsSelected( int iMenuId, QWidget * popupMenu );
	void						slotRemoveContact( VxNetIdent * netIdent );
	void						slotContactOnline( VxNetIdent * netIdent, bool newContact );
	void						slotContactOffline( VxNetIdent * netIdent );
	void						slotContactNearby( VxNetIdent * netIdent );
	void						onContactNotNearby( VxNetIdent * netIdent );
	void						onContactNameChange( VxNetIdent * netIdent );
	void						onContactDescChange( VxNetIdent * netIdent );
	void						onContactMyFriendshipChange( VxNetIdent * netIdent );
	void						onContactHisFriendshipChange( VxNetIdent * netIdent );
	void						onContactPluginPermissionChange( VxNetIdent * netIdent );
	void						onContactSearchFlagsChange( VxNetIdent * netIdent );
	void						onContactLastSessionTimeChange( VxNetIdent * netIdent );

	void						onEngineStatusMsg( QString );

	void						onUpdateMyIdent( VxNetIdent * poMyIdent );

private slots:
	void						slotMainWindowResized( void );

	void						slotStartLoadingFromThread( void );
	void						slotFinishedLoadingGui( void );
	void						slotFinishedLoadingEngine( void );

private:
	void						restoreWindowPosition( void );

	bool						loadLastUserAccount( void );
	void						showUserNameInTitle();
	void						sendAppSettingsToEngine( void );
	void						startNetworkMonitor( void );
	bool						shouldShowFriend( VxNetIdent * poFriend );

	void						removePluginSessionOffer( EPluginType ePluginType, VxNetIdent * poFriend );

	void						addPermissionMenuEntry( PopupMenu *		poPopupMenu, 
														EPluginType		ePluginType, 
														EMyIcons		eIconType, 
														const char *	pText );
	void						connectSignals( void );
	void						checkForIniSettings( VxNetIdent * netIdent, std::string& strNetworkName );
	void						updateFriendList( VxNetIdent * netIdent, bool sessionTimeChange = false );

	void						toGuiActivityClientsLock( void );
	void						toGuiActivityClientsUnlock( void );
	void						clearToGuiActivityClientList( void );

	void						toGuiFileXferClientsLock( void );
	void						toGuiFileXferClientsUnlock( void );
	void						clearFileXferClientList( void );

	void						toGuiHardwareCtrlLock( void );
	void						toGuiHardwareCtrlUnlock( void );
	void						clearHardwareCtrlList( void );

	//=== vars ===//
	QApplication&				m_QApp;
	EDefaultAppMode				m_AppDefaultMode;
	AppGlobals					m_AppGlobals;
	AppSettings&				m_AppSettings;
	VxDataHelper&				m_DataHelper;
    IGoTv&                      m_GoTv;
	VxPeerMgr&					m_VxPeerMgr;
	QString						m_AppTitle;
	QString						m_AppShortName;

	MyIcons&					m_MyIcons;
	VxAppTheme&					m_AppTheme;
	VxAppStyle&					m_AppStyle;
    VxAppDisplay				m_AppDisplay;
	VxTilePositioner&			m_TilePositioner;

	P2PEngine&					m_Engine; // engine before sound so can initialize engine sound interface
	MySndMgr&					m_MySndMgr;
	OffersMgr&					m_OffersMgr;

	HomeWindow					m_HomePage;

	ActivityCreateProfile *		m_CreateProfileDlg;
	ActivityDownloads *			m_Downloads;
	ActivityUploads *			m_Uploads;
	ActivityDebugSettings*		m_DebugSettingsDlg;
	ActivityShowHelp *			m_ActivityShowHelpDlg;

	std::string					m_strAccountUserName;

	IVxVidCap *					m_VidCap;
	QTimer *					m_VidCapTimer;
	QTimer *					m_IdleTimer;
	QTimer *					m_OncePerSecondTimer;
	EFriendViewType				m_eLastSelectedWhichContactsToView; // last selection of which friends to view

	bool						m_bUserCanceledCreateProfile;
	VxMutex						m_AppMutex;
	std::vector<QString>		m_DebugLogQue;
	std::vector<QString>		m_AppErrLogQue;
	ENetworkStateType			m_LastNetworkState;

private:
	void						registerMetaData();
	void						doAccountStartup( void );

private:
	AppCommon( const AppCommon& rhs ) = delete;

	uint32_t					m_CamSourceId;
	uint32_t					m_CamCaptureRotation;
	VxMutex						m_ToGuiActivityClientMutex;
	std::vector<ToGuiActivityClient>	m_ToGuiActivityClientList;

	VxMutex						m_ToGuiFileXferClientMutex;
	std::vector<ToGuiFileXferClient>	m_ToGuiFileXferClientList;
	
	VxMutex						m_ToGuiHardwareCtrlMutex;
	std::vector<ToGuiHardwareCtrlClient> m_ToGuiHardwareCtrlList;

	bool						m_LibraryActivityActive;
	bool						m_VidCaptureEnabled;
	bool						m_MicrophoneHardwareEnabled;
	bool						m_SpeakerHardwareEnabled;
	QVector<EPluginType>		m_VisiblePluginsList;
	AppletMgr&					m_AppletMgr;
    bool                        m_AppCommonInitialized;
    bool                        m_LoginBegin;
    bool                        m_LoginComplete;

    KodiThread *                m_KodiThread;
    AudioOutQt                  m_AudioOut;
};

AppCommon& CreateAppInstance( IGoTv& gotv, QApplication* myApp, AppSettings& appSettings );

AppCommon& GetAppInstance( void );

void DestroyAppInstance( );
