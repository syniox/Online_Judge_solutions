#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e7+5;
const int mod=1e9+7;
int n,fac[N],ifac[N],inv[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
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
}

inline int C(const int x,const int y){
	if(x<y||y<0) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

inline int invC(const int x,const int y){
	if(x<y||y<0) return 0;
	return (lint)ifac[x]*fac[y]%mod*fac[x-y]%mod;
}

int main(){
	init();
	n=nxi();
	int ans=0;
	for(int i=0; i<n>>1; ++i){
		ans=(ans+inv[n-i])%mod;
	}
	for(int i=n>>1; i<=n; ++i){
		int res=(lint)C(i,n-i)*invC(n-1,i-1)%mod;
		ans=(ans+(lint)(1-res)*inv[n-i])%mod;
	}
	if(ans<0) ans+=mod;
	printf("%lld\n",(lint)ans*n%mod);
	return 0;
}
