#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
typedef long long lint;
const int N=1e6+2;
int n,p,jc[N],cj[N],dp[N],sz[N];
//dp[i]=C(sz[i]-1,sz[left[i]])*dp[i<<1]*dp[d<<1|1];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t,const int mod){
	lint ans(1);
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline void init(const int mod){
	jc[0]=1;
	const int P=std::min(N,mod);
	for(int i=1;i<P;++i){
		jc[i]=(lint)jc[i-1]*i%mod;
	}
	cj[P-1]=qpow(jc[P-1],mod-2,mod);
	for(int i=P-1;i;--i){
		cj[i-1]=(lint)cj[i]*i%mod;
	}
}


inline lint C(const int n,const int k,const int mod){
	return (lint)jc[n]*cj[k]%mod*cj[n-k]%mod;
}

inline lint get_C(const int n,const int k,const int mod){
	if(k<mod) return C(n,k,mod);
	return C(n/mod,k/mod,mod)*C(n%mod,k%mod,mod)%mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("3014.in","r",stdin);
#endif
	n=nxi(),p=nxi();
	init(p);
	const int mod=p;
	for(int i=n;i;--i){
		sz[i]=1+sz[i<<1]+sz[i<<1|1];
		dp[i]=get_C(sz[i]-1,sz[i<<1],mod)*(i<<1>n?1:dp[i<<1])%mod*((i<<1|1)>n?1:dp[i<<1|1])%mod;
	}
	printf("%d\n",dp[1]);
	return 0;
}
