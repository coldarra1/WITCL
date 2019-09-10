#include<stdio.h>
int main() {
	int a[105] = {0}; //一般比题目数据范围要求大一点
	int i, j, t, n;
	//数据输入
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	//冒泡排序
	for(i = 0; i < n - 1; i++) { //n个数的数列总共扫描n-1次
		for(j = 0; j < n - i - 1; j++) { //每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
			if(a[j] > a[j + 1]) { //后一位数比前一位数小的话，就交换两个数的位置（升序）
				t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
			}
		}
	}
	//输出排列
	for(i = 0; i < n; i++) {
	printf("%d ", a[i]);
	}
	return 0;
}
