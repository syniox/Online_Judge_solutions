#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e7+5;
const int mod=998244353;
int fac[N<<1],ifac[N<<1];

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

inline int qpow(int x,int t){
	int ans=1;
	for(;t;t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1;i<N<<1;++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[(N<<1)-1]=qpow(fac[(N<<1)-1],mod-2);
	for(int i=(N<<1)-1;i;--i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(int x,int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	int n=nxi()-1,m=nxi();
	init();
	int ans=C(n<<1,n);
	for(int i=0;i<=n;i+=m){
		twk(ans+=mod-C(n<<1,n+i+1));
		twk(ans+=mod-C(n<<1,n+m+i-1));
		ans=(ans+(lint)(C(n<<1,n+m+i)<<1))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
