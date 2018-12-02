package com.p2pgotv.gotvstation;

public class GuiFileXferSession extends VxFileInfo
{
	VxNetIdent					m_HisIdent										= null;
	int							m_ePluginType									= 0;
	VxGUID						m_LclInstanceId									= null;
	int							m_eXferState									= Constants.eXferStateUnknown;
	int							m_XferStateParam1								= 0;
	int							m_XferStateParam2								= 0;
	int							m_XferProcess									= 0;
	String 						m_XferErrorDesc									= "";
	int							m_XferDirection									= 0;
	public long					m_LastUpdateTimeMs								= 0;
	

	void						setHisIdent( VxNetIdent netIdent )				{ m_HisIdent = netIdent; }
	VxNetIdent					getHisIdent()									{ return m_HisIdent; }
	void						setPluginType( int ePluginType )				{ m_ePluginType = ePluginType; }
	int							getPluginType()									{ return m_ePluginType; }
	void						setLclSessionId( VxGUID lclSessionId )			{ m_LclInstanceId = lclSessionId; }
	VxGUID						getLclSessionId()								{ return m_LclInstanceId; }

	int							getXferState()									{ return m_eXferState; }
	int							getXferStateParam1()							{ return m_XferStateParam1; }
	int							getXferStateParam2()							{ return m_XferStateParam2; }
	int							getXferProgress()								{ return m_XferProcess; }
	void 						setXferDirection( int direction )				{ m_XferDirection = direction; }
	int							getXferDirection()								{ return m_XferDirection; }

	//========================================================================
	GuiFileXferSession( VxNetIdent		netIdent, 
						int				ePluginType,
						VxGUID			lclSessionId, 
						int				fileType, 
						long			fileLen, 
						String			fileName,
						byte[]			fileHash )
	{
		m_HisIdent 			= netIdent;
		m_ePluginType 		= ePluginType;
		m_LclInstanceId		= lclSessionId;
		
		setFullFileName( fileName );
		setFileType( fileType );
		setFileLength( fileLen );
		setFileHashData( fileHash );
		updateJustFileName();
	}
	
	//========================================================================
	void setXferState( int xferState, int param1, int param2 ) 
	{ 
		m_eXferState = xferState; 
		m_XferStateParam1 = param1; 
		m_XferStateParam2 = param2; 
		if( ( m_eXferState == Constants.eXferStateInDownloadXfer ) || ( m_eXferState == Constants.eXferStateInUploadXfer ) )
		{
			m_XferProcess = param1;
		}
		
		if( ( m_eXferState == Constants.eXferStateDownloadError ) || ( m_eXferState == Constants.eXferStateUploadError ) )
		{
			m_XferErrorDesc = GuiHelpers.describeEXferError( param2 );
		}
	}
	
	//========================================================================
	String describeXferState()
	{
		if( !m_XferErrorDesc.isEmpty()  )
		{
			return m_XferErrorDesc;
		}
		
		return GuiHelpers.describeEXferState( m_eXferState );
	}

	//============================================================================
	boolean getIsCompleted()
	{
		return ( Constants.eXferStateCompletedUpload == m_eXferState ) || ( Constants.eXferStateCompletedDownload == m_eXferState );
	}

	//============================================================================
	boolean getIsInError()
	{
		return ( Constants.eXferStateDownloadError == m_eXferState ) || ( Constants.eXferStateUploadError == m_eXferState );
	}
}
