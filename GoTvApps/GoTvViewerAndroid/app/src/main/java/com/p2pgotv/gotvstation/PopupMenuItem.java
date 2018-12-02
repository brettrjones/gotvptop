package com.p2pgotv.gotvstation;

public class PopupMenuItem
{
	//=== constants ===//
	public static final String LOG_TAG = "PopupMenuItem:";

	//=== vars ===//
	public int			m_iMenuId;
	public int			m_iSubMenuId;
	public String		m_strMenuText;
	public int 			m_iMenuIconId;
	
  	//============================================================================
	PopupMenuItem( int iMenuId, int iSubMenuId, int iIconId, String strItemText )
	{
		m_iMenuId 		= iMenuId;
		m_iSubMenuId 	= iSubMenuId;
		m_strMenuText 	= strItemText;
		m_iMenuIconId 	= iIconId;
	}
}
