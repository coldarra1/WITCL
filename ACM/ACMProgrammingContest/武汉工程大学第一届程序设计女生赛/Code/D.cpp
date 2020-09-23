# include <iostream>
# include <cstring>
# include <algorithm>

using namespace std;

int n, m, pos, res;
int card[5], q[11];

void dfs(int u, int fire, int damage, int attack, bool atk, bool sf, bool can_sf) {
	res = max(res, damage);
	if (u == n + pos || !fire && (sf || !can_sf))
		return;
// 用普攻
	if (!atk && fire)
		dfs(u, fire - 1, damage + attack, 0, true, sf, can_sf);
// 用 1
	if (card[1]) {
		card[1]--;
		if (!sf && can_sf)
			dfs(u + 1, fire, damage + 4, attack, atk, true, false);
		else if (fire)
			dfs(u + 1, fire - 1, damage + 4, attack, atk, sf, true);
		card[1]++;
	}
// 用 2
	if (card[2]) {
		card[2]--;
		if (!sf && can_sf)
			dfs(u + 1, fire, damage + 5, attack, atk, true, false);
		else if (fire)
			dfs(u + 1, fire - 1, damage + 5, attack, atk, sf, true);
		card[2]++;
	}
// 用 3
	if (card[3]) {
		card[3]--;
		card[q[pos++]]++;
		if (!sf)
			dfs(u + 1, fire, damage, attack + 2, atk, true, can_sf);
		else if (fire)
			dfs(u + 1, fire - 1, damage, attack + 2, atk, sf, can_sf);
		card[3]++;
		card[q[--pos]]--;
	}
// 用 4
	if (card[4]) {
		card[4]--;
		card[q[pos++]]++;
		if (!sf)
			dfs(u + 1, fire + 1, damage, attack, atk, true, can_sf);
		else if (fire)
			dfs(u + 1, fire, damage, attack, atk, sf, can_sf);
		card[4]++;
		card[q[--pos]]--;
	}
	return;
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		memset(card, 0, sizeof card);
		memset(q, 0, sizeof q);
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			card[x]++;
		}
		for (int i = 0; i < m; i++)
			cin >> q[i];
		pos = res = 0;
		dfs(0, 2, 0, 3, false, false, false);
		cout << res << endl;
	}
	return 0;
}
