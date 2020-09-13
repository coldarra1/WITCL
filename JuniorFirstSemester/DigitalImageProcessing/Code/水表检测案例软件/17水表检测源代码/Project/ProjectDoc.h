// ProjectDoc.h : interface of the CProjectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTDOC_H__58E7F920_1CA8_4EF6_BA11_963B935982C9__INCLUDED_)
#define AFX_PROJECTDOC_H__58E7F920_1CA8_4EF6_BA11_963B935982C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CProjectDoc : public CDocument
{
protected: // create from serialization only
	CProjectDoc();
	DECLARE_DYNCREATE(CProjectDoc)

// Attributes
public:
	BITMAPFILEHEADER BitMapFileHeader;  //图像文件头
	//BITMAPINFOHEADER BitMapInfoHeader;  //图像文件信息头
	PBITMAPINFO pBitMapInfo;//图像文件信息（包括图像文件信息头和调色板）
	long BmpWidth;  //BMP图像文件象素宽
	long nWidth;
	long BmpHeight; //BMP图像文件象素高
	long BitCount;  //表示BMP文件每象素颜色所用比特数
	long Compression;//表示BMP文件的压缩方式
	int ColorUsed;// 使用的颜色数
	BOOL bImageLoaded;//是否开了内存读取图像数据，若是，则在析构函数中要释放内存
	BYTE * pImage;//图像数据
	BYTE * pImageBak;//图像备份数据
	//BYTE * pHist;//直方图数据
// Operations
public:
	BOOL ReadImage(const char *szFileName);
	void SetDocument(CProjectDoc* pDoc);
	WriteToFile(const char *szFileName);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProjectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTDOC_H__58E7F920_1CA8_4EF6_BA11_963B935982C9__INCLUDED_)
