# include <iostream>
# include <cstdio>
# include <cstring>
# include <vector>
# include <unordered_map>
# include <algorithm>
 
using namespace std;
 
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
unordered_map<int, vector<PII>> M; // 某一个点能够直接到达的其它所有点  (也可以不存终点，只存由该点出发的每条通道的能量）
int F[maxn * 30][2], pos;
 
void build(vector<PII> &w)
{
	for (auto x : w) {
		int p = 0;
		for (int i = 30; ~i; i--) {
			if (!F[p][x.second >> i & 1])
				F[p][x.second >> i & 1] = ++pos;
			p = F[p][x.second >> i & 1];
		}
	}
	return;
}
 
int serch(vector<PII> &w)
{
	int ans = 0;
	for (auto x : w) {
		int res = 0, p = 0;
		for (int i = 30; ~i; i--) {
			if (F[p][x.second >> i & 1 ^ 1]) {
				res += 1 << i;
				p = F[p][x.second >> i & 1 ^ 1];
			}
			else
				p = F[p][x.second >> i & 1];
		}
		ans = max(ans, res);
	}
	return ans;
}
 
int main()
{
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		M[u].push_back({ v, w });
	}
	int ans = 0;
	for (auto x : M) {
		if (x.second.size() >= 2) {
			memset(F, 0, sizeof(F));
			pos = 0;
			build(x.second);
			ans = max(ans, serch(x.second));
		}
	}
	if (ans >= t)
		printf("%d\n", ans);
	else
		printf("QAQ\n");
	return 0;
}
