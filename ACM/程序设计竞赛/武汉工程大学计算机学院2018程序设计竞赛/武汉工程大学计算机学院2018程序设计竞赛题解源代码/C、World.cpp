#include<stdio.h>
int main() {
	double n, sum = 0;
	scanf("%lf", &n);
	sum = n * 6;
	if(n >= 15)
		sum -= n * 0.1;
	printf("%.2f", sum);
	return 0;
}
