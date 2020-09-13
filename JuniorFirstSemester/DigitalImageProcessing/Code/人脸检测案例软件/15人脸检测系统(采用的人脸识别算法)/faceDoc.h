// faceDoc.h : interface of the CFaceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDOC_H__2C468D15_1BDF_4504_AAB7_01F866E7DB29__INCLUDED_)
#define AFX_FACEDOC_H__2C468D15_1BDF_4504_AAB7_01F866E7DB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFaceDoc : public CDocument
{
protected: // create from serialization only
	CFaceDoc();
	DECLARE_DYNCREATE(CFaceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDOC_H__2C468D15_1BDF_4504_AAB7_01F866E7DB29__INCLUDED_)
