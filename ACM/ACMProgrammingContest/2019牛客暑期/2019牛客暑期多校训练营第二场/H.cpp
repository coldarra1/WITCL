// Author: Yen-Jen Wang
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Data {
    int up, down, left, right;

    Data( int _up , int _down , int _left , int _right ) : up(_up), down(_down), left(_left), right(_right) {}

    bool operator == (const Data &rhs) const {
        return (up == rhs.up) && (down == rhs.down) && (left == rhs.left) && (right == rhs.right);
    }
};

vector<Data> vs[1000000 + 7];

int solve(int n, int m, vector<vector<int> > &array) {
    int lo, ro;
    int ans = 0, tmp = 0;
    vector<int> h(m + 1, 0), l(m + 1, 1), r(m + 1, m);

    for (int i = 1; i <= n; i++) {
        lo = 0;
        ro = m + 1;

        for (int j = 1; j <= m; j++) {
            if (array[i][j] == 0)
                h[j] = 0, l[j] = 1, lo = j;
            else
                h[j]++, l[j] = max(l[j], lo + 1);
        }

        for (int j = m; j >= 1; j--) {
            if (array[i][j] == 0)
                r[j] = m, ro = j;
            else {
                r[j] = min(r[j], ro - 1);
                int x = h[j] * (r[j] - l[j] + 1);
                if (x > tmp && x > 0) {
                    int up = i - h[j] + 1, down = i, left = l[j], right = r[j];
                    Data rect = Data(up, down, left, right);
                    vs[x].push_back(rect);
                    ans = max(tmp, max((down - up + 1) * (right - left), (down - up) * (right - left + 1)));
                    tmp = max(tmp, x);
                }
                else if(x > 0) {
                    int up = i - h[j] + 1, down = i, left = l[j], right = r[j];
                    Data rect = Data(up, down, left, right);
                    bool check = true;
                    for (int k = 0; k < (int)vs[x].size(); k++) {
                        if(vs[x][k] == rect) {
                            check = false;
                            break;
                        }
                    }
                    if (check)
                        ans = max(ans, x);
                    ans = max(ans, max((down - up + 1) * (right - left), (down - up) * (right - left + 1)));
                }
            }
        }
    }
    return ans;
}

int read_char() {
    char c;
    for (c = getchar(); !(c == '0' || c == '1'); c = getchar());
    return c - '0';
}

int main() {
    int n , m;
    scanf("%d%d", &n, &m);
	vector<vector<int> > array(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            array[i][j] = read_char();
    }
	printf("%d\n", solve(n, m, array));
    return 0;
}
