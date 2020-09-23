// ydpdDoc.h : interface of the CYdpdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YDPDDOC_H__3A9DF85D_FEDA_481E_9E8F_F10025EBBA9C__INCLUDED_)
#define AFX_YDPDDOC_H__3A9DF85D_FEDA_481E_9E8F_F10025EBBA9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CYdpdDoc : public CDocument
{
protected: // create from serialization only
	CYdpdDoc();
	DECLARE_DYNCREATE(CYdpdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYdpdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYdpdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYdpdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YDPDDOC_H__3A9DF85D_FEDA_481E_9E8F_F10025EBBA9C__INCLUDED_)
