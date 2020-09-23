// modeDoc.h : interface of the CModeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEDOC_H__6D423A26_9CDB_4C98_917E_CEFB2869768A__INCLUDED_)
#define AFX_MODEDOC_H__6D423A26_9CDB_4C98_917E_CEFB2869768A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cluster.h"

class CModeDoc : public CDocument
{
protected: // create from serialization only
	CModeDoc();
	DECLARE_DYNCREATE(CModeDoc)

// Attributes
public:
	CCluster mCluster;
	int state;//0:初始状态；1：打开一幅bmp图片；2：手写识别。
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CModeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CModeDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODEDOC_H__6D423A26_9CDB_4C98_917E_CEFB2869768A__INCLUDED_)
