#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=405;
int n,m,q,qcnt;
int icnt,key[N],door[N],idx[N],ivl[N];
int idis[N][N],idp[33][33][1<<16];
int ans[N][N];
struct data{
	int x,t,dis;
	friend bool operator < (const data &a,const data &b){
		return a.dis>b.dis;
	}
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void floyd_jk(int dis[N][N],int i){
	for(int j=1; j<=n; ++j){
		for(int k=1; k<=n; ++k)
			apn(idis[j][k],idis[j][i]+idis[i][k]);
	}
}

void dij(const int s,int dp[33][1<<16]){
	static bool vis[33][1<<16];
	std::priority_queue <data> pq;
	for(int i=1; i<=icnt; ++i){
		memset(dp[i],60,sizeof(dp[i]));
	}
	memset(vis,0,sizeof(vis));
	pq.push((data){s,key[ivl[s]],0});
	while(!pq.empty()){
		data x=pq.top();
		pq.pop();
		if(vis[x.x][x.t]) continue;
		vis[x.x][x.t]=1;
		for(int i=1; i<=icnt; ++i){
			int st_t=x.t|key[ivl[i]],v=x.dis+idis[ivl[x.x]][ivl[i]];
			if(door[ivl[i]]&~st_t) continue;
			if(dp[i][st_t]>v){
				dp[i][st_t]=v;
				pq.push((data){i,st_t,v});
			}
		}
	}
}

void getans(){
	static int ians[33][33];
	memset(ians,60,sizeof(ians));
	for(int i=1; i<=icnt; ++i){
		for(int j=1; j<=icnt; ++j){
			for(int k=0; k<1<<q; ++k)
				apn(ians[i][j],idp[i][j][k]);
		}
	}
	memset(ans,60,sizeof(ans));
	for(int i=1; i<=n; ++i){
		if(door[i]) continue;
		for(int j=1; j<=n; ++j){
			if(!(door[j]&~key[i])) ans[i][j]=idis[i][j];
			for(int k=1; k<=icnt; ++k){
				if(door[ivl[k]]) continue;
				if(door[j]||key[j]){
					apn(ans[i][j],idis[i][ivl[k]]+ians[k][idx[j]]);
					continue;
				}
				for(int l=1; l<=icnt; ++l){
					apn(ans[i][j],idis[i][ivl[k]]+ians[k][l]+idis[ivl[l]][j]);
				}
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	memset(idis,60,sizeof(idis));
	for(int i=1; i<=n; ++i)
		idis[i][i]=0;
	for(int i=1; i<=m; ++i){
		int x=nxi(),y=nxi(),v=nxi();
		apn(idis[x][y],v);
		apn(idis[y][x],v);
	}
	for(int i=0; i<q; ++i){
		door[nxi()]|=1<<i,key[nxi()]|=1<<i;
	}
	for(int i=1; i<=n; ++i){
		if(door[i]||key[i]) ivl[++icnt]=i,idx[i]=icnt;
	}
	for(int i=1; i<=n; ++i){
		if(idx[i]) continue;
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=n; ++k){
				apn(idis[j][k],idis[j][i]+idis[i][k]);
			}
		}
	}
	for(int i=1; i<=icnt; ++i){
		if(!door[ivl[i]]) dij(i,idp[i]);
	}
	getans();
	for(int i=nxi(); i; --i){
		int x=nxi(),y=nxi();
		printf("%d\n",ans[x][y]<1e9?ans[x][y]:-1);
	}
	return 0;
}
