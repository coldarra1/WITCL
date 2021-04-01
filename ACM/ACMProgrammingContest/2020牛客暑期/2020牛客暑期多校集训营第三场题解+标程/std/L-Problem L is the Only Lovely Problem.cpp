#include<cstdio>
const int SIZE = 25;
char s[SIZE];
char need[]="lovely";
int main() {
    scanf("%s",s);
    for(int i = 0; i < 6; i++) {
        if(s[i] >= 'A' && s[i]<='Z') s[i] -= 'A' - 'a';
        if(s[i] != need[i]) {
            puts("ugly");
            return 0;
        }
    }
    puts("lovely");
}
