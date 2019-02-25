#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=52;
const int M=1280;
lint dp[N][M][2];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_seq(const int x){
	return x*(x+1)>>1;
}

int main(){
	int n=nxi();
	int tot=get_seq(n);
	long double ans=0;
	dp[0][0][0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=tot; j>=0; --j){
			for(int k=i-1; k>=0; --k){
				if(j<get_seq(i-k-1)) break;
				dp[i][j][0]+=dp[k][j-get_seq(i-k-1)][1];
				dp[i][j][1]+=dp[k][j-get_seq(i-k-1)][0];
			}
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=0; j<tot-get_seq(n-i); ++j){
			const int real=j+get_seq(n-i);
			const long double res=(long double)tot/(tot-real);
			ans+=dp[i][j][1]*res;
			ans-=dp[i][j][0]*res;
		}
	}
	printf("%Lf\n",ans);
	return 0;
}
