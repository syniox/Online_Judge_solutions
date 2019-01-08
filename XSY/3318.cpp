//dp[i][j]: 前i个数,团和散点的和j的团内匹配方案数
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=505;
int n,mod,npow[N],dp[N],fp[N][N];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline T qpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	n=nxi(),mod=nxi();
	fp[0][0]=1;
	for(int i=0; i<=n; ++i){
		npow[i]=qpow(2,i*(i+1)>>1);
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=i; ++j){
			fp[i][j]=fp[i-1][j-1];
			for(int k=2; k<=i-j+1; ++k){
				fp[i][j]=(fp[i][j]+(lint)fp[i-k][j-1]*npow[k-2])%mod;
			}
		}
	}
	for(int i=1; i<=n; ++i){
		dp[i]=npow[i];
		for(int j=1; j<i; ++j){
			dp[i]=(dp[i]-(lint)dp[j]*fp[i][j])%mod;
		}
		twk(dp[i]+=mod);
	}
	printf("%d\n",dp[n]);
	return 0;
}
