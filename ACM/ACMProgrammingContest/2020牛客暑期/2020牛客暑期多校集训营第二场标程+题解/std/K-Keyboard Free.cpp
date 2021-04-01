#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long double LD;
#define K 1024

int Case, r1, r2, r3;
const LD pi = acosl(-1.0);

LD Dis(LD x_1, LD y_1, LD x_2, LD y_2)
{
	LD _x = x_1 - x_2, _y = y_1 - y_2;
	return sqrtl(_x * _x + _y * _y);
}

int main()
{
	for (scanf("%d", &Case); Case; Case --)
	{
		scanf("%d%d%d", &r1, &r2, &r3);
		if (r1 > r2) swap(r1, r2);
		if (r2 > r3) swap(r2, r3);
		if (r1 > r2) swap(r1, r2);
		LD x1 = r1, y1 = 0.0, res = 0.0;
		for (int i = 0; i < K; i ++)
		{
			LD theta = (LD(i + 0.5) / K) * pi;
			LD x2 = r2 * cosl(theta), y2 = r2 * sinl(theta);
			LD a = Dis(x1, y1, x2, y2);
			LD d = r1 * y2 / a;
			LD alpha = asinl(d / r3);
			LD expected_dis = 2 * r3 * (cosl(alpha) + alpha * sinl(alpha)) / pi;
			res += expected_dis * a / 2;
		}
		res /= K;
		printf("%.1Lf\n", res);
	}
	return 0;
}
