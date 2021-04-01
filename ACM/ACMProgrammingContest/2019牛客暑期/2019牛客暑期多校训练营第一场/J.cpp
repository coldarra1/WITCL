#include <bits/stdc++.h>

static std::pair<uint64_t, uint64_t> fcompare(uint64_t x, uint32_t a,
                                              uint64_t y, uint32_t b) {
  uint64_t p = x / a; // p <= (x / a) < p + 1
  uint64_t q = y / b; // q <= (y / b) < q + 1
  if (p != q) {
    return {p, q};
  }
  x %= a;
  y %= b;
  return {x * b, y * a};
}

int main() {
  std::ios::sync_with_stdio(false);
  uint64_t x, y;
  uint32_t a, b;
  while (std::cin >> x >> a >> y >> b) {
    auto result = fcompare(x, a, y, b);
    if (result.first == result.second) {
      puts("=");
    } else if (result.first < result.second) {
      puts("<");
    } else {
      puts(">");
    }
  }
}
