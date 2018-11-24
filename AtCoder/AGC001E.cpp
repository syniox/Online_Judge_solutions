#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int n,ans,fac[N<<2],inv[N<<2],dp[N<<1][N<<1];
struct pnt{
	int x,y;
}pt[(int)2e5+2];

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

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init_C(){
	fac[0]=1;
	for(int i=1;i<N<<2;++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	inv[(N<<2)-1]=qpow(fac[(N<<2)-1],mod-2);
	for(int i=(N<<2)-1;i;--i){
		inv[i-1]=(lint)inv[i]*i%mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("e.in","r",stdin);
#endif
	init_C();
	n=nxi();
	for(int i=1;i<=n;++i){
		const int x=nxi(),y=nxi();
		twk(ans+=mod-C((x+y)<<1,x<<1));
		pt[i]=(pnt){x,y};
		++dp[N-x][N-y];
	}
	for(int i=1;i<N<<1;++i){
		for(int j=1;j<N<<1;++j){
			twk(dp[i][j]+=dp[i-1][j]);
			twk(dp[i][j]+=dp[i][j-1]);
		}
	}
	for(int i=1;i<=n;++i){
		twk(ans+=dp[pt[i].x+N][pt[i].y+N]);
	}
	printf("%lld\n",(lint)ans*inv[2]%mod);
	return 0;
}
