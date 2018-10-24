#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e6+2;
const int mod=1e9+7;
int n,dp[N];

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

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	const int base=(lint)(n-1)*(n-1)%mod;
	int pre=0,ans=base+(n>1);
	dp[0]=1;
	for(int i=1;i<=n;++i){
		if(i-3>=0) twk(pre+=dp[i-3]);
		twk(dp[i]=dp[i-1]+pre);
		if(i<n-1){
			ans=(ans+(lint)dp[i]*base)%mod;
			ans=(ans+(n-(n-i)+1)*(lint)dp[i])%mod;
		}
		else if (i==n-1){
			ans=(ans+(lint)dp[i]*(n-1))%mod;
		}
	}
	twk(ans+=dp[n]);
	printf("%d\n",ans);
	return 0;
}
