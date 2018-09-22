#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2502;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	static double dp[N][52][52];
	//dp[i stamps][j lines][k columns]
	int T=nxi();
	while(T--){
		memset(dp,0,sizeof(dp));
		const int n=nxi(),m=nxi();
		double ans=0;
		dp[0][0][0]=1;
		for(int i=0;i<n*m;++i){
			for(int j=0;j<=n;++j){
				for(int k=0;k<=m;++k){
					if(!dp[i][j][k]||(j==n&&k==m)||j*k<i) continue;
					const double cur=dp[i][j][k]/(n*m-i);
					dp[i+1][j][k]+=cur*(j*k-i);
					dp[i+1][j+1][k]+=cur*((n-j)*k);
					dp[i+1][j][k+1]+=cur*(j*(m-k));
					dp[i+1][j+1][k+1]+=cur*(n-j)*(m-k);
				}
			}
//			for(int j=0;j<=n;++j){
//				for(int k=0;k<=m;++k){
//					printf("%.3lf ",dp[i+1][j][k]);
//				}
//				puts("");
//			}
//			puts("-----");
			if(dp[i+1][n][m]) ans+=dp[i+1][n][m]*(i+1);
		}
		printf("%.12lf\n",ans);
	}
	return 0;
}
