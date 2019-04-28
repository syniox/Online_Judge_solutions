#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
int n,m,tot_n,tot_m,ans[1001][1001];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace G{
	const int N=325;
	int cnt,fir[N],lnk[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N*12];

	inline void clear(const int len){
		cnt=0;
		memset(fir+1,0,len*sizeof(fir[0]));
		memset(lnk+1,0,len*sizeof(lnk[0]));
	}

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	bool dfs(const int x){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]) continue;
			vis[y]=1;
			if(!lnk[y]||dfs(lnk[y])){
				lnk[y]=x;
				lnk[x]=y;
				return 1;
			}
		}
		return 0;
	}
}

inline int id(const int x,const int y){
	return (x-1)*m+y;
}

inline bool vld(const int x,const int y){
	return x>0&&x<=n&&y>0&&y<=m;
}

inline void build_edge(){
	static int cx[]={0,-1,-2,-3,-2,-1,0,1,2,3,2,1};
	static int cy[]={3,2,1,0,-1,-2,-3,-2,-1,0,1,2};
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			for(int k=0; k<12; ++k){
				int tx=i+cx[k],ty=j+cy[k];
				if(vld(tx,ty)){
					G::add(id(i,j),id(tx,ty));
				}
			}
		}
	}
}

int main(){
	for(int T=nxi(); T; --T){
		tot_n=nxi(),tot_m=nxi();
		n=tot_n>12?tot_n%6+12:tot_n;
		m=tot_m>12?tot_m%6+12:tot_m;
		G::clear(n*m);
		build_edge();
		for(int i=1; i<=n*m; ++i){
			if(!G::lnk[i]){
				memset(G::vis+1,0,n*m*sizeof(bool));
				G::dfs(i);
			}
		}
		for(int i=1; i<=tot_n; ++i){
			memset(ans[i]+1,0,tot_m*sizeof(int));
		}
		int cnd=0;
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				const int x=id(i,j),y=G::lnk[x];
				if(!y) continue;
				G::lnk[x]=G::lnk[y]=0;
				int k=(y-1)/m;
				ans[i][j]=++cnd;
				ans[k+1][y-k*m]=cnd;
			}
		}
		for(int i=1; i<=tot_n; ++i){
			for(int j=m+1; j<=tot_m; j+=6){
				ans[i][j+0]=cnd+1;
				ans[i][j+1]=cnd+2;
				ans[i][j+2]=cnd+3;
				ans[i][j+3]=cnd+1;
				ans[i][j+4]=cnd+2;
				ans[i][j+5]=cnd+3;
				cnd+=3;
			}
		}
		for(int i=1; i<=m; ++i){
			for(int j=n+1; j<=tot_n; j+=6){
				ans[j+0][i]=cnd+1;
				ans[j+1][i]=cnd+2;
				ans[j+2][i]=cnd+3;
				ans[j+3][i]=cnd+1;
				ans[j+4][i]=cnd+2;
				ans[j+5][i]=cnd+3;
				cnd+=3;
			}
		}
		printf("%d\n",cnd<<1);
		for(int i=1; i<=tot_n; ++i){
			for(int j=1; j<=tot_m; ++j){
				printf("%d ",ans[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
