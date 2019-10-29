#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=505;
const int mod=998244353;
int n,C[N][N],dp[N][N],sum[N][N];
bool bad[N];

namespace utils{
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

int main(){
	n=nxi();
	for(int i=nxi(); i; --i){
		bad[nxi()]=1;
	}
	for(int i=0; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	dp[0][0]=dp[1][1]=1;
	sum[0][0]=1;
	for(int i=1; i<=n; ++i){
		sum[0][i]=sum[1][i]=1;
	}
	for(int i=2; i<=n; ++i){
		//if(bad[i]) continue;
		for(int j=2; j<=i; ++j){
			for(int k=1; k<i; ++k){
				if(bad[k]) continue;
				lint r1=(lint)dp[k][j-1]*sum[i-k][j-1];
				lint r2=(lint)dp[k][j-1]*dp[i-k][j];
				lint r3=(lint)sum[k][j-2]*dp[i-k][j];
				dp[i][j]=(dp[i][j]+(r1+r2+r3)%mod*C[i-2][k-1])%mod;
			}
			sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
		}
		for(int j=i+1; j<=n; ++j){
			sum[i][j]=sum[i][j-1];
		}
	}
	for(int ql=nxi(),qr=nxi(),i=ql; i<=qr; ++i){
		printf("%d ",bad[n]?0:dp[n][i]);
	}
	puts("");
	return 0;
}
