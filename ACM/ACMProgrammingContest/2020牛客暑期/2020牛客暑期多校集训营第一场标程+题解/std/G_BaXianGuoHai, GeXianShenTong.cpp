#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>

// #define DEBUG
#ifdef DEBUG
#include <chrono>
#include <iostream>
#endif

const int DIM = 3;
const int MOD = 998244353;

struct Poly {
  int &operator[](int i) { return a[i]; }

  int operator[](int i) const { return a[i]; }

  Poly operator*(const Poly &b) {
    Poly result;
    for (int i = 0; i < DIM; ++i) {
      int tmp = 0;
      for (int j = 0; j < DIM; ++j) {
        tmp += 1LL * a[j] * b[(i + DIM - j) % DIM] % MOD;
        if (tmp >= MOD) {
          tmp -= MOD;
        }
      }
      result[i] = tmp;
    }
    return result;
  }

  int a[DIM];
};

Poly identity;

void init_identity() {
  memset(&identity, 0, sizeof(Poly));
  identity[0] = 1;
}

struct Generator {
  Generator(int n, int m, uint32_t z0, uint32_t a, uint32_t b)
      : n(n), m(m), z(z0), a(a), b(b), bases(n), exps(n * m) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < DIM; ++j) {
        z = z * a + b;
        bases[i][j] = z % MOD;
      }
    }
  }

  void sample() {
    for (int i = 0; i < n * m; ++i) {
      z = z * a + b;
      exps[i] = z;
    }
  }

  int n, m;
  uint32_t z, a, b;
  std::vector<Poly> bases;
  std::vector<uint32_t> exps;
};

#ifndef NO_MAIN
int main() {
  init_identity();
  int n, m, q, z0, a, b;
  scanf("%d%d%d%d%d%d", &n, &m, &q, &z0, &a, &b);
  Generator gen(n, m, z0, a, b);
  const int W = 16;
  std::vector<Poly> precomputed(n * m * 2);
  for (int i = 0; i < n; ++i) {
    auto power = precomputed[i * (m * 2)] = gen.bases[i];
    for (int j = 1; j < m * 2; ++j) {
      for (int _ = 0; _ < W; ++_) {
        power = power * power;
      }
      precomputed[i * (m * 2) + j] = power;
    }
  }
  std::vector<Poly> stats(1 << W);
  while (q--) {
    gen.sample();
    for (int i = 1; i < 1 << W; ++i) {
      stats[i] = identity;
    }
#ifdef DEBUG
    auto t0 = std::chrono::high_resolution_clock::now();
#endif
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        {
          int e = gen.exps[i * m + j] & (1 << W) - 1;
          stats[e] = stats[e] * precomputed[i * (m * 2) + j * 2];
        }
        {
          int e = gen.exps[i * m + j] >> W;
          stats[e] = stats[e] * precomputed[i * (m * 2) + j * 2 + 1];
        }
      }
    }
#ifdef DEBUG
    auto t1 = std::chrono::high_resolution_clock::now();
#endif
    Poly result = identity, suffix = identity;
    for (int i = 1 << W; --i;) {
      suffix = suffix * stats[i];
      result = result * suffix;
    }
#ifdef DEBUG
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0)
                     .count()
              << " "
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1)
                     .count()
              << std::endl;
#endif
    for (int i = 0; i < DIM; ++i) {
      printf("%d%c", result[i], " \n"[i + 1 == DIM]);
    }
  }
}
#endif
