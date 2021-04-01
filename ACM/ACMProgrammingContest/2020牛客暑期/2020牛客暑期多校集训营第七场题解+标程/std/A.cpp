#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#define mp make_pair
#define pb push_back
#define left lef
#define right righ
#define rep(i,n) for(long long i=1;i<=n;++i)
#define bit(i) __builtin_popcount(i)
#define x1 gtmsub
#define y1 gtmshb
#define x2 gtmjtjl
#define y2 gtmsf
using namespace std;
const int maxn=250, inf = 200000000;
int f[9][2*maxn][2*maxn], n, r;
int Ans[20][50];
int main()
{
    int T;
    cin>>T;
    memset(Ans,255,sizeof(Ans));
    while (T--)
    {
        scanf("%d%d", &n, &r);
        if (Ans[n][r]!=-1)
        {
            printf("%d\n",Ans[n][r]);
            continue;
        }
        for (int i=0; i<=n; ++i)
            for (int j=maxn-n*r; j<=maxn+n*r; ++j)
                for (int k=maxn-n*r; k<=maxn+n*r; ++k)
                    f[i][j][k] = -1; 
        f[0][maxn][maxn] = 0;
        for (int i=-r; i<=r; ++i)
            for (int j=-r; j<=r; ++j)
                if (i*i+j*j<=r*r)
                    f[1][maxn+i][maxn+j] = 0;
        for (int i=2; i<=n; ++i)
        {
            for (int j=-r; j<=r; ++j)
            {
                int k = trunc(sqrt(r*r-j*j));
                for (int s1=maxn-(i-1)*r; s1<=maxn+(i-1)*r; ++s1)
                    for (int s2=maxn-(i-1)*r; s2<=maxn+(i-1)*r; ++s2)
                    {
                        int z = f[i-1][s1][s2]; int t1 = s1 - maxn; int t2 = s2 - maxn;
                        if (z==-1) continue;
                        f[i][s1+j][s2+k] = max(f[i][s1+j][s2+k], z + (t1*t1+t2*t2+z)/(i-1) - 2*(j*t1+k*t2) + (i-1)*(j*j+k*k));
                        f[i][s1+j][s2-k] = max(f[i][s1+j][s2-k], z + (t1*t1+t2*t2+z)/(i-1) - 2*(j*t1-k*t2) + (i-1)*(j*j+k*k));                  
                    } 
            }
        }
        int ans = 0;
        for (int i=maxn-n*r; i<=maxn+n*r; ++i)
            for (int j=maxn-n*r; j<=maxn+n*r; ++j)
                ans = max(ans, f[n][i][j]);
        printf("%d\n", ans);
        Ans[n][r]=ans;
    }
    
    return 0;
}           