#include <bits/stdc++.h>

std::vector<int> read(int n) {
  std::vector<int> result(n);
  std::vector<std::pair<int, int>> stack;
  stack.emplace_back(0, -1);
  for (int i = 0, a; i < n; ++i) {
    scanf("%d", &a);
    while (stack.back().first > a) {
      stack.pop_back();
    }
    result[i] = stack.back().second;
    stack.emplace_back(a, i);
  }
  return result;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    auto a = read(n);
    auto b = read(n);
    int length = 0;
    while (length < n && a[length] == b[length]) {
      length++;
    }
    printf("%d\n", length);
  }
}
