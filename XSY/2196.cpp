#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=105;
const int mod=1004535809;
int n,q,val[N],C[N][N],dp[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=0; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
}

int main(){
	n=nxi();
	init();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	dp[0][0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=i; j; --j){
			for(int k=n; ~k; --k){
				for(int l=0; l<=k&&l<val[i]; ++l){
					dp[j][k]=(dp[j][k]+(lint)dp[j-1][k-l]*C[k][l])%mod;
				}
			}
		}
	}
	printf("%d ",n);
	for(int i=2; i<=n; ++i){
		printf("%d ",dp[i][i-2]);
	}
	puts("");
	return 0;
}
