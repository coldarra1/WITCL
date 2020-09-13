// YIchuansuanfa.h: interface for the YIchuansuanfa class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YICHUANSUANFA_H__5EC8E48F_0B4E_4548_8A5A_F50BCB371440__INCLUDED_)
#define AFX_YICHUANSUANFA_H__5EC8E48F_0B4E_4548_8A5A_F50BCB371440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cluster.h"

class YIchuansuanfa : public CCluster
{
public:
	YIchuansuanfa();
	virtual ~YIchuansuanfa();
	int     FunctionMode;
 	int     CHROMLENGTH;
    int     PopSize;
    int     MaxGeneration;
	double  Pc;//交叉概率
	double  Pm;//变异概率

	struct  individual
	{
		int		chrom[50];
	    double value;
		double fitness;
		int    index;
	};
	int    index;//最优解出现的最小代数
	int    generation;
	int    best_index;
	int    worst_index;
	struct individual bestindividual;//最优个体
	struct individual worstindividual;//最差个体
	struct individual currentbest;//当前的最优个体
	struct individual population[80];
	void   GenerationInitialPopulation();
	void   GenerateNextPopulation();//繁殖下一个体
	void   EvaluatePopulation();//评估人群
	void   CalculateObjectValue();//计算物体价值
	void   CalculateFitnessValue();//计算适应性
	void   FindBestAndWorstIndividual();
	void   PerformEvolution();//开始演变
	void   SelectionOperator();
	void   CrossoverOperator();
	void   MutationOperator();
	void   OutputTextReport();
	void   main();
};

#endif // !defined(AFX_YICHUANSUANFA_H__5EC8E48F_0B4E_4548_8A5A_F50BCB371440__INCLUDED_)
