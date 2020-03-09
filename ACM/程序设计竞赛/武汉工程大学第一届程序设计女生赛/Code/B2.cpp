# include <iostream>

using namespace std;

const int N = 1e5 + 5;
int n, m, t;
int source[N], cnt[N], pre[N];
bool vis[N];

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}

void merge(int a, int b) {
	cnt[a] += cnt[b];
	pre[b] = a;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m >> t;
		for (int i = 1; i <= n; i++) {
			cnt[i] = 1;
			pre[i] = i;
			vis[i] = false;
		}
		for (int i = 0; i < m; i++)
			cin >> source[i];
		while (t--) {
			int a, b;
			cin >> a >> b;
			a = find(a), b = find(b);
			if (a != b)
				merge(a, b);
		}
		int res = 0;
		for (int i = 0; i < m; i++) {
			int root = find(source[i]);
			if (!vis[root]) {
				vis[root] = true;
				res += cnt[root];
			}
		}
		cout << res << endl;
	}
	return 0;
}
