#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,val[N],idx[N],phi[N],dp[N];
int dfn[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool cmp_dfn(const int a,const int b){
	return dfn[a]<dfn[b];
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	static bool npr[N];
	static int prm[N];
	int cnp=0;
	phi[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			phi[i]=i-1;
		}
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0){
				phi[i*prm[j]]=phi[i]*prm[j];
				break;
			}
			phi[i*prm[j]]=phi[i]*phi[prm[j]];
		}
	}
}

class _Graph{
	public:
		int cnt,fir[N];
		struct edge{
			int to,wi,nx;
		}eg[N<<1];

		inline void add_edge(const int a,const int b,const int v){
			eg[++cnt]=(edge){b,v,fir[a]};
			fir[a]=cnt;
		}
};

class _Tree:public _Graph{
	protected:
		int cnd,sz[N],fa[N],top[N],son[N];
	public:
		int dep[N];
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
			top[x]=son[fa[x]]==x?top[fa[x]]:x;
			dfn[x]=++cnd;
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
}T;

class _VirTr: public _Graph{
	protected:
		int tick,tag[N],rt,sum[N],prod[N],ans;

		void dfs(const int x){
			sum[x]=(tag[x]==tick)*phi[val[x]];
			prod[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				dfs(y);
				prod[y]=(prod[y]+(lint)sum[y]*eg[i].wi)%mod;
				ans=(ans+(lint)sum[x]*prod[y])%mod;
				ans=(ans+(lint)sum[y]*prod[x])%mod;
				sum[x]=(sum[x]+sum[y])%mod;
				prod[x]=(prod[x]+prod[y])%mod;
			}
		}
	public:
		inline void clear(){
			cnt=0,++tick;
		}

		inline void build(int* const seq,const int cnt){
			static int stk[N];
			int top=0;
			std::sort(seq,seq+cnt,cmp_dfn);
			for(int i=0; i<cnt; ++i){
				tag[seq[i]]=tick;
				fir[seq[i]]=0;
				if(!top) stk[++top]=seq[i];
				else{
					int lca=T.get_lca(stk[top],seq[i]);
					for(; top>1&&T.dep[stk[top-1]]>=T.dep[lca]; --top){
						add_edge(stk[top-1],stk[top],T.dep[stk[top]]-T.dep[stk[top-1]]);
					}
					if(T.dep[lca]<T.dep[stk[top]]){
						fir[lca]=0;
						add_edge(lca,stk[top],T.dep[stk[top]]-T.dep[lca]);
						stk[top]=lca;
					}
					stk[++top]=seq[i];
				}
			}
			for(; top>1; --top){
				assert(T.dep[stk[top-1]]<T.dep[stk[top]]);
				add_edge(stk[top-1],stk[top],T.dep[stk[top]]-T.dep[stk[top-1]]);
			}
			rt=stk[top];
		}

		inline int solve(){
			ans=0;
			dfs(rt);
			return ans;
		}
}V;

int main(){
	static int seq[N];
	init();
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		idx[val[i]]=i;
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		T.add_edge(a,b,1);
		T.add_edge(b,a,1);
	}
	T.dfs_son(1);
	T.dfs_top(1);
	for(int i=1; i<=n; ++i){
		int pt=0;
		for(int j=i; j<=n; j+=i){
			seq[pt++]=idx[j];
		}
		V.clear();
		V.build(seq,pt);
		dp[i]=V.solve();
	}
	for(int i=n; i; --i){
		for(int j=i<<1; j<=n; j+=i){
			dp[i]=(dp[i]-dp[j]+mod)%mod;
		}
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		dp[i]=(lint)dp[i]*i%mod*fpow(phi[i],mod-2)%mod;
		ans=(ans+dp[i])%mod;
	}
	ans=(ans<<1)%mod;
	printf("%lld\n",(lint)ans*fpow(n,mod-2)%mod*fpow(n-1,mod-2)%mod);
	return 0;
}
