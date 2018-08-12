#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=50005;
int n;

inline int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	struct node{
		//size father child
		int sz,fa,c[2];
		//flag hex sum_hx lrank*hex rrank*hex value
		lint f,hx,sx,lv,rv,v;
		bool rev;
	}tr[N];
	inline bool side(int k){
		return tr[tr[k].fa].c[1]==k;
	}
	inline bool isrt(int k){
		return tr[tr[k].fa].c[0]!=k&&tr[tr[k].fa].c[1]!=k;
	}
	inline void rever(int k){
		std::swap(tr[k].lv,tr[k].rv);
		std::swap(tr[k].c[0],tr[k].c[1]);
		tr[k].rev^=1;
	}
	inline void upd(int k){
		node &x=tr[k],&l=tr[x.c[0]],&r=tr[x.c[1]];
		x.sz=l.sz+r.sz+1;
		x.sx=x.hx+l.sx+r.sx;
		x.lv=l.lv+r.lv+(r.sx+x.hx)*(l.sz+1);
		x.rv=l.rv+r.rv+(l.sx+x.hx)*(r.sz+1);
		x.v=l.v+r.v+l.lv*(r.sz+1)+r.rv*(l.sz+1)+x.hx*(l.sz+1)*(r.sz+1);
	}
	inline void add(int x,int f){
		int sz=tr[x].sz;
		tr[x].f+=f;
		tr[x].hx+=f;
		tr[x].sx+=f*sz;
		tr[x].lv+=f*sz*(sz+1)>>1;
		tr[x].rv+=f*sz*(sz+1)>>1;
		tr[x].v+=f*sz*(sz+1)*(sz+2)/6;
	}
	void psh(int x){
		if(tr[x].fa) psh(tr[x].fa);
		if(tr[x].rev){
			rever(tr[x].c[0]);
			rever(tr[x].c[1]);
			tr[x].rev=0;
		}
		if(tr[x].f){
			add(tr[x].c[0],tr[x].f);
			add(tr[x].c[1],tr[x].f);
			tr[x].f=0;
		}
	}
	inline void rot(int x){
		int f=tr[x].fa,ff=tr[f].fa;
		bool k=side(x);
		int &p=tr[x].c[k^1];
		if(!isrt(f)) tr[ff].c[side(f)]=x;
		tr[x].fa=ff;
		tr[f].fa=x;
		tr[f].c[k]=p;
		if(p) tr[p].fa=f;
		p=f;
		upd(f);
		upd(x);
	}
	inline void splay(int x){
		psh(x);
		while(!isrt(x)){
			int f=tr[x].fa;
			if(!isrt(f)){
				rot(side(x)==side(f)?f:x);
			}
			rot(x);
		}
	}
	inline void acs(int x){
		int y=0;
		while(x){
			splay(x);
			tr[x].c[1]=y;
			upd(x);
			y=x;
			x=tr[x].fa;
		}
	}
	inline void mrt(int x){
		acs(x);
		splay(x);
		rever(x);
	}
	inline void split(int x,int y){
		mrt(x);
		acs(y);
		splay(y);
	}
	inline bool same_rt(int x,int y){
		acs(x),splay(x);
		acs(y),splay(y);
		return tr[x].fa;
	}
	inline void cut(int x,int y){
		split(x,y);
		if(tr[x].fa==y){
			tr[x].fa=0;
			tr[y].c[1]=0;
			upd(y);
		}
	}
	inline void link(int x,int y){
		if(!same_rt(x,y)){
			rever(x);
			tr[x].fa=y;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("2.in","r",stdin);
#endif
	n=nxi();
	int m=nxi();
	for(int i=1;i<=n;++i){
		T::tr[i].hx=nxi();
		T::upd(i);
	}
	for(int i=1;i<n;++i){
		int a=nxi(),b=nxi();
		T::link(a,b);
	}
	while(m--){
		int d,op=nxi(),x=nxi(),y=nxi();
		switch(op){
			case 1:
				T::cut(x,y);
				break;
			case 2:
				T::link(x,y);
				break;
			case 3:
				d=nxi();
				if(T::same_rt(x,y)){
					T::split(x,y);
					T::add(y,d);
				}
				break;
			case 4:
				if(!T::same_rt(x,y)) puts("-1");
				else{
					using namespace T;
					split(x,y);
					lint a=tr[y].v,b=tr[y].sz*(tr[y].sz+1)>>1,g=gcd(a,b);
					printf("%lld/%lld\n",a/g,b/g);
				}
				break;
		}
/*		for(int i=1;i<=n;++i){
			using T::tr;
			printf("%d:v%lld f%d l%d r%d\n",i,tr[i].v,tr[i].fa,tr[i].c[0],tr[i].c[1]);
		}
		puts("---");*/
	}
	return 0;
}
