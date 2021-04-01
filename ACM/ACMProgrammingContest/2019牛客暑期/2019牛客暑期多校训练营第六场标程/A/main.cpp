#include <bits/stdc++.h>

const int max_N = 2000 + 21;

int T;

char s[max_N], ss[233];

void testCase(int id) {
  printf("Case #%d: ", id);
  scanf("%s%s", s, ss);
  std::map<char, int> cnt;
  int n = strlen(s);
  for (int i = 0; i < n; ++i) {
    ++cnt[ss[s[i] - 'a']];
  }
  int h = cnt['h'];
  if (n * 0.25 <= h) {
    puts("Harmful");
    return;
  }
  if (n * 0.10 >= h) {
    puts("Recyclable");
    return;
  }
  int d = cnt['d'];
  int w = cnt['w'];
  puts(d >= 2 * w ? "Dry" : "Wet");
}

int main() {
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    testCase(i);
  }
}