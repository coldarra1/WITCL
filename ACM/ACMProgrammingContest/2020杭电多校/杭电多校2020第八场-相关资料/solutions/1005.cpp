#include <bits/stdc++.h>
using namespace std;

int n, m, x, y, sx, sy, T;

namespace T1 {
bool bo, ud, BO[201][201];
int a[201][201], dx[4], dy[4];
void print(int x, int y) {
    if (ud)
        x = n + 1 - x;
    if (bo)
        printf("%d %d\n", y, x);
    else
        printf("%d %d\n", x, y);
}
void dfs(int x, int y) {
    if (BO[x][y])
        return;
    BO[x][y] = 1, print(x, y);
    dfs(x + dx[a[x][y]], y + dy[a[x][y]]);
}
void solve() {
    bo = ud = 0;
    dy[0] = dy[1] = dx[2] = dx[3] = 0;
    dx[0] = dy[2] = -1, dx[1] = dy[3] = 1;
    if (n > m)
        swap(n, m), swap(x, y), swap(sx, sy), bo = 1;
    if (n == 1) {
        if (y != 1 && y != m) {
            puts("-1");
            return;
        }
        if (y == 1) {
            if (sy != 2 && sy != m) {
                puts("-1");
                return;
            }
            printf("%d\n", n * m - 1);
            if (sy == m)
                for (int i = sy; i > 1; i--) print(1, i);
            else
                for (int i = sy; i <= m; i++) print(1, i);
        } else {
            if (sy != 1 && sy != m - 1) {
                puts("-1");
                return;
            }
            printf("%d\n", n * m - 1);
            if (sy == m - 1)
                for (int i = sy; i >= 1; i--) print(1, i);
            else
                for (int i = sy; i < m; i++) print(1, i);
        }
        return;
    }
    if ((x & 1) != (y & 1)) {
        puts("-1");
        return;
    }
    if (y == 1 || y == m)
        swap(n, m), swap(x, y), swap(sx, sy), bo ^= 1;
    if (x == 1)
        ud = 1, x = n + 1 - x, sx = n + 1 - sx;
    if (x == n) {
        for (int i = 1; i < y; i += 2) {
            a[n - 1][i] = 1, a[n][i] = 3;
            a[n - 1][i + 1] = 3, a[n][i + 1] = 0;
        }
        a[n - 1][y] = 3;
        for (int i = y + 1; i < m; i += 2) {
            a[n - 1][i] = 1, a[n][i] = 3;
            a[n - 1][i + 1] = 3, a[n][i + 1] = 0;
        }
        a[n - 1][m] = 0;
        for (int i = 1; i < n - 1; i++) a[i][1] = 1;
        for (int i = n - 2; i > 0; i -= 2) {
            for (int j = 3; j <= m; j++) a[i][j] = 2;
            for (int j = 2; j < m; j++) a[i - 1][j] = 3;
            a[i][2] = a[i - 1][m] = 0;
        }
        a[1][2] = 2;
    } else {
        if (!(x & 1)) {
            for (int i = 1; i < y - 1; i += 2) {
                for (int j = 1; j < x; j++) a[j][i] = 1;
                for (int j = 2; j <= x; j++) a[j][i + 1] = 0;
                a[x][i] = a[1][i + 1] = 2;
            }
            for (int j = 1; j < x; j++) a[j][y - 1] = 1;
            a[x][y - 1] = 2, a[x][1] = 1;
            for (int i = x + 1; i < n; i += 2) {
                for (int j = 1; j < y; j++) a[i][j] = 3;
                for (int j = 2; j <= y; j++) a[i + 1][j] = 2;
                a[i][y] = a[i + 1][1] = 1;
            }
            for (int j = 1; j <= y; j++) a[n][j] = 3;
            for (int i = y + 1; i < m; i += 2) {
                for (int j = x + 1; j <= n; j++) a[j][i] = 0;
                for (int j = x; j < n; j++) a[j][i + 1] = 1;
                a[x][i] = a[n][i + 1] = 3;
            }
            for (int j = x; j <= n; j++) a[j][m] = 0;
            for (int i = 1; i < x - 1; i += 2) {
                for (int j = y + 1; j <= m; j++) a[i][j] = 2;
                for (int j = y; j < m; j++) a[i + 1][j] = 3;
                a[i][y] = a[i + 1][m] = 0;
            }
            for (int j = y + 1; j <= m; j++) a[x - 1][j] = 2;
            a[x - 1][y] = 0, a[1][y] = 2;
        } else {
            for (int i = 1; i < x; i += 2) {
                for (int j = 2; j < y; j++) a[i][j] = 2;
                for (int j = 1; j < y - 1; j++) a[i + 1][j] = 3;
                a[i][1] = a[i + 1][y - 1] = 1;
            }
            for (int j = 2; j < y; j++) a[x][j] = 2;
            a[x][1] = 1;
            for (int i = 1; i < y; i += 2) {
                for (int j = x + 1; j < n; j++) a[j][i] = 1;
                for (int j = x + 2; j <= n; j++) a[j][i + 1] = 0;
                a[n][i] = a[x + 1][i + 1] = 3;
            }
            for (int j = x + 1; j < n; j++) a[j][y] = 1;
            a[n][y] = 3;
            for (int i = x; i < n; i += 2) {
                for (int j = y + 1; j < m; j++) a[i][j] = 3;
                for (int j = y + 2; j <= m; j++) a[i + 1][j] = 2;
                a[i][m] = a[i + 1][y + 1] = 0;
            }
            for (int j = y + 1; j < m; j++) a[n][j] = 3;
            a[n][m] = 0;
            for (int i = y; i < m; i += 2) {
                for (int j = 2; j < x; j++) a[j][i] = 0;
                for (int j = 1; j < x - 1; j++) a[j][i + 1] = 1;
                a[1][i] = a[x - 1][i + 1] = 2;
            }
            for (int j = 2; j < x; j++) a[j][m] = 0;
            a[1][m] = 2;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) BO[i][j] = 0;
    printf("%d\n", n * m - 1);
    dfs(sx, sy);
}
}  // namespace T1

namespace T2 {
bool bo, f[2][35][52][2], ud, a[201][201][4], BO[201][201];
int dx[4], dy[4], p[1001][5], tot, lax[201][35][52][2], lay[201][35][52][2], laz[201][35][52][2],
    la1[201][35][52][2], la2[201][35][52][2], po[100010], X, Y;
// 0:up 1:down 2:left 3:right
void print(int x, int y) {
    if (ud)
        x = n + 1 - x;
    if (bo)
        printf("%d %d\n", y, x);
    else
        printf("%d %d\n", x, y);
}
int calc(int a[]) {
    int ans = 0;
    for (int j = 0; j < 5; j++) ans = ans * 10 + a[j];
    return ans;
}
void dfs(int x, int y) {
    if (x > y) {
        tot++;
        for (int i = y + 1; i < 5; i++) p[tot - 1][i] = 0;
        for (int i = 0; i < 5; i++) p[tot][i] = p[tot - 1][i];
        return;
    }
    for (int i = 0; i < x; i++)
        if (p[tot][i] == i)
            p[tot][x] = i, dfs(x + 1, y);
    p[tot][x] = x, dfs(x + 1, y);
}
bool check(int x, int y, int l, int r) {
    bool bo;
    for (int i = 0; i < r - l + 1; i++)
        if (!(x >> i & 1)) {
            bo = 0;
            for (int j = 0; j < r - l + 1; j++)
                if (p[y][j] == p[y][i] && (x >> j & 1)) {
                    bo = 1;
                    break;
                }
            if (!bo)
                return 0;
        }
    return 1;
}
struct Solver {
    int pp[6], ttn, tt[7], pt[6], i, j, k, I, J, K, l, r, id;
    bool boc[6], BOO[6];
    void con(int x, int y) {
        if (pp[x] > pp[y])
            swap(x, y);
        for (int o = 0, nw = pp[y]; o < r - l + 1; o++)
            if (pp[o] == nw)
                pp[o] = pp[x];
    }
    void DFSS(int nw, int nwi) {
        while (nw < r - l + 1 && BOO[nw]) nw++;
        if (nw < r - l + 1) {
            int ll = nw, rr = nw;
            while (rr < r - l && !BOO[rr + 1]) rr++;
            if (ll == rr)
                return;
            if (rr == ll + 1)
                boc[ll] = 1, DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 1)), boc[ll] = 0;
            else if (rr == ll + 2)
                boc[ll] = boc[ll + 1] = 1, DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 2)),
                boc[ll] = boc[ll + 1] = 0;
            else if (rr == ll + 3) {
                boc[ll] = boc[ll + 1] = boc[ll + 2] = 1;
                DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 3)), boc[ll + 1] = 0;
                DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 1) | (1 << ll + 2) | (1 << ll + 3));
                boc[ll] = boc[ll + 2] = 0;
            } else {
                boc[ll] = boc[ll + 1] = boc[ll + 2] = boc[ll + 3] = 1;
                DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 4)), boc[ll + 1] = 0;
                DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 1) | (1 << ll + 2) | (1 << ll + 4));
                boc[ll + 1] = 1, boc[ll + 2] = 0;
                DFSS(rr + 1, nwi | (1 << ll) | (1 << ll + 2) | (1 << ll + 3) | (1 << ll + 4));
                boc[ll] = boc[ll + 1] = boc[ll + 3] = 0;
            }
            return;
        }
        for (int o = 0; o < r - l + 1; o++) pp[o] = o;
        for (int o = r - l + 1; o < 5; o++) pp[o] = 0;
        for (int o = 0; o < r - l + 1; o++)
            if (I >> o & 1)
                for (int oo = o + 1; oo < r - l + 1; oo++)
                    if (I >> oo & 1)
                        if (pp[o] != pp[oo] && p[j][o] == p[j][oo])
                            con(o, oo);
        for (int o = 0; o < r - l + 1; o++)
            if (id == y && o + l == x) {
                if (o == 0)
                    con(o, 1);
                else
                    con(0, o);
                break;
            }
        for (int o = 0; o < r - l; o++)
            if (boc[o] && pp[o] != pp[o + 1])
                con(o, o + 1);
        int nwj = po[calc(pp)];
        f[Y][nwi][nwj][k] = 1;
        lax[id][nwi][nwj][k] = I;
        lay[id][nwi][nwj][k] = J;
        laz[id][nwi][nwj][k] = K;
        la1[id][nwi][nwj][k] = I;
        la2[id][nwi][nwj][k] = 0;
        for (int i = 0; i < r - l; i++)
            if (boc[i])
                la2[id][nwi][nwj][k] |= (1 << i);
    }
    void DFS(int nw) {
        if (nw == ttn + 1) {
            memset(boc, 0, sizeof(boc));
            for (int o = 1; o <= ttn; o++) {
                for (int oo = tt[o]; oo < pt[o]; oo++) BOO[oo] = 1, boc[oo] = 1;
                for (int oo = pt[o]; oo < tt[o]; oo++) BOO[oo] = 1, boc[oo] = 1;
                BOO[tt[o]] = BOO[pt[o]] = 1;
            }
            int nwi = 0;
            for (int o = 1; o <= ttn; o++)
                if (pt[o] != tt[o + 1] && pt[o] != tt[o - 1])
                    nwi |= (1 << pt[o]);
            DFSS(0, nwi);
            for (int o = 1; o <= ttn; o++) {
                for (int oo = tt[o]; oo < pt[o]; oo++) BOO[oo] = 0;
                for (int oo = pt[o]; oo < tt[o]; oo++) BOO[oo] = 0;
                BOO[tt[o]] = BOO[pt[o]] = 0;
            }
            return;
        }
        for (int o = tt[nw]; o > tt[nw - 1] && o > pt[nw - 1]; o--)
            if (!BOO[o])
                pt[nw] = o, DFS(nw + 1);
            else
                break;
        bool booo = 1;
        for (int o = tt[nw] + 1; o < tt[nw + 1]; o++)
            if (!BOO[o])
                pt[nw] = o, DFS(nw + 1);
            else {
                booo = 0;
                break;
            }
        if (booo && nw < ttn && !BOO[tt[nw + 1]])
            pt[nw] = tt[nw + 1], pt[nw + 1] = tt[nw], DFS(nw + 2);
    }
    void trans(int ii, int jj, int kk, int II, int JJ, int KK, int ll, int rr, int idd) {
        i = ii, j = jj, k = kk, I = II, J = JJ, K = KK, l = ll, r = rr, id = idd;
        for (int o = 0; o < r - l + 1; o++) pp[o] = p[j][o];
        for (int o = r - l + 1; o < 5; o++) pp[o] = 0;
        for (int o = 0; o < r - l + 1; o++)
            if ((i ^ I) >> o & 1) {
                pp[o] = o;
                for (int la = -1, q = o + 1; q < r - l + 1; q++)
                    if (pp[q] == o)
                        pp[q] = ((la < 0) ? (la = q) : la);
            }
        j = po[calc(pp)], ttn = 0;
        for (int o = 0; o < r - l + 1; o++)
            if ((i >> o & 1) && !BOO[o])
                tt[++ttn] = o;
        tt[0] = pt[0] = -1, tt[ttn + 1] = r - l + 1, DFS(1);
    }
} solver;
bool work(int l, int r) {
    tot = 0, dfs(0, r - l), tot--;
    for (int i = 0; i <= tot; i++) po[calc(p[i])] = i;
    memset(f, 0, sizeof(f));
    f[0][0][0][0] = 1, X = 1, Y = 0;
    for (int i = 1; i <= m; i++) {
        X ^= 1, Y ^= 1;
        for (int j = 0; j < (1 << r - l + 1); j++)
            for (int k = 0; k <= tot; k++)
                for (int o = 0; o < 2; o++) {
                    if (f[X][j][k][o] && (i == 1 || check(j, k, l, r))) {
                        int nw = j;
                        for (int oo = 0; oo < r - l + 1; oo++) solver.BOO[oo] = 0;
                        if (y == i) {
                            if (j >> (x - l) & 1) {
                                f[X][j][k][o] = 0;
                                continue;
                            }
                            solver.BOO[x - l] = 1;
                        }
                        if (sy == i) {
                            if (j >> (sx - l) & 1)
                                solver.BOO[sx - l] = 1;
                            else
                                nw |= (1 << sx - l);
                        }
                        if (!o) {
                            for (int oo = 0; oo < r - l + 1; oo++)
                                if ((y != i || x != oo + l) && (sy != i || sx != oo + l)) {
                                    if (j >> oo & 1)
                                        solver.BOO[oo] = 1;
                                    else
                                        nw ^= (1 << oo);
                                    solver.trans(nw, k, 1, j, k, o, l, r, i);
                                    if (j >> oo & 1)
                                        solver.BOO[oo] = 0;
                                    else
                                        nw ^= (1 << oo);
                                }
                        }
                        solver.trans(nw, k, o, j, k, o, l, r, i);
                    }
                    f[X][j][k][o] = 0;
                }
    }
    if (!f[Y][0][0][1])
        return 0;
    int nwx = 0, nwy = 0, nwz = 1, NWX, NWY, NWZ;
    for (int i = m; i; i--) {
        for (int j = 0; j < r - l + 1; j++)
            if (la1[i][nwx][nwy][nwz] >> j & 1)
                a[l + j][i][2] = a[l + j][i - 1][3] = 1;
        for (int j = 0; j < r - l; j++)
            if (la2[i][nwx][nwy][nwz] >> j & 1)
                a[l + j][i][1] = a[l + j + 1][i][0] = 1;
        NWX = nwx, NWY = nwy, NWZ = nwz;
        nwx = lax[i][NWX][NWY][NWZ];
        nwy = lay[i][NWX][NWY][NWZ];
        nwz = laz[i][NWX][NWY][NWZ];
    }
    return 1;
}
void Dfs(int x, int y) {
    if (BO[x][y])
        return;
    BO[x][y] = 1, print(x, y);
    for (int i = 0; i < 4; i++)
        if (a[x][y][i])
            Dfs(x + dx[i], y + dy[i]);
}
void solve() {
    bo = ud = 0;
    dy[0] = dy[1] = dx[2] = dx[3] = 0;
    dx[0] = dy[2] = -1, dx[1] = dy[3] = 1;
    if (n > m)
        swap(n, m), swap(x, y), swap(sx, sy), bo = 1;
    if (n == 1) {
        if (y != 1 && y != m) {
            puts("-1");
            return;
        }
        if (y == 1) {
            if (sy != 2 && sy != m) {
                puts("-1");
                return;
            }
            printf("%d\n", n * m - 1);
            if (sy == m)
                for (int i = sy; i > 1; i--) print(1, i);
            else
                for (int i = sy; i <= m; i++) print(1, i);
        } else {
            if (sy != 1 && sy != m - 1) {
                puts("-1");
                return;
            }
            printf("%d\n", n * m - 1);
            if (sy == m - 1)
                for (int i = sy; i >= 1; i--) print(1, i);
            else
                for (int i = sy; i < m; i++) print(1, i);
        }
        return;
    }
    if (!((sx - x + sy - y + 1000) & 1)) {
        puts("-1");
        return;
    }
    if (n <= 5) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) a[i][j][0] = a[i][j][1] = a[i][j][2] = a[i][j][3] = 0;
        if (!work(1, n)) {
            puts("-1");
            return;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) BO[i][j] = 0;
        printf("%d\n", n * m - 1), Dfs(sx, sy);
        return;
    }
    if (m & 1)
        swap(n, m), swap(x, y), swap(sx, sy), bo ^= 1;
    if (sx < x)
        x = n + 1 - x, sx = n + 1 - sx, ud = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j][0] = a[i][j][1] = a[i][j][2] = a[i][j][3] = 0;
    int l = x, r = sx, Sx = sx, Sy = sy;
    if (l == 2)
        l--;
    if (r == n - 1) {
        if (r - l > 3) {
            if (sy != m) {
                for (int i = 2; i <= sy; i++) a[sx][i][2] = 1;
                a[sx][1][1] = a[sx][sy + 1][0] = a[sx + 1][m][0] = 1;
                for (int i = 1; i < m; i++) a[sx + 1][i][3] = 1;
                for (int i = sy + 2; i <= m; i++) a[sx][i][2] = 1;
                r--, sx--, sy++;
            } else {
                a[sx][sy][1] = a[sx + 1][1][0] = a[sx][sy - 1][0] = 1;
                for (int i = 2; i <= m; i++) a[sx + 1][i][2] = 1;
                for (int i = 1; i < sy - 1; i++) a[sx][i][3] = 1;
                r--, sx--, sy--;
            }
        } else
            r++;
    }
    if (r - l > 4 && sy != 1 && sy != m) {
        if (sy & 1) {
            for (int i = sy; i < m; i++) a[sx][i][3] = 1;
            for (int i = sy; i <= m; i++) a[sx - 1][i][2] = 1;
            for (int i = 1; i < sy; i += 2)
                a[sx - 1][i][2] = a[sx][i][0] = a[sx][i + 1][2] = a[sx - 1][i + 1][1] = 1;
            a[sx][m][0] = a[sx - 1][1][0] = 1, a[sx - 1][1][2] = 0;
            sx -= 2, sy = 1, r -= 2;
        } else {
            for (int i = 2; i <= sy; i++) a[sx][i][2] = 1;
            for (int i = 1; i <= sy; i++) a[sx - 1][i][3] = 1;
            for (int i = sy + 1; i < m; i += 2)
                a[sx - 1][i][1] = a[sx][i][3] = a[sx][i + 1][0] = a[sx - 1][i + 1][3] = 1;
            a[sx][1][0] = a[sx - 1][m][0] = 1, a[sx - 1][m][3] = 0;
            sx -= 2, sy = m, r -= 2;
        }
    }
    while (r - l > 4) {
        for (int i = 1; i < m; i++) a[sx - (sy == m)][i][3] = 1;
        for (int i = 2; i <= m; i++) a[sx - (sy == 1)][i][2] = 1;
        a[sx - (sy == m)][m][0] = a[sx - (sy == 1)][1][0] = 1;
        sx -= 2, r -= 2;
    }
    if (r - l < 3) {
        if (l == r) {
            if (l <= 3)
                r++;
            else
                l--;
        } else if (r - l == 1) {
            if (l == 1)
                r += 2;
            else if (l == 4)
                l -= 3;
            else
                l -= 2;
        } else {
            if (l == 1)
                r++;
            else if (l == 3)
                l -= 2;
            else
                l--;
        }
    }
    if (!work(l, r)) {
        puts("-1");
        return;
    }
    sx = Sx, sy = Sy, r = max(r, sx);
    if (r < n - 1) {
        for (int i = 1; i < m; i++) a[r + 1][i][3] = 1;
        for (int i = 2; i <= m; i++) a[r + 1][i][2] = 1;
        a[r + 1][1][1] = a[r + 1][m][1] = a[r + 2][1][0] = a[r + 2][m][0] = 1;
        for (int i = 1; i < m; i += 2) {
            for (int j = r + 2; j < n; j++) a[j][i][1] = a[j][i + 1][1] = 1;
            for (int j = r + 3; j <= n; j++) a[j][i][0] = a[j][i + 1][0] = 1;
            a[n][i][3] = a[n][i + 1][2] = 1;
            if (i != m - 1)
                a[r + 2][i + 1][3] = a[r + 2][i + 2][2] = 1;
        }
        for (int i = 1; i <= m; i++)
            if (a[r][i][3] || a[r][i][2]) {
                if (a[r][i][2])
                    i--;
                a[r][i][3] = a[r][i + 1][2] = 0;
                a[r][i][1] = a[r][i + 1][1] = 1;
                a[r + 1][i][3] = a[r + 1][i + 1][2] = 0;
                a[r + 1][i][0] = a[r + 1][i + 1][0] = 1;
                break;
            }
    }
    if (l != 1) {
        for (int i = 1; i < m; i++) a[l - 1][i][3] = 1;
        for (int i = 2; i <= m; i++) a[l - 1][i][2] = 1;
        a[l - 1][1][0] = a[l - 1][m][0] = a[l - 2][1][1] = a[l - 2][m][1] = 1;
        for (int i = 1; i < m; i += 2) {
            for (int j = 1; j <= l - 3; j++) a[j][i][1] = a[j][i + 1][1] = 1;
            for (int j = 2; j <= l - 2; j++) a[j][i][0] = a[j][i + 1][0] = 1;
            a[1][i][3] = a[1][i + 1][2] = 1;
            if (i != m - 1)
                a[l - 2][i + 1][3] = a[l - 2][i + 2][2] = 1;
        }
        for (int i = 1; i <= m; i++)
            if (a[l][i][3] || a[l][i][2]) {
                if (a[l][i][2])
                    i--;
                a[l][i][3] = a[l][i + 1][2] = 0;
                a[l][i][0] = a[l][i + 1][0] = 1;
                a[l - 1][i][3] = a[l - 1][i + 1][2] = 0;
                a[l - 1][i][1] = a[l - 1][i + 1][1] = 1;
                break;
            }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) BO[i][j] = 0;
    printf("%d\n", n * m - 1);
    Dfs(sx, sy);
}
}  // namespace T2

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d %d %d", &n, &m, &x, &y, &sx, &sy);
        if ((n & 1) && (m & 1))
            T1::solve();
        else
            T2::solve();
    }
    return 0;
}