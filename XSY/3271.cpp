#include <iostream>
#include <cstdio>
#include <cstring>
typedef long double ld;
const int N=105;
int qr,qb,n,m;
ld dp[N][N];//still have red balls
ld fac[N<<1];
bool vis[N][N];

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
	for(int i=1;i<N<<1;++i){
		fac[i]=fac[i-1]*i;
	}
}

inline ld C(const int x,const int y){
	if(x<y) return 0;
	return fac[x]/fac[y]/fac[x-y];
}

ld dfs(const int r,const int b){
	if(!r||r+b<=m) return 1;
	if(vis[r][b]) return dp[r][b];
	vis[r][b]=1;
	ld ans=0;
	const int limit_i=std::min(n,r+b);
	for(int i=1;i<=limit_i;++i){
		const int limit_j=std::min(n,r);
		ld cnt=0;
		if(r+b-i<=m) break;
		for(int j=0;j<=limit_j;++j){
			if(b-(i-j)<0) continue;
			const ld not_end=1-C(m,r-j)/C(r+b-i,r-j);
			cnt+=C(i,j)*C(r+b-i,r-j)/(C(r+b,r)-C(m,r))*not_end*(1-dfs(r-j,b-(i-j)));
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
	qr=nxi(),qb=nxi(),n=nxi(),m=nxi();
	printf("%.9lf\n",(double)dfs(qr,qb));
	return 0;
}
