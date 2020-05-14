# include <iostream>
# include <cstdio>
# include <climits>
# include <vector>
# include <algorithm>
 
using namespace std;
 
typedef long long LL;
typedef pair<LL, LL> PLL;
const int maxn = 1e6 + 5;
LL n, k, S, a[maxn], sum[maxn];
vector<PLL> F, G;
bool vis[maxn];
 
void search(LL &team, vector<PLL> &T)
{
	for (int i = 0; i < T.size(); i++)
		sum[i + 1] = sum[i] + T[i].second;
	for (int i = 1; i <= T.size(); i++) {
		LL l = 0, r = T.size() - i;
		while (l < r) {
			LL mid = l + r >> 1;
			if (sum[i + mid] - sum[i - 1] >= S)
				r = mid;
			else
				l = mid + 1;
		}
		if (sum[i + l] - sum[i - 1] >= S)
			team = min(team, l + 1);
	}
	return;
}
 
int main()
{
	scanf("%lld %lld %lld", &n, &k, &S);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	LL cnt = 0;
	for (int i = 1; F.size() < n / 2; i = i + 1 <= n ? i + 1 : 1) {
		if (vis[i])
			continue;
		cnt++;
		if (cnt == k) {
			cnt = 0;
			vis[i] = true;
			F.push_back({ i, a[i] });
		}
	}
	sort(F.begin(), F.end());
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			G.push_back({ i, a[i] });
	LL team1, team2;
	team1 = team2 = INT_MAX;
	search(team1, F);
	search(team2, G);
	printf("%lld %lld\n", team1 == INT_MAX ? 0 : team1, team2 == INT_MAX ? 0 : team2);
	return 0;
}
