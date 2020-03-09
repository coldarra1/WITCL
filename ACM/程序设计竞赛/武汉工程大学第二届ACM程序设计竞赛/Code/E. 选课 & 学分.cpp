# include <iostream>
# include <cstdio>
# include <cmath>
# include <queue>
# include <vector>
# include <algorithm>
 
using namespace std;
 
typedef long long LL;
typedef pair<LL, LL> PLL;
const int maxn = 2010;
LL m, n;
LL a[maxn], b[maxn], c[maxn];
 
void merge()
{
	priority_queue<PLL, vector<PLL>, greater<PLL> > heap;
	for (int i = 0; i < n; i++)
		heap.push({ a[0] + b[i], 0 });
	for (int i = 0; i < n; i++) {
		auto t = heap.top();
		heap.pop();
		c[i] = t.first;
		heap.push({ t.first - a[t.second] + a[t.second + 1], t.second + 1 });
	}
	for (int i = 0; i < n; i++)
		a[i] = c[i];
	return;
}
 
int main()
{
	scanf("%lld %lld", &m, &n);
	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	sort(a, a + n);
	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < n; j++)
			scanf("%lld", &b[j]);
		merge();
	}
	for (int i = 0; i < n; i++)
		printf("%lld%c", a[i], " \n"[i + 1 == n]);
	LL sum = 0, mid = a[n >> 1];
	for (int i = 0; i < n; i++)
		sum += abs(mid - a[i]);
	printf("%lld\n", sum);
	return 0;
}
