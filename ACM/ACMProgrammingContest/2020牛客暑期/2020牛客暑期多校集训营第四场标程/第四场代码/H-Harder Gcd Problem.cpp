#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> mp(n + 1, 0);
    for (int i = 2; i <= n; ++i) if (mp[i] == 0) {
      for (int j = i; j <= n; j += i) mp[j] = i;
    }
    std::vector<std::pair<int, int>> group;
    int cnt = 1;
    for (int i = 2; i <= n; ++i) {
      cnt += i > n / 2 && mp[i] == i;
      if (i > n / 2 && mp[i] == i) continue;
      group.emplace_back(mp[i], i);
    }
    std::sort(group.begin(), group.end());
    std::vector<std::pair<int, int>> ret;
    std::vector<int> extra;
    for (size_t i = 0, j; i < group.size(); i = j) {
      for (j = i + 1; j < group.size() && group[i].first == group[j].first; ++j);
      if ((j - i) % 2 == 0) {
        for (size_t k = i; k < j; k += 2) ret.emplace_back(group[k].second, group[k + 1].second);
      } else {
        int last = -1, even = -1;
        for (size_t k = i; k < j; k++) {
          if (group[k].second % 2 == 0 && even == -1) {
            even = group[k].second;
            continue;
          }
          if (last == -1) last = group[k].second;
          else {
            ret.emplace_back(last, group[k].second);
            last = -1;
          }
        }
        assert(even != -1);
        extra.push_back(even);
      }
    }
    for (size_t i = 0; i + 1 < extra.size(); i += 2) {
      ret.emplace_back(extra[i], extra[i + 1]);
    }
    assert((int)ret.size() == (n - cnt) / 2);
    printf("%d\n", (int)ret.size());
    for (auto &e: ret) printf("%d %d\n", e.first, e.second);
  }
  return 0;
}
