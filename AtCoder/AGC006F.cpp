#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e5+2;
int m,n,cnf,in[N],sz[N],col[N],bel[N],fir[N],cedge[N],scol[N][3];
bool str[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int fir_e[N],fir_f[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N],fg[N];
	inline void add_e(int a,int b){
		static int cnt;
		eg[++cnt]=(edge){b,fir_e[a]};
		fir_e[a]=cnt;
	}
	inline void add_f(int a,int b){
		static int cnt;
		fg[++cnt]=(edge){b,fir_f[a]};
		fir_f[a]=cnt;
	}
	void get_link(int x){
		bel[x]=cnf;
		++sz[cnf];
		cedge[cnf]+=in[x];
		for(int i=fir_e[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!bel[y]) get_link(y);
		}
		for(int i=fir_f[x];i;i=fg[i].nx){
			int y=fg[i].to;
			if(!bel[y]) get_link(y);
		}
	}
	void dfs(int x){
		++scol[bel[x]][col[x]-1];
		for(int i=fir_e[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!col[y]){
				col[y]=col[x]==3?1:col[x]+1;
				dfs(y);
			}
			else if(col[y]!=col[x]+1&&col[y]!=col[x]-2){
				str[bel[x]]=1;
			}
		}
		for(int i=fir_f[x];i;i=fg[i].nx){
			int y=fg[i].to;
			if(!col[y]){
				col[y]=col[x]==1?3:col[x]-1;
				dfs(y);
			}
			else if(col[y]!=col[x]-1&&col[y]!=col[x]+2){
				str[bel[x]]=1;
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		int a=nxi(),b=nxi();
		G::add_e(a,b);
		G::add_f(b,a);
		++in[b];
	}
	for(int i=1;i<=n;++i){
		if(!bel[i]){
			++cnf;
			G::get_link(i);
		}
	}
	for(int i=1;i<=n;++i){
		if(!col[i]){
			col[i]=1;
			G::dfs(i);
		}
	}
	lint ans=0;
	for(int i=1;i<=cnf;++i){
		if(str[i]){
			ans+=(lint)sz[i]*sz[i];
		}
		else if(scol[i][2]&&scol[i][1]&&scol[i][0]){
			int *p=scol[i];
			ans+=(lint)p[0]*p[1]+(lint)p[1]*p[2]+(lint)p[2]*p[0];
		}
		else{
			ans+=cedge[i];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
