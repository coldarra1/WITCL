#include <bits/stdc++.h>

const int N = 100010;
const int M = 20;
const int YY = 10000;
const int MM = 13;
const int DD = 40;

int monthDay[MM] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int dayOfWeek[YY][MM][DD];
char tmp[M];

std::string solve(){
    int n;
    scanf("%d", &n);
    std::vector <std::string> s;
    for (int i = 0; i < n; ++ i){
        scanf("%s", tmp);
        s.emplace_back(tmp);
    }
    std::sort(s.begin(), s.end());
    s.erase(std::unique(s.begin(), s.end()), s.end());
    std::random_shuffle(s.begin(), s.end());
    std::vector <int> perm(10);
    for (int i = 0; i < 10; ++ i){
        perm[i] = i;
    }
    do{
        bool flag = true;
        for (int i = 0, sz = s.size(); i < sz; ++ i){
            int year = 0;
            for (int j = 0; j < 4; ++ j){
                year = year * 10 + perm[s[i][j] - 'A'];
            }
            int month = 0;
            for (int j = 5; j < 7; ++ j){
                month = month * 10 + perm[s[i][j] - 'A'];
            }
            int day = 0;
            for (int j = 8; j < 10; ++ j){
                day = day * 10 + perm[s[i][j] - 'A'];
            }
            if (year >= YY || month >= MM || day >= DD || dayOfWeek[year][month][day] != 5){
                flag = false;
                break;
            }
        }
        if (flag){
            std::string res;
            for (int i = 0; i < 10; ++ i){
                res += (char) (perm[i] + '0');
            }
            return res;
        }
    }
    while (std::next_permutation(perm.begin(), perm.end()));
    return "Impossible";
}

int main(){
    srand((unsigned) time(NULL));
    memset(dayOfWeek, -1, sizeof(dayOfWeek));
    int now = 0;
    for (int year = 1600; year < YY; ++ year){
        for (int month = 1; month < MM; ++ month){
            int dayNum = monthDay[month];
            if (month == 2){
                if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)){
                    ++ dayNum;
                }
            }
            for (int day = 1; day <= dayNum; ++ day){
                dayOfWeek[year][month][day] = now;
                now = (now + 1) % 7;
            }
        }
    }
    //printf("%d\n", dayOfWeek[2019][8][2]);
    for (int i = 0; i < YY; ++ i){
        for (int j = 0; j < MM; ++ j){
            for (int k = 0; k < DD; ++ k){
                if (dayOfWeek[i][j][k] != -1){
                    dayOfWeek[i][j][k] = (dayOfWeek[i][j][k] - 1 + 7) % 7;
                }
            }
        }
    }
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %s\n", i, solve().c_str());
    }
    return 0;
}
