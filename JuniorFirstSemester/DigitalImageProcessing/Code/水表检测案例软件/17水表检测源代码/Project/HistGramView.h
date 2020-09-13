#if !defined(AFX_HISTGRAMVIEW_H__213BDE8F_48CD_4A70_80A5_90B7702D6A95__INCLUDED_)
#define AFX_HISTGRAMVIEW_H__213BDE8F_48CD_4A70_80A5_90B7702D6A95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistGramView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistGramView view

class CHistGramView : public CScrollView
{
protected:
	CHistGramView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHistGramView)

// Attributes
public:
	void DrawHist(long lBitCount, CHistGramDoc * pDoc, CDC *pDC);
	long GetMax(long *List, int length, int StartPos);
    void DrawHistSon(CRect rect, CPen *pen, CFont *font, CDC *pDC, long *Hist, int Start);
	CString LongToString(long data);
// Operations
public:
	CHistGramDoc* GetDocument(); // non-debug version is inline

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistGramView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHistGramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistGramView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTGRAMVIEW_H__213BDE8F_48CD_4A70_80A5_90B7702D6A95__INCLUDED_)
