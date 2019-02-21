#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2005;
const int N2=N*N;
const int mod=1e9+7;
int n,m,fac[N2],inv[N2],dp[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N2; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	inv[N2-1]=fpow(fac[N2-1],mod-2);
	for(int i=N2-1; i; --i){
		inv[i-1]=(lint)inv[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

int main(){
	n=nxi(),m=nxi();
	if(m==1){
		puts("1");
		return 0;
	}
	init();
	dp[0][0]=1;
	for(int i=1; i<=n; ++i){
		dp[i][0]=dp[i-1][0];
		for(int j=1; j<=i; ++j){
			dp[i][j]=dp[i-1][j];
			const int rest=n*m-i-(j-1)*(m-1)-1;
			//make sequence unique
			dp[i][j]=(dp[i][j]+(lint)dp[i][j-1]*C(rest,m-2))%mod;
		}
	}
	printf("%lld\n",(lint)dp[n][n]*fac[n]%mod);
	return 0;
}
