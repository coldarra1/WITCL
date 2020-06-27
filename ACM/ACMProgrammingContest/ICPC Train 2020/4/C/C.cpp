#include <bits/stdc++.h>
using namespace std;
const int kN = 105;
typedef pair<int, int> pii;
#define F first
#define S second

char c[kN][kN];
int n, m;
vector<pair<int, int>> ans;
pii Next(int x, int y) {
	if(c[x][y] == 'X') return {x, y};
	else if(c[x + 1][y] == 'X') return {x + 1, y};
	else if(c[x][y + 1] == 'X') return {x, y + 1};
	else if(c[x + 1][y + 1] == 'X') return {x + 1, y + 1};
	return {-1, -1}; 
}
void dfs(int x, int y, bool f, int dx, int dy) {
	c[x][y] = '.';
	for(int i = 0; i < 4; i++) {
		ans.emplace_back(x + dx, y + dy);
		if(f) dx = ~dx, dy = ~dy;
		else dx = ~dx;
		f ^= 1;
		while(true) {
			pii p = Next(x + dx, y + dy);
			if(p.F == -1) break;
			dfs(p.F, p.S, f, x + dx - p.F, y + dy - p.S);
		}
	}
}
int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i++) scanf("%s", c[i] + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(c[i][j] == 'X') dfs(i, j, 1, -1, -1);

	printf("%d\n", int(ans.size()) - 1);
	for(auto p : ans) printf("%d %d\n", p.S, p.F);
	return 0;
}
