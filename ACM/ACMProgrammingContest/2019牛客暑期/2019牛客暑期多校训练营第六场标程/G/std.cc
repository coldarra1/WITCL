#include <bits/stdc++.h>

using namespace std;

int days[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int ReturnWeekDay(int yy, int mm, int dd) {
    if (mm == 1 || mm == 2) {
        -- yy;
        mm += 12;
    }
    int c = yy / 100, y = yy % 100;
    int ww = y + y / 4 + c / 4 - 2 * c + 26 * (mm + 1) / 10 + dd - 1;
    return (ww % 7 + 7) % 7;
}

bool validDay(int x) {
    int y = x / 10000;
    if (y < 1600 || y > 9999) {
        return false;
    }
    int is_leap = y % 400 == 0 || y % 100 != 0 && y % 4 == 0;
    int m = x / 100 % 100;
    if (m < 1 || m > 12) {
        return false;
    }
    int d = x % 100;
    if (d < 1 || d > days[m] + (m == 2 && is_leap)) {
        return false;
    }
    return ReturnWeekDay(y, m, d) == 5;
}

int p[3628800][10];

void init() {
    int a[10];
    for (int i = 0 ; i < 10 ; ++ i) {
        a[i] = i;
    }
    int cnt = 0;
    do {
        memcpy(p[cnt ++], a, sizeof(a));
    } while (next_permutation(a , a + 10));
}

bool check(string date, int* a) {
    int x = 0;
    for (int i = 0 ; i < date.size() ; ++ i) {
        if (isalpha(date[i])) {
            x = x * 10 + a[date[i] - 'A'];
        }
    }
    return validDay(x);
}

int n;

void work() {
    scanf("%d" , &n);
    vector<string> v;
    for (int i = 0 ; i < n ; ++ i) {
        static char str[20];
        scanf("%s" , str);
        v.emplace_back(str);
    }
    sort(v.begin() , v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    random_shuffle(v.begin() , v.end());
    n = v.size();

    vector<int> candidates;
    for (int i = 0 ; i < 3628800 ; ++ i) {
        if (check(v[0] , p[i])) {
            candidates.emplace_back(i);
        }
    }

    int cur = 1;
    while (cur < n && candidates.size() > 10) {
        int size = 0;
        for (auto &i : candidates) {
            if (check(v[cur], p[i])) {
                candidates[size ++] = i;
            }
        }
        ++ cur;
        candidates.resize(size);
    }

    static int ca = 0;
    printf("Case #%d: " , ++ ca);
    for (auto &i : candidates) {
        bool valid = 1;
        for (int j = cur ; j < n ; ++ j) {
            if (!check(v[j], p[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            for (int j = 0 ; j < 10 ; ++ j) {
                printf("%d" , p[i][j]);
            }
            puts("");
            return;
        }
    }
    puts("Impossible");
}

int main() {
    init();
    int T;
    scanf("%d" , &T);
    while (T --) {
        work();
    }
}