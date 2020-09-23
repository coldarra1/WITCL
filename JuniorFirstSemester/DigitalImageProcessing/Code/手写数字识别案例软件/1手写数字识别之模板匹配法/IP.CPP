#include "stdafx.h"
#include "dibapi.h"

// Definitions required for convolution image filtering
#define KERNELCOLS 3
#define KERNELROWS 3
#define KERNELELEMENTS (KERNELCOLS * KERNELROWS)

// struct for convolute kernel 
typedef struct 
{
  int Element[KERNELELEMENTS];
  int Divisor;
} KERNEL;

// The following kernel definitions are for convolution filtering.
// Kernel entries are specified with a divisor to get around the
// requirement for floating point numbers in the low pass filters. 

KERNEL HP1 = {                    // HP filter #1
  {-1, -1, -1,
   -1,  9, -1,
   -1, -1, -1},
    1                             // Divisor = 1
};

KERNEL HP2 = {                    // HP filter #2
  { 0, -1,  0,
   -1,  5, -1,
    0, -1,  0},
    1                             // Divisor = 1
};

KERNEL HP3 = {                    // HP filter #3
  { 1, -2,  1,
   -2,  5, -2,
    1, -2,  1},
    1                             // Divisor = 1
};

KERNEL LP1 = {                    // LP filter #1
  { 1,  1,  1,
    1,  1,  1,
    1,  1,  1},
    9                             // Divisor = 9
};

KERNEL LP2 = {                    // LP filter #2
  { 1,  1,  1,
    1,  2,  1,
    1,  1,  1},
    10                            // Divisor = 10
};

KERNEL LP3 = {                    // LP filter #3
  { 1,  2,  1,
    2,  4,  2,
    1,  2,  1},
    16                            // Divisor = 16
};

KERNEL VertEdge = {              // Vertical edge
  { 0,  0,  0,
    -1, 1,  0,
    0,  0,  0},
    1                             // Divisor = 1
};

KERNEL HorzEdge = {              // Horizontal edge
  { 0,  -1,  0,
    0,  1,  0,
    0,  0,  0},
    1                             // Divisor = 1
};

KERNEL VertHorzEdge = {           // Vertical Horizontal edge
  { -1, 0,  0,
    0,  1,  0,
    0,  0,  0},
    1                             // Divisor = 1
};

KERNEL EdgeNorth = {              // North gradient
  { 1,  1,  1,
    1, -2,  1,
   -1, -1, -1},
    1                             // Divisor = 1
};

KERNEL EdgeNorthEast = {          // North East gradient
  { 1,  1,  1,
   -1, -2,  1,
   -1, -1,  1},
    1                             // Divisor = 1
};

KERNEL EdgeEast = {               // East gradient
  {-1,  1,  1,
   -1, -2,  1,
   -1,  1,  1},
    1                             // Divisor = 1
};

KERNEL EdgeSouthEast = {          // South East gradient
  {-1, -1,  1,
   -1, -2,  1,
    1,  1,  1},
    1                             // Divisor = 1
};

KERNEL EdgeSouth = {              // South gadient
  {-1, -1, -1,
    1, -2,  1,
    1,  1,  1},
    1                             // Divisor = 1
};

KERNEL EdgeSouthWest = {          // South West gradient
  { 1, -1, -1,
    1, -2, -1,
    1,  1,  1},
    1                             // Divisor = 1
};

KERNEL EdgeWest = {               // West gradient
  { 1,  1, -1,
    1, -2, -1,
    1,  1, -1},
    1                             // Divisor = 1
};

KERNEL EdgeNorthWest = {          // North West gradient
  { 1,  1,  1,
    1, -2, -1,
    1, -1, -1},
    1                             // Divisor = 1
};

KERNEL Lap1 = {					  // Laplace filter 1
  { 0,  1,  0,
    1, -4,  1,
    0,  1,  0},
    1                             // Divisor = 1
};

KERNEL Lap2 = {					  // Laplace filter 2
  { -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1},
    1                             // Divisor = 1
};

KERNEL Lap3 = {					  // Laplace filter 3
  { -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1},
    1                             // Divisor = 1
};

KERNEL Lap4 = {					  // Laplace filter 4
  { 1, -2, 1,
    -2, 4, -2,
    1, -2, 1},
    1                             // Divisor = 1
};

KERNEL Sobel[4] = {
	{                    // Sobel1
		{-1, 0, 1,
		 -2, 0, 2,
		 -1, 0, 1},
		1                             // Divisor = 1
	},
	{                    // Sobel2
		{-1, -2, -1,
		  0,  0,  0,
		  1,  2,  1},
		1                             // Divisor = 1
	},
	{                    // Sobel3
		{-2, -1, 0,
		 -1,  0, 1,
		  0,  1, 2},
		1                             // Divisor = 1
	},
	{                    // Sobel4
		{0, -1, -2,
		 1,  0, -1,
		 2,  1, 0},
		1                             // Divisor = 1
	}
};

KERNEL Hough[4] = {
	{                    // Hough1
		{-1, 0, 1,
		 -1, 0, 1,
		 -1, 0, 1},
		1                             // Divisor = 1
	},
	{                    // Hough2
		{-1, -1, 0,
		 -1,  0, 1,
		  0,  1, 1},
		1                             // Divisor = 1
	},
	{                    // Hough3
		{-1, -1, -1,
		  0,  0, 0,
		  1,  1, 1},
		1                             // Divisor = 1
	},
	{                    // Hough4
		{0, -1, -1,
		 1,  0, -1,
		 1,  1, 0},
		1                             // Divisor = 1
	}
};

// local use macro
#define PIXEL_OFFSET(i, j, nWidthBytes)	\
		(LONG)((LONG)(i)*(LONG)(nWidthBytes) + (LONG)(j)*3)

// local function prototype
int compare(const void *e1, const void *e2);
void DoMedianFilterDIB(int *red, int *green, int *blue, int i, int j, 
			WORD wBytesPerLine, LPBYTE lpDIBits);
void DoConvoluteDIB(int *red, int *green, int *blue, int i, int j, 
			WORD wBytesPerLine, LPBYTE lpDIBits, KERNEL *lpKernel);
BOOL ConvoluteDIB(HDIB hDib, KERNEL *lpKernel, int Strength, int nKernelNum=1);


// function body

/************************************************************************* 
 * 
 * HighPassDIB() 
 * 
 * Parameters: 
 * 
 * HDIB hDib        - objective DIB handle
 * int nAlgorithm   - specify the filter to use
 * int Strength     - operation strength set to the convolute
 * 
 * Return Value: 
 * 
 * BOOL             - True is success, else False
 * 
 * Description: 
 * 
 * High pass filtering to sharp DIB
 * 
 ************************************************************************/ 
BOOL HighPassDIB(HDIB hDib, int Strength, int nAlgorithm) 
{
	switch (nAlgorithm)
	{
	case FILTER1:
		return ConvoluteDIB(hDib, &HP1, Strength);
	case FILTER2:
		return ConvoluteDIB(hDib, &HP2, Strength);
	case FILTER3:
		return ConvoluteDIB(hDib, &HP3, Strength);
	}

	return FALSE;
}

/************************************************************************* 
 * 
 * LowPassDIB() 
 * 
 * Parameters: 
 * 
 * HDIB hDib        - objective DIB handle
 * int nAlgorithm   - specify the filter to use
 * int Strength     - operation strength set to the convolute
 * 
 * Return Value: 
 * 
 * BOOL             - True is success, else False
 * 
 * Description: 
 * 
 * Low pass filtering to blur DIB
 * 
 ************************************************************************/ 
BOOL LowPassDIB(HDIB hDib, int Strength, int nAlgorithm) 
{
	switch (nAlgorithm)
	{
	case FILTER1:
		return ConvoluteDIB(hDib, &LP1, Strength);
	case FILTER2:
		return ConvoluteDIB(hDib, &LP2, Strength);
	case FILTER3:
		return ConvoluteDIB(hDib, &LP3, Strength);
	}

	return FALSE;
}

/************************************************************************* 
 * 
 * EdgeEnhanceDIB() 
 * 
 * Parameters: 
 * 
 * HDIB hDib        - objective DIB handle
 * int nAlgorithm   - specify the filter to use
 * int Strength     - operation strength set to the convolute
 * 
 * Return Value: 
 * 
 * BOOL             - True is success, else False
 * 
 * Description: 
 * 
 * Edge enhance DIB
 * 
 ************************************************************************/ 
BOOL EdgeEnhanceDIB(HDIB hDib, int Strength, int nAlgorithm)
{
	switch (nAlgorithm)
	{
	case VERT:
		return ConvoluteDIB(hDib, &VertEdge, Strength);
	case HORZ:
		return ConvoluteDIB(hDib, &HorzEdge, Strength);
	case VERTHORZ:
		return ConvoluteDIB(hDib, &VertHorzEdge, Strength);
	case NORTH:
		return ConvoluteDIB(hDib, &EdgeNorth, Strength);
	case NORTHEAST:
		return ConvoluteDIB(hDib, &EdgeNorthEast, Strength);
	case EAST:
		return ConvoluteDIB(hDib, &EdgeEast, Strength);
	case SOUTH:
		return ConvoluteDIB(hDib, &EdgeSouth, Strength);
	case SOUTHEAST:
		return ConvoluteDIB(hDib, &EdgeSouthEast, Strength);
	case SOUTHWEST:
		return ConvoluteDIB(hDib, &EdgeSouthWest, Strength);
	case WEST:
		return ConvoluteDIB(hDib, &EdgeWest, Strength);
	case NORTHWEST:
		return ConvoluteDIB(hDib, &EdgeNorthWest, Strength);
	case LAP1:
		return ConvoluteDIB(hDib, &Lap1, Strength);
	case LAP2:
		return ConvoluteDIB(hDib, &Lap2, Strength);
	case LAP3:
		return ConvoluteDIB(hDib, &Lap3, Strength);
	case LAP4:
		return ConvoluteDIB(hDib, &Lap4, Strength);
	case SOBEL:
		return ConvoluteDIB(hDib, Sobel, Strength, 4);
	case HOUGH:
		return ConvoluteDIB(hDib, Hough, Strength, 4);
	}

	return FALSE;
}

/************************************************************************* 
 * 
 * MedianFilterDIB() 
 * 
 * Parameters: 
 * 
 * HDIB hDib        - objective DIB handle
 * 
 * Return Value: 
 * 
 * BOOL             - True is success, else False
 * 
 * Description: 
 * 
 * This is the media filtering function to DIB
 * 
 ************************************************************************/ 
BOOL MedianFilterDIB(HDIB hDib) 
{
	WaitCursorBegin();

	HDIB hNewDib = NULL;
	// we only convolute 24bpp DIB, so first convert DIB to 24bpp
	WORD wBitCount = DIBBitCount(hDib);
	if (wBitCount != 24)
		hNewDib = ConvertDIBFormat(hDib, 24, NULL);
	else
		hNewDib = CopyHandle(hDib);

	if (! hNewDib)
	{
		WaitCursorEnd();
		return FALSE;
	}

	// new DIB attributes
	WORD wDIBWidth = (WORD)DIBWidth(hNewDib);
	WORD wDIBHeight = (WORD)DIBHeight(hNewDib);
	WORD wBytesPerLine = (WORD)BytesPerLine(hNewDib);
	DWORD dwImageSize = wBytesPerLine * wDIBHeight;

	// Allocate and lock memory for filtered image data
	HGLOBAL hFilteredBits = GlobalAlloc(GHND, dwImageSize);
	if (!hFilteredBits) 
	{
		WaitCursorEnd();
		return FALSE;
	}
	LPBYTE lpDestImage = (LPBYTE)GlobalLock(hFilteredBits);

	// get bits address in DIB
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hNewDib);
	LPBYTE lpDIBits = FindDIBBits(lpDIB);

	// convolute...
	for (int i=1; i<wDIBHeight-1; i++) 
		for (int j=1; j<wDIBWidth-1; j++) 
		{
			int  red=0, green=0, blue=0; 
			DoMedianFilterDIB(&red, &green, &blue, i, j, wBytesPerLine, lpDIBits);

			LONG lOffset= PIXEL_OFFSET(i,j, wBytesPerLine);
			*(lpDestImage + lOffset++) = BOUND(blue, 0, 255);
			*(lpDestImage + lOffset++) = BOUND(green, 0, 255);
			*(lpDestImage + lOffset)   = BOUND(red, 0, 255);
		}

	// a filtered image is available in lpDestImage
	// copy it to DIB bits
	memcpy(lpDIBits, lpDestImage, dwImageSize);

	// cleanup temp buffers
	GlobalUnlock(hFilteredBits);
	GlobalFree(hFilteredBits);
	GlobalUnlock(hNewDib);

	// rebuild hDib
	HDIB hTmp = NULL;
	if (wBitCount != 24)
		hTmp = ConvertDIBFormat(hNewDib, wBitCount, NULL);
	else
		hTmp = CopyHandle(hNewDib);
	GlobalFree(hNewDib);
	DWORD dwSize = GlobalSize(hTmp);
	memcpy((LPBYTE)GlobalLock(hDib), (LPBYTE)GlobalLock(hTmp), dwSize);
	GlobalUnlock(hTmp);
	GlobalFree(hTmp);
	GlobalUnlock(hDib);
	WaitCursorEnd();

	return TRUE;
}

/************************************************************************* 
 * 
 * ConvoluteDIB() 
 * 
 * Parameters: 
 * 
 * HDIB hDib        - objective DIB handle
 * KERNEL *lpKernel - pointer of kernel used to convolute with DIB
 * int Strength     - operation strength set to the convolute
 * int nKernelNum   - kernel number used to convolute
 * 
 * Return Value: 
 * 
 * BOOL             - True is success, else False
 * 
 * Description: 
 * 
 * This is the generic convolute function to DIB
 * 
 ************************************************************************/ 
BOOL ConvoluteDIB(HDIB hDib, KERNEL *lpKernel, int Strength, int nKernelNum) 
{
	WaitCursorBegin();

	HDIB hNewDib = NULL;
	// we only convolute 24bpp DIB, so first convert DIB to 24bpp
	WORD wBitCount = DIBBitCount(hDib);
	if (wBitCount != 24)
		hNewDib = ConvertDIBFormat(hDib, 24, NULL);
	else
		hNewDib = CopyHandle(hDib);

	if (! hNewDib)
	{
		WaitCursorEnd();
		return FALSE;
	}

	// new DIB attributes
	WORD wDIBWidth = (WORD)DIBWidth(hNewDib);
	WORD wDIBHeight = (WORD)DIBHeight(hNewDib);
	WORD wBytesPerLine = (WORD)BytesPerLine(hNewDib);
	DWORD dwImageSize = wBytesPerLine * wDIBHeight;

	// Allocate and lock memory for filtered image data
	HGLOBAL hFilteredBits = GlobalAlloc(GHND, dwImageSize);
	if (!hFilteredBits) 
	{
		WaitCursorEnd();
		return FALSE;
	}
	LPBYTE lpDestImage = (LPBYTE)GlobalLock(hFilteredBits);

	// get bits address in DIB
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hNewDib);
	LPBYTE lpDIBits = FindDIBBits(lpDIB);

	// convolute...
	for (int i=1; i<wDIBHeight-1; i++) 
		for (int j=1; j<wDIBWidth-1; j++) 
		{
			int  red=0, green=0, blue=0; 

			for (int k=0; k<nKernelNum; ++k)
			{
				int r=0, g=0, b=0; 
				DoConvoluteDIB(&r, &g, &b, i, j, 
					wBytesPerLine, lpDIBits, lpKernel+k);
				if (r > red)
					red = r;
				if (g > green)
					green = g;
				if (b > blue)
					blue = b;
				//red += r; green += g; blue += b;
			}

			// original RGB value in center pixel  (j, i)
			LONG lOffset= PIXEL_OFFSET(i,j, wBytesPerLine);
			BYTE OldB = *(lpDIBits + lOffset++);
			BYTE OldG = *(lpDIBits + lOffset++);
			BYTE OldR = *(lpDIBits + lOffset);
			// When we get here, red, green and blue have the new RGB value.
			if (Strength != 10) 
			{
				// Interpolate pixel data
				red   = OldR + (((red - OldR) * Strength) / 10);
				green = OldG + (((green - OldG) * Strength) / 10);
				blue  = OldB + (((blue - OldB) * Strength) / 10);
			}

			lOffset= PIXEL_OFFSET(i,j, wBytesPerLine);
			*(lpDestImage + lOffset++) = BOUND(blue, 0, 255);
			*(lpDestImage + lOffset++) = BOUND(green, 0, 255);
			*(lpDestImage + lOffset)   = BOUND(red, 0, 255);
		}

	// a filtered image is available in lpDestImage
	// copy it to DIB bits
	memcpy(lpDIBits, lpDestImage, dwImageSize);

	// cleanup temp buffers
	GlobalUnlock(hFilteredBits);
	GlobalFree(hFilteredBits);
	GlobalUnlock(hNewDib);

	// rebuild hDib  为什么要重建。
	HDIB hTmp = NULL;
	if (wBitCount != 24)
		hTmp = ConvertDIBFormat(hNewDib, wBitCount, NULL);
	else
		hTmp = CopyHandle(hNewDib);
	GlobalFree(hNewDib);
	DWORD dwSize = GlobalSize(hTmp);
	memcpy((LPBYTE)GlobalLock(hDib), (LPBYTE)GlobalLock(hTmp), dwSize);
	GlobalUnlock(hTmp);
	GlobalFree(hTmp);
	GlobalUnlock(hDib);
	WaitCursorEnd();

	return TRUE;
}

// local function: perform convolution to DIB with a kernel
void DoConvoluteDIB(int *red, int *green, int *blue, int i, int j, 
			WORD wBytesPerLine, LPBYTE lpDIBits, KERNEL *lpKernel)
{
	BYTE b[9], g[9], r[9];
	LONG lOffset;
	
	lOffset= PIXEL_OFFSET(i-1,j-1, wBytesPerLine);
	b[0] = *(lpDIBits + lOffset++);
	g[0] = *(lpDIBits + lOffset++);
	r[0] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i-1,j, wBytesPerLine);
	b[1] = *(lpDIBits + lOffset++);
	g[1] = *(lpDIBits + lOffset++);
	r[1] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i-1,j+1, wBytesPerLine);
	b[2] = *(lpDIBits + lOffset++);
	g[2] = *(lpDIBits + lOffset++);
	r[2] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i,j-1, wBytesPerLine);
	b[3] = *(lpDIBits + lOffset++);
	g[3] = *(lpDIBits + lOffset++);
	r[3] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i,j, wBytesPerLine);
	b[4] = *(lpDIBits + lOffset++);
	g[4] = *(lpDIBits + lOffset++);
	r[4] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i,j+1, wBytesPerLine);
	b[5] = *(lpDIBits + lOffset++);
	g[5] = *(lpDIBits + lOffset++);
	r[5] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i+1,j-1, wBytesPerLine);
	b[6] = *(lpDIBits + lOffset++);
	g[6] = *(lpDIBits + lOffset++);
	r[6] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i+1,j, wBytesPerLine);
	b[7] = *(lpDIBits + lOffset++);
	g[7] = *(lpDIBits + lOffset++);
	r[7] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i+1,j+1, wBytesPerLine);
	b[8] = *(lpDIBits + lOffset++);
	g[8] = *(lpDIBits + lOffset++);
	r[8] = *(lpDIBits + lOffset);

	*red = *green = *blue = 0;
	for (int k=0; k<8; ++k)
	{
		*red   += lpKernel->Element[k]*r[k];
		*green += lpKernel->Element[k]*g[k];
		*blue  += lpKernel->Element[k]*b[k];
	}

	if (lpKernel->Divisor != 1) 
	{
		*red   /= lpKernel->Divisor;
		*green /= lpKernel->Divisor;
		*blue  /= lpKernel->Divisor;
	}

	// getoff opposite
	*red   = abs(*red);
	*green = abs(*green);
	*blue  = abs(*blue);
}

// local function: perform median filter to DIB
void DoMedianFilterDIB(int *red, int *green, int *blue, int i, int j, 
			WORD wBytesPerLine, LPBYTE lpDIBits)
{
	BYTE b[9], g[9], r[9];
	LONG lOffset;
	
	lOffset= PIXEL_OFFSET(i-1,j-1, wBytesPerLine);
	b[0] = *(lpDIBits + lOffset++);
	g[0] = *(lpDIBits + lOffset++);
	r[0] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i-1,j, wBytesPerLine);
	b[1] = *(lpDIBits + lOffset++);
	g[1] = *(lpDIBits + lOffset++);
	r[1] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i-1,j+1, wBytesPerLine);
	b[2] = *(lpDIBits + lOffset++);
	g[2] = *(lpDIBits + lOffset++);
	r[2] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i,j-1, wBytesPerLine);
	b[3] = *(lpDIBits + lOffset++);
	g[3] = *(lpDIBits + lOffset++);
	r[3] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i,j, wBytesPerLine);
	b[4] = *(lpDIBits + lOffset++);
	g[4] = *(lpDIBits + lOffset++);
	r[4] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i,j+1, wBytesPerLine);
	b[5] = *(lpDIBits + lOffset++);
	g[5] = *(lpDIBits + lOffset++);
	r[5] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i+1,j-1, wBytesPerLine);
	b[6] = *(lpDIBits + lOffset++);
	g[6] = *(lpDIBits + lOffset++);
	r[6] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i+1,j, wBytesPerLine);
	b[7] = *(lpDIBits + lOffset++);
	g[7] = *(lpDIBits + lOffset++);
	r[7] = *(lpDIBits + lOffset);

	lOffset= PIXEL_OFFSET(i+1,j+1, wBytesPerLine);
	b[8] = *(lpDIBits + lOffset++);
	g[8] = *(lpDIBits + lOffset++);
	r[8] = *(lpDIBits + lOffset);

    qsort(r, 9, 1, compare);
    qsort(g, 9, 1, compare);
    qsort(b, 9, 1, compare);

	*red   = r[0];
	*green = g[0];
	*blue  = b[0];
}

// function used to sort in the call of qsort
int compare(const void *e1, const void *e2)
{
	if (*(BYTE *)e1 < *(BYTE *)e2)
		return -1;
	if (*(BYTE *)e1 > *(BYTE *)e2)
		return 1;

	return 0;
}