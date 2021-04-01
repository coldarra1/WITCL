#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
const double eps=1e-11;
const double Pi=acos(-1);

int n;double Le,r;
int tip(double x){return x<-eps?-1:x>eps;}
int mos(double x,double y){return tip(x-y);}

struct conot
{
    double x,y;
    conot(double xx=0,double yy=0){x=xx,y=yy;}

    conot operator +(const conot &b)const{return conot(x+b.x,y+b.y);}
    conot operator -(const conot &b)const{return conot(x-b.x,y-b.y);}
    conot operator *(const double &b)const{return conot(x*b,y*b);}
    conot operator /(const double &b)const{return conot(x/b,y/b);}

    double ee(conot b){return x*b.x+y*b.y;}
    double xx(conot b){return x*b.y-y*b.x;}

    double Dis2(){return x*x+y*y;}
    double Dis(){return sqrt(Dis2());}

    bool operator <(const conot &b)const
    {
        if((tip(x)<0)!=(tip(b.x)<0))return (tip(x)<0)<(tip(b.x)<0);
        return tip(x*b.y-y*b.x)==1;
    }

    double arg()
    {
        if(tip(x)==0)return tip(y)>=0?Pi/2:Pi*3/2;
        if(tip(x)>0)return atan(y/x);
        return atan(y/x)+Pi;
    }
}A[M],g1,g2;

conot Shadow(conot a,conot p,conot q)
{
	double k=(a-p).ee(q-p)/(q-p).ee(q-p);
	return p*(1-k)+q*k;
}
conot Land(conot a,conot b,conot p,conot q)
{
	double s1=(a-p).xx(q-p),s2=(q-p).xx(b-p);
	return (a*s2+b*s1)/(s1+s2);
}
conot oSeq(double xa,double ya,double d1,double d2)
{
    if(tip(xa)==0)return conot(-d2/ya,d1/ya);
    double c=ya/xa;
    double y=(d2+c*d1)/(xa+c*ya);
    double x=(d1-ya*y)/xa;
    return conot(x,y);
}
bool II(conot a,conot b,conot p,conot q)
{
	return tip((a-b).xx(p-q))==0;
}
void oTangent(conot a,conot o,conot &ans1,conot &ans2)
{
    double d=(a-o).Dis();
    double _cos_=r/d;
    double _sin_=sqrt(1-_cos_*_cos_);
    ans1=oSeq(a.x,a.y,r*d*_cos_,r*d*_sin_);
    ans2=oSeq(a.x,a.y,r*d*_cos_,-r*d*_sin_);
}

struct event
{
    int x;bool ty;double t;
    bool operator <(const event &b)const{return t<b.t;}
}T[M<<4];int tc;

double Len(double k,int a,int b,int c,int d)
{
    double cc=cos(k),ss=sin(k);
    conot c1(cc*r,ss*r),c2=c1+conot(-ss,cc);
    if(II(c1,c2,A[a],A[b]))return (A[a]-A[b]).Dis2();
    if(II(c1,c2,A[c],A[d]))return (A[c]-A[d]).Dis2();
    double ret=(Land(c1,c2,A[a],A[b])-Land(c1,c2,A[c],A[d])).Dis2();
    return ret;
}
double Calc(int a,int b,int c,int d,double t1,double t2)
{
    static const int TIMES=60;
    double L=t1,R=t2,ans1=t1,ans2=t2;
    for(int i=1;i<=TIMES;i++)
    {
        double mid1=L+(R-L)*0.45,mid2=L+(R-L)*0.55;
        if(mos(Len(mid1,a,b,c,d),Len(mid2,a,b,c,d))==1)L=mid1;
        else R=mid2;
    }
    double m=L;
    {
        L=t1,R=m;
        for(int i=1;i<=TIMES && fabs(R-L)>1e-10;i++)
        {
            double mid=(L+R)*0.5;
            if(mos(Len(mid,a,b,c,d),Le*Le)==1)ans1=mid,L=mid;
            else R=mid;
        }
    }
    {
        L=m,R=t2;
        for(int i=1;i<=TIMES && fabs(R-L)>1e-10;i++)
        {
            double mid=(L+R)*0.5;
            if(mos(Len(mid,a,b,c,d),Le*Le)==1)ans2=mid,R=mid;
            else L=mid;
        }
    }
    return (ans1-t1)+(t2-ans2);
}

int Pre(int x){return x==1?n:x-1;}
int Nxt(int x){return x==n?1:x+1;}
double Mod(double x){if(mos(x,0)<0)x+=2*Pi;if(mos(x,2*Pi)>=0)x-=2*Pi;return x;}
int ll,rr,siz;
void Push(int x){if(siz==0)ll=rr=x;else{if(x==Pre(ll) && false)ll=x;if(x==Nxt(rr))rr=x;}siz++;}
void Pop(int x){if(!x)return;if(rr==x)rr=Pre(rr);if(ll==x)ll=Nxt(ll);siz--;}
void Solve()
{
    r=Shadow(conot(0,0),g1,g2).Dis();
    double test=2e18;
    for(int i=1;i<=n;i++)
    {
        double d=Shadow(conot(0,0),A[i],A[i==n?1:i+1]).Dis();
        test=min(test,d);
    }
    for(int i=1;i<=n;i++)
    {
        if(mos(A[i].Dis2(),r*r)<=0)continue;
        conot a,b;
        oTangent(A[i],conot(0,0),a,b);
        a=a-A[i];b=b-A[i];
        if(tip(a.xx(b)>=0))swap(a,b);
        double t1=Mod(a.arg()+Pi/2),t2=Mod(b.arg()-Pi/2);
        T[++tc]=(event){i,true,t1};
        T[++tc]=(event){i,false,t2};
    }
    sort(T+1,T+tc+1);
    ll=-1,rr=-1,siz=0;
    for(int i=1;i<=n;i++)
    {
        if(mos(A[i].x,r)>0 || (mos(A[i].x,r)==0 && mos(A[Pre(i)].x,r)<0))siz++;
        if(mos(A[i].x,r)>0 && mos(A[Nxt(i)].x,r)<=0)rr=i;
        if(mos(A[i].x,r)>=0 && mos(A[Pre(i)].x,r)<0)ll=i;
    }
    double Ans=0;
    if(siz && siz!=n)Ans+=Calc(Pre(ll),ll,rr,Nxt(rr),0,T[1].t);
    for(int i=1;i<=tc;i++)
    {
        if(T[i].ty)Push(T[i].x);
        else Pop(T[i].x);
        if(siz==0 || siz==n)continue;
        Ans+=Calc(Pre(ll),ll,rr,Nxt(rr),T[i].t,i==tc?2*Pi:T[i+1].t);
    }
    printf("%.4lf\n",Ans/(2*Pi));
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lf%lf",&A[i].x,&A[i].y);
    scanf("%lf%lf%lf%lf%lf",&Le,&g1.x,&g1.y,&g2.x,&g2.y);
    Solve();
    return 0;
}
