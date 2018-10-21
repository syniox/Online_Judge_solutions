#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=5e5+2;
const int mod=998244353;
int n,m,fac[N<<1],inv[N<<1];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(const int T){
	fac[0]=1;
	for(int i=1;i<=T;++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	inv[T]=qpow(fac[T],mod-2);
	for(int i=T;i;--i){
		inv[i-1]=(lint)inv[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	if(n<m) std::swap(n,m);
	init(n+m);
	int ans=0;
	for(int i=1;i<=m;++i){
		ans=(ans+(lint)C(i<<1,i)*C(n+m-(i<<1),n-i))%mod;
	}
	ans=(lint)ans*qpow(C(n+m,n),mod-2)%mod*inv[2]%mod;
	printf("%d\n",(ans+n)%mod);
	return 0;
}
