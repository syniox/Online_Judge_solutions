#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=3002;
const int mod=1e9+7;
int n,m,dp[2][N][2];
//0: haven't touch dead line 1:have

inline void twk(int &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	dp[0][0][1]=1;
	for(int i=1;i<=n;++i){
		dp[0][i][0]=1;
	}
	for(int i=1;i<=m;++i){
		int p=i&1;
		memset(dp[p],0,sizeof(dp[p]));
		twk(dp[p][0][1]+=dp[p^1][1][0]);
		twk(dp[p][1][1]+=dp[p^1][1][0]);
		for(int j=0;j<=n;++j){
			if(j>1){
				twk(dp[p][j][0]+=dp[p^1][j][0]);
				twk(dp[p][j][0]+=dp[p^1][j-1][0]);
			}
			if(j&&j<n){
				twk(dp[p][j][0]+=dp[p^1][j][0]);
				twk(dp[p][j][0]+=dp[p^1][j+1][0]);
			}
			if(j){
				twk(dp[p][j][1]+=dp[p^1][j][1]);
				twk(dp[p][j][1]+=dp[p^1][j-1][1]);
			}
			if(j<n){
				twk(dp[p][j][1]+=dp[p^1][j][1]);
				twk(dp[p][j][1]+=dp[p^1][j+1][1]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;++i){
		twk(ans+=dp[m&1][i][1]);
	}
	printf("%d\n",ans);
	return 0;
}
