// Classification.h: interface for the Classification class.
// 2005.1.13гн16г║02 By Superman 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSIFICATION_H__F24DD6D8_8029_4ACB_9D73_4994B97F97A9__INCLUDED_)
#define AFX_CLASSIFICATION_H__F24DD6D8_8029_4ACB_9D73_4994B97F97A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GetFeature.h"

struct number_no
{
	int number;
	int no;
};

class Classification : public GetFeature  
{
public:
	Classification();
	virtual ~Classification();
public:
	double pipei(double s1[], double s2[]);
	double K(double X[], double Xk[]);
	int Shihanshu();
	CString ifClassified(int Class0,int Class1);
	int Zengliangjiaozheng();
	int LMSE();
	int Jiangcheng();
	double* BayesLeastRisk(double loss[10][10]);
	int BayesLeasterror();
	int BayesErzhishuju();
	int Fisher();
	int Fisher_2Classes(int Class0,int Class1);
	number_no LeastDistance();


};

#endif // !defined(AFX_CLASSIFICATION_H__F24DD6D8_8029_4ACB_9D73_4994B97F97A9__INCLUDED_)
