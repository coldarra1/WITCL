// GetFeature.h: interface for the GetFeature class.
// 2005.1.13－16：02 By Superman 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETFEATURE_H__F4AF6FFD_5056_4E03_8774_096D222CD072__INCLUDED_)
#define AFX_GETFEATURE_H__F4AF6FFD_5056_4E03_8774_096D222CD072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cdib.h"

struct pattern//pattern结构体，保存某个数字类别(0～9)的所有样品特征
{
	int number;//该手写数字样品个数
	double feature[200][25];//各样品特征，每类手写数字最多有200个样品，每个样品有25个特征
};

class GetFeature : public CDib  
{
public:
	pattern pattern[10];//手写数字样品特征库
	double testsample[25];//待测的手写数字
	int width;//手写数字的宽
	int height;//手写数字的高
	int LineBytes;

	void Save(int cls);//将手写的数字保存到cls(0～9)类别中
	BOOL Saveable(int cls);//判断手写的数字能否保存到cls(0～9)类别中，因为各类别中样品特征不能重复
	double Cal(int row, int col);//计算分割好的5×5小区域中，黑像素所占的比例
	void SetFeature();//计算手写数字的特征，赋值给testsample
	void GetPosition();//获得手写数字的位置
	GetFeature();
	virtual ~GetFeature();

protected:
	int bottom;//手写数字的底部
	int top;//手写数字的顶部
	int left;//手写数字的左边
	int right;//手写数字的右边
};

#endif // !defined(AFX_GETFEATURE_H__F4AF6FFD_5056_4E03_8774_096D222CD072__INCLUDED_)
