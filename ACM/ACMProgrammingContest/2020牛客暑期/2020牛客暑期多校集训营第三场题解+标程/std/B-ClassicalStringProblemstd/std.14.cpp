#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define X first
#define Y second
#define ALL(v) v.begin(),v.end()
#define pb push_back
#define SZ(a) ((int)a.size())
#define IOS() ios::sync_with_stdio(0),cin.tie(0);

struct node{
    char data;
    int pri,sz;
    node *l,*r;
    node(char c):data(c),pri(rand()),sz(1),l(0),r(0){}
    void up(){
        sz=1;
        if(l) sz+=l->sz;
        if(r) sz+=r->sz;
    }
};

int sz(node *o){
    return o?o->sz:0;
}

node *merge(node *a,node *b){
    if(!a||!b) return a?a:b;
    if(a->pri<b->pri) return a->r=merge(a->r,b),a->up(),a;
    return b->l=merge(a,b->l),b->up(),b;
}

void split(node *o,node *&a,node *&b,int k){
    if(!o) return a=b=0,void();
    if(sz(o->l)+1<=k)
        a=o,split(o->r,a->r,b,k-sz(o->l)-1),a->up();
    else
        b=o,split(o->l,a,b->l,k),b->up();
}

char kth(node *o,int k){
    if(sz(o->l)+1==k)
        return o->data;
    if(sz(o->l)>=k)
        return kth(o->l,k);
    return kth(o->r,k-sz(o->l)-1);
}

string s;

int main()
{
    srand(time(NULL));
    IOS();
    node *root=0;
    int q,k;
    char c;
    cin >> s >> q;
    for(char cc:s)
        root=merge(root,new node(cc));
    while(q--)
    {
        cin >> c >> k;
        if(c=='M')
        {
            if(k<0)
                k=SZ(s)+k;
            node *a,*b;
            split(root,a,b,k);
            root=merge(b,a);
        }
        else
            cout << kth(root,k) << "\n";
    }
}