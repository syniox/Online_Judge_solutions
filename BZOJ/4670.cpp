#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=255;
int n,cnt_dt;
struct data{
	int x,y,v;
	bool operator < (const data &b) const {
		return v<b.v;
	}
}dt[N*N>>1];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace UFS{
	int fa[N];
	inline void init(){
		memset(fa,0,sizeof(fa));
	}
	inline int find_rt(int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace G{
	int cnd,cnt,cnf,fir[N<<1],dfn[N<<1],low[N<<1],bel[N<<1];
	bool vis[N<<1];
	//0~n: in a, n+1~n*2: in b
	struct edge{
		int to,nx;
	}eg[N*N<<2];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void init(){
		cnd=cnt=cnf=0;
		memset(dfn,0,sizeof(dfn));
		memset(fir,0,sizeof(fir));
		memset(vis,0,sizeof(vis));
	}

	void tarjan(const int x){
		static int top,stk[N<<1];
		dfn[x]=low[x]=++cnd;
		stk[++top]=x;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(dfn[y]){
				if(!vis[y]) apn(low[x],dfn[y]);
			}
			else{
				tarjan(y);
				apn(low[x],low[y]);
			}
		}
		if(dfn[x]==low[x]){
			++cnf;
			int j=0;
			while(j!=x){
				j=stk[top--];
				vis[j]=1;
				bel[j]=cnf;
			}
		}
	}

	inline bool jdg(const int pta,const int ptb){
		init();
		for(int i=pta+1;i<=ptb;++i){
			add(dt[i].x,dt[i].y+n);
			add(dt[i].y,dt[i].x+n);
		}
		for(int i=ptb+1;i<=cnt_dt;++i){
			add(dt[i].x,dt[i].y+n);
			add(dt[i].y,dt[i].x+n);
			add(dt[i].x+n,dt[i].y);
			add(dt[i].y+n,dt[i].x);
		}
		for(int i=1;i<=n<<1;++i){
			if(!dfn[i]) tarjan(i);
		}
		for(int i=1;i<=n;++i){
			if(bel[i]==bel[i+n]) return 0;
		}
		return 1;
	}
}

inline int find_pos(const int ptb){
	int l=1,r=ptb,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(G::jdg(mid,ptb)) l=mid;
		else r=mid-1;
	}
	return l;
}

inline int solve(){
	int pta=find_pos(cnt_dt),ptb=cnt_dt;
	int ans=dt[pta].v+dt[ptb].v;
	for(ptb=cnt_dt-1;ptb;--ptb){
		const int x=dt[ptb+1].x,y=dt[ptb+1].y;
		const int rx=UFS::find_rt(x),ry=UFS::find_rt(y);
		if(rx==ry) apn(pta,ptb);
		else{
			UFS::fa[rx]=ry;
			pta=find_pos(ptb);
			if(pta>ptb) break;
		}
		apn(ans,dt[pta].v+dt[ptb].v);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	while(~scanf("%d",&n)){
		UFS::init();
		cnt_dt=0;
		for(int i=1;i<n;++i){
			for(int j=i+1;j<=n;++j){
				dt[++cnt_dt]=(data){i,j,nxi()};
			}
		}
		std::sort(dt+1,dt+cnt_dt+1);
		printf("%d\n",solve());
	}
	return 0;
}
