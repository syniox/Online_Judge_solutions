#include <iostream>
#include <cstdio>
#include <cstring>
const int N=13;
const int mod=1e8;
int n,m,st[N],dp[2][1<<12];

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

inline int solve(){
	int ans=0;
	for(int i=0;i<1<<m;++i){
		twk(ans+=dp[n&1][i]);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			st[i]|=((nxi()^1)<<(j-1));
		}
	}
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		const int p=i&1;
		for(int j=0;j<1<<m;++j){
			dp[p][j]=0;
			if(j&j>>1||j&st[i]) continue;
			for(int k=j;k<1<<m;k=j|(k+1)){
				if(!(st[i-1]&(k^j))||(k^j)&(k^j)>>1){
					twk(dp[p][j]+=dp[p^1][k^j]);
				}
			}
		}
	}
	printf("%d\n",solve());
	return 0;
}
