// CDib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__1A2F121B_2FC3_4D06_9B9A_D8CF4F0619D2__INCLUDED_)
#define AFX_DIB_H__1A2F121B_2FC3_4D06_9B9A_D8CF4F0619D2__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//等待设置
#define WaitCursorBegin()	HCURSOR hcURSOR = SetCursor(LoadCursor(NULL, IDC_WAIT))
#define WaitCursorEnd()		SetCursor(hcURSOR) 

// 计算矩形区域的宽度

#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)

// 计算矩形区域的高度
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

class CDib  
{

public:
	BITMAPINFO			*m_pBMI;//位图信息头结构指针
	BITMAPFILEHEADER	*m_pBMFHeader;//位图文件头结构指针   

	BYTE				*m_pDIBData;//DIB图像数据指针
	BYTE				*m_pFileHeader; //位图文件头指针
	
	DWORD				m_ImageData;//位图图像实际数据大小
	DWORD          		m_ImageCount;//位图文件大小

	int					m_ByteWidth;//图象每行的字节数，图象的扫描宽度
public:  // 构造函数与析构函数
	CDib();
	CDib(BYTE *pSrc);
	CDib(CDib &dib);
	CDib(LPCTSTR lpszPathName);
	void operator = (CDib &dib);
	virtual ~CDib();
	
	UINT GetW();//获取DIB图像的宽度
	UINT GetH();//获取DIB图像的高度
	void updatedata(void); // 将m_pDIBData的数据更新m_pFILEHeader中的图像像素数据
	BOOL SaveFile(CString filename);  // 保存DIB图像文件
	BOOL LoadFromFile(LPCTSTR lpszFileName);    //将DIB磁盘文件中读入内存中，以待处理
   	void ShowDIB(CDC  *pDC,int nLeft,int nTop); //显示DIB位图	

 };



#endif // !defined(AFX_DIB_H__1A2F121B_2FC3_4D06_9B9A_D8CF4F0619D2__INCLUDED_)
