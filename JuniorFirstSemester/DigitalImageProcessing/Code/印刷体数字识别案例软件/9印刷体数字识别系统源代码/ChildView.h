// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__6E49B475_7592_4B3F_B33D_CA54E54CC1AA__INCLUDED_)
#define AFX_CHILDVIEW_H__6E49B475_7592_4B3F_B33D_CA54E54CC1AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();
	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnFileOpenBmp();
	afx_msg void OnFileSaveBmp();
	afx_msg void OnImgprcShrinkAlign();
	afx_msg void OnImgprcAll();
	afx_msg void OnIMGPRC256ToGray();
	afx_msg void OnImgprcDivide();
	afx_msg void OnImgprcToDibAndSave();
	afx_msg void OnImgprcRemoveNoise();
	afx_msg void OnImgprcStandarize();
	afx_msg void OnImgprcThinning();
	afx_msg void OnImgprcAdjustSlope();
	afx_msg void OnIMGPRCGrayToWhiteBlack();
	afx_msg void OnImgprcSharp();
	afx_msg void OnFileReLoadBmp();
	afx_msg void OnInputGuiyihuaInfo();
	afx_msg void OnBpnetTrain();
	afx_msg void OnBpnetRecognize();
	afx_msg void OnThin2();
	afx_msg void Onaver();
	afx_msg void OnGass();
	afx_msg void OnMid();
	afx_msg void OnImgprcEqualize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnDraw(CDC * pDC);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__6E49B475_7592_4B3F_B33D_CA54E54CC1AA__INCLUDED_)
