#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int mod=924844033;
const int N=2002;
int n,m,fac[N],dp1[N][2],dp2[N][2],dp[N];

inline void twk(int &x){
	if(x>=mod) x-=mod;
	if(x<0) x+=mod;
}

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10-48+c,(c=gtc())>='0'&&c<='9');
	return x;
}

inline void init(){
	fac[0]=1;
	for(int i=1;i<N;++i){
		fac[i]=(lint)fac[i-1]*i;
	}
}

inline void calc(int dp[N][2],int limit){
	for(int i=0;i<=limit;++i){
		dp[i][0]+=dp[i][1];
	}
	for(int i=limit;i;--i){
		int tp=0;
		for(int j=0;j<=i;++j){
			tp=(tp+(lint)dp[j][0]*dp[i-j][0])%mod;
		}
		dp[i][0]=tp;
	}
}

inline void getans(int dp[N],int dp2[N][2],int len){
	for(int i=1;i<=len;++i){
		for(int j=m;j>=0;--j){
			int cnt=0;
			for(int k=0;k<=j;++k){
				cnt=(cnt+(lint)dp[k]*dp2[j-k][0])%mod;
			}
			dp[j]=cnt;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	init();
	n=nxi(),m=nxi();
	int limit=n/m;
	dp1[0][0]=1;
	for(int i=2;i<=limit;++i){
		for(int j=limit;j;--j){
			dp1[j][0]=dp1[j][0]+dp1[j][1];
			dp1[j][1]=dp1[j-1][0];
		}
	}
	memcpy(dp2,dp1,sizeof(dp1));
	calc(dp1,limit);
	for(int i=limit+1;i;--i){
		twk(dp2[i][0]=dp2[i][0]+dp2[i][1]);
		dp2[i][1]=dp2[i-1][0];
	}
	calc(dp2,limit+1);
	dp[0]=1;
	getans(dp,dp1,n-n%m);
	getans(dp,dp2,n%m);
	int ans=0;
	for(int i=1;i<=m;++i){
		twk(ans+=(i&1?1:-1)*dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}
