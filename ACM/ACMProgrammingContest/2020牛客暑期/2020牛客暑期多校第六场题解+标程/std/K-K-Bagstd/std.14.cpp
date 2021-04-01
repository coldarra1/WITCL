#include <bits/stdc++.h>

const int maxn = 500111;
int a[maxn], ord[maxn], n, k;
bool check()
{
	for(int i=1; i<=n; i++) ord[i] = i;
	std::stable_sort(ord + 1, ord + n + 1, [](int x, int y) { return a[x] < a[y]; });
	
	std::vector<std::pair<int, int> > vs;
	for(int i=2; i<=n; i++) if(a[ord[i]] == a[ord[i-1]])
	{
		int p1 = ord[i-1], p2 = ord[i];
		if(p2 - p1 >= k) continue;
		int vl = p2 % k, vr = (p1 - 1) % k;
		if(vl <= vr) vs.emplace_back(vl, vr);
		else
		{
			vs.emplace_back(vl, k - 1);
			vs.emplace_back(0, vr);
		}
	}
	
	std::sort(vs.begin(), vs.end());
	int MX = -1;
	for(int i=0; i<(int)vs.size(); i++)
	{
		if(MX < vs[i].first - 1) return true;
		MX = std::max(MX, vs[i].second);
	}
	if(MX < k - 1) return true;
	return false;
}

void solve()
{
	scanf("%d%d", &n, &k);
	for(int i=1; i<=n; i++) scanf("%d", a+i);
	
	if(check()) puts("YES");
	else puts("NO");
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--) solve();
	return 0;
}
