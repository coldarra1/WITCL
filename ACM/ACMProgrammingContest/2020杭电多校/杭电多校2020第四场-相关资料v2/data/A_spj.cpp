const double eps = 1.010000e-09;
const double ans[] = {
  583.16037779824355269387,
  464.17160092592879677698,
  22.11638056391024719470,
  5.21352702677543994444,
  8.92704014729671928036,
  207.28594567977415774607,
};
const int T = sizeof(ans) / sizeof(ans[0]);

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

const int maxn = 3e5;
typedef double real;

int n;
char s[maxn + 1];
int m;
int head[maxn];

void WrongAnswer(void) {
  puts("WA");
  exit(0);
}

void Accepted(void) {
  puts("AC");
  exit(0);
}

int main(void) {
  n = fread(s, 1, maxn, stdin);
  s[n] = '\0';
  m = 0;
  for (int i = 0; i < n; ) {
    int j = i;
    while (j < n && s[j] != '\n') ++j;
    int k = j;
    while (k > i && isspace(s[k - 1])) --k;
    s[k] = '\0';
    head[m++] = i;
    i = j + 1;
  }
  while (m > 0 && s[head[m - 1]] == '\0') --m;

  if (m != T) {
    WrongAnswer();
  }
  for (int i = 0; i < T; ++i) {
    real x, y = ans[i];
    sscanf(s + head[i], "%lf", &x);
    if (!isfinite(x)) {
      WrongAnswer();
    }
    if (abs(x - y) > max(1.0, abs(y)) * eps) {
      WrongAnswer();
    }
  }
  Accepted();
}
