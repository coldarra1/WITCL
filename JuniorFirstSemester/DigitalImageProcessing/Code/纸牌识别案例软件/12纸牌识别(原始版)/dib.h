#if !defined (__DIB_H__)
#define	__DIB_H__

#if _MSC_VER>=1000
#pragma once
#endif

//DBI.H:header file
//

////////////////////////
//CDIB class

class CDIB:public CObject{

public:
	int m_nImType;
	void close();
	void UpdateData();
	void InvalidateData();
	BYTE *m_pdata;
	BYTE *m_pR,*m_pG,*m_pB;
	void ShowDIB(CDC *,int,int,int,int,BYTE*,BITMAPINFO*);
	bool m_bLoaded;
	CDIB();
	virtual ~CDIB();
	BITMAPINFO* m_pBMI;               //BITMAPINFO pointer
	BYTE* m_pDIBData;                 //DIB data pointer
	BYTE* m_pDumpDIBData;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	CPalette *m_pPalette;


    DWORD dataBytes;
	bool SaveFile(LPCTSTR lpszFileName);
	virtual bool LoadFromFile(LPCTSTR lpszFileName);

	int GetDIBWidth()
	{
		return m_pBMI->bmiHeader.biWidth;
	}

	int GetDIBHeight()
	{
		return m_pBMI->bmiHeader.biHeight;
	}
};

////////////////////////
#endif // !defined (__DIB_H__)

