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
int gcd(int x,int y)
{
    if(x%y==0)return y;
    return gcd(y,x%y);
}
int main()
{
    int T;
    cin>>T;
    while (T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        int tot=n+m-gcd(n,m);
        printf("%d\n",tot);
        if(n>m)swap(n,m);
        static vector<int> ans; ans.clear();
        while(n!=m)
        {
            for(int i=1;i<=n;i++)ans.pb(n);
            m=m-n;
            if(n>m)swap(n,m);
        }
        for(int i=1;i<=n;i++)ans.pb(n);
        for(int i=0;i<tot;i++)printf("%d%c",ans[i],i==tot-1?'\n':' ');
    }
    return 0;   
}