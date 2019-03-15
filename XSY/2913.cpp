#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

class _Seg{
	public:
		int sl,sr;
		bool full;

		void clear(){
			sl=sr=full=0;
		}
		friend _Seg operator + (const _Seg &a,const _Seg &b){
			_Seg ans=(_Seg){a.sl,b.sr,a.full&b.full};
			if(a.full) ans.sl=a.sl+b.sl;
			if(b.full) ans.sr=b.sr+a.sr;
			return ans;
		}
		void operator += (const _Seg &b){
			(*this)=(*this)+b;
		}
};

//每个点维护自己与轻儿子们的权值和
template <size_t S> class _Sgt{
	protected:
		_Seg tr[(S+1)<<1],all[(S+1)<<1];
		int x,y,v,full,tick,tag[(S+1)<<1];//full:-1 do not change
		bool clr[(S+1)<<1];

		inline int idx(const int l,const int r){
			return (l+r)|(l!=r);
		}

		inline void upd(const int l,const int r){
			const int mid=(l+r)>>1;
			tr[idx(l,r)]=tr[idx(l,mid)]+tr[idx(mid+1,r)];
			all[idx(l,r)]=all[idx(l,mid)]+all[idx(mid+1,r)];
		}

		inline void get_psh(const int l,const int r,const int v){
			const int k=idx(l,r);
			if(v) tr[k]=all[k];
			else tr[k].clear();
			clr[idx(l,r)]=v^1;
		}

		inline void psh(const int l,const int r){
			if(l==r) return;
			const int k=idx(l,r),mid=(l+r)>>1;
			const int ls=idx(l,mid),rs=idx(mid+1,r);
			if(tag[k]>tag[ls]){
				get_psh(l,mid,clr[k]^1);
				tag[ls]=tag[k];
			}
			if(tag[k]>tag[rs]){
				get_psh(mid+1,r,clr[k]^1);
				tag[rs]=tag[k];
			}
		}

		void add_t(const int l,const int r){
			psh(l,r);
			if(l==r){
				const int k=idx(l,r);
				all[k].sl=all[k].sr=all[k].sl+v;
				if(!clr[k]) tr[k].sl=tr[k].sr=all[k].sl;
				if(~full) tr[k].full=full;
				return;
			}
			const int mid=(l+r)>>1;
			if(x<=mid) add_t(l,mid);
			else add_t(mid+1,r);
			upd(l,r);
		}

		void set_t(const int l,const int r){
			psh(l,r);
			if(l>=x&&r<=y){
				get_psh(l,r,v);
				tag[idx(l,r)]=tick;
				return;
			}
			const int mid=(l+r)>>1;
			if(x<=mid) set_t(l,mid);
			if(y>mid) set_t(mid+1,r);
			upd(l,r);
		}

		_Seg ask_t(const int l,const int r){
			psh(l,r);
			if(l>=x&&r<=y) return tr[idx(l,r)];
			const int mid=(l+r)>>1;
			_Seg ans=(_Seg){0,0,1};
			if(x<=mid) ans=ask_t(l,mid);
			if(y>mid) ans+=ask_t(mid+1,r);
			return ans;
		}

	public:
		void build(const int l,const int r,const bool v){
			const int k=idx(l,r);
			if(l==r){
				all[k].sl=all[k].sr=all[k].full=1;
				if(v) tr[k]=all[k];
				else tr[k].clear();
				return;
			}
			const int mid=(l+r)>>1;
			build(l,mid,v);
			build(mid+1,r,v);
			upd(l,r);
		}

		inline void add(const int pos,const int v,const int full){
			x=pos,this->v=v,this->full=full;
			add_t(1,n);
		}

		inline void set(const int l,const int r,const bool v){
			++tick,x=l,y=r,this->v=v;
			set_t(1,n);
		}

		inline _Seg ask(const int l,const int r){
			if(!l||l>r) return (_Seg){0,0,1};
			x=l,y=r;
			return ask_t(1,n);
		}
};
_Sgt <N> T[3];

namespace G{
	int cnt,fa[N],fir[N],dep[N];
	int sz[N],son[N],top[N],bot[N],dfn[N];
	class edge{
		public:
			int to,nx;
	}eg[N];//single!

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
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
		bot[top[x]]=x;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs_top(y);
		}
	}

	void build_t(){
		for(int i=0; i<3; ++i){
			T[i].build(1,n,i==0);
			if(i) T[i].set(1,n,0);
		}
		for(int i=1; i<=n; ++i){
			if(sz[i]!=sz[son[i]]){
				T[0].add(dfn[i],sz[i]-sz[son[i]]-1,1);
			}
			bot[i]=bot[top[i]];
		}
	}

	inline int ask(int x){
		int col=-1;
		for(int i=0; col==-1&&i<3; ++i){
			if(T[i].ask(dfn[x],dfn[x]).full) col=i;
		}
		assert(~col);
		int ans=0;
		for(int f=fa[top[x]]; x; x=f,f=fa[top[x]]){
			_Seg res=T[col].ask(dfn[top[x]],dfn[x]-1);
			if(f&&res.full&&T[col].ask(dfn[f],dfn[f]).full) continue;
			ans=res.sr+T[col].ask(dfn[x],dfn[bot[x]]).sl;
			break;
		}
		return ans;
	}

	inline void mod(const int a,const int b,const int v){
		static int orig[N][3];
		int x=a,y=b;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			for(int i=0; i<3; ++i){
				orig[x][i]=T[i].ask(dfn[top[x]],dfn[bot[x]]).sl;
			}
			x=fa[top[x]];
		}
		if(dep[x]<dep[y]) std::swap(x,y);
		if(fa[top[x]]){
			for(int i=0; i<3; ++i){
				orig[x][i]=T[i].ask(dfn[top[x]],dfn[bot[x]]).sl;
			}
		}
		for(int x=a,y=b; top[x]!=top[y];){
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			for(int i=0; i<3; ++i){
				T[i].set(dfn[top[x]],dfn[x],i==v);
				int delta=T[i].ask(dfn[top[x]],dfn[bot[x]]).sl-orig[x][i];
				T[i].add(dfn[fa[top[x]]],delta,i==v);
			}
			x=fa[top[x]];
		}
		if(dep[x]<dep[y]) std::swap(x,y);
		for(int i=0; i<3; ++i){
			T[i].set(dfn[y],dfn[x],i==v);
			if(fa[top[x]]){
				int delta=T[i].ask(dfn[top[x]],dfn[bot[x]]).sl-orig[x][i];
				T[i].add(dfn[fa[top[x]]],delta,-1);
			}
		}
		//printf("full: %d\n",T[0].ask(2,2).full);
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=2; i<=n; ++i){
		G::fa[i]=nxi();
		G::add(G::fa[i],i);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	G::build_t();
	while(m--){
		const int op=nxi();
		if(op==2) printf("%d\n",G::ask(nxi()));
		else{
			const int x=nxi(),y=nxi();
			G::mod(x,y,nxi());
		}
	}
	return 0;
}
