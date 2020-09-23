// DIB.h: interface for the DIB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__A2ADDB4C_F0D1_4301_B08F_262BB56BC373__INCLUDED_)
#define AFX_DIB_H__A2ADDB4C_F0D1_4301_B08F_262BB56BC373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define HDIB  HANDLE 
#define RADIUS  12
#define m_HEIGHT 600
#define m_WIDTH 600

class DIB  
{
	
public:
	int lenth;
	CPoint    GetEdgeCenter(HANDLE hDIB);
	BOOL      CompareImg2(HANDLE hDIBBK,HANDLE hDIBCurrent,CPoint pt1,CPoint pt2);
	BOOL      ComPareImg(HANDLE hDIB1, HANDLE hDIB2 ,CPoint pt1,CPoint pt2);
    BOOL      MatchImportantPoint(HANDLE hDIB,int CharaterInfo[RADIUS*2+1][RADIUS*2+1][3],CPoint *ImPoint);
	HANDLE    CopyHandle(HANDLE hSrc);
	void      interPolate(LPBYTE Src,int x,int y, float u,float v, int scanw, int scanh,int *r,int *g,int *b);
	HANDLE    ScaleDIB(HANDLE hDIB,float scal_x,float scal_y);
	HANDLE    Gradient(HANDLE hDIB);	
	BOOL      SaveDIB(HDIB hDib, CFile& file);
	void      ThinningDIB(HANDLE hDIB);
	CPoint	  SearchInteriorPoint(CPoint Point,LPBYTE lpDIBBits,WORD wBytesPerLine);
	BOOL      IsBorderPoint(CPoint CurrentPoint ,LPBYTE lpDIBBits,WORD wBytesPerLine);
	CPoint    NextBorderPoint(CPoint CurrentPoint, LPBYTE lpDIBBits,WORD wBytesPerLine);
	HDIB      LoadDIB(LPCTSTR lpFileName);
	HDIB      ReadDIBFile(HANDLE hFile);

	BOOL      PaintDIBTrue(HDC hDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect,DWORD dwRop);

	WORD      BytePerLine(HANDLE hDIB);
	HDIB      ToGray(HANDLE hDIB);
	LPBYTE    FindDIBBits(HANDLE hDIB);
	long	  PixelOffset(int i,int j,WORD wBytePerLine);
	int       MedianSearch(int a[9][3],int n,int *r,int *g,int *b);
	void	  DoMedianFilterDIB(int *r,int *g,int*b,WORD i,WORD j,WORD wBytesPerLine,LPBYTE lpDIBBits);
	void	  MedianFilterDIB(HANDLE hDIB);
	int		  BOUND(int a ,int b ,int rgb);
	void 	  WhiteBlack(HANDLE hDIB,unsigned n);
	void        LocateImporntPoint(HANDLE hDIB,int Radius,CPoint *pPoint);
	DIB();
	virtual ~DIB();
public :
	BOOL IsScaterPoint(int x,int y,int width,int height,LPBYTE lpData,WORD wBytesPerLine,int threshold,bool lab[m_HEIGHT][m_WIDTH]);
	
	int width;
	int height;

private:


};

#endif // !defined(AFX_DIB_H__A2ADDB4C_F0D1_4301_B08F_262BB56BC373__INCLUDED_)
