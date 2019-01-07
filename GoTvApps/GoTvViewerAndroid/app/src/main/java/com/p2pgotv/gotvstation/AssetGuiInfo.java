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

import android.util.Log;

class AssetGuiInfo implements Comparable<AssetGuiInfo>  
{
	public static final String LOG_TAG = "AssetGuiInfo:"; 
	
	//=== vars ===//
	String						m_AssetName				= new String(""); // usually file name
	String						m_AssetTag				= new String("");
	
	VxGUID						m_UniqueId				= new VxGUID( 0, 0 );
	VxGUID						m_CreatorId				= new VxGUID( 0, 0 );
	VxGUID						m_HistoryId				= new VxGUID( 0, 0 );
	
	byte[]						m_AssetHash				= new byte[20];
	long						m_AssetLen				= 0;
	short						m_AssetType				= 0;
	long						m_CreationTime			= 0;
	int							m_LocationFlags			= 0;
	int							m_AssetSendState		= 0;
	
	//============================================================================
	AssetGuiInfo()
	{
	}
	
	//============================================================================
	boolean isValid()
	{
		return ( Constants.VXFILE_TYPE_UNKNOWN != m_AssetType );
	}

	//============================================================================
	boolean isHashValid()
	{
		for( int i = 0; i < 20; i++ )
		{
			if( 0 != m_AssetHash[i] )
			{
				return true;
			}
		}
		
		return false;
	}

    //============================================================================
    void setContent( String contentText )
    {
        switch( m_AssetType )
        {
            case Constants.eAssetTypeChatText:
            case Constants.eAssetTypeChatFace:
            case Constants.eAssetTypePhoto:
            case Constants.eAssetTypeAudio:
            case Constants.eAssetTypeVideo:
            case Constants.eAssetTypeDocument:
            case Constants.eAssetTypeArchives:
            case Constants.eAssetTypeExe:
            case Constants.eAssetTypeOtherFiles:
            case Constants.eAssetTypeDirectory:
                m_AssetName 		= contentText;
                break;

            default:
            	m_AssetName 		= contentText;
                m_AssetType 		= Constants.eAssetTypeChatText;
        }
    }

    //============================================================================
    boolean isVideoAsset()
    {
    	return ( Constants.eAssetTypeVideo == m_AssetType );
    }

    //============================================================================
    boolean isAudioAsset()
    {
    	return ( Constants.eAssetTypeAudio == m_AssetType );
    }
   
    //============================================================================
    boolean isFileAsset()
    {
    	boolean isFile = false;
        switch( m_AssetType )
        {
        case Constants.eAssetTypePhoto:
        case Constants.eAssetTypeAudio:
        case Constants.eAssetTypeVideo:
        case Constants.eAssetTypeDocument:
        case Constants.eAssetTypeArchives:
        case Constants.eAssetTypeExe:
        case Constants.eAssetTypeOtherFiles:
        	isFile 		= true;
            break;

        default:
            break;
        }
        
        return isFile;
    }

    //============================================================================
    void setContentAndAssetType( short assetType, String contentText )
    {
        m_AssetType 		= assetType;
        setContent( contentText );
    }

    //============================================================================
    String getContent()
    {
        switch( m_AssetType )
        {
            case Constants.eAssetTypeChatFace:
            case Constants.eAssetTypeChatText:
            case Constants.eAssetTypePhoto:
            case Constants.eAssetTypeAudio:
            case Constants.eAssetTypeVideo:
            case Constants.eAssetTypeDocument:
            case Constants.eAssetTypeArchives:
            case Constants.eAssetTypeExe:
            case Constants.eAssetTypeOtherFiles:
            case Constants.eAssetTypeDirectory:
                return m_AssetName;

            default:
                return m_AssetTag;
        }
    }

	//============================================================================
	void setChatText( String chatText )
	{
		m_AssetName 		= chatText;
		m_AssetType 		= Constants.eAssetTypeChatText;
	}
	
	//============================================================================
	String getChatText()
	{
		return m_AssetName;
	}
	
	//============================================================================
	void setChatFace( String faceResourceName )
	{
		m_AssetName 		= faceResourceName;
		m_AssetType 		= Constants.eAssetTypeChatFace;
	}
	
	//============================================================================
	String getChatFace()
	{
		return m_AssetName;
	}
	
	//============================================================================
	void setAssetName( String assetName)
	{
		Log.d( LOG_TAG, "setAssetName " + assetName );
		m_AssetName 		= assetName;
	}
		
	//============================================================================
	String getAssetName()
	{
		return m_AssetName;
	}
	
	//============================================================================
	void setAssetType( short assetType )
	{
		m_AssetType = assetType;
	}
		
	//============================================================================
	short getAssetType()
	{
		return m_AssetType;
	}
	
	//============================================================================
	void setAssetTag( String assetTag )
	{
		m_AssetTag = assetTag;
	}
		
	//============================================================================
	String getAssetTag()
	{
		return m_AssetTag;
	}
	
	//============================================================================
	// generates unique id, assigns it to asset and returns reference to it
	VxGUID generateNewUniqueId()
	{
		m_UniqueId = VxGUID.generateNewGUID();
		return m_UniqueId;
	}
	
	//============================================================================
	void setUniqueIdLong( long idHiPart, long idLoPart )
	{
		m_UniqueId.setOnlineId(idHiPart, idLoPart);
	}
	
	//============================================================================
	void setAssetUniqueId( VxGUID id )
	{
		m_UniqueId = id;
	}
	
	//============================================================================
	VxGUID getAssetUniqueId()
	{
		return m_UniqueId;
	}
	//============================================================================
	void setCreatorIdLong( long idHiPart, long idLoPart )
	{
		m_CreatorId.setOnlineId(idHiPart, idLoPart);
	}
	
	//============================================================================
	void setCreatorId( VxGUID id )
	{
		m_CreatorId = id;
	}
	
	//============================================================================
	VxGUID getCreatorId()
	{
		return m_CreatorId;
	}
	
	//============================================================================
	void setHistoryIdLong( long idHiPart, long idLoPart )
	{
		m_HistoryId.setOnlineId(idHiPart, idLoPart);
	}
	
	//============================================================================
	void setHistoryId( VxGUID id )
	{
		m_HistoryId = id;
	}
	
	//============================================================================
	VxGUID getHistoryId()
	{
		return m_HistoryId;
	}
	
	//============================================================================
	void setCreationTime( long createTime )
	{
		m_CreationTime = createTime;
	}
	
	//============================================================================
	long getCreationTime()
	{
		if( 0 == m_CreationTime )
		{
			Log.d( LOG_TAG, "Asset has no creation time " );
		}
		
		return m_CreationTime;
	}

	//============================================================================
	void setLocationFlags( int locFlags )			
	{ 
		m_LocationFlags = locFlags; 
	}
	
	//============================================================================
	int	getLocationFlags()					
	{ 
		return m_LocationFlags; 
	}

	//============================================================================
	void setAssetSendState( int sendState )	
	{ 
		m_AssetSendState = sendState; 
	}
	
	//============================================================================
	int	getAssetSendState()					
	{ 
		return m_AssetSendState; 
	}

	//============================================================================
	void setAssetLength( long assetLength )
	{
		m_AssetLen = assetLength;
	}
	
	//============================================================================
	long getAssetLength()
	{
		return m_AssetLen;
	}
	
	//============================================================================
	boolean isChatTextAsset()
	{
		return ( 0 == ( Constants.eAssetTypeChatText & m_AssetType ) ) ? true : false;
	}
	
	//============================================================================
	boolean hasFileName()
	{
		if( ( 0 != getAssetName().length() )
			&& ( 0 != ( m_AssetType & ( Constants.eAssetTypePhoto | Constants.eAssetTypeAudio | Constants.eAssetTypeVideo | Constants.eAssetTypeDocument | Constants.eAssetTypeArchives | Constants.eAssetTypeExe | Constants.eAssetTypeOtherFiles ) ) ) )
		{
			return true;
		}

		return false;
	}

	//============================================================================
	boolean needsHashGenerated()
	{
		if( ( false == isHashValid() )
			&& hasFileName() )
		{
			return true;
		}

		return false;
	}

	//============================================================================
	boolean isDirectory()
	{
		return ( 0 == ( Constants.VXFILE_TYPE_DIRECTORY & m_AssetType ) ) ? true : false;
	}

	//============================================================================
	String getRemoteAssetName()
	{
		VxFileName fileName = new VxFileName( getAssetName() );
		return fileName.getJustFileName();
	}

	//============================================================================
	String getDefaultFileExtension( int assetType )
	{
		String extension = new String(".txt");
		switch( assetType )
		{
		case Constants.eAssetTypePhoto:
			extension = ".jpg";
			break;

		case Constants.eAssetTypeAudio:
			extension = ".opus";
			break;

		case Constants.eAssetTypeVideo:
			extension = ".avi";
			break;

		default:
			break;
		}

		return extension;
	}

	//============================================================================
	String getSubDirectoryName( int assetType )
	{
		String subDir = new String("asset/");
		switch( assetType )
		{
		case Constants.eAssetTypeDocument:
			subDir = "documents/";
			break;

		case Constants.eAssetTypeArchives:
			subDir = "archives/";
			break;

		case Constants.eAssetTypeOtherFiles:
			subDir = "other_files/";
			break;

		case Constants.eAssetTypePhoto:
			subDir = "photos/";
			break;

		case Constants.eAssetTypeAudio:
			subDir = "audio/";
			break;

		case Constants.eAssetTypeVideo:
			subDir = "video/";
			break;

		default:
			break;
		}

		return subDir;
	}

	//============================================================================
	@Override
	public int compareTo( AssetGuiInfo another )
	{
		if( (another == this) 
			|| ((another.m_UniqueId.m_u64IdHiPart == this.m_UniqueId.m_u64IdHiPart) && (another.m_UniqueId.m_u64IdLoPart == this.m_UniqueId.m_u64IdLoPart)) )
		{
			return 0;
		}
		
		if( m_UniqueId.m_u64IdLoPart >  another.m_UniqueId.m_u64IdLoPart )
		{
			return 1;
		}
		
		return -1;
	}	
}
