#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
const int N=1e5+5;
int n,q,bak_col[N],col[N];
int cnt_q,cnt_mod,ans[N],mod_x[N],bef_v[N],aft_v[N];
int seq[N<<1],fpos[N],spos[N];//based on dfn
struct data{
	int id,t,x,y;
}dt[N];
class _Seg{
	public:
		int cl,cr,s;
};

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline _Seg merge(const _Seg &a,const _Seg &b){
	if(!a.s) return b;
	if(!b.s) return a;
	return (_Seg){a.cl,b.cr,a.s+b.s-(a.cr==b.cl)};
}

namespace T{
	int x,y,v;
	_Seg tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=merge(tr[idx(l,mid)],tr[idx(mid+1,r)]);
	}

	void mod_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=(_Seg){v,v,1};
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		else mod_t(mid+1,r);
		upd(l,r);
	}

	_Seg ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		const int mid=(l+r)>>1;
		if(y<=mid) return ask_t(l,mid);
		if(x>mid) return ask_t(mid+1,r);
		return merge(ask_t(l,mid),ask_t(mid+1,r));
	}

	inline void mod(const int x,const int v){
		T::x=x,T::v=v;
		mod_t(1,n);
	}

	inline _Seg ask(const int x,const int y){
		T::x=x,T::y=y;
		return ask_t(1,n);
	}
}

namespace G{
	int cnt,fir[N],fa[N],dep[N];
	int sz[N],son[N],dfn[N],idx[N],top[N];
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
		static int cnd,cns;
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		seq[++cns]=dfn[x];
		fpos[dfn[x]]=cns;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
		seq[++cns]=dfn[x];
		spos[dfn[x]]=cns;
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	inline int ask_seg(int x,int y){
		const int lca=get_lca(x,y);
		_Seg sx=(_Seg){-1,-1,0};
		while(top[x]!=top[lca]){
			sx=merge(T::ask(dfn[top[x]],dfn[x]),sx);
			x=fa[top[x]];
		}
		sx=merge(T::ask(dfn[lca],dfn[x]),sx);
		_Seg sy=(_Seg){-1,-1,0};
		while(top[y]!=top[lca]){
			sy=merge(T::ask(dfn[top[y]],dfn[y]),sy);
			y=fa[top[y]];
		}
		if(y!=lca) sy=merge(T::ask(dfn[lca]+1,dfn[y]),sy);
		return sx.s+sy.s-(sx.cl==sy.cl);
	}
}

namespace M{
	using G::dfn;
	using G::idx;
	const int S=2100;//2154??
	int buk[N],xexi,cexi[N],val[N];
	//buk表示每种颜色的出现次数，cexi表示每种次数的个数
	bool vis[N];

	inline bool cmp(const data &a,const data &b){
		if(a.t/S!=b.t/S) return a.t/S<b.t/S;
		if(a.x/S!=b.x/S) return a.x/S<b.x/S;
		return a.y<b.y;
	}

	inline void mns_col(const int col){
		//assert(cexi[buk[col]]);
		//assert(buk[col]);
		--cexi[buk[col]];
		--buk[col];
		++cexi[buk[col]];
		while(xexi&&cexi[xexi]==0) --xexi;
	}

	inline void pls_col(const int col){
		//assert(cexi[buk[col]]);
		--cexi[buk[col]];
		++buk[col];
		++cexi[buk[col]];
		apx(xexi,buk[col]);
	}

	inline void mod_t(const int x,const int bef,const int aft){
		val[x]=aft;
		if(vis[x]){
			mns_col(bef);
			pls_col(aft);
		}
	}

	inline void mod_p(const int x){
		if(vis[x]) mns_col(val[x]);
		else pls_col(val[x]);
		vis[x]^=1;
	}

	inline void main(){
		for(int i=1; i<=n; ++i){
			val[G::dfn[i]]=bak_col[i];
		}
		std::sort(dt+1,dt+cnt_q+1,cmp);
		int pt=0,px=1,py=0;//[],pt=i表示第i次操作之后
		cexi[0]=n;
		for(int i=1; i<=cnt_q; ++i){
			while(pt<dt[i].t){
				++pt;
				mod_t(dfn[mod_x[pt]],bef_v[pt],aft_v[pt]);
			}
			while(pt>dt[i].t){
				mod_t(dfn[mod_x[pt]],aft_v[pt],bef_v[pt]);
				--pt;
			}
			const int tx=dt[i].x,ty=dt[i].y;
			const int lca=dfn[G::get_lca(idx[seq[tx]],idx[seq[ty]])];
			while(px>tx){
				mod_p(seq[--px]);
			}
			while(py<ty){
				mod_p(seq[++py]);
			}
			while(px<tx){
				mod_p(seq[px++]);
			}
			while(py>ty){
				mod_p(seq[py--]);
			}
			if(lca==seq[tx]) ans[dt[i].id]=xexi;
			else{
				//assert(vis[lca]==0);
				mod_p(lca);
				ans[dt[i].id]=xexi;
				mod_p(lca);
			}
		}
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		col[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	for(int i=1; i<=n; ++i){
		T::mod(G::dfn[i],col[i]);
	}
	memcpy(bak_col,col,sizeof(col));
	for(int x,y,i=1; i<=q; ++i){
		const int op=nxi();
		switch(op){
			case 1:
				++cnt_mod;
				mod_x[cnt_mod]=x=nxi(),aft_v[cnt_mod]=y=nxi();
				bef_v[cnt_mod]=col[x];
				col[x]=y;
				T::mod(G::dfn[x],y);
				break;
			case 2:
				ans[i]=G::ask_seg(nxi(),nxi());
				break;
			case 3:
				int x=nxi(),y=nxi(),lca=G::get_lca(x,y);
				x=G::dfn[x],y=G::dfn[y];
				if(x>y) std::swap(x,y);
				if(G::dfn[lca]==x){
					dt[++cnt_q]=(data){i,cnt_mod,fpos[x],fpos[y]};
				}
				else{
					dt[++cnt_q]=(data){i,cnt_mod,spos[x],fpos[y]};
				}
				break;
		}
	}
	M::main();
	for(int i=1; i<=q; ++i){
		if(ans[i]) printf("%d\n",ans[i]);
	}
	return 0;
}
