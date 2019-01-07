package com.p2pgotv.gotvstation;

import java.lang.reflect.Array;
import java.util.List;

public class FileShareSettings 
{
	//=== vars ===//
	//String						m_strCompletedDir;
	//String						m_strIncompleteDir;
	int							m_u32DownloadBandwidth;
	int							m_u32MaxDownloadingFiles;

	//String[]					m_aoSharedDirs = null;
	
	int							m_u32UploadBandwidth;
	int							m_u32MaxUploadingFiles;
	boolean						m_bStartServerOnStartup;

/*	
	void						addSharedDir( String dir )
	{
		int stringCnt = ( null == m_aoSharedDirs ) ? 1 : (m_aoSharedDirs.length + 1);
		String[] newList = new String[ stringCnt ];
		if( null != m_aoSharedDirs )
		{
			for( int i = 0; i < m_aoSharedDirs.length; i++ )
			{
				newList[i] = m_aoSharedDirs[i];
			}
		}

		newList[ stringCnt - 1 ] = dir;
		m_aoSharedDirs = newList;
	}*/

}
