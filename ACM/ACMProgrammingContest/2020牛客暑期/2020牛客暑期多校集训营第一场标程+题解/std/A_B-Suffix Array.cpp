#include <bits/stdc++.h>

static const int N = 100000;

#ifndef NO_MAIN

struct CharRank {
  int operator[](int i) const { return s[i]; }

  const int *s;
};

template <int N> struct SA {
  void compute(int _n, const int *s) {
    n = _n;
    sort(n, IdOrder{}, CharRank{s}, sa);
    int range = rank(CharRank{s}, CharRank{s});
    for (int length = 1; length < n && range < n; length <<= 1) {
      memcpy(trk, rk, sizeof(*rk) * n);
      TRank r1{n, length, trk}, r0{n, 0, trk};
      sort(range + 1, IdOrder{}, r1, tsa);
      sort(range + 1, TOrder{tsa}, r0, sa);
      range = rank(r0, r1);
    }
  }

  int sa[N], rk[N];

private:
  struct IdOrder {
    int operator[](int i) const { return i; }
  };

  struct TOrder {
    int operator[](int i) const { return sa[i]; }
    const int *sa;
  };

  struct TRank {
    int operator[](int i) const {
      return i + shift < n ? rk[i + shift] + 1 : 0;
    }
    int n, shift;
    const int *rk;
  };

  template <typename Order, typename Rank>
  void sort(int range, const Order &o, const Rank &r, int *out) {
    memset(count, 0, sizeof(*count) * range);
    for (int i = 0; i < n; ++i) {
      count[r[i]]++;
    }
    for (int i = 1; i < range; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = n; i--;) {
      out[--count[r[o[i]]]] = o[i];
    }
  }

  template <typename Rank0, typename Rank1>
  int rank(const Rank0 &r0, const Rank1 &r1) {
    rk[sa[0]] = 0;
    for (int _ = 1; _ < n; ++_) {
      int i = sa[_];
      int j = sa[_ - 1];
      rk[i] = rk[j] + (r0[i] != r0[j] || r1[i] != r1[j]);
    }
    return rk[sa[n - 1]] + 1;
  }

  int n;
  int count[N], tsa[N], trk[N];
};

char s[N + 1];
int fwd[N + 1];
SA<N + 1> sa;

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    scanf("%s", s);
    int last[]{-1, -1};
    for (int i = n; i--;) {
      fwd[i] = (~last[s[i] - 'a'] ? last[s[i] - 'a'] - i : n) - 1;
      last[s[i] - 'a'] = i;
    }
    fwd[n] = n;
    sa.compute(n + 1, fwd);
    for (int i = n; i--;) {
      printf("%d%c", sa.sa[i] + 1, " \n"[!i]);
    }
  }
}

#endif