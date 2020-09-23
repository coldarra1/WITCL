#if !defined(AFX_DIB_H__33817561_072D_11D1_8C94_000021003EA5__INCLUDED_)
#define AFX_DIB_H__33817561_072D_11D1_8C94_000021003EA5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dib.h : header file
//

#include "DIBAPI.H"

// Effect consts
#define EFFECT_SCANDOWN		1
#define EFFECT_SCANUP		2
#define EFFECT_SCANRIGHT	3
#define EFFECT_SCANLEFT		4
#define EFFECT_VSPLITSCAN	5
#define EFFECT_HSPLITSCAN	6
#define EFFECT_MOVEDOWN		7
#define EFFECT_MOVEUP		8
#define EFFECT_MOVERIGHT	9
#define EFFECT_MOVELEFT		10
#define EFFECT_VSPLITMOVE	11
#define EFFECT_HSPLITMOVE	12
#define EFFECT_VCROSSMOVE	13
#define EFFECT_HCROSSMOVE	14
#define EFFECT_VRASTER		15
#define EFFECT_HRASTER		16
#define EFFECT_VBLIND		17
#define EFFECT_HBLIND		18
#define EFFECT_MOSAIC		19
#define EFFECT_FADE			20

////////////////////////////////////////////////////////////////////////////
// CDib
class CDib : public CObject
{                          
	DECLARE_SERIAL(CDib)

// Public member function
public: 
	// constructor
	CDib();
	// create
	BOOL	Create(DWORD dwWidth, DWORD dwHeight);
	BOOL	Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount);
	BOOL	Create(LPBYTE lpDIB);
	BOOL	Create(LPBYTE lpDIB,		// DIB pointer
				   WORD  wBitCount);	// bits/pixel 
	BOOL	Create(HBITMAP hBitmap);	// DIBSection
	BOOL	Create(HBITMAP hBitmap,		// DIBSection
				   WORD  wBitCount);	// bits/pixel 
	BOOL	Create(HBITMAP hBitmap,		// Bitmap handle
				   HPALETTE hPalette);	// Palette handle
	BOOL	Create(HBITMAP hBitmap,		// Bitmap handle
				   HPALETTE hPalette,	// Palette handle
				   WORD  wBitCount);	// bits/pixel 
	BOOL	Create(CRect rcScreen);
	BOOL	Create(HWND hWnd, WORD fPrintArea);
	BOOL	Create(HWND hWnd, CRect rcClientArea);
	// attach handle
	BOOL	Attach(HDIB hDib);
	// load/save
    BOOL	Load(UINT uIDS, LPCTSTR lpszDibType);
    BOOL	Load(LPCTSTR lpszDibRes, LPCTSTR lpszDibType);
    BOOL	Load(LPCTSTR lpszDibFile);
    BOOL	Save(LPCTSTR lpszDibFile);
	BOOL	Read(CFile *pFile);
	BOOL	Write(CFile *pFile);

	// deconstructor
	virtual ~CDib();
	// destroy
	void	Destroy();
	HDIB	Detach();

	// overlaying Serialize
	virtual void Serialize(CArchive &ar);
    
	// display
	BOOL	Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
 				   int xSrc, int ySrc, DWORD dwRop=SRCCOPY);
	BOOL	Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
				    int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop=SRCCOPY);
    BOOL	Display(CDC* pDC, int x, int y, DWORD dwRop=SRCCOPY);
	BOOL	Display(CDC* pDC, CRect rcDest, CRect rcSrc,DWORD dwRop=SRCCOPY);
	BOOL	DisplayPalette(CDC* pDC, CRect rc);

	// DC for modify DIB
	CDC*	BeginPaint(CDC *pDC);
	void	EndPaint();

	// DDB and palette
	BOOL	BuildBitmap();
	BOOL	BuildPalette();

	// attributes
	BOOL	IsEmpty();
	DWORD	GetCompression();
    WORD	GetBitCount();
    LONG	GetWidth();
    LONG	GetHeight();    
	LONG	GetWidthBytes();
    WORD	GetColorNumber();
	WORD	GetPaletteSize();
    CBitmap*  GetBitmap();
	CPalette* GetPalette();
	HANDLE	GetHandle();
	LPBYTE	GetBitsPtr();
	COLORREF GetPixel(LONG x, LONG y);
	LONG    GetPixelOffset(LONG x, LONG y);
	BOOL	ConvertFormat(WORD wBitCount); 

	// display transparently
	BOOL	DisplayTransparent(CDC* pDC, int x, int y, COLORREF cTransparentColor);

	// effect operation
	BOOL	Display(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime, DWORD dwRop=SRCCOPY);
	BOOL	Clear(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime);

	// transform
	HDIB	CopyRect(CRect rc);
	BOOL	CutRect(CRect rc);
	BOOL	MergeDib(HDIB hDib, CPoint ptTopLeft);
	BOOL	Crop(CRect rc);
	BOOL	Rotate90();
	BOOL	Rotate180();
	BOOL	Rotate270();
	BOOL	FlipHorz();
	BOOL	FlipVert();
	BOOL	Zoom(double fRatioX, double fRatioY);
	BOOL	ChangeImageSize(int nWidth, int nHeight);
	BOOL	ChangeCanvasSize(int nWidth, int nHeight, int nPosition);

	// color process
	BOOL	IsRequireDither(CDC* pDC);
	BOOL	DitherDisplay(CDC* pDC, CRect rcDest, CRect rcSrc, DWORD dwRop=SRCCOPY);
	BOOL	ColorQuantize(int nColors);
	BOOL	ChangeToGrayscale(int nMethod = MEAN_GRAY, 
							  double fRedWeight = 0.30, 
							  double fGreenWeight = 0.59, 
							  double fBlueWeight = 0.11);
	BOOL	AdjustColor(int nColorModel, int v1, int v2, int v3);
	BOOL	AdjustBrightness(int v);
	BOOL	AdjustContrast(int v);
	BOOL	SeparateRGB(int nIndex);
	BOOL	FilteRGB(int nIndex);
	
	// image process
	BOOL	HighPass(int Strength, int nAlgorithm);
	BOOL	LowPass(int Strength, int nAlgorithm);
	BOOL	EdgeEnhance(int Strength, int nAlgorithm);
	BOOL	MedianFilter();

// private member function
private:
	BOOL	UpdateInternal();
	BOOL	DisplayFadeIn(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime);
	BOOL	DisplayFadeOut(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime);
	BOOL	DisplayMosaicIn(CDC *pDC, int x, int y, int nTileSize, DWORD dwDelayTime, DWORD dwRop=SRCCOPY);
	BOOL	DisplayMosaicOut(CDC *pDC, int x, int y, int nTileSize, DWORD dwDelayTime);

// public member data
public:
	BOOL SetPixel8(LONG x, LONG y, BYTE value);
	BYTE GetPixel8(LONG x, LONG y);
	HDIB		m_hDib;
	HBITMAP		m_hBitmap;	// handle of DIBSection
	CPalette* 	m_pPalette;
	CBitmap*	m_pBitmap;

// private member data
private:
	// for drawing in DIB
	CDC *		m_pMemDC;
	CBitmap*	m_pBitmapTmp;
	CPalette*	m_pPaletteTmp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIB_H__33817561_072D_11D1_8C94_000021003EA5__INCLUDED_)
