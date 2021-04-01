#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 100000 + 5

int n;
LL ans;
vector <int> Vec[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		Vec[i].push_back(0);
	for (int i = 1, x; i <= n; i ++)
	{
		scanf("%d", &x);
		Vec[x].push_back(i);
	}
	for (int i = 1; i <= n; i ++)
		Vec[i].push_back(n + 1);
	for (int i = 1; i <= n; i ++)
	{
		ans += 1LL * n * (n + 1) / 2;
		for (size_t j = 0; j < Vec[i].size() - 1; j ++)
			ans -= 1LL * (Vec[i][j + 1] - Vec[i][j]) * (Vec[i][j + 1] - Vec[i][j] - 1) / 2;
	}
	printf("%lld\n", ans);
	return 0;
}
