#include "testlib.h"

using std::string;

const int max_N = (int)2e3 + 21;

bool map[max_N][max_N];

int f[max_N], g[max_N];

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  int T = inf.readInt(1, 5, "T");
  inf.readEoln();
  for (int t = 1; t <= T; ++t) {
    int n = inf.readInt(1, 2000, "n");
    inf.readEoln();
    ouf.readToken("Case");
    ouf.readSpace();
    string id = "#" + toString(t) + ":";
    ouf.readToken(id);
    ouf.readSpace();
    string answer = ouf.readToken("Yes|No");
    ouf.readEoln();
    if (answer == "Yes") {
      if (n % 4 > 1) {
        quitf(_wa, "Wrong answer");
      }
      for (int i = 1; i <= n; ++i) {
        string str = ouf.readToken();
        if (str.length() != n) {
          quitf(_wa, "Wrong answer");
        }
        for (int j = 0; j < n; ++j) {
          if (str[j] != '1' && str[j] != '0') {
            quitf(_wa, "Wrong answer");
          }
          map[i][j + 1] = str[j] == '1';
        }
        ouf.readEoln();
      }
      for (int i = 1; i <= n; ++i) {
        g[i] = f[i] = ouf.readInt(1, n);
        if (i == n) ouf.readEoln();
        else ouf.readSpace();
      }
      std::sort(g + 1, g + 1 + n);
      for (int i = 1; i <= n; ++i) {
        if (g[i] != i) {
          quitf(_wa, "Wrong answer");
        }
      }
      for (int i = 1; i <= n; ++i) {
        if (map[i][i]) {
          quitf(_wa, "Wrong answer");
        }
        for (int j = i + 1; j <= n; ++j) {
          if (map[i][j] ^ map[j][i]) {
            quitf(_wa, "Wrong answer");
          }
          if (!(map[i][j] ^ map[f[i]][f[j]])) {
            quitf(_wa, "Wrong answer");
          }
        }
      }
    } else {
      if (n % 4 < 2) {
        quitf(_wa, "Wrong answer");
      }
    }
  }
  ouf.readEof();
  quitf(_ok, "All tests passed");
}