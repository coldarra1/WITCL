# include <iostream>
# include <cstdio>
# include <climits>
# include <algorithm>
 
using namespace std;
 
const int maxn = 1e6 + 5;
int people[maxn], pre[maxn], w[maxn], F[maxn], q[maxn];
 
int find(int x)
{
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
 
void merge(int a, int b)
{
	people[find(a)] += people[find(b)];
	pre[find(b)] = find(a);
	return;
}
 
void pre_sum(int n)
{
	for (int i = 1; i <= n; i++)
		F[i] += F[i - 1];
	return;
}
 
int search(int n, int t)
{
	pre_sum(n);
	int hh = 0, tt = 0, ans = INT_MIN;
	for (int i = 1; i <= n; i++) {
		if (hh <= tt && i - q[hh] > t)
			hh++;
		ans = max(ans, F[i] - F[q[hh]]);
		while (hh <= tt && F[i] <= F[q[tt]])
			tt--;
		q[++tt] = i;
	}
	return ans;
}
 
int main()
{
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
		pre[i] = i;
		people[i] = 1;
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		if (find(u) != find(v)) {
			if (find(u) > find(v))
				swap(u, v);
			merge(u, v);
		}
	}
	int pos = 0;
	pair<int, int> now_max;
	now_max = { 0, 0 };
	for (int i = 1; i <= n; i++) {
		if (people[i] > now_max.first) {
			now_max = { people[i], i };
			pos = 0;
			F[++pos] = w[i];
		}
		else if (find(now_max.second) == find(i))
			F[++pos] = w[i];
	}
	printf("%d %d\n", find(now_max.second), search(pos, t));
	return 0;
}
