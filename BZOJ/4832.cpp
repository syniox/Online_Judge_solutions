#include<iostream>
#include<cstdio>
#include<cstring>
double dp[2][51][8][8][8];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int T=nxi();
	while(T--){
		int n=nxi(),a=nxi(),b=nxi(),c=nxi();
		dp[0][0][a][b][c]=1;
		for(int i=0;i<n;++i){
			int p=i&1;
			for(int j=0;j<=i;++j){
				for(int k=0;k<=7;++k){
					for(int l=0;l<=7-k;++l){
						for(int m=0;m<=7-k-l;++m){
							if(dp[p][j][k][l][m]){
								double s=dp[p][j][k][l][m]/(k+l+m+1);
								dp[p^1][j+1][k][l][m]+=s;
								if(k) dp[p^1][j][k-1][l][m]+=s*k;
								if(k+l+m<7){
									if(l) dp[p^1][j][k+1][l-1][m+1]+=s*l;
									if(m) dp[p^1][j][k][l+1][m]+=s*m;
								}
								else{
									if(l) dp[p^1][j][k+1][l-1][m]+=s*l;
									if(m) dp[p^1][j][k][l+1][m-1]+=s*m;
								}
								dp[p][j][k][l][m]=0;
							}
						}
					}
				}
			}
		}
		double ans=0;
		for(int i=0;i<=n;++i){
			for(int j=0;j<=7;++j){
				for(int k=0;k<=7;++k){
					for(int l=0;l<=7;++l){
						ans+=dp[n&1][i][j][k][l]*i;
						dp[n&1][i][j][k][l]=0;
					}
				}
			}
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
