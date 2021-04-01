#include <bits/stdc++.h>

const int max_N = (int)1e5 + 21;

const int sigma = 26;

int n;

char s[max_N];

std::vector<std::pair<int, int>> pos[max_N];

struct PalindromicTree {
  int tot, last;

  int ch[max_N][sigma], len[max_N], link[max_N];

  int diff[max_N], slink[max_N], st[max_N];

  inline int new_node(int L) {
    int x = tot++;
    len[x] = L;
    memset(ch[x], 0, sizeof(ch[x]));
    link[x] = diff[x] = slink[x] = st[x] = 0;
    return x;
  }

  inline bool append(int n, int c) {
    auto get_node = [&](int x) {
      while (s[n - len[x] - 1] != s[n]) {
        x = link[x];
      }
      return x;
    };

    int u = get_node(last);
    int v = ch[u][c];

    if (!v) {
      v = new_node(len[u] + 2);
      link[v] = ch[get_node(link[u])][c];
      ch[u][c] = v;

      diff[v] = len[v] - len[link[v]];
      if (diff[v] == diff[link[v]]) {
        st[v] = st[link[v]];
        slink[v] = slink[link[v]];
      } else {
        st[v] = v;
        slink[v] = link[v];
      }
      last = v;
      return true;
    }

    last = v;
    return false;
  }

  inline void init() {
    last = tot = 0;
    link[new_node(0)] = new_node(-1);
  }
} pt;

int bit[max_N];

inline void modify(int x, int y) {
  for (; x <= n; x += x & -x) {
    bit[x] += y;
  }
}

inline int query(int x) {
  int ret = 0;
  for (; x; x -= x & -x) {
    ret += bit[x];
  }
  return ret;
}

void testCase(int id) {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  s[0] = -1;
  pt.init();
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    bool flag = pt.append(i, s[i] - 'a');
    for (int u = pt.last; pt.len[u] > 0; u = pt.slink[u]) {
      int v = pt.st[u], left = i - pt.len[u] + 1;
      auto &vec = pos[v];

      modify(i - pt.len[v] + 1, 1);

      if (!vec.empty() && vec.back().first == left) {
        assert(vec.back().second <= pt.len[u]);
        vec.back().second = pt.len[u];
      } else {
        vec.emplace_back(left, pt.len[u]);
      }
      if (vec.size() > 1) {
        auto x = vec[vec.size() - 2];
        int R = x.first + x.second - 1;
        modify(R - pt.len[u] + 1, -1);
        assert(vec.back().second <= x.second);
        if (vec.back().second == x.second) {
          vec[vec.size() - 2].first = vec.back().first;
          vec.pop_back();
        }
      }
    }
    if (flag) {
      ans += query(i) - query(i - pt.len[pt.last]) - 1;
    }
  }
  printf("Case #%d: %lld\n", id, ans);
}

void clr() {
  for (int i = 1; i <= n; ++i) {
    bit[i] = 0;
  }
  for (int i = 0; i <= pt.tot; ++i) {
    pos[i].clear();
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    testCase(i);
    clr();
  }
}
