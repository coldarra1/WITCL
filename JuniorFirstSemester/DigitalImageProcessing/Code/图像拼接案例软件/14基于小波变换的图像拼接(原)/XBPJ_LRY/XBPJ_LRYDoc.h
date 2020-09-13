// XBPJ_LRYDoc.h : interface of the CXBPJ_LRYDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XBPJ_LRYDOC_H__8A9372CE_ED64_47D2_8DCB_2546C6E29172__INCLUDED_)
#define AFX_XBPJ_LRYDOC_H__8A9372CE_ED64_47D2_8DCB_2546C6E29172__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXBPJ_LRYDoc : public CDocument
{
protected: // create from serialization only
	CXBPJ_LRYDoc();
	DECLARE_DYNCREATE(CXBPJ_LRYDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXBPJ_LRYDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXBPJ_LRYDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXBPJ_LRYDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XBPJ_LRYDOC_H__8A9372CE_ED64_47D2_8DCB_2546C6E29172__INCLUDED_)
