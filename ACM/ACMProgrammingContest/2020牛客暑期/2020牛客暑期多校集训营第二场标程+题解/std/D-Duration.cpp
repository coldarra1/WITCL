#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

int h1, m1, s1, h2, m2, s2, t1, t2;

int main()
{
	scanf("%d:%d:%d", &h1, &m1, &s1);
	scanf("%d:%d:%d", &h2, &m2, &s2);
	t1 = h1 * 3600 + m1 * 60 + s1;
	t2 = h2 * 3600 + m2 * 60 + s2;
	printf("%d\n", abs(t1 - t2));
	return 0;
}
