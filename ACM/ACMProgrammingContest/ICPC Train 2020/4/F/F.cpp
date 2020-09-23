#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

int main() {
//  freopen("in", "r", stdin);
	int n;
	scanf("%d", &n);
	vector<int> a(n), b(n);
	for (int &x: a) {
		scanf("%d", &x);
	}
	for (int &x: b) {
		scanf("%d", &x);
	}
	if (a == b) {
		printf("0\n");
		return 0;
	}
	set<int> required(b.begin(), b.end());
	if ((int)required.size() == n) {
		printf("-1\n");
		return 0;
	}
	for (int x : b) {
		if (find(a.begin(), a.end(), x) == a.end()) {
			printf("-1\n");
			return 0;
		}
	}
	vector<pair<int, int>> ops;
	int trash = 1;
	while (find(a.begin(), a.end(), trash) != a.end()) {
		trash++;
	}

  int rep = -1;
  for (int i = 0; i < n; i++) {
    if (find(b.begin() + i + 1, b.end(), b[i]) != b.end()) {
      rep = i;
      break;
    }
	}
  int rep_backup = b[rep];
  b[rep] = b[0];


	auto save_back = [&](int prefix) {
		if (required.count(a.back()) && find(a.begin(), a.begin() + prefix, a.back()) == a.begin() + prefix) {
			int req = 0;
			map<int, int> found;
			while (req < prefix && required.count(a[req])) {
				if (found.find(a[req]) != found.end()) {
					req = found[a[req]];
					break;
				}
				found[a[req]] = req;
				req++;
			}
			assert(req < prefix);
			ops.emplace_back(a[req], a.back());
			a[req] = a.back();
		}
	};

	save_back(n - 1);
	for (int i = n - 2; i >= 0; i--) {
		if (a[i] != b[i]) {
			int other = 0;
			while (other < n && a[other] == a[i]) {
				other++;
			}
			assert(other < n);
			for (int j = 0; j < i; j++) {
				if (a[j] == a[i]) {
					ops.emplace_back(a[j], a[other]);
					a[j] = a[other];
				}
			}
			if (a.back() != a[i]) {
				ops.emplace_back(trash, a[i]);
				a.back() = a[i];
			}
			ops.emplace_back(a[i], b[i]);
			a[i] = b[i];
		}
		required.erase(b[i]);
		if (i) {
      save_back(i);
    }
	}
	if (a.back() != b.back()) {
	   ops.emplace_back(trash, b.back());
  }
	if (rep != 0) {
                                               // b[0], b[0], b[end]
	  ops.emplace_back(b[0], b.back());          // b[end], b[0], b[end]
    assert(b[rep] == b[0]);
    assert(find(b.begin(), b.begin() + rep, b.back()) == b.begin() + rep);
    ops.emplace_back(trash, b[rep]);           // b[end], b[0], b[0]
    ops.emplace_back(b[rep], b.back());        // b[end], b[end], b[0]
    ops.emplace_back(b.back(), b[0]);          // b[0], b[end], b[0]
    ops.emplace_back(trash, b.back());         // b[0], b[end], b[end]
    ops.emplace_back(b.back(), rep_backup);    // b[0], b[end], b[end]
	}

	printf("%d\n", 2 * (int)ops.size());
	for (auto x : ops) {
		printf("foreach ($a as &$x) if ($x == %d) break;\n", x.first);
		printf("foreach ($a as  $x) if ($x == %d) break;\n", x.second);
	}
}


