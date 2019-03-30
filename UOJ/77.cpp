#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
const int N=5005;
const int M=N*14;
const int END=N+N+M-1;
const int INF=1e9+5;
int n,pts;
struct data{
	int a,b,w,l,r,p;
}dt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace D{
	int buk[N],*pt=buk,tot;
	inline void insert(const int v){
		*pt++=v;
	}
	inline void build(){
		std::sort(buk,pt);
		pt=std::unique(buk,pt);
		tot=pt-buk;
	}
	inline int ask(const int v){
		return std::lower_bound(buk,pt,v)-buk+1;
	}
}

namespace G{
	int cnt=1,fir[N+N+M],cur[N+N+M],dep[N+N+M];
	struct edge{
		int to,wi,nx;
	}eg[M*10];

	inline void add(const int a,const int b,const int v){
		//printf("add: %d -> %d, v%d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	inline bool bfs(){
		static int que[N+N+M];
		memset(dep,0,pts*sizeof(int));
		dep[END]=0;
		dep[0]=1;
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&!dep[y]){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[END];
	}

	int dfs(const int x,const int t){
		if(x==END) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if(!(tt-=tp)) break;
			}
		}
		return t-tt;
	}
}

namespace T{
	int rt,cnt,x,y,v;
	struct node{
		int ls,rs;
	}tr[M];

	void mod_t(const int p,int &k,const int l,const int r){
		k=++cnt;
		tr[k].ls=tr[p].ls,tr[k].rs=tr[p].rs;
		if(l==r){
			if(p) G::add(k+(n<<1),p+(n<<1),INF);
			G::add(k+(n<<1),v,INF);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(tr[p].ls,tr[k].ls,l,mid);
		else mod_t(tr[p].rs,tr[k].rs,mid+1,r);
		if(tr[k].ls) G::add(k+(n<<1),tr[k].ls+(n<<1),INF);
		if(tr[k].rs) G::add(k+(n<<1),tr[k].rs+(n<<1),INF);
	}

	void link_t(const int k,const int l,const int r){
		if(!k) return;
		if(l>=x&&r<=y){
			G::add(v,k+(n<<1),INF);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) link_t(tr[k].ls,l,mid);
		if(y>mid) link_t(tr[k].rs,mid+1,r);
	}

	inline void mod(const int x,const int v){
		T::x=x,T::v=v;
		mod_t(rt,rt,1,D::tot);
	}

	inline void link(const int x,const int l,const int r){
		if(l>r) return;
		T::v=x,T::x=l,T::y=r;
		link_t(rt,1,D::tot);
	}
}

int main(){
	int ans=0;
	n=nxi();
	for(int i=1; i<=n; ++i){
		dt[i].a=nxi(),dt[i].b=nxi(),dt[i].w=nxi();
		dt[i].l=nxi(),dt[i].r=nxi(),dt[i].p=nxi();
		ans+=dt[i].b+dt[i].w;
		D::insert(dt[i].a);
	}
	D::build();
	for(int i=1; i<=n; ++i){
		dt[i].a=D::ask(dt[i].a);
		dt[i].l=std::lower_bound(D::buk,D::pt,dt[i].l)-D::buk+1;
		dt[i].r=std::upper_bound(D::buk,D::pt,dt[i].r)-D::buk;
	}
	for(int i=1; i<=n; ++i){
		T::link(i+n,dt[i].l,dt[i].r);
		T::mod(dt[i].a,i);
		G::add(0,i,dt[i].b);
		G::add(i,END,dt[i].w);
		G::add(i,i+n,dt[i].p);
	}
	pts=T::cnt+(n<<1|1);
	while(G::bfs()) ans-=G::dfs(0,INF);
	printf("%d\n",ans);
	return 0;
}
