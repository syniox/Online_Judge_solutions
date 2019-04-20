#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,mu[N],phi[N],fn[N];
//fn[i]=\sum{i|x,i|y} phi[x]*phi[y]*dis(x,y)

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	static int prm[N];
	static bool npr[N];
	int cnp=0;
	mu[1]=phi[1]=1;
	for(int i=2; i<=n; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int j=1; j<=cnp&&i*prm[j]<=n; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0){
				phi[i*prm[j]]=phi[i]*prm[j];
				break;
			}
			mu[i*prm[j]]=-mu[i];
			phi[i*prm[j]]=phi[i]*(prm[j]-1);
		}
	}
}

class _BaseGraph{
	protected:
		int cnt;
	public:
		int n,fir[N];

		struct edge{
			int to,wi,nx;
		}eg[N<<1];
		inline void clear(){
			cnt=0;
			memset(fir+1,0,n*sizeof(int));
		}
		inline void add(const int a,const int b,const int v){
			eg[++cnt]=(edge){b,v,fir[a]};
			fir[a]=cnt;
			eg[++cnt]=(edge){a,v,fir[b]};
			fir[b]=cnt;
		}
};

class _vTr: public _BaseGraph{
	public:
		int ans,val[N],dp0[N],dp1[N];
		bool able[N];
		//dp0=\sum val, dp1=\sum val*dis

		void init(){
			clear();
			memset(val+1,0,n*sizeof(int));
			ans=0;
		}
		void dfs(const int x,const int fa){
			assert(x<=n);
			dp0[x]=able[x]?val[x]:0;
			dp1[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(y==fa) continue;
				dfs(y,x);
				dp1[y]=(dp1[y]+(lint)eg[i].wi*dp0[y])%mod;
				ans=(ans+(lint)dp0[x]*dp1[y])%mod;
				ans=(ans+(lint)dp1[x]*dp0[y])%mod;
				dp0[x]=(dp0[x]+dp0[y])%mod;
				dp1[x]=(dp1[x]+dp1[y])%mod;
			}
		}
}vG;

class _rTr: public _BaseGraph{
	protected:
		int fa[N],top[N],son[N],sz[N];
	public:
		int dfn[N],dep[N];

		struct cmp{
			int *val;
			inline bool operator () (const int x,const int y){
				return val[x]<val[y];
			}
		};

		void dfs_son(const int x){
			sz[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(sz[y]) continue;
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs_son(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
		void dfs_top(const int x){
			static int cnd;
			dfn[x]=++cnd;
			top[x]=son[fa[x]]==x?top[fa[x]]:x;
			if(son[x]) dfs_top(son[x]);
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!top[y]) dfs_top(y);
			}
		}
		inline int get_lca(int x,int y){
			while(top[x]!=top[y]){
				dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
			}
			return dep[x]<dep[y]?x:y;
		}
}G;

int build_fn(const int t){
	static int buk[N],mp[N],stk[N];
	int cnt=0,cnd=0,top=0;
	for(int i=t; i<=n; i+=t){
		buk[++cnt]=i;
	}
	std::sort(buk+1,buk+cnt+1,(_rTr::cmp){G.dfn});
	vG.init();
	for(int i=1; i<=cnt; ++i){
		mp[buk[i]]=++cnd;
		vG.val[cnd]=phi[buk[i]];
		vG.able[cnd]=1;
		int lca=G.get_lca(stk[top],buk[i]);
		for(int lst=stk[top-1]; top>1&&G.dep[lst]>=G.dep[lca]; --top,lst=stk[top-1]){
			vG.add(mp[lst],mp[stk[top]],G.dep[stk[top]]-G.dep[lst]);
		}
		if(lca!=stk[top]){
			mp[lca]=++cnd;
			vG.val[cnd]=phi[buk[i]];
			vG.able[cnd]=0;
			vG.add(mp[stk[top]],mp[lca],G.dep[stk[top]]-G.dep[lca]);
			stk[top]=lca;
		}
		stk[++top]=buk[i];
	}
	for(int lst=stk[top-1]; top>1; --top,lst=stk[top-1]){
		vG.add(mp[lst],mp[stk[top]],G.dep[stk[top]]-G.dep[lst]);
	}
	vG.n=cnd;
	assert(cnd<=n);
	vG.dfs(1,1);
	return vG.ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	init();
	for(int i=1; i<n; ++i){
		G.add(nxi(),nxi(),0);
	}
	G.dep[0]=-1;
	G.dfs_son(1);
	G.dfs_top(1);
	for(int i=1; i<=n; ++i){
		fn[i]=(build_fn(i)<<1)%mod;
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		const int wgt=(lint)i*fpow(phi[i],mod-2)%mod;
		const int lim=n/i;
		lint res=0;
		for(int j=1; j<=lim; ++j){
			mu[j]?res+=mu[j]*fn[i*j]:0;
		}
		res%=mod;
		ans=(ans+(lint)wgt*res)%mod;
	}
	printf("%d\n",ans<0?ans+mod:ans);
	return 0;
}
