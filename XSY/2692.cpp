#include <iostream>
#include <cstdio>
#include <cstring>
const int N=105;
int ro,co,n,qa,qb;
bool good[N*N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool vld(const int x,const int y){
	return x>0&&x<=ro&&y>0&&y<=co;
}

namespace G{
	int cnt,fir[N*N],pre_p[N*N],pre_e[N*N];
	struct edge{
		int to,wi,cs,nx;
	}eg[N*N<<4];

	inline void add(const int a,const int b,const int v,const int c){
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
	}

	inline bool spfa(){
		static int que[N*N],dis[N*N];
		static bool vis[N*N];
		memset(dis,1,sizeof(dis));
		int hd=0,tl=1;
		que[0]=dis[0]=0;
		while(hd!=tl){
			int x=que[hd++];
			vis[x]=0;
			if(hd==N*N) hd=0;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to,v=eg[i].cs;
				if(eg[i].wi&&dis[x]+v<dis[y]){
					dis[y]=dis[x]+v;
					pre_p[y]=x,pre_e[y]=i;
					if(!vis[y]){
						que[tl++]=y;
						if(tl==N*N) tl=0;
						vis[y]=1;
					}
				}
			}
		}
		return dis[N*N-1]<16000000;
	}

	inline int solve(){
		int cnt=0,ans=0;
		while(spfa()){
			for(int x=N*N-1;x;x=pre_p[x]){
				int p=pre_e[x];
				ans+=eg[p].cs;
				--eg[p].wi;
				++eg[p^1].wi;
			}
			++cnt;
		}
		return cnt==n?ans:-1;
	}
}

inline void init(){
	int cx[]={qa,qa,-qa,-qa,qb,qb,-qb,-qb};
	int cy[]={qb,-qb,qb,-qb,qa,-qa,qa,-qa};
	for(int i=1;i<=ro;++i){
		char c;
		for(int j=1;j<=co;++j){
			const int cur=(i-1)*co+j;
			while((c=getchar())!='.'&&c!='*');
			if(!(good[cur]=c=='.')) continue;
			for(int k=0;k<8;++k){
				int tx=i+cx[k],ty=j+cy[k];
				if(vld(tx,ty)) G::add(cur,(tx-1)*co+ty,1e8,1);
			}
		}
	}
	for(int i=1;i<=n;++i){
		const int x=nxi(),y=nxi();
		G::add(0,(x-1)*co+y,1,0);
	}
	for(int i=1;i<=n;++i){
		const int x=nxi(),y=nxi();
		G::add((x-1)*co+y,(N*N)-1,1,0);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	G::cnt=1;
	ro=nxi(),co=nxi(),n=nxi(),qa=nxi(),qb=nxi();
	init();
	printf("%d\n",G::solve());
	return 0;
}
