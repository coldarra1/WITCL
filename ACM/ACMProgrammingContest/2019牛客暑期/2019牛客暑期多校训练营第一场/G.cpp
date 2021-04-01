#include <bits/stdc++.h>

struct Solver {
  using Hash = uint64_t;
  static const Hash MAGIC = 1e6 + 3;

  Solver(int n)
      : n(n), bsize(get_sqrt(n)), event(n, -1), power(bsize + 1),
        hashes(n + 1, std::vector<Hash *>(bsize)) {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    power[0] = 1;
    for (int i = 1; i <= bsize; ++i) {
      power[i] = power[i - 1] * MAGIC;
    }
    blocks.emplace_back(bsize + 1);
    for (int i = 0; i < bsize; ++i) {
      hashes[n][i] = blocks.back().data();
    }
    {
      blocks.emplace_back(bsize + 1);
      auto block = blocks.back().data();
      block[n % bsize] = -1;
      for (int i = bsize - 1; i >= 0; --i) {
        block[i] += block[i + 1] * MAGIC;
      }
      hashes[n][n / bsize] = block;
    }
    {
      std::vector<int> next(n + 1, n);
      for (int i = n - 1; i >= 0; --i) {
        hashes[i] = hashes[i + 1];
        int j = next[a[i]];
        next[a[i]] = i;
        if (j < n) {
          event[j] = i;
          blocks.emplace_back(bsize + 1);
          int block_id = j / bsize;
          int base = block_id * bsize;
          auto block = blocks.back().data();
          Hash hh = 0;
          for (int k = bsize - 1; k >= 0; --k) {
            hh = hh * MAGIC + char_at(i, base + k);
            block[k] = hh;
          }
          hashes[i][block_id] = block;
        }
      }
    }

    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [this](int x, int y) {
      int length = get_lcp(x, y);
      return char_at(x, x + length) < char_at(y, y + length);
    });
    long long result = n * (n + 1LL) / 2;
    for (int i = 1; i < n; ++i) {
      result -= get_lcp(order[i - 1], order[i]);
    }
    std::cout << result << std::endl;
  }

  static inline int get_sqrt(int n) {
    int b = 0;
    while (b * b <= n) {
      b++;
    }
    return b;
  }

  int char_at(int s, int i) const {
    if (i >= n) {
      return -1;
    }
    return s <= event[i] ? i - event[i] : 0;
  }

  int get_LCP(int x, int y) const {
    if (x == y) {
      return n - x;
    }
    int length = 0;
    while (char_at(x, x + length) == char_at(y, y + length)) {
      length++;
    }
    return length;
  }

  int get_lcp(int x, int y) const {
    int length = 0;
    if (x % bsize > y % bsize) {
      std::swap(x, y);
    }
    auto &hashx = hashes[x];
    auto &hashy = hashes[y];
    int xi = x / bsize;
    int yi = y / bsize;
    int xr = x % bsize;
    int yr = y % bsize;
    if (xr == yr) {
      if (hashx[xi][xr] == hashy[yi][yr]) {
        length += bsize - xr;
        xi++, yi++;
        xr = yr = 0;
        while (hashx[xi][0] == hashy[yi][0]) {
          xi++, yi++;
          length += bsize;
        }
      }
    } else {
      while (true) {
        if (hashx[xi][xr] - power[bsize - yr] * hashx[xi][xr + bsize - yr] ==
            hashy[yi][yr]) {
          xr += bsize - yr;
          length += bsize - yr;
          yi++, yr = 0;
        } else {
          break;
        }
        if (hashy[yi][yr] - power[bsize - xr] * hashy[yi][yr + bsize - xr] ==
            hashx[xi][xr]) {
          yr += bsize - xr;
          length += bsize - xr;
          xi++, xr = 0;
        } else {
          break;
        }
      }
    }
    int xx = xi * bsize + xr;
    int yy = yi * bsize + yr;
    while (char_at(x, xx) == char_at(y, yy)) {
      xx++, yy++, length++;
    }
    return length;
  }

  int n, bsize;
  std::vector<int> event;
  std::vector<Hash> power;
  std::vector<std::vector<Hash *>> hashes;
  std::vector<std::vector<Hash>> blocks;
};

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    Solver{n};
  }
}
