// BarCodeView.h : interface of the CBarCodeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARCODEVIEW_H__CD0DCA1E_8D03_48E2_A864_B6B5F7F7CD5B__INCLUDED_)
#define AFX_BARCODEVIEW_H__CD0DCA1E_8D03_48E2_A864_B6B5F7F7CD5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBarCodeView : public CView
{
protected: // create from serialization only
	CBarCodeView();
	DECLARE_DYNCREATE(CBarCodeView)

// Attributes
public:
	CBarCodeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarCodeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBarCodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL    m_isBitmap;
	HBITMAP hBitmap;
	CBitmap m_bitmap;
private:
	BOOL   m_isCut;
	BOOL   m_isLBDown;
	BYTE*  hDataOld;
	BYTE*  hDataNew;
	BITMAP bmInfo;
	CPoint m_start;
	CPoint m_end;
// Generated message map functions
protected:
	//{{AFX_MSG(CBarCodeView)
	afx_msg void OnPicBw();
	afx_msg void OnFileOpen();
	afx_msg void OnPicSb();
	afx_msg void OnPicGray();
	afx_msg void OnPicPre();
	afx_msg void OnPicQz();
	afx_msg void OnPicCut();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BarCodeView.cpp
inline CBarCodeDoc* CBarCodeView::GetDocument()
   { return (CBarCodeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARCODEVIEW_H__CD0DCA1E_8D03_48E2_A864_B6B5F7F7CD5B__INCLUDED_)
