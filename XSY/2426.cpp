#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,cdt,col[N];
std::vector <int> bcol[N];
struct data{
	int k,l,r,v;
	friend bool operator < (const data &a,const data &b){
		return a.k<b.k;
	}
}dt[N*80];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],fa[N],sz[N],dfn[N],idx[N];
	int top[N],son[N],dep[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}

	void dfs_top(const int x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dfn[x]=++cnd;
		idx[cnd]=x;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	inline int jmp(int x,int step){
		assert(dep[x]>=step);
		while(dep[x]-dep[top[x]]+1<=step){
			step-=dep[x]-dep[top[x]]+1;
			x=fa[top[x]];
		}
		return idx[dfn[x]-step];
	}
}

namespace T{
	int x,y,v;
	struct node{
		int s,min,mincnt,delta;
		inline void get_psh(const int v){
			//assert(v==1||v==-1);
			if(v>0) s=0,min+=v;
			else if((min+=v)==0) s=mincnt;
			delta+=v;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		assert(l!=r);
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].s=tr[ls].s+tr[rs].s;
		tr[k].min=std::min(tr[ls].min,tr[rs].min);
		tr[k].mincnt=0;
		if(tr[ls].min==tr[k].min) tr[k].mincnt+=tr[ls].mincnt;
		if(tr[rs].min==tr[k].min) tr[k].mincnt+=tr[rs].mincnt;
	}

	inline void psh(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(l==r||tr[k].delta==0) return;
		tr[idx(l,mid)].get_psh(tr[k].delta);
		tr[idx(mid+1,r)].get_psh(tr[k].delta);
		tr[k].delta=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=(node){1,0,1,0};
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void mod_t(const int l,const int r){
		if(l!=r) psh(l,r);
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

	inline int ask(){
		return tr[idx(1,n)].s;
	}
}

inline void add_mtrx(const int x1,const int x2,const int y1,const int y2){
#ifdef debug
	printf("add: %d %d %d %d\n",x1,x2,y1,y2);
#endif
	dt[++cdt]=(data){x1,y1,y2,1};
	if(x2<n) dt[++cdt]=(data){x2+1,y1,y2,-1};
	dt[++cdt]=(data){y1,x1,x2,1};
	if(y2<n) dt[++cdt]=(data){y2+1,x1,x2,-1};
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		col[i]=nxi();
		bcol[col[i]].push_back(i);
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	for(int i=1; i<=n; ++i){
		const int sz=bcol[i].size();
		if(sz<=1) continue;
		for(int j=0; j<sz; ++j){
			for(int k=j+1; k<sz; ++k){
				using G::dfn;
				using G::dep;
				using G::sz;
				int x=bcol[i][j],y=bcol[i][k];
				const int lca=G::get_lca(x,y);
				if(lca==y) std::swap(x,y);
				const int st_y=dfn[y],ed_y=dfn[y]+sz[y]-1;
				if(lca==x){
					const int fca=G::jmp(y,dep[y]-dep[lca]-1);
					if(dfn[fca]>1) add_mtrx(1,dfn[fca]-1,st_y,ed_y);
					if(dfn[fca]+sz[fca]>n) continue;
					add_mtrx(dfn[fca]+sz[fca],n,st_y,ed_y);
				}
				else{
					add_mtrx(dfn[x],dfn[x]+sz[x]-1,st_y,ed_y);
				}
			}
		}
	}
	std::sort(dt+1,dt+cdt+1);
	T::build(1,n);
	lint ans=0;
	for(int j=1,i=1; i<=n; ++i){
		for(; j<=cdt&&dt[j].k<=i; ++j){
			T::mod(dt[j].l,dt[j].r,dt[j].v);
		}
		ans+=T::ask();
	}
	ans+=n;
	assert((ans&1)==0);
	printf("%lld\n",ans>>1);
	return 0;
}
