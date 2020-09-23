// PalmDoc.h : interface of the CPalmDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PALMDOC_H__65F4BFB6_0DCC_4311_8785_3B2D324EE9D0__INCLUDED_)
#define AFX_PALMDOC_H__65F4BFB6_0DCC_4311_8785_3B2D324EE9D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPalmDoc : public CDocument
{
protected: // create from serialization only
	CPalmDoc();
	DECLARE_DYNCREATE(CPalmDoc)

// Attributes
public:
	HDIB m_hDIB;
	CPalette* m_palDIB;
	CSize m_sizeDoc;
		bool *corner;
		bool harris;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPalmDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPalmDoc();
	void ReplaceHDIB(HDIB hDIB);
	BOOL InitDIBData();
	afx_msg void OnGray();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPalmDoc)
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ReadImgFile(CString sName);
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALMDOC_H__65F4BFB6_0DCC_4311_8785_3B2D324EE9D0__INCLUDED_)
