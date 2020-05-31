#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005,P=15;
int lg2[N],C[N][N],dp[N][P][3],psum[N][P][3];
//长i 清j次恰好清完(k=1,2)或剩一个(k=0) 与k座大山相邻的排列数

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

const int n=nxi(),q=nxi(),mod=nxi();

void get_psum(int l){
	psum[l][0][1]=dp[l][0][1];
	psum[l][0][2]=dp[l][0][2];
	for(int i=1; i<P; ++i){
		psum[l][i][1]=((lint)psum[l][i-1][1]+dp[l][i][1])%mod;
		psum[l][i][2]=((lint)psum[l][i-1][2]+dp[l][i][2])%mod;
	}
}

int main(){
	if(n==1){
		printf("%d\n",q==0);
		return 0;
	}
	for(int i=2; i<=n; ++i){
		lg2[i]=lg2[i>>1]+1;
	}
	for(int i=0; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=((lint)C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	dp[0][0][1]=dp[0][0][2]=dp[1][1][1]=dp[1][1][2]=1;
	get_psum(0),get_psum(1);
	for(int i=2; i<=n; ++i){
		for(int j=1; j<=lg2[i]+1; ++j){
			if(i==n&&j==q){//0
				int ans=dp[i-1][j][1]*2ll%mod;
				for(int k=1; k<i-1; ++k){
					ans=(ans+2ll*C[i-1][k]*psum[k][j][1]%mod*dp[i-k-1][j][1])%mod;
					ans=(ans-(lint)C[i-1][k]*dp[k][j][1]%mod*dp[i-k-1][j][1])%mod;
				}
				dp[i][j][0]=((lint)ans+mod)%mod;
			}
			{//1
				int ans=0;
				for(int k=0; k<i; ++k){//最后被清除的点包含最大值
					ans=(ans+(lint)C[i-1][k]*dp[k][j-1][2]%mod*psum[i-k-1][j][1])%mod;
				}
				for(int k=0; j>1&&k<i; ++k){//最后被清除的点在一侧
					ans=(ans+(lint)C[i-1][k]*psum[k][j-2][2]%mod*dp[i-k-1][j][1])%mod;
				}
				dp[i][j][1]=ans;
			}
			{//2
				int ans=0;
				for(int k=0; k<=i-1; ++k){//最后被清除的点包含最大值
					int l=i-k-1;
					int wgt=(lint)dp[k][j-1][2]*dp[l][j-1][2]%mod;
					wgt=((lint)wgt+(lint)dp[k][j][2]*dp[l][j-1][2])%mod;
					wgt=((lint)wgt+(lint)dp[k][j-1][2]*dp[l][j][2])%mod;
					ans=(ans+(lint)C[i-1][k]*wgt)%mod;
				}
				for(int k=1; j>1&&k<i; ++k){//最后被清除的点在一侧
					ans=(ans+2ll*C[i-1][k]%mod*psum[i-k-1][j-2][2]%mod*dp[k][j][2])%mod;
				}
				dp[i][j][2]=ans;
			}
		}
		get_psum(i);
	}
	printf("%d\n",q<P?dp[n][q][0]:0);
	return 0;
}
