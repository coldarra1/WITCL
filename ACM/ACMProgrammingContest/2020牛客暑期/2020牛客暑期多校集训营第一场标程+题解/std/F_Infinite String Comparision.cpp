#include <cstdio>
#include <cstring>

static const int N = 100000;

template <typename T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

#ifndef NO_MAIN
int main() {
  static char a[N + 1], b[N + 1];
  while (scanf("%s%s", a, b) == 2) {
    int alen = strlen(a);
    int blen = strlen(b);
    int maxlen = alen + blen - gcd(alen, blen);
    char result = '=';
    for (int i = 0; i < maxlen && result == '='; ++i) {
      char ai = a[i % alen];
      char bi = b[i % blen];
      if (ai != bi) {
        result = ai < bi ? '<' : '>';
      }
    }
    printf("%c\n", result);
  }
}
#endif