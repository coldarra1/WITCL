#include<stdio.h>
#include<math.h>
#define PI acos(-1)
int main() {
	int t;
	double a, b, tmp, x, ans;
	scanf("%d", &t);
	while(t--) {
		scanf("%lf%lf", &a, &b);
		tmp = sin(PI / 3.0 - a / 180.0 * PI) / sin(a / 180.0 * PI) * sin(PI / 3.0 - b / 180.0 * PI) / sin(b / 180.0 * PI);
		x = sqrt(3.0 / 4.0 * tmp * tmp / (tmp * tmp + tmp + 1.0));
		ans = asin(x) / PI * 180.0;
		printf("%.2f\n", ans);
	}
	return 0;
}
