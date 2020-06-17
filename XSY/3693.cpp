#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=50005;
const int mod=998244353;
int n,ans,g[N],dp[N][5];
//dp[i][j]: 做了前i位 红蓝球状态为j 为4代表此球相对

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T1,class T2>
inline void apadd(T1 &a,const T2 b){
	a=(a+b)%mod;
}

inline int pw2(int x){
	return (lint)x*x%mod;
}
inline void fold_add(int *to,int val,int len){
	for(int i=0; i<len; ++i) apadd(to[i],val);
}
inline int fold_sum(int *v,int len){
	int ans=0;
	for(int i=0; i<len; ++i) apadd(ans,v[i]);
	return ans;
}

void get_dp(){
	for(int i=0; i<n; ++i){
		for(int j=0; j<=4; ++j){
			const int cur=dp[i][j];
			if(!cur) continue;
			//均不终结
			apadd(dp[i+2][(j&3)],cur);
			apadd(dp[i+4][(j&3)],cur);
			if(!(j&1)){
				apadd(dp[i+2][(j&3)|1],cur*2ll);
				apadd(dp[i+4][(j&3)|1],cur*4ll);
			}
			if(!(j&2)){
				apadd(dp[i+2][(j&3)|2],cur*2ll);
				apadd(dp[i+4][(j&3)|2],cur*4ll);
			}
			if(!(j&3)){
				apadd(dp[i+2][(j&3)|3],cur*4ll);
				apadd(dp[i+4][(j&3)|3],cur*16ll);
			}
		}
		apadd(dp[i+1][4],dp[i][3]);
		fold_add(dp[i+3],fold_sum(dp[i],5),4);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	g[0]=1,g[1]=0;
	for(int i=0; i<n-1; ++i){
		apadd(g[i+2],g[i]),apadd(g[i+4],g[i]);
	}
	ans=(lint)g[n-1]*pw2(n-1)%mod*n%mod;
	ans=(ans+(lint)g[n-3]*pw2(n-1)%mod*n)%mod;
	dp[0][4]=1;
	get_dp();
	for(int i=1; n-i-2>=0; ++i){//1+1
		ans=(ans+(lint)(i+1)*pw2(i)%mod*g[i]%mod*dp[n-i-2][3])%mod;
	}
	for(int i=0; n-i-4>=0; ++i){//3+1
		ans=(ans+(lint)(i+2)*pw2(i+1)%mod*g[i]%mod*fold_sum(dp[n-i-4],5))%mod;
	}
	memset(dp,0,sizeof(dp));
	fold_add(dp[0],1,4);
	get_dp();
	for(int i=0; n-i-4>=0; ++i){//1+3
		ans=(ans+(lint)(i+2)*pw2(i+1)%mod*g[i]%mod*dp[n-i-4][3])%mod;
	}
	for(int i=0; n-i-6>=0; ++i){//3+3
		ans=(ans+(lint)(i+3)*pw2(i+2)%mod*g[i]%mod*fold_sum(dp[n-i-6],5))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
