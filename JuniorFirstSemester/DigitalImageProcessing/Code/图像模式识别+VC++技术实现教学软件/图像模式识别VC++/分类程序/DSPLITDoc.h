// DSPLITDoc.h : interface of the CDSPLITDoc class
// 2005.1.13гн16г║02 By Superman 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPLITDOC_H__56C06037_E139_4924_9EEE_15034315991F__INCLUDED_)
#define AFX_DSPLITDOC_H__56C06037_E139_4924_9EEE_15034315991F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Classification.h"



class CDSPLITDoc : public CDocument
{
protected: // create from serialization only
	CDSPLITDoc();
	DECLARE_DYNCREATE(CDSPLITDoc)

// Attributes
public:
	Classification classify;
	CString filename;
	CString curDir;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPLITDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSPLITDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSPLITDoc)
	afx_msg void OnMenuDesign();
	afx_msg void OnButtonOpen();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPLITDOC_H__56C06037_E139_4924_9EEE_15034315991F__INCLUDED_)
