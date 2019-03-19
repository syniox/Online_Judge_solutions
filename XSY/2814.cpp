#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=105;
const int mod=998244353;
int n,q,fac[N],poly[N],inv[N],ifac[N],dp[N][N],wdt[N],st2[N][N];
//dp[i][j]表示已经拥有i个球之后的期望步数的j次方
//poly[i]表示自然数幂求和展开之后每一项的系数
//$\sum_ {i=1}^ {t} i^m = \sum_ {k=1}^ m \frac{\{^ m_ k\}}{k+1}(t+1)^ \underline{k+1}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=fpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
		inv[i]=(lint)ifac[i]*fac[i-1]%mod;
	}
	st2[0][0]=1;
	for(int i=1; i<N; ++i){
		for(int j=1; j<=i; ++j){
			st2[i][j]=((lint)st2[i-1][j]*j+st2[i-1][j-1])%mod;
		}
	}
}

inline void get_poly(){
	static int cur[N];
	cur[0]=1;
	for(int i=0; i<=q; ++i){
		for(int j=i+1; j; --j){
			cur[j]=((lint)cur[j]*-(i-1)+cur[j-1])%mod;
		}
		cur[0]=(lint)cur[0]*-(i-1)%mod;
		int wdt=(lint)st2[q][i]*inv[i+1]%mod;
		for(int j=0; j<=i+1; ++j){
			poly[j]=(poly[j]+(lint)wdt*cur[j])%mod;
		}
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[x-y]%mod*ifac[y]%mod;
}

int main(){
	n=nxi(),q=nxi();
	init();
	get_poly();
	dp[n][0]=1;
	for(int i=n-1; ~i; --i){
		dp[i][0]=1;
		for(int j=1; j<=q+1; ++j){
			int res=0;
			for(int k=0; k<j; ++k){
				res=(res+(lint)dp[i][k]*C(j,k)%mod*i)%mod;
				res=(res+(lint)dp[i+1][k]*C(j,k)%mod*(n-i))%mod;
			}
			res=(res+(lint)dp[i+1][j]*(n-i))%mod;
			dp[i][j]=(lint)res*inv[n-i]%mod;
		}
	}
	int ans=0;
	for(int i=0; i<=q+1; ++i){
		ans=(ans+(lint)poly[i]*dp[0][i])%mod;
	}
	if(q==0&&--ans==-1) ans=mod-1;
	printf("%d\n",ans);
	return 0;
}
