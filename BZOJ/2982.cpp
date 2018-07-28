#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int mod=10007;
int fac[mod],inv[mod];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans(1);
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1;i<mod;++i){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[mod-1]=qpow(fac[mod-1],mod-2);
	for(int i=mod-1;i;--i){
		inv[i-1]=inv[i]*i%mod;
	}
}

inline int C(int n,int m){
	if(n<m) return 0;
	if(n<mod) return fac[n]*inv[m]%mod*inv[n-m]%mod;
	return C(n/mod,m/mod)*C(n%mod,m%mod)%mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	init();
	int T=nxi();
	while(T--){
		int n=nxi(),m=nxi();
		printf("%d\n",C(n,m));
	}
	return 0;
}
