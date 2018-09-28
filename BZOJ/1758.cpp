#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
const double eps=1e-5;
int n,ql,qr,dfn[N],idx[N],rdis[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline char get_c(){
	static bool buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,2000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y;
	double v;
	double hx[N],tr[N<<1];

	inline int indx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[indx(l,r)]=std::max(tr[indx(l,mid)],tr[indx(mid+1,r)]);
	}

	inline void build(const int l,const int r){
		const int k=indx(l,r);
		if(l==r){
			tr[k]=hx[idx[l]];
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	double ask(const int l,const int r){
		const int k=indx(l,r);
		if(l>=x&&r<=y) return tr[k];
		const int mid=(l+r)>>1;
		if(x>mid) return ask(mid+1,r);
		if(y<=mid) return ask(l,mid);
		return std::max(ask(l,mid),ask(mid+1,r));
	}

	void mod(const int l,const int r){
		const int k=indx(l,r);
		if(l==r){
			tr[k]=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x>mid) mod(mid+1,r);
		else mod(l,mid);
		upd(l,r);
	}

	inline void mod_t(const int x,const double v){
		T::x=dfn[x],T::v=v;
		hx[x]=v;
		mod(1,n);
	}

	inline double ask_t(const int x,const int y){
		if(x>y) return -19260817;//-INF
		T::x=x,T::y=y;
		return ask(1,n);
	}
}

namespace G{
	int cnd,cnt,fa[N],fir[N],dep[N],son[N],top[N],xdep[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs1(const int x){
		xdep[x]=dep[x];
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(fa[x]!=y){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(xdep[y]>xdep[x]){
					son[x]=y;
					xdep[x]=xdep[y];
				}
			}
		}
	}

	void dfs2(const int x){
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
}

namespace S{
	double tgt;

	void get_rdis(const int x){
		for(int i=G::fir[x];i;i=G::eg[i].nx){
			const int y=G::eg[i].to;
			if(y!=G::fa[x]){
				T::hx[y]=T::hx[x]+G::eg[i].wi-tgt;
				get_rdis(y);
			}
		}
	}

	bool get_ans(const int x){
		if(G::son[x]){
			if(get_ans(G::son[x])) return 1;
		}
		const int len=G::xdep[x]-G::dep[x];
		const double px=T::hx[x];
		for(int i=G::fir[x];i;i=G::eg[i].nx){
			const int y=G::eg[i].to;
			if(y!=G::fa[x]&&y!=G::son[x]){
				if(get_ans(y)) return 1;
				for(int j=0;j<=G::xdep[y]-G::dep[y];++j){
					const int cur=idx[dfn[y]+j];
					if(ql-(j+1)>len) continue;
					if(qr-(j+1)<0) break;
					const int fl=dfn[x]+std::max(0,ql-(j+1));
					const int fr=dfn[x]+std::min(len,qr-(j+1));
					if((T::ask_t(fl,fr)-px)+(T::hx[cur]-px)>eps) return 1;
				}
				for(int j=0;j<=G::xdep[y]-G::dep[y];++j){
					const int cur=idx[dfn[y]+j];
					const int lc=idx[dfn[x]+j+1];
					if(T::hx[lc]<T::hx[cur]) T::mod_t(lc,T::hx[cur]);
				}
			}
		}
		if(ql>len) return 0;
		const int fl=dfn[x]+ql;
		const int fr=dfn[x]+std::min(len,qr);
		if(T::ask_t(fl,fr)-px>eps) return 1;
		return 0;
	}

	inline bool solve(const double tgt){
		S::tgt=tgt;
		get_rdis(1);
		T::build(1,n);
		return get_ans(1);
	}
}

inline double solve(){
	double l=0,r=1e6,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(S::solve(mid)) l=mid;
		else r=mid;
	}
	return l;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	n=nxi(),ql=nxi(),qr=nxi();
	for(int i=1;i<n;++i){
		const int x=nxi(),y=nxi(),v=nxi();
		G::add(x,y,v);
		G::add(y,x,v);
	}
	G::dfs1(1);
	G::dfs2(1);
	printf("%.3lf\n",solve());
	return 0;
}
