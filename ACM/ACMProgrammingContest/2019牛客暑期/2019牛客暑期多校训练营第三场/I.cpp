#include <bits/stdc++.h>

using namespace std;

int T,N,a[100010];
int v[100010][3];
bool f[100010][3][3];
int ans[100010];
typedef pair<int,int> pii;
int from[100010][3][3];

int med(int x,int y,int z) {
    static int tmp[3];
    tmp[0] = x; tmp[1] = y; tmp[2] = z;
    sort(tmp,tmp+3);
    return tmp[1];
}

void gao(int i,int j,int k) {
    while(i >= 1) {
        ans[i] = v[i][j];
        int nxt = from[i][j][k];
        j = k;
        k = nxt;
        i--;
    }
}

int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&N);
        for (int i=2;i<N;i++) {
            scanf("%d",&a[i]);
        }
        a[0] = a[1] = a[2];
        a[N + 1] = a[N] = a[N - 1];
        for (int i=1;i<=N;i++) {
            for (int j=0;j<3;j++) {
                v[i][j] = a[i - 1 + j];
            }
            sort(v[i], v[i] + 3);
        }
        for (int i=1;i<=N;i++) {
            for (int j=0;j<3;j++) {
                for (int k=0;k<3;k++) {
                    f[i][j][k] = false;
                }
            }
        }
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                f[2][i][j] = true;
            }
        }
        bool findans = false;
        for (int i=3;i<=N;i++) {
            for (int j=0;j<3;j++) {
                for (int k=0;k<3;k++) {
                    for (int l=0;l<3;l++) {
                        if (!f[i-1][k][l]) continue;
                        if (med(v[i-2][l], v[i-1][k], v[i][j]) != a[i-1]) {
                            continue;
                        }
                        f[i][j][k] = true;
                        from[i][j][k] = l;
                        break;
                    }
                    if (i == N && f[i][j][k]) {
                        findans = true;
                        gao(i,j,k);
                        goto END;
                    }
                }
            }
        }
        END:
        if (!findans) {
            puts("-1");
        } else {
            for (int i=2;i<N;i++) {
                assert(med(ans[i-1],ans[i],ans[i+1]) == a[i]);
            }
            for (int i=1;i<=N;i++) {
                printf("%d%c",ans[i]," \n"[i==N]);
            }
        }
    }   
}