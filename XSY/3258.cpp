#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int n,dp[N*2][2];
char mp[3][N];

namespace utils{
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

inline int A(const int x,const int y){
	if(x<y) return 0;
	if(!y) return 1;
	return y==1?x:(lint)x*(x-1)%mod;
}

int solve(){
	//0: 预填
	if(mp[0][0]=='x'||mp[2][0]=='x'||mp[0][n-1]=='x'||mp[2][n-1]=='x'){
		return 0;
	}
	for(int i=0; i<n-1; ++i){
		if(mp[0][i]=='x'&&mp[0][i+1]=='x') return 0;
		if(mp[2][i]=='x'&&mp[2][i+1]=='x') return 0;
	}
	int sum=0;
	dp[sum+=(mp[1][0]=='x')][0]=1;
	//dp[i][j][k] k=0: 放置时上下已成型 k=1: 放置时上下未成型
	for(int i=1; i<n; ++i){
		static int p0[N*2],p1[N*2];
		int xcnt=(mp[0][i]=='x')+(mp[1][i]=='x')+(mp[2][i]=='x');
		p0[0]=dp[0][0];
		sum+=xcnt;
		for(int j=1; j<=sum; ++j){
			p0[j]=(p0[j-1]+dp[j][0])%mod;
		}
		p1[sum]=dp[sum][1];
		for(int j=sum-1; ~j; --j){
			p1[j]=(p1[j+1]+dp[j][1])%mod;
		}
		memset(dp,0,sizeof(dp));
		if(mp[1][i]=='o'){
			dp[0][0]=(lint)(p0[sum-xcnt]+p1[0])*A(sum,xcnt)%mod;
			continue;
		}
		for(int j=1; j<=sum; ++j){
			if(xcnt==1){
				dp[j][0]=(p0[sum-xcnt]+p1[j])%mod;
			}
			else if (xcnt==2){
				dp[j][0]=(lint)(p0[sum-xcnt]+p1[j-1])*(j-1)%mod;
				dp[j][1]=(lint)p0[j-1]*(sum-j)%mod;
			}
			else{
				dp[j][0]=(lint)(p0[sum-xcnt]+p1[j-1])*A(j-1,2)%mod;
				dp[j][1]=(lint)p0[j-1]*A(sum-j,2)%mod;
				dp[j][1]=(dp[j][1]+(lint)p0[j-2]*(sum-j)%mod*(j-1)*2)%mod;
			}
		}
	}
	int ans=0;
	for(int i=0; i<=sum; ++i){
		ans=(ans+dp[i][0])%mod;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=0; i<3; ++i){
		scanf("%s",mp[i]);
	}
	printf("%d\n",solve());
	return 0;
}
