//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

public class VxFileInfo 
{
	private String				m_FullFileName			= "";
	private int					m_FileType				= 0;
	private long				m_FileLen				= 0;
	private VxSha1Hash			m_FileHashId			= new VxSha1Hash();
	private String				m_JustFileName			= "";
	private String				m_FilePath				= "";
	private boolean				m_IsShared				= false;
	private boolean				m_IsInLibrary			= false;
	
	private int					m_ListIndex				= 0; // temporary value.. do not use if list is unlocked

	//============================================================================
	void 						setFullFileName( String fileName )		{ m_FullFileName = fileName; }
	String						getFullFileName()						{ return m_FullFileName; }
	void						setFileType( int fileType )				{ m_FileType = fileType; }
	int							getFileType()							{ return m_FileType; }
	void						setFileLength( long fileLen )			{ m_FileLen = fileLen; }
	long						getFileLength()							{ return m_FileLen; }
	void						setFileHashId( VxSha1Hash id )			{ m_FileHashId = id; }
	VxSha1Hash					getFileHashId()							{ return m_FileHashId; }
	void						setFileHashData( byte[] fileHashData )	{ m_FileHashId.setHashData( fileHashData ); }
	byte[]						getFileHashData()						{ return m_FileHashId.getHashData(); }
	void						setJustFileName( String fileName )		{ m_JustFileName = fileName; }
	String						getJustFileName()						{ return m_JustFileName; }
	void						setFilePath( String filePath )			{ m_FilePath = filePath; }
	String						getFilePath()							{ return m_FilePath; }
	boolean						isDirectory()							{ return ( 0 != ( m_FileType & Constants.VXFILE_TYPE_DIRECTORY )) ? true : false; }
	boolean						isPhoto()								{ return ( 0 != ( m_FileType & Constants.VXFILE_TYPE_PHOTO )) ? true : false; }
	void						setIsShared( boolean isShared )			{ m_IsShared = isShared; }
	boolean						getIsShared()							{ return m_IsShared; }
	void						setIsInLibrary( boolean isInLibrary )	{ m_IsInLibrary = isInLibrary; }
	boolean						getIsInLibrary()						{ return m_IsInLibrary; }
	void						setListIndex( int listIndex )			{ m_ListIndex = listIndex; }
	int							getListIndex()							{ return m_ListIndex; }
	
	//============================================================================
	VxFileInfo()
	{	
	}
	
	//============================================================================
	VxFileInfo(	String			fileName,
				long			fileLen, 
				int				fileType, 			
				byte[]			fileHash )
	{	
		m_FullFileName			= fileName;
		m_FileLen				= fileLen;
		m_FileType				= fileType;
		m_FileHashId.setHashData( fileHash );
		updateJustFileName();
	}
	
	//============================================================================
	void updateJustFileName()
	{
		if( m_FullFileName.isEmpty() )
		{
			m_JustFileName 	= "";
			m_FilePath 		= "";
			return;
		}
		
		m_JustFileName 	= VxFileUtil.getJustFileName( m_FullFileName );
		m_FilePath 		= VxFileUtil.getFilePath( m_FullFileName );
	}
	
	//========================================================================
	boolean isMyP2PWebVideoFile()
	{
		boolean isMyVidFile = ( ( Constants.VXFILE_TYPE_VIDEO == getFileType() ) && NativeTxTo.fromGuiIsMyP2PWebVideoFile( getFullFileName() ) );
		return isMyVidFile;
	}
	
	//========================================================================
	boolean isMyP2PWebAudioFile()
	{
		boolean isMyAudioFile = ( ( Constants.VXFILE_TYPE_AUDIO == getFileType() ) && NativeTxTo.fromGuiIsMyP2PWebAudioFile( getFullFileName() ) );
		return isMyAudioFile;
	}

	//========================================================================
	String describeFileLength()
	{
		return VxFileUtil.describeFileLength( m_FileLen );
	}
	
	//========================================================================
	String describeFileType()
	{
		String fileDesc = VxFileUtil.describeFileType( getFileType() );
		fileDesc += ": ";
		return fileDesc;   
	}
	
	//========================================================================
	int getFileIconResource()
	{
		return VxFileUtil.getFileIconResource( getFileType() );
	}
}
