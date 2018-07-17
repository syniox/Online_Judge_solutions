#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;
const int N=1002;
int n,m,cnf,bel[N];
template<class T> void apn(T &a,T b){
	if(a>b) a=b;
}
template<class T> void apx(T &a,T b){
	if(a<b) a=b;
}
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}
namespace G{
	int cnt,clk,top,fir[N],stk[N],dfn[N],low[N];
	bool st[N],ed[N],bh[N],bt[N],in[N],ot[N],vis[N];
	struct edge{
		int to,nx;
	}eg[N*20];

	inline void add(int a,int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void init(){
		clk=cnt=0;
		memset(fir,0,sizeof fir);
		memset(vis,0,sizeof vis);
		memset(dfn,0,sizeof dfn);
		memset(in,0,sizeof in);
		memset(ot,0,sizeof ot);
	}
	inline bool jdg(){
		for(int i=1;i<=cnf;++i){
			if(!ot[i]&&!bt[i]) return 0;
			if(!in[i]&&!bh[i]) return 0;
		}
		return 1;
	}
	void tarjan(int x){
		stk[++top]=x;
		low[x]=dfn[x]=++clk;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!dfn[y]){
				tarjan(y);
				apn(dfn[x],low[y]);
			}
			else if(!vis[y]){
				apn(dfn[x],dfn[y]);
			}
		}
		if(low[x]==dfn[x]){
			++cnf;
			int j(0);
			while(j!=x){
				j=stk[top--];
				bel[j]=cnf;
				bh[cnf]|=st[j];
				bt[cnf]|=ed[j];
				vis[j]=1;
			}
		}
	}
}
namespace F{
	int cnt,fr[N<<1],fir[N<<1],que[N<<1],dis[N<<1],pre[N<<1],cnv[N<<1];
	bool vis[N<<1];
	struct edge{
		int to,wi,cs,nx;
	}eg[26005];
	inline void init(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}
	inline void add(int x,int y,int v,int c){
		eg[++cnt]=(edge){y,v,c,fir[x]};
		fir[x]=cnt;
		eg[++cnt]=(edge){x,0,-c,fir[y]};
		fir[y]=cnt;
	}
	inline void make(){
		for(int x=1;x<=n;++x){
			if(G::bt[x]) add(x+N,(N<<1)-1,N,0);
			if(G::bh[x]) add(0,x,N,0);
			add(x,x+N,1,1);
			add(x,x+N,N,0);
			for(int i=G::fir[x];i;i=G::eg[i].nx){
				int y=G::eg[i].to;
				if(bel[x]!=bel[y]){
					add(x+N,y,N,0);
				}
			}
		}
	}
	inline bool bfs(){
		memset(dis,-1,sizeof(dis));
		dis[0]=0;
		int hd=0,tl=1;
		que[hd]=0;
		while(hd!=tl){
			int x=que[hd];
			if(++hd==N) hd=0;
			vis[x]=0;
			for(int i=fir[x];i;i=eg[i].nx){
				int y=eg[i].to,v=eg[i].wi;
				if(v&&dis[y]<dis[x]+eg[i].cs){
					pre[y]=i;
					fr[y]=x;
					dis[y]=dis[x]+eg[i].cs;
					if(!vis[y]){
						que[tl]=y;
						if(++tl==N) tl=0;
						vis[y]=1;
					}
				}
			}
		}
		return dis[(N<<1)-1];
	}
	inline void mod(){
		int x=(N<<1)-1;
		while(x){
			--eg[pre[x]].wi;
			++eg[pre[x]^1].wi;
			x=fr[x];
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		n=nxi(),m=nxi();
		int A=nxi(),B=nxi(),ans(0);
		G::init();
		for(int i=1;i<=A;++i) G::st[nxi()]=1;
		for(int i=1;i<=B;++i) G::ed[nxi()]=1;
		for(int a,b,i=1;i<=m;++i){
			a=nxi(),b=nxi();
			G::add(a,b);
			G::ot[a]=G::in[b]=1;
		}
		for(int i=1;i<=n;++i){
			if(!G::dfn[i]) G::tarjan(i);
		}
		if(!G::jdg()){
			puts("no solution");
			continue;
		}
		F::init();
		F::make();
		while(F::bfs()){
			++ans;
			F::mod();
		}
		printf("%d\n",ans);
	}
	return 0;
}
