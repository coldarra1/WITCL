#include<bits/stdc++.h>
using namespace std;
const int MAXN=10005;
const double EPS=1e-6;
const double PI=4.0*atan(1.0);
const double base=2*PI/3;
int k,T;
double L,vx,vy,x,y,h;
pair<double,double> get_point(const pair<double,double> &a,const double &rad)
{
    return make_pair(a.first*cos(rad)-(a.second-h/3)*sin(rad),a.first*sin(rad)+(a.second-h/3)*cos(rad)+h/3);
}
bool ck(double times)
{
    long long has=0;
    has+=abs(floor(get_point(make_pair(x+vx*times,y+vy*times),base*0).second/h));
    has+=abs(floor(get_point(make_pair(x+vx*times,y+vy*times),base*1).second/h));
    has+=abs(floor(get_point(make_pair(x+vx*times,y+vy*times),base*2).second/h));
    return has>=k;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf %lf %lf %lf %lf %d",&L,&x,&y,&vx,&vy,&k);
        h=L*sqrt(3)/2;

        double l=0,r=1e11,mid;
        while(r-l>EPS)
        {
            mid=(l+r)/2;
            if(ck(mid)) r=mid;
            else l=mid;
        }
        printf("%.8lf\n",(l+r)/2);
    }
    return 0;
}
