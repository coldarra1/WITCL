# include <iostream>
# include <cstring>
# include <queue>
# include <algorithm>

using namespace std;

typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
const int N = 1010, INF = 0x3f3f3f3f;
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
int n, m;
char F[N][N];
bool vis[N][N];

int bfs(int stx, int sty, int edx, int edy) {
	memset(vis, false, sizeof vis);
	queue<PIII> q;
	q.push({ {stx, sty}, 0 });
	vis[stx][sty] = true;
	while (!q.empty()) {
		auto t = q.front();
		q.pop();
		int a = t.first.first, b = t.first.second, dis = t.second;
		if (a == edx && b == edy)
			return dis;
		for (int i = 0; i < 4; i++) {
			int x = a + dx[i], y = b + dy[i];
			if (x < 1 || x > n || y < 1 || y > m || F[x][y] == '*' ||
			        vis[x][y])
				continue;
			q.push({ {x, y}, dis + 1 });
			vis[x][y] = true;
		}
	}
	return INF;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			cin >> F[i] + 1;
		int x1, y1, x2, y2, x3, y3;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		int dis1 = bfs(x1, y1, x2, y2), dis2 = bfs(x2, y2, x3, y3);
		if (dis1 == INF || dis2 == INF)
			cout << -1 << endl;
		else
			cout << dis1 + dis2 << endl;
	}
	return 0;
}
