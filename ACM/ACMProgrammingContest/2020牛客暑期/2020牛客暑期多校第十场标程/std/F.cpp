#include<bits/stdc++.h>
#define lc c[0]
#define rc c[1]
#define Rt c[2]
#define elif else if

const int N=2e6+7,BUF_SZ=1e6;
bool leq(int&k,int sz){
	return k>sz?k-=sz,0:1;
}

char ib[BUF_SZ],*ip=ib+BUF_SZ,ob[1<<22],*op=ob;
int read(int L,int R){
	size_t n=ib+BUF_SZ-ip;
	if(n<100){
		memcpy(ib,ip,n);
		fread(ib+n,1,BUF_SZ-n,stdin)[ib+n]=0;
		ip=ib;
	}
	int x=0;
	while(*ip<48)++ip;
	while(*ip>47)x=x*10+*ip++-48;
	assert(L<=x&&x<=R);
	return x;
}
void print(unsigned int x){
	char ss[20];
	int sp=0;
	do ss[sp++]=x%10+48;while(x/=10);
	while(sp)*op++=ss[--sp];
	*op++=10;
}
struct info{
	int size;
	unsigned s0,s1,s2;
	void init(unsigned x){
		size=1;
		s0=~0u;
		s1=~x;
		s2=x;
	}
	void init(){
		size=0;
		s0=0u;
		s1=~0u;
		s2=0;
	}
	void up(const info&l,const info&r){
		size=l.size+r.size;
		s0=l.s0&r.s1|~l.s0&r.s0;
		s1=l.s1&r.s1|~l.s1&r.s0;
		s2=std::max(l.s2,r.s2);
	}
};

struct node;
typedef node* pn;
struct node{
	pn c[3];
	int ssz;
	info pi;
	void C(){
		ssz=lc->ssz+rc->ssz+Rt->ssz;
		pi.up(lc->pi,rc->pi);
	}
	void R(){
		ssz=lc->ssz+rc->ssz;
	}
	void R3(){
		ssz=lc->ssz+rc->ssz+Rt->ssz;
	}
	bool isC(){
		return pi.size;
	}
	int p_sz(){
		return pi.size;
	}
	int st_sz(){
		return ssz;
	}
}nil[N<<1],*pool[N<<1],**pool_p;
pn _new(){return *pool_p++;}
void _del(pn&x){*--pool_p=x;}
void _del(pn&x,int d){_del(x);x=x->c[d];}
struct _init{
	_init(){
		for(int i=1;i<N<<1;++i)pool[i]=nil+i;
		pool_p=pool+1;
		nil->pi.init();
	}
}_i;
pn ls[N],rs[N];
int lp,rp;
void sel_Rt(pn&x,pn&l,pn&r){
	ls[lp]=x->lc;
	rs[rp]=x->rc;
	_del(x,2);
	l=ls[0],r=rs[0];
}
template<void (node::*up)()>
void upd(){
	for(;lp;--lp){
		ls[lp-1]->rc=ls[lp];
		(ls[lp-1]->*up)();
	}
	for(;rp;--rp){
		rs[rp-1]->c[0]=rs[rp];
		(rs[rp-1]->*up)();
	}
}
void deCp(pn&x,int k,pn&l,pn&r){
	if(!k)return r=x,l=x=nil,void();
	if(k==x->p_sz())return l=x,x=r=nil,void();
	assert(0<k&&k<x->p_sz());
	pn y;
	int a;
	for(;;){
		y=x->lc;
		a=y->p_sz();
		if(k==a)break;
		if(k<a){
			a=y->lc->p_sz();
			if(k==a){rs[rp++]=x,x=y;break;}
			if(k<a){
				x->lc=y->rc,y->rc=x,x->C();
				rs[rp++]=y,x=y->lc;
			}else{
				k-=a;
				ls[lp++]=y,rs[rp++]=x,x=y->rc;
			}
		}else{
			k-=a;
			y=x->rc;
			a=y->lc->p_sz();
			if(k==a){ls[lp++]=x,x=y;break;}
			if(k<a){
				ls[lp++]=x,rs[rp++]=y,x=y->lc;
			}else{
				k-=a;
				x->rc=y->lc,y->lc=x,x->C();
				ls[lp++]=y,x=y->rc;
			}
		}
	}
	sel_Rt(x,l,r);
	upd<&node::C>();
}

bool deCs(pn&x,int&k,pn&l,pn&r){
	if(!k)return r=x,l=x=nil,1;
	if(k==x->st_sz())return l=x,x=r=nil,1;
	assert(0<k&&k<=x->st_sz());
	pn y,z;
	for(;;){
		y=x->lc;
		if(!y)break;
		if(leq(k,y->st_sz())){
			z=y->lc;
			if(!z){rs[rp++]=x,x=y;break;}
			if(leq(k,z->st_sz())){
				x->lc=y->rc,y->rc=x,x->C();
				rs[rp++]=y,x=z;
			}elif(leq(k,y->Rt->st_sz())){
				rs[rp++]=x,x=y;
				break;
			}else{
				ls[lp++]=y,rs[rp++]=x,x=y->rc;
			}
		}elif(leq(k,x->Rt->st_sz())){
			break;
		}else{
			y=x->rc;
			z=y->lc;
			if(!z){ls[lp++]=x,x=y;break;}
			if(leq(k,z->st_sz())){
				ls[lp++]=x,rs[rp++]=y,x=z;
			}elif(leq(k,y->Rt->st_sz())){
				ls[lp++]=x,x=y;
				break;
			}else{
				x->rc=y->lc,y->lc=x,x->C();
				ls[lp++]=y,x=y->rc;
			}
		}
	}
	if(x->lc){
		sel_Rt(x,l,r);
		upd<&node::C>();
		return 0;
	}
	ls[lp]=x;
	l=ls[0];
	if(rp){
		x=rs[--rp]->Rt;
		_del(rs[rp],1);
		r=rs[0];
	}else r=x=nil;
	upd<&node::C>();
	return 1;
}

void deR(pn&x,int&k,pn&l,pn&r){
	assert(0<k&&k<=x->st_sz());
	pn y,z;
	for(;;){
		y=x->lc;
		if(y->isC())break;
		if(leq(k,y->st_sz())){
			z=y->lc;
			if(z->isC()){rs[rp++]=x,x=y;break;}
			if(leq(k,z->st_sz())){
				x->lc=y->rc,y->rc=x,x->R();
				rs[rp++]=y,x=z;
			}else{
				ls[lp++]=y,rs[rp++]=x,x=y->rc;
			}
		}else{
			y=x->rc;
			z=y->lc;
			if(z->isC()){ls[lp++]=x,x=y;break;}
			if(leq(k,z->st_sz())){
				ls[lp++]=x,rs[rp++]=y,x=z;
			}else{
				x->rc=y->lc,y->lc=x,x->R();
				ls[lp++]=y,x=y->rc;
			}
		}
	}
	l=(lp?_del(ls[--lp],0),ls[0]:nil);
	r=(rp?_del(rs[--rp],1),rs[0]:nil);
	upd<&node::R>();
}

pn R(pn l,pn r){
	if(l==nil)return r;
	if(r==nil)return l;
	pn w=_new();
	w->lc=l,w->rc=r,w->Rt=nil;
	w->pi.size=0;
	w->R();
	return w;
}
pn R3(pn l,pn m,pn r){
	assert(l->p_sz()==r->p_sz());
	if(l==nil)return assert(r==nil),m;
	pn w=_new();
	w->lc=l,w->rc=r,w->Rt=m;
	w->pi.size=0;
	w->R3();
	return w;
}
pn C(pn l,pn m,pn r){
	if(l==nil)return assert(m==nil),r;
	if(r==nil)return assert(m==nil),l;
	pn w=_new();
	w->lc=l,w->rc=r,w->Rt=m;
	w->C();
	return w;
}
pn leaf(int x){
	pn w=_new();
	w->lc=w->rc=w->Rt=0;
	w->ssz=1;
	w->pi.init(x);
	return w;
}
struct seq{
	pn lR,lC,mR,rC,rR;
	int size(){
		return lR->st_sz()+lC->st_sz()+mR->st_sz()+rC->st_sz()+rR->st_sz();
	}
	void fix(){
		if(lC==nil&&lR!=nil)mR=R(lR,mR),lR=nil;
		if(rC==nil&&rR!=nil)mR=R(mR,rR),rR=nil;
	}
	void _rR(pn w){
		if(rC!=nil)rR=R(rR,w);
		else mR=R(mR,w);
	}
	void _lR(pn w){
		if(lC!=nil)lR=R(w,lR);
		else mR=R(w,mR);
	}
	void _rC(pn w){
		if(w!=nil)rC=C(rC,rR,w),rR=nil;
	}
	void _lC(pn w){
		if(w!=nil)lC=C(w,lR,lC),lR=nil;
	}
}empty_seq=(seq){nil,nil,nil,nil,nil};

#ifdef DBG
	void pr(seq);
	void pr(pn);
#endif

seq cut(seq&s0,int k){
	int k0=k,k1=s0.size()-k0;
	pn x=nil;
	bool end=0;
	seq sl=empty_seq,sr=s0;
	if(!k){
		end=1;
		goto _cut;
	}
	
	#define fR(w) \
	sr.w=nil;\
	if(leq(k,s0.w->st_sz())){\
		x=s0.w;\
		goto _cut;\
	}\
	sl.w=s0.w;
	
	#define fC(w) \
	sr.w=nil;\
	if(leq(k,s0.w->st_sz())){\
		x=s0.w;\
		end=deCs(x,k,sl.w,sr.w);\
		goto _cut;\
	}\
	sl.w=s0.w;
	
	fR(lR) fC(lC) fR(mR) fC(rC) fR(rR)
	
	#undef fR
	#undef fC
	
	assert(0);
	_cut:
	sl.fix(),sr.fix();
	while(!end){
		pn x1,x2,w,w1,w2,y,y1,y2;
		_deR:
		deR(x,k,x1,x2);
		sl._rR(x1);
		sr._lR(x2);
		w=x->lc,y=x->rc,_del(x,2);
		if(leq(k,w->st_sz())){
			end=deCs(w,k,w1,w2);
			deCp(y,w2->p_sz(),y2,y1);
			sl._rC(w1);
			sr._lC(y1);
			sr._lR(R(R3(w2,x,y2),y));
			x=w;
		}elif(leq(k,x->st_sz())){
			sl._rC(w);
			sr._lC(y);
			goto _deR;
		}else{
			end=deCs(y,k,y2,y1);
			deCp(w,y1->p_sz(),w1,w2);
			sl._rC(w1);
			sr._lC(y1);
			sl._rR(R(w,R3(w2,x,y2)));
			x=y;
		}
	}
	sr._lR(x);
	assert(sl.size()==k0&&sr.size()==k1);
	return s0=sl,sr;
}
seq _join(seq sl,seq sr){
	pn l,r,x,m=R(sl.rR,sr.lR);
	sl.rR=sr.lR=nil;
	int k1=sl.rC->p_sz(),k2=sr.lC->p_sz();
	if(k1<k2){
		x=sr.lC;
		deCp(x,k1,l,sr.lC);
		m=R3(sl.rC,m,l);
		sr.lR=R(sl.mR,R(m,x));
		sr._lC(sl.lC);
		sr._lR(sl.lR);
		return sr;
	}
	if(k1>k2){
		x=sl.rC;
		deCp(x,k1-k2,sl.rC,r);
		m=R3(r,m,sr.lC);
		sl.rR=R(R(x,m),sr.mR);
		sl._rC(sr.rC);
		sl._rR(sr.rR);
		return sl;
	}
	m=R3(sl.rC,m,sr.lC);
	return (seq){sl.lR,sl.lC,R(R(sl.mR,m),sr.mR),sr.rC,sr.rR};
}
seq join(seq sl,seq sr){
	sl=_join(sl,sr);
	return sl;
}

int n,m;

int main(){
	//freopen( "sample.in" , "r" , stdin );
	//freopen( "sample.out" , "w" , stdout );
	seq s=empty_seq;
	n=read(1,2e6);
	m=read(1,2e5);
	for(int i=1;i<=n;++i){
		int tp=read(0,1),vs=read(0,1e9);
		seq tmp=empty_seq;
		(tp?tmp.rC:tmp.lC)=leaf(vs);
		s=join(s,tmp);
	}
	for(int i=1;i<=m;++i){
		int op=read(1,3),l=read(1,n),r;
		if(op==1)r=read(0,1e9);
		else r=read(l,n);
		{
			if(op==1){
				seq s1,s2;
				s1=cut(s,l-1);
				s2=cut(s1,1);
				int t=0;
				if(s1.lC!=nil)s1.lC->pi.init(r),++t;
				if(s1.rC!=nil)s1.rC->pi.init(r),++t;
				assert(t==1);
				s=join(s,join(s1,s2));
			}else if(op==2){
				seq s1,s2;
				s1=cut(s,l-1);
				s2=cut(s1,r-l+1);
				info tmp;
				tmp.up(s1.lC->pi,s1.rC->pi);
				unsigned ans=tmp.s1^tmp.s2;
				print(ans);
				s=join(s,join(s1,s2));
			}else{
				seq s1,s2;
				s1=cut(s,l-1);
				s2=cut(s1,r-l+1);
				s=join(s,join(s2,s1));
			}
		}
	}
	fwrite(ob,1,op-ob,stdout);
	return 0;
}
