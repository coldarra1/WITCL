#include<stdio.h>
#include<stdlib.h>

int time_elapse(int hour, int minute, int second)
{
	return (hour * 60 * 60 + minute * 60 + second);
}

int main()
{
	int n = 100, sum1, sum2;
	int hour, mi, second;
	scanf("%d:%d:%d", &hour, &mi, &second);
	sum1 = time_elapse(hour, mi, second);
	printf("%d ", sum1);
	scanf("%d:%d:%d", &hour, &mi, &second);
	sum2 = time_elapse(hour, mi, second);
	printf("%d ", sum2);
	sum1 = abs(sum1 - sum2);
	printf("%d\n", sum1);
	
	system("pause");


}