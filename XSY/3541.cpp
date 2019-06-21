#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,q,v1[N],v2[N],vt[N];
bool ol;

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace P{
	const int N=131072;
	int wt[N];
	struct _init{
		_init(){
			int w=fpow(3,(mod-1)/N);
			wt[0]=1;
			for(int i=1; i<N; ++i){
				wt[i]=(lint)wt[i-1]*w%mod;
			}
		}
	}init;

	void ntt(int *v,const int len,const bool f){
		static int rev[N];
		assert(len==(len&-len));
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) std::swap(v[i],v[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=N/(i<<1);
			for(int j=0; j<len; j+=i<<1){
				for(int k=0,w=0; k<i; ++k,w+=t){
					lint p1=v[j+k],p2=(lint)v[j+k+i]*wt[w];
					v[j+k]=(p1+p2)%mod;
					v[j+k+i]=(p1-p2)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			v[i]=(v[i]+mod)%mod;
		}
		if(!f) return;
		std::reverse(v+1,v+len);
		int wgt=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			v[i]=(lint)v[i]*wgt%mod;
		}
	}

	void pmul(int *a,int *b,int la,int lb,int *c=0){
		static int t1[N],t2[N];
		if(c==0) c=a;
		int len=1;
		while(len<la+lb) len<<=1;
		memset(t1,0,len*sizeof(t1[0]));
		memset(t2,0,len*sizeof(t2[0]));
		memcpy(t1,a,la*sizeof(t1[0]));
		memcpy(t2,b,lb*sizeof(t2[0]));
		ntt(t1,len,0);
		ntt(t2,len,0);
		for(int i=0; i<len; ++i){
			t1[i]=(lint)t1[i]*t2[i]%mod;
		}
		ntt(t1,len,1);
		memcpy(c,t1,(la+lb-1)*sizeof(c[0]));
	}
}

namespace G{
	int cnt,fir[N],fa[N],son[N],sz[N],dfn[N],idx[N],top[N];
	struct edge{
		int to,nx;
	}eg[N];
}

namespace T{
	int x,y,v;
	struct node{
		int *v,tag;
		bool vis;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		P::pmul(tr[idx(l,mid)].v,tr[idx(mid+1,r)].v,mid-l+2,r-mid+1,tr[idx(l,r)].v);
	}

	void getv(const int l,const int r,const int v){
		const int k=idx(l,r);
		for(int i=1,w=v; i<=r-l+1; ++i,w=(lint)w*v%mod){
			tr[k].v[i]=(lint)tr[k].v[i]*w%mod;
		}
		tr[k].tag=(lint)tr[k].tag*v%mod;
	}

	void psh(const int l,const int r){
		int &t=tr[idx(l,r)].tag;
		if(l==r||t==1) return;
		const int mid=(l+r)>>1;
		getv(l,mid,t);
		getv(mid+1,r,t);
		t=1;
	}

	void build(const int l,const int r){
		const int k=idx(l,r);
		tr[k].v=new int[r-l+2];
		tr[k].tag=1;
		if(l==r){
			tr[k].v[0]=v1[G::idx[l]];
			tr[k].v[1]=v2[G::idx[r]];
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			getv(l,r,v);
			return;
		}
		tr[idx(l,r)].vis=1;
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
	}

	void sanans(const int l,const int r){
		const int mid=(l+r)>>1;
		if(l!=r){
			psh(l,r);
			if(tr[idx(l,mid)].vis) sanans(l,mid);
			if(tr[idx(mid+1,r)].vis) sanans(mid+1,r);
			upd(l,r);
		}
		tr[idx(l,r)].vis=0;
	}

	inline void add(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		add_t(1,n);
	}

	int getans(){
		int *res=tr[idx(1,n)].v;
		int ans=0;
		for(int i=0; i<=n; ++i){
			ans=(ans+(lint)res[i]*vt[i])%mod;
		}
		return ans;
	}
}

namespace G{
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dfn(const int x){
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs_dfn(son[x]);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!dfn[eg[i].to]) dfs_dfn(eg[i].to);
		}
	}

	void init(){
		for(int i=2; i<=n; ++i){
			fa[i]=nxi();
			add(fa[i],i);
		}
		for(int i=n; i>=1; --i){
			sz[fa[i]]+=++sz[i];
			if(sz[son[fa[i]]]<sz[i]) son[fa[i]]=i;
		}
		dfs_dfn(1);
	}

	void add_v(int x,const int v){
		for(; x; x=fa[top[x]]){
			T::add(dfn[top[x]],dfn[x],v);
		}
		T::sanans(1,n);
	}
}

int main(){
	n=nxi(),q=nxi(),ol=nxi();
	for(int i=1; i<=n; ++i){
		v1[i]=nxi(),v2[i]=nxi();
	}
	for(int i=0; i<=n; ++i){
		vt[i]=nxi();
	}
	G::init();
	T::build(1,n);
	int ans=T::getans();
	printf("%d\n",ans);
	for(int i=1; i<=q; ++i){
		int x=nxi(),v=nxi();
		if(ol) x^=ans,v^=ans;
		G::add_v(x,v);
		printf("%d\n",ans=T::getans());
	}
	return 0;
}
