// Dib.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windowsx.h>		// especially for GlobalAllocPtr

#include "Dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(CDib, CObject, 0)

////////////////////////////////////////////////////////////////////////////
CDib::CDib()
{
	m_hDib		= NULL;
	m_hBitmap   = NULL;
	m_pPalette  = NULL;
	m_pBitmap   = NULL;
}           
                                      
CDib::~CDib()
{
	Destroy();
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
}

void CDib::Destroy()
{
	if (m_hDib != NULL)
	{
		DestroyDIB(m_hDib);
		m_hDib = NULL;
	}
}

HDIB CDib::Detach()
{
	if (m_hDib == NULL)
		return NULL;

	HDIB hDib = m_hDib;
	m_hDib = NULL;
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}

	return hDib;
}

BOOL CDib::Create(DWORD dwWidth, DWORD dwHeight)
{
	HDIB hDib = CreateDefaultDIB(dwWidth, dwHeight);
	if (! hDib)
		return FALSE;

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount)
{
	HDIB hDib = CreateDIB(dwWidth, dwHeight, wBitCount);
	if (! hDib)
		return FALSE;

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(LPBYTE lpDIB)
{
	if (lpDIB == NULL)
		return FALSE;
	
	DWORD dwSize = DIBlockSize(lpDIB);

    HDIB hDib  = GlobalAlloc(GHND, dwSize); 
    // Check that DIB handle is valid 
    if (! hDib) 
        return FALSE; 
 
    LPBYTE lpbi  = (LPBYTE)GlobalLock(hDib); 
	if (! lpbi)
        return FALSE; 
		
	CopyMemory(lpbi, lpDIB, dwSize);
	GlobalUnlock(hDib);

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(LPBYTE lpDIB,
				  WORD  wBitCount)		// bits/pixel 
{
	if (lpDIB == NULL)
		return FALSE;
	if (! Create(lpDIB))
		return FALSE;

	WORD wBits = ((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	if (wBitCount == wBits)
		return TRUE;

	HDIB hNewDib = ConvertDIBFormat(m_hDib, wBitCount, NULL); 
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap)		// DIB Section
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = DIBSectionToDIB(hBitmap); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap,		// DIB Section
				  WORD  wBitCount)		// bits/pixel 
{
	HDIB hNewDib;

	if (! hBitmap)
        return FALSE; 

	HDIB hDib = DIBSectionToDIB(hBitmap); 
    if (! hDib) 
        return FALSE; 

	DIBSECTION ds;
	GetObject(hBitmap, sizeof(DIBSECTION), &ds);

	if (wBitCount == ds.dsBmih.biBitCount)
		hNewDib = hDib;
	else
	{
		hNewDib = ConvertDIBFormat(hDib, wBitCount, NULL); 
		// cleanup hDib
		GlobalFree(hDib);
	}
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap,		// DDB bitmap
			      HPALETTE hPalette)	// DDB palette
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = BitmapToDIB(hBitmap, hPalette); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap,		// DDB bitmap
			      HPALETTE hPalette,	// DDB palette
				  WORD  wBitCount)		// bits/pixel 
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = BitmapToDIB(hBitmap, hPalette, wBitCount); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(CRect rcScreen)
{
	HDIB hDib = CopyScreenToDIB(rcScreen); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HWND hWnd, WORD fPrintArea)
{
	HDIB hDib = CopyWindowToDIB(hWnd, fPrintArea); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HWND hWnd, CRect rcClientArea)
{
	HDIB hDib = CopyClientRectToDIB(hWnd, rcClientArea); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Attach(HDIB hDib)
{
	if (hDib == NULL)
		return FALSE;
	
	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

void CDib::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	ar.Flush();
	if (ar.IsStoring())
	{
		Write(ar.GetFile());
	}
    else
    {
   		Read(ar.GetFile());
    }
}

BOOL CDib::Load(UINT uIDS, LPCSTR lpszDibType)
{                                
	LPCSTR lpszDibRes = MAKEINTRESOURCE(uIDS);

	return Load(lpszDibRes, lpszDibType);
}

BOOL CDib::Load(LPCSTR lpszDibRes, LPCSTR lpszDibType)
{                                
	HINSTANCE hInst = AfxGetInstanceHandle();
	HRSRC   hRes    = ::FindResource(hInst, lpszDibRes, lpszDibType);
	HGLOBAL hData   = ::LoadResource(hInst, hRes);

	// if resource ok?
	if (hRes == NULL || hData == NULL)
		return FALSE;

	// get resource buffer
	LPBYTE lpBuf = (LPBYTE)::LockResource(hData);
	// is DIB ?
	if (((LPBITMAPFILEHEADER)lpBuf)->bfType != DIB_HEADER_MARKER/*"BM"*/)
		return FALSE;

	// use this buffer to create CDib
	LPBYTE lpDIB = lpBuf + sizeof(BITMAPFILEHEADER);
	return Create(lpDIB);
}

BOOL CDib::Load(LPCSTR lpszDibFile)
{                                
	TRY
	{
		CFile file(lpszDibFile, CFile::modeRead|CFile::shareDenyNone);

		if (! Read(&file))
			return FALSE;
	}
	CATCH (CException, e)
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}               

BOOL CDib::Save(LPCSTR lpszDibFile)
{
	TRY
	{
		CFile file(lpszDibFile, CFile::modeCreate|CFile::modeWrite);

		if (! Write(&file))
			return FALSE;
	}
	CATCH (CException, e)
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

BOOL CDib::Read(CFile *pFile)
{
	WaitCursorBegin();

	LPBITMAPINFOHEADER lpbi;
	DWORD dwSize;
	TRY
	{
		// read DIB file header
		BITMAPFILEHEADER bmfHdr;
		pFile->Read(&bmfHdr, sizeof(BITMAPFILEHEADER));
		// is DIB file?
		if (bmfHdr.bfType != DIB_HEADER_MARKER/*"BM"*/)
		{
			WaitCursorEnd();
			return FALSE;
		}
		DWORD dwLength = pFile->GetLength();
		if (bmfHdr.bfSize != dwLength)
			bmfHdr.bfSize = dwLength;

		// read DIB buffer
		dwSize = bmfHdr.bfSize - sizeof(BITMAPFILEHEADER);
		lpbi = (LPBITMAPINFOHEADER)GlobalAllocPtr(GHND, dwSize);
		DWORD dwCount = pFile->ReadHuge(lpbi, dwSize);
		// read ok?
		if (dwCount != dwSize)
		{
			GlobalFreePtr(lpbi);
			WaitCursorEnd();
			return FALSE;
		}

		// Check to see that it's a Windows DIB -- an OS/2 DIB would cause 
		// strange problems with the rest of the DIB API since the fields 
		// in the header are different and the color table entries are 
		// smaller. 
		// 
		// If it's not a Windows DIB (e.g. if biSize is wrong), return NULL. 
	    if (lpbi->biSize != sizeof(BITMAPINFOHEADER)) 
		{
			GlobalFreePtr(lpbi);
			WaitCursorEnd();
			return FALSE;
		}
		
		// fill color num item
		int nNumColors = (UINT)lpbi->biClrUsed;
		if (nNumColors == 0) 
		{ 
			// no color table for 24-bit, default size otherwise 
	        if (lpbi->biBitCount != 24) 
		        nNumColors = 1 << lpbi->biBitCount; // standard size table 
		} 
 
		// fill in some default values if they are zero 
	    if (lpbi->biClrUsed == 0) 
		    lpbi->biClrUsed = nNumColors; 
		if (lpbi->biSizeImage == 0) 
			lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3) * lpbi->biHeight; 
 	}
	CATCH (CException, e)
	{
		GlobalFreePtr(lpbi);
		WaitCursorEnd();
		return FALSE;
	}
	END_CATCH

	// create CDib with DIB buffer
	BOOL bSuccess = Create((LPBYTE)lpbi);
	GlobalFreePtr(lpbi);
	WaitCursorEnd();

	return bSuccess;
}

BOOL CDib::Write(CFile *pFile)
{
	WaitCursorBegin();

    BITMAPFILEHEADER    bmfHdr;     // Header for Bitmap file 
    LPBITMAPINFOHEADER  lpBI;       // Pointer to DIB info structure 
    DWORD               dwDIBSize; 

	// Get a pointer to the DIB memory, the first of which contains 
    // a BITMAPINFO structure 
    lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
		WaitCursorEnd();
        return FALSE; 
	}
 
    // Check to see if we're dealing with an OS/2 DIB.  If so, don't 
    // save it because our functions aren't written to deal with these 
    // DIBs. 
    if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) 
    { 
        GlobalUnlock(m_hDib); 
		WaitCursorEnd();
        return FALSE; 
    } 
 
    // Fill in the fields of the file header 
 
    // Fill in file type (first 2 bytes must be "BM" for a bitmap) 
 
    bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM" 
 
    // Calculating the size of the DIB is a bit tricky (if we want to 
    // do it right).  The easiest way to do this is to call GlobalSize() 
    // on our global handle, but since the size of our global memory may have 
    // been padded a few bytes, we may end up writing out a few too 
    // many bytes to the file (which may cause problems with some apps, 
    // like HC 3.0). 
    // 
    // So, instead let's calculate the size manually. 
    // 
    // To do this, find size of header plus size of color table.  Since the 
    // first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains 
    // the size of the structure, let's use this. 
 
    // Partial Calculation 
 
    dwDIBSize = *(LPDWORD)lpBI + PaletteSize((LPBYTE)lpBI);   
 
    // Now calculate the size of the image 
 
    // It's an RLE bitmap, we can't calculate size, so trust the biSizeImage 
    // field 
 
    if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4)) 
        dwDIBSize += lpBI->biSizeImage; 
    else 
    { 
        DWORD dwBmBitsSize;  // Size of Bitmap Bits only 
 
        // It's not RLE, so size is Width (DWORD aligned) * Height 
 
        dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * 
                lpBI->biHeight; 
 
        dwDIBSize += dwBmBitsSize; 
 
        // Now, since we have calculated the correct size, why don't we 
        // fill in the biSizeImage field (this will fix any .BMP files which  
        // have this field incorrect). 
 
        lpBI->biSizeImage = dwBmBitsSize; 
    } 
 
 
    // Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER) 
                    
    bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER); 
    bmfHdr.bfReserved1 = 0; 
    bmfHdr.bfReserved2 = 0; 
 
    // Now, calculate the offset the actual bitmap bits will be in 
    // the file -- It's the Bitmap file header plus the DIB header, 
    // plus the size of the color table. 
     
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize + 
            PaletteSize((LPBYTE)lpBI); 
 
 	TRY
	{
	    // Write the file header 
		pFile->Write(&bmfHdr, sizeof(BITMAPFILEHEADER));
		// write DIB buffer
		pFile->WriteHuge(lpBI, dwDIBSize);
	}
	CATCH (CException, e)
	{
        GlobalUnlock(m_hDib); 
		WaitCursorEnd();
		return FALSE;
	}
	END_CATCH

	GlobalUnlock(m_hDib); 
	WaitCursorEnd();
	
	return TRUE;
}

BOOL CDib::Display(CDC* pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
 				   int xSrc, int ySrc, DWORD dwRop)
{
	if (IsRequireDither(pDC))
	{
		CRect rcDest(xDest, yDest, xDest+nWidthDest, yDest+nHeightDest);
		CRect rcSrc(xSrc, ySrc, xSrc+nWidthDest, ySrc+nHeightDest);
		return DitherDisplay(pDC, rcDest, rcSrc, dwRop);
	}

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->BitBlt( xDest, yDest, 
							nWidthDest, nHeightDest,
						    &MemDC, 
							xSrc, ySrc, 
							dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
				   int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	if (IsRequireDither(pDC))
	{
		CRect rcDest(xDest, yDest, xDest+nWidthDest, yDest+nHeightDest);
		CRect rcSrc(xSrc, ySrc, xSrc+nWidthSrc, ySrc+nHeightSrc);
		return DitherDisplay(pDC, rcDest, rcSrc, dwRop);
	}

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->StretchBlt( xDest, yDest, 
								nWidthDest, nHeightDest,
						        &MemDC, 
								xSrc, ySrc, 
								nWidthSrc, nHeightSrc, 
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Display(CDC * pDC, int x, int y, DWORD dwRop)
{
	if (IsRequireDither(pDC))
	{
		int nWidth = (int)GetWidth();
		int nHeight = (int)GetHeight();
		CRect rcDest(x, y, x+nWidth, y+nHeight);
		CRect rcSrc(0, 0, nWidth, nHeight);
		return DitherDisplay(pDC, rcDest, rcSrc, dwRop);
	}

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->BitBlt(x, y, 
								GetWidth(), GetHeight(),
								&MemDC, 
								0, 0, 
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Display(CDC* pDC, CRect rcDest, CRect rcSrc, DWORD dwRop)
{
	if (IsRequireDither(pDC))
		return DitherDisplay(pDC, rcDest, rcSrc, dwRop);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->StretchBlt( rcDest.left, rcDest.top, 
								rcDest.Width(), rcDest.Height(),
						        &MemDC, 
								rcSrc.left, rcSrc.top, 
								rcSrc.Width(), rcSrc.Height(),
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}


BOOL CDib::BuildBitmap()
{
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
		m_hBitmap = NULL;
	}
	m_hBitmap = DIBToDIBSection(m_hDib);
	if (m_hBitmap == NULL)
		return FALSE;
	m_pBitmap = new CBitmap;
	m_pBitmap->Attach(m_hBitmap);

	return TRUE;
}

BOOL CDib::BuildPalette()
{
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
	HPALETTE hPalette = CreateDIBPalette(m_hDib);
	if (hPalette == NULL)
		return FALSE;
	m_pPalette = new CPalette;
	m_pPalette->Attach(hPalette);

	return TRUE;
}

BOOL CDib::UpdateInternal()
{
	BuildPalette();
	return BuildBitmap();
}

CPalette* CDib::GetPalette()
{
	return m_pPalette;
}

CBitmap* CDib::GetBitmap()
{
	return m_pBitmap;
}

BOOL CDib::IsEmpty()
{
	if (m_hDib == NULL)
		return TRUE;

	if (! GlobalLock(m_hDib))
		return TRUE;

	GlobalUnlock(m_hDib);
	return FALSE;
}

DWORD CDib::GetCompression()
{
    LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
        return 0; 
	}
 
	DWORD dwCompression = lpBI->biCompression;
	GlobalUnlock(m_hDib);

	return dwCompression;
}

WORD CDib::GetBitCount()
{
    LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
        return 0; 
	}
 
	WORD wBitCount = lpBI->biBitCount;
	GlobalUnlock(m_hDib);

	return wBitCount;
}

LONG CDib::GetWidth()
{
	// get DIB buffer pointer
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
	if (! lpDIB)
	{
		GlobalUnlock(m_hDib);
		return 0;
	}

	LONG lWidth = (LONG)DIBWidth(lpDIB);
	GlobalUnlock(m_hDib);

	return lWidth; 
}

LONG CDib::GetHeight()
{
	// get DIB buffer pointer
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
	if (! lpDIB)
	{
		GlobalUnlock(m_hDib);
		return 0;
	}

	LONG lHeight = (LONG)DIBHeight(lpDIB);
	GlobalUnlock(m_hDib);

	return lHeight; 
}

LONG CDib::GetWidthBytes()
{
	return WIDTHBYTES((GetWidth())*((DWORD)GetBitCount()));
}

COLORREF CDib::GetPixel(LONG x, LONG y)
{
	COLORREF cColor;
	switch (GetBitCount())
	{
		case 1 :	if (1<<(7-x%8) & 
						*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)))
						cColor = RGB(255,255,255);
					else
						cColor = RGB(0,0,0);
					break;
		case 4 :	
				{
					PALETTEENTRY PaletteColors[16];
					m_pPalette->GetPaletteEntries(0, 16, PaletteColors);
					int nIndex = (*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)) & 
								   (x%2 ? 0x0f : 0xf0)) >> (x%2 ? 0 : 4);
					cColor = RGB(PaletteColors[nIndex].peRed,
								 PaletteColors[nIndex].peGreen,
								 PaletteColors[nIndex].peBlue);
				}
					break;
		case 8 :	
				{
					PALETTEENTRY PaletteColors[256];
					m_pPalette->GetPaletteEntries(0, 256, PaletteColors);
					int nIndex = *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y));
					cColor = RGB(PaletteColors[nIndex].peRed,
								 PaletteColors[nIndex].peGreen,
								 PaletteColors[nIndex].peBlue);
				}
					break;
		default:	cColor = RGB(*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)),
								 *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)+1),
								 *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)+2));
					break;
	}
	return cColor;
}

LONG CDib::GetPixelOffset(LONG x, LONG y)
{
	return (GetHeight()-y-1)*GetWidthBytes()+x/(8/GetBitCount());
}

LPBYTE CDib::GetBitsPtr()
{
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpDIB) 
	{
		GlobalUnlock(m_hDib);
		return NULL;
	}

	LPBYTE lpData = FindDIBBits(lpDIB);
	GlobalUnlock(m_hDib);

	return lpData;
}

HANDLE CDib::GetHandle()
{
	return m_hDib;
}

WORD CDib::GetColorNumber()
{
    LPBYTE lpBI = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpBI) 
	{
		GlobalUnlock(m_hDib);
		return 0;
	}
 
	WORD wColors = DIBNumColors(lpBI);
	GlobalUnlock(m_hDib);

	return wColors;
}

WORD CDib::GetPaletteSize()
{
    LPBYTE lpBI = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpBI) 
	{
		GlobalUnlock(m_hDib);
		return 0;
	}
 
	WORD wPalSize = PaletteSize(lpBI);
	GlobalUnlock(m_hDib);

	return wPalSize;
}

CDC* CDib::BeginPaint(CDC *pDC)
{
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pPaletteTmp = m_pMemDC->SelectPalette(m_pPalette, TRUE);
	m_pMemDC->RealizePalette();
	m_pBitmapTmp = (CBitmap *)m_pMemDC->SelectObject(m_pBitmap);
	return m_pMemDC;
}

void CDib::EndPaint()
{
	m_pMemDC->SelectObject(m_pBitmapTmp);
	m_pMemDC->SelectPalette(m_pPaletteTmp, TRUE);
	delete m_pMemDC;

	Create(m_hBitmap);
}

BOOL CDib::DisplayPalette(CDC* pDC, CRect rc)
{
	return ::DisplayPalette(pDC->GetSafeHdc(), &rc, (HPALETTE)m_pPalette->GetSafeHandle());
}

BOOL CDib::DisplayTransparent(CDC * pDC, int x, int y, COLORREF cTransparentColor)
{
	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	DrawTransparentBitmap(pDC->GetSafeHdc(), 
						  m_hBitmap, 
						  x, 
						  y, 
						  cTransparentColor);

	pDC->SelectPalette(pOldPal, TRUE);

	return TRUE;
}

#define UPVALUE(x, n)	((x)/((n) ? (n) : 1) + ((x)%((n) ? (n) : 1) ? 1 : 0))
BOOL CDib::DisplayFadeIn(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime)
{
	// backup DIB
	HDIB hDib = CopyHandle(m_hDib);

	// get color number
	WORD wNumColors = GetColorNumber();

	BITMAPINFO *bmi = (BITMAPINFO *)GlobalLock(m_hDib);
	BITMAPINFO *bmi0 = (BITMAPINFO *)GlobalLock(hDib);
	if (! bmi)
		return FALSE;

	BOOL bDone = FALSE;
	int nDetaR, nDetaG, nDetaB;
	// fade out
	if (wNumColors)		// There is palette
	{
		// build black image
		for (WORD i=0; i<wNumColors; ++i)
		{
			bmi->bmiColors[i].rgbRed = 0 ;
			bmi->bmiColors[i].rgbGreen = 0 ;
			bmi->bmiColors[i].rgbBlue = 0 ;
		}
		UpdateInternal();
		// display black first
		Display(pDC, x, y, SRCCOPY);

		while (! bDone)
		{
			bDone = TRUE;
			for (WORD i=0; i<wNumColors; i++)
			{
				nDetaR = UPVALUE(bmi0->bmiColors[i].rgbRed-bmi->bmiColors[i].rgbRed, nDeta);
				nDetaG = UPVALUE(bmi0->bmiColors[i].rgbGreen-bmi->bmiColors[i].rgbGreen, nDeta);
				nDetaB = UPVALUE(bmi0->bmiColors[i].rgbBlue-bmi->bmiColors[i].rgbBlue, nDeta);
				if (! Fade(nDetaR, nDetaG, nDetaB,
						 bmi0->bmiColors[i].rgbRed,
						 bmi0->bmiColors[i].rgbGreen,
						 bmi0->bmiColors[i].rgbBlue,
						 &(bmi->bmiColors[i].rgbRed),
						 &(bmi->bmiColors[i].rgbGreen),
						 &(bmi->bmiColors[i].rgbBlue)))
					 bDone = FALSE;
			}
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			//Delay(dwDelayTime);
			nDeta--;
		}
	}
	else		// No palette
	{
		// should increase the speed!
		dwDelayTime /= 10;
		// bits position
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)bmi;
		LPBYTE lpBits = (LPBYTE)lpbi + lpbi->biSize;
		LPBYTE lpBits0 = (LPBYTE)bmi0 + lpbi->biSize;
		int nDelta = WIDTHBYTES(lpbi->biBitCount*lpbi->biWidth) - lpbi->biWidth*lpbi->biBitCount/8;
		int nx, ny;

		// build black image
		for (ny=0; ny<lpbi->biHeight; ny++)
		{
			for (nx=0; nx<lpbi->biWidth; nx++)
			{
				*lpBits++ = 0;
				*lpBits++ = 0;
				*lpBits++ = 0;
			}
			lpBits += nDelta; 
		}
		lpBits = (LPBYTE)lpbi + lpbi->biSize;
		UpdateInternal();
		// display black first
		Display(pDC, x, y, SRCCOPY);

		BYTE r, g, b, r0, g0, b0;
		while (! bDone)
		{
			bDone = TRUE;
			for (ny=0; ny<lpbi->biHeight; ny++)
			{
				for (nx=0; nx<lpbi->biWidth; nx++)
				{
					b0 = (BYTE)*lpBits0++;
					g0 = (BYTE)*lpBits0++;
					r0 = (BYTE)*lpBits0++;
					b = (BYTE)*(lpBits);
					g = (BYTE)*(lpBits+1);
					r = (BYTE)*(lpBits+2);
					nDetaR = UPVALUE(r0-r, nDeta);
					nDetaG = UPVALUE(g0-g, nDeta);
					nDetaB = UPVALUE(b0-b, nDeta);
					if (! Fade(nDetaR, nDetaG, nDetaB, r0, g0, b0, &r, &g, &b))
						bDone = FALSE;
					*lpBits++ = b;
					*lpBits++ = g;
					*lpBits++ = r;
				}
				lpBits += nDelta; 
				lpBits0 += nDelta; 
			}
			lpBits = (LPBYTE)lpbi + lpbi->biSize;
			lpBits0 = (LPBYTE)bmi0 + lpbi->biSize;
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			//Delay(dwDelayTime);
			nDeta--;
		}
	}

	// cleanup 
	GlobalUnlock(m_hDib);
	GlobalUnlock(hDib);

	// restore DIB
	m_hDib = CopyHandle(hDib);
	GlobalFree(hDib);

	return TRUE;
}

BOOL CDib::DisplayFadeOut(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime)
{
	// display first
	Display(pDC, x, y, SRCCOPY);
	
	// backup DIB
	HDIB hDib = CopyHandle(m_hDib);

	// get color number
	WORD wNumColors = GetColorNumber();

	BITMAPINFO *bmi = (BITMAPINFO *)GlobalLock(m_hDib);
	if (! bmi)
		return FALSE;

	BOOL bDone = FALSE;
	int nDetaR, nDetaG, nDetaB;
	// fade out
	if (wNumColors)		// There is palette
	{
		while (! bDone)
		{
			bDone = TRUE;
			for (WORD i=0; i<wNumColors; i++)
			{
				nDetaR = -1*UPVALUE(bmi->bmiColors[i].rgbRed, nDeta);
				nDetaG = -1*UPVALUE(bmi->bmiColors[i].rgbGreen, nDeta);
				nDetaB = -1*UPVALUE(bmi->bmiColors[i].rgbBlue, nDeta);
				if (! Fade(nDetaR, nDetaG, nDetaB,
						 0, 0, 0,
						 &(bmi->bmiColors[i].rgbRed),
						 &(bmi->bmiColors[i].rgbGreen),
						 &(bmi->bmiColors[i].rgbBlue)))
					 bDone = FALSE;
			}
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			//Delay(dwDelayTime);
			nDeta--;
		}
	}
	else		// No palette
	{
		// should increase the speed!
		dwDelayTime /= 10;
		// bits position
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)bmi;
		LPBYTE lpBits = (LPBYTE)lpbi + lpbi->biSize;
		int nDelta = WIDTHBYTES(lpbi->biBitCount*lpbi->biWidth) - lpbi->biWidth*lpbi->biBitCount/8;

		BYTE r, g, b;
		int nx, ny;
		while (! bDone)
		{
			bDone = TRUE;
			for (ny=0; ny<lpbi->biHeight; ny++)
			{
				for (nx=0; nx<lpbi->biWidth; nx++)
				{
					b = (BYTE)*(lpBits);
					g = (BYTE)*(lpBits+1);
					r = (BYTE)*(lpBits+2);
					nDetaR = -1*UPVALUE(r, nDeta);
					nDetaG = -1*UPVALUE(g, nDeta);
					nDetaB = -1*UPVALUE(b, nDeta);
					if (! Fade(nDetaR, nDetaG, nDetaB, 0, 0, 0, &r, &g, &b))
						bDone = FALSE;
					*lpBits++ = b;
					*lpBits++ = g;
					*lpBits++ = r;
				}
				lpBits += nDelta; 
			}
			lpBits = (LPBYTE)lpbi + lpbi->biSize;
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			//Delay(dwDelayTime);
			nDeta--;
		}
	}

	// cleanup 
	GlobalUnlock(m_hDib);

	// restore DIB
	m_hDib = CopyHandle(hDib);
	GlobalFree(hDib);

	return TRUE;
}

BOOL CDib::DisplayMosaicIn(CDC *pDC, int xx, int yy, int nTileSize, DWORD dwDelayTime, DWORD dwRop)
{
    // count the number of dwTileNum
	DWORD dwTileNum=(GetWidth()/nTileSize + ((GetWidth() % nTileSize) ? 1:0))*
					(GetHeight()/nTileSize + ((GetHeight() % nTileSize) ? 1:0));
	// allocate tile array
	POINT *point = new POINT[dwTileNum];
	if (point == NULL)
		return FALSE;

	// initialize the tile array
	LONG x=0, y=0;
	for (DWORD i=0;i<dwTileNum;++i) 
	{
		point[i].x=x;
		point[i].y=y;

		x+=nTileSize;
		if (x >= GetWidth()) 
		{
			x=0;
            y+=nTileSize;
		}
	}

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();
	
	double fMax = RAND_MAX;
	BOOL  bDone = FALSE;
	while (! bDone)
	{
		DWORD n = (DWORD)((double)dwTileNum*(double)((double)rand()/fMax));
		x = point[n].x;
		y = point[n].y;

		pDC->BitBlt(xx+x,
					yy+y,
					nTileSize,
					nTileSize,
					&MemDC,
					x,
					y,
					dwRop);

		dwTileNum--;
		bDone = !dwTileNum;

		point[n].x = point[dwTileNum].x;
		point[n].y = point[dwTileNum].y;
		//Delay(dwDelayTime);
	}

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	delete[] point;

	return TRUE;
}

BOOL CDib::DisplayMosaicOut(CDC *pDC, int xx, int yy, int nTileSize, DWORD dwDelayTime)
{
	// display dib first
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	pDC->BitBlt(xx,	yy,
				GetWidth(),	GetHeight(),
				&MemDC,
				0, 0,
				SRCCOPY);

    // count the number of dwTileNum
	DWORD dwTileNum=(GetWidth()/nTileSize + ((GetWidth() % nTileSize) ? 1:0))*
					(GetHeight()/nTileSize + ((GetHeight() % nTileSize) ? 1:0));
	// allocate tile array
	POINT *point = new POINT[dwTileNum];
	if (point == NULL)
		return FALSE;

	// initialize the tile array
	LONG x=0, y=0;
	for (DWORD i=0;i<dwTileNum;++i) 
	{
		point[i].x=x;
		point[i].y=y;

		x+=nTileSize;
		if (x >= GetWidth()) 
		{
			x=0;
            y+=nTileSize;
		}
	}

	CBrush brush(GetSysColor(COLOR_WINDOW));
	CBrush* oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,GetSysColor(COLOR_WINDOW));
    CPen* oldpen = pDC->SelectObject(&pen);
	
	double fMax = RAND_MAX;
	BOOL bDone = FALSE;
	while (! bDone)
	{
		DWORD n = (DWORD)((double)dwTileNum*(double)((double)rand()/fMax));
		x = point[n].x;
		y = point[n].y;

		pDC->Rectangle(	xx+x,
						yy+y,
						xx+x+nTileSize+1,
						yy+y+nTileSize+1);

		dwTileNum--;
		bDone = !dwTileNum;

		point[n].x = point[dwTileNum].x;
		point[n].y = point[dwTileNum].y;
		//Delay(dwDelayTime);
	}

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);
	pDC->SelectObject(oldbrush);
    pDC->SelectObject(oldpen);

	delete[] point;

	return TRUE;
}

BOOL CDib::Display(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime, DWORD dwRop)
{
	if (nEffect == EFFECT_FADE)
		return DisplayFadeIn(pDC, x, y, nDeta, dwDelayTime);
	else if (nEffect == EFFECT_MOSAIC)
		return DisplayMosaicIn(pDC, x, y, nDeta, dwDelayTime, dwRop);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	LONG i = 0;
	BOOL bDone = FALSE;
	while (! bDone)
	{
		switch (nEffect)
		{
		case EFFECT_SCANDOWN:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
            pDC->BitBlt(x, 
						y+i,
                        GetWidth(),
						nDeta,
						&MemDC,
                        0,
						i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_SCANUP:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
            pDC->BitBlt(x, 
						y+GetHeight()-i,
                        GetWidth(),
						nDeta,
						&MemDC,
                        0,
						GetHeight()-i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_SCANRIGHT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
            pDC->BitBlt(x+i, 
						y,
						nDeta,
                        GetHeight(),
						&MemDC,
						i,
                        0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_SCANLEFT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
            pDC->BitBlt(x+GetWidth()-i, 
						y,
						nDeta,
                        GetHeight(),
						&MemDC,
						GetWidth()-i,
                        0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VSPLITSCAN:
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y+i,
						GetWidth(),
						nDeta,
						&MemDC,
						0,
						i,
						dwRop);
			pDC->BitBlt(x,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						0,
						GetHeight()-i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_HSPLITSCAN:
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x+i,
						y,
						nDeta,
						GetHeight(),
						&MemDC,
						i,
						0,
						dwRop);
			pDC->BitBlt(x+GetWidth()-i,
						y,
						nDeta,
						GetHeight(),
						&MemDC,
						GetWidth()-i,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVEDOWN:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						GetWidth(),
						i+nDeta,
						&MemDC,
						0,
						GetHeight()-i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVEUP:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						0,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVERIGHT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						i+nDeta,
						GetHeight(),
						&MemDC,
						GetWidth()-i,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVELEFT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x+GetWidth()-i,
						y,
						i,
						GetHeight(),
						&MemDC,
						0,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VSPLITMOVE:
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						GetWidth(),
						i+nDeta,
						&MemDC,
						0,
						GetHeight()/2-i,
						dwRop);
			pDC->BitBlt(x,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						0,
						GetHeight()/2,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_HSPLITMOVE:
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						i+nDeta,
						GetHeight(),
						&MemDC,
						GetWidth()/2-i,
						0,
						dwRop);
			pDC->BitBlt(x+GetWidth()-i,
						y,
						i,
						GetHeight(),
						&MemDC,
						GetWidth()/2,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VCROSSMOVE:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						GetWidth()/2,
						i+nDeta,
						&MemDC,
						0,
						GetHeight()-i,
						dwRop);
			pDC->BitBlt(x+GetWidth()/2,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						GetWidth()/2,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_HCROSSMOVE:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						i+nDeta,
						GetHeight()/2,
						&MemDC,
						GetWidth()-i,
						0,
						dwRop);
			pDC->BitBlt(x+GetWidth()-i,
						y+GetHeight()/2,
						i,
						GetHeight()/2,
						&MemDC,
						0,
						GetHeight()/2,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VRASTER:
		{
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+j,
							y,
							nDeta,
							i+1,
							&MemDC,
							j,
							GetHeight()-i,
							dwRop);
				j += nDeta;
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+j,
							y+GetHeight()-i,
							nDeta,
							i,
							&MemDC,
							j,
							0,
							dwRop);
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HRASTER:
		{
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x,
							y+j,
							i+1,
							nDeta,
							&MemDC,
							GetWidth()-i,
							j,
							dwRop);
				j += nDeta;
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+GetWidth()-i,
							y+j,
							i,
							nDeta,
							&MemDC,
							0,
							j,
							dwRop);
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HBLIND:
		{
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetHeight(); j+=nDeta)
				pDC->BitBlt(x,
							y+j,
							GetWidth(),
							1,
							&MemDC,
							0,
							j,
							dwRop);
			i++;
			break;
		}
		case EFFECT_VBLIND:
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetWidth(); j+=nDeta)
				pDC->BitBlt(x+j,
							y,
							1,
							GetHeight(),
							&MemDC,
							j,
							0,
							dwRop);
			i++;
			break;
		}  // end of switch
		//Delay(dwDelayTime);
	}	// end of while

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return TRUE;
}

BOOL CDib::Clear(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime)
{
	if (nEffect == EFFECT_FADE)
		return DisplayFadeOut(pDC, x, y, nDeta, dwDelayTime);
	else if (nEffect == EFFECT_MOSAIC)
		return DisplayMosaicOut(pDC, x, y, nDeta, dwDelayTime);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	pDC->BitBlt(x,
				y,
				GetWidth(),
				GetHeight(),
				&MemDC,
				0,
				0,
				SRCCOPY);

	CBrush brush(GetSysColor(COLOR_WINDOW));
	CBrush* oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,GetSysColor(COLOR_WINDOW));
    CPen* oldpen = pDC->SelectObject(&pen);

	LONG i = 0;
	BOOL bDone = FALSE;
	while (! bDone)
	{
		switch (nEffect)
		{
		case EFFECT_SCANDOWN:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->Rectangle(x, 
						   y+i,
						   x+GetWidth(), 
						   y+nDeta);
			i += nDeta;
			break;
		case EFFECT_SCANUP:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->Rectangle(x, 
						   y+GetHeight()-i,
						   x+GetWidth(), 
						   y+GetHeight()-i+nDeta);
			i += nDeta;
			break;
		case EFFECT_SCANRIGHT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->Rectangle(x+i,
						   y,
						   x+nDeta, 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_SCANLEFT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->Rectangle(x+GetWidth()-i, 
						   y,
						   x+GetWidth()-i+nDeta, 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_VSPLITSCAN:
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->Rectangle(x, 
						   y+i,
						   x+GetWidth(), 
						   y+i+nDeta);
			pDC->Rectangle(x, 
						   y+GetHeight()-i,
						   x+GetWidth(), 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_HSPLITSCAN:
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->Rectangle(x+i, 
						   y,
						   x+i+nDeta, 
						   y+GetHeight());
			pDC->Rectangle(x+GetWidth()-i,
						   y,
						   x+GetWidth(), 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_MOVEDOWN:
		{
			i += nDeta;
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			//x dest
						y+i,		//y dest
      					GetWidth(),		//width
						GetHeight()-i,	//depth
						&MemDC,
						0,				//x source
						0,			//y source
						SRCCOPY);

			pDC->Rectangle(x, y+i-nDeta,
						   x+GetWidth(), y+i);
			break;
		}
		case EFFECT_MOVEUP:
		{
			i += nDeta;
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			//x dest
						y,		//y dest
	      				GetWidth(),		//width
						GetHeight()-i,	//depth
						&MemDC,
						0,				//x source
						i,			//y source
						SRCCOPY);

			pDC->Rectangle( x,
							y+GetHeight()-i,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_MOVERIGHT:
		{
			i += nDeta;
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x+i,  			//x dest
						y,		//y dest
      					GetWidth()-i,		//width
						GetHeight(),	//depth
						&MemDC,
						0,				//x source
						0,			//y source
						SRCCOPY);

			pDC->Rectangle(x+i-nDeta, y,
						   x+i, y+GetHeight());
			break;
		}
		case EFFECT_MOVELEFT:
		{
			i += nDeta;
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			//x dest
						y,		//y dest
	      				GetWidth()-i,		//width
						GetHeight(),	//depth
						&MemDC,
						i,			//y source
						0,				//x source
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()-i,
							y,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_VCROSSMOVE:
		{
			i += nDeta;
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			//x dest
						y+i,		//y dest
      					GetWidth()/2,		//width
						GetHeight()-i,	//depth
						&MemDC,
						0,				//x source
						0,			//y source
						SRCCOPY);

			pDC->Rectangle(x, y+i-nDeta,
						   x+GetWidth()/2, y+i);

			pDC->BitBlt(x+GetWidth()/2,  			//x dest
						y,		//y dest
	      				GetWidth(),		//width
						GetHeight()-i,	//depth
						&MemDC,
						GetWidth()/2,				//x source
						i,			//y source
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()/2,
							y+GetHeight()-i,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_HCROSSMOVE:
		{
			i += nDeta;
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x+i,  			//x dest
						y,		//y dest
      					GetWidth()-i,		//width
						GetHeight()/2,	//depth
						&MemDC,
						0,				//x source
						0,			//y source
						SRCCOPY);

			pDC->Rectangle(x+i-nDeta, y,
						   x+i, y+GetHeight()/2);
	
			pDC->BitBlt(x,  			//x dest
						y+GetHeight()/2,	//depth
	      				GetWidth()-i,		//width
						GetHeight(),	//depth
						&MemDC,
						i,			//y source
						GetHeight()/2,	//depth
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()-i,
							y+GetHeight()/2,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_VSPLITMOVE:
		{
			i += nDeta;
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			//x dest
						y,		//y dest
			  			GetWidth(),		//width
						GetHeight()/2-i,	//depth
						&MemDC,
						0,				//x source
						i,			//y source
						SRCCOPY);

			pDC->BitBlt(x,  			//x dest
						y+GetHeight()/2+i,		//y dest
      					GetWidth(),		//width
						GetHeight()/2-i,	//depth
						&MemDC,
						0,				//x source
						GetHeight()/2,			//y source
						SRCCOPY);

			pDC->Rectangle( x,
							y+GetHeight()/2-i,
							x+GetWidth(),
							y+GetHeight()/2+i+1);
			break;
		}
		case EFFECT_HSPLITMOVE:
		{
			i += nDeta;
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			//x dest
						y,		//y dest
	      				GetWidth()/2-i,		//width
						GetHeight(),	//depth
						&MemDC,
						i,			//y source
						0,				//x source
						SRCCOPY);

			pDC->BitBlt(x+GetWidth()/2+i,  			//x dest
						y,		//y dest
      					GetWidth()/2-i,		//width
						GetHeight(),	//depth
						&MemDC,
						GetWidth()/2,				//x source
						0,			//y source
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()/2-i,
							y,
							x+GetWidth()/2+i+1,
							y+GetHeight());
			break;
		}
		case EFFECT_VRASTER:
		{
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+j,  			//x dest
							y+i,		//y dest
      						nDeta,		//width
							GetHeight()-i,	//depth
							&MemDC,
							j,				//x source
							0,			//y source
							SRCCOPY);

				pDC->Rectangle(x+j, y+i-1,
							   x+j+nDeta, y+i);
				j += nDeta;
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
	
				pDC->BitBlt(x+j,  			//x dest
							y,		//y dest
				  			nDeta,		//width
							GetHeight()-i,	//depth
							&MemDC,
							j,			//y source
							i,				//x source
							SRCCOPY);

				pDC->Rectangle( x+j,
								y+GetHeight()-i,
								x+j+nDeta,
								y+GetHeight());
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HRASTER:
		{
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+i,  			//x dest
							y+j,		//y dest
      						GetWidth()-i,		//width
							nDeta,	//depth
							&MemDC,
							0,				//x source
							j,			//y source
							SRCCOPY);
				pDC->Rectangle(x+i-1, y+j,
							   x+i, y+j+nDeta);
				j += nDeta;
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x,  			//x dest
							y+j,		//y dest
				  			GetWidth()-i,		//width
							nDeta,	//depth
							&MemDC,
							i,			//y source
							j,				//x source
							SRCCOPY);
				pDC->Rectangle( x+GetWidth()-i,
								y+j,
								x+GetWidth(),
								y+j+nDeta);
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HBLIND:
		{
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetHeight(); j+=nDeta)
				pDC->Rectangle( x,
								y+j,
								x+GetWidth(),
								y+j+1);
			i++;
			break;
		}
		case EFFECT_VBLIND:
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetWidth(); j+=nDeta)
				pDC->Rectangle( x+j,
								y,
								x+j+1,
								y+GetHeight());
			i++;
			break;
		}	// end of switch
		//Delay(dwDelayTime);
	}	// end of while

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return TRUE;
}

HDIB CDib::CopyRect(CRect rc)
{
	return CropDIB(m_hDib, rc);
}

BOOL CDib::CutRect(CRect rc)
{
	HDIB hNewDib = CutDIB(m_hDib, rc);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::MergeDib(HDIB hDib, CPoint ptTopLeft)
{
	POINT pt;
	pt.x = ptTopLeft.x;
	pt.y = ptTopLeft.y;
	HDIB hNewDib = MergeDIB(m_hDib, hDib, pt);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::	Crop(CRect rc)
{
	HDIB hNewDib = CropDIB(m_hDib, rc);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::Rotate90()
{
	HDIB hNewDib = RotateDIB(m_hDib);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::Rotate180()
{
	HDIB h = RotateDIB(m_hDib);
	if (! h)
		return FALSE;
	HDIB hNewDib = RotateDIB(h);
	DestroyDIB(h);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::Rotate270()
{
	HDIB h1 = RotateDIB(m_hDib);
	if (! h1)
		return FALSE;
	HDIB h2 = RotateDIB(h1);
	DestroyDIB(h1);
	if (! h2)
		return FALSE;
	HDIB hNewDib = RotateDIB(h2);
	DestroyDIB(h2);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::FlipHorz()
{
	HDIB hNewDib = FlipHorzDIB(m_hDib);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::FlipVert()
{
	HDIB hNewDib = FlipVertDIB(m_hDib);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::	ChangeImageSize(int nWidth, int nHeight)
{
	HDIB hNewDib = ChangeDIBSize(m_hDib, nWidth, nHeight);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::Zoom(double fRatioX, double fRatioY)
{
	int nWidth = (int)(fRatioX * (double)GetWidth());
	int nHeight = (int)(fRatioY * (double)GetHeight());

	HDIB hNewDib = ChangeDIBSize(m_hDib, nWidth, nHeight);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::	ChangeCanvasSize(int nWidth, int nHeight, int nPosition)
{
	HDIB hNewDib = ChangeDIBCanvasSize(m_hDib, nWidth, nHeight, nPosition);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::IsRequireDither(CDC* pDC)
{
	// if device can not display DIB color, dithering DIB
	if (GetBitCount() == 24 && 
		pDC->GetDeviceCaps(BITSPIXEL) <= 8)
		return TRUE;

	return FALSE;
}

BOOL CDib::DitherDisplay(CDC* pDC, CRect rcDest, CRect rcSrc, DWORD dwRop)
{
	return DitherDisplayDIB(pDC->GetSafeHdc(), 
							rcDest, 
							m_hDib, 
							rcSrc, 
							dwRop);
}

BOOL CDib::AdjustColor(int nColorModel, int v1, int v2, int v3)
{
	if (! AdjustDIBColor(m_hDib, nColorModel, v1, v2, v3))
		return FALSE;

	return UpdateInternal();
}

BOOL CDib::AdjustBrightness(int v)
{
	if (! AdjustDIBBrightness(m_hDib, v))
		return FALSE;

	return UpdateInternal();
}

BOOL CDib::AdjustContrast(int v)
{
	if (! AdjustDIBContrast(m_hDib, v))
		return FALSE;

	return UpdateInternal();
}

BOOL CDib::SeparateRGB(int nIndex)
{
	HDIB hNewDib = SeparateRGBfromDIB(m_hDib, nIndex);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::FilteRGB(int nIndex)
{
	HDIB hNewDib = FilteRGBfromDIB(m_hDib, nIndex);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::ColorQuantize(int nColorBits)
{
	HDIB hNewDib;

	if (nColorBits > 8)
		hNewDib = ConvertDIBFormat(m_hDib, nColorBits, NULL); 
	else
	{
		int nColors = 1<<nColorBits;
		hNewDib = ColorQuantizeDIB(m_hDib, nColorBits, nColors);
	}

	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	
	return UpdateInternal();
}

BOOL CDib::ChangeToGrayscale(int nMethod, double fRedWeight, double fGreenWeight, double fBlueWeight)
{
	HPALETTE hPal = ConvertToGrayscale(m_hDib, nMethod, fRedWeight, fGreenWeight, fBlueWeight);
	if (hPal == NULL)
		return FALSE;

	// set new palette
	if (m_pPalette != NULL)
		delete m_pPalette;

	m_pPalette = new CPalette;
	m_pPalette->Attach(hPal);

	// rebuild bitmap
	return UpdateInternal();
}

BOOL CDib::HighPass(int Strength, int nAlgorithm)
{
	if (! HighPassDIB(m_hDib, Strength, nAlgorithm))
		return FALSE;

	// return
	return UpdateInternal();
}

BOOL CDib::LowPass(int Strength, int nAlgorithm)
{
	if (! LowPassDIB(m_hDib, Strength, nAlgorithm))
		return FALSE;

	// return
	return UpdateInternal();
}

BOOL CDib::EdgeEnhance(int Strength, int nAlgorithm)
{
	if (! EdgeEnhanceDIB(m_hDib, Strength, nAlgorithm))
		return FALSE;

	// return
	return UpdateInternal();
}

BOOL CDib::MedianFilter()
{
	if (! MedianFilterDIB(m_hDib))
		return FALSE;

	// return
	return UpdateInternal();
}

BOOL CDib::ConvertFormat(WORD wBitCount)
{
	if (IsEmpty())
		return FALSE;

	if (GetBitCount() == wBitCount)
		return TRUE;

	HDIB hNewDib = ConvertDIBFormat(m_hDib, wBitCount, NULL); 
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

BYTE CDib::GetPixel8(LONG x, LONG y)
{
	BYTE result;
	switch (GetBitCount())
	{
		case 1 :	result = 0;
					break;
		case 4 :	result = 0;
					break;
		case 8 :	
				{
					result = *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y));
				}
					break;
		default:	result = 0;
					break;
	}
	return result;
}

BOOL CDib::SetPixel8(LONG x, LONG y, BYTE value)
{
	if(GetBitCount() != 8)
		return false;

	else
	{
		*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)) = value;
		return true;
	}
}
