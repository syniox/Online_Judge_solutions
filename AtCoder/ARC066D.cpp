#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=64;
const int mod=1e9+7;
bool lim[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline T nxi(){
		T x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

//p: 进位　up: 上界
int dfs_dp(const int t,const bool p,const bool up){
	static int dp[N][2][2];
	if(t<0) return !p;
	if(dp[t][p][up]) return dp[t][p][up];
	int ans=0;
	bool u0=up&&(lim[t]==0);
	if(p==0){
		ans=(ans+dfs_dp(t-1,0,u0))%mod;		//0 0
		if(!up||lim[t]){
			ans=(ans+dfs_dp(t-1,1,up))%mod;	//0 0
			ans=(ans+dfs_dp(t-1,0,up))%mod;	//0 1
		}
	}
	else{
		ans=(ans+dfs_dp(t-1,1,u0))%mod;		//0 1
		ans=(ans+dfs_dp(t-1,0,u0))%mod;		//1 1
		if(!up||lim[t]){
			ans=(ans+dfs_dp(t-1,1,up))%mod;	//1 1
		}
	}
	return dp[t][p][up]=ans;
}

int solve(lint n){
	int t=0;
	for(; n; ++t,n>>=1){
		lim[t]=n&1;
	}
	return dfs_dp(t,0,1);
}

int main(){
	printf("%d\n",solve(nxi<lint>()));
	return 0;
}
