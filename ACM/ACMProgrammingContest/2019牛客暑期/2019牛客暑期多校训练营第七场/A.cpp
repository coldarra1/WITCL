#include <bits/stdc++.h>
using namespace std;
 
bool isOk(string s) {
    int n = s.length();
    for (int i = 1; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (s[j] < s[(i+j)%n]) break;
            if (s[j] > s[(i+j)%n]) return false;
        }
    return true;
}
int main() {
    int T;
    string s;
    scanf("%d", &T);
    assert(T <= 300);
    while (T--) {
        cin>>s;
        int n = s.length();
        assert(n > 0 && n <= 200);
        int i = 0;
        while (i < n) {
            for (int j = n-i; j > 0; j--) {
                if (isOk(s.substr(i, j))) {
                    cout<<s.substr(i, j);
                    i += j;
                    if (i < n)printf(" ");
                    break;
                }
            }
        }
        cout<<endl;
    }
    return 0;
 
}
