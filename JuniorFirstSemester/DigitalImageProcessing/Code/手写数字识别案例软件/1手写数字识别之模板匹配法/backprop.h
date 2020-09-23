/*
 ******************************************************************
 * backprop.h
 ******************************************************************
 */

#ifndef _BACKPROP_H_

#define _BACKPROP_H_

#define BIGRND 0x7fffffff

/*** 神经网络的数据结构。网络被假定为一个全连接的3层前向结构，
	 每层的单元0是阈值，这意味着真正的神经元编号为1－n
 ***/

typedef struct {
	int input_n;                  /* 输入层的神经元个数 */
	int hidden_n;                 /* 隐含层的神经元个数 */
	int output_n;                 /* 输出层的神经元个数 */

	double *input_units;          /* 输入层的神经元 */
	double *hidden_units;         /* 隐藏层的神经元 */
	double *output_units;         /* 输出曾的神经元 */

	double *hidden_delta;         /* 隐藏层的误差 */
	double *output_delta;         /* 输出层的误差 */

	double *target;               /* 目标向量 */

	double **input_weights;       /* 输入层到隐藏层的连接权 */
	double **hidden_weights;      /* 隐藏层到输出曾的连接权 */

                                /*** 下面两个在迭代时使用 ***/
	double **input_prev_weights;  /* 前次输入层导隐藏层权值的改变 */
	double **hidden_prev_weights; /* 前次隐藏层导输出层权值的改变 */
} BPNN;


/*** 用户接口 ***/

/* 初始化随机数种子 */
void bpnn_initialize(int seed);

/* 创建BP网络 */
BPNN *bpnn_create(int n_in, int n_hidden, int n_out);

/* 释放BP网络所占地内存空间 */
void bpnn_free(BPNN *net);

/* 训练BP网络 */
void bpnn_train(BPNN *net, double eta, double momentum, double *eo, double *eh);

/* 前向运算 */
void bpnn_feedforward(BPNN* net);

/* 保存BP网络到文件中 */
void bpnn_save(BPNN *net, char *filename);

/* 从文件中读取BP网络参数 */
BPNN *bpnn_read(char *filename);


#endif
