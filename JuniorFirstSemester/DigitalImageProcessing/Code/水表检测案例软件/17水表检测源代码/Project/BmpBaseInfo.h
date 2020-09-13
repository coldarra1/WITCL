#if !defined(AFX_BMPBASEINFO_H__F97EB1E9_69A3_4890_AF5D_96903E17BEE1__INCLUDED_)
#define AFX_BMPBASEINFO_H__F97EB1E9_69A3_4890_AF5D_96903E17BEE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpBaseInfo.h : header file
//
#include "ProjectDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CBmpBaseInfo dialog

class CBmpBaseInfo : public CDialog
{
// Construction
public:
	CBmpBaseInfo(CWnd* pParent = NULL);   // standard constructor
	void SetInfo(CProjectDoc * pDoc);
	CString LongToString(long data);
// Dialog Data
	//{{AFX_DATA(CBmpBaseInfo)
	enum { IDD = IDD_BASEINFO };
	CString	m_Style;
	CString	m_FileSize;
	CString	m_DataOff;
	CString	m_SelfLen;
	CString	m_Width;
	CString	m_Height;
	CString	m_DataSize;
	CString	m_PixelDep;
	CString	m_UsedColor;
	CString	m_ImportColor;
	CString	m_Compress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpBaseInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBmpBaseInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBASEINFO_H__F97EB1E9_69A3_4890_AF5D_96903E17BEE1__INCLUDED_)
