#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
const int N=105;
int m,n,cnp,val[N<<1],prm[3200];
bool npr[3200];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	npr[1]=1;
	for(int i=2;i<3200;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<3200;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline bool ispr(int x){
	if(x<3200) return !npr[x];
	int sq=sqrt(x);
	for(int i=1; prm[i]<=sq; ++i){
		if(x%prm[i]==0) return 0;
	}
	return 1;
}

namespace G{
	int cnt,fir[N<<1],cur[N<<1],dep[N<<1];
	struct edge{
		int to,wi,nx;
	}eg[N*(N+4)];

	inline void add(const int a,const int b,const int v){
		//printf("add: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	inline void clear(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}

	bool bfs(){
		static int que[N<<1];
		memset(dep,0,(n+2)*sizeof(int));
		dep[0]=1;
		que[0]=0;
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&!dep[y]){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[n+1];
	}

	int dfs(const int x,const int t){
		if(x==n+1) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if((tt-=tp)==0) break;
			}
		}
		return t-tt;
	}
}

int main(){
#ifdef LOCAL
	//freopen("d.in","r",stdin);
#endif
	static int lit[N];
	init();
	for(int T=nxi(); T; --T){
		m=nxi();
		n=0;
		for(int i=1; i<=m; ++i){
			lit[i]=nxi();
		}
		lit[0]=-1;
		for(int i=1; i<=m; ++i){
			if(lit[i]!=lit[i-1]+1){
				if(lit[i-1]+1>0)
					val[++n]=lit[i-1]+1;
				val[++n]=lit[i];
			}
		}
		val[++n]=lit[m]+1;
		G::clear();
		int cnt_odd=0;
		for(int i=1; i<=n; ++i){
			if(val[i]&1){
				++cnt_odd;
				G::add(0,i,1);
			}
			else{
				G::add(i,n+1,1);
			}
			for(int j=1; j<i; ++j){
				int p=val[i]-val[j];
				if(!(p&1)||!ispr(p)) continue;
				if(val[i]&1)
					G::add(i,j,1);
				else
					G::add(j,i,1);
			}
		}
		int ans=0;
		while(G::bfs()){
			ans+=G::dfs(0,1e9);
		}
		printf("%d\n",n-ans+((cnt_odd-ans)&1));
	}
	return 0;
}
