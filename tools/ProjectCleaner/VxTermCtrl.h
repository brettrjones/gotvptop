
//  ============================================================
//		Copyright (c) 2000 Brett Jones
//  ============================================================

#if !defined(AFX_VXTERMCTRL_H__D5BF8227_F619_11D4_8DCC_00C0F05BDC17__INCLUDED_)
#define AFX_VXTERMCTRL_H__D5BF8227_F619_11D4_8DCC_00C0F05BDC17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOMScrollCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VxTermCtrl window

class VxTermCtrl : public CEdit
{
public:
	int m_iMaxLines;
	void Print( char * pStr, ...);
	void HexDump( char * pBuf, long s32DataLen );
	void HexDumpToFile( char * pFileName, char * pBuf, long lCount);
	void SetMaxLines( int iMaxLines ){ m_iMaxLines = iMaxLines; }

// Construction
public:
	VxTermCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VxTermCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VxTermCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(VxTermCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bCopyToTrace;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VXTERMCTRL_H__D5BF8227_F619_11D4_8DCC_00C0F05BDC17__INCLUDED_)
