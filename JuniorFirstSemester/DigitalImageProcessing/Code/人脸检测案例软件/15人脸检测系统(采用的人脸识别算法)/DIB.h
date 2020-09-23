#if !defined(AFX_DIB_H__A2ADDB4C_F0D1_4301_B08F_262BB56BC373__INCLUDED_)
#define AFX_DIB_H__A2ADDB4C_F0D1_4301_B08F_262BB56BC373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define HDIB  HANDLE 
#define RADIUS  12
#define m_HEIGHT 600
#define m_WIDTH 600
#define AREAPIXEL 600
#define Wcb  46.97
#define WLcb  23
#define WHcb  14
#define Wcr  38.76
#define WLcr  20
#define WHcr  10
#define Kl  125
#define Kh  188
#define Ymin  16
#define Ymax  235
#define ImgRange 600

class DIB  
{
	
public:
	bool    lab[ImgRange][ImgRange];
	int		lenth;
	void    Erasion2(HANDLE hDIB);
	void    MouseMap(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void    EyeMapb(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void    EyeMapR(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void    Erasion(HANDLE hDIB);
	void    RgbtoYcb(HANDLE hDIB, LPBYTE lpYcb);
	void    ErasionFalseArea(HANDLE hDIB);
	void    FaceLocate(HANDLE hDIB, CRect faceLocation[10], int &faceNum);
	void    EyeMapL(LPBYTE lpRgb, WORD wBytesPerLine, CRect faceLocation);
	void    eyeMap(LPBYTE lpResult, bool eyemapc[][ImgRange], bool eyemapl[][ImgRange], bool lab[][ImgRange], WORD wBytesPerLine, CRect faceLocation);
	void    RecursiveCal(LPBYTE lpData, int y, int x, WORD wBytesPerLine, int &pixelNum, int num);
	void    EyeMapC(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation);
	void    RecursiveLocateRect(LPBYTE lpData,WORD wBytesPerLine, int y, int x, int num, CRect &faceRect);
	void    faceear(LPBYTE lpYcc, WORD wBytesPerLine, int height,int width, bool flag[ImgRange][ImgRange]);
	int     _WCr(int Y);
	int     _Cr(int Y);
	int     _WCb(int Y);
	void    YccTransform(LPBYTE lpYcc,WORD wBytesPerLine,int height,int width);
	int     _Cb(int Y);
	LPBYTE    YcctoRgb(LPBYTE lpYcc,WORD wBytesPerLine,int height,int width);
	BOOL      FaceModeling(int Cr,int Cb);
    BOOL      MatchImportantPoint(HANDLE hDIB,int CharaterInfo[RADIUS*2+1][RADIUS*2+1][3],CPoint *ImPoint);
	HANDLE    CopyHandle(HANDLE hSrc);
	BOOL      SaveDIB(HDIB hDib, CFile& file);
	CPoint	  SearchInteriorPoint(CPoint Point,LPBYTE lpDIBBits,WORD wBytesPerLine);
	HDIB      LoadDIB(LPCTSTR lpFileName);
	HDIB      ReadDIBFile(HANDLE hFile);

	BOOL      PaintDIBTrue(HDC hDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect,DWORD dwRop);

	WORD      BytePerLine(HANDLE hDIB);
	HDIB      ToGray(HANDLE hDIB);
	LPBYTE    FindDIBBits(HANDLE hDIB);
	long	  PixelOffset(int i,int j,WORD wBytePerLine);
	int		  BOUND(int a ,int b ,int rgb);
	void 	  WhiteBlack(HANDLE hDIB,unsigned n);
	DIB();
	virtual ~DIB();
public :
	void DdaLine(CPoint from,CPoint end,LPBYTE lpData,WORD wBytesPerLine);
	void EllipseFace(HANDLE hDIB,CPoint mouth,CPoint eye1,CPoint eye2);
	void EyeCenter(HANDLE hDIB, CRect faceLocation, CPoint &eye1,CPoint &eye2);
	void MouthCenter(HANDLE hDIB, CRect faceLocation, CPoint &mouthLocation);
	void DeleteScatePoint(HANDLE hDIB);
	void DeleteFasleEye(HANDLE hDIB,CRect);
	void Dilation(HANDLE hDIB);
	BOOL LightingCompensate(HANDLE hDIB);
	BOOL IsScaterPoint(int x,int y,int width,int height,LPBYTE lpData,WORD wBytesPerLine,int threshold,bool lab[m_HEIGHT][m_WIDTH]);
	
	int width;
	int height;

private:


};

#endif // !defined(AFX_DIB_H__A2ADDB4C_F0D1_4301_B08F_262BB56BC373__INCLUDED_)
