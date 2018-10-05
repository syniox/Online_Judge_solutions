#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e3+2;
int n,cnf,sz[N],bel[N],prs[N];
bool vis[N],map[N][N];

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

namespace G{
	int top,cnd,cnt,fir[N],dfn[N],low[N],stk[N];
	bool inq[N];
	struct edge{
		int to,nx;
	}eg[N*N<<1];
	inline void init(){
		cnt=cnd=cnf=top=0;
		memset(fir,0,sizeof(fir));
		memset(dfn,0,sizeof(dfn));
		memset(inq,0,sizeof(inq));
	}
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void tarjan(const int x){
		dfn[x]=low[x]=++cnd;
		stk[++top]=x;
		inq[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){
				tarjan(y);
				apn(low[x],low[y]);
			}
			else{
				if(inq[y]) apn(low[x],dfn[y]);
			}
		}
		if(dfn[x]==low[x]){
			++cnf;
			int p=0;
			while(p!=x){
				p=stk[top--];
				++sz[cnf];
				bel[p]=cnf;
				inq[p]=0;
			}
		}
	}
	inline void make_map(){
		for(int x=1;x<=n;++x){
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(bel[x]!=bel[y]) map[bel[x]][bel[y]]=1;
			}
		}
	}
}

void add_prs(const int x,const int sz){
	prs[x]+=sz;
	vis[x]=1;
	for(int i=1;i<=n;++i){
		if(map[x][i]&&!vis[i]) add_prs(i,sz);
	}
}

inline double get_ans(){
	double ans=0;
	for(int i=1;i<=cnf;++i){
		ans+=(double)sz[i]/(double)prs[i];
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int tick=0,T=nxi();
	while(T--){
		memset(prs,0,sizeof(prs));
		memset(sz,0,sizeof(sz));
		memset(map,0,sizeof(map));
		G::init();
		n=nxi();
		for(int i=1;i<=n;++i){
			int k=nxi();
			while(k--) G::add(i,nxi());
		}
		for(int i=1;i<=n;++i){
			if(!G::dfn[i]) G::tarjan(i);
		}
		G::make_map();
		for(int i=1;i<=cnf;++i){
			memset(vis,0,sizeof(vis));
			add_prs(i,sz[i]);
		}
		printf("Case #%d: %.5lf\n",++tick,get_ans());
	}
	return 0;
}
