#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=20;
const int mod=1e9+7;
int n,m,q,hbit[1<<N];
int limit[N+1][N+1],dp[2][1<<N];

template <class T> inline void apadd(T &x,const T y){
	x+y<mod?x=x+y:x=x+y-mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void init(){
	for(int i=2; i<1<<n; ++i){
		hbit[i]=hbit[i>>1]+1;
	}
}

int main(){
	memset(limit,-1,sizeof(limit));
	n=nxi(),m=nxi(),q=nxi();
	--n;
	init();
	for(int i=1; i<=q; ++i){
		const int a=nxi(),b=nxi(),c=nxi();
		limit[a][b]=c;
	}
	dp[0][0]=1;
	for(int i=1; i<=m; ++i){
		for(int j=0; j<n; ++j){
			int p=j&1;
			memset(dp[p^1],0,sizeof(dp[p^1]));
			for(int k=0; k<1<<n; ++k){
				if(!dp[p][k]) continue;
				if((k>>j&1)==0&&limit[i][j+1]!=1){
					//apadd(dp[p^1][k],dp[p][k]);
					dp[p^1][k]=(dp[p^1][k]+dp[p][k])%mod;
				}
				if(limit[i][j+1]!=0){
					int lbit=((k>>j)&-(k>>j))<<j;
					int tgt=k^(1<<j)^lbit;
					dp[p^1][tgt]=(dp[p^1][tgt]+dp[p][k])%mod;
				}
			}
		}
		if(n&1){
			memcpy(dp[0],dp[1],sizeof(dp[1]));
		}
	}
	lint ans=0;
	for(int i=0; i<1<<n; ++i){
		ans+=dp[0][i];
	}
	printf("%lld\n",ans%mod);
	return 0;
}
