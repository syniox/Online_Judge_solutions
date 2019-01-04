#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+2;
int n,m,fa[N];
lint ans;

struct data{
	int x;
	lint val;
	friend bool operator < (const data &a,const data &b){
		return a.val==b.val?a.x<b.x:a.val<b.val;
	}
};

struct node{
	lint delta;
	data d1,d2;
	inline void get_psh(const int v){
		d1.val+=v,d2.val+=v,delta+=v;
	}
};

struct change{
	int x,l,r,v;
	friend bool cmp_x(const change &a,const change &b){
		return a.x<b.x;
	}
}chn[N<<2];

bool cmp_x(const change &a,const change &b);

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

inline int find_rt(const int x){
	return fa[x]?fa[x]=find_rt(fa[x]):x;
}

inline bool same_rt(const data &a,const data &b){
	return find_rt(a.x)==find_rt(b.x);
}

namespace T{
	int x,y,v;
	node tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		const int k=idx(l,r),ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].d1=std::min(tr[ls].d1,tr[rs].d1);
		data fir=std::max(tr[ls].d1,tr[rs].d1);
		data sec=std::min(tr[ls].d2,tr[rs].d2);
		if(sec<fir) std::swap(fir,sec);
		tr[k].d2=same_rt(tr[k].d1,fir)?sec:fir;
	}

	inline void psh(const int l,const int r){
		lint &delta=tr[idx(l,r)].delta;
		if(l==r||delta==0) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].get_psh(delta);
		tr[idx(mid+1,r)].get_psh(delta);
		delta=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=(node){0,(data){l,0},(data){0,(lint)1e14}};
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		tr[idx(l,r)].delta=0;
		upd(l,r);
	}

	void mod_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].get_psh(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	inline void mod(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		mod_t(1,n);
	}
}

namespace G{
	struct edge{
		int x,y;
		lint v;
		friend bool cmp_v(const edge &a,const edge &b){
			return a.v<b.v;
		}
	}eg[N];

	bool cmp_v(const edge &a,const edge &b);

	inline void init(){
		for(int i=1; i<=n; ++i){
			eg[i].x=i,eg[i].v=1e13;
		}
	}

	inline void psh_edge(int x,int y,const lint v){
		x=find_rt(x),y=find_rt(y);
		if(x!=y&&eg[x].v>v) eg[x].y=y,eg[x].v=v;
	}

	inline void kruskal(){
		std::sort(eg+1,eg+n+1,cmp_v);
		for(int i=1; i<=n&&eg[i].v<1e13; ++i){
//			printf("b%d - b%d: v%lld\n",eg[i].x,eg[i].y,eg[i].v);
			const int x=find_rt(eg[i].x),y=find_rt(eg[i].y);
			if(x!=y) fa[x]=y,ans+=eg[i].v;
		}
//		puts("--");
	}
}

bool solve(){
	T::build(1,n);
	G::init();
	for(int i=1,j=1; i<=n; ++i){
		for(; j<=m&&chn[j].x<=i; ++j){
			T::mod(chn[j].l,chn[j].r,chn[j].v);
		}
		data res=T::tr[T::idx(1,n)].d1;
		if(find_rt(i)==find_rt(res.x)){
			res=T::tr[T::idx(1,n)].d2;
		}
		if(!res.x) return 0;
		G::psh_edge(i,res.x,res.val);
//		printf("%d->%d: val%lld\n",i,res.x,res.val);
	}
//	puts("---");
	G::kruskal();
	return 1;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int x1=nxi(),x2=nxi(),y1=nxi(),y2=nxi(),w=nxi();
		chn[(i<<2)-3]=(change){x1,y1,y2,w};
		chn[(i<<2)-2]=(change){x2+1,y1,y2,-w};
		chn[(i<<2)-1]=(change){y1,x1,x2,w};
		chn[(i<<2)-0]=(change){y2+1,x1,x2,-w};
	}
	m<<=2;
	std::sort(chn+1,chn+m+1,cmp_x);
//	for(int i=1; i<=m; ++i){
//		printf("x%d %d-%d v%d\n",chn[i].x,chn[i].l,chn[i].r,chn[i].v);
//	}
	while(solve());
	printf("%lld\n",ans);
	return 0;
}
