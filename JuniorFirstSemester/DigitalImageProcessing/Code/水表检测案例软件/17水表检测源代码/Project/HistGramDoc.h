#if !defined(AFX_HISTGRAMDOC_H__AEF3F44F_ABD9_4252_A654_49BA371FD80F__INCLUDED_)
#define AFX_HISTGRAMDOC_H__AEF3F44F_ABD9_4252_A654_49BA371FD80F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistGramDoc.h : header file
//

#include "ProjectDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CHistGramDoc document

class CHistGramDoc : public CDocument
{
protected:
	CHistGramDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHistGramDoc)

// Attributes
public:
	long BitCount;
	long *pHist;
	BOOL bIsLoaded;

// Operations
public:
	void SetDocument(CProjectDoc * pDoc);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistGramDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CHistGramDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistGramDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTGRAMDOC_H__AEF3F44F_ABD9_4252_A654_49BA371FD80F__INCLUDED_)
