// recognise_yanDoc.h : interface of the CRecognise_yanDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECOGNISE_YANDOC_H__F607EF82_DB79_4649_B260_32B55E435001__INCLUDED_)
#define AFX_RECOGNISE_YANDOC_H__F607EF82_DB79_4649_B260_32B55E435001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRecognise_yanDoc : public CDocument
{
protected: // create from serialization only
	CRecognise_yanDoc();
	DECLARE_DYNCREATE(CRecognise_yanDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecognise_yanDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRecognise_yanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRecognise_yanDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECOGNISE_YANDOC_H__F607EF82_DB79_4649_B260_32B55E435001__INCLUDED_)
