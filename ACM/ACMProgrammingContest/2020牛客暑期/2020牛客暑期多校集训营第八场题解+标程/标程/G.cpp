#include <bits/stdc++.h>
using namespace std;

struct Card {
	int a[4];
};
Card card[300];

char str[100];

bool isSet(int x, int y, int z) {
	for (int i = 0; i < 4; i++) {
		int wild_num = 0;
		set<int> st;
		if (card[x].a[i] == -1) wild_num++;
		else st.insert(card[x].a[i]);
		if (card[y].a[i] == -1) wild_num++;
		else st.insert(card[y].a[i]);
		if (card[z].a[i] == -1) wild_num++;
		else st.insert(card[z].a[i]);
		if (st.size() != 1 && st.size() + wild_num != 3)
			return false;
	}

	return true;
}

int main() {
	map<string, pair<int, int>> cardIndex;
	cardIndex["one"] = make_pair(0, 0);
	cardIndex["two"] = make_pair(0, 1);
	cardIndex["three"] = make_pair(0, 2);
	cardIndex["diamond"] = make_pair(1, 0);
	cardIndex["squiggle"] = make_pair(1, 1);
	cardIndex["oval"] = make_pair(1, 2);
	cardIndex["solid"] = make_pair(2, 0);
	cardIndex["striped"] = make_pair(2, 1);
	cardIndex["open"] = make_pair(2, 2);
	cardIndex["red"] = make_pair(3, 0);
	cardIndex["green"] = make_pair(3, 1);
	cardIndex["purple"] = make_pair(3, 2);

	int T;
	scanf("%d", &T);
	int iCase = 0;
	while (T--) {
		iCase++;
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", str);
			int len = strlen(str);
			int id = 0;
			for (int j = 0; j < 4; j++) {
				if (str[id] == '[') id++;
				string ss = "";
				while (str[id] != ']') {
					ss = ss + str[id];
					id++;
				}
				if (str[id] == ']') id++;
				if (ss == "*") card[i].a[j] = -1;
				else {
					pair<int, int> pp = cardIndex[ss];
					card[i].a[pp.first] = pp.second;
				}
			}
		}
		bool ff = false;
		for (int i = 1; i <= min(n, 21); i++) {
			if (ff) break;
			for (int j = i+1; j <= min(n, 21); j++) {
				for (int k = j+1; k <= min(n, 21); k++) {
					if (isSet(i, j, k)) {
						ff = true;
						printf("Case #%d: %d %d %d\n", iCase, i, j, k);
						break;
					}
				}
				if (ff) break;
			}
		}
		if (!ff)
			printf("Case #%d: -1\n", iCase);
	}
	return 0;
}
