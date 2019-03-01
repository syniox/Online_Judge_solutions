#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,m,fac[N<<1],ifac[N<<1];

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

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<=n<<1; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[n<<1]=fpow(fac[n<<1],mod-2);
	for(int i=n<<1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(int x,int y){
	if(x<y||y<0) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int main(){
	n=nxi(),m=nxi();
	init();
	if(n<m){
		puts("0");
		return 0;
	}
	int ans=C(n<<1,n);
	for(int i=1; (i-1)*m-1+(i<<1)<=n; ++i){
		twk(ans+=mod-C(n<<1,n-(i-1)*m+1-(i<<1)));
		twk(ans+=mod-C(n<<1,n-i*m+1-(i<<1)));
		ans=((lint)ans+(C(n<<1,n-i*m-(i<<1))<<1))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
