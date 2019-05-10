#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=5e4+5;
int n,m,q;
//改变白色边权,计算当前最小生成树最多能用多少条白边

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

namespace U{
	int fa[N];
	void init(){
		memset(fa+1,0,n*sizeof(int));
	}
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace G{
	int ans;
	struct edge{
		int x,y,v;
		bool c;
		friend inline bool operator < (const edge &a,const edge &b){
			return a.v==b.v?a.c<b.c:a.v<b.v;
		}
	}eg[N<<1];

	int jdg(const int tgt){
		int cnt=0;
		U::init();
		for(int i=1; i<=m; ++i){
			if(eg[i].c==0) eg[i].v+=tgt;
		}
		std::sort(eg+1,eg+m+1);
		ans=0;
		for(int i=1; i<=m; ++i){
			int x=U::find_rt(eg[i].x);
			int y=U::find_rt(eg[i].y);
			if(x!=y){
				U::fa[x]=y;
				cnt+=eg[i].c==0;
				ans+=eg[i].v;
			}
		}
		for(int i=1; i<=m; ++i){
			if(eg[i].c==0) eg[i].v-=tgt;
		}
		return cnt;
	}
}

int solve(){
	int l=-1e3,r=1e3,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(G::jdg(mid)>=q) l=mid;
		else r=mid-1;
	}
	G::jdg(l);
	return G::ans-q*l;
}

int main(){
	for(int cas=1; ~scanf("%d%d%d",&n,&m,&q); ++cas){
		for(int i=1; i<=m; ++i){
			using G::eg;
			eg[i].x=nxi()+1,eg[i].y=nxi()+1;
			eg[i].v=nxi(),eg[i].c=nxi();
		}
		printf("Case %d: %d\n",cas,solve());
	}
	return 0;
}
