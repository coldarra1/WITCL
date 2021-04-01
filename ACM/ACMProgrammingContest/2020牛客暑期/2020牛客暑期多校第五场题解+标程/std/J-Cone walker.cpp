#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

const long double pi=acos((long double)-1);
const long double eps=1e-11;
struct dn{long double x,y;};
dn operator+(dn u,dn v){
	return(dn){u.x+v.x,u.y+v.y};
}
dn operator-(dn u,dn v){
	return(dn){u.x-v.x,u.y-v.y};
}
dn operator*(long double u,dn v){
	return(dn){u*v.x,u*v.y};
}
dn operator/(dn u,long double v){
	return(dn){u.x/v,u.y/v};
}
long double operator/(dn u,dn v){
	return u.x*v.y-v.x*u.y;
}
long double operator*(dn u,dn v){
	return u.x*v.x+u.y*v.y;
}
long double dis(dn o){
	return sqrt(max((long double)0.,o.x*o.x+o.y*o.y));
}
dn dd(long double o){
	return(dn){cos(o),sin(o)};
}
int jd(dn o1,long double r1,dn o2,long double r2,dn p,dn q,dn&u,dn&v){
	vector<dn>g;
	dn o=(o1-p)*(q-p)*(q-p)/((q-p)*(q-p))+p;
	if(dis(o-o1)<r1-eps){
		g.push_back(o+sqrt(r1*r1-(o1-o)*(o1-o))*(q-p)/dis(q-p));
		g.push_back(o-sqrt(r1*r1-(o1-o)*(o1-o))*(q-p)/dis(q-p));
	}
	o=(o2-p)*(q-p)*(q-p)/((q-p)*(q-p))+p;
	if(dis(o-o2)<r2-eps){
		g.push_back(o+sqrt(r2*r2-(o2-o)*(o2-o))*(q-p)/dis(q-p));
		g.push_back(o-sqrt(r2*r2-(o2-o)*(o2-o))*(q-p)/dis(q-p));
	}
//	printf("size%d\n",g.size());
	for(int i=0;i<g.size();i++){
//		printf("(%f %f)\n",(double)g[i].x,(double)g[i].y);
		bool ok=1;
		for(int j=0;j<i;j++)
			if(dis(g[i]-g[j])<eps)
				ok=0;
		if(dis(g[i]-o1)>r1+eps||dis(g[i]-o2)>r2+eps)
			ok=0;
		if((g[i]-p)*(q-p)<-eps)ok=0;
		if(!ok){
			swap(g[i],g[g.size()-1]);
			g.pop_back();
			i--;
		}
	}
//	printf("size%d\n",g.size());
	if(g.size()>0)u=g[0];
	if(g.size()>1)v=g[1];
	if(g.size()==2&&(u-p)*(q-p)>(v-p)*(q-p))
		swap(u,v);
	return g.size();
}
long double arc(dn o,long double r,dn u,dn v){
	long double w=(v-o)*(u-o)/r/r;
	w=max((long double)-1,w);
	w=min((long double)1,w);
	if((o-u)/(v-u)>0)return 0.5*acos(w)*r*r-0.5*abs((v-o)/(u-o));
	else return pi*r*r-0.5*acos(w)*r*r+0.5*abs((v-o)/(u-o));
}
long double ar(dn o1,long double r1,dn o2,long double r2,dn u,dn v,bool www=0){
	if(dis(o2-o1)<r2-r1+eps){
//		printf("!!!%d %f\n",www,(double)r1);
		if(www)return pi*r1*r1;
		else return arc(o1,r1,u,v);
	}
	dn d1,d2;
	dn o=(r1*r1+(o2-o1)*(o2-o1)-r2*r2)/(2*r1*dis(o2-o1))*r1*(o2-o1)/dis(o2-o1);
	dn w=sqrt(r1*r1-o*o)*o/dis(o);
	d1=o1+o+(dn){w.y,-w.x};
	d2=o1+o-(dn){w.y,-w.x};
	if(o*(o2-o1)<eps)swap(d1,d2);
	long double aa=arc(o1,r1,d2,d1)+arc(o2,r2,d1,d2);
	if(www)return aa;
	if((u-d1)/(d2-d1)<eps&&(v-d1)/(d2-d1)<eps){
		if((0.5*(d1+d2)-u)/(v-u)>eps||(0.5*(d1+d2)-u)/(v-u)>-eps&&(v-u)*(d2-d1)>0)
			return arc(o2,r2,u,v);
		else return aa-arc(o2,r2,v,u);
	}
	if((u-d1)/(d2-d1)>-eps&&(v-d1)/(d2-d1)>-eps){
		if((0.5*(d1+d2)-u)/(v-u)>eps||(0.5*(d1+d2)-u)/(v-u)>-eps&&(v-u)*(d1-d2)>0)
			return arc(o1,r1,u,v);
		else return aa-arc(o1,r1,v,u);
	}
	if((u-d1)/(d2-d1)>-eps)
		return arc(o1,r1,u,d1)+arc(o2,r2,d1,v)+0.5*abs((u-d1)/(v-d1));
	else return arc(o1,r1,d2,v)+arc(o2,r2,u,d2)+0.5*abs((u-d2)/(v-d2));
}
long double cc(long double p,long double q,dn o1,long double r1,dn o2,long double r2){
	if(dis(o1-o2)>r1+r2-eps)return 0;
	if(r1>r2){
		swap(o1,o2);
		swap(r1,r2);
	}
	if(r1<eps)return 0;
//	printf("%f %f %f %f (%f %f)(%f %f)\n",(double)p,(double)q,(double)r1,(double)r2,(double)o1.x,(double)o1.y,(double)o2.x,(double)o2.y);
	if(dis(o1)<r1-eps&&dis(o2)<r2-eps){
		dn u,v;
		if(jd(o1,r1,o2,r2,(dn){0,0},dd(p),u,v)!=1)return 1/0;
		if(jd(o1,r1,o2,r2,(dn){0,0},dd(q),v,u)!=1)return 1/0;
//		printf("(%f %f) (%f %f)~~~\n",(double)u.x,(double)u.y,(double)v.x,(double)v.y);
		return dis(u-v)<eps?0:ar(o1,r1,o2,r2,v,u)+0.5*abs(u/v);
	}
	else{
		dn u1,u2,v1,v2;
		int ok1,ok2;
		ok1=jd(o1,r1,o2,r2,(dn){0,0},dd(p),u1,u2);
		ok2=jd(o1,r1,o2,r2,(dn){0,0},dd(q),v1,v2);
		if(ok1==1)ok1=0;
		if(ok2==1)ok2=0;
		if(ok1==1||ok2==1)return 1/0;
		long double aa=ar(o1,r1,o2,r2,(dn){0,0},(dn){0,0},1);
		if(!ok1&&!ok2){
			dn o;
			if(dis(o1-o2)<r2-r1+eps)
				o=o1;
			else o=(r1*r1+(o2-o1)*(o2-o1)-r2*r2)/(2*r1*dis(o2-o1))*r1*(o2-o1)/dis(o2-o1)+o1;
//			printf("(%f %f) %f %f!!!\n",(double)o.x,(double)o.y,(double)(o/dd(p)),(double)(o/dd(q)));
			if(o/dd(p)<-eps&&o/dd(q)>eps)
				return aa;
			else return 0;
		}
//		printf("%daa%f(%f %f)(%f %f)\n",ok1,(double)aa,(double)u1.x,(double)u1.y,(double)u2.x,(double)u2.y);
		if(ok1)aa-=ar(o1,r1,o2,r2,u2,u1);
//		printf("%daa%f(%f %f)(%f %f)\n",ok2,(double)aa,(double)v1.x,(double)v1.y,(double)v2.x,(double)v2.y);
		if(ok2)aa-=ar(o1,r1,o2,r2,v1,v2);
//		printf("aa%f\n",(double)aa);
		return aa;
	}
}
int main(){
//	printf("%f\n",cc(0.00*pi,0.30*pi,(dn){3,3},3,(dn){3,-1},3));
//	freopen("std.in","r",stdin);
//	FILE*in=fopen("1.in","w");
//	FILE*out=fopen("1.out","w");
	int t=100000;
//	fprintf(in,"%d\n",t);
	scanf("%d",&t);
	for(int tt=1;tt<=t;tt++){
		double a,a1,a2,z1,z2,r1,r2;
		a=rand()%89+1;
		a1=rand()%360;
		a2=rand()%360;
		z1=rand()%2001;
		z2=rand()%2001;
		r1=rand()%2001;
		r2=rand()%2001;
//		fprintf(in,"%d\n%d %d\n%d %d\n%d %d\n",(int)a,(int)a1,(int)a2,(int)z1,(int)z2,(int)r1,(int)r2);
		scanf("%lf%lf%lf%lf%lf%lf%lf",&a,&a1,&a2,&z1,&z2,&r1,&r2);
		a2=a2-a1+360;
		if(a2>=360)a2-=360;
		a1=0;
		if(a2>180)a2=360-a2;
		a=sin(a/180*pi);
		long double ans=0;
//		printf("%f %f %f\n",(double)a1,(double)a2,(double)a);
		ans+=cc(0,a2/180*pi*a,z2*dd(a2/180*pi*a),r2,z1*dd(0),r1);
//		printf("%f\n",(double)ans);
		ans+=cc(0,(180-a2)/180*pi*a,z2*dd(0),r2,z1*dd(-a2/180*pi*a),r1);
//		printf("%f\n",(double)ans);
		ans+=cc(0,a2/180*pi*a,z2*dd(-(180-a2)/180*pi*a),r2,z1*dd(pi*a),r1);
//		printf("%f\n",(double)ans);
		ans+=cc(0,(180-a2)/180*pi*a,z2*dd(pi*a),r2,z1*dd((180-a2)/180*pi*a),r1);
		if(ans!=0&&!isnormal(ans))return 1/0;
//		fprintf(out,"%.30f\n",(double)ans);
		printf("%.30f\n",(double)ans);
	}
}