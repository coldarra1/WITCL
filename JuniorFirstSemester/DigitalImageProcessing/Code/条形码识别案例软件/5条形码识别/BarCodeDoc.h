// BarCodeDoc.h : interface of the CBarCodeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARCODEDOC_H__AF2A7446_00A3_45B7_82AC_00D25DB9BB13__INCLUDED_)
#define AFX_BARCODEDOC_H__AF2A7446_00A3_45B7_82AC_00D25DB9BB13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBarCodeDoc : public CDocument
{
protected: // create from serialization only
	CBarCodeDoc();
	DECLARE_DYNCREATE(CBarCodeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarCodeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBarCodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBarCodeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARCODEDOC_H__AF2A7446_00A3_45B7_82AC_00D25DB9BB13__INCLUDED_)
