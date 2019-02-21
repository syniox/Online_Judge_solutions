#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1050;
int n,m,cap[22],rnk[N][22];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],cur[N],dep[N];
	struct edge{
		int to,wi,nx;
	}eg[N*42];

	inline void clear(){
		cnt=1;
		memset(fir,0,(n+m+2)*sizeof(int));
	}

	inline void add(const int a,const int b,const int v){
		//printf("add: %d -> %d: %d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	inline bool bfs(){
		static int que[N];
		int hd=0,tl=1;
		memset(dep,0,(n+m+2)*sizeof(int));
		dep[0]=1;
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
		return dep[n+m+1];
	}

	int dfs(const int x,const int t){
		if(x==n+m+1) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				tt-=tp;
				if(!tt) return t;
			}
		}
		return t-tt;
	}

	inline bool valid(const int l,const int r){
		clear();
		for(int i=1; i<=n; ++i){
			add(0,i,1);
		}
		for(int i=1; i<=m; ++i){
			add(n+i,n+m+1,cap[i]);
		}
		for(int i=1; i<=n; ++i){
			for(int j=l; j<=r; ++j) add(i,n+rnk[i][j],1);
		}
		int ans=0;
		while(bfs()){
			ans+=dfs(0,N);
		}
		return ans==n;
	}

	inline bool jdg(const int tgt){
		for(int i=1; i+tgt-1<=m; ++i){
			if(valid(i,i+tgt-1)) return 1;
		}
		return 0;
	}
}

inline int solve(){
	int l=1,r=m,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(G::jdg(mid)) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			rnk[i][j]=nxi();
		}
	}
	for(int i=1; i<=m; ++i){
		cap[i]=nxi();
	}
	printf("%d\n",solve());
	return 0;
}
