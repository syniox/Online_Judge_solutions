#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=5005;//!!!
const int mod=998244353;

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

inline void get(int dp[][2]){
	static int tdp[N<<1][2];
	static char ch[N];
	scanf("%s",ch+1);
	int n=strlen(ch+1);
	dp[N][1]=1;
	for(int i=n; i; --i){
		const int dis=n-i+1;
		memcpy(tdp+N-dis,dp+N-dis,((dis+1)<<1)*sizeof(tdp[0]));
		memset(dp+N-dis,0,((dis+1)<<1)*sizeof(tdp[0]));
		for(int j=N-dis; j<=N+dis; ++j){
			if(ch[i]!='V'){
				if(j<=N){
					twk(dp[j-1][0]+=tdp[j][0]);
					twk(dp[j-1][1]+=tdp[j][1]);
				}
				else{
					twk(dp[N][0]+=tdp[j][0]);
					twk(dp[N][0]+=tdp[j][1]);
				}
			}
			if(ch[i]!='P'){
				twk(dp[j+1][0]+=tdp[j][0]);
				twk(dp[j+1][1]+=tdp[j][1]);
			}
		}
	}
}

inline int solve(int dp0[][2],int dp1[][2]){
	int ans=0;
	for(int i=1; i<N<<1; ++i){
		ans=(ans+(lint)dp0[i][1]*dp1[(N<<1)-i][1])%mod;
	}
	for(int i=(N<<1)-1; i; --i){
		twk(dp1[i-1][0]+=dp1[i][0]);
		twk(dp1[i-1][1]+=dp1[i][1]);
	}
	for(int i=1; i<N<<1; ++i){
		ans=(ans+(lint)(dp0[i][0]+dp0[i][1])*dp1[(N<<1)-i+1][0])%mod;
		ans=(ans+(lint)(dp0[i][0]+dp0[i][1])*dp1[(N<<1)-i+1][1])%mod;
	}
	return ans;
}

int main(){
	static int dp0[N<<1][2],dp1[N<<1][2];
	get(dp0);
	get(dp1);
	printf("%d\n",solve(dp0,dp1));
	return 0;
}
