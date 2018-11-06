#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int fac[N],inv[N];

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
	for(;t;x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

inline void init(){
	fac[0]=1;
	for(int i=1;i<N;++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-1;i;--i){
		inv[i-1]=(lint)inv[i]*i%mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	nxi();
	int ans=1;
	for(int i=nxi();i;--i){
		const int l=nxi(),r=nxi(),k=nxi();
		ans=((lint)ans*(C(r+1,l-k+1)-C(l,l-k+1)+mod))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
