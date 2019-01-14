#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1005;
int n,m,l,vir_fa[N],fir_eg[N];
int mp[N][N];
struct _Space{
	int l,r,v;
	friend bool operator < (const _Space &a,const _Space &b){
		return a.r-a.l<b.r-b.l;
	}
}spc[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt=1,fir[N],cur[N],dep[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<3];

	inline void add(const int a,const int b,const int v1,const int v2){
		//printf("%d->%d: %d,%d\n",a,b,v1,v2);
		eg[++cnt]=(edge){b,v1,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,v2,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[N];
		memset(dep,0,sizeof(dep));
		dep[0]=1;
		int hd=0,tl=1;
		while(hd!=tl){
			int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&!dep[y]){
					dep[y]=dep[x]+1;
					que[tl++]=y;
				}
			}
		}
		return dep[N-1];
	}

	int dfs(int x,int t){
		if(x==N-1) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i^1].wi+=tp;
				eg[i].wi-=tp;
				if((tt-=tp)==0) break;
			}
		}
		return t-tt;
	}
}

inline bool build_base(){
	static int cf[N];
	int pre;
	for(int i=1; i<=m; ++i){
		++cf[spc[i].l];
		--cf[spc[i].r];
	}
	pre=0;
	for(int i=1; i<n; ++i){
		if((pre+=cf[i])<=0) return 0;
	}
	for(int i=m; i; --i){
		G::add(vir_fa[i],i,spc[i].v,1e9+5);//fake?
		memset(cf,0,sizeof(cf));
		for(int j=i-1; j; --j){
			if(spc[j].l>=spc[i].l&&spc[j].r<=spc[i].r){
				vir_fa[j]=i;
				++cf[spc[j].l];
				--cf[spc[j].r];
			}
		}
		for(int j=spc[i].l+1; j<spc[i].r; ++j){
			fir_eg[j]=i;
		}
		bool flag=0;
		pre=0;
		for(int j=spc[i].l; j<spc[i].r; ++j){
			if((pre+=cf[j])<=0){
				flag=1;
				break;
			}
		}
		if(flag) G::add(i,N-1,1e9+5,0);
	}
	return 1;
}

int main(){
	n=nxi(),m=nxi(),l=nxi();
	for(int i=1; i<=m; ++i){
		int x=nxi(),y=nxi(),v=nxi();
		if(!mp[x][y]||mp[x][y]>v){
			mp[x][y]=v;
			spc[i]=(_Space){x,y,v};
		}
	}
	m=0;
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			if(mp[i][j]) spc[++m]=(_Space){i,j,mp[i][j]};
		}
	}
	std::sort(spc+1,spc+m+1);
	/*
	for(int i=1; i<=m; ++i){
		printf("space%d: %d-%d, v%d\n",i,spc[i].l,spc[i].r,spc[i].v);
	}
	 */
	if(!build_base()){
		puts("-1");
		return 0;
	}
	for(int i=1; i<=l; ++i){
		const int x=nxi(),y=nxi();
		if(fir_eg[x]!=fir_eg[y]){
			G::add(fir_eg[x],fir_eg[y],1e9+5,1e9+5);
		}
	}
	int ans=0;
	while(G::bfs()){
		if((ans+=G::dfs(0,1e9+5))>=1e9+5) break;
	}
	printf("%d\n",ans>=1e9+5?-1:ans);
	return 0;
}
