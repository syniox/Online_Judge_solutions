#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=152;
const int M=5005;
int n,m,q,dp[N][N][N];
struct edge{
	int x,y,v;
	friend bool operator < (const edge &a,const edge &b){
		return a.v<b.v;
	}
}eg[M];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi(),eg[i].v=nxi();
	}
	std::sort(eg+1,eg+m+1);
	for(int i=1; i<=n; ++i){
		memset(dp[i],10,sizeof(dp[i]));
		dp[i][i][0]=0;
		for(int j=1; j<=m; ++j){
			for(int k=0; k<n; ++k){
				apn(dp[i][eg[j].y][k+1],dp[i][eg[j].x][k]+eg[j].v);
			}
		}
		for(int j=1; j<=n; ++j){
			for(int k=1; k<n; ++k){
				apn(dp[i][j][k],dp[i][j][k-1]);
			}
		}
	}
	while(q--){
		const int a=nxi(),b=nxi(),v=nxi();
		int res=dp[a][b][std::min(n-1,v)];
		printf("%d\n",res<1e7?res:-1);
	}
	return 0;
}
