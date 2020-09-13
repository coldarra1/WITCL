/*#include "stdafx.h"
#include "cdib.h"
#include "windowsx.h"
#include "math.h"
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

CDib::CDib()
{
	size=0;
}

CDib::~CDib()
{
    GlobalFreePtr(m_pBitmapInfo);
}

void CDib::LoadFile(const char* dibFileName)
{
   strcpy(m_fileName,dibFileName);
    CFile dibFile(m_fileName, CFile::modeRead);
    dibFile.Read((void*)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
    if (bitmapFileHeader.bfType == 0x4d42)///////bmp位图
    {
        DWORD fileLength = dibFile.GetLength(); //////////文件大小   
         size = fileLength -sizeof(BITMAPFILEHEADER);//////////出去文件头之后文件大小
         pDib =(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, size);/////////指向文件头+1
        dibFile.Read((void*)pDib, size);//////////读入内存
        dibFile.Close();/////文件对象关闭
        m_pBitmapInfo = (BITMAPINFO*) pDib;/////////////强制转换下
        m_pBitmapInfoHeader = (BITMAPINFOHEADER*) pDib;///强制转换下
        m_pRGB = (RGBQUAD*)(pDib +
			m_pBitmapInfoHeader->biSize);////////////m_RGB指针位置
        int m_numberOfColors = GetNumberOfColors();///////颜色值
        if (m_pBitmapInfoHeader->biClrUsed == 0)
            m_pBitmapInfoHeader->biClrUsed =
			    m_numberOfColors;
        DWORD colorTableSize = m_numberOfColors *
            sizeof(RGBQUAD);
        m_pData = pDib + m_pBitmapInfoHeader->biSize
            + colorTableSize;/////数据区
		if (m_pRGB == (RGBQUAD*)m_pData) // No color table
			m_pRGB = NULL;
        m_pBitmapInfoHeader->biSizeImage = GetSize();
		m_valid = TRUE;
    }    
    else
    {
        m_valid = FALSE;
        AfxMessageBox("This isn't a bitmap file!");
    }
}

BOOL CDib::IsValid()
{
    return m_valid;
}
        
char* CDib::GetFileName()
{
    return m_fileName;
}
        
UINT CDib::GetWidth()
{
    return (UINT) m_pBitmapInfoHeader->biWidth;
}
        
UINT CDib::GetHeight()
{
    return (UINT) m_pBitmapInfoHeader->biHeight;
}
        
DWORD CDib::GetSize()
{
    if (m_pBitmapInfoHeader->biSizeImage != 0)
        return m_pBitmapInfoHeader->biSizeImage;
	else
    {
        DWORD height = (DWORD) GetHeight();
        DWORD width = (DWORD) GetWidth();
        return height * width;
    }
}

UINT CDib::GetNumberOfColors()
{
	int numberOfColors;

    if ((m_pBitmapInfoHeader->biClrUsed == 0) &&
          (m_pBitmapInfoHeader->biBitCount < 9))
	{
		switch (m_pBitmapInfoHeader->biBitCount)
		{
		    case 1: numberOfColors = 2; break;
		    case 4: numberOfColors = 16; break;
		    case 8: numberOfColors = 256;
		}
	}
    else
		numberOfColors = (int) m_pBitmapInfoHeader->biClrUsed;

    return numberOfColors;
}
    
BYTE* CDib::GetData()
{
    return m_pData;
}

RGBQUAD* CDib::GetRGB()
{
    return m_pRGB;
}

BITMAPINFO* CDib::GetInfo()
{
    return m_pBitmapInfo;
}

WORD CDib::PaletteSize(LPBYTE lpDIB) 
{ 
    return (DIBNumColors(lpDIB) * sizeof(RGBTRIPLE)); 
} 

WORD CDib::DIBNumColors(LPBYTE lpDIB) 
{ 
    WORD wBitCount;  // DIB bit count 
    wBitCount = ((LPBITMAPCOREHEADER)lpDIB)->bcBitCount; 
    switch (wBitCount) 
    { 
        case 1: 
            return 2; 
        case 4: 
            return 16; 
        case 8: 
            return 256; 
        default: 
            return 0; 
    } 
} 

void CDib::SaveFile(const CString filename)
{ 
   strcpy(m_fileName,filename);
    CFile dibFile(m_fileName, CFile::modeCreate|CFile::modeWrite);
    dibFile.Write((void*)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
    dibFile.Write((void*)pDib, size);
    dibFile.Close();

}

bool CDib::Open(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
/*	CFile file;
	int nBmpFileHeaderSize;

	Close();

	//drawdibopen initialize the diradib library and 
	//returns a handle for all drawdib operations
	//if(!(m_hDrawDib=DrawDibOpen()))
	//	goto exit;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeRead | CFile::typeBinary))
		goto exit;

	if(file.Read((void *)&bitmapFileHeader,nBmpFileHeaderSize)!=(UINT)nBmpFileHeaderSize)
		goto failure;

	//validate the DIB file header by checking the first
	//two characters for the signature "BM"
	if(bitmapFileHeader.bfType!=*((WORD *)"BM"))
		goto failure;

	//allocate a big chuck of global memory to store the DIB
	mpDib=(BYTE *)new char [bitmapFileHeader.bfSize-nBmpFileHeaderSize];

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.ReadHuge(m_pDib,bitmapFileHeader.bfSize-nBmpFileHeaderSize);

	if(((BITMAPINFOHEADER *)m_pDib)->biSizeImage==0)
	{
		//the application that create this bitmap didn't fill
		//in the biSizeImage field. Let's fill it
		//in even though the DrawDib * functions don't need it.
		BITMAPINFOHEADER *pDib=(BITMAPINFOHEADER *)m_pDib;

		//scan lines must be DWord aligned, hence the strange bit stuff
		pDib->biSizeImage=((((pDib->biWidth*pDib->biBitCount)+31)&~31)>>3)*pDib->biHeight;
	}

	m_pDibBits=GetBits();

	//file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	Close();*/
//	return FALSE;

//	return true;
//}
/*void CDib::Close()
{
	if(this->m_hDrawDib!=NULL)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib=NULL;
	}

	if(this->m_pDib!=NULL)
	{
		delete m_pDib;
		m_pDib=NULL;
	}
}*/


// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "CDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
	this->m_hDrawDib=NULL;
	this->m_pDib=NULL;
}

CDib::~CDib()
{
	Close();
}

void CDib::Draw(CDC *pDC,int nWidth, int nHeight)
{
	if(m_pDib!=NULL)
	{
	ASSERT(IsValid());
	DrawDibRealize(this->m_hDrawDib,pDC->GetSafeHdc(),TRUE);
	DrawDibDraw(this->m_hDrawDib,pDC->GetSafeHdc(),
				0,  //desktop left
				0,  //desktop top
				nWidth,
				nHeight,
				(BITMAPINFOHEADER *)m_pDib,
				(LPVOID) GetBits(),
				0,  //source left
				0,  //source top
				((BITMAPINFOHEADER *)m_pDib)->biWidth,
				((BITMAPINFOHEADER *)m_pDib)->biHeight,
				DDF_BACKGROUNDPAL);
	}
}

CSize CDib::GetSize()
{
	return CSize(((BITMAPINFOHEADER *)m_pDib)->biWidth,
				 ((BITMAPINFOHEADER *)m_pDib)->biHeight);	
}

LONG CDib::GetWidth()
{
	return ((BITMAPINFOHEADER *)m_pDib)->biWidth;
}

LONG CDib::GetHeight()
{
	return	((BITMAPINFOHEADER *)m_pDib)->biHeight;
}

void CDib::Close()
{
	if(this->m_hDrawDib!=NULL)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib=NULL;
	}

	if(this->m_pDib!=NULL)
	{
		delete m_pDib;
		m_pDib=NULL;
	}
}

BOOL CDib::Open(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
	CFile file;
	int nBmpFileHeaderSize;

	Close();

	//drawdibopen initialize the diradib library and 
	//returns a handle for all drawdib operations
	if(!(m_hDrawDib=DrawDibOpen()))
		goto exit;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeRead | CFile::typeBinary))
		goto exit;

	if(file.Read((void *)&bmpFileHeader,nBmpFileHeaderSize)!=(UINT)nBmpFileHeaderSize)
		goto failure;

	//validate the DIB file header by checking the first
	//two characters for the signature "BM"
	if(bmpFileHeader.bfType!=*((WORD *)"BM"))
		goto failure;

	//allocate a big chuck of global memory to store the DIB
	m_pDib=(BYTE *)new char [bmpFileHeader.bfSize-nBmpFileHeaderSize];

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.ReadHuge(m_pDib,bmpFileHeader.bfSize-nBmpFileHeaderSize);

	if(((BITMAPINFOHEADER *)m_pDib)->biSizeImage==0)
	{
		//the application that create this bitmap didn't fill
		//in the biSizeImage field. Let's fill it
		//in even though the DrawDib * functions don't need it.
		BITMAPINFOHEADER *pDib=(BITMAPINFOHEADER *)m_pDib;

		//scan lines must be DWord aligned, hence the strange bit stuff
		pDib->biSizeImage=((((pDib->biWidth*pDib->biBitCount)+31)&~31)>>3)*pDib->biHeight;
	}

	m_pDibBits=GetBits();

	file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	Close();
	return FALSE;
}

BOOL CDib::Save(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
	CFile file;
	int nBmpFileHeaderSize;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		goto exit;

	file.Write(&bmpFileHeader,nBmpFileHeaderSize); 

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.WriteHuge(m_pDib,bmpFileHeader.bfSize-nBmpFileHeaderSize);

	file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	return FALSE;
}

BYTE * CDib::GetBits()
{
	//the size of the color map is determined by the number
	//of RGBQUAD structures presend.
	//it also depends on the bit_depth of the Dib
	DWORD dwNumColors,dwColorTableSize;
	BITMAPINFOHEADER *lpDib=(BITMAPINFOHEADER *)m_pDib;

	WORD wBitCount=lpDib->biBitCount;

	if(lpDib->biSize>=36)
		dwNumColors=lpDib->biClrUsed;
	else
		dwNumColors=0;

	if(dwNumColors==0)
	{
		if(wBitCount!=24)
			dwNumColors=1L<<wBitCount;
		else 
			dwNumColors=0;
	}

	dwColorTableSize=dwNumColors*sizeof(RGBQUAD);

	return m_pDib+lpDib->biSize+dwColorTableSize;
}

int CDib::GetBiBitCount()
{
	if(m_pDib!=NULL)
		return ((BITMAPINFOHEADER *)m_pDib)->biBitCount; 
	return 0;
}
