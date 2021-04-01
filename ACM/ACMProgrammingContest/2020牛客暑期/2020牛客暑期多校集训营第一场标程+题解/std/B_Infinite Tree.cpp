#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

const int M = 100000;

static inline int get_exp(int p, int n) {
  int result = 0;
  while (n >= p) {
    result += (n /= p);
  }
  return result;
}

struct Entry {
  int exp, index, size;
};

struct Oracle {
  void add(const std::vector<int> &primes, int k, int n, int c) {
    // for (int i = 0; i < k; ++i) {
    //   result += 1LL * c * get_exp(primes[i], n);
    // }
    queries.push_back({k, n, c});
  }

  long long sum(int m, const std::vector<int> &primes) {
    long long result = 0;
    int processed = queries.size();
    std::vector<int> count(m);
    for (int i = 0; i < static_cast<int>(primes.size()) && primes[i] < m; ++i) {
      while (processed && queries[processed - 1].i == i) {
        int sum = 0;
        const auto &query = queries[--processed];
        for (int j = query.n; j > 0; j -= j & -j) {
          sum += count[j];
        }
        result += 1LL * sum * query.c;
      }
      int p = primes[i];
      for (long long pk = p; pk < m; pk *= p) {
        for (int d = pk; d < m; d += pk) {
          for (int j = d; j < m; j += j & -j) {
            count[j]++;
          }
        }
      }
    }
    return result;
  }

  struct Query {
    int i, n, c;
  };

  long long result = 0;
  std::vector<Query> queries;
};

template <typename OracleT> void solve() {
  static int sum[M + 2], maxdiv[M + 1];
  std::vector<int> primes;
  static Entry entries[M + 2];

  memset(maxdiv, -1, sizeof(maxdiv));
  for (int d = 2; d < M; ++d) {
    if (maxdiv[d] == -1) {
      maxdiv[d] = primes.size();
      primes.push_back(d);
    }
    for (int p : primes) {
      if (1LL * d * p >= M) {
        break;
      }
      maxdiv[d * p] = maxdiv[d];
      if (d % p == 0) {
        break;
      }
    }
  }
  int m;
  while (scanf("%d", &m) == 1) {
    sum[0] = sum[++m] = 0;
    for (int i = 1; i < m; ++i) {
      scanf("%d", sum + i);
    }
    for (int i = m; i--;) {
      sum[i] += sum[i + 1];
    }
    int k = 0;
    while (k < static_cast<int>(primes.size()) && primes[k] < m) {
      k++;
    }
    std::vector<std::pair<int, int>> dividens(m - 2);
    for (int i = 2; i < m; ++i) {
      dividens[i - 2] = std::make_pair(maxdiv[i], i);
    }
    std::sort(dividens.begin(), dividens.end(),
              std::greater<std::pair<int, int>>());
    int low = 1, high = m; // [low, high)
    long long result = 0;
    OracleT oracle;
    for (int j = 0; k--;) {
      int p = primes[k];
      int count = 1;
      entries[0] = {get_exp(p, low), low, sum[low]};
      int outSize = sum[0] - (sum[low] - sum[high]);
      if (entries[0].exp) {
        count = 2;
        entries[1] = entries[0];
        entries[0] = {0, -1, outSize};
      } else {
        entries[0].size += outSize;
      }
      while (j < m - 1 && dividens[j].first == k) {
        int d = dividens[j++].second;
        if (low < d && d <= high) {
          entries[count - 1].size -= sum[d];
          entries[count++] = {get_exp(p, d), d, sum[d]};
        }
      }
      entries[count - 1].size -= sum[high];
      entries[count].index = high;
      int total = 0, pivot = 0;
      while ((total + entries[pivot].size) * 2 <= sum[0]) {
        total += entries[pivot++].size;
      }
      for (int i = low; i < entries[pivot].index; ++i) {
        oracle.add(primes, k, i, sum[i] - sum[i + 1]);
      }
      for (int i = entries[pivot + 1].index; i < high; ++i) {
        oracle.add(primes, k, i, sum[i] - sum[i + 1]);
      }
      for (int i = 0; i < count; ++i) {
        result += 1LL * std::abs(entries[i].exp - entries[pivot].exp) *
                  entries[i].size;
      }
      low = entries[pivot].index, high = entries[pivot + 1].index;
      if (entries[pivot].size * 2 <= sum[0]) {
        for (int i = low; i < high; ++i) {
          oracle.add(primes, k, i, sum[i] - sum[i + 1]);
        }
        break;
      }
    }
    printf("%lld\n", result + oracle.sum(m, primes));
  }
}

#ifndef NO_MAIN
int main() { solve<Oracle>(); }
#endif
