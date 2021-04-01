//
// Created by calabash_boy on 2020/4/13.
//
#include<bits/stdc++.h>
using namespace std;
const int REPEAT = 3;
const int maxn = 2e6+ 100;
typedef long long ll;
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26], fa[maxn*2], l[maxn*2];
    int last,cnt;
    int match_len[maxn*2], match_times[maxn*2];
    int label[maxn*2], mx[maxn*2];
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
        for (int i=0;i<maxn*2;i++) match_len[i] = INT_MAX;
    }
    void init(char *s){
        while (*s){
            add(*s-'a');s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void run(char * s,int Label){
        vector<pair<int,int> > nodes;
        vector<int> a,b;
        int now = 1, len = 0;
        while (*s){
            int ch = *s - 'a';
            while (now != 1 and !nxt[now][ch]){
                now = fa[now];
                len = l[now];
            }
            if (nxt[now][ch]){
                now = nxt[now][ch];
                len ++;
            }
            nodes.push_back(make_pair(now,len));
            a.push_back(now);
            s ++;
        }
        auto cmp = [&](int x,int y){
            return l[x] > l[y];
        };
        sort(a.begin(),a.end(),cmp);
        a.erase(unique(a.begin(),a.end()),a.end());
        for (int x : a){
            int temp = x;
            while (temp != 1 and label[temp] != Label){
                b.push_back(temp);
                label[temp] = Label;
                mx[temp] = 0;
                temp = fa[temp];
            }
        }
        sort(b.begin(),b.end(),cmp);
        for (auto pr : nodes){
            mx[pr.first] = max(mx[pr.first],pr.second);
        }
        for (int x : b){
            mx[fa[x]] = max(mx[fa[x]],l[fa[x]]);
            match_len[x] = min(match_len[x],mx[x]);
            match_times[x] ++;
        }
    }
    ll calc(int tot_times){
        ll tot = 0;
        for (int i = 1;i <= cnt;i ++){
            if (match_times[i] == tot_times){
                tot += max(0,match_len[i] - l[fa[i]]);
            }
        }
        return tot;
    }
}sam;
struct KMP{
    int nxt[maxn];int len;
    char t[maxn];
    void clear(){
        len =nxt[0] = nxt[1] =0;
    }
    void init(const char* ss){
        len = strlen(ss+1);
        memcpy(t,ss,(len+2)*sizeof(char));
        for (int i=2;i<=len;i++){
            nxt[i] = nxt[i-1];
            while (nxt[i]&&ss[i]!=ss[nxt[i]+1]) nxt[i] = nxt[nxt[i]];
            nxt[i]+=(ss[i]==ss[nxt[i]+1]);
        }
    }
    int min_periodic_loop(){
        int now = len;
        while (now){
            now = nxt[now];
            if (len % (len - now) == 0)return len - now;
        }
    }
}kmper;
int min_rep(char *buff){
    int n = strlen(buff);
    int i = 0,j = 1, k = 0;
    while(i<n && j<n && k<n){
        int t = buff[(i+k)%n] - buff[(j+k)%n] ;
        if(t == 0)k++;
        else{
            if(t>0)i+=k+1;
            else j+=k+1;
            if(i==j)j++;
            k = 0;
        }
    }
    return i < j ? i : j;
}
string s[maxn];
string proc(char * buff){
    kmper.clear();
    kmper.init(buff);
    int min_cyc = kmper.min_periodic_loop();
    buff[min_cyc+1] = 0;
    int pos = min_rep(buff+1) + 1;
    for (int i = 1;i < pos;i ++){
        buff[min_cyc + i] = buff[i];
    }
    buff[min_cyc + pos] = 0;
    return string(buff+pos);
}
int main(){
#ifdef LOCAL
    freopen("input.test","r",stdin);
#endif
    int n;
    cin>>n;
    for (int i=0;i<n;i++){
       static char buff[maxn];
       cin>>buff+1;
       s[i] = proc(buff);
    }
    sort(s,s+n);
    n = unique(s,s+n) - s;
    if (n == 1){
        cout<<-1<<endl;
        return 0;
    }
    int minid = 0, maxid = 0;
    for (int i=0;i<n;i++){
        if (s[i].length() < s[minid].length()) minid = i;
        if (s[i].length() > s[maxid].length()) maxid = i;
    }
    static char buff[maxn];
    strcpy(buff,s[minid].c_str());
    int len = s[minid].length();
    int target = s[maxid].length() * REPEAT*2;
    int now = len;
    while (now < target){
        strcpy(buff + now,s[minid].c_str());
        now += len;
    }
    sam.init(buff);
    int id = 0;
    for (int i=0;i<n;i++){
        if (i == minid)continue;
        static char buff[maxn];
        strcpy(buff,s[i].c_str());
        for (int _ = 1;_ <= REPEAT;_ ++){
            strcpy(buff + _ * s[i].length(), s[i].c_str());
        }
        sam.run(buff,++id);
    }
    cout<<sam.calc(n-1)<<endl;
    return 0;
}