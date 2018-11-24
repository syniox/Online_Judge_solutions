#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=10;
const int mod=998244353;
int n;
lint ql[N],qr[N],lim[N],dp[60][1<<9];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int dfs(const int t,const int st){
	if(t<0) return 1;
	if(dp[t][st]) return dp[t][st];
	int p=st;
	for(int i=1;i<=n;++i){
		if(p&1<<(i-1)&&lim[i]&1ll<<t) p^=1<<(i-1);
	}
	//total: zero
	int ans=dfs(t-1,p);
	//total: one
	for(int i=1;i<=n;++i){
		if((p&1<<(i-1))==0){
			twk(ans+=dfs(t-1,p|(st&1<<(i-1))));
		}
	}
	return dp[t][st]=ans;
}

inline int solve(const int t){
	memset(dp,0,sizeof(dp));
	int cnt=0;
	for(int i=1;i<=n;++i){
		if(t&1<<(i-1)) lim[i]=qr[i];
		else lim[i]=ql[i]-1,++cnt;
		if(lim[i]<0) return 0;
	}
	return cnt&1?mod-dfs(55,(1<<n)-1):dfs(55,(1<<n)-1);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi<int>();
	for(int i=1;i<=n;++i){
		ql[i]=nxi<lint>()-1,qr[i]=nxi<lint>()-1;
	}
	int ans=0;
	for(int i=0;i<1<<n;++i){
		twk(ans+=solve(i));
	}
	printf("%d\n",ans);
	return 0;
}
