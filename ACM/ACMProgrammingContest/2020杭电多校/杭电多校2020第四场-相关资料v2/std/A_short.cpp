#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef double ld;

const int N=5005;
const ld pi=acos(-1);
const ld eps=2e-13;

int fcmp(const ld &x){
  return fabs(x)<eps?0:x>0?1:-1;
}
ld ran(){
  return rand()/(ld)RAND_MAX*2-1;
}
struct P{
  ld x,y;
  P (ld _x=0,ld _y=0):x(_x),y(_y){}
  P operator + (const P &o){ return P(x+o.x,y+o.y); }
  P operator - (const P &o){ return P(x-o.x,y-o.y); }
  P operator * (const ld &b){ return P(x*b,y*b); }
  P operator / (const ld &b){ return P(x/b,y/b); }
  friend ld cross(const P &a,const P &b){
    return a.x*b.y-a.y*b.x;
  }
  friend ld dot(const P &a,const P &b){
    return a.x*b.x+a.y*b.y;
  }
  friend ld len(const P &a){
    return sqrtl(dot(a,a));
  }
  friend P rot(const P &a){
    return P(-a.y,a.x);
  }
} zero;
struct line{
  P o,v;
  line(P _o=P(),P _v=P()):o(_o),v(_v){}
};
P cro(line a,line b){
  return a.o-(a.v*cross(b.v,(a.o-b.o)))/cross(b.v,a.v);
}

struct pt{
  ld x,y,z;
  pt (ld _x=0,ld _y=0,ld _z=0):x(_x),y(_y),z(_z){}
  pt operator + (const pt &o){ return pt(x+o.x,y+o.y,z+o.z); }
  pt operator - (const pt &o){ return pt(x-o.x,y-o.y,z-o.z); }
  pt operator * (const ld &b){ return pt(x*b,y*b,z*b); }
  friend ld len2(const pt &a){
    return max((ld)0,dot(a,a));
  }
  friend ld len(const pt &a){
    return sqrtl(len2(a));
  }
  friend pt cross(const pt &a,const pt &b){
    return pt(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
  }
  friend ld dot(const pt &a,const pt &b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
  }
  friend pt norm(const pt &a){
    ld c=len(a);
    return pt(a.x/c,a.y/c,a.z/c);
  }
  friend pt vertical(const pt &p){
    ld X=fabs(p.x),Y=fabs(p.y),Z=fabs(p.z);
    if(X>Y&&X>Z) return pt((-p.y-p.z)/p.x,1,1);
    if(Y>X&&Y>Z) return pt(1,(-p.x-p.z)/p.y,1);
    return pt(1,1,(-p.x-p.y)/p.z);
  }
  friend bool operator == (const pt &a,const pt &b){
    return !fcmp(a.x-b.x)&&!fcmp(a.y-b.y)&&!fcmp(a.z-b.z);
  }
} O,South;
struct L{
  pt o,v;
  L (pt _o=pt(),pt _v=pt()):o(_o),v(_v){}
};

ld distance(pt a,pt b){
  ld dist=len(a-b);
  return 2*asin(min((ld)1,dist/2));
}
ld Cos(const pt &a, const pt &o, const pt &b){
  pt A=cross(a,o),B=cross(o,b);
  return (len2(A)+len2(B)-len2(A-B))/(2*sqrtl(len2(A)*len2(B)));
}
ld Sin(const pt &a, const pt &o, const pt &b){
  pt A=cross(a,o),B=cross(o,b);
  return sqrtl(len2(cross(A,B))/len2(A)/len2(B));
}
ld SubL(const pt &A, const pt &B, const pt &C){
  ld a=distance(B,C),b=distance(A,C);
  ld cos_c=-Cos(B,C,A),sin_c=Sin(B,C,A);
  return atan2((tan(a/2)*tan(b/2)*sin_c),
               (1+tan(a/2)*tan(b/2)*cos_c))*2;
}
ld TriangleArea(const pt &a,const pt &b, const pt &c){
  ld A=distance(b,c),B=distance(c,a),C=distance(a,b);
  if(A<=B&&A<=C) return SubL(b,c,a);
  return B<=C?SubL(c,a,b):SubL(a,b,c);
}
ld Triangle(const pt &a,const pt &b, const pt &c){
  ld tmp=TriangleArea(a,b,c);
  return dot(cross(a,b),c)>=0?tmp:-tmp;
}

struct circle{
  pt v,o,x,y; ld R,r;
  void init(pt _v,ld _r){
    v=_v,o=_v*cos(_r);
    x=vertical(v),y=cross(v,x);
    x=norm(x),y=norm(y);
    R=_r,r=sin(_r);
  }
  pt position(ld a){
    return (x*cos(a)*r)+(y*sin(a)*r)+o;
  }
  ld Area(){
    return len(v-o)*2*pi;
  }
  ld area(ld a){
    a=max((ld)0,min((ld)2*pi,a));
    ld res=len(v-o)*a;
    pt A=position(0);
    pt B=position(a);
    return res-Triangle(v,A,B);
  }
};

L intersect(L a,L b){
  pt v=cross(a.v,b.v);
  pt x=vertical(v),y=cross(v,x);
  x=norm(x),y=norm(y);
  P oa=P(dot(a.o,x),dot(a.o,y));
  P va=rot(P(dot(a.v,x),dot(a.v,y)));
  P ob=P(dot(b.o,x),dot(b.o,y));
  P vb=rot(P(dot(b.v,x),dot(b.v,y)));
  P p=cro(line(oa,va),line(ob,vb));
  pt res=(x*p.x)+(y*p.y);
  return L(res,v);
}
pair<ld,ld> fix(pair<ld,ld> a){
  for(;a.se-a.fi>2*pi;a.se-=2*pi);
  for(;a.se-a.fi<0;a.se+=2*pi);
  for(;a.fi>2*pi;a.se-=2*pi,a.fi-=2*pi);
  for(;a.fi<0;a.se+=2*pi,a.fi+=2*pi);
  return a;
}
pair<ld,ld> cover(circle a,circle b){
  L l=intersect(L(a.o,a.v),L(b.o,b.v));
  P o=P(dot(l.o,a.x),dot(l.o,a.y));
  P v=P(dot(l.v,a.x),dot(l.v,a.y));
  ld d=cross(v,zero-o)/len(v);
  ld beta=acos(min((ld)1,d/a.r));
  ld alpha=atan2l(v.y,v.x)-pi/2;
  return fix(mp(alpha-beta,alpha+beta));
}

circle a[N];
ld r[N],R,result;
int mark[N],n,m;
pt p[N];

void calc(int k){
  static pair<ld,ld> seg[N];
  int num=0;
  rep(i,1,n){
    if(i==k||fcmp(distance(a[i].v,a[k].v)-(a[i].R+a[k].R))>=0) continue;
    seg[++num]=cover(a[k],a[i]);
  }
  if(num==0){
    result+=a[k].Area();
    return;
  }
  sort(seg+1,seg+num+1);
  ld las=0;
  rep(i,1,num) las=max(las,seg[i].se);
  las-=2*pi;
  rep(i,1,num){
    if(las<seg[i].fi){
      pt A=a[k].position(las);
      pt B=a[k].position(seg[i].fi);
      result+=Triangle(A,B,South);
      result+=a[k].area(seg[i].fi-las);
    }
    las=max(las,seg[i].se);
  }
}

int main(){
  int T;
  cin>>T;
  while (T--) {
    South=norm(pt(ran(),ran(),ran()));
    ld rr;
    cin>>n>>R>>rr;
    rep(i,1,n){
      cin>>p[i].x>>p[i].y>>p[i].z>>r[i];
      p[i].x/=R,p[i].y/=R,p[i].z/=R,r[i]/=R;
    }
    memset(mark,0,sizeof mark);
    rep(i,1,n) rep(j,1,n){
      if(i==j) continue;
      if(fcmp(r[j]-r[i])>0&&fcmp(r[j]-r[i]-distance(p[i],p[j]))>=0
         ||fcmp(r[j]-r[i])==0&&(p[i]==p[j])&&j<i) mark[i]=1;
    }
    m=0;
    rep(i,1,n){
      if(!mark[i]) a[++m].init(p[i],r[i]);
    }
    n=m;
    result=0;
    rep(i,1,n) calc(i);
    for(;result>4*pi;result-=4*pi);
    for(;result<eps;result+=4*pi);
    ld small,tot=4*pi*R*R;
    small=2*pi*R*(R-cos(rr/R)*R);
    result*=R*R;
    result=result+(tot-result)*(small/tot);
    printf("%.20lf\n",double(result));
  }
  return 0;
}