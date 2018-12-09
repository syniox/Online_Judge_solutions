#include <iostream>
#include <cstdio>
#include <cstring>
const int N=102;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt=1,fir[N*N],cur[N*N],dep[N*N];
	struct edge{
		int to,wi,nx;
	}eg[N*N*10];

	inline void add(const int a,const int b,const int v1,const int v2){
		eg[++cnt]=(edge){b,v1,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,v2,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[N*N];
		int hd=0,tl=1;
		memset(dep,-1,sizeof(dep));
		dep[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&dep[y]==-1){
					que[tl++]=y;
					dep[y]=dep[x]+1;
				}
			}
		}
		return dep[n*m+1]!=-1;
	}

	int dfs(const int x,const int t){
		if(x==n*m+1) return t;
		int tt=t,tp;
		for(int &i=cur[x];i;i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&tt&&(dep[y]==dep[x]+1)&&(tp=dfs(y,std::min(v,tt)))){
				eg[i^1].wi+=tp;
				eg[i].wi-=tp;
				if(!(tt-=tp)) break;
			}
		}
		return t-tt;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1,cnp=1;i<=n;++i){
		for(int j=1;j<=m;++j,++cnp){
			const int hx=nxi();
			if(hx==1) G::add(cnp,n*m+1,1e8,0);
			else if(hx==2) G::add(0,cnp,1e8,0);
			if(j>1) G::add(cnp,cnp-1,1,1);
			if(i>1) G::add(cnp,cnp-m,1,1);
		}
	}
	int ans=0;
	while(G::bfs()) ans+=G::dfs(0,1e6);
	printf("%d\n",ans);
	return 0;
}
