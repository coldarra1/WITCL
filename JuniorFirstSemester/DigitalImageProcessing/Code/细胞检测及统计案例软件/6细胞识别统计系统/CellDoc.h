// CellDoc.h : interface of the CCellDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLDOC_H__64A4D1E8_CB1E_41AF_96EE_C2130B4F479B__INCLUDED_)
#define AFX_CELLDOC_H__64A4D1E8_CB1E_41AF_96EE_C2130B4F479B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCellDoc : public CDocument
{
protected: // create from serialization only
	CCellDoc();
	DECLARE_DYNCREATE(CCellDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCellDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCellDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCellDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLDOC_H__64A4D1E8_CB1E_41AF_96EE_C2130B4F479B__INCLUDED_)
