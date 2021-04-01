#include<cstdio>
using namespace std;
const int MAX_N = 10000;
int n, m;
char s[10][10][MAX_N + 5];
int len[10][10];
void read_input(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m * (m - 1) / 2; i++){
        char c[4];
        int sz;
        scanf("%s%d", c, &sz);
        int x = c[0] - 'a';
        int y = c[1] - 'a';
        if(x > y) {
            int tmp = x;
            x = y;
            y = tmp;
        }
        len[x][y] = sz;
        if(sz) {
            scanf("%s", s[x][y]);
        }
    }
}
int it[10][10];
char an[MAX_N + 5];
bool check() {
    for(int i = 0; i < m; i++) {
        for(int j = i + 1; j < m; j++) {
            int now = 0;
            for(int k = 0; k < n; k++) {
                if(an[k] == 'a' + i || an[k] == 'a' + j) {
                    if(an[k] != s[i][j][now]) return 0;
                    now++;
                }
            }
            if(now != len[i][j]) return 0;
        }
    }
    return 1;
}
bool solve() {
    for(int i = 0; i < n; i++) {
        bool stop[10] = {};
        for(int j = 0; j < m; j++) {
            for(int k = j + 1; k < m; k++) {
                if(!s[j][k][it[j][k]]) stop[j] = stop[k] = 1;
                else if(s[j][k][it[j][k]]=='a'+j)stop[k]=1;
                else stop[j]=1;
            }
        }
        bool done = false;
        for(int j = 0; j < m; j++) {
            if(!stop[j]) {
                an[i] = 'a' + j;
                for(int k = 0; k < m; k++) {
                    if(k < j) it[k][j] ++;
                    else if(k > j) it[j][k] ++;
                }
                an[i] = 'a' + j;
                done = true;
                break;
            }
        }
        if(!done) return 0;
    }
    if(!check()) return 0;
    puts(an);
    return 1;
}
int main() {
    read_input();
    if(!solve()) puts("-1");
    return 0;
}
