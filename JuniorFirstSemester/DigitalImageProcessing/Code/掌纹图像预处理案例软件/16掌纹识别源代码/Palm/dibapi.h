// dibapi.h
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#ifndef _INC_DIBAPI
#define _INC_DIBAPI

/* Handle to a DIB */
DECLARE_HANDLE(HDIB);

/* DIB constants */
#define PALVERSION   0x300

/* DIB Macros*/

#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

/* Function prototypes */
BOOL      WINAPI  PaintDIB (HDC, LPRECT, HDIB, LPRECT, CPalette* pPal);
BOOL      WINAPI  CreateDIBPalette(HDIB hDIB, CPalette* cPal);
LPSTR     WINAPI  FindDIBBits (LPSTR lpbi);
DWORD     WINAPI  DIBWidth (LPSTR lpDIB);
DWORD     WINAPI  DIBHeight (LPSTR lpDIB);
WORD      WINAPI  PaletteSize (LPSTR lpbi);
WORD      WINAPI  DIBNumColors (LPSTR lpbi);
HGLOBAL   WINAPI  CopyHandle (HGLOBAL h);
BYTE ** FillDibToArray(HDIB hDIB);
BOOL      WINAPI  SaveDIB (HDIB hDib, CFile& file);
HDIB      WINAPI  ReadDIBFile(CFile& file);
HDIB				Template(HDIB hDIB,double * tem ,int tem_w,int tem_h,double xishu);
HDIB				MaxTemplate(HDIB hDIB,double * tem ,int tem_w,int tem_h,double xishu,int count);
HDIB	  WINAPI  MidFilter(HDIB hDIB,int tem_w,int tem_h);
void Thinning(HDIB hDIB);
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly);
BOOL WINAPI TranslationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset);
HGLOBAL WINAPI ZoomDIB(LPSTR lpDIB, float fXZoomRatio, float fYZoomRatio);
HGLOBAL WINAPI RotateDIB(LPSTR lpDIB, int iRotateAngle);

HDIB      WINAPI NewDIB(long width, long height, unsigned short biBitCount= 0); //add
void	WINAPI ConvertShort(unsigned short *array, long length);
void	WINAPI ConvertLong(unsigned long *array, long length);
void      WINAPI decomposition(double* image,double* c,double* d,int n,int s);
void      WINAPI reconstruction(double* x, double* c,double* d,int n,int s);



#endif //!_INC_DIBAPI
