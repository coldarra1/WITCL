#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 1000000;
char s[MAX_N+1];
int n;
void assign() {
    char c[] = "09";
    int num[2] = {};
    for(int i = 0; i < n; i++) {
        if(s[i] == '?') num[i&1]++;
    }
    if((!num[0] || !num[1]) && ((num[0] + num[1]) & 1)) {
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '?') {
                if(cnt == 0 || (cnt & 1)) s[i] = '0';
                else s[i] = '9';
                cnt++;
            }
        }
        return;
    }
    if((num[0] & 1) != (num[1] & 1)) {
        for(int i = 1; i <= 2; i++) {
            for(int j = n - i; j >= 0; j -= 2) {
                if(s[j] == '?') {
                    s[j] = '0';
                    break;
                }
            }
        }
    }
    num[0] = num[1] = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '?') {
            s[i] = c[num[i & 1]];
            num[i & 1] ^= 1;
        }
    }
}
void solve() {
    scanf("%d", &n);
    scanf("%s", s);
    int base = 0;
    int qn = 0;
    for(int i = 0; i < n; i++) {
        if(i & 1) {
            if(s[i] == '?') {
                qn++;
                base += 10;
            } else {
                base += s[i] - '0';
            }
        } else {
            if(s[i] == '?') {
                qn++;
                base ++;
            } else {
                base += 11 - (s[i] - '0');
            }
        }
    }
    base %= 11;
    if(!base) { // negative
        assign();
    } else { // positive
        bool done = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '?') {
                if(i & 1) {
                    if(base != 10) {
                        s[i] = 10 - base + '0';
                        done = 1;
                        break;
                    }
                } else {
                    if(base != 1) {
                        s[i] = '0' - 1 + base;
                        done = 1;
                        break;
                    }
                }
            }
        }
        if(!done) {
            for(int i = n - 1; i >= 0; i--) {
                if(s[i] == '?') {
                    s[i] = '0';
                    break;
                }
            }
        }
        assign();
    }
    int v = 0;
    for(int i = 0; i < n; i++) {
        if(i & 1) v += s[i] - '0';
        else v -= s[i] - '0';
    }
    if(v % 11) putchar('-');
    puts(s);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}
