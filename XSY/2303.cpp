#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int M=3005;
const int mod=1e9+7;
int n,m,val[M],Cm[M],dp[(int)1e7];

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
	Cm[0]=1;
	for(int i=1; i<=m; ++i){
		Cm[i]=(lint)Cm[i-1]*(n-m-i+1)%mod*fpow(i,mod-2)%mod;
	}
	dp[0]=1,dp[1]=1;
	for(int i=2; i<=n-m; ++i){
		dp[i]=(dp[i-1]+(lint)dp[i-2]*(i-1))%mod;
	}
}

int solve(const int t){
	static int que[M];
	int v=1;
	for(int i=1; i<t; ++i){
		if(val[i]<val[t]) ++v;
		else ++que[i];
	}
	que[t]=v;
	if(n-m<m-t) return 0;
	for(int i=1; i<=t; ++i){
		if(que[que[i]]!=i) return 0;
	}
	return (lint)Cm[m-t]*dp[n-(m<<1)+t]%mod;
}

int main(){
	n=nxi(),m=nxi();
	init();
	for(int i=1; i<=m; ++i){
		val[i]=nxi();
	}
	int ans=m<=n-m?(lint)Cm[m]*dp[n-(m<<1)]%mod:0;
	for(int k=1; k<=m; ++k){
		ans=(ans+solve(k))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
