# include <iostream>
 
const int maxn = 100000 + 5;

int n;
int m;
int FH[maxn];
 
int cnt[maxn] = {0};
 
int findfa(int x) {
    return (FH[x]==x) ? x : FH[x] = findfa(FH[x]);
}
 
void merge(int x, int y) {
    FH[x] = y;
}
 
int main() {
    scanf("%d %d", &n, &m);
     
    for (int i=1; i<=n; i++) {
        FH[i] = i;
    }
     
    for (int i=1; i<=m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
         
        if (findfa(u) != findfa(v)) {
            merge(FH[u], FH[v]);
        }
    }

    for (int i=1; i<=n; i++) {
        cnt[findfa(i)]++;
    }
     
    for (int i=1; i<=n; i++) {
        printf("%d ", cnt[findfa(i)]);
    }
     
    return 0;
}
