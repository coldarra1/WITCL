// Cluster.h: interface for the CCluster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLUSTER_H__E921280B_4D09_4970_813F_8831EAEDF1F4__INCLUDED_)
#define AFX_CLUSTER_H__E921280B_4D09_4970_813F_8831EAEDF1F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cdib.h"

const int N=7;

class CCluster : public CDib  
{

public:
struct Pattern //样本结构
{ 
	int			index;    //样本标号
	int			category;   //样本或模板所属类别
	double		feature[N*N];//特征值
	double		distance; // 样品到类中心的距离
	CPoint		lefttop,rightbottom;//样品在图像中的位置
};

struct	Center//聚类中心结构
{
	int 		index;//中心编号
	double		feature[N*N];//中心特征值
	int 		patternnum;//该聚类中心包含的样品数目
};



public:
	int			patternnum;//样本总数
	int 		centernum;//聚类中心数目
	Pattern		*m_pattern;//指向样本的指针
	Center		*m_center;//指向中心的指针
	int			wide, height;//图像的宽、高
public:
	CCluster();
	virtual ~CCluster();

public:
	void GetFeature();
	void CalFeature(CCluster::Pattern *m_pattern);
	void CalCenter(CCluster::Center *pcenter);
	double GetDistance( CCluster::Pattern  pattern1, CCluster::Pattern  pattern2, const int distype);
	double GetDistance(CCluster::Pattern  pattern,  CCluster::Center   center, const int distype);
	double GetDistance(CCluster::Center  mCenter1,CCluster::Center  mCenter2,int distype);
	double GetDistance(double * dis, int i, int j);
	double GetFuzzyDistance(CCluster::Pattern pattern1,CCluster::Pattern pattern2,int distype);
	void FuzzyCluster();
	void ISODATA();
	void Kjunzhi();
	void Leipingjunjulifa();
	void Zhongxinfa();
	void Zhongjianjulifa();
	void Zuichangjulifa();
	void Zuiduanjulifa();
	void Zuidazuixiaojulifa();

	void Zuilinjinguize();

};

#endif // !defined(AFX_CLUSTER_H__E921280B_4D09_4970_813F_8831EAEDF1F4__INCLUDED_)
