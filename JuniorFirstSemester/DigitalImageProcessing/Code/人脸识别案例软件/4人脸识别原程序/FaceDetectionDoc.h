// FaceDetectionDoc.h : interface of the CFaceDetectionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDETECTIONDOC_H__C653164F_64DF_4C47_BDE9_77623DD7D5E7__INCLUDED_)
#define AFX_FACEDETECTIONDOC_H__C653164F_64DF_4C47_BDE9_77623DD7D5E7__INCLUDED_
#include"math.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dibapi.h"
#define Kl  145//125 //亮度的低值门限
#define Kh  200//188//亮度的高值门限
#define ImgRange 600//图像的最大值
#define RADIUS  12
#define m_HEIGHT 600
#define m_WIDTH 600
#define AREAPIXEL 900//600
#define Wcb  46.97
#define WLcb  23
#define WHcb  14
#define Wcr  38.76
#define WLcr  20
#define WHcr  10
#define Ymin  16
#define Ymax  235
#define PI 3.1415926

class CFaceDetectionDoc : public CDocument
{
protected: // create from serialization only
	CFaceDetectionDoc();
	DECLARE_DYNCREATE(CFaceDetectionDoc)
	CFile fileM2;

// Attributes
public:
		//HDIB m_hDIB; 
		HDIB m_hDIB;
		HDIB m_hDIBtemp;
		CSize m_sizeDoc;
		CPalette* m_palDIB;
		LONG lLineBytesMulspec;

		HDIB GetHDIB() const
		{ return m_hDIB; }
		CPalette* GetDocPalette() const
		{ return m_palDIB; }
		CSize GetDocSize() const
		{ return m_sizeDoc; }
		LPBYTE lpYcc;
		bool flag[ImgRange][ImgRange];
		bool   emymapc[ImgRange][ImgRange];
		bool   emymapl[ImgRange][ImgRange];
		int		lenth;
		bool    lab[ImgRange][ImgRange];

// Operations
public:
	bool LightingCompensate();
	void RgbtoYcb(HDIB hDIB,LPBYTE lpYcb);
	int _Cb(int Y);
	int _Cr(int Y);
	int _WCb(int Y);
	int _WCr(int Y);
	void YccTransform(LPBYTE lpYcc,WORD wBytesPerLine,int height,int width);
	void faceear(LPBYTE lpYcc, WORD wBytesPerLine, int height,int width, bool flag[ImgRange][ImgRange]);
	BOOL FaceModeling(int Cr,int Cb);
	void Skintone();
	void Dilation();
	void Erasion();
	void ErasionMouse();
	void DeleteFalseArea();
	void RecursiveCal(LPBYTE lpData, int y, int x, WORD wBytesPerLine, int &pixelNum, int num);
	HANDLE  CopyHandle(HANDLE  hSrc);
	void RecursiveLocateRect(LPBYTE lpData,WORD wBytesPerLine, int y, int x, int num, CRect &faceRect);
	void FaceLocate(CRect faceLocation[10], int &faceNum);
	void EyeMapR(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void Crmap();
	void EyeMapC(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void EyeMappingC();
	void EyeMappingL();
	void EyeMapL(LPBYTE lpRgb, WORD wBytesPerLine, CRect faceLocation);
	void Eyemap(); 
	void DeleteFasleEye(CRect facelocation);
	void EyeCenter(CPoint &eye1, CPoint &eye2);
	void FunctionMouseMap(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void MouseMap();
	void DeleteScatePoint();
	BOOL IsScaterPoint(int x, int y, int width, int height, LPBYTE lpData,WORD wBytesPerLine,  int threshold,bool lab[m_HEIGHT][m_WIDTH]);
	void MouthCenter(CPoint &mouthLocation);
	void EllipseFace(CPoint mouth, CPoint eye1, CPoint eye2,CRect faceLocation);
	void DdaLine(CPoint from, CPoint end, LPBYTE lpData, WORD wBytesPerLine);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDetectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDetectionDoc)
	afx_msg void OnFileSaveAs(LPCTSTR lpszPathName);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTIONDOC_H__C653164F_64DF_4C47_BDE9_77623DD7D5E7__INCLUDED_)
