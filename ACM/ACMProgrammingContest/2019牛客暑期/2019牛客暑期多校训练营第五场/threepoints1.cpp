#include<cstdio>
#include<cmath>
int sqr(int x) {return x * x;}
int w, h;
int _a, _b, _c;
void read_input() {
    scanf("%d%d", &w, &h);
    scanf("%d%d%d",&_a,&_b,&_c);
}
struct Point{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y){}
    Point operator-(const Point b)const{
        return Point(x-b.x,y-b.y);
    }
    double dis(){return sqrt(x*x+y*y);}
}an[3];
const double EPS = 1e-12;
bool valid(){
    if(fabs((an[0]-an[1]).dis() - _a) > EPS ||
       fabs((an[0]-an[2]).dis() - _b) > EPS ||
       fabs((an[1]-an[2]).dis() - _c) > EPS) return false;
    for(int i = 0; i < 3; i++) {
        if(an[i].x < -EPS || an[i].y < -EPS) return false;
        if(an[i].x > w + EPS) return false;
        if(an[i].y > h + EPS) return false;
    }
    return true;
}
bool check(int a, int b, int c,Point& X,Point& Y,Point& Z){
    if(sqr(a)+sqr(b)<sqr(c)) return 0;
    X=Point();
    bool suc = 0;
    double angle_ab=acos((double)(sqr(a)+sqr(b)-sqr(c))/(2*a*b));
    if(b <= w) {
        Z = Point(b, 0);
        Y = Point(a * cos(angle_ab), a * sin(angle_ab));
        if(valid()) suc = 1;
    }
    else {
        Z = Point(w, sqrt(sqr(b) - sqr(w)));
        double angle_tmp = acos(1.*w/b);
        Y = Point(a * cos(angle_ab + angle_tmp), a * sin(angle_ab + angle_tmp));
        if(valid()) suc = 1;
    }
    if(!suc) {
        if(a <= h) {
            Y = Point(0, a);
            Z = Point(b * sin(angle_ab), a * cos(angle_ab));
            if(valid()) suc = 1;
        }
        else {
            Y = Point(sqrt(sqr(a) - sqr(h)), h);
            double angle_tmp = acos(1.*h/a);
            Z = Point(a * sin(angle_ab + angle_tmp), a * cos(angle_ab + angle_tmp));
            if(valid()) suc = 1;
        }
    }
    if(!suc) return 0;
    for(int i=0;i<3;i++)printf("%.12lf %.12lf%c",an[i].x,an[i].y," \n"[i==2]);
    return 1;
}
void solve() {
    if(check(_a,_b,_c,an[0],an[1],an[2]))return;
    if(check(_a,_c,_b,an[1],an[0],an[2]))return;
    if(check(_b,_a,_c,an[0],an[2],an[1]))return;
    if(check(_b,_c,_a,an[2],an[0],an[1]))return;
    if(check(_c,_a,_b,an[1],an[2],an[0]))return;
    if(check(_c,_b,_a,an[2],an[1],an[0]))return;
    puts("-1");
}
int main () {
    int T;
    scanf("%d", &T);
    while(T--) {
        read_input();
        solve();
    }
    return 0;
}
