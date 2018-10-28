#include<iostream>
#include<cstdio>
#include<cstring>
typedef long double ld;
const int N=205;
ld fac[N],dp[N][N];
bool vis[N][N];
int n,m;

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	fac[0]=1;
	for(int i=1;i<N;++i){
		fac[i]=fac[i-1]*i;
	}
}

inline ld C(const int n,const int k){
	return fac[n]/fac[k]/fac[n-k];
}

inline ld dfs(const int r,const int b){
	if(!r) return 1;
	if(vis[r][b]) return dp[r][b];
	vis[r][b]=1;
	ld ans=0;
	const int limit_i=std::min(r+b,n);
	for(int i=1;i<=limit_i;++i){
		const int limit=std::min(i,r);
		ld cnt=0;
		for(int j=0;j<=limit;++j){
			if(i-j>b) continue;
			cnt+=(1-dfs(r-j,b-(i-j)))*C(r,j)*C(b,i-j)/C(r+b,i);
		}
		apx(ans,cnt);
	}
	return dp[r][b]=ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	init();
	const int r=nxi(),b=nxi();
	n=nxi(),m=nxi();
	ld ans=0;
	for(int i=0;i<=m;++i){
		if(b-(m-i)<0) continue;
		ans+=dfs(r-i,b-(m-i))*C(r,i)*C(b,m-i)/C(r+b,m);
	}
	printf("%.9Lf\n",ans);
	return 0;
}
