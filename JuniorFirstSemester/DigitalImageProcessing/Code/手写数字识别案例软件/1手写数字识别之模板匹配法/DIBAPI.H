/******************************************************************************** 
 *  DIBAPI.H
 * 
 *  Header file for Device-Independent Bitmap (DIB) API.  Provides 
 *  function prototypes and constants for DIB functions 
 ********************************************************************************/ 

#ifndef __DIBAPI_H_
#define __DIBAPI_H_
//////////////////////////////////////////////////////////

/* Handle to a DIB */ 
#define HDIB				HANDLE 

// Dib Header Marker - used in writing DIBs to files 
#define DIB_HEADER_MARKER	((WORD) ('M' << 8) | 'B') 

/* DIB constants */ 
#define PALVERSION			0x300 

/* DIB copy constants */ 
#define PW_WINDOW			1 
#define PW_CLIENT			2

// Image position in Canvas
#define LEFT_UP				1
#define CENTER_UP			2
#define RIGHT_UP			3
#define LEFT_CENTER			4
#define CENTER_CENTER		5
#define CENTER_RIGHT        6
#define LEFT_DOWN			7
#define CENTER_DOWN			8
#define RIGHT_DOWN			9

/* Gray Method */
#define MEAN_GRAY			0
#define MAXIMUM_GRAY		1
#define WEIGHT_GRAY			2

/* Color Model */
#define RGB_COLOR			0
#define CMYK_COLOR			1
#define HSI_COLOR			2
#define HLS_COLOR			3
#define UNDEFINED			(-1.0)

// Separate color
#define SEPARATE_RED		1
#define SEPARATE_GREEN		2
#define SEPARATE_BLUE		3

// Filte color
#define FILTE_RED			1
#define FILTE_GREEN			2
#define FILTE_BLUE			3

// Filter algorithm
#define FILTER1				1
#define FILTER2				2
#define FILTER3				3

// Edge enhancement algorithm
#define VERT				1
#define HORZ				2
#define VERTHORZ			3
#define NORTH				4
#define NORTHEAST			5
#define EAST				6
#define SOUTH				7
#define SOUTHEAST			8
#define SOUTHWEST			9
#define WEST				10
#define NORTHWEST			11
#define LAP1				12
#define LAP2				13
#define LAP3				14
#define LAP4				15
#define SOBEL				16
#define HOUGH				17

/* DIB Macros*/ 
// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits" 
// parameter is the bit count for the scanline (biWidth * biBitCount), 
// and this macro returns the number of DWORD-aligned bytes needed  
// to hold those bits. 
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER)) 
#define RECTWIDTH(lpRect)   ((lpRect)->right - (lpRect)->left) 
#define RECTHEIGHT(lpRect)  ((lpRect)->bottom - (lpRect)->top) 
#define BOUND(x, mn, mx)	((x) < (mn) ? (mn) : ((x) > (mx) ? (mx) : (x)))
#define WaitCursorBegin()	HCURSOR hcURSOR = SetCursor(LoadCursor(NULL, IDC_WAIT))
#define WaitCursorEnd()		SetCursor(hcURSOR) 
 
/* function prototypes */ 
	// DIB initialization
HDIB CreateDIB(DWORD, DWORD, WORD); 
HDIB CreateDefaultDIB(DWORD dwWidth, DWORD dwHeight);
void DestroyDIB(HDIB); 
HDIB LoadDIB (LPTSTR); 
BOOL SaveDIB (HDIB, LPTSTR); 
HDIB ReadDIBFile(HANDLE); 
	// DIB attributes
DWORD BytesPerLine(LPBYTE lpDIB);
DWORD BytesPerLine(HDIB hDIB);
DWORD DIBlockSize(HDIB hDIB);
DWORD DIBlockSize(LPBYTE lpDIB);
DWORD DIBHeight (LPBYTE lpDIB); 
DWORD DIBHeight (HDIB hDIB); 
DWORD DIBWidth (LPBYTE lpDIB); 
DWORD DIBWidth (HDIB hDIB); 
WORD DIBNumColors (LPBYTE lpDIB); 
WORD DIBNumColors (HDIB hDIB); 
WORD DIBBitCount (LPBYTE lpDIB); 
WORD DIBBitCount (HDIB hDIB); 
LPBYTE FindDIBBits (LPBYTE lpDIB); 
WORD PaletteSize (LPBYTE lpDIB); 
WORD PaletteSize (HDIB hDIB); 
	// DIB display
BOOL PaintBitmap(HDC, LPRECT, HBITMAP, LPRECT, HPALETTE, DWORD);
BOOL PaintDIB(HDC, LPRECT, HDIB, LPRECT, HPALETTE, DWORD);
BOOL DitherDisplayDIB(HDC, LPRECT, HDIB, LPRECT, DWORD);
	// DIB operations
HBITMAP DIBToDIBSection(LPBYTE lpDIB);
HBITMAP DIBToDIBSection(HDIB hDIB);
HDIB DIBSectionToDIB(HBITMAP hBitmap);
HDIB ConvertDIBFormat(LPBYTE lpSrcDIB, UINT nWidth, UINT nHeight, UINT nbpp, BOOL bStretch, HPALETTE hPalSrc);
HDIB ConvertDIBFormat(HDIB hDIB, UINT nWidth, UINT nHeight, UINT nbpp, BOOL bStretch, HPALETTE hPalSrc);
HDIB ConvertDIBFormat(LPBYTE lpSrcDIB, UINT nbpp, HPALETTE hPalSrc);
HDIB ConvertDIBFormat(HDIB hDIB, UINT nbpp, HPALETTE hPalSrc);
HDIB BitmapToDIB (HBITMAP, HPALETTE); 
HDIB BitmapToDIB (HBITMAP, HPALETTE, WORD);
HDIB ChangeBitmapFormat (HBITMAP, WORD, DWORD, HPALETTE); 
HBITMAP DIBToBitmap (HDIB hDIB, HPALETTE hPal); 
HDIB ChangeDIBFormat (HDIB, WORD, DWORD); 
	// DIB palette
HPALETTE CreateDIBPalette(LPBYTE lpDIB);
HPALETTE CreateDIBPalette(HDIB hDIB); 
BOOL DisplayPalette(HDC hDC, LPRECT lpRect, HPALETTE hPal);
HPALETTE CopyPalette(HPALETTE hPalSrc);
HPALETTE GetSystemPalette(void); 
int PalEntriesOnDevice (HDC hDC); 
HPALETTE CreateIdentifyPalette(HPALETTE hPalSrc);
BOOL MapDIBColorsToPalette(HDIB hDIB, HPALETTE hPalette);
HPALETTE CreateDitherPalette();
HDIB CreateDither8BppDIB(HDIB hDIB);
	// DIB capture
HBITMAP CopyScreenToBitmap (LPRECT); 
HBITMAP CopyWindowToBitmap (HWND, WORD); 
HBITMAP CopyClientRectToBitmap(HWND hWnd, LPRECT lpRect);
HDIB CopyScreenToDIB (LPRECT); 
HDIB CopyWindowToDIB (HWND, WORD); 
HDIB CopyClientRectToDIB(HWND hWnd, LPRECT lpRect); 
	// effect display
void DrawTransparentBitmap(HDC, HBITMAP, LONG, LONG, COLORREF);
BOOL Fade(int nDeltaR, int nDeltaG, int nDeltaB, 
		  BYTE rm, BYTE gm, BYTE bm,
		  BYTE *r, BYTE *g, BYTE *b);
	// Helper
HANDLE CopyHandle(HANDLE h);
//void Delay(DWORD dwDelayTime);
	// DIB transform
HBITMAP	CropBitmap(HBITMAP, LPRECT);
HDIB CropDIB(HDIB, LPRECT);
HDIB CutDIB(HDIB, LPRECT);
HDIB MergeDIB(HDIB hDib1, HDIB hDib2, POINT ptTopLeft);
HDIB RotateDIB(HDIB hDib);
HDIB FlipHorzDIB(HDIB hDib);
HDIB FlipVertDIB(HDIB hDib);
HDIB ChangeDIBSize(HDIB hDIB, int nWidth, int nHeight);
HDIB ChangeDIBCanvasSize(HDIB hDIB, int nWidth, int nHeight, int nPosition);
	// Color quantization
HPALETTE CreateOctreePalette(HDIB hDIB, UINT nMaxColors, UINT nColorBits);
HPALETTE CreateOctreePalette(LPBYTE lpDIB, UINT nMaxColors, UINT nColorBits);
	// color process
HDIB SeparateRGBfromDIB(HDIB hDib, int nIndex);
HDIB FilteRGBfromDIB(HDIB hDib, int nIndex);
HDIB ColorQuantizeDIB(HDIB hDIB, UINT nColorBits, UINT nMaxColors);
HPALETTE ConvertToGrayscale(HDIB hDib, int nMethod, 
			    double fRedWeight, double fGreenWeight, double fBlueWeight);
BOOL AdjustDIBColor(HDIB hDib, int nColorModel, int v1, int v2, int v3);
BOOL AdjustDIBBrightness(HDIB hDib, int v);
BOOL AdjustDIBContrast(HDIB hDib, int v);
void RGBtoHSI(BYTE r, BYTE g, BYTE b, double *h, double *s, double *i);
void HSItoRGB(double h, double s, double i, BYTE *r, BYTE *g, BYTE *b);
void RGBtoHLS(BYTE r, BYTE g, BYTE b, double *h, double *l, double *s);
void HLStoRGB(double h, double l, double s, BYTE *r, BYTE *g, BYTE *b);
void CMYKtoRGB(BYTE c, BYTE m, BYTE y, BYTE k, BYTE *r, BYTE *g, BYTE *b);
void RGBtoCMYK(BYTE r, BYTE g, BYTE b, BYTE *c, BYTE *m, BYTE *y, BYTE *k);
void ChangeContrast(int nDelta, BYTE *r, BYTE *g, BYTE *b);
void ChangeBrightness(int nDelta, BYTE *r, BYTE *g, BYTE *b);
	// image process
BOOL HighPassDIB(HDIB hDib, int Strength, int nAlgorithm);
BOOL LowPassDIB(HDIB hDib, int Strength, int nAlgorithm);
BOOL EdgeEnhanceDIB(HDIB hDib, int Strength, int nDirection);
BOOL MedianFilterDIB(HDIB hDib);

//////////////////////////////////////////////////////////
#endif	//__DIBAPI_H_