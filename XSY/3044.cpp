#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=30005;
const int M=128;
const int mod=10007;
const int inv2=(mod+1)>>1;
int n,m,val[N],wdp[N][M],cc0[N][M],wsum[N][M];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=x*x%mod,t>>=1){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline void fwt(int *a,const int len,const bool type){
	for(int i=1; i<len; i<<=1){
		for(int j=0; j<len; j+=i<<1){
			for(int k=0; k<i; ++k){
				const int x=a[j+k],y=a[j+k+i];
				if(type){
					a[j+k]=(x+y)*inv2%mod;
					a[j+k+i]=(x+mod-y)*inv2%mod;
				}
				else{
					a[j+k]=(x+y)%mod;
					a[j+k+i]=(x+mod-y)%mod;
				}
				assert(a[j+k]>=0);
				assert(a[j+k+i]>=0);
			}
		}
	}
}

class _mtrx{
	public:
		int n[2][2];

		friend _mtrx operator * (const _mtrx &a,const _mtrx &b){
			_mtrx c;
			memset(c.n,0,sizeof(c.n));
			c.n[0][0]=a.n[0][0]*b.n[0][0]%mod;
			c.n[0][1]=(a.n[0][0]*b.n[0][1]+a.n[0][1])%mod;
			c.n[1][0]=(a.n[1][0]*b.n[0][0]+b.n[1][0])%mod;
			c.n[1][1]=(a.n[1][0]*b.n[0][1]+a.n[1][1]+b.n[1][1])%mod;
			return c;
		}

		inline void oput(){
			for(int i=0; i<3; ++i){
				for(int j=0; j<3; ++j) printf("%d ",n[i][j]);
				puts("");
			}
		}
};

class _data{
	public:
		_mtrx n[M];

		friend _data operator * (const _data &a,const _data &b){
			_data c;
			for(int i=0; i<m; ++i){
				c.n[i]=a.n[i]*b.n[i];
			}
			return c;
		}
};

namespace MP{
	_data pool[N<<1],*ptr=pool+1;
	inline _data* apply(const int len){
		_data *tmp=ptr;
		ptr+=len;
		assert(int(ptr-pool)<N<<1);
		return tmp;
	}
}

class _Tr{
	protected:
		_data v,*tr;
		int x,y,len;

		inline int idx(const int l,const int r){
			return (l+r)|(l!=r);
		}

		inline void upd(const int l,const int r){
			const int mid=(l+r)>>1;
			tr[idx(l,r)]=tr[idx(mid+1,r)]*tr[idx(l,mid)];
		}

		_data ask_t(const int l,const int r){
			if(l>=x&&r<=y) return tr[idx(l,r)];
			const int mid=(l+r)>>1;
			if(y<=mid) return ask_t(l,mid);
			if(x>mid) return ask_t(mid+1,r);
			return ask_t(mid+1,r)*ask_t(l,mid);
		}

		void mod_t(const int l,const int r){
			if(l==r){
				tr[idx(l,r)]=v;
				return;
			}
			const int mid=(l+r)>>1;
			if(x<=mid) mod_t(l,mid);
			else mod_t(mid+1,r);
			upd(l,r);
		}

	public:
		inline void init(int len){
			assert(len);
			this->len=len;
			tr=MP::apply(len<<1)-1;
		}

		inline _data ask_p(const int x){
			return tr[idx(x,x)];
		}

		inline _data ask_all(){
			return tr[idx(1,len)];
		}

		inline _data ask(const int l,const int r){
			assert(l&&r&&l<=r);
			x=l,y=r;
			return ask_t(1,len);
		}

		inline void mod(const int x,const _data &v){
			assert(x>0);
			this->v=v,this->x=x;
			mod_t(1,len);
		}
}T[N];

inline void splitv(const int x,const int t,const int v){
	if(v==0){
		assert(cc0[x][t]);
		--cc0[x][t];
	}
	else wdp[x][t]=wdp[x][t]*fpow(v,mod-2)%mod;
}

inline void mergev(const int x,const int t,const int v){
	if(v==0) ++cc0[x][t];
	else wdp[x][t]=wdp[x][t]*v%mod;
}

inline int qdp(const int x,const int t){
	return cc0[x][t]?0:wdp[x][t];
}

inline int qsum(const _mtrx &x){
	return (x.n[0][1]+x.n[1][1])%mod;
}

inline int qdp(const _mtrx &x){
	return (x.n[0][0]+x.n[1][0])%mod;
}

namespace G{
	int cnt,fir[N],fa[N],dep[N],sz[N],top[N],son[N],dfn[N],bot[N];
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
			if(!sz[y]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs_son(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
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
			if(!top[y]) dfs_top(y);
		}
	}

	void dfs_sum(const int x){
		static _data f;
		if(top[x]==x) T[x].init(dep[bot[x]]-dep[x]+1);
		bot[x]=bot[top[x]];
		wdp[x][val[x]]=1;
		fwt(wdp[x],m,0);
		for(int i=0; i<m; ++i){
			if(!wdp[x][i]) wdp[x][i]=1,++cc0[x][i];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			dfs_sum(y);
			if(y==son[x]) continue;
			f=T[top[y]].ask(dfn[y]-dfn[top[y]]+1,dfn[bot[y]]-dfn[top[y]]+1);
			for(int i=0; i<m; ++i){
				mergev(x,i,qdp(f.n[i]));
				wsum[x][i]=(wsum[x][i]+qsum(f.n[i]))%mod;
			}
		}
		for(int i=0; i<m; ++i){
			memset(f.n[i].n,0,sizeof(f.n[i].n));
			f.n[i].n[1][0]=1;
		}
		for(int i=0; i<m; ++i){
			f.n[i].n[0][0]=f.n[i].n[0][1]=qdp(x,i)%mod;
			f.n[i].n[1][1]=(wsum[x][i]+1)%mod;
		}
		T[top[x]].mod(dfn[x]-dfn[top[x]]+1,f);
	}

	void chn(int x,const int *lst,const int *cur){
		static _data res;
		static int prev_dp[M],cur_dp[M],prev_s[M],cur_s[M];
		for(int i=0; i<m; ++i){
			memset(res.n[i].n,0,sizeof(res.n[i].n));
			res.n[i].n[1][0]=1;
		}
		memcpy(prev_dp,lst,m*sizeof(int));
		memcpy(cur_dp,cur,m*sizeof(int));
		memset(prev_s,0,m*sizeof(int));
		memset(cur_s,0,m*sizeof(int));
		for(; x; x=fa[top[x]]){
			_data f(T[top[x]].ask_all());
			for(int i=0; i<m; ++i){
				splitv(x,i,prev_dp[i]);
				wsum[x][i]=(wsum[x][i]-prev_s[i]+cur_s[i]+mod)%mod;
				prev_dp[i]=qdp(f.n[i]),prev_s[i]=qsum(f.n[i]);
				mergev(x,i,cur_dp[i]);
				res.n[i].n[0][0]=res.n[i].n[0][1]=qdp(x,i)%mod;
				res.n[i].n[1][1]=(wsum[x][i]+1)%mod;
			}
			T[top[x]].mod(dfn[x]-dfn[top[x]]+1,res);
			f=T[top[x]].ask_all();
			for(int i=0; i<m; ++i){
				cur_dp[i]=qdp(f.n[i]),cur_s[i]=qsum(f.n[i]);
			}
		}
	}
}

inline void chn(const int x,const int v){
	static int res[M],lst[M];
	memset(res,0,sizeof(res));
	memset(lst,0,sizeof(lst));
	res[v]=1;
	lst[val[x]]=1;
	fwt(res,m,0);
	fwt(lst,m,0);
	G::chn(x,lst,res);
	val[x]=v;
}

inline int ask(const int q){
	static int pol[M];
	_data res(T[1].ask_all());
	for(int i=0; i<m; ++i){
		pol[i]=qsum(res.n[i]);
	}
	fwt(pol,m,1);
	return q==0?((pol[q]-n)%mod+mod)%mod:pol[q];
}

int main(){
	static char ch[10];
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	G::dfs_sum(1);
	for(int q=nxi(); q; --q){
		scanf("%s",ch+1);
		if(ch[1]=='Q') printf("%d\n",ask(nxi()));
		else{
			const int x=nxi(),y=nxi();
			chn(x,y);
		}
	}
	return 0;
}
