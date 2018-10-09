#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=5e4+2;
int n,m,fort[12];
double dp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())<'0'||c>'9');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,cnd,fa[N],idx[N],fir[N],dfn[N],son[N],dep[N],cdep[N],xdep[N];
	lint ans=0;
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs(const int x){
		xdep[x]=dep[x];
		cdep[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(fa[x]!=y){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs(y);
				if(xdep[x]<xdep[y]){
					son[x]=y;
					xdep[x]=xdep[y];
				}
			}
		}
	}
	void solve(const int x){
		dfn[x]=++cnd;
		idx[cnd]=x;
		cdep[x]=1;
		if(son[x]) solve(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){
				solve(y);
				for(int j=0;j<=xdep[y]-dep[y];++j){
					const int p=idx[dfn[y]+j];
					for(int k=1;k<=m;++k){
						if(fort[k]<=j+1) continue;
						if(fort[k]-j-1>xdep[x]-dep[x]) break;
						ans+=(lint)cdep[p]*cdep[idx[dfn[x]+(fort[k]-j-1)]];
					}
				}
				for(int j=0;j<=xdep[y]-dep[y];++j){
					const int p=idx[dfn[y]+j];
					cdep[idx[dfn[x]+j+1]]+=cdep[p];
				}
			}
		}
		for(int i=1;i<=m&&fort[i]<=xdep[x]-dep[x];++i){
			ans+=cdep[idx[dfn[x]+fort[i]]];
		}
//		printf("next %d:",x);
//		for(int i=1;i<=xdep[x]-dep[x];++i){
//			printf("%d ",idx[dfn[x]+i]);
//		}
//		puts("");
//		printf("%d: ans%lld\n",x,ans);
	}
}

inline void oput(){
	const int p=n/3,tp=n-p*3;
	const double base=(double)1/((lint)n*(n-1));
	const double ans1=base*p*(p+1)*G::ans;
	const double ans2=base*p*(p-1)*G::ans;
	for(int i=1;i<=tp;++i){
		printf("%.2lf\n",ans1);
	}
	for(int i=tp+1;i<=3;++i){
		printf("%.2lf\n",ans2);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		fort[i]=nxi();
	}
	std::sort(fort+1,fort+m+1);
	for(int i=1;i<n;++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs(1);
	G::solve(1);
//	printf("ans:%lld\n",G::ans);
	oput();
	return 0;
}
