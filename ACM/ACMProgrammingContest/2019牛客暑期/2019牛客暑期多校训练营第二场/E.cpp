// Author: Yen-Jen Wang
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 50000 + 7;
const int MAX_M = 10 + 1;

const ll MOD = 1000000000 + 7;

struct Node {
    Node *lc, *rc;
    int l, r;
    ll dp[MAX_M][MAX_M];

    Node(int _l = 0, int _r = 0) : lc(0), rc(0), l(_l), r(_r) {
        memset(dp, 0, sizeof(dp));
    }
};

int N, M;
char mp[MAX_N][MAX_M];

void pull(Node *o) {
    //static ll dp1[MAX_M];
    //static ll dp2[MAX_M];

    Node *a = o->lc;
    Node *b = o->rc;

    for (int i = 1; i <= M; ++i) {
      for (int j = 1; j <= M; ++j) {
        o->dp[i][j] = 0;
      }
    }

    for (int i = 1; i <= M; ++i) {
      for (int j = 1; j <= M; ++j) {
        if (a->dp[i][j] == 0) {
          continue;
        }
        for (int k = 1; k <= M; ++k) {
          ll way = (a->dp[i][j] * b->dp[j][k]) % MOD;
          o->dp[i][k] = (o->dp[i][k] + way) % MOD;
        }
      }
    }

    /*for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= M; j++) {
            if (!a->dp[i][j])
                continue;
            if (mp[b->l][j]) 
                dp1[j] = a->dp[i][j];
            else
                dp1[j] = 0;
        }
        
        for (int j = 1; j <= M; j++) 
            dp2[j] = 0;
        
        ll s = 0;
        for (int j = 1; j <= M; j++) {
            if (mp[b->l][j] == 0)
                s = 0;
            else {
                s += dp1[j];
                if (s >= MOD)
                    s -= MOD;
            }
            dp2[j] += s;
            if (dp2[j] >= MOD)
                dp2[j] -= MOD;
        }

        s = 0;
        for (int j = M; j >= 0; j--) {
            if (mp[b->l][j] == 0)
                s = 0;
            dp2[j] += s;
            if (dp2[j] >= MOD)
                dp2[j] -= MOD;
            if (mp[b->l][j] != 0) {
                s += dp1[j];
                if (s >= MOD)
                    s -= MOD;
            }
        }

        for (int j = 1; j <= M; j++) {
            o->dp[i][j] = 0;
            for (int k = 1; k <= M; k++) {
                o->dp[i][j] += dp2[k] * b->dp[k][j] % MOD;
                if (o->dp[i][j] >= MOD)
                    o->dp[i][j] -= MOD;
            }
        }
    }*/
}

Node* build(int l, int r) {
    Node *o = new Node(l, r);
    if (l == r) {
        for (int i = 1; i <= M; i++) {
          for (int j = 1; j <= M; j++) {
            o->dp[i][j] = 0;
          }
          for (int j = i; j <= M; ++j) {
            if (mp[l][j] == 0) {
              break;
            }
            o->dp[i][j] = 1;
          }
          for (int j = i; j >= 1; --j) {
            if (mp[l][j] == 0) {
              break;
            }
            o->dp[i][j] = 1;
          }
        }
    }
    else {
        int m = (l + r) >> 1;
        o->lc = build(l, m);
        o->rc = build(m + 1, r);
        pull(o);
    }
    return o;
}

void maintain(Node *o, int p) {
    int l = o->l, r = o->r;
    if (l == r) {
        for (int i = 1; i <= M; i++) {
          for (int j = 1; j <= M; j++) {
            o->dp[i][j] = 0;
          }
          for (int j = i; j <= M; ++j) {
            if (mp[l][j] == 0) {
              break;
            }
            o->dp[i][j] = 1;
          }
          for (int j = i; j >= 1; --j) {
            if (mp[l][j] == 0) {
              break;
            }
            o->dp[i][j] = 1;
          }
        }
    }
    else {
        int m = (l + r) >> 1;
        if (p <= m)
            maintain(o->lc, p);
        else
            maintain(o->rc, p);
        pull(o);
    }
}

int main() {
    int Q;
    scanf("%d%d%d", &N, &M, &Q); 
    for (int i = 1; i <= N; i++) {
        scanf("%s", mp[i] + 1);
        for (int j = 1; j <= M; j++){
            mp[i][j] -= '0';
            mp[i][j] = 1 - mp[i][j];
        }
    }
    Node *tr = build(1, N);
    while (Q--) {
        int q, a, b;
        scanf("%d%d%d", &q, &a, &b);
        if (q == 1) {
            mp[a][b] ^= 1;
            maintain(tr, a);
        }
        else 
            printf("%lld\n", tr->dp[a][b]);
    }
    return 0;
}
