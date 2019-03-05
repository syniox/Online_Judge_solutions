#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int n,m,q,dp[N][2],pre_dp[N];
//dp([i])[j][0/1]: 枚举到第i位,现在有j个1,末尾为0/1的方案数

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_dp(const int x){
	return x<0?0:pre_dp[x];
}

int main(){
	m=nxi(),n=nxi(),q=nxi();
	int len=(n+m-1)/(q-1);
	int ans=0;
	dp[0][0]=1;
	for(int i=1; i<=len; ++i){
		pre_dp[0]=(dp[0][0]+dp[0][1])%mod;
		for(int j=1; j<=n; ++j){
			pre_dp[j]=((lint)pre_dp[j-1]+dp[j][0]+dp[j][1])%mod;
		}
		for(int j=0; j<=n; ++j){
			dp[j][0]=(pre_dp[j]-get_dp(j-1)+mod)%mod;
			dp[j][1]=(get_dp(j-1)-get_dp(j-q)+mod)%mod;
		}
		int all_bit=(lint)(q-1)*i%mod;
		for(int j=0; j<=n; ++j){
			int zero_cnt=(all_bit-j+mod)%mod;
			if(j%(q-1)==n%(q-1)&&zero_cnt<m&&zero_cnt%(q-1)==(m-1)%(q-1)){
				ans=(ans+dp[j][1])%mod;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
