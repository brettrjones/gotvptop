
package com.p2pgotv.gotvstation;

import android.net.Uri;
import android.util.Log;

public class VxNetIdent implements Comparable<VxNetIdent>
{
	private static final String LOG_TAG = "VxNetIdent:";
	
	//=== vars ===//
	public long					m_u64RelayIdLoPart 		= 0;
	public long					m_u64RelayIdHiPart 		= 0;
	public int					m_RelayPort 			= 0;	// proxy incoming connection port
	public String				m_as8RelayIPv4 			= "0.0.0.0";
	public String				m_as8RelayIPv6 			= "0";	
	public int					m_u32RelayIp 			= 0;		// proxy ip address

	public byte					m_u8RelayFlags 			= 0;
	
	public long					m_u64IdHiPart 			= 0;
	public long					m_u64IdLoPart 			= 0;
	public int					m_OnlinePort 			= 0;	// users incoming connection port
	public String				m_as8LocalIPv4 			= "0.0.0.0";
	public String				m_as8OnlineIPv4 		= "0.0.0.0";
	public String				m_as8OnlineIPv6 		= "0";	
	
	static final byte 			ONLINE_STATUS_CONNECTED 			= 0x01; 
	static final byte 			ONLINE_STATUS_NEARBY 				= 0x02;
	static final byte 			ONLINE_STATUS_FROM_SEARCH_PKT		= 0x04; // is from search list.. never connected to
	static final byte 			ONLINE_STATUS_HAS_TEXT_OFFERS 		= 0x08;
	
	public byte					m_u8OnlineStatusFlags 				= 0;

	public String				m_as8OnlineName 					= "";
	public String				m_as8OnlineDesc 					= "";				// users online description (max 31 chars)
	public byte					m_u8FriendMatch 					= 0;
	public byte					m_u8SearchFlags 					= 0;
	public byte					m_u8FileTypeFlags 					= 0;
	public byte[]			    m_au8Permissions					= new byte[24];
	
	public int					m_u32TruthCnt						= 0;							// 
	public int					m_u32DareCnt						= 0;							// 
	public int					m_RejectedTruthCnt					= 0;						// 
	public int					m_RejectedDareCnt					= 0;						// 
	public long					m_s64LastSessionTime				= 0;						// 
	
	static final byte			RC_PROXY_FLAG_REQUIRES_PROXY		= 0x01;	// user requires relay to connect to him
	static final byte			RC_PROXY_FLAG_HAS_PROXY				= 0x02;	// user has at least one relay that may be used to connect to him
	static final byte			RC_PROXY_FLAG_IS_MY_PREFERED_PROXY	= 0x04;	// user is a relay for others
	static final byte			RC_PROXY_FLAG_USE_ENCRYPTION		= 0x08;	// user wants encrypted traffic
		
	static final byte			RC_FLAG_HAS_IMAGE_FILES				= 0x01;	// user has shared image files
	static final byte			RC_FLAG_HAS_AUDIO_FILES				= 0x02;	// user has shared audio files
	static final byte			RC_FLAG_HAS_VIDEO_FILES				= 0x04;	// user has shared video files
	static final byte			RC_FLAG_HAS_DOC_FILES				= 0x08;	
	static final byte			RC_FLAG_HAS_OTHER_FILES				= 0x10;	
	static final byte			RC_FLAG_HAS_FOLDER					= 0x20;

	static final byte			RC_FLAG_HAS_PROFILE_PIC				= 0x01;	// user has set his profile picture
	static final byte			RC_FLAG_HAS_SHARED_WEBCAM			= 0x02;	// user has shared web cam
	static final byte			RC_FLAG_ENABLED_SHARED_FILES		= 0x04;	// user has shared files enabled

	//! NOTE: also used as permission type
	static public enum EFriendState
	{
		eFriendStateIgnore,			// unknown or disabled or ignore
		eFriendStateAnonymous,		// anonymous user
		eFriendStateGuest,			// guest user
		eFriendStateFriend,			// friend user
		eFriendStateSuperUser		// super user rights
	};
	
	static final EFriendState[] 		Friendships 	= { EFriendState.eFriendStateIgnore, EFriendState.eFriendStateAnonymous, EFriendState.eFriendStateGuest, EFriendState.eFriendStateFriend };
	
	//========================================================================
	boolean isRelayValid()
	{
		if( ( 0 ==  m_u64RelayIdLoPart ) || 
			( 0 ==  m_u64RelayIdHiPart ) ||
			( 0 == m_RelayPort ))
		{
			return false; 
		}
		
		return true;
	}
	
	//========================================================================
	String getMyExternalIp()
	{
		return m_as8OnlineIPv4;
	}

	//========================================================================
	void setLocalIPv4( String localIPv4 )
	{
		if( ( null == localIPv4 ) || ( 0 == localIPv4.length() ) )
		{
			m_as8LocalIPv4 = "0.0.0.0";
		}
		else
		{
			m_as8LocalIPv4 = localIPv4;
		}
	}
	
	//========================================================================
	String getLocalIPv4()
	{
		return m_as8LocalIPv4;
	}

	//========================================================================
	void setOnlineIPv4( String onlineIPv4 )
	{
		if( ( null == onlineIPv4 ) || ( 0 == onlineIPv4.length() ) )
		{
			m_as8OnlineIPv4 = "0.0.0.0";
		}
		else
		{
			m_as8OnlineIPv4 = onlineIPv4;
		}
	}
	
	//========================================================================
	String getOnlineIPv4()
	{
		return m_as8OnlineIPv4;
	}
	
	//========================================================================
	void setRelayIPv4( String relayIPv4 )
	{
		if( ( null == relayIPv4 ) || ( 0 == relayIPv4.length() ) )
		{
			m_as8RelayIPv4 = "0.0.0.0";
		}
		else
		{
			m_as8RelayIPv4 = relayIPv4;
		}
	}
	
	//========================================================================
	String getRelayIPv4()
	{
		return m_as8RelayIPv4;
	}

	//========================================================================
	void setOnlineIPv6( String onlineIPv6 )
	{
		if( ( null == onlineIPv6 ) || ( 0 == onlineIPv6.length() ) )
		{
			m_as8OnlineIPv6 = "0.0.0.0";
		}
		else
		{
			m_as8OnlineIPv6 = onlineIPv6;
		}
	}
	
	//========================================================================
	String getOnlineIPv6()
	{
		return m_as8OnlineIPv6;
	}
	
	//========================================================================
	void setRelayIPv6( String relayIPv6 )
	{
		if( ( null == relayIPv6 ) || ( 0 == relayIPv6.length() ) )
		{
			m_as8RelayIPv6 = "0.0.0.0";
		}
		else
		{
			m_as8RelayIPv6 = relayIPv6;
		}
	}
	
	//========================================================================
	String getRelayIPv6()
	{
		return m_as8RelayIPv6;
	}

	//========================================================================
	public void setDefaultPermissions()
	{
		for( int i = 0; i < m_au8Permissions.length; i++ )
		{
			m_au8Permissions[i] = 0;
		}

		setPermission( m_au8Permissions, Constants.ePluginTypeAdmin, 		Constants.eFriendStateAdministrator );	
		setPermission( m_au8Permissions, Constants.ePluginTypeRelay, 		Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeWebServer, 	Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeCamServer, 	Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeMultiSession, Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeVoicePhone, 	Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeVideoPhone, 	Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeTruthOrDare, 	Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeFileOffer, 	Constants.eFriendStateFriend );	
		setPermission( m_au8Permissions, Constants.ePluginTypeFileServer, 	Constants.eFriendStateAnonymous );	
		setPermission( m_au8Permissions, Constants.ePluginTypeStoryBoard, 	Constants.eFriendStateAnonymous );	
	}
	
	//========================================================================
	public void	setPluginPermission( int ePluginType, int eFriendState ) 
	{ 
		setPermission( m_au8Permissions, ePluginType, eFriendState );
		NativeTxTo.fromGuiSetPluginPermission( ePluginType, eFriendState );
	}
	
	//========================================================================
	static private void setPermission( byte[] au8Permissions, int ePluginType, int eFriendState )
	{
		if(( ePluginType > 0 ) && ( ePluginType < Constants.eMaxPluginType ) )
		{
			int pluginNum = (int)(ePluginType - 1);
			byte byteWithPerm = au8Permissions[ pluginNum >> 1 ];
			int byteShift = (0 != (pluginNum & 0x01)) ? 4 : 0;
			if( 0 != byteShift )
			{
				byteWithPerm &= 0x0f;
				byteWithPerm |= eFriendState << byteShift;
			}
			else
			{
				byteWithPerm &= 0xf0;
				byteWithPerm |= eFriendState;
			}

			au8Permissions[ pluginNum >> 1 ] = byteWithPerm;
		}
	}

	//========================================================================
	public int getPluginPermission( int ePluginType ) 
	{ 
		if(( ePluginType > 0 ) && ( ePluginType < Constants.eMaxPluginType ) )
		{
			int pluginNum = (int)(ePluginType - 1);
			byte byteWithPerm = m_au8Permissions[ pluginNum >> 1 ];
			int byteShift = (0 != (pluginNum & 0x01)) ? 4 : 0;

			return  (int)( ( byteWithPerm >> byteShift ) & 0xf ); 
		}
		
		return Constants.eFriendStateIgnore;
	}

	//========================================================================
	void setTruthCount( int u32TruthCnt )
	{
		m_u32TruthCnt = u32TruthCnt;
	}
	
	//========================================================================
	int getTruthCount()
	{
		return m_u32TruthCnt;
	}

	//========================================================================
	void setDareCount( int u32DareCnt )
	{
		m_u32DareCnt = u32DareCnt;
	}
	
	//========================================================================
	int	getDareCount()
	{
		return m_u32DareCnt;
	}

	//========================================================================
	void setRejectedTruthCount( int u32RejectedCnt )
	{
		m_RejectedTruthCnt = u32RejectedCnt;
	}
	
	//========================================================================
	int	getRejectedTruthCount()
	{
		return m_RejectedTruthCnt;
	}

	//========================================================================
	void setRejectedDareCount( int u32RejectedCnt )
	{
		m_RejectedDareCnt = u32RejectedCnt;
	}
	
	//========================================================================
	int	getRejectedDareCount()
	{
		return m_RejectedDareCnt;
	}
	
	//========================================================================
	String describeMyId()
	{
		String strId = " 0x" + VxParseUtil.longToHexString(m_u64IdHiPart) + " 0x" + VxParseUtil.longToHexString(m_u64IdLoPart);
		return strId;
	}
	
	//========================================================================
	String describeRelayId()
	{
		String strId = " 0x" + VxParseUtil.longToHexString(m_u64RelayIdHiPart) + " 0x" + VxParseUtil.longToHexString(m_u64RelayIdLoPart);
		return strId;
	}
	
	//========================================================================
	String getMyIdAsString()
	{
		String strId = VxParseUtil.longToHexString( m_u64IdHiPart ) + VxParseUtil.longToHexString( m_u64IdLoPart );
		return strId;
	}
		
	//========================================================================
	VxGUID getOnlineId()
	{
		return new VxGUID( m_u64IdHiPart, m_u64IdLoPart );
	}
	
	//========================================================================
	public VxGUID getMyOnlineId()
	{
		return new VxGUID( m_u64IdHiPart, m_u64IdLoPart );
	}
	
	//========================================================================
	public boolean isSameId( VxNetIdent friend )
	{
		boolean isSame = false;
		if( (friend.m_u64IdLoPart == m_u64IdLoPart) &&
			(friend.m_u64IdHiPart == m_u64IdHiPart)	)
		{
			isSame = true;
		}	
		
		return isSame;
	}
	
	//========================================================================
	boolean isValid()
	{
		if( 0 ==  m_as8OnlineName.length() )
		{
			return false; 
		}
		
		if( ( 0 ==  m_u64IdLoPart ) || 
			( 0 ==  m_u64IdHiPart ) )
		{
			return false; 
		}
		
		return true;
	}

	//========================================================================
	void debugDumpIdent()
	{
		 Log.d( "FriendBase", "Ident " +
				getOnlineName() +
				" id " + 
				describeMyId() +
				" my friendship " +
				Constants.describeFriendState(getMyFriendshipToHim()) +
				" his friendship " + 
				Constants.describeFriendState(getHisFriendshipToMe()) +
				"permissions 0x" +
				VxParseUtil.byteArrayToHexString( m_au8Permissions ) +
				"\n" 
				);
		 Log.d( "FriendBase", 
				" search 0x" +
						VxParseUtil.byteToHexString( m_u8SearchFlags ) +
				" file types 0x" +
				VxParseUtil.byteToHexString( m_u8FileTypeFlags ) +
				" online status 0x" +
				VxParseUtil.byteToHexString( m_u8OnlineStatusFlags ) +
				" relay flags 0x" +
				VxParseUtil.byteToHexString( m_u8RelayFlags ) +
				" ip_v4 " + m_as8OnlineIPv4 +
				" ip_v6 " + m_as8OnlineIPv6 +
				" port " + 
				getOnlinePort() +
				" relay ipv4 " 	+ m_as8RelayIPv4 +
				" relay ipv6 " 	+ m_as8RelayIPv6 +
				" relay port " +
				getRelayPort() +
				"\n"
				);	
	}

	//========================================================================
	String getOnlineName()										{ return m_as8OnlineName; }
	String getOnlineDescription()								{ return m_as8OnlineDesc; }
	
	//========================================================================
	String getTruthsAndDaresDescription()
	{
		String truthsText = "Truths: " + getTruthCount() + " Dares: " + getDareCount();
		return truthsText;
	}	
	
	//========================================================================
	void setOnlinePort( int port )
	{	
		m_OnlinePort = ( port & 0xFFFF );
	}
	
	//========================================================================
	int getOnlinePort()
	{	
		return ( m_OnlinePort & 0xFFFF );
	}
	
	//========================================================================
	void setRelayPort( int port )
	{	
		m_RelayPort = ( port & 0xFFFF );
	}

	//========================================================================
	int getRelayPort()
	{	
		return ( m_RelayPort & 0xFFFF );
	}
	
	//========================================================================
	//! online status
	//========================================================================	
	void			setIsOnline( boolean bIsOnline )	{ if( bIsOnline ) m_u8OnlineStatusFlags |= ONLINE_STATUS_CONNECTED; else m_u8OnlineStatusFlags &= (~ONLINE_STATUS_CONNECTED); }
	boolean			isOnline()							{ if(0 != (m_u8OnlineStatusFlags & ONLINE_STATUS_CONNECTED)) return true; return false; }
	
	void			setIsNearby( boolean bIsNearby )	{ if( bIsNearby ) m_u8OnlineStatusFlags |= ONLINE_STATUS_NEARBY; else m_u8OnlineStatusFlags &= (~ONLINE_STATUS_NEARBY); }
	boolean			isNearby()							{ if(0 != (m_u8OnlineStatusFlags & ONLINE_STATUS_NEARBY)) return true; return false; }
	
	void			setHasTextOffers( boolean hasOffers )	{ if( hasOffers ) m_u8OnlineStatusFlags |= ONLINE_STATUS_HAS_TEXT_OFFERS; else m_u8OnlineStatusFlags &= (~ONLINE_STATUS_HAS_TEXT_OFFERS); }
	boolean			getHasTextOffers()						{ if(0 != (m_u8OnlineStatusFlags & ONLINE_STATUS_HAS_TEXT_OFFERS)) return true; return false; }
	

	//========================================================================
	//! relay
	//========================================================================
	//! return true if has any relay flags
	boolean	hasRelayFlags()						{ if(0 == m_u8RelayFlags) return false; return true; }
	
	//========================================================================
	//! return true if has a relay
	boolean	hasRelay()							{ if( 0 == (RC_PROXY_FLAG_HAS_PROXY & m_u8RelayFlags)) return false; return true; }
	
	//========================================================================
	void	setHasRelay( boolean bHasRelay )				
	{
		if( bHasRelay )
			m_u8RelayFlags |= RC_PROXY_FLAG_HAS_PROXY;
		else
			m_u8RelayFlags &= ~RC_PROXY_FLAG_HAS_PROXY;
	}
	
	//========================================================================
	boolean	requiresRelay()						{ if( 0 == (RC_PROXY_FLAG_REQUIRES_PROXY & m_u8RelayFlags)) return false; return true; }
	
	//========================================================================
	//! set requires relay
	void	setRequiresRelay( boolean bRequiresRelay )				
	{
		if( bRequiresRelay )
			m_u8RelayFlags |= RC_PROXY_FLAG_REQUIRES_PROXY;
		else
			m_u8RelayFlags &= ~RC_PROXY_FLAG_REQUIRES_PROXY;
	}
	
	//========================================================================
	//! return true if has any shared files
	boolean	isMyPreferedRelay()					{ if( 0 == (RC_PROXY_FLAG_IS_MY_PREFERED_PROXY & m_u8RelayFlags)) return false; return true; }
	
	//========================================================================
	//! set requires relay
	void	setIsMyPreferedRelay( boolean bRequiresRelay )				
	{
		if( bRequiresRelay )
			m_u8RelayFlags |= RC_PROXY_FLAG_IS_MY_PREFERED_PROXY;
		else
			m_u8RelayFlags &= ~RC_PROXY_FLAG_IS_MY_PREFERED_PROXY;
	}

	//========================================================================
	//! friend flags
	//========================================================================
	//! get permission level I gave to him
	int				getMyFriendshipToHim()								{ return m_u8FriendMatch & 0x0f; }
	int				getHisFriendshipToMe()								{ return ((m_u8FriendMatch >> 4) & 0x0f); }

	//! get permission level I gave to him
	byte			getMyFriendshipToHimFlags()							{ return (byte)(m_u8FriendMatch & 0x0f); }
	//! set permission level I gave to him
	void			setMyFriendshipToHimFlags( byte u8Flags )			{ m_u8FriendMatch = (byte)(m_u8FriendMatch & 0xf0); m_u8FriendMatch = (byte) (m_u8FriendMatch | (byte)(u8Flags & 0x0f )); }
	//! get permission level he has given to me
	byte			getHisFriendshipToMeFlags()							{ return (byte)((m_u8FriendMatch >> 4) & 0x0f); }
	//! set permission level he has given to me
	void			setHisFriendshipToMeFlags( byte u8Flags )			{ m_u8FriendMatch = (byte)((m_u8FriendMatch & 0x0f) | (((u8Flags & 0x0f) << 4) ) ); }
	//! return true if is ignored
	boolean			isIgnored()											{ return Constants.PERMISSION_IGNORE == getMyFriendshipToHimFlags(); }
	//! return true if is Anonymous
	boolean			isAnonymous()										{ return Constants.PERMISSION_ANONYMOUS == getMyFriendshipToHimFlags(); }
	//! return true if is Guest
	boolean			isGuest()											{ return Constants.PERMISSION_GUEST == getMyFriendshipToHimFlags(); }
	//! return true if is Friend
	boolean			isFriend()											{ return Constants.PERMISSION_FRIEND == getMyFriendshipToHimFlags(); }
	//! return true if is Administrator
	boolean			isAdministrator()									{ return Constants.PERMISSION_ADMIN == getMyFriendshipToHimFlags(); }
	
	//! set my permissions to him as ignored
	void			makeIgnored()										{ setMyFriendshipToHimFlags( Constants.PERMISSION_IGNORE ); }
	//! set my permissions to him as Anonymous
	void			makeAnonymous()										{ setMyFriendshipToHimFlags( Constants.PERMISSION_ANONYMOUS ); }
	//! set my permissions to him as Guest
	void			makeGuest()											{ setMyFriendshipToHimFlags( Constants.PERMISSION_GUEST ); }
	//! set my permissions to him as Friend
	void			makeFriend()										{ setMyFriendshipToHimFlags( Constants.PERMISSION_FRIEND ); }
	//! set my permissions to him as Administrator
	void			makeAdministrator()									{ setMyFriendshipToHimFlags( Constants.PERMISSION_ADMIN ); }
	
	//========================================================================
	//! describe friend state
	String 			describeFriendState( int iFriendship )
	{
		switch( iFriendship )
		{
		case Constants.eFriendStateAnonymous:		// anonymous user
			return "Anonymous ";
		case Constants.eFriendStateGuest:			// guest user
			return "Guest ";
		case Constants.eFriendStateFriend:			// friend user
			return "Friend ";
		case Constants.eFriendStateAdministrator:	// administrator
			return "Administrator ";
		default:
			return "Ignore ";
		}
	}

	//========================================================================
	//! search flags
	//========================================================================
	//! return true if has any shared files
	boolean			hasSharedFiles()									{ return ( 0 != m_u8FileTypeFlags ); }
	//! return true if user has set profile picture
	int				hasProfilePicture()									{ return ( RC_FLAG_HAS_PROFILE_PIC & m_u8SearchFlags ); }
	//! set has profile picture
	void			setHasProfilePicture( boolean bHasPicture )				
	{
		if( bHasPicture )
			m_u8SearchFlags |= RC_FLAG_HAS_PROFILE_PIC;
		else
			m_u8SearchFlags &= ~RC_FLAG_HAS_PROFILE_PIC;
	}
	
	//========================================================================
	//! return true if user has shared his web cam
	boolean	hasSharedWebCam()					
	{ 
		if( 0 == (RC_FLAG_HAS_SHARED_WEBCAM & m_u8SearchFlags)) 
			return false; 
		return true; 
	}
	
	//========================================================================
	//! set has audio files
	void	setHasSharedWebCam( boolean bHasWebCam )				
	{
		if( bHasWebCam )
			m_u8SearchFlags |= RC_FLAG_HAS_SHARED_WEBCAM;
		else
			m_u8SearchFlags &= ~RC_FLAG_HAS_SHARED_WEBCAM;
	}
	
	//========================================================================	
	boolean isAccessAllowed( int ePluginType )
	{
		return (Constants.ePluginAccessOk == getPluginAccessState(ePluginType));
	}
	
	//========================================================================		
	int	getPluginAccessState( int ePluginType )
	{
		return getPluginAccessState( ePluginType, getHisFriendshipToMe() );
	}
	
	//========================================================================
	int	getPluginAccessState( int ePluginType, int eHisPermissionToMe )
	{
		if( Constants.eFriendStateIgnore == eHisPermissionToMe )
		{
			return Constants.ePluginAccessIgnored;
		}
		
		int ePermissionLevel = getPluginPermission(ePluginType);
		if( Constants.eFriendStateIgnore == ePermissionLevel )
		{
			return Constants.ePluginAccessDisabled;
		}
		
		if( ePermissionLevel > eHisPermissionToMe )
		{
			return Constants.ePluginAccessLocked;
		}
		
		if( ( Constants.ePluginTypeFileServer == ePluginType ) 
			&& ( false == hasSharedFiles() ) )
		{
			// no files shared
			return Constants.ePluginAccessInactive;
		}
		
		if( (Constants.ePluginTypeCamServer == ePluginType) 
			&& ( false == hasSharedWebCam() ) )
		{
			// no shared web cam
			return Constants.ePluginAccessInactive;
		}
		
		int accessState = Constants.ePluginAccessOk;
		if( ( Constants.ePluginTypeWebServer == ePluginType )
				|| ( Constants.ePluginTypeStoryBoard == ePluginType )
				|| ( Constants.ePluginTypeRelay == ePluginType ) )
		{
			if( false == isOnline() )
			{
				accessState = Constants.ePluginAccessRequiresOnline;
			}

			if( requiresRelay() )
			{
				accessState = Constants.ePluginAccessRequiresDirectConnect;
			}
		}
		else if( Constants.ePluginTypeMultiSession != ePluginType )
		{
			if( false == isOnline() )
			{
				accessState = Constants.ePluginAccessRequiresOnline;
			}
		}

		return accessState;
	}

	//========================================================================
	boolean 		isPluginEnabled( int ePlugin )					
	{ 
		return ( false == (Constants.eFriendStateIgnore == getPluginPermission(ePlugin))); 
	}	
	
	//========================================================================
	String 			describePluginAction( int ePluginType, int ePluginAccess )
	{
		String strAction = "";
		switch( ePluginType )
		{
		case Constants.ePluginTypeRelay:	// relay plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				if( isMyPreferedRelay() )
				{
					strAction = "Is my preferred relay";
				}
				else
				{
					strAction = "Can be my preferred relay";
				}
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Relay Requires ";
				strAction += describeFriendState(  getPluginPermission(Constants.ePluginTypeRelay) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Relay is disabled";
				break;
			case Constants.ePluginAccessInactive:		
				strAction = "Relay is inactive or busy";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Relay unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Relay is busy with other clients";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Relay provider must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Relay provider is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeWebServer:	// web server plugin ( for profile web page )
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "View Contact's About Me Web Page";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "About Me Web Page Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeWebServer ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "About Me Web Page is disabled";
				break;
			case Constants.ePluginAccessInactive:		// plugin inactive
				strAction = "About Me Web Page is inactive";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "About Me Web Page unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "About Me Web Page is busy with other clients";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "About Me Web Page provider must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "About Me Web Page provider is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeStoryBoard:		// web server plugin ( for story board web page )
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "View Contact's Story Board";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "View Story Board Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeStoryBoard ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Story Board is disabled";
				break;
			case Constants.ePluginAccessInactive:		// plugin inactive
				strAction = "Story Board is inactive";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Story Board unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Story Board Web Page is busy with other clients";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Story Board Web Page provider must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Story Board Web Page provider is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeFileOffer:	// file offer plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "Send A File";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Send A File Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeFileOffer ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessInactive:		// no shared files
				strAction = "Send file inactive";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled 
				strAction = "Send file is disabled";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Send file unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Send file is busy with other clients";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Send file contact must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Send file contact is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeFileServer:	// file share plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "View Shared Files";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Shared Files Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeFileServer ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessInactive:		// no shared files
				strAction = "No Shared Files";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled 
				strAction = "Shared Files is disabled";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Shared Files unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Shared Files is busy with other clients";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Shared Files provider must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Shared Files provider is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeCamServer:	// web cam broadcast plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "View Shared Web Cam";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Shared Web Cam Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeCamServer ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Shared Web Cam is disabled";
				break;
			case Constants.ePluginAccessInactive:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Shared Web Cam is not active";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Shared Web Cam unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Shared Web Cam is busy with other clients";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Shared Web Cam provider must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Shared Web Cam provider is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeMultiSession:	// chat message p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				if( isOnline() )
				{
					strAction = "Offer Text Chat Session";
				}
				else
				{
					strAction = "View Last Text Chat Session";
				}
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Text Chat Session Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeMultiSession ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Text Chat Session is disabled";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Text Chat Session unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Text Chat is busy with other contacts";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Text Chat contact must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Text Chat contact is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeVoicePhone:	// VOIP p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "Offer Voice Phone (VOIP)";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Voice Phone Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeVoicePhone ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Voice Phone is disabled";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Voice Phone unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Voice Phone is busy with other contacts";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Voice Phone contact must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Voice Phone contact is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeVideoPhone:
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "Offer Video Chat";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Video Chat Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeVideoPhone ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Video Chat is disabled";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Video Chat unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Video Chat is busy with other contacts";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Video Chat contact must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Video Chat contact is not online";
				break;
			}
			
			break;
			
		case Constants.ePluginTypeTruthOrDare:	// Web Cam Truth Or Dare game p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:			// plugin access allowed
				strAction = "Offer To Play Truth Or Dare";
				break;
			case Constants.ePluginAccessLocked:		// insufficient Friend permission level
				strAction = "Truth Or Dare Requires ";
				strAction += describeFriendState( getPluginPermission( Constants.ePluginTypeTruthOrDare ) );
				strAction += " permission";
				break;
			case Constants.ePluginAccessDisabled:		// plugin disabled or no files shared or no web cam broadcast
				strAction = "Truth Or Dare is disabled";
				break;
			case Constants.ePluginAccessIgnored:		// access denied because you are being ignored
				strAction = "Truth Or Dare unavailable due to ignore status";
				break;
			case Constants.ePluginAccessBusy:					// sufficient permission but cannot accept any more sessions
				strAction = "Truth Or Dare is busy with other contacts";
				break;
			case Constants.ePluginAccessRequiresDirectConnect:	// plugin requires direct connection
				strAction = "Truth Or Dare contact must have direct connection";
				break;
			case Constants.ePluginAccessRequiresOnline:			// plugin requires user to be online
				strAction = "Truth Or Dare contact is not online";
				break;
			}
			
			break;
		}
		
		return strAction;
	}
	
	//========================================================================
	Uri 	getProfileUri( String myExternIP )
	{	
		String 	userWebUrl = getUserWebServerUri( myExternIP );
		userWebUrl += "index.htm";
		return Uri.parse( userWebUrl );
	}
	
	//========================================================================
	Uri 	getStoryboardUri( String myExternIP )
	{	
		String 	userWebUrl = getUserWebServerUri( myExternIP );
		userWebUrl += "story_board.htm";
		return Uri.parse( userWebUrl );
	}
	
	//========================================================================
	String 	getUserWebServerUri( String myExternIP )
	{
		int onlinePort = 0;
		String ipAddr = "";
		if( hasRelay() && requiresRelay() )
		{
			onlinePort = getRelayPort();
			ipAddr = m_as8RelayIPv4;
		}
		else
		{
			onlinePort = getOnlinePort();
			ipAddr = m_as8OnlineIPv4;
		}
		
		if( 0 == ipAddr.compareTo( myExternIP )  )
		{
			ipAddr = m_as8LocalIPv4;			
		}
		
		if( onlinePort < 0 )
		{
			// port is really a unsigned short.. but has rolled over
			onlinePort = 65536 + onlinePort;
		}
		
		String strUrl = "http://" + ipAddr + ":" + onlinePort + "/" + getMyIdAsString() + "/";
		Log.i( LOG_TAG, strUrl );
		return strUrl;
	}


	//============================================================================
	boolean isHisAccessAllowedFromMe( int ePluginType )
	{
		return ( Constants.ePluginAccessOk == getPluginAccessState( ePluginType, getMyFriendshipToHim() ) );
	}

	//============================================================================
	boolean isMyAccessAllowedFromHim( int ePluginType )
	{
		return ( Constants.ePluginAccessOk == getPluginAccessState( ePluginType, getHisFriendshipToMe() ) );
	}
	
	//========================================================================
	public String describeMyFriendshipToHim()
	{
		return Constants.describeFriendState( getMyFriendshipToHim() );
	}
	
	//========================================================================
	public String describeHisFriendshipToMe()
	{
		return Constants.describeFriendState( getHisFriendshipToMe() ); 
	}

	//========================================================================
	@Override
	public int compareTo( VxNetIdent another )
	{
		if( this == another )
			return 0;
		if( this.m_s64LastSessionTime < another.getLastSessionTime() ) 
			return 1;
		else if( this.m_s64LastSessionTime == another.getLastSessionTime() ) 
			return 0;
		else 
			return -1;
	}

	//========================================================================
	public long getLastSessionTime()
	{
		return m_s64LastSessionTime;
	}

	//========================================================================
	public int getMyAccessPermissionFromHim( int ePluginType )
	{
		int accessState = getPluginAccessState( ePluginType, getHisFriendshipToMe() );
		if( Constants.ePluginAccessOk == accessState )
		{
			if( ( Constants.ePluginTypeFileServer == ePluginType ) 
				&& ( false == hasSharedFiles() ) )
			{
				// no files shared
				return Constants.ePluginAccessInactive;
			}

			if( ( Constants.ePluginTypeCamServer == ePluginType ) 
				&& ( false == hasSharedWebCam() ) )
			{
				// no shared web cam
				return Constants.ePluginAccessInactive;
			}

			if( ( Constants.ePluginTypeWebServer == ePluginType )
				|| ( Constants.ePluginTypeStoryBoard == ePluginType )
				|| ( Constants.ePluginTypeRelay == ePluginType ) )
			{
				if( false == isOnline() )
				{
					accessState = Constants.ePluginAccessRequiresOnline;
				}

				if( requiresRelay() )
				{
					accessState = Constants.ePluginAccessRequiresDirectConnect;
				}
			}
			else if( Constants.ePluginTypeMultiSession != ePluginType )
			{
				if( false == isOnline() )
				{
					accessState = Constants.ePluginAccessRequiresOnline;
				}
			}		
		}

		return accessState;
	}
}
